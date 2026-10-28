/* xl_limit.x func_00f21e60: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xD0]; OvlMtx m; } Chr;
f32 func_00120bf8(f32 *);
f32 func_00120c18(f32 *);
f32 func_00120c88(f32);
void func_00121fc4(f32 *, f32 *);
void func_001336d8(void);
void func_00133708(void);
f32 atan2f(f32, f32);
f32 sinf(f32);
f32 cosf(f32);
extern f32 D_002BBDFC;
extern OvlMtx D_002C58D0;
extern s32 D_002C5958;
extern OvlVec D_002E2780;
extern OvlVec D_002E2790;
extern OvlVec D_00F23350;
extern OvlVec D_00F23360;
extern OvlVec D_00F23370;
extern OvlVec D_00F23380;
extern OvlVec D_00F23390;
extern OvlVec D_00F233A0;
extern OvlVec D_00F233B0;
extern f32 D_00F23E20;
extern f32 D_00F23E24;
extern f32 D_00F23E28;
extern OvlVec D_00F23E30;
extern OvlVec D_00F23E40;
extern OvlVec D_00F23E50;
extern OvlVec D_00F23E60;
extern f32 D_00F23E70;
extern OvlVec D_00F23E80;
extern OvlVec D_00F23E90;
extern Chr *D_00F23F90;
extern OvlMtx D_00F23FA0;

s32 func_00f21e60(u16 *pad) {
    OvlMtx m;
    f32 t;
    f32 k;
    f32 a;

    if ((D_002C5958 & 0x810000) != 0x10000) {
        goto end;
    }
    if (*pad & 0x10) {
        D_002E2780[3] = D_002E2790[3] = 1.0f;
        sceVu0ApplyMatrix(D_00F23E40, D_00F23FA0, D_002E2780);
        sceVu0ApplyMatrix(D_00F23E50, D_00F23FA0, D_002E2790);
        sceVu0SubVector(D_00F23E30, D_00F23360, D_00F23E40);
        D_00F23E24 = func_00120bf8(D_00F23E30);
        sceVu0SubVector(D_00F23E30, D_00F23E50, D_00F23E40);
        sceVu0Normalize(D_00F23E30, D_00F23E30);
        sceVu0ScaleVector(D_00F23E30, D_00F23E30, D_00F23E24);
        sceVu0AddVector(D_00F23E50, D_00F23E30, D_00F23E40);
        sceVu0SubVector(D_00F23E60, D_00F23E40, D_00F23E50);
        D_00F23E60[1] = 0.0f;
        func_00121fc4(D_00F23E60, D_00F23E60);
        D_00F23E24 = D_00F23E60[3];
        D_00F23E60[3] = 1.0f;
        sceVu0SubVector(D_00F23E30, D_00F23350, D_00F23360);
        D_00F23E28 = func_00120c18(D_00F23E30) - D_00F23E24;
        a = atan2f(D_00F23E40[0] - D_00F23E50[0], D_00F23E40[2] - D_00F23E50[2]);
        D_00F23E20 = func_00120c88(atan2f(D_00F23350[0] - D_00F23360[0], D_00F23350[2] - D_00F23360[2]) - a);
        D_00F23E70 = 0.0f;
        func_001336d8();
    }
    D_00F23E70 += D_002BBDFC;
    t = D_00F23E70;
    if (t < 30.0f) {
        sceVu0CopyVector(D_00F23E80, D_00F23E40);
        sceVu0CopyVector(D_00F23E90, D_00F23E50);
    } else if ((t -= 30.0f) < 70.0f) {
        k = t / 70.0f;
        k = (1.0f - cosf(k * 3.1415928f)) * 0.5f;
        sceVu0InterVector(D_00F23E90, D_00F23360, D_00F23E50, k);
        sceVu0RotMatrixY(m, D_002C58D0, func_00120c88(D_00F23E20 * k));
        sceVu0ApplyMatrix(D_00F23E30, m, D_00F23E60);
        sceVu0ScaleVector(D_00F23E30, D_00F23E30, D_00F23E24 + D_00F23E28 * k);
        sceVu0AddVector(D_00F23E80, D_00F23E90, D_00F23E30);
        D_00F23E80[1] = D_00F23350[1] * k + D_00F23E40[1] * (1.0f - k);
    } else if ((t -= 70.0f) < 54.0f) {
    } else if ((t -= 54.0f) < 10.0f) {
        k = t / 10.0f;
        k = sinf(k * 3.1415928f * 0.5f);
        sceVu0CopyVector(D_00F23E90, D_00F23370);
        sceVu0InterVector(D_00F23E80, D_00F233A0, D_00F23390, k);
    } else if ((t -= 10.0f) < 130.0f) {
        sceVu0CopyVector(D_00F23E90, D_00F23370);
        sceVu0CopyVector(D_00F23E80, D_00F233A0);
    } else if ((t -= 130.0f) < 120.0f) {
        k = t / 120.0f;
        k = cosf(k * 3.1415928f * 0.5f);
        sceVu0InterVector(D_00F23E90, D_00F23370, D_00F23380, k);
        sceVu0InterVector(D_00F23E80, D_00F233A0, D_00F233B0, k);
    } else if (!((t -= 120.0f) < 50.0f)) {
    end:
        func_00133708();
        return 4;
    } else {
        sceVu0CopyVector(D_00F23E90, D_00F23370);
        sceVu0CopyVector(D_00F23E80, D_00F233B0);
    }
    D_00F23E90[3] = 1.0f;
    D_00F23E80[3] = 1.0f;
    sceVu0ApplyMatrix(D_002E2780, D_00F23F90->m, D_00F23E80);
    sceVu0ApplyMatrix(D_002E2790, D_00F23F90->m, D_00F23E90);
    return 0;
}
