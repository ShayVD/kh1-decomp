import sys, subprocess, os
sys.path.insert(0, '/home/claude/kh1-decomp/tools')
import autodecomp as A
import kh1tool as K
A.AUTO_DIR = A.ROOT / os.environ.get("D","src/hand")
A._init()
fl = K.flags_for(A._cfg, A._flag_path())
cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
out = '/tmp/claude-0/s/c08/dump'
os.makedirs(out, exist_ok=True)
src = os.path.abspath(sys.argv[1])
r = subprocess.run([str(cc), "-S", "-x", "c", *fl.cflags.split(), *sys.argv[2:], "-ffunction-sections", f"-I{A.ROOT/'include'}", *[f"-I{d}" for d in A.EXTRA_INCLUDES], "-o", out+"/x.s", src], capture_output=True, text=True, cwd=out)
print(r.stderr)
