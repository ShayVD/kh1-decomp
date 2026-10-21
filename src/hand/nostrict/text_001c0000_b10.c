#include "common.h"

/* D_00389C90: script/event manager state. */
typedef struct {
    u8 pad0[0x3034];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    u8 pad3040[0x30];
    u64 f3070;
    u64 f3078;
} Big;

/* Script VM instance (0x350 bytes). */
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
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, brest:22;
    u8 pad32c[0x24];
} __attribute__((aligned(8))) VM;

extern Big D_00389C90;
extern VM D_003A7990[], D_003B4DA0[];
extern s32 D_003B4D90, D_003C21A0, D_002C5958;
extern s32 (*D_0037A198[])(VM *, s32);
#include "data/pieces/D_0037A378.h"
extern s32 D_002BCDE4, D_002BCC90;
s32 func_001c1ce8(s8 *, s32);
s32 func_001c1cf8(s8 *, s32);
void *func_0011ef10(s32, void *);
void func_001c3408(void);
void func_001c2ec8(s32, u32);

void func_001c3770(s8 *p, s32 a1) {
    s32 done = 0;
    VM *e, *e2;
    s32 h0;
    s32 *cnt;
    s32 i, j, k;
    s32 op, arg, r;
    D_00389C90.f3070 &= ~0x10000000000ULL;
    h0 = ((s32 *)p)[0];
    { u32 n = (a1 + (((s32 *)p)[1] + h0)) * 4; p += *(s32 *)((u32)p + n + 16); }
    p += 12;
    if (a1 == 0) { e = D_003A7990; cnt = &D_003B4D90; }
    else { e = D_003B4DA0; cnt = &D_003C21A0; }
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
        p += 4;
        e->ret[7] = e->pc;
        e->b0 = 0; e2 = e; e2->b1 = 0; e->b2 = 0; e->b3 = 0; e->b4 = 0;
        e->b5 = 1;
        e->b6 = 0; e->b7 = 0; e2->b8 = 0; e2->b9 = 0;
        k = 0;
        for (j = 0; j < e2->n; j++) {
            e2->lbl[j] = k;
            while (p[3] != 5) { p += 4; k++; }
            p += 4; k++;
        }
    }
    if (a1 == 0) { e = D_003A7990; cnt = &D_003B4D90; }
    else { e = D_003B4DA0; cnt = &D_003C21A0; }
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
        if (!((D_00389C90.f3070 >> 42) & 1)) {
            func_0011ef10(50001, func_001c3408);
            D_00389C90.f3070 |= 0x40000000000ULL;
        }
        D_00389C90.x3038 = a1;
    } else {
        D_00389C90.x3038 = 0;
    }
}

void func_001c4808(s32 a, u32 b) {
    if (((u32)D_0037A378 >> 1) & 1) return;
    if ((s32)(D_00389C90.f3070 >> 40) & 1) return;
    if ((s32)(D_00389C90.f3078 >> 7) & 1) return;
    D_00389C90.x303c = a;
    if (b == 0) return;
    if (b < 100) {
        if (D_00389C90.x3034 != b) {
            func_001c2ec8(D_002BCDE4, b);
            D_00389C90.f3078 |= 64;
        }
    } else if (D_00389C90.x3038 == 0) {
        func_001c3770((s8 *)D_002BCC90, b - 100);
    }
}
#include "data/data_002B.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
