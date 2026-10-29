/* score 11 (6 words; was 13). Round 30 wwm2: hill2 over all ten setup stores (D_0108F1AC = 0 first) took it from 11 to 6 words. Left: the 8 and the %hi(0x109) pick t6/t4 the other way round, and one store is scheduled differently; CONTEXT_ONLY callees (ctx2, pairs) do not help. Earlier header: score 13 (11 words; only the trailing pad differs in size). Fade-thread start: global setup, func_001f31a8, then a wait loop. Putting `D_0108F1A0 = 8` first fixes most of the store order (brute-forced over the first six and middle five statements). Left: the original loads -8 late into v0 and keeps 224 in a2; ours loads -8 early into v1. Chained assignments, a 224 local and a third call argument did not help. */
#include "ovl.h"

extern u8 D_00FB5B30[];
extern s32 D_0108F578;
extern s32 D_0108F1B0;
extern s32 D_0108F1A0;
extern s32 D_0108F568;
extern s32 D_0108F56C;
extern s32 D_0108F258;
extern s32 D_0108F1A8;
extern s32 D_0108F574;
extern s32 D_0108F570;
extern s32 D_0108F1AC;
s32 func_001f31a8(void *, s32);
void func_0024e468(s32);

s32 func_00f78458(s32 arg) {
    D_0108F1AC = 0;
    D_0108F568 = arg;
    D_0108F1A0 = 8;
    D_0108F1B0 = 224;
    D_0108F258 = 1;
    D_0108F56C = arg;
    D_0108F1A8 = 1;
    D_0108F574 = 0;
    D_0108F570 = 0;
    D_0108F578 = -8;
    func_001f31a8(D_00FB5B30, 1);
    while (D_0108F1AC != 1) {
        func_0024e468(1);
    }
    D_0108F1A0 = 16;
    return D_0108F56C;
}
