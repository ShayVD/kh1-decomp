/* wm.x func_00f2f678: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xB0]; OvlVec c; } S;
void func_001bfac8(void);
void func_00f2ce60(s32, s32, s32, s32);
extern s32 D_00F850F4;
extern S D_00FBB850;

void func_00f2f678(void) {
    s32 i;
    D_00FBB850.c[0] = 0.0f;
    D_00FBB850.c[1] = 0.0f;
    D_00FBB850.c[2] = 0.0f;
    D_00FBB850.c[3] = 0.0f;
    for (i = 0; i < 80; i++) {
        if (D_00F850F4 == 0) return;
        D_00FBB850.c[0] += 1.0f;
        D_00FBB850.c[1] += 1.0f;
        D_00FBB850.c[2] += 1.0f;
        D_00FBB850.c[3] += 1.0f;
        func_001bfac8();
    }
    D_00FBB850.c[0] = 0.0f;
    D_00FBB850.c[1] = 0.0f;
    D_00FBB850.c[2] = 0.0f;
    D_00FBB850.c[3] = 0.0f;
    func_00f2ce60(0, -1, 44, -1);
    func_00f2ce60(0, -1, 45, -1);
    func_00f2ce60(0, -1, 46, -1);
    func_00f2ce60(0, -1, 47, -1);
}
