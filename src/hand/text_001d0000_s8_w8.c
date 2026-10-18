#include "common.h"
typedef struct { void *obj; u8 pad4[0x178]; s32 sp; s32 stk[100]; } Sub;
typedef struct { s32 x0; Sub s; } VM;
typedef struct { s32 key; s32 pad; u64 d[5]; } E48;
typedef struct { u8 pad0[0x3178]; s32 n; s32 pad317c; E48 e[8]; } Big63;
extern Big63 D_00389C90;
s32 func_001d63e8(VM *vm) {
    s32 i, j, k;
    for (i = 0; i < D_00389C90.n; i = k) {
        if (D_00389C90.e[i].key == vm->s.stk[vm->s.sp]) {
            k = i + 1;
            if (k < D_00389C90.n) {
                for (j = k; j < D_00389C90.n; j++) D_00389C90.e[j - 1] = D_00389C90.e[j];
                k = i;
                D_00389C90.n--;
            } else D_00389C90.n--;
        } else k = i + 1;
    }
    vm->s.sp--;
    return 2;
}
