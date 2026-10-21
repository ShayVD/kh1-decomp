/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0052.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_00133920();
M2C_UNK func_001c4788(s32);
extern M2C_UNK D_003042F0;
extern M2C_UNK D_00304BF0[];
extern M2C_UNK D_00525368;
extern M2C_UNK D_0052536C;
M2C_UNK D_00529800[0x240] ALIGNED(64);
extern M2C_UNK D_0052A100; /* src/data/bss_0052.c: u8 D_0052A100[0x10] */
extern M2C_UNK D_0052AE70; /* src/data/bss_0052.c: void *D_0052AE70[0xa] */
extern M2C_UNK func_00136c98;
extern f32 D_002BBDFC;
extern s32 D_00304BE8;
extern s32 D_0052A150;
extern void *D_0052AE5C;
f32 func_0013fe10();
f32 func_0026b9c0(f32, f32);
s32 func_0011ef38(M2C_UNK *);
s32 func_00123488(s32);
s32 func_00130040(s32, s32);
s32 func_00130340(s32, s32, f32);
s32 func_00132f60(s32, s32);
s32 func_00148908(s32);
s32 func_0014f5c8(s32);
s32 func_0014f658(s32, s32);
u32 func_00232cc0(M2C_UNK);
void func_001247e8(s32);
void func_001302d0(s32, s32, f32, f32);
void func_00131498(s32, s32);
void func_001315c0(s32, s32, s32, f32);
void func_00133978(s32, s32);
void func_00138900(s32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_0015c9f8(s32);
void func_00162058(s32);
void func_001623d0(s32, s32);
void func_001763f0(s32);

s32 func_00130270(s32 *arg0, s32 arg1) {
    s32 temp_a2;
    s32 var_a1;

    var_a1 = arg1;
    if (var_a1 & 0x01000000) {
        temp_a2 = *arg0 | 4;
        var_a1 &= 0xFEFFFFFF;
        *arg0 = temp_a2;
        if (temp_a2 & 0x80) {
            *arg0 = temp_a2 | 0x100000;
        }
    }
    if (var_a1 & 0x800000) {
        *arg0 |= 0x1000;
    }
    return var_a1;
}

void func_00130578(s32 arg0, s32 arg1, f32 fparg0) {
    func_001302d0(arg0, arg1, 0.0f, fparg0);
}

void func_00130648(Actor *arg0) {
    arg0->unk290 = 0;
    arg0->unk288 = 0;
    arg0->unk28C = (f32) arg0->unk280;
}

f32 func_00130dd0(Actor *arg0) {
    f32 var_f0;
    void *temp_a0;

    var_f0 = -1.0f;
    if (arg0->unk164 == 0xBF) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x98);
        var_f0 = M2C_FIELD(temp_a0, f32 *, 0x16C) / M2C_FIELD(temp_a0, f32 *, 0x280);
        if (arg0->unk000 & 0x800000) {
            var_f0 = func_0026b9c0(var_f0 + 0.5f, 1.0f);
        }
    }
    return var_f0;
}

void func_00131c08(Actor *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    M2C_FIELD(arg0, f32 *, 0x288) = fparg0;
    arg0->unk160_64 = (s64) (arg0->unk160_64 | 0x40);
    arg0->unk28C = fparg1;
    M2C_FIELD(arg0, f32 *, 0x290) = fparg2;
}

void func_001321a0(s32 arg0, s32 arg1) {
    s32 temp_v1;

    M2C_FIELD(arg0, s32 *, 0) = arg1;
    if (arg1 != 0) {
        func_001623d0(arg1 + M2C_FIELD(arg1, s32 *, 4), arg0 + 4);
        M2C_FIELD(arg0, s32 *, 8) = (s32) (arg1 + M2C_FIELD(arg1, s32 *, 8));
        temp_v1 = M2C_FIELD(arg1, s32 *, 0xC);
        if ((M2C_FIELD(arg1, s32 *, 0x10) - temp_v1) > 0) {
            M2C_FIELD(arg0, s32 *, 0xC) = (s32) (arg1 + temp_v1);
            return;
        }
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

void func_00132678(s32 arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if ((M2C_FIELD(arg0, s32 *, 8) - temp_v0) > 0) {
        func_00162058(arg0 + temp_v0);
    }
    if ((M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 8)) > 0) {
        func_00162058(arg0 + M2C_FIELD(arg0, s32 *, 8));
    }
    if ((M2C_FIELD(arg0, s32 *, 0x10) - M2C_FIELD(arg0, s32 *, 0xC)) > 0) {
        func_0015c9f8(arg0 + M2C_FIELD(arg0, s32 *, 0xC));
    }
    if ((M2C_FIELD(arg0, s32 *, 0x14) - M2C_FIELD(arg0, s32 *, 0x10)) <= 0) {
        return;
    }
    func_001763f0(arg0 + M2C_FIELD(arg0, s32 *, 0x10));
}

f32 func_00132f00(void *arg0) {
    return *(f32 *)((s8 *)&D_003042F0 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 4));
}

void *func_00132f20(s32 arg0) {
    void *temp_v1;

    temp_v1 = *(M2C_UNK *)((s8 *)&D_0052536C + (arg0 * 0x1C));
    return temp_v1 + M2C_FIELD(temp_v1, s32 *, 8);
}

s32 func_00132f88(s32 arg0) {
    s32 temp_v1;

    if (((u32) arg0 >= 7U) || (temp_v1 = *(M2C_UNK *)((s8 *)&D_00525368 + (arg0 * 0x1C)), (temp_v1 == 0))) {
        return 0;
    }
    return func_00132f60(arg0, temp_v1);
}

s32 func_00132fe0(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_00525368 + (arg0 * 0x1C));
}

void func_00133830(s32 arg0, s32 arg1) {
    func_001315c0(func_00123488(arg0), 0x8006, arg1, 0.0f);
}

void func_00133950(s32 arg0, s32 arg1) {
    func_00133920();
    func_001c4788(arg1 + 0x10);
}

void func_001339c0(s32 arg0) {
    func_00133978(arg0, 4);
    func_00133978(arg0, 0x15);
    func_00133978(arg0, 0x16);
}

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
    D_00304BE8 = func_00232cc0(0);
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
