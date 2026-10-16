#!/usr/bin/env python3
"""Find struct types hiding behind M2C_FIELD(argN, T *, offset) accesses.

Functions that hand their own first argument, unchanged, to another
function's first argument probably agree on its type (methods of one
"class": actor update calling actor helpers). This groups functions that
way (union-find over a0 passed through to calls, from the original machine
code), then lists, for the biggest groups, which offsets their matched C
code reads and writes through arg0 and with what types.

  tools/structs.py                  # top groups, with field tables
  tools/structs.py --group func_X   # the group containing func_X
  tools/structs.py apply --seed func_X --struct Actor --header include/actor.h [--write]
      # write the struct and rewrite the group's matched functions to use it
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K  # noqa: E402
import mips  # noqa: E402
import sigs as S  # noqa: E402

FIELD_RE = re.compile(r"M2C_FIELD\(arg0, ([\w ]+?) \*, (0x[0-9A-Fa-f]+|\d+)\)")
SDK_START = 0x0024F2E0
DEF_RE = re.compile(r"^\S[^\n;]*?\b(\w+)\(([^)]*)\) \{$", re.M)


def c_functions() -> dict[str, tuple[Path, str, str]]:
    """name -> (file, parameter list, body) for every function in src/."""
    out = {}
    for src in K.iter_sources():
        if src.suffix != ".c":
            continue
        text = src.read_text()
        for m in DEF_RE.finditer(text):
            end = text.find("\n}\n", m.end())
            out[m.group(1)] = (src, m.group(2), text[m.end(): end + 2])
    return out


def passthrough_edges(cfg) -> list[tuple[int, int]]:
    """(caller, callee) where the caller's a0 reaches the callee's a0 unchanged."""
    funcs = S.disassemble(cfg)
    edges = []
    for a, insns in funcs.items():
        alias = {"a0"}  # registers holding the incoming a0
        k = 0
        while k < len(insns):
            mn, ops, w = insns[k]
            i = mips.Insn(a + 4 * k, w)
            if (i.is_jal or i.is_j) and k + 1 < len(insns):
                dmn, dops, _ = insns[k + 1]
                rd, wr = S.rw(dmn, dops)
                al = set(alias)
                if dmn == "move" and len(rd) == 1 and rd[0] in alias:
                    al |= set(wr)
                else:
                    al -= set(wr)
                t = i.jump_target
                if "a0" in al and not a <= t < a + 4 * len(insns):
                    edges.append((a, t))
                alias = {r for r in alias if r.startswith("s")}  # calls clobber the rest
                k += 2
                continue
            rd, wr = S.rw(mn, ops)
            if mn == "move" and len(rd) == 1 and rd[0] in alias:
                alias |= set(wr)
            else:
                alias -= set(wr)
            if i.is_jr_ra or not alias:
                pass
            k += 1
    return edges


def groups(cfg) -> dict[int, list[int]]:
    parent: dict[int, int] = {}

    def find(x):
        parent.setdefault(x, x)
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x
    edges = passthrough_edges(cfg)
    regions = defaultdict(set)
    for a, b in edges:
        regions[b].add(a >> 16)
    for a, b in edges:
        # Generic helpers (called with a0 passed through from all over the
        # game, or SDK code) take many types and would merge everything.
        if b < SDK_START and len(regions[b]) <= 2:
            parent[find(a)] = find(b)
    out = defaultdict(list)
    for x in list(parent):
        out[find(x)].append(x)
    return out


SIZEOF = {"s8": 1, "u8": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "f32": 4, "s64": 8, "u64": 8,
          "void *": 4, "M2C_UNK": 4}
PARAM_RE = r"(?:void \*|[su]32 |M2C_UNK |[A-Z]\w* \*)arg0\b"  # untyped, or already a struct


def convertible(params: str, body: str) -> bool:
    """arg0 is a 4-byte parameter used only as a field base, a call
    argument or compared with NULL."""
    if not re.match(rf"^{PARAM_RE}", params):
        return False
    rest = re.sub(r"M2C_FIELD\(arg0, |\barg0->", "", body)
    rest = re.sub(r"(?<=[(,] )arg0(?=[,)])|(?<=\()arg0(?=[,)])|arg0 [!=]= (NULL|0)\b", "", rest)
    return not re.search(r"\barg0\b", rest)


def layout_fields(uses: dict[int, Counter]) -> dict[int, str]:
    """offset -> the most common access type, dropping overlaps (the more
    common offset wins). Accesses with another type keep their M2C_FIELD.
    A 64-bit word also accessed as two 32-bit halves becomes a union: the
    64-bit type is then stored under the key `(offset, 64)`."""
    single = {o: c.most_common(1)[0][0] for o, c in uses.items() if c.most_common(1)[0][0] in SIZEOF}
    # 64-bit accesses at an offset whose words are also used as 32-bit fields
    wide = {}
    for o, c in uses.items():
        t64 = next((t for t, _n in c.most_common() if t in ("s64", "u64")), None)
        if t64 and o % 8 == 0 and (SIZEOF.get(single.get(o)) == 4 or SIZEOF.get(single.get(o + 4)) == 4):
            wide[o] = t64
            single.pop(o, None) if SIZEOF.get(single.get(o)) == 8 else None
    by_count = sorted(single, key=lambda o: -sum(uses[o].values()))
    taken: list[tuple[int, int]] = []
    out: dict = {}
    for o in by_count:
        size = SIZEOF[single[o]]
        if o % size:
            continue
        if any(o < e and b < o + size for b, e in taken):
            continue
        taken.append((o, o + size))
        out[o] = single[o]
    for o, t in wide.items():
        # both halves must be plain words (or free) for the union
        if all(out.get(h, "s32") in ("s32", "u32", "f32", "void *") for h in (o, o + 4)) and \
                not any(b < o + 8 and o < e and b not in (o, o + 4) for b, e in taken):
            out[(o, 64)] = t
            for h in (o, o + 4):
                out.setdefault(h, "s32")
    return dict(sorted(out.items(), key=lambda kv: kv[0] if isinstance(kv[0], int) else kv[0][0]))


def field_name(o: int, t: str, fields: dict) -> str | None:
    """The struct member that an access of type `t` at offset `o` maps to."""
    if fields.get(o) == t:
        return f"unk{o:03X}"
    if t in ("s64", "u64") and fields.get((o, 64)) == t:
        return f"unk{o:03X}_64"
    return None


def header_text(name: str, guard: str, fields: dict[int, str], note: str) -> str:
    lines = [f"/* {note} */", f"#ifndef {guard}", f"#define {guard}", "", '#include "common.h"', "",
             f"typedef struct {name} {{"]
    pos = 0
    unions = {k[0]: t for k, t in fields.items() if isinstance(k, tuple)}
    plain = {o: t for o, t in fields.items() if isinstance(o, int)}
    for o, t in plain.items():
        if o > pos:
            lines.append(f"    u8 pad{pos:03X}[0x{o - pos:X}];")
        ctype = "void *" if t == "void *" else t + " "
        if o in unions:
            hi = plain[o + 4]
            lines += ["    union {", f"        {unions[o]} unk{o:03X}_64;", "        struct {",
                      f"            {ctype}unk{o:03X};",
                      f"            {'void *' if hi == 'void *' else hi + ' '}unk{o + 4:03X};",
                      "        };", "    };"]
            pos = o + 8
            continue
        if o - 4 in unions:
            continue
        lines.append(f"    {ctype}unk{o:03X};")
        pos = o + SIZEOF[t]
    lines.append(f"}} {name}; /* size unknown: at least 0x{pos:X} */")
    lines.append("")
    for o in list(plain)[-1:]:
        lines.append(f"/* layout check: the last known field must sit at 0x{o:X} */")
        lines.append(f"typedef char {name}_check_{o:X}[(sizeof(struct {name}) == 0x{pos:X}) ? 1 : -1];")
    lines += ["", f"#endif /* {guard} */", ""]
    return "\n".join(lines)


def cmd_apply(args) -> int:
    cfg = K.load_config()
    names = {a: s for s, a in K.load_registry().items()}
    cfuncs = c_functions()
    seed = K.find_func(args.seed).addr
    group = next(g for g in groups(cfg).values() if seed in g)
    members = [names.get(x, f"func_{x:08x}") for x in sorted(group)]
    conv = [n for n in members if n in cfuncs and convertible(cfuncs[n][1], cfuncs[n][2])
            and FIELD_RE.search(cfuncs[n][2])]
    uses: dict[int, Counter] = defaultdict(Counter)
    for n in conv:
        for t, off in FIELD_RE.findall(cfuncs[n][2]):
            uses[int(off, 0)][t] += 1
    # Unmatched members' closest drafts (autodecomp batch writes them) add
    # evidence for the layout; only matched code is rewritten.
    fail_dir = K.OUT / "autodecomp" / "fail"
    drafts = 0
    for x in sorted(group):
        p = fail_dir / f"{x:08x}.c"
        if names.get(x, f"func_{x:08x}") not in cfuncs and p.exists():
            m = DEF_RE.search(p.read_text())
            if m and re.match(rf"^{PARAM_RE}", m.group(2)):
                drafts += 1
                for t, off in FIELD_RE.findall(p.read_text()):
                    uses[int(off, 0)][t] += 1
    hdr = K.ROOT / args.header
    if hdr.exists():  # fields already in use by rewritten code must stay
        for t, off in re.findall(r"^\s+(void \*|[su](?:8|16|32|64) |f32 )unk([0-9A-F]+)(?:_64)?;", hdr.read_text(), re.M):
            uses[int(off, 16)][t.strip() if t != "void *" else t] += 1000
    fields = layout_fields(uses)
    guard = "KH1_" + re.sub(r"\W", "_", hdr.stem.upper()) + "_H"
    note = (f"{args.struct}: recovered from M2C_FIELD accesses in {len(conv)} matched functions (and\n"
            f" * {drafts} unmatched drafts) that pass\n"
            f" * the same first argument to each other (tools/structs.py apply --seed {args.seed}).\n"
            " * Field names are offsets until their meaning is known.")
    print(f"group {len(group)} functions, {len(conv)} convertible, {drafts} unmatched drafts, {len(fields)} fields")
    if not args.write:
        print(header_text(args.struct, guard, fields, note))
        return 0
    hdr.write_text(header_text(args.struct, guard, fields, note))
    files: dict[Path, list[str]] = defaultdict(list)
    for n in conv:
        files[cfuncs[n][0]].append(n)
    for path, fns in files.items():
        text = path.read_text()
        for n in fns:
            m = re.search(rf"^(\S[^\n;]*?\b{n}\()({PARAM_RE})", text, re.M)
            start = m.start()
            end = text.find("\n}\n", start)
            func = text[start:end]
            func = re.sub(rf"^(\S[^\n;]*?\b{n}\(){PARAM_RE}", rf"\g<1>{args.struct} *arg0", func, count=1, flags=re.M)

            def fld(mm: re.Match) -> str:
                o = int(mm.group(2), 0)
                n = field_name(o, mm.group(1), fields)
                return f"arg0->{n}" if n else mm.group(0)
            func = FIELD_RE.sub(fld, func)
            text = text[:start] + func + text[end:]
        inc = f'#include "{hdr.name}"'
        if inc not in text:
            text = text.replace('#include "m2c.h"\n', f'#include "m2c.h"\n{inc}\n', 1)
        path.write_text(text)
        print(f"rewrote {len(fns)} functions in {path.relative_to(K.ROOT)}")
    return 0


def main() -> int:
    if sys.argv[1:2] == ["apply"]:
        ap = argparse.ArgumentParser(prog="structs.py apply")
        ap.add_argument("--seed", required=True, help="a function in the group")
        ap.add_argument("--struct", required=True)
        ap.add_argument("--header", required=True, help="e.g. include/actor.h")
        ap.add_argument("--write", action="store_true")
        return cmd_apply(ap.parse_args(sys.argv[2:]))
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--group")
    ap.add_argument("--top", type=int, default=5)
    args = ap.parse_args()
    cfg = K.load_config()
    names = {a: s for s, a in K.load_registry().items()}
    cfuncs = c_functions()
    gs = groups(cfg)
    if args.group:
        a = K.find_func(args.group).addr
        sel = [g for g in gs.values() if a in g]
    else:
        def weight(g):
            return sum(len(FIELD_RE.findall(cfuncs[names.get(x, f"func_{x:08x}")][2]))
                       for x in g if names.get(x, f"func_{x:08x}") in cfuncs)
        sel = sorted(gs.values(), key=weight, reverse=True)[: args.top]
    for g in sel:
        fields: dict[int, Counter] = defaultdict(Counter)
        users = 0
        for x in sorted(g):
            n = names.get(x, f"func_{x:08x}")
            if n not in cfuncs:
                continue
            found = FIELD_RE.findall(cfuncs[n][2])
            users += bool(found)
            for t, off in found:
                fields[int(off, 0)][t] += 1
        print(f"group of {len(g)} functions ({users} matched ones use arg0 fields), e.g. "
              + ", ".join(names.get(x, f"func_{x:08x}") for x in sorted(g)[:6]))
        for off in sorted(fields):
            print(f"  0x{off:04X}  " + ", ".join(f"{t} x{c}" for t, c in fields[off].most_common()))
    return 0


if __name__ == "__main__":
    sys.exit(main())
