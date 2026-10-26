/* wm.x func_00f48dd8: matched by hand. */
#include "ovl.h"

typedef struct { u32 a; u32 b; u32 trig; } WmPad;
s32 func_001ba3f0(s32);
s32 func_001b9b78(s32);
void func_001b9bb0(s32, s32);
void func_00f49430(s32, s32, s32, s32);
WmPad *func_001ba488(s32);
void func_001bfac8(void);

void func_00f48dd8(void) {
    s32 msg[4];
    s32 n = 0;
    s32 lv;
    s32 i;

    lv = func_001ba3f0(69) != 0;
    if (func_001ba3f0(70) != 0) {
        lv = 2;
    }
    if (func_001b9b78(1) < lv) {
        msg[n++] = 127;
    }
    func_001b9bb0(1, lv);
    lv = func_001ba3f0(64) != 0;
    if (func_001b9b78(2) < lv) {
        msg[n++] = 128;
        func_001b9bb0(2, lv);
    }
    if (func_001ba3f0(65) != 0) {
        lv = 2;
    }
    if (func_001b9b78(2) < lv) {
        msg[n++] = 129;
        func_001b9bb0(2, lv);
    }
    if (n != 0) {
        for (i = 0; i < n; i++) {
            func_00f49430(2, msg[i], 0x80E19664, 0);
            while (!(func_001ba488(0)->trig & 0x2000)) {
                func_001bfac8();
            }
            func_001bfac8();
        }
    }
}
