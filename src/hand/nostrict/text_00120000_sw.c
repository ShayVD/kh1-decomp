#include "common.h"
#include "data/bss_004F.h"

typedef struct { u8 b0; u8 pad[19]; } T23;
typedef struct { u8 pad[7]; u8 b7; u8 pad8[0x14]; T23 *f1c; } I23;
typedef struct { u8 pad[0x134]; I23 *f134; u8 pad138[0x3ac - 0x138]; u32 f3ac; } E23;
extern s32 func_00122ff8(void *);
extern f32 func_0012ec60(s32, s32, f32 *);
extern void func_00267530(void *, void *, void *);
extern void func_002675a8(void *, void *);
extern void *func_00123158(void *, void *);
extern void func_00121fc4(f32 *, f32 *);
s32 func_0012ee70(E23 *e, s32 i);
extern u32 D_002E27C8;

typedef struct { u8 pad[0x10]; f32 f10[16]; } E4;
typedef struct { u8 pad[0x28]; s32 f28, f2c, f30, f34, f38; } C4;
extern f32 D_002E27CC;
extern f32 D_002E27D0;
extern f32 D_004F77F0;
extern f32 D_004F77F4;
extern f32 func_00267390(f32 *, f32 *);

void func_00126108(E4 *e, f32 *dir, f32 *pos, f32 a, C4 *c, f32 b) {
    f32 v[4];
    f32 d;
    func_00267530(v, pos, e->f10);
    v[1] = 0.0f;
    func_00121fc4(v, v);
    v[3] = v[3] * b - a;
    d = func_00267390(v, dir);
    if (D_004F77F4 < d) {
        if (v[3] < D_002E27D0) {
            c->f38++;
            if (v[3] < D_002E27CC) c->f34++;
        }
    } else if (D_004F77F0 < d) {
        if (v[3] < D_002E27CC) c->f2c++;
    }
    if (D_002E27C8 & 1) c->f28 = c->f2c;
}

typedef struct { u8 pad[0x370]; u64 f370; } E5;
typedef struct { u8 pad[0xc]; s32 fc; } C5;
typedef struct { u64 flags; u8 pad8[4]; f32 fc; f32 f10[8]; u64 f30; } O5;
extern O5 *func_0014a398(O5 *);

void func_00126238(E5 *e, C5 *c, void *s) {
    void *p;
    s32 i;
    O5 *o;
    f32 v[4];
    p = 0;
    while ((p = func_00123158(e, p)) != 0) {
        i = -1;
        while ((i = func_0012ee70(p, i)) >= 0) {
            f32 f = func_0012ec60((s32)p, i, v);
            func_00126108((E4 *)e, (f32 *)c, v, f, s, 1.0f);
        }
    }
    o = 0;
    while ((o = func_0014a398(o)) != 0) {
        if (((s32)(o->flags >> 12) & 3) != ((s32)(e->f370 >> 37) & 3) && ((s32)(o->f30 >> 10) & 1))
            func_00126108((E4 *)e, (f32 *)c, o->f10, o->fc, s, 0.25f);
    }
    c->fc = 0;
}

/* func_00126360 matches only below func_00126238. */
typedef struct { f32 x, y, z, w; } C01Vec;
typedef struct { u8 pad[0x10]; f32 x10; u8 pad2[0xd0 - 0x14]; u8 xd0; } C01Sub6c;
typedef struct { u8 pad[0x29]; u8 x29; } C01Sub14c;
typedef struct {
    u8 pad[0x10];
    C01Vec x10;
    u8 pad2[0x6c - 0x20];
    C01Sub6c *x6c;
    u8 pad3[0x14c - 0x70];
    C01Sub14c *x14c;
    u8 pad4[0x164 - 0x150];
    s32 x164;
} C01Obj2;
typedef struct { s16 id; u8 pad[18]; } C01Ent20;

extern f32 D_002E27CC;
extern f32 D_002E27D0;
extern C01Ent20 *D_004F7810; /* src/data/bss_004F.c: E7810 *D_004F7810 */

f32 func_00176850(void);
s32 func_001562d0(C01Obj2 *, C01Vec *);

#define C01MIN(a, b) ((a) < (b) ? (a) : (b))


s32 func_00126360(C01Obj2 *o, s32 *ctx, C01Vec *v) {
    s32 fl[66];
    C01Vec a;
    C01Vec b;
    f32 d;
    f32 y;
    f32 t;
    f32 u;
    s32 i;
    s32 k;

    for (i = 0; i < 66; i++) fl[i] = 0;
    if (!(o->x14c->x29 < o->x6c->xd0)) {
        t = func_00176850();
        if ((D_002E27C8 >> 27 & 1) && (t -= 0.3f) < 0.0f) fl[3] = 1;
        else if ((D_002E27C8 >> 28 & 1) && (t -= 0.3f) < 0.0f) fl[4] = 1;
        else if ((D_002E27C8 >> 29 & 1) && (t -= 0.3f) < 0.0f) fl[5] = 1;
        else fl[8] = 1;
        if (D_002E27C8 >> 26 & 1) fl[7] = 1;
    }
    if (!func_00122ff8((void *)ctx[0])) {
        func_00126238((E5 *)o, (C5 *)v, fl);
    } else {
        d = func_0012ec60(ctx[0], ctx[1], (f32 *)&a);
        func_00267530(v, &a, &o->x10);
        y = -v->y;
        v->y = 0;
        func_00121fc4((f32 *)v, (f32 *)v);
        v->w = v->w - d;
        if (160.0f < y && y < o->x6c->x10 + 150.0f && v->w < D_002E27D0) {
            if (D_002E27C8 >> 1 & 1) fl[0] = 1;
            else fl[1] = 1;
            v->w = (u = (v->w - 50.0f) / 14.0f) < -8.0f ? -8.0f : (8.0f < u ? 8.0f : u);
            v->y = C01MIN(y - 30.0f, o->x6c->x10) < 100.0f ? 100.0f : C01MIN(y - 30.0f, o->x6c->x10);
        } else if (v->w < D_002E27D0 && D_002E27CC < v->w) {
            fl[14] = 1;
            if (D_002E27C8 & 1) fl[10] = 1;
            v->w = 0;
        } else if ((D_002E27C8 >> 24 & 1) && y < 160.0f && D_002E27D0 <= v->w) {
            fl[9] = 1;
        } else {
            func_00126238((E5 *)o, (C5 *)v, fl);
            if (D_002E27C8 >> 23 & 1) fl[12] = fl[13];
        }
    }
    func_002675a8(&b, v);
    b.w = 20.0f;
    if (func_001562d0(o, &b)) fl[2] = 1;
    if ((D_002E27C8 >> 3 & 1) && fl[8] > 0 && !fl[11]) fl[6] = 1;
    for (i = 0; i < 66; i++) {
        if (fl[i] > 0 && D_004F7810[i].id != o->x164) return i;
    }
    if (o->x14c->x29 >= 2) {
        if (o->x164 == D_004F7810[14].id) {
            if (fl[14] > 0) return 13;
        }
        if (o->x164 != D_004F7810[11].id) return 11;
    }
    return 13;

}
