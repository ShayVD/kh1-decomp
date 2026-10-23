#include "common.h"
#include "data/types/vm_rec.h"
#include "data/bss_0062.h"
/* func_001c2ec8 (s11w1): the op loop reaches D_002C5958 as &D_002C5950[2], a different RTL address (const (plus D_002C5950 8)) from the top `D_002C5958 |= 0xc`, so gcse PRE does not share the two and the hoisted lui/addiu orders as in the original. */
typedef struct {
    u8 pad0[0x1034];
    s32 a1034[512];
    s32 a1834[512];
    s32 a2034[512];
    s32 a2834[512];
    s32 x3034;
    s32 x3038;
    s32 x303c;
    s8 *x3040;
    s32 x3044;
    s32 x3048;
    s32 *x304c;
    u8 pad3050[0xc];
    s32 x305c;
    s32 *x3060;
    u8 pad3064[0xc];
    u64 f3070;
    union { u64 x; struct { u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, brest:25; u32 hi; } __attribute__((aligned(8))) b; } f3078;
    u8 pad3080[0x3178 - 0x3080];
    s32 x3178;
} Big;
typedef VmRec VM;
#include "data/pieces/D_0037A378.h"
extern Big D_00389C90;
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_0038D170.h"
extern s32 D_0039A570, D_003A7980;
extern s32 (*D_0037A198[])(VM *, s32);
extern s32 D_002C5958;
extern s32 D_002C5950[]; /* D_002C5950[2] is D_002C5958 */
extern s8 *D_003C39AC;
extern s32 D_006277E0, D_006277E4, D_006297F0, D_006297F4;
#include "data/pieces/D_00389C80.h"
#include "data/pieces/D_00388480.h"
s32 func_001c1ce8(s8 *, s32);
s32 func_001c1cf8(s8 *, s32);
void *func_0011ef10(s32, void *);
s32 func_001ee200(void);
void srand(u32);
void func_001c29d8(void);
void func_001c6720(void);
void func_001cab48(void);
void func_001c2d20(s8 *, s32 *, s8 **);
s32 func_001c2778();
void func_001c2ec8(s8 *p, s32 a1) {
    s32 done = 0;
    VM *e;
    s32 h0;
    s32 *cnt;
    s32 i, j, k;
    s32 op, arg, r;
    s8 *q;
    s8 *c;
    s32 *t;
    s32 (**fn)(VM *, s32);
    s32 *fl;
    D_003C39AC = p;
    (*(Bits_37a378 *)&D_0037A378).b2 = 0;
    (*(Bits_37a378 *)&D_0037A378).b3 = 0;
    (*(Bits_37a378 *)&D_0037A378).b4 = 0;
    if (a1 == 0) {
        srand(func_001ee200());
        (*(Bits_37a378 *)&D_0037A378).b0 = 0;
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
    D_00389C90.x3060 = t + 1 + h0;
    D_00389C90.x305c = ((s32 *)p)[1];
    D_00389C90.x3040 = p;
    q = p + *t;
    c = p + t[(a1 + (D_00389C90.x305c + h0)) + 1];
    c += 12;
    if (a1 == 0) { e = D_0038D170; cnt = &D_0039A570; }
    else { e = D_0039A580; cnt = &D_003A7980; }
    *cnt = *c++;
    for (i = 0; i < *cnt; i++, e++) {
        e->x0 = 0;
        e->obj = 0;
        e->code = c + 4;
        e->n = *c;
        e->pc = 0;
        e->sp = -1;
        e->x78 = 0;
        e->x2f0 = 0;
        e->rsp = 7;
        for (j = 0; j < 8; j++) e->ret[j] = -1;
        e->ret[7] = e->pc;
        for (j = 0; j < 26; j++) e->var[j] = 0;
        c += 4;
        e->fl.b.b0 = 0; e->fl.b.b1 = 0; e->fl.b.b2 = 0; e->fl.b.b3 = 0; e->fl.b.b4 = 0; e->fl.b.b5 = 0; e->fl.b.b6 = 0; e->fl.b.b7 = 0;
        e->fl.b.b8 = 0; e->fl.b.b9 = 0; e->fl.b.b10 = 0; e->fl.b.b11 = 0; e->fl.b.b12 = 0; e->fl.b.b13 = 0; e->fl.b.b14 = 0; e->fl.b.b15 = 0;
        k = 0;
        for (j = 0; j < e->n; j++) {
            e->lbl[j] = k;
            while (c[3] != 5) { c += 4; k++; }
            c += 4; k++;
        }
    }
    func_001c2d20(q, &D_00389C80, ((s8 **)&D_00388480));
    if (a1 == 0) e = D_0038D170;
    else e = D_0039A580;
    fn = D_0037A198;
    fl = &D_002C5950[2];
    e->pc = e->lbl[0];
    while ((op = func_001c1ce8(e->code, e->pc), arg = func_001c1cf8(e->code, e->pc), op != 5)) {
        r = fn[op](e, arg);
        if (r & 2) e->pc++;
        if (r & 8) {
            done = 1;
            *fl &= ~8;
            do { *fl &= ~4; } while (0);
            break;
        }
    }
    e->x78 = 1;
    e->pc = e->lbl[1];
    D_00389C90.x3034 = a1;
    if (!done) {
        if (a1 == 99 || D_00389C90.f3078.b.b6) {
            D_00389C90.f3078.b.b6 = 0;
            func_0011ef10(50001, func_001c2778);
            return;
        }
        func_0011ef10(50002, func_001c2778);
    }
}
#include "data/bss_0062_mixed.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003C.h"
