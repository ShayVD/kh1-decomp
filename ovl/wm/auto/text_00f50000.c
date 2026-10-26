/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011d1e0(s32, s32, M2C_UNK *, M2C_UNK);
M2C_UNK func_0011d3c8(s32, s32, M2C_UNK);
M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_001bb658(s32);
M2C_UNK func_001bbf38(s32, void *);
M2C_UNK func_001bfac8();
M2C_UNK func_001bffa0(s32);
M2C_UNK func_001ed278(M2C_UNK, s32, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00f49430(M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00f50050();
M2C_UNK func_00f559d0();
M2C_UNK func_00f5c0c8();
M2C_UNK func_00f5c1c8();
M2C_UNK func_00f5c380();
M2C_UNK func_00f68808();
M2C_UNK func_00f68ab0(s32);
M2C_UNK func_00f78000(s32);
extern M2C_UNK D_00FA5DB0;
extern M2C_UNK D_00FA5DC8;
extern M2C_UNK D_00FA5DD8;
extern M2C_UNK D_0108BD00;
extern M2C_UNK D_0108CED0;
extern f32 D_00FA5AF8;
extern f32 D_00FA5B08;
extern f32 D_00FA5CE4;
extern f32 D_00FA5CE8;
extern f32 D_00FA5CEC;
extern f32 D_00FA5DC0;
extern s32 D_00F9B544;
extern s32 D_00FA5AF0;
extern s32 D_00FA5AF4;
extern s32 D_00FA5AFC;
extern s32 D_00FA5B00;
extern s32 D_00FA5B04;
extern s32 D_00FA5B2C;
extern s32 D_00FA5B30;
extern s32 D_00FA5B34;
extern s32 D_00FA5BA8;
extern s32 D_00FA5BAC;
extern s32 D_00FA5CE0;
extern s32 D_00FA5D48;
extern s32 D_00FA5E38;
extern s32 D_0108CE7C;
extern s32 D_0108CE80;
extern s32 D_0108CE88;
extern s32 D_0108D180;
extern void *D_00F9B540;
s32 func_00f4afb8(s32);
s32 func_00f5ac08();
s32 func_00f5acf0(s32, s32);
s32 func_00f667b8(s32, s32, s32);
s32 func_00f680c0(s32);
s32 func_00f68140(s32);
s32 func_00f684e8(s32);
void *func_00f4b258(u16, s32);
void func_00f59820(M2C_UNK, s32);
void func_00f67008(s32, s32);
void func_00f67258(s32, s32);
void func_00f68a40(s32);

f32 func_00f50030(s32 arg0) {
    return *(f32 *)((s8 *)(s8 *)&D_0108BD00 + (arg0 * 0xC));
}

void func_00f500f0(s32 arg0, void *arg1) {
    func_001bb658(M2C_FIELD(arg1, u16 *, 4) - 1);
    func_001bbf38(arg0, arg1);
}

void func_00f502b8(s32 arg0) {
    func_0011d768(4);
    func_00f78000(arg0);
}

void func_00f504a8(void) {
    if (func_00f680c0(D_00FA5B2C) != 0) {
        func_00f68a40(D_00FA5B2C);
        D_00FA5B2C = -1;
    }
    D_00FA5B30 = 0;
}

void func_00f50548(s32 arg0) {
    D_00FA5B04 = arg0;
    func_00f50050();
}

void func_00f50568(s32 arg0) {
    D_00FA5B00 = arg0;
}

void func_00f50578(s32 arg0) {
    D_00FA5B08 = (f32) arg0 * 0.0078125f;
}

void func_00f50598(s32 arg0) {
    D_00FA5B34 = arg0;
}

void func_00f50610(s32 arg0) {
    D_00FA5AF8 = (f32) arg0 * 0.0078125f;
    func_00f50050();
}

s32 func_00f50640(void) {
    return D_00FA5AFC;
}

void func_00f516e0(s32 arg0) {
    s32 temp_a1;
    u16 temp_a0;

    temp_a1 = func_00f4afb8(M2C_FIELD(D_00F9B540, u16 *, 0x4C) - 1) < 1;
    if (D_00FA5AF0 != 0) {
        func_00f49430(1, D_00FA5AF4, 0x8000C4C4, 0x80009191);
        return;
    }
    if (arg0 != 0) {
        func_00f49430(2, 0x9F, 0x80E19664, 0);
        return;
    }
    temp_a0 = M2C_FIELD(D_00F9B540, u16 *, 0x74);
    if (temp_a0 & 2) {
        func_00f49430(1, M2C_FIELD(func_00f4b258(M2C_FIELD(D_00F9B540, u16 *, 0x5C), D_00F9B544), u16 *, 4) - 1, 0x806168F4, 0x804E53C2);
        return;
    }
    if (temp_a1 != 0) {
        func_00f49430(2, 0x9E, 0x80077328, 0);
        return;
    }
    if (temp_a0 & 1 & 0xFFFF) {
        func_00f49430(1, (s32) M2C_FIELD(D_00F9B540, s16 *, 0x82), 0x80077328, 0x800C401D);
        return;
    }
    func_00f49430(1, (s32) M2C_FIELD(D_00F9B540, s16 *, 0x82), 0x801FA64C, 0x80077328);
}

void func_00f51cd0(void) {
    s32 var_a2;
    void *var_a0;

    var_a2 = 0;
    var_a0 = D_00F9B540 + 0x110;
    if (M2C_FIELD(D_00F9B540, u16 *, 0xA4) != 0) {
        do {
            var_a2 += 1;
            M2C_FIELD(var_a0, u8 *, 8) = (u8) M2C_FIELD(D_00F9B540, u8 *, 0x7E);
            var_a0 += 0xC;
        } while (var_a2 < (s32) M2C_FIELD(D_00F9B540, u16 *, 0xA4));
    }
}

void func_00f530d0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00FA5BA8 = arg0;
    D_0108CE7C = arg1;
    D_0108CE80 = arg2;
    D_00FA5BAC = arg3;
}

void func_00f55190(void) {
    D_0108CE88 = (s32) M2C_FIELD(D_00F9B540, s16 *, 0x80);
}

void func_00f55298(void) {
    s32 temp_v0;
    s32 var_v1;

    if (D_00FA5CE0 != 0) {
        var_v1 = D_00FA5D48;
        if (var_v1 >= 0x28) {
            var_v1 = 0x4F - var_v1;
        }
        func_00f59820(7, ((s32) (var_v1 + ((u32) var_v1 >> 0x1F)) >> 1) + 0x14);
        temp_v0 = D_00FA5D48 + 1;
        D_00FA5D48 = temp_v0;
        if (temp_v0 >= 0x50) {
            D_00FA5D48 = 0;
        }
    }
}

void func_00f55330(s32 arg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0 * 0.0078125f;
    D_00FA5CE4 = temp_f0;
    D_00FA5CEC = temp_f0;
}

void func_00f55358(s32 arg0) {
    D_00FA5CEC = (f32) arg0 * 0.0078125f;
}

void func_00f55378(s32 arg0) {
    D_00FA5CE8 = (f32) arg0 * 0.0078125f;
}

void func_00f55d38(s32 arg0) {
    s32 var_s0;

    if (arg0 > 0) {
        var_s0 = arg0;
        do {
            var_s0 -= 1;
            func_00f559d0();
            func_001bfac8();
        } while (var_s0 != 0);
    }
}

void func_00f59848(u32 arg0, s32 arg1) {
    if (arg0 < 0x10U) {
        *(M2C_UNK *)((s8 *)(s8 *)&D_0108CED0 + (arg0 * 4)) = arg1;
    }
}

void func_00f5a478(s32 arg0) {
    D_00FA5DC0 = (f32) arg0 * 0.0078125f;
}

void func_00f5aa60(void) {
    s32 var_s0;

    var_s0 = 0x3B;
    do {
        var_s0 -= 1;
        func_001bfac8();
    } while (var_s0 >= 0);
    func_001bffa0(D_0108D180);
}

void func_00f5ac80(s32 arg0) {
    func_001ed278(-1, *(M2C_UNK *)((s8 *)(s8 *)&D_00FA5DC8 + (arg0 * 4)), arg0 + 1, 0x3FFF, 0x3FFF);
}

void func_00f5acb8(s32 arg0) {
    func_001ed278(-1, *(M2C_UNK *)((s8 *)(s8 *)&D_00FA5DD8 + (arg0 * 4)), arg0 + 0xB, 0x3FFF, 0x3FFF);
}

void func_00f5ad68(s32 arg0) {
    s32 temp_v0;

    if (D_00FA5E38 != arg0) {
        temp_v0 = func_00f5ac08();
        if (temp_v0 >= 0) {
            if (D_00FA5E38 >= 0) {
                func_0011d3c8(func_00f5acf0(D_00FA5E38, temp_v0), D_00FA5E38 + 0x1000, 0x3C);
            }
            if (arg0 >= 0) {
                func_0011d1e0(func_00f5acf0(arg0, temp_v0), arg0 + 0x1000, &D_00FA5DB0, 0);
            }
            D_00FA5E38 = arg0;
        }
    }
}

void func_00f5ae98(void) {
    func_00f68808();
}

void func_00f5aeb0(s32 arg0) {
    s32 var_s0;

    var_s0 = 0;
    do {
        if ((func_00f68140(var_s0) != 0) && (func_00f684e8(var_s0) == arg0)) {
            func_00f68ab0(var_s0);
        }
        var_s0 += 1;
    } while (var_s0 < 0x100);
}

void func_00f5c4b0(void) {
    func_001bfac8();
    func_00f5c380();
    func_00f5c0c8();
    func_00f5c1c8();
}

void func_00f5ded0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 *var_s0;
    s32 var_s1;

    var_s0 = arg0;
    var_s1 = 2;
    do {
        var_s1 -= 1;
        *var_s0 = func_00f667b8(*var_s0, arg2, arg1);
        var_s0 += 1;
    } while (var_s1 >= 0);
}

void func_00f5df38(s32 arg0, s32 arg1, s32 arg2) {
    func_00f67008(arg0, M2C_FIELD(arg2, s32 *, 0));
    func_00f67008(arg0, M2C_FIELD(arg2, s32 *, 8));
    func_00f67008(arg1, M2C_FIELD(arg2, s32 *, 4));
}

void func_00f5df90(s32 arg0, s32 arg1, s32 arg2) {
    func_00f67258(arg0, M2C_FIELD(arg2, s32 *, 4));
    func_00f67258(arg1, M2C_FIELD(arg2, s32 *, 8));
    func_00f67258(arg1, M2C_FIELD(arg2, s32 *, 0));
}

void func_00f5e6e0(s32 arg0) {
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
