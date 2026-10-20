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

--mixed takes the names whose users disagree on the type (s32 vs u32, `T D[]`
vs `T D[32]`, M2C_UNK vs `u8 D[]`, ...). Each distinct declaration is sized in
a user that writes it (probe compile) and checked against the extent as above;
one is picked: exact before fill before pad, a real type before M2C_UNK, a
hand-written file before src/auto, more users first. Users whose declaration
is unparsed (block-scope or several extern lines) are allowed for exact and
fill; pad also needs the row's reach to fit. Types must be basic (common.h,
m2c.h) for now. The definition is appended to `src/data/bss_XXXX.c`, the
declaration goes to `include/data/bss_XXXX_mixed.h` (a separate header, so the
files that already include bss_XXXX.h are not touched). A user of a name in
it includes that header (at the end of the file, after all code, so no
declaration moves ahead of any function) only when the file still compiles
with it, i.e. it agrees with every name there (`s32`/`int` agree; `s32`/`u32`
do not); the others keep their own extern, marked with a comment naming the
chosen type when the extern line declares only that name.

Without --apply only the plan is printed. `make` must stay byte-identical."""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/shift"))
from define_vars import address_taken, align_for, parse_extern, probe_sizes  # noqa: E402
import type_move  # noqa: E402

BASIC = {"s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "f64",
         "int", "char", "short", "long", "float", "double", "unsigned", "M2C_UNK",
         "unsigned char", "unsigned short", "unsigned int", "signed char", "void"}


def norm(s: str) -> str:
    return re.sub(r"\s+", " ", re.sub(r"\s*([\[\]*])\s*", r"\1", s)).strip()


def module(addr: int) -> str:
    return f"bss_{addr >> 16:04X}"


def user_decl(path: Path, name: str, repeat: bool = False):
    """(type, declarator) of path's file-scope extern of name. With repeat,
    several extern lines are fine when they all declare it the same way."""
    lines = path.read_text().splitlines()
    hits = [ln for ln in lines if ln.startswith("extern") and re.search(r"\b" + name + r"\b", ln)]
    if len(hits) != 1 and not (repeat and hits):
        return None, f"{path.relative_to(ROOT)}: {len(hits)} file-scope extern lines"
    got = set()
    for ln in hits:
        pe = parse_extern(ln, name)
        if not pe:
            return None, f"{path.relative_to(ROOT)}: declaration not understood"
        tspec, decls, i = pe
        got.add((norm(tspec), norm(decls[i])))
    if len(got) != 1:
        return None, f"{path.relative_to(ROOT)}: {len(hits)} extern lines that disagree"
    return got.pop(), None


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


KIND_RANK = {"exact": 0, "fill": 1, "pad": 2, "fill-floor": 3, "pad-align": 4}


def align_slack(addr: int, used: int, ext: int) -> bool:
    """The extent past `used` bytes is only alignment: the next anchor is the
    first 8- or 16-aligned address at or after addr + used."""
    end = addr + ext
    return any(ext - used < a and end % a == 0 for a in (8, 16))

# Types more than one moved header needs (u128, PppMtx) live in one shared
# header; a plan whose type is there has tsrc (SHARED, type) and moves nothing.
SHARED = "include/data/types/shared.h"


def tkey(f: str) -> str:
    """The include/data/types/<key>.h a plan's type comes from."""
    return "shared" if f == SHARED else type_move.header_name(ROOT / f)


def defined_names() -> set[str]:
    t = ROOT / "out/gen/data.tsv"
    return {ln.split("\t")[1] for ln in t.read_text().splitlines()[1:]} if t.exists() else set()


def base_type(tspec: str) -> str:
    return re.sub(r"\b(volatile|const)\s+", "", tspec).strip()


def plan_mixed(owners: Path, names: list[str], types: bool = False, exclude=(), relax: bool = False):
    """Names whose users disagree: pick one declaration (see the module doc).
    relax (session 19) adds pad-align and fill-floor, reads repeated identical
    extern lines, and takes names whose users agree when they are named."""
    done = defined_names()
    rows, others = [], {}
    for ln in owners.read_text().splitlines()[1:]:
        f = ln.split("\t")
        if f[2] != "bss" or f[6] != "shared" or f[1] in done or f[1] in exclude:
            continue
        if names and f[1] not in names:
            continue
        files = f[7].split(";")
        if any(not x.endswith(".c") or x.startswith("src/sdk/") for x in files):
            continue
        rows.append((int(f[0], 16), f[1], int(f[3], 16), int(f[4], 16), files))
        others[f[1]] = f[8] if len(f) > 8 else ""
    # data_owners.py counts the C-defined variables (out/gen/data.tsv) as anchors, so
    # no extent runs over one; an extent that does means data_owners.tsv is older
    # than the last `make`.
    import bisect
    defs = sorted(int(ln.split("\t")[0], 16)
                  for ln in (ROOT / "out/gen/data.tsv").read_text().splitlines()[1:])
    for addr, name, ext, reach, files in rows:
        i = bisect.bisect_right(defs, addr)
        if i < len(defs) and defs[i] < addr + ext:
            sys.exit(f"error: {name}'s extent runs over the C variable at {defs[i]:08x}; "
                     "rerun tools/shift/data_owners.py")
    skip, cands = [], {}
    probes: dict[str, dict[str, str]] = {}
    for addr, name, ext, reach, files in rows:
        decls: dict[tuple, list] = {}
        unknown = []
        for fn in files:
            d, _why = user_decl(ROOT / fn, name, relax)
            if d:
                decls.setdefault(d, []).append(fn)
            else:
                unknown.append(fn)
        if len(decls) < 2 and not unknown and not (relax and names):
            continue  # agreeing names are the default mode's
        if not decls:
            skip.append((name, "no user has a single file-scope extern"))
            continue
        cands[name] = (addr, ext, reach, files, decls, unknown)
        for (tspec, decl), fns in decls.items():
            probes.setdefault(fns[0], {})
    # sizes: one probe per file, every declaration sized where it is written
    need: dict[str, dict[str, str]] = {}
    for name, (addr, ext, reach, files, decls, unknown) in cands.items():
        for (tspec, decl), fns in decls.items():
            need.setdefault(fns[0], {})[name] = f"{name}[0]" if "[]" in decl else name
    sizes: dict[tuple, int] = {}
    for fn, exprs in need.items():
        try:
            got = probe_sizes(ROOT / fn, exprs)
        except RuntimeError:
            got = {}
        for n, sz in got.items():
            sizes[(fn, n)] = sz
    out = []
    for name, (addr, ext, reach, files, decls, unknown) in sorted(cands.items(), key=lambda kv: kv[1][0]):
        taken = any(address_taken((ROOT / f).read_text(), name) for f in files)
        opts, why, sopts = [], [], []
        # the definition must cover every complete declaration (a user writing
        # `s32 D[2]` reads D[1] even if another writes `s32 D`)
        big = max([sizes.get((fns[0], name), 0) for (t, dcl), fns in decls.items() if "[]" not in dcl] + [0])
        if big > ext:
            skip.append((name, f"a declaration is larger than the extent ({big:#x} > {ext:#x})"))
            continue
        for (tspec, decl), fns in decls.items():
            tag = f"{tspec} {decl}"
            bt = base_type(tspec)
            if not re.fullmatch(r"\**\w+(\[[^\]]*\])?(\[[^\]]+\])*", decl):
                why.append(f"{tag}: declarator not handled")
                continue
            sz = sizes.get((fns[0], name))
            if not sz:
                why.append(f"{tag}: no size")
                continue
            if "[]" in decl:
                if (ext % sz and relax and not others[name] and ext // sz >= 2
                        and align_slack(addr, ext // sz * sz, ext)):
                    d, kind, size = decl.replace("[]", f"[{ext // sz:#x}]", 1), "fill-floor", ext // sz * sz
                elif ext % sz:
                    why.append(f"{tag}: extent not a multiple of {sz:#x}")
                    continue
                elif ext == sz:
                    why.append(f"{tag}: one element fills the extent (users index past it)")
                    continue
                else:
                    d, kind, size = decl.replace("[]", f"[{ext // sz:#x}]", 1), "fill", ext
            elif sz == ext:
                d, kind, size = decl, "exact", sz
            elif (sz < ext and "[" not in decl and not taken and not unknown
                  and reach <= max(sz, 4)):
                d, kind, size = decl, "pad", sz
            elif (relax and sz < ext and not unknown and not others[name] and reach <= max(sz, 4)
                    and align_slack(addr, sz, ext)):
                # taken, or a sized array: the slack is only alignment, and reach_check
                # keeps the name in place if code reaches past it through a pointer
                d, kind, size = decl, "pad-align", sz
            else:
                why.append(f"{tag}: sizeof {sz:#x} vs extent {ext:#x}")
                continue
            if size < big:
                why.append(f"{tag}: smaller than another declaration ({size:#x} < {big:#x})")
                continue
            if "[" in d and addr % 8 and size % 8:
                why.append(f"{tag}: array at an address that is not 8-aligned")
                continue
            score = (KIND_RANK[kind], bt == "M2C_UNK",
                     -sum(f.startswith("src/hand/") for f in fns), -len(fns), "volatile" in tspec, tag)
            if bt not in BASIC:
                why.append(f"{tag}: type {bt} not basic (fits: {kind})")
                sopts.append((score, tspec, decl, d, kind, size, bt, fns))
                continue
            opts.append((score, tspec, decl, d, kind, size))
        tsrc = None
        if not opts and types and sopts:
            for score, tspec, decl, d, kind, size, bt, fns in sorted(sopts, key=lambda o: o[0]):
                if bt in type_move.header_types(ROOT / SHARED):
                    tsrc = (SHARED, bt)
                for f in [] if tsrc else sorted(fns, key=lambda f: not f.startswith("src/hand/")):
                    hp = type_move.header_path(ROOT / f)
                    if hp.exists():
                        ok = bt in type_move.header_types(hp)
                    else:
                        ok = type_move.plan(ROOT / f, [bt])[0] is not None
                    if ok:
                        tsrc = (f, bt)
                        break
                if tsrc:
                    opts.append((score, tspec, decl, d, kind, size))
                    why.append(f"{tag}: type from {tsrc[0]}")
                    break
        if not opts:
            skip.append((name, "; ".join(why)))
            continue
        _sc, tspec, decl, d, kind, size = min(opts)
        out.append((addr, name, files, tspec, decl, d, kind, size, ext, align_for(addr, size), tsrc))
    if types:
        out, more = settle_types(out)
        skip += more
    return out, skip


def settle_types(plans):
    """One type move per source file; no two moved type sets in a module may
    define the same name (the typed header includes them all)."""
    per_src: dict[str, set] = {}
    for p in plans:
        if p[10]:
            per_src.setdefault(p[10][0], set()).add(p[10][1])
    moved: dict[str, set] = {}  # src -> type names its header defines
    bad: dict[str, str] = {}
    for f, ts in per_src.items():
        if f == SHARED:
            moved[f] = type_move.header_types(ROOT / SHARED)
            continue
        src = ROOT / f
        hp = type_move.header_path(src)
        if hp.exists():
            names = type_move.header_types(hp)
            if ts - names:
                bad[f] = f"{hp.relative_to(ROOT)} exists without {sorted(ts - names)}"
            moved[f] = names
            continue
        take, info = type_move.plan(src, sorted(ts))
        if take is None:
            bad[f] = f"type move from {f}: {info}"
            continue
        names = set()
        for k in take:
            names |= info[k][4]
        moved[f] = names
    out, skip, mod_types = [], [], {}
    for p in plans:
        if not p[10]:
            out.append(p)
            continue
        f = p[10][0]
        if f in bad:
            skip.append((p[1], bad[f]))
            continue
        mod = module(p[0])
        if mod not in mod_types:  # the type headers an earlier run already put in this module
            mod_types[mod] = {}
            th = ROOT / "include/data" / f"{mod}_typed.h"
            if th.exists():
                for m in re.finditer(r'#include "data/types/(\w+)\.h"', th.read_text()):
                    for n in type_move.header_types(ROOT / "include/data/types" / f"{m.group(1)}.h"):
                        mod_types[mod][n] = m.group(1)
        have = mod_types[mod]
        key = tkey(f)
        clash = {n for n in moved[f] if have.get(n, key) != key}
        if clash:
            skip.append((p[1], f"type names {sorted(clash)} from {f} clash with another file's in {mod}"))
            continue
        for n in moved[f]:
            have[n] = key
        out.append(p)
    return out, skip


def compiles_with(src: Path, inc: str) -> bool:
    import subprocess, tempfile
    from define_vars import CC
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / src.name
        p.write_text(src.read_text() + (f'\n#include "{inc}"\n' if inc else ""))
        r = subprocess.run([str(CC), "-fsyntax-only", "-x", "c", "-O2", "-G0", "-fno-common",
                            f"-I{ROOT/'include'}", f"-I{ROOT/'src'}", f"-I{src.parent}", str(p)],
                           capture_output=True, text=True)
        return r.returncode == 0


def hkey(p) -> str:
    """The header a mixed plan's declaration goes to: bss_XXXX_mixed (basic
    types) or bss_XXXX_typed (types moved to include/data/types/)."""
    return f"{module(p[0])}_{'typed' if len(p) > 10 and p[10] else 'mixed'}"


def apply_mixed(plans) -> None:
    # move the types first (one header per source file)
    srcs: dict[str, set] = {}
    for p in plans:
        if len(p) > 10 and p[10]:
            srcs.setdefault(p[10][0], set()).add(p[10][1])
    for f, ts in sorted(srcs.items()):
        if f == SHARED:
            continue
        src = ROOT / f
        if type_move.header_path(src).exists():
            continue
        take, info = type_move.plan(src, sorted(ts))
        type_move.apply(src, take, info)
        print(f"types\t{f}\t{type_move.header_path(src).relative_to(ROOT)}", file=sys.stderr)
    heads: dict[str, list] = {}
    for p in plans:
        heads.setdefault(hkey(p), []).append(p)
    for key, ps in heads.items():
        mod, kind = key.rsplit("_", 1)
        guard = f"KH1_DATA_{key.upper()}_H"
        hdr = ROOT / "include/data" / f"{key}.h"
        src = ROOT / "src/data" / f"{mod}.c"
        old, oinc = [], []
        if hdr.exists():  # keep the declarations already there
            old = [ln for ln in hdr.read_text().splitlines() if ln.startswith("extern ")]
            oinc = [ln for ln in hdr.read_text().splitlines() if ln.startswith('#include "data/types/')]
        new = [f"extern {p[3]} {p[4]};" for p in ps]
        decls = sorted(set(old + new), key=lambda ln: re.search(r"D_([0-9A-F]{8})", ln).group(1))
        tinc = sorted(set(oinc) | {f'#include "data/types/{tkey(p[10][0])}.h"'
                                    for p in ps if len(p) > 10 and p[10]})
        m2c = any(re.search(r"\bM2C_UNK", ln) for ln in decls)
        what = "whose users disagree on the type" if kind == "mixed" else "declared with a moved type"
        h = [f"/* Shared bss names {ps[0][0] >> 16:04X}xxxx {what}",
             " * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include",
             " * this at their end; the others keep their own extern. */",
             f"#ifndef {guard}", f"#define {guard}", "", '#include "common.h"']
        h += ['#include "m2c.h"'] if m2c else []
        h += tinc
        h += [""] + decls + ["", f"#endif /* {guard} */", ""]
        hdr.write_text("\n".join(h))
        hdr_inc = f'#include "data/{key}.h"'
        if src.exists():
            text = src.read_text()
        else:
            text = f"/* Definitions of the shared bss names in include/data/{mod}*.h. */\n"
        if hdr_inc not in text:
            lines = text.splitlines(keepends=True)
            inc = [i for i, ln in enumerate(lines) if ln.startswith("#include")]
            at = inc[-1] + 1 if inc else 1
            lines[at:at] = [hdr_inc + "\n"]
            text = "".join(lines)
        if not text.endswith("\n"):
            text += "\n"
        text += "".join(f"{p[3]} {p[5]} ALIGNED({p[9]});\n" for p in ps)
        src.write_text(text)
    # files that already include a header that just grew must still compile
    for key in heads:
        line = f'#include "data/{key}.h"\n'
        for path in sorted((ROOT / "src").rglob("*.c")):
            text = path.read_text(errors="replace")
            if line in text and "src/data/" not in str(path) and not compiles_with(path, None):
                path.write_text(text.replace(line, ""))
                print(f"drop\t{path.relative_to(ROOT)}\tdata/{key}.h", file=sys.stderr)
    # users: include where the file still compiles, else mark the extern
    users: dict[str, list] = {}
    for p in plans:
        for f in p[2]:
            users.setdefault(f, []).append(p)
    for f, ps in sorted(users.items()):
        path = ROOT / f
        for key in sorted({hkey(p) for p in ps}):
            inc = f"data/{key}.h"
            text = path.read_text()
            if f'#include "{inc}"' in text:
                continue
            if compiles_with(path, inc):
                if not text.endswith("\n"):
                    text += "\n"
                path.write_text(text + f'#include "{inc}"\n')
                print(f"include\t{f}\t{inc}", file=sys.stderr)
                continue
            lines = text.splitlines(keepends=True)
            for p in ps:
                if hkey(p) != key:
                    continue
                hits = [i for i, ln in enumerate(lines)
                        if ln.startswith("extern") and re.search(r"\b" + p[1] + r"\b", ln)]
                if len(hits) != 1:
                    continue
                ln = lines[hits[0]]
                pe = parse_extern(ln.rstrip("\n"), p[1])
                if (pe and len(pe[1]) == 1 and "/*" not in ln and "//" not in ln
                        and (norm(pe[0]), norm(pe[1][0])) != (p[3], p[4])):
                    lines[hits[0]] = ln.rstrip("\n") + f" /* src/data/{module(p[0])}.c: {p[3]} {p[5]} */\n"
            path.write_text("".join(lines))
            print(f"keep\t{f}\t{inc}", file=sys.stderr)

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--owners", default=str(ROOT / "out/shift/data_owners.tsv"))
    ap.add_argument("--name", action="append", default=[])
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--mixed", action="store_true", help="names whose users disagree on the type")
    ap.add_argument("--types", action="store_true",
                    help="with --mixed: allow file-local types, moved to include/data/types/")
    ap.add_argument("--exclude", action="append", default=[], help="leave this name alone")
    ap.add_argument("--relax", action="store_true",
                    help="with --mixed: pad-align, fill-floor, repeated extern lines (session 19)")
    a = ap.parse_args()
    if a.mixed:
        plans, skip = plan_mixed(Path(a.owners), a.name, a.types, set(a.exclude), a.relax)
    else:
        plans, skip = plan(Path(a.owners), a.name)
    kinds: dict[str, int] = {}
    for p in plans:
        kinds[p[6]] = kinds.get(p[6], 0) + 1
        print(f"{module(p[0])}\t{p[1]}\t{p[6]}\t{p[7]:#x}/{p[8]:#x}\t{p[3]} {p[5]}\t{len(p[2])} users")
    for n, why in skip:
        print(f"-\t{n}\tskip\t{why}")
    print(f"# {len(plans)} defined ({kinds}), {len(skip)} skipped", file=sys.stderr)
    if a.apply and plans:
        (apply_mixed if a.mixed else apply)(plans)
    return 0


if __name__ == "__main__":
    sys.exit(main())
