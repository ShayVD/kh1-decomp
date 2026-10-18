/* 00110e68: 2 LCS words off, hand (strict), no context. FINDING (best stays w20's 2w). Loop exact with the original's `amp + t` order once x is a GLOBAL pseudo: here `f32 x = D_002BCB40[3];` before the test (cse shares the load, so the block-0 compare reads x: `lwc1 $f2` / `c.eq.s $f2` vs orig $f0). Diagnosis (lreg + sched dumps): if x is local it ties to amp2 (op0, dies), and the merged qty (8 refs over 5 insns, 3*8/5) beats the *p load qty (4 refs over 3 insns, 2*4/3) for $f1; orig has *p $f1, amp2 $f2, x $f2, which is exactly x global with set_preference to amp2's $f2. Needs x global with no reference outside the loop head (2 deaths, or a use in another block that leaves no code). Tried ~45 shapes: sum spellings, x reused (cos result, D[i] first), second variables, w = *p in head + mul in arms, v = x * *p, block-0 x forms. */
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
    { f32 x = D_002BCB40[3]; if (D_002BCB40[3] != 1.0f) {
        p = D_002BC190;
        for (i = 0; i < 3; i++) {
            ph = &D_002BCB50[i];
            *ph += D_002BCB40[3];
            if (*ph > 3.141592801f) *ph -= 6.2831855f;
            if (*ph < -3.141592801f) *ph += 6.2831855f;
{ f32 v; x = D_002BCB40[i] + (1.0f - D_002BCB40[i]) * cosf(*ph); v = *p * x;
            if (a) { *p++ = v; } else { *p++ = v; } }
        }
    }
    } func_00176110(a);
    func_00176150(a);
}
