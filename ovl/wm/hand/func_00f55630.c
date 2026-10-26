/* wm.x func_00f55630: matched by hand. */
#include "ovl.h"

extern f32 D_00FA5D00[3];

void func_00f55630(f32 *arg0) {
    if (arg0 == NULL) {
        D_00FA5D00[0] = 0;
        D_00FA5D00[1] = 0;
        D_00FA5D00[2] = 0;
        return;
    }
    D_00FA5D00[0] = arg0[0];
    D_00FA5D00[1] = arg0[1];
    D_00FA5D00[2] = arg0[2];
}
