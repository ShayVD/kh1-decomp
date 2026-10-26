/* xs_dh_break.x func_00f206a0: matched by hand. */
#include "ovl.h"

f32 func_00f20020(void);
extern f32 D_00F9CEB0[51][51][2];
void func_00f206a0(void) {
    s32 i, j;
    for (i = 0; i < 51; i++) {
        for (j = 0; j < 51; j++) {
            D_00F9CEB0[i][j][0] = i * 0.0199999996275f + (func_00f20020() - 0.5f) * 0.0199999996275f * 2.0f;
            D_00F9CEB0[i][j][1] = j * 0.0199999996275f + (func_00f20020() - 0.5f) * 0.0199999996275f * 2.0f;
        }
    }
}
