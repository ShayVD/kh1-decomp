#include "common.h"
/* func_0010ec08: matches with -fno-gcse -fno-sched-interblock (session 7 flag sweep). */
extern void *memcpy(void *, const void *, u32);

void func_0010ec08(u8 *src, u8 *dst, s32 n) {
    u8 *buf[32];
    u8 **q;
    s32 i, go;
    u32 c;
    u8 *s;

    for (i = 31; i >= 0; i--) buf[i] = 0;
    *dst = 0;
    buf[0] = src;
    q = &buf[1];
    s = src;
    go = 1;
    while (go) {
        c = *s;
        if (c < 32) {
            if (c < 9) {
                if (c != 0) {
                    if (c == 4) {
                        go = 0;
                        *q++ = s + 1;
                    }
                } else {
                    go = 0;
                    *q++ = s + 1;
                }
            } else {
                s++;
                if (c == 15 && *s == 1) {
                    *q++ = s + 1;
                }
            }
        }
        s++;
    }
    if (buf[n + 1] && buf[n]) {
        memcpy(dst, buf[n], buf[n + 1] - buf[n]);
        dst[buf[n + 1] - buf[n]] = 0;
    }
}






