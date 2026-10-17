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
void func_001c2ec8(s8 *p, s32 a1) {
    s32 done = 0;
    VMa *e, *e2;
    s32 h0;
    s32 *cnt;
    s32 i, j, k;
    s32 op, arg, r;
    s8 *q;
    s32 *t;
    D_003C39AC = p;
    ((Bits *)&D_0037A378)->b2 = 0;
    ((Bits *)&D_0037A378)->b3 = 0;
    ((Bits *)&D_0037A378)->b4 = 0;
    if (a1 == 0) {
        srand(func_001ee200());
        ((Bits *)&D_0037A378)->b0 = 0;
        D_002C5958 |= 0xc;
        func_001c29d8();
        D_006277E0 = 0;
        D_006277E4 = 0;
        D_006297F0 = 0;
        D_006297F4 = 0;
        D_00389C90.x3178 = 0;
        func_001c6720();
        func_001cab48();
    } else if (D_00389C90.x3034 == 0) {
        for (i = 0; i < 512; i++) {
            D_00389C90.a2034[i] = D_00389C90.a1034[i];
            D_00389C90.a2834[i] = D_00389C90.a1834[i];
        }
    }
    for (i = 0; i < 512; i++) {
        D_00389C90.a1034[i] = 0;
        D_00389C90.a1834[i] = 0;
    }
    h0 = ((s32 *)p)[0];
    t = (s32 *)p + 3;
    D_00389C90.x3048 = h0;
    D_00389C90.x304c = t + 1;
    D_00389C90.x305c = ((s32 *)p)[1];
    D_00389C90.x3060 = t + 1 + h0;
    D_00389C90.x3040 = (u8 *)p;
    q = p + *t;
    p += t[(a1 + (D_00389C90.x305c + h0)) + 1];
    p += 12;
    if (a1 == 0) { e = D_0038D170; cnt = &D_0039A570; }
    else { e = D_0039A580; cnt = &D_003A7980; }
    *cnt = *p++;
    for (i = 0; i < *cnt; i++, e++) {
        e->x0 = 0;
        e->x4 = 0;
        e->code = p + 4;
        e->n = *p;
        e->pc = 0;
        e->sp = -1;
        e->x78 = 0;
        e->x2f0 = 0;
        e->rsp = 7;
        for (j = 7; j >= 0; j--) e->ret[j] = -1;
        e->ret[7] = e->pc;
        for (j = 25; j >= 0; j--) e->var[j] = 0;
        p += 4;
        e->b0 = 0; e->b1 = 0; e->b2 = 0; e->b3 = 0; e->b4 = 0; e->b5 = 0; e->b6 = 0; e->b7 = 0;
        e->b8 = 0; e->b9 = 0; e->b10 = 0; e->b11 = 0; e->b12 = 0; e->b13 = 0; e->b14 = 0; e->b15 = 0;
        k = 0;
        for (j = 0; j < e->n; j++) {
            e->lbl[j] = k;
            while (p[3] != 5) { p += 4; k++; }
            p += 4; k++;
        }
    }
    func_001c2d20(q, &D_00389C80, D_00388480);
    if (a1 == 0) e = D_0038D170;
    else e = D_0039A580;
    e->pc = e->lbl[0];
    while (op = func_001c1ce8(e->code, e->pc), arg = func_001c1cf8(e->code, e->pc), op != 5) {
        r = D_0037A198[op](e, arg);
        if (r & 2) e->pc++;
        if (r & 8) {
            done = 1;
            D_002C5958 &= ~8;
            D_002C5958 &= ~4;
            break;
        }
    }
    e->x78 = 1;
    e->pc = e->lbl[1];
    D_00389C90.x3034 = a1;
    if (done) return;
    if (a1 == 99 || D_00389C90.f3078.b.b6) {
        D_00389C90.f3078.b.b6 = 0;
        func_0011ef10(50001, func_001c2778);
    } else {
        func_0011ef10(50002, func_001c2778);
    }
}
