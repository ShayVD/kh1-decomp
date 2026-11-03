/* wm.x func_00f4a328: matched by hand. */
#include "ovl.h"

typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
typedef struct {
    GbPos p;
    u16 x2;
    u16 x4;
    u16 x6;
    u8 x8;
    u8 x9;
    u16 xA;
} Ent;
typedef struct {
    u8 pad0[4];
    u16 n;
    u8 pad6[112 - 6];
    Ent e[1];
} Grp;
typedef struct {
    u8 pad0[8];
    u8 x8;
    u8 x9;
} Info;
typedef struct {
    void *x0;
    u8 *x4;
    u8 x8[1];
} Ctx;
extern u8 *D_00F9B540;
extern s32 D_00F9B744;
extern f32 D_00F9B74C;
extern s32 D_00F9B750;
extern u8 D_01080A38[];
void sceVu0UnitMatrix(OvlMtx);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void func_00f5df38(s32, s32, void *);
void func_00f5df90(s32, s32, void *);
void func_00f5de50(void *, s32);
Info *func_001bb658(s32);
#ifdef KH1_PS2
GbPos func_001bbdf0(Ent *);
#else /* a port: the definition returns s32 (src/gummi/ship.c); an i386 struct return is a hidden pointer */
s32 func_001bbdf0(Ent *);
static __inline__ GbPos ee_001bbdf0(Ent *p) {
    union { s32 i; GbPos s; } u;
    u.i = func_001bbdf0(p);
    return u.s;
}
#define func_001bbdf0 ee_001bbdf0
#endif
void func_00f5dcf8(void *, s32);
void func_00f5dd78(void *, void *, void *, void *, Ent *);
s32 func_00f4cc38(s32, void *);
u8 *func_00f5e540(void *, u8 *, s32, s32, void *);
f32 func_00f50030(s32);
u8 *func_00f5e368(void *, u8 *, s32, s32, s32, f32);
void func_00f5e6e0(void *);
void *func_00f66ac8(void *);
void *func_00f4d730(void *, s32);
void *func_00f4e0b0(void *, s32, s32);
void *func_00f4d9c0(void *, s32, s32, s32, s32, s32, s32, s32);
void *func_00f4d5f8(void *);
s32 func_00f66ae0(void *);
void func_00f66f78(s32, s32);
void func_00f66fe8(s32, s32);

s32 func_00f4a328(s32 pri, Ctx *c, u8 *cam, s32 alpha, s32 lim, Grp *g) {
    OvlMtx m;
    u8 tmp[64];
    Ent *e;
    Info *info;
    GbPos pos;
    s32 i;
    s32 k;
    if (g == NULL) {
        g = (Grp *)(D_00F9B540 + 160);
    }
    if (D_00F9B744 != 0) {
        sceVu0UnitMatrix(m);
        m[2][2] = m[1][1] = m[0][0] = D_00F9B74C;
    }
    if (D_00F9B750 == 0) {
        func_00f5df38(pri, pri + 1, c->x8);
    } else {
        func_00f5df90(2, 1, c->x8);
    }
    func_00f5de50(c->x8, 0);
    for (i = 0, e = g->e; i < g->n; i++, e++) {
        if (e->x4 == 0) {
            continue;
        }
        info = func_001bb658(e->x4 - 1);
        pos = func_001bbdf0(e);
        func_00f5dcf8(c->x4 + 16, e->x4 - 1);
        if (D_00F9B744 != 0 && D_01080A38[e->x4 - 1] == 0) {
            sceVu0MulMatrix((f32 (*)[4])(c->x4 + 16), (f32 (*)[4])(c->x4 + 16), m);
        }
        *(f32 *)(c->x4 + 76) = *(f32 *)(cam + 60);
        func_00f5dd78(c->x4 + 144, c->x4 + 80, cam + 192, cam + 64, e);
        if (e->x6 & 0x20) {
            if (alpha != 128) {
                if (lim < e->p.y) {
                    continue;
                }
                if (lim >= e->p.y + pos.y) {
                    continue;
                }
            }
            if (func_00f4cc38(e->x4 - 1, tmp)) {
                c->x4 = func_00f5e540(c->x8, c->x4, info->x8 + 1, e->x8, tmp);
            } else {
                k = info->x9;
                if (k == 0xFF) {
                    k = 0;
                } else {
                    k++;
                }
                c->x4 = func_00f5e368(c->x8, c->x4, info->x8 + 1, k, e->x8, func_00f50030(i));
            }
        }
    }
    func_00f5e6e0(c->x8);
    if (alpha != 128) {
        if (D_00F9B750 == 0) {
            func_00f5df38(pri + 3, pri + 4, c->x8);
        } else {
            func_00f5df90(5, 6, c->x8);
        }
        func_00f5de50(c->x8, 0);
        for (i = 0, e = g->e; i < g->n; i++, e++) {
            if (e->x4 == 0) {
                continue;
            }
            info = func_001bb658(e->x4 - 1);
            pos = func_001bbdf0(e);
            func_00f5dcf8(c->x4 + 16, e->x4 - 1);
            *(f32 *)(c->x4 + 76) = *(f32 *)(cam + 60);
            func_00f5dd78(c->x4 + 144, c->x4 + 80, cam + 192, cam + 64, e);
            if (e->x6 & 0x20) {
                if (lim >= e->p.y && lim < e->p.y + pos.y) {
                    continue;
                }
                k = info->x9;
                if (k == 0xFF) {
                    k = 0;
                } else {
                    k++;
                }
                c->x4 = func_00f5e368(c->x8, c->x4, info->x8 + 1, k, e->x8, func_00f50030(i));
            }
        }
        func_00f5e6e0(c->x8);
        c->x0 = func_00f66ac8(c->x0);
        c->x0 = func_00f4d730(c->x0, 3);
        c->x0 = func_00f4e0b0(c->x0, 1776, 1824);
        if (D_00F9B750 == 0) {
            func_00f66f78(pri + 2, func_00f66ae0(c->x0));
        } else {
            func_00f66fe8(4, func_00f66ae0(c->x0));
        }
        c->x0 = func_00f66ac8(c->x0);
        c->x0 = func_00f4e0b0(c->x0, 1792, 1856);
        c->x0 = func_00f4d9c0(c->x0, alpha, 5, 1, 64, 2, 448, 382);
        c->x0 = func_00f4d5f8(c->x0);
        c->x0 = func_00f4e0b0(c->x0, 1776, 1824);
        if (D_00F9B750 == 0) {
            func_00f66f78(pri + 5, func_00f66ae0(c->x0));
        } else {
            func_00f66fe8(7, func_00f66ae0(c->x0));
        }
    } else {
        c->x0 = func_00f66ac8(c->x0);
        c->x0 = func_00f4e0b0(c->x0, 1776, 1824);
        if (D_00F9B750 == 0) {
            func_00f66f78(pri + 2, func_00f66ae0(c->x0));
        } else {
            func_00f66fe8(4, func_00f66ae0(c->x0));
        }
    }
    c->x0 = func_00f66ac8(c->x0);
    c->x0 = func_00f4e0b0(c->x0, 1792, 1856);
    if (D_00F9B750 == 0) {
        func_00f66f78(pri + 7, func_00f66ae0(c->x0));
    } else {
        func_00f66fe8(9, func_00f66ae0(c->x0));
    }
    return pri + 8;
}
