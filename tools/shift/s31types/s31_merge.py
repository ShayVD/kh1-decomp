#!/usr/bin/env python3
"""Merge a file's second view of an object into its first (session 31).

  python3 -I tools/shift/s31types/s31_merge.py [--apply] FILE.c A B [B2 ..]

A and each B are struct typedefs defined in FILE.c (`typedef struct [tag] {..} X;`)
that describe the same object at the same base (two actor views of one file).
The members of every B that A lacks are put into A at their offsets (layouts
from gcc's stabs, s29_stabs; the declarations' text from the source), the
padding is recomputed, and B becomes `typedef A B;`.  Refused when two members
overlap, when a B member's name is used by A at another offset, or for anonymous
members.  The size is the largest view's.  The result is -S checked against
HEAD and its new warnings listed; --apply writes it when SAME.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s29types"))
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402
import s29_stabs as ST  # noqa: E402
from s31_tag import find_def  # noqa: E402

PAD = re.compile(r"^(pad\w*|p[0-9a-fA-F]+|_pad\w*|padx|unk_pad\w*)$")


def split_members(body):
    """top-level declarations of a struct body (text between the braces)"""
    out, d, cur = [], 0, ""
    for ch in body:
        if ch in "{(":
            d += 1
        elif ch in "})":
            d -= 1
        if ch == ";" and d == 0:
            if cur.strip():
                out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        raise ValueError("trailing text: " + cur)
    return out


def declarators(decl):
    """[(name, text of a one-member declaration)] of a declaration"""
    decl = re.sub(r"/\*.*?\*/", " ", decl, flags=re.S)
    decl = re.sub(r"//[^\n]*", " ", decl).strip()
    if "{" in decl:  # struct/union member: one declarator after the closing brace
        j = decl.rindex("}")
        tail = decl[j + 1:].strip()
        m = re.match(r"^(\**\s*)(\w+)(.*)$", tail)
        if not m:
            raise ValueError("anonymous member: " + decl[:60])
        return [(m.group(2), decl)]
    # split the declarators at top-level commas
    parts, d, cur = [], 0, ""
    for ch in decl:
        if ch in "([":
            d += 1
        elif ch in ")]":
            d -= 1
        if ch == "," and d == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    parts.append(cur)
    m = re.match(r"^((?:(?:const|volatile|unsigned|signed|struct|union|enum)\s+)*\w+)\s*(.*)$", parts[0].strip(), re.S)
    if not m:
        raise ValueError("cannot parse: " + decl[:60])
    base, first = m.group(1), m.group(2)
    out = []
    for dcl in [first] + [p.strip() for p in parts[1:]]:
        n = re.search(r"\b([A-Za-z_]\w*)\b(?=[^\w]*(?:\[|:|$|\)))", dcl)
        nm = re.findall(r"[A-Za-z_]\w*", re.sub(r"\[[^\]]*\]|:.*$", "", dcl))
        if not nm:
            raise ValueError("no name in " + dcl)
        out.append((nm[-1], f"{base} {dcl.strip()}"))
    return out


def layout(p, name):
    n = p.named[name]
    _, t = p.resolve(n)
    return {f: (bo, bs, ft) for f, ft, bo, bs in t.fields}, p.size(n)


def members(t, ty, lay):
    """[(byte start, byte end, name, text, is_bits)] of ty's non-pad members"""
    s, e, tag, k = find_def(t, ty)
    body = t[k + 1:t.rindex("}", s, e)]
    out = []
    for decl in split_members(body):
        for nm, txt in declarators(decl):
            if nm not in lay:
                raise ValueError(f"{ty}.{nm}: not in stabs")
            bo, bs, ft = lay[nm]
            bits = ":" in re.sub(r"\[[^\]]*\]", "", txt.split("}")[-1])
            if PAD.match(nm) and re.match(r"^(u8|s8|char)\b", txt) and not bits:
                continue
            out.append([bo, bs, nm, txt, bits])
    return out


def units(ms, p_size_of_bits):
    """group runs of bit-fields: [(start, end, [members])]"""
    out = []
    i = 0
    while i < len(ms):
        bo, bs, nm, txt, bits = ms[i]
        if not bits:
            out.append((bo // 8, (bo + bs) // 8, [ms[i]]))
            i += 1
            continue
        j = i
        while j + 1 < len(ms) and ms[j + 1][4]:
            j += 1
        w = p_size_of_bits(ms[i][3])
        start = (ms[i][0] // (8 * w)) * w
        end = -(-(ms[j][0] + ms[j][1]) // (8 * w)) * w
        out.append((start, end, ms[i:j + 1]))
        i = j + 1
    return out


def word_of(txt):
    m = re.match(r"^\s*(?:unsigned\s+|signed\s+)?(\w+)", txt)
    return {"u64": 8, "s64": 8, "u16": 2, "s16": 2, "u8": 1, "s8": 1}.get(m.group(1), 4)


def merge(t, rel, a, bs):
    p = ST.parse(rel, t)
    la, sa = layout(p, a)
    ua = units(members(t, a, la), word_of)
    size = sa
    names = {m[2]: u[0] for u in ua for m in u[2]}
    allu = list(ua)
    for b in bs:
        lb, sb = layout(p, b)
        size = max(size, sb)
        for u in units(members(t, b, lb), word_of):
            if any(u[0] == x[0] and u[1] == x[1] and [m[2] for m in u[2]] == [m[2] for m in x[2]] for x in allu):
                continue
            for x in allu:
                if u[0] < x[1] and x[0] < u[1]:
                    raise ValueError(f"{b}.{u[2][0][2]} at {u[0]:#x} overlaps {x[2][0][2]} at {x[0]:#x}")
            for m in u[2]:
                if m[2] in names and names[m[2]] != u[0]:
                    raise ValueError(f"{b}.{m[2]}: name used at another offset")
                names[m[2]] = u[0]
            allu.append(u)
    allu.sort(key=lambda u: u[0])
    lines, off = [], 0
    for st, en, ms in allu:
        if st > off:
            lines.append(f"    u8 pad{off:x}[0x{st - off:x}];")
        for m in ms:
            lines.append(f"    {m[3]};")
        off = en
    if size > off:
        lines.append(f"    u8 pad{off:x}[0x{size - off:x}];")
    s, e, tag, k = find_def(t, a)
    head = t[s:k]
    t = t[:s] + head + "{\n" + "\n".join(lines) + "\n} " + a + ";" + t[e:]
    t = hoist(t, a, "\n".join(lines))
    for b in bs:
        s, e, tag, k = find_def(t, b)
        t = t[:s] + f"typedef {a} {b};" + t[e:]
    return t


def typedef_stmt(t, x):
    """(start, end) of the typedef statement that defines x in t, or None"""
    d = find_def(t, x)
    if d:
        return d[0], d[1]
    m = re.search(r"^typedef[^;{}]*\b" + x + r"\s*(?:\[[^\]]*\])*\s*;[^\n]*\n?", t, re.M)
    return (m.start(), m.end()) if m else None


def hoist(t, a, text, depth=0):
    """move the typedefs that `text` (members of a) names and that come after a's
    definition to just before it"""
    for x in sorted(set(re.findall(r"\b[A-Za-z_]\w*\b", text))):
        if x == a:
            continue
        sa = find_def(t, a)[0]
        r = typedef_stmt(t, x)
        if r is None or r[0] < sa:
            continue
        stmt = t[r[0]:r[1]]
        if not stmt.endswith("\n"):
            stmt += "\n"
        t = t[:r[0]] + t[r[1]:]
        t = t[:sa] + stmt + t[sa:]
        if depth < 5:
            t = hoist(t, a, stmt, depth + 1)
    return t


def main(argv):
    apply = "--apply" in argv
    argv = [x for x in argv if x != "--apply"]
    rel, a, bs = argv[0], argv[1], argv[2:]
    src = (L.ROOT / rel).read_text()
    try:
        t = merge(src, rel, a, bs)
    except ValueError as ex:
        print("REFUSED", ex)
        return 1
    asm, da = L.compile_s(rel, t)
    h, dh = L.head_compile(rel)
    if asm is None:
        print("NOCOMPILE", [x for x in da if "warning" not in x[1]][:5])
        return 1
    old = L.warnings(dh)
    for ln, m in da:
        if "warning" in m and m not in old:
            print(f"  new: {ln}: {m}")
    same = L.same_asm(asm, h)
    print("SAME" if same else "CODE")
    if same and apply:
        (L.ROOT / rel).write_text(t)
        print("applied")
    return 0 if same else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
