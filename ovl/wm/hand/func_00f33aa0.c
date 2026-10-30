/* wm.x func_00f33aa0: matched by hand. */
#include "ovl.h"

extern s32 D_00FBBA68;
extern f32 D_00FBBA70[][4];
void sceVu0CopyVector(f32 *, f32 *);

void func_00f33aa0(f32 *pos, s32 x0, s32 y0, s32 z0, s32 nx, s32 ny, s32 nz) {
    f32 v[4];
    s32 i, j, k;
    f32 half;

    if (nx == ny && ny == nz) {
        half = ny * 0.5f;
        v[0] = -pos[0] - (x0 + half) * 200.0f;
        v[1] = pos[1] - (y0 + half) * 200.0f;
        v[2] = -pos[2] - (z0 + half) * 200.0f;
        v[3] = ny * 200.0f * 0.25f;
        sceVu0CopyVector(D_00FBBA70[D_00FBBA68], v);
        D_00FBBA68++;
        return;
    }
    for (i = 0; i < ny; i++) {
        for (j = 0; j < nz; j++) {
            for (k = 0; k < nx; k++) {
                v[0] = -pos[0] - (x0 + k + 0.5f) * 200.0f;
                v[1] = pos[1] - (y0 + i + 0.5f) * 200.0f;
                v[2] = -pos[2] - (z0 + j + 0.5f) * 200.0f;
                v[3] = 50.0f;
                sceVu0CopyVector(D_00FBBA70[D_00FBBA68], v);
                D_00FBBA68++;
            }
        }
    }
}
