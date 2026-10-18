/* func_001cf3e0: 2 words off (was 19), hand/nogcse or hand/nostrict_nogcse. Only the loop body order is off: ours sll; addiu s0 (i++); addu v0,v1,v0; orig sll; addu v0,v0,v1; addiu s0. sched1 issues i++ beside the sll; every loop form/index expression/i type tried gives the same. flagsweep: nothing better. */
#include "common.h"
typedef struct { u8 pad[12400]; u64 d12400; } Big3;
extern Big3 D_00389C90;
typedef struct { s32 x0; u8 n; s32 off[1]; } Tbl;
extern Tbl *D_003DABD4;
void func_00155be0(void *p);

void func_001cf3e0(void) {
    s32 i, n;
    Tbl *base;
    Tbl *t;
    D_00389C90.d12400 &= ~0x400000000ULL;
    base = D_003DABD4;
    n = base->n;
    i = 0;
    if (n != 0) {
        t = base;
        do {
            func_00155be0((u8 *)t + t->off[i]);
            t = base;
        } while (++i < n);
    }
}
