/* gb.x func_00f25bc8: matched by hand. */
#include "ovl.h"

typedef struct { s32 w[0xb040 / 4]; } Big;
Big *func_00232cc0(s32);
extern Big D_00F74498;
extern s32 D_00F60BF8;
void func_00f25bc8(void) {
    Big *s = func_00232cc0(4);
    D_00F74498 = *s;
    D_00F60BF8 = 1;
}
