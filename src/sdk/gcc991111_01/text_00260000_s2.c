#include "common.h"
void sceVu0UnitMatrix(f32 m[4][4]);
void sceVu0MulMatrix(f32 m0[4][4], f32 m1[4][4], f32 m2[4][4]);

void func_00267b08(f32 m[4][4], f32 scrz, f32 ax, f32 ay, f32 cx, f32 cy,
                   f32 zmin, f32 zmax, f32 nearz, f32 farz) {
    f32 mt[4][4];
    f32 az, cz;
    cz = (-zmax * nearz + zmin * farz) / (-nearz + farz);
    az = farz * nearz * (-zmin + zmax) / (-nearz + farz);
    sceVu0UnitMatrix(m);
    m[0][0] = scrz;
    m[1][1] = scrz;
    m[2][2] = 0.0f;
    m[3][2] = 1.0f;
    m[2][3] = 1.0f;
    m[3][3] = 0.0f;
    sceVu0UnitMatrix(mt);
    mt[0][0] = ax;
    mt[1][1] = ay;
    mt[2][2] = az;
    mt[3][0] = cx;
    mt[3][1] = cy;
    mt[3][2] = cz;
    sceVu0MulMatrix(m, mt, m);
}
