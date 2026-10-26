/* wm.x func_00f302e8: matched by hand. */
#include "ovl.h"

void func_00f68508(s32, s32, s32, s32, s32, s32);
extern s32 D_00F87048;

void func_00f302e8(s32 arg0, s32 arg1, s32 arg2) {
    s32 id = -1;
    switch (arg2) {
    case 0:
        id = arg1 + 63;
        break;
    case 1:
        id = (arg1 < 2) ? 48 : 49;
        break;
    case 2:
        id = (arg1 < 2) ? 53 : 54;
        break;
    }
    if (id >= 0) {
        func_00f68508(id, 1, arg0, 0, 0, D_00F87048);
    }
}
