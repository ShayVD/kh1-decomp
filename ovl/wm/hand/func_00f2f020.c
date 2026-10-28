/* wm.x func_00f2f020: matched by hand. */
#include "ovl.h"

typedef struct { u8 b0; u8 pad1[13]; u16 h0e; u16 pad10; s16 h12; u8 pad14[12]; f32 m[2][4]; f32 x, y, z; } O2f020;
extern f32 D_002BBDEC;
O2f020 *func_00f2cae8(void);
s32 func_00f680c0(s32);
void func_00f68ab0(s32);
void func_001c0310(s32, void (*)(s32), ...);
void func_00f2efa8(s32);
void func_00f2ee20(s32);
void func_001bfac8(void);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);

void func_00f2f020(s32 arg0) {
    O2f020 *o;
    s32 i;
    s32 done = 0;
    f32 s;
    f32 v[4];
    o = func_00f2cae8();
    s = D_002BBDEC * 1000.0f;
    for (i = 0; func_00f680c0(o->h0e); i++) {
        if (o->b0 == 0) {
            return;
        }
        if (!done) {
            if (done) {
                v[0] = -o->x * s;
                v[1] = -o->y * s;
                v[2] = -o->z * s;
                v[3] = 1.0f;
                s *= 0.9f;
                sceVu0TransMatrix(o->m, o->m, v);
            } else {
                v[0] = -o->x * s;
                v[1] = -o->y * s;
                v[2] = -o->z * s;
                v[3] = 1.0f;
                s *= 0.9f;
                sceVu0TransMatrix(o->m, o->m, v);
            }
            if (i >= 31 || (o->h12 & 1)) {
                func_00f68ab0(o->h0e);
                done = 1;
                func_001c0310(-1, func_00f2efa8, arg0);
                func_00f2ee20(arg0 | 0x8000);
            }
            if (!done) {
                func_00f2ee20(arg0 | 0x4000);
            }
        }
        func_001bfac8();
    }
}
