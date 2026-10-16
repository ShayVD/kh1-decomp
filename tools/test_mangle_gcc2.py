"""Expected names were produced by ee-gcc 2.96-ee-001003-1 (see docs/toolchain.md)."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from mangle_gcc2 import mangle  # noqa: E402

CASES = {
    "YS::PROGRESS::CheckFlag(int)": "CheckFlag__Q22YS8PROGRESSi",
    "YS::PROGRESS::Get() const": "Get__CQ22YS8PROGRESS",
    "YS::PROGRESS::Set(int, unsigned char*, const Vec&)": "Set__Q22YS8PROGRESSiPUcRC3Vec",
    "SOUND::init()": "init__5SOUND",
    "freefn(int a, float b, Vec* v, Vec* w)": "freefn__FifP3VecT2",
    "nothing(void)": "nothing__Fv",
    "two(unsigned int, unsigned int)": "two__FUiUi",
    "V::V()": "__1V",
    "V::~V()": "_$_1V",
    "V::add(const V&, V*)": "add__1VRC1VP1V",
    "V::q(V*, V*, V*)": "q__1VP1VN21",
    "f(A*, A*, A*, A*)": "f__FP1AN30",
    "g(A*, int, A*)": "g__FP1AiT0",
    "h(char*, char*)": "h__FPcT0",
}

fails = 0
for sig, want in CASES.items():
    got = mangle(sig)
    if got != want:
        fails += 1
        print(f"FAIL {sig}: got {got}, want {want}")
print(f"mangle_gcc2: {len(CASES) - fails}/{len(CASES)} ok")
sys.exit(1 if fails else 0)
