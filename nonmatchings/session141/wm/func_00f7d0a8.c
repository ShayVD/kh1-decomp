/* Round 47 wwm2: score 331 -> 265, hill3o statement order. Earlier header below. */
/* score 335 (2372 vs 2360 bytes, 507 words). Camera fly-to between map points: accelerate (t += 0.02) until half the start distance is covered, cruise, then decelerate (t -= 0.02, floor 0.01) while the distance shrinks, then snap. Bare sqrt.s needs PlatSqrtf from platform/math.h; sqrtf and __builtin_sqrtf compile to a call. Scalar vx/vy/vz locals (451 -> 335) stop gcc hoisting &v[2] into s8. Loop exits are written as !(half <= d) and !(d <= half). Left: the frame is 16 bytes smaller (the original also spills the 128.0f/D_00FB5BB4 constant to sp+16), the original keeps %hi(0x0109) in s8, and the FA88/FA8C/FA90 base registers are numbered differently. Tried split range tests for D_0108F6E8 (21..26), struct and array forms of the position. Round 18 (wwm1): 499 words with a CONTEXT_ONLY definition of func_0024e468 (ctx2.py). */
#include "platform/math.h"
typedef struct { u8 pad[20]; u8 f14[128]; s32 x94; } St;
typedef struct { u8 pad[7]; u8 x7; u32 x8; } Pad;
extern f32 D_00FB5BB4;
extern f32 D_00FB5BC8;
extern f32 D_00FB5BF0;
extern s32 D_00FB5EC0;
extern s32 D_00FB5ED0;
extern s32 D_00FB6108;
extern s32 D_00FB610C;
extern s32 D_00FB6164;
extern f32 D_00FB6478[3];
extern f32 D_00FB6488[3];
extern St D_00FB6498;
extern s32 D_0108F6D4;
extern f32 D_0108F6D8;
extern f32 D_0108F6DC;
extern s32 D_0108F6E0;
extern s32 D_0108F6E4;
extern s32 D_0108F6E8;
extern s32 D_0108F730[2];
extern s32 D_0108F910;
extern s32 D_0108F914;
extern Pad D_0108F980;
extern s32 D_0108FA70;
extern s32 D_0108FA74;
extern f32 D_0108FA88;
extern f32 D_0108FA8C;
extern f32 D_0108FA90;
void func_0011d768(s32);
CONTEXT_ONLY void func_0024e468(s32 a0) {}
s32 func_00f79868(f32 *, f32 *, f32 *, s32, s32);
s32 func_00f7c220(s32, s32);
void func_00f7cb60(void);
void func_00f7cc98(void);
void func_00f7cd68(void);
f32 func_00f7d060(f32);

void func_00f7d0a8(void)
{
    f32 x, y, z, dx, dy, dz, half, t, mx, my, mz, d, od;
    f32 *p;
    s32 sel, prev, i, a, b;
    f32 vx, vy, vz;
    f32 sx, sy, sz;
    sel = D_00FB6498.x94;
    D_00FB6108 = sel;
    D_0108F6E0 = 128;
    D_0108F6D8 = 0.0f;
    if (func_00f79868(&vx, &vy, &vz, 26, 1)) D_0108F6D8 = vy;

    D_0108F6DC = 0.0f;
    if (func_00f79868(&vx, &vy, &vz, 24, 1)) D_0108F6DC = vy;
    while (!func_00f79868(&vx, &vy, &vz, sel, 0)) {
        sel++;
        D_00FB6108 = sel;
        if (sel >= 28) {
            sel = 0;
            D_00FB6108 = 0;
            break;
        }
    }
    D_00FB610C = sel;
    D_00FB6498.x94 = sel;
    if (sel < 27) {
        if (sel >= 21) D_0108F6E8 = 1;
        else goto z;
    } else {
    z:
        D_0108F6E8 = 0;
    }
    D_0108F6E4 = 0;
    if (sel >= 2 && sel < 28) {
        if ((D_00FB6498.f14[sel] & 1) && (D_00FB6498.f14[sel] & 8)) D_0108F6E4 = 1;
    }
    D_0108FA8C = vy;
    D_0108FA90 = vz;
    D_0108FA88 = vx;
    D_00FB5BF0 = func_00f7d060(vx);
    D_00FB5EC0 = 0;
    func_00f7cb60();
    func_0024e468(2);
    D_0108FA70 = 66;
    if (D_0108F730[0] == 0 && D_0108F730[1] == 0) D_0108FA70 = 67;
    D_0108FA74 = D_0108FA70;
    while (D_00FB6164 == 0) func_0024e468(1);
    for (;;) {
        func_00f7cc98();
        D_00FB5ED0 = 1;
        if (sel >= 2 && sel < 28) {
            if ((D_00FB6498.f14[sel] & 2) || D_0108F6E8 == 1) D_00FB5ED0 = 0;
            if (D_0108F980.x8 & 0x1000) {
                if (D_00FB5ED0 == 0 || D_0108F6E8 == 1) func_0011d768(4);
                else func_00f7cd68();
            }
        }
        a = D_0108F6E0 + 128.0f / D_00FB5BB4;
        D_0108F6E0 = a;
        if (a > 128) D_0108F6E0 = 128;
        b = D_0108F980.x7 & 0xF0;
        D_0108FA70 = 66;
        if (b && D_0108F6D4) {
            prev = sel;
            sel = func_00f7c220(b, prev);
            if (prev != sel) {
                D_00FB610C = -1;
            retry:
                if (func_00f79868(&vx, &vy, &vz, sel, 0)) {
                    D_0108F6E4 = 0;
                    if (D_0108F914 == 0) {
                        if (prev == 25 && sel == 26) {
                            D_0108F730[0] = 0;
                            D_0108F730[1] = 0;
                            vx = D_00FB6488[0];
                            vy = D_00FB6488[1];
                            D_0108F914 = 1;
                            D_0108F910 = 0;
                            vz = D_00FB6488[2];
                        }
                        if (prev == 26 && sel == 25) {
                            vx = D_00FB6478[0];
                            vy = D_00FB6478[1];
                            vz = D_00FB6478[2];
                            D_0108F910 = 0;
                            D_0108F914 = 2;
                            D_0108F730[0] = 0;
                            D_0108F730[1] = 0;
                        }
                    } else {
                        D_0108F914 = 3;
                    }
                    x = D_0108FA88;
                    y = D_0108FA8C;
                    sy = y;
                    dx = vx - x;
                    z = D_0108FA90;
                    sz = z;
                    dy = vy - y;
                    dz = vz - z;
                    sx = x;
                    half = PlatSqrtf(dx * dx + dy * dy + dz * dz) * 0.25f;
                    if (sel == 21) half /= D_00FB5BC8;
                    if (sel == 22) half /= D_00FB5BC8;
                    if (sel == 23) half /= D_00FB5BC8;
                    if (sel == 24) half /= D_00FB5BC8;
                    t = 0.0f;
                    D_0108FA70 = 67;
                    do {
                        y += dy * t;
                        x += dx * t;
                        D_0108FA88 = x;
                        z += dz * t;
                        D_0108FA8C = y;
                        D_0108FA90 = z;
                        a = D_0108F6E0 - 128.0f / D_00FB5BB4;
                        t += 0.02f;
                        D_0108F6E0 = a < 0 ? 0 : a;
                        D_00FB5BF0 = func_00f7d060(x);
                        func_0024e468(1);
                        d = PlatSqrtf((sx - x) * (sx - x) + (sy - y) * (sy - y) + (sz - z) * (sz - z));
                    } while (!(half <= d));
                    mx = dx * t;
                    my = dy * t;
                    mz = dz * t;
                    do {
                        x += mx;
                        a = D_0108F6E0 - 128.0f / D_00FB5BB4;
                        D_0108FA88 = x;
                        z += mz;
                        y += my;
                        D_0108FA90 = z;
                        D_0108FA8C = y;
                        D_0108F6E0 = a < 0 ? 0 : a;
                        D_00FB5BF0 = func_00f7d060(x);
                        func_0024e468(1);
                        d = PlatSqrtf((vx - x) * (vx - x) + (vy - y) * (vy - y) + (vz - z) * (vz - z));
                    } while (!(d <= half));
                    for (;;) {
                        x += mx;
                        y += my;
                        od = d;
                        t -= 0.02f;
                        z += mz;
                        a = D_0108F6E0 - 128.0f / D_00FB5BB4;
                        D_0108F6E0 = a < 0 ? 0 : a;
                        if (t < 0.02f) t = 0.01f;
                        d = PlatSqrtf((vx - x) * (vx - x) + (vy - y) * (vy - y) + (vz - z) * (vz - z));
                        D_0108FA90 = z;
                        D_0108FA8C = y;
                        mx = dx * t;
                        D_0108FA88 = x;
                        my = dy * t;
                        mz = dz * t;
                        D_00FB5BF0 = func_00f7d060(x);
                        func_0024e468(1);
                        if (od < d) break;
                    }
                    D_0108FA88 = vx;
                    D_0108FA90 = vz;
                    D_0108FA8C = vy;
                    D_00FB5BF0 = func_00f7d060(vx);
                    if ((u32)(D_0108F914 - 1) < 2) {
                        while (D_0108F910 != 128) func_0024e468(1);
                        if (D_0108F914 == 1) p = D_00FB6478;
                        else p = D_00FB6488;
                        D_0108FA8C = p[1];
                        D_0108FA88 = p[0];
                        D_0108FA90 = p[2];
                        D_00FB5BF0 = func_00f7d060(D_0108FA88);
                        goto retry;
                    }
                    if (D_0108F914 == 3) D_0108F914 = 0;
                    D_00FB6108 = sel;
                    func_00f7cb60();
                    D_00FB610C = sel;
                    func_0011d768(1);
                    if (sel < 27) {
                        if (sel < 21) D_0108F6E8 = 0;
                        else D_0108F6E8 = 1;
                    } else D_0108F6E8 = 0;
                }
            }
        }
        if (sel == 0) {
            for (i = 2; i < 27; i++) {
                if (D_00FB6498.f14[i] & 4) {
                    while (!func_00f79868(&vx, &vy, &vz, sel, 0)) {
                        sel++;
                        D_00FB6108 = sel;
                        if (sel >= 28) {
                            D_00FB6108 = 0;
                            sel = 0;
                            break;
                        }
                    }
                    D_00FB610C = sel;
                    break;
                }
            }
        }
        func_0024e468(1);
    }
}
