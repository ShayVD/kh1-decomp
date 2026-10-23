#!/usr/bin/env python3
"""Give a file's own struct type a shared struct tag, and drop the casts that then go (session 31).

  python3 -I tools/shift/s31types/s31_tag.py [--apply] FILE.c TAG TYPE[,TYPE2..] [--uncast D_X ..]

A piece declared through an incomplete tag (`struct TAG *D_X[3]`) is completed in
each user file by that file's own view: the first TYPE's definition
`typedef struct [OLD] { .. } TYPE;` gets the tag TAG (an old tag OLD is renamed
in the whole file); each further TYPE (a second view of the same object in the
file) becomes `typedef struct TAG TYPE2;` only when its definition is a copy of
the first's body, else it is left alone and reported.  A TYPE that is
`typedef X TYPE;` is followed to X.  `--uncast D_X` drops the casts of D_X's
elements to a tagged type: `((TYPE *)D_X[k])`, `(TYPE *)D_X[k]`,
`(*(TYPE **)&D_X)` (element 0, as `D_X[0]`).
The result is -S checked against HEAD (s27lib) and its new warnings listed;
--apply writes it when SAME.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402


def find_def(t, ty):
    """(start, end, tag, body_start) of `typedef struct [tag] {..} ty;` in t, or None"""
    for m in re.finditer(r"\}\s*(?:__attribute__\s*\(\(.*?\)\)\s*)?" + ty + r"\s*;", t):
        d, k = 0, m.start()
        while k >= 0:
            if t[k] == "}":
                d += 1
            elif t[k] == "{":
                d -= 1
                if d == 0:
                    break
            k -= 1
        h = re.search(r"typedef\s+(?:struct|union)(\s+\w+)?\s*$", t[:k])
        if h:
            tag = h.group(1).strip() if h.group(1) else None
            return h.start(), m.end(), tag, k
    return None


def alias_of(t, ty):
    m = re.search(r"^typedef\s+(\w+)\s+" + ty + r"\s*;", t, re.M)
    return m.group(1) if m else None


def tag_type(t, ty, tag):
    seen = set()
    while find_def(t, ty) is None:
        a = alias_of(t, ty)
        if a is None or a in seen:
            raise SystemExit(f"{ty}: no local struct definition")
        seen.add(a)
        ty = a
    s, e, old, k = find_def(t, ty)
    head = t[s:k]
    if old == tag:
        return t, ty
    new_head = re.sub(r"typedef\s+struct(\s+\w+)?\s*$", f"typedef struct {tag} ", head)
    t = t[:s] + new_head + t[k:]
    if old:
        t = re.sub(r"\bstruct\s+" + old + r"\b", "struct " + tag, t)
    return t, ty


def uncast(t, ty, D):
    n = 0
    for pat, rep in [(r"\(\s*\(\s*" + ty + r"\s*\*\s*\)\s*" + D + r"\s*\[([^\]]+)\]\s*\)", D + r"[\1]"),
                     (r"\(\s*" + ty + r"\s*\*\s*\)\s*" + D + r"\s*\[", D + "["),
                     (r"\(\s*\*\s*\(\s*" + ty + r"\s*\*\s*\*\s*\)\s*&\s*" + D + r"\s*\)", D + "[0]")]:
        t, k = re.subn(pat, rep, t)
        n += k
    return t, n


def main(argv):
    apply = "--apply" in argv
    argv = [a for a in argv if a != "--apply"]
    unc = []
    if "--uncast" in argv:
        i = argv.index("--uncast")
        unc = argv[i + 1:]
        argv = argv[:i]
    rel, tag, types = argv[0], argv[1], argv[2].split(",")
    src = (L.ROOT / rel).read_text()
    t, base = tag_type(src, types[0], tag)
    body0 = find_def(t, base)
    for ty in types[1:]:
        d = find_def(t, ty)
        if d is None:
            print(f"{ty}: no local definition, left")
            continue
        b0 = re.sub(r"\s+", " ", t[body0[3]:body0[1]]).rsplit("}", 1)[0]
        b1 = re.sub(r"\s+", " ", t[d[3]:d[1]]).rsplit("}", 1)[0]
        if b0 != b1:
            print(f"{ty}: body differs from {base}, left")
            continue
        t = t[:d[0]] + f"typedef struct {tag} {ty};" + t[d[1]:]
        body0 = find_def(t, base)
    n = 0
    for D in unc:
        for ty in types:
            t, k = uncast(t, ty, D)
            n += k
    a, da = L.compile_s(rel, t)
    h, dh = L.head_compile(rel)
    if a is None:
        print("NOCOMPILE", [x for x in da if "warning" not in x[1]][:5])
        return 1
    old = L.warnings(dh)
    for ln, m in da:
        if "warning" in m and m not in old:
            print(f"  new: {ln}: {m}")
    same = L.same_asm(a, h)
    print(("SAME" if same else "CODE") + f" ({n} casts dropped)")
    if same and apply:
        (L.ROOT / rel).write_text(t)
        print("applied")
    return 0 if same else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
