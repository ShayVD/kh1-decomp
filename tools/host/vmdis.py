#!/usr/bin/env python3
"""Disassemble the field's script VMs at one frame of a host run (session 137).

    python3 -I tools/host/vmdis.py FRAME [--pad FILE] [--iso DISC] [--only K]

runs out/host/kh1-host under gdb to FRAME (KH1_HOST_CD=go, the ISO from --iso or
KH1_HOST_ISO, the pad script from --pad or KH1_HOST_PAD), then for each VM of the
table D_0038D170 (count D_0039A570; src/vm/script_vm.c) prints its entity id, pc,
entity position and its code, label by label (VmRec.lbl, `n` labels), with the
opcode names of D_0037A198 (script_vm.c's comments), opcode 1's operations
(vm_calc.c) and opcode 24's library functions (D_003D9FE0, vm_lib.c).
The pc is marked `<<`.  A label that loops on `waitvm` or a library call that
returns 4 is where the VM waits.  Variables: push8 / pop8 below 0x800 are the save
block's bytes (func_00232cc0(1)), 0x900-0xAFF the VM's own, 0xB00-0xC7F the save
block's from +0x900, 0xC80-0xD3F D_003C2D30's (script_vm.c func_001c0f30).
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
EXE = os.path.join(ROOT, "out", "host", "kh1-host")
OPS = ["nop", "calc", "jmp", "jz", "nop4", "end", "sel", "pushsel==", "selprev", "push", "pushreg", "popreg",
       "push8", "pop8", "push16", "pop16", "push32", "pop32", "op18", "op19", "op20", "pusharg", "jumpvm",
       "waitvm", "lib", "clrvm", "op26", "op27", "op28", "op29", "op30", "op31"]
CALC = "add sub mul div mod neg eq gt ge lt le ne and or xor not shr shl".split()
SPAN = 0x4000


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("frame", type=int)
    ap.add_argument("--pad", default=os.environ.get("KH1_HOST_PAD"))
    ap.add_argument("--iso", default=os.environ.get("KH1_HOST_ISO"))
    ap.add_argument("--only", type=int, help="one VM's code (the others' state lines only)")
    a = ap.parse_args()
    tmp = tempfile.mkdtemp(prefix="vmdis")
    g = ["handle SIGSEGV nostop noprint pass", "set pagination off",
         "break kh1_host_vblank if frames == %d" % a.frame, "run",
         'printf "count %d\\n", D_0039A570']
    for k in range(32):
        v = "((VmRec*)&D_0038D170)[%d]" % k
        g += ["if %d < D_0039A570" % k,
              'printf "vm %d %%x %%d %%d %%d", %s.x0, %s.pc, %s.n, %s.obj != 0' % (k, v, v, v, v),
              "if %s.obj" % v,
              'printf " %%.0f %%.0f %%.0f", ((float*)((char*)%s.obj+0x10))[0], ((float*)((char*)%s.obj+0x10))[1], '
              '((float*)((char*)%s.obj+0x10))[2]' % (v, v, v),
              "end", 'printf "\\n"',
              'printf "lbl %d"' % k] + ['printf " %%d", %s.lbl[%d]' % (v, i) for i in range(64)] + [
              'printf "\\n"',
              "dump binary memory %s/vm%d.bin %s.code %s.code+%d" % (tmp, k, v, v, SPAN),
              "end"]
    g.append("x/1024a &D_003D9FE0")
    open(os.path.join(tmp, "dump.gdb"), "w").write("\n".join(g) + "\n")
    env = dict(os.environ, KH1_HOST_CD="go", KH1_HOST_FRAMES=str(a.frame + 1), KH1_HOST_QUIET="1")
    if a.pad:
        env["KH1_HOST_PAD"] = a.pad
    if a.iso:
        env["KH1_HOST_ISO"] = a.iso
    out = subprocess.run(["gdb", "-batch", "-x", os.path.join(tmp, "dump.gdb"), EXE], env=env, cwd=ROOT,
                         capture_output=True, text=True).stdout
    lib, state, lbls = [], {}, {}
    for l in out.splitlines():
        if "<D_003D9FE0" in l:
            lib += re.findall(r"0x[0-9a-f]+(?: <([^>]+)>)?", l.split(":", 1)[1])
        elif l.startswith("vm "):
            f = l.split()
            state[int(f[1])] = f[2:]
        elif l.startswith("lbl "):
            f = l.split()
            lbls[int(f[1])] = [int(x) for x in f[2:]]
    if not state:
        print("vmdis: no VM table at frame %d (gdb said: %s)" % (a.frame, out.strip().splitlines()[-1:]), file=sys.stderr)
        return 1
    for k in sorted(state):
        x0, pc, n, has, *pos = state[k]
        pc, n = int(pc), int(n)
        print("==== vm%d  entity %s  pc %d  labels %d%s" % (k, x0, pc, n, ("  at " + " ".join(pos)) if pos else ""))
        if a.only is not None and a.only != k:
            continue
        b = open(os.path.join(tmp, "vm%d.bin" % k), "rb").read()
        starts = {lbls[k][i]: i for i in range(min(n, 64))}
        last = max(starts) if starts else 0
        for p in range(len(b) // 4):
            if p in starts:
                print("  label %d:" % starts[p])
            w = b[p * 4:p * 4 + 4]
            op = w[3] - 256 if w[3] > 127 else w[3]
            arg = w[0] | (w[1] << 8) | ((w[2] - 256 if w[2] > 127 else w[2]) << 16)
            s = OPS[op] if 0 <= op < 32 else "?%d" % op
            if op == 1:
                s += " " + (CALC[arg] if 0 <= arg < 18 else str(arg))
            elif op == 24:
                s += " %d %s" % (arg, (lib[arg] or "?") if 0 <= arg < len(lib) else "?")
            elif op in (2, 3):
                s += " -> %d" % (p + arg)
            elif op != 5:
                s += " %d" % arg
            if op != 5 or p in starts:
                print("  %5d  %s%s" % (p, s, "   <<" if p == pc else ""))
            if (op == 5 and p >= last) or not 0 <= op < 32:
                break
    return 0


if __name__ == "__main__":
    sys.exit(main())
