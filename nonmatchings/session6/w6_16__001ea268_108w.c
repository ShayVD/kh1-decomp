/* ~108w by word count but structurally almost identical (shifted by 4 words): ours hoists li 11/10/13 out of the outer scan loop to the function top; orig keeps them in the copy-loop preheader and uses li v0,K in the scan. strict hand. func_001ea128 (matched) is the same copy loop. */
#include "common.h"

void func_001ea268(char *dst, char *src) {
    s32 len = 0;
    s32 n, i;
    for (;;) {
        char c = dst[len];
        u8 uc = dst[len];
        if (c == 0) {
            n = 0;
            i = 0;
            while (src[i] != 0) {
                dst[len + n] = src[i];
                if ((u8)(src[i] - 5) < 3) {
                    i++; n++;
                    dst[len + n] = src[i];
                    i++; n++;
                    dst[len + n] = src[i];
                } else if (src[i] == 11) {
                    i++; n++;
                    dst[len + n] = src[i];
                    i++; n++;
                    dst[len + n] = src[i];
                    i++; n++;
                    dst[len + n] = src[i];
                } else if (src[i] == 10) {
                    i++; n++;
                    dst[len + n] = src[i];
                    if (dst[len] == 0) {
                        i++; n++;
                        dst[len + n] = src[i];
                        i++; n++;
                        dst[len + n] = src[i];
                    }
                } else if (src[i] == 13) {
                    i++; n++;
                    dst[len + n] = src[i];
                    i++; n++;
                    dst[len + n] = src[i];
                    i++; n++;
                    dst[len + n] = src[i];
                }
                if ((u8)(src[i] - 9) < 23) {
                    i++; n++;
                    dst[len + n] = src[i];
                }
                i++; n++;
            }
            dst[len + n] = 0;
            return;
        }
        if ((u8)(uc - 5) < 3) {
            len += 2;
        } else if (c == 11) {
            len += 3;
        } else if (c == 10) {
            len++;
            if (dst[len] == 0) len += 2;
        } else if (c == 13) {
            len += 3;
        } else {
            len += (u8)(uc - 9) < 23;
        }
        len++;
    }
}
