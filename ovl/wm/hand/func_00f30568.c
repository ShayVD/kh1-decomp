/* wm.x func_00f30568: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; s16 v; u8 pad2[0x7E]; } E;
s32 func_00f2cfd8(s32, s32, s32, s32, s32, s32, f32 *, void (*)(void), s32, s32);
extern f32 D_00F8C150;
extern s32 D_00F8C1FC;
extern s32 D_00F8C200;
extern s32 D_00FBB5A8;
extern E D_00FBEBC0[];
void func_00f30388(void);

void func_00f30568(void) {
    OvlVec c;
    s32 i;
    if (D_00F8C1FC == 0) {
        D_00FBB5A8++;
        c[0] = D_00F8C150;
        c[1] = D_00F8C150;
        c[2] = D_00F8C150;
        c[3] = 1.0f;
        i = func_00f2cfd8(0, -1, -1, 55, 2, 55, 0, func_00f30388, 0, -1);
        if (i >= 0) {
            D_00F8C1FC = 1;
            D_00F8C200 = D_00FBEBC0[i].v;
        }
    }
}
