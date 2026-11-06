/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0012cab8(M2C_UNK *);
M2C_UNK func_0012cc38(M2C_UNK, M2C_UNK);
M2C_UNK func_0012ccb0(M2C_UNK);
M2C_UNK func_00135870(s32 *);
M2C_UNK func_00137688(s32, f32);
M2C_UNK func_00147e08(s32 *, M2C_UNK *);
M2C_UNK func_00f224d8();
M2C_UNK func_00f22968(M2C_UNK);
M2C_UNK sceVu0AddVector(M2C_UNK *, s32, void *);
M2C_UNK sceVu0ApplyMatrix(s32, s32, void *);
M2C_UNK sceVu0CopyVector(s32, s32);
M2C_UNK sceVu0SubVector(M2C_UNK *, M2C_UNK *, s32);
extern M2C_UNK D_002C58A0;
extern M2C_UNK D_002E31B0;
extern M2C_UNK D_00F23290;
extern M2C_UNK func_00f20188;
extern M2C_UNK func_00f20228;
extern M2C_UNK func_00f21938;
extern f32 D_00F23484;
extern s32 D_002C5958;
extern s32 D_00F23200;
extern s32 D_00F23208;
extern s32 D_00F2320C;
extern s32 D_00F23480;
extern s32 D_00F23488;
extern s32 D_00F23E04;
extern s32 D_00F23E0C;
extern s32 D_00F23F90;
extern void *D_002E26A0;
f32 PlatSqrtf(f32);
#ifdef KH1_PS2
f32 func_001224c8(s32, s32, s32, f32);
#else /* the definition is void: an x86 caller of an f32 one pops an empty x87 stack */
void func_001224c8(s32, s32, s32, f32);
#endif
f32 func_001376e8();
s32 func_001226f0(s32, s32, s32);
s32 func_00130030(void *);
s32 func_00130340(s32, s32, f32);
s32 func_00130398(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
s32 func_0013dc10(s32, s32);
s32 func_00147c98(s32, M2C_UNK, M2C_UNK);
s32 func_0014f658(s32, s32);
void func_00106978(s32);
void func_00131500(s32);
void func_0013ecf8(s32, s32, s32);
void func_00148068(s32, f32);
void func_00f21710(s32, f32);
void func_00f22408(s32);

void func_00f20130(s32 arg0) {
    s32 temp_v0;

    D_00F23200 = 1;
    temp_v0 = func_001226f0(1, 9, 0);
    D_00F2320C = temp_v0;
    func_001224c8(temp_v0, arg0, 0, 3e+01f);
}

void func_00f20208(void) {
    func_0011ef10(0xCB20, &func_00f20188);
}

void func_00f202b8(void) {
    func_0011ef10(0xCB20, &func_00f20228);
}

void func_00f208f8(void) {
    if (D_00F23488 == 0) {
        D_00F23488 = func_00147c98(D_00F23208, 2, 0x4E20);
    }
}

void func_00f20940(void) {
    if (D_00F23488 != 0) {
        func_00148068(D_00F23488, 3e+01f);
        D_00F23488 = 0;
    }
}

void func_00f20988(void) {
    func_0012cc38(0, 0x5B);
    if ((D_00F23484 < 1e+01f) || (D_00F23484 >= 7e+01f)) {
        func_0012ccb0(0);
    }
}

void func_00f209e0(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x3B8) = PlatSqrtf((2.0f * fparg0) / 0.48469386f);
    M2C_FIELD(arg0, f32 *, 0x3B4) = (f32) M2C_FIELD(arg0, f32 *, 0x14);
    M2C_FIELD(arg0, s32 *, 0x3D0) = 0;
    M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    M2C_FIELD(arg0, f32 *, 0x3BC) = (f32) -fparg0;
}

void func_00f20d70(void *arg0) {
    sceVu0CopyVector(arg0 + 0x20, arg0 + 0x30);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

s32 func_00f20da0(s32 arg0, s32 arg1) {
    if ((D_00F23480 >= 6) && (arg1 == 0)) {
        func_00130398(arg0, 0x01000007, 0.0f);
        func_00130578(arg0, 0x40000000, 8.0f);
        return 0;
    }
    return M2C_FIELD(arg0, s32 *, 0x70);
}

void func_00f210e0(void) {
    void *temp_s0;

    temp_s0 = D_002E26A0;
    if (D_00F23E04 < 0xC) {
        func_0012cc38(0, 0x58);
    } else {
        func_0012cc38(0, 0x59);
    }
    if ((func_00130030(temp_s0) == 0) || !(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x14C), s32 *, 0x28) & 0x10000)) {
        func_0012ccb0(0);
    }
}

s32 func_00f21208(s32 arg0) {
    func_0014f658(arg0, 0);
    return func_00130340(arg0, 0x40000000, 0.0f);
}

s32 func_00f21240(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v1;
    s64 *temp_a2;

    func_0013ecf8(arg0, (s32) &D_002E31B0, arg1);
    func_0013dc10(arg0, D_00F23E04 + 0x22);
    temp_a2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s64 **, 0x2C);
    *temp_a2 |= 0x800000;
    temp_v0 = func_00130578(arg0, 0x40000000, 0.0f);
    temp_v1 = D_00F23E04 + 1;
    D_00F23E04 = temp_v1;
    if ((temp_v1 == 7) || (temp_v1 == 0xD)) {
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s64 **, 0x2C), s32 *, 8) = (s32) D_00F23208;
    }
    return temp_v0;
}

void func_00f21328(void *arg0) {
    sceVu0CopyVector(arg0 + 0x20, arg0 + 0x30);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

void func_00f21528(void) {
    void *temp_s0;

    temp_s0 = D_002E26A0;
    if (D_00F23E0C < 6) {
        func_0012cc38(0, 0x4D);
    } else {
        func_0012cc38(0, 0x4E);
    }
    if ((func_00130030(temp_s0) == 0) || !(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x14C), s32 *, 0x28) & 0x10000)) {
        func_0012ccb0(0);
    }
}

void func_00f21678(void *arg0) {
    sceVu0CopyVector(arg0 + 0x20, arg0 + 0x30);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

s32 func_00f216a8(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        func_00131500(arg0);
        func_00130340(arg0, 6, 8.0f);
        return 2;
    }
    return M2C_FIELD(arg0, s32 *, 0x70);
}

void func_00f21858(s32 arg0) {
    func_00f21710(arg0, 0.0f);
}

void func_00f219d8(s32 *arg0) {
    func_0012cab8(&func_00f21938);
    *arg0 |= 0x01200080;
    func_00135870(arg0);
}

void func_00f21a68(void *arg0) {
    sceVu0CopyVector(arg0 + 0x20, arg0 + 0x30);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

void func_00f22510(s32 arg0) {
    *(M2C_UNK *)arg0 = (s32) (*(M2C_UNK *)arg0 | 0x01200080);
    func_00f22408(arg0);
}

s32 func_00f22578(s32 arg0) {
    func_0014f658(arg0, 0);
    return func_00130340(arg0, 0x40000000, 0.0f);
}

void func_00f22870(s32 arg0) {
    s32 sp[16];    s32 temp_s2;
    void *temp_s3;

    temp_s2 = arg0 << 5;
    temp_s3 = temp_s2 + (s8 *)&D_00F23290;
    if (M2C_FIELD(temp_s3, s32 *, 4) != 0) {
        sceVu0SubVector(sp, &D_002C58A0, D_00F23F90 + 0xF0);
        sceVu0SubVector(&M2C_FIELD(sp, M2C_UNK *, 0x10), &D_002C58A0, D_00F23F90 + 0xE0);
        sceVu0SubVector(&M2C_FIELD(sp, M2C_UNK *, 0x20), &D_002C58A0, D_00F23F90 + 0xD0);
        sceVu0AddVector(&M2C_FIELD(sp, M2C_UNK *, 0x30), D_00F23F90 + 0x100, temp_s2 + ((s8 *)&D_00F23290 + 0x10));
        M2C_FIELD(sp, f32 *, 0x3C) = 1.0f;
        func_00147e08(M2C_FIELD(temp_s3, s32 **, 8), sp);
        return;
    }
    sceVu0ApplyMatrix(*M2C_FIELD(temp_s3, s32 **, 8), D_00F23F90 + 0xD0, temp_s2 + ((s8 *)&D_00F23290 + 0x10));
}

s32 func_00f229c0(void) {
    func_00f22968(0);
    func_00f22968(1);
    return 1;
}

s32 func_00f229e8(void) {
    func_00f22968(2);
    func_00f22968(5);
    return 1;
}

s32 func_00f22a10(void) {
    func_00f22968(3);
    func_00f224d8();
    return 1;
}

s32 func_00f22a38(void) {
    D_002C5958 |= 0x04000000;
    func_00106978(0x3C);
    return 1;
}

/* a class's 3rd callback (func_0014f830): (object, the vector it is given), as class15.c func_0014c6c0 */
void func_00f22d10(s32 arg0, f32 *arg1) {
    func_00137688(arg0, func_001376e8(arg0, arg1));
}

void func_00f22ee8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg2;
    sceVu0CopyVector(arg1, arg3);
}
