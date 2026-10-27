#!/usr/bin/env python3
"""tools/host/ps2mc.py on a made-up card image (no game data), then host/port/mc_dir.c on what it
copied out (tests/host/mc_test.c, gcc -m32 when that works).  tests/selftest.sh runs it.

The card: an 8 MB image with the spare areas (and once without), a root of ".", "..", a save
directory BISLPS-25198-07 holding a 3,000-byte data file (four clusters, chained out of order) and
a 60-byte system.bin, and another game's directory that --match leaves out."""
import calendar
import os
import shutil
import struct
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "host"))
import ps2mc  # noqa: E402

PAGE, PPC, CLUSTERS, IFC, FAT0, ALLOC = 512, 2, 8192, 8, 9, 41
CL = PAGE * PPC


def jst(y, mo, d, h, mi, s):
    return struct.pack("<6BH", 0, s, mi, h, d, mo, y)


def entry(mode, length, cluster, name, t=jst(2002, 3, 28, 12, 0, 0)):
    e = struct.pack("<HHI", mode, 0, length) + t + struct.pack("<II", cluster, 0) + t
    e += struct.pack("<I", 0) + b"\0" * (0x40 - 0x24) + name.encode().ljust(32, b"\0")
    return e.ljust(512, b"\0")


def build(spare):
    clusters = {}
    fat = [0x7FFFFFFF] * CLUSTERS

    def put(chain, data):
        for i, c in enumerate(chain):
            clusters[c] = data[i * CL:(i + 1) * CL].ljust(CL, b"\0")
            fat[c] = 0x80000000 | (chain[i + 1] if i + 1 < len(chain) else 0x7FFFFFFF)

    data = bytes((i * 7) & 0xFF for i in range(3000))
    sysbin = struct.pack("<II", 0x5153484B, 0x01317F14).ljust(60, b"\x11")
    put([0, 1], entry(0x8427, 4, 0, ".") + entry(0x8427, 4, 0, "..") +
        entry(0x8427, 4, 2, "BISLPS-25198-07", jst(2004, 5, 6, 7, 8, 9)) + entry(0x8427, 2, 9, "BASLUS-20370"))
    put([2, 3], entry(0x8427, 4, 0, ".") + entry(0x8427, 0, 0, "..") +
        entry(0x8497, 3000, 4, "BISLPS-25198-07", jst(2004, 5, 6, 7, 8, 9)) + entry(0x8497, 60, 8, "system.bin"))
    put([4, 7, 5, 6], data)
    put([8], sysbin)
    put([9], entry(0x8427, 2, 9, ".") + entry(0x8427, 0, 0, ".."))
    img = {}
    sb = ps2mc.MAGIC + b"1.2.0.0".ljust(12, b"\0")
    sb += struct.pack("<4H4I", PAGE, PPC, 16, 0xFF00, CLUSTERS, ALLOC, CLUSTERS - 2 * 8, 0)
    sb += struct.pack("<II", 1023, 1022) + b"\0" * 8 + struct.pack("<32I", IFC, *([0] * 31))
    img[0] = sb.ljust(CL, b"\0")
    img[IFC] = struct.pack("<256I", *(list(range(FAT0, FAT0 + 32)) + [0] * 224))
    for i in range(32):
        img[FAT0 + i] = struct.pack("<256I", *fat[i * 256:(i + 1) * 256])
    for c, b in clusters.items():
        img[ALLOC + c] = b
    raw = PAGE + (16 if spare else 0)
    out = bytearray(b"\xff" * (CLUSTERS * PPC * raw))
    for c, b in img.items():
        for p in range(PPC):
            at = (c * PPC + p) * raw
            out[at:at + PAGE] = b[p * PAGE:(p + 1) * PAGE]
    return bytes(out), data, sysbin


def main():
    fails = 0
    w = tempfile.mkdtemp()
    try:
        for spare in (1, 0):
            img, data, sysbin = build(spare)
            card = os.path.join(w, "card.ps2")
            open(card, "wb").write(img)
            out = os.path.join(w, "mc%d" % spare)
            p = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "host", "ps2mc.py"),
                                "extract", card, out], capture_output=True, text=True)
            d = os.path.join(out, "BISLPS-25198-07")
            ok = (p.returncode == 0 and sorted(os.listdir(out)) == ["BISLPS-25198-07"]
                  and open(os.path.join(d, "BISLPS-25198-07"), "rb").read() == data
                  and open(os.path.join(d, "system.bin"), "rb").read() == sysbin
                  and int(os.stat(d).st_mtime) == calendar.timegm((2004, 5, 6, 7, 8, 9)) - 9 * 3600)
            if not ok:
                print("ps2mc_test: extract (spare %d) wrong:\n%s%s" % (spare, p.stdout, p.stderr))
                fails += 1
        exe = os.path.join(w, "mc_test")
        cc = ["gcc", "-m32", "-std=gnu89", "-O1", "-w", "-DKH1_HOST", "-I" + os.path.join(ROOT, "include"), "-o", exe,
              os.path.join(ROOT, "tests", "host", "mc_test.c"), os.path.join(ROOT, "host", "port", "mc_dir.c")]
        if subprocess.run(cc, capture_output=True).returncode:
            cc = [c for c in cc if c != "-m32"]
            subprocess.run(cc, check=True)
        p = subprocess.run([exe, os.path.join(w, "mc1")], capture_output=True, text=True)
        sys.stdout.write(p.stdout)
        fails += p.returncode != 0
    finally:
        shutil.rmtree(w)
    print("ps2mc_test: %s" % ("FAIL" if fails else "PASS"))
    sys.exit(1 if fails else 0)


if __name__ == "__main__":
    main()
