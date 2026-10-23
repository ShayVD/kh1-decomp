/* The library functions of src/vm/vm_lib.c that need nofill (docs/modules.md
 * "Session 32"). */
#include "common.h"
#include "vm/script_vm.h"
#include "vm/vm_mgr.h"

/* The entity a VM drives (as in vm_lib.c). */
struct VmObj {
    u8 pad0[0x10];
    f32 pos[3];             /* 0x10 */
    u8 pad1c[0x14];
    f32 rot[3];             /* 0x30: radians */
    u8 pad3c[0x370 - 0x3c];
    u64 flags;              /* 0x370 */
};

/* func_001cd2d8 (session 9, w7) matched with this message view: u32 val:24
 * (VmMsg's u64 bit-field reads differently in `vm->f20 = m.val`), aligned(8),
 * m.type = 2 as a constant, the dead `d = f * 180 / pi; if (d < 0) d = -d;
 * g = d;` tail (only the libcall compare stays), and vm->sp -= 4 after the
 * f60 / f64 stores.  Written like its sibling func_001d5b58. */
typedef struct { u8 type; u32 val:24; s32 x; s32 a8; s32 ac; f32 v[4]; } __attribute__((aligned(8))) Msg2;
double sqrt(double);
double atan2(double, double);
extern VmFx *D_0038CD3C[];

/* Send message 2 (turn towards the point stk[sp-2..sp]). */
s32 func_001cd2d8(VmRec *vm) {
    Msg2 m;
    f32 v[3];
    f32 len, a, f, g;
    double d;
    vm->fl.x |= 1;
    v[0] = (f32)vm->stk[vm->sp - 2] - vm->obj->pos[0];
    v[1] = (f32)vm->stk[vm->sp - 1] - vm->obj->pos[1];
    v[2] = (f32)vm->stk[vm->sp] - vm->obj->pos[2];
    len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    v[2] /= len;
    v[0] /= len;
    v[1] /= len;

    a = atan2(v[2], v[0]);
    d = a - (f32)atan2(vm->obj->rot[2], vm->obj->rot[0]);
    if (d < 0.0) d = -d;
    f = d;
    if (3.1415928f < f) f = 3.1415928f - (f - 3.1415928f);
    d = f * 180.0f / 3.1415928f;
    if (d < 0.0) d = -d;
    g = d;

    m.type = 2;
    m.val = vm->stk[vm->sp - 3];
    m.v[0] = vm->stk[vm->sp - 2];
    m.x = vm->x0;
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    m.v[3] = 179.99998f;

    func_001c4640((VmMsg *)&m);
    vm->f14[0] = m.v[0];
    vm->f14[1] = m.v[1];
    vm->f14[2] = m.v[2];
    vm->f20 = m.val;
    vm->f60 = 0;
    vm->f64 = 0;
    vm->sp -= 4;
    return 2;
}

/* The fade of effect D_0038CD3C[stk[sp-1]]: 1 - stk[sp] / 180. */
s32 func_001cede8(VmRec *vm) {
    s32 sp = vm->sp;
    VmFx *p = D_0038CD3C[vm->stk[sp - 1]];
    p->f0c = 1.0 - vm->stk[sp] / 180.0f;
    vm->sp = sp - 2;
    return 2;
}
