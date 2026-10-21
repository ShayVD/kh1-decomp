/* func_002114f0, func_00214130, func_00214290: all three MATCH (checkfile) in src/hand and src/hand/nogcse when -mabi=n32 is added to the gcc -S step only (assembler flags unchanged). Without it 21/22/24 words differ: the original never folds a symbol into a register add (no "la rd,sym(rs)" / leasi), it keeps lui/addiu base + addu. */
#include "common.h"
#include "data/pieces/D_003F2C40.h"
typedef S2C40_3F2C40 S2C40;
s32 func_001ee698(s32);
s32 func_001efbb8(s32);
s32 func_001ef540(s32);
void func_00201550(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32);
void func_002083a8(s32, s32, s32, s32, s32, u32);
void func_00208280(s32, s32, s32, s32, s32, u32);
void func_002016b0(s32, s32, s32, s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, u32);
s32 func_001ef5c0(s32);
void func_001fb428(s32, s32, s32, s32, s32, s32, s32, s32, u32);

void func_002114f0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    S2C40 *e = &D_003F2C40.s2C40[a1];
    u32 c = e->e;
    s32 s;
    if (t1 != 0) s = func_001ee698(t1);
    else s = func_001efbb8(167);
    func_00201550(a0, 2, 0, a2, a3, t0, a2 + 24, e, s, 15);
    func_002083a8(a0, a2 + 6, a3 + 4, 18, t1, c >> 24);
}

void func_00214130(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    S2C40 *e = &D_003F2C40.s2C40[a1];
    u32 c = e->e;
    func_00201550(a0, 2, 0, a2, a3, t0, a2 + 24, e, func_001ef540(t1 & ~0x80), 15);
    if (!(t1 & 0x80)) {
        func_00208280(a0, a2 + 6, a3 + 4, 18, 53, c >> 24);
        func_00208280(a0, a2 + 6, a3 + 4, 18, 41, c >> 24);
    } else {
        func_00208280(a0, a2 + 6, a3 + 4, 18, 41, c >> 24);
    }
}

void func_00214290(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    S2C40 *e;
    u32 c;
    func_00214130(a0, a1, a2, a3, t0, t1);
    a2 += t0;
    e = &D_003F2C40.s2C40[a1];
    c = e->e;
    func_002016b0(a0, a2 + 2, a3 + 2, e->a);
    a3 += 7;
    func_001f9438(a0, 0, a2 + 6, a3, 81, 12, c);
    func_001fb428(a0, 1, 2, 0, a2 + 40, a3, func_001ef5c0(t1 & ~0x80), 12, c);
}
