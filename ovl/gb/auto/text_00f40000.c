/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0010c1b8(void (*)());
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00176328();
M2C_UNK func_001ed560(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_001efb18(s32, s32);
M2C_UNK func_001f9438(s32, M2C_UNK, s32, s32, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0024b138(s32, s32);
M2C_UNK func_00f41100(void *, M2C_UNK *);
s32 func_00f41410(s32, s32, void *, M2C_UNK *, s32, s32);
M2C_UNK func_00f41bb8(s32, s32, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
extern M2C_UNK D_00F707D0;
extern M2C_UNK D_00F71120;
extern M2C_UNK func_00f43c38;
extern s32 D_00F70268;
extern s32 D_00F70480;
extern s32 D_00F70484;
extern s32 D_00F705FC;
extern s32 D_00F70600;
extern s32 D_00F70604;
extern s32 D_00F70734;
extern s32 D_00F82888;
extern s32 D_00F8288C;
extern s32 D_00F82990;
extern s32 D_00F829C0;
extern s32 D_00F829C4;
extern s32 D_00F829C8;
extern s32 D_00F829CC;
extern s32 D_00F829D4;
extern s32 D_00F829D8;
extern s32 D_00F829E0;
extern s32 D_00F82AA0;
extern s32 D_00F82AA4;
extern s32 D_00F82AA8;
extern s32 D_00F82B48;
extern s8 D_00F70738;
extern s8 D_00F7073A;
extern u32 D_00F705F8;
s32 func_001ba3f0(M2C_UNK);
s32 func_001bb7c8(s32, s32);
s32 func_001efe68(s32);
s32 func_001f31a8(M2C_UNK *, M2C_UNK);
s32 func_001f3c20(void);
s32 func_001f4390(s32);
s32 func_00f39330();
s32 func_00f39340();
s32 func_00f40a10(s32, s32);
s32 func_00f40d28(s32);
s32 func_00f40fc8(s32);
s32 func_00f41048(s32);
u32 func_001f0118(s32, M2C_UNK);
void func_0011ca68(s32, s32);
void func_001bfac8();
void func_001f3840(s32);
void func_001f8f30(void);
void func_00203788(s32, s32, s32, s32, s32);
void func_00f3c7b0(M2C_UNK, s32);

void func_00f409d0(s8 *arg0) {
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

s32 func_00f40e18(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s2;

    var_s2 = -1;
    D_00F8288C = 0;
    D_00F82888 = arg1;
    func_001bfac8();
    temp_v0 = func_00f40d28(arg0);
    if (temp_v0 >= 0) {
        if (func_00f40a10(arg0, temp_v0) != 0) {
            var_s2 = (arg0 != 0) ? temp_v0 : 1;
        }
        if (var_s2 < 0) {
            func_00f3c7b0(2, arg0 + 0xA);
        } else {
            func_00f3c7b0(2, arg0 + 0xC);
        }
    }
    func_001bfac8();
    return var_s2;
}

void func_00f40ec8(void) {
    D_00F82990 = 1;
}

void func_00f40ed8(s32 arg0, s32 arg1) {
    s32 sp[8];
    func_0011ca68(arg0, (s32) sp);
    func_001bb7c8((s32) sp, arg1);
}

void func_00f40fa8(void) {
    func_001ed560(0, 0, 0xA0);
}

void func_00f410b8(void) {
    func_00176328();
    if (D_00F70268 != 0) {
        memset(D_00F70268, 0, 0x4800);
    }
}

s32 func_00f413f0(s32 arg0) {
    return M2C_FIELD(((arg0 * 0x48) + D_00F70268), s32 *, 0x40);
}

s32 func_00f41678(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp[8];
    func_00f41100(sp, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    return func_00f41410(arg0, arg1, sp, &M2C_FIELD(sp, M2C_UNK *, 0x10), arg3, arg4);
}

void func_00f416f0(s32 arg0, s32 arg1) {
    M2C_FIELD(((arg0 * 0x48) + D_00F70268), s32 *, 0x3C) = arg1;
}

void func_00f41710(s32 arg0, s32 arg1) {
    M2C_FIELD(((arg0 * 0x48) + D_00F70268), s32 *, 0x40) = arg1;
}

s32 func_00f41730(s32 arg0) {
    s32 var_v0;

    var_v0 = func_00f40fc8(arg0);
    if (var_v0 == 0) {
        return var_v0;
    }
    var_v0 = M2C_FIELD(((arg0 * 0x48) + D_00F70268), s32 *, 0x3C);
    return var_v0;
}

void func_00f41778(s32 arg0) {
    if (arg0 >= 0) {
        M2C_FIELD(((arg0 * 0x48) + D_00F70268), s8 *, 0x46) = 1;
    }
}

void func_00f417a8(s32 arg0) {
    if (arg0 >= 0) {
        M2C_FIELD(((arg0 * 0x48) + D_00F70268), s8 *, 0x46) = 0;
    }
}

void func_00f417d0(s32 arg0, void *arg1, void *arg2) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0;

    if ((arg0 >= 0) && (func_00f41048(arg0) != 0)) {
        temp_a0 = D_00F70268 + (arg0 * 0x48);
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

s32 func_00f41a20(s32 arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (arg0 < 0) {
        return var_v0;
    }
    var_v0 = D_00F70268 + (arg0 * 0x48);
    return var_v0;
}

s32 func_00f41a48(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

void func_00f41c98(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s0_2;
    u32 temp_s0;
    u32 temp_v0;

    temp_s0 = (func_001efe68(arg1) * 0x1E) - 0xF;
    temp_s0_2 = temp_s0 + (temp_s0 >> 0x1F);
    func_00f41bb8(arg0, arg2, arg4);
    temp_v0 = func_001f0118(arg1, 0xF);
    func_001f9438(arg0, 0, 0x100 - ((s32) ((temp_v0 >> 0x1F) + temp_v0) >> 1), 0xBF - (temp_s0_2 >> 1), arg1, 0xF, 0x80FFFFFF);
}

void func_00f42898(void) {
    func_0024b138(D_00F82AA8, D_00F82AA4);
    func_0010c1b8(func_00f42898);
    D_00F82AA0 = 1;
}

void func_00f42ea0(void) {
    s32 var_a0;
    s32 var_v1;
    s8 *temp_v0;

    var_a0 = 0;
    var_v1 = 0x1FF;
    do {
        var_v1 -= 1;
        temp_v0 = var_a0 + D_00F829C0;
        var_a0 += 0x44;
        *temp_v0 = 0;
    } while (var_v1 >= 0);
}

s8 func_00f431b8(void) {
    return D_00F70738;
}

s32 func_00f432e8(void) {
    D_00F829C4 = 0;
    D_00F7073A = 3;
    D_00F70734 = -1;
    return func_001f3c20();
}

M2C_UNK *func_00f43320(void) {
    return &D_00F707D0;
}

void func_00f43350(void) {
    s32 temp_s0;

    temp_s0 = func_00f39330();
    func_001efb18(temp_s0, func_00f39340());
}

void func_00f43ca0(void) {
    D_00F829C4 = -1;
    func_0011ef10(0x2BFE9, &func_00f43c38);
    D_00F829CC = func_001f31a8(&D_00F71120, 1);
}

void func_00f43d68(s8 *arg0) {
    *arg0 = 0;
}

void func_00f444b8(void *arg0, f32 fparg0, f32 fparg1) {
    M2C_FIELD(arg0, f32 *, 0x30) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) ((fparg0 - M2C_FIELD(arg0, f32 *, 0x2C)) / fparg1);
}

s32 func_00f45e80(void) {
    return (func_001ba3f0(0x30) == 0) ? 0 : 3;
}

void func_00f49678(s32 arg0) {
    if (M2C_FIELD(arg0, s16 *, 0xD8) >= 2) {
        func_00203788(arg0, D_00F70480, 6, D_00F70480 + D_00F70484, D_00F705F8 | (D_00F70604 << 0x18) | ((D_00F70600 << 0x10) | (D_00F705FC << 8)));
    }
    func_001f8f30();
    if ((func_001f4390(arg0) != 0) && (D_00F829C8 != 0)) {
        func_001f3840(arg0);
    }
}

s32 func_00f4aa60(void) {
    return D_00F82B48;
}

void func_00f4d8c0(s32 arg0, s32 arg1, s32 arg2) {
    D_00F829D4 = arg0;
    D_00F829D8 = arg1;
    D_00F829E0 = arg2;
}
