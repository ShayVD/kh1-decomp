/* Round 43 wwm2: score 86 -> 78. The msdscan hit was srl where we had sra: the qword count is unsigned, ((((u32)p - (u32)top) >> 4) - 1) | 0x10000000. The per-arm X = x; Y = y; copies come back with y4 = Y + 4 computed before the second flag test. Left: the Y copy is still coalesced into the load register (s0 instead of a3 -> s3), and x0 lands in a2 instead of the x temp t0. Earlier header below. */
/* score 86 (149 words; 696 vs 720 bytes). Draws a panel through func_00f799e0, then a GIF packet with func_001f07d8. Logic is complete. Left: in the original each arm of the flag `if` copies x and y into new registers (s2/s3) before the x-378/x-314 (x-6/x+170) arithmetic, and y+4 / y+48 are computed before the second flag test. Per-arm `X = x; Y = y;` copies give the x copy (score 94) but the y copy is still propagated away. Tried separate x0/x1/y0/y1 locals, all modes. */
#include "ovl.h"

typedef struct {
    u8 pad0[8];
    u8 *base;
    s32 a;
    s32 b;
    s32 c;
    s32 x[2];
    s32 y[2];
    s32 n[2];
    s32 flag[2];
} St;

typedef struct {
    u8 pad[12];
    s32 v;
} St2;

typedef union {
    kh1_u128 q;
    u64 d[2];
    u32 w[4];
} Qw;

extern St D_00FB6408;
extern St2 D_00FB6498;
extern u8 D_0108FAA0[][4];
extern Qw *D_0108FA60;
void func_00f799e0(u8 *, u8 *, s32, s32, s32, s32, s32, u8 *, s32, u64, s32, u64);
void func_001efb18(s32, s32);
Qw *func_001f07d8(Qw *, s32, s32, u32, s32, s32, s32, s32);

#define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))

void func_00f7c510(s32 idx) {
    s32 save;
    s32 x;
    s32 y;
    s32 X, Y, y4;
    s32 x0;
    s32 n;
    Qw *top;
    Qw *p;

    save = D_00FB6498.v;
    D_00FB6498.v = D_00FB6408.c;
    x = D_00FB6408.x[idx];
    y = D_00FB6408.y[idx];
    if (D_00FB6408.flag[idx] != 0) {
        X = x;
        Y = y;
        x0 = X - 378;
        X -= 314;
    } else {
        X = x;
        Y = y;
        x0 = X - 6;
        X += 170;
    }
    y4 = Y + 4;
    if (D_00FB6408.flag[idx] == 0) {
        func_00f799e0(D_00FB6408.base + 0x19000, D_00FB6408.base + 0x29000, x0, y4, 512, 120, 8, D_0108FAA0[idx], 0, 68, 0, 0x5001D);
    } else {
        func_00f799e0(D_00FB6408.base + 0xA000, D_00FB6408.base + 0x28C00, x0, y4, 512, 120, 8, D_0108FAA0[idx], 0, 68, 0, 0x5001D);
    }
    Y += 48;
    top = D_0108FA60;
    top->q = KH1_Q(0);
    n = D_00FB6408.n[idx];
    p = top + 1;
    if (n > 0) {
        p->d[0] = 0x1000000000000002;
    } else {
        p->d[0] = 0x1000000000008002;
    }
    p->d[1] = 14;
    p++;
    p->d[0] = 27;
    p->d[1] = 71;
    p++;
    p->d[0] = 68;
    p->d[1] = 66;
    p++;
    if (n > 0) {
        func_001efb18(D_00FB6408.a, D_00FB6408.b);
        p = func_001f07d8(p, 1, 0,
                          RGBA(D_0108FAA0[idx][0] * 230 >> 7, D_0108FAA0[idx][1] * 230 >> 7, D_0108FAA0[idx][2] * 230 >> 7,
                               D_0108FAA0[idx][3]),
                          X, Y, n, 15);
    }
    top->w[0] = ((((u32)p - (u32)top) >> 4) - 1) | 0x10000000;
    D_0108FA60 = p;
    D_00FB6498.v = save;
}
