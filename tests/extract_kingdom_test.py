#!/usr/bin/env python3
"""Self-test for tools/shift/extract_kingdom.py on a synthetic disc image
(no game data): a minimal ISO9660 with SYSTEM.CNF and KINGDOM.IDX in the
root, files placed past them by sector (relative to SYSTEM.CNF), one stored
plain and others compressed with a small encoder for the game's backwards LZ.

  python3 -I tests/extract_kingdom_test.py
"""
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TOOL = ROOT / "tools" / "shift" / "extract_kingdom.py"
sys.path.insert(0, str(TOOL.parent))
import extract_kingdom as X  # noqa: E402

S = 2048


def compress(data: bytes) -> bytes:
    """Encoder for func_00120040: tokens are read from the end backwards and
    fill the output from its end, so they are emitted in that order and the
    stream is reversed at the end."""
    counts = [0] * 256
    for b in data:
        counts[b] += 1
    key = counts.index(min(counts))
    toks = []                  # in decoder read order; each token's bytes also in read order
    d = len(data)
    while d > 0:
        best_n = best_len = 0
        for n in range(1, 256):
            if d + n > len(data):
                break
            ln = 0
            while ln < 258 and d - 1 - ln >= 0 and data[d - 1 - ln] == data[d - 1 - ln + n]:
                ln += 1
            if ln > best_len:
                best_n, best_len = n, ln
        if best_len >= 3:
            toks.append(bytes([key, best_n, best_len - 3]))
            d -= best_len
        else:
            c = data[d - 1]
            toks.append(bytes([key, 0]) if c == key else bytes([c]))
            d -= 1
    stream = b"".join(toks)[::-1]
    n = len(data)
    return stream + bytes([(n >> 16) & 0xFF, (n >> 8) & 0xFF, n & 0xFF, key])


def dirrec(name: bytes, lba: int, size: int, isdir: bool = False) -> bytes:
    n = 33 + len(name)
    n += n & 1
    r = bytearray(n)
    r[0] = n
    struct.pack_into("<I", r, 2, lba)
    struct.pack_into(">I", r, 6, lba)
    struct.pack_into("<I", r, 10, size)
    struct.pack_into(">I", r, 14, size)
    r[25] = 2 if isdir else 0
    r[32] = len(name)
    r[33: 33 + len(name)] = name
    return bytes(r)


def build_iso(files: dict[str, tuple[bytes, bool]], sector_rel: dict[str, int]) -> tuple[bytes, list]:
    root_lba, cnf_lba, idx_lba = 20, 22, 23
    cnf = b"BOOT2 = cdrom0:\\SLPS_251.98;1\r\n"
    entries = []
    for name, (blob, comp) in files.items():
        stored = compress(blob) if comp else blob
        entries.append((X.kh_hash(name), 1 if comp else 0, sector_rel[name], len(stored), stored))
    entries.sort(key=lambda e: e[0])
    idx = b"".join(struct.pack("<4I", *e[:4]) for e in entries) + bytes(16)
    end = max(cnf_lba + e[2] + (e[3] + S - 1) // S for e in entries) + 1
    img = bytearray(end * S)
    root = (dirrec(b"\x00", root_lba, S, True) + dirrec(b"\x01", root_lba, S, True)
            + dirrec(b"KINGDOM.IDX;1", idx_lba, len(idx)) + dirrec(b"SYSTEM.CNF;1", cnf_lba, len(cnf)))
    pvd = bytearray(S)
    pvd[0], pvd[1:6], pvd[6] = 1, b"CD001", 1
    pvd[156:156 + 34] = dirrec(b"\x00", root_lba, S, True)
    img[16 * S: 17 * S] = pvd
    img[17 * S: 17 * S + 6] = b"\xffCD001"
    img[root_lba * S: root_lba * S + len(root)] = root
    img[cnf_lba * S: cnf_lba * S + len(cnf)] = cnf
    img[idx_lba * S: idx_lba * S + len(idx)] = idx
    for e in entries:
        o = (cnf_lba + e[2]) * S
        img[o: o + e[3]] = e[4]
    return bytes(img), entries


# hash: hand-computed values for short names
assert X.kh_hash("") == 0
assert X.kh_hash("a") == (0x61 << 16) % 0x11021
assert X.kh_hash("ab") == ((((0x61 << 16) % 0x11021) << 1) ^ ((0x62 << 16) % 0x11021))
assert X.kh_hash(b"\xe9") == (-(((0x100 - 0xE9) << 16) % 0x11021)) & 0xFFFFFFFF  # signed char, C %
assert X.kh_hash("x" * 40) <= 0xFFFFFFFF

# decoder: hand-built stream "abcabcabc!" with key 0x7E: literals then a copy
for sample in (b"", b"a", b"abcabcabcabcabc!", bytes(range(256)) * 3, b"\x00" * 5000,
               bytes((i * 7919) & 0xFF for i in range(3000)) + b"kingdom" * 200):
    assert X.decompress(compress(sample)) == sample, sample[:20]
# a literal equal to the key byte (escape "key, 0")
s = bytes(range(256)) + b"\x05\x05"
assert X.decompress(compress(s)) == s

ovl = struct.pack("<8I", 0x0C04804E, 0, 0x3C040049, 0x24844050, 0x03E00008, 0, 0x00100008, 0) * 40
files = {
    "dktitle.x": (ovl, True),
    "dkmovie.x": (b"plain overlay bytes " * 300, False),
    "menu/sysfont.bin": (bytes(range(256)) * 20, True),
    "kingdom.img": (b"", False),
}
rel = {"kingdom.img": 4, "dktitle.x": 4, "dkmovie.x": 12, "menu/sysfont.bin": 30}
iso, entries = build_iso(files, rel)

with tempfile.TemporaryDirectory() as d:
    d = Path(d)
    p = d / "fake.iso"
    p.write_bytes(iso)
    run = lambda *a: subprocess.run([sys.executable, "-I", str(TOOL), *a], capture_output=True, text=True)
    r = run(str(p), "dktitle.x", "dkmovie.x", "menu/sysfont.bin", "--out", str(d / "out"))
    assert r.returncode == 0, r.stderr + r.stdout
    for name in ("dktitle.x", "dkmovie.x", "menu/sysfont.bin"):
        got = (d / "out" / name).read_bytes()
        assert got == files[name][0], name
    r = run(str(p), "--list")
    assert r.returncode == 0, r.stderr
    assert f"{len(entries)} entries" in r.stdout and "dktitle.x" in r.stdout and "kingdom.img" in r.stdout, r.stdout
    assert f"0x{X.kh_hash('dkmovie.x'):08x}" in r.stdout
    r = run(str(p), "nothere.x", "--out", str(d / "out"))
    assert r.returncode == 1 and "not in the index" in r.stderr
    r = run(str(p), "../evil", "--out", str(d / "out"))
    assert r.returncode != 0
print("extract_kingdom_test: PASS")
