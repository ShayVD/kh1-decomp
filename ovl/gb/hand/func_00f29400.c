/* gb.x func_00f29400: matched by hand. */
#include "ovl.h"

void func_00f293b0(void);
extern s32 D_00F613B0;
extern s32 D_00F80580;
void func_00f29400(s32 arg0) {
    if (arg0 == 0) {
        func_00f293b0();
        D_00F613B0 = 0;
    }
    D_00F80580 = arg0;
    D_00F613B0 = 1;
}
