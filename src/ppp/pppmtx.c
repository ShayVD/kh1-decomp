/* ppp's rotation matrices (docs/modules.md "Session 49"),
 * 0x001a50d0-0x001a5520: func_001a50d0 / func_001a5150 / func_001a51d0 build
 * a rotation about X / Y / Z from a 16-bit angle (0x10000 a turn) through the
 * sine table D_003732D0 (4096 entries, the cosine a quarter turn on);
 * func_001a5250 ... func_001a5490 multiply the three for one Euler order
 * (XZY, YZX, YXZ, ZXY, ZYX, as the pppMatrix*Frame / pppRyjMatrixWorld*
 * classes that call them are named) from the angles a[0..2].
 * Read from the code, not proved by a boot. */
#include "common.h"

typedef f32 Mtx[4][4];
void sceVu0MulMatrix(Mtx, Mtx, Mtx);
extern f32 D_003732D0[]; /* sine table, 4096 entries per turn */

void func_001a50d0(f32 m[4][4], u32 a) {
    f32 s = D_003732D0[(a >> 4) & 0xFFF];
    f32 c = D_003732D0[((a + 0x4000) >> 4) & 0xFFF];

    m[0][0] = 1.0f;
    m[1][0] = 0.0f;
    m[2][0] = 0.0f;
    m[3][0] = 0.0f;
    m[0][1] = 0.0f;
    m[1][1] = c;
    m[2][1] = -s;
    m[3][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][2] = s;
    m[2][2] = c;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

void func_001a5150(f32 m[4][4], u32 a) {
    f32 s = D_003732D0[(a >> 4) & 0xFFF];
    f32 c = D_003732D0[((a + 0x4000) >> 4) & 0xFFF];

    m[0][0] = c;
    m[1][0] = 0.0f;
    m[2][0] = s;
    m[3][0] = 0.0f;
    m[0][1] = 0.0f;
    m[1][1] = 1.0f;
    m[2][1] = 0.0f;
    m[3][1] = 0.0f;
    m[0][2] = -s;
    m[1][2] = 0.0f;
    m[2][2] = c;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

void func_001a51d0(f32 m[4][4], u32 a) {
    f32 s = D_003732D0[(a >> 4) & 0xFFF];
    f32 c = D_003732D0[((a + 0x4000) >> 4) & 0xFFF];

    m[0][0] = c;
    m[1][0] = -s;
    m[2][0] = 0.0f;
    m[3][0] = 0.0f;
    m[0][1] = s;
    m[1][1] = c;
    m[2][1] = 0.0f;
    m[3][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][2] = 0.0f;
    m[2][2] = 1.0f;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

/* XZY */
void func_001a5250(Mtx out, s32 *a) {
    Mtx m[4];
    func_001a5150(m[0], a[1]);
    func_001a51d0(m[1], a[2]);
    sceVu0MulMatrix(m[2], m[0], m[1]);
    func_001a50d0(m[3], a[0]);
    sceVu0MulMatrix(out, m[2], m[3]);
}

/* YZX */
void func_001a52e0(Mtx out, s32 *a) {
    Mtx m[4];
    func_001a50d0(m[0], a[0]);
    func_001a51d0(m[1], a[2]);
    sceVu0MulMatrix(m[2], m[0], m[1]);
    func_001a5150(m[3], a[1]);
    sceVu0MulMatrix(out, m[2], m[3]);
}

/* YXZ */
void func_001a5370(Mtx out, s32 *a) {
    Mtx m[4];
    func_001a51d0(m[0], a[2]);
    func_001a50d0(m[1], a[0]);
    sceVu0MulMatrix(m[2], m[0], m[1]);
    func_001a5150(m[3], a[1]);
    sceVu0MulMatrix(out, m[2], m[3]);
}

/* ZXY */
void func_001a5400(Mtx out, s32 *a) {
    Mtx m[4];
    func_001a5150(m[0], a[1]);
    func_001a50d0(m[1], a[0]);
    sceVu0MulMatrix(m[2], m[0], m[1]);
    func_001a51d0(m[3], a[2]);
    sceVu0MulMatrix(out, m[2], m[3]);
}

/* ZYX */
void func_001a5490(Mtx out, s32 *a) {
    Mtx m[4];
    func_001a50d0(m[0], a[0]);
    func_001a5150(m[1], a[1]);
    sceVu0MulMatrix(m[2], m[0], m[1]);
    func_001a51d0(m[3], a[2]);
    sceVu0MulMatrix(out, m[2], m[3]);
}

#include "data/data_0037.h"
