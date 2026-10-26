/* xs_mushu.x func_00f20380: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x70]; s32 f70; u8 pad2[0xEC]; s64 f160; } Pl;
void func_0012cc38(s32, s32);
void func_0012ccb0(s32);
extern f32 D_00304B7C;
extern Pl *D_00F21384;
extern u32 D_00F21398;
void func_00f20380(void) {
    if (D_00F21398 < 2 && D_00304B7C >= 0.0f) {
        func_0012cc38(0, 0x47);
        switch (D_00F21384->f70) {
        case 0:
        case 1:
        case 2:
        case 8:
            break;
        default:
            func_0012ccb0(0);
            break;
        }
    } else if ((s32)(D_00F21384->f160 >> 5) & 1) {
        func_0012ccb0(0);
    }
}
