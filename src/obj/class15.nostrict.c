/* Object class 0x15: the handlers func_0014cb38 registers in the class table
 * D_00350D88 (func_0014f830(0x15, ...)) and their helpers. Flag mode:
 * nostrict (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_0054.h"
#include "data/types/nostrict_text_00140000_h57.h"
#include "data/types/nostrict_text_00140000_h57_p.h"

/* func_0014c850 (from hand/nostrict/text_00140000_h57.c). */
typedef struct { u8 pad0[0x100]; u64 f100; } Sub57_c850;
typedef struct {
    u8 pad0[0x30];
    f32 v30[3];
    f32 f3c;
    u8 pad40[0x148-0x40];
    Sub57_c850 *o148;
    u8 pad14c[0x150-0x14c];
    f32 f150;
    u8 pad154[0x170-0x154];
    f32 f170;
    u8 pad174[0x3c0-0x174];
    f32 v3c0[4];
    u8 pad3d0[4];
    f32 f3d4;
} Obj57_c850;
extern f32 D_002BBDFC;
extern f32 D_002C5970;
void func_002675a8(f32 *, f32 *);
f32 func_00120c18(f32 *);
f32 func_00120bf8(f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_0014c850(Obj57_c850 *o, f32 *v) {
    f32 d;
    f32 lim;
    f32 k;
    f32 t;

    if ((s32)(o->o148->f100 >> 32) & 1) {
        lim = 16.0f;
        k = 2.0f;
        if (o->f3d4 < 70.0f) {
            t = o->f3d4 / 70.0f;
            k = (t * t * 0.800000026822f + 0.199999991804f) * 2.0f;
        }
    } else {
        lim = 8.0f;
        k = 1.19999995828f;
    }
    d = func_00120c18(o->v3c0);
    if (d < lim) {
        d += D_002BBDFC * 0.399999983609f;
        if (lim < d) d = lim;
    }
    func_002675a8(v, o->v30);
    func_00267560(v, v, d * D_002BBDFC);
    if (k * D_002BBDFC < o->v3c0[1]) {
        v[1] = k;
    } else {
        if (o->v3c0[1] < 0.0f) {
            o->v3c0[1] *= 0.799999967217f;
        }
        v[1] = o->v3c0[1] + D_002BBDFC * 0.484693862498f;
    }
    func_00267560(o->v3c0, v, D_002C5970);
    o->v3c0[1] = v[1];
    D_0054F444 = func_00120bf8(v);
}

