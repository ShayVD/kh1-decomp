/* wm.x func_00f380b0: matched by hand. */
#include "ovl.h"

#include "platform/math.h"
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    u8 pad24[0x3C];
    f32 m60[4][4];
} S380;
extern s32 D_00F87058;
S380 *func_00f363c0(s32);
s32 func_00f68770(s32, s32, f32 (*)[4], f32 *, s32);
void func_00f2c818(f32 (*)[4]);
void func_001bf290(f32 *);
void func_001bf698(f32 *, f32 *, f32);
void func_001bf3e8(f32 (*)[4], f32 *);
void func_001bfac8(void);
void func_00f689f0(s32, f32 (*)[4]);
void func_00f68ab0(s32);
void func_00f68a40(s32);
void func_00f36308(s32);
f32 acosf(f32);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void sceVu0Normalize(f32 *, f32 *);
void sceVu0OuterProduct(f32 *, f32 *, f32 *);
f32 sceVu0InnerProduct(f32 *, f32 *);

void func_00f380b0(s32 arg0) {
    f32 cm[4][4];
    f32 m[4][4];
    f32 p[4];
    f32 d[4];
    f32 ax[4];
    f32 u[4];
    f32 q[4];
    f32 tgt[4];
    S380 *s;
    s32 h;
    s32 i;
    s32 n;
    s32 k;
    f32 sc;
    f32 c;
    f32 a;

    s = func_00f363c0(arg0);
    h = func_00f68770(s->x8, 1, s->m60, 0, D_00F87058);
    if (h < 0) return;
    sc = 250.0f;
    if (s->x10 != 0) sc = s->x10 * 100.0f;
    if (s->x14 == 0) s->x14 = 80;
    n = 10;
    if (s->x18 != 0) n = s->x18;
    for (i = 0; i < s->x14 + 10; i++) {
        if (s->x0 == 0) break;
        if (s->xC & 1) break;
        if (i % n == 0) {
            func_00f2c818(cm);
            tgt[0] = cm[3][0];
            tgt[1] = cm[3][1];
            tgt[2] = cm[3][2];
            tgt[3] = 1.0f;
        }
        sceVu0CopyMatrix(m, s->m60);
        d[3] = 1.0f;
        d[0] = tgt[0] - m[3][0];
        d[1] = tgt[1] - m[3][1];
        d[2] = tgt[2] - m[3][2];
        sceVu0Normalize(d, d);
        u[0] = m[2][0];
        u[1] = m[2][1];
        u[2] = m[2][2];
        u[3] = 1.0f;
        sceVu0Normalize(u, u);
        sceVu0OuterProduct(ax, u, d);
        sceVu0Normalize(ax, ax);
        c = sceVu0InnerProduct(u, d) /
            PlatSqrtf((d[0] * d[0] + d[1] * d[1] + d[2] * d[2]) * (u[0] * u[0] + u[1] * u[1] + u[2] * u[2]));
        if (!(0.999f < c && c < 1.001f) && !(c < -0.999f && -1.001f < c)) {
            if (-0.001f < c && c < 0.001f) {
                a = 1.5707962513f;
            } else {
                a = acosf(c);
            }
            while (3.1415927f < a) a -= 6.28318505f;
            while (a < -3.1415927f) a += 6.28318505f;
            if (a < 0.0f) {
                if (a < -0.08726646f) a = -0.08726646f;
            } else {
                if (0.08726646f < a) a = 0.08726646f;
            }
            func_001bf290(q);
            func_001bf698(q, ax, a);
            func_001bf3e8(cm, q);
            p[0] = m[3][0];
            p[1] = m[3][1];
            p[2] = m[3][2];
            m[3][0] = 0.0f;
            m[3][1] = 0.0f;
            m[3][2] = 0.0f;
            sceVu0MulMatrix(m, cm, m);
            m[3][0] = p[0];
            m[3][1] = p[1];
            m[3][2] = p[2];
        }
        m[3][0] += m[2][0] * sc;
        m[3][1] += m[2][1] * sc;
        m[3][2] += m[2][2] * sc;
        sceVu0CopyMatrix(s->m60, m);
        func_00f689f0(h, s->m60);
        if (i == s->x14) func_00f68ab0(h);
        if (i < s->x14) func_00f36308(arg0);
        func_001bfac8();
    }
    if (s->x0 != 0) {
        k = -1;
        if (s->xC & 1) {
            switch (s->x20) {
            case 0:
                k = 6;
                break;
            case 1:
                k = 7;
                break;
            }
        }
        if (k >= 0) func_00f68770(k, 1, s->m60, 0, D_00F87058);
    }
    s->x0 = 0;
    func_00f68a40(h);
}
