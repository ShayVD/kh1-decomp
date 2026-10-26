/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001763f0(s32);
M2C_UNK func_001bb7c8(M2C_UNK *, s32);
M2C_UNK func_001be820(M2C_UNK *, M2C_UNK);
M2C_UNK func_001bef40(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_00f2cc20();
M2C_UNK func_00f2cf78(s32);
M2C_UNK func_00f3e030(M2C_UNK *, s32);
M2C_UNK func_00f68a40(s32);
M2C_UNK sceVu0ApplyMatrix(M2C_UNK *, s32, void *);
M2C_UNK sceVu0CopyMatrix(s32, s32);
M2C_UNK sceVu0CopyVector(s32, M2C_UNK *);
M2C_UNK sceVu0RotMatrix(s32, s32, M2C_UNK *);
M2C_UNK sceVu0TransMatrix(void *, s32, f32 *);
M2C_UNK sceVu0UnitMatrix(s32);
extern M2C_UNK D_00F8C530;
extern M2C_UNK D_00F9A5C0;
extern M2C_UNK D_00F9B1E8;
extern M2C_UNK D_00F9B2A8;
extern M2C_UNK D_00FB71D0;
extern M2C_UNK D_00FB71D8;
extern M2C_UNK D_00FB71F0;
extern M2C_UNK D_00FBBA70;
extern M2C_UNK D_00FBDA80;
extern M2C_UNK D_00FBDA90;
extern M2C_UNK D_00FCE040;
extern M2C_UNK D_00FCE340;
extern M2C_UNK D_00FCE350;
extern M2C_UNK D_00FDF3D0;
extern M2C_UNK D_00FDF7D8;
extern f32 D_002BBDEC;
extern f32 D_00F8C144;
extern f32 D_00F9B1D0;
extern f32 D_00F9B1D4;
extern f32 D_00F9B1D8;
extern s32 D_00F850F4;
extern s32 D_00F8C120;
extern s32 D_00F8C16C;
extern s32 D_00F8C220;
extern s32 D_00F8C224;
extern s32 D_00F8C22C;
extern s32 D_00F8C280;
extern s32 D_00F8C2D0;
extern s32 D_00F8C2D4;
extern s32 D_00F8C2E4;
extern s32 D_00F8C2FC;
extern s32 D_00F9A534;
extern s32 D_00FBB5C0;
extern s32 D_00FBB5C4;
extern s32 D_00FBBA50;
extern s32 D_00FBBA58;
extern s32 D_00FBBA5C;
extern s32 D_00FBBA60;
extern s32 D_00FBBA68;
extern s32 D_00FBEBB8;
extern s32 D_00FCE380;
extern s32 D_00FDF7D0;
extern s32 D_00FDFFD8;
extern void *D_00F864C0;
s32 func_001623e0(s32);
s32 func_001ba9d8(s32);
s32 func_00f20030();
void *func_00f3f260(s32, s32);
void func_0011d1a8(s32, M2C_UNK, M2C_UNK);
void func_001bfac8();
void func_00241c60(M2C_UNK, M2C_UNK);
void func_00242b68(M2C_UNK);
void func_00f2d480();
void func_00f300a8();
void func_00f30210();
void func_00f30638(M2C_UNK);
void func_00f33e48(s32, M2C_UNK);
void func_00f355a8();
void func_00f38dc0(s32);
void func_00f39058(s32, s32, s32);

void func_00f30040(void) {
    if (D_00F8C2D0 >= 0) {
        func_00f2cf78(D_00F8C2D0);
    }
    if (D_00F8C2D4 >= 0) {
        func_00f2cf78(D_00F8C2D4);
    }
    D_00F8C2D0 = -1;
    D_00F8C2D4 = -1;
}

void func_00f30208(void) {

}

void func_00f30628(void) {
    D_00F8C16C = 0;
}

void func_00f30938(void) {
    D_00F8C144 = 1.0f;
    D_00FBEBB8 = 0;
    func_00242b68(4);
    func_00f33e48(func_001ba9d8(D_00F8C120), 1);
    func_00f30638(1);
    func_00f2d480();
    if (D_00F8C280 != 0) {
        func_00f300a8();
    }
    func_00f30210();
    func_00241c60(0, 4);
    D_00F850F4 = 1;
}

void func_00f309d0(s32 arg0) {
    D_00F8C220 = arg0;
}

s32 func_00f309e0(void) {
    return D_00FBBA50;
}

void func_00f309f0(void) {
    if (D_00F850F4 != 0) {
        func_00f2cc20();
    }
}

void func_00f30a80(void) {
    s32 temp_v0;

    temp_v0 = D_00FBBA58 + 0xA;
    D_00FBBA58 = temp_v0;
    if (D_00FBBA5C < temp_v0) {
        D_00FBBA58 = D_00FBBA5C;
    }
}

void func_00f30ab0(void) {
    s32 temp_v1;

    temp_v1 = D_00FBBA60 + 1;
    D_00FBBA60 = temp_v1;
    if (temp_v1 >= 6) {
        D_00FBBA60 = 5;
    }
}

void func_00f32318(void *arg0, void *arg1, f32 fparg0) {
    M2C_FIELD(&D_00FBDA80, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0);
    M2C_FIELD(&D_00FBDA80, f32 *, 4) = (f32) M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(&D_00FBDA80, f32 *, 8) = (f32) M2C_FIELD(arg0, f32 *, 8);
    M2C_FIELD(&D_00FBDA80, f32 *, 0xC) = (f32) M2C_FIELD(arg0, f32 *, 0xC);
    M2C_FIELD(&D_00FBDA90, f32 *, 0) = (f32) M2C_FIELD(arg1, f32 *, 0);
    M2C_FIELD(&D_00FBDA90, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(&D_00FBDA90, f32 *, 8) = (f32) M2C_FIELD(arg1, f32 *, 8);
    M2C_FIELD(&D_00FBDA90, f32 *, 0xC) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
    D_00F8C144 = fparg0;
}

s32 func_00f32378(void *arg0) {
    f32 temp_f1;
    s32 var_v0;

    temp_f1 = M2C_FIELD(arg0, f32 *, 8);
    var_v0 = 0;
    if (temp_f1 >= 3e+03f) {
        var_v0 = 1;
        if (!(temp_f1 <= 3e+04f)) {
            var_v0 = 0;
        }
    }
    return var_v0;
}

void func_00f324c0(s32 arg0) {
    D_00FBB5C4 = arg0;
}

s32 func_00f33a90(void) {
    return D_00FBBA68;
}

void func_00f344e0(s32 arg0) {
    D_00F8C224 = arg0;
}

void *func_00f35058(s32 arg0) {
    return (s8 *)&D_00FBBA70 + (arg0 * 0x10);
}

s32 func_00f35070(void) {
    return D_00F8C22C;
}

void func_00f35398(void) {
    D_00FBB5C0 = 1;
}

s32 func_00f35798(s32 arg0) {
    return *(M2C_UNK *)((s8 *)(s8 *)&D_00FCE040 + (arg0 * 4));
}

void func_00f357b0(void) {
    func_00f355a8();
    M2C_FIELD(&D_00FCE340, s32 *, 0) = 0;
    M2C_FIELD(&D_00FCE340, s32 *, 4) = 0;
    M2C_FIELD(&D_00FCE340, s32 *, 8) = 0;
    M2C_FIELD(&D_00FCE340, f32 *, 0xC) = 1.0f;
    M2C_FIELD(&D_00FCE340, s32 *, 0x10) = 0;
    M2C_FIELD(&D_00FCE340, s32 *, 0x14) = 0;
    M2C_FIELD(&D_00FCE340, s32 *, 0x18) = 0;
    M2C_FIELD(&D_00FCE340, f32 *, 0x1C) = 1.0f;
}

s32 func_00f358d8(s32 arg0, s32 arg1) {
    switch (arg0) {                                 /* irregular */
    case 0x80:
        sceVu0UnitMatrix(arg1);
        sceVu0RotMatrix(arg1, arg1, &D_00FCE340);
block_7:
        return 1;
    case 0x8D:
        sceVu0UnitMatrix(arg1);
        sceVu0RotMatrix(arg1, arg1, &D_00FCE350);
        goto block_7;
    default:
        return 0;
    }
}

s32 func_00f35960(void) {
    return D_00F8C2E4;
}

void func_00f362f8(void) {
    D_00F8C2FC = 0;
}

void func_00f36308(s32 arg0) {
    *(M2C_UNK *)((s8 *)(s8 *)&D_00FDF3D0 + (D_00F8C2FC * 4)) = arg0;
    D_00F8C2FC += 1;
}

void func_00f36330(void) {
    s8 *var_a0;
    s8 *var_s0;
    s32 var_s1;

    var_s0 = &D_00F8C530;
    var_s1 = 0xFF;
    var_a0 = &D_00F8C530;
    do {
        var_a0 = var_s0;
        func_001be820(var_a0, 0xE0);
        var_s1 -= 1;
        var_s0 += 0xE0;
    } while (var_s1 >= 0);
}

void *func_00f363c0(s32 arg0) {
    return (s8 *)&D_00F8C530 + (arg0 * 0xE0);
}

void func_00f374b0(s32 arg0, void *arg1) {
    s32 sp[20];    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg1, s32 *, 0x18);
    M2C_FIELD(sp, f32 *, 0x40) = (f32) M2C_FIELD(arg1, s32 *, 0x1C) * 1e+02f;
    M2C_FIELD(sp, f32 *, 0x44) = (f32) M2C_FIELD(arg1, s32 *, 0x20) * 1e+02f;
    M2C_FIELD(sp, f32 *, 0x48) = (f32) M2C_FIELD(arg1, s32 *, 0x24) * 1e+02f;
    M2C_FIELD(sp, f32 *, 0x4C) = 1.0f;
    sceVu0TransMatrix(sp, arg0, &M2C_FIELD(sp, f32 *, 0x40));
    func_00f3e030(&M2C_FIELD(sp, M2C_UNK *, 0x30), temp_s0);
}

void func_00f37538(void *arg0, void *arg1) {
    s32 temp_s0;
    void *temp_v0;

    temp_s0 = M2C_FIELD(arg1, s32 *, 0x18);
    temp_v0 = func_00f3f260(M2C_FIELD(arg0, s32 *, 0xE4), M2C_FIELD(D_00F864C0, s32 *, 0x540));
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s16 *, 0x24) = (s16) temp_s0;
    }
}

void func_00f37ea0(s32 arg0, s32 arg1) {
    s32 sp[8];    s32 temp_a1;
    s32 temp_s0;

    temp_a1 = func_001623e0(func_00f20030());
    switch (arg0) {                                 /* irregular */
    case 0:
        sceVu0CopyMatrix(arg1, temp_a1 + 0x2200);
        return;
    case 1:
        sceVu0CopyMatrix(arg1, temp_a1 + 0xD40);
        break;
    case 2:
        sceVu0CopyMatrix(arg1, temp_a1 + 0x1FC0);
        break;
    case 3:
        temp_s0 = temp_a1 + 0x1100;
        M2C_FIELD(sp, f32 *, 0x0) = 4.1e+02f;
        M2C_FIELD(sp, f32 *, 0x4) = -1354.0f;
        M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
        M2C_FIELD(sp, s32 *, 0x8) = 0;
        sceVu0ApplyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x10), temp_s0, sp);
        sceVu0CopyMatrix(arg1, temp_s0);
        sceVu0CopyVector(arg1 + 0x30, &M2C_FIELD(sp, M2C_UNK *, 0x10));
        break;
    }
}

void func_00f37fc8(s32 arg0, s32 arg1) {
    s32 temp_a1;

    temp_a1 = func_001623e0(func_00f20030());
    switch (arg0) {                                 /* irregular */
    case 0:
        sceVu0CopyMatrix(arg1, temp_a1 + 0x2D80);
        return;
    case 1:
        sceVu0CopyMatrix(arg1, temp_a1 + 0x2CC0);
        return;
    case 2:
        sceVu0CopyMatrix(arg1, temp_a1 + 0x2C00);
        return;
    case 3:
        sceVu0CopyMatrix(arg1, temp_a1 + 0x2B40);
        return;
    }
}

void func_00f38b70(s32 arg0, s32 arg1) {
    s32 sp[4];    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg1, s32 *, 0x18);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_00f38dc0(arg1);
        return;
    case 1:
        M2C_FIELD(sp, f32 *, 0x0) = (f32) M2C_FIELD(arg1, s32 *, 0x1C) * 1e+02f;
        M2C_FIELD(sp, f32 *, 0x4) = (f32) M2C_FIELD(arg1, s32 *, 0x20) * 1e+02f;
        M2C_FIELD(sp, f32 *, 0x8) = (f32) M2C_FIELD(arg1, s32 *, 0x24) * 1e+02f;
        func_00f39058(arg0, (s32) sp, M2C_FIELD(arg1, s32 *, 0x28));
        break;
    }
}

void func_00f397f8(void *arg0, void *arg1, s32 arg2) {
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f2;
    s32 temp_f0;
    s32 var_s1;

    temp_f20 = M2C_FIELD(arg0, f32 *, 0xF8);
    M2C_FIELD(arg0, s32 *, 0x100) = (s32) (M2C_FIELD(arg0, s32 *, 0x100) | 1);
    temp_f21 = ((f32) M2C_FIELD(arg1, s32 *, 0x1C) * 1e+02f) / 3e+01f;
    temp_f0 = (s32) ((f32) M2C_FIELD(arg1, s32 *, 0x18) / D_002BBDEC);
    if ((arg2 != 0) && (var_s1 = 0, (temp_f0 > 0))) {
loop_2:
        if (M2C_FIELD(arg0, s32 *, 0xFC) != 0) {
            if ((M2C_FIELD(arg0, s32 *, 0x100) & 1) && (M2C_FIELD(arg0, s32 *, 0xE0) != 0)) {
                temp_f2 = (f32) var_s1;
                var_s1 += 1;
                M2C_FIELD(arg0, f32 *, 0xF8) = (f32) ((((temp_f21 - temp_f20) * temp_f2) / (f32) temp_f0) + temp_f20);
                func_001bfac8();
                if (var_s1 >= temp_f0) {
                    goto block_6;
                }
                goto loop_2;
            }
        } else {
            goto block_6;
        }
    } else {
block_6:
        M2C_FIELD(arg0, f32 *, 0xF8) = temp_f21;
    }
}

void func_00f39910(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x104) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
}

void func_00f39920(void *arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x100);
    M2C_FIELD(arg0, f32 *, 0xF8) = (f32) (((f32) M2C_FIELD(arg1, s32 *, 0x18) * 1e+02f) / 3e+01f);
    if (temp_v0 & 1) {
        M2C_FIELD(arg0, s32 *, 0x100) = (s32) (temp_v0 ^ 1);
    }
}

s32 func_00f3a1d8(void *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    s32 var_v0;

    temp_f0 = M2C_FIELD(arg0, f32 *, 0);
    var_v0 = 0;
    if (!(temp_f0 < -3e+04f) && !(temp_f0 > 3e+04f)) {
        temp_f0_2 = M2C_FIELD(arg0, f32 *, 4);
        if (!(temp_f0_2 < -3e+04f) && !(temp_f0_2 > 3e+04f)) {
            temp_f1 = M2C_FIELD(arg0, f32 *, 8);
            if (!(temp_f1 < -2e+04f)) {
                var_v0 = 1;
                if (temp_f1 > 4e+04f) {
                    var_v0 = 0;
                }
            }
        }
    }
    return var_v0;
}

s32 func_00f3b080(void) {
    if (D_00FCE380 < 0) {
        return 1;
    }
    return 0;
}

s32 func_00f3b090(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_00FCE380 - arg0;
    D_00FCE380 = temp_v0;
    if (temp_v0 < 0) {
        return 1;
    }
    return 0;
}

f32 func_00f3b318(s32 arg0) {
    return (f32) *(u8 *)((s8 *)(s8 *)&D_00FDF7D8 + (M2C_FIELD(((arg0 * 0x110) + D_00FDFFD8), s32 *, 4) & 0x7FF)) * 0.25f;
}

void func_00f3b360(s32 arg0) {
    D_00FDF7D0 = arg0;
}

s32 func_00f3b370(void) {
    return D_00FDF7D0;
}

s32 func_00f3b460(s32 arg0) {
    return D_00FDFFD8 + (arg0 * 0x110);
}

s32 func_00f3b480(void) {
    return D_00F9A534;
}

void func_00f3b850(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
}

void func_00f3e3a0(void) {
    s8 *var_s0;
    s32 temp_v0;
    s32 var_s1;

    var_s0 = &D_00F9A5C0;
    var_s1 = 0x3F;
    do {
        temp_v0 = M2C_FIELD(var_s0, s32 *, 4);
        if (temp_v0 >= 0) {
            func_00f68a40(temp_v0);
        }
        var_s1 -= 1;
        M2C_FIELD(var_s0, s32 *, 0) = -1;
        M2C_FIELD(var_s0, s32 *, 4) = -1;
        var_s0 += 0x30;
    } while (var_s1 >= 0);
}

M2C_UNK *func_00f3f2c0(void) {
    return &D_00F9B2A8;
}

void func_00f3f2d0(f32 fparg0) {
    D_00F9B1D0 = fparg0;
    D_00F9B1D4 = fparg0;
}

f32 func_00f3f2e8(void) {
    return D_00F9B1D0;
}

void func_00f3f2f8(f32 fparg0) {
    D_00F9B1D8 = fparg0;
}

void func_00f3f358(void) {
    s32 var_s0;

    for (var_s0 = 0xE2C3; var_s0 <= 0xE2CC; var_s0 += 1) {
        func_0011d1a8(var_s0, 0, 0xA0);
    }
}

void func_00f3f3a8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[24];    M2C_UNK **temp_s3;
    s8 *temp_v0;

    temp_s3 = (s8 *)&D_00F9B1E8 + (arg0 * 4);
    temp_v0 = *temp_s3;
    if (temp_v0 != NULL) {
        func_001bef40(&M2C_FIELD(sp, M2C_UNK *, 0x40), temp_v0, &D_00FB71D0);
        func_001bef40(sp, &D_00FB71D8, &M2C_FIELD(sp, M2C_UNK *, 0x40));
        func_001bb7c8(sp, arg1);
        func_001763f0(arg1);
        func_001bef40(&M2C_FIELD(sp, M2C_UNK *, 0x40), *temp_s3, &D_00FB71F0);
        func_001bef40(sp, &D_00FB71D8, &M2C_FIELD(sp, M2C_UNK *, 0x40));
        func_001bb7c8(sp, arg2);
    }
}
