/* 20 words off (same size): D_003F2C40 address folds into la; original keeps split base (needs 2-use lo_sum). mode hand */
#include "common.h"
typedef struct { s32 a; s32 b; s32 c; s32 d; u32 e; } S2C40;
extern S2C40 D_003F2C40[];
void func_0020dd38(s32, s32, s32, s32, s32, s32, s32);
void func_001fb428(s32, s32, s32, s32, s32, s32, s32, s32, s32);
static inline void inl(s32 o, S2C40 *e, s32 x, s32 y, s32 n) {
    if (n >= 2) func_001fb428(o, 1, 2, 0, x - 5, y + 7, n, 12, e->e);
}
void func_0020de28(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    func_0020dd38(a0, a1, a2, a3, t0, t1, t2);
    inl(a0, &D_003F2C40[a1], a2 + t0, a3, t2);
}
