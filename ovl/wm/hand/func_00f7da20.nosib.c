/* wm.x func_00f7da20: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x1E]; s16 x1E; } WinDesc;
extern WinDesc D_00FB6140;
extern s32 D_0108F6C4;
extern s32 D_0108F6EC;
void func_00f7d9e0(void);
s32 func_0011ef10(s32, void (*)(void));
void *func_001f31a8(void *, s32);

void func_00f7da20(void) {
    D_0108F6C4 = -1;
    func_0011ef10(0x2BFE9, func_00f7d9e0);
    if (D_0108F6EC != 0) {
        D_00FB6140.x1E = 2;
    } else {
        D_00FB6140.x1E = 1;
    }
    func_001f31a8(&D_00FB6140, 0);
}
