/* wm.x func_00f4c510: matched by hand. */
#include "ovl.h"

s32 func_00f4c510(f32 *arg0) {
    s32 r = 0;

    if (arg0[0x4C / 4] >= 0.8f) {
        if (arg0[0x60 / 4] >= 0.8f) {
            r = 0x20;
        } else if (arg0[0x60 / 4] <= -0.8f) {
            r = 0x80;
        } else if (arg0[0x64 / 4] >= 0.8f) {
            r = 0x40;
        } else if (arg0[0x64 / 4] <= -0.8f) {
            r = 0x10;
        }
    }
    if (arg0[0x3C / 4] >= 0.8f) {
        if (arg0[0x50 / 4] >= 0.8f) {
            r = 0x2000;
        } else if (arg0[0x50 / 4] <= -0.8f) {
            r = 0x8000;
        } else if (arg0[0x54 / 4] >= 0.8f) {
            r = 0x4000;
        } else if (arg0[0x54 / 4] <= -0.8f) {
            r = 0x1000;
        }
    }
    return r;
}
