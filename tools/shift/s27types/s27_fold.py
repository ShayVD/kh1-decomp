#!/usr/bin/env python3
"""Fold the users' struct views of a cast-unified data piece into one struct (session 27).

  python3 -I tools/shift/s27types/s27_fold.py [--apply] [--name S] [--only F ...] [--skip F ...] D_X

Session 26 gave each "users disagree" piece one declaration, and users whose view
differed cast at each use (`((View *)D_X)->f`, `(*(View *)&D_X).f`).  This tool:

1. finds each user's view types (local struct typedefs cast to before D_X / &D_X)
   and, per file, the local struct types reachable from them (named or anonymous
   member structs); measures their layouts with a probe compile;
2. renames every field of those types to a unique temporary name and lets the
   compiler find the accesses (`structure has no member named`), so only the fields
   the file really uses count, and each access is renamed exactly;
3. merges the used fields of all users into one struct per class of types (types at
   the same struct position in some file are one class): fields at the same offset,
   size and type become one field, named from the users' names (hand files first);
   a file whose field overlaps another's differently stays as it was;
4. writes the merged types and `extern S *D_X;` (pointer pieces) or `extern S D_X;`
   (object pieces) to include/data/pieces/D_X.h; in each folded file the view types
   become aliases (`typedef S View;`), the accesses use the merged names and the
   casts to the view go; files that are not folded keep their casts (other users
   whose plain uses no longer type-check get value casts to the old declaration);
5. accepts a file only if its -S output (vs HEAD) is the same and it warns no more;
   files that change are dropped and the merge is redone.

Without --apply the work tree is restored.  Log lines go to stdout.
"""
import itertools, os, re, sys
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s26types"))
import s27lib as L  # noqa: E402
import s27_ctext as C  # noqa: E402
import s27_layout as Y  # noqa: E402
import s27_merge as M  # noqa: E402

ROOT = L.ROOT
NOTVIEW = C.BASIC | {"M2C_UNK", "int", "char", "void"}


def log(*a):
    print(*a, flush=True)


# ---------------------------------------------------------------- users and views

def users_of(N):
    out = {}
    for p in sorted((ROOT / "src").rglob("*.c")):
        rel = str(p.relative_to(ROOT))
        if rel.startswith(("src/sdk/", "src/data/")) or p.name.startswith("."):
            continue
        t = p.read_text()
        if re.search(r"\b" + N + r"\b", t) and rel in L.recipes():
            out[rel] = t
    return out


def view_casts(text, N):
    """[(view type, form)] of casts `(V *)N` (form 'ptr') or `(V *)&N` (form 'obj')"""
    ct = C.strip_comments(text)
    out = []
    for m in re.finditer(r"\(\s*(\w+)\s*\*\s*\)\s*(&?)\s*(?:\(\s*)?" + N + r"\b", ct):
        out.append((m.group(1), "obj" if m.group(2) else "ptr"))
    # (V *)((W *)N): the outer cast of an inner view cast
    for m in re.finditer(r"\(\s*(\w+)\s*\*\s*\)\s*\(\s*\(\s*\w+\s*\*\s*\)\s*(&?)\s*" + N + r"\b", ct):
        out.append((m.group(1), "obj" if m.group(2) else "ptr"))
    return out


# ---------------------------------------------------------------- phase 1: compiler-driven rename

def tmpname(x, nid):
    return f"{x}__q{nid}"


def rename_defs(ft):
    """text with every field of every node renamed to its temporary name (in the definitions)"""
    text = ft.text
    edits = []  # (start, end, new)

    def body_edits(node, b0, b1):
        body = text[b0:b1]
        cbody = C.strip_comments(body)
        # inline children: their braces at depth 0 of this body, in order
        kids = list(node.inline_children)
        spans = []
        for m in re.finditer(r"\b(struct|union)\s*\w*\s*\{", cbody):
            if any(a <= m.start() < b for a, b in spans):
                continue
            depth = cbody[:m.start()].count("{") - cbody[:m.start()].count("}")
            if depth != 0:
                continue
            e = C.match_brace(cbody, m.end() - 1)
            spans.append((m.end(), e - 1))
        if len(spans) != len(kids):
            raise ValueError(f"inline structs of {node.name}: {len(spans)} vs {len(kids)}")
        for (a, b), k in zip(spans, kids):
            body_edits(ft.nodes[k], b0 + a, b0 + b)
        names = {f.name for f in node.fields}
        for m in re.finditer(r"\b(\w+)\b(?=\s*(\[|;|,|:|\)))", cbody):
            if any(a <= m.start() < b for a, b in spans):
                continue
            if m.group(1) in names:
                edits.append((b0 + m.start(1), b0 + m.end(1), tmpname(m.group(1), node.nid)))
    for n in ft.nodes.values():
        if n.parent is None:
            body_edits(n, n.defn.b0, n.defn.b1)
    for a, b, new in sorted(edits, reverse=True):
        text = text[:a] + new + text[b:]
    return text


def number_dot(line, i):
    """line[i] == '.' or '-': is it the dot of a number literal (1.5f)?"""
    if line[i] != ".":
        return False
    k = i
    while k > 0 and (line[k - 1].isalnum() or line[k - 1] == "_"):
        k -= 1
    return k < i and line[k].isdigit()


MISSING = re.compile(r"(?:structure|union) has no member named `(\w+)'")


def phase1(ft):
    """(text with every use of a node field renamed, set of used tmp names)"""
    cand = defaultdict(list)
    for n in ft.nodes.values():
        for f in n.fields:
            if tmpname(f.name, n.nid) not in cand[f.name]:
                cand[f.name].append(tmpname(f.name, n.nid))
    text = rename_defs(ft)
    lines = text.split("\n")
    state = {}  # line -> (orig line, occs, combo iterator index, combos)
    for it in range(60):
        asm, diags = L.compile_s(ft.rel, "\n".join(lines))
        errs = defaultdict(int)
        other = []
        for ln, msg in diags:
            m = MISSING.search(msg)
            if m:
                x = m.group(1)
                if x in cand or "__q" in x:
                    errs[ln] += 1
                    continue
            if "error" in msg.lower() or (asm is None and ln and "warning" not in msg):
                other.append((ln, msg))
        if not errs:
            if asm is None:
                raise ValueError("phase 1: " + "; ".join(f"{a}: {b}" for a, b in other)[:400])
            break
        for ln in errs:
            i = ln - 1
            if i not in state:
                # the occurrence may be on this line or a few lines before (multi-line expressions)
                for j in (i, i - 1, i - 2, i - 3):
                    if j < 0:
                        continue
                    occ = [(m.start(1), m.end(1), m.group(1))
                           for m in re.finditer(r"(?:->|\.)\s*(\w+)\b", lines[j])
                           if m.group(1) in cand and not number_dot(lines[j], m.start())]
                    if occ:
                        break
                else:
                    raise ValueError(f"phase 1: no field use found near line {ln}")
                opts = [[o[2]] + cand[o[2]] for o in occ]
                combos = sorted(itertools.product(*[range(len(o)) for o in opts]),
                                key=lambda c: (sum(1 for x in c if x == 0), c))
                if len(combos) > 4096:
                    raise ValueError(f"phase 1: line {j + 1}: too many combinations")
                state[i] = [j, lines[j], occ, opts, -1, combos]
            st = state[i]
            st[4] += 1
            if st[4] >= len(st[5]):
                raise ValueError(f"phase 1: line {st[0] + 1}: no renaming compiles")
            j, orig, occ, opts, k, combos = st
            new, last = [], 0
            for (a, b, x), o, c in zip(occ, opts, combos[k]):
                new.append(orig[last:a]); new.append(o[c]); last = b
            new.append(orig[last:])
            lines[j] = "".join(new)
    else:
        raise ValueError("phase 1: no fixpoint")
    text = "\n".join(lines)
    used = set(re.findall(r"\b\w+__q\d+\b", C.strip_comments(text)))
    # the definitions themselves name every tmp field once; a use needs a second occurrence
    cnt = Counter(re.findall(r"\b\w+__q\d+\b", C.strip_comments(text)))
    used = {u for u in used if cnt[u] > 1}
    return text, used


def is_hand(rel):
    return rel.startswith("src/hand/")


# ---------------------------------------------------------------- phase 2: per file

def strip_view_casts(text, N, views, obj):
    vs = "|".join(re.escape(v) for v in sorted(views, key=len, reverse=True))
    if not vs:
        return text
    for _ in range(4):
        old = text
        if obj:
            text = re.sub(r"\(\s*\*\s*\(\s*(?:" + vs + r")\s*\*\s*\)\s*&\s*" + N + r"\s*\)", N, text)
            text = re.sub(r"\(\s*\(\s*(?:" + vs + r")\s*\*\s*\)\s*&\s*" + N + r"\s*\)", "&" + N, text)
            text = re.sub(r"\(\s*(?:" + vs + r")\s*\*\s*\)\s*&\s*" + N + r"\b", "&" + N, text)
        else:
            text = re.sub(r"\(\s*\(\s*(?:" + vs + r")\s*\*\s*\)\s*" + N + r"\s*\)", N, text)
            text = re.sub(r"\(\s*(?:" + vs + r")\s*\*\s*\)\s*" + N + r"\b", N, text)
            text = re.sub(r"\(\s*\(\s*(?:" + vs + r")\s*\*\s*\)\s*\(\s*" + N + r"\s*\)\s*\)", N, text)
        if text == old:
            break
    return text


def rename_view_casts(text, N, views, S):
    """`(V *)N`, `(V *)&N` -> `(S *)...` for the folded views V (aliases of S)"""
    vs = "|".join(re.escape(v) for v in sorted(views, key=len, reverse=True))
    text = re.sub(r"\(\s*\(\s*(?:" + vs + r")\s*\*\s*\)\s*\(\s*\(\s*(?:" + vs + r")\s*\*\s*\)\s*(&?)\s*" + N + r"\s*\)\s*\)",
                  lambda m: f"(({S} *){m.group(1)}{N})", text)
    return re.sub(r"\(\s*(?:" + vs + r")\s*\*\s*\)(\s*&?\s*" + N + r"\b)", lambda m: f"({S} *){m.group(1)}", text)


def phase2(rel, p1text, ft, aliases, fmap, N, obj, views, keepcast=None):
    text = p1text
    inc = f'#include "data/pieces/{N}.h"'
    # alias the class members' named types
    reps = []
    for nid, n in ft.nodes.items():
        if n.parent is not None or (rel, nid) not in aliases:
            continue
        d = C.find_def(text, n.name)
        if d.tagdef:
            raise ValueError("tag-defined view")
        reps.append((d, aliases[(rel, nid)], n.name))
    first = min(d.start for d, _, _ in reps)
    for d, S, name in sorted(reps, key=lambda r: -r[0].start):
        new = f"typedef {S} {name};"
        if d.others:
            new += f"\ntypedef {S} " + ", ".join(d.others) + ";"
        text = text[:d.start] + new + text[d.end:]
    # field names
    def rn(m):
        k = (rel, m.group(0))
        if k not in fmap:
            raise KeyError(m.group(0))
        return fmap[k]
    try:
        text = re.sub(r"\b\w+__q\d+\b", rn, text)
    except KeyError as e:
        raise ValueError(f"used field {e} has no merged field")
    if keepcast:
        text = rename_view_casts(text, N, views, keepcast)
    else:
        text = strip_view_casts(text, N, views, obj)
    # aliases nothing names any more go
    for d, S, name in reps:
        line = f"typedef {S} {name};"
        ct = C.strip_comments(text)
        if not d.others and len(re.findall(r"\b" + name + r"\b", ct)) == 1 and line in text:
            i = text.index(line)
            text = text[:i] + text[i + len(line):].lstrip(" ")
            if text[i:i + 1] == "\n" and (i == 0 or text[i - 1] == "\n"):
                text = text[:i] + text[i + 1:]
            first = min(first, i)
    # the piece header before the first alias
    pos = text.find(inc)
    if pos < 0 or pos > first:
        if pos >= 0:
            e = text.find("\n", pos)
            text = text[:pos] + text[e + 1:] if text[pos - 1] == "\n" or pos == 0 else text[:pos] + text[e:]
        text = text[:first] + inc + "\n" + text[first:]
    return text


# ---------------------------------------------------------------- the piece header

def header_decl(N):
    t = (ROOT / f"include/data/pieces/{N}.h").read_text()
    m = re.search(r"^extern ([^\n]*\b" + N + r"\b[^\n]*);", t, re.M)
    return t, m.group(1)


def new_header(N, oldhdr, defs, deps, decl, mode="full"):
    incs = sorted(deps)
    body = ["/* The data piece " + N + " (src/data/data_" + f"{int(N[2:], 16) >> 16:04X}" + ".s): one struct its",
            " * users share (phase 4: session 26 cast at each use, session 27 folded the users'",
            " * views into these types; users not folded still cast" +
            ("" if mode == "full" else ", and the folded ones cast to it: the declaration\n * keeps its type because other users' code needs it") + "). */",
            f"#ifndef KH1_DATA_PIECES_{N}_H", f"#define KH1_DATA_PIECES_{N}_H", "", '#include "common.h"']
    body += [f'#include "{h}"' for h in incs if h != "common.h"]
    body += [""] + [d + "\n" for d in defs] + [f"extern {decl};", "", f"#endif /* KH1_DATA_PIECES_{N}_H */", ""]
    return "\n".join(body)


# ---------------------------------------------------------------- fallback for other users

CASTBEFORE = re.compile(r"\)\s*&?\s*$")


def plain_fix(text, N, olddecl, newdecl, lvalue=False):
    """users that are not folded and use N without a cast: give each such use the value (or
    lvalue) of the old declaration"""
    os.environ.setdefault("S26_DIR", str(L.SCR / "s26"))
    import s26_cast as S26
    m = re.match(r"^(.*?)\b" + N + r"\b(.*)$", olddecl)
    tspec = m.group(1).strip()
    dpart = (olddecl[len(m.group(1)):]).strip()
    # protect already-cast uses
    ct = C.strip_comments(text)
    hits = []
    for mm in re.finditer(r"\b" + N + r"\b", ct):
        pre = ct[:mm.start()].rstrip()
        if pre.endswith("&"):
            pre2 = pre[:-1].rstrip()
        else:
            pre2 = pre
        if pre2.endswith(")") and S26.CASTEND.search(pre2):
            hits.append(mm.start())
    for s in reversed(hits):
        text = text[:s] + "\0P\0" + text[s + len(N):]
    ts = re.sub(r"\s+", " ", tspec)
    own = (ts.replace("extern ", ""), S26.norm(dpart))
    # every use through the old declaration's lvalue (`(*(s32 *)&N)`): a value cast of the
    # new pointer type would load N with the pointer's alias set and can move code.
    # (a "shared" declaration that is not scalar_int makes rewrite_uses use the lvalue form)
    shared = ("volatile __lvalue_form", N)
    if not lvalue:
        m2 = re.match(r"^(.*?)(\**\s*(?:volatile\s*)?\b" + N + r"\b.*)$", newdecl)
        shared = (m2.group(1).strip(), S26.norm(m2.group(2)))
    text = S26.rewrite_uses(text, N, own, shared)
    return text.replace("\0P\0", N)


# ---------------------------------------------------------------- driver

def main(argv):
    apply = "--apply" in argv
    args = [a for a in argv if a != "--apply"]
    sname = only = None
    skip = set()
    if "--name" in args:
        i = args.index("--name"); sname = args[i + 1]; del args[i:i + 2]
    if "--skip" in args:
        i = args.index("--skip"); j = i + 1
        while j < len(args) and not args[j].startswith("-") and not args[j].startswith("D_"):
            skip.add(args[j]); j += 1
        del args[i:j]
    if "--only" in args:
        i = args.index("--only"); j = i + 1; only = set()
        while j < len(args) and not args[j].startswith("-") and not args[j].startswith("D_"):
            only.add(args[j]); j += 1
        del args[i:j]
    N = args[0]
    given_name = sname
    hpath = ROOT / f"include/data/pieces/{N}.h"
    oldhdr, olddecl = header_decl(N)
    users = users_of(N)
    log(f"{N}: {olddecl}; {len(users)} users")
    L.head_tree()
    files = {}
    prio = {}
    forms = set()
    for rel, t in users.items():
        vc = view_casts(t, N)
        roots = []
        ct = C.strip_comments(t)
        for v, form in vc:
            if v in NOTVIEW or v in roots:
                continue
            if C.find_def(t, v, ct) is None:
                continue
            roots.append(v)
            forms.add(form)
        if not roots or rel in skip or (only and rel not in only):
            continue
        prio[rel] = (0 if is_hand(rel) else 1, -len(vc), rel)
        files[rel] = (t, roots)
    if len(forms) > 1:
        log(f"  mixed cast forms {forms}: stop")
        return 1
    obj = forms == {"obj"}
    log(f"  {len(files)} files with struct views ({'object' if obj else 'pointer'} piece)")

    def p1(rel):
        t, roots = files[rel]
        try:
            ft = Y.FileTypes(rel, t, roots)
            ft.probe()
            for n in ft.nodes.values():
                if n.kind != "struct":
                    raise ValueError(f"{n.name or 'anon'} is a union")
            text, used = phase1(ft)
            return rel, (ft, used, roots, text), None
        except Exception as e:  # noqa: BLE001
            return rel, None, str(e)
    done = {}
    with ThreadPoolExecutor(3) as ex:
        for rel, res, err in ex.map(p1, sorted(files)):
            if err:
                log(f"  skip {rel}: {err}")
            else:
                done[rel] = res
    if not done:
        log("  nothing to fold")
        return 1
    # an earlier session 27 fold: its header's struct is one more view, first in naming
    hrel = f"include/data/pieces/{N}.h"
    if "session 27 folded" in oldhdr:
        hm = re.match(r"^(?:volatile\s+)?(\w+)\s*\*?\s*(?:volatile\s*)?" + N + r"\b", olddecl)
        S0 = hm.group(1) if hm else None
        if S0 is None or C.find_def(oldhdr, S0) is None:
            # keep mode: the struct is the one every typedef in the header ends with
            defs0 = re.findall(r"\}\s*(\w+);", C.strip_comments(oldhdr))
            S0 = defs0[-1] if defs0 else None
        try:
            ft = Y.FileTypes(hrel, oldhdr, [S0])
            ft.probe()
            used = {tmpname(f.name, n.nid) for n in ft.nodes.values() for f in n.fields
                    if not f.name.startswith("pad_")}
            done[hrel] = (ft, used, [S0], oldhdr)
            prio[hrel] = (-1, 0, hrel)
            given_name = given_name or S0
            log(f"  earlier fold: {S0} is a view")
        except Exception as e:  # noqa: BLE001
            log(f"  earlier fold's header not understood: {e}")
            return 1
    if not given_name:
        cnt = Counter()
        for rel, (t, roots) in files.items():
            for r in roots:
                cnt[r] += 3 if is_hand(rel) else 1
        addr = N[2:].lstrip("0").lower()
        sname = f"{cnt.most_common(1)[0][0]}_{addr}" if cnt else f"T_{addr}"
    sname = given_name or sname
    result = None
    for mode in ("full", "keep"):
        result = fold_rounds(mode, N, sname, obj, olddecl, oldhdr, hpath, users, done, prio, apply)
        if result:
            break
    if result:
        newtexts, hdr, mode = result
        log(f"  OK ({mode}): {len(newtexts)} files folded into {sname}")
        log(f"  folded: {' '.join(sorted(newtexts))}")
        log(f"  not folded: {' '.join(sorted(set(files) - set(newtexts)))}")
        if newtexts_plain:
            log(f"  value casts (old declaration) added in: {' '.join(sorted(newtexts_plain))}")
        print(hdr)
    return 0 if result else 1


def fold_rounds(mode, N, sname, obj, olddecl, oldhdr, hpath, users, done, prio, apply):
    hrel = f"include/data/pieces/{N}.h"
    """mode full: the piece is declared as the merged struct (pointer) and the folded users'
    casts go; mode keep: the declaration stays, folded users cast to the merged struct"""
    log(f"  -- mode {mode}")
    newtexts_plain.clear()
    excluded = {}
    for rnd in range(12):
        live = {r: (v[0], v[1], v[2]) for r, v in done.items() if r not in excluded}
        if not live:
            break
        mg = M.Merge(live, prio)
        while not mg.run():
            for r, why in mg.fail.items():
                log(f"  drop {r}: {why}")
                excluded[r] = why
            live = {r: v for r, v in live.items() if r not in excluded}
            if not live:
                break
            mg = M.Merge(live, prio)
        if not [r for r in live if r != hrel]:
            break
        defs, deps, aliases, fmap = M.emit(N, mg, sname)
        if mode == "keep":
            decl = olddecl
        elif obj:
            decl = f"{sname} {N}"
        else:
            vol = " volatile" if re.search(r"\*\s*volatile", olddecl) else ""
            decl = f"{sname} *{vol}{N}".replace("*volatile", "* volatile ").replace("  ", " ")
        newtexts = {}
        bad = {}
        for rel in live:
            if rel == hrel:
                continue
            try:
                ft = live[rel][0]
                views = [ft.nodes[nid].name for (r, nid) in mg.classes[0].nodes if r == rel]
                newtexts[rel] = phase2(rel, done[rel][3], ft, aliases, fmap, N, obj,
                                       views, sname if mode == "keep" else None)
            except Exception as e:  # noqa: BLE001
                bad[rel] = f"phase 2: {e}"
        if bad:
            for r, why in bad.items():
                log(f"  drop {r}: {why}")
            excluded.update(bad)
            continue
        if mode == "keep":
            deps = set(deps) | header_deps(oldhdr)
        hdr = new_header(N, oldhdr, defs, deps, decl, mode)
        if os.environ.get("S27_DEBUG"):
            dd = L.SCR / "dbg" / N
            dd.mkdir(parents=True, exist_ok=True)
            (dd / "hdr.h").write_text(hdr)
            for rel, t in newtexts.items():
                (dd / Path(rel).name).write_text(t)
        saved = {rel: (ROOT / rel).read_text() for rel in users}
        hpath.write_text(hdr)
        for rel, t in newtexts.items():
            (ROOT / rel).write_text(t)
        try:
            res = check_all(list(users), N, olddecl, newtexts, decl, mode == "full")
        except BaseException:
            restore(saved, hpath, oldhdr)
            raise
        failed = {r: why for r, why in res.items() if why != "SAME" and r in newtexts}
        others = {r: why for r, why in res.items() if why != "SAME" and r not in newtexts}
        if others:
            for r, why in others.items():
                log(f"  other user {r}: {why[:300]}")
            restore(saved, hpath, oldhdr)
            return None
        if failed:
            for r, why in failed.items():
                log(f"  drop {r}: {why[:300]}")
            excluded.update(failed)
            restore(saved, hpath, oldhdr)
            continue
        if mode == "keep" and len(newtexts) < 2:
            log("  keep mode folds one file only: not worth a shared type")
            restore(saved, hpath, oldhdr)
            return None
        if not apply:
            restore(saved, hpath, oldhdr)
        return newtexts, hdr, mode
    return None


def header_deps(hdr):
    return {i for i in re.findall(r'#include "([^"]+)"', hdr) if i != "common.h" and i != "m2c.h"} | (
        {"m2c.h"} if "m2c.h" in hdr else set())


def restore(saved, hpath, oldhdr):
    for rel, t in saved.items():
        (ROOT / rel).write_text(t)
    hpath.write_text(oldhdr)


def check_all(rels, N, olddecl, newtexts, newdecl, fix=True):
    """-S check of every user against HEAD; users not folded that fail get plain_fix casts"""
    res = {}

    def one(rel):
        b_asm, b_d = L.head_compile(rel)
        n_asm, n_d = L.compile_s(rel)
        ok = n_asm is not None and L.same_asm(n_asm, b_asm) and not (L.warnings(n_d) - L.warnings(b_d))
        if ok:
            return rel, "SAME"
        if rel not in newtexts and fix:
            t = (ROOT / rel).read_text()
            for lv in (False, True):
                try:
                    t2 = plain_fix(t, N, olddecl, newdecl, lv)
                except Exception as e:  # noqa: BLE001
                    return rel, f"plain_fix: {e}"
                n_asm, n_d = L.compile_s(rel, t2)
                ok = n_asm is not None and L.same_asm(n_asm, b_asm) and not (L.warnings(n_d) - L.warnings(b_d))
                if ok:
                    (ROOT / rel).write_text(t2)
                    newtexts_plain[rel] = t2
                    return rel, "SAME"
        if n_asm is None:
            return rel, "NOCOMPILE " + "; ".join(f"{a}: {b}" for a, b in n_d)[:300]
        if not L.same_asm(n_asm, b_asm):
            return rel, "CODE"
        return rel, "WARN " + "; ".join(sorted(L.warnings(n_d) - L.warnings(b_d)))[:300]
    with ThreadPoolExecutor(3) as ex:
        for rel, r in ex.map(one, rels):
            res[rel] = r
    return res


newtexts_plain = {}

if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
