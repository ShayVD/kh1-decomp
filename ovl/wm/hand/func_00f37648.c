/* wm.x func_00f37648: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x14]; s32 kind; s32 snd; s32 x; s32 y; s32 z; } P;
void func_001bfac8(void);
s32 func_00f68140(s32);
s32 func_00f68770(s32, s32, OvlMtx, s32, s32);
void func_00f689f0(s32, OvlMtx);
extern s32 D_00F87048;
extern s32 D_00F87058;

void func_00f37648(OvlMtx arg0, P *arg1) {
    OvlMtx m;
    OvlVec v;
    s32 snd, bank, h, i;
    v[3] = 1.0f;
    snd = arg1->snd;
    v[2] = arg1->z * 100.0f;
    v[0] = arg1->x * 100.0f;
    v[1] = arg1->y * 100.0f;
    if (arg1->kind == 8) {
        bank = D_00F87058;
    } else {
        bank = D_00F87048;
    }
    PlatVu0TransMatrix(m, arg0, v);
    h = func_00f68770(snd, 1, m, 0, bank);
    if (h >= 0) {
        for (i = 0; i < 120 && func_00f68140(h) != 0; i++) {
            PlatVu0TransMatrix(m, arg0, v);
            func_00f689f0(h, m);
            func_001bfac8();
        }
    }
}
