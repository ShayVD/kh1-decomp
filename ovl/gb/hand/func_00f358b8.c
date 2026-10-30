/* gb.x func_00f358b8: matched by hand. */
#include "ovl.h"

typedef struct { s32 a, b; s32 buttons; } Pad5c9b0;
Pad5c9b0 *func_001ba488(s32);
void func_001bfac8(void);
s32 func_001bff70(s32);
s32 func_001c0310(s32, void *, ...);
void func_00f50fb0();
void func_00f51440();

s32 func_00f358b8(s32 arg0) {
    s32 m1 = arg0;
    s32 t1;
    s32 m2 = -1;
    s32 t2 = -1;
    Pad5c9b0 *pad;

    if (m1 == 0) {
        t1 = func_001c0310(-1, func_00f50fb0);
    } else {
        t1 = func_001c0310(-1, func_00f51440, 32, 32);
    }
    func_001bfac8();
    while (func_001bff70(t1) | func_001bff70(t2)) {
        pad = func_001ba488(0);
        if (!func_001bff70(t1)) {
            t1 = -1;
            m1 = -1;
        }
        if (!func_001bff70(t2)) {
            t2 = -1;
            m2 = -1;
        }
        if (pad->buttons & 0x8000) {
            if (m1 < 0) {
                if (m2 != 0) {
                    m1 = 0;
                    t1 = func_001c0310(-1, func_00f50fb0);
                }
            } else if (m2 < 0 && m1 != 0) {
                m2 = 0;
                t2 = func_001c0310(-1, func_00f50fb0);
            }
        } else if (pad->buttons & 0x1000) {
            if (m1 < 0 && m2 != 1) {
                m1 = 1;
                t1 = func_001c0310(-1, func_00f51440, 32, 32);
            } else if (m2 < 0 && m1 != 1) {
                m2 = 1;
                t2 = func_001c0310(-1, func_00f51440, 32, 32);
            }
        }
        func_001bfac8();
    }
    return 1;
}
