/* 8w off (hand, any mode): needs func_00113df8 above (CONTEXT_ONLY, included). Only the printf tail differs: ++D value lands in a2 then move a1 (orig computes it directly in a1). */
#include "common.h"
extern s32 D_004D9328;
extern s32 D_004D932C;
extern char D_0048D010[];
void func_001ed1c8(s32);
void func_001edba0(void);
void func_001104e0(void);
int printf(const char *, ...);
CONTEXT_ONLY void func_00113df8(s32 a) {
    func_001ed1c8(a);
    D_004D932C = a;
}

void func_00113e28(s32 a) {
    if (a == 0) {
        if (--D_004D9328 != 0) return;
        if (D_004D932C == 1) {
            func_00113df8(a);
            func_001edba0();
            func_001104e0();
            func_00113df8(1);
            return;
        }
        func_00113df8(a);
        return;
    }
    func_001ed1c8(2);
    if (++D_004D9328 == 0) { a = ++D_004D9328; printf(D_0048D010, a); return; }
}
