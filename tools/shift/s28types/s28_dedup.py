#!/usr/bin/env python3
"""Views that are copies of a piece header's own type (session 28).

  python3 -I tools/shift/s28types/s28_dedup.py [--apply] [D_X ...]

A user that casts a data piece to its own struct type V (a "view cast") whose
definition is the same text as a type H of the piece's header (field names, types
and attributes; the header's `_<addr>` suffixes ignored, the types V refers to
matched the same way) gets `typedef H V;` in place of its definition (the piece
header moves up to it) and its casts name H, or, for a union piece with a member
of type H, the member (`(*(V *)&D_X).f` -> `D_X.m.f`) when that keeps the code.
Each file is -S checked against HEAD (s27lib); a file that changes is left alone.
Without --apply nothing is written.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402
import s27_ctext as C  # noqa: E402
import s27_survey as S  # noqa: E402

ROOT = L.ROOT


def norm(s):
    s = C.strip_comments(s)
    s = re.sub(r"\s+", " ", s).strip()
    s = re.sub(r"\s*([{}\[\]();,*:])\s*", r"\1", s)
    return s


def header_types(N):
    """{name: (kind, normalized def with the name blanked, the names it refers to)} of the
    piece header (and D_X_s.h), and the union members {type: member}"""
    h = ROOT / f"include/data/pieces/{N}.h"
    t = h.read_text()
    s = h.with_name(N + "_s.h")
    if s.exists():
        t += "\n" + s.read_text()
    addr = N[2:].upper().lstrip("0")
    ct = C.strip_comments(t)
    out = {}
    for m in re.finditer(r"\}\s*(?:__attribute__\s*\(\(.*?\)\)\s*)?(\w+)\s*;", ct):
        nm = m.group(1)
        d = C.find_def(t, nm, ct)
        if d is None:
            continue
        out[nm] = (d.kind, ct[d.start:d.end])
    for m in re.finditer(r"\bstruct (\w+) \{", ct):  # split-header `struct S {...};`
        nm = m.group(1)
        if nm not in out:
            e = C.match_brace(ct, ct.index("{", m.start()))
            out[nm] = ("struct", ct[m.start():e + 1])
    members = {}
    um = re.search(r"typedef union \{([^{}]*)\}\s*(\w+)\s*;\s*(?:\n\s*)*extern\s+\2\s+" + N + r"\b", ct)
    if um:
        for mm in re.finditer(r"(\w+)\s+(\w+)\s*;", um.group(1)):
            members.setdefault(mm.group(1), mm.group(2))
    return out, members, addr


def canon(text, names, sfx):
    """normalized definition text with the given type names mapped to placeholders"""
    s = norm(text)
    for i, n in enumerate(sorted(names, key=len, reverse=True)):
        s = re.sub(r"\b" + re.escape(n) + r"\b", f"@T{n}@" if sfx is None else f"@T{n}@", s)
    return s


def strip_sfx(name, addr):
    return re.sub(r"_" + addr + r"(_\d+)?$", "", name, flags=re.I)


def match_file(N, rel, text, views):
    """{local name: header name} for the views (and the local types they use) that are
    copies of header types, or {} """
    htypes, members, addr = header_types(N)
    # header names without their suffix
    hbase = {}
    for hn in htypes:
        hbase.setdefault(strip_sfx(hn, addr), []).append(hn)
    ct = C.strip_comments(text)
    pairs = {}

    def try_pair(v, h, seen):
        if (v, h) in seen:
            return True
        seen.add((v, h))
        d = C.find_def(text, v, ct)
        if d is None or d.others or d.tagdef:
            return False
        vt = ct[d.start:d.end]
        hk, ht = htypes[h]
        if hk != d.kind:
            return False
        # names used inside each definition
        vnames = set(re.findall(r"\b[A-Za-z_]\w*\b", ct[d.b0:d.b1]))
        hnames = set(re.findall(r"\b[A-Za-z_]\w*\b", ht))
        sub = {}
        for n in vnames:
            if n == v or C.find_def(text, n, ct) is None:
                continue
            cands = [x for x in hbase.get(n, []) if x in hnames]
            if not cands:
                return False
            if not try_pair(n, cands[0], seen):
                return False
            sub[n] = cands[0]
        a = norm(vt)
        b = norm(ht)
        # map: local names -> header names, the view name -> header name; struct tags too
        for n, hn in list(sub.items()) + [(v, h)]:
            a = re.sub(r"\b" + re.escape(n) + r"\b", hn, a)
        if a != b:
            # tags: `typedef struct Elem {...} Elem;` vs `typedef struct Elem_X {...} Elem_X;`
            return False
        pairs[v] = h
        pairs.update(sub)
        return True

    for v in views:
        cands = hbase.get(v, []) + [h for h in htypes if h not in hbase.get(v, [])]
        for h in cands:
            seen = set()
            saved = dict(pairs)
            if try_pair(v, h, seen):
                break
            pairs.clear(); pairs.update(saved)
    return pairs, members


def rewrite(N, rel, text, pairs, members, use_member):
    ct = C.strip_comments(text)
    inc = f'#include "data/pieces/{N}.h"'
    sinc = f'#include "data/pieces/{N}_s.h"'
    myinc = sinc if sinc in text else inc
    defs = sorted(((C.find_def(text, v, ct), v) for v in pairs), key=lambda x: -x[0].start)
    first = min(d.start for d, _ in defs)
    for d, v in defs:
        new = f"typedef {pairs[v]} {v};"
        text = text[:d.start] + ("\x01" if d.start == first else "") + new + text[d.end:]
    # struct tags of the old definitions (`struct Elem *`) -> the header's tags
    for v, h in pairs.items():
        text = re.sub(r"\bstruct " + v + r"\b", f"struct {h}", text)
    # the piece header goes up to the first alias
    pos = text.find(myinc)
    if pos < 0 or pos > text.index("\x01"):
        if pos >= 0:
            e = text.find("\n", pos)
            text = text[:pos] + text[e + 1:]
        text = text.replace("\x01", myinc + "\n")
    else:
        text = text.replace("\x01", "")
    for v, h in pairs.items():
        if use_member and h in members:
            text = re.sub(r"\(\s*\*\s*\(\s*" + v + r"\s*\*\s*\)\s*&\s*" + N + r"\s*\)", f"{N}.{members[h]}", text)
            text = re.sub(r"\(\s*" + v + r"\s*\*\s*\)\s*&\s*" + N + r"\b(?!\s*\.)", f"&{N}.{members[h]}", text)
        text = re.sub(r"\(\s*" + v + r"\s*\*\s*\)(\s*&?\s*" + N + r"\b)", lambda m: f"({h} *){m.group(1)}", text)
        text = re.sub(r"\(\s*" + v + r"\s*\*\s*\*\s*\)(\s*&\s*" + N + r"\b)", lambda m: f"({h} **){m.group(1)}", text)
    # aliases nothing names any more go
    for v, h in pairs.items():
        line = f"typedef {h} {v};\n"
        if line in text and len(re.findall(r"\b" + v + r"\b", C.strip_comments(text))) == 1:
            text = text.replace(line, "", 1)
    return text


def check(rel, text):
    b_asm, b_d = L.head_compile(rel)
    n_asm, n_d = L.compile_s(rel, text)
    return n_asm is not None and L.same_asm(n_asm, b_asm) and not (L.warnings(n_d) - L.warnings(b_d))


def main(argv):
    apply = "--apply" in argv
    names = [a for a in argv if a.startswith("D_")]
    L.head_tree()
    srcs = {p: p.read_text() for p in (ROOT / "src").rglob("*.c") if not str(p).startswith(str(ROOT / "src/sdk"))}
    hdrs = sorted((ROOT / "include/data/pieces").glob("D_*.h"))
    done = 0
    for h in hdrs:
        N = h.stem
        if N.endswith("_s") or (names and N not in names):
            continue
        ht = h.read_text() + (h.with_name(N + "_s.h").read_text() if h.with_name(N + "_s.h").exists() else "")
        hdr_types = set(re.findall(r"\}\s*(\w+)\s*;", ht)) | set(re.findall(r"typedef struct (\w+) \1;", ht))
        for p, t in srcs.items():
            if N not in t:
                continue
            rel = str(p.relative_to(ROOT))
            if rel not in L.recipes():
                continue
            views = []
            for _, ty in S.casts(t, N):
                if S.kind(ty, hdr_types) == "view":
                    m = re.match(r"\s*(?:volatile\s+)?(\w+)\s*\*+\s*$", ty)
                    if m and m.group(1) not in views:
                        views.append(m.group(1))
            if not views:
                continue
            try:
                pairs, members = match_file(N, rel, t, views)
            except Exception as e:  # noqa: BLE001
                print(f"{N}\t{rel}\terror {e}")
                continue
            if not any(v in pairs for v in views):
                continue
            res = None
            for use_member in ((True, False) if members else (False,)):
                try:
                    nt = rewrite(N, rel, t, pairs, members, use_member)
                except Exception as e:  # noqa: BLE001
                    print(f"{N}\t{rel}\trewrite error {e}")
                    break
                if check(rel, nt):
                    res = (nt, "member" if use_member else "cast")
                    break
            mapped = ", ".join(f"{v}->{pairs[v]}" for v in views if v in pairs)
            if res is None:
                print(f"{N}\t{rel}\tCHANGES\t{mapped}")
                continue
            print(f"{N}\t{rel}\tOK {res[1]}\t{mapped}", flush=True)
            if apply:
                p.write_text(res[0])
                srcs[p] = res[0]
                done += 1
    print(f"# {done} files written", file=sys.stderr)


if __name__ == "__main__":
    main(sys.argv[1:])
