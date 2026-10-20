#include "common.h"
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
} Actor;
typedef struct {
    s32 x0;
    Actor *obj;
    f32 v08[3];
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x154];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
} VM;
typedef struct {
    u8 pad0[0x3070];
    union { u64 x; s32 i[2]; } f3070;
    union { u64 x; s32 i[2]; } f3078;
} Big;
extern Big D_00389C90;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
void func_001c4640(Msg *m);
typedef union { u64 x; struct { u32 lo; u32 b0:29; u32 b29:1; u32 b30:1; u32 b31:1; } b; } F64;
extern F64 D_0038CD00;
void func_0013c108(s32, s32);
s32 func_001d7678(VM *vm) {
    func_0013c108(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
s32 func_001d76c8(void) {
    if (D_0038CD00.b.b29) return 4;
    return 2;
}
s32 func_0013c188(s32, s32);
s32 func_00132fe0(s32);
s32 func_001d76e8(VM *vm) {
    if (func_0013c188(0, vm->stk[vm->sp]) == 0) {
        vm->stk[vm->sp] = 0;
    } else {
        vm->stk[vm->sp] = func_00132fe0(vm->stk[vm->sp]);
    }
    return 2;
}
s32 func_0011e340(s32);
void func_00131f40(s32, void *);
void func_001d7768(void);
s32 func_001d7798(VM *vm) {
    if (func_0011e340(0) == 0) {
        D_00389C90.f3070.x |= 0x4000000000000000ULL;
        func_00131f40(vm->stk[vm->sp], func_001d7768);
    } else {
        return 4;
    }
    vm->sp--;
    return 2;
}
s32 func_001d7820(void) {
    if (D_0038CD00.b.b30) return 4;
    return 2;
}
typedef struct { s32 key; u8 pad[8]; s32 val; u8 pad2[8]; } E18;
typedef struct { u8 pad0[0x3384]; E18 e[8]; } Big2;
s32 func_001d7840(VM *vm) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if ((s32)vm->obj == ((Big2 *)&D_00389C90)->e[i].key) {
            ((Big2 *)&D_00389C90)->e[i].val = vm->stk[vm->sp];
        }
    }
    vm->sp--;
    return 2;
}
s32 func_00123488(s32);
void func_001248e8(s32);
s32 func_00131de0(s32, s32);
s32 func_001d8838(VM *vm) {
    s32 r = -1;
    while ((r = func_00131de0(r, vm->stk[vm->sp])) != -1) {
        if (func_00123488(r) != 0) func_001248e8(r);
    }
    vm->sp--;
    return 2;
}
s32 func_00111090(void);
s32 func_001d8b68(void) {
    if (func_00111090() == 2) return 2;
    return 4;
}
s32 func_00111090(void);
s32 func_001d8c00(void) {
    if (func_00111090() != 4) return 4;
    return 2;
}
void func_001116b0(s32, s32);
s32 func_001d8c30(VM *vm) {
    func_001116b0(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
void func_0013c2a0(s32, s32);
s32 func_001d8cc8(VM *vm) {
    func_0013c2a0(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
void func_001054d0(s32, s32, s32);
s32 func_001d8db8(VM *vm) {
    func_001054d0(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}
void func_00105710(s32, s32);
s32 func_001d8e10(VM *vm) {
    func_00105710(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
void func_00105760(s32, s32);
s32 func_001d8e60(VM *vm) {
    func_00105760(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
s32 func_001d9480(VM *vm) {
    vm->flags.x |= 0x800;
    vm->f24 = (f32)vm->stk[vm->sp - 3] * 2.0f;
    vm->f14 = vm->stk[vm->sp - 2];
    vm->f18 = vm->stk[vm->sp - 1];
    vm->f1c = vm->stk[vm->sp];
    vm->sp -= 4;
    vm->v08[0] = vm->obj->pos[0];
    vm->v08[1] = vm->obj->pos[1];
    vm->v08[2] = vm->obj->pos[2];
    vm->f28 = 0;
    return 2;
}
typedef struct { u8 pad[0x70]; s32 f70; } Obj70;
s32 func_001d9850(VM *vm) {
    vm->sp++;
    vm->stk[vm->sp] = ((Obj70 *)vm->obj)->f70;
    return 2;
}
void func_00108650(s32, s32);
s32 func_001d9880(VM *vm) {
    func_00108650(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
void func_001086b8(s32, s32);
s32 func_001d98d0(VM *vm) {
    func_001086b8(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
void func_001d9920(void) {
    D_00389C90.f3070.x &= ~0x200000000000ULL;
}
void func_001d9920(void);
extern void (*D_00377344)(s32, s32, void *);
s32 func_001d9950(VM *vm) {
    D_00377344(vm->stk[vm->sp - 1], vm->stk[vm->sp], func_001d9920);
    D_00389C90.f3070.x |= 0x200000000000ULL;
    vm->sp -= 2;
    return 2;
}
typedef union { u64 x; struct { u32 lo; u32 b0:13; u32 b13:1; u32 r:18; } b; } F64b;
s32 func_001d99d0(void) {
    if (((F64b *)&D_0038CD00)->b.b13) return 4;
    return 2;
}
void func_001d99f0(void);
extern void (*D_0037733C)(s32, void *);
s32 func_001d99f8(VM *vm) {
    D_0037733C(vm->stk[vm->sp], func_001d99f0);
    vm->sp--;
    return 2;
}
extern void (*D_00377340)(s32);
s32 func_001d9a50(VM *vm) {
    D_00377340(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}
extern void (*D_00377348)(s32, s32);
s32 func_001d9aa0(VM *vm) {
    D_00377348(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
extern void (*D_0037734C)(s32, s32, s32);
s32 func_001d9af8(VM *vm) {
    D_0037734C(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}
extern void (*D_00377350)(s32, s32);
s32 func_001d9b58(VM *vm) {
    D_00377350(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
extern void (*D_00377354)(s32, s32);
s32 func_001d9bb0(VM *vm) {
    D_00377354(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
extern void (*D_00377358)(s32, s32);
s32 func_001d9c08(VM *vm) {
    D_00377358(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
extern void (*D_0037735C)(s32);
s32 func_001d9c60(VM *vm) {
    D_0037735C(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}
void func_00144eb0(s32, f32 *);
s32 func_001d9cb0(VM *vm) {
    f32 v[3];
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    func_00144eb0(vm->stk[vm->sp - 3], v);
    vm->sp -= 4;
    return 2;
}
extern u64 D_0038CD08;
extern s32 D_002E26A0;
void func_00245280(s32, s32);
s32 func_001d9d48(void) {
    if (!((s32)(D_0038CD08 >> 2) & 1)) return 4;
    func_00245280(1, D_002E26A0);
    return 0;
}
extern void (*D_00377360)(s32);
s32 func_001d9df0(VM *vm) {
    D_00377360(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}
void func_0013c8c8(s32, s32);
s32 func_001d9e40(VM *vm) {
    func_0013c8c8(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
extern s32 D_002BBABC;
extern s32 D_002BBAC0;
s32 func_001d9ee0(VM *vm) {
    D_002BBABC = vm->stk[vm->sp - 1];
    D_002BBAC0 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}
extern s32 D_002BBAD0[];
extern s32 D_002BBAE0[];
s32 func_001d9f20(VM *vm) {
    D_002BBAD0[vm->stk[vm->sp - 2]] = vm->stk[vm->sp - 1];
    D_002BBAE0[vm->stk[vm->sp - 2]] = vm->stk[vm->sp];
    vm->sp -= 3;
    return 2;
}
extern volatile s32 D_0037A378;
s32 func_001d9ff8(void) {
    D_0037A378 &= ~4;
    D_00389C90.f3070.x &= ~0x2000000000ULL;
    return 2;
}
typedef struct { s32 f0; s32 f4; } P8;
P8 *func_001e98d0(s32, s32);
void func_00141218(s32);
s32 func_001da088(VM *vm) {
    func_00141218(func_001e98d0((s32)(vm->flags.x >> 5) & 1, vm->stk[vm->sp])->f4);
    vm->sp--;
    return 2;
}
extern u16 D_002C595A;
s32 func_001da0e8(void) {
    if (D_002C595A & 1) return 4;
    return 2;
}
extern s32 D_002C5958;
s32 func_001da108(void) {
    if (D_002C5958 & 0x6000) return 4;
    return 2;
}
extern void (*D_00377364)(s32);
s32 func_001da128(VM *vm) {
    D_00377364(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}
s32 func_002394f8(void);
s32 func_001da178(void) {
    return func_002394f8() ? 4 : 2;
}
typedef struct { u16 a:4; u16 b:4; u16 c:8; } B16;
B16 *func_00147778(s32);
void func_0013c9e0(s32, s32);
void func_0013c8c8(s32, s32);
s32 func_001da1d0(VM *vm) {
    B16 *p = func_00147778(vm->stk[vm->sp]);
    switch (p->a) {
    case 0:
        func_0013c9e0(p->c, p->b);
        break;
    case 1:
        func_0013c8c8(p->c, p->b);
        break;
    }
    vm->sp--;
    return 2;
}
s32 func_00111660(s32, s32);
s32 func_001da260(VM *vm) {
    s32 a = vm->stk[vm->sp - 1];
    s32 b = vm->stk[vm->sp];
    vm->sp--;
    vm->stk[vm->sp] = func_00111660(a, b);
    return 2;
}
typedef struct { u8 pad[4]; u8 f4; u8 pad5[0x6f]; } E74;
extern E74 *D_00304BE8;
s32 func_001da3b8(VM *vm) {
    E74 *e = D_00304BE8;
    e += vm->stk[vm->sp];
    vm->stk[vm->sp] = e->f4;
    return 2;
}
void func_00142388(f32 *, s32 *);
s32 func_001da400(VM *vm) {
    f32 v[3];
    s32 o[4];
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    func_00142388(v, o);
    vm->sp -= 2;
    vm->stk[vm->sp] = o[0];
    return 2;
}
void func_00142388(f32 *, s32 *);
s32 func_001da490(VM *vm) {
    f32 v[3];
    s32 o[4];
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    func_00142388(v, o);
    vm->sp -= 2;
    vm->stk[vm->sp] = o[1];
    return 2;
}
void func_00142388(f32 *, s32 *);
s32 func_001da520(VM *vm) {
    f32 v[3];
    s32 o[4];
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    func_00142388(v, o);
    vm->sp -= 2;
    vm->stk[vm->sp] = o[2];
    return 2;
}
void func_00142470(Actor *, s32 *);
s32 func_001da5b0(VM *vm) {
    s32 v[3];
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    if (vm->obj) func_00142470(vm->obj, v);
    vm->sp -= 3;
    return 2;
}
#include "data/data_002B.h"
#include "data/data_0038.h"
