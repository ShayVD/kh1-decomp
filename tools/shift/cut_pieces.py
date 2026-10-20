#!/usr/bin/env python3
"""Cut the data pieces of src/data/data_*.s out of the user's ELF (phase 4, step 4).

  python3 -I tools/shift/cut_pieces.py [--elf SLPS_251.98] [--out-dir out/data/pieces]
                                       [--stamp FILE] SRC.s ...

Each `PIECE D_XXXXXXXX, size, align` line (include/data/piece.inc) names an
address and a size; the bytes at that address of the user's ELF are written to
OUT_DIR/D_XXXXXXXX.bin, which the piece's `.incbin` reads. Files are rewritten
only when their bytes change. The ELF must match the SHA-256 in kh1.toml.
Build output only: out/ is gitignored and never committed."""
from __future__ import annotations

import argparse
import hashlib
import re
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import kh1tool as K  # noqa: E402
from elf32 import Elf  # noqa: E402

PIECE_RE = re.compile(r"^\s*PIECE\s+D_([0-9A-F]{8})\s*,\s*(0x[0-9a-fA-F]+|\d+)\s*,\s*(\d+)")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("srcs", nargs="*", type=Path)
    ap.add_argument("--elf", type=Path, help="the original ELF (default: kh1.toml target.elf)")
    ap.add_argument("--out-dir", type=Path, default=K.OUT / "data" / "pieces")
    ap.add_argument("--stamp", type=Path, help="touch this file when done (make target)")
    a = ap.parse_args()
    cfg = K.load_config()
    path = a.elf or K.orig_path(cfg)
    raw = path.read_bytes()
    if hashlib.sha256(raw).hexdigest() != cfg["target"]["sha256"].lower():
        sys.exit(f"error: {path}: SHA-256 does not match kh1.toml")
    elf = Elf(raw, path)
    a.out_dir.mkdir(parents=True, exist_ok=True)
    n = written = 0
    for src in a.srcs:
        for ln in src.read_text().splitlines():
            m = PIECE_RE.match(ln)
            if not m:
                continue
            addr, size = int(m.group(1), 16), int(m.group(2), 0)
            off = elf.vaddr_to_offset(addr)
            if off is None or elf.vaddr_to_offset(addr + size - 1) is None:
                sys.exit(f"error: {src}: D_{m.group(1)} (0x{size:x} bytes) is not file-backed in {path}")
            body = raw[off:off + size]
            out = a.out_dir / f"D_{m.group(1)}.bin"
            if not out.exists() or out.read_bytes() != body:
                out.write_bytes(body)
                written += 1
            n += 1
    if a.stamp:
        a.stamp.parent.mkdir(parents=True, exist_ok=True)
        a.stamp.write_text(f"{n}\n")
    print(f"cut-pieces: {n} pieces ({written} written) -> {a.out_dir.relative_to(K.ROOT) if a.out_dir.is_absolute() else a.out_dir}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
