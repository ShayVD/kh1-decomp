/* wm.x func_00f38dc0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x1C]; s32 kind; s32 ang; s32 n; } B;
void func_001bfac8(void);
void func_00f37fc8(s32, OvlMtx);
s32 func_00f68770(s32, s32, OvlMtx, s32, s32);
s32 func_00f361d8(void);
s32 func_00f3d758(f32 *, f32);
s32 func_00f31118(s32, s32, s32);
void func_00f68508(s32, s32, f32 *, s32, s32, s32);
void func_00f689f0(s32, OvlMtx);
void func_00f68ab0(s32);
void func_00f68a40(s32);
extern s32 D_00F87048;
extern s32 D_00F87058;

void func_00f38dc0(B *arg0) {
    OvlMtx m0;
    OvlMtx m1;
    OvlMtx m2;
    OvlVec rot;
    OvlVec dir;
    OvlVec vel;
    s32 kind, n, h, i, t;
    f32 ang, sp, g;
    t = arg0->n;
    kind = arg0->kind;
    ang = arg0->ang * 0.017453291f;
    sp = t * 100.0f;
    n = t;
    if (n <= 0) n = 100;
    func_00f37fc8(kind, m0);
    if (kind < 2) ang = -ang;
    rot[1] = ang;
    rot[0] = 0.0f;
    rot[2] = 0.0f;
    rot[3] = 1.0f;
    PlatVu0UnitMatrix(m2);
    PlatVu0RotMatrix(m2, m2, rot);
    dir[0] = 1.0f;
    dir[3] = 1.0f;
    dir[1] = 0.0f;
    dir[2] = 0.0f;
    PlatVu0MulMatrix(m1, m0, m2);
    PlatVu0CopyVector(dir, m1[0]);
    PlatVu0UnitMatrix(m1);
    PlatVu0CopyVector(m1[3], m0[3]);
    h = func_00f68770(8, 1, m1, 0, D_00F87058);
    if (h < 0) return;
    func_00f68770(12, 1, m0, 0, D_00F87058);
    g = 32.666663f;
    vel[0] = dir[0] * sp;
    vel[1] = dir[1] * sp;
    vel[2] = dir[2] * sp;
    for (i = 0; i < n + 10 && func_00f361d8() != 0; i++) {
        if (i < n && func_00f3d758(m1[3], 1000.0f) != 0 && func_00f31118(3, 1, 0) != 0) {
            func_00f68508(49, 1, m1[3], 0, 0, D_00F87048);
            break;
        }
        m1[3][0] += vel[0];
        m1[3][1] += vel[1];
        vel[1] += g;
        m1[3][2] += vel[2];
        func_00f689f0(h, m1);
        if (i == n) func_00f68ab0(h);
        func_001bfac8();
    }
    func_00f68a40(h);
}
