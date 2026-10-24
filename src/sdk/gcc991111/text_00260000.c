/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK Deci2Call(M2C_UNK, void *);
M2C_UNK RemoveIntcHandler(M2C_UNK, s32);
M2C_UNK func_00258c40(M2C_UNK);
M2C_UNK func_00258ca8(M2C_UNK);
M2C_UNK sceVu0OuterProduct(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK sceVu0Normalize(M2C_UNK *, M2C_UNK *);
M2C_UNK sceVu0InversMatrix(s32, M2C_UNK *);
M2C_UNK sceVu0TransMatrix(M2C_UNK *, M2C_UNK *, s32);
M2C_UNK func_00267620(M2C_UNK *);
M2C_UNK sceVu0RotMatrixZ(f32);
M2C_UNK sceVu0RotMatrixX(s32, s32, f32);
M2C_UNK sceVu0RotMatrixY(s32, s32, f32);
extern M2C_UNK D_00670040;
extern s32 D_0046C5D0;
s32 AddIntcHandler(M2C_UNK, s32, M2C_UNK);
s32 func_00266ba8(s32);
s32 sceVu0CopyVector(s32, s32);
void *func_002654e0();
void func_00266ab0(void *);
void func_00266b20(s32, s32, s32);

void func_00260028(s32 arg0) {
    s32 sp[4];
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    Deci2Call(-8, sp);
}

void func_00260050(s32 arg0) {
    s32 sp[4];
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    Deci2Call(-9, sp);
}

void func_00260078(s32 arg0) {
    s32 sp[4];
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    Deci2Call(0x10, sp);
}

s32 func_002608e0(s32 *arg0, s32 *arg1, u32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 temp_v1;
    u32 temp_a2;
    u32 var_a3;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a2 = arg2 >> 2;
    var_a3 = 0;
    if (temp_a2 != 0) {
        do {
            temp_v1 = *var_a1;
            var_a3 += 1;
            var_a1 += 1;
            *var_a0 = temp_v1;
            var_a0 += 1;
        } while (var_a3 < temp_a2);
    }
    return 0;
}

s32 func_00266a10(s32 arg0) {
    s32 temp_s2;
    void *temp_s0;

    temp_s0 = func_002654e0();
    temp_s2 = M2C_FIELD(temp_s0, s32 *, 8);
    if (arg0 == 0) {
        func_00258c40(2);
        RemoveIntcHandler(2, M2C_FIELD(temp_s0, s32 *, 0xC));
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
    } else {
        if (temp_s2 != 0) {
            func_00258c40(2);
            RemoveIntcHandler(2, M2C_FIELD(temp_s0, s32 *, 0xC));
        }
        M2C_FIELD(temp_s0, s32 *, 8) = arg0;
        M2C_FIELD(temp_s0, s32 *, 0xC) = AddIntcHandler(2, arg0, -1);
        func_00258ca8(2);
    }
    return temp_s2;
}

void func_00266bd0(s8 *arg0, s32 arg1) {
    s32 var_v0;
    s8 *var_a0;

    var_a0 = arg0;
    var_v0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            *var_a0 = 0;
            var_v0 -= 1;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}

void func_00266f38(void *arg0, s32 arg1) {
    s32 temp_s1;

    temp_s1 = func_00266ba8(arg1);
    func_00266ab0(arg0);
    if (M2C_FIELD(arg0, s32 *, 0x30) != 0xFFFFFFFF) {
        M2C_FIELD(arg0, s32 *, 0x30) = temp_s1;
    }
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0) & ~0xC) | 0x105);
}

void func_00266fa0(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;

    temp_s1 = func_00266ba8(arg1);
    func_00266ab0(arg0);
    if (M2C_FIELD(arg0, s32 *, 0x10) != 0xFFFFFFFF) {
        M2C_FIELD(arg0, s32 *, 0x10) = temp_s1;
    }
    M2C_FIELD(arg0, s32 *, 0x20) = arg2;
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0) & ~0xC) | 0x101);
}

void func_00267018(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;

    temp_s1 = func_00266ba8(arg1);
    func_00266ab0(arg0);
    if (M2C_FIELD(arg0, s32 *, 0x10) != 0xFFFFFFFF) {
        M2C_FIELD(arg0, s32 *, 0x10) = temp_s1;
    }
    M2C_FIELD(arg0, s32 *, 0x20) = arg2;
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0) & ~0xC) | 0x109);
}

void func_00267158(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;

    temp_s1 = func_00266ba8(arg1);
    func_00266ab0(arg0);
    if (M2C_FIELD(arg0, s32 *, 0x10) != 0xFFFFFFFF) {
        M2C_FIELD(arg0, s32 *, 0x10) = temp_s1;
    }
    M2C_FIELD(arg0, s32 *, 0x20) = arg2;
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((((M2C_FIELD(arg0, s32 *, 0) & ~0xC) | 8) & ~1) | 0x100);
}

s32 func_00267210(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 == 1) {
        return (u32) M2C_FIELD(arg0, u32 *, 0x10) < (u32) arg1;
    }
    func_00266b20(arg0, arg1, arg3);
    return 0;
}

void sceVu0RotMatrix(s32 arg0, s32 arg1, void *arg2) {
    sceVu0RotMatrixZ(M2C_FIELD(arg2, f32 *, 8));
    sceVu0RotMatrixY(arg0, arg0, M2C_FIELD(arg2, f32 *, 4));
    sceVu0RotMatrixX(arg0, arg0, M2C_FIELD(arg2, f32 *, 0));
}

void sceVu0CameraMatrix(s32 arg0, s32 arg1, M2C_UNK *arg2, M2C_UNK *arg3) {
    s32 sp[20];
    func_00267620(sp);
    sceVu0OuterProduct(&M2C_FIELD(sp, M2C_UNK *, 0x40), arg3, arg2);
    sceVu0Normalize(sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    sceVu0Normalize(&M2C_FIELD(sp, M2C_UNK *, 0x20), arg2);
    sceVu0OuterProduct(&M2C_FIELD(sp, M2C_UNK *, 0x10), &M2C_FIELD(sp, M2C_UNK *, 0x20), sp);
    sceVu0TransMatrix(sp, sp, arg1);
    sceVu0InversMatrix(arg0, sp);
}

void sceVu0LightColorMatrix(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    sceVu0CopyVector(arg0, arg1);
    sceVu0CopyVector(arg0 + 0x10, arg2);
    sceVu0CopyVector(arg0 + 0x20, arg3);
    sceVu0CopyVector(arg0 + 0x30, arg4);
}

s32 scePad2Init(void) {
    s8 *var_a0;

    D_0046C5D0 = 1;
    var_a0 = &D_00670040;
    do {
        M2C_FIELD(var_a0, s32 *, 0) = 0;
        M2C_FIELD(var_a0, s32 *, 4) = 0;
        M2C_FIELD(var_a0, s32 *, 8) = 0;
        var_a0 += 0x330;
    } while ((s32) var_a0 < (s32) ((s8 *)&D_00670040 + 0x3300));
    return 1;
}
