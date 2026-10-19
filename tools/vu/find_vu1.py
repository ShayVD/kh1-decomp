#!/usr/bin/env python3
"""List the VU microprograms in the user's SLPS_251.98 (and overlays), where
they are uploaded from and who kicks them; optionally disassemble one.

  python3 -I tools/vu/find_vu1.py [ELF] [--layout layout.tsv]
  python3 -I tools/vu/find_vu1.py [ELF] --disasm N      # program N to stdout
  python3 -I tools/vu/find_vu1.py [ELF] --summary N     # per-program usage summary
  python3 -I tools/vu/find_vu1.py --overlay FILE.x [...]   # MPG scan of an overlay

Standalone (Python >= 3.10, stdlib only). Reads only the files given.
Default output is addresses, sizes and names only: no game bytes. The
--disasm output is derived from the user's own ELF at run time and must not
be committed (README: no game data in this repository).

How programs are found
  * The ELF keeps dvp-as's overlay table (.DVP.ovlytab: {name, LMA in main
    RAM, VMA in VU micro memory}) and one .DVP.overlay.* section per MPG
    chunk. dvp-as splits a program into 256-instruction MPG chunks; a chunk
    whose name says `unknvma` continues the previous program. Each chunk in
    main RAM is preceded by its VIF MPG code (0x4A, NUM, ADDR) in the word
    before it, which this tool checks.
  * Without section headers (or for overlays) MPG codes are found by a scan:
    a word 0x4Annaaaa in an odd word slot whose NUM*8 bytes decode as VU
    code (>= 95% known upper and lower opcodes).
  * Carriers: the qword that holds the MPG code is either inside a DMA END
    or CNT packet (tag found by walking back over the VIF stream) or is the
    ADDR of a REF tag somewhere in the data (tag tables). Code references
    to the carrier (lui + addiu/ori/load pairs) and data words holding it
    are listed with the function (layout.tsv) they are in.
"""
from __future__ import annotations

import argparse
import bisect
import struct
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
TEXT_LO, TEXT_HI = 0x00100000, 0x00272C70
VU1_MICRO = 0x4000  # 16 KB of VU1 micro memory (VU0: 4 KB)

# ---------------------------------------------------------------- ELF ----


class Image:
    """The main ELF's PT_LOAD segment as a flat little-endian memory view."""

    def __init__(self, path: Path):
        self.raw = path.read_bytes()
        d = self.raw
        if d[:4] != b"\x7fELF":
            sys.exit(f"{path}: not an ELF")
        phoff, shoff = struct.unpack_from("<II", d, 0x1C)
        phentsize, phnum, shentsize, shnum, shstrndx = struct.unpack_from("<HHHHH", d, 0x2A)
        self.segs = []
        for i in range(phnum):
            p_type, off, vaddr, _pa, filesz, memsz = struct.unpack_from("<6I", d, phoff + i * phentsize)
            if p_type == 1:
                self.segs.append((vaddr, off, filesz))
        self.sections = []
        if shoff and shnum:
            hdrs = [struct.unpack_from("<10I", d, shoff + i * shentsize) for i in range(shnum)]
            stro = hdrs[shstrndx][4]
            for h in hdrs:
                name = d[stro + h[0]: d.index(b"\0", stro + h[0])].decode("latin-1")
                self.sections.append((name, h[1], h[3], h[4], h[5]))  # name type addr off size

    def ok(self, a: int, n: int = 4) -> bool:
        return any(v <= a and a + n <= v + fs for v, _o, fs in self.segs)

    def w(self, a: int) -> int:
        for v, o, fs in self.segs:
            if v <= a < v + fs:
                return struct.unpack_from("<I", self.raw, o + a - v)[0]
        raise KeyError(hex(a))

    def words(self):
        for v, o, fs in self.segs:
            for a in range(v, v + fs - 3, 4):
                yield a, struct.unpack_from("<I", self.raw, o + a - v)[0]


# ------------------------------------------------------- VU disassembler --

BC = "xyzw"
UP_BC = ["add", "sub", "madd", "msub", "max", "mini", "mul"]
UP_STD = {0x1C: "mulq", 0x1D: "maxi", 0x1E: "muli", 0x1F: "minii",
          0x20: "addq", 0x21: "maddq", 0x22: "addi", 0x23: "maddi",
          0x24: "subq", 0x25: "msubq", 0x26: "subi", 0x27: "msubi",
          0x28: "add", 0x29: "madd", 0x2A: "mul", 0x2B: "max",
          0x2C: "sub", 0x2D: "msub", 0x2E: "opmsub", 0x2F: "mini"}
# extended upper: index (bits 10..6) -> 4 names by bits 1..0
UP_EXT = {0: ["addax", "adday", "addaz", "addaw"],
          1: ["subax", "subay", "subaz", "subaw"],
          2: ["maddax", "madday", "maddaz", "maddaw"],
          3: ["msubax", "msubay", "msubaz", "msubaw"],
          4: ["itof0", "itof4", "itof12", "itof15"],
          5: ["ftoi0", "ftoi4", "ftoi12", "ftoi15"],
          6: ["mulax", "mulay", "mulaz", "mulaw"],
          7: ["mulaq", "abs", "mulai", "clip"],
          8: ["addaq", "maddaq", "addai", "maddai"],
          9: ["subaq", "msubaq", "subai", "msubai"],
          10: ["adda", "madda", "mula", None],
          11: ["suba", "msuba", "opmula", "nop"]}
LO_EXT = {12: ["move", "mr32", None, None],
          13: ["lqi", "sqi", "lqd", "sqd"],
          14: ["div", "sqrt", "rsqrt", "waitq"],
          15: ["mtir", "mfir", "ilwr", "iswr"],
          16: ["rnext", "rget", "rinit", "rxor"],
          25: ["mfp", None, None, None],
          26: ["xtop", "xitop", None, None],
          27: ["xgkick", None, None, None],
          28: ["esadd", "ersadd", "eleng", "erleng"],
          29: ["eatanxy", "eatanxz", "esum", None],
          30: ["esqrt", "ersqrt", "ercpr", "waitp"],
          31: ["esin", "eatan", "eexp", None]}
LO_MAIN = {0x00: "lq", 0x01: "sq", 0x04: "ilw", 0x05: "isw", 0x08: "iaddiu", 0x09: "isubiu",
           0x10: "fceq", 0x11: "fcset", 0x12: "fcand", 0x13: "fcor",
           0x14: "fseq", 0x15: "fsset", 0x16: "fsand", 0x17: "fsor",
           0x18: "fmeq", 0x1A: "fmand", 0x1B: "fmor", 0x1C: "fcget",
           0x20: "b", 0x21: "bal", 0x24: "jr", 0x25: "jalr",
           0x28: "ibeq", 0x29: "ibne", 0x2C: "ibltz", 0x2D: "ibgtz", 0x2E: "iblez", 0x2F: "ibgez"}
LO_OP = {0x30: "iadd", 0x31: "isub", 0x32: "iaddi", 0x34: "iand", 0x35: "ior"}
BRANCHES = {"b", "bal", "ibeq", "ibne", "ibltz", "ibgtz", "iblez", "ibgez"}


def _dest(w: int) -> str:
    return "".join(c for i, c in enumerate("xyzw") if w >> (24 - i) & 1)


def _s11(v: int) -> int:
    return v - 0x800 if v & 0x400 else v


def upper(w: int) -> str | None:
    dest, ft, fs, fd, o = _dest(w), w >> 16 & 31, w >> 11 & 31, w >> 6 & 31, w & 63
    flags = "".join(f for b, f in ((31, "[I]"), (30, "[E]"), (29, "[M]"), (28, "[D]"), (27, "[T]")) if w >> b & 1)
    if o >= 0x3C:
        idx, bc = fd, o & 3
        names = UP_EXT.get(idx)
        name = names[bc] if names else None
        if name is None:
            return None
        if name == "nop":
            s = "nop"
        elif name == "clip":
            s = f"clipw.xyz vf{fs:02d}, vf{ft:02d}w"
        elif name.startswith(("itof", "ftoi", "abs")):
            s = f"{name}.{dest} vf{ft:02d}, vf{fs:02d}"
        elif name[-1] in "q" or name[-1] == "i" and name not in ("mulai",) and name.endswith("ai") or name in ("mulai",):
            s = f"{name}.{dest} ACC, vf{fs:02d}, {name[-1].upper()}"
        elif name[-1] in BC and name[:-1] in ("adda", "suba", "madda", "msuba", "mula"):
            s = f"{name}.{dest} ACC, vf{fs:02d}, vf{ft:02d}{name[-1]}"
        else:
            s = f"{name}.{dest} ACC, vf{fs:02d}, vf{ft:02d}"
        return (s + " " + flags).rstrip()
    if o < 0x1C:
        name = UP_BC[o >> 2] + BC[o & 3]
        s = f"{name}.{dest} vf{fd:02d}, vf{fs:02d}, vf{ft:02d}{BC[o & 3]}"
    elif o in UP_STD:
        name = UP_STD[o]
        if name.endswith(("q", "i")) and name not in ("mini",):
            s = f"{name}.{dest} vf{fd:02d}, vf{fs:02d}, {name[-1].upper()}"
        else:
            s = f"{name}.{dest} vf{fd:02d}, vf{fs:02d}, vf{ft:02d}"
    else:
        return None
    return (s + " " + flags).rstrip()


def lower(w: int, pc: int) -> tuple[str | None, int | None]:
    """(text, branch target instruction index or None)."""
    o = w >> 25
    dest = _dest(w)
    it, is_, id_ = w >> 16 & 31, w >> 11 & 31, w >> 6 & 31
    imm11 = _s11(w & 0x7FF)
    if o == 0x40:
        f = w & 63
        if f >= 0x3C:
            names = LO_EXT.get(id_)
            name = names[w & 3] if names else None
            if name is None:
                return None, None
            fsf, ftf = BC[w >> 21 & 3], BC[w >> 23 & 3]
            if name == "move" and w == 0x8000033C:
                return "nop", None
            if name in ("move", "mr32"):
                return f"{name}.{dest} vf{it:02d}, vf{is_:02d}", None
            if name in ("lqi", "lqd"):
                return f"{name}.{dest} vf{it:02d}, ({'--' if name == 'lqd' else ''}vi{is_:02d}{'++' if name == 'lqi' else ''})", None
            if name in ("sqi", "sqd"):
                return f"{name}.{dest} vf{is_:02d}, ({'--' if name == 'sqd' else ''}vi{it:02d}{'++' if name == 'sqi' else ''})", None
            if name in ("div", "rsqrt"):
                return f"{name} Q, vf{is_:02d}{fsf}, vf{it:02d}{ftf}", None
            if name == "sqrt":
                return f"sqrt Q, vf{it:02d}{ftf}", None
            if name in ("waitq", "waitp"):
                return name, None
            if name == "mtir":
                return f"mtir vi{it:02d}, vf{is_:02d}{fsf}", None
            if name == "mfir":
                return f"mfir.{dest} vf{it:02d}, vi{is_:02d}", None
            if name in ("ilwr", "iswr"):
                return f"{name}.{dest} vi{it:02d}, (vi{is_:02d})", None
            if name in ("xtop", "xitop"):
                return f"{name} vi{it:02d}", None
            if name == "xgkick":
                return f"xgkick vi{is_:02d}", None
            if name == "mfp":
                return f"mfp.{dest} vf{it:02d}, P", None
            if name in ("esadd", "ersadd", "eleng", "erleng", "esum"):
                return f"{name} P, vf{is_:02d}", None
            if name.startswith("eatanx"):
                return f"{name} P, vf{is_:02d}", None
            if name.startswith("r"):
                return f"{name}.{dest} vf{it:02d}, R" if name in ("rnext", "rget") else f"{name} R, vf{is_:02d}{fsf}", None
            return f"{name} P, vf{is_:02d}{fsf}", None
        if f in LO_OP:
            name = LO_OP[f]
            if name == "iaddi":
                v = id_ - 32 if id_ & 16 else id_
                return f"iaddi vi{it:02d}, vi{is_:02d}, {v}", None
            return f"{name} vi{id_:02d}, vi{is_:02d}, vi{it:02d}", None
        return None, None
    name = LO_MAIN.get(o)
    if name is None:
        return None, None
    if name == "lq":
        return f"lq.{dest} vf{it:02d}, {imm11}(vi{is_:02d})", None
    if name == "sq":
        return f"sq.{dest} vf{is_:02d}, {imm11}(vi{it:02d})", None
    if name in ("ilw", "isw"):
        return f"{name}.{dest} vi{it:02d}, {imm11}(vi{is_:02d})", None
    if name in ("iaddiu", "isubiu"):
        v = (w >> 21 & 15) << 11 | (w & 0x7FF)
        return f"{name} vi{it:02d}, vi{is_:02d}, 0x{v:x}", None
    if name.startswith("fc"):
        if name == "fcget":
            return f"fcget vi{it:02d}", None
        return f"{name} {'vi01, ' if name != 'fcset' else ''}0x{w & 0xFFFFFF:06x}", None
    if name.startswith("fs"):
        v = (w >> 21 & 1) << 11 | (w & 0x7FF)
        return f"{name} {'vi%02d, ' % it if name != 'fsset' else ''}0x{v:03x}", None
    if name.startswith("fm"):
        return f"{name} vi{it:02d}, vi{is_:02d}", None
    if name == "jr":
        return f"jr vi{is_:02d}", None
    if name == "jalr":
        return f"jalr vi{it:02d}, vi{is_:02d}", None
    tgt = pc + 1 + imm11
    if name == "b":
        return f"b {tgt:#06x}", tgt
    if name == "bal":
        return f"bal vi{it:02d}, {tgt:#06x}", tgt
    if name in ("ibeq", "ibne"):
        return f"{name} vi{it:02d}, vi{is_:02d}, {tgt:#06x}", tgt
    return f"{name} vi{is_:02d}, {tgt:#06x}", tgt


def decode_pair(lo: int, hi: int, pc: int):
    u = upper(hi)
    if hi >> 31 & 1:  # I bit: lower is a float immediate (LOI)
        f = struct.unpack("<f", struct.pack("<I", lo))[0]
        return u, f"loi {f:.6g} (0x{lo:08x})", None
    l, t = lower(lo, pc)
    return u, l, t


def code_score(get, a: int, n: int) -> float:
    good = 0
    for i in range(n):
        lo, hi = get(a + 8 * i), get(a + 8 * i + 4)
        u, l, _ = decode_pair(lo, hi, i)
        good += (u is not None) + (l is not None)
    return good / (2 * n) if n else 0.0


# ---------------------------------------------------------- VIF / DMA ----

VIF = {0x00: "NOP", 0x01: "STCYCL", 0x02: "OFFSET", 0x03: "BASE", 0x04: "ITOP", 0x05: "STMOD",
       0x06: "MSKPATH3", 0x07: "MARK", 0x10: "FLUSHE", 0x11: "FLUSH", 0x13: "FLUSHA",
       0x14: "MSCAL", 0x15: "MSCALF", 0x17: "MSCNT", 0x20: "STMASK", 0x30: "STROW",
       0x31: "STCOL", 0x4A: "MPG", 0x50: "DIRECT", 0x51: "DIRECTHL"}
TAGID = ["REFE", "CNT", "NEXT", "REF", "REFS", "CALL", "RET", "END"]


def is_tag(lo: int, hi: int) -> bool:
    return (lo >> 16 & 0x3FF) == 0 and not lo >> 26 & 1 and not lo >> 31 & 1 and hi & 0x8000000F == 0


# ------------------------------------------------------------- layout ----


def load_layout(path: Path):
    starts, rows = [], []
    if path.exists():
        for line in path.read_text().splitlines():
            if not line or line[0] in "#a":
                continue
            p = line.split("\t")
            starts.append(int(p[0], 16))
            rows.append((int(p[0], 16), int(p[1], 16), p[3] if len(p) > 3 else "func_" + p[0]))
    return starts, rows


def func_of(layout, a: int) -> str:
    starts, rows = layout
    i = bisect.bisect_right(starts, a) - 1
    if i >= 0 and rows[i][0] <= a < rows[i][1]:
        return rows[i][2]
    return "?"


def code_refs(img: Image, layout, targets: set[int]):
    """lui/low-half pairs inside each function that build an address in targets."""
    out = []
    for s, e, name in layout[1]:
        hi = {}
        for a in range(s, e, 4):
            w = img.w(a)
            o, rs, rt, im = w >> 26, w >> 21 & 31, w >> 16 & 31, w & 0xFFFF
            sim = im - 0x10000 if im & 0x8000 else im
            if o == 0x0F:
                hi[rt] = im << 16
                continue
            if rs in hi and o in (0x09, 0x19, 0x0D, 0x20, 0x21, 0x23, 0x24, 0x25, 0x27, 0x28, 0x29,
                                  0x2B, 0x37, 0x3F, 0x1E, 0x1F, 0x31, 0x39, 0x36, 0x3E):
                v = (hi[rs] | im) if o == 0x0D else (hi[rs] + sim) & 0xFFFFFFFF
                if v in targets:
                    out.append((a, name, v))
    return out


# ------------------------------------------------------------- programs --


def programs_from_sections(img: Image):
    tab = next((s for s in img.sections if s[0] == ".DVP.ovlytab"), None)
    strt = next((s for s in img.sections if s[0] == ".DVP.ovlystrtab"), None)
    if not tab or not strt:
        return None
    chunks = []
    for i in range(tab[4] // 12):
        n, lma, vma = struct.unpack_from("<3I", img.raw, tab[3] + 12 * i)
        name = img.raw[strt[3] + n: img.raw.index(b"\0", strt[3] + n)].decode("latin-1")
        sec = next((s for s in img.sections if s[0] == name), None)
        chunks.append({"name": name, "lma": lma, "vma": vma, "size": sec[4] if sec else None})
    progs = []
    for c in chunks:
        if "unknvma" in c["name"] and progs:
            progs[-1]["chunks"].append(c)
        else:
            progs.append({"chunks": [c]})
    return progs


def programs_from_scan(get, lo: int, hi: int, ok):
    progs, a = [], lo
    while a < hi:
        w = get(a)
        if w >> 24 == 0x4A and a % 8 == 4:
            num = (w >> 16 & 0xFF) or 256
            addr = (w & 0xFFFF) * 8
            if (addr + num * 8 <= VU1_MICRO and num >= 4 and ok(a + 4, num * 8)
                    and code_score(get, a + 4, num) >= 0.99):
                c = {"name": "(scan)", "lma": a + 4, "vma": addr, "size": num * 8}
                if progs and addr and progs[-1]["chunks"][-1]["vma"] + progs[-1]["chunks"][-1]["size"] == addr:
                    progs[-1]["chunks"].append(c)
                else:
                    progs.append({"chunks": [c]})
                a += 4 + num * 8
                continue
        a += 4
    return progs


def carrier(img: Image, lma: int):
    """The DMA tag whose packet carries the MPG code at lma-4: (id, tag address).

    The MPG code sits in the upper half of the tag qword (lma - 16), or in a
    VIF stream inside a CNT/END/NEXT packet further back. A qword at lma - 8
    that no tag covers is a REF target (found via data references)."""
    first = (lma - 4) & ~15
    for t in range(first, first - 0x1000, -16):
        if not img.ok(t, 16):
            break
        lo = img.w(t)
        if is_tag(lo, img.w(t + 4)) and lo >> 28 & 7 in (1, 2, 7):
            qwc = lo & 0xFFFF
            if t == first or (qwc and t + 16 + 16 * qwc > lma):
                return TAGID[lo >> 28 & 7], t
            return None, None  # a tag that ends before: the MPG is not in its packet
    return None, None


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("elf", nargs="?", default=str(REPO / "SLPS_251.98"))
    ap.add_argument("--layout", default=str(REPO / "layout.tsv"))
    ap.add_argument("--disasm", type=int, metavar="N", help="disassemble program N (output is game-derived: do not commit)")
    ap.add_argument("--summary", type=int, metavar="N", help="register/memory usage summary of program N")
    ap.add_argument("--overlay", nargs="+", metavar="FILE", help="scan overlay files for MPG uploads")
    ap.add_argument("--base", type=lambda s: int(s, 0), default=0, help="load address of a raw overlay")
    args = ap.parse_args()

    if args.overlay:
        for f in args.overlay:
            progs = scan_overlay(Path(f), args.base, quiet=args.disasm is not None)
            if args.disasm is not None:
                p = progs[0][args.disasm]
                get = progs[1]
                code = [(c["vma"] // 8 + i, get(c["lma"] + 8 * i), get(c["lma"] + 8 * i + 4))
                        for c in p["chunks"] for i in range(c["size"] // 8)]
                print(disasm(code))
        return

    img = Image(Path(args.elf))
    layout = load_layout(Path(args.layout))
    progs = programs_from_sections(img)
    src = "section table"
    if progs is None:
        lo = min(v for v, _o, _f in img.segs)
        hi = max(v + f for v, _o, f in img.segs)
        progs = programs_from_scan(img.w, lo, hi, img.ok)
        src = "scan"
    for p in progs:
        p["vma"] = p["chunks"][0]["vma"]
        p["size"] = sum(c["size"] or 0 for c in p["chunks"])

    if args.disasm is not None or args.summary is not None:
        n = args.disasm if args.disasm is not None else args.summary
        p = progs[n]
        code = []
        for c in p["chunks"]:
            mpg = img.w(c["lma"] - 4)
            for i in range((c["size"] or 0) // 8):
                code.append((c["vma"] // 8 + i, img.w(c["lma"] + 8 * i), img.w(c["lma"] + 8 * i + 4)))
        if args.disasm is not None:
            print(disasm(code))
        else:
            print(summarize(code))
        return

    # Carriers and references.
    for p in progs:
        c0 = p["chunks"][0]
        kind, tag = carrier(img, c0["lma"])
        p["tag"], p["tagkind"] = tag, kind
    targets = {}
    for i, p in enumerate(progs):
        c0 = p["chunks"][0]
        for t in {c0["lma"] - 8, p["tag"]} - {None}:
            targets[t] = i
    data_refs = {}
    for a, v in img.words():
        if v in targets and not (TEXT_LO <= a < TEXT_HI):
            data_refs.setdefault(targets[v], []).append(a)
    crefs = {}
    for a, fn, v in code_refs(img, layout, set(targets)):
        crefs.setdefault(targets[v], []).append((a, fn, v))
    # Code references to the data tables holding REF tags (one level).
    tbl = {}
    for i, refs in data_refs.items():
        for a in refs:
            tbl[a - 4] = i  # REF tag address = ADDR word - 4
    tbl_targets = set(tbl)
    tbl_refs = {}
    for a, fn, v in code_refs(img, layout, tbl_targets | {t & ~0xFF for t in tbl_targets}):
        for t, i in tbl.items():
            if v == t:
                tbl_refs.setdefault(i, []).append((a, fn, v))

    print(f"# {len(progs)} VU microprograms ({src}); addresses only")
    print("# n  vma(bytes) size   instr  chunks (lma:size)                       carrier")
    for i, p in enumerate(progs):
        ch = " ".join(f"{c['lma']:08x}:{c['size']:x}" for c in p["chunks"])
        car = f"{p['tagkind']} tag @{p['tag']:08x}" if p["tag"] else "in-stream (REF target)"
        print(f"{i:3d} {p['vma']:#06x}     {p['size']:#06x} {p['size'] // 8:5d}  {ch:40s} {car}")
        for a in data_refs.get(i, []):
            lo = img.w(a - 4)
            if a % 16 == 4 and is_tag(lo, 0):
                print(f"      DMA {TAGID[lo >> 28 & 7]} tag @{a - 4:08x} (qwc {lo & 0xFFFF:#x}) points at its MPG qword")
            else:
                print(f"      pointer word @{a:08x} (table entry; code indexes the table)")
        for a, fn, v in crefs.get(i, []):
            print(f"      code ref @{a:08x} in {fn} -> {v:08x}")
        for a, fn, v in tbl_refs.get(i, []):
            print(f"      table ref @{a:08x} in {fn} -> {v:08x}")


def disasm(code) -> str:
    targets = set()
    rows = []
    for pc, lo, hi in code:
        u, l, t = decode_pair(lo, hi, pc)
        if t is not None:
            targets.add(t)
        rows.append((pc, u, l))
    out = []
    for pc, u, l in rows:
        lab = f"L{pc:04x}:" if pc in targets else ""
        out.append(f"{lab:7s}{pc:04x}  {u or '??? (upper)':44s} {l or '??? (lower)'}")
    return "\n".join(out)


def summarize(code) -> str:
    """Counts that say what a program does, without listing the code."""
    from collections import Counter
    ops = Counter()
    mem = Counter()
    for pc, lo, hi in code:
        u, l, _ = decode_pair(lo, hi, pc)
        for s in (u, l):
            if s:
                ops[s.split()[0].split(".")[0]] += 1
        if l and l.split()[0].split(".")[0] in ("lq", "sq", "ilw", "isw") and "(vi00)" in l:
            mem[l.split()[0].split(".")[0] + " " + l.split(",")[-1].strip()] += 1
    lines = ["ops: " + ", ".join(f"{k} {v}" for k, v in sorted(ops.items(), key=lambda x: -x[1]))]
    lines.append("absolute VU memory (vi00-based): " + ", ".join(f"{k} x{v}" for k, v in sorted(mem.items())))
    return "\n".join(lines)


def scan_overlay(path: Path, base: int, quiet: bool = False):
    raw = path.read_bytes()
    segs = []
    if raw[:4] == b"\x7fELF":
        phoff = struct.unpack_from("<I", raw, 0x1C)[0]
        phentsize, phnum = struct.unpack_from("<HH", raw, 0x2A)
        for i in range(phnum):
            t, off, vaddr, _pa, filesz, _m = struct.unpack_from("<6I", raw, phoff + i * phentsize)
            if t == 1:
                segs.append((vaddr, off, filesz))
    else:
        segs.append((base, 0, len(raw)))

    def ok(a, n=4):
        return any(v <= a and a + n <= v + f for v, _o, f in segs)

    def get(a):
        for v, o, f in segs:
            if v <= a < v + f - 3:
                return struct.unpack_from("<I", raw, o + a - v)[0]
        return 0
    allp = []
    for v, _o, f in segs:
        allp += programs_from_scan(get, v, v + f, ok)
    found = len(allp)
    if quiet:
        return allp, get
    for n, p in enumerate(allp):
        ch = " ".join(f"{c['lma']:08x}:{c['size']:x}@{c['vma']:#x}" for c in p["chunks"])
        print(f"{path.name}: program {n} at {ch}")
    # VIF kicks without an upload (programs resident from the main ELF).
    kicks = 0
    for v, _o, f in segs:
        for a in range(v, v + f - 3, 4):
            w = get(a)
            if w >> 24 in (0x14, 0x15, 0x17) and w & 0xFF0000 == 0 and (w >> 24 != 0x17 or w & 0xFFFF == 0):
                kicks += 1
    print(f"{path.name}: {found} MPG upload(s); {kicks} word(s) shaped like MSCAL/MSCALF/MSCNT (unverified)")
    return allp, get


if __name__ == "__main__":
    main()
