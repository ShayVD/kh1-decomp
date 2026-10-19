#!/usr/bin/env python3
"""Self-test for tools/shift/scan_overlay.py on a synthetic raw overlay
(no game data; names come from the repo's layout.tsv / functions.tsv).

  python3 -I tests/scan_overlay_test.py
"""
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools" / "shift"))
sys.path.insert(0, str(ROOT / "tools"))
import scan_overlay as S  # noqa: E402


def lui(rt, v): return (0x0F << 26) | (rt << 16) | v
def addiu(rt, rs, v): return (0x09 << 26) | (rs << 21) | (rt << 16) | (v & 0xFFFF)
def lw(rt, rs, v): return (0x23 << 26) | (rs << 21) | (rt << 16) | (v & 0xFFFF)
def jal(t): return (0x03 << 26) | (t >> 2)


words = [
    jal(0x00100008),            # call into crt0's _start (function start)
    0,
    lui(4, 0x0049),             # lui a0,0x49
    addiu(4, 4, 0x4050),        # addiu a0,a0,0x4050 -> 0x00494050 (data)
    lui(2, 0x0067),             # lui v0,0x67
    lw(3, 2, -0x0780),          # lw v1,-0x780(v0) -> 0x0066F880 (bss)
    lui(5, 0x0050),             # lui a1,0x50 then a1 rewritten: no pair
    addiu(5, 0, 1),
    lw(6, 5, 0),                # base a1 no longer holds the %hi
    0x03E00008, 0,              # jr ra; nop
    0x00F20010,                 # pointer inside the overlay itself: ignored
    0x00100008,                 # data word: function start
    0x00700000,                 # past the image: ignored
]
blob = struct.pack(f"<{len(words)}I", *words)
hits = S.scan([(0x00F20000, blob)], S.Names())
got = {(h[1], h[2]) for h in hits}
want = {("jal", 0x00100008), ("%hi/%lo", 0x00494050), ("%hi/%lo", 0x0066F880), ("word", 0x00100008)}
assert want <= got, (sorted(got), sorted(want))
assert not any(h[2] in (0x00F20010, 0x00700000, 0x00500000) for h in hits), hits
assert [h[0] for h in hits if h[1] == "word"] == [0x00F20000 + 4 * 12], hits

with tempfile.TemporaryDirectory() as d:
    p = Path(d) / "synthetic.x"
    p.write_bytes(blob)
    out = subprocess.run([sys.executable, "-I", str(ROOT / "tools/shift/scan_overlay.py"), str(p)],
                         check=True, capture_output=True, text=True).stdout
assert "jal" in out and "D_00494050" in out and "D_0066F880" in out, out
print("scan_overlay_test: PASS")
