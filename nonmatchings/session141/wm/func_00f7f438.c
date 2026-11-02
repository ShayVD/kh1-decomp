/* Round 36 (wgb): wm.x func_00f7f438 near miss: 80 -> 76 words, score 71 -> 57 (aligned diff 40 -> 31). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* score 71: original stores the three GIF qwords in strict order with li values interleaved (one address reg a1 reused); ours schedules the li early. Inline put() helpers give the per-qword address registers (see func_00f7ef20) but not the order. */
#include "ovl.h"

typedef union {
    kh1_u128 q;
    u64 d[2];
    u32 w[4];
} Qw;

Qw *func_00f21e90(void);
void func_00f21ea0(Qw *);
Qw *func_00f7ef20(Qw *, s32, s32, s32, s32, u8 *, s32, s32);
Qw *func_00f7f338(Qw *, s32, s32, s32, s32);
Qw *func_00f7f128(Qw *, s32, s32, s32);
Qw *func_00f7f218(Qw *, s32, s32, s32);
Qw *func_001f0ea8(Qw *, s32, s32, u32, s32, s32, s32, s32);
Qw *func_00f7f0e8(Qw *);
void func_00f66fe8(s32, Qw *);

void func_00f7f438(s32 id, s32 *str, s32 bits, s32 n, s32 v) {
    u8 col[4];
    Qw *base;
    Qw *q;
    Qw *p;

    if (*str == 0) {
        return;
    }
    col[0] = 64;
    col[1] = 64;
    col[2] = 64;
    col[3] = 64;
    base = func_00f21e90();
    q = func_00f7ef20(base, 12, 160, 484, 72, col, 68, 0x5001D);
    q[0].q = KH1_Q(0);
    q[1].d[1] = 14;
    q[1].d[0] = 0x1000000000000002;
    q[3].d[0] = 68;
    q[3].d[1] = 66;
    q[2].d[0] = 27;
    q[2].d[1] = 71;
    p = func_00f7f338(q + 4, bits, 256, 190, n);
    p = func_00f7f128(p, bits, 256, 162);
    p = func_00f7f218(p, v, 16, 188);
    p = func_001f0ea8(p, 1, 0, 0x800000F0, 16, 160, *str, 24);
    q[0].w[0] = (((u32)p - (u32)q) >> 4) - 1 | 0x10000000;
    p = func_00f7f0e8(p);
    func_00f21ea0(p);
    func_00f66fe8(id, base);
}
