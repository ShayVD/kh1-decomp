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
s32 func_001c3b10(Task *t) {
    s32 n;
    Msg m;
    Msg msgs[256];
    s32 used[256];
    s32 i, j, k;
    VMa *vm, *e;
    Msg *p;
    u32 mask;
    u32 c;
    s32 *pn;
    s32 op, arg, r;
    n = 0;
    D_00389C90.x316c = t;
    mask = D_00389C90.x3148;
    D_002C5BB0.x4 &= mask;
    D_002C5BB0.x8 &= mask;
    if (~(mask >> 23) & 1) {
        for (i = 0; i < 3; i++) {
            D_002C5BB0.x40[i] = 0;
            D_002C5BB0.x60[i] = 0;
        }
    }
    vm = t->vm;
    pn = &t->n;
    p = func_001c4730();
    while (p) {
        msgs[n++] = *p;
        p = func_001c4730();
    }
    for (i = 255; i >= 0; i--) used[i] = 0;
    if (D_00389C90.f3070.f.b43 == 1) func_001cebe8();
    if (D_00389C90.f3070.f.b38 == 1) func_001cff28();
    if (D_00389C90.f3070.f.b39 == 1) func_001cfff8();
    if (D_00389C90.f3078.b.b10) func_001ca800();
    if (D_00389C90.f3070.f.b53) return 0;
    for (i = 0; i < *pn; i++, vm++) {
        if (vm->b3) {
            if (i != 0) continue;
            if (t->x18 != 0) {
                D_00389C90.x3034 = 0;
                for (j = 1, e = &D_0038D170[1]; j < t->n; j++, e++) {
                    if (e->b0 == 1) {
                        m.type = 2;
                        m.val = (u32)e->f20;
                        m.x = e->x0;
                        m.v[0] = e->f14;
                        m.v[1] = e->f18;
                        m.v[2] = e->f1c;
                        m.v[3] = 10.0f;
                        func_001c4640(&m);
                    }
                }
                for (k = 0; k < n; k++) if (!used[k]) func_001c4788(&msgs[k]);
                return 0;
            }
            D_00389C90.x3040 = D_00389C90.x3044;
            D_00389C90.x3060 = D_00389C90.x3068;
            D_00389C90.x3048 = D_00389C90.x3050;
            D_00389C90.x304c = D_00389C90.x3054;
            D_00389C90.x305c = D_00389C90.x3064;
            c = D_003C39A8;
            D_00389C80 = c;
            for (i = 0; i < c; i++) D_00388480[i] = D_003C21A8[i];
            for (k = 0; k < n; k++) if (!used[k]) func_001c4788(&msgs[k]);
            return 4;
        }
        if (vm->b8) continue;
        func_001dcea8(vm);
        func_001dcfd0(vm);
        if ((vm->b2 && !vm->b4)) {
            vm->x2f4 -= D_002BBDFC;
            if (vm->x2f4 > 0.0f) continue;
            vm->b2 = 0;
        }
        for (k = 0; k < n; k++) {
            switch (msgs[k].type) {
            case 2:
                if (msgs[k].x == vm->x0) { vm->b0 = 0; used[k] = 1; }
                break;
            case 4:
                if (msgs[k].x == vm->x0) { vm->b1 = 0; used[k] = 1; }
                break;
            case 21:
                if (msgs[k].x == vm->x0) { vm->b1 = 0; used[k] = 1; }
                break;
            case 22:
                if (msgs[k].x == vm->x0) { vm->b1 = 0; used[k] = 1; }
                break;
            }
        }
        for (;;) {
            op = func_001c1ce8(vm->code, vm->pc);
            arg = func_001c1cf8(vm->code, vm->pc);
            r = D_0037A198[op](vm, arg);
            if (r & 2) vm->pc++;
            if (r & 4) break;
            if (r & 8) {
                D_00389C90.x3040 = D_00389C90.x3044;
                D_00389C90.x3060 = D_00389C90.x3068;
                D_00389C90.x3048 = D_00389C90.x3050;
                D_00389C90.x304c = D_00389C90.x3054;
                D_00389C90.x305c = D_00389C90.x3064;
                c = D_003C39A8;
                D_00389C80 = c;
                for (i = 0; i < c; i++) D_00388480[i] = D_003C21A8[i];
                for (k = 0; k < n; k++) if (!used[k]) func_001c4788(&msgs[k]);
                return 4;
            }
        }
    }
    for (k = 0; k < n; k++) if (!used[k]) func_001c4788(&msgs[k]);
    return 0;
}
