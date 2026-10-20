#!/usr/bin/env python3
"""Turn single-owner bss `extern` declarations into C definitions (phase 4, step 1).

  python3 -I tools/shift/define_vars.py [--owners out/shift/data_owners.tsv]
                                        [--file SRC ...] [--name D_X ...] [--apply]

For every `bss` row of data_owners.tsv with verdict `single` whose owner is a C
file outside `src/sdk/`, finds the file-scope `extern` declaration of the name
in that file and plans a definition in its place:

  extern s32 D_00494418, D_0049441C;   ->   s32 D_00494418 ALIGNED(8);
                                            s32 D_0049441C ALIGNED(4);

Sizes come from the compiler (a probe copy of the file with
`int __kh1sz_N = sizeof(...)` appended, compiled with -S), checked against the
row's extent (the distance to the next anchor, an upper bound):

  exact    sizeof == extent: defined as declared
  fill     incomplete first dimension (`T D[]`, `T D[][4]`): filled with
           extent / sizeof(element) (must divide)
  pad      sizeof < extent, the name is never address-taken or indexed past
           its type in the file (`&D`, a cast of it): defined as declared; the
           rest of the extent is alignment padding or unused
  manual   anything else (smaller than the extent and address-taken, larger
           than the extent, no single-line file-scope extern, function-pointer
           declarators): printed, not changed

Alignment: ALIGNED(n) with n = the largest power of two dividing the address,
capped at 16 (64 for objects of 64 bytes or more), so a floated copy keeps the
alignment the original had (DMA buffers, cache-line flushes).

Without --apply only the plan is printed. `make` must stay byte-identical after
applying (verify catches a codegen change)."""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
CC = ROOT / "tools/toolchain/ee-gcc2.96/bin/ee-gcc"
EXTERN_RE = re.compile(r"^extern\s+(.*?);\s*(/\*.*\*/|//.*)?$")


def split_top(s: str, sep: str = ",") -> list[str]:
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == sep and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    out.append(cur)
    return [x.strip() for x in out]


def parse_extern(line: str, name: str):
    """(type_spec, [declarators], index of name's declarator) or None."""
    m = EXTERN_RE.match(line)
    if not m:
        return None
    body = m.group(1)
    # the type spec is everything before the first declarator; find the first
    # D_/identifier declarator by scanning the comma-split list of the body
    # with the leading type removed: the type is the text up to the first
    # declarator token of the first item
    items = split_top(body)
    first = items[0]
    dm = re.match(r"^((?:(?:const|volatile|unsigned|signed|struct|union|enum)\s+)*[A-Za-z_]\w*)\s+(.*)$", first)
    if not dm:
        return None
    tspec, d0 = dm.group(1), dm.group(2)
    decls = [d0] + items[1:]
    for i, d in enumerate(decls):
        if re.fullmatch(r"\**\s*" + re.escape(name) + r"\s*(\[[^\]]*\]\s*)*", d):
            return tspec, decls, i
    return None


def lowbit(a: int) -> int:
    return a & -a


def align_for(addr: int, size: int) -> int:
    cap = 64 if size >= 64 else 16
    return min(lowbit(addr), cap)


def probe_sizes(src: Path, exprs: dict[str, str]) -> dict[str, int]:
    """sizeof(expr) for each key, compiled in the context of src."""
    text = src.read_text()
    extra = "".join(f"\nint __kh1sz_{k} = sizeof({e});" for k, e in exprs.items())
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / src.name
        p.write_text(text + extra + "\n")
        out = Path(td) / "probe.s"
        r = subprocess.run([str(CC), "-S", "-x", "c", "-O2", "-G0", "-fno-common",
                            f"-I{ROOT/'include'}", f"-I{ROOT/'src'}", f"-I{src.parent}",
                            "-o", str(out), str(p)], capture_output=True, text=True)
        if r.returncode:
            raise RuntimeError(f"probe of {src} failed:\n{r.stderr[-2000:]}")
        sizes, cur = {}, None
        for ln in out.read_text().splitlines():
            m = re.match(r"^__kh1sz_(\w+):", ln)
            if m:
                cur = m.group(1)
                continue
            m = re.match(r"^\s*\.word\s+(\d+)", ln)
            if cur and m:
                sizes[cur] = int(m.group(1))
                cur = None
        return sizes


def address_taken(text: str, name: str) -> bool:
    n = re.escape(name)
    return bool(re.search(r"&\s*" + n + r"\b|\(\s*[A-Za-z_][\w\s]*\*+\s*\)\s*" + n + r"\b", text))


def plan_file(src: Path, rows: list[tuple[int, str, int]]):
    lines = src.read_text().splitlines(keepends=True)
    text = "".join(lines)
    found, manual = {}, []
    for addr, name, extent in rows:
        hits = [i for i, ln in enumerate(lines)
                if ln.startswith("extern") and re.search(r"\b" + name + r"\b", ln)]
        if not hits and re.search(r"^(?!extern|typedef|return)[A-Za-z_][\w \t*]*?\b" + name + r"\b",
                                  text, re.M):
            continue  # already a definition
        if len(hits) != 1:
            manual.append((name, f"{len(hits)} file-scope extern lines"))
            continue
        pe = parse_extern(lines[hits[0]].rstrip("\n"), name)
        if not pe:
            manual.append((name, "declaration not understood: " + lines[hits[0]].strip()))
            continue
        tspec, decls, i = pe
        d = decls[i]
        incomplete = re.search(r"\[\s*\]", d) is not None
        if incomplete and not re.fullmatch(r"\**\s*\w+\s*\[\s*\](\s*\[[^\]]+\])*", d):
            manual.append((name, "incomplete inner dimension"))
            continue
        found[name] = (addr, extent, hits[0], tspec, decls, i, incomplete)
    if not found:
        return [], manual
    exprs = {n: (f"{n}[0]" if v[6] else n) for n, v in found.items()}
    sizes = probe_sizes(src, exprs)
    plans = []
    for name, (addr, extent, ln, tspec, decls, i, incomplete) in found.items():
        sz = sizes.get(name)
        if sz is None or sz == 0:
            manual.append((name, "no size from probe"))
            continue
        d = decls[i]
        if incomplete:
            if extent % sz:
                manual.append((name, f"extent {extent:#x} not a multiple of element {sz:#x}"))
                continue
            d = re.sub(r"\[\s*\]", f"[{extent // sz:#x}]", d, count=1)
            kind, size = "fill", extent
        elif sz == extent:
            kind, size = "exact", sz
        elif sz < extent and not address_taken(text, name) and "[" not in d:
            kind, size = "pad", sz
        elif sz < extent:
            manual.append((name, f"sizeof {sz:#x} < extent {extent:#x}, address taken or array"))
            continue
        else:
            manual.append((name, f"sizeof {sz:#x} > extent {extent:#x}"))
            continue
        plans.append((ln, name, tspec, decls, i, d, align_for(addr, size), kind, size, extent))
    return plans, manual


def apply_file(src: Path, plans) -> None:
    lines = src.read_text().splitlines(keepends=True)
    by_line: dict[int, list] = {}
    for p in plans:
        by_line.setdefault(p[0], []).append(p)
    for ln in sorted(by_line, reverse=True):
        ps = by_line[ln]
        tspec, decls = ps[0][2], ps[0][3]
        drop = {p[4] for p in ps}
        keep = [d for j, d in enumerate(decls) if j not in drop]
        new = []
        if keep:
            m = EXTERN_RE.match(lines[ln].rstrip("\n"))
            tail = f" {m.group(2)}" if m and m.group(2) else ""
            new.append(f"extern {tspec} {', '.join(keep)};{tail}\n")
        for p in sorted(ps, key=lambda p: p[4]):
            new.append(f"{tspec} {p[5]} ALIGNED({p[6]});\n")
        lines[ln:ln + 1] = new
    text = "".join(lines)
    if "ALIGNED(" in text and not re.search(r'#include\s+"common.h"|#include\s+<common.h>', text):
        sys.stderr.write(f"warning: {src} does not include common.h directly (ALIGNED)\n")
    src.write_text(text)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--owners", default=str(ROOT / "out/shift/data_owners.tsv"))
    ap.add_argument("--file", action="append", default=[])
    ap.add_argument("--name", action="append", default=[])
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    per_file: dict[str, list] = {}
    for ln in Path(a.owners).read_text().splitlines()[1:]:
        f = ln.split("\t")
        addr, name, region, extent, verdict, files = int(f[0], 16), f[1], f[2], int(f[3], 16), f[6], f[7]
        if region != "bss" or verdict != "single" or ";" in files:
            continue
        if not files.endswith(".c") or files.startswith("src/sdk/"):
            continue
        if a.file and files not in a.file:
            continue
        if a.name and name not in a.name:
            continue
        per_file.setdefault(files, []).append((addr, name, extent))
    total = {"exact": 0, "fill": 0, "pad": 0, "manual": 0}
    for fn in sorted(per_file):
        src = ROOT / fn
        try:
            plans, manual = plan_file(src, per_file[fn])
        except RuntimeError as e:
            print(f"{fn}: {e}")
            continue
        for p in plans:
            total[p[7]] += 1
            print(f"{fn}\t{p[1]}\t{p[7]}\t{p[8]:#x}/{p[9]:#x}\t{p[2]} {p[5]} ALIGNED({p[6]})")
        for n, why in manual:
            total["manual"] += 1
            print(f"{fn}\t{n}\tmanual\t{why}")
        if a.apply and plans:
            apply_file(src, plans)
    print("# " + ", ".join(f"{k} {v}" for k, v in total.items()), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
