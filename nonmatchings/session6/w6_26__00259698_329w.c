/* func_00259698 (libkernl printf engine), sdk/gcc991111 (991111a), rodata jump table D_004921A0
 * (check with rr.py 004921A0). 329 words off, but only ~37 instructions differ after
 * normalising registers: the original keeps the format pointer in two registers (s0 at the
 * loop top/print pointer, s2 as the walker, with "s2 = s0+1; s0 = s2" copies); this single
 * variable version uses s2 for both and s0/s1 swap for p/v. Two-variable rewrites
 * (p698e/h in the work dir) made the structure worse. */
#include "common.h"

typedef char *va_list;
typedef void (*PutFn)(int);
extern PutFn D_0046AE50;
int DIntr(void);
int EIntr(void);
void func_00259530(double);

int func_00259698(const char *fmt, va_list ap) {
    char buf[32];
    char *pad;
    char *p;
    const char *s;
    int size;
    int w;
    long v;
    int intr = DIntr();

    while (*fmt) {
        pad = 0;
        size = 0;
        if (*fmt == '%') {
        again:
            fmt++;
            switch (*fmt) {
            case '0':
                w = fmt[1] - '0';
                if ((u8) w < 10) {
                    if ((unsigned) (fmt[2] - '0') < 10) {
                        w = w * 10 + (fmt[2] - '0');
                        fmt += 2;
                        if (w >= 32)
                            w = 31;
                    } else {
                        fmt++;
                    }
                    pad = &buf[31 - w];
                    while (w > 0) {
                        buf[31 - w] = '0';
                        w--;
                    }
                }
                goto again;
            case 'l':
                size = 'l';
                goto again;
            case 'h':
                size = 'h';
                goto again;
            case 'o':
                if (size == 'l') {
                    ap += 8;
                    v = *(unsigned long *) (ap - 8);
                } else if (size == 'h') {
                    ap += 8;
                    v = *(u16 *) (ap - 8);
                } else {
                    ap += 8;
                    v = *(u32 *) (ap - 8);
                }
                p = &buf[31];
                *p = 0;
                if (v == 0) {
                    *--p = '0';
                } else {
                    while (v) {
                        *--p = (v & 7) + '0';
                        v = (unsigned long) v >> 3;
                    }
                }
                fmt++;
                if (pad && pad < p)
                    p = pad;
                while (*p)
                    D_0046AE50(*p++);
                break;
            case 'x':
                if (size == 'l') {
                    ap += 8;
                    v = *(unsigned long *) (ap - 8);
                } else if (size == 'h') {
                    ap += 8;
                    v = *(u16 *) (ap - 8);
                } else {
                    ap += 8;
                    v = *(u32 *) (ap - 8);
                }
                p = &buf[31];
                *p = 0;
                if (v == 0) {
                    *--p = '0';
                } else {
                    while (v) {
                        unsigned long d = v & 15;
                        *--p = d < 10 ? d + '0' : d + 'a' - 10;
                        v = (unsigned long) v >> 4;
                    }
                }
                fmt++;
                if (pad && pad < p)
                    p = pad;
                while (*p)
                    D_0046AE50(*p++);
                break;
            case 'd':
                if (size == 'l') {
                    ap += 8;
                    v = *(long *) (ap - 8);
                } else if (size == 'h') {
                    ap += 8;
                    v = *(s16 *) (ap - 8);
                } else {
                    ap += 8;
                    v = *(s32 *) (ap - 8);
                }
                p = &buf[31];
                *p = 0;
                if (v == 0) {
                    *--p = '0';
                } else {
                    if (v < 0) {
                        v = -v;
                        D_0046AE50('-');
                    }
                    while (v) {
                        *--p = v % 10 + '0';
                        v /= 10;
                    }
                }
                fmt++;
                if (pad && pad < p)
                    p = pad;
                while (*p)
                    D_0046AE50(*p++);
                break;
            case 'u':
                if (size == 'l') {
                    ap += 8;
                    v = *(unsigned long *) (ap - 8);
                } else if (size == 'h') {
                    ap += 8;
                    v = *(u16 *) (ap - 8);
                } else {
                    ap += 8;
                    v = *(u32 *) (ap - 8);
                }
                p = &buf[31];
                *p = 0;
                if (v == 0) {
                    *--p = '0';
                } else {
                    while (v) {
                        *--p = (unsigned long) v % 10 + '0';
                        v = (unsigned long) v / 10;
                    }
                }
                fmt++;
                if (pad && pad < p)
                    p = pad;
                while (*p)
                    D_0046AE50(*p++);
                break;
            case 'e':
            case 'f': {
                float f;
                ap += 8;
                f = *(float *) (ap - 8);
                if (f == 0) {
                    fmt++;
                    D_0046AE50('0');
                } else {
                    fmt++;
                    func_00259530(f);
                }
                break;
            }
            case 's':
                ap += 8;
                p = *(char **) (ap - 8);
                if (*p == 0) {
                    fmt++;
                    D_0046AE50('(');
                    D_0046AE50('n');
                    D_0046AE50('u');
                    D_0046AE50('l');
                    D_0046AE50('l');
                    D_0046AE50(')');
                } else {
                    fmt++;
                    do
                        D_0046AE50(*p++);
                    while (*p);
                }
                break;
            case 'c':
                ap += 8;
                v = *(char *) (ap - 8);
                fmt++;
                D_0046AE50(v);
                break;
            default:
                fmt++;
                break;
            }
        } else {
            D_0046AE50(*fmt);
            fmt++;
        }
    }
    if (intr)
        EIntr();
}
