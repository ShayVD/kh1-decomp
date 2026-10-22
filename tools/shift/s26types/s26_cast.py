#!/usr/bin/env python3
"""Unify a "users disagree" data piece with casts in every user (session 26).

  python3 -I tools/shift/s26types/s26_cast.py survey  [D_X ...]   > /tmp/s26types/survey.txt
  python3 -I tools/shift/s26types/s26_cast.py try     [--apply] [--decl 'T D_X'] [--inc h] D_X ...

One shared declaration goes to include/data/pieces/D_X.h. Every C user (hand and
auto) includes it in place of its own extern (file scope or block scope); a user
whose declaration differs keeps its code through casts at each use of the name:
`D_X` becomes `(*(T (*)...)&D_X)` (the lvalue it declared) and `&D_X` becomes
`((T (*)...)&D_X)`. Accepted only when every changed file's -S output is identical
and no new warning appears (same check as s25_unify). Candidates: the users' own
declarations (hand x3, types that are basic, in a header the user includes, or
local to the user and movable with type_pieces.move_types), then basic fallbacks
(`void *` for pointer pieces, `s32 [n]`, `u8 [n]`).
"""
import hashlib, json, os, re, subprocess, sys, tempfile, threading
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools")); sys.path.insert(0, str(ROOT / "tools/shift"))
SCR = Path(os.environ.get("S26_DIR", "/tmp/s26types"))
CACHE = SCR / "cache"
CACHE.mkdir(parents=True, exist_ok=True)
recipes = {}
for blk in (ROOT / "out/gen/objects.mk").read_text().split("\n\n"):
    m = re.match(r"out/build/(src/\S+\.c)\.o:", blk)
    if m:
        for ln in blk.splitlines():
            if "-S -x c" in ln:
                recipes[m.group(1)] = ln.strip().lstrip("@").split(" && ")[0]

BASIC = {"s8": 1, "u8": 1, "char": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "f32": 4, "int": 4,
         "M2C_UNK": 4, "s64": 8, "u64": 8, "f64": 8, "void": 0, "unsigned": 4, "short": 2, "long": 4,
         "float": 4, "double": 8, "u128": 16, "s128": 16}
TSPEC = r"((?:(?:const|volatile|unsigned|signed|struct|union|enum)\s+)*[A-Za-z_]\w*(?:\s+(?:const|volatile))*)"


def split_top(s, sep=","):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == sep and depth == 0:
            out.append(cur); cur = ""
        else:
            cur += ch
    out.append(cur)
    return [x.strip() for x in out]


def norm(s):
    return re.sub(r"\s+", " ", re.sub(r"\s*([\[\]*(),])\s*", r"\1", s)).strip()


ASM = re.compile(r'\s*__asm__\s*\(\s*"[^"]*"\s*\)')


def parse_line(line, N):
    """(indent, tspec, [decls], i) for an extern line declaring N, else None.
    `X __asm__("N")` names the symbol N under another C name: not a declaration of N;
    `N __asm__("N")` is N."""
    line = ASM.sub("", line)
    m = re.match(r"^(\s*)extern\s+(.*?);\s*(/\*.*\*/|//.*)?$", line)
    if not m:
        return None
    items = split_top(m.group(2))
    dm = re.match(r"^" + TSPEC + r"\s*(.*)$", items[0])
    if not dm or not dm.group(2):
        return None
    tspec, decls = norm(dm.group(1)), [dm.group(2)] + items[1:]
    hit = [i for i, d in enumerate(decls) if re.search(r"\b" + N + r"\b", d)]
    if len(hit) != 1:
        return None
    return m.group(1), tspec, decls, hit[0]


def strip_comments(t):
    t = re.sub(r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), t, flags=re.S)
    return re.sub(r"//[^\n]*", "", t)


def names_it(t, N):
    ml = macro_lines(t, N)
    lines = [ASM.sub("", ln) for i, ln in enumerate(strip_comments(t).split("\n")) if i not in ml]
    return any(re.search(r"\b" + N + r"\b", ln) for ln in lines)


def c_text_users(N):
    files = {}
    for p in sorted((ROOT / "src").rglob("*.c")):
        rel = str(p.relative_to(ROOT))
        if rel.startswith(("src/sdk/", "src/data/")) or p.name.startswith("."):
            continue
        t = p.read_text()
        if re.search(r"\b" + N + r"\b", t):
            files[rel] = t
    return files


def macro_lines(text, N):
    """line numbers from `#define N ...` to its `#undef N`: N there names another object"""
    out, on = set(), False
    for i, ln in enumerate(text.split("\n")):
        if re.match(r"\s*#\s*define\s+" + N + r"\b", ln):
            on = True
        if on:
            out.add(i)
        if re.match(r"\s*#\s*undef\s+" + N + r"\b", ln):
            on = False
    return out


def user_decls(text, N):
    """[(lineno, indent, tspec, decl)] of every extern of N; None if one is not understood."""
    out = []
    ml = macro_lines(text, N)
    for i, ln in enumerate(text.split("\n")):
        if i in ml:
            continue
        if re.search(r"\bextern\b", ln) and re.search(r"\b" + N + r"\b", ASM.sub("", ln)):
            p = parse_line(ln, N)
            if not p:
                return None
            ind, ts, ds, k = p
            out.append((i, ind, ts, norm(ds[k])))
    return out


def cast_types(N, tspec, decl):
    """(value form, address form) of N for a user that declared `tspec decl`."""
    d = decl.replace(" ", "")
    m = re.fullmatch(r"(\**)" + N + r"\[\](.*)", d)
    if m:  # T D[]...: the rvalue it decays to
        ptrs, rest = m.groups()
        PT = f"{tspec} {ptrs}*" if not rest else f"{tspec} {ptrs}(*){rest}"
        AT = f"{tspec} " + norm(re.sub(r"\b" + N + r"\b", "(*)", decl))
        return f"(({PT})&{N})", f"(({AT})&{N})"
    if re.fullmatch(r"\**" + N, d):
        stars = d[:-len(N)]
        PT = f"{tspec} {stars}*"
    else:
        PT = f"{tspec} " + norm(re.sub(r"\b" + N + r"\b", "(*)", decl))
    return f"(*({PT})&{N})", f"(({PT})&{N})"


def base_of(tspec):
    t = [x for x in tspec.split() if x not in ("volatile", "const", "struct", "union", "enum", "signed")]
    if not t:
        return None
    if all(x in ("unsigned", "short", "long", "int", "char") for x in t):
        return "s32" if t in (["unsigned"], ["int"], ["unsigned", "int"]) else t[-1]
    t = [x for x in t if x != "unsigned"]
    return t[0] if len(t) == 1 else None


def same(a, b):
    """two (tspec, decl) that need no cast between them"""
    ta, tb = a[0].replace("M2C_UNK", "s32"), b[0].replace("M2C_UNK", "s32")
    da, db = norm(a[1]), norm(b[1])
    if ta != tb:
        return False
    if da == db:
        return True
    # T D[] vs T D[n] (same inner dims)
    ra = re.sub(r"^(\**D_[0-9A-F]{8})\[[^\]]*\]", r"\1[]", da)
    rb = re.sub(r"^(\**D_[0-9A-F]{8})\[[^\]]*\]", r"\1[]", db)
    return ra == rb and "[" in da and "[" in db


def edit_user(N, text, decls, shared, INC):
    """New text: externs of N out (include at the first file-scope one, or after the
    last top #include), uses cast when the user's declaration differs."""
    lines = text.split("\n")
    kinds = {(ts, d) for _, _, ts, d in decls}
    if len(kinds) > 1:
        raise ValueError("externs disagree within the file")
    own = next(iter(kinds)) if kinds else None
    if own is None:
        raise ValueError("no extern")
    drop = {}
    for i, ind, ts, d in decls:
        p = parse_line(lines[i], N)
        _, tspec0, ds, k = p
        keep = [x for j, x in enumerate(ds) if j != k]
        if keep:
            m = re.match(r"^(\s*extern\s+)(.*?);(\s*(/\*.*\*/|//.*)?)$", lines[i])
            first = split_top(m.group(2))[0]
            dm = re.match(r"^" + TSPEC + r"\s*(.*)$", first)
            drop[i] = f"{m.group(1)}{dm.group(1)} {', '.join(keep)};{m.group(3)}"
        else:
            drop[i] = None
    fs = [i for i, ind, _, _ in decls if ind == ""]
    if fs:
        at = fs[0]
    else:
        incs = [i for i, ln in enumerate(lines) if re.match(r"\s*#\s*include", ln)]
        if not incs:
            raise ValueError("no include line")
        at = incs[-1]
    cast = not same(own, shared)
    out = []
    for i, ln in enumerate(lines):
        if i in drop:
            if drop[i] is not None:
                out.append(drop[i])
            if i == at:
                out.append(INC)
            continue
        out.append(ln)
        if i == at and i not in drop:
            out.append(INC)
    text = "\n".join(out)
    if cast:
        text = rewrite_uses(text, N, own, shared)
    return text


INTS = {"s8", "u8", "char", "s16", "u16", "s32", "u32", "int", "M2C_UNK", "unsigned", "short", "long"}


def scalar_int(tspec, decl):
    """a 4-byte int or pointer object (not array / function pointer): value casts are free"""
    d = decl.replace(" ", "")
    if "volatile" in tspec.split() or "volatile" in d:
        return False
    if re.fullmatch(r"\*+D_[0-9A-F]{8}", d):
        return True
    if re.fullmatch(r"D_[0-9A-F]{8}", d):
        return base_of(tspec) in ("s32", "u32", "int", "M2C_UNK", "unsigned", "long")
    return False


def code_spans(text):
    """[(start, end)] of text outside comments, string/char literals and #include lines"""
    spans, i, st, n = [], 0, 0, len(text)
    pat = re.compile(r'/\*|//|"|\'|^[ \t]*#[ \t]*include[^\n]*', re.M)
    while True:
        m = pat.search(text, i)
        if not m:
            spans.append((st, n))
            return spans
        spans.append((st, m.start()))
        tok = m.group(0)
        if tok == "/*":
            e = text.find("*/", m.end()); e = n if e < 0 else e + 2
        elif tok == "//":
            e = text.find("\n", m.end()); e = n if e < 0 else e
        elif tok in ('"', "'"):
            j = m.end()
            while j < n and text[j] != tok:
                j += 2 if text[j] == "\\" else 1
            e = min(j + 1, n)
        else:
            e = m.end()
        i = st = e


CASTEND = re.compile(r"\(\s*(?:(?:const|volatile|struct|union|unsigned|signed)\s+)*[A-Za-z_]\w*(?:\s*\*\s*(?:const|volatile)?)+\s*\)$"
                     r"|\(\s*(?:unsigned\s+)?(?:s8|u8|s16|u16|s32|u32|int|char|short|long|unsigned|M2C_UNK)\s*\)$")


def rewrite_uses(text, N, own, shared):
    """each use of N in code: the value/lvalue/address the user's own declaration gave"""
    pa_own = re.fullmatch(r"(\*+)" + N + r"\[[^\]]*\]", own[1].replace(" ", ""))
    pa_sh = re.fullmatch(r"(\*+)" + N + r"\[[^\]]*\]", shared[1].replace(" ", ""))
    if pa_own and pa_sh and "volatile" not in own[0] + shared[0]:
        return elem_casts(text, N, f"{own[0]} {pa_own.group(1)}")
    val, adr = cast_types(N, *own)
    rv = None
    if scalar_int(*own) and scalar_int(*shared):
        rv = f"(({own[0]} {own[1].replace(N, '').strip()}){N})".replace(" )", ")")
        if os.environ.get("S26_STORECAST", "1") == "1":
            text = store_casts(text, N, f"{shared[0]} {shared[1].replace(N, '').strip()}".strip())
    out, last = [], 0
    ml = macro_lines(text, N)
    for a, b in code_spans(text):
        out.append(text[last:a])
        seg = text[a:b]
        res, k = [], 0
        for m in re.finditer(r"\b" + N + r"\b", seg):
            pre = seg[k:m.start()]
            prev = (text[:a] + seg[:m.start()]).rstrip()
            after = seg[m.end():]
            if (text.count("\n", 0, a + m.start()) in ml
                    or re.search(r"#\s*(define|undef|ifdef|ifndef)\s+$", prev)):
                continue  # `#define N N_alias` ... `#undef N`: another object there
            if prev.endswith("&") and not prev.endswith("&&") and not re.match(r"\s*(\[|\.|->|\()", after):
                p2 = prev[:-1].rstrip()
                addr = (not p2 or p2[-1] in "(,=+-*/!~?:;{[<>|&^%" or re.search(r"\breturn$", p2)
                        or (p2.endswith(")") and CASTEND.search(p2)))
                if addr:
                    pr = pre.rstrip()
                    if not pr.endswith("&"):
                        raise ValueError("address-of across a span")
                    res.append(pr[:-1]); res.append(adr); k = m.end()
                    continue
            lval = (re.match(r"\s*(=(?!=)|\+\+|--|[-+*/%&|^]=|<<=|>>=)", after)
                    or prev.endswith("++") or prev.endswith("--"))
            res.append(pre)
            res.append(rv if rv and not lval else val)
            k = m.end()
        res.append(seg[k:])
        out.append("".join(res))
        last = b
    out.append(text[last:])
    return "".join(out).replace("\0K\0", N)


def elem_casts(text, N, ET):
    """pointer-array user of a pointer-array shared name: each element read converts
    its value (`((T *)N[i])`), a store `N[i] = v` stays (the pointer converts)"""
    ml = macro_lines(text, N)
    out, last = [], 0
    for a, b in code_spans(text):
        out.append(text[last:a])
        seg = text[a:b]
        res, k = [], 0
        for m in re.finditer(r"\b" + N + r"\b", seg):
            if m.start() < k or text.count("\n", 0, a + m.start()) in ml:
                continue
            j = m.end()
            mm = re.match(r"\s*\[", seg[j:])
            if not mm:
                continue  # the array itself (decays to a pointer): left as it is
            i, d = j + mm.end(), 1
            while i < len(seg) and d:
                d += seg[i] == "["
                d -= seg[i] == "]"
                i += 1
            if d:
                raise ValueError("unbalanced index")
            prev = seg[:m.start()].rstrip()
            post = re.match(r"\s*(->|\.|\[)", seg[i:])
            if prev.endswith("&") and not prev.endswith("&&") and not post:
                raise ValueError("address of an element")
            ref = seg[m.start():i]
            deref = prev.endswith("*") and (len(prev) < 2 or not re.match(r"[\w)\]]", prev[-2]))
            if not post and not deref and re.match(r"\s*(=(?!=)|\+\+|--|[-+*/%&|^]=|<<=|>>=)", seg[i:]):
                if not re.match(r"\s*=(?!=)", seg[i:]):
                    raise ValueError("compound store to an element")
                res.append(seg[k:m.start()] + ref)
            else:
                res.append(seg[k:m.start()] + f"(({ET.strip()}){ref})")
            k = i
        res.append(seg[k:])
        out.append("".join(res))
        last = b
    out.append(text[last:])
    return "".join(out)


def store_casts(text, N, ST):
    """`N = rhs;` statements -> `N = (ST)rhs;` with N hidden from the use rewrite
    (an int <-> pointer store through the shared type, no lvalue cast)."""
    def rep(m):
        rhs = m.group(3).strip()
        if re.search(r"\b" + N + r"\b", rhs) or "\n" in rhs:
            return m.group(0)
        d = 0
        for ch in rhs:
            d += ch == "("
            d -= ch == ")"
            if d < 0:
                return m.group(0)
        if d:
            return m.group(0)
        if re.fullmatch(r"-?(0x[0-9a-fA-F]+|\d+)", rhs):
            return f"{m.group(1)}\0K\0{m.group(2)}{rhs};"
        simple = re.fullmatch(r"[\w.]+(->\w+)*|\(.*\)", rhs) and not re.fullmatch(r"\([^()]*\)\s*\S.*", rhs)
        new = f"({ST}){rhs}" if simple else f"({ST})({rhs})"
        return f"{m.group(1)}\0K\0{m.group(2)}{new};"
    return re.sub(r"((?:^|[;{})])[ \t]*)" + N + r"(\s*=\s*)(?!=)([^;]*);", rep, text, flags=re.M)


_lock = threading.Lock()
NOTE = None


def compile_s(rel, text, cache=False):
    key = CACHE / (hashlib.sha1((recipes[rel] + "\0" + rel + "\0" + text).encode()).hexdigest() + ".json")
    if cache and key.exists():
        d = json.loads(key.read_text())
        return d["asm"], d["warn"]
    cmd = recipes[rel]
    with tempfile.TemporaryDirectory(dir=SCR) as td:
        src = ROOT / rel
        tmp = src.with_name(".s26tmp_" + src.name)
        tmp.write_text(text)
        try:
            c = cmd.replace("$(TOOLCHAIN)", "tools/toolchain").replace("$(INCLUDES)", "-Iinclude -Isrc")
            c = c.replace("$(@:.o=.s)", f"{td}/o.s").replace(" " + rel, " " + str(tmp.relative_to(ROOT)))
            r = subprocess.run(c, shell=True, cwd=ROOT, capture_output=True, text=True)
            asm = Path(td, "o.s").read_text() if r.returncode == 0 else None
        finally:
            tmp.unlink()
    warn = sorted(set(re.sub(r"^[^:]*:\d+: ", "", l) for l in r.stderr.splitlines()
                      if "warning" in l or "error" in l or asm is None))
    if cache and asm is not None:
        key.write_text(json.dumps(dict(asm=asm, warn=warn)))
    return asm, warn


def header_text(N, decl, incs):
    return "\n".join([
        f"/* The data piece {N} (src/data/data_{int(N[2:], 16) >> 16:04X}.s): one declaration its users",
        " * share (phase 4, session 26: users whose own type differs cast at each use). */",
        f"#ifndef KH1_DATA_PIECES_{N}_H", f"#define KH1_DATA_PIECES_{N}_H", "", '#include "common.h"'] +
        (['#include "m2c.h"'] if "M2C_UNK" in decl else []) + [f'#include "{i}"' for i in incs] +
        ["", f"extern {decl};", "", f"#endif /* KH1_DATA_PIECES_{N}_H */", ""])


def canon_labels(asm):
    """local labels ($L12, $LC3) renumbered by first appearance: gcc's label counter
    moves when a declaration changes, the assembled code does not"""
    seen = {}

    def rep(m):
        k = m.group(0)
        if k not in seen:
            seen[k] = f"{m.group(1)}#{len([x for x in seen if x.startswith(m.group(1))])}"
        return seen[k]
    return re.sub(r"(\$LC?)\d+\b", rep, asm)


def same_asm(a, b):
    """-S identical, or identical up to local label numbers (S26_STRICT=1: exact)"""
    if a == b:
        return True
    if os.environ.get("S26_STRICT") == "1" or a is None or b is None:
        return False
    return canon_labels(a) == canon_labels(b)


def check_files(new, files):
    """[(rel, why)] for files whose -S changes or warns anew."""
    def one(rel):
        if rel not in recipes:
            return rel, "not built"
        b_asm, b_warn = compile_s(rel, files[rel], cache=True)
        n_asm, n_warn = compile_s(rel, new[rel])
        if n_asm is None:
            if os.environ.get("S26_KEEP"):
                kd = SCR / "keep"; kd.mkdir(exist_ok=True); (kd / Path(rel).name).write_text(new[rel])
            return rel, "does not compile: " + " / ".join(n_warn)[:300]
        if not same_asm(n_asm, b_asm):
            if os.environ.get("S26_KEEP"):
                kd = SCR / "keep"; kd.mkdir(exist_ok=True)
                stem = Path(rel).name
                (kd / (stem + ".old.s")).write_text(b_asm); (kd / (stem + ".new.s")).write_text(n_asm)
                (kd / stem).write_text(new[rel])
            return rel, "code changes"
        nw = [w for w in n_warn if w not in b_warn]
        if nw:
            return rel, "new warning: " + " / ".join(nw)[:300]
        return None
    with ThreadPoolExecutor(int(os.environ.get("S27_JOBS", "2"))) as ex:
        return [r for r in ex.map(one, sorted(new)) if r]


def piece_info(N):
    mod = ROOT / f"src/data/data_{int(N[2:], 16) >> 16:04X}.s"
    m = re.search(r"PIECE(?:_BEGIN)?\s+" + N + r",\s*(0x[0-9a-fA-F]+|\d+)[^\n]*", mod.read_text())
    return int(m.group(1), 0), m.group(0)


def try_decl(N, tspec, decl, incs=(), apply=False):
    HDR = ROOT / "include/data/pieces" / f"{N}.h"
    INC = f'#include "data/pieces/{N}.h"'
    if HDR.exists():
        return [("-", "header exists")]
    files = c_text_users(N)
    shared = (tspec, decl)
    new, fail = {}, []
    for rel, t in files.items():
        ds = user_decls(t, N)
        if ds is None:
            fail.append((rel, "extern not understood")); continue
        if not ds and not names_it(t, N):
            continue  # only a comment, an __asm__ alias or a #define region names it
        try:
            new[rel] = edit_user(N, t, ds, shared, INC)
        except ValueError as e:
            fail.append((rel, str(e)))
    if fail:
        return fail
    HDR.write_text(header_text(N, f"{tspec} {decl}", incs))
    try:
        fail = check_files(new, files)
    finally:
        if fail or not apply:
            HDR.unlink()
    if fail:
        return fail
    if apply:
        for rel, nt in new.items():
            (ROOT / rel).write_text(nt)
        mark_done(N)
    return []


def mark_done(N):
    mod = ROOT / f"src/data/data_{int(N[2:], 16) >> 16:04X}.s"
    st = mod.read_text()
    pat = re.compile(r"(PIECE(?:_BEGIN)?\s+" + N + r",[^/\n]*)/\* untyped: users disagree[^\n]*?\*/")
    st, k = pat.subn(lambda m: m.group(1) + f"/* data/pieces/{N}.h */", st, count=1)
    if not k:
        print(f"note not found for {N}", file=sys.stderr)
    mod.write_text(st)


def fill(tspec, decl, size):
    b = base_of(tspec)
    el0 = BASIC.get(b) if b else None
    m = re.fullmatch(r"(\**)(D_[0-9A-F]{8})((?:\[[^\]]*\])*)", decl.replace(" ", ""))
    if not m:
        return decl
    ptr, n, dims = m.groups()
    ds = re.findall(r"\[([^\]]*)\]", dims)
    if not ds or ds[0] != "":
        return decl
    el = 4 if ptr else el0
    if not el:
        return decl
    inner = 1
    for x in ds[1:]:
        try:
            inner *= int(x, 0)
        except ValueError:
            return decl
    if size % (el * inner):
        return decl
    return f"{ptr}{n}[{size // (el * inner):#x}]" + "".join(f"[{x}]" for x in ds[1:])


def candidates(N):
    import type_pieces as TP
    size, _ = piece_info(N)
    files = c_text_users(N)
    cnt, info = Counter(), {}
    for rel, t in files.items():
        ds = user_decls(t, N) or []
        for ts, d in {(ts, d) for _, _, ts, d in ds}:
            b = base_of(ts)
            if b is None:
                continue
            if b in BASIC:
                kind, where = "basic", None
            else:
                kind, where = TP.type_home(rel, b)
                if kind is None:
                    continue
            d2 = fill(ts, d, size) if kind == "basic" else d
            key = norm(ts + " " + d2)
            cnt[key] += 3 if rel.startswith("src/hand/") else 1
            info.setdefault(key, (ts, d2, kind, where, rel, b))
    out = [info[k] for k, _ in cnt.most_common()]
    ptr = any(re.match(r"\*", d) for (_, d, *_r) in out)
    fb = []
    if size == 4 and ptr:
        fb.append(("void", f"*{N}", "basic", None, None, "void"))
    if size % 4 == 0:
        fb.append(("s32", f"{N}" if size == 4 else f"{N}[{size // 4:#x}]", "basic", None, None, "s32"))
    fb.append(("u8", f"{N}[{size:#x}]", "basic", None, None, "u8"))
    for f in fb:
        if norm(f[0] + " " + f[1]) not in info:
            out.append(f)
    return out


def attempt(N, cand, apply):
    import type_pieces as TP
    tspec, d, kind, where, src, tname = cand
    snap, created, incs = {}, [], []
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
            return [(src, f"type move: {e}")]
        created = list(set((ROOT / "include/data/types").glob("*.h")) - before)
        a0, _ = compile_s(src, snap[srcp], cache=True)
        a1, _ = compile_s(src, srcp.read_text())
        if a0 != a1:
            srcp.write_text(snap[srcp]); [h.unlink() for h in created]
            return [(src, "type move changes code")]
        incs = [inc]
    elif kind == "header":
        incs = [where]
    try:
        fail = try_decl(N, tspec, d, incs, apply)
    except Exception as e:  # noqa
        fail = [("-", f"error {e}")]
    if fail or not apply:
        for f, t in snap.items():
            f.write_text(t)
        for h in created:
            h.unlink()
    return fail


def main():
    a = sys.argv[1:]
    cmd = a.pop(0)
    apply = "--apply" in a
    a = [x for x in a if x != "--apply"]
    global NOTE
    decl = inc = None
    if "--note" in a:
        i = a.index("--note"); NOTE = a[i + 1]; del a[i:i + 2]
    if "--decl" in a:
        i = a.index("--decl"); decl = a[i + 1]; del a[i:i + 2]
    if "--inc" in a:
        i = a.index("--inc"); inc = a[i + 1]; del a[i:i + 2]
    names = a
    if not names:
        names = []
        for p in sorted((ROOT / "src/data").glob("*.s")):
            names += re.findall(r"PIECE(?:_BEGIN)?\s+(D_[0-9A-F]{8}),[^\n]*session 25: as", p.read_text())
    log = open(SCR / "try.log", "a")
    for N in names:
        if cmd == "survey":
            size, line = piece_info(N)
            print(f"== {N} size {size:#x}")
            for rel, t in c_text_users(N).items():
                ds = user_decls(t, N)
                print(f"   {rel}: " + (" | ".join(sorted({f'{ind and "(block) "}{ts} {d}' for _, ind, ts, d in ds})) if ds is not None else "NOT UNDERSTOOD"))
            continue
        if cmd == "hdr":  # hand-made unification: write the header, mark the piece; users by hand
            HDR = ROOT / "include/data/pieces" / f"{N}.h"
            t = header_text(N, decl, [inc] if inc else [])
            HDR.write_text(t.replace("users whose own type differs cast at each use", NOTE or "unified by hand"))
            mark_done(N)
            print(f"{N}\theader written")
            continue
        if decl:
            m = re.match(r"^" + TSPEC + r"\s*(.*)$", decl)
            cands = [(norm(m.group(1)), m.group(2), "header" if inc else "basic", inc, None, None)]
        else:
            cands = candidates(N)
        res, tried = None, []
        for c in cands[:6]:
            fail = attempt(N, c, False)
            tried.append((f"{c[0]} {c[1]}", fail))
            if not fail:
                res = c
                break
        if res and apply:
            fail = attempt(N, res, True)
            assert not fail, fail
        msg = f"{N}\t" + (f"OK {res[0]} {res[1]} ({res[2]})" if res else "NO")
        if not res:
            for dd, fail in tried:
                msg += f"\n   {dd}: " + "; ".join(f"{r} {w}" for r, w in fail[:6])
        print(msg, flush=True)
        print(msg, file=log, flush=True)


if __name__ == "__main__":
    main()
