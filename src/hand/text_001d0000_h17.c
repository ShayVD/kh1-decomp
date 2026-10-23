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
extern s32 D_002A61F0;
extern s32 D_0062A210;
extern s32 D_002E27A8;
extern u64 D_0038CD00;
typedef struct { s32 f0; s32 f4; s32 f8; } S5AD0;
typedef struct { s32 f0; s32 f4; s32 f8; u8 padc[0x24]; s32 a30[15]; s32 f6c; } S5BB0;
extern volatile S5AD0 D_002C5AD0;
extern volatile S5BB0 D_002C5BB0;
typedef struct Node { s32 x0; s32 f4; } Node;

void func_00103988(s32);
void func_0011ef10(s32, void (*)());
void func_001d5060();
s32 func_00123298(void);
Node *func_001230a0(Node *);
Node *func_00123220(Node *);
s32 func_00123618(s32);
void func_001248e8(s32);
void func_0013c638(s32, s32);
void func_0013c778(s32, s32, s32);
s32 func_0024d490(void);
void func_00105d38(s32, s32);
s32 func_00131de0(s32, s32);
void func_00124218(s32);

s32 func_001d5090(VM *vm) {
    D_002A61F0 = 1;
    func_00103988(vm->stk[vm->sp]);
    D_0062A210 = vm->stk[vm->sp];
    func_0011ef10(50000, func_001d5060);
    vm->sp--;
    return 2;
}

s32 func_001d5278(VM *vm) {
    VmMsg m;
    m.type = 33;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001d52c0(VM *vm) {
    VmMsg m;
    m.type = 34;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001d5350(VM *vm) {
    vm->sp++;
    if (vm->obj) vm->stk[vm->sp] = vm->obj->f164;
    return 2;
}

s32 func_001d54a8(VM *vm) {
    if (func_00123298() <= 0) return 2;
    return 4;
}

s32 func_001d5618(VM *vm) {
    s32 n = 0;
    Node *p;
    for (p = func_001230a0(0); p; p = func_00123220(p)) {
        if (func_00123618(p->f4) == 0xcd) n++;
    }
    vm->sp++;
    vm->stk[vm->sp] = n;
    return 2;
}

s32 func_001d56a8(VM *vm) {
    vm->sp++;
    if (D_002E27A8 == 2) vm->stk[vm->sp] = 1;
    else vm->stk[vm->sp] = 0;
    return 2;
}

s32 func_001d56f0(VM *vm) {
    VmMsg m;
    m.type = 37;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001d5738(VM *vm) {
    VmMsg m;
    m.type = 38;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001d5780(VM *vm) {
    func_0013c638(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d5b00(VM *vm) {
    func_0013c778(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}

s32 func_001d6348(VM *vm) {
    s32 n = 0;
    Node *p;
    for (p = func_001230a0(0); p; p = func_00123220(p)) {
        if (func_00123618(p->f4) == vm->stk[vm->sp]) n++;
    }
    vm->stk[vm->sp] = n;
    return 2;
}

s32 func_001d6628(VM *vm) {
    if (!func_0024d490()) return 4;
    return 2;
}

s32 func_001d69d0(VM *vm) {
    func_00105d38(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d6b70(VM *vm) {
    if (!((s32)(D_0038CD00 >> 58) & 1)) return 4;
    D_002C5AD0.f8 = 0;
    D_002C5AD0.f4 = 0;
    D_002C5BB0.f6c = 0;
    D_002C5BB0.f4 = 0;
    D_002C5BB0.f8 = 0;
    D_002C5BB0.a30[0] = 0;
    D_002C5BB0.a30[1] = 0;
    D_002C5BB0.a30[2] = 0;
    D_002C5BB0.a30[3] = 0;
    D_002C5BB0.a30[4] = 0;
    D_002C5BB0.a30[5] = 0;
    D_002C5BB0.a30[6] = 0;
    D_002C5BB0.a30[7] = 0;
    D_002C5BB0.a30[8] = 0;
    D_002C5BB0.a30[9] = 0;
    D_002C5BB0.a30[10] = 0;
    D_002C5BB0.a30[11] = 0;
    D_002C5BB0.a30[12] = 0;
    D_002C5BB0.a30[13] = 0;
    D_002C5BB0.a30[14] = 0;
    return 0;
}

s32 func_001d6cf0(VM *vm) {
    Node *p;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if (func_00123618(p->f4) >= 300 && func_00123618(p->f4) < 351) func_001248e8(p->f4);
    }
    return 2;
}

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
