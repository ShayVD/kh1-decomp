#!/usr/bin/env python3
"""Cut the file-backed data region (everything after code) out of the user's
own ELF, as a build-time input of the shiftable build (docs/shiftable-plan.md).

  python3 -I tools/shift/extract_data.py [--elf SLPS_251.98] [--out-dir out/shift/data]

Writes (all under out/, gitignored, never committed):
  main.bin      bytes [text_end, data_end) of the image: .data, VU microcode,
                DMA packets, tables, .rodata
  image.json    header facts the link and the M0 check need: load address,
                entry, file/mem sizes, bss, e_flags, the .reginfo words

Checks the SHA-256 pinned in kh1.toml and that the program/section headers
have the layout the shiftable build assumes (one PT_LOAD at 0x100000 holding
code + data, .bss after it, nothing loaded past the data except zeros)."""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import kh1tool as K  # noqa: E402
from elf32 import PT_LOAD, SHT_NOBITS, Elf  # noqa: E402

PT_MIPS_REGINFO = 0x70000000
DEFAULT_OUT = K.OUT / "shift" / "data"


def image_facts(elf: Elf, cfg: dict) -> dict:
    loads = [s for s in elf.segments if s.type == PT_LOAD]
    if len(loads) != 1:
        sys.exit(f"error: expected one PT_LOAD segment, found {len(loads)}")
    seg = loads[0]
    text_start = K.parse_int(cfg["target"]["text_start"])
    text_end = K.parse_int(cfg["target"]["text_end"])
    if seg.vaddr != text_start:
        sys.exit(f"error: PT_LOAD at 0x{seg.vaddr:08x}, kh1.toml text_start is 0x{text_start:08x}")
    alloc = [s for s in elf.sections if s.flags & 2]  # SHF_ALLOC
    progbits = [s for s in alloc if s.type != SHT_NOBITS and s.addr >= seg.vaddr
                and s.addr < seg.vaddr + seg.filesz]
    bss = [s for s in alloc if s.type == SHT_NOBITS]
    if len(progbits) != 1 or progbits[0].addr != seg.vaddr or len(bss) != 1:
        sys.exit("error: expected one PROGBITS section at the load address and one .bss "
                 f"(found {[s.name for s in progbits]}, {[s.name for s in bss]})")
    main, bss = progbits[0], bss[0]
    data_end = main.addr + main.size
    file_end = seg.vaddr + seg.filesz
    if not text_start < text_end < data_end <= file_end <= bss.addr:
        sys.exit(f"error: unexpected layout: text 0x{text_start:x}-0x{text_end:x}, data end 0x{data_end:x}, "
                 f"file end 0x{file_end:x}, bss 0x{bss.addr:x}")
    tail = elf.read(data_end, file_end - data_end) if file_end > data_end else b""
    if any(tail):
        sys.exit(f"error: PT_LOAD carries non-zero bytes after the main section (0x{data_end:x}-0x{file_end:x})")
    reginfo = next((s for s in elf.segments if s.type == PT_MIPS_REGINFO), None)
    reg_words = (list(struct.unpack_from("<6I", elf.data, reginfo.offset)) if reginfo and reginfo.filesz >= 24
                 else None)
    return {
        "load": seg.vaddr, "entry": elf.entry, "e_flags": elf.e_flags,
        "filesz": seg.filesz, "memsz": seg.memsz, "p_flags": seg.flags,
        "p_offset": seg.offset,
        "text_start": text_start, "text_end": text_end,
        "data_start": text_end, "data_end": data_end,
        "bss_start": bss.addr, "bss_size": bss.size,
        "image_end": seg.vaddr + seg.memsz,
        "reginfo_vaddr": reginfo.vaddr if reginfo else None,
        "reginfo": reg_words,
    }


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", type=Path, help="the original ELF (default: kh1.toml target.elf)")
    ap.add_argument("--out-dir", type=Path, default=DEFAULT_OUT)
    a = ap.parse_args()
    cfg = K.load_config()
    path = a.elf or K.orig_path(cfg)
    raw = path.read_bytes()
    want = cfg["target"]["sha256"].lower()
    got = hashlib.sha256(raw).hexdigest()
    if got != want:
        sys.exit(f"error: {path}: SHA-256 {got} does not match kh1.toml ({want})")
    elf = Elf(raw, path)
    facts = image_facts(elf, cfg)
    blob = elf.read(facts["data_start"], facts["data_end"] - facts["data_start"])
    a.out_dir.mkdir(parents=True, exist_ok=True)
    out_bin = a.out_dir / "main.bin"
    if not out_bin.exists() or out_bin.read_bytes() != blob:
        out_bin.write_bytes(blob)
    out_json = a.out_dir / "image.json"
    text = json.dumps(facts, indent=1) + "\n"
    if not out_json.exists() or out_json.read_text() != text:
        out_json.write_text(text)
    print(f"extract-data: 0x{facts['data_start']:08x}-0x{facts['data_end']:08x} "
          f"({len(blob)} bytes) -> {out_bin.relative_to(K.ROOT) if out_bin.is_absolute() else out_bin}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
