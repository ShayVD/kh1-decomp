/* dkmovie.x func_00f27b90: matched by hand. */
#include "ovl.h"

void func_00f27b90(u32 *arg0, u32 *dst, s32 w, s32 h) {
    u32 *src = arg0;
    u32 *src2;
    s32 y, x, j, k;
    if ((h & 0xF) != 0 || ((h / 2) & 0xF) == 0) {
        src2 = src + w * h / 2;
        for (y = 0; y < h / 32; y++) {
            for (x = 0; x < w / 16; x++) {
                for (j = 0; j < 8; j++) {
                    for (k = 0; k < 16; k++) {
                        dst[k] = src[k];
                        dst[k + 16] = src2[k];
                        dst[w * 16 + k] = src[k + 128];
                        dst[w * 16 + k + 16] = src2[k + 128];
                    }
                    dst += 32;
                    src += 16;
                    src2 += 16;
                }
                src += 128;
                src2 += 128;
            }
            dst += w * 16;
        }
    } else {
        src2 = arg0 + w * ((h / 2) & ~0xF);
        for (y = 0; y < (h + 16) / 32; y++) {
            for (x = 0; x < w / 16; x++) {
                for (j = 0; j < 8; j++) {
                    for (k = 0; k < 16; k++) {
                        dst[k] = src[k];
                        dst[k + 16] = src2[k + 128];
                        dst[w * 16 + k] = src[k + 128];
                        dst[w * 16 + k + 16] = src2[w * 16 + k];
                    }
                    dst += 32;
                    src += 16;
                    src2 += 16;
                }
                src += 128;
                src2 += 128;
            }
            dst += w * 16;
        }
    }
}
