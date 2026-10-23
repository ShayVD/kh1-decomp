/* The library functions of src/vm/vm_lib.c that need -fno-strict-aliasing
 * (docs/modules.md "Session 32"). */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/vm_mgr.h"
#include "data/types/text_001c0000_h16.h"
#include "data/pieces/D_003DABD0.h"

/* The entity a VM drives (as in vm_lib.c). */
struct VmObj {
    u8 pad0[0x10];
    f32 pos[3];             /* 0x10 */
    u8 pad1c[0x14];
    f32 rot[3];             /* 0x30: radians */
    u8 pad3c[0x370 - 0x3c];
    u64 flags;              /* 0x370 */
};

extern VmMgr D_00389C90;
void func_00155be0(void *p);

/* Set the entity's rotation from degrees. */
s32 func_001cd600(VmRec *vm) {
    struct VmObj *o = vm->obj;
    VmRec *s = vm;
    struct VmObj *o2;
    s32 i;
    f32 x, y, z;
    if (o) {
        i = vm->sp;
        x = s->stk[i - 2];
        y = s->stk[i - 1];
        z = s->stk[i];
        o2 = s->obj;
        o->rot[0] = x * 3.1415928f / 180.0f;
        o2->rot[1] = y * 3.1415928f / 180.0f;
        o2->rot[2] = z * 3.1415928f / 180.0f;
        o2->flags |= 0x100000000000ULL;
    }
    vm->sp -= 3;
    return 2;
}

/* The callback of the first file func_001cf478 / func_001cf5d0 load (see
 * func_001cf3e0 in vm_lib.c). */
void func_001cf348(void) {
    s32 i;
    s32 n;
    Tbl *base;
    Tbl *t;
    D_00389C90.f3070.x &= ~0x200000000ULL;
    base = D_003DABD0[0];
    n = base->n;
    t = base;
    for (i = 0; i < n; i++) {
        t = base;
        func_00155be0((u8 *)t + *(s32 *)((u8 *)t + i * 4 + 8));
        t = 0;
    }
}
