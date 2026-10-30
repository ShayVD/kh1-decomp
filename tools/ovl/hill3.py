#!/usr/bin/env python3
"""tools/ovl/hill3.py (session 141): dependency-safe statement-order hill climb for an overlay draft.

  python3 tools/ovl/hill3.py OVL func_X draft.c [SECS] [SEED] [--out=best.c] [--rank=words] [--noalias]

Finds runs of simple statements (one per line, same indent, inside the function body: assignments,
x++ / x--, calls) and hill-climbs their order with hand.py's compile-and-diff, keeping a candidate
when (score, words differ) does not get worse and its size gap to the target (|ours - original| bytes)
is no larger than the starting draft's, so a lower score can never come from code going missing.
Ranking by the score first works better than by the word count (wwm2, round 35: on wm
func_00f4c610 the word ranking made things worse); --rank=words ranks by the word count first. Only orders that keep every conflicting pair of
statements in its original order are tried, so the result means the same as the draft:

- two statements conflict when one writes a name the other reads or writes (the base name of the
  left side: `p` for `p[2]`, `o` for `o->x`), except stores to the same array or struct through
  constant indexes or fields (`v[0] = a; v[1] = b;`);
- memory is either an object (a declared array, a struct accessed with `.`, a D_ global, a local
  whose address is taken) or reached through a pointer (`*p`, `p->x`, `p[i]` on a name that is not
  a declared array). A store through a pointer conflicts with every other memory access; a store to
  an object conflicts with every access through a pointer. Different objects never alias;
- calls, `asm`, `++`/`--` inside expressions, chained assignments (`a = b = 0`) and lines with more
  than one statement are barriers; labelled lines and the last line of a multi-line statement never move.

--noalias drops the memory rules except "a store through a pointer never crosses another pointer
access" (stores through different pointers, and pointers against globals, are assumed not to
alias). The orders it finds are usually right for decompiled code, but they are not proven to mean
the same thing.

Read the result before keeping it. The best order goes to --out (default
out/ovl/OVL/hill3/<draft name>).

  python3 tools/ovl/hill3.py --check func_X draft.c candidate.c [--noalias]

checks that candidate.c only reorders draft.c's statement runs in ways these rules allow.
"""
from __future__ import annotations

import random
import re
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hand  # noqa: E402

SIMPLE = re.compile(r"^\s+[^\s{}/#].*;\s*$")
SKIP = re.compile(r"^\s*(if|for|while|do|switch|return|case|default|goto|break|continue|else)\b"
                  r"|^\s*[A-Za-z_]\w*\s*:(?!:)"  # a label, even with a statement after it
                  r"|^\s*(const\s+|static\s+|register\s+|volatile\s+)*"
                  r"(s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|int|char|void|struct|union|unsigned|signed|long|short|float|double|[A-Z]\w*)\b\s*\**\s*\w+\s*(=|;|,|\[)")
ASG = re.compile(r"^(.+?)\s*(\+|-|\*|/|%|<<|>>|&|\||\^)?=(?!=)\s*(.*);$")
ID = re.compile(r"[A-Za-z_]\w*")
CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
KEYWORDS = {"sizeof"}


NOALIAS = "--noalias" in sys.argv  # assume pointers never reach globals or each other's targets
GLOBAL: set[str] = set()  # file-scope arrays and structs, and locals whose address is taken
LOCAL: set[str] = set()  # arrays and structs declared in the function body


def mem(expr: str) -> tuple[bool, bool]:
    """(access through a pointer, access to a global object) in an expression"""
    e = re.sub(r"\([A-Za-z_][\w ]*\**\s*\)", " ", expr)  # drop casts like (u64), (f32 *)
    ptr = "->" in e or bool(re.search(r"(^|[^\w)\]\s])\s*\*\s*[\w(]", e))
    obj = False
    for m in re.finditer(r"\b([A-Za-z_]\w*)\s*(\[|\.(?!\d))?", e):
        n, sub = m.group(1), m.group(2)
        if n in GLOBAL or n.startswith("D_"):
            obj = True
        elif sub == "[" and n not in LOCAL:
            ptr = True
    return ptr, obj


def info(line: str) -> dict:
    s = line.strip()
    body = s[:-1]
    barrier = (";" in body or "asm" in s or any(n not in KEYWORDS for n in CALL.findall(s))
               or len(re.findall(r"(?<![=!<>])(?:<<|>>|[-+*/%&|^])?=(?!=)", body)) > 1)  # a = b = c writes b too
    m2 = re.match(r"^(\w+)\s*(\+\+|--);$", s) or re.match(r"^(?:\+\+|--)\s*(\w+);$", s)
    if m2:
        v = m2.group(1)
        o = v in GLOBAL or v.startswith("D_")
        return {"lhs": v, "base": v, "reads": {v}, "barrier": barrier,
                "wp": False, "wo": o, "rp": False, "ro": o}
    m = ASG.match(s)
    if not m or "++" in s or "--" in s:
        return {"lhs": None, "base": None, "reads": set(ID.findall(s)), "barrier": True}
    lhs, op, rhs = m.group(1).strip(), m.group(2), m.group(3)
    lids = ID.findall(lhs)
    base = lids[0] if lids else lhs
    reads = set(ID.findall(rhs)) | set(lids[1:])
    if op:
        reads.add(base)
    lhs_index = re.sub(r"^\W*\w+", "", lhs)  # what follows the base name: [i], ->x, .f
    wp, wo = mem(lhs)
    if not lhs.startswith("*") and "->" not in lhs and "[" not in lhs:
        wp, wo = False, base in GLOBAL or base.startswith("D_")
    rp1, ro1 = mem(rhs)
    rp2, ro2 = mem(lhs_index)
    rp, ro = rp1 or rp2, ro1 or ro2
    if op:
        rp, ro = rp or wp, ro or wo
    return {"lhs": lhs, "base": base, "reads": reads, "barrier": barrier, "wp": wp, "wo": wo, "rp": rp, "ro": ro}


def conflict(a: dict, b: dict) -> bool:
    if a["barrier"] or b["barrier"]:
        return True
    if a["lhs"] == b["lhs"] or a["base"] in b["reads"] or b["base"] in a["reads"]:
        return True
    if a["base"] == b["base"]:
        const = re.compile(r"^\w+((\[\d+\])|(\.\w+)|(->\w+))+$")
        return not (const.match(a["lhs"].replace(" ", "")) and const.match(b["lhs"].replace(" ", "")))
    for x, y in ((a, b), (b, a)):
        if NOALIAS:
            if x["wp"] and (y["rp"] or y["wp"]) and not x["lhs"].startswith("D_") and not y["lhs"].startswith("D_"):
                return True
            continue
        if x["wp"] and (y["rp"] or y["ro"] or y["wp"] or y["wo"]):
            return True
        if x["wo"] and (y["rp"] or y["wp"]):
            return True
    return False


def scan_objects(lines: list[str], start: int) -> None:
    GLOBAL.clear()
    LOCAL.clear()
    for n, ln in enumerate(lines):
        s = ln.strip()
        decl = n < start or SKIP.match(ln)
        if decl and not s.startswith("typedef") and not re.match(r"^(if|for|while|return)\b", s):
            names = {m.group(1) for m in re.finditer(r"\b([A-Za-z_]\w*)\s*\[", s)}
            if n < start:
                if s.startswith("extern") or re.match(r"^(static\s+)?[A-Za-z_][\w ]*\s\**\w+\s*(\[|;|=)", s):
                    GLOBAL.update(names)
                    m = re.match(r"^(extern\s+|static\s+)*[A-Za-z_]\w*\s+(\w+)\s*(;|=)", s)
                    if m and not re.match(r"^(extern\s+|static\s+)*(s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|int|char|float|double|long|short)\b", s):
                        GLOBAL.add(m.group(2))  # a struct object at file scope
            else:
                LOCAL.update(names)
                m = re.match(r"^[A-Za-z_]\w*\s+(\w+)\s*;", s)
                if m:
                    LOCAL.add(m.group(1))  # a local struct (or scalar)
        for m in re.finditer(r"&\s*([A-Za-z_]\w*)", ln):
            GLOBAL.add(m.group(1))


def blocks(lines: list[str], func: str) -> list[tuple[int, int, list[str], list[tuple[int, int]]]]:
    start = next((i for i, ln in enumerate(lines)
                  if re.match(r"^\w.*\b%s\s*\(" % func, ln) and not ln.rstrip().endswith(";")), None)
    if start is None:
        return []
    scan_objects(lines, start)
    out = []
    i = start + 1
    while i < len(lines):
        prev = lines[i - 1].split("//")[0].rstrip()
        cont = bool(prev) and not prev.endswith((";", "{", "}", ":", "*/")) and not prev.lstrip().startswith("#")
        if SIMPLE.match(lines[i]) and not SKIP.match(lines[i]) and not cont:  # cont: the end of a multi-line statement
            ind = len(lines[i]) - len(lines[i].lstrip())
            j = i
            while (j + 1 < len(lines) and SIMPLE.match(lines[j + 1]) and not SKIP.match(lines[j + 1])
                   and len(lines[j + 1]) - len(lines[j + 1].lstrip()) == ind):
                j += 1
            orig = lines[i:j + 1]
            inf = [info(x) for x in orig]
            cons = [(x, y) for x in range(len(orig)) for y in range(x + 1, len(orig)) if conflict(inf[x], inf[y])]
            if len(orig) > 1 and len(cons) < len(orig) * (len(orig) - 1) // 2:
                out.append((i, j + 1, orig, cons))
            i = j + 1
        else:
            i += 1
    return out


GAPS: dict[str, int] = {}


def score(name: str, func: str, code: str) -> tuple[int, int]:
    ok, out = hand.try_code(name, func, code, diff=False)
    if ok:
        GAPS[code] = 0
        return (0, 0)
    g = re.search(r"\((\d+) vs (\d+) bytes", out)
    GAPS[code] = abs(int(g.group(1)) - int(g.group(2))) if g else 10**6
    m = re.search(r"(\d+) words differ, score (\d+)", out)
    return (int(m.group(1)), int(m.group(2))) if m else (10**6, 10**6)


def check(func: str, draft: Path, cand: Path) -> int:
    a, b = draft.read_text().split("\n"), cand.read_text().split("\n")
    bl = blocks(a, func)
    inblock = set()
    bad = []
    for s, e, orig, cons in bl:
        inblock.update(range(s, e))
        new = b[s:e]
        if sorted(new) != sorted(orig):
            bad.append(f"lines {s + 1}-{e}: not a reordering of the draft's statements")
            continue
        used, pos = set(), {}
        for n, ln in enumerate(new):
            k = next(k for k, o in enumerate(orig) if o == ln and k not in used)
            used.add(k)
            pos[k] = n
        for x, y in cons:
            if pos[x] > pos[y]:
                bad.append(f"line {s + 1 + x} moved past line {s + 1 + y}: {orig[x].strip()} / {orig[y].strip()}")
    if len(a) != len(b) or any(a[i] != b[i] for i in range(len(a)) if i not in inblock):
        bad.append("lines outside the statement runs differ")
    print("\n".join(bad) if bad else "ok")
    return 1 if bad else 0


def main() -> int:
    if sys.argv[1:2] == ["--check"]:
        a = [x for x in sys.argv[2:] if not x.startswith("--")]
        return check(a[0], Path(a[1]), Path(a[2]))
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    outs = [a.split("=", 1)[1] for a in sys.argv[1:] if a.startswith("--out=")]
    by_words = "--rank=words" in sys.argv[1:]
    if len(args) < 3:
        sys.exit(__doc__)
    name, func, draft = args[0], args[1], Path(args[2])
    secs = float(args[3]) if len(args) > 3 else 120.0
    random.seed(int(args[4]) if len(args) > 4 else 1)
    hand.MODE = draft.suffixes[-2][1:] if len(draft.suffixes) > 1 else ""
    out = Path(outs[0]) if outs else hand.ROOT / "out" / "ovl" / name / "hill3" / draft.name
    lines = draft.read_text().split("\n")
    bl = blocks(lines, func)
    if not bl:
        print(f"{func}: no movable statements")
        return 1
    perms = [list(range(b - a)) for a, b, _, _ in bl]

    def render(ps: list[list[int]]) -> str:
        ll = list(lines)
        for (a, b, orig, _), pm in zip(reversed(bl), reversed(ps)):
            ll[a:b] = [orig[k] for k in pm]
        return "\n".join(ll)

    def key(s: tuple[int, int]) -> tuple[int, int]:
        return s if by_words else (s[1], s[0])

    code0 = render(perms)
    best = start = score(name, func, code0)
    gap0 = GAPS.pop(code0)
    t0, tries, invalid, toobig = time.time(), 0, 0, 0
    while time.time() - t0 < secs and best[0] > 0 and invalid < 5000:
        k = random.randrange(len(bl))
        pm = list(perms[k])
        x, y = random.sample(range(len(pm)), 2)
        if random.random() < 0.5:
            pm[x], pm[y] = pm[y], pm[x]
        else:
            pm.insert(y, pm.pop(x))
        pos = {v: n for n, v in enumerate(pm)}
        if not all(pos[a] < pos[b] for a, b in bl[k][3]):
            invalid += 1
            continue
        invalid = 0
        cand = perms[:k] + [pm] + perms[k + 1:]
        code = render(cand)
        s = score(name, func, code)
        tries += 1
        if GAPS.pop(code) > gap0:
            toobig += 1
            continue
        if key(s) <= key(best):
            if key(s) < key(best):
                out.parent.mkdir(parents=True, exist_ok=True)
                out.write_text(render(cand))
            best, perms = s, cand
    print(f"{func}: {len(bl)} blocks, start {start[0]} words / score {start[1]}, "
          f"best {best[0]} / {best[1]}, {tries} tries, {toobig} over the size gap {gap0}" + (f" -> {out}" if key(best) < key(start) else ""))
    return 0


if __name__ == "__main__":
    sys.exit(main())
