#!/usr/bin/env python3
"""Rename a user's field accesses through its own view to the piece's struct (session 28).

  python3 -I tools/shift/s28types/s28_partial.py [--apply] [--only FILE ...] D_X ...

s27_fold folds a user only when every field it reads fits the merged struct; a user
with one field that overlaps differently keeps all its casts.  This takes the casts
off one access at a time: an access `(*(V *)&D_X).f` / `((V *)&D_X)->f` (object
piece) or `((V *)D_X)->f` (pointer piece), and `((V *)D_X)[i].f` when V is as big as
the piece's element type, becomes `D_X.F` / `D_X->F` / `D_X[i].F` when V's field f
(measured by a probe compile, s27_layout) is a field F of the piece's struct at the
same offset: a scalar of a compatible type (`compatible()` of s27_merge), an array
of the same element type starting there (`F` keeps its length), a scalar inside such
an array (`F[k]`), or a bit-field at the same bits.  Struct-typed and pointer fields
are left alone.  Each file is -S checked against HEAD (all of its renames at once,
else one by one); a split piece's users get D_X_s.h in place of D_X.h.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402
import s27_ctext as C  # noqa: E402
import s27_layout as Y  # noqa: E402
import s27_merge as M  # noqa: E402
import s27_fold as F  # noqa: E402
import s27_trim as T  # noqa: E402

ROOT = L.ROOT


def piece_struct(N):
    """(root struct name, form 'obj'|'ptr'|'arr', {fields}, struct size, split) or None"""
    hpath = ROOT / f"include/data/pieces/{N}.h"
    htext = hpath.read_text()
    em = re.search(r"^extern ([^\n]*\b" + N + r"\b[^\n]*);", htext, re.M)
    if not em:
        return None
    decl = em.group(1)
    m = re.match(r"^(?:volatile\s+)?(\w+)\s*(\*?)\s*(?:volatile\s+)?" + N + r"\s*(\[[^\]]*\])?\s*$", decl)
    if not m:
        return None
    S0 = m.group(1)
    form = "ptr" if m.group(2) else ("arr" if m.group(3) else "obj")
    spath = hpath.with_name(f"{N}_s.h")
    split = spath.exists()
    if split:
        body = re.sub(r'#(?:ifndef|define|endif|include)[^\n]*\n', "", spath.read_text())
        e2 = re.search(r"^extern [^\n]*\b" + N + r"\b[^\n]*;\n", htext, re.M)
        htext = htext[:e2.start()] + body + "\n" + htext[e2.start():]
    if C.find_def(types_headers(htext) + htext, S0) is None:
        return None
    ft = HFileTypes(str(hpath.relative_to(ROOT)), htext, [S0])
    ft.probe()
    node = ft.nodes[ft.byname[S0]]
    if node.kind != "struct":
        return None
    return S0, form, node, split


def types_headers(text, seen=None):
    """text of the data/types headers a file includes (and theirs), for parsing view types
    that session 24 moved out of the file"""
    seen = set() if seen is None else seen
    out = ""
    for inc in re.findall(r'#include "(data/types/[^"]+)"', text):
        if inc in seen:
            continue
        seen.add(inc)
        p = ROOT / "include" / inc
        if p.exists():
            t = p.read_text()
            out += types_headers(t, seen) + re.sub(r"#[^\n]*\n", "\n", t) + "\n"
    return out


class HFileTypes(Y.FileTypes):
    """FileTypes that also finds view types in the file's data/types headers (the probe
    still compiles the file itself, which includes them)"""
    def __init__(self, rel, text, roots):
        self.probe_text = text
        extra = types_headers(text)
        self.extra_len = len(extra)
        super().__init__(rel, extra + text, roots)

    def probe(self):
        aug = self.text
        self.text = self.probe_text
        try:
            super().probe()
        finally:
            self.text = aug


def compat(a, b):
    return M.compatible((a or "").strip(), (b or "").strip())


def match(fv, node):
    """the access text replacing `.f` for view field fv, or None"""
    for fs in node.fields:
        if fs.name.startswith("pad") or fs.kind == "struct" or fs.ptrnode is not None or fs.localref:
            continue
        if fv.kind == "bits":
            if fs.kind == "bits" and fs.bitoff == fv.bitoff and fs.width == fv.width and compat(fs.tkey, fv.tkey):
                return fs.name
            continue
        if fs.kind == "bits" or fv.kind != "leaf":
            continue
        if "*" in (fv.tkey or "") or "*" in (fs.tkey or ""):
            continue
        vd, sd = len(fv.mem.dims), len(fs.mem.dims)
        if fv.off == fs.off and vd == sd == 0 and fv.size == fs.size and compat(fs.tkey, fv.tkey):
            return fs.name
        if (fv.off == fs.off and vd == sd == 1 and fv.elem == fs.elem
                and compat(M.elem_key(fs.tkey) or "", M.elem_key(fv.tkey) or "?")):
            return fs.name
        if (vd == 0 and sd == 1 and fs.off <= fv.off < fs.off + fs.size and fv.size == fs.elem
                and (fv.off - fs.off) % fs.elem == 0 and compat(M.elem_key(fs.tkey) or "", fv.tkey)):
            return f"{fs.name}[{(fv.off - fs.off) // fs.elem}]"
    return None


def edits_for(N, rel, text, info):
    S0, form, node, split = info
    ct = C.strip_comments(text)
    res = []
    for V in sorted({v for v, _ in F.view_casts(text, N) if v not in F.NOTVIEW}):
        try:
            ft = HFileTypes(rel, text, [V])
            ft.probe()
        except Exception:  # noqa: BLE001
            continue
        vn = ft.nodes[ft.byname[V]]
        if vn.kind != "struct":
            continue
        vf = {f.name: f for f in vn.fields}
        v = re.escape(V)
        pats = []
        if form == "obj":
            pats.append((r"\(\s*\*\s*\(\s*" + v + r"\s*\*\s*\)\s*&\s*" + N + r"\s*\)\s*\.\s*(\w+)\b", N + "."))
            pats.append((r"\(\s*\(\s*" + v + r"\s*\*\s*\)\s*&\s*" + N + r"\s*\)\s*->\s*(\w+)\b", N + "."))
        elif form == "ptr":
            pats.append((r"\(\s*\(\s*" + v + r"\s*\*\s*\)\s*" + N + r"\s*\)\s*->\s*(\w+)\b", N + "->"))
            pats.append((r"\(\s*\*\s*\(\s*" + v + r"\s*\*\s*\)\s*" + N + r"\s*\)\s*\.\s*(\w+)\b", N + "->"))
        if vn.size == node.size and form in ("ptr", "arr"):
            pats.append((r"\(\s*\(\s*" + v + r"\s*\*\s*\)\s*" + N + r"\s*\)\s*(\[[^\[\]]*(?:\[[^\[\]]*\][^\[\]]*)*\])\s*\.\s*(\w+)\b", None))
        for pat, pre in pats:
            for m in re.finditer(pat, ct):
                if pre is None:
                    idx, fname = m.group(1), m.group(2)
                    rep_pre = N + text[m.start(1):m.end(1)] + "."
                else:
                    fname, rep_pre = m.group(1), pre
                f = vf.get(fname)
                if f is None:
                    continue
                to = match(f, node)
                if to is None:
                    continue
                res.append((m.start(), m.end(), rep_pre + to))
    return sorted(res)


def with_include(N, text, split):
    if not split:
        return text
    inc0 = f'#include "data/pieces/{N}.h"'
    inc = f'#include "data/pieces/{N}_s.h"'
    if inc in text or inc0 not in text:
        return text
    return text.replace(inc0, inc, 1)


def ok(rel, text, base):
    asm, d = L.compile_s(rel, text)
    return asm is not None and L.same_asm(asm, base[0]) and not (L.warnings(d) - L.warnings(base[1]))


def do_file(N, rel, info):
    text = (ROOT / rel).read_text()
    es = edits_for(N, rel, text, info)
    if not es:
        return text, 0, 0
    base = L.head_compile(rel)
    cur = L.compile_s(rel, text)
    if not (cur[0] is not None and L.same_asm(cur[0], base[0])):
        return text, 0, len(es)
    base = (base[0], cur[1])
    split = info[3]
    t_all = with_include(N, T.apply_some(text, es), split)
    if ok(rel, t_all, base):
        return t_all, len(es), len(es)
    keep = []
    for e in es:
        if ok(rel, with_include(N, T.apply_some(text, keep + [e]), split), base):
            keep.append(e)
    if not keep:
        return text, 0, len(es)
    return with_include(N, T.apply_some(text, keep), split), len(keep), len(es)


def main(argv):
    apply = "--apply" in argv
    only = None
    if "--only" in argv:
        i = argv.index("--only"); only = set()
        j = i + 1
        while j < len(argv) and not argv[j].startswith("D_") and not argv[j].startswith("-"):
            only.add(argv[j]); j += 1
    names = [a for a in argv if a.startswith("D_")]
    L.head_tree()
    tot = [0, 0]
    for N in names:
        try:
            info = piece_struct(N)
        except Exception as e:  # noqa: BLE001
            print(f"{N}: piece struct not understood: {e}")
            continue
        if info is None:
            print(f"{N}: no struct declaration")
            continue
        for rel in sorted(F.users_of(N)):
            if only and rel not in only:
                continue
            try:
                t, k, n = do_file(N, rel, info)
            except Exception as e:  # noqa: BLE001
                print(f"{N} {rel}: error {e}")
                continue
            if n:
                print(f"{N} {rel}: {k} of {n} accesses renamed", flush=True)
            tot[0] += k; tot[1] += n
            if apply and k:
                (ROOT / rel).write_text(t)
    print(f"# {tot[0]} of {tot[1]} accesses renamed")


if __name__ == "__main__":
    main(sys.argv[1:])
