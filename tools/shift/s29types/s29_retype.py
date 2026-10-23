#!/usr/bin/env python3
"""Make a file's own struct type an alias of a shared one, renaming its field accesses (session 29).

  python3 -I tools/shift/s29types/s29_retype.py [--apply] FILE.c TYPE --shared S --header H
        [--alias A ...] [--map f=g ...] [--objtag TYPE2=TAG ...] [--uncast D_X ...]
        [--sub 'OLD=>NEW' ...]

TYPE is a struct typedef defined in FILE.c (or an alias `typedef X TYPE;` there).
Its definition becomes `typedef S TYPE;` and `#include "H"` goes after common.h.
Every field of TYPE the file reads (s29_used) is mapped to S by layout (s29_stabs):
the field of S at the same offset with the same type (a scalar inside an S array
becomes `arr[k]`, a top-level bit-field the bit-field at the same bits anywhere
in S, an aggregate the S aggregate of the same size).  `--map f=g` overrides.
Accesses are renamed on the lines gcc reports (`has no member named`), all
occurrences on a line first, else one at a time.  `--objtag T2=TAG` gives the
file's struct typedef T2 the tag TAG (for S's `struct TAG *` fields).
`--uncast D_X` drops the casts `(TYPE *)&D_X` / `(A *)&D_X` (D_X must be an S array).
The result is -S checked against HEAD (s27lib); --apply writes it when SAME.
"""
import argparse, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402
import s27_ctext as C  # noqa: E402
import s29_stabs as ST  # noqa: E402
import s29_used as U  # noqa: E402


def leaves_of(rel, text, name):
    p = ST.parse(rel, text)
    n = p.named[name]
    return p, n, p.leaves(n)


def shared_leaves(rel, S, header):
    probe = f'#include "common.h"\n#include "{header}"\n{S} s29_probe_v;\n'
    return leaves_of(rel, probe, S)


def auto_map(tl, sl, used, shift=0):
    """{field: S path} for the used top-level fields of TYPE (tl/sl: leaves of TYPE / S);
    shift: TYPE's offset o is S's offset o - shift (a view that starts `shift` bytes early)"""
    top = {path: (bo - 8 * shift, bs, sp, k) for bo, bs, sp, path, k in tl if "." not in path}
    out, why = {}, {}
    for f in sorted(used):
        if f not in top:
            why[f] = "not a top-level field"
            continue
        bo, bs, sp, k = top[f]
        cands = []
        for sbo, sbs, ssp, spath, sk in sl:
            if re.match(r"(.*\.)?pad", spath):
                continue  # never map onto S's padding
            if k.startswith("bits"):
                if sk.startswith("bits") and sbo == bo and sbs == bs:
                    cands.append(spath)
            elif k.startswith("agg"):
                if sk.startswith("agg") and sbo == bo and sbs == bs and ssp == sp:
                    cands.append(spath)
            elif sk.startswith("leaf") and ssp == sp and sbo == bo and sbs == bs:
                cands.append(spath)
            elif sk.startswith("leaf") and sbo == bo and sp.endswith(" *") and ssp.endswith(" *"):
                cands.append(spath)  # a pointer: the pointee is the file's own view (--objtag)
            elif (sk.startswith("leaf") and sbo == bo and sp.endswith("]") and ssp.endswith("]")
                  and sp.rsplit(" [", 1)[0] == ssp.rsplit(" [", 1)[0]):
                cands.append(spath)  # an array of the same elements from the same offset
            elif sk.startswith("leaf") and ssp.endswith("]") and "." not in spath:
                el = ssp.rsplit(" [", 1)[0]
                esz = sbs // int(ssp.rsplit("[", 1)[1][:-1])
                if el == sp and esz == bs and sbo <= bo < sbo + sbs and (bo - sbo) % esz == 0:
                    cands.append(f"{spath}[{(bo - sbo) // esz}]")
        if f in cands:
            out[f] = f
        elif cands:
            out[f] = sorted(cands, key=lambda c: (c.count("."), c))[0]
        else:
            why[f] = f"no S field at {bo // 8:#x} as {sp} ({bs} bits)"
    return out, why


def rename_line(line, f, g):
    return re.sub(r"(->|\.)(\s*)" + re.escape(f) + r"\b", lambda m: m.group(1) + m.group(2) + g, line)


def occurrences(line, f):
    return [m.start() for m in re.finditer(r"(->|\.)\s*" + re.escape(f) + r"\b", line)]


def rename_one(line, f, g, idx):
    m = re.compile(r"(->|\.)(\s*)" + re.escape(f) + r"\b").match(line, idx)
    return line[:m.start()] + m.group(1) + m.group(2) + g + line[m.end():]


def member_errors(diags):
    out = {}
    for ln, msg in diags:
        m = re.search(r"has no member named [`'](\w+)'", msg)
        if m:
            out.setdefault(ln, set()).add(m.group(1))
    return out


TOUCHED = []  # (path, original text) of headers edited in place


def restore():
    while TOUCHED:
        p, t = TOUCHED.pop()
        p.write_text(t)


def retype(rel, T, S, header, aliases=(), manual=None, objtags=(), uncast=(), subs=(), hdr=None, shift=0):
    """(new text or None, report lines)"""
    rep = []
    text = (L.ROOT / rel).read_text()
    names = [T] + list(aliases)
    used = sorted(set(f for _, f in U.used(rel, names)[0]))
    _, _, tl = leaves_of(rel, None, T)
    _, _, sl = shared_leaves(rel, S, header)
    fmap, why = auto_map(tl, sl, used, shift)
    fmap.update(manual or {})
    for f in list(why):
        if f in fmap:
            del why[f]
    rep.append(f"used: {' '.join(used)}")
    rep.append("map: " + " ".join(f"{a}->{b}" for a, b in sorted(fmap.items()) if a != b))
    if why:
        rep.append("unmapped: " + "; ".join(f"{a}: {b}" for a, b in sorted(why.items())))
        return None, rep
    # the definition
    ct = U.blank_attrs(C.strip_comments(text))
    d = C.find_def(text, T, ct)
    if hdr:
        hp = L.ROOT / "include" / hdr
        ht = hp.read_text()
        hd = C.find_def(ht, T, U.blank_attrs(C.strip_comments(ht)))
        if hd is None:
            rep.append(f"{T}: not defined in {hdr}")
            return None, rep
        h2 = ht[:hd.start] + f"typedef {S} {T};" + ht[hd.end:]
        m = re.search(r'#include "common.h"\n', h2)
        h2 = h2[:m.end()] + f'#include "{header}"\n' + h2[m.end():]
        TOUCHED.append((hp, ht))
        hp.write_text(h2)
        t2 = text
    elif d is not None:
        if d.others:
            rep.append(f"{T} definition has other declarators {d.others}")
            return None, rep
        nl = text[d.start:d.end].count("\n")
        new = f"typedef {S} {T};" + "\n/*s29blank*/" * nl
        t2 = text[:d.start] + new + text[d.end:]
        if d.tagdef:
            a, b = d.tagdef
            t2 = t2[:a] + t2[b:] if a > d.end else t2  # (rare) leave others alone
    else:
        st = C.simple_typedef(ct, T)
        if st is None:
            rep.append(f"{T}: no local definition")
            return None, rep
        m = re.search(r"\btypedef\s+[\w\s]+?\s+" + T + r"\s*;", ct)
        t2 = text[:m.start()] + f"typedef {S} {T};" + text[m.end():]
    for spec in objtags:
        t2n, tag = spec.split("=")
        ct2 = U.blank_attrs(C.strip_comments(t2))
        d2 = C.find_def(t2, t2n, ct2)
        if d2 is None:
            rep.append(f"--objtag {t2n}: no local struct")
            return None, rep
        head = t2[d2.start:d2.b0]
        nh = re.sub(r"\btypedef\s+struct\s*(\w+\s*)?\{", f"typedef struct {tag} {{", head)
        t2 = t2[:d2.start] + nh + t2[d2.b0:]
    for sub in subs:
        old, new = sub.split("=>", 1)
        if old not in t2:
            rep.append(f"--sub: {old!r} not found")
            return None, rep
        t2 = t2.replace(old, new)
    inc = f'#include "{header}"'
    td = t2.find(f"typedef {S} {T};")
    if inc in t2 and td >= 0 and t2.index(inc) > td:
        t2 = t2.replace(inc, "/*s29blank*/", 1)  # included below the definition: moved up
    if inc not in t2:
        m = re.search(r'#include "common.h"\n', t2)
        if m:
            t2 = t2[:m.end()] + inc + "\n" + t2[m.end():]
        else:
            t2 = inc + "\n" + t2
        # one line was added above everything: line numbers below shift by 1
    # rename loop
    for it in range(30):
        asm, diags = L.compile_s(rel, t2)
        errs = member_errors(diags)
        if not errs:
            break
        lines = t2.split("\n")
        progress = False
        for ln, fs in sorted(errs.items()):
            if ln <= 0:
                continue
            for f in sorted(fs):
                if f not in fmap:
                    rep.append(f"line {ln}: {f} not mapped")
                    return None, rep
                g = fmap[f]
                occ = occurrences(lines[ln - 1], f)
                if len(occ) == 1:
                    lines[ln - 1] = rename_one(lines[ln - 1], f, g, occ[0])
                    progress = True
                    continue
                # several: keep each rename that does not leave `g` missing on the line
                for idx in reversed(occ):
                    cand = rename_one(lines[ln - 1], f, g, idx)
                    tt = "\n".join(lines[:ln - 1] + [cand] + lines[ln:])
                    _, dd = L.compile_s(rel, tt)
                    if g.split(".")[0].split("[")[0] not in member_errors(dd).get(ln, set()):
                        lines[ln - 1] = cand
                        progress = True
        t2 = "\n".join(lines)
        if not progress:
            break
    asm, diags = L.compile_s(rel, t2)
    if member_errors(diags) or asm is None:
        rep.append("does not compile: " + "; ".join(f"{a}: {b}" for a, b in diags[:6]))
        return None, rep
    t2 = t2.replace("\n/*s29blank*/", "")
    for D in uncast:
        for nm in names + [S]:
            pat = r"\(\s*\(\s*" + nm + r"\s*\*\s*\)\s*&\s*" + D + r"\s*\)"
            t2 = re.sub(pat, D, t2)
            t2 = re.sub(r"\(\s*" + nm + r"\s*\*\s*\)\s*&\s*" + D + r"\b", D, t2)
    return t2, rep


def check(rel, t2):
    asm, diags = L.compile_s(rel, t2)
    hasm, hdiags = L.head_compile(rel)
    if asm is None:
        return "NOCOMPILE", diags
    if not L.same_asm(asm, hasm):
        return "CODE", diags
    nw = L.warnings(diags) - L.warnings(hdiags)
    if nw:
        return "WARN", sorted(nw)
    return "SAME", []


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("file")
    ap.add_argument("type")
    ap.add_argument("--shared", required=True)
    ap.add_argument("--header", required=True)
    ap.add_argument("--alias", nargs="*", default=[])
    ap.add_argument("--map", nargs="*", default=[])
    ap.add_argument("--objtag", nargs="*", default=[])
    ap.add_argument("--uncast", nargs="*", default=[])
    ap.add_argument("--sub", nargs="*", default=[], help="OLD=>NEW text edits made first")
    ap.add_argument("--hdr", help="TYPE is defined in this include/ header (edited too)")
    ap.add_argument("--shift", type=lambda x: int(x, 0), default=0,
                    help="TYPE starts this many bytes before S (field at o is S's o - shift)")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--force", action="store_true", help="write even when the -S differs")
    ap.add_argument("--out")
    a = ap.parse_args(argv)
    manual = dict(x.split("=", 1) for x in a.map)
    t2, rep = retype(a.file, a.type, a.shared, a.header, a.alias, manual, a.objtag, a.uncast, a.sub, a.hdr, a.shift)
    for r in rep:
        print(r)
    if t2 is None:
        restore()
        print("FAIL")
        return 1
    if a.out:
        Path(a.out).write_text(t2)
    res, info = check(a.file, t2)
    print(res, *info[:8])
    if a.force and res in ("SAME", "CODE"):
        (L.ROOT / a.file).write_text(t2)
        TOUCHED.clear()
        print("written (--force: a step of a two-type change; check the next step)")
    elif res == "SAME" and a.apply:
        (L.ROOT / a.file).write_text(t2)
        TOUCHED.clear()
        print("applied")
    restore()
    return 0 if res == "SAME" else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
