/* gb.x func_00f40830: matched by hand. */
#include "ovl.h"

char *func_00f3c1d8(s32);

void func_00f40830(char *buf, s32 type, s32 val, s32 lim, s32 base) {
    s32 q;
    s32 r;
    s32 n;
    char *s;

    while (*buf) {
        buf++;
    }
    q = val / 5;
    r = val % 5;
    switch (type) {
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
        *buf++ = 0x81;
        *buf++ = 0x40;
        *buf++ = 0;
    }
    s = func_00f3c1d8(base + q);
    n = 0;
    while (s[n]) {
        n++;
    }
    n /= 2;
    if (r >= n) {
        *buf++ = 0x81;
        *buf++ = 0x40;
        *buf++ = 0;
    }
    s += r * 2;
    *buf++ = s[0];
    *buf++ = s[1];
    *buf = 0;
}
