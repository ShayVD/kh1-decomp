/* gb.x func_00f25418: matched by hand. */
#include "ovl.h"

s32 func_00f25418(f32 *m) {
    s32 r = 0;
    if (m[19] >= 0.8f) {
        if (m[24] >= 0.8f) {
            r = 0x20;
        } else if (m[24] <= -0.8f) {
            r = 0x80;
        } else if (m[25] >= 0.8f) {
            r = 0x40;
        } else if (m[25] <= -0.8f) {
            r = 0x10;
        }
    }
    if (m[15] >= 0.8f) {
        if (m[20] >= 0.8f) {
            r = 0x2000;
        } else if (m[20] <= -0.8f) {
            r = 0x8000;
        } else if (m[21] >= 0.8f) {
            r = 0x4000;
        } else if (m[21] <= -0.8f) {
            r = 0x1000;
        }
    }
    return r;
}
