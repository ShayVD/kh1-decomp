/* wm.x func_00f530f8: matched by hand. */
#include "ovl.h"

typedef struct {
    u16 x0;
    u16 x2;
    u16 x4;
    u16 x6;
    u16 x8;
    u16 xA;
} Ent;

typedef struct {
    u8 pad0[0x48];
    Ent x48;
    u8 pad54[0x60 - 0x54];
    u16 x60;
    u8 pad62[0x74 - 0x62];
    u16 x74;
} World;

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

extern World *D_00F9B540;
extern Ent *D_00FA5BA8;
extern s32 D_00FA5AF0;
extern s32 D_00FA5BAC;
extern s32 D_00FA5B04;
extern s32 D_0108CD40;
extern s32 D_0108CE7C;
extern s32 D_0108CE80;
extern u8 D_0108CE10[];
s32 func_00f4afb8(s32);
s32 func_00f4ca10(s32);
s32 func_00f4ca70(s32);
void func_00f50130(Ent *);
void *func_00f66ac8(void *);
void *func_00f4d730(void *, s32);
void *func_00f4e0b0(void *, s32, s32);
s32 func_00f66ae0(void *);
void func_00f66f78(s32, s32);
void func_00f5df38(s32, s32, void *);
void func_00f5de50(void *, s32);
Info *func_001bb658(s32);
void func_00f5dcf8(void *, s32);
void func_00f5dd78(void *, void *, void *, void *, Ent *);
u8 *func_00f5dfd8(void *, u8 *, s32, s32, s32, s32);
void func_00f5e6e0(void *);
void *func_00f4d9c0(void *, s32, s32, s32, s32, s32, s32, s32);

s32 func_00f530f8(s32 pri, Ctx *c) {
    Ent *o = D_00FA5BA8;
    s32 ret = 0;
    Ent *e;
    s32 id;
    Info *info;
    Ent tmp;
    s32 t;
    s32 k;

    if (o == NULL) {
        if (!(D_00F9B540->x74 & 2)) {
            e = &D_00F9B540->x48;
            id = e->x4 - 1;
            if (D_00FA5AF0 == 0 && func_00f4afb8(id) <= 0) {
                return 0;
            }
            D_0108CE7C = func_00f4ca10(id);
            D_0108CE80 = func_00f4ca70(id);
            if (D_0108CD40) {
                func_00f50130(e);
                ret = 1;
            }
        } else {
            return 0;
        }
    } else {
        e = o;
        id = e->x4 - 1;
        if (D_00FA5AF0 == 0 && func_00f4afb8(id) <= 0) {
            return 0;
        }
        if (D_0108CD40) {
            func_00f50130(o);
            ret = 1;
        }
    }
    c->x0 = func_00f66ac8(c->x0);
    c->x0 = func_00f4d730(c->x0, 2);
    c->x0 = func_00f4e0b0(c->x0, 1776, 1824);
    func_00f66f78(pri, func_00f66ae0(c->x0));
    pri++;
    func_00f5df38(pri, pri + 1, c->x8);
    pri += 2;
    func_00f5de50(c->x8, 0);
    info = func_001bb658(e->x4 - 1);
    func_00f5dcf8(c->x4 + 16, e->x4 - 1);
    if (D_00FA5BAC == 0 && func_00f4afb8(e->x4 - 1) == 0) {
        f32 *f = (f32 *)(c->x4 + 16);
        f[15] *= 0.5f;
    }
    tmp = *e;
    tmp.x0 = D_00F9B540->x60;
    func_00f5dd78(c->x4 + 144, c->x4 + 80, D_0108CE10, D_0108CE10 - 128, &tmp);
    k = info->x9 + 1;
    if (info->x9 == 0xFF) {
        k = 0;
    }
    c->x4 = func_00f5dfd8(c->x8, c->x4, info->x8 + 1, k, D_0108CE7C, D_0108CE80);
    func_00f5e6e0(c->x8);
    t = D_00FA5B04;
    c->x0 = func_00f66ac8(c->x0);
    c->x0 = func_00f4e0b0(c->x0, 1792, 1856);
    c->x0 = func_00f4d9c0(c->x0, t, 5, 1, 64, 2, 448, 382);
    func_00f66f78(pri, func_00f66ae0(c->x0));
    return ret;
}
