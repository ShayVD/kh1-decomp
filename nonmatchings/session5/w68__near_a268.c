#include "common.h"
void func_001ea268(char *dst, char *src) {
    s32 len = 0;
    s32 n;
    char *d;
    char *p;
    for (;;) {
        char c = dst[len];
        u8 uc = dst[len];
        if (c == 0) {
            n = 0;
            d = &dst[len];
            p = d;
            while (*src != 0) {
                u8 k;
                *p = *src;
                k = *src;
                if ((u32)(k - 5) < 3) {
                    p[1] = src[1];
                    p[2] = src[2];
                    p += 2;
                    src += 2;
                    n += 2;
                } else if ((s8)k == 11) {
                    p[1] = src[1];
                    p[2] = src[2];
                    p[3] = src[3];
                    p += 3;
                    src += 3;
                    n += 3;
                } else if ((s8)k == 10) {
                    p[1] = src[1];
                    p++;
                    src++;
                    n++;
                    if (*d == 0) {
                        p[1] = src[1];
                        p[2] = src[2];
                        p += 2;
                        src += 2;
                        n += 2;
                    }
                } else if ((s8)k == 13) {
                    p[1] = src[1];
                    p[2] = src[2];
                    p[3] = src[3];
                    p += 3;
                    src += 3;
                    n += 3;
                }
                if ((u32)((u8)*src - 9) < 23) {
                    p[1] = src[1];
                    p++;
                    src++;
                    n++;
                }
                src++;
                p++;
                n++;
            }
            dst[n + len] = 0;
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
