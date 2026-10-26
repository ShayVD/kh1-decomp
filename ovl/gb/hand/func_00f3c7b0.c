/* gb.x func_00f3c7b0: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0, x4, x8, xc; } Pad;
Pad *func_001ba488(s32);
void func_00f3c1f0(s32, s32, s32);
void func_001bfac8(void);
s32 func_00f3c7b0(s32 mode, s32 arg) {
    s32 r = 0;
    s32 btn;
    Pad *p;
    while (func_001ba488(0)->x4 & 0x6000) {
        func_00f3c1f0(256, 192, arg);
        func_001bfac8();
    }
    btn = 0;
    for (;;) {
        p = func_001ba488(0);
        if (btn == 0) {
          if (mode == 1) {
            s32 v = p->x8;
            if (v & 0x2000) {
                r = 1;
                btn = 0x2000;
            } else if (v & 0x4000) {
                r = 0;
                btn = 0x4000;
            }
        } else if (p->x8 & 0x2000) {
            r = 1;
            btn = 0x2000;
        }
        } else if (p->xc & btn) return r;
        func_00f3c1f0(256, 192, arg);
        func_001bfac8();
    }
}
