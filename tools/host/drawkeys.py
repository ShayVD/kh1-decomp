#!/usr/bin/env python3
"""The draw list's key map: every insert into the draw / immediate list by key (phase 5, renderer-spec 4.12).

  python3 -I tools/host/drawkeys.py [--tsv OUT]

The draw list (renderer-spec 4.1, 4.2) runs its nodes in ascending key order, so the keys are the
port's command order.  This reads src/ for every insert:

  func_0015ed80(key, cb)       the draw list (D_00559DB0), run node by node from the DMAC interrupts
  func_0015ee78(key, cb)       the immediate list (D_0055BDE0), run by task 0x27CB8
  func_00106bd8(packet, key)   a draw list node with callback func_00106b98 sending `packet` on the GIF

A variable in a key that src/ assigns once, from a literal (shadow.c's base D_004F82C4 = 60000), is
read as that literal; a `c ? A : B` of two literals gives a row for each.  A key that is a parameter of the function making the insert (a wrapper such as func_00107d30 or
func_00100670) is followed to every call of that function by name, as deep as it goes; a call with
a literal there is a row "via" the wrapper.  Keys built from a literal and a variable (texanim's
`0x15f92 + k`) are listed at the literal with the variable named.  The rest is data-driven (renderer
B's per-entry `e->x28`, shadow.c's running counter) or reached only through a pointer to the wrapper,
and is listed after the table.

Static and approximate (calls by name, no branches); it reads only the repo's C, no game data.
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
LIST, IMMEDIATE = 0x9C40, 0x27CB8
# insert function: (list name, key argument, callback argument or None for func_00106b98 + packet)
INSERTS = {
    "func_0015ed80": ("draw", 0, 1),
    "func_0015ee78": ("immediate", 0, 1),
    "func_00106bd8": ("draw", 1, None),
}
FN = re.compile(r"^[A-Za-z_][^;{}()=]*?\b(func_[0-9a-f]{8})\s*\(((?:[^;{()]|\([^()]*\))*)\)\s*\{", re.M)
CALL = re.compile(r"(?<![&\w])(func_[0-9a-f]{8})\s*\(")
INT = re.compile(r"^(0[xX][0-9a-fA-F]+|\d+)[uUlL]*$")
IDENT = re.compile(r"[A-Za-z_]\w*")


def bodies():
    """name -> list of (file, params, body)"""
    out: dict[str, list[tuple[str, list[str], str]]] = {}
    for p in sorted((ROOT / "src").rglob("*.c")):
        t = p.read_text(errors="replace")
        for m in FN.finditer(t):
            i = j = m.end()
            depth = 1
            while depth and j < len(t):
                depth += {"{": 1, "}": -1}.get(t[j], 0)
                j += 1
            params = []
            for piece in m.group(2).split(","):
                ids = IDENT.findall(piece)
                params.append(ids[-1] if ids and ids[-1] != "void" else "")
            out.setdefault(m.group(1), []).append((str(p.relative_to(ROOT)), params, t[i:j]))
    return out


def args_at(text: str, i: int) -> list[str]:
    """the arguments of the call whose '(' is at text[i]"""
    depth, cur, out = 0, "", []
    for ch in text[i:]:
        if ch == "(":
            depth += 1
            if depth == 1:
                continue
        elif ch == ")":
            depth -= 1
            if depth == 0:
                out.append(cur.strip())
                return out
        elif ch == "," and depth == 1:
            out.append(cur.strip())
            cur = ""
            continue
        cur += ch
    return out


def strip_casts(e: str) -> str:
    e = e.strip()
    while True:
        m = re.match(r"^\(\s*[A-Za-z_][\w\s]*\**\s*\)\s*(.+)$", e)
        if not m:
            return e.lstrip("&").strip()
        e = m.group(1).strip()


CONST: dict[str, int] = {}


def constants() -> None:
    """the variables src/ assigns exactly once, from a literal, and never changes otherwise"""
    text = "\n".join(p.read_text(errors="replace") for p in sorted((ROOT / "src").rglob("*.c")))
    writes: dict[str, int] = {}
    for m in re.finditer(r"\b(D_[0-9A-F]{8})\s*(?:[-+*/|&^]?=(?!=)|\+\+|--)|(?:\+\+|--|&)\s*(D_[0-9A-F]{8})\b", text):
        n = m.group(1) or m.group(2)
        writes[n] = writes.get(n, 0) + 1
    for name, val in re.findall(r"\b(D_[0-9A-F]{8})\s*=\s*(0[xX][0-9a-fA-F]+|\d+)\s*;", text):
        if writes.get(name) == 1:
            CONST[name] = int(val, 0)


def classify(e: str, params: list[str]):
    """('lit', n) / ('lit+', n, var) / ('param', index, offset) / ('data', text) / ('alt', cond, [n, m])"""
    e = strip_casts(e)
    m = re.match(r"^(.+?)\s*\?\s*(\S+)\s*:\s*(\S+)$", e)
    if m and INT.match(m.group(2)) and INT.match(m.group(3)):
        return ("alt", m.group(1).strip(), [int(m.group(2).rstrip("uUlL"), 0), int(m.group(3).rstrip("uUlL"), 0)])
    if INT.match(e):
        return ("lit", int(e.rstrip("uUlL"), 0))
    e = re.sub(r"\+\+|--", "", e)
    parts = [x.strip() for x in re.split(r"\s*\+\s*", e)]
    parts = [str(CONST[x]) if x in CONST else x for x in parts]
    parts = [x for x in parts if x]
    lits = [x for x in parts if INT.match(x)]
    rest = [x for x in parts if not INT.match(x)]
    off = sum(int(x.rstrip("uUlL"), 0) for x in lits)
    if len(rest) == 1 and rest[0] in params:
        return ("param", params.index(rest[0]), off)
    if lits and rest:
        return ("lit+", off, " + ".join(rest))
    return ("data", e)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--tsv", help="also write the rows (key, list, callback, payload, file, function, via)")
    a = ap.parse_args()
    constants()
    body = bodies()
    callers: dict[str, list[tuple[str, str, list[str], str]]] = {}  # callee -> (caller, file, params, args...)
    pointer: set[str] = set()
    for name, defs in body.items():
        for f, params, b in defs:
            for m in CALL.finditer(b):
                callers.setdefault(m.group(1), []).append((name, f, params, args_at(b, m.end() - 1)))
            for m in re.finditer(r"&?\b(func_[0-9a-f]{8})\b(?!\s*\()", b):
                pointer.add(m.group(1))

    rows = []    # (key, var, list, cb, payload, file, fn, via)
    other = []   # (list, key text, cb, file, fn, via)

    def resolve(fn: str, idx: int, off: int, lst: str, cb: str, payload: str, via: list[str], depth: int):
        cs = callers.get(fn, [])
        if fn in pointer:
            other.append((lst, "(%s's argument %d, through a pointer)" % (fn, idx + 1), cb, "-", fn, via))
        if not cs and fn not in pointer:
            other.append((lst, "(%s has no caller by name)" % fn, cb, "-", fn, via))
        for caller, f, params, args in cs:
            if caller in INSERTS or idx >= len(args):
                continue
            k = classify(args[idx], params)
            add(k, off, lst, cb, payload, f, caller, via + [fn], depth + 1)

    def add(k, off, lst, cb, payload, f, fn, via, depth=0):
        if k[0] == "lit":
            rows.append((k[1] + off, "", lst, cb, payload, f, fn, via))
        elif k[0] == "alt":
            for n, cond in zip(k[2], ("if %s" % k[1], "else")):
                rows.append((n + off, " " + cond, lst, cb, payload, f, fn, via))
        elif k[0] == "lit+":
            rows.append((k[1] + off, k[2], lst, cb, payload, f, fn, via))
        elif k[0] == "param" and depth < 6:
            resolve(fn, k[1], k[2] + off, lst, cb, payload, via, depth)
        else:
            other.append((lst, k[1] if k[0] == "data" else "(too deep)", cb, f, fn, via))

    for ins, (lst, ki, ci) in INSERTS.items():
        for caller, f, params, args in callers.get(ins, []):
            if caller in INSERTS or len(args) < 2:
                continue
            if ci is None:
                cb, payload = "func_00106b98", strip_casts(args[0])
            else:
                cb, payload = strip_casts(args[ci]), ""
            add(classify(args[ki], params), 0, lst, cb, payload, f, caller, [])

    rows.sort(key=lambda r: (r[2] != "draw", r[0], r[1], r[5], r[6]))
    print("# the draw list's inserts by key (task 0x%x starts it; the immediate list runs at task 0x%x)"
          % (LIST, IMMEDIATE))
    print("# key              list       callback        payload        inserted by (file: function [> the wrapper it calls ...])")
    seen = set()
    for key, var, lst, cb, payload, f, fn, via in rows:
        line = "%-18s %-10s %-15s %-14s %s: %s%s" % (
            "0x%X" % key + (var if var.startswith(" ") else "+" + var if var else ""), lst, cb, payload or "-", f, fn,
            "".join(" > " + v for v in reversed(via)) if via else "")
        if line in seen:
            continue
        seen.add(line)
        print(line)
    print("# keys not decided here (data-driven, or a wrapper reached only through a pointer)")
    for lst, key, cb, f, fn, via in sorted(set((o[0], o[1], o[2], o[3], o[4], tuple(o[5])) for o in other)):
        print("%-10s %-15s %s  (%s: %s%s)" % (lst, cb, key, f, fn, "".join(" > " + v for v in reversed(via))))
    if a.tsv:
        with open(a.tsv, "w") as out:
            out.write("key\tvar\tlist\tcallback\tpayload\tfile\tfunction\tvia\n")
            for key, var, lst, cb, payload, f, fn, via in rows:
                out.write("0x%X\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n" % (key, var, lst, cb, payload, f, fn, ",".join(via)))
    print("drawkeys: %d rows with a literal key, %d not decided" % (len(seen), len(set(map(str, other)))),
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
