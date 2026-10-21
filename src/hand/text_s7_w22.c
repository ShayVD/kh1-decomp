#include "common.h"

typedef struct { u8 pad[12400]; u64 d12400; } Big3;
extern Big3 D_00389C90;
typedef struct { s32 x0; u8 n; s32 off[1]; } Tbl;
#include "data/pieces/D_003DABD4.h"
void func_00155be0(void *p);

/* func_001cf3e0: t is copied from base at the loop top and killed (t = 0) after the call:
   two sets in the loop stop loop.c hoisting the copy / strength-reducing t->off[i], and the
   mention outside the loop makes cse keep t (not base) as the canonical register. The copy
   at the top fills sched2's cycle-0 slot (sll; addu; addiu order); reorg steals it into bnez. */
void func_001cf3e0(void) {
    s32 i;
    s32 n;
    Tbl *base;
    Tbl *t;
    D_00389C90.d12400 &= ~0x400000000ULL;
    base = ((Tbl *)D_003DABD4);
    n = base->n;
    t = base;
    for (i = 0; i < n; i++) {
        t = base;
        func_00155be0((u8 *)t + *(s32 *)((u8 *)t + i * 4 + 8));
        t = 0;
    }
}
