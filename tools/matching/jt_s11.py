# jt70.py [td] : per-case start offsets ours vs orig (from jump tables)
# (session 11, s11w70) Written for func_001f5fe0 (table 0x490c70, 55 cases); edit a0/table/count for another switch.
import sys, struct, subprocess
sys.path.insert(0, '/home/claude/kh1-decomp/tools')
from elf32 import Elf
td = sys.argv[1] if len(sys.argv) > 1 else '/tmp/claude-0/s11/s11w70/td'
a0 = 0x1f5fe0
L = Elf.load(td + '/c.elf'); sec = L.section('.r'); rb = L.section_bytes(sec)
ours = struct.unpack('<55I', rb[:220])
o = open('/home/claude/kh1-decomp/SLPS_251.98', 'rb').read()
# find file offset of vaddr via program headers
E = Elf.load('/home/claude/kh1-decomp/SLPS_251.98')
def rd(va, n):
    for ph in E.phdrs if hasattr(E, 'phdrs') else []:
        pass
    return None
import struct as S
ph_off, ph_n = S.unpack_from('<I', o, 28)[0], S.unpack_from('<H', o, 44)[0]
segs = []
for i in range(ph_n):
    t, off, va, pa, fs, ms = S.unpack_from('<6I', o, ph_off + 32 * i)
    segs.append((va, off, fs))
def fo(va):
    for v, off, fs in segs:
        if v <= va < v + fs: return off + va - v
th = S.unpack_from('<55I', o, fo(0x490c70))
rows = sorted(set([x - a0 for x in th]))
ro = sorted(set([x - a0 for x in ours]))
cases = {}
for c in range(55): cases.setdefault(th[c] - a0, []).append(c)
oc = {}
for c in range(55): oc.setdefault(ours[c] - a0, []).append(c)
print('orig:', ' '.join('%x:%s' % (k, ','.join(map(str, v))) for k, v in sorted(cases.items())))
print('ours:', ' '.join('%x:%s' % (k, ','.join(map(str, v))) for k, v in sorted(oc.items())))
print('per case (case, orig_off, ours_off, delta):')
print(' '.join('%d:%x/%x/%+d' % (c, th[c] - a0, ours[c] - a0, (ours[c] - th[c]) // 4) for c in sorted(range(55), key=lambda c: th[c])))

order = sorted(range(55), key=lambda c: th[c])
starts_t = sorted(set(th)); starts_o = sorted(set(ours))
end_t = a0 + 8488; end_o = a0 + len(L.section_bytes(L.section('.f_func_001f5fe0')))
def size(st, x, end):
    i = st.index(x); return (st[i+1] if i + 1 < len(st) else end) - x
print('sizes (case: orig ours) mismatches only:')
seen = set(); out = []
for c in order:
    if th[c] in seen: continue
    seen.add(th[c])
    a = size(starts_t, th[c], end_t) // 4; b = size(starts_o, ours[c], end_o) // 4
    out.append('%d:%d/%d%s' % (c, a, b, '' if a == b else '*'))
print(' '.join(out))
