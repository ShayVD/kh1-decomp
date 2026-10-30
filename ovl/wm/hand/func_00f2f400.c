/* wm.x func_00f2f400: matched by hand. */
#include "ovl.h"

typedef struct { u8 p[6]; u16 f; u16 h; u16 pad; } N2f400;
typedef struct { s32 n; u8 pad[0x2C]; N2f400 ent[1]; } D2f400;
extern D2f400 D_00F85240;
CONTEXT_ONLY s32 func_00f2cd88(s32 a0, s32 a1, s32 a2) { return 0; }
CONTEXT_ONLY s32 func_00f2cfd8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, void *a6, void *a7, void *a8, s32 a9) { return 0; }
void func_00f2ee48();
void func_00f2f3a0();
void func_00f2f3b8();
void func_00f2f020();
void func_00f2f3d0();
void func_00f2f3e8();

void func_00f2f400(s32 arg0) {
    s32 i;

    for (i = 0; i < D_00F85240.n; i++) {
        switch (D_00F85240.ent[i].h - 1) {
        case 58:
            if (arg0 == 0) {
                func_00f2cfd8(func_00f2cd88(i, 58, 40), i, 58, 40, 0, 40, 0, func_00f2ee48, 0, -1);
            }
            break;
        case 59:
            if (arg0 == 1) {
                func_00f2cfd8(func_00f2cd88(i, 59, 42), i, 59, 42, 0, 42, 0, func_00f2f3a0, func_00f2f3d0, -1);
                func_00f2cfd8(func_00f2cd88(i, 59, 42), i, 59, 42, 0, 42, 0, func_00f2f3b8, func_00f2f3e8, -1);
            }
            break;
        case 60:
            if (arg0 == 2) {
                func_00f2cfd8(func_00f2cd88(i, 60, 37), i, 60, 37, 0, 37, 0, func_00f2f020, 0, -1);
            }
            break;
        }
    }
}
