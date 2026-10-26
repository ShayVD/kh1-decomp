/* wm.x func_00f3a4c8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xE0]; s32 e0; u8 pad2[0x18]; s32 fc; u8 pad3[0x10]; } W110;
void func_00f3a030(void);
extern W110 D_00FCE390[256];
void func_00f3a4c8(void) {
    s32 i;
    func_00f3a030();
    for (i = 0; i < 256; i++) {
        D_00FCE390[i].e0 = 0;
        D_00FCE390[i].fc = 0;
    }
}
