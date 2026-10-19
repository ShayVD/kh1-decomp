#!/usr/bin/env python3
"""SHIFT_DRAFTS: link the near-miss C drafts of the unmatched functions in place of
their asm exports (docs/shiftable-plan.md, "Session 14: SHIFT_DRAFTS").

  python3 -I tools/shift/drafts.py build [--out-dir DIR] [--table shift/drafts.tsv]
      compile every draft of the table with the compile rule of its `mode` directory
      (kh1.toml overrides, the same command `kh1tool gen` writes into
      out/gen/objects.mk) into DIR/<name>.o, check that it defines .text.<name> and
      nothing the shift link cannot place, and print `--draft-obj <name>=<object>` for
      each one that compiled (the shift_ld.py arguments). Failures go to stderr and to
      DIR/compile.tsv; they are not fatal (that function keeps its asm export).
  python3 -I tools/shift/drafts.py report --ref out/shift --new out/shift/m12-drafts
      static diff of every draft against the asm export it replaced: whether it
      compiled and linked, sizes, words off (LCS over the words with relocated fields
      masked), words off ignoring registers and immediates (instruction kinds only),
      and whether it calls the same functions (jal targets mapped M0 -> NEW).
      Written to NEW/drafts_report.txt and printed.

A draft is not matched code and is never counted: nothing here is built by `make`,
and the report is a static diff, not a behaviour claim. The shift link
(shift_ld.py --draft-obj) places a draft's .text.<name> where the asm export would
go (later code moves by multiples of 64 if it is longer) and its .rodata* after the
data blob, so it needs a moved mode (m1, m2, m12). Outputs go under out/ only."""
from __future__ import annotations

import argparse
import collections
import difflib
import struct
import subprocess
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TOOLS / "shift"))
import kh1tool as K  # noqa: E402
import mips  # noqa: E402
from elf32 import R_MIPS_26, R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16, Elf  # noqa: E402

TABLE = K.ROOT / "shift" / "drafts.tsv"
MASK = {R_MIPS_26: 0x03FFFFFF, R_MIPS_HI16: 0xFFFF, R_MIPS_LO16: 0xFFFF, R_MIPS_32: 0xFFFFFFFF}


def load(table: Path) -> list[dict]:
    rows = []
    for line in table.read_text().splitlines():
        if not line.strip() or line.startswith(("#", "name\t")):
            continue
        name, draft, mode, words = line.split("\t")[:4]
        rows.append(dict(name=name, draft=draft, mode=mode, words=words))
    return rows


def compile_cmd(cfg: dict, src: str, mode: str, obj: Path) -> str:
    """The `kh1tool gen` rule for a C file in `mode`, with make variables expanded."""
    fl = K.flags_for(cfg, mode + Path(src).name)
    tc = f"tools/toolchain/{fl.compiler}/bin"
    atc = f"tools/toolchain/{fl.as_compiler or fl.compiler}/bin"
    kh1 = f"{sys.executable} -I tools/kh1tool.py"
    s = obj.with_suffix(".s")
    return (f"{tc}/ee-gcc -S -x c {fl.cflags} {fl.ccflags} -ffunction-sections -Iinclude -Isrc -o {s} {src} && "
            f"{kh1} split-rodata {'--no-fill ' if fl.no_fill else ''}{s} && "
            f"{atc}/ee-gcc -c -x assembler {fl.cflags} -o {obj} {s} && {kh1} fix-obj {obj}")


def check(obj: Path, name: str) -> list[str]:
    e = Elf.load(obj)
    errs = []
    texts = [s.name for s in e.sections if s.name.startswith(".text") and s.size]
    if f".text.{name}" not in texts:
        errs.append(f"no .text.{name} (has {', '.join(texts) or 'no code'})")
    for t in texts:
        if t != f".text.{name}":
            errs.append(f"extra code section {t} (the shift link places one function per draft)")
    for s in e.sections:
        if s.size and s.flags & 2 and s.name.startswith((".data", ".sdata", ".bss", ".sbss", ".lit")):
            errs.append(f"section {s.name} (a draft must not define data)")
    return errs


def cmd_build(a) -> int:
    out_dir = a.out_dir.resolve()
    if K.OUT.resolve() not in out_dir.parents:
        sys.exit("error: --out-dir must be under out/")
    cfg = K.load_config()
    out_dir.mkdir(parents=True, exist_ok=True)
    status = []
    for r in load(a.table):
        obj = (out_dir / f"{r['name']}.o").relative_to(K.ROOT.resolve())
        p = subprocess.run(compile_cmd(cfg, r["draft"], r["mode"], obj), shell=True, cwd=K.ROOT,
                           capture_output=True, text=True)
        errs = [f"compile failed: {(p.stdout + p.stderr).strip().splitlines()[-1:]}"] if p.returncode else \
            check(K.ROOT / obj, r["name"])
        if errs:
            print(f"drafts: {r['name']} ({r['draft']}): " + "; ".join(errs), file=sys.stderr)
            status.append((r["name"], "no-compile", r["draft"], "; ".join(errs)))
            continue
        status.append((r["name"], "compiled", r["draft"], ""))
        print(f"--draft-obj {r['name']}={obj}")
    (out_dir / "compile.tsv").write_text("name\tstatus\tdraft\tnote\n" + "".join("\t".join(s) + "\n" for s in status))
    return 0


def masked_words(elf: Elf, img, addr: int, size: int) -> tuple[list[int], list[int]]:
    """Words of [addr, addr+size) with every relocated field zeroed, and the relocated jal/j targets."""
    raw = list(struct.unpack_from(f"<{size // 4}I", img.bytes(addr, size - size % 4)))
    words = list(raw)
    jumps = []
    for s in elf.sections:
        if s.name != ".text":
            continue
        for off, typ, _si in elf.relocations(s):
            if addr <= off < addr + size - size % 4:
                k = (off - addr) // 4
                words[k] &= ~MASK.get(typ, 0xFFFFFFFF) & 0xFFFFFFFF
                if typ == R_MIPS_26 and mips.op(raw[k]) in (mips.OP_J, mips.OP_JAL):
                    jumps.append(((off + 4) & 0xF0000000) | ((raw[k] & 0x3FFFFFF) << 2))
    return words, jumps


def kind(w: int) -> int:
    """Instruction kind only: the opcode, plus funct / rt selector where they pick the operation."""
    op = mips.op(w)
    if op == 0:
        return w & 0x3F
    if op == 1:
        return 0x100 | ((w >> 16) & 0x1F)
    if op in (0x10, 0x11, 0x12, 0x1C):  # COP0/COP1/COP2/MMI: format and function
        return (op << 16) | (w & 0x03E0003F)
    return op << 16


def lcs_off(a: list[int], b: list[int]) -> int:
    m = difflib.SequenceMatcher(None, a, b, autojunk=False)
    return max(len(a), len(b)) - sum(bl.size for bl in m.get_matching_blocks())


def cmd_report(a) -> int:
    from shift_cmp import Links
    rows: dict[str, dict] = {}
    for f in (a.new / "drafts" / "compile.tsv", a.new / "drafts.tsv"):
        if f.exists():
            lines = f.read_text().splitlines()
            head = lines[0].split("\t")
            for line in lines[1:]:
                d = dict(zip(head, line.split("\t")))
                rows.setdefault(d["name"], {}).update(d)
    if not rows:
        print(f"drafts: nothing to report in {a.new}")
        return 1
    L = Links(a.ref, a.new)
    by_sec = {key[1]: key for key in L.drafted}
    names = {}
    for n, v in L.nsym.items():
        if not n.startswith(("__dr_", ".")):
            names.setdefault(v, n)

    def fmt(c: collections.Counter) -> str:
        return ", ".join(f"{names.get(t, f'0x{t:08x}')}" + (f" x{n}" if n > 1 else "") for t, n in sorted(c.items())) or "-"
    out = [f"SHIFT_DRAFTS static diff ({a.new.name}): near-miss C drafts linked in place of their asm "
           f"exports. Not matched code, never counted; no behaviour claim.",
           "off: LCS over the words with relocated fields masked (max(len) - common words); kinds: the same over "
           "instruction kinds only (registers, immediates and relocations ignored); calls: jal/j targets of the "
           "asm export mapped M0 -> NEW against the draft's.",
           f"{'function':<17} {'status':<10} {'orig':>5} {'draft':>5} {'off':>5} {'kinds':>5}  calls / note"]
    linked = 0
    for name in sorted(rows, key=lambda n: (rows[n].get("addr", "~"), n)):
        r = rows[name]
        st = r.get("status", "?")
        key = by_sec.get(f".text.{name}")
        if st != "linked" or key is None:
            note = r.get("note", "") or "not in the NEW link map"
            out.append(f"{name:<17} {st if st != 'linked' else 'no-link':<10} {'':>5} {'':>5} {'':>5} {'':>5}  {note}")
            continue
        linked += 1
        ra, rsize, _ = L.ref_map[key]
        na, nsize, _ = L.new_map[key]
        ow, oj = masked_words(L.ref_elf, L.ref_img, ra, rsize)
        dw, dj = masked_words(L.new_elf, L.new_img, na, nsize)
        want = collections.Counter(min(L.amap.fwd(t)) for t in oj)
        got = collections.Counter(dj)
        calls = (f"same {sum(got.values())} jal/j targets" if want == got else
                 f"calls differ: only asm {fmt(want - got)}; only draft {fmt(got - want)}")
        out.append(f"{name:<17} {'linked':<10} {len(ow):>5} {len(dw):>5} {lcs_off(ow, dw):>5} "
                   f"{lcs_off([kind(w) for w in ow], [kind(w) for w in dw]):>5}  {calls}")
    out.append(f"{linked} of {len(rows)} drafts linked")
    text = "\n".join(out) + "\n"
    (a.new / "drafts_report.txt").write_text(text)
    print(text, end="")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    b = sub.add_parser("build")
    b.add_argument("--out-dir", type=Path, default=K.OUT / "shift" / "m12-drafts" / "drafts")
    b.add_argument("--table", type=Path, default=TABLE)
    r = sub.add_parser("report")
    r.add_argument("--ref", type=Path, default=K.OUT / "shift")
    r.add_argument("--new", type=Path, default=K.OUT / "shift" / "m12-drafts")
    a = ap.parse_args()
    return cmd_build(a) if a.cmd == "build" else cmd_report(a)


if __name__ == "__main__":
    sys.exit(main())
