/* 00110e68: 5 LCS (posoff 6), hand (strict), no context. New: p (the D_002BC190 walker) needs priority over &amp[i] (.571): identical arms on p around the *p store, `{ f32 x = ...cosf(*ph); if (p) { *p *= x; } else { *p *= x; } }`, raise p to 16 refs/110 (.582) and give the original s0=p, s1=&amp[i], s2=i (odd source, jump2 re-merges the arms). Left: the *p load now sits in the arm, after the add (original: lwc1 $f1,0(s0) before add.s, x in f2, *p in f1). Loading *p before the arms drops p back to 13-14 refs. */
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
            { f32 x = D_002BCB40[i] + (1.0f - D_002BCB40[i]) * cosf(*ph);
            if (p) { *p *= x; } else { *p *= x; } }
            p++;
        }
    }
    func_00176110(a);
    func_00176150(a);
}
