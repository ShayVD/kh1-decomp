"""Source-level fixes and permutations for m2c output (used by autodecomp.py).

Two kinds of rewrite:

- `preprocess`: fixes that are right for every function. Adds prototypes
  for callees m2c left undeclared (from tools/sigs.py), restores unused
  leading parameters m2c drops (`f(void *arg1)` -> `f(s32 arg0, void *arg1)`),
  and respells float literals so ee-gcc 2.96 produces the original bits
  (its decimal conversion is off by one ULP for some spellings).
- `variants`: alternative readings of the same draft to try first, e.g.
  byte-scaled pointer arithmetic on `M2C_UNK *`.
- `mutations`: single small edits for the greedy search: toggle the
  signedness of one type, give one `M2C_UNK` a concrete type, swap two
  adjacent statements or declarations, drop one cast, inline a temp used
  once. None of them changes what a correct program means in a way gcc would
  notice, except type changes, which the byte comparison judges.
"""
from __future__ import annotations

import itertools
import re
import struct
import subprocess
import tempfile
from pathlib import Path

# --------------------------------------------------------------------------- prototypes

CALL_RE = re.compile(r"\b([A-Za-z_]\w*)\s*\(")


def add_prototypes(code: str, sigs: dict[str, str]) -> str:
    """Declare every referenced func_ that has neither a declaration nor a
    definition in `code`, using the guessed prototype."""
    declared = set(re.findall(r"^(?!\s)[^\n;{}(]*?\b(\w+)\s*\(", code, re.M))
    missing = []
    for name in dict.fromkeys(CALL_RE.findall(code)):
        if name not in declared and name in sigs and not re.search(rf"&{name}\b|\b{name}\b(?!\s*\()", code):
            missing.append(sigs[name])
    return ("\n".join(missing) + "\n" + code) if missing else code


SIG_RE = re.compile(r"^(?P<ret>[\w ]+?\*?)\s*(?P<name>\w+)\((?P<params>[^)]*)\)\s*\{", re.M)


def fill_params(code: str) -> str:
    """m2c omits leading parameters a function never reads: `f(void *arg1)`.
    Restore them so the remaining ones land in the right registers."""
    def fix(m: re.Match) -> str:
        params = [p.strip() for p in m.group("params").split(",") if p.strip() and p.strip() != "void"]
        if not params:
            return m.group(0)
        idx = {}
        for p in params:
            a = re.search(r"\barg(\d+)$", p)
            if not a:
                return m.group(0)
            idx[int(a.group(1))] = p
        ints = sorted(idx)
        if ints == list(range(len(ints))):
            return m.group(0)
        new = [idx.get(i, f"s32 arg{i}") for i in range(max(ints) + 1)]
        fl = [p for p in params if not re.search(r"\barg\d+$", p)]
        return f"{m.group('ret')} {m.group('name')}({', '.join(new + fl)}) {{"
    return SIG_RE.sub(fix, code)


# --------------------------------------------------------------------------- floats

FLOAT_RE = re.compile(r"(?<![\w.])(\d+\.\d*(?:[eE][+-]?\d+)?|\d+[eE][+-]?\d+)f\b")
_float_cache: dict[int, str] = {}


def f32_bits(text: str) -> int:
    return struct.unpack("<I", struct.pack("<f", float(text)))[0]


def _spellings(bits: int) -> list[str]:
    v = struct.unpack("<f", struct.pack("<I", bits))[0]
    out = []
    for b in (bits, bits - 1, bits + 1):
        w = struct.unpack("<f", struct.pack("<I", b & 0xFFFFFFFF))[0]
        for n in range(1, 13):
            s = f"{w:.{n}g}"
            if "e" not in s and "." not in s:
                s += ".0"
            out.append(s)
    # midpoints towards the neighbours (truncating converters)
    for b in (bits - 1, bits + 1):
        w = struct.unpack("<f", struct.pack("<I", b & 0xFFFFFFFF))[0]
        for n in range(1, 12):
            s = f"{(v + w) / 2:.{n}g}"
            out.append(s if ("." in s or "e" in s) else s + ".0")
    import math
    return [x for x in dict.fromkeys(out) if "n" not in x]  # no nan/inf


def resolve_floats(bits_list: list[int], cc: str) -> None:
    """Find, for each target bit pattern, a literal that ee-gcc turns into
    exactly those bits (one compiler run for all candidates)."""
    todo = [b for b in dict.fromkeys(bits_list) if b not in _float_cache]
    if not todo:
        return
    cands = [(b, s) for b in todo for s in _spellings(b)]
    src = "".join(f"float x{i} = {s}f;\n" for i, (_b, s) in enumerate(cands))
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / "f.c"
        p.write_text(src)
        r = subprocess.run([cc, "-S", "-O2", "-G0", "-o", "-", str(p)], capture_output=True, text=True)
    words = [int(m.group(1), 16) for m in re.finditer(r"\.word\s+0x([0-9a-f]+)", r.stdout)]
    if len(words) != len(cands):
        return
    for (b, s), w in zip(cands, words):
        if w == b and b not in _float_cache:
            _float_cache[b] = s


def fix_floats(code: str, cc: str) -> str:
    lits = FLOAT_RE.findall(code)
    if not lits:
        return code
    resolve_floats([f32_bits(l) for l in lits], cc)

    def sub(m: re.Match) -> str:
        b = f32_bits(m.group(1))
        return _float_cache.get(b, m.group(1)) + "f"
    return FLOAT_RE.sub(sub, code)


def preprocess(code: str, sigs: dict[str, str], cc: str, locals_size: int = 0) -> str:
    return wide_consts(stack_buffer(fix_floats(fill_params(add_prototypes(code, sigs)), cc), locals_size))


SHIFT_CONST_RE = re.compile(r"\((-?(?:0x[0-9A-Fa-f]+|\d+)) << (0x[0-9A-Fa-f]+|\d+)\)")


def wide_consts(code: str) -> str:
    """m2c writes 64-bit constants built with `li; dsll32` as `(0x8000 << 0x22)`,
    an int shift that overflows. Make the shift 64-bit."""
    def fix(m: re.Match) -> str:
        n, k = int(m.group(1), 0), int(m.group(2), 0)
        if k < 32 and -0x80000000 <= (n << k) <= 0xFFFFFFFF:
            return m.group(0)
        return f"((s64) {m.group(1)} << {m.group(2)})"
    return SHIFT_CONST_RE.sub(fix, code)


# --------------------------------------------------------------------------- stack locals

SPVAR_RE = re.compile(r"\bsp([0-9A-F]+)\b")
SPDECL_RE = re.compile(r"^\s+((?:[su](?:8|16|32|64)|f32|f64|M2C_UNK\d*|void \*|[\w ]+\*)) ?sp([0-9A-F]+)(\[[^\]]*\])?;[^\n]*\n", re.M)


def stack_buffer(code: str, locals_size: int) -> str:
    """m2c writes the address of the frame's bottom as a bare `sp` (a
    matrix or struct at sp+0 passed by address) and the other words of that
    object as separate `spXX` variables, some never declared. gcc cannot
    compile that; declare the whole locals area as one buffer named `sp`
    instead, and turn `spXX` into `M2C_FIELD(sp, T *, 0xXX)`.
    `locals_size`: bytes below the callee-saved registers."""
    if not locals_size or not re.search(r"\bsp\b(?!\s*=)", code):
        return code
    start = re.search(r"^\S.*\)\s*\{\s*$", code, re.M)
    if not start:
        return code
    head, body = code[: start.end()], code[start.end():]
    types = {}
    for m in SPDECL_RE.finditer(body):
        if m.group(3):
            return code  # m2c already declared an array; leave it alone
        types[int(m.group(2), 16)] = m.group(1).strip()
    body = SPDECL_RE.sub(lambda m: "" if int(m.group(2), 16) < locals_size else m.group(0), body)

    def field(m: re.Match) -> str:
        off = int(m.group(1), 16)
        if off >= locals_size:
            return m.group(0)
        t = types.get(off, "M2C_UNK")
        return f"M2C_FIELD(sp, {t} *, 0x{off:X})"
    body = SPVAR_RE.sub(field, body)
    return head + f"\n    s32 sp[{(locals_size + 3) // 4}];" + body


# --------------------------------------------------------------------------- variants

def variants(code: str) -> list[str]:
    """Whole-draft alternatives worth trying before the search."""
    out = []
    # m2c means byte offsets for arithmetic on unknown-typed pointers.
    v = re.sub(r"\*\(&(D_[0-9A-F]{8}) \+ ", r"*(M2C_UNK *)((s8 *)&\1 + ", code)
    v = re.sub(r"(?<!\*\()&(D_[0-9A-F]{8}) ([+-]) ", r"(s8 *)&\1 \2 ", v)
    v = re.sub(r"(\w) ([+-]) &(D_[0-9A-F]{8})\b", r"\1 \2 (s8 *)&\3", v)  # `i * 4 + &D_X`
    v = re.sub(r"\bM2C_UNK \*(\w+);", r"s8 *\1;", v)
    if v != code:
        out.append(v)
    # m2c counts pointer increments in bytes even on typed pointers
    v = scale_increments(code)
    if v != code:
        out.append(v)
    v = rebase_fields(code)
    if v != code:
        out.append(v)
    # globals only used as `M2C_FIELD(&D_X, T *, off)` are arrays of T: gcc
    # addresses array elements from one base, not symbol+offset each time
    v = as_arrays(code)
    if v != code:
        out.append(v)
    # counter loops m2c split into a counter and a copy, and callees whose
    # result is unused declared void (together: func_00157668)
    # the game's inline square root (bare sqrt.s, no sqrtf call)
    if re.search(r"\bsqrtf\(", code):
        out.append(re.sub(r"^f32 sqrtf\(f32\);\n", "", re.sub(r"(?<!\w)sqrtf\(", "PlatSqrtf(", code), flags=re.M))
    # m2c's `loop_N: ... goto loop_N;` as a real loop: gcc only aligns loop
    # heads (`.p2align 3`, a nop before the head) for loops it sees as loops,
    # which shows in ee-gcc 2.9-991111 code (scePad2End)
    for v in list(out) + [code]:
        gl = goto_loops(v)
        if gl != v:
            out.append(gl)
    lp = copy_loop(code)
    for v in (lp, void_callees(code), void_callees(lp)):
        if v != code:
            out.append(v)
    # all globals volatile / none volatile, as search starting points (the
    # search toggles one at a time, which misses fixes needing two edits)
    for v in list(out) + [code]:
        for w in (re.sub(r"^extern volatile ", "extern ", v, flags=re.M),
                  re.sub(r"^extern (?!volatile)", "extern volatile ", v, flags=re.M)):
            if w != v and w != code:
                out.append(w)
    return list(dict.fromkeys(out))


NARROW_LOAD_RE = re.compile(r"M2C_FIELD\((?:[^(),]|\([^()]*\))+, ([su](?:8|16|32)) \*, (?:0x[0-9A-Fa-f]+|\d+)\)|\*(arg\d+)\b")
WIDER = {"8": ("s32", "u32", "u64"), "16": ("s32", "u32", "u64"), "32": ("u64", "s64")}


def widen_loads(code: str):
    start = re.search(r"^\S.*\)\s*\{\s*$", code, re.M)
    if not start:
        return
    head, body = code[: start.end()], code[start.end():]
    narrow_globals = dict((n, t) for t, n in re.findall(r"^extern (?:volatile )?([su](?:8|16|32)) (D_[0-9A-F]{8});$", code, re.M))
    params = dict((n, t) for t, n in re.findall(r"([su](?:8|16|32)) \*(arg\d+)", head))
    for m in re.finditer(r"^(\s+)(?!return\b)([^\n;{}]*);$", body, re.M):
        ind, stmt = m.group(1), m.group(2)
        cands = []
        cm = re.match(r"^(\S.*?) ([-+|&^]|<<|>>)= (.+)$", stmt)  # x op= y
        if cm:
            for n, t in narrow_globals.items():
                if cm.group(1) == n:
                    cands.append((t, n, f"{n} = {{w}} {cm.group(2)} {cm.group(3)}"))
        rhs_at = stmt.find(" = ") + 3 if " = " in stmt else 0
        for lm in NARROW_LOAD_RE.finditer(stmt, rhs_at):
            t = lm.group(1) or params.get(lm.group(2))
            if t:
                cands.append((t, lm.group(0), stmt[:lm.start()] + "{w}" + stmt[lm.end():]))
        for gn, t in narrow_globals.items():
            for gm in re.finditer(rf"\b{gn}\b", stmt[rhs_at:]):
                a = rhs_at + gm.start()
                cands.append((t, gn, stmt[:a] + "{w}" + stmt[a + len(gn):]))
        yield from _widen(head, body, m, ind, cands)
    for m in re.finditer(r"^(\s+)(if \(.*\) \{)$", body, re.M):  # loads in a condition
        ind, stmt = m.group(1), m.group(2)
        cands = []
        for lm in NARROW_LOAD_RE.finditer(stmt):
            t = lm.group(1) or params.get(lm.group(2))
            if t:
                a = lm.start()
                cast = re.search(r"\((?:[su]64|[su]32)\) $", stmt[:a])
                a0 = cast.start() if cast else a
                cands.append((t, lm.group(0), stmt[:a0] + "{w}" + stmt[lm.end():]))
        yield from _widen(head, body, m, ind, cands, semicolon=False)


def _widen(head, body, m, ind, cands, semicolon=True):
    for t, load, new_stmt in cands:
        for w in WIDER[t[1:]]:
            decl = f"\n    {w} wide;"
            nb = (body[: m.start()] + f"{ind}wide = {load};\n{ind}" + new_stmt.replace("{w}", "wide")
                  + (";" if semicolon else "") + body[m.end():])
            yield f"widen {w}@{m.start()}", head + decl + nb


def rebase_fields(code: str) -> str:
    """`q = p + 0xA0; ... M2C_FIELD(p, T *, 0xA0)` -> `M2C_FIELD(q, T *, 0)`: one
    base for a run of stores into a sub-struct (lets store reordering work)."""
    for m in re.finditer(r"^\s+(\w+) = (\w+) \+ (0x[0-9A-Fa-f]+|\d+);$", code, re.M):
        new, base, c = m.group(1), m.group(2), int(m.group(3), 0)
        head, tail = code[: m.end()], code[m.end():]

        def fix(mm: re.Match) -> str:
            off = int(mm.group(2), 0)
            if off < c:
                return mm.group(0)
            return f"M2C_FIELD({new}, {mm.group(1)} *, 0x{off - c:X})"
        tail = re.sub(rf"M2C_FIELD\({base}, ([\w ]+?) \*, (0x[0-9A-Fa-f]+|\d+)\)", fix, tail)
        code = head + tail
    return code


def as_arrays(code: str) -> str:
    for m in re.finditer(r"^extern (volatile )?M2C_UNK (D_[0-9A-F]{8});$", code, re.M):
        name = m.group(2)
        uses = re.findall(rf"\b{name}\b", code)
        fields = re.findall(rf"M2C_FIELD\(&{name}, (\w+) \*, (0x[0-9A-Fa-f]+|\d+)\)", code)
        idx = re.findall(rf"\*\((\w+) \*\)\(\(s8 \*\)(?:\(s8 \*\))?&{name} \+ \((.+?) \* (\d+)\)\)", code)
        idx += [("M2C_UNK", e, n) for e, n in re.findall(rf"\*\(&{name} \+ \((.+?) \* (\d+)\)\)", code)]
        types = {t for t, _ in fields} | {t for t, _e, _n in idx}
        if len(types) != 1 or len(uses) != 1 + len(fields) + len(idx):
            continue
        t = types.pop()
        size = SIZES.get(t)
        if not size or any(int(o, 0) % size for _, o in fields) or any(int(n) != size for _t, _e, n in idx):
            continue
        code = code.replace(m.group(0), f"extern {m.group(1) or ''}{t} {name}[];")
        code = re.sub(rf"M2C_FIELD\(&{name}, \w+ \*, (0x[0-9A-Fa-f]+|\d+)\)",
                      lambda mm: f"{name}[{int(mm.group(1), 0) // size}]", code)
        code = re.sub(rf"\*\(&{name} \+ \((.+?) \* \d+\)\)", lambda mm: f"{name}[{mm.group(1)}]", code)
        code = re.sub(rf"\*\(\w+ \*\)\(\(s8 \*\)(?:\(s8 \*\))?&{name} \+ \((.+?) \* \d+\)\)",
                      lambda mm: f"{name}[{mm.group(1)}]", code)
    return code


SIZES = {"s8": 1, "u8": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "f32": 4, "s64": 8, "u64": 8,
         "M2C_UNK": 4, "void *": 4}


def scale_increments(code: str) -> str:
    """`u32 *p; ... p += 4;` -> `p += 1;` (m2c's increments are byte counts)."""
    for m in re.finditer(r"^\s+([su](?:8|16|32|64)|f32|M2C_UNK|void \*) \*(\w+);", code, re.M):
        size, name = SIZES[m.group(1)], m.group(2)
        if size == 1:
            continue

        def fix(mm: re.Match) -> str:
            n = int(mm.group(2), 0)
            return f"{name} {mm.group(1)}= {n // size};" if n % size == 0 else mm.group(0)
        code = re.sub(rf"\b{name} ([+-])= (0x[0-9A-Fa-f]+|\d+);", fix, code)
    return code


# --------------------------------------------------------------------------- mutations

STORE_RE = re.compile(r"^\s+M2C_FIELD\(([^,]+), [^,]+, (0x[0-9A-Fa-f]+|\d+)\) = [^;]+;$")
TYPE_RE = re.compile(r"\b([su])(8|16|32|64)\b")
UNK_RE = re.compile(r"\bM2C_UNK\b")
CAST_RE = re.compile(r"\((?:[su](?:8|16|32|64)|f32|M2C_UNK\d*|void \*|[su](?:8|16|32) \*)\) ")
STMT_RE = re.compile(r"^(\s+)(?!\s)(?!(?:if|else|do|while|for|return|switch|case|default|goto|break|continue)\b)[^\n{}]*;\s*$")
DECL_LINE_RE = re.compile(r"^(\s+)(?:const |volatile |static |register )*(?:[su](?:8|16|32|64)|f32|f64|M2C_UNK\d*|void|char|int)\b[\s*]+\w+(\[\w*\])?;(\s*/\*.*\*/)?$")


def _indent(line: str) -> int:
    return len(line) - len(line.lstrip())


def _plain_stmt(line: str) -> bool:
    return bool(STMT_RE.match(line)) and not DECL_LINE_RE.match(line)


def _body_range(lines: list[str]) -> tuple[int, int]:
    start = next((i for i, l in enumerate(lines) if re.match(r"^\S.*\)\s*\{\s*$", l)), 0)
    return start, len(lines)


# Offsets of the original function's stores, in asm order (set per function
# by autodecomp): a target order for runs of independent stores.
STORE_HINT: list[int] = []


def mutations(code: str):
    """Yield (description, new code) for single-edit permutations, the ones
    most often right first."""
    muts = list(_mutations(code))
    first = ("rebase", "earlyreturn", "forloop", "voidcallee", "narrowand", "hint", "unvolatile", "volatile")
    yield from sorted(muts, key=lambda m: next((i for i, p in enumerate(first) if m[0].startswith(p)), len(first)))


def _mutations(code: str):
    v = rebase_fields(code)
    if v != code:
        yield "rebase", v
    lines = code.split("\n")
    # volatile globals: gcc then builds the full address (lui/addiu) and
    # accesses offset 0, and keeps the access order
    for m in re.finditer(r"^extern (?!volatile)", code, re.M):
        yield f"volatile@{m.start()}", code[:m.end()] + "volatile " + code[m.end():]
    for m in re.finditer(r"^extern volatile ", code, re.M):
        yield f"unvolatile@{m.start()}", code[:m.start()] + "extern " + code[m.end():]
    b0, b1 = _body_range(lines)
    # reorder runs of 3-4 adjacent statements (gcc's scheduler reorders
    # independent stores, so the source order is rarely the asm order)
    i = b0 + 1
    while i < b1:
        j = i
        while j < b1 and _plain_stmt(lines[j]) and _indent(lines[j]) == _indent(lines[i]):
            j += 1
        # stores written in field order (the way people write initialisers)
        stores = [k for k in range(i, j) if STORE_RE.match(lines[k])]
        if len(stores) >= 2:
            def key(k):
                m = STORE_RE.match(lines[k])
                return (m.group(1), int(m.group(2), 0))
            for rev in (False, True):
                order = sorted(stores, key=key, reverse=rev)
                if order != stores:
                    new = list(lines)
                    for dst, src in zip(stores, order):
                        new[dst] = lines[src]
                    yield f"sortstores@{i}", "\n".join(new)
        # the run's stores in the order the original stores those offsets,
        # as is and rotated by one (gcc emits the last independent store first)
        groups: list[list[int]] = []  # consecutive stores through the same base
        for k in stores:
            b = STORE_RE.match(lines[k]).group(1)
            if groups and groups[-1][-1] == k - 1 and STORE_RE.match(lines[groups[-1][0]]).group(1) == b:
                groups[-1].append(k)
            else:
                groups.append([k])
        for grp in groups if STORE_HINT else []:
            if len(grp) < 2:
                continue

            def pos(k):
                o = int(STORE_RE.match(lines[k]).group(2), 0)
                return STORE_HINT.index(o) if o in STORE_HINT else len(STORE_HINT)
            order = sorted(grp, key=pos)
            for cand in (order[1:] + order[:1], order, order[-1:] + order[:-1]):
                if cand != grp:
                    new = list(lines)
                    for dst, src in zip(grp, cand):
                        new[dst] = lines[src]
                    yield f"hintstores@{grp[0]}", "\n".join(new)
        # gcc tends to emit the last of a run of independent stores first, so
        # rotating the whole run (any length) is the most likely fix
        if j - i >= 3:
            run = lines[i:j]
            for rot in (run[1:] + run[:1], run[-1:] + run[:-1], run[::-1]):
                yield f"rot@{i}", "\n".join(lines[:i] + rot + lines[j:])
        for size in (3, 4):
            for w in range(i, j - size + 1):
                for perm in itertools.permutations(range(w, w + size)):
                    if list(perm) == list(range(w, w + size)) or perm[0] == w and perm[1] == w + 1:
                        continue  # identity, or the same as a smaller window
                    new = lines[:w] + [lines[k] for k in perm] + lines[w + size:]
                    yield f"perm@{w}", "\n".join(new)
        i = max(j, i + 1)
    for i in range(b0 + 1, b1 - 1):
        a, b = lines[i], lines[i + 1]
        both_decl = DECL_LINE_RE.match(a) and DECL_LINE_RE.match(b)
        both_stmt = (STMT_RE.match(a) and STMT_RE.match(b) and not DECL_LINE_RE.match(a)
                     and not DECL_LINE_RE.match(b))
        if (both_decl or both_stmt) and len(a) - len(a.lstrip()) == len(b) - len(b.lstrip()):
            new = lines[:i] + [b, a] + lines[i + 2:]
            yield f"swap@{i}", "\n".join(new)
    # signedness toggles, one occurrence at a time
    for m in TYPE_RE.finditer(code):
        t = ("u" if m.group(1) == "s" else "s") + m.group(2)
        yield f"type {m.group(0)}->{t}@{m.start()}", code[:m.start()] + t + code[m.end():]
    for m in UNK_RE.finditer(code):
        for t in ("s8", "u8", "s16", "u16", "u32", "f32"):
            yield f"unk->{t}@{m.start()}", code[:m.start()] + t + code[m.end():]
    for m in CAST_RE.finditer(code):
        yield f"nocast@{m.start()}", code[:m.start()] + code[m.end():]
    # inline temps assigned once and used once
    for m in re.finditer(r"^\s+(temp_\w+) = ([^;\n]+);\s*$\n", code, re.M):
        name, expr = m.group(1), m.group(2)
        uses = [u for u in re.finditer(rf"\b{name}\b", code)]
        if len(uses) != 3:  # declaration, assignment, one use
            continue
        rest = code[: m.start()] + code[m.end():]
        rest = re.sub(rf"^\s+[^\n;]*\b{name};[^\n]*\n", "", rest, count=1, flags=re.M)
        rest2 = re.sub(rf"\b{name}\b", lambda _m: f"({expr})", rest, count=1)
        if rest2 != rest:
            yield f"inline {name}", rest2
    # `return a != b;` -> `if (a != b) return 1; return 0;` (gcc keeps an sltu)
    for m in re.finditer(r"^(\s+)return (\(?[^;]+ (?:==|!=|<|>|<=|>=) [^;]+?\)?);$", code, re.M):
        ind = m.group(1)
        yield (f"ifreturn@{m.start()}", code[:m.start()] + f"{ind}if ({m.group(2)}) {{\n{ind}    return 1;\n"
               f"{ind}}}\n{ind}return 0;" + code[m.end():])
    # a 64-bit field narrowed on assignment: gcc keeps the 64-bit shift
    # unless the value is cast first (func_0012a030)
    for m in re.finditer(r"M2C_FIELD\([^()]*(?:\([^()]*\)[^()]*)*, [su]64 \*, [^)]+\)", code):
        if code[m.end():].startswith(" >>"):
            continue
        for t in ("(s32) ", "(u32) "):
            yield f"narrow@{m.start()}", code[:m.start()] + t + code[m.start():]
    for m in re.finditer(r"\((M2C_FIELD\([^;]*?, [su]64 \*, [^)]+\) >> [^)]+)\)", code):
        yield f"narrowshift@{m.start()}", code[:m.start()] + "(s32) " + code[m.start():]
    # a 64-bit value shifted and masked: `(s32) (x >> n) & m` truncates before
    # the `andi` (dsll32/dsra32 first), as the original does (func_0012aa38)
    for m in re.finditer(r"\((?:\([su]64\) )?", code):
        if not re.match(r"\((?:\([su]64\) )", code[m.start():]) and "64 *" not in code[m.start():m.start() + 200]:
            continue
        e = _group_end(code, m.start())
        if e < 0 or not code[e:].startswith(" & ") or " >> " not in code[m.start():e]:
            continue
        g = code[m.start():e]
        if "64" not in g:
            continue
        for inner in dict.fromkeys((g, re.sub(r"^\(\([su]64\) ", "(", g))):
            yield f"narrowand@{m.start()}", code[:m.start()] + "(s32) " + inner + code[e:]
    v = copy_loop(code)
    if v != code:
        yield "forloop", v
    v = early_return(code)
    if v != code:
        yield "earlyreturn", v
    # an extern whose result is never used: declared void, v0 is free after
    # the call (func_00157668)
    for m in re.finditer(r"^(?:extern )?(M2C_UNK|s32|u32|void \*|\? \*) (func_[0-9a-f]{8}|\w+)\(([^)]*)\);", code, re.M):
        fn = m.group(2)
        uses = re.findall(rf"(^\s*|[^\n]*?)\b{fn}\(", code[m.end():], re.M)
        if uses and all(re.fullmatch(r"\s*", u) for u in uses):
            yield f"voidcallee {fn}", code[:m.start()] + f"void {fn}({m.group(3)});" + code[m.end():]
    # `(u32)` on a narrow load before `>>` picks srlv over srav (func_00171a88)
    for m in re.finditer(r"(?<![)\w])((?:M2C_FIELD\([^;]*?, [su](?:8|16) \*, [^)]+\))|\w+\[[^\]]+\]) >> ", code):
        for t in ("(u32) ", "(s32) "):
            yield f"shiftcast@{m.start()}", code[:m.start()] + t + code[m.start():]
    # a void function that really returns the global array it filled in
    # (`move v0, base` before the return; no caller uses it, so sigs said void)
    m = re.search(r"^void (\w+\([^)]*\)) \{", code, re.M)
    if m:
        for a in re.finditer(r"^extern (?:volatile )?(\w+) (D_[0-9A-F]{8})\[\];$", code, re.M):
            body = code[m.end():].rstrip()
            if body.endswith("}") and re.search(rf"\b{a.group(2)}\[", body):
                yield (f"retarray {a.group(2)}", code[:m.start()] + f"{a.group(1)} *{m.group(1)} {{"
                       + body[:-1] + f"    return {a.group(2)};\n}}\n")
    # a narrow value read into a wider local first: gcc then uses the
    # sign/zero-extending load of the wider type (lb for an s8 kept in an
    # int, lwu for a u32 kept in a u64, dsrl on it...)
    yield from widen_loads(code)
    # an argument the callee takes as 64-bit: the caller keeps one 64-bit
    # constant for it and a 64-bit operation (func_001dbcd8)
    for m in re.finditer(r"^(?:extern )?[\w *]+? (\w+)\(([^)]*)\);", code, re.M):
        params = [p.strip() for p in m.group(2).split(",")]
        for i, p_ in enumerate(params):
            if p_ in ("M2C_UNK", "s32", "u32"):
                np_ = params[:i] + ["s64"] + params[i + 1:]
                yield (f"wideparam {m.group(1)}#{i}",
                       code[:m.start(2)] + ", ".join(np_) + code[m.end(2):])
    # value <-> void return
    m = re.search(r"^(s32|u32|M2C_UNK) (\w+\([^)]*\)) \{", code, re.M)
    if m and not re.search(r"\breturn\b[^;]*\w", code[m.end():]):
        yield "ret->void", code[:m.start()] + f"void {m.group(2)} {{" + code[m.end():]


# --------------------------------------------------------------------------- compile-error fixes

DEREF_ERRORS = ("invalid type argument of `unary *'", "void value not ignored", "invalid use of void expression",
                "called object is not a function")


def _group_end(s: str, i: int) -> int:
    """Index just past the parenthesised group starting at s[i] == '('."""
    depth = 0
    for k in range(i, len(s)):
        if s[k] == "(":
            depth += 1
        elif s[k] == ")":
            depth -= 1
            if depth == 0:
                return k + 1
    return -1


def _top_terms(expr: str) -> list[str] | None:
    """Split `a + b + c` at top-level ' + ' (None if there is no such '+')."""
    terms, depth, last = [], 0, 0
    k = 0
    while k < len(expr):
        c = expr[k]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        elif depth == 0 and expr.startswith(" + ", k):
            terms.append(expr[last:k])
            last = k + 3
            k += 3
            continue
        k += 1
    terms.append(expr[last:])
    return terms if len(terms) > 1 else None


CAST_PREFIX_RE = re.compile(r"\((?:[\w ]+\*+|[\w ]+ \(\*+\)\([^)]*\))\)\s*")


def fix_int_derefs(line: str, int_names: set[str]) -> str:
    """m2c writes byte-offset accesses through integers as `*(a + b)`,
    `*(void *)0x2C5968`, `*var` (var an int) and calls through a table as
    `*(&D_X + i)(args)`. Make them valid C with byte arithmetic."""
    out, k = [], 0
    while k < len(line):
        c = line[k]
        prev = line[k - 1] if k else " "
        if c == "*" and k + 1 < len(line) and line[k + 1] not in " =" and prev not in "*" and not (prev.isalnum() or prev in "_)]"):
            rest = line[k + 1:]
            if rest.startswith("*"):  # **x: the inner value is an int too
                out.append("*(M2C_UNK *)" + fix_int_derefs(rest, int_names))
                break
            m = re.match(r"\(void \*\)", rest)
            if m:
                out.append("*(M2C_UNK *)")
                k += 1 + m.end()
                continue
            if rest.startswith("("):
                e = _group_end(rest, 0)
                inner = rest[1:e - 1] if e > 0 else ""
                call = e > 0 and rest[e:].startswith("(")
                if e > 0 and re.fullmatch(r"[\w ]+\*+", inner):  # already a cast
                    out.append(c)
                    k += 1
                    continue
                if e > 0 and not CAST_PREFIX_RE.match(inner):
                    terms = _top_terms(inner)
                    if terms or call:
                        addr = " + ".join(f"(s32) {t}" if re.fullmatch(r"[\w.]+|&\w+", t.strip()) else f"(s32) ({t})"
                                          for t in (terms or [inner]))
                        if call:
                            out.append(f"(*(M2C_UNK (**)())({addr}))")
                        else:
                            out.append(f"*(M2C_UNK *)({addr})")
                        k += 1 + e
                        continue
            m = re.match(r"\w+", rest)
            if m and m.group(0) in int_names:
                out.append(f"*(M2C_UNK *){m.group(0)}")
                k += 1 + m.end()
                continue
        out.append(c)
        k += 1
    else:
        return "".join(out)
    return "".join(out)


def int_typed_names(code: str) -> set[str]:
    names = set(re.findall(r"^\s+(?:volatile )?(?:[su](?:8|16|32|64)|M2C_UNK\d*) (\w+);", code, re.M))
    names |= set(re.findall(r"^extern (?:volatile )?(?:[su](?:8|16|32|64)|M2C_UNK\d*) (\w+);", code, re.M))
    head = re.search(r"^\S.*\((.*)\)\s*\{\s*$", code, re.M)
    if head:
        names |= set(re.findall(r"(?:[su](?:8|16|32|64)|M2C_UNK\d*) (\w+)(?:,|$)", head.group(1)))
    return names


def fix_compile_errors(code: str, errors: list[tuple[int, str]]) -> str:
    """Rewrite the lines gcc rejected for dereferencing a non-pointer."""
    lines = code.split("\n")
    names = int_typed_names(code)
    # calls with differing argument counts (m2c inferred a prototype from one
    # call site): declare the callee without a prototype, unless it takes floats
    for _ln, msg in errors:
        m = re.search(r"too (?:few|many) arguments to function `(\w+)'", msg)
        if m:
            fn = m.group(1)
            for i, l in enumerate(lines):
                d = re.match(rf"^((?:extern )?[\w *]+?\b{fn})\(([^)]*)\);(.*)$", l)
                if d and "f32" not in d.group(2) and "f64" not in d.group(2):
                    lines[i] = f"{d.group(1)}();{d.group(3)}"
    bad = {ln for ln, msg in errors if any(e in msg for e in DEREF_ERRORS)}
    for ln in sorted(bad):
        if 0 < ln <= len(lines):
            lines[ln - 1] = fix_int_derefs(lines[ln - 1], names)
    return "\n".join(lines)


def copy_loop(code: str) -> str:
    """m2c's `i = C; j = C; do { i += k; f(j); j = i; } while (i < N);` (a
    counter copied into the argument register) -> `for (i = C; i < N; i += k)
    { f(i); }` (func_00157668)."""
    m = re.search(r"^(\s+)(\w+) = ([^;\n]+);\n\1(\w+) = \3;\n\1do \{\n((?:\1    [^\n]*\n)+?)\1    \4 = \2;\n\1\} while \(\2 ([<>!=]=?) ([^;\n]+)\);\n",
                  code, re.M)
    if not m:
        m2 = re.search(r"^(\s+)(\w+) = ([^;\n]+);\n\1(\w+) = \3;\n", code, re.M)
        if not m2:
            return code
        return code
    ind, var, init, cp, body, op, lim = m.groups()
    inc = re.search(rf"^{ind}    {var} (\+=|-=) ([^;\n]+);\n", body, re.M)
    if not inc or re.search(rf"\b{cp}\b", body[:inc.start()]) is None and False:
        return code
    if not inc:
        return code
    rest = body[:inc.start()] + body[inc.end():]
    rest = re.sub(rf"\b{cp}\b", var, rest)
    new = (f"{ind}for ({var} = {init}; {var} {op} {lim}; {var} {inc.group(1)} {inc.group(2)}) {{\n"
           f"{rest}{ind}}}\n")
    out = code[:m.start()] + new + code[m.end():]
    out = re.sub(rf"^\s+[\w ]+\b{cp};\n", "", out, count=1, flags=re.M)
    return out


def goto_loops(code: str) -> str:
    """`loop_N:` + body + `goto loop_N;` at the label's own indent -> `for (;;)
    { body }`, other `goto loop_N;` in the body -> `continue;`. Only when the
    body has no loop of its own (a `continue` there would bind to it)."""
    lines = code.split("\n")
    i = 0
    while i < len(lines):
        m = re.fullmatch(r"(loop_\d+):", lines[i].strip())
        if not m:
            i += 1
            continue
        lab = m.group(1)
        ind = " " * _indent(lines[i]) if lines[i].startswith(" ") else "    "
        end = max((j for j in range(i + 1, len(lines)) if lines[j] == f"{ind}goto {lab};"), default=None)
        body = lines[i + 1:end] if end else None
        if (body is None or any(re.search(r"\b(do|while|for)\b\s*[({]", l) for l in body)
                or any(re.search(rf"\b{lab}\b", l) for l in lines[:i] + lines[end + 1:])):
            i += 1
            continue
        body = [("    " + l if l.strip() else l).replace(f"goto {lab};", "continue;") for l in body]
        lines[i:end + 1] = [f"{ind}for (;;) {{", *body, f"{ind}}}"]
        i += 1
    return "\n".join(lines)


def void_callees(code: str) -> str:
    """Declare void every extern function whose result the code never uses."""
    for m in reversed(list(re.finditer(r"^(?:extern )?(M2C_UNK|s32|u32|void \*|\? \*) (\w+)\(([^)]*)\);", code, re.M))):
        fn = m.group(2)
        uses = re.findall(rf"(^\s*|[^\n]*?)\b{fn}\(", code[m.end():], re.M)
        if uses and all(re.fullmatch(r"\s*", u) for u in uses):
            code = code[:m.start()] + f"void {fn}({m.group(3)});" + code[m.end():]
    return code


def negate(cond: str) -> str:
    if cond.startswith("!(") and cond.endswith(")") and _group_end(cond, 1) == len(cond):
        return cond[2:-1]
    for a, b in (("==", "!="), ("!=", "=="), (">=", "<"), ("<=", ">"), (" < ", " >= "), (" > ", " <= ")):
        if cond.count(a) == 1 and "&&" not in cond and "||" not in cond and "(" not in cond:
            return cond.replace(a, b)
    return f"!({cond})"


def early_return(code: str) -> str:
    """`if (c) { body } return r; }` at the end of a function ->
    `if (!c) { return r; } body return r; }` (func_001ece70)."""
    m = re.search(r"^    if \((.*)\) \{\n((?:        [^\n]*\n)+)    \}\n    (return[^;\n]*;)\n\}\s*$", code, re.M)
    if not m:
        return code
    body = re.sub(r"^    ", "", m.group(2), flags=re.M)
    return (code[:m.start()] + f"    if ({negate(m.group(1))}) {{\n        {m.group(3)}\n    }}\n"
            + body + f"    {m.group(3)}\n}}\n")
