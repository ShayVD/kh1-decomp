/* 001df9c0 6w (hand/nostrict, was 13w hand): FP regs and y/z ok; left: z load (stk[i]) and sp store are scheduled after the p->x store (orig before it; nostrict aliasing keeps source order, and moving z before p->x breaks allocation), x/pos.x f0/f1 swap. */
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
s32 func_001df9c0(VM *vm) { O10 *o = vm->u.h.obj; Sub *s = &vm->u.s; s32 i = vm->u.h.sp; V3 *p; O10 *o2; f32 x, y, z, ox;
x = s->stk[i - 2];
o2 = s->obj;
y = s->stk[i - 1];
p = D_0062A428;
ox = o->pos.x;
p->x = x + ox;
z = s->stk[i];
vm->u.h.sp = i - 4;
p->y = o2->pos.y + y;
p->z = o2->pos.z + z;
return 2; }
