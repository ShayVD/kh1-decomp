/* 3 ndiff (strict, src/hand, CONTEXT_ONLY func_001efba8 above): pad!=0 branch: our 'move a1,sp' lands in the bnez a1 delay slot, original has 'li a3,10' there and 'move a1,sp' in the branch body (q init must come after the hoisted 10). */
#include "common.h"
extern s32 D_003E8E04;
CONTEXT_ONLY s32 func_001efba8(void) { return D_003E8E04; }

s32 func_001f0448(s32 n, s32 pad, s32 val, s32 w) {
    s32 buf[10];
    s32 neg = 0;
    s32 cnt;
    s32 i;
    s32 ws = w * 16;
    if (val == 0) {
        if (n == 0 || pad == 0) {
            buf[0] = 0;
            cnt = 1;
        } else {
            for (i = n - 1; i >= 0; i--) buf[i] = 0;
            cnt = n;
        }
    } else {
        if (val < 0) { val = -val; neg = 1; }
        if (n == 0) {
            cnt = 0;
            do { buf[cnt++] = val % 10; val /= 10; } while (val != 0 && cnt < 10);
        } else {
            cnt = 0;
            if (pad == 0) {
                do { buf[cnt++] = val % 10; val /= 10; } while (val != 0 && cnt < n);
            } else {
                s32 *q = buf; do { if (val == 0) { *q = 0; q++; cnt++; } else { cnt++; *q = val % 10; val /= 10; q++; } } while (cnt < n);
            }
        }
    }
    return (cnt + neg) * (ws + func_001efba8()) >> 4;
}
