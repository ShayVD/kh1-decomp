#include "common.h"
typedef struct { s32 a; s32 b; s32 c; s32 d; u32 e; } S2C40;
extern S2C40 D_003F2C40[];
void func_0020dd38(s32, s32, s32, s32, s32, s32, s32);
void func_001fb428(s32, s32, s32, s32, s32, s32, s32, s32, s32);

static inline void inl(s32 a0, s32 x, s32 y, s32 n, S2C40 *e) {
    if (n >= 2) func_001fb428(a0, 1, 2, 0, x, y, n, 12, e->e);
}

void func_0020de28(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    func_0020dd38(a0, a1, a2, a3, t0, t1, t2);
    inl(a0, a2 + t0 - 5, a3 + 7, t2, &D_003F2C40[a1]);
}
