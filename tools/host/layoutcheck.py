#!/usr/bin/env python3
"""Find code that reaches past a variable's host definition (phase 5, vita-port-plan.md 5.1i).

  python3 -I tools/host/layoutcheck.py [--all] [--tsv out/host/layoutcheck.tsv]

After `make shift` (for out/shift/kh1-shift.linked.elf) and `make host-census`.

On the PS2 every data name sits at its original address, so code may reach one
variable from another (`&D_00656230[9]` is D_00656254) or run past a definition's
C type into bytes no C definition owns. On the host each C definition is its own
object, placed by the host linker. Names whose host addresses keep their PS2
distances (one definition, a data piece, a census.py block) form a host run;
tools/shift/reach_check.py, given those runs as its pieces, lists every access
from a base in one run to an address outside it.

Default output: the rows with a fixed displacement (loads / stores at base+d,
addresses built as base+d, bounded index spans, memset / argument reads), one
per (base name, target name) with the kinds and the functions. Left out as
benign on the host: an end pointer one past the base's own definition (C's
&a[N]); string arguments of the libc string functions and the disc file
functions' names (the host reads them to the NUL, not in quadwords); rows whose
functions are all in the SDK (not compiled for the host); and the REVIEWED rows
below, read by hand. --all also prints reach_check's unbounded index rows
(idx-next: an index with no bound reaching the next run) and the uncached-alias
rows (DMA buffers), which are mostly not layout dependencies.
Only addresses and names are printed, no game bytes."""
from __future__ import annotations

import argparse
import bisect
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
LIBC_STR = {"func_00250f40", "func_002512c4", "func_0025106c", "func_002511b0", "func_00250340",
            "func_0024ff10", "func_00251400",
            # the disc file functions take a file name (strcpy / strlen on the host)
            "func_00120748", "func_001205f0", "func_00120190", "func_00120a20", "func_001b9c60"}

# Rows read by hand (session 69): (base, target) -> why the host is not affected.
REVIEWED = {
    ("D_00494050", "00494080"): "_gp: crt0 and the thread setups pass it as the gp register; nothing reads through it",
    ("00674bc0", "D_00675018"): "crt0's .bss clear (src/asm), not run on the host",
    ("D_003C5830", "D_003C5898"): "func_0010d470 (unmatched, its draft runs): D_003C5830[c] for a text control byte; "
                                  "the analysis' bound ends at D_003C5898",
    ("D_00490A80", "004901c0"): "func_001f1fc8 (unmatched, its draft runs): an index read 0x8c0 below; check when it matches",
    ("00490d90", "D_00492730"): "func_001f94f0: no name owns 0x00490D90 (a constant the analysis took as a base)",
    ("D_004F6DB0", "D_004F45B0"): "heap.c sets the walk pointer to &D_004F45B0[1] by name",
    ("D_0052AE98", "D_0052CB18"): "partystat.c compares with D_0052AE98 + 32, its own end",
    ("D_0054B800", "D_00547C00"): "effobj.c resets the pointer to D_00547C00 by name",
    ("D_00575528", "D_00575784"): "session 33 idx-span: not reached",
    ("D_00575A00", "D_00575A10"): "eiwind.nostrict.c reads the empty object as a PppWfacc: its min (+0x14) only when "
                                  "len < range, and range (+0xC) is 0",
}
SDK_START = 0x0024F2E0  # src/sdk: not compiled for the host (the port's own libc / libraries)


def ps2_names():
    """name -> (PS2 address, size or None, defining object)"""
    names = {}
    for ln in (ROOT / "out/gen/data.tsv").read_text().splitlines()[1:]:
        f = ln.split("\t")
        names[f[1]] = (int(f[0], 16), int(f[3], 16), f[2].replace("out/build/", "").replace(".o", ""))
    for ln in (ROOT / "out/gen/symbols.ld").read_text().splitlines():
        m = re.search(r"PROVIDE\((D_[0-9A-F]{8}) = 0x([0-9a-f]+)\)", ln)
        if m and m.group(1) not in names:
            names[m.group(1)] = (int(m.group(2), 16), None, "symbols.ld")
    return names


def host_names(exe):
    """name -> (host address, host size) for the D_ names the host executable defines"""
    out = {}
    nm = subprocess.run(["nm", "-S", str(exe)], capture_output=True, text=True, check=True).stdout
    for ln in nm.splitlines():
        f = ln.split()
        if len(f) == 4 and f[2] in "DdBbRr" and re.fullmatch(r"D_[0-9A-F]{8}", f[3]):
            out[f[3]] = (int(f[0], 16), int(f[1], 16))
        elif len(f) == 3 and f[1] in "DdBbRr" and re.fullmatch(r"D_[0-9A-F]{8}", f[2]):
            out[f[2]] = (int(f[0], 16), 0)  # a linker alias (aliases.ld): no size
    return out


def runs(ps2, host):
    names = sorted((ps2[n][0], n) for n in ps2 if n in host and 0x272C70 <= ps2[n][0] < 0x6A0000)
    rs = []
    for a, n in names:
        h, s = host[n]
        if rs and h - rs[-1]["h"] == a - rs[-1]["a"] and a - rs[-1]["end"] < 0x1000:
            rs[-1]["end"] = max(rs[-1]["end"], a + s)
            rs[-1]["names"].append(n)
            continue
        rs.append({"a": a, "h": h, "end": a + max(s, 1), "names": [n]})
    return rs


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--all", action="store_true", help="also the unbounded index and uncached-alias rows")
    ap.add_argument("--tsv", type=Path, help="write the rows as TSV")
    ap.add_argument("--exe", type=Path, default=ROOT / "out/host/kh1-host")
    a = ap.parse_args()
    ps2, host = ps2_names(), host_names(a.exe)
    rs = runs(ps2, host)
    owners = sorted((v[0], k) for k, v in ps2.items() if k in host)
    starts = [o[0] for o in owners]

    def owner(addr):
        i = bisect.bisect_right(starts, addr) - 1
        if i >= 0:
            n = owners[i][1]
            if addr < owners[i][0] + max(host[n][1], 1):
                return n
        return None

    with tempfile.TemporaryDirectory() as td:
        tsv = Path(td) / "runs.tsv"
        tsv.write_text("addr\tsymbol\tobject\tsize\tregion\n" + "".join(
            "%08x\t%s\thost\t%x\t-\n" % (r["a"], r["names"][0], r["end"] - r["a"]) for r in rs))
        (Path(td) / "ovl").mkdir()
        p = subprocess.run([sys.executable, "-I", str(ROOT / "tools/shift/reach_check.py"), "--overlays",
                            str(Path(td) / "ovl"), "--data-tsv", str(tsv)], capture_output=True, text=True)
        if p.returncode:
            print(p.stderr[-2000:])
            return 1
    rows: dict[tuple, list] = {}
    benign = 0
    for ln in p.stdout.splitlines():
        f = ln.split("\t")
        m = re.match(r"([0-9a-f]{8}) \(.*?\) -> ([0-9a-f]{8})", f[0])
        if not m:
            continue
        b, t = int(m.group(1), 16), int(m.group(2), 16)
        kind = re.sub(r"[\[:].*", "", f[1]) or "?"
        if kind in ("idx-next", "uncached") and not a.all:
            continue
        nb, nt = owner(b), owner(t)
        if kind == "end-ptr" and nb and t == ps2[nb][0] + host[nb][1]:
            benign += 1
            continue
        if kind.startswith("arg") and f[1].split(":")[1] in LIBC_STR:
            benign += 1
            continue
        key = (nb or "%08x" % b, nt or "%08x" % t)
        fs = [x for x in f[2].split() if x.startswith("func_")]
        if key in REVIEWED or (fs and all(int(x[5:], 16) >= SDK_START for x in fs)):
            benign += 1
            continue
        r = rows.setdefault(key, [set(), set(), []])
        r[0].add(kind)
        r[1].update(f[2].split())
        r[2].append(t - (ps2[nb][0] if nb else b))
    lines = []
    for (nb, nt), (kinds, fs, offs) in sorted(rows.items()):
        def where(n):
            if n in ps2:
                return "%s (%s, host 0x%x)" % (n, ps2[n][2], host[n][1])
            return n + " (no host name)"
        fl = sorted(f for f in fs if f.startswith("func_"))
        lines.append("%s\t%s\t%s\t+0x%x..+0x%x\t%s" % (where(nb), where(nt), ",".join(sorted(kinds)), min(offs),
                                                     max(offs), " ".join(fl[:6]) + (" +%d" % (len(fl) - 6) if len(fl) > 6 else "")))
    print("\n".join(lines))
    bases = len(set(k[0] for k in rows))
    print("# %d host runs; %d rows from %d base names (%d benign left out)%s" %
          (len(rs), len(rows), bases, benign, "" if a.all else "; --all adds idx-next / uncached"), file=sys.stderr)
    if a.tsv:
        a.tsv.parent.mkdir(parents=True, exist_ok=True)
        a.tsv.write_text("base\ttarget\tkinds\toffsets\tfunctions\n" + "\n".join(lines) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
