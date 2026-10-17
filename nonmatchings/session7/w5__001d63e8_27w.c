/* func_001d63e8 (hand): 27 words, all register numbering only (structure, loop hoist of &vm->u.s exact). Orig vm=t3, D copy=t4, inner D=t5, k=a0, sp=a1, D hi lui a2; ours vm=t5, D=t3, inner D=t4, k=a1, sp=a2, lui a1. Writing the stack as vm->u.s.stk[...] (no Sub* local) gives the orig's loop-hoisted addiu t6,vm,4. */
#include "common.h"
typedef struct {
    void *obj;
    u8 pad4[0x17c];
    s32 stk[105];
} Sub;
typedef struct {
    s32 x0;
    union {
        Sub s;
        struct { void *obj; u8 pad[0x178]; s32 sp; } h;
    } u;
} VM;
typedef struct { s32 key; s32 pad; u64 d[5]; } E48;
typedef struct { u8 pad0[0x3178]; s32 n; s32 pad317c; E48 e[8]; } Big63;
extern Big63 D_00389C90;
s32 func_001d63e8(VM *vm) {
    s32 i, j, k, m;
    
    for (i = 0; i < D_00389C90.n; i = k) {
        k = i + 1;
        if (D_00389C90.e[i].key == vm->u.s.stk[vm->u.h.sp]) {
            m = D_00389C90.n; if (k < m) { j = k; do { D_00389C90.e[j - 1] = D_00389C90.e[j]; j++; } while (j < D_00389C90.n); k = i; m = D_00389C90.n; } D_00389C90.n = m - 1;

        }
    }
    vm->u.h.sp--;
    return 2;
}
