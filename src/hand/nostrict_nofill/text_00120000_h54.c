#include "common.h"
typedef struct { f32 x, y, z, w; } V4;
extern void func_00267530(V4 *, V4 *, V4 *);
typedef struct { s32 f0, f4, f8, fc; s32 n; u8 ids[0x24]; } Q38;
extern Q38 D_002E2FD8[7];
extern u8 D_00524F68[];
typedef struct { s32 f0, f4; } S31b0;
typedef struct { u32 b0:8; u32 b1:16; u32 b24:1; u32 flag:1; u32 rest:6; S31b0 f4; } St8;
typedef struct { u16 f0; u8 p2[4]; u8 f6; s8 f7; s8 f8; s8 f9; s8 fa; s8 fb; } O8;
typedef struct { s32 f0, f4; u32 f8; s32 fc; s32 n; u8 ids[0x20]; s32 f34; } Q8;
extern St8 D_002E3190;
extern O8 *D_002E319C;
extern s32 D_002E31A4;
extern S31b0 D_002E31B0;
extern s32 D_002E31B8;
extern Q8 D_002E30B8;
extern Q8 *D_002E3170[];
extern Q8 **D_00524F40;
extern s32 D_00524F58[];
extern s32 D_002E3160[];
extern O8 *func_001478c8(s32);
extern void func_0011d768(s32);
extern void func_0012dce0(Q38 *);
extern s32 func_0012dd70(O8 *);
extern s32 func_0012dd38(void);
extern s32 func_00219288(void);
extern void func_0012fb20(S31b0 *, s32);
s32 func_0012dea0(Q8 *q, s32 i) {
    O8 *o;
    s32 f;
    S31b0 tmp;
    if (q->f8 & (1 << i)) {
        if (D_002E3190.flag) func_0011d768(4);
        return 0;
    }
    o = func_001478c8(q->ids[i]);
    if (o->f8 > 0) {
        q->f34 = i;
        func_0012dce0(&D_002E2FD8[o->f8]);
        return 0;
    }
    f = 0;
    if (q->f0 == 4) {
        if (q == &D_002E30B8) tmp.f0 = D_00524F58[i];
        else tmp.f0 = D_002E3160[i];
        tmp.f4 = 0;
        q = D_00524F40[-1];
        o = func_001478c8(q->ids[q->f34]);
    } else if (D_002E31B8) {
        tmp = D_002E31B0;
        f = 1;
    } else {
        tmp.f0 = 0;
        tmp.f4 = 0;
    }
    if (!func_0012dd70(o)) return 0;
    if (f && func_00219288() != 1 && (o->f0 & 4)) {
        if (D_002E31B8 - 1 < 2u || D_002E31B8 == 4) func_0012fb20(&D_002E31B0, 4);
    }
    if (q->f0 == 2) D_002E31A4 = D_00524F68[q->fc];
    D_002E3190.f4 = tmp;
    D_002E3190.b0 = o->f6;
    D_002E3190.b1 = o->f7;
    D_002E319C = o;
    while (D_00524F40 != D_002E3170) func_0012dd38();
    return 1;
}
typedef union { u64 x; struct { u32 lo0; u32 x32:3; u32 f35:1; u32 x36:1; u32 kind:2; u32 hi:25; } b; } F370b;
typedef struct { u8 pad[4]; u32 f4; } I9;
typedef struct { u8 pad[0x130]; I9 *f130; u8 p134[0x370-0x134]; F370b f370; } E9;
typedef struct { E9 *f0; s32 f4; } A9;
extern f32 D_002E2780[];
extern f32 func_0012ec60(E9 *, s32, f32 *);
extern f32 func_00120bf8(f32 *);
extern s32 func_0012eaf8(E9 *);
extern s32 func_0012f0f8(f32 *, f32 *, s32);
s32 func_0012f218(f32 *pos, A9 *a, s32 lim) {
    f32 tmp[4];
    f32 d[4];
    f32 r;
    s32 s, v;
    r = func_0012ec60(a->f0, a->f4, tmp);
    func_00267530((V4 *)d, (V4 *)tmp, (V4 *)pos);
    r = func_00120bf8(d) - r;
    if (func_0012eaf8(a->f0) && r > 1200.0f) return -1;
    s = r;
    if (!(r > 0.0f)) s = 0;
    if (D_002E319C) {
        switch (a->f0->f370.b.kind) {
        case 1:
            v = D_002E319C->f9;
            if (v < 0) return -1;
            s |= v << 24;
            break;
        case 2:
            v = D_002E319C->fa;
            if (v < 0) return -1;
            s |= v << 24;
            break;
        case 0:
        case 3:
            v = D_002E319C->fb;
            if (v < 0) return -1;
            s |= v << 24;
            break;
        }
    }
    if (lim >= 0 && !(s < lim)) return -1;
    if (a->f0->f370.b.f35 && func_0012f0f8(D_002E2780, tmp, 0)) return s;
    if (!func_0012f0f8(pos, tmp, 0)) return -1;
    if (func_0012eaf8(a->f0)) s |= 0x10000;
    return s;
}
