/* wm.x func_00f3b8d0: matched by hand. */
#include "ovl.h"

typedef struct { s32 type; s32 a; s32 b; } C3b8d0;
typedef struct { u8 pad[0x30]; u8 sub[8]; f32 f38; } O3b8d0;
s32 func_00f3b380(void *, f32);

s32 func_00f3b8d0(s32 arg0, O3b8d0 *arg1, C3b8d0 *arg2) {
    switch (arg2->type) {
    case 2:
        if (arg2->b == 0) {
            if (arg2->a != arg0) {
                break;
            }
            return 1;
        }
        if (arg2->a < arg0) {
            break;
        }
        if (arg0 < arg2->b) {
            break;
        }
        return 1;
    case 3:
        if (!(arg2->a * 100.0f < arg1->f38)) {
            break;
        }
        return 1;
    case 4:
        if (!(arg1->f38 < arg2->a * 100.0f)) {
            break;
        }
        return 1;
    case 5:
        if (func_00f3b380(arg1->sub, arg2->a * 100.0f) != 1) {
            break;
        }
        return 1;
    case 6:
        if (func_00f3b380(arg1->sub, arg2->a * 100.0f) != 2) {
            break;
        }
        return 1;
    case 7:
        return 1;
    }
    return 0;
}
