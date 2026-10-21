#!/usr/bin/env python3
"""C types for untyped data pieces (phase 4, session 24).

  python3 -I tools/shift/type_pieces.py [--note "untyped: merged"] [--name D_X ...]
                                        [--exclude D_X ...] [--apply]

A piece (src/data/data_XXXX.s) whose comment says "untyped" has no shared
declaration: its C users each declare their own extern. For each such piece
(the PIECE_BEGIN name and, for a merged piece, every PIECE_LABEL inside it)
this picks one declaration among the users' file-scope externs:

  - the largest (sizeof, probed in the user's own file; an incomplete array
    `T D[]` counts as one element), never larger than what is left of the
    piece from that name on;
  - then a real type before M2C_UNK, a complete type before an incomplete
    array, a hand file before an auto one, the declaration more files use.

The piece's own name, chosen as `T D[]`, is declared `T D[size / sizeof T]`
when that divides (compatible with `T D[]`, and it says how big the piece is).

A struct type the chosen file defines itself moves to include/data/types/
(tools/shift/type_move.py; into a second header <stem>_p.h when that file's
header exists already, so no header other files include grows),
a type an included header defines is used through that header. The
declarations go to include/data/pieces/D_X.h, one new header per piece (no
file included it before, so nothing that compiled stops compiling; one header
per module clashed with twice as many users); a piece whose declarations need
type headers that clash gets D_X_2.h and so on. Each header must compile on
its own.

A user whose extern declares the name exactly as chosen includes the header at
its end (after all code, like define_shared.py), when the file still compiles
with it; it keeps its own extern, which the compiler now checks against the
shared one. Types emit no code: `make` must stay byte-identical.

The piece's comment loses "untyped" when its own name got a declaration
(a merged piece keeps "merged (...)"); a piece whose name no C user declares
keeps it, saying so.

Without --apply only the plan is printed. Nothing here reads game bytes."""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/shift"))
from define_vars import CC, probe_sizes  # noqa: E402
from define_shared import BASIC, compiles_with, user_decl  # noqa: E402
import type_move  # noqa: E402

LINE_RE = re.compile(r"^\s*(PIECE|PIECE_BEGIN|PIECE_LABEL)\s+(D_[0-9A-F]{8})\s*,\s*(\S+?)\s*,\s*(\S+?)\s*(/\*.*\*/)?\s*$")
SHARED = "include/data/types/shared.h"
SHARED_TYPES = {"u128", "PppMtx"}


def module(addr: int) -> str:
    return f"data_{addr >> 16:04X}"


def read_pieces(note: str):
    """[(module path, head, size, note, [(label, off)])] of the pieces whose comment has note."""
    out = []
    for src in sorted((ROOT / "src/data").glob("data_*.s")):
        cur = None
        for ln in src.read_text().splitlines():
            m = LINE_RE.match(ln)
            if not m:
                continue
            if m.group(1) in ("PIECE", "PIECE_BEGIN"):
                cur = None
                if note in (m.group(5) or ""):
                    cur = [src, m.group(2), int(m.group(3), 0), m.group(5), []]
                    out.append(cur)
            elif cur and m.group(1) == "PIECE_LABEL":
                cur[4].append((m.group(3), int(m.group(4), 0)))
    return out


def base_name(tspec: str) -> str:
    t = re.sub(r"\b(const|volatile|struct|union|enum)\b", " ", tspec).split()
    return " ".join(t)


def c_files() -> dict[str, str]:
    out = {}
    for p in sorted((ROOT / "src").rglob("*.c")):
        rel = str(p.relative_to(ROOT))
        if rel.startswith(("src/sdk/", "src/data/")):
            continue
        out[rel] = p.read_text(errors="replace")
    return out


def type_home(fn: str, tname: str):
    """Where fn gets type tname from: ('basic', None), ('local', fn) when fn defines it at
    file scope, ('header', include path) when one of its includes does, else (None, why)."""
    if tname in BASIC or tname in ("u64", "s64", "f64"):
        return "basic", None
    if tname in SHARED_TYPES:
        return "header", "data/types/shared.h"
    src = ROOT / fn
    text = src.read_text()
    b = type_move.blank_comments(text)
    for st, en, kind, _c in type_move.statements(text):
        if kind == "decl" and tname in type_move.defines(b[st:en])[0]:
            return "local", fn
    for inc in re.findall(r'^\s*#\s*include\s+"([^"]+)"', text, re.M):
        h = ROOT / "include" / inc
        if h.exists() and tname in type_move.header_types(h):
            return "header", inc
    return None, f"type {tname} not found at file scope in {fn} or its headers"


def plan(note: str, names: list[str], exclude: set[str]):
    pieces = [p for p in read_pieces(note) if (not names or p[1] in names) and p[1] not in exclude]
    files = c_files()
    rows = []  # (piece, name, off, room)
    for p in pieces:
        rows.append((p, p[1], 0, p[2]))
        for lab, off in p[4]:
            rows.append((p, lab, off, p[2] - off))
    wanted = {r[1] for r in rows}
    mentions: dict[str, list[str]] = {}
    for fn, text in files.items():
        for n in set(re.findall(r"\bD_[0-9A-F]{8}\b", text)) & wanted:
            mentions.setdefault(n, []).append(fn)
    decls: dict[str, dict[tuple, list]] = {}
    probe: dict[str, dict[str, str]] = {}
    for _p, n, _o, _r in rows:
        ds: dict[tuple, list] = {}
        for fn in mentions.get(n, []):
            d, _why = user_decl(ROOT / fn, n, repeat=True)
            if d:
                ds.setdefault(d, []).append(fn)
                probe.setdefault(fn, {})[n] = f"{n}[0]" if "[]" in d[1] else n
        decls[n] = ds
    sizes: dict[tuple[str, str], int] = {}
    for fn, exprs in probe.items():
        try:
            got = probe_sizes(ROOT / fn, exprs)
        except RuntimeError:
            got = {}
        for n, sz in got.items():
            sizes[(fn, n)] = sz
    declared: dict[str, str] = {}  # names include/data/data_XXXX.h declares already
    for h in (ROOT / "include/data").glob("data_[0-9A-F][0-9A-F][0-9A-F][0-9A-F].h"):
        for n in re.findall(r"^extern .*?\b(D_[0-9A-F]{8})\b", h.read_text(), re.M):
            declared[n] = f"data/{h.name}"
    out = []
    for p, n, off, room in rows:
        if n in declared:
            out.append(dict(piece=p, name=n, off=off, header=declared[n], existing=True))
            continue
        cands = []
        for (tspec, decl), fns in decls[n].items():
            sz = max((sizes.get((fn, n), 0) for fn in fns), default=0)
            if not sz or sz > room:
                continue
            complete = "[]" not in decl
            fn = sorted(fns, key=lambda f: (not f.startswith("src/hand/"), f.count("/"), f))[0]
            score = (sz, base_name(tspec) != "M2C_UNK", complete, fn.startswith("src/hand/"), len(fns))
            cands.append((score, tspec, decl, fn, fns))
        if not cands:
            why = "no C user declares it" if not decls[n] else "no declaration fits"
            out.append(dict(piece=p, name=n, off=off, why=why))
            continue
        cands.sort(key=lambda c: c[0], reverse=True)
        score, tspec, decl, fn, fns = cands[0]
        kind, where = type_home(fn, base_name(tspec))
        if kind is None:
            out.append(dict(piece=p, name=n, off=off, why=where))
            continue
        hdecl = decl
        if off == 0 and decl.endswith("[]") and decl.count("[") == 1 and room % score[0] == 0:
            hdecl = decl[:-2] + f"[{room // score[0]:#x}]"
        out.append(dict(piece=p, name=n, off=off, tspec=tspec, decl=decl, hdecl=hdecl, src=fn, users=fns,
                        size=score[0], kind=kind, where=where, tname=base_name(tspec),
                        others=sum(len(c[4]) for c in cands[1:]) + sum(
                            len(v) for k, v in decls[n].items() if k not in {(c[1], c[2]) for c in cands})))
    return out


def move_types(src: Path, types: list[str]) -> str:
    """Move types to src's include/data/types header. When that header exists (an earlier
    move), the types go to a second one, <stem>_p.h, that includes the first: a header
    other files include already must not grow (a bss_XXXX_typed.h that includes two of
    them could see a type twice). Returns the include path."""
    hdr = type_move.header_path(src)
    stem = type_move.header_name(src)
    take, info = type_move.plan(src, sorted(types))
    if take is None:
        raise RuntimeError(f"type_move {src}: {info}")
    if not hdr.exists():
        type_move.apply(src, take, info)
        return f"data/types/{stem}.h"
    stem2 = stem + "_p"
    hdr2 = hdr.with_name(stem2 + ".h")
    if hdr2.exists():
        raise RuntimeError(f"{hdr2} exists")
    text = src.read_text()
    incs = []
    for ln in text.splitlines():
        m = re.match(r'\s*#\s*include\s+[<"]([^>"]+)[>"]', ln)
        if m and (ROOT / "include" / m.group(1)).exists() and (not m.group(1).startswith("data/")
                                                                    or m.group(1).startswith("data/types/")):
            incs.append(f'#include "{m.group(1)}"')
    incs = list(dict.fromkeys(incs + [f'#include "data/types/{stem}.h"']))
    body = [text[info[k][0]:info[k][1]] for k in take]
    guard = "KH1_DATA_TYPES_" + re.sub(r"\W", "_", stem2).upper() + "_H"
    rel = src.relative_to(ROOT)
    hdr2.write_text("\n".join(
        [f"/* More types moved from {rel} (phase 4, session 24, tools/shift/type_pieces.py). */",
         f"#ifndef {guard}", f"#define {guard}", ""] + incs + [""] + body + ["", f"#endif /* {guard} */", ""]))
    out = text
    for k in reversed(take):
        st, en = info[k][0], info[k][1]
        ls = out.rfind("\n", 0, st) + 1
        le = out.find("\n", en)
        le = len(out) if le < 0 else le
        whole = out[ls:st].strip() == "" and out[en:le].strip() == ""
        rep = f'#include "data/types/{stem2}.h"' if k == take[0] else ""
        if whole:
            out = out[:ls] + (rep + "\n" if rep else "") + out[le + 1:]
        else:
            out = out[:st] + rep + out[en:]
    src.write_text(out)
    return f"data/types/{stem2}.h"


def header_ok(path: Path) -> bool:
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / "t.c"
        p.write_text(f'#include "{path.relative_to(ROOT / "include")}"\n')
        r = subprocess.run([str(CC), "-fsyntax-only", "-x", "c", "-O2", "-G0", f"-I{ROOT/'include'}", str(p)],
                           capture_output=True, text=True)
        if r.returncode:
            print(r.stderr[-1500:], file=sys.stderr)
        return r.returncode == 0


def write_header(path: Path, piece: str, incs: list[str], decls: list[str]) -> None:
    guard = "KH1_DATA_PIECES_" + re.sub(r"\W", "_", path.stem).upper() + "_H"
    m2c = any(re.search(r"\bM2C_UNK", d) for d in decls)
    mod = module(int(piece[2:], 16))
    h = [f"/* The data piece {piece} (src/data/{mod}.s) and the names inside it: one",
         " * declaration per name, the largest a user makes (phase 4, session 24,",
         " * tools/shift/type_pieces.py). Users that agree include this at their end;",
         " * the others keep their own extern. */",
         f"#ifndef {guard}", f"#define {guard}", "", '#include "common.h"']
    h += ['#include "m2c.h"'] if m2c else []
    h += [f'#include "{i}"' for i in sorted(set(incs))]
    h += [""] + sorted(decls, key=lambda d: re.search(r"D_([0-9A-F]{8})", d).group(1)) + \
         ["", f"#endif /* {guard} */", ""]
    path.write_text("\n".join(h))


def apply(rows) -> None:
    typed = [r for r in rows if "tspec" in r]
    # 1. types
    moves: dict[str, set] = {}
    for r in typed:
        if r["kind"] == "local":
            moves.setdefault(r["src"], set()).add(r["tname"])
    for fn, ts in sorted(moves.items()):
        inc = move_types(ROOT / fn, sorted(ts))
        print(f"types\t{fn}\t{inc}\t{' '.join(sorted(ts))}", file=sys.stderr)
        for r in typed:
            if r["kind"] == "local" and r["src"] == fn:
                r["kind"], r["where"] = "header", inc
    # 2. headers, greedy: a declaration whose type header clashes goes to the next one
    by_mod: dict[str, list] = {}  # one header per piece (a module-wide one clashes with more users)
    for r in typed:
        by_mod.setdefault(r["piece"][1], []).append(r)
    (ROOT / "include/data/pieces").mkdir(exist_ok=True)
    for mod, rs in sorted(by_mod.items()):
        heads: list[tuple[Path, list, list, list]] = []  # path, incs, decls, rows
        for r in sorted(rs, key=lambda r: r["name"]):
            d = f"extern {r['tspec']} {r['hdecl']};"
            inc = [r["where"]] if r["kind"] == "header" else []
            placed = False
            for k, (path, incs, decls, hr) in enumerate(heads):
                write_header(path, mod, incs + inc, decls + [d])
                if header_ok(path):
                    incs += inc
                    decls.append(d)
                    hr.append(r)
                    placed = True
                    break
                write_header(path, mod, incs, decls)
            if not placed:
                path = ROOT / "include/data/pieces" / f"{mod}{'' if not heads else '_' + str(len(heads) + 1)}.h"
                write_header(path, mod, inc, [d])
                if not header_ok(path):
                    print(f"refused\t{r['name']}\t{d}: header does not compile", file=sys.stderr)
                    path.unlink()
                    r["why"] = f"its declaration does not compile on its own ({d})"
                    del r["tspec"]
                    continue
                heads.append((path, inc, [d], [r]))
        for path, _i, _d, hr in heads:
            for r in hr:
                r["header"] = f"data/pieces/{path.name}"
    # 3. users
    users: dict[str, set] = {}
    for r in rows:
        if "tspec" not in r:
            continue
        for fn in r["users"]:
            users.setdefault(fn, set()).add(r["header"])
    for fn, hs in sorted(users.items()):
        path = ROOT / fn
        for inc in sorted(hs):
            text = path.read_text()
            if f'#include "{inc}"' in text:
                continue
            if compiles_with(path, inc):
                path.write_text(text + ("" if text.endswith("\n") else "\n") + f'#include "{inc}"\n')
                print(f"include\t{fn}\t{inc}", file=sys.stderr)
            else:
                print(f"keep\t{fn}\t{inc}", file=sys.stderr)
    # 4. the comments in src/data
    heads_done = {r["piece"][1]: r for r in rows if r["off"] == 0}
    by_src: dict[Path, list] = {}
    for r in heads_done.values():
        by_src.setdefault(r["piece"][0], []).append(r)
    for src, rs in by_src.items():
        text = src.read_text()
        for r in rs:
            old = r["piece"][3]
            if "tspec" in r or r.get("existing"):
                new = old.replace("/* untyped: merged", "/* merged").replace("/* untyped: ", "/* was untyped: ") \
                    if "untyped: merged" in old else ""
                new = new.replace(" */", f"; {r['header']} */") if new else f"/* {r['header']} */"
            else:
                inner = [x for x in rows if x["piece"] is r["piece"] and x["off"] and "header" in x]
                tail = f"; labels in {inner[0]['header']}" if inner else ""
                base = "merged" if "untyped: merged" in old else old[len("/* untyped: "):-3]
                new = f"/* untyped: {r['why']} ({base}){tail} */" if "merged" in base else \
                    f"/* untyped: {r['why']} (was: {base}){tail} */"
            pat = re.compile(r"(\b" + r["name"] + r",[^/\n]*)" + re.escape(old))
            text, k = pat.subn(lambda m: m.group(1) + new, text, count=1)
            if not k:
                print(f"note not found for {r['name']}", file=sys.stderr)
        src.write_text(text)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--note", default="untyped: merged")
    ap.add_argument("--name", action="append", default=[])
    ap.add_argument("--exclude", action="append", default=[])
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    rows = plan(a.note, a.name, set(a.exclude))
    for r in rows:
        if r.get("existing"):
            print(f"{r['piece'][1]}\t+{r['off']:#x}\t{r['name']}\t(declared in {r['header']})")
        elif "tspec" in r:
            print(f"{r['piece'][1]}\t+{r['off']:#x}\t{r['name']}\t{r['tspec']} {r['hdecl']}\t{r['size']:#x}\t"
                  f"{r['kind']}:{r['where']}\t{r['src']}\t{len(r['users'])} agree, {r['others']} other")
        else:
            print(f"{r['piece'][1]}\t+{r['off']:#x}\t{r['name']}\t-\t{r['why']}")
    heads = [r for r in rows if r["off"] == 0]
    ok = lambda r: "tspec" in r or r.get("existing")  # noqa: E731
    print(f"# {len(heads)} pieces: {sum(1 for r in heads if ok(r))} with a declaration "
          f"({sum(1 for r in heads if r.get('existing'))} in data_XXXX.h already); "
          f"{sum(1 for r in rows if r['off'] and ok(r))} of {sum(1 for r in rows if r['off'])} labels",
          file=sys.stderr)
    if a.apply:
        apply(rows)
    return 0


if __name__ == "__main__":
    sys.exit(main())
