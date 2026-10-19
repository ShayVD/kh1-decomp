#!/usr/bin/env python3
"""Static proof of the overlay fixups of a moved shift link (M1/M2)
(docs/shiftable-plan.md, "Session 13: overlay fixups").

  python3 -I tools/shift/ovl_proof.py --ref out/shift --new out/shift/m1 [--overlays out/overlays]

For every overlay of the table (out/shift/<mode>/ovl_fixups.json, written by
tools/shift/overlay_relocs.py):

1. the table is read from the linked NEW ELF (kh1_ovl_fixups .. kh1_ovl_fixups_end,
   every `.word sym+addend` resolved by the linker);
2. the fixups are applied twice: by a Python model of the hook, and by the
   real hook code (shift/ovl_fixup.c compiled for the build host with
   tools/shift/ovl_hook_host.c); both must return the same count and bytes;
3. inverse-map comparison against the overlay as loaded: every rewritten field
   (jal/j target, %hi/%lo pair as a full address, data word) must be its
   original value mapped old -> new through the M0 -> NEW address map (the
   one tools/shift/shift_cmp.py proves the main ELF with); only the field bits
   may change; every other byte must be identical;
4. the loader really calls the hook: func_00120678 and func_001205f0 of the NEW
   link each contain one jal kh1_ovl_flush0 (in place of a FlushCache(0)).

Like shift_cmp, this proves the fixups that exist; a reference the analysis
missed stays at its old value in both and shows only at run time. Patched
overlays are written under out/ only if --keep is given (they hold the user's
bytes). Exit status 1 on any failure."""
from __future__ import annotations

import argparse
import json
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TOOLS / "shift"))
import kh1tool as K  # noqa: E402
from shift_cmp import Links  # noqa: E402
from extract_kingdom import kh_hash  # noqa: E402

BASE = 0x00F20000
J26, WORD, HI16, LO16 = 0, 1, 2, 3
MASK = {J26: 0x03FFFFFF, WORD: 0xFFFFFFFF, HI16: 0xFFFF, LO16: 0xFFFF}


def sext16(v: int) -> int:
    v &= 0xFFFF
    return v | 0xFFFF0000 if v & 0x8000 else v


def hi16(a: int) -> int:
    return ((a + 0x8000) >> 16) & 0xFFFF


def model_apply(tab: bytes, name: str, buf: bytearray, base: int = BASE) -> int:
    """Python model of kh1_ovl_apply (shift/ovl_fixup.c), same results."""
    rd = lambda b, o: struct.unpack_from("<I", b, o)[0]  # noqa: E731
    if rd(tab, 0) != 0x464F484B or rd(tab, 4) != 1:
        return -1
    h = kh_hash(name)
    n = rd(tab, 8)
    hd = next((12 + 24 * i for i in range(n) if rd(tab, 12 + 24 * i) == h), None)
    if hd is None:
        return 0
    cnt, ent, ntg, tgt = rd(tab, hd + 8), rd(tab, hd + 12), rd(tab, hd + 16), rd(tab, hd + 20)
    size = len(buf)
    for pas in (0, 1):
        e = ent
        for _k in range(cnt):
            w = rd(tab, e)
            kind, ti, off = w >> 30, (w >> 18) & 0xFFF, (w & 0x3FFFF) << 2
            e += 4
            hoff = 0
            if kind == LO16:
                hoff = (rd(tab, e) & 0x3FFFF) << 2
                e += 4
            if ti >= ntg:
                return -1
            if off + 4 > size or hoff + 4 > size:
                return -2
            nv, ov = rd(tab, tgt + 8 * ti), rd(tab, tgt + 8 * ti + 4)
            f = rd(buf, off)
            pc = base + off
            if pas == 0:
                if kind == J26:
                    ok = (((pc + 4) & 0xF0000000) | ((f & 0x03FFFFFF) << 2)) == ov
                elif kind == WORD:
                    ok = f == ov
                elif kind == HI16:
                    ok = (f & 0xFFFF) == hi16(ov)
                else:
                    ok = (((rd(buf, hoff) << 16) + sext16(f)) & 0xFFFFFFFF) == ov
                if not ok:
                    return -3
                continue
            if kind == J26:
                f = (f & 0xFC000000) | ((nv >> 2) & 0x03FFFFFF)
            elif kind == WORD:
                f = nv
            elif kind == HI16:
                f = (f & 0xFFFF0000) | hi16(nv)
            else:
                lo = (nv - (rd(buf, hoff) << 16)) & 0xFFFFFFFF
                if sext16(lo) != lo:
                    return -4
                f = (f & 0xFFFF0000) | (lo & 0xFFFF)
            struct.pack_into("<I", buf, off, f)
    return cnt


def build_host(work: Path) -> Path | None:
    cc = shutil.which("cc") or shutil.which("gcc")
    if not cc:
        return None
    exe = work / "ovl_hook_host"
    subprocess.run([cc, "-O2", "-Wall", "-DKH1_OVL_HOST", "-o", str(exe), str(K.ROOT / "shift" / "ovl_fixup.c"),
                    str(TOOLS / "shift" / "ovl_hook_host.c")], check=True)
    return exe


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ref", type=Path, default=K.OUT / "shift")
    ap.add_argument("--new", type=Path, required=True)
    ap.add_argument("--overlays", type=Path, default=K.OUT / "overlays")
    ap.add_argument("--keep", action="store_true", help="write the patched overlays to NEW/ovl_patched/ (out/ only)")
    a = ap.parse_args()
    mode = a.new.name.upper()
    L = Links(a.ref, a.new)
    ns = L.nsym
    fails: list[str] = []
    for sym in ("kh1_ovl_fixups", "kh1_ovl_fixups_end", "kh1_ovl_flush0", "kh1_ovl_apply"):
        if sym not in ns:
            print(f"{mode} overlay fixups FAIL: {sym} is not in the link")
            return 1
    tab = L.new_img.bytes(ns["kh1_ovl_fixups"], ns["kh1_ovl_fixups_end"] - ns["kh1_ovl_fixups"])
    js = json.loads((a.new / "ovl_fixups.json").read_text())

    # 4: the loader calls the hook
    sizes = {s.name: s.size for s in L.new_elf.symbols() if s.name}
    for fn in ("func_00120678", "func_001205f0"):
        ad, n = ns.get(fn), sizes.get(fn, 0)
        calls = 0
        for o in range(0, n, 4):
            w = L.new_img.word(ad + o)
            if w >> 26 == 3 and (((ad + o + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)) == ns["kh1_ovl_flush0"]:
                calls += 1
        if calls != 1:
            fails.append(f"{fn} calls kh1_ovl_flush0 {calls} times (want 1)")

    work = Path(tempfile.mkdtemp(prefix="ovlproof", dir=str(a.new)))
    try:
        exe = build_host(work)
        (work / "table.bin").write_bytes(tab)
        rows = []
        for ov in js["overlays"]:
            name = ov["name"]
            path = a.overlays / name
            if not path.exists():
                fails.append(f"{name}: not in {a.overlays}")
                continue
            orig = path.read_bytes()
            if len(orig) != ov["size"] or kh_hash(name) != ov["hash"]:
                fails.append(f"{name}: size or hash differs from the analysed file")
                continue
            # 2: Python model and the real hook
            pyb = bytearray(orig)
            r_py = model_apply(tab, name, pyb)
            r_c, cb = None, None
            if exe:
                out = subprocess.run([str(exe), str(work / "table.bin"), str(path), name, str(work / "out.bin")],
                                     check=True, capture_output=True, text=True).stdout
                r_c, cb = int(out.split()[0]), (work / "out.bin").read_bytes()
                (work / "out.bin").unlink()
            if r_py != len(ov["fix"]):
                fails.append(f"{name}: model returned {r_py}, want {len(ov['fix'])}")
            if exe and (r_c != r_py or cb != bytes(pyb)):
                fails.append(f"{name}: the C hook (returned {r_c}) and the model (returned {r_py}) disagree")
            # 3: inverse map
            fields: dict[int, int] = {}
            bad: list[str] = []
            moved = 0
            amap = L.amap

            def word(b, off):
                return struct.unpack_from("<I", b, off)[0]
            for f in ov["fix"]:
                off, kind, old = f["off"], f["kind"], f["old"]
                fields[off] = fields.get(off, 0) | MASK[kind]
                nw, ow = word(pyb, off), word(orig, off)
                if kind == J26:
                    got = ((BASE + off + 4) & 0xF0000000) | ((nw & 0x3FFFFFF) << 2)
                    was = ((BASE + off + 4) & 0xF0000000) | ((ow & 0x3FFFFFF) << 2)
                elif kind == WORD:
                    hb = old & 0xF0000000 if not 0x00100000 <= old <= 0x00675018 else 0
                    got, was = (nw - hb) & 0xFFFFFFFF, (ow - hb) & 0xFFFFFFFF
                    old = old - hb
                elif kind == LO16:
                    hoff = f["hi"]
                    got = ((word(pyb, hoff) << 16) + sext16(nw)) & 0xFFFFFFFF
                    was = ((word(orig, hoff) << 16) + sext16(ow)) & 0xFFFFFFFF
                else:
                    continue  # a %hi is proven through every %lo that pairs with it
                if was != old:
                    bad.append(f"0x{BASE + off:08x}: field held 0x{was:08x}, the analysis said 0x{old:08x}")
                elif got not in amap.fwd(old):
                    bad.append(f"0x{BASE + off:08x}: {('J26', 'WORD', 'HI16', 'LO16')[kind]} 0x{old:08x} -> "
                               f"0x{got:08x}, map says {sorted(hex(x) for x in amap.fwd(old))}")
                elif got != old:
                    moved += 1
            other = 0
            for o in range(0, len(orig) - len(orig) % 4, 4):
                m = fields.get(o, 0)
                if (word(orig, o) & ~m & 0xFFFFFFFF) != (word(pyb, o) & ~m & 0xFFFFFFFF):
                    other += 1
            if bytes(orig[len(orig) - len(orig) % 4:]) != bytes(pyb[len(orig) - len(orig) % 4:]):
                other += 1
            if bad or other:
                fails.append(f"{name}: {len(bad)} fields do not map back, {other} other words differ"
                             + (f"; e.g. {'; '.join(bad[:3])}" if bad else ""))
            kinds = [sum(1 for f in ov["fix"] if f["kind"] == k) for k in (J26, WORD, HI16, LO16)]
            rows.append(f"  {name:14} {len(ov['fix']):5d} fields (J26 {kinds[0]}, WORD {kinds[1]}, HI16 {kinds[2]}, "
                        f"LO16 {kinds[3]}), {moved} moved, C hook {'= model' if exe else 'not run (no cc)'}, "
                        f"fields map back, other words unchanged: {'ok' if not bad and not other and r_py == len(ov['fix']) else 'FAIL'}")
            if a.keep:
                kd = a.new / "ovl_patched"
                kd.mkdir(exist_ok=True)
                (kd / name).write_bytes(bytes(pyb))
        # a file that is not in the table, and a second application, change nothing
        if js["overlays"] and (a.overlays / js["overlays"][0]["name"]).exists():
            name = js["overlays"][0]["name"]
            b = bytearray((a.overlays / name).read_bytes())
            model_apply(tab, name, b)
            again = bytearray(b)
            r2 = model_apply(tab, name, again)
            if again != b or (_moved_any(L, js["overlays"][0]) and r2 != -3):
                fails.append(f"{name}: a second application is not refused (returned {r2})")
            if model_apply(tab, "not_an_overlay.bin", bytearray(16)) != 0:
                fails.append("a file name that is not in the table is not ignored")
    finally:
        shutil.rmtree(work, ignore_errors=True)
    n_ovl = len(js["overlays"])
    print(f"{mode} overlay fixups {'OK' if not fails else 'FAIL'}: {n_ovl} overlays, "
          f"table 0x{len(tab):x} bytes at 0x{ns['kh1_ovl_fixups']:08x}, hook kh1_ovl_flush0 at "
          f"0x{ns['kh1_ovl_flush0']:08x} (called from func_00120678 and func_001205f0)"
          + ("" if n_ovl else f"; no overlays in {a.overlays}: empty table"))
    for r in rows:
        print(r)
    for f in fails:
        print(f"  FAIL: {f}")
    return 1 if fails else 0


def _moved_any(L, ov) -> bool:
    return any(L.amap.moved(f["old"]) for f in ov["fix"] if 0x00100000 <= f["old"] <= 0x00675018)


if __name__ == "__main__":
    sys.exit(main())
