/* wm.x func_00f2c518: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[12]; u8 b12; } A2c518;
typedef struct { u8 b0; u8 b1; u8 b2; u8 b3; u8 pad[12]; f32 v16[4]; f32 v32[4]; u8 pad2[48]; } I2c518;
extern s32 D_00FBB82C, D_00F8C14C, D_00FBDAF0;
extern s32 D_00F8C28C, D_00F8C280, D_00F8C284, D_00F8C288, D_00FBBA54, D_00FBBA5C;
extern f32 D_00F8C140, D_00F8C134, D_00F8C13C, D_00F8C138;
extern f32 D_00FBB7D0[4], D_00FBB7E0[4], D_00FBB7F0[4];
extern s32 D_00F8C154, D_00F8C158, D_00F8C15C, D_00F8C164, D_00F8C160, D_00F8C168;
void func_001bd090(A2c518 *, s32 *);
void *func_001ba9d8(s32);
void func_001bc900(void *, I2c518 *);
void sceVu0CopyVector(f32 *, f32 *);
s32 func_001b9df0(s32);

void func_00f2c518(A2c518 *a) {
    s32 buf[12];
    I2c518 info;
    s32 n;
    s32 i;
    f32 f;

    func_001bd090(a, buf);
    D_00FBB82C = buf[8];
    if (a->b12 != 0 && buf[9] != 0) {
        n = a->b12 - 1;
        func_001bc900(func_001ba9d8(n), &info);
        if (info.b3 != 0 && info.b2 != 0) {
            D_00F8C14C = 1;
            D_00FBDAF0 = n;
        } else {
            D_00F8C14C = 0;
            D_00FBDAF0 = -1;
        }
    } else {
        D_00F8C14C = 0;
    }
    func_001bc900(a, &info);
    D_00F8C28C = buf[7];
    D_00F8C280 = buf[4];
    D_00F8C284 = buf[5];
    D_00F8C288 = buf[6];
    D_00FBBA54 = buf[0];
    D_00FBBA5C = buf[1] * 10;
    f = buf[3] * 1.2f / 80.0f;
    D_00F8C140 = f;
    D_00F8C13C = f * 0.39999998f;
    D_00F8C134 = buf[2] * 1.5f / 100.0f;
    switch (buf[5]) {
    case 1:
        D_00F8C138 = f * 1.5f;
        break;
    case 2:
        D_00F8C138 = f * 2.5f;
        break;
    default:
        D_00F8C138 = D_00F8C140;
        break;
    }
    sceVu0CopyVector(D_00FBB7D0, info.v16);
    sceVu0CopyVector(D_00FBB7E0, info.v32);
    for (i = 0; i < 3; i++) {
        D_00FBB7F0[i] = D_00FBB7D0[i] + (D_00FBB7E0[i] - D_00FBB7D0[i]) * 0.5f;
    }
    D_00FBB7F0[3] = 1.0f;
    D_00F8C154 = func_001b9df0(1);
    D_00F8C158 = func_001b9df0(0);
    D_00F8C15C = func_001b9df0(2);
    D_00F8C164 = func_001b9df0(3);
    D_00F8C160 = func_001b9df0(6);
    D_00F8C168 = 0;
}
