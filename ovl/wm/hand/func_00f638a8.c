/* wm.x func_00f638a8: matched by hand. */
#include "ovl.h"

typedef struct { u32 a; u32 held; u32 trig; u32 rel; } WmPad4;
WmPad4 *func_001ba488(s32);
void func_001bfac8(void);
void func_00f632e8(s32, s32, s32);

s32 func_00f638a8(s32 mode, s32 arg1) {
    s32 r = 0;
    s32 key;
    WmPad4 *p;

    while (func_001ba488(0)->held & 0x6000) {
        func_00f632e8(256, 192, arg1);
        func_001bfac8();
    }
    key = 0;
    for (;;) {
        p = func_001ba488(0);
        if (key == 0) {
            if (mode == 1) {
                if (p->trig & 0x2000) {
                    r = 1;
                    key = 0x2000;
                } else if (p->trig & 0x4000) {
                    r = 0;
                    key = 0x4000;
                }
            } else if (p->trig & 0x2000) {
                r = 1;
                key = 0x2000;
            }
        } else if (p->rel & key) {
            return r;
        }
        func_00f632e8(256, 192, arg1);
        func_001bfac8();
    }
}
