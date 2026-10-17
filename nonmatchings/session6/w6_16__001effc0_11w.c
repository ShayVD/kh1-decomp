/* 11w off (all modes; rodata jtbl at 0x490960, test with wqb03_rr.py 00490960): only s-reg permutation: orig s1=jumptable hi, s2=n, s3=tbl; ours s1=n, s2=tbl, s3=jt (global-alloc priority). strict hand */
#include "common.h"
extern u8 *D_003E8E08[];

s32 func_001effc0(u8 *s) {
    s32 n = 0;
    u8 **tbl = D_003E8E08;
    u8 *q;
    for (;;) {
        if (*s < 21) {
            switch (*s) {
            case 1:
                n++;
            case 4: case 5: case 6: case 9:
            default:
            inc:
                s++;
                break;
            case 10:
                if (tbl[0]) n += func_001effc0(tbl[0]);
                tbl++;
                goto inc;
            case 11:
                tbl++;
                s += 4;
                break;
            case 8:
                s += 5;
                break;
            case 7: case 12: case 15:
                s += 2;
                break;
            case 13: case 14: case 17: case 18: case 19: case 20:
                s += 3;
                break;
            case 0: case 2: case 3: case 16:
                return n;
            }
        } else {
            if (*s == 24) s += 2;
            else s = (*s < 32) ? s + 2 : s + 1;
            n++;
        }
    }
}
