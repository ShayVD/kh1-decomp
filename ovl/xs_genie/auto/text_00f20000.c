/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00f200a0(M2C_UNK);
M2C_UNK func_00f20fe8(s32 *);
M2C_UNK func_00f22760(s32 *);
M2C_UNK sceVu0CopyVector(s32, s32);
extern f32 D_002BBDFC;
extern f32 D_00FC0D98;
extern f32 D_00FC1A4C;
extern s32 D_00F22E98;
extern s32 D_00FC0E48;
extern s32 D_00FC1A48;
extern s32 D_00FC1A50;
extern s32 D_00FC1A60;
extern s32 D_00FC1CE0[];
extern s32 D_00FC1DE0;
extern s32 D_00FC2E20;
extern void *D_00F22E90;
s32 func_0012cc38(s32, s32);
s32 func_0012ccb0(s32);
s32 func_00f21ab0(s32, s32, f32);
s32 func_00f22078();
s32 func_00f223a8(s32, f32);
void **func_00147ed8(s32, M2C_UNK, M2C_UNK, s32);
void func_00f20c68(void *);
void func_00f20cb8(void *);
void memset(s32, s32, s32);

s32 func_00f20480(void) {
    s32 var_v0;
    u32 temp_v1;

    func_0012cc38(3, 0x51);
    if ((D_00FC0E48 != 1) || ((temp_v1 = M2C_FIELD(D_00F22E90, u32 *, 0x70), var_v0 = temp_v1 < 3U, (var_v0 == 0)) && (var_v0 = 8, (temp_v1 != 8)))) {
        return func_0012ccb0(3);
    }
    return var_v0;
}

s32 func_00f20670(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 0x51) {
        func_00f200a0(2);
    }
    return 0;
}

void func_00f20eb8(void) {
    s32 sp[4];
    f32 temp_f1;

    if ((D_00FC1A50 < 0xA) && (temp_f1 = D_00FC1A4C - D_002BBDFC, D_00FC1A4C = temp_f1, (temp_f1 <= 0.0f))) {
        D_00FC1A4C = temp_f1 + 4.0f;
        func_00f20cb8(sp);
        if (M2C_FIELD(sp, M2C_UNK *, 0x0) == 0) {
            D_00FC1A48 = 0;
            return;
        }
        func_00f20c68(sp);
        D_00FC1A50 += 1;
    }
}

void func_00f20f58(void) {
    D_00FC1A48 = 0;
    D_00FC1A4C = 4.0f;
    D_00FC1A50 = 0;
}

void func_00f20fc0(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x30);
    M2C_FIELD(arg0, s32 *, 0) = 0;
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
        M2C_FIELD(arg0, void **, 0x30) = NULL;
    }
}

s32 func_00f21450(void) {
    s32 *var_s0;
    s32 var_s1;
    s32 var_v0;

    var_v0 = 4;
    if (D_00FC0E48 != 0x65) {
        var_s1 = 9;
        var_s0 = &D_00FC1A60;
        do {
            if (*var_s0 != 0) {
                func_00f20fe8(var_s0);
            }
            var_s1 -= 1;
            var_s0 += 16;
        } while (var_s1 >= 0);
        var_v0 = 0;
    }
    return var_v0;
}

s32 func_00f214b8(void) {
    s32 *var_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_v0;

    var_a1 = 0;
    var_a0 = &D_00FC1A60;
loop_1:
    temp_v1 = *var_a0;
    var_a0 += 16;
    var_v0 = 1;
    if (temp_v1 != 0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 0xA) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

void func_00f21530(s32 arg0, s32 arg1, s32 arg2) {
    memset(arg0, 0, 0x10);
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
}

s32 func_00f21a98(void) {
    return D_00FC1CE0[62] - D_00FC1CE0[63];
}

void func_00f21b50(s32 arg0) {
    void *temp_a0;

    temp_a0 = *func_00147ed8(D_00F22E98, 0x11, 0x4E20, arg0 + 0x10);
    M2C_FIELD(temp_a0, f32 *, 4) = (f32) (M2C_FIELD(temp_a0, f32 *, 4) - D_00FC0D98);
}

void func_00f21fc0(void *arg0) {
    M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg0, f32 *, 4) + D_002BBDFC);
    if (func_00f223a8(arg0 + 0x28, D_002BBDFC) != 0) {
        M2C_FIELD(arg0, s32 *, 0) = 0;
    }
}

void func_00f221a0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_00f22078();
    if (temp_v0 != 0) {
        sceVu0CopyVector(temp_v0 + 0x10, arg0);
    }
}

void func_00f22230(s32 arg0) {
    func_00f21ab0(3, arg0, 1e+02f);
}

s32 func_00f22290(void) {
    s32 *var_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_v0;

    var_a1 = 0;
    var_a0 = &D_00FC1DE0;
loop_1:
    temp_v1 = *var_a0;
    var_a0 += 104;
    var_v0 = 1;
    if (temp_v1 != 0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 0xA) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

s32 func_00f229f0(void) {
    s32 *var_s0;
    s32 var_s1;
    s32 var_v0;

    var_v0 = 4;
    if (D_00FC0E48 != 0x65) {
        var_s1 = 9;
        var_s0 = &D_00FC2E20;
        do {
            if (*var_s0 != 0) {
                func_00f22760(var_s0);
            }
            var_s1 -= 1;
            var_s0 += 5;
        } while (var_s1 >= 0);
        var_v0 = 0;
    }
    return var_v0;
}

void func_00f22b80(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg2;
    sceVu0CopyVector(arg1, arg3);
}
