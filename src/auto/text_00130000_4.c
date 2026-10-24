/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0052.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
#include "vm/script_vm.h"
extern M2C_UNK D_00304BF0[];
M2C_UNK D_00529800[0x240] ALIGNED(64);
extern M2C_UNK D_0052A100; /* src/data/bss_0052.c: u8 D_0052A100[0x10] */
extern M2C_UNK D_0052AE70; /* src/data/bss_0052.c: void *D_0052AE70[0xa] */
extern M2C_UNK func_00136c98;
extern f32 D_002BBDFC;
#include "data/pieces/D_00304BE8.h"
extern s32 D_0052A150;
extern void *D_0052AE5C;
f32 func_0013fe10();
f32 func_0026b9c0(f32, f32);
s32 func_0011ef38(M2C_UNK *);
s32 func_00130040(s32, s32);
s32 func_00130340(s32, s32, f32);
s32 func_00148908(s32);
s32 func_0014f5c8(s32);
s32 func_0014f658(s32, s32);
u32 func_00232cc0(M2C_UNK);
void func_001247e8(s32);
void func_00131498(s32, s32);
void func_00138900(s32, f32, f32, f32, f32, f32, f32, f32, f32);

void func_001372a0(void) {
    func_0011efa8(&D_0052A100, &D_00529800, 0x18, 0x60);
    if (func_0011ef38(&func_00136c98) == 0) {
        func_0011ef10(0x1FBD0, &func_00136c98);
    }
    D_0052A150 = 0;
}

void func_001373f8(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0xC) = fparg0;
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0) | 0x80) & 0xFFEFFFFF);
}

void func_00137990(Actor *arg0) {
    f32 temp_f0;
    f32 temp_f2;

    temp_f2 = arg0->unk064;
    if (temp_f2 != 0.0f) {
        temp_f0 = arg0->unk060 + (temp_f2 * D_002BBDFC);
        arg0->unk060 = temp_f0;
        if (temp_f0 > 1.0f) {
            arg0->unk060 = 1.0f;
            arg0->unk064 = 0.0f;
        } else if (temp_f0 < 0.0f) {
            arg0->unk060 = 0.0f;
            arg0->unk064 = 0.0f;
            if (arg0->unk000 & 8) {
                func_001247e8(arg0);
            }
        }
    }
}

void func_00137d40(void *arg0) {
    f32 temp_f0;
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0);
    if ((temp_a1 & 0x01000080) == 0x80) {
        if (temp_a1 & 0x100000) {
            temp_f0 = M2C_FIELD(arg0, f32 *, 0xC) - D_002BBDFC;
            M2C_FIELD(arg0, f32 *, 0xC) = temp_f0;
            if (temp_f0 <= 0.0f) {
                M2C_FIELD(arg0, s32 *, 0) = (s32) (temp_a1 & 0xFFEFFF7F);
            }
        } else if (!(temp_a1 & 4)) {
            M2C_FIELD(arg0, s32 *, 0) = (s32) (temp_a1 | 0x100000);
        }
    }
}

void func_00138808(Actor *arg0, f32 fparg0) {
    if (func_00130040(arg0, 0x42) != 0) {
        arg0->unk3E4 = fparg0;
        arg0->unk088 = (s32) (arg0->unk088 | 2);
    }
}

void func_00138948(Actor *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7) {
    func_00138900(arg0, fparg0, fparg1, fparg2, fparg3, fparg4, fparg5, fparg6, fparg7);
    arg0->unk088 = (s32) (arg0->unk088 | 2);
    arg0->unk400 = func_00148908(arg0);
}

void func_001394e8(Actor *arg0) {
    if (func_0014f5c8(arg0) != 0) {
        func_0014f658(arg0, 0x17);
    } else {
        func_0014f658(arg0, 0x16);
    }
    func_00130340(arg0, 0x01000068, 0.0f);
    arg0->unk404 = 75.0f;
    arg0->unk02C = 0.0f;
}

void func_0013aac0(s32 arg0) {
    s32 temp_v1;

    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) == 0) {
        temp_v1 = M2C_FIELD(D_0052AE5C, s32 *, 8);
        if ((M2C_FIELD(D_0052AE5C, s32 *, 0xC) - temp_v1) > 0) {
            func_00131498(arg0, (s32) (D_0052AE5C + temp_v1));
        }
    }
}

void func_0013bde8(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

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
#include "data/pieces/D_002BBDFC.h"
