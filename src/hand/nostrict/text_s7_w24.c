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

typedef struct { u8 pad[48]; f32 rot[3]; u8 pad3c[880 - 60]; u64 flags; } Obj600;
/* Script VM: obj at +4, top index at +0x180, value stack at +0x184 (indexed off &vm->u.s). */
typedef struct { Obj600 *obj; u8 pad4[0x17c]; s32 stk[92]; } Sub;
typedef struct { s32 x0; union { Sub s; struct { Obj600 *obj; u8 pad[0x178]; s32 sp; } h; } u; } VM;

s32 func_001cd600(VM *vm) {
    Obj600 *o = vm->u.h.obj;
    Sub *s = &vm->u.s;
    Obj600 *o2;
    s32 i;
    f32 x, y, z;
    if (o) {
        i = vm->u.h.sp;
        x = s->stk[i - 2];
        y = s->stk[i - 1];
        z = s->stk[i];
        o2 = s->obj;
        o->rot[0] = x * 3.1415928f / 180.0f;
        o2->rot[1] = y * 3.1415928f / 180.0f;
        o2->rot[2] = z * 3.1415928f / 180.0f;
        o2->flags |= 0x100000000000ULL;
    }
    vm->u.h.sp -= 3;
    return 2;
}

