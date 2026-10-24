#include "common.h"
/* func_00126f18: MATCH hand/nostrict (func_0014cc88 takes (o, f32): the 5.0f goes in f12 as its argument) */
typedef struct { u8 pad[8]; f32 x8; } S6c8;
typedef struct { u8 pad[0x29]; u8 x29; } S14c;
typedef struct {
    u32 flags; u8 pad4[0x68]; S6c8 *x6c; s32 x70; u8 pad74[0xd8]; S14c *x14c;
    u8 pad150[0x260]; f32 x3b0; u8 pad3b4[4]; f32 x3b8; u8 pad3bc[0x14]; s32 x3d0;
} Obj3d0;
typedef struct { u8 pad[4]; s32 x4; } Ctx4;
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { void (*fn)(Obj3d0 *, Ctx4 *, V4f *); u8 pad[28]; } Handler;
#include "data/pieces/D_002E27C8.h"
extern u32 D_002E3190;
extern Handler D_00350DA0[];
#include "data/pieces/D_002E31B0.h"
void func_00126e80(Obj3d0 *, Ctx4 *, V4f *);
void func_0014c580(Obj3d0 *);
void func_0013dfb8(Obj3d0 *, V4f *);
s32 func_001443a8(Obj3d0 *);
void func_0013ecf8(Obj3d0 *, u8 *, V4f *);
void func_0013dc10(Obj3d0 *, s32);
void func_00130578(Obj3d0 *, f32, s32);
f32 func_001376e8(Obj3d0 *, V4f *);
void func_00137688(Obj3d0 *, f32);
void func_0015abd0(Obj3d0 *);
f32 func_0014cc88(Obj3d0 *, f32);
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
            func_00130578(o, 0.0f, 0x40000000);
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

/* func_00172998: MATCH hand/nostrict. Shared labels against if-conversion: r0 (return 0) reached from the p90 test, r1 (the final return 1) from the x90 test and after the range tests; r = 0 before the range tests (w13). */
typedef struct { f32 x, y, z, w; } V4_29;
typedef struct { u8 pad0[0x30]; V4_29 v30; u8 pad40[0x30]; s32 w70; u8 pad74[0x1C]; u64 x90; } Ob29;

static inline s32 inl_free(Ob29 *o) {
    s32 r = 1;
    if (o->x90 != 0) r = 0;
    return r;
}
