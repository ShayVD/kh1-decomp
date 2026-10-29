/* gb.x func_00f2c000: matched by hand. */
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

extern World *D_00F56DC0;
extern Ent *D_00F61428;
extern s32 D_00F61370;
extern s32 D_00F6142C;
extern s32 D_00F61384;
extern s32 D_00F80580;
extern s32 D_00F806BC;
extern s32 D_00F806C0;
extern u8 D_00F80650[];
s32 func_00f23ec0(s32);
s32 func_00f25918(s32);
s32 func_00f25978(s32);
void func_00f29038(Ent *);
void *func_00f3f9d0(void *);
void *func_00f26638(void *, s32);
void *func_00f26fb8(void *, s32, s32);
s32 func_00f3f9e8(void *);
void func_00f3fe80(s32, s32);
void func_00f36e40(s32, s32, void *);
void func_00f36d58(void *, s32);
Info *func_001bb658(s32);
void func_00f36c00(void *, s32);
void func_00f36c80(void *, void *, void *, void *, Ent *);
u8 *func_00f36ee0(void *, u8 *, s32, s32, s32, s32);
void func_00f375e8(void *);
void *func_00f268c8(void *, s32, s32, s32, s32, s32, s32, s32);

s32 func_00f2c000(s32 pri, Ctx *c) {
    Ent *o = D_00F61428;
    s32 ret = 0;
    Ent *e;
    s32 id;
    Info *info;
    Ent tmp;
    s32 t;
    s32 k;

    if (o == NULL) {
        if (!(D_00F56DC0->x74 & 2)) {
            e = &D_00F56DC0->x48;
            id = e->x4 - 1;
            if (D_00F61370 == 0 && func_00f23ec0(id) <= 0) {
                return 0;
            }
            D_00F806BC = func_00f25918(id);
            D_00F806C0 = func_00f25978(id);
            if (D_00F80580) {
                func_00f29038(e);
                ret = 1;
            }
        } else {
            return 0;
        }
    } else {
        e = o;
        id = e->x4 - 1;
        if (D_00F61370 == 0 && func_00f23ec0(id) <= 0) {
            return 0;
        }
        if (D_00F80580) {
            func_00f29038(o);
            ret = 1;
        }
    }
    c->x0 = func_00f3f9d0(c->x0);
    c->x0 = func_00f26638(c->x0, 2);
    c->x0 = func_00f26fb8(c->x0, 1776, 1824);
    func_00f3fe80(pri, func_00f3f9e8(c->x0));
    pri++;
    func_00f36e40(pri, pri + 1, c->x8);
    pri += 2;
    func_00f36d58(c->x8, 0);
    info = func_001bb658(e->x4 - 1);
    func_00f36c00(c->x4 + 16, e->x4 - 1);
    if (D_00F6142C == 0 && func_00f23ec0(e->x4 - 1) == 0) {
        f32 *f = (f32 *)(c->x4 + 16);
        f[15] *= 0.5f;
    }
    tmp = *e;
    tmp.x0 = D_00F56DC0->x60;
    func_00f36c80(c->x4 + 144, c->x4 + 80, D_00F80650, D_00F80650 - 128, &tmp);
    k = info->x9 + 1;
    if (info->x9 == 0xFF) {
        k = 0;
    }
    c->x4 = func_00f36ee0(c->x8, c->x4, info->x8 + 1, k, D_00F806BC, D_00F806C0);
    func_00f375e8(c->x8);
    t = D_00F61384;
    c->x0 = func_00f3f9d0(c->x0);
    c->x0 = func_00f26fb8(c->x0, 1792, 1856);
    c->x0 = func_00f268c8(c->x0, t, 5, 1, 64, 2, 448, 382);
    func_00f3fe80(pri, func_00f3f9e8(c->x0));
    return ret;
}
