import subprocess, sys, re, collections, os, glob
# NOTE: written for a one-off scan in session 12; input paths point at a scratch snapshot of out/ (copy out/ and edit the paths to rerun).
SNAP = sys.argv[1]
objs = sorted(glob.glob(SNAP + "/build/**/*.o", recursive=True))
TEXT_END, DATA_END, BSS_START, BSS_END = 0x272c70, 0x494068, 0x494080, 0x675018
# registry
reg = {}
for l in open('/home/claude/kh1-decomp/out/gen/symbols.ld'):
    m = re.match(r'PROVIDE\((\S+) = 0x([0-9a-f]+)\);', l)
    if m: reg[m.group(1)] = int(m.group(2), 16)
defined = set(); undef_refs = collections.Counter(); reltypes = collections.Counter()
relsec_kind = collections.Counter(); secsizes = collections.Counter()
ref_by_type = collections.defaultdict(collections.Counter)
for o in objs:
    s = subprocess.run(['mips-linux-gnu-readelf', '-sW', o], capture_output=True, text=True).stdout
    for l in s.splitlines():
        p = l.split()
        if len(p) >= 8 and p[0].endswith(':') and p[4] in ('GLOBAL','WEAK'):
            if p[6] != 'UND' and not p[6].startswith('ABS'):
                defined.add(p[7])
    sec = subprocess.run(['mips-linux-gnu-readelf', '-SW', o], capture_output=True, text=True).stdout
    for l in sec.splitlines():
        m = re.match(r'\s*\[\s*\d+\]\s+(\S+)\s+(\S+)\s+\S+\s+\S+\s+([0-9a-f]+)', l)
        if m:
            name = m.group(1)
            k = name.split('.')[1] if name.startswith('.') and len(name.split('.'))>1 else name
            if name.startswith(('.rodata', '.data', '.sdata', '.bss', '.sbss', '.ctx', '.lit', '.text')):
                key = '.ctx' if name.startswith('.ctx') else ('.rodata.fn' if name.startswith('.rodata.') else name.split('.')[1] if name.count('.')>=1 else name)
                if name.startswith('.text.'): key='.text.fn'
                secsizes[key] += int(m.group(3), 16)
    r = subprocess.run(['mips-linux-gnu-readelf', '-rW', o], capture_output=True, text=True).stdout
    cur = None
    for l in r.splitlines():
        m = re.match(r"Relocation section '\.rel(\S+)'", l)
        if m: cur = m.group(1); continue
        p = l.split()
        if len(p) >= 5 and p[2].startswith('R_MIPS'):
            if cur.startswith(('.pdr', '.mdebug', '.ctx')): continue
            sym = p[4]
            reltypes[p[2]] += 1
            relsec_kind[cur.split('.')[1]] += 1
            ref_by_type[p[2]][sym if not sym.startswith('.') else 'SECTION'] += 1
            if not sym.startswith('.'):
                undef_refs[sym] += 1
ext = {s: n for s, n in undef_refs.items() if s not in defined}
def cls(a):
    if a is None: return 'noaddr'
    if a < 0x100000: return 'low'
    if a < TEXT_END: return 'text'
    if a < DATA_END: return 'data(file)'
    if a < BSS_START: return 'gap'
    if a < BSS_END: return 'bss'
    if a < 0x10000000: return 'beyond-image(<256M)'
    return 'hw/other'
c = collections.Counter(); cr = collections.Counter(); kinds = collections.Counter()
for s, n in ext.items():
    a = reg.get(s)
    pre = 'D_' if s.startswith('D_') else 'func_' if s.startswith('func_') else 'named'
    k = (pre, cls(a)); c[k] += 1; cr[k] += n
print('objects', len(objs), 'defined globals', len(defined))
print('external symbols referenced (not defined in src):', len(ext), 'refs', sum(ext.values()))
for k in sorted(c): print('  ', k, 'symbols', c[k], 'reloc refs', cr[k])
print('reloc types', dict(reltypes))
print('reloc by section kind', dict(relsec_kind))
print('section byte totals', dict(secsizes))
# func_ refs defined in src
fd = [s for s in undef_refs if s in defined and s.startswith('func_')]
print('func_ placeholders referenced that ARE defined in src (resolve to new code):', len(fd))
open(SNAP+'/../ext_syms.tsv','w').write(''.join(f"{s}\t{reg.get(s,0):08x}\t{n}\n" for s,n in sorted(ext.items(), key=lambda kv: reg.get(kv[0],0))))
# R_MIPS_32 in data/rodata against what
print('R_MIPS_32 targets: section-relative', ref_by_type['R_MIPS_32'].get('SECTION',0), 'symbols', sum(v for k,v in ref_by_type['R_MIPS_32'].items() if k!='SECTION'))
