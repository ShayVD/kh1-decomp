#!/usr/bin/env python3
"""When the main loop's tasks send to the GS, against the draw list (phase 5, renderer-spec 4.12).

  python3 -I tools/host/sendorder.py [--all]

The draw list (renderer-spec 4.1) is started by task 0x9C40 (func_0015eb78) and then runs from
the DMAC interrupts, one node at a time, each node only once sceGsSyncPath(1, 0) reports every
path idle (func_0015ea98).  The immediate list's task 0x27CB8 (func_0015eea0) waits with
sceGsSyncPath(0, 0) first, which on the main thread returns only once the draw list has drained.
So a task between the two keys that sends (a PlatDmaSend, a VIF1 / GIF CHCR write, a draw
environment) before any PlatGsSyncPath can reach the GS while the list's meshes still draw.

This reads src/: every func_0011ef10(KEY, fn) with a literal key, the C call graph from fn (calls
by name only: a pointer passed to func_0015ed80 / func_0015ee78 / func_00106bd8 / func_0011ef10
is deferred work, not a call), and, walking the calls in source order (branches not followed
apart), the first PlatGsSyncPath or send.  It prints each task that can reach a send, its first
event and the call path to it; RACE marks a task between the two keys whose first event is a
send.  --all also lists the tasks whose registration key is not a literal (not decided here; none
in session 82: all 168 registrations have one) and any registration the pattern cannot read.

Static and approximate (source order, not run order); it reads only the repo's C, no game data.
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
LIST, IMMEDIATE = 0x9C40, 0x27CB8
DEFER = {"func_0015ed80", "func_0015ee78", "func_0011ef10", "func_00106bd8"}
FN = re.compile(r"^[A-Za-z_][^;{}()=]*?\b(func_[0-9a-f]{8})\s*\([^;{]*\)\s*\{", re.M)
TOK = re.compile(r"(?<![&\w])(func_[0-9a-f]{8})\s*\(|(PlatGsSyncPath)\s*\(|"
                 r"(PlatDmaSend\w*|PlatDmaPutVif1Chcr|PlatDmaPutGifChcr|PlatGsPutDrawEnv)\s*\(")
# the callback may carry a function-pointer cast or a plain one (`(s32) &func_X`, session 82: four
# registrations, among them light.c's 0xEA60 and brightfade's 0x2E646, were missed before)
CALL_SITE = re.compile(r"(?<![\w&])func_0011ef10\s*\(")
TASK = re.compile(r"func_0011ef10\(\s*([^,()]+?)\s*,\s*(?:\(\s*\w+\s*(?:\(\s*\*\s*\)\s*\([^)]*\)\s*)?\)\s*)?&?"
                  r"(func_[0-9a-f]{8})")


def bodies() -> dict[str, str]:
    out: dict[str, str] = {}
    for p in sorted((ROOT / "src").rglob("*.c")):
        t = p.read_text(errors="replace")
        for m in FN.finditer(t):
            i = j = m.end()
            depth = 1
            while depth and j < len(t):
                depth += {"{": 1, "}": -1}.get(t[j], 0)
                j += 1
            out[m.group(1)] = out.get(m.group(1), "") + t[i:j]
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--all", action="store_true", help="also the tasks registered with a non-literal key")
    a = ap.parse_args()
    body = bodies()

    def first(n: str, path: list[str], seen: set[str]):
        if n in seen:
            return None
        seen.add(n)
        for m in TOK.finditer(body.get(n, "")):
            if m.group(2):
                return "sync", path + [n]
            if m.group(3):
                return "send " + m.group(3), path + [n]
            c = m.group(1)
            if c in DEFER or c == n:
                continue
            r = first(c, path + [n], seen)
            if r:
                return r
        return None

    memo: dict[str, bool] = {}

    def sends(n: str, seen: set[str]) -> bool:
        if n in memo:
            return memo[n]
        if n in seen:
            return False
        seen.add(n)
        r = False
        for m in TOK.finditer(body.get(n, "")):
            if m.group(3) or (m.group(1) and m.group(1) not in DEFER and m.group(1) != n
                              and sends(m.group(1), seen)):
                r = True
                break
        memo[n] = r
        return r

    tasks = set()
    other = set()
    unread = set()  # registrations TASK cannot read (a callback that is not a func_ name)
    for who, b in body.items():
        for m in TASK.finditer(b):
            try:
                tasks.add((int(m.group(1), 0), m.group(2), who))
            except ValueError:
                other.add((m.group(1), m.group(2), who))
        for m in CALL_SITE.finditer(b):
            if not TASK.match(b, m.start()):
                unread.add((who, b[m.start():b.find(";", m.start())]))
    races = 0
    print("# tasks that send (key, task, first event, path; draw list at 0x%x, immediate list at 0x%x)"
          % (LIST, IMMEDIATE))
    for key, f, who in sorted(tasks):
        if not sends(f, set()):
            continue
        r = first(f, [], set())
        race = LIST < key < IMMEDIATE and r[0] != "sync"
        races += race
        print("%6x %-5s %-14s %-22s %s  (registered by %s)" % (key, "RACE" if race else "", f, r[0],
                                                             " > ".join(r[1][1:]) or "-", who))
    if a.all:
        print("# registrations not read (callback not a func_ name)")
        for who, text in sorted(unread):
            print("  %s: %s" % (who, " ".join(text.split())))
        print("# registered with a non-literal key")
        for key, f, who in sorted(other):
            if sends(f, set()):
                r = first(f, [], set())
                print("%-12s %-14s %-22s %s  (registered by %s)" % (key, f, r[0], " > ".join(r[1][1:]) or "-", who))
    print("sendorder: %d tasks with a literal key, %d RACE" % (len(tasks), races), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
