/* wm.x func_00f39220: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f2c818(f32 (*)[4]);
extern f32 D_002BBDEC;

typedef struct { u8 pad[0x50]; f32 pos[3]; u8 pad2[0x84]; s32 e0; u8 pad3[0x18]; s32 fc; } A0;
typedef struct { u8 pad[0x14]; s32 type; s32 time; s32 x; s32 y; s32 z; } A1;

void func_00f39220(A0 *arg0, A1 *arg1, s32 arg2) {
    f32 d[3];
    f32 t[3];
    f32 s[3];
    f32 m[4][4];
    s32 n;
    s32 i;

    n = (f32) arg1->time / D_002BBDEC;
    s[0] = arg0->pos[0];
    s[1] = arg0->pos[1];
    s[2] = arg0->pos[2];
    d[2] = (f32) arg1->z * 100.0f;
    d[0] = (f32) arg1->x * 100.0f;
    d[1] = (f32) arg1->y * 100.0f;
    switch (arg1->type) {
    case 2:
        t[0] = s[0] + d[0];
        t[1] = s[1] + d[1];
        t[2] = s[2] + d[2];
        break;
    case 3:
        func_00f2c818(m);
        t[0] = m[3][0] + d[0];
        t[1] = m[3][1] + d[1];
        t[2] = m[3][2] + d[2];
        break;
    case 4:
        t[0] = d[0];
        t[1] = d[1];
        t[2] = d[2];
        break;
    }
    if (arg2 != 0 && n > 0) {
        for (i = 0; i < n; i++) {
            if (arg0->fc == 0) break;
            if (arg0->e0 == 0) return;
            arg0->pos[0] = d[0] = (t[0] - s[0]) * i / n + s[0];
            arg0->pos[1] = d[1] = (t[1] - s[1]) * i / n + s[1];
            arg0->pos[2] = d[2] = (t[2] - s[2]) * i / n + s[2];
            func_001bfac8();
        }
    }
    arg0->pos[0] = t[0];
    arg0->pos[1] = t[1];
    arg0->pos[2] = t[2];
}
