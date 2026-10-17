#include "common.h"

void func_00267c10(f32 m[4][4], f32 *n, f32 lx, f32 ly, f32 lz, s32 flag) {
    if (flag) {
        f32 nx, ny, nz, d;
        nx = n[0];
        ny = n[1];
        nz = n[2];
        d = 1.0f - (lx * nx + ly * ny + lz * nz);
        m[0][0] = lx * nx + d;
        m[1][0] = ly * nx;
        m[2][0] = lz * nx;
        m[3][0] = -nx;
        m[0][1] = lx * ny;
        m[1][1] = ly * ny + d;
        m[2][1] = lz * ny;
        m[3][1] = -ny;
        m[0][2] = lx * nz;
        m[1][2] = ly * nz;
        m[2][2] = lz * nz + d;
        m[3][2] = -nz;
        m[0][3] = lx;
        m[1][3] = ly;
        m[2][3] = lz;
        m[3][3] = d - 1.0f;
    } else {
        f32 nx, ny, nz, d;
        f32 s;
        nx = n[0];
        ny = n[1];
        nz = n[2];
        d = lx * nx + ly * ny + lz * nz;
        s = -1.0f / d;
        m[0][0] = s * (lx * nx - d);
        m[1][0] = s * (ly * nx);
        m[2][0] = s * (lz * nx);
        m[3][0] = s * -nx;
        m[0][1] = s * (lx * ny);
        m[1][1] = s * (ly * ny - d);
        m[2][1] = s * (lz * ny);
        m[3][1] = s * -ny;
        m[0][2] = s * (lx * nz);
        m[1][2] = s * (ly * nz);
        m[2][2] = s * (lz * nz - d);
        m[3][2] = s * -nz;
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        m[3][3] = s * -d;
    }
}
