/* gb.x func_00f43cf0: matched by hand. */
#include "ovl.h"

extern s8 *D_00F829C0;

void func_00f43cf0(s32 arg0) {
    s32 i;
    s8 *p;

    p = D_00F829C0;
    if (arg0 < 0) {
        for (i = 0; i < 0x200; i++) {
            if (*p != 0) {
                *p = 0;
            }
            p += 0x44;
        }
        return;
    }
    for (i = 0x1FF; i >= 0; i--) {
        if (*p == arg0) {
            *p = 0;
        }
        p += 0x44;
    }
}
