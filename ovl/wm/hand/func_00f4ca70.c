/* wm.x func_00f4ca70: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x11]; u8 x; } R4c;
R4c *func_001bb658(s32);
extern s32 D_0037A028[];
extern u8 *D_00F9B540;

s32 *func_00f4ca70(s32 arg0) {
    switch (*(s32 *)(D_00F9B540 + 0x94)) {
    case 0:
    default:
        return &D_0037A028[func_001bb658(arg0)->x];
    case 1:
    case 2:
        return (s32 *)(D_00F9B540 + 0x44);
    }
}
