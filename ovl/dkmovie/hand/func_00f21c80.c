/* dkmovie.x func_00f21c80: matched by hand. */
#include "ovl.h"

s32 sceCdStatus(void);
s32 sceCdDiskReady(s32);
void func_00f21b98(void);
void func_00f23480(void);
extern s8 D_00F28680;
s32 func_00f21c80(void) {
    s32 st;
    st = sceCdStatus();
    if (st == 1) {
        D_00F28680 = st;
        while (1) {
            if (sceCdDiskReady(1) == 2) {
                if (sceCdStatus() != 1) {
                    func_00f21b98();
                    return 0;
                }
            }
            func_00f23480();
        }
    }
    return 1;
}
