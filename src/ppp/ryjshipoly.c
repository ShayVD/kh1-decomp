/* The pppRyjDrawShipoly and pppRyjDrawShipolyBone classes' default-flag
 * functions (docs/modules.md "Session 50"): func_00199908 places a new
 * ribbon point (the key's offset through the current matrix),
 * func_001999f0 / func_0019aa60 give a texture page's UV bounds, and the
 * Con / Des clear and free the point buffer.  ryjshipoly.nostrict.c has
 * the rest.  Read from the code, not proved by a boot. */
/* func_00199908 (from auto/text_00190000_10.c). */
#include "m2c.h"
extern M2C_UNK D_00615E70;
extern s32 D_00615E68;
void func_002672f8(void *, M2C_UNK *, void *);
void func_00199908(void *arg0, void *arg1, void *arg2) {
    s32 sp[4];    f32 temp_f20;

    temp_f20 = M2C_FIELD(arg0, f32 *, 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    M2C_FIELD(sp, s32 *, 0x0) = 0;
    M2C_FIELD(sp, s32 *, 0x8) = 0;
    M2C_FIELD(sp, f32 *, 0x4) = temp_f20 * 0.5f;
    func_002672f8(arg1, D_00615E68 + 0x10, sp);
    M2C_FIELD(sp, f32 *, 0x4) = -temp_f20 * 0.5f;
    func_002672f8(arg2, D_00615E68 + 0x10, sp);
    if (M2C_FIELD(arg0, u8 *, 0x15) != 0) {
        func_002672f8(arg1, &D_00615E70, arg1);
        func_002672f8(arg2, &D_00615E70, arg2);
    }
}

/* func_001999f0 (from hand/text_00180000_h40.c). */
#include "common.h"
#include "ppp.h"
#include "data/types/shared.h"
#include "data/types/text_00180000_h40.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701D0.h"
typedef struct {
    u8 pad[0x16];
    u8 h, w, y;  /* +0x16 */
} PppTexMode;
void func_001999f0(PppTexMode *p, s32 *y0, s32 *y1, s32 *x0, s32 *x1) {
    s32 y = 0, w = 4096, h = 4096;

    switch (p->h) {
    case 1:
        h = 2048;
        break;
    case 2:
        h = 1024;
        break;
    }
    switch (p->w) {
    case 1:
        w = 2048;
        break;
    case 2:
        w = 1024;
        break;
    }
    switch (p->y) {
    case 1:
        y = 1024;
        h += 1024;
        break;
    case 2:
        y = 2048;
        h += 2048;
        break;
    case 3:
        y = 3072;
        h += 3072;
        break;
    }
    *y0 = y + 16;
    *y1 = h - 16;
    *x0 = 16;
    *x1 = w - 16;
}

/* pppRyjDrawShipolyCon (from auto/text_00190000_2.c). */
#include "data/pieces/D_003701E0.h"
void pppRyjDrawShipolyCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s8 *, 5) = 1;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s8 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}

/* pppRyjDrawShipolyDes (from auto/text_00190000.c). */
M2C_UNK func_00183b20(s32, s32);
extern s32 D_00615E64;
void pppRyjDrawShipolyDes(s32 arg0, PppEntry *arg1) {
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[2] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 8);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
    }
}

/* func_0019aa60 (from hand/text_00180000_h40.c). */
typedef struct {
    u8 pad[0x21];
    u8 h, w, y;  /* +0x21 */
} PppTexMode2;
void func_0019aa60(PppTexMode2 *p, s32 *y0, s32 *y1, s32 *x0, s32 *x1) {
    s32 y = 0, w = 4096, h = 4096;

    switch (p->h) {
    case 1:
        h = 2048;
        break;
    case 2:
        h = 1024;
        break;
    }
    switch (p->w) {
    case 1:
        w = 2048;
        break;
    case 2:
        w = 1024;
        break;
    }
    switch (p->y) {
    case 1:
        y = 1024;
        h += 1024;
        break;
    case 2:
        y = 2048;
        h += 2048;
        break;
    case 3:
        y = 3072;
        h += 3072;
        break;
    }
    *y0 = y + 16;
    *y1 = h - 16;
    *x0 = 16;
    *x1 = w - 16;
}

/* pppRyjDrawShipolyBoneFrame (from auto/text_00190000.c). */
void pppRyjDrawShipolyBoneFrame(void) {

}

/* pppRyjDrawShipolyBoneCon (from auto/text_00190000_4.c). */
extern void *D_00615E60;
void pppRyjDrawShipolyBoneCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s8 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s8 *, 5) = 1;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(D_00615E60, s8 *, 0xB3) = 1;
}

/* pppRyjDrawShipolyBoneDes (from auto/text_00190000.c). */
void pppRyjDrawShipolyBoneDes(s32 arg0, PppEntry *arg1) {
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[1] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 8);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
    }
}

#include "data/bss_0061_mixed.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_003727B0.h"
#include "data/data_0037.h"
