#!/usr/bin/env python3
"""Why files stayed unfolded: summary of the s27_batch logs (session 27).

  python3 -I tools/shift/s27types/s27_reasons.py [--per-piece] [D_X ...]   (default: every log in $S27_DIR/batch)

Reads the last mode tried in each piece's log and counts the reasons by kind.
"""
import re, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import s27lib as L  # noqa: E402

KINDS = [
    (r"overlaps", "overlap: a field overlaps another user's field differently"),
    (r"has the file's own type", "field of a local type that is not a struct (or not found)"),
    (r"is a union", "view is (or contains) a union"),
    (r"sits in two different places", "one local type in two places of the merged layout"),
    (r"phase 1: no field use found", "phase 1: field access hidden (macro / multi-line)"),
    (r"phase 1:", "phase 1: other"),
    (r"phase 2: used field", "phase 2: a used field has no merged field"),
    (r"phase 2:", "phase 2: other"),
    (r": CODE", "-S code changes"),
    (r": WARN", "new warning"),
    (r"NOCOMPILE", "does not compile"),
    (r"not a local struct typedef|probe", "view type not local / probe failed"),
]


def main(argv):
    per = "--per-piece" in argv
    names = [a for a in argv if a.startswith("D_")]
    logs = [L.SCR / "batch" / f"{n}.log" for n in names] if names else sorted((L.SCR / "batch").glob("*.log"))
    tot = Counter()
    for lg in logs:
        if not lg.exists():
            continue
        t = lg.read_text()
        parts = t.split("  -- mode ")
        body = parts[0] + (parts[-1] if len(parts) > 1 else "")
        c = Counter()
        for ln in body.splitlines():
            if not re.match(r"\s+(drop|skip|other user)", ln):
                continue
            for pat, k in KINDS:
                if re.search(pat, ln):
                    c[("other user " if "other user" in ln else "") + k] += 1
                    break
        tot += c
        if per and c:
            print(lg.stem, dict(c))
    for k, v in tot.most_common():
        print(f"{v:5} {k}")


if __name__ == "__main__":
    main(sys.argv[1:])
