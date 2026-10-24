/* The pointer of the menus (docs/modules.md "Session 39"),
 * 0x0020b6a8-0x0020be68: a sprite at D_00641210 / D_00641214 (pixels) that
 * glides to a new place in D_006411E4 frames (func_0020bc48; D_006411E0 on
 * while it moves, from D_006411EC / D_006411F0 to D_006411F4 / D_006411F8)
 * and fades in or out (D_006411FC: 0 fading in, 1 shown, 2 fading out, 3
 * hidden; D_00641204 of D_00641200 frames from D_00641208 to D_0064120C, the
 * alpha D_00641218).  func_0020b998 is the frame update and draws it
 * (func_0020b6a8: the alpha pulses with D_002BBDF8);  func_0020bbc0 /
 * func_0020bd18 point at the cursor cell of a TextWin. */
#include "common.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "text/textwin.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_003F1E70.h"
#include "data/pieces/D_002BBDFC.h"

s32 D_006411E0 ALIGNED(16);
f32 D_006411E4 ALIGNED(4);
f32 D_006411E8 ALIGNED(8);
f32 D_006411EC ALIGNED(4);
f32 D_006411F0 ALIGNED(16);
f32 D_006411F4 ALIGNED(4);
f32 D_006411F8 ALIGNED(8);
s32 D_006411FC ALIGNED(4);
f32 D_00641200 ALIGNED(16);
f32 D_00641204 ALIGNED(4);
f32 D_00641208 ALIGNED(8);
f32 D_0064120C ALIGNED(4);
f32 D_00641210 ALIGNED(16);
f32 D_00641214 ALIGNED(4);
f32 D_00641218 ALIGNED(8);
void *func_00122048(s32, s32);
void func_001220b8(void *);
f32 sinf(f32);
s32 func_0020bb78(void);
void func_0020bb90(s32, s32);
void func_0020bc48(s32, s32, s32);

/* func_0020b6a8: one packet word written through a u64/s32[2] union (W64), which gives that sw a dependence on the later sd buf[0] in sched2; tail order found by hill_s8. */
typedef union { u64 ul; s32 i[2]; } W64;
void func_0020b6a8(void) {
    u64 *buf;
    u64 *p;
    void *ua;
    f32 f;
    u32 a;
    s32 x, y, m;
    s32 k = 22;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(0x400, 0x80);
    p = buf + 2;
    ua = (void *)(((u32)buf & 0x0FFFFFFF) | 0x80000000);
    m = D_002BBDF8;
    p[0] = 0x50AB400000000001;
    p[1] = 0xEEEEE;
    p[3] = 0x3F;
    p[4] = 0x7BF8621413D7C;
    p[5] = 6;
    p[6] = 0x4007BF8001300000;
    p[8] = 0x0407BF8001400000;
    p[10] = 0x48;
    p[11] = 0x42;
    p[12] = 0x5000000000008001;
    p[13] = 0x4343E;
    p[7] = k;
    p[9] = k;
    p[2] = 0;
    f = (sinf((f32)(m % 90) / 90.0f * 6.2831855f) * 32.0f + 96.0f) * D_00641218;
    a = f;
    x = (s32)D_00641210 * 16;
    y = (s32)D_00641214 * 16;

    ((s32 *)p)[38] = 0x100000;
    ((s32 *)p)[32] = 0xE18;
    p[14] = (u32)(((a >> 7) << 24) | 0x808080);
    ((s32 *)p)[33] = 0x158;
    ((s32 *)p)[36] = x + 0x6F10;
    ((s32 *)p)[39] = 0x8000;
    ((s32 *)p)[40] = 0xFE8;
    ((s32 *)p)[41] = 0x328;
    ((W64 *)p)[18].i[1] = y + 0x7310;
    ((s32 *)p)[44] = x + 0x70F0;
    p[15] = 1;
    ((s32 *)p)[47] = 0;
    ((s32 *)p)[45] = y + 0x74F0;
    ((s32 *)p)[46] = 0x100000;
    buf[0] = (((s32)((u8 *)p - (u8 *)buf + 0xC0) >> 4) - 1) | 0x70000000;

    PlatDmaSend(PlatDmaGetChan(2), ua);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_0020b968(void) {
    D_006411FC = 3;
    D_006411E0 = 0;
    D_00641210 = 0;
    D_00641214 = 0;
    D_00641218 = 0;
}

void func_0020b998(void) {
    if (D_006411E0) {
        D_006411E8 += D_002BBDFC;
        if (D_006411E4 <= D_006411E8) {
            D_00641210 = D_006411F4;
            D_00641214 = D_006411F8;
            D_006411E0 = 0;
        } else {
            D_00641210 = D_006411EC + (D_006411F4 - D_006411EC) * D_006411E8 / D_006411E4;
            D_00641214 = D_006411F0 + (D_006411F8 - D_006411F0) * D_006411E8 / D_006411E4;
        }
    }
    switch (D_006411FC) {
    case 1:
        break;
    case 0:
        D_00641204 += D_002BBDFC;
        if (D_00641200 <= D_00641204) {
            D_006411FC = 1;
            D_00641218 = 128.0f;
        } else {
            D_00641218 = D_00641208 + (D_0064120C - D_00641208) * D_00641204 / D_00641200;
        }
        break;
    case 2:
        D_00641204 += D_002BBDFC;
        if (D_00641200 <= D_00641204) {
            D_006411FC = 3;
            D_00641204 = D_00641200;
            D_00641218 = 0.0f;
        } else {
            D_00641218 = D_00641208 + (D_0064120C - D_00641208) * D_00641204 / D_00641200;
        }
        break;
    }
    if (func_0020bb78()) func_0020b6a8();
}

s32 func_0020bb78(void) {
    return D_006411FC != 3;
}

void func_0020bb90(s32 x, s32 y) {
    D_006411E0 = 0;
    D_00641210 = (f32)x;
    D_00641214 = (f32)y;
}

void func_0020bbc0(TextWin *a0) {
    func_0020bb90((a0->xb0 + a0->xc2 * (a0->xda + 16) / 16 + a0->xbe - a0->xc6 - 0x7000) >> 4,
                  (a0->xb4 + a0->xc4 * a0->ud0.s.xd2 / 16 + a0->xc0 - 0x7400) >> 4);
}

void func_0020bc48(s32 a0, s32 a1, s32 a2) {
    if ((a1 - (s32)D_00641210 + 1) >> 1 == 0 && (a2 - (s32)D_00641214 + 1) >> 1 == 0) {
        D_00641210 = a1;
        D_00641214 = a2;
        D_006411E0 = 0;
        return;
    }
    D_006411E0 = 1;
    D_006411E4 = a0;
    D_006411E8 = 0;
    D_006411EC = D_00641210;
    D_006411F0 = D_00641214;
    D_006411F4 = a1;
    D_006411F8 = a2;
}

void func_0020bd18(TextWin *a0, s32 a1) {
    func_0020bc48(a1, (a0->xb0 + a0->xc2 * (a0->xda + 16) / 16 + a0->xbe - a0->xc6 - 0x7000) >> 4,
                  (a0->xb4 + a0->xc4 * a0->ud0.s.xd2 / 16 + a0->xc0 - 0x7400) >> 4);
}

void func_0020bda8(s32 n) {
    D_006411FC = 0;
    D_00641200 = (f32)n;
    D_00641204 = 0;
    D_00641208 = D_00641218;
    D_0064120C = 128.0f;
}

void func_0020bdf0(void) {
    D_006411FC = 1;
    D_00641218 = 128.0f;
}

void func_0020be10(s32 n) {
    D_006411FC = 2;
    D_00641200 = n;
    D_00641204 = 0;
    D_00641208 = D_00641218;
    D_0064120C = 0;
}

void func_0020be50(void) {
    D_006411FC = 3;
    D_00641218 = 0;
}
