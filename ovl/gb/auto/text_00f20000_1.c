/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001ba708(M2C_UNK);
M2C_UNK func_001bb658(s32);
M2C_UNK func_001bb7c8(M2C_UNK *, s32);
M2C_UNK func_001bbf38(s32, void *);
M2C_UNK func_001bfac8();
M2C_UNK func_001c0310(M2C_UNK, M2C_UNK *);
M2C_UNK func_00f22338(M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00f29450(s32);
M2C_UNK func_00f29470(s32);
M2C_UNK func_00f29518(s32);
M2C_UNK func_00f2e1a0();
M2C_UNK func_00f2e238(s32);
M2C_UNK func_00f2e8d8();
M2C_UNK func_00f32750(M2C_UNK, M2C_UNK);
M2C_UNK func_00f32778(M2C_UNK, s32, s32, s32, s32);
extern M2C_UNK *D_003773A4;
extern M2C_UNK *D_003773A8;
extern M2C_UNK *D_003773D0;
extern M2C_UNK *D_003773D4;
extern M2C_UNK *D_003773D8;
extern M2C_UNK *D_003773E8;
extern M2C_UNK D_00F56DC8;
extern M2C_UNK D_00F715B8;
extern M2C_UNK D_00F715C8;
extern M2C_UNK D_00F715D8;
extern M2C_UNK D_00F74350;
extern M2C_UNK D_00F7F540;
extern M2C_UNK func_00f21e58;
extern M2C_UNK func_00f25f40;
extern M2C_UNK func_00f25f60;
extern M2C_UNK func_00f25fe8;
extern M2C_UNK func_00f26010;
extern M2C_UNK func_00f26040;
extern M2C_UNK func_00f26120;
extern f32 D_00F61388;
extern f32 D_00F61568;
extern s32 D_00F56D80;
extern s32 D_00F56DC4;
extern s32 D_00F61370;
extern s32 D_00F61374;
extern s32 D_00F74210;
extern s32 D_00F806C8;
extern void *D_00F56DC0;
s32 func_00f23ec0(s32);
s32 func_00f25ec0(M2C_UNK);
void *func_00f24160(u16, s32);
void func_00f32838(M2C_UNK *, s32);
void func_00f37080();

s32 func_00f200c8(void) {
    func_00f32838(&D_00F56DC8, D_00F74210);
    return (D_00F56D80 != 0) ? 0 : 4;
}

void func_00f216b0(void *arg0) {
    func_00f32778(1, 0x80, 0x80, 0x80, M2C_FIELD(arg0, s32 *, 0x24));
    if (M2C_FIELD(arg0, s32 *, 0x24) == 0) {
        func_00f32750(1, 0);
    } else {
        func_00f32750(1, 1);
    }
    func_00f32778(4, M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), 0x80);
    func_00f32778(7, M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, s32 *, 0x14), 0x80);
    func_00f32778(6, M2C_FIELD(arg0, s32 *, 0x18), M2C_FIELD(arg0, s32 *, 0x1C), M2C_FIELD(arg0, s32 *, 0x20), 0x80);
    func_00f2e238(M2C_FIELD(arg0, s32 *, 0x28));
    func_00f29518(M2C_FIELD(arg0, s32 *, 0x2C));
    func_00f29450(M2C_FIELD(arg0, s32 *, 0x30));
    func_00f29470(M2C_FIELD(arg0, s32 *, 0x34));
}

void func_00f21e78(void) {
    func_001ba708(1);
    func_001c0310(-1, &func_00f21e58);
}

void func_00f25a18(void) {
    func_00f37080();
    M2C_FIELD(&D_00F74350, s32 *, 0) = 0;
    M2C_FIELD(&D_00F74350, s32 *, 4) = 0;
    M2C_FIELD(&D_00F74350, s32 *, 8) = 0;
    M2C_FIELD(&D_00F74350, f32 *, 0xC) = 1.0f;
    M2C_FIELD(&D_00F74350, s32 *, 0x10) = 0;
    M2C_FIELD(&D_00F74350, s32 *, 0x14) = 0;
    M2C_FIELD(&D_00F74350, s32 *, 0x18) = 0;
    M2C_FIELD(&D_00F74350, f32 *, 0x1C) = 1.0f;
}

void func_00f25ed8(void) {
    func_001bb7c8(&D_00F715B8, func_00f25ec0(0));
    func_001bb7c8(&D_00F715C8, func_00f25ec0(1));
    func_001bb7c8(&D_00F715D8, func_00f25ec0(2));
}

void func_00f26180(void) {
    D_003773A4 = &func_00f25f60;
    D_003773A8 = &func_00f25fe8;
    D_003773D8 = &func_00f26010;
    D_003773D0 = &func_00f25f40;
    D_003773D4 = &func_00f26040;
    D_003773E8 = &func_00f26120;
}

void func_00f28c70(void) {
    s8 *var_v0;
    s32 var_v1;

    var_v1 = 0x13F;
    var_v0 = &D_00F7F540;
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s32 *, 0) = 0;
        M2C_FIELD(var_v0, s32 *, 4) = 0;
        M2C_FIELD(var_v0, s16 *, 8) = 0;
        var_v0 += 0xC;
    } while (var_v1 >= 0);
}

void func_00f28ff8(s32 arg0, void *arg1) {
    func_001bb658(M2C_FIELD(arg1, u16 *, 4) - 1);
    func_001bbf38(arg0, arg1);
}

void func_00f29480(s32 arg0) {
    D_00F61388 = (f32) arg0 * 0.0078125f;
}

void func_00f2a5e8(s32 arg0) {
    s32 temp_a1;
    u16 temp_a0;

    temp_a1 = func_00f23ec0(M2C_FIELD(D_00F56DC0, u16 *, 0x4C) - 1) < 1;
    if (D_00F61370 != 0) {
        func_00f22338(1, D_00F61374, 0x8000C4C4, 0x80009191);
        return;
    }
    if (arg0 != 0) {
        func_00f22338(2, 0x9F, 0x80E19664, 0);
        return;
    }
    temp_a0 = M2C_FIELD(D_00F56DC0, u16 *, 0x74);
    if (temp_a0 & 2) {
        func_00f22338(1, M2C_FIELD(func_00f24160(M2C_FIELD(D_00F56DC0, u16 *, 0x5C), D_00F56DC4), u16 *, 4) - 1, 0x806168F4, 0x804E53C2);
        return;
    }
    if (temp_a1 != 0) {
        func_00f22338(2, 0x9E, 0x80077328, 0);
        return;
    }
    if (temp_a0 & 1 & 0xFFFF) {
        func_00f22338(1, (s32) M2C_FIELD(D_00F56DC0, s16 *, 0x82), 0x80077328, 0x800C401D);
        return;
    }
    func_00f22338(1, (s32) M2C_FIELD(D_00F56DC0, s16 *, 0x82), 0x801FA64C, 0x80077328);
}

void func_00f2abd8(void) {
    s32 var_a2;
    void *var_a0;

    var_a2 = 0;
    var_a0 = D_00F56DC0 + 0x110;
    if (M2C_FIELD(D_00F56DC0, u16 *, 0xA4) != 0) {
        do {
            var_a2 += 1;
            M2C_FIELD(var_a0, u8 *, 8) = (u8) M2C_FIELD(D_00F56DC0, u8 *, 0x7E);
            var_a0 += 0xC;
        } while (var_a2 < (s32) M2C_FIELD(D_00F56DC0, u16 *, 0xA4));
    }
}

void func_00f2e098(void) {
    D_00F806C8 = (s32) M2C_FIELD(D_00F56DC0, s16 *, 0x80);
}

void func_00f2e218(void) {
loop_1:
    func_00f2e1a0();
    func_001bfac8();
    goto loop_1;
}

void func_00f2e280(s32 arg0) {
    D_00F61568 = (f32) arg0 * 0.0078125f;
}

void func_00f2ec40(s32 arg0) {
    s32 var_s0;

    if (arg0 > 0) {
        var_s0 = arg0;
        do {
            var_s0 -= 1;
            func_00f2e8d8();
            func_001bfac8();
        } while (var_s0 != 0);
    }
}
