/* wm.x func_00f4ccc0: the twin of gb.x func_00f25bc8 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { s32 w[0xb040 / 4]; } Big;
Big *func_00232cc0(s32);
extern Big D_01080C58;
extern s32 D_00FA5378;
void func_00f4ccc0(void) {
    Big *s = func_00232cc0(4);
    D_01080C58 = *s;
    D_00FA5378 = 1;
}
