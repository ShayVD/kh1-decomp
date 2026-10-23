#!/usr/bin/env python3
"""Which fields of a struct type a file reads, and on which lines (session 29).

  python3 -I tools/shift/s29types/s29_used.py FILE.c TYPE [ALIAS ...]

Copies TYPE's definition (from FILE.c or a header it includes) with every member
renamed (`name__u`), points the file's uses of TYPE (and of the ALIAS typedef names
given) at the copy, compiles, and reads gcc's "has no member named" errors: each is
an access through TYPE.  Prints `line field` pairs and the set of fields.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402
import s27_ctext as C  # noqa: E402

TYPEWORDS = C.BASIC | C.KW | {"s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "f64"}


def includes(text, seen=None):
    """texts of the headers under include/ that text includes (recursively, in order)"""
    seen = seen if seen is not None else set()
    out = []
    for m in re.finditer(r'#include\s+"([^"]+)"', text):
        p = L.ROOT / "include" / m.group(1)
        if not p.exists():
            p = L.ROOT / "src" / m.group(1)
        if not p.exists() or p in seen:
            continue
        seen.add(p)
        t = p.read_text(errors="replace")
        out += includes(t, seen)
        out.append((p, t))
    return out


ATTR = r"__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)"


def blank_attrs(t):
    """__attribute__((...)) blanked to spaces (same length)"""
    return re.sub(ATTR, lambda m: " " * len(m.group(0)), t)


def find_type(text, name):
    """(Def, text it is in, path or None) for typedef name, following `typedef X name;` aliases"""
    srcs = [(None, text)] + list(reversed(includes(text)))
    for _ in range(10):
        for p, t in srcs:
            d = C.find_def(t, name, blank_attrs(C.strip_comments(t)))
            if d is not None:
                return d, t, p, name
        nxt = None
        for p, t in srcs:
            st = C.simple_typedef(C.strip_comments(t), name)
            if st and re.fullmatch(r"\w+", st):
                nxt = st
                break
        if not nxt:
            return None
        name = nxt
    return None


def rename_members(body, suffix="__u"):
    """body with each member declarator name suffixed (inline sub-structs too)"""
    def rep(m):
        w = m.group(1)
        if w in TYPEWORDS:
            return m.group(0)
        return w + suffix + m.group(2)
    return re.sub(r"\b([A-Za-z_]\w*)(\s*(?:\[[^\]]*\]\s*)*(?::\s*\w+\s*)?[;,])", rep, body)


def used(rel, names, text=None):
    """[(line, field)] of accesses through the type names[0] (and aliases names[1:])"""
    text = text if text is not None else (L.ROOT / rel).read_text()
    r = find_type(text, names[0])
    if r is None:
        raise ValueError(f"{names[0]}: no struct definition found")
    d, dtext, dpath, base = r
    body = dtext[d.b0:d.b1]
    attr = " ".join(re.findall(ATTR, dtext[d.b1:d.end]))
    new = f"typedef {d.kind} {{{rename_members(body)}}} {attr} {names[0]}__u;".replace("\n", " ")
    allnames = sorted(set(names) | {base}, key=len, reverse=True)
    pat = re.compile(r"\b(" + "|".join(map(re.escape, allnames)) + r")\b")
    if dpath is None:  # local definition: replace it in place
        t2 = text[:d.start] + new + pat.sub(names[0] + "__u", text[d.end:])
        t2 = pat.sub(names[0] + "__u", t2[:d.start]) + t2[d.start:]
    else:
        lines = text.split("\n")
        # the first top-level line mentioning a name, that is not an #include
        idx = next((i for i, ln in enumerate(lines) if ln[:1] not in (" ", "\t", "#", "")
                    and pat.search(ln)), None)
        if idx is None:
            idx = next(i for i, ln in enumerate(lines) if pat.search(ln))
        body_t = pat.sub(names[0] + "__u", "\n".join(lines[idx:]))
        t2 = "\n".join(lines[:idx]) + "\n" + new + " " + body_t
    asm, diags = L.compile_s(rel, t2)
    out = []
    for ln, msg in diags:
        m = re.search(r"has no member named [`'](\w+)'", msg)
        if m:
            out.append((ln, m.group(1)))
    # line numbers: a local def collapsed to one line moves later lines up by its newlines
    if dpath is None:
        nl = text[d.start:d.end].count("\n")
        defline = text.count("\n", 0, d.start) + 1
        out = [(ln + nl if ln > defline else ln, f) for ln, f in out]
    return out, [m for _, m in diags if "no member" not in m and "error" in m.lower()][:5]


def main(argv):
    rel, names = argv[0], argv[1:]
    acc, errs = used(rel, names)
    for ln, f in acc:
        print(ln, f)
    print("fields:", " ".join(sorted(set(f for _, f in acc))))
    for e in errs:
        print("other error:", e)


if __name__ == "__main__":
    main(sys.argv[1:])
