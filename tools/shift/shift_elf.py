#!/usr/bin/env python3
"""Write the shiftable build's ELF and check milestone M0 (docs/shiftable-plan.md, step 7).

  python3 -I tools/shift/shift_elf.py write  [--linked out/shift/kh1-shift.linked.elf] [--out out/shift/kh1-shift.elf]
  python3 -I tools/shift/shift_elf.py verify [--elf out/shift/kh1-shift.elf]

`write` turns the ld output into a fresh, minimal ELF like the original: one
PT_LOAD (code + data from the load address, .bss as memsz) at file offset
0x80 with 0x80 alignment, a PT_MIPS_REGINFO with $gp, the original e_flags,
and a symbol table (function and D_ names, for debuggers). Nothing is copied
from the original ELF except header facts (out/shift/data/image.json).

`verify` (M0) loads the original and the new ELF the way the PS2 loader does
(file bytes, then zeros up to memsz) and requires: same load address, entry,
image end and .bss start, the same image byte for byte, and every function,
alias/label, data and bss name of out/shift/expected.tsv at its original
address. On a mismatch it prints the first differing addresses with the
function or D_ name that holds them."""
from __future__ import annotations

import argparse
import bisect
import hashlib
import json
import struct
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import kh1tool as K  # noqa: E402
from elf32 import PT_LOAD, SHT_NOBITS, Elf  # noqa: E402

SHIFT = K.OUT / "shift"
PT_MIPS_REGINFO = 0x70000000
SHT_PROGBITS, SHT_SYMTAB, SHT_STRTAB, SHT_MIPS_REGINFO = 1, 2, 3, 0x70000006
SHF_WRITE, SHF_ALLOC, SHF_EXEC = 1, 2, 4
SHN_ABS = 0xFFF1
FILE_ALIGN = 0x80


def load_image_facts() -> dict:
    return json.loads((SHIFT / "data" / "image.json").read_text())


def symbol_map(elf: Elf) -> dict[str, int]:
    out = {}
    for s in elf.symbols():
        if s.name and s.type != 4 and s.type != 3:  # not FILE/SECTION
            if s.bind in (1, 2) or s.name not in out:
                out[s.name] = s.value
    return out


# --------------------------------------------------------------------------- write

def cmd_write(a) -> int:
    img = load_image_facts()
    linked = Elf.load(a.linked)
    orphan = linked.section(".shift_orphan")
    if orphan and orphan.size:
        print(f"error: .shift_orphan holds 0x{orphan.size:x} bytes of code/data no link rule placed",
              file=sys.stderr)
        return 1
    alloc = sorted((s for s in linked.sections if s.flags & SHF_ALLOC and s.size), key=lambda s: s.addr)
    progbits = [s for s in alloc if s.type != SHT_NOBITS]
    nobits = [s for s in alloc if s.type == SHT_NOBITS]
    load = alloc[0].addr
    file_end = max(s.addr + s.size for s in progbits)
    mem_end = max(s.addr + s.size for s in alloc)
    if any(s.addr < file_end for s in nobits):
        print("error: a NOBITS section lies inside the file-backed image", file=sys.stderr)
        return 1
    image = bytearray(file_end - load)
    for s in progbits:
        image[s.addr - load: s.addr - load + s.size] = linked.section_bytes(s)
    syms = symbol_map(linked)

    # Sections of the new file.
    out_secs = []  # (name, type, flags, addr, data|None, size, align, link, info, entsize)
    for s in alloc:
        flags = SHF_ALLOC | (SHF_EXEC if s.flags & SHF_EXEC else 0) | (SHF_WRITE if s.flags & SHF_WRITE else 0)
        data = None if s.type == SHT_NOBITS else linked.section_bytes(s)
        out_secs.append([s.name, s.type, flags, s.addr, data, s.size, 16 if s.type != SHT_NOBITS else 128, 0, 0, 0])
    reginfo = None
    if img.get("reginfo"):
        words = list(img["reginfo"])
        words[5] = syms.get("_gp", words[5])
        reginfo = struct.pack("<6I", *words)
        out_secs.append([".reginfo", SHT_MIPS_REGINFO, SHF_ALLOC, mem_end - 24, reginfo, 24, 4, 0, 0, 1])

    # Symbol table: functions (local statics too), global names.
    sec_index = {name: i + 1 for i, (name, *_r) in enumerate(out_secs)}
    lsec = {s.index: s.name for s in linked.sections}
    strtab = bytearray(b"\0")
    local, glob = [], []
    for s in linked.symbols():
        if not s.name or s.type in (3, 4) or s.name.startswith((".L", "$")):
            continue
        if s.bind == 0 and s.type != 2:
            continue
        shndx = sec_index.get(lsec.get(s.shndx, ""), SHN_ABS)
        entry = (s.name, s.value, s.size, (s.bind << 4) | s.type, shndx)
        (local if s.bind == 0 else glob).append(entry)
    symtab = bytearray(16)
    for name, value, size, info, shndx in local + glob:
        symtab += struct.pack("<IIIBBH", len(strtab), value, size, info, 0, shndx)
        strtab += name.encode() + b"\0"
    n_local = 1 + len(local)
    sym_i = len(out_secs) + 1
    out_secs.append([".symtab", SHT_SYMTAB, 0, 0, bytes(symtab), len(symtab), 4, sym_i + 1, n_local, 16])
    out_secs.append([".strtab", SHT_STRTAB, 0, 0, bytes(strtab), len(strtab), 1, 0, 0, 0])
    shstr = bytearray(b"\0")
    names = []
    for sec in out_secs + [[".shstrtab"]]:
        names.append(len(shstr))
        shstr += sec[0].encode() + b"\0"
    out_secs.append([".shstrtab", SHT_STRTAB, 0, 0, bytes(shstr), len(shstr), 1, 0, 0, 0])

    phnum = 2 if reginfo else 1
    f = bytearray(FILE_ALIGN)
    seg_off = FILE_ALIGN
    assert 52 + 32 * phnum <= FILE_ALIGN
    f += image
    offsets = {}
    for i, sec in enumerate(out_secs):
        name, typ, _fl, addr, data, size = sec[:6]
        if typ != SHT_NOBITS and sec[2] & SHF_ALLOC and name != ".reginfo":
            offsets[i] = seg_off + (addr - load)
        elif typ == SHT_NOBITS:
            offsets[i] = len(f)
        else:
            while len(f) % max(sec[6], 1):
                f.append(0)
            offsets[i] = len(f)
            f += data
    while len(f) % 4:
        f.append(0)
    shoff = len(f)
    f += bytes(40)
    for i, sec in enumerate(out_secs):
        name, typ, flags, addr, _data, size, align, link, info, ent = sec
        f += struct.pack("<10I", names[i], typ, flags, addr, offsets[i], size, link, info, align, ent)
    entry = linked.entry
    struct.pack_into("<16sHHIIIIIHHHHHH", f, 0, b"\x7fELF\x01\x01\x01" + bytes(9), 2, 8, 1, entry, 52,
                     shoff, img["e_flags"], 52, 32, phnum, 40, len(out_secs) + 1, len(out_secs))
    struct.pack_into("<8I", f, 52, PT_LOAD, seg_off, load, load, len(image), mem_end - load,
                     img.get("p_flags", 7), FILE_ALIGN)
    if reginfo:
        ri = next(i for i, s in enumerate(out_secs) if s[0] == ".reginfo")
        struct.pack_into("<8I", f, 84, PT_MIPS_REGINFO, offsets[ri], mem_end - 24, mem_end - 24, 24, 24, 4, 4)
    Path(a.out).write_bytes(bytes(f))
    print(f"shift-elf: {Path(a.out).relative_to(K.ROOT) if Path(a.out).is_absolute() else a.out}: "
          f"load 0x{load:08x}, file-backed 0x{len(image):x}, memsz 0x{mem_end - load:x}, entry 0x{entry:08x}, "
          f"{len(local) + len(glob)} symbols")
    return 0


# --------------------------------------------------------------------------- verify

def loaded_image(elf: Elf) -> tuple[int, bytearray]:
    loads = [s for s in elf.segments if s.type == PT_LOAD and s.memsz]
    lo = min(s.vaddr for s in loads)
    hi = max(s.vaddr + s.memsz for s in loads)
    mem = bytearray(hi - lo)
    for s in loads:
        mem[s.vaddr - lo: s.vaddr - lo + s.filesz] = elf.data[s.offset: s.offset + s.filesz]
    return lo, mem


class Namer:
    """Address -> `name+0xoff` from layout.tsv and out/shift/expected.tsv."""

    def __init__(self):
        rows: dict[int, str] = {f.addr: f.name for f in K.load_layout()}
        exp = SHIFT / "expected.tsv"
        if exp.exists():
            for line in exp.read_text().splitlines()[1:]:
                a, kind, name = line.split("\t")
                if kind in ("func", "data", "bss", "rodata"):
                    rows[int(a, 16)] = name
        self.addrs = sorted(rows)
        self.names = rows

    def __call__(self, addr: int) -> str:
        i = bisect.bisect_right(self.addrs, addr) - 1
        if i < 0:
            return "?"
        a = self.addrs[i]
        return self.names[a] + (f"+0x{addr - a:x}" if addr != a else "")


def cmd_verify(a) -> int:
    cfg = K.load_config()
    orig_raw = K.orig_path(cfg).read_bytes()
    if hashlib.sha256(orig_raw).hexdigest() != cfg["target"]["sha256"].lower():
        print("error: the original ELF does not match the SHA-256 in kh1.toml", file=sys.stderr)
        return 1
    orig, new = Elf(orig_raw), Elf.load(a.elf)
    img = load_image_facts()
    o_lo, o_mem = loaded_image(orig)
    n_lo, n_mem = loaded_image(new)
    fails = []
    if (o_lo, orig.entry) != (n_lo, new.entry):
        fails.append(f"load/entry: original 0x{o_lo:08x}/0x{orig.entry:08x}, new 0x{n_lo:08x}/0x{new.entry:08x}")
    if o_lo + len(o_mem) != n_lo + len(n_mem):
        fails.append(f"image end: original 0x{o_lo + len(o_mem):08x}, new 0x{n_lo + len(n_mem):08x}")
    nb = new.section(".bss")
    if nb is None or nb.addr != img["bss_start"]:
        fails.append(f".bss start: original 0x{img['bss_start']:08x}, new {hex(nb.addr) if nb else 'none'}")

    namer = Namer()
    diffs = []
    n = min(len(o_mem), len(n_mem))
    if o_mem[:n] != n_mem[:n]:
        step = 0x10000
        for base in range(0, n, step):
            if o_mem[base: base + step] == n_mem[base: base + step]:
                continue
            for off in range(base & ~3, min(base + step, n), 4):
                if o_mem[off: off + 4] != n_mem[off: off + 4]:
                    diffs.append(off)
    if diffs:
        fails.append(f"image: {len(diffs)} differing words; first ones:")
        for off in diffs[:a.max_diffs]:
            addr = o_lo + off
            ow, nw = (struct.unpack_from("<I", m, off)[0] for m in (o_mem, n_mem))
            fails.append(f"  0x{addr:08x} {namer(addr):40s} original {ow:08x} new {nw:08x}")

    linked = Elf.load(a.linked) if Path(a.linked).exists() else new
    syms = symbol_map(linked)
    moved, checked = [], 0
    exp = SHIFT / "expected.tsv"
    for line in exp.read_text().splitlines()[1:]:
        ad, kind, name = line.split("\t")
        if kind == "rodata":
            continue
        checked += 1
        if syms.get(name) != int(ad, 16):
            got = syms.get(name)
            moved.append(f"  {kind} {name}: original 0x{ad}, new {('0x%08x' % got) if got is not None else 'missing'}")
    for name, key in (("D_BLOB", "data_start"), ("D_BSS", "bss_start")):
        checked += 1
        if syms.get(name) != img[key]:
            moved.append(f"  {name}: expected 0x{img[key]:08x}, new {syms.get(name)}")
    if moved:
        fails.append(f"addresses: {len(moved)} names are not at their original address:")
        fails += moved[:a.max_diffs]

    if fails:
        print("M0 FAIL")
        print("\n".join(fails))
        return 1
    print(f"M0 OK: {Path(a.elf).name} loads byte-identical to the original: "
          f"0x{n_lo:08x}-0x{n_lo + len(n_mem):08x}, entry 0x{new.entry:08x}, .bss 0x{nb.addr:08x}+0x{nb.size:x}")
    print(f"M0 OK: {checked} functions, labels and D_ names at their original addresses")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    w = sub.add_parser("write", help="write the fresh ELF from the ld output")
    w.add_argument("--linked", default=str(SHIFT / "kh1-shift.linked.elf"))
    w.add_argument("--out", default=str(SHIFT / "kh1-shift.elf"))
    v = sub.add_parser("verify", help="M0: compare the loaded image with the original")
    v.add_argument("--elf", default=str(SHIFT / "kh1-shift.elf"))
    v.add_argument("--linked", default=str(SHIFT / "kh1-shift.linked.elf"))
    v.add_argument("--max-diffs", type=int, default=20)
    a = ap.parse_args()
    return cmd_write(a) if a.cmd == "write" else cmd_verify(a)


if __name__ == "__main__":
    sys.exit(main())
