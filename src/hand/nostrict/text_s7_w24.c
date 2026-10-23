#include "common.h"

typedef struct { u8 pad[12400]; u64 d12400; } Big3;
extern Big3 D_00389C90;
typedef struct { s32 x0; s32 n; s32 off[1]; } Tbl;
#include "data/pieces/D_003DABD0.h"
void func_00155be0(void *p);

void func_001cf348(void) {
    s32 i;
    s32 n;
    Tbl *base;
    Tbl *t;
    D_00389C90.d12400 &= ~0x200000000ULL;
    base = D_003DABD0[0];
    n = base->n;
    t = base;
    for (i = 0; i < n; i++) {
        t = base;
        func_00155be0((u8 *)t + *(s32 *)((u8 *)t + i * 4 + 8));
        t = 0;
    }
}

/* func_001cd600 is in src/vm/vm_lib.nostrict.c. */

