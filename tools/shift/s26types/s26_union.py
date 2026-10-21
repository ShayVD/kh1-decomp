#!/usr/bin/env python3
"""Unify a "users disagree" data piece as a union of its users' views (session 26).

  python3 -I tools/shift/s26types/s26_union.py [--apply] [--cast F ...] D_X

include/data/pieces/D_X.h gets one member type per distinct view and
`typedef union { ... } U_X; extern U_X D_X;`. Each user picks its member:
`D_X` becomes `D_X.<member>` in its code (an array view `s32 D_X[]` becomes the
member `s32 i[n]`, a struct view `E20 D_X[]` the member `E20_X e20[size / sizeof]`,
a pointer view `Grid *D_X` the member `Grid_X *grid`). A struct view's type must
be self-contained (only common.h types); its copy in the header gets a unique name
(`<T>_<addr>`) and the user's own typedef becomes `typedef <T>_<addr> <T>;` at the
same place (the typedef statement in the file, or in a data/types header only that
file includes), so the user's type *is* the shared member type. Users that cannot
take a member (`--cast F`, or a view whose type is not self-contained) keep their
code through s26_cast's casts. Accepted only if every changed file's -S is
identical with no new warning; the result names the users that failed.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import s26_cast as C  # noqa: E402

ROOT = C.ROOT
sys.path.insert(0, str(ROOT / "tools/shift"))
import type_move as TM  # noqa: E402

COMMON = {"u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64", "u128", "s128", "M2C_UNK"}
MEMB = {"s32": "i", "int": "i", "M2C_UNK": "i", "u32": "u", "f32": "f", "u8": "b", "s8": "c", "char": "c",
        "u16": "h", "s16": "sh", "u64": "d", "s64": "sd", "void": "v"}


def find_typedef(rel, text, tname):
    """(where, path, start, end, stmt): the statement defining tname in the file or in a
    data/types header that only this file includes."""
    b = TM.blank_comments(text)
    for st, en, kind, cond in TM.statements(text):
        if kind == "decl" and not cond and tname in TM.defines(b[st:en])[0]:
            return "file", ROOT / rel, st, en, text[st:en]
    for inc in re.findall(r'^\s*#\s*include\s+"(data/types/[^"]+)"', text, re.M):
        h = ROOT / "include" / inc
        if not h.exists():
            continue
        ht = h.read_text()
        hb = TM.blank_comments(ht)
        for st, en, kind, cond in TM.statements(ht):
            if kind == "decl" and not cond and tname in TM.defines(hb[st:en])[0]:
                n = 0
                for p in (ROOT / "src").rglob("*.c"):
                    if f'"{inc}"' in p.read_text(errors="replace"):
                        n += 1
                for p in (ROOT / "include").rglob("*.h"):
                    if p != h and f'"{inc}"' in p.read_text(errors="replace"):
                        n += 2
                if n != 1:
                    return None
                return "header", h, st, en, ht[st:en]
    return None


def self_contained(stmt, tname):
    b = TM.blank_comments(stmt)
    names, tags = TM.uses(b)
    # identifiers in type position: a word followed by a declarator start
    types = set(re.findall(r"(?:^|[{;,]\s*)(?:(?:const|volatile|unsigned|signed)\s+)*([A-Za-z_]\w*)\s+[*A-Za-z_(]",
                           re.sub(r"^\s*typedef\s+(struct|union)\s*\w*\s*", "", b)))
    bad = {t for t in types if t not in COMMON and t not in TM.KEYWORDS and t != tname}
    if tags - set(TM.defines(b)[1]):
        bad |= {"struct " + t for t in tags - set(TM.defines(b)[1])}
    if len(TM.defines(b)[0]) != 1:
        bad.add("several typedef names")
    return bad


def plan(N, cast_users=()):
    size, _ = C.piece_info(N)
    files = C.c_text_users(N)
    views, users, why = [], {}, {}
    vkey = {}
    for rel, t in files.items():
        ds = C.user_decls(t, N)
        if ds is None:
            why[rel] = "extern not understood"; continue
        if not ds:
            if not C.names_it(t, N):
                continue
            why[rel] = "no extern"; continue
        kinds = {(ts, d) for _, _, ts, d in ds}
        if len(kinds) != 1:
            why[rel] = "externs disagree"; continue
        ts, d = next(iter(kinds))
        if rel in cast_users:
            users[rel] = ("cast", (ts, d)); continue
        b = C.base_of(ts)
        dd = d.replace(" ", "")
        m = re.fullmatch(r"(\**)" + N + r"((?:\[[^\]]*\])*)", dd)
        if not m or b is None:
            users[rel] = ("cast", (ts, d)); continue
        ptr, dims = m.groups()
        if b in C.BASIC or b in COMMON:
            d2 = C.fill(ts, d, size).replace(" ", "")
            if "[]" in d2:
                users[rel] = ("cast", (ts, d)); continue
            mname = MEMB.get(b, b.lower()) + ("p" * len(ptr))
            key = norm_view(ts, d2.replace(N, "@"))
            view = dict(key=key, mname=mname, decl=f"{ts} {d2.replace(N, mname)}", stmt=None, tname=None)
        else:
            ft = find_typedef(rel, t, b)
            if not ft:
                users[rel] = ("cast", (ts, d)); continue
            where, path, st, en, stmt = ft
            am = re.fullmatch(r"\s*typedef\s+(\w+)\s+" + b + r"\s*;\s*", stmt)
            if am and pieces_type(am.group(1)):
                X = am.group(1)
                mname = b[0].lower() + b[1:]
                view = dict(key=("alias", X, ptr, dims), mname=mname, decl=member_decl(X, mname, ptr, dims, size),
                            stmt=None, tname=None, inc=pieces_type(X))
                if view["key"] in vkey:
                    view = dict(vkey[view["key"]])
                else:
                    vkey[view["key"]] = view
                    views.append(view)
                users[rel] = ("member", view)
                continue
            bad = self_contained(stmt, b)
            if bad:
                users[rel] = ("cast", (ts, d)); continue
            body = re.sub(r"\s+", " ", TM.blank_comments(stmt))
            key = (body.replace(b, "@T"), ptr, dims)
            mname = b[0].lower() + b[1:]
            uniq = f"{b}_{N[2:].lstrip('0')}"
            if not ptr and dims:
                ds_ = re.findall(r"\[([^\]]*)\]", dims)
                if ds_[0] == "":
                    inner = "".join(f"[{x}]" for x in ds_[1:])
                    mdecl = f"{uniq} {mname}[{size:#x} / sizeof({uniq}{inner and ' ' + inner})]{inner}"
                    if inner:
                        mdecl = f"{uniq} {mname}[{size:#x} / sizeof({uniq}){'' if not inner else ' / (' + ' * '.join(ds_[1:]) + ')'}]{inner}"
                else:
                    mdecl = f"{uniq} {mname}{dims}"
            else:
                mdecl = f"{uniq} {ptr}{mname}"
            vol = "volatile " if "volatile" in ts.split() else ""
            view = dict(key=key, mname=mname, decl=vol + mdecl, stmt=stmt, tname=b, uniq=uniq,
                        where=(where, path, st, en))
        if view["key"] in vkey:
            v0 = vkey[view["key"]]
            if view.get("tname") and v0.get("tname") != view.get("tname"):
                pass  # same layout, another local name: alias to v0's type
            view = dict(view, mname=v0["mname"], decl=v0["decl"], uniq=v0.get("uniq"), shared_from=v0)
        else:
            names = {v["mname"] for v in views}
            k = 2
            base = view["mname"]
            while view["mname"] in names:
                view["mname"] = f"{base}{k}"; k += 1
            if view["mname"] != base:
                view["decl"] = re.sub(r"\b" + base + r"\b(?=\s*[\[;]|$)", view["mname"], view["decl"])
                view["decl"] = view["decl"].replace(f" {base}[", f" {view['mname']}[").replace(f"*{base}", f"*{view['mname']}")
            if view.get("tname") and view["uniq"] in {v.get("uniq") for v in views}:
                view["uniq"] = view["uniq"] + f"_{len(views)}"
                view["decl"] = re.sub(r"^(volatile )?\w+", lambda m: (m.group(1) or "") + view["uniq"], view["decl"])
            vkey[view["key"]] = view
            views.append(view)
        users[rel] = ("member", view)
    return size, files, views, users, why


def pieces_type(X):
    """the include path of the pieces header that defines type X (a member type), or None"""
    for h in (ROOT / "include/data/pieces").glob("*.h"):
        if re.search(r"\b" + X + r"\s*;", h.read_text()) and re.search(r"^typedef .*\b" + X + r";", h.read_text(), re.M):
            return f"data/pieces/{h.name}"
    return None


def member_decl(uniq, mname, ptr, dims, size):
    if not ptr and dims:
        ds_ = re.findall(r"\[([^\]]*)\]", dims)
        inner = "".join(f"[{x}]" for x in ds_[1:])
        if ds_[0] == "":
            div = "" if not ds_[1:] else " / (" + " * ".join(ds_[1:]) + ")"
            return f"{uniq} {mname}[{size:#x} / sizeof({uniq}){div}]{inner}"
        return f"{uniq} {mname}{dims}"
    return f"{uniq} {ptr}{mname}"


def norm_view(ts, d):
    return (C.norm(ts.replace("M2C_UNK", "s32")), d)


def header(N, views):
    U = "U" + N[2:]
    lines = [f"/* The data piece {N} (src/data/data_{int(N[2:], 16) >> 16:04X}.s): one declaration its users",
             " * share (phase 4, session 26: a union of the users' views; each user names its member). */",
             f"#ifndef KH1_DATA_PIECES_{N}_H", f"#define KH1_DATA_PIECES_{N}_H", "", '#include "common.h"']
    if any("M2C_UNK" in v["decl"] for v in views):
        lines.append('#include "m2c.h"')
    for i in sorted({v["inc"] for v in views if v.get("inc")}):
        lines.append(f'#include "{i}"')
    lines.append("")
    for v in views:
        if v.get("stmt"):
            st = v["stmt"].strip()
            k = st.rfind("}")
            st = st[:k] + re.sub(r"\b" + v["tname"] + r"\b", v["uniq"], st[k:])
            lines.append(st)
    lines.append(f"typedef union {{ " + " ".join(v["decl"] + ";" for v in views) + f" }} {U};")
    lines += ["", f"extern {U} {N};", "", f"#endif /* KH1_DATA_PIECES_{N}_H */", ""]
    return "\n".join(lines)


def edit(N, rel, text, kind, info, INC):
    ds = C.user_decls(text, N)
    if kind == "cast":
        return C.edit_user(N, text, ds, ("U" + N[2:], N), INC), {}
    view = info
    lines = text.split("\n")
    extra = {}
    # extern lines out (keep other names)
    drop = {}
    for i, ind, ts, d in ds:
        _, tspec0, dl, k = C.parse_line(lines[i], N)
        keep = [x for j, x in enumerate(dl) if j != k]
        if keep:
            m = re.match(r"^(\s*extern\s+)(.*?);(\s*(/\*.*\*/|//.*)?)$", lines[i])
            first = C.split_top(m.group(2))[0]
            dm = re.match(r"^" + C.TSPEC + r"\s*(.*)$", first)
            drop[i] = f"{m.group(1)}{dm.group(1)} {', '.join(keep)};{m.group(3)}"
        else:
            drop[i] = None
    if view.get("tname"):
        where, path, st, en = view["where"]
        alias = f"typedef {view['uniq']} {view['tname']};"
        if where == "file":
            # the typedef statement becomes the include + an alias
            ln_st = text.count("\n", 0, st)
            new_text = text[:st] + INC + "\n" + alias + text[en:]
            lines = new_text.split("\n")
            shift = new_text.count("\n") - text.count("\n")
            drop = {(i + shift if i > ln_st else i): v for i, v in drop.items()}
            out = [ln if i not in drop else drop[i] for i, ln in enumerate(lines)]
            out = [x for x in out if x is not None]
        else:
            ht = path.read_text()
            extra[path] = ht[:st] + INC + "\n" + alias + ht[en:]
            out = [ln if i not in drop else drop[i] for i, ln in enumerate(lines)]
            out = [x for x in out if x is not None]
    else:
        out = []
        done = False
        for i, ln in enumerate(lines):
            if i in drop:
                if drop[i] is not None:
                    out.append(drop[i])
                if not done and not ds[[x[0] for x in ds].index(i)][1]:
                    out.append(INC); done = True
                continue
            out.append(ln)
        if not done:
            raise ValueError("only block-scope externs")
    t2 = "\n".join(out)
    return member_uses(t2, N, view["mname"]), extra


def member_uses(text, N, mname):
    ml = C.macro_lines(text, N)
    out, last = [], 0
    for a, b in C.code_spans(text):
        out.append(text[last:a])
        seg = text[a:b]
        seg2, k = [], 0
        for m in re.finditer(r"\b" + N + r"\b", seg):
            if text.count("\n", 0, a + m.start()) in ml:
                continue
            seg2.append(seg[k:m.end()] + "." + mname)
            k = m.end()
        seg2.append(seg[k:])
        out.append("".join(seg2))
        last = b
    out.append(text[last:])
    return "".join(out)


def run(N, cast_users=(), apply=False):
    INC = f'#include "data/pieces/{N}.h"'
    HDR = ROOT / "include/data/pieces" / f"{N}.h"
    if HDR.exists():
        return ["header exists"], []
    size, files, views, users, why = plan(N, cast_users)
    if why:
        return [f"{r}: {w}" for r, w in why.items()], []
    new, extras = {}, {}
    for rel, (kind, info) in users.items():
        try:
            nt, ex = edit(N, rel, files[rel], kind, info, INC)
        except Exception as e:  # noqa
            return [f"{rel}: edit {e}"], []
        new[rel] = nt
        extras.update(ex)
    HDR.write_text(header(N, views))
    snap = {p: p.read_text() for p in extras}
    for p, t in extras.items():
        p.write_text(t)
    try:
        fail = C.check_files(new, files)
    finally:
        if fail or not apply:
            HDR.unlink()
            for p, t in snap.items():
                p.write_text(t)
    if fail:
        return [f"{r}: {w}" for r, w in fail], users
    if apply:
        for rel, nt in new.items():
            (ROOT / rel).write_text(nt)
        C.mark_done(N)
    return [], users


def main():
    a = sys.argv[1:]
    apply = "--apply" in a
    a = [x for x in a if x != "--apply"]
    casts = []
    while "--cast" in a:
        i = a.index("--cast"); casts.append(a[i + 1]); del a[i:i + 2]
    for N in a:
        cu = list(casts)
        for it in range(6):
            fail, users = run(N, cu, apply=False)
            if not fail:
                break
            print(f"{N} try {it}: " + "; ".join(f[:200] for f in fail), flush=True)
            more = [f.split(":")[0] for f in fail if f.startswith("src/") and f.split(":")[0] not in cu
                    and users and users.get(f.split(":")[0], ("x",))[0] == "member"]
            if not more:
                break
            cu += more
        if fail:
            print(f"{N}\tNO", flush=True)
            continue
        if apply:
            f2, _ = run(N, cu, apply=True)
            assert not f2, f2
        print(f"{N}\tOK union, cast users: {', '.join(cu) or '-'}", flush=True)


if __name__ == "__main__":
    main()
