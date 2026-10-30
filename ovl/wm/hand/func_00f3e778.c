/* wm.x func_00f3e778: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0; u8 pad4[12]; f32 pos[4]; s32 flag; u8 pad24[12]; } E3e778;
extern E3e778 D_00F9A5C0[64];
extern f32 (*D_00F864C0)[4];
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);

void func_00f3e778(s32 arg0, f32 *arg1) {
    s32 i;
    s32 bi;
    s32 found = 0;
    f32 best;
    f32 dist;
    f32 d[4];
    f32 t[4];
    for (i = 0; i < 64; i++) {
        if (D_00F9A5C0[i].x0 < 0) continue;
        if (D_00F9A5C0[i].flag) continue;
        sceVu0ApplyMatrix(t, D_00F864C0, D_00F9A5C0[i].pos);
        d[0] = arg1[0] - t[0];
        d[1] = arg1[1] - t[1];
        d[2] = arg1[2] - t[2];
        d[3] = 1.0f;
        dist = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
        if (dist <= 400000000.0f) {
            if (!arg0) {
                if (!found || dist < best) {
                    best = dist;
                    bi = i;
                    found = 1;
                }
            } else {
                D_00F9A5C0[i].flag = 1;
            }
        }
    }
    if (!arg0 && found) {
        D_00F9A5C0[bi].flag = 1;
    }
}
