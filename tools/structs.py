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
NEAR = 0x4000
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
    for a, b in passthrough_edges(cfg):
        # Only callees close by (likely the same source file): generic helpers
        # far away take many types and would merge everything.
        if abs(a - b) < NEAR:
            parent[find(a)] = find(b)
    out = defaultdict(list)
    for x in list(parent):
        out[find(x)].append(x)
    return out


def main() -> int:
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
