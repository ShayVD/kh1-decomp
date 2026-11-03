/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_001b9bb0(M2C_UNK, M2C_UNK);
M2C_UNK func_001ba708(M2C_UNK);
M2C_UNK func_001be820(s32, M2C_UNK);
M2C_UNK func_001c0078(s32);
M2C_UNK func_001c0310(M2C_UNK, M2C_UNK *, s32);
M2C_UNK func_001c0688(M2C_UNK);
M2C_UNK func_00f20290(M2C_UNK);
M2C_UNK func_00f22b48(M2C_UNK);
M2C_UNK func_00f22f28();
M2C_UNK func_00f25d90(M2C_UNK, M2C_UNK);
M2C_UNK func_00f26180();
M2C_UNK func_00f28f58();
M2C_UNK func_00f29450(M2C_UNK);
M2C_UNK func_00f29470(M2C_UNK);
M2C_UNK func_00f29480(M2C_UNK);
M2C_UNK func_00f2e238(M2C_UNK);
M2C_UNK func_00f2e280(M2C_UNK);
M2C_UNK func_00f32778(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_00f3db18(s32);
M2C_UNK func_00f3fe80(M2C_UNK, s32);
M2C_UNK func_00f50f08(s32);
M2C_UNK func_00f51588(s32);
M2C_UNK memcpy(s32, M2C_UNK *, M2C_UNK);
M2C_UNK sceVu0RotMatrix(s32, s32, M2C_UNK *);
M2C_UNK sceVu0UnitMatrix(s32);
extern M2C_UNK D_00F56FD8;
extern M2C_UNK D_00F60D50;
extern M2C_UNK D_00F74200;
extern M2C_UNK D_00F74350;
extern M2C_UNK D_00F74360;
extern M2C_UNK D_00F7F540;
extern M2C_UNK func_00f25f78;
extern f32 D_00F61378;
extern f32 D_00F6156C;
extern s32 D_00F56D80;
extern s32 D_00F56D84;
extern s32 D_00F56D88;
extern s32 D_00F56D98;
extern s32 D_00F56DA4;
extern s32 D_00F56DBC;
extern s32 D_00F56DC0;
extern s32 D_00F56DC8;
extern s32 D_00F56EC4;
extern s32 D_00F56FD0;
extern s32 D_00F61364;
extern s32 D_00F61368;
extern s32 D_00F6137C;
extern s32 D_00F613AC;
extern s32 D_00F613B0;
extern s32 D_00F613B4;
extern s32 D_00F61428;
extern s32 D_00F6142C;
extern s32 D_00F61560;
extern s32 D_00F615C8;
extern s32 D_00F74224;
extern s32 D_00F74268;
extern s32 D_00F74270;
extern s32 D_00F74274;
extern s32 D_00F74278;
extern s32 D_00F7427C;
extern s32 D_00F74340;
extern s32 D_00F74344;
extern s32 D_00F74348;
extern s32 D_00F7F4D8;
extern s32 D_00F7F4DC;
extern s32 D_00F806BC;
extern s32 D_00F806C0;
s32 func_001b9b78(M2C_UNK);
s32 func_001ba3f0(s32);
s32 func_001bb500(M2C_UNK, M2C_UNK);
s32 func_00232cc0(M2C_UNK);
s32 func_00f26fb8(s32, M2C_UNK, M2C_UNK);
s32 func_00f2e420(M2C_UNK, M2C_UNK, u8, s32);
s32 func_00f3db20(s32, s32);
s32 func_00f3db40(s32, s32);
s32 func_00f3db58(s32, s32, s32);
s32 func_00f3f9d0(s32);
s32 func_00f3f9e8(s32);
s32 func_00f40fc8(s32);
void *func_001bb658(s32);
void func_001bb870(s32);
void func_001bfac8(void);
void func_00f20100(void);
void func_00f20e48();
void func_00f25a18();
s32 func_00f26458(s32, s32, s32);
void func_00f28c70();
void func_00f294b0(M2C_UNK);
void func_00f2e2a0();
void func_00f32728(M2C_UNK, s32);
void func_00f32750(M2C_UNK, M2C_UNK);
void func_00f40fa8(void);
void func_00f41948(s32);

void func_00f20000(void) {
    func_00f22f28();
}

s32 func_00f20018(void) {
    return D_00F56D88 | D_00F56EC4;
}

void func_00f20030(s32 arg0) {
    func_0011d768(4);
    func_00f50f08(arg0);
}

s32 func_00f20098(void) {
    return D_00F74224;
}

s32 func_00f200a8(void) {
    return D_00F56DC8;
}

void func_00f200b8(s32 arg0) {
    D_00F56DC8 = arg0;
}

void func_00f20248(s32 arg0) {
    s32 *temp_s0;
    s32 temp_v0;

    temp_s0 = (s8 *)&D_00F74200 + (arg0 * 4);
    temp_v0 = *temp_s0;
    if (temp_v0 >= 0) {
        func_001c0078(temp_v0);
    }
    *temp_s0 = -1;
}

void func_00f20328(void) {

}

void func_00f20708(void) {
    D_00F56DBC = 0;
}

s32 func_00f21410(void) {
    func_00f20e48();
    func_00f32750(1, 1);
    func_00f294b0(0);
    func_00f2e2a0();
    func_00f28c70();
    func_001bb870(D_00F56DC0 + 0xA0);
    func_00f25a18();
    return 1;
}

void func_00f21ba0(void) {
    func_00f20100();
    D_00F56D80 = 0;
    D_00F56D84 = 0;
    func_00f40fa8();
    for (;;) {
        func_001bfac8();
    }
}

void func_00f21bd8(void) {
    func_00f20290(0xB);
    func_00f20290(0xC);
    func_00f29450(0);
    func_00f29470(0x80);
    func_00f29480(0x80);
    func_00f2e238(0x80);
    func_00f2e280(0x80);
    func_00f32778(-1, 0x80, 0x80, 0x80, 0x80);
}

s32 func_00f21e38(void) {
    return D_00F74268;
}

void func_00f21e48(void) {
    D_00F74268 = 1;
}

void func_00f21e58(void) {
    func_001c0688(0x3E);
    func_001ba708(0);
}

void func_00f22338(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00F74270 = arg0;
    D_00F74274 = arg1;
    D_00F74278 = arg2;
    D_00F7427C = arg3;
}

s32 func_00f22ed8(void) {
    D_00F56D98 = 0;
    return 0;
}

s32 func_00f22ee8(void) {
    return func_001b9b78(0) == 0;
}

void func_00f22f08(void) {
    func_001b9bb0(0, 1);
}

s32 func_00f23078(void) {
    return D_00F56DA4;
}

s32 func_00f23088(void) {
    return D_00F56FD0;
}

void func_00f23830(s32 arg0) {
    D_00F74344 = arg0;
}

void func_00f23840(s32 arg0) {
    D_00F74348 = arg0;
}

void func_00f23850(s32 arg0) {
    D_00F74340 = arg0;
}

s32 func_00f23860(s32 arg0) {
    return func_00f3db40(arg0, D_00F74344);
}

s32 func_00f23880(s32 arg0) {
    return func_00f3db40(arg0, D_00F74344) + 0xB0;
}

void func_00f238a8(void) {
    func_00f3db18(D_00F74344);
}

s32 func_00f238c8(s32 arg0, s32 arg1) {
    return func_00f3db58(arg0, arg1, D_00F74340);
}

s32 func_00f238e8(s32 arg0) {
    return func_00f3db20(arg0, D_00F74340);
}

s32 func_00f23908(s32 arg0) {
    return func_00f3db40(arg0, D_00F74348);
}

u8 func_00f23bb0(s32 arg0) {
    return M2C_FIELD(func_001bb658(arg0), u8 *, 4);
}

void func_00f23e58(s32 arg0) {
    u32 temp_s1;
    u8 *temp_v1;
    u8 temp_s0;

    temp_s1 = arg0 + 0x10E0;
    temp_s0 = M2C_FIELD((D_00F56DC0 + temp_s1), u8 *, 0xC);
    if ((s32) temp_s0 < func_001ba3f0(arg0)) {
        temp_v1 = D_00F56DC0 + 0xC + temp_s1;
        *temp_v1 += 1;
    }
}

u8 func_00f23ec0(s32 arg0) {
    return M2C_FIELD((arg0 + D_00F56DC0), u8 *, 0x10EC);
}

s32 func_00f25b40(s32 arg0, s32 arg1) {
    switch (arg0) {                                 /* irregular */
    case 0x80:
        sceVu0UnitMatrix(arg1);
        sceVu0RotMatrix(arg1, arg1, &D_00F74350);
block_7:
        return 1;
    case 0x8D:
        sceVu0UnitMatrix(arg1);
        sceVu0RotMatrix(arg1, arg1, &D_00F74360);
        goto block_7;
    default:
        return 0;
    }
}

void func_00f25e48(void) {
    s32 temp_v0;

    temp_v0 = func_00232cc0(4);
    func_001be820(temp_v0, 0xB040);
    memcpy(temp_v0, &D_00F56FD8, 0x9C20);
    func_00f25d90(0, 0x47);
    func_00f25d90(1, 0x50);
    func_00f25d90(2, 0x51);
    func_00f25d90(3, 0x52);
}

s32 func_00f25ec0(s32 arg0) {
    return D_00F7F4D8 + (arg0 << 0xD);
}

void func_00f25f40(s32 arg0) {
    D_00F7F4DC = arg0;
    func_00f51588(arg0);
}

void func_00f25fe8(s32 arg0) {
    func_001c0310(-1, &func_00f25f78, arg0);
}

void func_00f261e8(void) {
    D_00F7F4D8 = func_001bb500(0x20000, 0x80);
    func_00f26180();
}

void func_00f26408(s32 arg0) {
    D_00F56EC4 = arg0 + 1;
    func_00f22b48(1);
}

s32 func_00f26500(s32 arg0) {
    return (s32)func_00f26458(arg0, (s32) &D_00F60D50, 0x70);
}

void func_00f272f0(s32 arg0) {
    D_00F61364 = arg0;
}

void func_00f27300(s32 arg0) {
    D_00F61368 = arg0;
}

void func_00f28a68(s8 *arg0) {
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

f32 func_00f28f38(s32 arg0) {
    return *(f32 *)((s8 *)(s8 *)&D_00F7F540 + (arg0 * 0xC));
}

void func_00f291c0(s32 arg0) {
    func_0011d768(4);
    func_00f50f08(arg0);
}

void func_00f293b0(void) {
    if (func_00f40fc8(D_00F613AC) != 0) {
        func_00f41948(D_00F613AC);
        D_00F613AC = -1;
    }
    D_00F613B0 = 0;
}

void func_00f294a0(s32 arg0) {
    D_00F613B4 = arg0;
}

void func_00f29518(s32 arg0) {
    D_00F61378 = (f32) arg0 * 0.0078125f;
    func_00f28f58();
}

s32 func_00f29548(void) {
    return D_00F6137C;
}

void func_00f2bfd8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00F61428 = arg0;
    D_00F806BC = arg1;
    D_00F806C0 = arg2;
    D_00F6142C = arg3;
}

void func_00f2e1a0(void) {
    s32 temp_v0;
    s32 var_v1;

    if (D_00F61560 != 0) {
        var_v1 = D_00F615C8;
        if (var_v1 >= 0x28) {
            var_v1 = 0x4F - var_v1;
        }
        func_00f32728(7, ((s32) (var_v1 + ((u32) var_v1 >> 0x1F)) >> 1) + 0x14);
        temp_v0 = D_00F615C8 + 1;
        D_00F615C8 = temp_v0;
        if (temp_v0 >= 0x50) {
            D_00F615C8 = 0;
        }
    }
}

void func_00f2e260(s32 arg0) {
    D_00F6156C = (f32) arg0 * 0.0078125f;
}

void func_00f2e788(s32 *arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = func_00f3f9d0(*arg0);
    *arg0 = temp_v0;
    temp_v0_2 = func_00f26fb8(temp_v0, 0, 0);
    *arg0 = temp_v0_2;
    temp_v0_3 = func_00f2e420(0x1F, 0x3C, M2C_FIELD((arg1 + D_00F56DC0), u8 *, 0x10EC), temp_v0_2);
    *arg0 = temp_v0_3;
    func_00f3fe80(0x2B71, func_00f3f9e8(temp_v0_3));
}
