/* func_00110e68: mode hand (strict), no context. s11w38 from w20's 2w, FLAGGED:
 *  - identical arms `if (a) { *p++ = v; } else { *p++ = v; }` (w20: keep p at 16 refs);
 *  - x written `D[i] + (1 - D[i]) * cosf(*ph)` (amp + t order, w25);
 *  - dead FP-condition set `if (x < p[-1]) v = 0;` at the end of the loop body (v is dead; flow2 deletes the
 *    empty test and the compare). The compare reads x in a block after the arms, so x is a GLOBAL pseudo
 *    (not tied to the dying amp2 load: *p gets $f1, amp2/x $f2 as in the original), and the p[-1] load adds
 *    a 17th ref to p, so p beats &D[i] for s0 in global-alloc (an `x < 1.0f` test lengthens p's life
 *    without the extra ref and loses s0: 15w). */
#include "common.h"
extern f32 D_002BCB40[4];
extern f32 D_002BCB50[3];
extern f32 D_002BC190[];
f32 cosf(f32);
void func_002675a8(f32 *, s32);
void func_00176110(s32);
void func_00176150(s32);

void func_00110e68(s32 a) {
    s32 i;
    f32 *p;
    f32 *ph;

    p = D_002BC190;
    func_002675a8(D_002BC190, a);
    if (D_002BCB40[3] != 1.0f) {
        p = D_002BC190;
        for (i = 0; i < 3; i++) {
            ph = &D_002BCB50[i];
            *ph += D_002BCB40[3];
            if (*ph > 3.141592801f) *ph -= 6.2831855f;
            if (*ph < -3.141592801f) *ph += 6.2831855f;
            {
                f32 v;
                f32 x = D_002BCB40[i] + (1.0f - D_002BCB40[i]) * cosf(*ph);
                v = *p * x;
                if (a) {
                    *p++ = v;
                } else {
                    *p++ = v;
                }
                if (x < p[-1]) v = 0; /* FLAGGED dead set */
            }
        }
    }
    func_00176110(a);
    func_00176150(a);
}
