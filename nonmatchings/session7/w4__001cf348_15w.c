/* 15w off (hand/nostrict_nogcse; s6 draft 19w): 'if (n <= 0) return; i = 0; do {...} while (++i < n);' gets move s0,zero out of the prologue. Still off: prologue sd order (orig s0,s2,s1), blez slot takes 't = base' copy instead of i = 0, and i++ scheduled before the addu. -fno-schedule-insns2 gives 11. */
#include "common.h"
typedef struct { u8 pad[12400]; u64 d12400; } Big3;
extern Big3 D_00389C90;
typedef struct { s32 x0; s32 n; s32 off[1]; } Tbl;
extern Tbl *D_003DABD0;
void func_00155be0(void *p);
void func_001cf348(void) {
    Tbl *base;
    Tbl *t;
    s32 i, n;
    D_00389C90.d12400 &= ~0x200000000ULL;
    base = D_003DABD0;
    n = base->n;
    t = base;
    if (n <= 0) return;
    i = 0;
    do {
        func_00155be0((u8 *)t + *(s32 *)(i * 4 + (u8 *)t + 8));
        t = base;
    } while (++i < n);
}
