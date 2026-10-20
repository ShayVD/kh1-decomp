#include "common.h"
typedef f32 Mtx9[4][4];
typedef struct {
    s32 x0; s32 x4; s32 x8; s32 xc; s32 x10; void *x14; u8 x18[4]; s32 x1c;
    u8 pad20[8]; s32 x28, x2c; s32 x30; s8 c34[4]; s8 c38[4]; s32 x3c;
    s8 c40[8]; s32 x48; s32 x4c; s32 x50; u8 pad54[0x60 - 0x54]; u64 x60, x68;
    f32 x70; s32 x74; s32 x78; u8 pad7c[4]; Mtx9 x80; f32 (*xc0)[4]; u8 padc4[0xd0 - 0xc4];
} E9;
typedef struct { u8 pad[0x48e]; u8 x48e[11]; } G9;
extern E9 D_003F3530[];
extern G9 *D_00304BE8;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern u8 D_00425CE0[];
void func_00162070(s32, void *, void *, void *);
void func_001321a0(void *, s32);
void func_00132220(s32, s32);
void func_00167ac0(s32, s32, s32);
s32 func_001301d8(void *, s32, s32, s32);
void func_001655e0(void *, s32, s32, f32);
s32 func_00162348(s32, s32);
s32 func_00162368(s32, s32);
s32 func_00162338(s32);
void func_00121e28(s32, void *);
Mtx9 *func_001623e0(s32);
void func_001625c8(Mtx9 *, Mtx9 *);
void sceVu0MulMatrix(void *, void *, void *);

void func_0020a248(s32 idx) {
    E9 *e = &D_003F3530[idx];
    s32 r, i, j, k, fl;
    Mtx9 *m;
    func_00162070(e->x0, &e->x10, &e->x1c, &e->x14);
    func_001321a0(e->x18, e->x8);
    func_00132220(e->x14, e->x8);
    func_00167ac0(e->x14, 0, 0);
    e->x70 = 0;
    e->x28 = 0;
    e->x30 = -1;
    e->x2c = 0;
    e->c38[0] = -128;
    e->c38[3] = -1;
    e->c38[1] = -128;
    e->c34[0] = 96;
    e->c38[2] = -128;
    e->c34[1] = 96;
    e->x48 = 0;
    e->c34[2] = 96;
    e->x50 = 0;
    e->c34[3] = -128;
    e->c40[0] = -128;
    e->c40[1] = -128;
    e->c40[7] = -1;
    e->x60 = 0x31000070;
    e->c40[2] = -128;
    e->c40[3] = -128;
    e->c40[4] = -128;
    e->x68 = 0x800d0;
    e->c40[5] = -128;
    e->c40[6] = -128;
    e->x3c = 0;
    func_001655e0(D_00425CE0, e->x14, func_001301d8(e->x18, 1, 0, 0), e->x70);
    r = func_00162348(e->x14, 52);
    if (r >= 0) {
        fl = 0;
        e->x78 = func_00162368(e->x14, r);
        e->x74 = func_00162338(e->x14) - e->x78;
        func_00121e28(e->x74 << 6, &e->xc0);
        m = func_001623e0(e->x14) + e->x78;
        func_001625c8(m, &e->x80);
        if (D_00304BE8->x48e[idx] == 2) {
            if (D_002BC128 == 9 || (D_002BC128 == 16 && D_002BC130 == 21)) fl = 1;
        }
        for (i = 0; i < e->x74; i++) {
            sceVu0MulMatrix(e->xc0 + i * 4, &e->x80, m + i);
            if (fl) {
                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 3; k++) {
                        f32 *d = &e->xc0[i * 4 + j][k];
                        if (j == k) *d = 1.0f;
                        else *d = 0;
                    }
                }
            }
        }
    } else {
        e->x74 = 0;
        e->x78 = -1;
        e->xc0 = 0;
    }
}
#include "data/data_002B.h"
