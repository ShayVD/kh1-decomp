/* func_0010ec08: 15w off (registers only, same size/structure), mode hand/nogcse (also nostrict_nogcse). Off: sched1 interblock-hoists the 'c < 9' sltiu above the 'c < 32' branch, making it a global pseudo that takes a0; so q goes to a3 instead of a0, go to t0 instead of a3, consts 4/15/1 shift t2/t1/t0 -> t3/t2/t1. Tried u8/s32/u16 c, case ranges, if-shapes, loop forms, init orders. */
#include "common.h"
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






