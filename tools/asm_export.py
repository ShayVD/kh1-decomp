#!/usr/bin/env python3
"""Write functions out as assembly sources (for code that was assembly, or
inline-asm blocks, in the original: VU0 macro code, MMI string routines).

  tools/asm_export.py OUT.s func_00267328 0x002675b8 ... [--header TEXT]

Each instruction becomes `.word 0x........` with its disassembly as a
comment: modern binutils does not take the VU0 macro mnemonics, and since
every function is linked at its original address, branch, jal and %hi/%lo
words are already right. One `.section .text.<name>` per function (the
build places functions by section, docs/workflow.md). Names come from
functions.tsv."""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K  # noqa: E402


def export(names: list[str], header: str) -> str:
    cfg = K.load_config()
    reg = K.load_registry()
    by_addr = {a: s for s, a in reg.items()}
    lines = [f"/* {header} */" if header else "/* exported by tools/asm_export.py */",
             "\t.set\tnoreorder", "\t.set\tnoat"]
    for n in names:
        f = K.find_func(n if not n.startswith("0x") else "func_" + n[2:].lower().zfill(8))
        sym = by_addr.get(f.addr, f"func_{f.addr:08x}")
        body = [l for l in K.function_asm(cfg, f, by_addr).splitlines() if l.strip().startswith("/*")]
        lines += ["", f'\t.section\t.text.{sym},"ax",@progbits', f"\t.globl\t{sym}", f"\t.ent\t{sym}",
                  f"{sym}:  /* 0x{f.addr:08X} */"]
        for l in body:
            # `/* ADDR WORD */ text`
            addr, word = l.strip()[2:].split("*/")[0].split()[:2]
            text = l.split("*/", 1)[1].strip()
            lines.append(f"\t.word\t0x{word}  /* {addr} {' '.join(text.split())} */")
        lines.append(f"\t.end\t{sym}")
    return "\n".join(lines) + "\n"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("out")
    ap.add_argument("functions", nargs="+")
    ap.add_argument("--header", default="")
    a = ap.parse_args()
    Path(a.out).write_text(export(a.functions, a.header))
    return 0


if __name__ == "__main__":
    sys.exit(main())
