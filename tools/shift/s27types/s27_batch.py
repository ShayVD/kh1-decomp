#!/usr/bin/env python3
"""Run s27_fold.py over several pieces, one after another (session 27).

  python3 -I tools/shift/s27types/s27_batch.py [--apply] D_X ...   (or --from FILE with one name per line)

Each piece's log goes to $S27_DIR/batch/D_X.log; prints one summary line per piece.
"""
import re, subprocess, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import s27lib as L  # noqa: E402


def main(argv):
    apply = "--apply" in argv
    names = [a for a in argv if a.startswith("D_")]
    if "--from" in argv:
        names += Path(argv[argv.index("--from") + 1]).read_text().split()
    out = L.SCR / "batch"
    out.mkdir(exist_ok=True)
    for N in names:
        cmd = [sys.executable, "-I", str(Path(__file__).with_name("s27_fold.py"))] + (["--apply"] if apply else []) + [N]
        r = subprocess.run(cmd, cwd=L.ROOT, capture_output=True, text=True)
        (out / f"{N}.log").write_text(r.stdout + r.stderr)
        ok = re.search(r"OK (\(\w+\)): (\d+) files folded", r.stdout)
        nv = re.search(r"(\d+) files with struct views", r.stdout)
        print(f"{N}\t{"OK " + ok.group(1) + " " + ok.group(2) if ok else "FAIL"}\tof {nv.group(1) if nv else '?'}"
              f"\t{(r.stderr.strip().splitlines() or [''])[-1][:120]}", flush=True)


if __name__ == "__main__":
    main(sys.argv[1:])
