/* wm.x func_00f3e5d0: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0; u8 pad4[12]; f32 pos[4]; s32 flag; u8 pad24[12]; } E3e5d0;
extern E3e5d0 D_00F9A5C0[64];
extern f32 (*D_00F864C0)[4];
extern f32 D_00F8C240[4][4];
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);
f32 *func_00f2c848(void);
f32 func_00f2c7f8(void);
s32 func_00f3caf0(f32 *, f32, f32 *, f32);
f32 *func_00f35058(s32);
s32 func_00f33a90(void);

s32 func_00f3e5d0(void) {
    s32 i, j;
    f32 *p;
    f32 r;
    f32 rad;
    f32 *s;
    f32 v[4];
    f32 t[4];
    p = func_00f2c848();
    r = func_00f2c7f8();
    r = r + r;
    for (i = 0; i < 64; i++) {
        if (D_00F9A5C0[i].x0 < 0) continue;
        if (D_00F9A5C0[i].flag) continue;
        sceVu0ApplyMatrix(t, D_00F864C0, D_00F9A5C0[i].pos);
        if (func_00f3caf0(p, r, t, 1000.0f)) {
            for (j = 0; j < func_00f33a90(); j++) {
                s = func_00f35058(j);
                v[0] = s[0];
                v[1] = s[1];
                v[2] = s[2];
                v[3] = 1.0f;
                rad = s[3];
                sceVu0ApplyMatrix(v, D_00F8C240, v);
                if (func_00f3caf0(v, rad, t, 1000.0f)) {
                    D_00F9A5C0[i].flag = 1;
                    break;
                }
            }
        }
    }
    return -1;
}
