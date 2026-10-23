/* Small helpers between the sound driver and the play timer
 * (docs/modules.md "Session 36"), 0x001edc80-0x001ee118: the distance of two
 * points, an angle wrapped to [-pi, pi), RGBA colour helpers (alpha scaled
 * by s / 128, a lerp, the average of two colours) and a GS scissor-rect
 * packet sent on PATH 2 (func_001edfb8).  util.nofill.c holds the vector
 * length func_001edc50. */
#include "common.h"
#include "platform/math.h"

typedef struct { f32 x, y, z; } V3;
typedef struct { u8 r, g, b, a; } __attribute__((aligned(4))) Col;
typedef struct { u64 a, b; } Q;

s32 func_00266c08(s32);
void func_00266f38(s32, void *);
Q *func_00122048(s32, s32);
s32 sceGsSyncPath(s32, u16);
void func_001220b8(void *);
Q *func_0011fb38(s32 reg, u64 val, Q *p);

f32 func_001edc80(V3 *a, V3 *b) {
    V3 d;
    d.x = a->x - b->x;
    d.y = a->y - b->y;
    d.z = a->z - b->z;
    return PlatSqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
}

f32 func_001edcd8(f32 fparg0) {
    f32 var_f12;

    var_f12 = fparg0;
    if (var_f12 >= 3.141592979f) {
        var_f12 -= 2.0f * ((f32) ((s32) (var_f12 / 6.2831855f) + 1) * 3.141592979f);
    } else if (var_f12 < -3.141592979f) {
        var_f12 += 2.0f * ((f32) ((s32) (var_f12 / -6.2831855f) + 1) * 3.141592979f);
    }
    return var_f12;
}

u32 func_001edd88(u32 c, s32 s) {
    u8 *p = (u8 *)&c;
    u32 a;
    if (s != 128) {
        a = ((c >> 24) * s) >> 7;
        if (a > 255) a = 255;
        p[3] = a;
    }
    return c;
}

/* Matched in session 19 (s19m1): a.r is pinned in a register variable (the lbu's own
 * result) and used for both g and c.r, so global-alloc gives g the register the
 * original does.  FLAGGED: one register variable.  As u32 it grows to 416 bytes. */
Col func_001eddc0(Col a0, Col b0, f32 t) {
    Col c, a, b;
    u8 *pa, *pb, *pc;
    u32 f, g;
    register s32 ar asm("$4");
    b = b0; a = a0;
    ar = a.r;
    g = (b.r - ar) * t;
    c.r = ar + g;
    pc = &c.r; pa = &a.r; pb = &b.r;
    f = (b.g - a.g) * t;
    pc[1] = pa[1] + f;
    c.b = pa[2] + (u32)((pb[2] - pa[2]) * t);
    c.a = pa[3] + (u32)((pb[3] - pa[3]) * t);
    return c;
}

u32 func_001edf40(u32 x, u32 y) {
    u32 res;
    u8 *r = (u8 *)&res;
    u8 *p = (u8 *)&x;
    u8 *q = (u8 *)&y;
    res = (res & ~0xff) | ((u32)(p[0] + q[0]) >> 1);
    r[1] = (p[1] + q[1]) >> 1;
    r[2] = (p[2] + q[2]) >> 1;
    r[3] = (p[3] + q[3]) >> 1;
    return res;
}

/* A port of its sibling func_001f86e0 (src/hand/text_001f0000_s6_17.c). */
void func_001edfb8(s32 x0, s32 y0, s32 w, s32 h) {
    s32 x1, y1;
    Q *buf, *e, *p;
    void *ub;
    x1 = x0 + w - 1;
    y1 = y0 + h - 1;
    if (x0 < 512 && y0 < 384 && x1 >= 0 && y1 >= 0) {
        if (x1 >= 512) x1 = 511;
        if (x0 < 0) x0 = 0;
        if (y0 < 0) y0 = 0;
        if (y1 >= 384) y1 = 383;

        p = func_00122048(1024, 128);
        buf = p;
        p = buf + 1;
        ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
        p->a = 0x1000000000008001;
        p->b = 14;

        e = func_0011fb38(64, (u64)x0 | ((u64)x1 << 16) | ((u64)y0 << 32) | ((u64)y1 << 48), p + 1);
        buf->a = ((e - buf) - 1) | 0x70000000;
        func_00266f38(func_00266c08(2), ub);
        sceGsSyncPath(0, 0);
        func_001220b8(buf);
    }
}
