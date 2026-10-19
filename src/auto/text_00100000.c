/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK D_00F20000(M2C_UNK, M2C_UNK);
M2C_UNK func_00100580(M2C_UNK, M2C_UNK *);
M2C_UNK func_00101660();
M2C_UNK func_00104480(M2C_UNK, M2C_UNK *);
M2C_UNK func_001044c0(M2C_UNK *);
M2C_UNK func_00104528();
M2C_UNK func_001047c8();
M2C_UNK func_00104f10(s32, s32);
M2C_UNK func_00106c78();
M2C_UNK func_00107ec0(M2C_UNK *);
M2C_UNK func_00109230(void *, void *);
M2C_UNK func_0010e3f0(void *);
M2C_UNK func_0010f658();
M2C_UNK func_0010fce8(s32, s32);
M2C_UNK func_00111170(s32);
M2C_UNK func_0011a978();
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
M2C_UNK func_00121ee0(s32);
M2C_UNK func_001559f0(M2C_UNK, M2C_UNK);
M2C_UNK func_00176250();
M2C_UNK func_00176290();
M2C_UNK func_002581a0(s32);
M2C_UNK func_002583e0(M2C_UNK);
M2C_UNK func_00265bc0(M2C_UNK, M2C_UNK);
M2C_UNK func_00266f38(s32, s32);
M2C_UNK func_00267930(M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_0029B280;
extern M2C_UNK D_002B74D0;
extern M2C_UNK D_002B74E0;
extern M2C_UNK D_002B74F0;
extern M2C_UNK D_004941D0;
extern M2C_UNK D_00494210;
extern M2C_UNK D_00494250;
extern M2C_UNK D_00494290;
extern M2C_UNK D_004942D0;
extern M2C_UNK D_00494320;
M2C_UNK D_004943A0[0x11] ALIGNED(32);
extern M2C_UNK D_00494878;
extern M2C_UNK D_004951D0;
f32 D_004943E4 ALIGNED(4);
extern f32 D_00494A70;
extern f32 D_00494A74;
extern s32 D_002A6258;
extern s32 D_002A6B84;
extern s32 D_002B647C;
extern s32 D_002B6484;
extern s32 D_002BC0A8;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC734;
extern s32 D_002BC738;
extern s32 D_002BCDD8;
extern s32 D_00494890;
extern s32 D_00494A94;
extern s32 D_00494A98;
extern s32 D_00495260;
extern s32 D_004D5AF4;
extern s32 D_004D5AF8;
extern s32 D_004D5AFC;
extern void *D_002A6238;
s32 func_00111090();

s32 func_001001f8(void) {
    func_00265bc0(0, 0);
    func_00106c78();
    return 0;
}

void func_00100610(void) {
    func_00100580(0, &D_004941D0);
    func_00100580(1, &D_00494210);
    func_00100580(3, &D_00494250);
    func_00100580(6, &D_00494290);
    func_00100580(7, &D_004942D0);
}

void func_00100768(void) {
    func_00104480(-1, &D_0029B280);
    func_00104480(-1, &D_00494320);
    M2C_FIELD(&D_00494320, s32 *, 0x44) = 0;
}

void func_001007b0(void) {
    func_00104480(-1, &D_004943A0);
    M2C_FIELD(&D_004943A0, s32 *, 0x44) = 0;
}

void func_001007e8(void) {
    func_001044c0(&D_0029B280);
    func_00107ec0(&D_0029B280);
}

void func_001008d8(f32 fparg0) {
    D_004943E4 = fparg0;
}

void func_00100ab0(void) {
    D_002BC0A8 |= 3;
    func_00176250();
    func_00176290();
}

void func_00102a28(void) {
    func_0011f130(&D_00494878, 0);
}

void func_00103810(void) {
    D_002BC734 = 1;
    D_00494890 = 0;
}

void func_00104268(f32 fparg0, f32 fparg1) {
    D_002BC738 = 1;
    D_00494A70 = fparg0;
    D_00494A74 = fparg1;
}

void func_00105710(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *var_a2;

    var_a3 = D_002A6258;
    if (var_a3 > 0) {
        var_a2 = D_002A6238;
        do {
            var_a3 -= 1;
            if (M2C_FIELD(var_a2, u8 *, 0xB) == arg0) {
                M2C_FIELD(var_a2, s32 *, 0x10) = (s32) ((M2C_FIELD(var_a2, s32 *, 0x10) & ~0xF0) | ((arg1 & 0xF) * 0x10));
            }
            var_a2 += 0x14;
        } while (var_a3 != 0);
    }
}

void func_00105a70(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        func_001047c8();
        func_00104f10(arg1, arg2);
        func_00104528();
        return;
    }
    func_0011a978();
}

void func_00105d38(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *var_a2;

    var_a3 = D_002A6258;
    if (var_a3 > 0) {
        var_a2 = D_002A6238;
        do {
            var_a3 -= 1;
            if (M2C_FIELD(var_a2, u8 *, 0xB) == arg0) {
                M2C_FIELD(var_a2, s32 *, 0x10) = (s32) ((M2C_FIELD(var_a2, s32 *, 0x10) & ~0x7800) | ((arg1 & 0xF) << 0xB));
            }
            var_a2 += 0x14;
        } while (var_a3 != 0);
    }
}

void func_00106900(void) {
    D_002B647C = 0;
}

void func_00106b18(s32 arg0) {
    func_002583e0(0);
    func_00265bc0(0, 0);
    func_00266f38(D_002A6B84, arg0);
}

s32 func_00106ca8(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_00494A98 * 0x10;
    D_00494A98 += arg0;
    return D_00494A94 + temp_v0;
}

void func_00108cd0(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x68) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x6C) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x70) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x74) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
}

void func_00109268(void) {
    D_002B6484 = 0;
}

void func_00109278(void) {
    D_002B6484 = 1;
}

void func_00109588(void) {
    D_002BCDD8 = 0;
    func_00101660();
    func_001559f0(0, 0x40);
}

void func_00109630(void) {
    func_002583e0(2);
    D_00F20000(0, 0);
}

void func_0010bd90(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x18) != 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = arg1;
        M2C_FIELD(arg0, s32 *, 0x18) = 3;
        func_0010e3f0(arg0 + 0x80);
    }
}

void func_0010c040(void) {
    func_00267930(&D_004951D0, &D_002B74D0, &D_002B74E0, &D_002B74F0);
}

void func_0010c150(void) {
    func_002581a0(D_00495260);
}

void func_0010c410(s32 arg0) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + 0x10;
    temp_a0_2 = temp_a0 + M2C_FIELD(temp_a0, u16 *, 0xC);
    func_00109230(temp_a0_2, temp_a0_2 + M2C_FIELD(temp_a0, s32 *, 8));
}

s32 func_0010d350(s8 *arg0) {
    s32 var_v1;
    s8 *var_a0;

    var_a0 = arg0;
    var_v1 = 0;
    if (*var_a0 != 0) {
        do {
            var_a0 += 1;
            var_v1 += 1;
        } while (*var_a0 != 0);
    }
    return var_v1;
}

void func_0010f520(void) {
    if (D_004D5AF4 != 0) {
        func_00121ee0(D_004D5AF4);
    }
}

void func_0010f558(s32 arg0, void *arg1, s32 arg2) {
    D_004D5AF8 = arg2 - 1;
    D_004D5AF4 = 0;
    D_004D5AFC = 0;
    M2C_FIELD(arg1, s32 *, 0xA8) = arg0;
}

void func_0010f8d0(s32 arg0) {
    func_0010f658();
    if (func_00111090() != 0) {
        func_00111170(arg0);
    }
}

void func_0010fd18(void) {
    func_0010fce8(D_002BC128, D_002BC130);
}
