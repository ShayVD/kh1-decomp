/* Windows drawn at objects (a guess at the name), 0x0010a4d8-0x0010c0c8:
 * func_0010bdd0 starts a task (func_0010ba98) for an object's sprite
 * window, func_0010b6c0 draws it at the object through the camera, and
 * func_0010a550 / func_0010a5d0 / func_0010a780 build its GS packets. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002B6778.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002A6238.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002A6234.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002BBDE4.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "m2c.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0048CC30.h"
#include "data/pieces/D_002A3F3C.h"

/* func_0010a550 (from hand/text_00100000_h2.c). */
extern u64 D_002B70B0[];
extern s32 D_00495250;
void func_0010a4d8(u64 *, s32, s32, s32, s32, s32, s32);
s32 func_0010a550(u64 *p, s32 a1, s32 a2, s32 a3, s32 a4, s32 idx, s32 a6) {
    p[0] = D_002B70B0[idx];
    p[1] = 0;
    p += 2;
    func_0010a4d8(p, a2, a6, a4, 4, a3, D_00495250);
    ((s32 *)p)[7] = 0x8000;
    ((s32 *)p)[19] = 0x8000;
    return a1 + 13;
}

/* func_0010b030 (from hand/text_00100000_h28.c). */
extern s32 FlushCache(s32);
extern s32 sceGsExecLoadImage(void *, void *);
extern s32 sceGsSyncPath(s32, s32);
extern u8 D_002BC1B0[];
extern void sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_0010b030(u8 *buf) {
    u8 *clut;
    u8 *p;
    s32 i;
    sceGsSetDefLoadImage(D_002BC1B0, 0x1800, 4, 27, 0, 0, 256, 128);
    clut = buf + 0x8000;
    FlushCache(0);
    sceGsExecLoadImage(D_002BC1B0, buf);
    sceGsSyncPath(0, 0);
    sceGsSetDefLoadImage(D_002BC1B0, 0x3FF4, 1, 0, 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(D_002BC1B0, clut);
    p = clut;
    for (i = 0; i < 256; i++) {
        *p++ = 0;
        *p++ = 0;
        *p = 0;
        p += 2;
    }
    sceGsSyncPath(0, 0);
    sceGsSetDefLoadImage(D_002BC1B0, 0x3FF8, 1, 0, 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(D_002BC1B0, clut);
    sceGsSyncPath(0, 0);
}

/* func_0010b170 (from auto/text_00100000_3.c). */
void func_0010b170(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, f32 *, 0x3C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x5C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x58) = 1.0f;
}

/* func_0010b190 (from hand/text_00100000_h2.c). */
extern u8 D_00495210[];
void func_00267b08(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_0010b190(u8 *p) {
    func_00267b08(D_00495210, 512.0f, 1.0f, 1.0f,
                  *(f32 *)(p + 0x30) + 2048.0f, *(f32 *)(p + 0x34) + 2048.0f,
                  1.0f, 16777000.0f, 2.0f, 4000000.0f);
}

/* func_0010b208 (from auto/text_00100000_9.c). */
M2C_UNK func_00267328(s32, s32, void *);
M2C_UNK func_00267620(void *);
void func_0010b208(s32 arg0, s32 arg1, void *arg2) {
    s32 sp[16];
    func_00267620(sp);
    M2C_FIELD(sp, f32 *, 0x0) = M2C_FIELD(arg2, f32 *, 0);
    M2C_FIELD(sp, f32 *, 0x14) = M2C_FIELD(arg2, f32 *, 4);
    M2C_FIELD(sp, f32 *, 0x28) = M2C_FIELD(arg2, f32 *, 8);
    func_00267328(arg0, arg1, sp);
}

/* func_0010b270 (from auto/text_00100000_10.c). */
M2C_UNK func_00267768(void *, M2C_UNK *, f32);
extern M2C_UNK D_00495190;
#define func_00267328 ((M2C_UNK (*)(void *, M2C_UNK *, void *)) func_00267328)
#define D_00495210 (*(M2C_UNK (*)) &D_00495210)
void func_0010b270(void *arg0, void *arg1) {
    s32 sp[16];
    func_00267768(sp, (M2C_UNK *)&D_002BCAF0, M2C_FIELD(arg1, f32 *, 0x20));
    func_00267328(sp, &D_00495190, sp);
    func_00267328(arg0, &D_00495210, sp);
}
#undef func_00267328
#undef D_00495210

/* func_0010b2d0 (from hand/text_00100000_h28.c). */
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
typedef struct { u8 pad[0x1c]; f32 ry; } Rot;
extern void func_00267578(Mtx, Mtx, void *);
extern void func_002676c0(Mtx, void *, f32);
extern void sceVu0MulMatrix(Mtx, Mtx, Mtx);
extern Mtx D_00495190_0010b2d0 __asm__("D_00495190");
#define D_00495190 D_00495190_0010b2d0
extern Mtx D_00495210_0010b2d0 __asm__("D_00495210");
#define D_00495210 D_00495210_0010b2d0
void func_0010b2d0(Mtx out, Rot *r, void *t) {
    Mtx m;
    f32 a = r->ry;
    if (a > 180.0f) {
        a -= 180.0f;
    } else {
        a += -180.0f;
    }
    func_002676c0(m, D_002BCAF0, a / 180.0f * 3.1415928f);
    func_00267578(m, m, t);
    sceVu0MulMatrix(m, D_00495190, m);
    sceVu0MulMatrix(out, D_00495210, m);
}
#undef D_00495190
#undef D_00495210

/* func_0010ba98 (from hand/text_00100000_s11_w38.c). */
typedef struct {
    s32 id;
    s16 pad4;
    u16 f6;
    u16 anim;
    u16 kind;
    u16 c;
    u16 pade;
    u16 n10;
    u16 n12;
    void (*cb)();
    s32 state;
    f32 f1c;
    u8 pad20[0x10];
    f32 x, y;
    u8 pad38[8];
    f32 w, h;
    u8 pad48[8];
    f32 f50, f54;
} Win;
typedef struct { u8 pad0[4]; s32 f4; u8 pad8[6]; u16 e; u8 pad10[0x14]; s32 f24; } P20;
typedef struct { u8 pad0[0x10]; u16 n; u16 pad12; f32 dx; f32 dy; Win *win; P20 *p20; } Task;
extern void func_0010b6c0(Win *);
extern s32 func_0010ea00(P20 *);
extern void func_0010e3f0(P20 *);
extern s32 D_002BC740;
#define func_0010b170 ((void (*)(Win *)) func_0010b170)
/* rodata (RO 0048cd30: jump table at 0x48cd30), mode hand (strict). Verified: wqb03_rr.py 0048cd30 MATCH.
 * func_0010ba98: s11w38 from w34's 2w. FLAGGED:
 *  (1) dead set `w = 0;` before func_0010b170(t->win) in case 0 (life1 deletes it; keeps the bb0 PRE copy) [w34];
 *  (2) redundant FP-condition set `if (t->dx < 0.0f) w = t->win;` at the start of the shared `case 0: case 3:` arm
 *      (w already equals t->win there, so it changes nothing). The FP test cannot be if-converted (no FP cmov),
 *      so the conditional set kills w on one path: the copy 212 = w no longer reaches the arm's t->win load, CPROP2
 *      leaves it on the PRE reg (lhu v0,16(a0)). The arm-end `w = t->win;` of w34 is gone; the test and the conditional set
 *      leave no code in the output (both hold t->win; deleted after allocation). */
s32 func_0010ba98(Task *t) {
    Win *w = t->win;
    f32 f;

    switch (w->state) {
    case 0:
        w = 0;
        func_0010b170(t->win);
        switch ((w = t->win)->c) {
        case 1:
            t->dy = t->dx = 1.0f / (f32)(t->win->n10 - 2);
            break;
        case 2:
            t->dy = t->dx = 1.0f / (f32)(t->win->n10 - 1);
            break;
        case 0:
        case 3:
            if (t->dx < 0.0f) w = t->win;
            t->dy = t->dx = 1.0f / (f32)t->win->n10;
            break;
        }
        t->win->state = 1;
        t->n = t->win->n10;
        t->win->f54 = 0.0f;
        t->win->f50 = 0.0f;
    case 1:
        if (t->n != 0) {
            if (w->c == 1 && t->n == w->c) {
                w->f50 -= t->dx * 0.5f;
                w->f54 -= t->dy * 0.5f;
            } else {
                w->f50 += t->dx;
                w->f54 += t->dy;
            }
            func_0010b6c0(w);
            t->n--;
            break;
        }
        w->f50 = 1.0f;
        w->f54 = 1.0f;
        w->state = 2;
        if (w->cb) {
            w->cb(t->p20->e, t->p20->f24);
            w = t->win;
        }
    case 2:
        func_0010b6c0(w);
        w = t->win;
        if (w->cb && t->p20->f4) {
            func_0010ea00(t->p20);
            if (D_002BC740 == 1) {
                func_0010e3f0(t->p20);
            }
            w = t->win;
        }
        if (w->state != 3 || t->win->n12 != 0) break;
    case 3:
        t->n = w->n12;
        w->state = 4;
        t->dy = t->dx = 1.0f / (f32)w->n12;
    case 4:
        if (t->n != 0) {
            w->f50 -= t->dx;
            w->f54 -= t->dy;
            func_0010b6c0(w);
            t->n--;
            break;
        }
        w->f50 = 0.0f;
        w->state = 5;
        w->f54 = 0.0f;
    case 5:
        w->state = 0;
        if (w->cb) {
            w->cb();
        }
        return 4;
    }
    if (D_002BC740 == 1) {
        t->win->state = 0;
        return 4;
    }
    return 0;
}
#undef func_0010b170

/* func_0010bd90 (from auto/text_00100000.c). */
#define func_0010e3f0 ((M2C_UNK (*)(void *)) func_0010e3f0)
void func_0010bd90(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x18) != 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = arg1;
        M2C_FIELD(arg0, s32 *, 0x18) = 3;
        func_0010e3f0(arg0 + 0x80);
    }
}
#undef func_0010e3f0

/* func_0010bdd0 (from hand/text_00100000_h51.c). */
typedef struct { f32 x, y, z, w; } V4b;
typedef struct {
    u8 pad0[4]; s32 x4; s16 x8; s16 xA; s16 xC; s16 xE; u8 x10; u8 pad11; u8 x12; u8 x13;
    f32 x14; u8 pad18[8]; s32 x20; struct Obj_s *x24; s32 x28;
} Spr;
typedef struct Obj_s {
    u8 pad0[4]; u16 type; u8 pad6[4]; u16 xA; u16 xC; u16 xE; u16 x10; u16 x12; s32 x14; s32 x18;
    u8 pad1c[4]; f32 x20; u8 pad24[12]; V4b pos; V4b sc; u8 pad50[0x20]; V4b v70; Spr spr;
} Obj;
typedef struct { u8 pad[0x1c]; void *obj; void *spr; } Task_0bdd0;
#define SPR(t) ((Spr *)(t)->spr)
extern u16 D_002B67C0[];
extern u16 D_002B67C8[];
extern f32 D_002B6798[];
extern u16 D_002B6780[];
Task_0bdd0 *func_0011f090(void *, s32, void *);
void func_002675a8(V4b *, V4b *);
void func_0010bdd0(Obj *o, s32 arg) {
    Task_0bdd0 *t;
    u16 type;
    Spr *sp;
    t = func_0011f090(D_002B7590, D_00495254++, func_0010ba98);
    if (t == 0) return;
    t->spr = &o->spr;
    t->obj = o;
    func_002675a8(&o->v70, &o->pos);
    o->x18 = 0;
    o->x14 = arg;
    sp = SPR(t);
    sp->x8 = (u32)(o->pos.x + 254.0f - o->sc.x * 12.0f);
    sp->xA = (u32)(o->pos.y + 180.0f - o->sc.y * 12.0f);
    sp->xC = o->pos.x + 256.0f;
    o->spr.x4 = 0;
    sp->x12 = 0;
    sp->x24 = o;
    SPR(t)->x20 = 0;
    SPR(t)->xE = 0;
    SPR(t)->x13 = 0;
    SPR(t)->x13 &= ~1;
    o->x10 = D_002B67C0[o->xC];
    SPR(t)->x14 = 0.5f;
    o->x12 = D_002B67C8[o->xE];
    type = o->type;
    o->x20 = D_002B6798[type];
    SPR(t)->x28 = 0;
    o->xA = D_002B6780[type];
    switch (type) {
    case 0:
        SPR(t)->x10 = 0;
        SPR(t)->x13 &= ~2;
        break;
    case 1:
        SPR(t)->x10 = 0;
        SPR(t)->x13 |= 2;
        break;
    default:
        SPR(t)->x10 = 1;
        SPR(t)->x13 |= 2;
        break;
    }
}
#undef SPR

/* func_0010c010 (from auto/text_00100000_9.c). */
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
s32 func_0010c010(void) {
    func_0011f130((M2C_UNK *)&D_002B7590, 0);
    D_00495254 = 0;
    return 0;
}

/* func_0010c040 (from auto/text_00100000.c). */
M2C_UNK func_00267930(M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_002B74D0;
extern M2C_UNK D_002B74E0;
extern M2C_UNK D_002B74F0;
extern M2C_UNK D_004951D0;
void func_0010c040(void) {
    func_00267930(&D_004951D0, &D_002B74D0, &D_002B74E0, &D_002B74F0);
}

/* func_0010c078 (from auto/text_00100000_10.c). */
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_002B7500;
#define func_0010c040 ((M2C_UNK (*)()) func_0010c040)
void func_0010c078(void) {
    D_00495254 = 0;
    func_0010c040();
    func_0011efa8((M2C_UNK *)&D_002B7590, &D_002B7500, 0x24, 4);
    func_0011ef10(0x2BFE8, &func_0010c010);
}
#undef func_0010c040

