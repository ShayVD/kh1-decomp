#include "common.h"

/* Script VM: obj at +4, sp at +0x180, value stack at +0x184. The stack is
 * indexed off &vm->s (vm+4). A plain struct, not a union with u8 padding:
 * a union access gets the union's alias set (which contains char), so it
 * would conflict with the float stores like -fno-strict-aliasing. */
typedef struct { void *obj; u8 pad4[0x178]; s32 sp; s32 stk[100]; } Sub;
typedef struct { s32 x0; Sub s; } VM;
typedef struct { f32 x, y, z; } V3;
typedef struct { u8 pad0[0x10]; V3 pos; } O10;
extern V3 *D_0062A428; /* src/data/bss_0062.c: u8 D_0062A428[0x8] */

s32 func_001df9c0(VM *vm) {
    O10 *o = vm->s.obj;
    Sub *s = &vm->s;
    s32 i = vm->s.sp;
    V3 *p;
    O10 *o2;
    f32 x, y, z, ox;

    x = s->stk[i - 2];
    o2 = s->obj;
    y = s->stk[i - 1];
    p = D_0062A428;
    ox = o->pos.x;
    z = s->stk[i];
    vm->s.sp = i - 4;
    p->x = ox + x;
    p->y = o2->pos.y + y;
    p->z = o2->pos.z + z;
    return 2;
}
