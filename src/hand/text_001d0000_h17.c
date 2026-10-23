#include "common.h"
#include "vm/script_vm.h"
#include "data/bss_0062.h"

/* Script VM handlers: value stack at +0x184, top index at +0x180. */
typedef struct {
    u8 pad0[0x18];
    f32 f18;
} Sub130;
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x50 - 0x1c];
    f32 p50[3];
    u8 pad5c[0x130 - 0x5c];
    Sub130 *f130;
    u8 pad134[0x164 - 0x134];
    s32 f164;
} Actor;
typedef struct {
    s32 x0;
    Actor *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
    f32 f330;
} VM;
typedef struct {
    u8 pad0[0x3040];
    s32 f3040;
    u8 pad3044[0x1c];
    s32 *f3060;
    u8 pad3064[0xc];
    union { u64 x; s32 i[2]; u8 c; } f3070;
    s32 w[8]; /* 0x3078 */
    u8 pad3098[0x3384 - 0x3098];
    struct { void *id; s32 f4; s32 f8; s32 fc; s32 f10; s32 f14; } e3384[8];
} Big;
extern Big D_00389C90;
#include "data/pieces/D_00304BE8_s.h"

#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0037A378.h"
extern u64 D_0038CD00;
typedef struct { s32 f0; s32 f4; s32 f8; } S5AD0;
typedef struct { s32 f0; s32 f4; s32 f8; u8 padc[0x24]; s32 a30[15]; s32 f6c; } S5BB0;
typedef struct Node { s32 x0; s32 f4; } Node;

s32 func_00131de0(s32, s32);
void func_00124218(s32);

s32 func_001d6e70(VM *vm) {
    s32 i = -1;
    while ((i = func_00131de0(i, vm->stk[vm->sp])) != -1) func_00124218(i);
    vm->sp--;
    return 2;
}

s32 func_001d7238(VM *vm) {
    if ((s32)(D_0038CD00 >> 60) & 1) return 4;
    return 2;
}

s32 func_001d7258(VM *vm) {
    VmMsg m;
    Actor *o = vm->obj;
    if (o) {
        m.x = vm->x0;
        m.type = 39;
        m.val = 0;
        m.v[0] = o->pos[0];
        m.v[1] = o->pos[1] - 20.0f;
        m.v[2] = o->pos[2];
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
    return 2;
}

s32 func_001d72e0(VM *vm) {
    vm->flags.x |= 0x4000;
    vm->f330 = (f32)vm->stk[vm->sp] * 2;
    vm->sp--;
    return 2;
}

s32 func_001d7438(VM *vm) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (D_00389C90.e3384[i].id == 0 || D_00389C90.e3384[i].id == vm->obj) {
            D_00389C90.e3384[i].id = vm->obj;
            D_00389C90.e3384[i].f8 = vm->stk[vm->sp - 1];
            D_00389C90.e3384[i].f10 = vm->stk[vm->sp];
            break;
        }
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001d74b8(VM *vm) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (D_00389C90.e3384[i].id == 0 || D_00389C90.e3384[i].id == vm->obj) {
            D_00389C90.e3384[i].id = vm->obj;
            D_00389C90.e3384[i].f14 = vm->stk[vm->sp];
            break;
        }
    }
    vm->sp -= 1;
    return 2;
}
#include "data/data_002A.h"
#include "data/data_002E.h"
#include "data/data_0038.h"
