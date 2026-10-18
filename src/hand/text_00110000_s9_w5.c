#include "common.h"

extern s32 D_004D9328;
extern s32 D_004D932C;
extern char D_0048D010[]; /* "ERROR:sound pause\n" */
void func_001ed1c8(s32);
void func_001edba0(void);
void func_001104e0(void);
int printf(const char *, ...);

CONTEXT_ONLY void func_00113df8(s32 a) {
    func_001ed1c8(a);
    D_004D932C = a;
}

/* func_00113e28: printf takes only the format (the string has no %d); the
 * value in a1 is just D+2 allocated to the first free register. */
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
    if (++D_004D9328 != 0) return;
    D_004D9328++;
    printf(D_0048D010);
}
