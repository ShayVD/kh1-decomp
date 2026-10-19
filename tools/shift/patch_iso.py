#!/usr/bin/env python3
"""Put a shift-build ELF into a copy of the user's own disc image, so PCSX2 boots it
like the retail disc (BIOS -> SYSTEM.CNF -> cdrom0:\\SLPS_251.98).

  tools/shift/patch_iso.py ORIGINAL.iso KH1_M1.ELF OUT.iso [--name SLPS_251.98] [--in-place]

The ELF is rewritten minimal (ELF header, REGINFO + LOAD program headers, the loaded
bytes; no section headers or symbols) so it fits in the retail file's sectors. The copy's
directory record gets the new size. Reads and writes only the files given on the command
line; nothing goes into the repository. With --in-place, OUT.iso must already be a copy of
ORIGINAL.iso (useful when copying 3.5 GB takes longer than one shell session).
"""
import argparse
import shutil
import struct
import sys

SECTOR = 2048
PT_LOAD, PT_MIPS_REGINFO = 1, 0x70000000


def minimal_elf(data: bytes) -> bytes:
    ehdr = struct.unpack_from("<16sHHIIIIIHHHHHH", data, 0)
    entry, phoff, flags, phnum = ehdr[4], ehdr[5], ehdr[7], ehdr[10]
    phdrs = [struct.unpack_from("<8I", data, phoff + 32 * i) for i in range(phnum)]
    load = [p for p in phdrs if p[0] == PT_LOAD and p[5]]
    reginfo = [p for p in phdrs if p[0] == PT_MIPS_REGINFO]
    if len(load) != 1:
        sys.exit(f"error: expected one PT_LOAD with memory, found {len(load)}")
    _, off, vaddr, _, filesz, memsz, pflags, _ = load[0]
    body = data[off:off + filesz]
    # Layout like the retail ELF: REGINFO first, LOAD data at 0x80, REGINFO after it.
    data_off = 0x80
    reg_off = data_off + filesz
    reg = data[reginfo[0][1]:reginfo[0][1] + reginfo[0][4]] if reginfo else b""
    out = bytearray(data_off)
    struct.pack_into("<16sHHIIIIIHHHHHH", out, 0, ehdr[0], 2, 8, 1, entry, 52, 0, flags,
                     52, 32, 1 + bool(reg), 40, 0, 0)
    ph = 52
    if reg:
        r = reginfo[0]
        struct.pack_into("<8I", out, ph, PT_MIPS_REGINFO, reg_off, r[2], r[3], len(reg), len(reg), r[6], r[7])
        ph += 32
    struct.pack_into("<8I", out, ph, PT_LOAD, data_off, vaddr, vaddr, filesz, memsz, pflags, 0x80)
    return bytes(out) + body + reg


def find_record(f, name: str):
    """(offset of the directory record, extent LBA, size) for a file in the root directory."""
    f.seek(16 * SECTOR)
    pvd = f.read(SECTOR)
    if pvd[1:6] != b"CD001":
        sys.exit("error: not an ISO 9660 image")
    root = pvd[156:156 + 34]
    lba, size = struct.unpack_from("<I", root, 2)[0], struct.unpack_from("<I", root, 10)[0]
    f.seek(lba * SECTOR)
    d = f.read(size)
    i = 0
    while i < len(d):
        n = d[i]
        if n == 0:
            i = (i // SECTOR + 1) * SECTOR
            continue
        rec = d[i:i + n]
        ident = rec[33:33 + rec[32]].decode("latin1").split(";")[0]
        if ident.upper() == name.upper():
            return lba * SECTOR + i, struct.unpack_from("<I", rec, 2)[0], struct.unpack_from("<I", rec, 10)[0]
        i += n
    sys.exit(f"error: {name} not found in the ISO root")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("iso")
    ap.add_argument("elf")
    ap.add_argument("out")
    ap.add_argument("--name", default="SLPS_251.98")
    ap.add_argument("--in-place", action="store_true", help="OUT is already a copy of ISO")
    a = ap.parse_args()
    new = minimal_elf(open(a.elf, "rb").read())
    with open(a.iso, "rb") as f:
        rec_off, lba, old_size = find_record(f, a.name)
    room = -(-old_size // SECTOR) * SECTOR
    if len(new) > room:
        sys.exit(f"error: ELF is {len(new)} bytes, the disc slot holds {room}")
    if not a.in_place:
        shutil.copyfile(a.iso, a.out)
    with open(a.out, "r+b") as f:
        if find_record(f, a.name)[:2] != (rec_off, lba):
            sys.exit("error: OUT is not a copy of ISO")
        f.seek(lba * SECTOR)
        f.write(new + bytes(room - len(new)))
        f.seek(rec_off + 10)
        f.write(struct.pack("<I", len(new)) + struct.pack(">I", len(new)))
    print(f"patch-iso: {a.name} -> {len(new)} bytes (slot {room}) at LBA {lba} in {a.out}")


if __name__ == "__main__":
    main()
