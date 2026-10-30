/* wm.x func_00f2e960: matched by hand. */
#include "ovl.h"

typedef struct { u8 p[6]; u16 f; u16 h; u16 pad; } N2e960;
typedef struct { s32 n; u8 pad[0x2C]; N2e960 ent[1]; } D2e960;
typedef struct { s32 active; u8 pad[28]; } O2e960;
typedef struct { u8 pad[0x30]; f32 pos[4]; } S2e960;
CONTEXT_ONLY void func_00f2c910(S2e960 *a0, s32 a1) {}
s32 func_00f2e890(s32);
extern D2e960 D_00F85240;
extern f32 D_00F85180[4][4];
extern f32 D_00F85200[4][4];
extern O2e960 D_00FBB5D0[16];
extern s32 D_00FCC3C4;
extern f32 D_00FCC3D0[][4];
extern u8 D_00FCC4D0[];

s32 func_00f2e960(s32 *out) {
    f32 m[4][4];
    S2e960 s;
    s32 cnt = 0;
    s32 i;
    s32 n;
    s32 k;
    s32 r;

    for (i = 0; i < 16; i++) {
        if (D_00FBB5D0[i].active == 1) {
            cnt++;
        }
    }
    for (i = 0; i < 16; i++) {
        out[i] = -1;
    }
    if (cnt == 0) {
        return 0;
    }
    sceVu0MulMatrix(m, D_00F85180, D_00F85200);
    n = 0;
    for (i = 0; i < D_00F85240.n; i++) {
        k = D_00F85240.ent[i].h - 1;
        if (k < 64) {
            if (k >= 61) {
                func_00f2c910(&s, i);
                sceVu0ApplyMatrix(D_00FCC3D0[n], m, s.pos);
                D_00FCC3D0[n][0] /= D_00FCC3D0[n][3];
                D_00FCC3D0[n][1] /= D_00FCC3D0[n][3];
                D_00FCC4D0[n] = 1;
                n++;
            }
        }
    }
    D_00FCC3C4 = n;
    while (n > 0) {
        for (i = 0; i < 16; i++) {
            if (D_00FBB5D0[i].active == 1) {
                r = func_00f2e890(i);
                if (r >= 0) {
                    out[r] = i;
                    n--;
                    D_00FCC4D0[r] = 0;
                }
            }
        }
    }
    return cnt;
}
