#!/usr/bin/env python3
"""Second pass (session 25): struct/pointer targets, and casts in src/auto/ users.
  python3 -I s25_drive2.py ROOT survey.json [--apply] [--no-struct] [--log F] [D_X ...]

For each piece still "users disagree", try targets from the users' own declarations
(hand files first). A src/auto/ user whose declaration differs keeps its code: each
use of the name becomes a cast to the type it declared (`(*(s32 *)&D_X)`,
`((u8 *)&D_X)`), the same lvalue/value as before; s25_unify checks the -S output.
Hand users only get the declaration. A struct type local to the chosen file moves
to include/data/types/ (type_pieces.move_types, `_pN.h` when the header exists)."""
import json, os, re, sys, time
from collections import Counter
from pathlib import Path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import s25_unify as U

root, surv = sys.argv[1], sys.argv[2]
apply = "--apply" in sys.argv
no_struct = "--no-struct" in sys.argv
names = [x for x in sys.argv[3:] if x.startswith("D_")]
U.setup(root)
ROOT = U.ROOT
import type_pieces as TP  # noqa (path set by setup)
from define_shared import user_decl  # noqa

BASIC = {"s8": 1, "u8": 1, "char": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "f32": 4, "int": 4,
         "M2C_UNK": 4, "s64": 8, "u64": 8, "f64": 8, "void": 0, "unsigned": 4}


def base_of(tspec):
    t = [x for x in tspec.split() if x not in ("volatile", "const", "struct", "union", "signed")]
    if t == ["unsigned"]:
        return "unsigned"
    t = [x for x in t if x != "unsigned"] or ["unsigned"]
    return t[0] if len(t) == 1 else None


def norm_decl(tspec, decl):
    return re.sub(r"\s+", " ", f"{tspec} {decl}").strip()


def cast_edit(N, tspec, decl):
    m = re.fullmatch(r"(\**)\s*" + N + r"\s*((?:\[[^\]]*\])*)", decl)
    if not m:
        return None
    ptr, dims = m.groups()
    ds = re.findall(r"\[([^\]]*)\]", dims)
    if not ds:
        OT = tspec + (" " + ptr if ptr else "")
        addr, val = f"(({OT} *)&{N})", f"(*({OT} *)&{N})"
    else:
        if len(ds) == 1:
            PT = f"{tspec} {ptr}*"
        else:
            PT = f"{tspec} {ptr}(*)" + "".join(f"[{d}]" for d in ds[1:])
        addr, val = None, f"(({PT})&{N})"

    def f(text):
        out = []
        for ln in text.split("\n"):
            if ln.lstrip().startswith("#"):
                out.append(ln); continue
            if addr:
                ln = re.sub(r"(?<![\w&)\]])&\s*" + N + r"\b", "\0A\0", ln)
            elif re.search(r"(?<![\w&)\]])&\s*" + N + r"\b", ln):
                raise ValueError("address of an array user")
            ln = re.sub(r"\b" + N + r"\b", "\0V\0", ln)
            ln = ln.replace("\0A\0", addr or "").replace("\0V\0", val)
            out.append(ln)
        return "\n".join(out)
    return f


def candidates(p):
    N, size = p["name"], p["size"]
    cnt, info = Counter(), {}
    for u in p["users"]:
        if not u["decl"]:
            continue
        tspec, decl = u["decl"]
        b = base_of(tspec)
        if not b or b == "M2C_UNK":
            continue
        if b in BASIC:
            kind, where = "basic", None
        else:
            if no_struct:
                continue
            kind, where = TP.type_home(u["fn"], b)
            if kind is None:
                continue
        d = decl
        mm = re.fullmatch(r"(\**)\s*(D_[0-9A-F]{8})\s*\[\]((?:\[[^\]]*\])*)", decl)
        if mm and kind == "basic" and not mm.group(1):
            inner = 1
            for x in re.findall(r"\[([^\]]*)\]", mm.group(3)):
                inner *= int(x, 0)
            el = BASIC[b] * inner
            if el and size % el == 0:
                d = f"{N}[{size // el:#x}]{mm.group(3)}"
        key = norm_decl(tspec, d)
        w = 3 if u["fn"].startswith("src/hand/") else 1
        cnt[key] += w
        info.setdefault(key, (tspec, d, kind, where, u["fn"], b))
    return [info[k] for k, _ in cnt.most_common()]


def attempt(p, cand, do_apply):
    N = p["name"]
    tspec, d, kind, where, src, tname = cand
    target = f"{tspec} {d}"
    snap = {}
    incs = []
    created = []
    if kind == "local":
        srcp = ROOT / src
        snap[srcp] = srcp.read_text()
        before = set((ROOT / "include/data/types").glob("*.h"))
        try:
            inc = TP.move_types(srcp, [tname])
        except Exception as e:  # noqa
            srcp.write_text(snap[srcp])
            for h in set((ROOT / "include/data/types").glob("*.h")) - before:
                h.unlink()
            return False, [(src, f"type move: {e}")]
        created = list(set((ROOT / "include/data/types").glob("*.h")) - before)
        a0, _ = U.compile_s(src, snap[srcp], cache=True)
        a1, _ = U.compile_s(src, srcp.read_text())
        if a0 != a1:
            srcp.write_text(snap[srcp]); [h.unlink() for h in created]
            return False, [(src, "type move changes code")]
        incs = [inc]
    elif kind == "header":
        incs = [where]
    edits = {}
    tn = norm_decl(tspec, d)
    for u in p["users"]:
        fn = u["fn"]
        if not fn.startswith("src/auto/"):
            continue
        ud, _ = user_decl(ROOT / fn, N, repeat=True)
        if not ud:
            continue
        if norm_decl(*ud) == tn or (ud[0] in ("M2C_UNK", "s32") and tn == f"s32 {N}"):
            continue
        ce = cast_edit(N, ud[0], ud[1])
        if ce:
            edits[fn] = ce
    try:
        ok, fail, n = U.try_unify(N, target, incs, apply=do_apply, edits=edits)
    except ValueError as e:
        ok, fail = False, [("-", str(e))]
    if not ok or not do_apply:
        for f, t in snap.items():
            f.write_text(t)
        for h in created:
            h.unlink()
    return ok, fail


data = json.load(open(surv))
logp = next((sys.argv[i + 1] for i, x in enumerate(sys.argv) if x == "--log"), os.environ.get("S25_DIR", "/tmp/s25types") + "/drive2.log")
log = open(logp, "a")
for p in data:
    N = p["name"]
    if names and N not in names:
        continue
    mod = ROOT / f"src/data/data_{int(N[2:], 16) >> 16:04X}.s"
    if not re.search(r"PIECE(?:_BEGIN)?\s+" + N + r",[^\n]*users disagree", mod.read_text()):
        continue  # done already
    t0 = time.time()
    res, tried = None, []
    for cand in candidates(p)[:5]:
        ok, fail = attempt(p, cand, False)
        tried.append((f"{cand[0]} {cand[1]}", fail))
        if ok:
            res = cand
            break
    if res and apply:
        ok, fail = attempt(p, res, True)
        assert ok, fail
    msg = f"{N}\t{'OK ' + res[0] + ' ' + res[1] + ' (' + res[2] + ')' if res else 'NO'}\t{time.time()-t0:.0f}s"
    if not res:
        for dd, fail in tried:
            msg += f"\n   {dd}: " + "; ".join(f"{r} {w}" for r, w in fail[:5])
        if not tried:
            msg += "\n   no candidate"
    print(msg, flush=True)
    print(msg, file=log, flush=True)
