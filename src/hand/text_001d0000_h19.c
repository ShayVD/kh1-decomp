#include "common.h"
#include "data/bss_0062.h"

/* Script VM handlers: value stack at +0x184, top index at +0x180. */
typedef struct { s32 flags; } Obj;
typedef struct {
    s32 x0;
    Obj *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags; /* 0x328 */
    f32 f330;
    u8 pad334[0xc];
    f32 f340;
    f32 f344;
    f32 f348;
} VM;

typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
void func_001c4640(Msg *m);

void func_00131c78(s32, s32);
extern void (*D_00377368)(s32, s32);
extern void (*D_0037736C)(s32, s32);
extern void (*D_00377370)(s32, s32);
extern void (*D_00377378)(s32, s32);
extern void (*D_0037737C)(s32, s32);
extern void (*D_00377380)(s32, s32, s32, s32);
extern void (*D_00377384)(s32);
extern s32 (*D_00377388)(s32, s32, s32);
extern void (*D_0037738C)(s32, s32);
extern void (*D_0037739C)(s32, s32, s32, s32, s32);
extern void (*D_00377390)(s32, s32, s32, s32);
extern void (*D_00377394)(s32, s32, s32, s32);
extern void (*D_00377398)(s32, s32, s32, s32, s32);
extern void (*D_003773A0)(s32, s32, s32, s32, s32);
extern void (*D_003773A4)(s32);
extern void (*D_003773A8)(s32);
extern void (*D_003773AC)(s32);
extern void (*D_003773B0)(s32, s32);
extern void (*D_003773B4)(s32);
extern void (*D_003773B8)(s32);
extern void (*D_003773BC)(s32, s32, s32, s32, s32);
extern s32 (*D_003773C0)(s32, s32);
extern s32 (*D_003773C4)(void);
extern void (*D_003773CC)(s32, s32);
extern void (*D_003773D0)(s32);
extern void (*D_003773D4)(s32, s32);
extern void (*D_003773D8)(s32, s32, s32);
extern s32 (*D_003773C8)(s32, s32);
extern void (*D_00377374)(s32, s32, s32);
s32 func_002193f0(void);
extern u64 D_0038CD08;
extern u64 D_0038CD00;
#include "data/pieces/D_0037A178.h"
extern s32 D_003F76B8;
extern s32 D_0062A220;
extern s32 D_0062A224;
extern s32 D_0062A628;
extern u8 D_0062A630[];
u8 D_0062A640[0x5000] ALIGNED(64);
void func_0011efa8(void *, void *, s32, s32);
s32 func_0011ef10(s32, void (*)());
void func_001dd148();
typedef struct { f32 *f0; u8 pad4[0x10]; s32 f14; } HObj;
typedef struct { u8 pad0[0x15c]; s32 f15c; } HSub4;
typedef struct { u8 pad0[4]; HSub4 *f4; } HSub;
typedef struct { u8 pad0[0x10]; HObj *f10; HSub *f14; s32 f18; } Handler;
typedef struct { u8 pad0[0x30]; f32 v[3]; u8 pad3c[4]; } M64;
M64 *func_001623e0(s32);
void func_001318e8(HSub4 *, s32, void *);
void func_00147e08(HObj *, void *);
typedef struct { u8 pad0[0x3078]; u64 f3078; } Big19;
extern Big19 D_00389C90;
s32 D_00F20000();
void func_001dbcb8();
void func_001dbd90();
void func_0011ea10(void (*)(), s32 (*)());
s32 func_001559f0(s32, s32);
s32 func_00120748(void *, s32, void (*)(), s32);
extern u8 D_004906C0[];
typedef struct { u8 pad0[0x36]; u8 f36; u8 pad37[116 - 0x37]; } E116;
extern E116 *D_00304BE8;

s32 func_001da6d0(VM *vm) {
    vm->flags.x |= 0x8000;
    vm->f330 = (f32)vm->stk[vm->sp - 3] * 2;
    vm->f340 = vm->stk[vm->sp - 2];
    vm->f344 = vm->stk[vm->sp - 1];
    vm->f348 = vm->stk[vm->sp];
    vm->sp -= 4;
    return 2;
}

s32 func_001da7b8(VM *vm) {
    func_00131c78(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da808(VM *vm) {
    D_00377368(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da860(VM *vm) {
    D_0037736C(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da8b8(VM *vm) {
    D_00377370(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da910(VM *vm) {
    D_00377378(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da968(VM *vm) {
    Msg m;
    m.type = 41;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    func_001c4640(&m);
    vm->sp -= 1;
    return 2;
}

s32 func_001dab20(VM *vm) {
    if ((s32)(D_0038CD08 >> 4) & 1) return 4;
    return 2;
}

s32 func_001dabe8(VM *vm) {
    D_0037737C(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001dac40(VM *vm) {
    D_00377380(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}

s32 func_001dad30(VM *vm) {
    if ((s32)(D_0038CD08 >> 5) & 1) return 4;
    return 2;
}

s32 func_001db080(VM *vm) {
    D_00377384(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db0d0(VM *vm) {
    if (D_00377388(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp])) {
        vm->sp -= 3;
        return 2;
    }
    return 4;
}

s32 func_001db140(VM *vm) {
    D_0037738C(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001db198(VM *vm) {
    D_0037739C(vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 5;
    return 2;
}

s32 func_001db208(VM *vm) {
    D_003773A0(vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 5;
    return 2;
}

s32 func_001db278(VM *vm) {
    D_00377390(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}

s32 func_001db2e0(VM *vm) {
    D_00377394(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}

s32 func_001db348(VM *vm) {
    D_00377398(vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 5;
    return 2;
}

s32 func_001db3b8(VM *vm) {
    D_003773A4(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db408(VM *vm) {
    D_003773A8(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db458(VM *vm) {
    D_003773AC(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db4a8(VM *vm) {
    D_003773B0(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001db500(VM *vm) {
    D_003773B4(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db550(VM *vm) {
    D_003773B8(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db600(VM *vm) {
    D_00304BE8[vm->stk[vm->sp - 1]].f36 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

s32 func_001db8e0(VM *vm) {
    s32 r = D_003773C0(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 1;
    vm->stk[vm->sp] = r;
    return 2;
}

s32 func_001db950(VM *vm) {
    D_003773BC(vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 5;
    return 2;
}

s32 func_001db9c0(VM *vm) {
    if (D_003773C4()) return 2;
    return 4;
}

s32 func_001dba88(VM *vm) {
    D_003773CC(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001dbba0(VM *vm) {
    D_003773D0(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001dbc38(VM *vm) {
    D_003773D4(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001dbcd8(VM *vm) {
    D_00389C90.f3078 |= 0x100;
    func_0011ea10(func_001dbcb8, D_00F20000);
    return 2;
}

s32 func_001dbd68(VM *vm) {
    if ((s32)(D_0038CD08 >> 8) & 1) return 4;
    return 2;
}


s32 func_001dbe50(VM *vm) {
    if ((s32)(D_0038CD08 >> 9) & 1) return 4;
    return 2;
}

s32 func_001dbec0(VM *vm) {
    D_003773D8(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}

s32 func_001dbf20(VM *vm) {
    vm->sp++;
    if (vm->obj) {
        if (vm->obj->flags & 0x4000) vm->stk[vm->sp] = 1;
        else vm->stk[vm->sp] = 0;
    }
    return 2;
}

s32 func_001dbf68(VM *vm) {
    vm->flags.x |= 4;
    vm->f2f4 = (f32)vm->stk[vm->sp] * 2 / 100.0f;
    vm->sp -= 1;
    return 6;
}

s32 func_001dc358(VM *vm) {
    if (D_003773C8(vm->stk[vm->sp - 1], vm->stk[vm->sp])) {
        vm->sp -= 2;
        return 2;
    }
    return 4;
}

s32 func_001dc520(VM *vm) {
    D_00377374(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}

s32 func_001dc868(VM *vm) {
    vm->sp++;
    if (!func_002193f0()) vm->stk[vm->sp] = 1;
    else vm->stk[vm->sp] = 0;
    return 2;
}

s32 func_001dc9a0(VM *vm) {
    if ((u32)vm->stk[vm->sp] >= 128) return 2;
    vm->stk[vm->sp] = (D_0037A178[vm->stk[vm->sp] / 32] >> (31 - vm->stk[vm->sp] % 32)) & 1;
    return 2;
}

s32 func_001dca48(VM *vm) {
    vm->sp++;
    if (!D_003F76B8) vm->stk[vm->sp] = 1;
    else vm->stk[vm->sp] = 0;
    return 2;
}

s32 func_001dd170(void) {
    s32 *p = &D_0062A220;
    s32 r;
    *p = func_001559f0(50, 2);
    D_0062A224 = *p + 0x7d000;
    func_0011efa8(D_0062A630, D_0062A640, 80, 256);
    r = func_0011ef10(0xc34f, func_001dd148);
    D_0062A628 = 0;
    return r;
}

s32 func_001dd3f8(Handler *h) {
    M64 *m;
    if ((s32)(D_0038CD00 >> 40) & 1) return 4;
    if (h->f10->f14 & 2) return 4;
    m = func_001623e0(h->f14->f4->f15c);
    h->f10->f0[0] = m[h->f18].v[0];
    h->f10->f0[1] = m[h->f18].v[1];
    h->f10->f0[2] = m[h->f18].v[2];
    return 0;
}

s32 func_001dd550(Handler *h) {
    u8 buf[64];
    if ((s32)(D_0038CD00 >> 40) & 1) return 4;
    if (h->f10->f14 & 2) return 4;
    func_001318e8(h->f14->f4, h->f18, buf);
    func_00147e08(h->f10, buf);
    return 0;
}

s32 func_001ddf98(VM *vm) {
    if ((s32)(D_0038CD00 >> 44) & 1) return 4;
    return 2;
}
#include "data/bss_0062_mixed.h"
#include "data/data_0038.h"
#include "data/data_003F.h"
#include "data/pieces/D_00377368.h"
#include "data/pieces/D_0037736C.h"
#include "data/pieces/D_00377370.h"
#include "data/pieces/D_00377374.h"
#include "data/pieces/D_00377378.h"
#include "data/pieces/D_0037737C.h"
#include "data/pieces/D_00377380.h"
#include "data/pieces/D_00377384.h"
#include "data/pieces/D_00377388.h"
#include "data/pieces/D_0037738C.h"
#include "data/pieces/D_00377390.h"
#include "data/pieces/D_00377394.h"
#include "data/pieces/D_00377398.h"
#include "data/pieces/D_0037739C.h"
#include "data/pieces/D_003773A0.h"
#include "data/pieces/D_003773A4.h"
#include "data/pieces/D_003773A8.h"
#include "data/pieces/D_003773AC.h"
#include "data/pieces/D_003773B0.h"
#include "data/pieces/D_003773B4.h"
#include "data/pieces/D_003773B8.h"
#include "data/pieces/D_003773BC.h"
#include "data/pieces/D_003773C0.h"
#include "data/pieces/D_003773C4.h"
#include "data/pieces/D_003773C8.h"
#include "data/pieces/D_003773CC.h"
#include "data/pieces/D_003773D0.h"
#include "data/pieces/D_003773D4.h"
#include "data/pieces/D_003773D8.h"
