#!/usr/bin/env python3
"""Put a shift-build ELF into a copy of the user's own disc image, so PCSX2 boots it
like the retail disc (BIOS -> SYSTEM.CNF -> cdrom0:\\SLPS_251.98).

  tools/shift/patch_iso.py ORIGINAL.iso KH1_M1.ELF OUT.iso [--name SLPS_251.98] [--in-place] [--append]

The ELF is rewritten minimal (ELF header, REGINFO + LOAD program headers, the loaded
bytes; no section headers or symbols). By default it must fit in the retail file's
sectors and is written there; the copy's directory record gets the new size.

--append puts the ELF in new sectors after the end of the volume instead, so it can be any
size: the ISO 9660 directory record gets the new LBA and size (both byte orders) and the
primary volume descriptor's volume space size grows to cover it. Patching an OUT that was
already appended reuses the same sectors (the image is truncated to the new end), so
repeated test builds do not grow the image. The UDF side of the bridge disc is not changed
(its partition still ends at the original volume end and its file entry still points at the
retail slot); the PS2 BIOS and PCSX2 boot through ISO 9660. The UDF anchor that sat in the
last sector is copied to the new last sector. The retail slot is zeroed, so a boot that
works can only have read the appended copy. Without --append, an OUT that was appended
earlier is put back to the retail slot, volume size and length.

Reads and writes only the files given on the command line; nothing goes into the
repository. With --in-place, OUT.iso must already be a copy of ORIGINAL.iso, perhaps patched
by this tool before (useful when copying 3.5 GB takes longer than one shell session).
"""
import argparse
import os
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


def volume_sectors(f) -> int:
    f.seek(16 * SECTOR + 80)
    le, be = struct.unpack("<I", f.read(4))[0], struct.unpack(">I", f.read(4))[0]
    if le != be:
        sys.exit("error: PVD volume space size differs between byte orders")
    return le


def write_volume_sectors(f, n: int):
    f.seek(16 * SECTOR + 80)
    f.write(struct.pack("<I", n) + struct.pack(">I", n))


def write_record(f, rec_off: int, lba: int, size: int):
    f.seek(rec_off + 2)
    f.write(struct.pack("<I", lba) + struct.pack(">I", lba) + struct.pack("<I", size) + struct.pack(">I", size))


def udf_anchor(f, sector: int):
    """The 2048 bytes at sector if they are a UDF anchor volume descriptor pointer (tag 2)."""
    f.seek(sector * SECTOR)
    d = f.read(SECTOR)
    return d if len(d) == SECTOR and struct.unpack_from("<H", d, 0)[0] == 2 else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("iso")
    ap.add_argument("elf")
    ap.add_argument("out")
    ap.add_argument("--name", default="SLPS_251.98")
    ap.add_argument("--in-place", action="store_true", help="OUT is already a copy of ISO")
    ap.add_argument("--append", action="store_true",
                    help="write the ELF after the end of the volume (no size limit)")
    a = ap.parse_args()
    new = minimal_elf(open(a.elf, "rb").read())
    with open(a.iso, "rb") as f:
        rec_off, lba, old_size = find_record(f, a.name)
        vol = volume_sectors(f)
        iso_len = os.fstat(f.fileno()).st_size
        anchor = udf_anchor(f, vol - 1)
    room = -(-old_size // SECTOR) * SECTOR
    if not a.append and len(new) > room:
        sys.exit(f"error: ELF is {len(new)} bytes, the disc slot holds {room}; use --append")
    if iso_len != vol * SECTOR:
        sys.exit(f"error: ORIGINAL is {iso_len} bytes, its volume is {vol * SECTOR}")
    if not a.in_place:
        shutil.copyfile(a.iso, a.out)
    with open(a.out, "r+b") as f:
        out_rec, out_lba, _ = find_record(f, a.name)
        # A copy is the original, or this tool's earlier output (retail slot or appended).
        if out_rec != rec_off or (out_lba != lba and out_lba < vol):
            sys.exit("error: OUT is not a copy of ISO")
        if a.append:
            at = vol  # first sector after the original volume (an earlier append is reused)
            sectors = -(-len(new) // SECTOR)
            end = at + sectors + (1 if anchor else 0)
            f.seek(at * SECTOR)
            f.write(new + bytes(sectors * SECTOR - len(new)))
            if anchor:
                f.write(anchor)
            f.truncate(end * SECTOR)
            # Zero the retail slot, so only the appended copy can boot (no stale ELF).
            f.seek(lba * SECTOR)
            f.write(bytes(room))
            write_volume_sectors(f, end)
            write_record(f, rec_off, at, len(new))
            print(f"patch-iso: {a.name} -> {len(new)} bytes appended at LBA {at} "
                  f"(volume {vol} -> {end} sectors) in {a.out}")
            return
        if out_lba != lba:  # undo an earlier append
            f.truncate(vol * SECTOR)
            write_volume_sectors(f, vol)
        f.seek(lba * SECTOR)
        f.write(new + bytes(room - len(new)))
        write_record(f, rec_off, lba, len(new))
    print(f"patch-iso: {a.name} -> {len(new)} bytes (slot {room}) at LBA {lba} in {a.out}")


if __name__ == "__main__":
    main()
