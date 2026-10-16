"""gcc 2.9x (pre-Itanium) C++ name mangling for functions.tsv signatures.

Covers what the registry needs day to day: free functions, methods (static or
not), const methods, nested classes/namespaces, constructors, destructors,
pointers, references, const, unsigned, and gcc2's T/N back-references.
Anything else (operators, templates, function-pointer parameters) should be
written in functions.tsv already mangled; `ee-nm` on a test object shows the
exact spelling. Checked against ee-gcc 2.96-ee-001003-1 output in
tools/test_mangle_gcc2.py.
"""
from __future__ import annotations

import re

BUILTINS = {
    "void": "v", "bool": "b", "char": "c", "signed char": "Sc", "unsigned char": "Uc",
    "short": "s", "unsigned short": "Us", "int": "i", "unsigned int": "Ui", "unsigned": "Ui",
    "long": "l", "unsigned long": "Ul", "long long": "x", "unsigned long long": "Ux",
    "float": "f", "double": "d", "long double": "r", "...": "e",
    "u8": "Uc", "s8": "Sc", "u16": "Us", "s16": "s", "u32": "Ui", "s32": "i",
    "u64": "Ul", "s64": "l", "f32": "f",
}
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def _num(n: int) -> str:
    return str(n) if n < 10 else f"{n}_"


def _qualified(parts: list[str]) -> str:
    for p in parts:
        if not IDENT.match(p):
            raise ValueError(f"bad identifier: {p!r}")
    if len(parts) == 1:
        return f"{len(parts[0])}{parts[0]}"
    return f"Q{_num(len(parts))}" + "".join(f"{len(p)}{p}" for p in parts)


def mangle_type(text: str) -> str:
    t = " ".join(text.replace("*", " * ").replace("&", " & ").split())
    suffix = ""
    while t.endswith(("*", "&")) or t.endswith(" const"):
        if t.endswith(" const"):
            suffix = "C" + suffix
            t = t[:-6].strip()
        else:
            suffix = ("P" if t[-1] == "*" else "R") + suffix
            t = t[:-1].strip()
    if t.startswith("const "):
        suffix += "C"
        t = t[6:].strip()
    if t.startswith(("struct ", "class ", "union ", "enum ")):
        t = t.split(" ", 1)[1]
    base = BUILTINS.get(t)
    if base is None:
        base = _qualified([p.strip() for p in t.split("::")])
    return suffix + base


def _is_builtin(code: str) -> bool:
    return code in BUILTINS.values()


def _split_args(text: str) -> list[str]:
    text = text.strip()
    if not text or text == "void":
        return []
    return [a.strip() for a in text.split(",")]


def _strip_param_name(arg: str) -> str:
    # "const VEC& pos" -> "const VEC&"; keep bare types untouched.
    m = re.match(r"^(.*?[\s\*&])([A-Za-z_][A-Za-z0-9_]*)$", arg)
    if m and m.group(1).strip() not in ("", "const", "unsigned", "signed", "struct", "class"):
        candidate = m.group(1).strip()
        if candidate not in ("unsigned", "signed", "long", "short"):
            return candidate
    return arg


def mangle(signature: str) -> str:
    """'NS::CLASS::Method(int, VEC*) const' -> 'Method__CQ22NS5CLASSiP3VEC'."""
    s = " ".join(signature.split())
    m = re.match(r"^(.*?)\((.*)\)\s*(const)?$", s)
    if not m:
        raise ValueError(f"not a C++ signature: {signature!r}")
    qual, args_text, is_const = m.group(1).strip(), m.group(2), bool(m.group(3))
    parts = [p.strip() for p in qual.split("::")]
    name, owner = parts[-1], parts[:-1]

    types: list[str] = []
    if owner:
        cls = _qualified(owner)
        types.append(cls)
        if name == owner[-1]:
            prefix = "__"
        elif name == "~" + owner[-1]:
            prefix = "_$_"
        else:
            if not IDENT.match(name):
                raise ValueError(f"operators must be mangled by hand: {signature!r}")
            prefix = f"{name}__"
        head = prefix + ("C" if is_const else "") + cls
    else:
        if not IDENT.match(name):
            raise ValueError(f"bad function name: {name!r}")
        head = f"{name}__F"

    codes = [mangle_type(_strip_param_name(a)) for a in _split_args(args_text)]
    if not owner and not codes:
        codes = ["v"]

    out: list[str] = []
    i = 0
    while i < len(codes):
        code = codes[i]
        if not _is_builtin(code) and code in types:
            ref = types.index(code)
            run = 1
            while i + run < len(codes) and codes[i + run] == code:
                run += 1
            out.append(f"T{_num(ref)}" if run == 1 else f"N{_num(run)}{_num(ref)}")
            types.extend([code] * run)
            i += run
            continue
        out.append(code)
        types.append(code)
        i += 1
    return head + "".join(out)


def resolve(name: str) -> str:
    """functions.tsv entries are plain symbols or C++ signatures (contain '(')."""
    return mangle(name) if "(" in name else name
