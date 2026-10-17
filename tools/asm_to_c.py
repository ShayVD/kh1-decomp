#!/usr/bin/env python3
"""Write leaf functions that are one inline-asm block in the original (the
game's VU0 macro helpers) as C: one `__asm__ volatile` holding the body,
the arguments passed in as operands, the result taken out of v0.

  tools/asm_to_c.py OUT.c func_001627d0 0x001627e8 ... [--try]

ee-as wants VU0 operands its own way (`R`, `Q`, `I`, `ACC`, no `$`;
docs/workflow.md). ee-as fills the final `jr ra` delay slot itself (an
instruction after the block moves into it), so a body without branches is
written as it is minus `jr ra`; one with branches is written under
`.set noreorder` with its delay slots, and the instruction in the final
delay slot (if any) goes after `.set reorder`. With --try each function is
compiled and compared (tools/autodecomp.py try); only matches are written.
Float arguments come in as "f" operands; a float result that the
original moves out of v0 (`mtc1 v0,$f0` before `jr ra`) is an "=r" float
output. Functions this does not handle (stack frame, calls, $at)
are reported and skipped."""
import argparse
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
ABI = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
       "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"]
REGNO = {n: i for i, n in enumerate(ABI)}
BRANCH = re.compile(r"^(b|bc[0-2][ft]l?|beq|bne|beql|bnel|blez|bgtz|bltz|bgez|blezl|bgtzl|bltzl|bgezl|"
                    r"beqz|bnez|beqzl|bnezl|j)$")


def parse(cfg, name: str, by_addr):
    f = K.find_func(name)
    text = K.function_asm(cfg, f, by_addr)
    out = []
    for line in text.splitlines():
        s = line.strip()
        if s.startswith(".L") and s.endswith(":"):
            out.append(("label", s[:-1]))
        elif s.startswith("/*"):
            ins = s.split("*/", 1)[1].strip()
            op, _, args = ins.partition(" ")
            out.append(("insn", op, args.strip()))
    return f, out


def gpr_uses(args: str, op: str):
    """(read, written) GPR numbers of one instruction, from its text."""
    regs = [m for m in re.findall(r"\$([a-z]+[0-9]?|zero)\b", args) if m in REGNO]
    nums = [REGNO[r] for r in regs]
    if not nums or op == "jr":
        return set(nums), set()
    stores = op in ("sw", "sd", "sq", "sh", "sb", "sqc2", "swc1", "sdc1", "ctc2", "qmtc2", "mtc1", "mtc0",
                    "sdl", "sdr", "swl", "swr") or BRANCH.match(op)
    if stores or op in ("lqc2", "lwc1", "ldc1"):
        return set(nums), set()
    return set(nums[1:]), {nums[0]}


def fpr_uses(args: str, op: str):
    """(read, written) FPU register numbers of one instruction."""
    nums = [int(n) for n in re.findall(r"\$f(\d+)\b", args)]
    if not nums:
        return set(), set()
    if op in ("swc1", "sdc1", "mfc1", "cfc1") or op.startswith("c."):
        return set(nums), set()
    if op in ("lwc1", "ldc1", "mtc1", "ctc1"):
        return set(), set(nums[:1])
    return set(nums[1:]), {nums[0]}


def convert(name: str, f, body):
    insns = [b for b in body if b[0] == "insn"]
    while insns and insns[-1][1] == "nop" and len(insns) > 2 and insns[-2][1] == "nop":
        insns.pop()  # alignment padding
    if len(insns) < 2 or (insns[-2][1], insns[-2][2]) != ("jr", "$ra"):
        return None, "does not end in jr ra"
    for _, op, args in insns[:-2]:
        if op in ("jal", "jalr", "jr", "syscall") or "$sp" in args or "$at" in args or "$ra" in args:
            return None, f"uses {op} {args}"
    # a float result moved out of v0 by gcc (an "=r" float output)
    fret_gpr = False
    body = list(body)
    tail = [("insn", "mtc1", "$v0,$f0")]
    if insns[-1][1:] == ("mtc1", "$v0,$f0") or (insns[-1][1] == "nop" and insns[-3][1:] == ("mtc1", "$v0,$f0")):
        fret_gpr = True
        i = len(insns) - 1 if insns[-1][1] == "mtc1" else len(insns) - 3
        drop = insns[i]
        insns = insns[:i] + insns[i + 1:]
        if insns[-1][1] == "jr":
            insns.append(("insn", "nop", ""))
        body = [b for b in body if b is not drop]
    written, args_in, fwritten, fargs_in = set(), set(), set(), set()
    for _, op, a in insns:
        r, w = gpr_uses(a, op)
        args_in |= {x for x in r - written if 4 <= x <= 11}
        written |= w
        r, w = fpr_uses(a, op)
        fargs_in |= {x for x in r - fwritten if 12 <= x <= 19}
        fwritten |= w
    nargs = max(args_in) - 3 if args_in else 0
    nfargs = max(fargs_in) - 11 if fargs_in else 0
    ret = 2 in written and not (0 in fwritten)
    fret = fret_gpr or (0 in fwritten)
    if fret_gpr and 2 not in written:
        return None, "float result not from v0"
    clob = sorted(written - {2, 0} - set(range(4, 4 + nargs)))
    fclob = sorted(fwritten - ({0} if fret and not fret_gpr else set()) - set(range(12, 12 + nfargs)))
    has_branch = any(BRANCH.match(op) for _, op, _ in insns)
    # operand numbers: the output %0 (v0 or $f0), then the arguments
    opnum, fopnum = {}, {}
    nout = 1 if (ret or fret) else 0
    if ret or fret_gpr:
        opnum[2] = 0
    elif fret:
        fopnum[0] = 0
    for i in range(nargs):
        opnum[4 + i] = i + nout
    for i in range(nfargs):
        fopnum[12 + i] = i + nout + nargs
    labels = {}

    def fix(op, a):
        a = re.sub(r"\$ACC\w*", "ACC", a)
        a = re.sub(r"\$([RQI])\b", r"\1", a)

        def reg(m):
            n = REGNO[m.group(1)]
            return f"%{opnum[n]}" if n in opnum else f"${n}"
        a = re.sub(r"\$([a-z]+[0-9]?|zero)\b(?![0-9a-z])", lambda m: reg(m) if m.group(1) in REGNO else m.group(0), a)
        a = re.sub(r"\$f(\d+)\b", lambda m: f"%{fopnum[int(m.group(1))]}" if int(m.group(1)) in fopnum else m.group(0), a)
        a = a.replace(",", ", ")
        return f"{op} {a}".strip()

    for b in body:
        if b[0] == "label":
            labels[b[1]] = f"{name}_{b[1][2:].lower()}"
    lines = []
    delay = insns[-1]
    n_print = len(insns) - 2
    # branches keep their own delay slots: noreorder up to the last one's
    last_br = max((i for i, b in enumerate(insns[:n_print]) if BRANCH.match(b[1])), default=-1)
    k = 0
    if has_branch:
        lines.append(".set noreorder")
    for b in body:
        if b[0] == "insn":
            if k >= n_print:
                break
            lines.append(fix(b[1], b[2]))
            if k == last_br + 1 and has_branch:
                lines.append(".set reorder")
            k += 1
        else:
            lines.append(labels[b[1]] + ":")
    if has_branch and last_br + 1 >= n_print:
        lines.append(".set reorder")
    lines = [re.sub(r"\.L[0-9A-F]+", lambda m: labels[m.group(0)], l) for l in lines]
    if delay[1] != "nop":
        lines.append(fix(delay[1], delay[2]))
    params = ", ".join([f"s32 a{i}" for i in range(nargs)] + [f"f32 f{i}" for i in range(nfargs)]) or "void"
    rtype = "f32" if fret else "s32" if ret else "void"
    asm = "\n".join(f'        "{l}\\n"' for l in lines)
    outs = '"=&r"(ret)' if (ret or fret_gpr) else '"=&f"(ret)' if fret else ""
    ins = ", ".join([f'"r"(a{i})' for i in range(nargs)] + [f'"f"(f{i})' for i in range(nfargs)])
    clobs = ", ".join([f'"${c}"' for c in clob] + [f'"$f{c}"' for c in fclob] + ['"memory"'])
    src = f"{rtype} {name}({params}) {{\n"
    if ret or fret:
        src += f"    {rtype} ret;\n\n"
    src += f"    __asm__ volatile(\n{asm}\n        : {outs}\n        : {ins}\n        : {clobs});\n"
    if ret or fret:
        src += "    return ret;\n"
    src += "}\n"
    return src, None


def try_match(name: str, src: str, out_dir: Path) -> bool:
    tmp = out_dir / f".asm_to_c_{name}.c"
    tmp.write_text('#include "common.h"\n\n' + src)
    try:
        r = subprocess.run([sys.executable, str(ROOT / "tools/autodecomp.py"), "try", name, "--file", str(tmp),
                            "--out-dir", str(out_dir)], capture_output=True, text=True, cwd=ROOT)
    finally:
        tmp.unlink()
    return " MATCH " in r.stdout


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("out")
    ap.add_argument("functions", nargs="+")
    ap.add_argument("--try", dest="try_", action="store_true")
    ap.add_argument("--header", default="")
    a = ap.parse_args()
    cfg = K.load_config()
    by_addr = {v: s for s, v in K.load_registry().items()}
    out = Path(a.out)
    parts = [f"/* {a.header} */\n#include \"common.h\"\n" if a.header else "#include \"common.h\"\n"]
    for n in a.functions:
        n = n if not n.startswith("0x") else "func_" + n[2:].lower().zfill(8)
        f, body = parse(cfg, n, by_addr)
        name = by_addr.get(f.addr, f"func_{f.addr:08x}")
        src, why = convert(name, f, body)
        if src is None:
            print(f"{name}: skipped ({why})")
            continue
        if a.try_ and not try_match(name, src, out.parent):
            print(f"{name}: no match")
            continue
        print(f"{name}: ok")
        parts.append(src)
    out.write_text("\n".join(parts))
    return 0


if __name__ == "__main__":
    sys.exit(main())
