import subprocess, glob, re, sys, collections
# NOTE: written for a one-off scan in session 12; input paths point at a scratch snapshot of out/ (copy out/ and edit the paths to rerun).
objs = sorted(glob.glob('/tmp/claude-0/s12/s12w15/snap/build/**/*.o', recursive=True))
hits = collections.Counter(); ex = []
for o in objs:
    if '/src/asm/' in o or o.endswith('.s.o'): continue
    out = subprocess.run(['mips-linux-gnu-objdump', '-drz', o], capture_output=True, text=True).stdout
    lines = out.splitlines(); fn=None
    for i, l in enumerate(lines):
        m = re.match(r'^[0-9a-f]+ <(\S+)>:', l)
        if m: fn = m.group(1)
        m = re.search(r'\tlui\t\w+,0x([0-9a-f]+)$', l)
        if m:
            v = int(m.group(1), 16)
            nxt = lines[i+1] if i+1 < len(lines) else ''
            if 'R_MIPS_HI16' in nxt: continue
            if 0x10 <= v <= 0x67:
                hits[v] += 1; ex.append((o.split('build/')[1], fn, hex(v)))
print('lui 0x0010..0x0067 without relocation:', sum(hits.values()))
for e in ex[:60]: print(' ', *e)
