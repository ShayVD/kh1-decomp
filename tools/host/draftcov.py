#!/usr/bin/env python3
"""Which of a native overlay's near-miss drafts a host run calls (session 142).

    python3 -I tools/host/draftcov.py gdb OVL > drafts.gdb
    KH1_HOST_... gdb -q -batch -x drafts.gdb out/host/kh1-host > run.log
    python3 -I tools/host/draftcov.py table OVL run.log

`gdb` writes a gdb script with a silent breakpoint on every function ovl/OVL/drafts.tsv lists (the
native module's names, OVL_xxxxxxxx) that prints `HIT name` and runs on; `table` counts the hits in the
run's output and prints, for each draft the run called: the function, the calls, the words its draft
differs by (drafts.tsv) and the draft's file, fewest words first. Those are the drafts a check against
PCSX2 has to cover for that route (docs/native-plan.md track A, "Near-miss drafts are not proven
correct"); docs/native-overlays.md keeps the list per route. Hot functions slow the run down (every
call stops in gdb).
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def drafts(ovl):
    rows = []
    with open(os.path.join(ROOT, "ovl", ovl, "drafts.tsv")) as f:
        for line in f:
            c = line.rstrip("\n").split("\t")
            if c[0].startswith("func_"):
                rows.append((c[0], c[1], c[2] if len(c) > 2 else "?"))
    return rows


def main():
    if len(sys.argv) < 3 or sys.argv[1] not in ("gdb", "table"):
        sys.exit(__doc__)
    ovl = sys.argv[2]
    rows = drafts(ovl)
    native = lambda fn: ovl + "_" + fn[5:]
    if sys.argv[1] == "gdb":
        print("set pagination off\nset confirm off")
        for sig in ("SIGSEGV", "SIGUSR1", "SIGUSR2"):
            print("handle %s nostop noprint pass" % sig)
        for fn, _, _ in rows:
            print('break %s\ncommands\nsilent\nprintf "HIT %s\\n"\ncontinue\nend' % (native(fn), native(fn)))
        print("run\nquit")
        return
    hits = {}
    with open(sys.argv[3], errors="replace") as f:
        for line in f:
            m = re.match(r"HIT (\S+)", line)
            if m:
                hits[m.group(1)] = hits.get(m.group(1), 0) + 1
    out = [(fn, hits[native(fn)], words, path) for fn, path, words in rows if native(fn) in hits]
    out.sort(key=lambda r: (int(r[2]) if r[2].isdigit() else 1 << 30, r[0]))
    print("function\tcalls\twords\tfile")
    for r in out:
        print("%s\t%d\t%s\t%s" % r)
    print("%d of %d drafts called" % (len(out), len(rows)), file=sys.stderr)


if __name__ == "__main__":
    main()
