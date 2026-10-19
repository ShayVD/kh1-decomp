#!/usr/bin/env python3
"""Turn single-owner pointer-only data tables into initialised C definitions (phase 4, step 2).

  python3 -I tools/shift/define_ptr_tables.py [--owners out/shift/data_owners.tsv]
                                              [--name D_X ...] [--list] [--apply]

A candidate is a `data` row of data_owners.tsv with verdict `single`, owned by a
C file outside `src/sdk/`, whose every word is either an accepted pointer of
data_relocs.tsv (tier 1-3) or zero. Its file-scope `extern` declaration becomes
a definition whose initialiser names each target symbolically:

  extern void *D_00469FF8[];  ->  void *D_00469FF8[8] ALIGNED(8) = {
                                      (void *)func_0024..., (void *)D_0046...,
                                      ...
                                  };

`func` relocations name the function, `D_BLOB+x` / `D_BSS+x` name the D_ symbol
at the target address (declared `extern u8 D_X[];` before the table when the
file does not declare it; `&D_X` when it does). Integer-typed elements (s32,
u32, M2C_UNK) get an `(s32)` cast, everything else `(void *)`. A scalar
`M2C_UNK` with a larger extent becomes an `M2C_UNK[n]` array (skipped when the
address is not 8-aligned and the size not a multiple of 8: gcc aligns such
arrays to 8 and pads the section). Function targets not declared in the file
get `void func_X();`.

Only the pointer values come from the ELF, as names; no game bytes are written.
`make` must stay byte-identical afterwards (verify compares the data words)."""
from __future__ import annotations

import argparse
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/shift"))
from define_vars import align_for, parse_extern, probe_sizes  # noqa: E402
from elf32 import Elf  # noqa: E402

BLOB, BSS = 0x00272C70, 0x00494080
INT_TYPES = {"s32", "u32", "M2C_UNK", "int", "unsigned"}


def load_relocs() -> dict[int, tuple[str, int]]:
    rel = {}
    for ln in (ROOT / "data_relocs.tsv").read_text().splitlines():
        if ln.startswith("#") or ln.startswith("offset"):
            continue
        f = ln.split("\t")
        if f[4] == "x":
            continue
        sym, add = f[2], f[3]
        if sym == "D_BLOB":
            tgt = BLOB + int(add, 16)
        elif sym == "D_BSS":
            tgt = BSS + int(add, 16)
        else:
            tgt = None
        rel[BLOB + int(f[0], 16)] = (sym, tgt)
    return rel


def candidates(owners: Path, rel, elf: Elf, raw: bytes, names: list[str]):
    out = []
    for ln in owners.read_text().splitlines()[1:]:
        f = ln.split("\t")
        a, ext = int(f[0], 16), int(f[3], 16)
        if f[2] != "data" or f[6] != "single" or a % 4 or ext % 4 or not ext:
            continue
        if not f[7].endswith(".c") or f[7].startswith("src/sdk/") or ";" in f[7]:
            continue
        if names and f[1] not in names:
            continue
        off = elf.vaddr_to_offset(a)
        words = [a + i for i in range(0, ext, 4)]
        nrel = sum(w in rel for w in words)
        zero = sum(struct.unpack_from("<I", raw, off + w - a)[0] == 0 for w in words if w not in rel)
        if nrel and nrel + zero == len(words):
            out.append((a, f[1], ext, f[7]))
    return out


def declared(text: str, name: str) -> bool:
    return re.search(r"\b" + re.escape(name) + r"\b", text) is not None


def plan(src: Path, rows, rel):
    text = src.read_text()
    lines = text.splitlines(keepends=True)
    found, skip = {}, []
    for a, name, ext in rows:
        hits = [i for i, ln in enumerate(lines) if ln.startswith("extern") and re.search(r"\b" + name + r"\b", ln)]
        if len(hits) != 1:
            skip.append((name, f"{len(hits)} file-scope extern lines"))
            continue
        pe = parse_extern(lines[hits[0]].rstrip("\n"), name)
        if not pe:
            # function-pointer forms: void (*D_X[])(args) / s32 (*D_X)(void)
            m = re.match(r"^extern\s+(.+?)\(\*\s*" + name + r"\s*(\[\s*\])?\)\s*(\(.*\))\s*;\s*$",
                         lines[hits[0]].rstrip("\n"))
            if not m:
                skip.append((name, "declaration not understood"))
                continue
            found[name] = (a, ext, hits[0], ("fnptr", m.group(1).strip(), bool(m.group(2)), m.group(3)))
            continue
        tspec, decls, i = pe
        if len(decls) != 1:
            skip.append((name, "extern line declares several names"))
            continue
        found[name] = (a, ext, hits[0], ("plain", tspec, decls[0]))
    if not found:
        return [], skip, {}
    exprs = {}
    for n, (_a, _e, _l, d) in found.items():
        if d[0] == "fnptr":
            exprs[n] = f"{n}[0]" if d[2] else n
        else:
            exprs[n] = f"{n}[0]" if re.search(r"\[\s*\]", d[2]) else n
    sizes = probe_sizes(src, exprs)
    plans, rewrites = [], {}
    for n, (a, ext, ln, d) in found.items():
        sz = sizes.get(n)
        if not sz or sz % 4:
            skip.append((n, f"element size {sz} is not a multiple of 4"))
            continue
        if d[0] == "fnptr":
            _k, ret, is_arr, args = d
            if is_arr:
                if ext % sz:
                    skip.append((n, "extent not a multiple of 4"))
                    continue
                cnt, size = ext // sz, ext
                head = f"{ret} (*{n}[{cnt:#x}]){args}"
            else:
                size, head = sz, f"{ret} (*{n}){args}"
            cast, base = "(void *)", "fn"
        else:
            _k, tspec, decl = d
            base = tspec.split()[-1]
            if re.search(r"\[\s*\]", decl):
                if ext % sz:
                    skip.append((n, f"extent {ext:#x} not a multiple of element {sz:#x}"))
                    continue
                decl = re.sub(r"\[\s*\]", f"[{ext // sz:#x}]", decl, count=1)
                size = ext
            elif "[" in decl or sz == ext:
                size = sz
                if size > ext:
                    skip.append((n, f"sizeof {sz:#x} > extent {ext:#x}"))
                    continue
            elif base == "M2C_UNK" and decl == n and sz < ext:
                if a % 8 and ext % 8:
                    skip.append((n, "M2C_UNK array at an address that is not 8-aligned"))
                    continue
                decl, size = f"{n}[{ext // 4:#x}]", ext
                rewrites[ln] = f"extern M2C_UNK {n}[];\n"
            elif sz < ext and decl == n:
                size = sz  # scalar: the rest stays in the blob
            else:
                skip.append((n, f"sizeof {sz:#x} vs extent {ext:#x}"))
                continue
            ptr = decl.startswith("*")
            cast = "(s32)" if (base in INT_TYPES and not ptr) else "(void *)"
            head = f"{tspec} {decl}"
        if "[" in head and a % 8 and size % 8:
            skip.append((n, "array at an address that is not 8-aligned, size not a multiple of 8 (gcc pads it)"))
            continue
        inits, externs, protos = [], [], []
        for w in range(a, a + size, 4):
            if w not in rel:
                inits.append("0")
                continue
            sym, tgt = rel[w]
            if tgt is None:
                if not declared(text, sym):
                    protos.append(sym)
                inits.append(f"{cast}{sym}")
            else:
                tn = f"D_{tgt:08X}"
                if declared(text, tn):
                    inits.append(f"{cast}&{tn}")
                else:
                    externs.append(tn)
                    inits.append(f"{cast}{tn}")
        scalar = (size == sz and not re.search(r"\[", head))
        plans.append((ln, n, head, align_for(a, size), inits, sorted(set(externs)), sorted(set(protos)), scalar))
    return plans, skip, rewrites


def apply(src: Path, plans, rewrites) -> None:
    """The extern stays where it is (code before the table compiles exactly as
    before); the definition goes at the end of the file, where every function
    and variable the file declares is in scope."""
    lines = src.read_text().splitlines(keepends=True)
    for ln, s in rewrites.items():
        lines[ln] = s
    text = "".join(lines).rstrip("\n") + "\n"
    new = ["", "/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */"]
    seen: set[str] = set()
    for ln, n, head, al, inits, externs, protos, scalar in sorted(plans):
        new += [f"extern u8 {e}[];" for e in externs if e not in seen]
        new += [f"void {p}();" for p in protos if p not in seen]
        seen.update(externs, protos)
        if scalar:
            new.append(f"{head} ALIGNED({al}) = {inits[0]};")
        else:
            new.append(f"{head} ALIGNED({al}) = {{")
            for i in range(0, len(inits), 4):
                new.append("    " + ", ".join(inits[i:i + 4]) + ",")
            new.append("};")
    src.write_text(text + "\n".join(new) + "\n")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--owners", default=str(ROOT / "out/shift/data_owners.tsv"))
    ap.add_argument("--elf", default=str(ROOT / "SLPS_251.98"))
    ap.add_argument("--name", action="append", default=[])
    ap.add_argument("--list", action="store_true", help="only list the candidates")
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    rel = load_relocs()
    elf = Elf.load(a.elf)
    raw = Path(a.elf).read_bytes()
    cands = candidates(Path(a.owners), rel, elf, raw, a.name)
    if a.list:
        for c in cands:
            print(f"{c[1]}\t{c[2]:#x}\t{c[3]}")
        print(f"# {len(cands)} pointer-only single-owner tables", file=sys.stderr)
        return 0
    per_file: dict[str, list] = {}
    for addr, name, ext, f in cands:
        per_file.setdefault(f, []).append((addr, name, ext))
    done = skipped = 0
    for fn in sorted(per_file):
        src = ROOT / fn
        plans, skip, rewrites = plan(src, per_file[fn], rel)
        for p in plans:
            print(f"{fn}\t{p[1]}\t{len(p[4])} words")
        for n, why in skip:
            print(f"{fn}\t{n}\tskip\t{why}")
        done += len(plans)
        skipped += len(skip)
        if a.apply and plans:
            apply(src, plans, rewrites)
    print(f"# {done} tables defined, {skipped} skipped", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
