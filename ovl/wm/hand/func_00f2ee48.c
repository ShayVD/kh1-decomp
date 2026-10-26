/* wm.x func_00f2ee48: matched by hand. */
#include "ovl.h"

typedef struct { u8 on; u8 pad[0xD]; u16 snd; u16 pad2; s16 flag; u8 pad3[0xC]; OvlMtx m; } O;
void func_001bfac8(void);
O *func_00f2cae8(void);
void func_00f2cf78(s32);
void func_00f2ee20(s32);
s32 func_00f680c0(s32);
void func_00f68ab0(s32);
extern f32 D_002BBDEC;

void func_00f2ee48(s32 arg0) {
    OvlVec v;
    s32 state = 0;
    O *o = func_00f2cae8();
    f32 *m = o->m[0];
    f32 acc = 0.0f;
    f32 step = D_002BBDEC * 4000.0f;
    while (func_00f680c0(o->snd) != 0) {
        if (o->on == 0) return;
        if (o->flag & 1) {
            o->flag = 0;
            break;
        }
        if (state == 0) func_00f2ee20(arg0);
        if (state < 2) {
            acc += step;
            v[0] = -o->m[2][0] * step;
            v[1] = -o->m[2][1] * step;
            v[2] = -o->m[2][2] * step;
            v[3] = 1.0f;
            PlatVu0TransMatrix(m, m, v);
        }
        if (state == 0 && acc > 40000.0f) {
            state = 1;
            func_00f68ab0(o->snd);
        }
        func_001bfac8();
    }
    func_00f2cf78(arg0);
}
