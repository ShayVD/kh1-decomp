#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
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
typedef W606Mem_304be8 ChrB;
#include "data/pieces/D_00304BE8.h"
s32 func_001db658(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    s32 j;
    for (j = 0; j < D_00304BE8->m[s->stk[i - 1]].sub.x18; j++) {
        u8 *p = (u8 *)((u32)(j + s->stk[i - 1] * 0x74) + (u32)D_00304BE8) + 29;
        if (*p == 0) { *p = s->stk[i]; break; }
        
    }
    vm->u.h.sp -= 2;
    return 2;
}
