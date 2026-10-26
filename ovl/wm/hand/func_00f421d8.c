/* wm.x func_00f421d8: matched by hand. */
#include "ovl.h"

typedef struct { OvlVec a; u8 pad[0x548]; s32 idx; u8 pad2[0x34]; } W;
typedef struct { u8 pad[0x10]; s32 k; u8 pad2[0x40]; s32 v; } P;
void func_001bef40(OvlVec, void *, s32);
void func_00f3f7c8(s32);
void func_00f3f8d0(s32, OvlVec);
extern s32 D_00F850E0;
extern W D_00F86500[];
extern s32 D_00F87E5C[];
extern P D_00F87E88[];
extern s32 D_00FB7250;

void func_00f421d8(s32 arg0) {
    OvlVec v[2];
    func_001bef40(v[0], &D_00FB7250, D_00F87E5C[D_00F87E88[D_00F86500[D_00F850E0].idx].k]);
    func_00f3f8d0(arg0, v[0]);
    func_00f3f7c8(D_00F87E88[D_00F86500[D_00F850E0].idx].v);
}
