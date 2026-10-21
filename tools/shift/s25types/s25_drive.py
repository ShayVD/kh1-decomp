#!/usr/bin/env python3
"""Try basic-type unifications for every "users disagree" piece (session 25).
  python3 -I s25_drive.py ROOT survey.json [--apply] [--name D_X ...]"""
import json, os, re, sys, time
from collections import Counter
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import s25_unify as U

root, surv = sys.argv[1], sys.argv[2]
apply = "--apply" in sys.argv
names = [x for x in sys.argv[3:] if x.startswith("D_")]
U.setup(root)
BASIC = {"s8": 1, "u8": 1, "char": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "f32": 4, "int": 4,
         "M2C_UNK": 4, "s64": 8, "u64": 8, "f64": 8, "void": 0, "unsigned": 4}


def tinfo(tspec, decl):
    toks = tspec.split()
    vol = "volatile" in toks
    base = [t for t in toks if t not in ("volatile", "const", "unsigned", "signed")] or ["unsigned"]
    if len(base) != 1 or base[0] not in BASIC:
        return None
    return base[0], vol


def fill(tspec, decl, size):
    """T D[] -> T D[n]; returns decl string or None"""
    b = tinfo(tspec, decl)
    if not b:
        return None
    m = re.fullmatch(r"(\**)\s*(D_[0-9A-F]{8})\s*((?:\[[^\]]*\])*)", decl)
    if not m:
        return None
    ptr, n, dims = m.groups()
    el = 4 if ptr else BASIC[b[0]]
    if el == 0:
        return None
    ds = re.findall(r"\[([^\]]*)\]", dims)
    inner = 1
    for d in ds[1:]:
        try:
            inner *= int(d, 0)
        except ValueError:
            return None
    if ds and ds[0] == "":
        if size % (el * inner):
            return None
        ds[0] = hex(size // (el * inner))
    tot = el * inner * (int(ds[0], 0) if ds else 1)
    if tot > size:
        return None
    return f"{ptr}{n}" + "".join(f"[{d}]" for d in ds)


data = json.load(open(surv))
log = open(os.environ.get("S25_DIR", "/tmp/s25types") + "/drive.log", "a")
for p in data:
    N, size = p["name"], p["size"]
    if names and N not in names:
        continue
    cnt = Counter()
    vol = False
    for u in p["users"]:
        if not u["decl"]:
            continue
        tspec, decl = u["decl"]
        if "volatile" in tspec.split():
            vol = True
        if not tinfo(tspec, decl) or tinfo(tspec, decl)[0] == "M2C_UNK":
            continue
        f = fill(tspec, decl, size)
        if f:
            w = 2 if u["fn"].startswith("src/hand/") else 1
            cnt[(tspec, f)] += w
    cands = [k for k, _ in cnt.most_common()]
    if vol:
        cands = [(t if "volatile" in t.split() else "volatile " + t, d) for t, d in cands]
        cands = list(dict.fromkeys(cands))
    m2c_users = [u["fn"] for u in p["users"] if u["decl"] and u["decl"][0] == "M2C_UNK" and u["decl"][1] == N]
    def mk_edits(d):
        if "[" not in d and "*" not in d:
            return None
        pat = re.compile(r"(?<![&\w])&\s*" + N + r"\b")
        return {fn: (lambda t: pat.sub("(M2C_UNK *)&" + N, t)) for fn in m2c_users}
    res = None
    t0 = time.time()
    tried = []
    for tspec, d in cands[:4]:
        ok, fail, n = U.try_unify(N, f"{tspec} {d}", apply=False, edits=mk_edits(d))
        tried.append((f"{tspec} {d}", fail))
        if ok:
            res = f"{tspec} {d}"
            break
    if res and apply:
        ok, fail, n = U.try_unify(N, res, apply=True, edits=mk_edits(res))
        assert ok, fail
    msg = f"{N}\t{'OK ' + res if res else 'NO'}\t{time.time()-t0:.0f}s"
    if not res:
        for dd, fail in tried:
            msg += f"\n   {dd}: " + "; ".join(f"{r} {w}" for r, w in fail[:4])
        if not tried:
            msg += "\n   no basic candidate"
    print(msg, flush=True)
    print(msg, file=log, flush=True)
