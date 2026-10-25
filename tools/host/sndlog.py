#!/usr/bin/env python3
"""Summarise a host run's sound commands (session 86, docs/sound-spec.md, vita-port-plan 5.1z).

    KH1_HOST_SND=trace out/host/kh1-host > RUN.txt
    python3 -I tools/host/sndlog.py RUN.txt [--frames]

reads host/null/sound.c's lines

    kh1-host: snd FRAME q CMD NAME key=value ...
    kh1-host: snd FRAME rpc NUM NAME a0 a1 a2 a3
    kh1-host: snd FRAME end se|voice|objse key=value ...

and prints the commands and RPCs by count, the bank / data transfers (kind, slot, bytes), the music
track starts, the SEs played by (bank, id), the voices, and the most records one frame sent (RPC 30
sends 256 at most; the server reads no more, so a frame near 256 is one to look at). --frames also prints each frame's
commands in order.
"""
import argparse
import collections
import re
import sys

LINE = re.compile(r"kh1-host: snd (\d+) (q|rpc|end) (.*)$")


def kv(words):
    out = {}
    for w in words:
        if "=" in w:
            k, v = w.split("=", 1)
            out[k] = int(v, 0)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("run")
    ap.add_argument("--frames", action="store_true")
    a = ap.parse_args()
    cmds = collections.Counter()
    rpcs = collections.Counter()
    ends = collections.Counter()
    per_frame = collections.Counter()
    transfers = collections.defaultdict(lambda: [0, 0])
    music = []
    ses = collections.Counter()
    voices = 0
    frames = collections.defaultdict(list)
    n = 0
    for l in open(a.run, errors="replace"):
        m = LINE.search(l)
        if not m:
            continue
        n += 1
        frame, kind, rest = int(m.group(1)), m.group(2), m.group(3).split()
        frames[frame].append(kind + " " + " ".join(rest))
        if kind == "q":
            name = rest[1]
            cmds["%s %s" % (rest[0], name)] += 1
            per_frame[frame] += 1
            f = kv(rest[2:])
            if name in ("wave", "setab", "seq"):
                t = transfers["%s slot %d" % (name, f.get("slot", 0))]
                t[0] += 1
                t[1] += f.get("size", 0)
            elif name == "voicebank":
                t = transfers["voicebank"]
                t[0] += 1
                t[1] += f.get("size", 0)
            elif name == "music-start":
                music.append((frame, f.get("track"), f.get("volume"), f.get("fade")))
            elif name == "se-play":
                ses[(f.get("bank"), f.get("id"))] += 1
            elif name == "voice-play":
                voices += 1
        elif kind == "rpc":
            rpcs["%s %s" % (rest[0], rest[1])] += 1
        else:
            ends[rest[0]] += 1
    if not n:
        print("sndlog: no `kh1-host: snd` lines (run with KH1_HOST_SND=trace)")
        return 1
    print("commands (queued):")
    for k, v in sorted(cmds.items()):
        print("  %-22s %6d" % (k, v))
    print("direct RPCs:")
    for k, v in sorted(rpcs.items()):
        print("  %-22s %6d" % (k, v))
    if transfers:
        print("transfers:")
        for k, (c, b) in sorted(transfers.items()):
            print("  %-22s %6d  %d bytes" % (k, c, b))
    if music:
        print("music starts (frame, track, volume, fade):")
        for x in music:
            print("  %d track %s volume %s fade %s" % x)
    if ses:
        print("SEs played: %d distinct (bank, id), %d plays; most played:" % (len(ses), sum(ses.values())))
        for (b, i), c in ses.most_common(10):
            print("  bank %s id %s: %d" % (b, i, c))
    print("voices played: %d; ended by time: %s" % (voices, ", ".join("%s %d" % kv_ for kv_ in sorted(ends.items()))
                                                     or "none"))
    if per_frame:
        f, c = max(per_frame.items(), key=lambda x: x[1])
        print("most records sent in one frame: %d (frame %d; one send holds 256 at most)" % (c, f))
    if a.frames:
        for f in sorted(frames):
            for x in frames[f]:
                print("%6d %s" % (f, x))
    return 0


if __name__ == "__main__":
    sys.exit(main())
