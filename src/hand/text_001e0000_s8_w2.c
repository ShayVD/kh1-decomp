#include "common.h"
void func_001ea268(char *dst, char *src) {
    s32 len = 0; s32 i; s64 c;
    while (1) {
        c = dst[len];
        if (c == 0) {
            i = 0;
            while (src[i] != 0) {
                dst[len + i] = src[i];
                if ((u8)(src[i] - 5) < 3) {
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                } else if (src[i] == 11) {
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                } else if (src[i] == 10) {
                    i++;
                    dst[len + i] = src[i];
                    if (dst[len] == 0) {
                        i++;
                        dst[len + i] = src[i];
                        i++;
                        dst[len + i] = src[i];
                    }
                } else if (src[i] == 13) {
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                    i++;
                    dst[len + i] = src[i];
                }
                if ((u8)(src[i] - 9) < 23) {
                    i++;
                    dst[len + i] = src[i];
                }
                i++;
            }
            dst[i + len] = 0;
        return; }

        if ((u8)(dst[len] - 5) < 3) {
            len += 2;
        } else if (c == 11) {
            len += 3;
        } else if (c == 10) {
            len++;
            if (dst[len] == 0) len += 2;
        } else if (c == 13) {
            len += 3;
        } else {
            len += (u8)(dst[len] - 9) < 23;
        }
        len++;
    }
}
