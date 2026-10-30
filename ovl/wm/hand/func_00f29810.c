/* wm.x func_00f29810: matched by hand. */
#include "ovl.h"

typedef struct { u64 d; u64 r; } GP29810;
s32 func_00f64c10(s32);
s32 func_00f64c38(s32, s32);
u64 func_00f65118(s32);
f32 *func_00f65158(s32);
s32 func_00f66b20(GP29810 *);
s32 func_00f66b38(GP29810 *);
GP29810 *func_00f66b78(s32);
void func_00f66b90(GP29810 *);
extern f32 D_002BBDFC;
extern s32 D_00FBB56C;

void func_00f29810(s32 arg0, GP29810 *buf, f32 (*out)[4]) {
    s32 i, j, h;
    f32 *v;
    GP29810 *p;

    for (i = 0; i < func_00f64c10(arg0); i++) {
        h = func_00f64c38(i, arg0);
        out[i][3] = 1.0f;
        v = func_00f65158(h);
        for (j = 0; j < 3; j++) {
            out[i][j] = 0;
            v[j] *= D_002BBDFC / 60.0f;
            while (v[j] < -180.0f) {
                v[j] += 360.0f;
            }
            while (v[j] > 180.0f) {
                v[j] -= 360.0f;
            }
            v[j] *= 0.017453291f;
        }
        for (j = 0; j < 8; j++) {
            buf[j].d = 0;
            buf[j].r = 0;
        }
        p = func_00f66b78(func_00f66b20(buf));
        p->d = 0x30000;
        p->r = 0x47;
        p++;
        p->d = 0x740000007000;
        p->r = 0x18;
        p++;
        p->d = 0x60;
        p->r = 0x14;
        p++;
        p->d = 0x101000070;
        p->r = 0x4E;
        p++;
        p->d = 0;
        p->r = 8;
        p++;
        p->d = func_00f65118(h);
        p->r = 0x42;
        p++;
        func_00f66b90(p);
        buf += 8;
        D_00FBB56C = func_00f66b38(p);
    }
}
