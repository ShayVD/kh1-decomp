/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0052.h"
#include "vm/script_vm.h"
extern M2C_UNK D_00304BF0[];
M2C_UNK D_00529800[0x240] ALIGNED(64);
extern M2C_UNK D_0052AE70; /* src/data/bss_0052.c: void *D_0052AE70[0xa] */
#include "data/pieces/D_00304BE8.h"
f32 func_0013fe10();
f32 func_0026b9c0(f32, f32);
s32 func_0014f658(s32, s32);
u32 func_00232cc0(M2C_UNK);

void func_0013ce98(void) {
    D_00304BE8 = (void *)(func_00232cc0(0));
}

s32 func_0013dbb0(u32 arg0) {
    if (arg0 < 0xAU) {
        return *(M2C_UNK *)((s8 *)&D_00304BF0 + (arg0 * 4));
    }
    return 0;
}

s32 func_0013dbe0(void *arg0, s32 arg1) {
    return *(M2C_UNK *)((s8 *)&D_0052AE70 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 4)) + (arg1 * 0x14);
}

void func_0013f450(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFDFFFFF);
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) | 1);
}

void func_0013fc28(s32 arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x164);
    if ((temp_v1 != 0x23) && (temp_v1 != 0x2C)) {
        func_0014f658(arg0, 0);
    }
}

void func_0013fd60(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFDFFFFF);
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) | 1);
}

f32 func_0013fe80(f32 fparg0) {
    f32 temp_f0;
    f32 var_f20;

    temp_f0 = func_0026b9c0(fparg0, 66.666664124f);
    var_f20 = fparg0 - temp_f0;
    if (temp_f0 < -33.3333321f) {
        var_f20 -= 66.666664124f;
    } else if (temp_f0 > 33.3333321f) {
        var_f20 += 66.666664124f;
    }
    return var_f20;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_0048DDA0[];
extern u8 D_0048DDA8[];
extern u8 D_0048DDB8[];
extern u8 D_0048DDC0[];
extern u8 D_0048DDC8[];
extern u8 D_0048DDD0[];
extern u8 D_0048DDD8[];
extern u8 D_0048DDE0[];
extern u8 D_0048DDE8[];
extern u8 D_0048DDF0[];
M2C_UNK D_00304BF0[0xa] ALIGNED(16) = {
    (s32)D_0048DDF0, (s32)D_0048DDE8, (s32)D_0048DDE0, (s32)D_0048DDD8,
    (s32)D_0048DDD0, (s32)D_0048DDC8, (s32)D_0048DDC0, (s32)D_0048DDB8,
    (s32)D_0048DDA8, (s32)D_0048DDA0,
};
#include "data/data_0030.h"
#include "data/data_0048.h"
