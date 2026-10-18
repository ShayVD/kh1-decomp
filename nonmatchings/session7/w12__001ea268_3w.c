/* 3 words off (hand, strict): only the copy-preheader move order (orig move t2,a2 ... move a3,t2; ours move a3,a2 ... move t2,a3: orig hoists the dst+len test address in loop pass 1, before the giv init). Key fixes vs s6 draft: scan char as s64 (DImode li 11/10/13 do not combine with the copy loop's SImode ones, so loop.c leaves them in place), (u8)(dst[len] - 5) for addiu -5 + andi, dst[n + len] = 0. */
#include "common.h"
void func_001ea268(char *dst, char *src) {
    s32 len = 0; s32 n, i; s64 c;
    while (1) {
        c = dst[len];
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
            dst[n + len] = 0;
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
