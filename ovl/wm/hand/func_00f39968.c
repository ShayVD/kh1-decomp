/* wm.x func_00f39968: matched by hand. */
#include "ovl.h"

typedef struct { s32 type; s32 a; s32 b; } C39968;
typedef struct { u8 pad[0x30]; u8 sub[8]; f32 f38; } O39968;
extern f32 D_002BBDEC;
s32 func_00f36260(void *, f32);

s32 func_00f39968(s32 arg0, O39968 *arg1, C39968 *arg2) {
    f32 t[2];
    switch (arg2->type) {
    case 2:
        if (arg2->b == 0) {
            t[0] = arg2->a / D_002BBDEC + 0.5f;
            if ((s32)t[0] != arg0) {
                break;
            }
            return 1;
        }
        t[0] = arg2->a / D_002BBDEC + 0.5f;
        t[1] = arg2->b / D_002BBDEC + 0.5f;
        if (arg0 < (s32)t[0]) {
            break;
        }
        if ((s32)t[1] < arg0) {
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
        if (func_00f36260(arg1->sub, arg2->a * 100.0f) != 1) {
            break;
        }
        return 1;
    case 6:
        if (func_00f36260(arg1->sub, arg2->a * 100.0f) != 2) {
            break;
        }
        return 1;
    case 7:
        return 1;
    }
    return 0;
}
