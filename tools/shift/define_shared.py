#!/usr/bin/env python3
"""Define shared bss names in common modules (phase 4, step 3).

  python3 -I tools/shift/define_shared.py [--owners out/shift/data_owners.tsv]
                                          [--name D_X ...] [--apply]

For every `bss` row of data_owners.tsv with verdict `shared` whose users are
all C files outside `src/sdk/`, reads each user's file-scope `extern`
declaration of the name. The name qualifies when every user declares it with
the same plain type (a basic type from common.h, or a pointer to one) and the
same declarator, and the size fits the extent like define_vars.py:

  exact    sizeof == extent
  fill     every user writes `T D[]`: filled with extent / sizeof(T)
  pad      a scalar no user takes the address of, sizeof < extent

A qualifying name gets one definition in `src/data/bss_XXXX.c` (XXXX = bits
31..16 of the address, so the modules follow the bss layout until the names
get subsystem homes) and one declaration in `include/data/bss_XXXX.h`. The
module includes its header, so the definition is checked against it. Each
user includes the header after its own includes and keeps its own extern for
now: a second, identical declaration changes nothing in the code, and the
compiler now checks that each user agrees with the definition.

Without --apply only the plan is printed. `make` must stay byte-identical."""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/shift"))
from define_vars import address_taken, align_for, parse_extern, probe_sizes  # noqa: E402

BASIC = {"s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "f64",
         "int", "char", "short", "long", "float", "double", "unsigned", "M2C_UNK",
         "unsigned char", "unsigned short", "unsigned int", "signed char", "void"}


def norm(s: str) -> str:
    return re.sub(r"\s+", " ", re.sub(r"\s*([\[\]*])\s*", r"\1", s)).strip()


def module(addr: int) -> str:
    return f"bss_{addr >> 16:04X}"


def user_decl(path: Path, name: str):
    lines = path.read_text().splitlines()
    hits = [ln for ln in lines if ln.startswith("extern") and re.search(r"\b" + name + r"\b", ln)]
    if len(hits) != 1:
        return None, f"{path.relative_to(ROOT)}: {len(hits)} file-scope extern lines"
    pe = parse_extern(hits[0], name)
    if not pe:
        return None, f"{path.relative_to(ROOT)}: declaration not understood"
    tspec, decls, i = pe
    return (norm(tspec), norm(decls[i])), None


def plan(owners: Path, names: list[str]):
    rows = []
    for ln in owners.read_text().splitlines()[1:]:
        f = ln.split("\t")
        if f[2] != "bss" or f[6] != "shared":
            continue
        if names and f[1] not in names:
            continue
        files = f[7].split(";")
        if any(not x.endswith(".c") or x.startswith("src/sdk/") for x in files):
            continue
        rows.append((int(f[0], 16), f[1], int(f[3], 16), files))
    plans, skip = [], []
    for addr, name, ext, files in rows:
        decls, why = set(), None
        for fn in files:
            d, why = user_decl(ROOT / fn, name)
            if not d:
                break
            decls.add(d)
        if why:
            skip.append((name, why))
            continue
        if len(decls) != 1:
            skip.append((name, "users disagree: " + " | ".join(f"{t} {d}" for t, d in sorted(decls))))
            continue
        tspec, decl = decls.pop()
        if tspec not in BASIC:
            skip.append((name, f"type {tspec} is not a common.h basic type"))
            continue
        if decl.count("[") > 1 or ("[" in decl and decl.startswith("*")):
            skip.append((name, f"declarator {decl} not handled"))
            continue
        plans.append([addr, name, ext, files, tspec, decl])
    # sizes: probe in the first user, which sees the declaration
    by_first: dict[str, list] = {}
    for p in plans:
        by_first.setdefault(p[3][0], []).append(p)
    out = []
    for fn, ps in by_first.items():
        exprs = {p[1]: (f"{p[1]}[0]" if "[]" in p[5] else p[1]) for p in ps}
        sizes = probe_sizes(ROOT / fn, exprs)
        for addr, name, ext, files, tspec, decl in ps:
            sz = sizes.get(name)
            if not sz:
                skip.append((name, "no size from probe"))
                continue
            if "[]" in decl:
                if ext % sz:
                    skip.append((name, f"extent {ext:#x} not a multiple of element {sz:#x}"))
                    continue
                d, kind, size = decl.replace("[]", f"[{ext // sz:#x}]"), "fill", ext
            elif sz == ext:
                d, kind, size = decl, "exact", sz
            elif sz < ext and "[" not in decl and not any(
                    address_taken((ROOT / f).read_text(), name) for f in files):
                d, kind, size = decl, "pad", sz
            else:
                skip.append((name, f"sizeof {sz:#x} vs extent {ext:#x}"))
                continue
            if "[" in d and addr % 8 and size % 8:
                skip.append((name, "array at an address that is not 8-aligned (gcc pads it)"))
                continue
            out.append((addr, name, files, tspec, decl, d, kind, size, ext, align_for(addr, size)))
    return sorted(out), skip


def apply(plans) -> None:
    mods: dict[str, list] = {}
    for p in plans:
        mods.setdefault(module(p[0]), []).append(p)
    users: dict[str, set] = {}
    for mod, ps in mods.items():
        guard = f"KH1_DATA_{mod.upper()}_H"
        hdr = ROOT / "include/data" / f"{mod}.h"
        src = ROOT / "src/data" / f"{mod}.c"
        hdr.parent.mkdir(parents=True, exist_ok=True)
        src.parent.mkdir(parents=True, exist_ok=True)
        h = [f"/* Shared bss names {ps[0][0] >> 16:04X}xxxx (phase 4, tools/shift/define_shared.py). */",
             f"#ifndef {guard}", f"#define {guard}", "", '#include "common.h"', ""]
        h += [f"extern {p[3]} {p[4]};" for p in ps]
        h += ["", f"#endif /* {guard} */", ""]
        hdr.write_text("\n".join(h))
        c = [f"/* Definitions of the shared bss names in include/data/{mod}.h. */",
             f'#include "data/{mod}.h"', ""]
        c += [f"{p[3]} {p[5]} ALIGNED({p[9]});" for p in ps]
        src.write_text("\n".join(c) + "\n")
        for p in ps:
            for f in p[2]:
                users.setdefault(f, set()).add(mod)
    for f, ms in users.items():
        path = ROOT / f
        lines = path.read_text().splitlines(keepends=True)
        inc = [i for i, ln in enumerate(lines) if ln.startswith("#include")]
        at = inc[-1] + 1 if inc else 0
        new = [f'#include "data/{m}.h"\n' for m in sorted(ms)
               if f'#include "data/{m}.h"' not in "".join(lines)]
        lines[at:at] = new
        path.write_text("".join(lines))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--owners", default=str(ROOT / "out/shift/data_owners.tsv"))
    ap.add_argument("--name", action="append", default=[])
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    plans, skip = plan(Path(a.owners), a.name)
    kinds: dict[str, int] = {}
    for p in plans:
        kinds[p[6]] = kinds.get(p[6], 0) + 1
        print(f"{module(p[0])}\t{p[1]}\t{p[6]}\t{p[7]:#x}/{p[8]:#x}\t{p[3]} {p[5]}\t{len(p[2])} users")
    for n, why in skip:
        print(f"-\t{n}\tskip\t{why}")
    print(f"# {len(plans)} defined ({kinds}), {len(skip)} skipped", file=sys.stderr)
    if a.apply and plans:
        apply(plans)
    return 0


if __name__ == "__main__":
    sys.exit(main())
