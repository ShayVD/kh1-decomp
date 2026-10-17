/* func_0020dd38..func_0020e1c0 (D_003F2C40 group): MATCH in src/hand/n32 and src/hand/n32_nogcse (checkfile); 17-34 words off in src/hand and src/hand/nogcse. */
#include "common.h"
typedef struct { s32 a; s32 b; s32 c; s32 d; u32 e; } S2C40;
extern S2C40 D_003F2C40[];
s32 func_001ee698(s32);
s32 func_001efbb8(s32);
s32 func_001ba228(s32);
s32 func_001ba3f0(s32);
void func_00201550(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32);
void func_002083a8(s32, s32, s32, s32, s32, u32);
void func_00208280(s32, s32, s32, s32, s32, u32);
void func_002016b0(s32, s32, s32, s32);
void func_001fb428(s32, s32, s32, s32, s32, s32, s32, s32, u32);
void func_0020dd38(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    S2C40 *e = &D_003F2C40[a1];
    u32 c = e->e;
    s32 s;
    if (t1 != 0) s = func_001ee698(t1);
    else s = func_001efbb8(151);
    func_00201550(a0, 2, 0, a2, a3, t0, a2 + 24, e, s, 15);
    func_002083a8(a0, a2 + 6, a3 + 4, 18, t1, c >> 24);
}

void func_0020de28(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    func_0020dd38(a0, a1, a2, a3, t0, t1);
    if (t2 >= 2) func_001fb428(a0, 1, 2, 0, a2 + t0 - 5, a3 + 7, t2, 12, D_003F2C40[a1].e);
}

void func_0020ded8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    S2C40 *e = &D_003F2C40[a1];
    u32 c = e->e;
    s32 s;
    if (t1 != 0) s = func_001ee698(t1);
    else s = func_001efbb8(151);
    func_00201550(a0, 2, 0, a2, a3, t0, a2 + 24, e, s, t2);
    func_002083a8(a0, a2 + 6, a3 + 4, 18, t1, c >> 24);
}

void func_0020dfc8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3) {
    u32 c;
    func_0020ded8(a0, a1, a2, a3, t0, t1, t3);
    if (t2 >= 2) { c = D_003F2C40[a1].e; c = (c & 0xFF000000) | 0x64E6FF; func_001fb428(a0, 1, 2, 0, a2 + t0 - 5, a3 + 7, t2, 12, c); }
}

void func_0020e090(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    S2C40 *e = &D_003F2C40[a1];
    u32 c = e->e;
    s32 x;
    s32 n;
    func_00201550(a0, 2, 0, a2, a3, t0, a2 + 24, e, func_001ba228(t1), 15);
    func_00208280(a0, a2 + 6, a3 + 4, 18, 43, c >> 24);
    n = func_001ba3f0(t1);
    x = a2 + t0;
    if (n >= 2) {
        func_002016b0(a0, x + 2, a3 + 2, e->a);
        func_001fb428(a0, 1, 2, 0, x + 35, a3 + 7, n, 12, c);
    }
}

void func_0020e1c0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    S2C40 *e = &D_003F2C40[a1];
    u32 c = e->e;
    func_00201550(a0, 2, 0, a2, a3, t0, a2 + 24, e, func_001ba228(t1), 15);
    func_00208280(a0, a2 + 6, a3 + 4, 18, 43, c >> 24);
}
