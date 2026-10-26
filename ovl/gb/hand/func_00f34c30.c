/* gb.x func_00f34c30: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 h4; u8 pad6[6]; } Ent;
typedef struct { u8 pad[164]; u16 n; u16 h166; u16 h168; u16 h170; u8 pad172[100]; Ent e[1]; } G;
extern G *D_00F56DC0;
extern s32 D_00F56DE8;
s32 func_00f41678(s32, s32, OvlMtx, s32, s32);
void func_00f33da0(s32, s32);
void func_00f34c30(void) {
    OvlMtx m;
    OvlVec v;
    s32 i;
    for (i = 0; i < D_00F56DC0->n; i++) {
        if ((u32)(D_00F56DC0->e[i].h4 - 1) == 48) {
            v[0] = D_00F56DC0->h166 * 0.5f * 200.0f;
            v[1] = -(D_00F56DC0->h168 * 0.5f) * 200.0f;
            v[2] = D_00F56DC0->h170 * 0.5f * 200.0f;
            v[3] = 1.0f;
            PlatVu0UnitMatrix(m);
            PlatVu0TransMatrix(m, m, v);
            func_00f33da0(func_00f41678(55, 1, m, 0, D_00F56DE8), 7);
            return;
        }
    }
}
