#!/usr/bin/env python3
"""Extract files by name from KINGDOM.IMG on your own Kingdom Hearts Final Mix
disc image (SLPS-25198), the way the game's loader does it.

  python3 -I extract_kingdom.py GAME.iso NAME [NAME...] --out DIR
  python3 -I extract_kingdom.py GAME.iso --overlays --out DIR   # every EE overlay (.x)
  python3 -I extract_kingdom.py GAME.iso --list [NAME...]        # the whole index

Standalone: Python >= 3.10, stdlib only, no repo imports. Reads the image,
writes only the files asked for into --out (nothing is sent anywhere).

Format (from the main ELF, see the decomp's src/):
  * func_00120ba0: sceCdSearchFile("\\SYSTEM.CNF;1") -> D_004F3208 (base LSN);
    func_0011fe20 reads "\\KINGDOM.IDX;1" (func_00120580) into D_004E4A00,
    at most 3,584 entries of 16 bytes, stopping at an entry whose sector and
    size are both 0, and adds the base LSN to every entry's sector. So the
    absolute LBA of a file is LBA(SYSTEM.CNF) + entry.sector. KINGDOM.IMG is
    not in the ISO directory; its own index entry is the name "kingdom.img"
    (D_004F3200 = that entry's LBA, used for the HDD copy pfs0:kingdom.img,
    func_001202c0: file offset = (LBA - D_004F3200) * 2048).
  * entry (little-endian u32 x4): hash, flags (bit 0 = compressed), sector
    (relative to SYSTEM.CNF), size in bytes as stored (compressed size when
    flag bit 0 is set). Entries are sorted by hash (unsigned) for bsearch
    (func_00120190 -> bsearch(hash, D_004E4A00, count, 16, func_00120170)).
  * hash (func_001200f8): h = 0; for each char c (signed): h = (h << 1) ^
    ((c << 16) % 0x11021), 32-bit, C remainder. Names are hashed as the game
    passes them ("dktitle.x", "menu/sysfont.bin"), case-sensitive.
  * read (func_001201d0): ceil(size / 2048) sectors from the LBA; if
    compressed, func_00120040 decodes in place, backwards: last byte = key,
    the 3 bytes before it = decoded size (byte at len-2 is bits 0-7, len-3
    bits 8-15, len-4 bits 16-23); then reading bytes backwards from len-4:
    c != key -> literal c; c == key, n = next byte: n == 0 -> literal key,
    else count = next byte + 3 and copy count bytes, each out[d] = out[d + n]
    as the output pointer d moves down.
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

SECTOR = 2048
IDX_MAX = 3584
HASH_MOD = 0x11021

# Every EE overlay name the main ELF references (all load to 0x00F20000).
OVERLAYS = [
    "dktitle.x", "dkmovie.x", "gb.x", "wm.x", "xl_limit.x", "xs_dh_break.x",
    "xs_dumbo.x", "xs_bambi.x", "xs_genie.x", "xs_tink.x", "xs_mushu.x", "xs_simba.x",
]
KNOWN = OVERLAYS + ["kingdom.img"]


def kh_hash(name: str | bytes) -> int:
    """func_001200f8."""
    b = name.encode("latin-1") if isinstance(name, str) else name
    h = 0
    for x in b:
        c = x - 256 if x >= 128 else x          # lb: signed char
        v = c << 16
        r = abs(v) % HASH_MOD                    # C remainder (truncating division)
        if v < 0:
            r = -r
        h = ((h << 1) ^ r) & 0xFFFFFFFF
    return h


def decompress(buf: bytes) -> bytes:
    """func_00120040 (backwards LZ with an escape key byte)."""
    if len(buf) < 4:
        raise ValueError("compressed file shorter than its 4-byte trailer")
    key = buf[-1]
    size = buf[-2] | buf[-3] << 8 | buf[-4] << 16
    out = bytearray(size)
    p = len(buf) - 4
    d = size
    try:
        while p > 0:
            p -= 1
            c = buf[p]
            if c == key:
                p -= 1
                n = buf[p]
                if n:
                    p -= 1
                    for _ in range(buf[p] + 3):
                        d -= 1
                        if d < 0:
                            raise IndexError
                        out[d] = out[d + n]
                    continue
            d -= 1
            if d < 0:
                raise IndexError
            out[d] = c
    except IndexError:
        raise ValueError("corrupt compressed data (runs past the start of the output)") from None
    if d != 0:
        print(f"warning: decoded data stops {d} bytes short of the start", file=sys.stderr)
    return bytes(out)


class Image:
    """A disc image: 2048-byte sectors (.iso), or raw 2352-byte (.bin, mode 1 / mode 2 form 1)."""

    def __init__(self, path: Path) -> None:
        self.f = open(path, "rb")
        for ssize, off in ((2048, 0), (2352, 24), (2352, 16)):
            self.ssize, self.off = ssize, off
            if self.read(16, 1)[1:6] == b"CD001":
                break
        else:
            sys.exit(f"{path}: no ISO9660 volume descriptor at sector 16")

    def read(self, lba: int, count: int) -> bytes:
        if self.ssize == SECTOR:
            self.f.seek(lba * SECTOR)
            return self.f.read(count * SECTOR)
        parts = []
        for i in range(count):
            self.f.seek((lba + i) * self.ssize + self.off)
            parts.append(self.f.read(SECTOR))
        return b"".join(parts)

    def read_bytes(self, lba: int, size: int) -> bytes:
        data = self.read(lba, (size + SECTOR - 1) // SECTOR)[:size]
        if len(data) < size:
            raise ValueError(f"image ends inside the file (LBA {lba}, {size} bytes)")
        return data

    def root_files(self) -> dict[str, tuple[int, int]]:
        """Root directory: NAME (upper case, no ';1') -> (lba, size)."""
        pvd = self.read(16, 1)
        rec = pvd[156:190]
        lba, size = struct.unpack_from("<I", rec, 2)[0], struct.unpack_from("<I", rec, 10)[0]
        data = self.read_bytes(lba, size)
        out: dict[str, tuple[int, int]] = {}
        i = 0
        while i < len(data):
            n = data[i]
            if n == 0:                       # records do not cross sectors
                i = (i // SECTOR + 1) * SECTOR
                continue
            r = data[i: i + n]
            nl = r[32]
            name = r[33: 33 + nl].decode("latin-1").split(";")[0].upper()
            if nl > 1 or r[33] > 1:
                out[name] = (struct.unpack_from("<I", r, 2)[0], struct.unpack_from("<I", r, 10)[0])
            i += n
        return out


def parse_idx(raw: bytes) -> list[tuple[int, int, int, int]]:
    """[(hash, flags, sector, size)] as func_0011fe20 keeps them."""
    out = []
    for k in range(min(IDX_MAX, len(raw) // 16)):
        e = struct.unpack_from("<4I", raw, 16 * k)
        if e[2] == 0 and e[3] == 0:
            break
        out.append(e)
    return out


def safe_out(out_dir: Path, name: str) -> Path:
    parts = [p for p in name.replace("\\", "/").split("/") if p not in ("", ".")]
    if not parts or ".." in parts:
        sys.exit(f"refusing to write {name!r}")
    return out_dir.joinpath(*parts)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("iso", help="your disc image (.iso, or raw .bin)")
    ap.add_argument("names", nargs="*", help='file names as the game asks for them, e.g. "dktitle.x"')
    ap.add_argument("--out", help="output directory")
    ap.add_argument("--overlays", action="store_true", help="also extract every EE overlay (.x) name")
    ap.add_argument("--list", action="store_true", help="print every index entry (names given are labelled)")
    ap.add_argument("--raw", action="store_true", help="write stored bytes, do not decompress")
    ap.add_argument("--base-lba", type=lambda s: int(s, 0),
                    help="LBA entry sectors are relative to (default: SYSTEM.CNF's)")
    a = ap.parse_args()

    img = Image(Path(a.iso))
    files = img.root_files()
    if "KINGDOM.IDX" not in files:
        sys.exit(f"KINGDOM.IDX not in the image's root directory (found: {', '.join(sorted(files))})")
    idx_lba, idx_size = files["KINGDOM.IDX"]
    if a.base_lba is not None:
        base = a.base_lba
    elif "SYSTEM.CNF" in files:
        base = files["SYSTEM.CNF"][0]
    else:
        sys.exit("SYSTEM.CNF not in the root directory; pass --base-lba")
    entries = parse_idx(img.read_bytes(idx_lba, idx_size))
    print(f"KINGDOM.IDX: LBA {idx_lba}, {idx_size} bytes, {len(entries)} entries; "
          f"sector base LBA {base} (SYSTEM.CNF)")

    names = list(a.names) + (OVERLAYS if a.overlays else [])
    if a.list:
        label: dict[int, list[str]] = {}
        for n in dict.fromkeys(KNOWN + names):
            label.setdefault(kh_hash(n), []).append(n)
        print("index  hash        flags  sector     LBA        size       name")
        for k, (h, fl, sec, size) in enumerate(entries):
            print(f"{k:5}  0x{h:08x}  {fl:5}  0x{sec:08x} {base + sec:<10} {size:<10} {' '.join(label.get(h, []))}")
        if not a.out:
            return 0
    if not names:
        if not a.list:
            ap.error("give NAME(s), --overlays or --list")
        return 0
    if not a.out:
        ap.error("--out DIR is required to extract")
    out_dir = Path(a.out)
    bad = 0
    for name in dict.fromkeys(names):
        h = kh_hash(name)
        hits = [e for e in entries if e[0] == h]
        if not hits:
            print(f"{name}: hash 0x{h:08x} not in the index", file=sys.stderr)
            bad += 1
            continue
        if len(hits) > 1:
            print(f"{name}: {len(hits)} entries share hash 0x{h:08x}; using the first", file=sys.stderr)
        _h, fl, sec, size = hits[0]
        data = img.read_bytes(base + sec, size)
        comp = bool(fl & 1) and not a.raw
        if comp:
            data = decompress(data)
        dst = safe_out(out_dir, name)
        dst.parent.mkdir(parents=True, exist_ok=True)
        dst.write_bytes(data)
        kind = "ELF" if data[:4] == b"\x7fELF" else "raw"
        print(f"{name}: hash 0x{h:08x} LBA {base + sec} stored {size} bytes"
              f"{' compressed' if fl & 1 else ''} -> {dst} ({len(data)} bytes, {kind})")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
