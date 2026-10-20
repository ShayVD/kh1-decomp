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

/* Shared loader body inlined into the four script-VM handlers below. The
   split tE load and the "p += 2; p += 2;" step are needed for the match
   (loop insn count / sched1 order). */
static inline void inl_load(u32 k) {
    u8 *p;
    s32 i;
    Elem *e;
    f32 tE;
    p = D_00389C90.x3040 + D_00389C90.x304c[k];
    D_0037A380.n = *(s32 *)p;
    p += 4;
    for (i = 0; i < D_0037A380.n; i++) {
        e = &D_0037A380.arr[i];
        __builtin_memcpy(&e->a, p, 4); p += 4;
        __builtin_memcpy(&e->b, p, 4); p += 4;
        e->c = *(s32 *)p; p += 4;
        __builtin_memcpy(&D_0037A380.arr[i].m[0], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[1], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[2], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[3], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[4], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[5], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[6], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[7], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[8], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[9], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.arr[i].m[10], p, 16); p += 16;
        D_0037A380.arr[i].f[0] = *(f32 *)p; p += 2; p += 2;
        D_0037A380.arr[i].f[1] = *(f32 *)p; p += 4;
        D_0037A380.arr[i].f[2] = *(f32 *)p; p += 4;
        D_0037A380.arr[i].f[3] = *(f32 *)p; p += 4;
        D_0037A380.arr[i].f[4] = *(f32 *)p; p += 4;
        D_0037A380.arr[i].f[5] = *(f32 *)p; p += 4;
        if (i == 0) {
            D_0037A380.arr[i].prev = 0;
            D_0037A380.arr[i].next = 0;
        } else {
            D_0037A380.arr[i - 1].next = (struct Elem *)e;
            e->next = 0;
            e->prev = (struct Elem *)&D_0037A380.arr[i - 1];
        }
    }
    D_0037A380.x0 = D_0037A380.arr[0].c;
    D_0037A380.first = &D_0037A380.arr[0];
    D_0037A380.last = &D_0037A380.arr[D_0037A380.n - 1];
    tE = D_0037A380.arr[0].f[5];
    D_003C5500 = D_0037A380.n + 1;
    __builtin_memcpy(&D_0037A380.q10, &D_0037A380.arr[0].m[5], 16);
    __builtin_memcpy(&D_0037A380.q20, &D_0037A380.arr[0].m[6], 16);
    __builtin_memcpy(&D_0037A380.q30, &D_0037A380.arr[0].m[7], 16);
    __builtin_memcpy(&D_0037A380.q40, &D_0037A380.arr[0].m[10], 16);
    D_0037A380.x60 = D_0037A380.arr[0].f[2];
    D_0037A380.xE0F4 = tE;
    D_0037A380.q50[0] = 0.0f;
    D_0037A380.q50[1] = 0.0f;
    D_0037A380.q50[2] = 0.0f;
    D_0037A380.q50[3] = 0.0f;
    func_001c53c8(D_0037A380.x0);
    __builtin_memcpy(&D_003C5510.v[0], &D_0037A380.q10, 16);
    __builtin_memcpy(&D_003C5510.v[1], &D_0037A380.q40, 16);
    __builtin_memcpy(&D_003C5510.v[2], &D_0037A380.q50, 16);
    __builtin_memcpy(&D_003C5510.v[4], &D_0037A380.q30, 16);
    __builtin_memcpy(&D_003C5510.v[3], &D_0037A380.q20, 16);
    D_003C5510.f120 = D_0037A380.x60;
    D_003C5510.f124 = D_0037A380.xE0F4;
    func_001c6a20();
    func_0011ef10(99999, func_001c5b88);
    D_00389C90.f3070.x |= 0x2000000000ULL;
}

s32 func_001c6d08(VMa *vm) {
    u32 k = vm->stk[vm->sp];
    if (k < D_00389C90.x3048) {
        D_00389C90.x3058 = 0;
        inl_load(k);
    }
    vm->sp--;
    return 2;
}

s32 func_001c71e8(VMa *vm) {
    u32 k = vm->stk[vm->sp - 1];
    VMa *r = func_001e98d0(vm->b5, vm->stk[vm->sp]);
    if (k < D_00389C90.x3048) {
        D_00389C90.x3058 = 1;
        if (r) D_00389C90.x306c = (s32)r->x4;
        inl_load(k);
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001c7700(VMa *vm) {
    u32 k = vm->stk[vm->sp - 1];
    VMa *r = func_001e98d0(vm->b5, vm->stk[vm->sp]);
    if (k < D_00389C90.x3048) {
        D_00389C90.x3058 = 2;
        if (r) D_00389C90.x306c = (s32)r->x4;
        inl_load(k);
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001c7c18(VMa *vm) {
    u32 k = vm->stk[vm->sp - 2];
    if (k < D_00389C90.x3048) {
        VMa *r;
        D_00389C90.x3058 = 3;
        r = func_001e98d0(vm->b5, vm->stk[vm->sp - 1]);
        if (r) D_00389C90.x306c = (s32)r->x4;
        r = func_001e98d0(vm->b5, vm->stk[vm->sp]);
        if (r) D_00389C90.f3070.w[0] = (s32)r->x4;
        inl_load(k);
    }
    vm->sp -= 3;
    return 2;
}
#include "data/data_003C.h"
