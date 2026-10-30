/* wm.x func_00f5d498: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 x8; u8 pad2[4]; s32 x10; } Pad5d498;
void func_001bfac8(void);
Pad5d498 *func_001ba488(s32);
s32 func_001bb720(void);
void func_00f4fba0(void *, s32, s32);
extern u8 D_00F9B548[];

void func_00f5d498(void) {
    s32 sel = 0;
    s32 top = 0;
    Pad5d498 *p;

    func_001bfac8();
    while (1) {
        p = func_001ba488(0);
        if (p->x8 & 0x4000) {
            return;
        }
        if (p->x10 & 0x10) {
            sel--;
        }
        if (p->x10 & 0x40) {
            sel++;
        }
        if (sel >= func_001bb720()) {
            sel = func_001bb720() - 1;
        }
        if (sel < 0) {
            sel = 0;
        }
        if (sel - top >= 10) {
            top = sel - 9;
        }
        if (sel < top) {
            top = sel;
        }
        func_00f4fba0(D_00F9B548, sel, top);
        func_001bfac8();
    }
}
