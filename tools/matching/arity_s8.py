# arity.py FUNC...: argument registers read before written (linear scan, ignoring branches)
import subprocess, sys, re
ARGS = ['$a0','$a1','$a2','$a3','$t0','$t1','$t2','$t3','$f12','$f13','$f14','$f15']
for fn in sys.argv[1:]:
    out = subprocess.run(['python3','/home/claude/kh1-decomp/tools/kh1tool.py','asm',fn],capture_output=True,text=True,cwd='/home/claude/kh1-decomp').stdout
    written=set(); read=[]; ret=False
    for l in out.split('\n'):
        m = re.match(r'\s*/\* \w+ \w+ \*/\s+(\S+)\s*(.*)', l)
        if not m: continue
        op, a = m.group(1), [x.strip() for x in m.group(2).split(',')]
        regs = [re.findall(r'\$\w+', x) for x in a]
        if op in ('sw','sd','sb','sh','swc1','sq','beq','bne','beql','bnel','jr','mtc1','bnez','beqz','bgez','bltz','blez','bgtz','bnezl','beqzl','mult') or op.startswith('c.') or op.startswith('b') and op not in ('break',):
            srcs = sum(regs, []); dst = []
            if op == 'mtc1': srcs, dst = regs[0], regs[1]
            if op == 'mult' and len(regs) == 3: srcs, dst = regs[1]+regs[2], regs[0]
        else:
            dst = regs[0] if regs else []; srcs = sum(regs[1:], [])
        for r in srcs:
            if r in ARGS and r not in written and r not in read: read.append(r)
        for r in dst: written.add(r)
    print(fn, ' '.join(read))
