# sc_s17.py (session 17, s17m1): score C drafts against the original with a true DP LCS.
# usage: python3 -I tools/matching/sc_s17.py FUNC MODE_DIR FILE [FILE...] [-d]
#   MODE_DIR: src/hand, src/hand/nostrict, src/hand/nofill ... (kh1.toml flags of that dir)
#   prints per file: TL <orig words unmatched> <ours unmatched> size; -d prints a diff of the last file.
import sys, os, tempfile, difflib
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
os.chdir(ROOT)
import autodecomp as A, kh1tool as K

def tlcs(a, b):
    prev = [0] * (len(b) + 1)
    for x in a:
        cur = [0] * (len(b) + 1)
        for j, y in enumerate(b):
            cur[j + 1] = prev[j] + 1 if x == y else (prev[j + 1] if prev[j + 1] > cur[j] else cur[j])
        prev = cur
    return prev[-1]

def main():
    args = [x for x in sys.argv[1:] if x not in ('-d', '-o')]
    dump = '-o' in sys.argv
    diff = '-d' in sys.argv
    fn, mode, files = args[0], args[1], args[2:]
    A.AUTO_DIR = (ROOT / mode).resolve()
    if not A.SIGS.SIGS_TSV.exists():
        A.SIGS.write(K.load_config())
    A._init()
    A._orig = K.require_orig(A._cfg)
    f = K.find_func(fn)
    sym = A._names.get(f.addr, f"func_{f.addr:08x}")
    theirs = A._orig.read(f.addr, f.size)
    tw = [theirs[i:i + 4] for i in range(0, len(theirs), 4)]
    for fp in files:
        code = Path(fp).read_text()
        A.EXTRA_INCLUDES[:] = [Path(fp).resolve().parent]
        with tempfile.TemporaryDirectory() as td:
            ok, why = A.build_and_compare(f, sym, code, Path(td))
        ours = A.LAST_BYTES
        if ok:
            print(fp, 'MATCH', flush=True); continue
        if not ours:
            print(fp, 'ERR', why, flush=True); continue
        ow = [ours[i:i + 4] for i in range(0, len(ours), 4)]
        m = tlcs(ow, tw)
        print(fp, 'TL', len(tw) - m, len(ow) - m, len(ours), flush=True)
    if dump and ours:
        for k, x in enumerate(A.disasm(ours, f.addr)):
            print('%x  %s' % (f.addr + 4 * k, x))
    if diff and ours:
        a, b = A.disasm(theirs, f.addr), A.disasm(ours, f.addr)
        sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == 'equal':
                continue
            print('--- orig %x / ours %x' % (f.addr + 4 * i1, f.addr + 4 * j1))
            for k in range(max(i2 - i1, j2 - j1)):
                x = a[i1 + k] if i1 + k < i2 else ''
                y = b[j1 + k] if j1 + k < j2 else ''
                print('   %-40s %s' % (x, y))

main()
