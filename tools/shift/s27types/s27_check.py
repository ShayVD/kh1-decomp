#!/usr/bin/env python3
"""-S check of the work tree against HEAD (session 27).

  python3 -I tools/shift/s27types/s27_check.py [FILE.c ...]

Default files: every src .c that differs from HEAD, plus every .c that includes
(directly or through other headers) a header under include/ or src/ that differs
from HEAD or is new.  Each is compiled with its objects.mk recipe in the work tree
and in an export of HEAD (cached per HEAD sha); prints SAME / CODE / NOCOMPILE /
WARN per file; exit 1 unless all are SAME.  S27_KEEP=1 keeps changed .s files in
$S27_DIR/keep/.
"""
import os, re, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import s27lib as L  # noqa: E402

ROOT = L.ROOT


def includers(headers):
    """.c files under src/ that include any of `headers` (paths relative to ROOT), transitively"""
    texts = {}
    for p in list((ROOT / "src").rglob("*.[ch]")) + list((ROOT / "include").rglob("*.h")):
        if p.name.startswith("."):
            continue
        texts[str(p.relative_to(ROOT))] = p.read_text(errors="replace")
    inc_re = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)
    deps = {f: set(inc_re.findall(t)) for f, t in texts.items()}

    def keys(h):  # the include spellings that can name header h
        ks = {h}
        for pre in ("include/", "src/"):
            if h.startswith(pre):
                ks.add(h[len(pre):])
        ks.add(Path(h).name)
        return ks
    todo, seen, out = list(headers), set(), set()
    while todo:
        h = todo.pop()
        if h in seen:
            continue
        seen.add(h)
        ks = keys(h)
        for f, d in deps.items():
            if d & ks:
                if f.endswith(".c"):
                    out.add(f)
                else:
                    todo.append(f)
    return out


def default_files():
    changed = L.git("diff", "--name-only", "HEAD", "--", "src", "include").split()
    changed += L.git("ls-files", "--others", "--exclude-standard", "--", "src", "include").split()
    cs = {f for f in changed if f.endswith(".c") and (ROOT / f).exists()}
    hs = [f for f in changed if f.endswith(".h")]
    if hs:
        cs |= includers(hs)
    return sorted(f for f in cs if f in L.recipes())


def one(f):
    b_asm, b_d = L.head_compile(f)
    n_asm, n_d = L.compile_s(f)
    if b_asm is None:
        return f, "BASEFAIL " + " / ".join(f"{l}: {m}" for l, m in b_d)[:400]
    if n_asm is None:
        return f, "NOCOMPILE " + " / ".join(f"{l}: {m}" for l, m in n_d)[:800]
    if not L.same_asm(n_asm, b_asm):
        if os.environ.get("S27_KEEP"):
            kd = L.SCR / "keep"; kd.mkdir(exist_ok=True)
            (kd / (Path(f).name + ".old.s")).write_text(b_asm or "")
            (kd / (Path(f).name + ".new.s")).write_text(n_asm)
        return f, "CODE"
    nw = L.warnings(n_d) - L.warnings(b_d)
    if nw:
        return f, "WARN " + " / ".join(sorted(nw))[:800]
    return f, "SAME"


def main():
    files = sys.argv[1:] or default_files()
    L.head_tree()
    bad = 0
    with ThreadPoolExecutor(3) as ex:
        for f, r in ex.map(one, files):
            if r != "SAME" or os.environ.get("S27_VERBOSE"):
                print(f"{r.split()[0]:9} {f} {r[len(r.split()[0]):].strip()}")
            bad += r != "SAME"
    print(f"# {len(files)} files, {bad} not SAME")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
