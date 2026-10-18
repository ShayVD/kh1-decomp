/* func_001ea268: 3w (w12 draft), hand. Cause: loop dump says insn computing dst+len (the 'dst[len]==0' test address) is 'savings 1 not desirable' in loop pass 1 (inner loop has 129 insns > threshold*savings*lifetime), so it is hoisted only in the rerun pass, after the giv init (move a3,a2 ... move t2,a3). Orig hoisted it in pass 1: the source must make that movable look cheaper/longer-lived or the loop smaller. Pointer temp d=dst+len breaks the giv (81w+). */
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
