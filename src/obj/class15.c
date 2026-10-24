/* Object class 0x15: the handlers func_0014cb38 registers in the class table
 * D_00350D88 (func_0014f830(0x15, ...)) and their helpers. Flag mode:
 * default (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0053.h"
#include "data/bss_0054.h"
#include "vm/script_vm.h"
#include "data/types/text_00140000_h8.h"
#include "m2c.h"
#include "platform/math.h"
#include "data/types/text_00140000_h34.h"
#include "data/types/text_00140000_h57_p.h"
#include "data/types/text_00140000_h57.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350D78.h"
#include "data/pieces/D_002C58D0.h"

/* func_0014c400 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[0x100]; union { f32 f; u64 x; struct { u64 lo:32; u64 b32:1; u64 r:31; } b; } x100; } W8A148;
typedef struct { u8 pad[0x148]; W8A148 *x148; u8 pad14c[0x1cc - 0x14c]; u32 x1cc; u8 pad1d0[0x3c0 - 0x1d0]; u8 x3c0[0x14]; f32 x3d4; } W8Act;
void func_0014c400(W8Act *a) {
    a->x148->x100.f = 46.0f;
    a->x1cc &= ~1;
}

/* func_0014c428 (from hand/text_00140000_h8.c). */
void func_0014c428(W8Act *a) {
    a->x148->x100.f = 24.0f;
    a->x1cc |= 1;
}

/* func_0014c448 (from hand/text_00140000_h8.c). */
void func_0014cce0(W8Act *, f32);
void func_00130398(W8Act *, s32, f32);
void func_0014c448(W8Act *a) {
    PlatVu0ScaleVector(a->x3c0, a->x3c0, 0.7f);
    func_0014cce0(a, 8.0f);
    func_00130398(a, 6, 8.0f);
}

/* func_0014c4a8 (from hand/text_00140000_h8.c). */
void func_0014f658(W8Act *, s32);
s32 func_0014c4a8(W8Act *a) {
    if (a->x148->x100.f <= 0.0f && 50.0f < a->x3d4) {
        func_00130398(a, 113, 16.0f);
        PlatVu0ScaleVector(a->x3c0, a->x3c0, 0.5f);
        func_0014f658(a, 21);
        return 1;
    }
    return 0;
}

/* func_0014c530 (from hand/text_00140000_h8.c). */
void func_0014c530(W8Act *a) {
    if (func_0014c4a8(a)) a->x148->x100.b.b32 = 0;
}

/* func_0014c580 (from auto/text_00140000_13.c). */
#define func_0014c4a8 ((s32 (*)()) func_0014c4a8)
void func_0014c580(void *arg0) {
    void *temp_v0;

    if (func_0014c4a8(arg0) != 0) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x148);
        M2C_FIELD(temp_v0, s64 *, 0x100) = (s64) (M2C_FIELD(temp_v0, s64 *, 0x100) | ((s64) 0x8000 << 0x11));
    }
}
#undef func_0014c4a8

/* func_0014c5c8 (from hand/text_00140000_h34.c). */
extern f32 D_002BBDFC;
typedef struct { u8 pad[0x100]; f32 x100; u64 f:32; } W34Tm;
typedef struct { u8 pad[4]; s32 x4; } W34Pad;
typedef struct { u8 pad[0x30]; f32 pos[4]; u8 pad40[0x148 - 0x40]; W34Tm *x148; } W34Pl;
#define func_0014c448 ((void (*)()) func_0014c448)
void func_0014c5c8(W34Pl *o, W34Pad *b, f32 *v) {
    s32 m;
    if (v[0] == 0.0f && v[1] == 0.0f && v[2] == 0.0f) {
        PlatVu0CopyVector(v, o->pos);
        v[3] = 0.0f;
    }
    if (o->x148->x100 > 0.0f) {
        o->x148->x100 -= D_002BBDFC;
    } else {
        if (o->x148->f & 1) m = b->x4 & 0x10;
        else m = b->x4 & 4;
        if (!m) func_0014c448(o, b->x4);
    }
}
#undef func_0014c448

/* func_0014c6c0 (from hand/text_00140000_h57.c). */
typedef struct { u8 pad0[0x100]; u64 f100; } Sub57_c6c0;
typedef struct {
    u8 pad0[0x3c];
    f32 f3c;
    u8 pad40[0x148-0x40];
    Sub57_c6c0 *o148;
    u8 pad14c[0x150-0x14c];
    f32 f150;
    u8 pad154[0x170-0x154];
    f32 f170;
    u8 pad174[0x3c0-0x174];
    f32 v3c0[4];
} Obj57_c6c0;
f32 atan2f(f32, f32);
f32 func_00120c88(f32);
void func_00121fc4(f32 *, f32 *);
void func_00137688(Obj57_c6c0 *, f32);
void func_00144650(Obj57_c6c0 *, f32 *);
#define func_00130398 ((void (*)(void *, s32, f32)) func_00130398)
void func_0014c6c0(Obj57_c6c0 *o, f32 *v) {
    f32 t[4];
    f32 a;
    f32 lim;
    s32 id;

    if (v[3] > 0.0f) {
        a = func_00120c88(atan2f(v[0], v[2]) - o->f3c);
    } else {
        a = 0.0f;
    }
    if (o->f170 == 0.0f) {
        if (a > 0.523598730564117431640625f) {
            id = 115;
        } else if (a < -0.523598730564117431640625f) {
            id = 116;
        } else {
            PlatVu0CopyVector(t, o->v3c0);
            t[1] = 0.0f;
            func_00121fc4(t, t);
            if (t[3] > 8.0f) id = 114;
            else id = 113;
        }
        func_00130398(o, id, 16.0f);
    }
    if ((s32)(o->o148->f100 >> 32) & 1) {
        lim = D_002BBDFC * 0.0174532905221f;
    } else {
        lim = D_002BBDFC * 0.0349065810442f;
    }
    if (lim < a) a = lim;
    else if (a < -lim) a = -lim;
    a = func_00120c88(a + o->f3c);
    func_00137688(o, a);
    o->f150 = a;
    func_00144650(o, v);
}
#undef func_00130398

/* func_0014ca38 (from hand/text_00140000_h34.c). */
f32 func_00120bf8(f32 *);
typedef struct { s32 x0; u8 pad4[0xc]; f32 x10[4]; u8 pad20[0x50]; s32 x70; u8 pad74[0x148 - 0x74]; W34Tm *x148; u8 pad14c[0x490 - 0x14c]; f32 x490[4]; } W34Pl2;
extern u32 D_002C5958;
s32 func_0014db20(W34Pl2 *);
#define func_0014c448 ((void (*)()) func_0014c448)
s32 func_0014ca38(W34Pl2 *o, s32 a) {
    f32 v[4] __attribute__((aligned(16)));
    if ((D_002C5958 >> 5 & 1) && func_0014db20(o)) {
        o->x0 &= ~4;
        return 8;
    }
    if (!a) goto call;
    if (o->x148->x100 <= 0.0f) {
        PlatVu0SubVector(v, o->x10, o->x490);
        if (v[1] < 0.0f) {
        call:
            func_0014c448(o);
        } else if (func_00120bf8(v) / D_0054F444 < 0.7f) func_0014c448(o);
    }
    return o->x70;
}
#undef func_0014c448

/* func_0014cb38 (from auto/text_00140000_6.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, s32);
void func_0014c850();
void func_0014cb38(void) {
    func_0014f830(0x15, 5, &func_0014c400, &func_0014c428, &func_0014c6c0, &func_0014c850, &func_0014ca38, &func_0014c5c8, 0);
}

