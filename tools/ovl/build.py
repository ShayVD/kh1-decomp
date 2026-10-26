#!/usr/bin/env python3
"""The overlay build (docs/overlays.md): the 12 EE overlays that load at 0x00F20000,
matched against the user's own overlay files like the main ELF is against SLPS_251.98.

  python3 tools/ovl/build.py wrap [NAME...]     # check out/overlays/NAME.x against
                                                # ovl/overlays.tsv, write out/ovl/NAME.elf
  python3 tools/ovl/build.py layout NAME...     # first ovl/NAME/layout.tsv (inventory.py's
                                                # function finder; hand edits allowed after)
  python3 tools/ovl/build.py verify [NAME...]   # wrap + make -f tools/ovl/ovl.mk for each
                                                # overlay with sources (default: all of them)
  python3 tools/ovl/build.py progress           # matched / functions per overlay

The overlay files come from the user's disc (tools/shift/extract_kingdom.py writes them to
out/overlays/); they are never committed. Only names, addresses and hashes are.
"""
from __future__ import annotations

import argparse
import hashlib
import os
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
BASE = 0x00F20000
PINS = ROOT / "ovl" / "overlays.tsv"
SRC_DIR = Path(os.environ.get("KH1_OVERLAYS", ROOT / "out" / "overlays"))
OUT = ROOT / "out" / "ovl"
BINUTILS = os.environ.get("KH1_BINUTILS_PREFIX", "mips-linux-gnu-")


def pins() -> dict[str, tuple[int, str]]:
    out = {}
    for line in PINS.read_text().splitlines():
        if line and not line.startswith(("#", "name")):
            name, size, sha = line.split("\t")[:3]
            out[name] = (int(size), sha)
    return out


def wrap(name: str) -> Path:
    """out/ovl/NAME.elf: the overlay as one PT_LOAD at 0x00F20000 (section .text), so
    objdump, kh1tool's asm / m2c and the patch step read it like the main ELF."""
    size, sha = pins()[name]
    src = SRC_DIR / f"{name}.x"
    if not src.exists():
        sys.exit(f"error: {src} missing: extract the overlays from your own disc "
                 "(tools/shift/extract_kingdom.py) or copy them there")
    blob = src.read_bytes()
    if len(blob) != size or hashlib.sha256(blob).hexdigest() != sha:
        sys.exit(f"error: {src} is not the pinned {name}.x (size {size}, sha256 {sha[:12]}...)")
    out = OUT / f"{name}.elf"
    if out.exists() and out.stat().st_mtime >= src.stat().st_mtime:
        return out
    OUT.mkdir(parents=True, exist_ok=True)
    ld = OUT / f"{name}.wrap.ld"
    ld.write_text(f"SECTIONS {{ .text 0x{BASE:08x} : {{ *(.data) }} /DISCARD/ : {{ *(*) }} }}\n")
    # ld -b binary takes the input's name for its symbols; link from inside the directory
    tmp = OUT / f"{name}.x"
    tmp.write_bytes(blob)
    subprocess.run([f"{BINUTILS}ld", "-EL", "-m", "elf32ltsmip", "--oformat", "elf32-tradlittlemips", "-e", f"0x{BASE:x}", "-b", "binary", "-s", "-T", ld.name, "-o", out.name,
                    tmp.name], cwd=OUT, check=True)
    tmp.unlink()
    return out


def layout(name: str) -> None:
    import inventory as inv
    path = ROOT / "ovl" / name / "layout.tsv"
    if path.exists():
        sys.exit(f"error: {path.relative_to(ROOT)} exists; edit it by hand")
    blob = (SRC_DIR / f"{name}.x").read_bytes()
    words = struct.unpack(f"<{len(blob) // 4}I", blob[: len(blob) // 4 * 4])
    starts, end = inv.find_functions(BASE, words)
    bounds = starts + [end]
    path.parent.mkdir(parents=True, exist_ok=True)
    lines = [f"# {name}.x at 0x{BASE:08x}: tools/ovl/build.py layout (inventory.py's finder); "
             "hand edits allowed, keep it sorted.", "addr\tend\tsize\tname"]
    lines += [f"{s:08x}\t{e:08x}\t{e - s}\tfunc_{s:08x}" for s, e in zip(starts, bounds[1:])]
    path.write_text("\n".join(lines) + "\n")
    print(f"wrote {path.relative_to(ROOT)}: {len(starts)} functions, code ends at 0x{end:08x}")


def with_sources() -> list[str]:
    return sorted(n for n in pins() if any((ROOT / "ovl" / n).rglob("*.c")) or any((ROOT / "ovl" / n).rglob("*.s")))


def make(name: str, goal: str) -> int:
    wrap(name)
    return subprocess.run(["make", "--no-print-directory", "-j", str(os.cpu_count() or 2), "-f", "tools/ovl/ovl.mk",
                           f"OVL={name}", goal], cwd=ROOT).returncode


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["wrap", "layout", "verify", "report", "progress"])
    ap.add_argument("names", nargs="*")
    a = ap.parse_args()
    if a.cmd == "wrap":
        for n in a.names or pins():
            print(wrap(n).relative_to(ROOT))
        return 0
    if a.cmd == "layout":
        for n in a.names:
            layout(n)
        return 0
    names = a.names or with_sources()
    if a.cmd == "progress":
        tf = tm = 0
        for n in sorted(pins()):
            lay = ROOT / "ovl" / n / "layout.tsv"
            nf = sum(1 for l in lay.read_text().splitlines() if l and not l.startswith(("#", "addr"))) if lay.exists() else 0
            nm = 0
            if n in with_sources():
                os.environ["KH1_OVL"] = n
                r = subprocess.run([sys.executable, "tools/kh1tool.py", "progress"], cwd=ROOT,
                                   capture_output=True, text=True, env=dict(os.environ, KH1_OVL=n))
                for line in r.stdout.splitlines():
                    if line.startswith("Functions matched:"):
                        nm = int(line.split()[2].split("/")[0])
            tf += nf
            tm += nm
            print(f"{n:<12} {nm:>5} / {nf:<5}")
        print(f"{'total':<12} {tm:>5} / {tf:<5}")
        return 0
    rc = 0
    for n in names:
        print(f"== {n}")
        rc |= make(n, a.cmd)
    return rc


if __name__ == "__main__":
    sys.exit(main())
