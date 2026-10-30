/* gb.x func_00f34aa8: matched by hand (session 141, wwm1 round 17): a CONTEXT_ONLY func_00f33d18 above it. A call to a function defined earlier in the file is nothrow, which changes reorg's branch-likely choice (docs/overlays.md, "Branch-likely vs plain branch"). */
#include "ovl.h"
typedef struct { u8 pad[4]; u16 h4; u8 pad6[6]; } Ent;
typedef struct { u8 pad[164]; u16 n; u16 h166; u16 h168; u16 h170; u8 pad172[100]; Ent e[1]; } G;
extern G *D_00F56DC0;
extern s32 D_00F56DE8;
CONTEXT_ONLY void func_00f33d18(OvlMtx a0, s32 a1) {}
s32 func_00f41678(s32, s32, OvlMtx, OvlVec, s32);
void func_00f33da0(s32, s32);

void func_00f34aa8(void) {
    OvlMtx m;
    OvlVec v;
    s32 i;
    v[0] = -1.0f;
    v[1] = 1.0f;
    v[2] = 1.0f;
    v[3] = 1.0f;
    for (i = 0; i < D_00F56DC0->n; i++) {
        switch (D_00F56DC0->e[i].h4 - 1) {
        case 44:
            func_00f33d18(m, i);
            func_00f33da0(func_00f41678(56, 1, m, 0, D_00F56DE8), 6);
            break;
        case 45:
            func_00f33d18(m, i);
            func_00f33da0(func_00f41678(56, 1, m, v, D_00F56DE8), 6);
            break;
        case 46:
            func_00f33d18(m, i);
            func_00f33da0(func_00f41678(57, 1, m, 0, D_00F56DE8), 6);
            break;
        case 47:
            func_00f33d18(m, i);
            func_00f33da0(func_00f41678(57, 1, m, v, D_00F56DE8), 6);
            break;
        }
    }
}
