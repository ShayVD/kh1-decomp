/* Party heal objects, without strict aliasing or gcse (docs/modules.md
 * "Session 52"): func_00156e88 (the object's effect state).  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"

/* func_00156e88 (from hand/nostrict_nogcse/text_00140000_s6_07.c). */
typedef struct {
    u8 pad0[8];
    f32 *x8;
    u8 padc[4];
    u8 *x10;
    u32 x14;
    u8 pad18[0x34 - 0x18];
    u8 *x34;
} Eff6e88;
typedef struct {
    u32 b0 : 1;
    u32 b1 : 1;
    u32 cnt : 2;
    u32 rest : 28;
    Eff6e88 *x4;
    Eff6e88 *x8;
} St6e88;
typedef struct { u8 pad[0x48]; s16 x48; } Sub6e88;
typedef struct {
    u32 w0;
    u8 pad4[0xc];
    f32 x10[4];
    u8 pad20[0x20];
    f32 x40[4];
    u8 pad50[0x18];
    s32 x68;
    u8 pad6c[0x130 - 0x6c];
    Sub6e88 *x130;
    u8 pad134[0x144 - 0x134];
    St6e88 *x144;
    u8 pad148[0x4a0 - 0x148];
    void *x4a0;
} A6e88;
void *func_00121e28(s32, void *);
void * func_00250054(void *, s32, s32);
void func_0013c2a0(s32, s32);
Eff6e88 *func_00147ed8(s32, s32, s32, f32 *);
void func_00156d88(void);
void func_00156e88(A6e88 *a) {
    St6e88 *s;
    Eff6e88 *e;
    u32 t;

    s = a->x144;
    if (s == 0) {
        a->x144 = func_00121e28(12, &a->x144);
        func_00250054(a->x144, 0, 4);
        a->x144->x4 = 0;

        a->x144->x8 = 0;
        a->x4a0 = func_00156d88;
        a->w0 |= 0x200;
        func_0013c2a0(a->x130->x48, 0);
        s = a->x144;
    }
    if (s->x4 == 0 || (s->x4->x14 & 3) != 1) {
        a->x144->x4 = func_00147ed8(a->x68, 0, 20000, a->x10);
        s = a->x144;
    }
    *s->x4->x34 = !s->b1;
    PlatVu0CopyVector(a->x144->x4->x8, a->x40);
    a->x144->b1 = a->w0 & 1;
    s = a->x144;
    e = s->x8;
    if (e == 0) {
        if (s->b0) {
            a->x144->x8 = func_00147ed8(a->x68, 1, 20000, a->x10);
            PlatVu0CopyVector(a->x144->x8->x8, a->x40);
            s = a->x144;
        }
    } else if ((t = e->x14 & 3) != 1) {
        s->x8 = 0;
        s = a->x144;
    } else if (!s->b0) {
        *e->x10 = t;
        s = a->x144;
    }
    s->b0 = 0;
    a->x144->cnt = (a->x144->cnt + 1) % 3;
}

