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
    u8 pad24[0x15c];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
} VM;
typedef struct {
    s32 x0;
    u8 pad4[8];
    f32 f0c;
    f32 v10[4];
    f32 v20[4];
    f32 v30[4];
} Fx;
typedef struct {
    u8 pad0[0x3070];
    union { u64 x; s32 i[2]; } f3070;
    union { u64 x; s32 i[2]; } f3078;
    u8 pad3080[0x18];
    s32 idx;
    s32 cnt;
    f32 d[3];
    Fx *ptrs[4];
    u8 pad30bc[0x6c];
    s32 cnt2;
    s32 step2;
    s32 cnt3;
    s32 step3[3];
} Big;
extern Big D_00389C90;
void func_00112b48(s32, s32, s32, s32);
s32 func_001cdf98(VM *vm) {
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b48(a, b, c, -1);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}
void func_00112b80(s32, s32, s32, s32);
void func_00112bb8(s32);
void func_00108180(s32);
void func_001081a0(s32);
s32 func_001ce020(VM *vm) {
    s32 d = vm->stk[vm->sp--];
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b48(a, b, c, d);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce0b8(VM *vm) {
    s32 d = vm->stk[vm->sp--];
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b80(a, b, c, d);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce150(VM *vm) {
    s32 a = vm->stk[vm->sp--];
    func_00112bb8(a);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce1a8(VM *vm) {
    s32 d = vm->stk[vm->sp--];
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b48(a, b, c, d);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce240(VM *vm) {
    s32 a = vm->stk[vm->sp--];
    func_00112bb8(a);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce2e8(VM *vm) {
    func_00108180(vm->stk[vm->sp--]);
    return 2;
}
s32 func_001ce320(VM *vm) {
    func_001081a0(vm->stk[vm->sp--]);
    return 2;
}
#include "data/pieces/D_00388CC4.h"
s32 func_001ce3c0(VM *vm) {
    s32 i = vm->stk[32];
    vm->sp--;
    if (i >= 2048) D_00388CC4[i]++;
    return 2;
}
s32 func_001ce400(VM *vm) {
    s32 i = vm->stk[32];
    vm->sp--;
    if (i >= 2048) D_00388CC4[i]--;
    return 2;
}
extern Fx *D_0038CD3C[];
Fx *func_001226f0(s32, s32, s32);
s32 func_001ce9b0(VM *vm) {
    s32 i = vm->stk[vm->sp];
    Fx *p = func_001226f0(2, 0, i);
    D_0038CD3C[i] = p;
    vm->sp--;
    p->v30[3] = p->v30[2] = p->v30[1] = p->v30[0] = 1.0f;
    return 2;
}
s32 func_001cea38(VM *vm) {
    s32 i = vm->stk[vm->sp];
    Fx *p = func_001226f0(2, 1, i);
    D_0038CD3C[i] = p;
    vm->sp--;
    p->v30[3] = p->v30[2] = p->v30[1] = p->v30[0] = 1.0f;
    return 2;
}
s32 func_001ceac0(VM *vm) {
    D_0038CD3C[vm->stk[vm->sp - 1]]->x0 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}
s32 func_001ceb08(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 3];
    f32 x = vm->stk[sp - 2];
    f32 y = vm->stk[sp - 1];
    f32 z = vm->stk[sp];
    Fx *p;
    vm->sp = sp - 4;
    p = D_0038CD3C[i];
    p->v10[0] = x;
    p->v10[1] = y;
    p->v10[2] = z;
    p->v10[3] = 1.0f;
    return 2;
}
s32 func_001ceb78(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 3];
    f32 x = vm->stk[sp - 2];
    f32 y = vm->stk[sp - 1];
    f32 z = vm->stk[sp];
    Fx *p;
    vm->sp = sp - 4;
    p = D_0038CD3C[i];
    p->v20[0] = x;
    p->v20[1] = y;
    p->v20[2] = z;
    p->v20[3] = 1.0f;
    return 2;
}
s32 func_001ceda0(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    f32 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_0038CD3C[i]->f0c = v;
    return 2;
}
void func_001cebe8(void) {
    Fx *p;
    if (--D_00389C90.cnt <= 0) D_00389C90.f3070.x &= ~0x80000000000ULL;
    p = D_00389C90.ptrs[D_00389C90.idx];
    p->v30[0] += D_00389C90.d[0];
    p->v30[1] += D_00389C90.d[1];
    p->v30[2] += D_00389C90.d[2];
}
void func_00104300(s32);
void func_001043f8(s32);
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
void func_001c4640(Msg *m);
s32 func_001cef20(VM *vm) {
    func_00104300(vm->stk[vm->sp]);
    D_00389C90.f3078.x |= 1;
    vm->sp--;
    return 2;
}
s32 func_001cefb8(VM *vm) {
    func_001043f8(vm->stk[vm->sp]);
    D_00389C90.f3078.x &= ~1ULL;
    vm->sp--;
    return 2;
}
s32 func_001cf0c8(VM *vm) {
    Msg m;
    m.type = 20;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}
void func_00135978(void *, s32, s32);
void func_001359c0(void *, s32, s32);
s32 func_00131b08(void *);
s32 func_001cf300(VM *vm) {
    Msg m;
    m.type = 24;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}
s32 func_001cf890(VM *vm) {
    func_00135978(vm->obj, vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
s32 func_001cf8e8(VM *vm) {
    func_001359c0(vm->obj, vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
s32 func_001cf940(VM *vm) {
    return ((s32)(vm->flags.x >> 1) & 1) ? 4 : 2;
}
s32 func_001cfad0(VM *vm) {
    return func_00131b08(vm->obj) ? 2 : 4;
}
s32 func_001cfb00(VM *vm) {
    Msg m;
    m.type = 27;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}
s32 func_001cfb90(VM *vm) {
    Msg m;
    m.type = 5;
    m.val = (u32)(vm->stk[vm->sp] | 0x10000);
    m.x = vm->x0;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}
typedef struct { s32 v[3]; s32 f0c; } Cam;
extern Cam D_002BC080;
extern s32 D_002BC08C;
void func_00111600(s32, s32, s32);
void func_001065a8(s32, s32, s32, s32);
void func_00106648(s32, s32, s32, s32);
s32 D_00F20000(s32, s32);
s32 func_001cfb48(VM *vm) {
    Msg m;
    m.type = 28;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}
void func_001cff28(void) {
    if (--D_00389C90.cnt2 <= 0) D_00389C90.f3070.x &= ~0x4000000000ULL;
    D_002BC080.f0c += D_00389C90.step2;
}
void func_001cfff8(void) {
    if (--D_00389C90.cnt3 <= 0) D_00389C90.f3070.x &= ~0x8000000000ULL;
    D_002BC080.v[0] += D_00389C90.step3[0];
    D_002BC080.v[1] += D_00389C90.step3[1];
    D_002BC080.v[2] += D_00389C90.step3[2];
}
s32 func_001d0548(VM *vm) {
    func_00111600(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}
s32 func_001d05a0(VM *vm) {
    func_001065a8(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}
s32 func_001d0600(VM *vm) {
    func_00106648(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}
s32 func_001d09a0(void) {
    D_00389C90.f3078.x &= ~0x2000ULL;
    return D_00F20000(0, 0);
}
s32 func_001d1230(VM *vm) {
    s32 sp = vm->sp;
    vm->flags.x |= 0x40;
    vm->f20 = vm->stk[sp - 3];
    vm->f14 = vm->stk[sp - 2];
    vm->f18 = vm->stk[sp - 1];
    vm->f1c = vm->stk[sp];
    vm->sp = sp - 4;
    vm->v08[0] = vm->obj->pos[0];
    vm->v08[1] = vm->obj->pos[1];
    vm->v08[2] = vm->obj->pos[2];
    return 2;
}
s32 func_001cff80(VM *vm) {
    s32 base = D_002BC08C;
    s32 n = vm->stk[vm->sp];
    D_00389C90.cnt2 = n;
    D_00389C90.step2 = (vm->stk[vm->sp - 1] - base) / n;
    D_00389C90.f3070.x |= 0x4000000000ULL;
    vm->sp -= 2;
    return 2;
}
void func_001d1610(void);
extern f32 D_002BBDFC;
extern u64 D_0038CD00;
extern s32 D_002BC09C;
#include "data/pieces/D_002BC098.h"
extern s32 D_002BC0A0;
extern s32 D_002BC0A4;
void func_001560f8(s32, void (*)(void));
void func_00124218(s32);
Actor *func_00123488(s32);
void func_00122f58(Actor *, f32, f32, f32);
s32 func_001d12b8(VM *vm) {
    s32 sp = vm->sp;
    vm->flags.x |= 0x40;
    vm->f20 = vm->stk[sp - 3] * D_002BBDFC;
    vm->f14 = vm->stk[sp - 2];
    vm->f18 = vm->stk[sp - 1];
    vm->f1c = vm->stk[sp];
    vm->sp = sp - 4;
    vm->v08[0] = vm->obj->pos[0];
    vm->v08[1] = vm->obj->pos[1];
    vm->v08[2] = vm->obj->pos[2];
    return 2;
}
void func_001d1610(void) {
    D_00389C90.f3070.x &= ~0x200000000000ULL;
}
s32 func_001d1640(VM *vm) {
    D_00389C90.f3070.x |= 0x200000000000ULL;
    func_001560f8(vm->stk[vm->sp], func_001d1610);
    vm->sp--;
    return 2;
}
s32 func_001d16a8(void) {
    return ((s32)(D_0038CD00 >> 45) & 1) ? 4 : 2;
}
s32 func_001d16c8(VM *vm) {
    func_00124218(vm->stk[vm->sp]);
    vm->obj = func_00123488(vm->x0);
    vm->sp--;
    return 2;
}
s32 func_001d1728(VM *vm) {
    s32 sp = vm->sp;
    D_002BC09C = vm->stk[sp - 1];
    D_002BC098 = vm->stk[sp] * 3.1415928f / 180.0f;
    vm->sp = sp - 2;
    return 2;
}
s32 func_001d1790(VM *vm) {
    s32 sp = vm->sp;
    D_002BC0A0 = vm->stk[sp - 1];
    D_002BC0A4 = vm->stk[sp];
    vm->sp = sp - 2;
    return 2;
}
#include "data/types/text_001c0000_h16.h"
extern Tbl *D_003DABCC[];
void func_00131498(void *, void *);
/* bit 7 of VM.flags as a u32 bitfield (compares against 1 are kept) */
typedef union { u64 x; struct { u32 b0:1; u32 b1:1; u32 b2:5; u32 b7:1; u32 r:24; u32 hi; } b; } VF;
s32 func_001cf728(VM *vm) {
    s32 f;
    switch (vm->stk[vm->sp]) {
    case 1:
        f = (s32)(D_0038CD00 >> 33) & 1;
        if (f == 1) return 4;
        vm->sp--;
        return 2;
    case 2:
        f = (s32)(D_0038CD00 >> 34) & 1;
        if (f == 1) return 4;
        vm->sp--;
        return 2;
    }
    return 4;
}
s32 func_001cf7a0(VM *vm) {
    if (((VF *)&vm->flags)->b.b7 != 1) {
        Tbl *t;
        s32 sp = vm->sp;
        vm->flags.x |= 0x80;
        t = D_003DABCC[vm->stk[sp - 1]];
        func_00131498(vm->obj, (u8 *)t + ((s32 *)t)[vm->stk[sp] + 2]);
        vm->sp -= 2;
        return 2;
    }
    vm->sp -= 2;
    return 2;
}
#include "data/data_002B.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_003DABCC.h"
