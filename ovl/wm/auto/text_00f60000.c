/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0010c1b8(void (*)());
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00176328();
M2C_UNK func_001ed560(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_001f9438(s32, M2C_UNK, s32, s32, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0024b138(s32, s32);
M2C_UNK func_00f681f8(void *, M2C_UNK *);
M2C_UNK func_00f68508(s32, s32, void *, M2C_UNK *, s32, s32);
M2C_UNK func_00f68cb0(s32, s32, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
extern M2C_UNK D_00FB4F50;
extern M2C_UNK D_00FB58A0;
extern M2C_UNK func_00f6ad30;
extern f32 D_0108EEC8;
extern f32 D_0108EECC;
extern f32 D_0108EED0;
extern f32 D_0108EED4;
extern s32 D_00F9B560;
extern s32 D_00F9B564;
extern s32 D_00FA66D8;
extern s32 D_00FB1140;
extern s32 D_00FB1144;
extern s32 D_00FB49E8;
extern s32 D_00FB4EB4;
extern s32 D_0108EEB0;
extern s32 D_0108EEB4;
extern s32 D_0108EEB8;
extern s32 D_0108EEC0;
extern s32 D_0108EEC4;
extern s32 D_0108F030;
extern s32 D_0108F034;
extern s32 D_0108F038;
extern s32 D_0108F044;
extern s32 D_0108F048;
extern s32 D_0108F04C;
extern s32 D_0108F150;
extern s32 D_0108F180;
extern s32 D_0108F184;
extern s32 D_0108F18C;
extern s32 D_0108F260;
extern s32 D_0108F264;
extern s32 D_0108F268;
extern s8 D_00FB4EB8;
extern s8 D_00FB4EBA;
s32 func_001ba3f0(M2C_UNK);
s32 func_001bb7c8(s32, s32);
s32 func_001efe68(s32);
s32 func_001f31a8(M2C_UNK *, M2C_UNK);
s32 func_001f3c20(void);
s32 func_00f65ae8(s32, s32);
s32 func_00f67b08(s32, s32);
s32 func_00f67e20(s32);
s32 func_00f680c0();
s32 func_00f68140();
u32 func_001f0118(s32, M2C_UNK);
void func_0011ca68(s32, s32);
void func_001bfac8();
void func_00f638a8(M2C_UNK, s32);
void func_00f66a30(s32, s32, s32);

s32 func_00f60428(void) {
    return D_00F9B560;
}

s32 func_00f60438(void) {
    return D_00F9B564;
}

s32 func_00f60f88(void) {
    return ((D_0108EEB4 * 8) - D_0108EEB0) + 7;
}

void func_00f62b38(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) + arg0);
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) + arg0);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) + arg0);
}

f32 func_00f62b60(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x20) * M2C_FIELD(arg0, f32 *, 0x24);
}

s32 func_00f62b70(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x34);
}

s32 func_00f62b78(s32 arg0) {
    return arg0 + 0x28;
}

f32 func_00f62b80(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x20);
}

f32 func_00f62b88(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x24);
}

s32 func_00f62b90(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

s32 func_00f62b98(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x14) + (arg0 << 6);
}

u8 func_00f62c60(s32 arg0, void *arg1) {
    return M2C_FIELD((M2C_FIELD(arg1, s32 *, 0x14) + (arg0 << 6)), u8 *, 5);
}

s32 func_00f62c78(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x1C) + (arg0 * 0x14);
}

s32 func_00f62c90(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x18);
}

void func_00f63260(s32 arg0) {
    D_00FA66D8 = arg0;
}

s32 func_00f63270(s8 *arg0) {
    s32 var_a1;

    var_a1 = 0;
    if (*arg0 != 0) {
        do {
            var_a1 += 1;
        } while (*(arg0 + var_a1) != 0);
    }
    return var_a1;
}

s32 func_00f645e8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

void func_00f64610(void *arg0, s32 arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg2, s32 *, 0x10) + (arg1 * 0x14);
    M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(temp_v1, s16 *, 0);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(temp_v1, s16 *, 2);
}

s32 func_00f64c10(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

s32 func_00f64c18(s32 arg0, void *arg1) {
    return M2C_FIELD(((arg0 * 0xC) + M2C_FIELD(arg1, s32 *, 0xC)), s32 *, 4);
}

s32 func_00f64c38(s32 arg0, void *arg1) {
    return *(M2C_UNK *)((s32) ((arg0 * 8)) + (s32) (M2C_FIELD(arg1, s32 *, 0x14)));
}

s32 func_00f64c50(s32 arg0, s32 arg1, void *arg2) {
    return *(M2C_UNK *)((s32) ((arg1 * 8)) + (s32) (M2C_FIELD(((arg0 * 0xC) + M2C_FIELD(arg2, s32 *, 0xC)), s32 *, 8)));
}

void func_00f650d8(s32 arg0) {
    D_00FB1140 = arg0;
}

s32 func_00f650e8(s32 arg0) {
    return arg0 + 0xD0;
}

void *func_00f650f0(s32 arg0, void *arg1) {
    return arg1 + M2C_FIELD(((arg0 * 0x10) + (arg1 + M2C_FIELD(arg1, s32 *, 0xA4))), s32 *, 0xC);
}

f32 func_00f65110(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0xC8);
}

s32 func_00f65158(s32 arg0) {
    return arg0 + 0x10;
}

void func_00f651c0(s32 arg0) {
    D_00FB1144 = arg0;
}

void func_00f65a68(s32 arg0) {
    u32 var_a2;
    void *temp_v0;
    void *var_a1;

    var_a2 = 0;
    temp_v0 = M2C_FIELD(arg0, void **, 0xC) + arg0;
    M2C_FIELD(arg0, void **, 0xC) = temp_v0;
    var_a1 = temp_v0;
    if (M2C_FIELD(arg0, u32 *, 8) != 0) {
        do {
            var_a2 += 1;
            M2C_FIELD(var_a1, s32 *, 0x18) = (s32) (M2C_FIELD(var_a1, s32 *, 0x18) + arg0);
            var_a1 += 0x1C;
        } while (var_a2 < (u32) M2C_FIELD(arg0, u32 *, 8));
    }
}

void func_00f65ab0(s32 arg0) {
    D_0108EEB8 = arg0;
}

s32 func_00f65ac0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 8);
}

s32 func_00f65b48(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = arg0;
    if (arg2 > 0) {
        do {
            temp_a1 = var_s0;
            var_s0 += 1;
            var_s1 += func_00f65ae8(arg1, temp_a1);
        } while (var_s0 < arg2);
    }
    return var_s1;
}

void func_00f66240(s32 arg0, s32 arg1) {
    D_0108EEC0 = arg0;
    D_0108EEC4 = arg1;
}

void func_00f66950(void *arg0) {
    D_0108EEC8 = 16384.0f;
    D_0108EECC = 1.0f;
    D_0108EED4 = M2C_FIELD(arg0, f32 *, 0x28) + M2C_FIELD(arg0, f32 *, 0x38);
    D_0108EED0 = 1.0f;
}

void func_00f669e8(s32 arg0, s32 arg1) {
    s32 sp[12];
    M2C_FIELD(sp, s64 *, 0x20) = (s64) arg0;
    M2C_FIELD(sp, s32 *, 0x10) = 0x8001;
    M2C_FIELD(sp, s32 *, 0x14) = 0x10000000;
    M2C_FIELD(sp, s32 *, 0x18) = 6;
    M2C_FIELD(sp, s32 *, 0x1C) = 0;
    func_00f66a30(2, (s32) sp, arg1);
}

s32 func_00f66ac8(s32 arg0) {
    D_0108F030 = arg0;
    return arg0 + 0x10;
}

s32 func_00f66b20(s32 arg0) {
    D_0108F034 = arg0;
    return arg0 + 0x10;
}

s32 func_00f66b78(s32 arg0) {
    D_0108F038 = arg0;
    return arg0 + 0x10;
}

void func_00f66ef0(void) {
    D_0108F044 = 0;
}

void func_00f67ac8(s8 *arg0) {
    s8 *var_a0;
    s8 *var_v1;

    var_a0 = arg0;
    var_v1 = NULL;
    if (*var_a0 != 0) {
        do {
            var_v1 = var_a0;
            var_a0 = var_v1 + 2;
        } while (M2C_FIELD(var_v1, s8 *, 2) != 0);
    }
    if (var_v1 != NULL) {
        *var_v1 = 0;
    }
}

s32 func_00f67f10(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s2;

    var_s2 = -1;
    D_0108F04C = 0;
    D_0108F048 = arg1;
    func_001bfac8();
    temp_v0 = func_00f67e20(arg0);
    if (temp_v0 >= 0) {
        if (func_00f67b08(arg0, temp_v0) != 0) {
            var_s2 = (arg0 != 0) ? temp_v0 : 1;
        }
        if (var_s2 < 0) {
            func_00f638a8(2, arg0 + 0xA);
        } else {
            func_00f638a8(2, arg0 + 0xC);
        }
    }
    func_001bfac8();
    return var_s2;
}

void func_00f67fc0(void) {
    D_0108F150 = 1;
}

void func_00f67fd0(s32 arg0, s32 arg1) {
    s32 sp[8];
    func_0011ca68(arg0, (s32) sp);
    func_001bb7c8((s32) sp, arg1);
}

void func_00f680a0(void) {
    func_001ed560(0, 0, 0xA0);
}

void func_00f681b0(void) {
    func_00176328();
    if (D_00FB49E8 != 0) {
        memset(D_00FB49E8, 0, 0x4800);
    }
}

s32 func_00f684e8(s32 arg0) {
    return M2C_FIELD(((arg0 * 0x48) + D_00FB49E8), s32 *, 0x40);
}

void func_00f68770(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp[8];
    func_00f681f8(sp, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    func_00f68508(arg0, arg1, sp, &M2C_FIELD(sp, M2C_UNK *, 0x10), arg3, arg4);
}

void func_00f687e8(s32 arg0, s32 arg1) {
    M2C_FIELD(((arg0 * 0x48) + D_00FB49E8), s32 *, 0x3C) = arg1;
}

void func_00f68808(s32 arg0, s32 arg1) {
    M2C_FIELD(((arg0 * 0x48) + D_00FB49E8), s32 *, 0x40) = arg1;
}

s32 func_00f68828(s32 arg0) {
    s32 var_v0;

    var_v0 = func_00f680c0();
    if (var_v0 == 0) {
        return var_v0;
    }
    var_v0 = M2C_FIELD(((arg0 * 0x48) + D_00FB49E8), s32 *, 0x3C);
    return var_v0;
}

void func_00f68870(s32 arg0) {
    if (arg0 >= 0) {
        M2C_FIELD(((arg0 * 0x48) + D_00FB49E8), s8 *, 0x46) = 1;
    }
}

void func_00f688a0(s32 arg0) {
    if (arg0 >= 0) {
        M2C_FIELD(((arg0 * 0x48) + D_00FB49E8), s8 *, 0x46) = 0;
    }
}

void func_00f688c8(s32 arg0, void *arg1, void *arg2) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0;

    if ((arg0 >= 0) && (func_00f68140() != 0)) {
        temp_a0 = D_00FB49E8 + (arg0 * 0x48);
        if (arg1 != NULL) {
            temp_v0 = M2C_FIELD(temp_a0, void **, 0);
            M2C_FIELD(temp_v0, f32 *, 0) = (f32) M2C_FIELD(arg1, f32 *, 0);
            M2C_FIELD(temp_v0, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 4);
            M2C_FIELD(temp_v0, f32 *, 8) = (f32) M2C_FIELD(arg1, f32 *, 8);
            M2C_FIELD(temp_v0, f32 *, 0xC) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
        }
        if (arg2 != NULL) {
            temp_a0_2 = M2C_FIELD(temp_a0, void **, 4);
            M2C_FIELD(temp_a0_2, s32 *, 0) = (s32) M2C_FIELD(arg2, s32 *, 0);
            M2C_FIELD(temp_a0_2, s32 *, 4) = (s32) M2C_FIELD(arg2, s32 *, 4);
            M2C_FIELD(temp_a0_2, s32 *, 8) = (s32) M2C_FIELD(arg2, s32 *, 8);
            M2C_FIELD(temp_a0_2, s32 *, 0xC) = (s32) M2C_FIELD(arg2, s32 *, 0xC);
        }
    }
}

s32 func_00f68b18(s32 arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (arg0 < 0) {
        return var_v0;
    }
    var_v0 = D_00FB49E8 + (arg0 * 0x48);
    return var_v0;
}

s32 func_00f68b40(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

void func_00f68d90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s0_2;
    u32 temp_s0;
    u32 temp_v0;

    temp_s0 = (func_001efe68(arg1) * 0x1E) - 0xF;
    temp_s0_2 = temp_s0 + (temp_s0 >> 0x1F);
    func_00f68cb0(arg0, arg2, arg4);
    temp_v0 = func_001f0118(arg1, 0xF);
    func_001f9438(arg0, 0, 0x100 - ((s32) ((temp_v0 >> 0x1F) + temp_v0) >> 1), 0xBF - (temp_s0_2 >> 1), arg1, 0xF, 0x80FFFFFF);
}

void func_00f69990(void) {
    func_0024b138(D_0108F268, D_0108F264);
    func_0010c1b8(func_00f69990);
    D_0108F260 = 1;
}

void func_00f69f98(void) {
    s32 var_a0;
    s32 var_v1;
    s8 *temp_v0;

    var_a0 = 0;
    var_v1 = 0x1FF;
    do {
        var_v1 -= 1;
        temp_v0 = var_a0 + D_0108F180;
        var_a0 += 0x44;
        *temp_v0 = 0;
    } while (var_v1 >= 0);
}

s8 func_00f6a2b0(void) {
    return D_00FB4EB8;
}

s32 func_00f6a3e0(void) {
    D_0108F184 = 0;
    D_00FB4EBA = 3;
    D_00FB4EB4 = -1;
    return func_001f3c20();
}

M2C_UNK *func_00f6a418(void) {
    return &D_00FB4F50;
}

void func_00f6ad98(void) {
    D_0108F184 = -1;
    func_0011ef10(0x2BFE9, &func_00f6ad30);
    D_0108F18C = func_001f31a8(&D_00FB58A0, 1);
}

void func_00f6ae60(s8 *arg0) {
    *arg0 = 0;
}

void func_00f6b5b0(void *arg0, f32 fparg0, f32 fparg1) {
    M2C_FIELD(arg0, f32 *, 0x30) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) ((fparg0 - M2C_FIELD(arg0, f32 *, 0x2C)) / fparg1);
}

s32 func_00f6cf78(void) {
    return (func_001ba3f0(0x30) == 0) ? 0 : 3;
}
