/* wm.x func_00f4f9c8: matched by hand. */
#include "ovl.h"

char *func_00f632d0(s32);

void func_00f4f9c8(char *s, s32 kind, s32 idx, s32 lim) {
    s32 base, q, r, len;
    char *t;
    while (*s)
        s++;
    q = idx / 5;
    r = idx % 5;
    switch (kind) {
    case 0:
        base = 15;
        lim = 10;
        break;
    case 1:
        base = 25;
        lim = 7;
        break;
    case 2:
        base = 32;
        lim = 10;
        break;
    case 3:
        base = 42;
        lim = 7;
        break;
    case 4:
        base = 49;
        lim = 8;
        break;
    case 5:
        base = 57;
        lim = 7;
        break;
    }
    if (q >= lim) {
        *s++ = 0x81;
        *s++ = 0x40;
        *s++ = 0;
    }
    t = func_00f632d0(base + q);
    for (len = 0; t[len]; len++)
        ;
    len /= 2;
    if (r >= len) {
        *s++ = 0x81;
        *s++ = 0x40;
        *s++ = 0;
    }
    t += r;
    *s++ = t[0];
    *s++ = t[1];
    *s = 0;
}
