/* gb.x func_00f23230: matched by hand. */
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
extern u8 *D_00F56DC0;
extern s32 D_00F56FC4;
extern f32 D_00F56FCC;
extern s32 D_00F56FD0;
extern u8 D_00F74280[];
void sceVu0UnitMatrix(OvlMtx);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void func_00f36e40(s32, s32, void *);
void func_00f36e98(s32, s32, void *);
void func_00f36d58(void *, s32);
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
void func_00f36c00(void *, s32);
void func_00f36c80(void *, void *, void *, void *, Ent *);
s32 func_00f25b40(s32, void *);
u8 *func_00f37448(void *, u8 *, s32, s32, void *);
f32 func_00f28f38(s32);
u8 *func_00f37270(void *, u8 *, s32, s32, s32, f32);
void func_00f375e8(void *);
void *func_00f3f9d0(void *);
void *func_00f26638(void *, s32);
void *func_00f26fb8(void *, s32, s32);
void *func_00f268c8(void *, s32, s32, s32, s32, s32, s32, s32);
void *func_00f26500(void *);
s32 func_00f3f9e8(void *);
void func_00f3fe80(s32, s32);
void func_00f3fef0(s32, s32);

s32 func_00f23230(s32 pri, Ctx *c, u8 *cam, s32 alpha, s32 lim, Grp *g) {
    OvlMtx m;
    u8 tmp[64];
    Ent *e;
    Info *info;
    GbPos pos;
    s32 i;
    s32 k;
    if (g == NULL) {
        g = (Grp *)(D_00F56DC0 + 160);
    }
    if (D_00F56FC4 != 0) {
        sceVu0UnitMatrix(m);
        m[2][2] = m[1][1] = m[0][0] = D_00F56FCC;
    }
    if (D_00F56FD0 == 0) {
        func_00f36e40(pri, pri + 1, c->x8);
    } else {
        func_00f36e98(2, 1, c->x8);
    }
    func_00f36d58(c->x8, 0);
    for (i = 0, e = g->e; i < g->n; i++, e++) {
        if (e->x4 == 0) {
            continue;
        }
        info = func_001bb658(e->x4 - 1);
        pos = func_001bbdf0(e);
        func_00f36c00(c->x4 + 16, e->x4 - 1);
        if (D_00F56FC4 != 0 && D_00F74280[e->x4 - 1] == 0) {
            sceVu0MulMatrix((f32 (*)[4])(c->x4 + 16), (f32 (*)[4])(c->x4 + 16), m);
        }
        *(f32 *)(c->x4 + 76) = *(f32 *)(cam + 60);
        func_00f36c80(c->x4 + 144, c->x4 + 80, cam + 192, cam + 64, e);
        if (e->x6 & 0x20) {
            if (alpha != 128) {
                if (lim < e->p.y) {
                    continue;
                }
                if (lim >= e->p.y + pos.y) {
                    continue;
                }
            }
            if (func_00f25b40(e->x4 - 1, tmp)) {
                c->x4 = func_00f37448(c->x8, c->x4, info->x8 + 1, e->x8, tmp);
            } else {
                k = info->x9;
                if (k == 0xFF) {
                    k = 0;
                } else {
                    k++;
                }
                c->x4 = func_00f37270(c->x8, c->x4, info->x8 + 1, k, e->x8, func_00f28f38(i));
            }
        }
    }
    func_00f375e8(c->x8);
    if (alpha != 128) {
        if (D_00F56FD0 == 0) {
            func_00f36e40(pri + 3, pri + 4, c->x8);
        } else {
            func_00f36e98(5, 6, c->x8);
        }
        func_00f36d58(c->x8, 0);
        for (i = 0, e = g->e; i < g->n; i++, e++) {
            if (e->x4 == 0) {
                continue;
            }
            info = func_001bb658(e->x4 - 1);
            pos = func_001bbdf0(e);
            func_00f36c00(c->x4 + 16, e->x4 - 1);
            *(f32 *)(c->x4 + 76) = *(f32 *)(cam + 60);
            func_00f36c80(c->x4 + 144, c->x4 + 80, cam + 192, cam + 64, e);
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
                c->x4 = func_00f37270(c->x8, c->x4, info->x8 + 1, k, e->x8, func_00f28f38(i));
            }
        }
        func_00f375e8(c->x8);
        c->x0 = func_00f3f9d0(c->x0);
        c->x0 = func_00f26638(c->x0, 3);
        c->x0 = func_00f26fb8(c->x0, 1776, 1824);
        if (D_00F56FD0 == 0) {
            func_00f3fe80(pri + 2, func_00f3f9e8(c->x0));
        } else {
            func_00f3fef0(4, func_00f3f9e8(c->x0));
        }
        c->x0 = func_00f3f9d0(c->x0);
        c->x0 = func_00f26fb8(c->x0, 1792, 1856);
        c->x0 = func_00f268c8(c->x0, alpha, 5, 1, 64, 2, 448, 382);
        c->x0 = func_00f26500(c->x0);
        c->x0 = func_00f26fb8(c->x0, 1776, 1824);
        if (D_00F56FD0 == 0) {
            func_00f3fe80(pri + 5, func_00f3f9e8(c->x0));
        } else {
            func_00f3fef0(7, func_00f3f9e8(c->x0));
        }
    } else {
        c->x0 = func_00f3f9d0(c->x0);
        c->x0 = func_00f26fb8(c->x0, 1776, 1824);
        if (D_00F56FD0 == 0) {
            func_00f3fe80(pri + 2, func_00f3f9e8(c->x0));
        } else {
            func_00f3fef0(4, func_00f3f9e8(c->x0));
        }
    }
    c->x0 = func_00f3f9d0(c->x0);
    c->x0 = func_00f26fb8(c->x0, 1792, 1856);
    if (D_00F56FD0 == 0) {
        func_00f3fe80(pri + 7, func_00f3f9e8(c->x0));
    } else {
        func_00f3fef0(9, func_00f3f9e8(c->x0));
    }
    return pri + 8;
}
