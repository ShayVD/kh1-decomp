/* dktitle.x func_00f23858: matched by hand. */
#include "ovl.h"

void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f23838(s32, s32, s32);
extern s32 D_00F27410[2];
extern s32 D_00F2C8F8;

typedef struct { s32 v[2]; } Pair;

void func_00f23858(void *a0, s32 a1, s32 a2, s32 a3) {
    Pair c = *(Pair *)D_00F27410;
    func_002078f0(a0, c.v[a1 == 0], 2, 2, a2, a3, 96, a2 + 48, 3);
    func_002078f0(a0, c.v[a1 == 1], 2, 2, a2 + 110, a3, 96, a2 + 158, 4);
    if (!a1) a2 += 96; else a2 += 206;
    if (D_00F2C8F8 == 0) {
        D_00F2C8F8 = 1;
        func_00f23838(a2, a3, 0);
    } else {
        func_00f23838(a2, a3, 8);
    }
}
