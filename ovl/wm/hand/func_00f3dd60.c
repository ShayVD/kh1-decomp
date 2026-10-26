/* wm.x func_00f3dd60: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 pad[3]; OvlVec v; s32 t; s32 pad2[3]; } S;
s32 func_00f41448(void);
s32 func_00f40c98(void);
extern s32 D_00F8C23C;
extern S D_00F9A5C0[];

void func_00f3dd60(s32 arg0, f32 *arg1) {
    s32 i;
    if (func_00f41448() != 0) return;
    if (D_00F8C23C != 0) return;
    if (func_00f40c98() >= 2) return;
    for (i = 0; i < 64; i++) {
        if (D_00F9A5C0[i].id < 0) {
            D_00F9A5C0[i].id = arg0;
            D_00F9A5C0[i].t = 0;
            PlatVu0CopyVector(D_00F9A5C0[i].v, arg1);
            return;
        }
    }
}
