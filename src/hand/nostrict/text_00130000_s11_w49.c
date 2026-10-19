#include "common.h"
/* 00135a68 (hand/nostrict), s11w49. FLAGGED dead tests: x = (s32)v at entry and three
   `if (x != (s32)v) { k = 2; k = 3; } else k = 1;` between the loop-2 stores (always false; k is
   loop 1's temp, dead in loop 2). The else and the two-set arm keep jump1 from if-converting and
   cse1 from skipping, so cse1/gcse see four store blocks (separate v+i*16 pseudos); gcse cprop
   copy-propagates x to v's register, cse2 folds (ne v v) and the jump pass after cse2 deletes the
   tests, so sched1 sees one block. `o = i * 16; *(f32 *)((s32)v + o)` gives the v+i16 operand
   order of v[i][0]; one counter i for both loops. */
void func_00135a68(f32 (*v)[4], f32 r, f32 h) {
    s32 i, k, o, x;
    x = (s32)v;
    if (0.0f <= h) {
        h = -h;
        for (i = 0; i < 8; i++) {
            k = ((i & 1) << 1) - 1;
            v[i][0] = r * k;
            v[i][1] = h * ((i & 2) >> 1);
            v[i][2] = r * (((i & 4) >> 1) - 1);
            v[i][3] = 1.0f;
        }
    } else {
        for (i = 0; i < 8; i++) {
            o = i * 16;
            *(f32 *)((s32)v + o) = r * (((i & 1) << 1) - 1);
            if (x != (s32)v) { k = 2; k = 3; } else k = 1;
            v[i][1] = h * ((i & 2) - 1);
            if (x != (s32)v) { k = 2; k = 3; } else k = 1;
            v[i][2] = r * (((i & 4) >> 1) - 1);
            if (x != (s32)v) { k = 2; k = 3; } else k = 1;
            v[i][3] = 1.0f;
        }
    }
}
