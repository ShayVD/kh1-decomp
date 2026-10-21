#include "common.h"

typedef struct { u32 b0:1, b1:1, b2:1, b3:1, b4:1, rest:27; } Bits;

typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0xc];
    f32 f14, f18, f1c, f20;
    u8 pad24[0x4c];
    s8 *code;
    s32 n;
    s32 x78;
    u32 lbl[64];
    u32 pc;
    s32 sp;
    s32 stk[32];
    s32 var[26];
    s32 stk2[33];
    s32 x2f0;
    f32 x2f4;
    s32 ret[8];
    s32 rsp;
    s32 x31c, x320, x324;
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, b14:1, b15:1, brest:16;
    u8 pad32c[0x24];
} __attribute__((aligned(8))) VMa;

typedef struct {
    u8 pad0[4];
    s32 x4;
    u8 pad8[0x3c];
    s32 x44;
    u8 pad48[0x24];
    s32 x6c;
} Q48;

typedef struct {
    u8 pad0[0x1034];
    s32 a1034[512];
    s32 a1834[512];
    s32 a2034[512];
    s32 a2834[512];
    s32 x3034;
    u8 pad3038[8];
    u8 *x3040;
    u8 *x3044;
    u32 x3048;
    s32 *x304c;
    u32 x3050;
    s32 *x3054;
    s32 x3058;
    s32 x305c;
    s32 *x3060;
    s32 x3064;
    s32 *x3068;
    s32 x306c;
    union { u64 x; s32 w[2]; struct { u32 lo; u32 p0:6, b38:1, b39:1, p40:3, b43:1, p44:9, b53:1, p54:10; } __attribute__((aligned(8))) f; } f3070;
    union { u64 x; struct { u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, b10:1, brest:21; u32 hi; } __attribute__((aligned(8))) b; } f3078;
    u8 pad3080[0x3148 - 0x3080];
    u32 x3148;
    u8 pad314c[0x3158 - 0x314c];
    s32 x3158[5];
    void *x316c;
    u8 pad3170[0x3178 - 0x3170];
    s32 x3178;
} BigA;

extern BigA D_00389C90;
extern u32 D_0037A378;
extern s32 D_002C5958;
extern VMa D_0038D170[];
extern VMa D_0039A580[];
extern s32 D_0039A570;
extern s32 D_003A7980;
extern u8 D_003DE570[];
s32 func_001c1ce8(s8 *, s32);
void func_001c19f8(VMa *, s32);
void func_001c4198(void *, s32);

typedef f32 Vec[4] __attribute__((aligned(16)));
typedef struct Elem {
    s32 a;
    s32 b;
    s32 c;
    s32 pad;
    Vec m[11];
    f32 f[6];
    struct Elem *next;
    struct Elem *prev;
} Elem;
typedef struct {
    f32 x0;
    u8 pad4[0xc];
    Vec q10, q20, q30, q40;
    Vec q50;
    f32 x60;
    u8 pad64[0xf0 - 0x64];
    Elem arr[256];
    s32 n;
    f32 xE0F4;
    Elem *first;
    Elem *last;
} Scn;
extern Scn D_0037A380;
typedef struct {
    u8 pad0[0xd0];
    Vec v[5];
    f32 f120, f124;
} __attribute__((aligned(16))) CamS;
extern CamS D_003C5510;
extern s32 D_003C5500;
void func_001c53c8(f32);
void func_001c6a20(void);
void func_001c5b88(void);
void func_0011ef10(s32, void *);
VMa *func_001e98d0(s32, s32);

extern s8 *D_003C39AC;
extern s32 D_006277E0, D_006277E4, D_006297F0, D_006297F4;
extern u32 D_00389C80;
extern u8 *D_00388480[];
extern s32 (*D_0037A198[])(VMa *, s32);
s32 func_001ee200(void);
void srand(u32);
void func_001c29d8(void);
void func_001c6720(void);
void func_001cab48(void);
void func_001c2d20(s8 *, void *, void *);
s32 func_001c1cf8(s8 *, s32);
void func_001c2778(void);

typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
typedef struct {
    u8 pad0[4];
    s32 x4;
    s32 x8;
    u8 padc[0x34];
    s32 x40[3];
    u8 pad4c[0x14];
    s32 x60[3];
} S5BB0;
typedef struct {
    u8 pad0[0x10];
    VMa *vm;
    s32 n;
    s32 x18;
} Task;
extern S5BB0 D_002C5BB0;
extern u32 D_003C39A8;
extern u8 *D_003C21A8[];
extern f32 D_002BBDFC;
Msg *func_001c4730(void);
void func_001c4788(Msg *);
s32 func_001c4640(Msg *);
void func_001cebe8(void);
void func_001cff28(void);
void func_001cfff8(void);
void func_001ca800(void);
void func_001dcea8(VMa *);
void func_001dcfd0(VMa *);

/* needs make: uses rodata (jump table jtbl_00490590) */
void func_001c48c8(s32 id, u32 kind, s32 *p) {
    VMa *vm;
    VMa *e;
    s32 n, i;
    if (!((s32)(D_00389C90.f3070.x >> 59) & 1)) return;
    if ((D_0037A378 >> 2) & 1) return;
    if (D_002C5958 & 0x12000) return;
    if (D_00389C90.x3034 == 0) {
        vm = D_0038D170;
        n = D_0039A570;
    } else {
        n = D_003A7980;
        vm = D_0039A580;
    }
    for (i = 0; i < n; i++) {
        if (vm[i].x0 == id) break;
    }
    if (i >= n && kind != 5) return;
    switch (kind) {
    case 0:
        e = &vm[i];
        if (func_001c1ce8(e->code, e->lbl[5]) == 5) return;
        if (e->pc >= e->lbl[5] && e->pc < e->lbl[6]) return;
        D_002C5958 |= 0x1000;
        D_00389C90.f3078.x |= 0x800;
        vm->stk[++vm->sp] = 3;
        vm->stk[++vm->sp] = i;
        func_001c19f8(vm, 5); return;

    case 1:
        if (func_001c1ce8(vm[i].code, vm[i].lbl[6]) == 5) return;
        vm->stk[++vm->sp] = 2;
        vm->stk[++vm->sp] = i;
        func_001c19f8(vm, 6); return;

    case 2: {
        Q48 *q;
        e = &vm[i];
        if (func_001c1ce8(e->code, e->lbl[4]) == 5) return;
        q = (Q48 *)p[11];
        vm->stk[++vm->sp] = 2;
        vm->stk[++vm->sp] = i;
        e->x31c = q->x6c;
        e->x320 = q->x4;
        e->x324 = q->x44;
        func_001c19f8(vm, 4); return;

    }
    case 3:
        if (func_001c1ce8(vm[i].code, vm[i].lbl[7]) == 5) return;
        vm->stk[++vm->sp] = 4;
        vm->stk[++vm->sp] = i;
        func_001c19f8(vm, 7); return;

    case 4:
        if (func_001c1ce8(vm[i].code, vm[i].lbl[3]) == 5) return;
        vm->stk[++vm->sp] = 3;
        vm->stk[++vm->sp] = i;
        func_001c19f8(vm, 3); return;

    case 5:
        {
        s32 c, d;
        D_00389C90.x3158[0] = p[0];
        D_00389C90.x3158[1] = p[1];
        c = p[2];
        D_00389C90.x3158[2] = c;
        d = p[3];
        D_00389C90.x3158[3] = d;
        D_00389C90.x3158[4] = p[4];
        if (c == 5) { func_001c4198(D_003DE570, d); return; }
        func_001c4198(D_003DE570, 0);
        }

    }
}
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003D.h"
#include "data/pieces/D_002BBDFC.h"
