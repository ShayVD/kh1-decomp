/* gb.x func_00f40d28: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 btn; } P67;
typedef struct { u8 pad[4]; u16 x; } Q67;
P67 *func_001ba488(s32);
Q67 *func_001ba9d8(s32);
void func_001bfac8(void);
void func_00f3cc20(s32, Q67 *, s32);
s32 func_00f40b68(s32, s32, s32, s32);
extern s32 D_00F82888;

s32 func_00f40d28(s32 arg0) {
    s32 sel = 0;
    s32 b;

    while (1) {
        b = func_001ba488(0)->btn;
        if (b & 0x10) {
            sel -= sel > 0;
        }
        if (b & 0x40) {
            sel += sel < 9;
        }
        if (b & 0x4000) {
            return -1;
        }
        if (b & 0x2000) {
            if (arg0 != 0) {
                if (func_001ba9d8(sel)->x != 0) {
                    return sel;
                }
            } else if (func_00f40b68(0, 0, sel, D_00F82888 + 0x50) != 0) {
                return sel;
            }
        }
        func_00f3cc20(arg0, func_001ba9d8(0), sel);
        func_001bfac8();
    }
}
