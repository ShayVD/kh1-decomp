/* The player's moves by state (a guess from the code): func_001271b0 (called
 * from the player's move, src/obj/plctl.c) picks a handler by state
 * (func_00126c10, func_00126f18), with the move's motions (func_00125b68,
 * func_00125be8), effects and jump arcs (func_00125dc8), the state block
 * D_002E27C8 / D_002E3190; func_001252f8 checks the abilities
 * (func_0013c968) for the moves allowed. Flag mode: nostrict (the other
 * modes are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00308CDC.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31B0.h"

/* func_001252f8 (from hand/nostrict/text_00110000_c01.c). */
typedef struct {
    u8 pad[0x170];
    u64 lo : 32;
    u64 b32 : 1;
    u64 b33 : 3;
    u64 b36 : 1;
    u64 b37 : 1;
    u64 b38 : 1;
} C01Sub148;
typedef struct { u8 pad[0x18]; u8 n; u8 id[1]; } C01Cnt;
typedef struct { u8 pad[0x10]; f32 x10; u8 pad14[0xc8 - 0x14]; C01Cnt *xc8; } C01Sub6C;
typedef struct { u8 pad[0x4c]; u16 x4c; } C01Sub130;
typedef struct {
    u32 lo : 4;
    u32 b4 : 1;
} __attribute__((aligned(8))) C01Bits160;
typedef struct Actor_252f8 {
    u32 x0;
    u8 pad4[0x38];
    f32 x3c;
    f32 x40[4];
    u8 pad50[0x1c];
    C01Sub6C *x6c;
    u8 pad70[0x30];
    f32 xa0[4];
    u8 padb0[0x80];
    C01Sub130 *x130;
    u8 pad134[0x14];
    C01Sub148 *x148;
    u8 pad14c[0x14];
    C01Bits160 x160;
    u8 pad168[0x1e8];
    f32 x350[4];
    u8 pad360[0x10];
    u64 x370;
    u8 pad378[0x48];
    f32 x3c0[3];
    f32 x3cc;
    s32 x3d0;
    u8 pad3d4[0x6c];
    u64 x440;
} C01Ply;
extern f32 D_00304D54;
extern f32 D_00306844;
extern f32 D_00306848;
extern s32 D_002C5C54;
extern s32 D_002C5C4C;
extern u32 D_002C5958;
s32 func_0013c968(s32, s32);
void func_001252f8(void) {
    C01Ply *p;
    s32 i;
    s32 j;
    s32 id;
    s32 c;

    *(u32 *)&D_002E27C8 = 0;
    D_00306844 = D_00306848 = 1.0f;
    D_00304D54 = 1.0f;
    for (i = 0; i < 3; i++) {
        p = D_002E26A0[i];
        if (!p) continue;
        id = p->x130->x4c;
        p->x148->b32 = (u32)func_0013c968(23, id);

        p->x148->b33 = func_0013c968(24, id);
        p->x148->b36 = (u32)func_0013c968(25, id);
        p->x148->b37 = (u32)func_0013c968(26, id);

        D_002E27C8.b10 += func_0013c968(16, id);
        D_00306844 += func_0013c968(27, id) * 0.5f;
        D_00306848 += func_0013c968(28, id) * 0.5f;
        p->x6c->x10 = D_002C5C54 ? (*(Cfg_308cdc **)&D_00308CDC)->e[id].b : (*(Cfg_308cdc **)&D_00308CDC)->e[id].a;
        p->x148->b38 = func_0013c968(62, id);
        for (j = 0; j < p->x6c->xc8->n; j++) {
            c = p->x6c->xc8->id[j];
            switch (c) { case 56: case 57: case 58: D_00304D54 += 0.2f; break; case 59: case 60: D_00304D54 += 0.3f; break; }

        }
    }
    if (D_002C5C54) return;
    if (D_002C5958 >> 22 & 1) return;
    D_002E27C8.b19 = func_0013c968(60, 0);
    if (func_0013c968(2, 11)) D_002E27C8.b6 = 1;
    if (D_002C5C4C) return;
    if (func_0013c968(17, 0)) D_002E27C8.b0 = 1;
    if (func_0013c968(18, 0)) D_002E27C8.b1 = 1;
    if (func_0013c968(19, 0)) D_002E27C8.b2 = 1;
    if (func_0013c968(20, 0)) D_002E27C8.b3 = 1;
    if (func_0013c968(21, 0)) D_002E27C8.b4 = 1;
    if (func_0013c968(22, 0)) D_002E27C8.b5 = 1;
    if (func_0013c968(1, 11)) {
        D_002E27C8.b9 = 1;
        for (i = 0; i < 3; i++) {
            p = D_002E26A0[i];
            if (p) p->x6c->x10 = (*(Cfg_308cdc **)&D_00308CDC)->e[p->x130->x4c].b;
        }
    }
    if (func_0013c968(3, 11)) D_002E27C8.b7 = 1;
    if (func_0013c968(4, 11)) D_002E27C8.b8 = 1;
    D_002E27C8.b23 = func_0013c968(53, 0);
    D_002E27C8.b24 = func_0013c968(54, 0);
    D_002E27C8.b25 = func_0013c968(55, 0);
    D_002E27C8.b26 = func_0013c968(56, 0);
    D_002E27C8.b27 = func_0013c968(57, 0);
    D_002E27C8.b28 = func_0013c968(58, 0);
    D_002E27C8.b29 = func_0013c968(59, 0);
}

/* func_00126108 (from hand/nostrict/text_00120000_sw.c). */
extern void func_00121fc4(f32 *, f32 *);
typedef struct { u8 pad[0x10]; f32 f10[16]; } E4;
typedef struct { u8 pad[0x28]; s32 f28, f2c, f30, f34, f38; } C4;
extern f32 D_002E27CC;
extern f32 D_002E27D0;
void func_00126108(E4 *e, f32 *dir, f32 *pos, f32 a, C4 *c, f32 b) {
    f32 v[4];
    f32 d;
    PlatVu0SubVector(v, pos, e->f10);
    v[1] = 0.0f;
    func_00121fc4(v, v);
    v[3] = v[3] * b - a;
    d = PlatVu0InnerProduct(v, dir);
    if (D_004F77F4 < d) {
        if (v[3] < D_002E27D0) {
            c->f38++;
            if (v[3] < D_002E27CC) c->f34++;
        }
    } else if (D_004F77F0 < d) {
        if (v[3] < D_002E27CC) c->f2c++;
    }
    if ((*(u32 *)&D_002E27C8) & 1) c->f28 = c->f2c;
}

/* func_00126238 (from hand/nostrict/text_00120000_sw.c). */
typedef struct { u8 b0; u8 pad[19]; } T23;
typedef struct { u8 pad[7]; u8 b7; u8 pad8[0x14]; T23 *f1c; } I23;
typedef struct { u8 pad[0x134]; I23 *f134; u8 pad138[0x3ac - 0x138]; u32 f3ac; } E23;
extern f32 func_0012ec60(s32, s32, f32 *);
extern void *func_00123158(void *, void *);
s32 func_0012ee70(E23 *e, s32 i);
typedef struct { u8 pad[0x370]; u64 f370; } E5;
typedef struct { u8 pad[0xc]; s32 fc; } C5;
typedef struct { u64 flags; u8 pad8[4]; f32 fc; f32 f10[8]; u64 f30; } O5;
extern O5 *func_0014a398(O5 *);
/* func_00126360 matches only below func_00126238. */
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

/* func_00126360 (from hand/nostrict/text_00120000_sw.c). */
extern s32 func_00122ff8(void *);
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
extern C01Ent20 *D_004F7810;
f32 func_00176850(void);
s32 func_001562d0(C01Obj2 *, C01Vec *);
#define C01MIN(a, b) ((a) < (b) ? (a) : (b))
/* func_00126360 matches only below func_00126238. */
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
        if (((*(u32 *)&D_002E27C8) >> 27 & 1) && (t -= 0.3f) < 0.0f) fl[3] = 1;
        else if (((*(u32 *)&D_002E27C8) >> 28 & 1) && (t -= 0.3f) < 0.0f) fl[4] = 1;
        else if (((*(u32 *)&D_002E27C8) >> 29 & 1) && (t -= 0.3f) < 0.0f) fl[5] = 1;
        else fl[8] = 1;
        if ((*(u32 *)&D_002E27C8) >> 26 & 1) fl[7] = 1;
    }
    if (!func_00122ff8((void *)ctx[0])) {
        func_00126238((E5 *)o, (C5 *)v, fl);
    } else {
        d = func_0012ec60(ctx[0], ctx[1], (f32 *)&a);
        PlatVu0SubVector(v, &a, &o->x10);
        y = -v->y;
        v->y = 0;
        func_00121fc4((f32 *)v, (f32 *)v);
        v->w = v->w - d;
        if (160.0f < y && y < o->x6c->x10 + 150.0f && v->w < D_002E27D0) {
            if ((*(u32 *)&D_002E27C8) >> 1 & 1) fl[0] = 1;
            else fl[1] = 1;
            v->w = (u = (v->w - 50.0f) / 14.0f) < -8.0f ? -8.0f : (8.0f < u ? 8.0f : u);
            v->y = C01MIN(y - 30.0f, o->x6c->x10) < 100.0f ? 100.0f : C01MIN(y - 30.0f, o->x6c->x10);
        } else if (v->w < D_002E27D0 && D_002E27CC < v->w) {
            fl[14] = 1;
            if ((*(u32 *)&D_002E27C8) & 1) fl[10] = 1;
            v->w = 0;
        } else if (((*(u32 *)&D_002E27C8) >> 24 & 1) && y < 160.0f && D_002E27D0 <= v->w) {
            fl[9] = 1;
        } else {
            func_00126238((E5 *)o, (C5 *)v, fl);
            if ((*(u32 *)&D_002E27C8) >> 23 & 1) fl[12] = fl[13];
        }
    }
    PlatVu0CopyVector(&b, v);
    b.w = 20.0f;
    if (func_001562d0(o, &b)) fl[2] = 1;
    if (((*(u32 *)&D_002E27C8) >> 3 & 1) && fl[8] > 0 && !fl[11]) fl[6] = 1;
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
#undef C01MIN

/* func_00126f18 (from hand/nostrict/text_s7_w30.c). */
typedef struct { u8 pad[8]; f32 x8; } S6c8;
typedef struct { u8 pad[0x29]; u8 x29; } S14c;
typedef struct {
    u32 flags; u8 pad4[0x68]; S6c8 *x6c; s32 x70; u8 pad74[0xd8]; S14c *x14c;
    u8 pad150[0x260]; f32 x3b0; u8 pad3b4[4]; f32 x3b8; u8 pad3bc[0x14]; s32 x3d0;
} Obj3d0;
typedef struct { u8 pad[4]; s32 x4; } Ctx4;
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { void (*fn)(Obj3d0 *, Ctx4 *, V4f *); u8 pad[28]; } Handler;
extern u32 D_002E3190;
extern Handler D_00350DA0[];
void func_00126e80(Obj3d0 *, Ctx4 *, V4f *);
void func_0014c580(Obj3d0 *);
void func_0013dfb8(Obj3d0 *, V4f *);
s32 func_001443a8(Obj3d0 *);
void func_0013ecf8(Obj3d0 *, u8 *, V4f *);
void func_0013dc10(Obj3d0 *, s32);
void func_00130578(Obj3d0 *, s32, f32);
f32 func_001376e8(Obj3d0 *, V4f *);
void func_00137688(Obj3d0 *, f32);
void func_0015abd0(Obj3d0 *);
f32 func_0014cc88(Obj3d0 *, f32);
/* func_00126f18: MATCH hand/nostrict (func_0014cc88 takes (o, f32): the 5.0f goes in f12 as its argument) */
void func_00126f18(Obj3d0 *o, Ctx4 *c, V4f *v) {
    u32 fl;
    switch (o->x70) {
    case 2:
        func_00126e80(o, c, v);
        if (((*(u32 *)&D_002E27C8) >> 8) & 1) {
            if ((D_002E3190 >> 26) & 1) {
                func_0014c580(o);
                return;
            }
        }
        break;
    case 4:
        func_00126e80(o, c, v);
        break;
    default:
        if (D_00350DA0[o->x70].fn) D_00350DA0[o->x70].fn(o, c, v);
        break;
    }
    if ((D_002E3190 >> 24) & 1) {
        do { func_0013dfb8(o, v); } while (0);
        return;
    }
    if (((D_002E3190 >> 26) & 1) && o->x70 == 0 && func_001443a8(o) == 0) {
        if ((((*(u32 *)&D_002E27C8) >> 4) & 1) && (!(((*(u32 *)&D_002E27C8) >> 5) & 1) || v->w < o->x6c->x8)) {
            func_0013ecf8(o, (*(u8 (*)[0x8])&D_002E31B0), v);
            func_0013dc10(o, 61);
            func_00130578(o, 0x40000000, 0.0f);
            o->x14c->x29 = 1;
            return;
        }
        if (((*(u32 *)&D_002E27C8) >> 5) & 1) {
            func_00137688(o, func_001376e8(o, v));
            do { func_0015abd0(o); } while (0);
        }
        return;
    }
    fl = o->flags;
    if (!(fl & 0x40000)) return;
    if (o->x3b8 <= o->x3b0 + 5.0f || o->x70 != 2) {
        o->flags = fl & ~0x40000;
        return;
    }
    if (fl & 0x20000) {
        if (c->x4 & 4) return;
        o->flags = fl & ~0x20000;
        return;
    }
    if (6.0f <= o->x3b0) {
        s32 save = o->x3d0;
        func_0014cc88(o, 5.0f);
        o->x3d0 = save;
        o->flags &= ~0x40000;
    }
}

