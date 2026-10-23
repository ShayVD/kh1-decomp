/* The library functions of src/vm/vm_lib.c that need -fno-strict-aliasing
 * (docs/modules.md "Session 32"). */
#include "common.h"
#include "vm/vm_obj.h"
#include "data/types/vm_rec.h"
#include "vm/vm_mgr.h"
#include "data/types/text_001c0000_h16.h"
#include "data/pieces/D_003DABD0.h"


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
        o2->f370.flags |= 0x100000000000ULL;
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

/* func_001d0380 .. func_001d9480 are in vm_lib.c. */

extern f32 D_002BBDFC;

/* Step the turn func_001d95f0 starts: rot from f2c to f38 over f44 (time
 * f48, as f32); at the end clear flag 12.  Kept the auto file's body, fields
 * by offset (VMF: 0x2c f2c, 0x38 f38, 0x44 f44, 0x48 f48, obj's 0x30 rot):
 * written on VmRec / struct VmObj the struct accesses schedule differently
 * (51 words off). */
#define VMF(p, t, off) (*(t *)((s8 *)(p) + (off)))
void func_001d9510(VmRec *vm) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f2;
    void *temp_v0;
    void *temp_v1;

    temp_f2 = VMF(vm, f32, 0x44);
    temp_f0 = VMF(vm, f32, 0x48) + D_002BBDFC;
    VMF(vm, f32, 0x48) = temp_f0;
    if (temp_f2 < temp_f0) {
        temp_v1 = VMF(vm, void *, 4);
        VMF(temp_v1, f32, 0x30) = (f32) VMF(vm, f32, 0x38);
        VMF(temp_v1, f32, 0x34) = (f32) VMF(vm, f32, 0x3C);
        VMF(temp_v1, f32, 0x38) = (f32) VMF(vm, f32, 0x40);
        VMF(vm, s64, 0x328) = (s64) (VMF(vm, s64, 0x328) & ~0x1000);
        return;
    }
    temp_f1 = VMF(vm, f32, 0x2C);
    temp_v0 = VMF(vm, void *, 4);
    VMF(temp_v0, f32, 0x30) = (f32) (temp_f1 + ((VMF(vm, f32, 0x38) - temp_f1) * (temp_f0 / temp_f2)));
    temp_f1_2 = VMF(vm, f32, 0x30);
    VMF(temp_v0, f32, 0x34) = (f32) (temp_f1_2 + ((VMF(vm, f32, 0x3C) - temp_f1_2) * (VMF(vm, f32, 0x48) / VMF(vm, f32, 0x44))));
    temp_f1_3 = VMF(vm, f32, 0x34);
    VMF(temp_v0, f32, 0x38) = (f32) (temp_f1_3 + ((VMF(vm, f32, 0x40) - temp_f1_3) * (VMF(vm, f32, 0x48) / VMF(vm, f32, 0x44))));
}
