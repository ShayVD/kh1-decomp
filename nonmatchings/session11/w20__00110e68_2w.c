/* 00110e68: 2 LCS words off, hand (strict), no context (w13 had 5). Shape: load *p in the head, product `v = *p * x` in the head, identical arms on the parameter `a` holding `*p++ = v` (store + addiu = 2 insns: survive to jump2, p keeps 16 refs; a test on p would be folded after the *p dereference). sched2 then places the *p load between sub.s and mul.s as in the original, and GPRs are exact. x written as `(1.0f - D[i]) * cosf(*ph) + D[i]` (t first): the amp2 load qty stays alone, loses $f1 to *p (orig *p f1, amp2 f2). Left: x ties to t (op0) so `add.s $f20,$f20,$f2` vs orig `add.s $f2,$f2,$f20`. With `amp + t` order x ties into the amp2 qty instead, which then beats *p (4w). Variant: x function-level and set in block 0 (`if ((x = D_002BCB40[3]) != 1.0f)`, x global, prefers f2) makes the loop exact; then only the block-0 compare loads into f2 instead of f0 (also 2w). Needs x global (or untied) without a visible extra reference. */
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
{ f32 v; f32 x = (1.0f - D_002BCB40[i]) * cosf(*ph) + D_002BCB40[i]; v = *p * x;
            if (a) { *p++ = v; } else { *p++ = v; } }
        }
    }
    func_00176110(a);
    func_00176150(a);
}
