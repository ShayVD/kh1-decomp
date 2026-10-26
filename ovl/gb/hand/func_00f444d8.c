/* gb.x func_00f444d8: matched by hand. */
#include "ovl.h"

void func_00f444b8(s8 *, f32, f32);
extern s8 *D_00F829C0;

void func_00f444d8(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s8 *p;

    p = D_00F829C0;
    if (arg0 < 0) {
        for (i = 0; i < 0x200; i++) {
            if (*p != 0) {
                func_00f444b8(p, (f32) arg1, (f32) arg2);
            }
            p += 0x44;
        }
        return;
    }
    for (i = 0x1FF; i >= 0; i--) {
        if (*p == arg0) {
            func_00f444b8(p, (f32) arg1, (f32) arg2);
        }
        p += 0x44;
    }
}
