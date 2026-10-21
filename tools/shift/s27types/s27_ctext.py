"""C text helpers for the session 27 fold (struct definitions, members, layouts by probe)."""
import re
from pathlib import Path

BASIC_NORM = {
    "int": "s32", "signed int": "s32", "signed": "s32", "M2C_UNK": "s32", "long": "s32", "long int": "s32",
    "signed long": "s32", "unsigned": "u32", "unsigned int": "u32", "unsigned long": "u32",
    "short": "s16", "short int": "s16", "signed short": "s16", "unsigned short": "u16",
    "unsigned short int": "u16", "unsigned char": "u8", "signed char": "s8", "float": "f32",
    "double": "f64", "long long": "s64", "unsigned long long": "u64",
}
BASIC = {"s8", "u8", "char", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "f64", "u128", "s128",
         "void", "vs8", "vu8", "vs16", "vu16", "vs32", "vu32"}
KW = {"const", "volatile", "unsigned", "signed", "struct", "union", "enum", "short", "long", "int", "char",
      "float", "double"}


def strip_comments(t):
    t = re.sub(r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), t, flags=re.S)
    return re.sub(r"//[^\n]*", lambda m: " " * len(m.group(0)), t)


def match_brace(t, i, o="{", c="}"):
    """t[i] == o: index after the matching c"""
    d = 0
    for k in range(i, len(t)):
        if t[k] == o:
            d += 1
        elif t[k] == c:
            d -= 1
            if d == 0:
                return k + 1
    raise ValueError("unbalanced")


def split_top(s, sep):
    out, d, cur = [], 0, ""
    for ch in s:
        if ch in "([{":
            d += 1
        elif ch in ")]}":
            d -= 1
        if ch == sep and d == 0:
            out.append(cur); cur = ""
        else:
            cur += ch
    out.append(cur)
    return out


class Def:
    """a struct/union typedef in a text: span of the whole definition and of its body"""
    def __init__(self, name, kind, start, end, b0, b1, others, tagdef=None):
        self.name, self.kind, self.start, self.end, self.b0, self.b1 = name, kind, start, end, b0, b1
        self.others = others  # other declarators of the same typedef (e.g. *PFoo)
        self.tagdef = tagdef  # (start, end) of a separate `typedef struct TAG name;` line


def find_def(text, name, ct=None):
    """the struct/union definition of typedef `name` in text (comments blanked in ct), or None"""
    ct = ct if ct is not None else strip_comments(text)
    for m in re.finditer(r"\btypedef\s+(struct|union)\s*(\w+)?\s*\{", ct):
        e = match_brace(ct, m.end() - 1)
        m2 = re.match(r"\s*([^;{}]*);", ct[e:])
        if not m2:
            continue
        decls = [d.strip() for d in m2.group(1).split(",")]
        if name in decls:
            return Def(name, m.group(1), m.start(), e + m2.end(), m.end(), e - 1,
                       [d for d in decls if d != name])
    m = re.search(r"\btypedef\s+(struct|union)\s+(\w+)\s+" + name + r"\s*;", ct)
    if m:
        tag = m.group(2)
        for m3 in re.finditer(r"(?<!typedef )\b" + m.group(1) + r"\s+" + tag + r"\s*\{", ct):
            e = match_brace(ct, m3.end() - 1)
            m4 = re.match(r"\s*;", ct[e:])
            if m4:
                return Def(name, m.group(1), m3.start(), e + m4.end(), m3.end(), e - 1, [],
                           tagdef=(m.start(), m.end()))
    return None


def simple_typedef(ct, name):
    """`typedef X name;` (no struct body): X, else None"""
    m = re.search(r"\btypedef\s+([\w\s]+?)\s+" + name + r"\s*;", ct)
    return re.sub(r"\s+", " ", m.group(1)).strip() if m else None


class Mem:
    def __init__(self, name, base, stars, dims, bits, fnptr, inline, tmpl):
        self.name, self.base, self.stars, self.dims = name, base, stars, dims
        self.bits, self.fnptr, self.inline, self.tmpl = bits, fnptr, inline, tmpl
        # inline: (kind, body text) of an anonymous struct/union member


def parse_members(body):
    out = []
    for decl in split_top(body, ";"):
        decl = decl.strip()
        if not decl:
            continue
        m = re.match(r"^(struct|union)\s*(\w+)?\s*\{", decl)
        inline = None
        if m:
            e = match_brace(decl, m.end() - 1)
            inline = (m.group(1), decl[m.end():e - 1])
            ts, rest_all = None, decl[e:]
            items = split_top(rest_all, ",")
        else:
            items = split_top(decl, ",")
            first = items[0].strip()
            mm = re.match(r"^((?:[A-Za-z_]\w*\s*)+)(.*)$", first, re.S)
            if not mm:
                raise ValueError("member: " + decl)
            run, rest = mm.group(1).split(), mm.group(2).strip()
            if not rest or rest[0] in ":[":
                ts, items[0] = " ".join(run[:-1]), run[-1] + rest
            else:
                ts, items[0] = " ".join(run), rest
        for it in items:
            it = it.strip()
            if not it:
                continue
            bits = None
            bm = re.match(r"^(.*?)\s*:\s*(\w+)$", it, re.S)
            if bm:
                it, bits = bm.group(1).strip(), int(bm.group(2), 0)
                if not it:
                    out.append(Mem(None, ts, 0, [], bits, False, None, None))  # unnamed padding
                    continue
            fm = re.match(r"^\(\s*(\**)\s*(\w+)\s*\)\s*\((.*)\)$", it, re.S)
            if fm:
                out.append(Mem(fm.group(2), ts, 0, [], None, True, None,
                               f"{ts} ({fm.group(1)}{{}})({fm.group(3)})"))
                continue
            dm = re.match(r"^(\**)\s*(\w+)\s*((?:\[[^\]]*\]\s*)*)$", it, re.S)
            if not dm:
                raise ValueError("declarator: " + it)
            dims = re.findall(r"\[([^\]]*)\]", dm.group(3))
            stars = len(dm.group(1))
            out.append(Mem(dm.group(2), ts, stars, dims, bits, False, inline,
                           None if inline else f"{ts} {dm.group(1)}{{}}" + "".join(f"[{d}]" for d in dims)))
    return out


def norm_base(ts):
    t = re.sub(r"\s+", " ", ts.replace("struct ", "").replace("union ", "")).strip()
    vol = ""
    if "volatile" in t.split():
        vol = "volatile "
    t = " ".join(w for w in t.split() if w not in ("volatile", "const"))
    return vol + BASIC_NORM.get(t, t)


def plain(ts):
    """the type name without qualifiers"""
    return " ".join(w for w in ts.split() if w not in ("volatile", "const", "struct", "union"))
