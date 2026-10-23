/* The library functions of src/vm/vm_lib.c that need -fno-strict-aliasing
 * and nofill (docs/modules.md "Session 32"). */
#include "common.h"
#include "vm/script_vm.h"

/* The entity a VM drives (as in vm_lib.c). */
struct VmObj {
    u8 pad0[0x10];
    f32 pos[3];             /* 0x10 */
    u8 pad1c[0x14];
    f32 rot[3];             /* 0x30: radians */
    u8 pad3c[0x370 - 0x3c];
    u64 flags;              /* 0x370 */
};

double sin(double);
double cos(double);
double atan2(double, double);

/* Keep turning towards f68 by f6c degrees a step (message 4) until the
 * entity's heading passes f68, then clear flag bit 1. */
void func_001ce4b8(VmRec *vm) {
    struct VmObj *e = vm->obj;
    VmMsg m;
    f32 a = atan2(e->rot[0], e->rot[2]) * 180.0 / 3.1415927410125732421875;
    if ((vm->f6c < 0.0f && a < vm->f68) || (0.0f < vm->f6c && vm->f68 < a)) {
        vm->fl.x &= ~2;
    } else {
        m.type = 4;
        m.val = 1;
        m.x = vm->x0;
        m.v[0] = 0.0f;
        m.v[1] = a + vm->f6c;
        m.v[2] = 0.0f;
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
}

/* Turn to the heading stk[sp-1] (degrees) at speed stk[sp]: message 4, 21
 * or 22. */
s32 func_001ce5f0(VmRec *vm) {
    VmMsg m;
    f32 a;
    double d;
    struct VmObj *e;
    m.type = 4;
    m.val = (u32)(vm->stk[vm->sp] * 2);
    m.x = vm->x0;
    vm->f68 = vm->stk[vm->sp - 1];
    a = vm->f68 * 3.1415928f / 180.0f;
    d = a;
    m.v[0] = sin(d);
    m.v[1] = 0.0f;
    m.v[2] = cos(d);
    m.v[3] = 1.0f;
    vm->fl.x |= 2;
    func_001c4640(&m);
    e = vm->obj;
    if (e) e->flags &= ~0x100000000000ULL;
    vm->sp -= 2;
    return 2;
}

s32 func_001ce750(VmRec *vm) {
    VmMsg m;
    f32 a;
    double d;
    m.type = 21;
    m.val = (u32)(vm->stk[vm->sp] * 2);
    m.x = vm->x0;
    vm->f68 = vm->stk[vm->sp - 1];
    a = vm->f68 * 3.1415928f / 180.0f;
    d = a;
    m.v[0] = sin(d);
    m.v[1] = 0.0f;
    m.v[2] = cos(d);
    m.v[3] = 1.0f;
    vm->fl.x |= 2;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}

s32 func_001ce880(VmRec *vm) {
    VmMsg m;
    f32 a;
    double d;
    m.type = 22;
    m.val = (u32)(vm->stk[vm->sp] * 2);
    m.x = vm->x0;
    vm->f68 = vm->stk[vm->sp - 1];
    a = vm->f68 * 3.1415928f / 180.0f;
    d = a;
    m.v[0] = sin(d);
    m.v[1] = 0.0f;
    m.v[2] = cos(d);
    m.v[3] = 1.0f;
    vm->fl.x |= 2;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}
