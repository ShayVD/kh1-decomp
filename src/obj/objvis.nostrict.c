/* Whether an object is drawn: its bounding box corners (func_00135a68), the
 * on-screen test func_00135bb0, the distance fade curve func_00135ca0
 * (D_002BC0F0, D_002BC120, D_002BC124) and its colour fade (func_00135d38,
 * func_00135df0). Flag mode: nostrict (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002BBFA0.h"

/* func_00135a68 (from hand/nostrict/text_00130000_s11_w49.c). */
void func_00135a68(f32 (*v)[4], f32 r, f32 h) {
    s32 i, k, o, x;
    x = (s32)v;
    if (0.0f <= h) {
        h = -h;
        for (i = 0; i < 8; i++) {
            k = ((i & 1) << 1) - 1;
            v[i][0] = r * k;
            v[i][1] = h * ((i & 2) >> 1);
            v[i][2] = r * (((i & 4) >> 1) - 1);
            v[i][3] = 1.0f;
        }
    } else {
        for (i = 0; i < 8; i++) {
            o = i * 16;
            *(f32 *)((s32)v + o) = r * (((i & 1) << 1) - 1);
            if (x != (s32)v) { k = 2; k = 3; } else k = 1;
            v[i][1] = h * ((i & 2) - 1);
            if (x != (s32)v) { k = 2; k = 3; } else k = 1;
            v[i][2] = r * (((i & 4) >> 1) - 1);
            if (x != (s32)v) { k = 2; k = 3; } else k = 1;
            v[i][3] = 1.0f;
        }
    }
}

/* func_00135bb0 (from hand/nostrict/text_s7_w1.c). */
typedef union { u64 x; struct { u32 lo; u32 x32:13; u32 b45:1; u32 x46:3; u32 b49:1; u32 hi:14; } b; } F370e;
typedef struct { u8 p0[0x40]; f32 sx, sy, sz; u8 p4c[4]; f32 f50[4]; u8 p60[0xd0-0x60]; f32 fd0[4][4]; u8 p110[0x370-0x110]; F370e f370; } Ob9;
extern s32 func_0012f040(Ob9 *, s32);
extern f32 func_0012ec88(Ob9 *, f32 *);
extern s32 func_0024edf0(f32 (*)[4], void *);
CONTEXT_ONLY void func_00135b88(Ob9 *o, void *b) { func_00135a68(b, *(f32 *)((u8 *)o + 0x410), *(f32 *)((u8 *)o + 0x414)); }
/* ---- func_00135bb0 ---- */
s32 func_00135bb0(Ob9 *o) {
    f32 m[4][4];
    f32 v[4];
    u8 buf[128];
    if (o->f370.b.b45 && o->sx * o->sy * o->sz == 0.0f) return 0;
    if (o->f370.b.b49) goto r1;
    func_00135b88(o, buf);
    PlatVu0CopyMatrix(m, o->fd0);
    PlatVu0CopyVector(m[3], o->f50);
    m[3][3] = 1.0f;
    PlatVu0MulMatrix(m, D_002BBFA0, m);
    if (func_0012f040(o, -1)) {
        func_0012ec88(o, v);
        if (func_0024edf0(m, buf) == 0) goto r1;
        return 0;
    }
    if (func_0024edf0(m, buf) == 0) goto r1;
    return 0;
r1:
    return 1;
}

