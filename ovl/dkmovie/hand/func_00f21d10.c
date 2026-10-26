/* dkmovie.x func_00f21d10: matched by hand. */
#include "ovl.h"

s32 sceCdStatus(void);
s32 sceCdDiskReady(s32);
s32 sceGsSyncV(s32);
void func_00f23480(void);
s32 func_00f21d10(s32 arg0) {
    if (sceCdStatus() != 1) {
        return 1;
    }
    while (1) {
        if (sceCdDiskReady(1) == 2) {
            if (sceCdStatus() != 1) {
                return 0;
            }
        }
        if (arg0 == 0) {
            sceGsSyncV(0);
        } else {
            func_00f23480();
        }
    }
}
