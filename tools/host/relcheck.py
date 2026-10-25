#!/usr/bin/env python3
"""Find C code that names one variable and reaches another (phase 5, vita-port-plan.md 5.1j).

  python3 -I tools/host/relcheck.py [--all] [--no-ps2] [--no-drafts] [--tsv out/host/relcheck.tsv]

After `make host-census`. layoutcheck.py reads the linked PS2 ELF, where an
address is only an address: cmdmenu.c's `&D_00650120[6]` is 0x00650C00, the
start of D_00650C00, so it reads as an access to D_00650C00 and is not a row.
On the host it is past the end of D_00650120's definition. This reads the
host objects' relocations instead (i386 REL: the addend is in the
instruction), where the C name is kept: every reference `name + addend` whose
address falls outside the host definition holding `name` is a row. A
reference exactly at the end is C's `&a[N]` (a loop end, a compare) and is
listed only with --all, since a call taking it as an object looks the same.

Three sources (session 71): the host objects (out/host, i386 REL); the PS2
objects (out/build, after `make`: a MIPS HI16 and the LO16s that follow it
give `%hi(name + k)` / `%lo(name + k)`, an R_MIPS_32 word holds its addend),
which keep what the host's -O1 folds or strength-reduces away; and every C
draft in nonmatchings/ that is not linked (compiled for the host into
out/host/relcheck-drafts, the ones that compile). A row says which source
found it (host / ps2 / draft). The PS2 objects of src/sdk are left out: the
port does not compile them. Only names and offsets are printed, no game bytes."""
from __future__ import annotations

import argparse
import bisect
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from elf32 import Elf  # noqa: E402
sys.path.insert(0, str(ROOT / "tools/host"))
from layoutcheck import host_names, ps2_names, runs  # noqa: E402

R_386_32 = 1
R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16 = 2, 5, 6
NAME = re.compile(r"D_[0-9A-F]{8}")

# (object, name) -> why the host is not affected: read by hand (session 70). A reference exactly at a
# definition's end (--all) was read too: all loop ends or C's &a[N], except the three made one definition.
LOOP_END = "a loop's end pointer to a field (&a[N].f, compared, never read)"
FOLDED = "an index folded into the address (a[i - k] with i >= k, or a scaled induction variable)"
REVIEWED: dict[tuple, str] = {
    ("src/ai/partyctl.nostrict.c", "D_00575528"): LOOP_END,
    ("src/coll/colobj.c", "D_004E2430"): LOOP_END,
    ("src/game/roomcache.c", "D_0052CB20"): LOOP_END,
    ("src/gfx/light.c", "D_002C5C80"): LOOP_END,
    ("src/gfx/light.nostrict.c", "D_002C5C80"): LOOP_END,
    ("src/hud/actmark.nostrict.c", "D_006626D0"): LOOP_END,
    ("src/hud/counter.c", "D_0065FD80"): LOOP_END,
    ("src/hud/counter.nostrict.c", "D_0065FCA0"): LOOP_END,
    ("src/hud/counter.nostrict.c", "D_0065FD80"): LOOP_END,
    ("src/hud/dmgnum.c", "D_00662A30"): LOOP_END,
    ("src/hud/dmgnum.nostrict.c", "D_00662950"): LOOP_END,
    ("src/hud/gauge.nofill.c", "D_00651D70"): LOOP_END,
    ("src/hud/marker.nofill.c", "D_00651210"): LOOP_END,
    ("src/hud/notice.nostrict.c", "D_006560F0"): LOOP_END,
    ("src/hud/popup.nostrict.c", "D_00656430"): LOOP_END,
    ("src/obj/class1b.nostrict.c", "D_0054F750"): LOOP_END,
    ("src/obj/effobj.c", "D_00547C00"): LOOP_END,
    ("src/util/heap.nostrict.c", "D_004F45B0"): LOOP_END,
    ("src/gfx/grideff.c", "D_00494C00"): "a down-counting loop's end (compared, never read)",
    ("src/game/cmdmenu.nostrict_nofill.c", "D_00524F80"): FOLDED,
    ("src/gfx/grideff.c", "D_00494AA0"): FOLDED,
    ("src/gfx/grideff.c", "D_00494B20"): FOLDED,
    ("src/gfx/mdlpkt.c", "D_00494F20"): FOLDED,
    ("src/list/list.c", "D_006310C8"): FOLDED,
    ("src/list/list.c", "D_00631148"): FOLDED,
    ("src/list/list.c", "D_006311C8"): FOLDED,
    ("src/list/list.c", "D_00631248"): FOLDED,
    ("src/menu/journal_s0.c", "D_006433F8"): FOLDED,
    ("src/menu/journal_s1.c", "D_006436A8"): FOLDED,
    ("src/menu/journal_s3.nofill.c", "D_00643430"): FOLDED,
    ("src/menu/loadmenu.c", "D_006450C0"): "D_006450C0[save number - 1], the number from the name's digits (1..99)",
    ("src/menu/partymdl.c", "D_003F31D0"): FOLDED,
    ("src/model/motion.nostrict.c", "D_00573F10"):
        "D_00573F10[n2C - 1][3]: the last bone's matrix, n2C >= 1 (the root, [0], is always set; session 71)",
    ("src/msgwin/msgwin.c", "D_0062A1F0"): FOLDED,
    ("src/ppp/ryjmbprize.nostrict.c", "D_0061E310"): FOLDED,
    ("src/screen/wave.c", "D_00631620"): "(i + 2098) << 4 strength-reduced: the strip loop stays inside the packet",
    ("src/screen/wave.nofill.c", "D_00631620"): "the strip loop's induction variable (as wave.c)",
    ("src/vm/objscript.c", "D_00514F20"): "(p - D_00514F20) / 2048: a division's rounding, not an access",
    ("nonmatchings/session12/s12w6__0010d470_179w_tlcs.c", "D_00495280"):
        "func_0010d470's draft (unmatched): the width table's last glyph code, as layoutcheck's D_003C5830 row",
}

# (function, name) -> why: every draft of that function, linked or not (the unlinked drafts, session 71)
DRAFT_FN = re.compile(r"__([0-9a-f]{8})_")
REVIEWED_DRAFTS = {
    ("0010d470", "D_00495280"): "func_0010d470's drafts: the width table's last glyph code (as the linked draft)",
    ("001636d0", "D_00573F10"): "func_001636d0's drafts: D_00573F10[s1 - 1][3] for a bone number counted from 1",
}


def host_defs(exe):
    """(sorted starts, [(start, end, name)]) of the sized data definitions, and name -> host address"""
    nm = subprocess.run(["nm", "-S", str(exe)], capture_output=True, text=True, check=True).stdout
    defs, addr = [], {}
    for ln in nm.splitlines():
        f = ln.split()
        if len(f) == 4 and f[2] in "DdBbRr":
            a, s = int(f[0], 16), int(f[1], 16)
            if s:
                defs.append((a, a + s, f[3]))
            addr[f[3]] = a
        elif len(f) == 3 and f[1] in "DdBbRr":
            addr[f[2]] = int(f[0], 16)
    defs.sort()
    return [d[0] for d in defs], defs, addr


def host_refs(o):
    """(name, addend) of every i386 R_386_32 reference in an object's code and initialised data"""
    e = Elf.load(o)
    syms = e.symbols()
    for sec in e.sections:
        if sec.type != 1 or not (sec.flags & 4) and not sec.name.startswith(".data"):
            continue  # code (SHF_EXECINSTR) and initialised data (pointer tables)
        body = e.section_bytes(sec)
        for off, typ, si in e.relocations(sec):
            if typ == R_386_32 and si < len(syms):
                yield syms[si].name, struct.unpack_from("<i", body, off)[0]


def ps2_refs(o):
    """(name, addend) of a MIPS object's references: HI16 + the LO16s after it (REL: the halves are in the
    instructions; lui's half is %hi, rounded for the signed %lo), and R_MIPS_32 words"""
    e = Elf.load(o)
    syms = e.symbols()
    for sec in e.sections:
        if sec.type != 1 or not sec.size:
            continue
        body = e.section_bytes(sec)
        hi = {}  # symbol index -> the last HI16's half
        for off, typ, si in e.relocations(sec):
            if si >= len(syms):
                continue
            n = syms[si].name
            if typ == R_MIPS_32:
                yield n, struct.unpack_from("<i", body, off)[0]
            elif typ == R_MIPS_HI16:
                hi[si] = struct.unpack_from("<I", body, off)[0] & 0xFFFF
            elif typ == R_MIPS_LO16 and si in hi:
                lo = struct.unpack_from("<I", body, off)[0] & 0xFFFF
                add = ((hi[si] << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
                yield n, add - (1 << 32) if add & 0x80000000 else add


def compile_drafts():
    """Compile the C drafts in nonmatchings/ that shift/drafts.tsv does not link, for the host (census.py's
    flags) into out/host/relcheck-drafts; ([(draft, object)], number tried)"""
    from census import CFLAGS, draft_files
    linked = set(draft_files())
    out = ROOT / "out/host/relcheck-drafts"
    todo = sorted(str(p.relative_to(ROOT)) for p in (ROOT / "nonmatchings").rglob("*.c"))
    todo = [d for d in todo if d not in linked and "/sdk_" not in "/" + d and not Path(d).name.startswith("sdk_")]
    built = []
    for d in todo:
        o = out / (d + ".o")
        o.parent.mkdir(parents=True, exist_ok=True)
        for extra in ([], ["-include", "common.h"]):  # some drafts were pasted without their #include
            p = subprocess.run([os.environ.get("HOST_CC", "gcc")] + CFLAGS + extra + ["-c", "-o", str(o), d],
                               cwd=ROOT, capture_output=True, text=True)
            if p.returncode == 0:
                built.append((d, o))
                break
    return built, len(todo)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--all", action="store_true", help="also references exactly at a definition's end")
    ap.add_argument("--no-ps2", action="store_true", help="skip the PS2 objects (out/build)")
    ap.add_argument("--no-drafts", action="store_true", help="skip the unlinked drafts in nonmatchings/")
    ap.add_argument("--tsv", type=Path)
    ap.add_argument("--exe", type=Path, default=ROOT / "out/host/kh1-host")
    a = ap.parse_args()
    starts, defs, addr = host_defs(a.exe)
    # a host run (layoutcheck.py: names that keep their PS2 distances: one definition, a data piece, a census
    # block) is one object on the host as on the PS2; a definition outside every run is its own
    ps2, hn = ps2_names(), host_names(a.exe)
    for r in runs(ps2, hn):
        h0 = r["h"]
        defs.append((h0, h0 + r["end"] - r["a"], r["names"][0]))
    defs.sort(key=lambda d: (d[0], -d[1]))
    merged = []
    for d in defs:  # keep the widest extent starting at or covering each address
        if merged and d[0] < merged[-1][1]:
            if d[1] > merged[-1][1]:
                merged[-1] = (merged[-1][0], d[1], merged[-1][2])
            continue
        merged.append(d)
    defs = merged
    starts = [d[0] for d in defs]

    def holder(x):
        i = bisect.bisect_right(starts, x) - 1
        return defs[i] if i >= 0 and x < defs[i][1] else None

    rows = {}

    def check(src, rel, n, add):
        if not NAME.fullmatch(n) or n not in addr or add == 0:
            return
        h = holder(addr[n])
        t = addr[n] + add
        if h is None or h[0] <= t < h[1]:
            return  # no sized host definition (an alias at a block's end), or inside it
        at_end = t == h[1]
        if at_end and not a.all:
            return
        key = (rel, n, add)
        if key[:2] in REVIEWED and not at_end:
            return
        m = DRAFT_FN.search(rel) if rel.startswith("nonmatchings/") else None
        if m and (m.group(1), n) in REVIEWED_DRAFTS and not at_end:
            return
        th = holder(t)
        rows.setdefault(key, [h[2], h[1] - h[0], th[2] if th else "-", "end" if at_end else "past", set()])[4].add(src)

    objs = sorted((ROOT / "out/host").rglob("*.o"))
    objs = [o for o in objs if "relcheck-drafts" not in o.parts]
    for o in objs:
        for n, add in host_refs(o):
            check("host", str(o.relative_to(ROOT / "out/host")).removesuffix(".o"), n, add)
    nps2 = 0
    if not a.no_ps2:
        for o in sorted((ROOT / "out/build").rglob("*.o")):
            rel = str(o.relative_to(ROOT / "out/build")).removesuffix(".o")
            if rel.startswith("src/sdk/") or rel.startswith("src/asm/"):
                continue
            nps2 += 1
            for n, add in ps2_refs(o):
                check("ps2", rel, n, add)
    nd = (0, 0)
    if not a.no_drafts:
        built, tried = compile_drafts()
        nd = (len(built), tried)
        for d, o in built:
            for n, add in host_refs(o):
                check("draft", d, n, add)
    lines = ["%s\t%s\t%+#x\t%s (host 0x%x)\t%s\t%s\t%s" % (k[0], k[1], k[2], v[0], v[1], v[2], v[3],
                                                         ",".join(sorted(v[4]))) for k, v in sorted(rows.items())]
    print("\n".join(lines))
    print("# %d host objects, %d PS2 objects, %d / %d unlinked drafts compiled; %d rows%s"
          % (len(objs), nps2, nd[0], nd[1], len(rows), "" if a.all else "; --all adds references at an end"),
          file=sys.stderr)
    if a.tsv:
        a.tsv.parent.mkdir(parents=True, exist_ok=True)
        a.tsv.write_text("object\tname\taddend\tdefinition\ttarget\tkind\tsource\n" + "\n".join(lines) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
