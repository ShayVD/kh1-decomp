#include "common.h"
typedef struct {
    u8 pad0[0x3034];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    s8 *x3040;
    s8 *x3044;
    s32 x3048;
    s32 *x304c;
    s32 x3050;
    s32 *x3054;
    u8 pad3058[4];
    s32 x305c;
    s32 *x3060;
    s32 x3064;
    s32 *x3068;
    u8 pad306c[4];
    u64 f3070;
    u64 f3078;
    u8 pad3080[0xc0];
    s32 x3140;
    u8 pad3144[4];
    s32 x3148;
    f32 f314c;
} Big;
typedef struct {
    s32 x0, x4;
    u8 pad8[0x68];
    s8 *code;
    s32 n;
    s32 x78;
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[91];
    s32 x2f0;
    s32 x2f4;
    s32 ret[8];
    s32 rsp;
    u8 pad31c[0xc];
    u64 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, brest:54;
    u8 pad330[0x20];
} VM;
typedef struct { u32 b0:1, b1:1, b2:1, b3:1, rest:28; } Bits;
typedef struct { u8 pad[0x10]; VM *vm; s32 n; s32 x18; } Task;
extern Big D_00389C90;
extern u32 D_00389C80;
extern s32 D_00388480[];
extern s32 D_003C21A8[];
extern u32 D_003C39A8;
extern s8 *D_003C39AC;
extern Bits D_0037A378;
extern VM D_003C3A70[];
extern s32 D_003C54F0, D_002C5958;
extern u8 D_006297F8[];
extern s32 (*D_0037A198[])(VM *, s32);
s32 func_001c1ce8(s8 *, s32);
s32 func_001c1cf8(s8 *, s32);
void func_001c6720(void);
void func_001c2d20(s8 *, u32 *, s32 *);
Task *func_0011f090(void *, s32, void *);
void func_001c3b10(void);
void func_001c4198(s8 *h, s32 a1) {
    s32 done = 0;
    VM *e, *e2;
    s32 i;
    s32 *cnt;
    s32 *o, *o1, n0, n1;
    s32 j, k;
    s8 *p, *q;
    s32 op, arg, r;
    Task *t;
    s32 *src;
    D_00389C90.x3044 = D_00389C90.x3040;
    D_00389C90.x3050 = D_00389C90.x3048;
    D_00389C90.x3054 = D_00389C90.x304c;
    D_00389C90.x3064 = D_00389C90.x305c;
    D_00389C90.x3068 = D_00389C90.x3060;
    D_003C39A8 = D_00389C80;
    for (i = 0; i < D_00389C80; i++) D_003C21A8[i] = D_00388480[i];
    D_0037A378.b0 = 0;
    D_0037A378.b1 = 0;
    D_0037A378.b2 = 0;
    D_0037A378.b3 = 0;
    D_003C39AC = h;
    D_00389C90.x3148 = -1;
    D_00389C90.f314c = 1.0f;
    D_00389C90.x3140 = 0;
    func_001c6720();
    o = (s32 *)(h + 12);
    o1 = (s32 *)(h + 16);
    n0 = ((s32 *)h)[0];
    D_00389C90.x3048 = n0;
    D_00389C90.x3040 = h;
    n1 = ((s32 *)h)[1];
    D_00389C90.x3060 = o + n0 + 1;
    D_00389C90.x305c = n1;
    q = h + o[0];
    D_00389C90.x304c = o1;
    p = h + o[a1 + (n1 + n0) + 1];
    p += 12;
    e = D_003C3A70;
    cnt = &D_003C54F0;
    *cnt = *p++;
    for (i = 0; i < *cnt; i++, e++) {
        s32 m;
        e->x0 = 0;
        e->x4 = 0;
        e->code = p + 4;
        e->n = *p;
        e->pc = 0;
        e->sp = -1;
        e->x78 = 0;
        e->x2f0 = 0;
        e->rsp = 7;
        for (m = 7; m >= 0; m--) e->ret[m] = -1;
        p += 4;
        e->ret[7] = e->pc;
        e->b0 = 0; e2 = e; e2->b1 = 0; e->b2 = 0; e->b3 = 0; e->b4 = 0;
        e->b5 = 0;
        e->b6 = 0; e->b7 = 0; e2->b8 = 0; e2->b9 = 0;
        k = 0;
        for (m = 0; m < e2->n; m++) {
            e2->lbl[m] = k;
            while (p[3] != 5) { p += 4; k++; }
            p += 4; k++;
        }
    }
    func_001c2d20(q, &D_00389C80, D_00388480);
    e = D_003C3A70;
    cnt = &D_003C54F0;
    for (i = 0; i < *cnt; i++, e++) {
        e->pc = e->lbl[0];
        while (1) {
            op = func_001c1ce8(e->code, e->pc);
            arg = func_001c1cf8(e->code, e->pc);
            if (op == 5) break;
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
    }
    if (done == 0) {
        t = func_0011f090(D_006297F8, 1, func_001c3b10);
        t->vm = D_003C3A70;
        t->n = D_003C54F0;
        t->x18 = 0;
    }
}
