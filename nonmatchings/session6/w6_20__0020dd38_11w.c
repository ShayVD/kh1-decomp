/* 11 words off: extra 'move s3,a1' copy + lui/addu order; D_003F2C40 base must stay split (lui/addiu then addu), our gcc folds into la unless lo_sum reg has 2 uses. mode hand */
#include "common.h"
typedef struct { s32 a; s32 b; s32 c; s32 d; u32 e; } S2C40;
extern S2C40 D_003F2C40[];
s32 func_001ee698(s32);
s32 func_001efbb8(s32);
void func_00201550(s32, s32, s32, s32, s32, s32, s32, S2C40 *, s32, s32);
void func_002083a8(s32, s32, s32, s32, s32, u32);
void func_0020dd38(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    u32 v = D_003F2C40[a1].e; S2C40 *e = &D_003F2C40[a1];
    s32 r;
    if (t1) r = func_001ee698(t1); else r = func_001efbb8(151);
    func_00201550(a0, 2, 0, a2, a3, t0, a2 + 24, e, r, 15);
    func_002083a8(a0, a2 + 6, a3 + 4, 18, t1, v >> 24);
}
