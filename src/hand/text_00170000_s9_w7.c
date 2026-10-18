#include "common.h"

/* func_00176c60: clears two bytes of the 112-byte record (the D_002C5AD2[i][j] pair
   that func_00176cc8 writes) and the 44-byte channel record. The chained assignment
   computes the [2] address first and the [3] address second, so sched1 issues the [3]
   add (it holds the REG_DEAD notes) first and reload_cse turns the [2] add into a copy. */
typedef struct { u8 *a; u8 *b; s32 c; f32 d; f32 e; } F20;
typedef struct { void *h; F20 e[2]; } T44;
extern T44 D_005757B0[];
extern u8 D_002C5AD0[][112];
void *memset(void *, s32, u32);

void func_00176c60(s32 i) {
    D_002C5AD0[i][2] = D_002C5AD0[i][3] = 0;
    memset(&D_005757B0[i], 0, sizeof(T44));
}
