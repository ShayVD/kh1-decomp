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

typedef struct {
    u8 pad0[0x10];
    u16 h10[8][256];
    s32 cnt[8];
    u8 pad1030[0x3034 - 0x1030];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    s8 *x3040;
    s8 *x3044;
    s32 x3048;
    s32 *x304c;
    s32 x3050;
    s32 *x3054;
    u8 pad3058[4];
    s32 x305c;
    s32 *x3060;
    s32 x3064;
    s32 *x3068;
    u8 pad306c[4];
    u64 f3070;
    u64 f3078;
    u8 pad3080[0xc0];
    s32 x3140;
    u8 pad3144[4];
    s32 x3148;
    f32 f314c;
} Big;

/* Camera state: channels 0-3 (pos, rot, ...) with Hermite moves, plus shake. */

#include "data/pieces/D_0037A378.h"


typedef struct {
    u32 type:8, id:24;
    s32 x4;
    u8 pad8[8];
    f32 x, y, z;
    f32 ang;
} __attribute__((aligned(16))) Msg;

typedef struct { u8 pad[0xdc4]; u32 xdc4; } Save;
typedef struct { u16 t:4, s:4, b1:8; } Ent;
typedef struct { u8 b0, b1, b2; } Ent2;

extern Big D_00389C90;
#include "data/pieces/D_00389C80.h"
#include "data/pieces/D_00388480.h"
#include "data/pieces/D_003C21A8.h"
#include "data/pieces/D_003C3A70.h"
extern CamS D_003C5510;
extern f32 D_002BBDFC;
extern s32 D_002BBAB0, D_002BBAB8, D_002BBAC8;
extern u8 D_003C5660[], D_003C5680[], D_003C56A0[], D_003C56C0[], D_003C56F0[], D_003C5728[], D_003C5750[], D_003C5780[], D_003C57B0[];

s32 func_001c4640(Msg *);
void func_002673b8(f32 *, f32 *);
Save *func_00232cc0(s32);
Ent *func_00147778(s32);
Ent2 *func_00147840(s32);
void *func_0011ef10(s32, void *);
void func_001caa50(void);

/* func_001c6a20 is in src/camera/camera.c. */
void func_001c6a20(void);

/* func_001c8e20, func_001c9308 and func_001c96c0 are in src/camera/camera.c. */
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
s32 func_001cb120(VM *vm) {
    s32 id = vm->stk[vm->sp];
    s32 k = vm->stk[vm->sp - 1];
    Save *sv = func_00232cc0(1);
    Ent *e = func_00147778(id);
    s32 n;
    switch (e->t) {
    case 0:
        n = D_002BBAB0 = e->b1;
        D_002BBAC8 = e->s;
        switch (func_00147840(n)->b2) {
        case 0: D_00388480[D_00389C80] = D_003C5660; break;
        case 12: D_00388480[D_00389C80] = D_003C5680; break;
        case 13: D_00388480[D_00389C80] = D_003C56A0; break;
        case 2: D_00388480[D_00389C80] = D_003C5750; break;
        case 3: D_00388480[D_00389C80] = D_003C5780; break;
        case 4: D_00388480[D_00389C80] = D_003C57B0; break;
        case 1: D_00388480[D_00389C80] = D_003C5728; break;
        }
        break;
    case 1:
        if (e->s == 11) {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_00388480[D_00389C80] = D_003C56F0;
            if (!((sv->xdc4 >> 4) & 1)) {
                sv->xdc4 |= 0x10;
                func_0011ef10(50000, func_001caa50);
            }
        } else {
            D_002BBAB8 = e->b1;
            D_002BBAC8 = e->s;
            D_00388480[D_00389C80] = D_003C56C0;
        }
        break;
    }
    { u16 v = D_00389C80; n = D_00389C90.cnt[k]++; D_00389C90.h10[k][n] = v; }
    vm->sp -= 2;
    return 2;
}
#include "data/bss_0062_mixed.h"
#include "data/data_002B.h"
#include "data/data_003C.h"
#include "data/pieces/D_003C5510.h"
#include "data/pieces/D_002BBDFC.h"
