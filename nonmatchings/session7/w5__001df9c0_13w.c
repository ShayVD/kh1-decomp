/* func_001df9c0: 13 words off (hand, was 23). Two obj loads now right (o loaded before s = &vm->u.s so CSE/reload_cse keep the s->obj reload); left: sp store scheduled after p->y store (orig before p->x) and y/z FP regs f2/f3 swapped. */
#include "common.h"
/* Script VM handlers: obj at +4, top index at +0x180, value stack at +0x184.
 * The stack is indexed off &vm->u.s (vm+4) with a local copy of sp. */
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
typedef struct { f32 x, y, z; } V3;
typedef struct { u8 pad0[0x10]; V3 pos; } O10;
extern V3 *D_0062A428;
s32 func_001df9c0(VM *vm) {
    O10 *o = vm->u.h.obj; Sub *s = &vm->u.s; s32 i = vm->u.h.sp; V3 *p; O10 *o2; f32 x, y, z;

    x = o->pos.x + s->stk[i - 2];
    o2 = s->obj;
    y = s->stk[i - 1];
    z = s->stk[i];
    p = D_0062A428;
    p->x = x;
    p->y = o2->pos.y + y;
    vm->u.h.sp = i - 4;
    p->z = o2->pos.z + z;
    return 2;
}
