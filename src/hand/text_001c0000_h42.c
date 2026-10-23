#include "common.h"
#include "data/types/vm_rec.h"
#include "data/bss_0062.h"

typedef struct VmObj {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x370 - 0x1c];
    u8 col[4];
} Ent2;

/* Script VM context (same layout as h15/h16): pc at +0x17c, sp at +0x180,
   value stack at +0x184, flags at +0x328. */
typedef VmRec VM;


typedef struct Fx {
    u8 pad0[0x30];
    f32 v30[4];
} Fx;
typedef struct { s32 id; u8 pad[12]; f32 c[4]; f32 s[4]; } Box;
typedef struct {
    u8 b0[4];
    u8 b4[8];
    u8 bc[4];
    u16 h10[8][256];
    s32 w1010[8];
    s8 c1030[4];
    u8 pad1034[0x3034 - 0x1034];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    u8 pad3040[0x30];
    union { u64 x; s32 i[2]; } f3070;
    u64 f3078;
    u8 pad3080[0x18];
    s32 idx;
    s32 cnt;
    f32 d[3];
    struct Fx *ptrs[4];
    u8 pad30bc[0x3170 - 0x30bc];
    s32 x3170;
    s32 x3174;
    s32 nbox;
    u8 pad317c[4];
    Box box[15];
    s32 x3450;
} Big;
extern Big D_00389C90;
#include "data/pieces/D_002E26A0.h"
/* 32-byte message queue at D_006257E0 (tail D_006277E4, head D_006277E0). */
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
extern Msg D_006257E0[256];
extern s32 D_006277E0;
extern s32 D_006277E4;
#include "data/types/text_001c0000_h42.h"
extern MsgTbl D_0037A21C[];
s32 func_00123488(s32);

/* func_001c4640 is in src/vm/script_vm.c; this copy is for the callers below (docs/context-only-plan.md). */
CONTEXT_ONLY s32 func_001c4640(Msg *m) {
    Msg t;
    if ((D_006277E4 + 1) % 256 == D_006277E0) return -1;
    if (func_00123488(m->x) == 0 && D_0037A21C[m->type].f != 0) return 0;
    D_006257E0[D_006277E4] = *m;
    D_006277E4 = (D_006277E4 + 1) % 256;
    return 0;
}

#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_0038D170.h"
extern volatile s32 D_002BBE04;

#include "data/pieces/D_0037A380.h"
/* func_001c5db8 is in src/camera/camera.c. */

/* func_001c8168, func_001c8260, func_001c8308, func_001c8758, func_001c8878 and func_001c8930 are in src/camera/camera.c. */
extern f32 D_002BBDFC;

/* func_001cab48, func_001cae78, func_001cafe8, func_001cbab0, func_001cbd80, func_001cbea0, func_001cc548 and func_001ccbf8 are in src/msgwin/msgwin.c. */

s32 func_001cd940(VM *vm) {
    Msg m;
    m.type = 3;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 2];
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    m.v[3] = 1.0f;
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}

s32 func_001cec68(VM *vm) {
    Fx *e;
    s32 n;
    f32 x, y, z, fn;
    D_00389C90.idx = vm->stk[vm->sp - 4];
    e = D_00389C90.ptrs[D_00389C90.idx];
    n = vm->stk[vm->sp];
    D_00389C90.cnt = n;
    fn = n;
    x = vm->stk[vm->sp - 3] / 255.0f;
    y = vm->stk[vm->sp - 2] / 255.0f;
    z = vm->stk[vm->sp - 1] / 255.0f;
    D_00389C90.d[0] = (x - e->v30[0]) / fn;
    D_00389C90.d[1] = (y - e->v30[1]) / fn;
    D_00389C90.d[2] = (z - e->v30[2]) / fn;
    if (n == 0) {
        e->v30[0] = x;
        e->v30[1] = y;
        e->v30[2] = z;
        e->v30[3] = 1.0f;
    } else {
        D_00389C90.f3070.x |= 0x80000000000ULL;
    }
    vm->sp -= 5;
    return 2;
}

s32 func_001cf018(VM *vm) {
    Msg m;
    m.type = 19;
    m.val = (u32)vm->stk[vm->sp - 2];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 1];
    m.v[1] = vm->stk[vm->sp] * 2.0f;
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}

s32 func_001cf110(VM *vm) {
    Msg m;
    m.type = 23;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 4] / 255.0f;
    m.v[1] = vm->stk[vm->sp - 3] / 255.0f;
    m.v[2] = vm->stk[vm->sp - 2] / 255.0f;
    m.v[3] = vm->stk[vm->sp - 1] * 0.0078125f;
    func_001c4640(&m);
    vm->sp -= 5;
    return 2;
}
s32 func_001cf210(VM *vm) {
    Msg m;
    if (vm->obj != 0) {
        m.type = 23;
        m.val = (u32)(vm->stk[vm->sp] * 2);
        m.x = vm->x0;
        m.v[0] = vm->obj->col[0] * 0.0078125f;
        m.v[1] = vm->obj->col[1] * 0.0078125f;
        m.v[2] = vm->obj->col[2] * 0.0078125f;
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
    vm->sp--;
    return 2;
}

s32 func_001cfd30(VM *vm) {
    Msg m;
    m.type = 17;
    m.val = (u32)(vm->stk[vm->sp - 1] | 0x10000);
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp];
    func_001c4640(&m);
    vm->sp -= 2;
    return 2;
}
#include "data/data_003C.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BBE04.h"
#include "data/pieces/D_0037A21C.h"
