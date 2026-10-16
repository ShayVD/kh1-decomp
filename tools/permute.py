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
        for n in range(6, 13):
            s = f"{w:.{n}g}"
            if "e" not in s and "." not in s:
                s += ".0"
            out.append(s)
    # midpoints towards the neighbours (truncating converters)
    for b in (bits - 1, bits + 1):
        w = struct.unpack("<f", struct.pack("<I", b & 0xFFFFFFFF))[0]
        for n in range(7, 12):
            s = f"{(v + w) / 2:.{n}g}"
            out.append(s if ("." in s or "e" in s) else s + ".0")
    return list(dict.fromkeys(out))


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


def preprocess(code: str, sigs: dict[str, str], cc: str) -> str:
    return fix_floats(fill_params(add_prototypes(code, sigs)), cc)


# --------------------------------------------------------------------------- variants

def variants(code: str) -> list[str]:
    """Whole-draft alternatives worth trying before the search."""
    out = []
    # m2c means byte offsets for arithmetic on unknown-typed pointers.
    v = re.sub(r"\*\(&(D_[0-9A-F]{8}) \+ ", r"*(M2C_UNK *)((s8 *)&\1 + ", code)
    v = re.sub(r"\bM2C_UNK \*(\w+);", r"s8 *\1;", v)
    if v != code:
        out.append(v)
    # m2c counts pointer increments in bytes even on typed pointers
    v = scale_increments(code)
    if v != code:
        out.append(v)
    return out


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

TYPE_RE = re.compile(r"\b([su])(8|16|32|64)\b")
UNK_RE = re.compile(r"\bM2C_UNK\b")
CAST_RE = re.compile(r"\((?:[su](?:8|16|32|64)|f32|M2C_UNK\d*|void \*|[su](?:8|16|32) \*)\) ")
STMT_RE = re.compile(r"^(\s+)(?!(?:if|else|do|while|for|return|switch|case|default|goto|break|continue)\b)[^\n{}]*;\s*$")
DECL_LINE_RE = re.compile(r"^(\s+)(?:const |volatile |static |register )*(?:[su](?:8|16|32|64)|f32|f64|M2C_UNK\d*|void|char|int)\b[\s*]+\w+(\[\w*\])?;(\s*/\*.*\*/)?$")


def _indent(line: str) -> int:
    return len(line) - len(line.lstrip())


def _plain_stmt(line: str) -> bool:
    return bool(STMT_RE.match(line)) and not DECL_LINE_RE.match(line)


def _body_range(lines: list[str]) -> tuple[int, int]:
    start = next((i for i, l in enumerate(lines) if re.match(r"^\S.*\)\s*\{\s*$", l)), 0)
    return start, len(lines)


def mutations(code: str):
    """Yield (description, new code) for single-edit permutations."""
    lines = code.split("\n")
    # volatile globals: gcc then builds the full address (lui/addiu) and
    # accesses offset 0, and keeps the access order
    for m in re.finditer(r"^extern (?!volatile)", code, re.M):
        yield f"volatile@{m.start()}", code[:m.end()] + "volatile " + code[m.end():]
    b0, b1 = _body_range(lines)
    # reorder runs of 3-4 adjacent statements (gcc's scheduler reorders
    # independent stores, so the source order is rarely the asm order)
    i = b0 + 1
    while i < b1:
        j = i
        while j < b1 and _plain_stmt(lines[j]) and _indent(lines[j]) == _indent(lines[i]):
            j += 1
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
    # value <-> void return
    m = re.search(r"^(s32|u32|M2C_UNK) (\w+\([^)]*\)) \{", code, re.M)
    if m and not re.search(r"\breturn\b[^;]*\w", code[m.end():]):
        yield "ret->void", code[:m.start()] + f"void {m.group(2)} {{" + code[m.end():]
