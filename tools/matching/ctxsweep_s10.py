# ctxsweep_s10.py (session 10, r2_10): sweeps CONTEXT_ONLY {} callee stubs (each, all, all-but-one) and void<->s32 callee returns over a list of drafts; edit the paths below before use.
# sweep.py: lever 1 (CONTEXT_ONLY {} stubs for callees) + lever 2 (callee return type flips) over drafts.
# usage: WDIR=... python3 sweep.py drafts.txt [only_addr...]
import os, sys, re, subprocess, tempfile, difflib, json, shutil
from pathlib import Path
ROOT = Path('/home/claude/kh1-decomp'); sys.path.insert(0, str(ROOT/'tools'))
import kh1tool as K, autodecomp as A
from elf32 import Elf
A._init(); cfg = A._cfg; orig = K.require_orig(cfg); reg = K.load_registry()
W = Path(os.environ.get('WDIR', '/tmp/claude-0/s10/r2_10'))
TD = Path(tempfile.mkdtemp(prefix='kh1sw_', dir=str(W)))
import atexit; atexit.register(shutil.rmtree, TD, True)

def check(src, only, ro=None, extra=()):
    src = Path(src).resolve(); fl = K.flags_for(cfg, str(src.relative_to(ROOT)))
    cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
    asm, obj, out = TD/'c.s', TD/'c.o', TD/'c.elf'
    r = subprocess.run([str(cc), "-S", "-x", "c", *fl.cflags.split(), *fl.ccflags.split(), *extra, "-ffunction-sections", f"-I{ROOT/'include'}", f"-I{src.parent}", "-o", str(asm), str(src)], capture_output=True, text=True, timeout=600)
    if r.returncode: return None, 'cc: ' + r.stderr[-300:]
    text = K.split_rodata(asm.read_text()); text = K.no_fill(text) if fl.no_fill else text
    asm.write_text(text)
    r = subprocess.run([str(K.TOOLCHAIN_DIR / (fl.as_compiler or fl.compiler) / "bin" / "ee-gcc"), "-c", "-x", "assembler", *fl.cflags.split(), "-o", str(obj), str(asm)], capture_output=True, text=True)
    if r.returncode: return None, 'as: ' + r.stderr[-300:]
    K.fix_object(obj); elf = Elf.load(obj)
    funcs = [s.name[6:] for s in elf.sections if s.name.startswith('.text.')]
    defs = []
    for u in [s.name for s in elf.symbols() if s.shndx == 0 and s.name]:
        a = A.resolve(u, reg)
        if a is None: return None, 'unresolved ' + u
        defs += ["--defsym", f"{u}=0x{a:08x}"]
    secs = ''.join(f"  .f_{fn} 0x{A.resolve(fn, reg):08x} : {{ *(.text.{fn}) }}\n" for fn in funcs if A.resolve(fn, reg) is not None)
    rod = f"  .r 0x{ro} : {{ *(.rodata*) }}\n" if ro else ""
    other = "*(.text .data .bss)" if ro else "*(.text .data .bss .rodata*)"
    (TD/'c.ld').write_text("SECTIONS {\n" + secs + rod + "  .ctx 0x0f000000 : { *(.ctx .ctx.*) }\n  .other 0x40000000 : { " + other + " }\n  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) } }\n")
    r = subprocess.run([f"{K.BINUTILS}ld", "-EL", "--no-warn-mismatch", "-e", "0", "-o", str(out), "-T", str(TD/'c.ld'), *defs, str(obj)], capture_output=True, text=True)
    if r.returncode: return None, 'ld: ' + r.stderr[-300:]
    L = Elf.load(out)
    for fn in funcs:
        a = A.resolve(fn, reg)
        if a != only: continue
        f = A._layout[a]
        ours = L.section_bytes(L.section(f".f_{fn}")); theirs = orig.read(f.addr, f.size)
        wo = [ours[i:i+4] for i in range(0, len(ours), 4)]; wt = [theirs[i:i+4] for i in range(0, len(theirs), 4)]
        sm = difflib.SequenceMatcher(None, wo, wt, autojunk=False)
        m = sum(b.size for b in sm.get_matching_blocks())
        pos = sum(1 for i in range(min(len(wo), len(wt))) if wo[i] != wt[i])
        global LAST; LAST = (ours, theirs, a)
        exact = ours + bytes(max(0, f.size - len(ours))) == theirs and len(ours) <= f.size
        mm = re.search(r'\.ent\s+' + fn + r'\b(.*?)\.end\s+' + fn, text, re.S)
        import hashlib; h = hashlib.md5((mm.group(1) if mm else '').encode()).hexdigest()[:6]
        return (max(len(wo), len(wt)) - m, pos, len(ours), f.size, exact, h), None
    return None, 'nofunc'

def mode_of(head, addr):
    for m in re.finditer(r'\b(hand|sdk)/([a-z0-9_]+)', head):
        d = ROOT/'src'/m.group(1)/m.group(2)
        if d.is_dir(): return f"{m.group(1)}/{m.group(2)}"
    return 'hand'

def ro_of(head):
    m = re.search(r'(?:rodata|rr(?:\.py)?|RO=|jtbl_)\s*(?:jtbl_)?(?:at\s+)?(?:0x)?([0-9A-Fa-f]{8})', head)
    if m and 0x480000 <= int(m.group(1), 16) < 0x4c0000: return m.group(1).lower()
    return None

KW = set('void char short int long float double signed unsigned const volatile struct union enum register static extern inline'.split())
def typedefs(text):
    t = set(re.findall(r'typedef[^;{}]*?\b(\w+)\s*(?:\[[^\]]*\])?\s*;', text))
    t |= set(re.findall(r'}[^;{}]*?\b(\w+)\s*(?:,\s*\*?\s*\w+\s*)*;', text))
    t |= set(re.findall(r'typedef[^;]*?\(\s*\*\s*(\w+)\s*\)', text))
    return t
COMMON = (ROOT/'include/common.h').read_text()
TD_COMMON = typedefs(COMMON) | {'u8','s8','u16','s16','u32','s32','u64','s64','f32','f64','u128','s128'}

def name_params(params, tds):
    ps = []; depth = 0; cur = ''
    for ch in params:
        if ch == '(' : depth += 1
        if ch == ')' : depth -= 1
        if ch == ',' and depth == 0: ps.append(cur); cur = ''
        else: cur += ch
    ps.append(cur); out = []
    for i, p in enumerate(ps):
        s = p.strip()
        if s in ('void', '...', ''): out.append(s); continue
        if '(' in s:  # function pointer: (*)(...) or (*name)(...)
            if re.search(r'\(\s*\*\s*\)', s): s = re.sub(r'\(\s*\*\s*\)', f'(*p{i})', s, count=1)
            out.append(s); continue
        arr = ''
        m = re.match(r'(.*?)(\s*(\[[^\]]*\])+)$', s)
        if m: s, arr = m.group(1), m.group(2)
        toks = re.findall(r'\w+|\*', s)
        last = toks[-1] if toks else ''
        named = len(toks) >= 2 and last != '*' and last not in KW and (last not in tds or toks[-2] == '*') and not (len(toks) >= 2 and toks[-2] in ('struct', 'union', 'enum'))
        out.append(s + arr if named else f'{s} p{i}{arr}')
    return ', '.join(out)

def find_def(text, name):
    # start index of a top-level definition of name (not a prototype)
    for m in re.finditer(r'(?m)^[A-Za-z_][^;{}\n]*\b' + name + r'\s*\(', text):
        j = m.end(); depth = 1
        while j < len(text) and depth: depth += {'(': 1, ')': -1}.get(text[j], 0); j += 1
        k = j
        while k < len(text) and text[k] in ' \t\n': k += 1
        if k < len(text) and text[k] == '{':
            d = 0; e = k
            while e < len(text):
                if text[e] == '{': d += 1
                elif text[e] == '}':
                    d -= 1
                    if d == 0: break
                e += 1
            return m.start(), k, e + 1
    return None

def find_decl(text, name):
    for m in re.finditer(r'(?m)^([ \t]*(?:extern\s+)?)([A-Za-z_][^;{}()\n#=]*?)\b' + name + r'\s*\(', text):
        j = m.end(); depth = 1
        while j < len(text) and depth: depth += {'(': 1, ')': -1}.get(text[j], 0); j += 1
        k = j
        while k < len(text) and text[k] in ' \t': k += 1
        if k < len(text) and text[k] == ';':
            return m.start(), k + 1, m.group(2).strip(), text[m.end():j-1]
    return None

def callees(text, addr, TN):
    d = find_def(text, TN)
    if not d: return None, []
    body = text[d[1]:d[2]] if not os.environ.get('WHOLE') else text
    names = []
    for n in re.findall(r'\b([A-Za-z_]\w*)\s*\(', body):
        if n in names or n == TN or n in KW or n in ('if', 'while', 'for', 'switch', 'return', 'sizeof', '__asm__', 'asm', '__builtin_expect'): continue
        if find_def(text, n): continue
        if n.startswith('func_') or find_decl(text, n): names.append(n)
    return d, names

def ret_type(rt):
    return re.sub(r'\b(extern|static|inline|__inline__|CONTEXT_ONLY)\b', '', rt).strip()

def stub(text, d, n, tds):
    """return text with a CONTEXT_ONLY {} stub for n, or None"""
    if find_def(text, n): return None
    dc = find_decl(text, n)
    if dc:
        s, e, rt, params = dc
        rt = ret_type(rt)
        return text[:s] + f'CONTEXT_ONLY {rt} {n}({name_params(params, tds)}) {{}}' + text[e:]
    if not n.startswith('func_'): return None
    return text[:d[0]] + f'CONTEXT_ONLY s32 {n}() {{}}\n' + text[d[0]:]

def flip(text, d, n):
    if find_def(text, n): return None
    dc = find_decl(text, n)
    if dc:
        s, e, rt, params = dc
        pre = re.match(r'\s*(?:extern\s+)?', text[s:]).group(0)
        rt2 = ret_type(rt)
        new = 's32' if rt2 == 'void' else 'void'
        if rt2 not in ('void', 's32', 'int', 'u32', 'signed int', 'unsigned int') and not rt2.endswith('*'): return None
        t = text[:s] + f'{pre}{new} {n}({params});' + text[e:]
        dc2 = find_decl(t[s + len(pre) + len(new) + 2:], n)
        if dc2:
            off = s + len(pre) + len(new) + 2
            s2, e2, rt2b, params2 = dc2
            pre2 = re.match(r'\s*(?:extern\s+)?', t[off+s2:]).group(0)
            t = t[:off+s2] + f'{pre2}{new} {n}({params2});' + t[off+e2:]
        return t
    if not n.startswith('func_'): return None
    return text[:d[0]] + f'void {n}();\n' + text[d[0]:]

def main():
    lines = [l.split() for l in Path(sys.argv[1]).read_text().splitlines() if l.strip()]
    onlys = sys.argv[2:]
    res_path = W/'sweep.jsonl'
    for addr, draft in lines:
        if draft == 'NONE' or (onlys and addr not in onlys) or not (ROOT/draft).exists(): continue
        src0 = (ROOT/draft).read_text(errors='replace')
        head = src0.split('\n', 1)[0]
        mode = mode_of(head, addr); ro = ro_of(src0[:600])
        dst = ROOT/'src'/mode/f'.r2_10_sw.c'
        extra = (f'-I{(ROOT/draft).parent}',)
        tds = TD_COMMON | typedefs(src0)
        TN = 'func_' + addr
        for nm in re.findall(r'(?m)^[A-Za-z_][^;{}\n]*?\b(\w+)\s*\(', src0):
            if A.resolve(nm, reg) == int(addr, 16) and find_def(src0, nm): TN = nm; break
        d, cs = callees(src0, addr, TN)
        rec = {'addr': addr, 'draft': draft, 'mode': mode, 'ro': ro, 'callees': cs}
        def run(text, tag):
            dst.write_text(text)
            try: r, e = check(dst, int(addr, 16), ro, extra)
            except Exception as ex: r, e = None, 'exc ' + str(ex)[:200]
            if r and r[4]:
                (W/'hits').mkdir(exist_ok=True); (W/'hits'/f'{addr}_{tag}.c').write_text(text)
            return list(r) if r else e
        rec['base'] = run(src0, 'base')
        I6 = ROOT/'nonmatchings/session6'
        for pre in ('#include "common.h"\n', '#include "common.h"\n' + (I6/'w6_14__types.inc').read_text(), '#include "common.h"\n' + (I6/'w6_14__types.inc').read_text() + (I6/'w6_14__ctx6890.inc').read_text()):
            if isinstance(rec['base'], list): break
            src1 = src0.split('\n', 1)[0] + '\n' + pre + src0.split('\n', 1)[1]
            b1 = run(src1, 'base')
            if isinstance(b1, list): src0 = src1; rec['base'] = b1; rec['pre'] = pre[:40]
        d, cs = callees(src0, addr, TN); tds = TD_COMMON | typedefs(src0); rec['callees'] = cs
        if d is None or not isinstance(rec['base'], list):
            print(addr, mode, 'BASE', rec['base'], flush=True); open(res_path, 'a').write(json.dumps(rec) + '\n'); continue
        v = {}
        alltext = src0
        for n in cs:
            t = stub(src0, d, n, tds)
            if t is None: v['S:' + n] = 'skip'; continue
            v['S:' + n] = run(t, 'S_' + n)
        # all stubs together
        ok = [n for n in cs if isinstance(v.get('S:' + n), list)]
        for n in ok:
            dd = find_def(alltext, TN)
            t = stub(alltext, dd, n, tds)
            if t: alltext = t
        if len(ok) > 1: v['S:ALL'] = run(alltext, 'S_ALL')
        if len(ok) > 2:
            for drop in ok:
                t = src0
                for n in ok:
                    if n == drop: continue
                    t2 = stub(t, find_def(t, TN), n, tds); t = t2 or t
                v['S:ALL-' + drop] = run(t, 'S_ALLm_' + drop)
        for n in cs:
            t = flip(src0, d, n)
            if t is None: v['R:' + n] = 'skip'; continue
            v['R:' + n] = run(t, 'R_' + n)
            if ok:
                # flip on top of all stubs (flip the stubbed prototype)
                dd = find_def(alltext, TN)
                m = re.search(r'CONTEXT_ONLY (\w[\w\s\*]*?) ' + n + r'\(', alltext)
                if m:
                    rt = m.group(1).strip()
                    if rt in ('void', 's32', 'int', 'u32'):
                        nt = 's32' if rt == 'void' else 'void'
                        t2 = alltext[:m.start()] + f'CONTEXT_ONLY {nt} {n}(' + alltext[m.end():]
                        v['SR:' + n] = run(t2, 'SR_' + n)
        rec['v'] = v
        b = rec['base']
        better = {k: x for k, x in v.items() if isinstance(x, list) and (x[0] < b[0] or x[1] < b[1] or x[4])}
        changed = sum(1 for x in v.values() if isinstance(x, list) and x[5] != b[5]); errs = sum(1 for x in v.values() if isinstance(x, str) and x != 'skip')
        print(addr, mode, ro, 'base', b[:4], 'callees', len(cs), 'changed', changed, 'errs', errs, 'better', {k: x[:2] for k, x in better.items()}, flush=True)
        open(res_path, 'a').write(json.dumps(rec) + '\n')
    for p in (ROOT/'src').glob('**/.r2_10_sw.c'): p.unlink()
main()
