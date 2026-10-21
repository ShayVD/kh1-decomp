#!/usr/bin/env python3
"""-S check of hand edits against HEAD (session 26).

  python3 -I tools/shift/s26types/s26_check.py [FILE.c ...]

Each file (default: every src/**.c that differs from HEAD) is compiled with its
objects.mk recipe (`-S`) as it is in HEAD (cached) and as it is now; prints
SAME / CODE / NOCOMPILE / WARN per file and exits 1 unless all are SAME.
With S26_KEEP=1 a changed file's two .s go to $S26_DIR/keep/.
"""
import subprocess, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import s26_cast as C  # noqa: E402

ROOT = C.ROOT


def main():
    files = sys.argv[1:]
    if not files:
        out = subprocess.run(["git", "diff", "--name-only", "HEAD", "--", "src"], cwd=ROOT,
                             capture_output=True, text=True).stdout.split()
        files = [f for f in out if f.endswith(".c")]
    files = [str(Path(f).resolve().relative_to(ROOT)) if Path(f).is_absolute() else f for f in files]
    old = {f: subprocess.run(["git", "show", f"HEAD:{f}"], cwd=ROOT, capture_output=True, text=True).stdout
           for f in files}
    new = {f: (ROOT / f).read_text() for f in files}

    def one(f):
        b_asm, b_warn = C.compile_s(f, old[f], cache=True)
        n_asm, n_warn = C.compile_s(f, new[f])
        if n_asm is None:
            return f, "NOCOMPILE " + " / ".join(n_warn)[:600]
        if n_asm != b_asm:
            import os
            if os.environ.get("S26_KEEP"):
                kd = C.SCR / "keep"; kd.mkdir(exist_ok=True)
                (kd / (Path(f).name + ".old.s")).write_text(b_asm)
                (kd / (Path(f).name + ".new.s")).write_text(n_asm)
            return f, "CODE"
        nw = [w for w in n_warn if w not in b_warn]
        if nw:
            return f, "WARN " + " / ".join(nw)[:600]
        return f, "SAME"
    bad = 0
    with ThreadPoolExecutor(3) as ex:
        for f, r in ex.map(one, files):
            print(f"{r.split()[0]:9} {f} {r[len(r.split()[0]):].strip()}")
            bad += r != "SAME"
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
