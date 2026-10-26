/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011d1e0(s32, s32, M2C_UNK *, M2C_UNK);
M2C_UNK func_0011d3c8(s32, s32, M2C_UNK);
M2C_UNK func_001bb658(s32);
M2C_UNK func_001bbf38(s32, s32);
M2C_UNK func_001bfac8();
M2C_UNK func_001bffa0(s32);
M2C_UNK func_001ed278(M2C_UNK, s32, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00f34fd0();
M2C_UNK func_00f350d0();
M2C_UNK func_00f35288();
M2C_UNK func_00f41710();
M2C_UNK func_00f419b8(s32);
M2C_UNK sceVu0MulMatrix(s32, void *, s32);
M2C_UNK sceVu0UnitMatrix(void *);
extern M2C_UNK D_00F61630;
extern M2C_UNK D_00F61648;
extern M2C_UNK D_00F61658;
extern M2C_UNK D_00F80710;
extern M2C_UNK D_00F80750;
extern f32 D_00F61640;
extern f32 D_00F82708;
extern f32 D_00F8270C;
extern f32 D_00F82710;
extern f32 D_00F82714;
extern s32 D_00F56DC0;
extern s32 D_00F56DE0;
extern s32 D_00F56DE4;
extern s32 D_00F616B8;
extern s32 D_00F61F58;
extern s32 D_00F6C9C0;
extern s32 D_00F6C9C4;
extern s32 D_00F809C0;
extern s32 D_00F826F0;
extern s32 D_00F826F4;
extern s32 D_00F826F8;
extern s32 D_00F82700;
extern s32 D_00F82704;
extern s32 D_00F82870;
extern s32 D_00F82874;
extern s32 D_00F82878;
extern s32 D_00F82884;
s32 func_00f33b10();
s32 func_00f33bf8(s32, s32);
s32 func_00f3e9f0(s32, s32);
s32 func_00f3f6c0(s32, s32, s32);
s32 func_00f41048(s32);
s32 func_00f413f0(s32);
s32 sceVu0CopyMatrix(s32, s32);
void func_00f3f938(s32, s32, s32);
void func_00f3ff10(s32, s32);
void func_00f40160(s32, s32);

u8 func_00f31030(s32 arg0) {
    return *(M2C_UNK *)((s32) D_00F56DC0 + (s32) ((arg0 & 7)));
}

void func_00f32728(u32 arg0, s32 arg1) {
    if (arg0 < 0x10U) {
        *(M2C_UNK *)((s8 *)(s8 *)&D_00F80750 + (arg0 * 4)) = arg1;
    }
}

void func_00f32750(u32 arg0, s32 arg1) {
    if (arg0 < 0x10U) {
        *(M2C_UNK *)((s8 *)(s8 *)&D_00F80710 + (arg0 * 4)) = arg1;
    }
}

void func_00f33380(s32 arg0) {
    D_00F61640 = (f32) arg0 * 0.0078125f;
}

void func_00f33968(void) {
    s32 var_s0;

    var_s0 = 0x3B;
    do {
        var_s0 -= 1;
        func_001bfac8();
    } while (var_s0 >= 0);
    func_001bffa0(D_00F809C0);
}

void func_00f33b88(s32 arg0) {
    func_001ed278(-1, *(M2C_UNK *)((s8 *)(s8 *)&D_00F61648 + (arg0 * 4)), arg0 + 1, 0x3FFF, 0x3FFF);
}

void func_00f33bc0(s32 arg0) {
    func_001ed278(-1, *(M2C_UNK *)((s8 *)(s8 *)&D_00F61658 + (arg0 * 4)), arg0 + 0xB, 0x3FFF, 0x3FFF);
}

void func_00f33c70(s32 arg0) {
    s32 temp_v0;

    if (D_00F616B8 != arg0) {
        temp_v0 = func_00f33b10();
        if (temp_v0 >= 0) {
            if (D_00F616B8 >= 0) {
                func_0011d3c8(func_00f33bf8(D_00F616B8, temp_v0), D_00F616B8 + 0x1000, 0x3C);
            }
            if (arg0 >= 0) {
                func_0011d1e0(func_00f33bf8(arg0, temp_v0), arg0 + 0x1000, &D_00F61630, 0);
            }
            D_00F616B8 = arg0;
        }
    }
}

void func_00f33d18(s32 arg0, s32 arg1) {
    s32 sp[16];
    s32 temp_s0;

    temp_s0 = arg1 * 0xC;
    func_001bb658(M2C_FIELD((temp_s0 + D_00F56DC0), u16 *, 0x114) - 1);
    sceVu0UnitMatrix(sp);
    func_001bbf38(arg0, D_00F56DC0 + temp_s0 + 0x110);
    sceVu0MulMatrix(arg0, sp, arg0);
}

void func_00f33da0(void) {
    func_00f41710();
}

void func_00f33db8(s32 arg0) {
    s32 var_s0;

    var_s0 = 0;
    do {
        if ((func_00f41048(var_s0) != 0) && (func_00f413f0(var_s0) == arg0)) {
            func_00f419b8(var_s0);
        }
        var_s0 += 1;
    } while (var_s0 < 0x100);
}

void func_00f353b8(void) {
    func_001bfac8();
    func_00f35288();
    func_00f34fd0();
    func_00f350d0();
}

void func_00f36c00(s32 arg0, s32 arg1) {
    if (arg1 == 0x8C) {
        M2C_FIELD(arg0, s32 *, 0) = 0;
        M2C_FIELD(arg0, s32 *, 4) = 0;
        M2C_FIELD(arg0, s32 *, 8) = 0;
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
        M2C_FIELD(arg0, s32 *, 0x10) = 0;
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
        M2C_FIELD(arg0, s32 *, 0x18) = 0;
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        M2C_FIELD(arg0, s32 *, 0x20) = 0;
        M2C_FIELD(arg0, s32 *, 0x24) = 0;
        M2C_FIELD(arg0, s32 *, 0x28) = 0;
        M2C_FIELD(arg0, s32 *, 0x2C) = 0;
        M2C_FIELD(arg0, f32 *, 0x30) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x34) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x38) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x3C) = 1.0f;
        return;
    }
    sceVu0CopyMatrix(arg0, D_00F56DC0 + 0x1090);
}

void func_00f36dd8(s32 *arg0, s32 arg1, s32 arg2) {
    s32 *var_s0;
    s32 var_s1;

    var_s0 = arg0;
    var_s1 = 2;
    do {
        var_s1 -= 1;
        *var_s0 = func_00f3f6c0(*var_s0, arg2, arg1);
        var_s0 += 1;
    } while (var_s1 >= 0);
}

void func_00f36e40(s32 arg0, s32 arg1, s32 arg2) {
    func_00f3ff10(arg0, M2C_FIELD(arg2, s32 *, 0));
    func_00f3ff10(arg0, M2C_FIELD(arg2, s32 *, 8));
    func_00f3ff10(arg1, M2C_FIELD(arg2, s32 *, 4));
}

void func_00f36e98(s32 arg0, s32 arg1, s32 arg2) {
    func_00f40160(arg0, M2C_FIELD(arg2, s32 *, 4));
    func_00f40160(arg1, M2C_FIELD(arg2, s32 *, 8));
    func_00f40160(arg1, M2C_FIELD(arg2, s32 *, 0));
}

void func_00f375e8(s32 arg0) {
    s32 var_a0;
    s32 var_v1;

    var_a0 = arg0;
    var_v1 = 2;
    do {
        var_v1 -= 1;
        *(M2C_UNK *)var_a0 = (s32) (*(M2C_UNK *)var_a0 + 0x10);
        var_a0 += 4;
    } while (var_v1 >= 0);
}

s32 func_00f39330(void) {
    return D_00F56DE0;
}

s32 func_00f39340(void) {
    return D_00F56DE4;
}

s32 func_00f39e90(void) {
    return ((D_00F826F4 * 8) - D_00F826F0) + 7;
}

s32 func_00f3ba40(s32 arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0xC) + arg0;
    M2C_FIELD(arg0, s32 *, 0xC) = temp_v0;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) + arg0);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) + arg0);
    return temp_v0;
}

f32 func_00f3ba68(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x20) * M2C_FIELD(arg0, f32 *, 0x24);
}

s32 func_00f3ba78(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x34);
}

s32 func_00f3ba80(s32 arg0) {
    return arg0 + 0x28;
}

f32 func_00f3ba88(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x20);
}

f32 func_00f3ba90(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x24);
}

s32 func_00f3ba98(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

s32 func_00f3baa0(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x14) + (arg0 << 6);
}

u8 func_00f3bb68(s32 arg0, void *arg1) {
    return M2C_FIELD((M2C_FIELD(arg1, s32 *, 0x14) + (arg0 << 6)), u8 *, 5);
}

s32 func_00f3bb80(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x1C) + (arg0 * 0x14);
}

s32 func_00f3bb98(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x18);
}

void func_00f3c168(s32 arg0) {
    D_00F61F58 = arg0;
}

s32 func_00f3c178(s8 *arg0) {
    s32 var_a1;

    var_a1 = 0;
    if (*arg0 != 0) {
        do {
            var_a1 += 1;
        } while (*(arg0 + var_a1) != 0);
    }
    return var_a1;
}

s32 func_00f3d4f0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

void func_00f3d518(void *arg0, s32 arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg2, s32 *, 0x10) + (arg1 * 0x14);
    M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(temp_v1, s16 *, 0);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(temp_v1, s16 *, 2);
}

s32 func_00f3db18(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

s32 func_00f3db20(s32 arg0, void *arg1) {
    return M2C_FIELD(((arg0 * 0xC) + M2C_FIELD(arg1, s32 *, 0xC)), s32 *, 4);
}

s32 func_00f3db40(s32 arg0, void *arg1) {
    return *(M2C_UNK *)((s32) ((arg0 * 8)) + (s32) (M2C_FIELD(arg1, s32 *, 0x14)));
}

s32 func_00f3db58(s32 arg0, s32 arg1, void *arg2) {
    return *(M2C_UNK *)((s32) ((arg1 * 8)) + (s32) (M2C_FIELD(((arg0 * 0xC) + M2C_FIELD(arg2, s32 *, 0xC)), s32 *, 8)));
}

void func_00f3dfe0(s32 arg0) {
    D_00F6C9C0 = arg0;
}

s32 func_00f3dff0(s32 arg0) {
    return arg0 + 0xD0;
}

void *func_00f3dff8(s32 arg0, void *arg1) {
    return arg1 + M2C_FIELD(((arg0 * 0x10) + (arg1 + M2C_FIELD(arg1, s32 *, 0xA4))), s32 *, 0xC);
}

f32 func_00f3e018(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0xC8);
}

s32 func_00f3e060(s32 arg0) {
    return arg0 + 0x10;
}

void func_00f3e0c8(s32 arg0) {
    D_00F6C9C4 = arg0;
}

void func_00f3e970(s32 arg0) {
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

void func_00f3e9b8(s32 arg0) {
    D_00F826F8 = arg0;
}

s32 func_00f3e9c8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 8);
}

s32 func_00f3ea50(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = arg0;
    if (arg2 > 0) {
        do {
            temp_a1 = var_s0;
            var_s0 += 1;
            var_s1 += func_00f3e9f0(arg1, temp_a1);
        } while (var_s0 < arg2);
    }
    return var_s1;
}

void func_00f3f148(s32 arg0, s32 arg1) {
    D_00F82700 = arg0;
    D_00F82704 = arg1;
}

void func_00f3f858(void *arg0) {
    D_00F82708 = 16384.0f;
    D_00F8270C = 1.0f;
    D_00F82714 = M2C_FIELD(arg0, f32 *, 0x28) + M2C_FIELD(arg0, f32 *, 0x38);
    D_00F82710 = 1.0f;
}

void func_00f3f8f0(s32 arg0, s32 arg1) {
    s32 sp[12];
    M2C_FIELD(sp, s64 *, 0x20) = (s64) arg0;
    M2C_FIELD(sp, s32 *, 0x10) = 0x8001;
    M2C_FIELD(sp, s32 *, 0x14) = 0x10000000;
    M2C_FIELD(sp, s32 *, 0x18) = 6;
    M2C_FIELD(sp, s32 *, 0x1C) = 0;
    func_00f3f938(2, (s32) sp, arg1);
}

s32 func_00f3f9d0(s32 arg0) {
    D_00F82870 = arg0;
    return arg0 + 0x10;
}

s32 func_00f3fa28(s32 arg0) {
    D_00F82874 = arg0;
    return arg0 + 0x10;
}

s32 func_00f3fa80(s32 arg0) {
    D_00F82878 = arg0;
    return arg0 + 0x10;
}

void func_00f3fdf8(void) {
    D_00F82884 = 0;
}
