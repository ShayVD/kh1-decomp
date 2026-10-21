#!/usr/bin/env python3
"""Unify the users' declarations of one "users disagree" data piece (session 25).

  python3 -I s25_unify.py ROOT D_X 'TYPE DECL' [--inc data/types/x.h] [--apply]

Writes include/data/pieces/D_X.h with `extern TYPE DECL;`. Each C file that
names D_X: its file-scope extern(s) of D_X are replaced by an include of that
header in place (a multi-name extern line loses just that name; the include goes
on the next line). The -S output of each changed file must be identical to the
original's and it must give no new warning; otherwise nothing is changed.
"""
import argparse, hashlib, json, os, re, subprocess, sys, tempfile
from pathlib import Path

ROOT = None
recipes = {}
CACHE = Path(os.environ.get("S25_DIR", "/tmp/s25types") + "/cache")


def setup(root):
    global ROOT
    ROOT = Path(root)
    sys.path.insert(0, str(ROOT / "tools")); sys.path.insert(0, str(ROOT / "tools/shift"))
    mk = (ROOT / "out/gen/objects.mk").read_text().split("\n\n")
    for blk in mk:
        m = re.match(r"out/build/(src/\S+\.c)\.o:", blk)
        if m:
            for ln in blk.splitlines():
                if "-S -x c" in ln:
                    recipes[m.group(1)] = ln.strip().lstrip("@").split(" && ")[0]
    CACHE.mkdir(parents=True, exist_ok=True)


def split_top(s: str, sep: str = ",") -> list:
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


def compile_s(rel: str, text: str, cache=False):
    key = None
    if cache:
        key = CACHE / (hashlib.sha1((rel + "\0" + text).encode()).hexdigest() + ".json")
        if key.exists():
            d = json.loads(key.read_text())
            return d["asm"], d["warn"]
    cmd = recipes[rel]
    with tempfile.TemporaryDirectory() as td:
        src = ROOT / rel
        tmp = src.with_name(".s25tmp_" + src.name)
        tmp.write_text(text)
        try:
            c = cmd.replace("$(TOOLCHAIN)", "tools/toolchain").replace("$(INCLUDES)", "-Iinclude -Isrc")
            c = c.replace("$(@:.o=.s)", f"{td}/o.s").replace(" " + rel, " " + str(tmp.relative_to(ROOT)))
            r = subprocess.run(c, shell=True, cwd=ROOT, capture_output=True, text=True)
            asm = Path(td, "o.s").read_text() if r.returncode == 0 else None
        finally:
            tmp.unlink()
    warn = sorted(set(re.sub(r"^[^:]*:\d+: ", "", l) for l in r.stderr.splitlines()
                      if "warning" in l or "error" in l))
    if key and asm is not None:
        key.write_text(json.dumps(dict(asm=asm, warn=warn)))
    return asm, warn


def strip_name(line: str, name: str):
    """line without name's declarator; '' when it was the only one; None if not understood."""
    m = re.match(r"^(extern\s+)(.*?);(\s*(/\*.*\*/|//.*)?)$", line)
    if not m:
        return None
    items = split_top(m.group(2))
    dm = re.match(r"^((?:(?:const|volatile|unsigned|signed|struct|union|enum)\s+)*[A-Za-z_]\w*)\s+(.*)$", items[0])
    if not dm:
        return None
    tspec, decls = dm.group(1), [dm.group(2)] + items[1:]
    keep = [d for d in decls if not re.search(r"\b" + name + r"\b", d)]
    if len(keep) != len(decls) - 1:
        return None
    if not keep:
        return ""
    return f"{m.group(1)}{tspec} {', '.join(keep)};{m.group(3)}"


def users(N):
    files = {}
    for p in sorted((ROOT / "src").rglob("*.c")):
        rel = str(p.relative_to(ROOT))
        if rel.startswith(("src/sdk/", "src/data/")) or p.name.startswith("."):
            continue
        t = p.read_text()
        if re.search(r"\b" + N + r"\b", t):
            files[rel] = t
    return files


def header_text(N, decls, incs, note=""):
    return "\n".join([
        f"/* The data piece {N} (src/data/data_{int(N[2:], 16) >> 16:04X}.s): one declaration its users",
        " * share (phase 4, session 25: the users' own types unified). */" if not note else f" * share (phase 4, session 25: {note}). */",
        f"#ifndef KH1_DATA_PIECES_{N}_H", f"#define KH1_DATA_PIECES_{N}_H", "", '#include "common.h"'] +
        (['#include "m2c.h"'] if any("M2C_UNK" in d for d in decls) else []) + [f'#include "{i}"' for i in incs] +
        [""] + [f"extern {d};" for d in decls] + ["", f"#endif /* KH1_DATA_PIECES_{N}_H */", ""])


def try_unify(N, decl, incs=(), apply=False, edits=None, note=""):
    """edits: {rel: [(old, new)]} extra textual edits (code-equivalent) in users.
    Returns (ok, [(rel, why)], nusers)."""
    HDR = ROOT / "include/data/pieces" / f"{N}.h"
    INC = f'#include "data/pieces/{N}.h"'
    if HDR.exists():
        return False, [("-", "header exists")], 0
    files = users(N)
    HDR.write_text(header_text(N, [decl], incs, note))
    fail, new = [], {}
    try:
        for rel, t in files.items():
            out, done, why = [], False, ""
            for ln in t.split("\n"):
                if ln.startswith("extern") and re.search(r"\b" + N + r"\b", ln):
                    s = strip_name(ln, N)
                    if s is None:
                        why = f"not understood: {ln}"; break
                    if s:
                        out.append(s)
                    if not done:
                        out.append(INC); done = True
                    continue
                out.append(ln)
            if why:
                fail.append((rel, why)); continue
            if not done:
                fail.append((rel, "no file-scope extern")); continue
            nt = "\n".join(out)
            if edits and rel in edits:
                nt = edits[rel](nt)
            if why:
                fail.append((rel, why)); continue
            if rel not in recipes:
                fail.append((rel, "not built")); continue
            b_asm, b_warn = compile_s(rel, t, cache=True)
            n_asm, n_warn = compile_s(rel, nt)
            if n_asm is None:
                fail.append((rel, "does not compile: " + " / ".join(n_warn)[:300])); continue
            if n_asm != b_asm:
                fail.append((rel, "code changes")); continue
            nw = [w for w in n_warn if w not in b_warn]
            if nw:
                fail.append((rel, "new warning: " + " / ".join(nw)[:300])); continue
            new[rel] = nt
    finally:
        if fail or not apply:
            HDR.unlink()
    if fail:
        return False, fail, len(files)
    if apply:
        for rel, nt in new.items():
            (ROOT / rel).write_text(nt)
        mod = ROOT / f"src/data/data_{int(N[2:], 16) >> 16:04X}.s"
        st = mod.read_text()
        pat = re.compile(r"(PIECE(?:_BEGIN)?\s+" + N + r",[^/\n]*)/\* untyped: users disagree[^\n]*?\*/")
        st, k = pat.subn(lambda m: m.group(1) + f"/* data/pieces/{N}.h */", st, count=1)
        if not k:
            print(f"note not found for {N}", file=sys.stderr)
        mod.write_text(st)
    return True, [], len(new)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("root"); ap.add_argument("name"); ap.add_argument("decl")
    ap.add_argument("--inc", action="append", default=[])
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    setup(a.root)
    ok, fail, n = try_unify(a.name, a.decl, a.inc, a.apply)
    for rel, why in fail:
        print(f"FAIL\t{a.name}\t{rel}\t{why}")
    if ok:
        print(f"OK\t{a.name}\t{n} users\t{a.decl}")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
