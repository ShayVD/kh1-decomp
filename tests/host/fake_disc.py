#!/usr/bin/env python3
"""A tiny ISO9660 image with no game data, for the host runner's disc platform
(host/port/cd_image.c, docs/vita-port-plan.md section 5.1c):

    python3 -I tests/host/fake_disc.py OUT.iso
    KH1_HOST_ISO=OUT.iso KH1_HOST_TRACE=1 out/host/kh1-host

Root directory: SYSTEM.CNF (a BOOT2 line), KINGDOM.IDX (two entries, sorted
by hash: the "kingdom.img" name, hashed like func_001200f8, pointing at a few
zero sectors after it, relative to SYSTEM.CNF as the game reads them, and a
one-sector "dktitle.x" that is not code, which the boot loads through the
loader thread before it calls the overlay) and a DIR\\FILE.BIN to test a path
search. It tests the search and the read, not the
game: the real run needs the user's own disc.
"""
import struct
import sys

S = 2048


def kh_hash(name):
    h = 0
    for x in name.encode("latin-1"):
        c = x - 256 if x >= 128 else x
        v = c << 16
        r = abs(v) % 0x11021
        h = ((h << 1) ^ (-r if v < 0 else r)) & 0xFFFFFFFF
    return h


def both16(v):
    return struct.pack("<H", v) + struct.pack(">H", v)


def both32(v):
    return struct.pack("<I", v) + struct.pack(">I", v)


def record(name, lba, size, is_dir):
    n = name.encode("ascii") if isinstance(name, str) else name
    body = (both32(lba) + both32(size) + bytes(7) + bytes([2 if is_dir else 0, 0, 0])
            + both16(1) + bytes([len(n)]) + n)
    r = bytes([0, 0]) + body
    if len(r) % 2:
        r += b"\0"
    return bytes([len(r)]) + r[1:]


def directory(entries, self_lba, parent_lba):
    d = record(b"\0", self_lba, S, True) + record(b"\1", parent_lba, S, True)
    for e in entries:
        d += record(*e)
    return d.ljust(S, b"\0")


def main():
    out = sys.argv[1]
    root, sub, cnf, idx, fbin, img = 19, 20, 21, 22, 23, 24
    cnf_data = b"BOOT2 = cdrom0:\\SLPS_251.98;1\r\nVER = 1.00\r\nVMODE = NTSC\r\n"
    ovl = img + 4
    ents = sorted([(kh_hash("kingdom.img"), 0, img - cnf, 4 * S),
                   (kh_hash("dktitle.x"), 0, ovl - cnf, S)])
    idx_data = b"".join(struct.pack("<4I", *e) for e in ents) + bytes(16)
    fbin_data = b"kh1-host fake disc\n"
    sectors = [bytes(S)] * 16
    pvd = bytearray(S)
    pvd[0:7] = b"\x01CD001\x01"
    pvd[80:88] = both32(ovl + 1)
    pvd[120:124] = both16(1)
    pvd[124:128] = both16(1)
    pvd[128:132] = both16(S)
    pvd[156:190] = record(b"\0", root, S, True)
    sectors.append(bytes(pvd))
    sectors.append(b"\xffCD001\x01".ljust(S, b"\0"))
    sectors.append(bytes(S))  # 18: path table (unused)
    sectors.append(directory([("SYSTEM.CNF;1", cnf, len(cnf_data), False),
                              ("KINGDOM.IDX;1", idx, len(idx_data), False),
                              ("DIR", sub, S, True)], root, root))
    sectors.append(directory([("FILE.BIN;1", fbin, len(fbin_data), False)], sub, root))
    for d in (cnf_data, idx_data, fbin_data):
        sectors.append(d.ljust(S, b"\0"))
    sectors += [bytes(S)] * 4
    sectors.append(b"kh1-host fake dktitle.x: not code\n".ljust(S, b"\0"))
    open(out, "wb").write(b"".join(sectors))
    print("%s: %d sectors" % (out, len(sectors)))


if __name__ == "__main__":
    main()
