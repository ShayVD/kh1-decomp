#include "common.h"
#include "data/types/vm_rec.h"
#include "platform/math.h"

#include "data/types/text_001c0000_b10.h"

typedef struct VmObj {
    u8 pad0[0x10];
    f32 x10, x14, x18;
    u8 pad1c[0x14];
    f32 x30, x34, x38;
} Obj;

/* Script VM instance (0x350 bytes). */
typedef VmRec VM;


/* Camera state: channels 0-3 (pos, rot, ...) with Hermite moves, plus shake. */

#include "data/pieces/D_0037A378.h"


typedef struct {
    u32 type:8, id:24;
    s32 x4;
    u8 pad8[8];
    f32 x, y, z;
    f32 ang;
} __attribute__((aligned(16))) Msg;

#include "data/pieces/D_003C21A8.h"
#include "data/pieces/D_003C3A70.h"
extern CamS D_003C5510;
extern f32 D_002BBDFC;

s32 func_001c4640(Msg *);
void func_002673b8(f32 *, f32 *);

/* func_001c6a20 is in src/camera/camera.c. */
void func_001c6a20(void);

/* func_001c8e20, func_001c9308 and func_001c96c0 are in src/camera/camera.c,
 * func_001cb120 in src/msgwin/msgwin.c. */
s32 func_001d2c68(VM *vm) {
    Vec v;
    Msg m;
    f32 a, t, r, s, dx, dz;
    if ((*(Bits_37a378 *)&D_0037A378).b0) {
        m.type = 3;
        m.id = 0;
        m.x4 = vm->x0;
        m.x = vm->stk[vm->sp - 2];
        m.y = vm->stk[vm->sp - 1];
        m.z = vm->stk[vm->sp];
        m.ang = 1.0f;
        func_001c4640(&m);
        vm->sp -= 4;
        return 6;
    }
    a = vm->stk[vm->sp - 3];
    t = D_002BBDFC;
    r = PlatSqrtf(a * t / 0.48469386f);
    r = (r + PlatSqrtf((a + (vm->obj->x14 - (f32)vm->stk[vm->sp - 1])) * t / 0.48469386f)) * 0.5f;
    dx = (f32)vm->stk[vm->sp - 2] - vm->obj->x10;
    dz = (f32)vm->stk[vm->sp] - vm->obj->x18;
    s = PlatSqrtf(dx * dx + dz * dz) / r;
    m.type = 4;
    m.id = 0;
    m.x4 = vm->x0;
    m.x = -(vm->obj->x10 - (f32)vm->stk[vm->sp - 2]);
    m.y = 0.0f;
    m.z = -(vm->obj->x18 - (f32)vm->stk[vm->sp]);
    m.ang = 1.0f;
    vm->fl.b.b1 = 1;
    func_001c4640(&m);
    m.type = 12;
    m.id = 0;
    m.x4 = vm->x0;
    m.x = -(vm->obj->x10 - (f32)vm->stk[vm->sp - 2]);
    m.y = a;
    m.z = -(vm->obj->x18 - (f32)vm->stk[vm->sp]);
    m.ang = 1.0f;
    v[0] = -(vm->obj->x10 - (f32)vm->stk[vm->sp - 2]);
    v[1] = 0.0f;
    v[2] = -(vm->obj->x18 - (f32)vm->stk[vm->sp]);
    v[3] = 1.0f;
    func_002673b8(v, v);
    m.x = v[0] = v[0] * s;
    m.z = v[2] = v[2] * s;
    func_001c4640(&m);
    vm->f20 = s;
    vm->fl.b.b2 = 1;
    vm->f14[0] = vm->stk[vm->sp - 2];
    vm->f14[1] = vm->stk[vm->sp - 1];
    vm->f14[2] = vm->stk[vm->sp];
    vm->sp -= 4;
    vm->x2f4 = r * (2.0f - D_002BBDFC + 2.0f);
    return 6;
}

/* needs make: uses rodata */
#include "data/bss_0062_mixed.h"
#include "data/data_002B.h"
#include "data/data_003C.h"
#include "data/pieces/D_003C5510.h"
#include "data/pieces/D_002BBDFC.h"
