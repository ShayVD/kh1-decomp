/* 15w off (hand, strict): s0/s1/s2 permutation only (orig s0=p, s1=&amp[i], s2=i). */
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
            *p *= D_002BCB40[i] + (1.0f - D_002BCB40[i]) * cosf(*ph);
            p++;
        }
    }
    func_00176110(a);
    func_00176150(a);
}
