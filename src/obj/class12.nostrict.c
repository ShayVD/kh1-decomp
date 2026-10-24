/* Object class 0x12, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_0015dbf8 registers in the class table D_00350D88
 * (func_0014f830(0x12, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class12.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_00304BE8_s.h"

/* func_0015d6c8 (from hand/nostrict/text_00150000_h36.c). */
typedef struct { u8 b0; u8 type; u16 bone; f32 off; f32 dy; f32 r; f32 h; } CylSrc;
typedef struct { u8 pad[4]; u8 n4, n5, n6, n7; u8 pad8[0xC]; CylSrc *cyl; CylSrc *cyl2; } CylHdr;
typedef struct { u8 pad[0xD0]; f32 m[4][4]; } Mtx0D0;
typedef struct { u8 pad[0x60]; f32 v60[4]; f32 v70[4]; f32 v80[4]; s32 x90; Mtx0D0 *mtx; u8 pad98[0x78]; f32 x110[4]; s32 x120; } Sub148;
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4]; f32 vel[4]; f32 sx, sy; u8 pad48[0x24]; struct { u8 pad[4]; f32 f4, f8; } *p6C; s32 x70; u8 pad74[0xC0];
    CylHdr *hdr; u8 pad138[0x10]; Sub148 *p148; u8 pad14c[4]; f32 rot; u8 pad154[0xC]; union { u64 d; u32 w; } x160; u8 pad168[0x1A6];
    u16 h30E; u8 pad310[0x60]; u64 flags; u8 pad378[0x2C]; u32 mask; u32 mask2;
    u8 pad3ac[0x14]; f32 x3C0[4];
} CylObj;
void func_00105a30(s32, s32, f32 *);
void func_0015d5e8(void *);
s32 func_0015d6c8(CylObj *o, f32 *v) {
    f32 a[4], b[4];
    f32 z = 0.0f;
    if (v[3] == z || o->h30E == 0xFFFF) return 0;
    func_00105a30(-1, o->h30E, a);
    PlatVu0Normalize(b, v);
    if (z < PlatVu0InnerProduct(a, b)) return 0;
    func_0015d5e8(o);
    return 1;
}

/* func_0015d848 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { u8 pad[0xC0]; f32 xC0[4]; f32 xD0[4]; } M59;
typedef struct {
    u32 w0; u8 pad4[0xC]; f32 pos[4]; f32 x20[4];
    u8 pad30[0x148 - 0x30];
    M59 *m;
    u8 pad14c[0x164 - 0x14c];
    s32 st;
    u8 pad168[0x30e - 0x168];
    u16 h30e;
} Ob59;
typedef struct { u8 pad[4]; f32 f4; } Tk59;
void func_0015d7b8(Ob59 *, f32 *);
void func_00130398(void *, s32, f32);
Tk59 *func_00130340(Ob59 *, s32, f32);
void func_0015d848(Ob59 *o, f32 *v) {
    f32 d[4];
    f32 t[4];
    f32 c;
    s32 st;
    if (o->h30e == 0xFFFF) {
        func_0015d7b8(o, v);
        return;
    }
    st = 52;
    PlatVu0SubVector(d, o->m->xD0, o->pos);
    c = d[0] * o->m->xC0[2] - d[2] * o->m->xC0[0];
    if (c > 0.0f) {
    } else if (c < 0.0f) {
        st = 51;
    } else {
        st = 50;
    }
    PlatVu0CopyVector(o->m->xD0, o->pos);
    if (v[3] > 0.0f) {
        PlatVu0OuterProduct(t, v, o->m->xC0);
        PlatVu0OuterProduct(t, o->m->xC0, t);
        PlatVu0Normalize(v, t);
        PlatVu0ScaleVector(v, v, 1.5f);
    } else {
        PlatVu0CopyVector(v, (*(f32 (*)[0x4])&D_002C58A0));
        st = 50;
    }
    PlatVu0ScaleVector(d, o->m->xC0, -1.5f);
    PlatVu0AddVector(o->x20, v, d);
    switch (st) {
    case 50:
        if ((u32)(o->st - 51) < 2) {
            func_00130398(o, 50, 8.0f);
        } else {
            func_00130398(o, 0x40000032, 0.0f);
        }
        break;
    case 51:
    case 52:
        if (o->st != st && (o->st == 50 || o->st == 52 || o->st == 51)) {
            func_00130340(o, st, 12.0f)->f4 = 12.0f;
        } else {
            func_00130398(o, st, 0.0f);
        }
        break;
    }
}

/* func_0015dac0 (from hand/nostrict/text_00150000_h36.c). */
void func_00137688(void *, f32);
f32 func_0014cce0(void *, f32);
f32 func_00120c88(f32);
void func_0015dac0(CylObj *o) {
    f32 z;
    if (o->h30E != 0xFFFF) {
        func_0015d5e8(o);
        func_00137688(o, o->rot);
        return;
    }
    z = 0.0f;
    func_0014cce0(o, z);
    o->w0 &= ~0x400;
    o->rot = func_00120c88(o->rot + 3.1415928f);
    func_00130398(o, 6, z);
    func_00137688(o, o->rot);
    PlatVu0ScaleVector(o->x3C0, o->vel, 4.0f);
}

