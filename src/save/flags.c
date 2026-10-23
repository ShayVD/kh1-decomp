/* The script's save-data commands (docs/modules.md "Session 35"),
 * 0x001eac68-0x001ec7c0.
 *
 * Getters, setters and VM library entries (D_003D9FE0 2033-2057 and others)
 * over save block 1 (func_00232cc0(1), include/save/save1.h): the name
 * (func_001eac68 / func_001ec678), the reset of the whole block
 * (func_001eacd0), the flag arrays fl / fl2 / fl3 / fl5 (bit 7 of byte n / 8
 * first), the flag words w[] (bit 31 first), the score tables tbl[32][5]
 * (func_001eb698 inserts a score; flags.fmam.c's func_001eb7b0 inserts a
 * pair), the list switches at 0xad0 and the words at 0xdc4-0xdd4, one bit
 * of save block 2 (func_001ec5d8 / func_001ec610), and the records at
 * 0x34c / 0x368 (func_001ec6f8 / func_001ec758). */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/vm_sub.h"
#include "save/save1.h"
#include "data/types/text_001d0000_b11.h"
#include "data/types/text_001e0000_h21.h"

/* Save block 2's byte 0x1b (func_00232cc0(2)), read signed and written
 * unsigned. */
typedef struct { u8 pad[0x1b]; union { s8 s; u8 u; } f1b; } Save2;
/* h45's view of the score tables from +4 (func_001eb698, func_001eb7b0). */
typedef struct { u8 pad[0xb10]; u32 tbl[4][5]; } Save1Tbl;
typedef struct { s32 x0; Save1Tbl s; } Save1T;

extern S10 D_004908E0;
extern Str10 D_004908F0;
extern S10 D_00490900;

void *func_00232cc0(s32);
void func_001ba2a8(s32, u8 *);

void func_001eac68(void);
void func_001eacd0(void);
u8 *func_001eafd8(void);
u8 *func_001eaff8(void);
u8 *func_001eb018(void);
s32 func_001eb038(s32 n);
void func_001eb0a0(s32 n, s32 on);
s32 func_001eb140(VmRec *vm);
s32 func_001eb1d8(VmRec *vm);
s32 func_001eb278(VmRec *vm);
s32 func_001eb318(s32 n);
s32 func_001eb380(VmRec *vm);
void func_001eb418(s32 n, s32 on);
s32 func_001eb4b8(VmRec *vm);
s32 func_001eb558(VmRec *vm);
s32 func_001eb5f0(s32 a, s32 b);
void func_001eb640(s32 a, s32 b, s32 x);
s32 func_001eb698(VmRec *vm);
s32 func_001eb7b0(VmRec *vm);
s32 func_001eb910(VmRec *vm);
s32 func_001eb9a8(s32 a, s32 b);
void func_001eb9f8(s32 a, s32 b, s32 on);
s32 func_001eba80(VmRec *vm);
s32 func_001ebb10(VmRec *vm);
s32 func_001ebba0(VmRec *vm);
s32 func_001ebc38(s32 n);
void func_001ebca0(s32 n, s32 on);
s32 func_001ebd48(VmRec *vm);
s32 func_001ebde0(VmRec *vm);
s32 func_001ebe80(void);
s32 func_001ebea8(void);
void func_001ebed0(s32 on);
s32 func_001ebf18(void);
s32 func_001ebf48(VmRec *vm);
s32 func_001ebf98(void);
s32 func_001ebfc8(void);
s32 func_001ebff0(VmRec *vm);
s32 func_001ec040(VmRec *vm);
void func_001ec0b0(void);
s32 func_001ec0d8(VmRec *vm);
s32 func_001ec1a0(VmRec *vm);
s32 func_001ec258(s32 n);
void func_001ec2c0(s32 n, s32 on);
u8 func_001ec360(void);
void func_001ec380(s32 x);
s32 func_001ec3b0(VmRec *vm);
s32 func_001ec3f8(VmRec *vm);
s32 func_001ec468(VmRec *vm);
void func_001ec4b8(void);
void func_001ec4e0(void);
s32 func_001ec510(void);
s32 func_001ec538(s32 n);
void func_001ec570(s32 n, s32 on);
s32 func_001ec5d8(s32 n);
void func_001ec610(s32 n, s32 on);
s32 func_001ec678(void);
s32 func_001ec6f8(s32 a, s32 b);
void func_001ec758(s32 a, s32 b, s32 x);

void func_001eac68(void) {
    S10 t = D_004908E0;
    u8 *p = (u8 *)((Save1 *)func_00232cc0(1))->ad0.b.name;
    u32 i;
    for (i = 0; i < 10; i++) {
        *p++ = t.c[i];
    }
}

void func_001eacd0(void) {
    Str10 tmp = D_004908F0;
    Save1 *s;
    u8 *q;
    s32 i, j;

    s = (Save1 *)func_00232cc0(1);
    q = (u8 *)func_00232cc0(2);
    for (i = 0; i < 2048; i++) s->u.z.a[i] = 0;
    for (i = 0; i < 256; i++) s->u.z.b[i] = 0;
    for (i = 0; i < 384; i++) s->u.z.c[i] = 0;
    for (i = 0; i < 1024; i++) q[i] = 0;
    for (i = 0; i < 10; i++) {
        if (i == 9) {
            s->l2[i] = 0;
            s->l1[i] = 0;
            s->l0[i] = 0;
        } else {
            s->l2[i] = i + 1;
            s->l1[i] = i + 1;
            s->l0[i] = i + 1;
        }
    }
    for (i = 0; i < 50; i++) {
        if (i == 49) s->l3[i] = 0;
        else s->l3[i] = i + 1;
    }
    s->ad0.b.f2 = 0;
    s->ad0.b.f1 = 0;
    s->ad0.b.f0 = 0;
    s->ad0.b.f3 = 0;
    for (i = 0; i < sizeof(tmp); i++) s->ad0.b.name[i] = tmp.s[i];
    s->x.i.g0 = 0;
    s->x.i.g1 = 0;
    s->x.i.g2 = 0;
    s->x.i.g3 = 0;
    s->x.i.g4 = 0;
    for (i = 0; i < 32; i++)
        for (j = 0; j < 5; j++) s->tbl[i][j] = -1;
    for (i = 0; i < 8; i++) s->x.i.h[i] = 0;
    s->x.i.dd0 = 0;
    s->dd4 = 0;
    for (i = 0; i < 5; i++) {
        func_001ec758(0, i, -1);
        func_001ec758(1, i, -1);
        func_001ec758(2, i, -1);
        func_001ec758(3, i, -1);
    }
}

u8 *func_001eafd8(void) {
    return (u8 *)((Save1 *)func_00232cc0(1))->ad0.b.name;
}

u8 *func_001eaff8(void) {
    return &((Save1 *)func_00232cc0(1))->u.z.c[4];
}

u8 *func_001eb018(void) {
    return &((Save1 *)func_00232cc0(1))->u.z.c[9];
}

s32 func_001eb038(s32 n) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    return (((Save1 *)func_00232cc0(1))->fl[q] >> s) & 1;
}

void func_001eb0a0(s32 n, s32 on) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    Save1 *v = func_00232cc0(1);
    if (on) v->fl[q] |= 1 << s;
    else v->fl[q] &= ~(1 << s);
}

s32 func_001eb140(VmRec *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    ((Save1 *)func_00232cc0(1))->fl[q] |= 1 << s;
    vm->sp--;
    return 2;
}

s32 func_001eb1d8(VmRec *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    ((Save1 *)func_00232cc0(1))->fl[q] &= ~(1 << s);
    vm->sp--;
    return 2;
}

s32 func_001eb278(VmRec *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    vm->stk[vm->sp] = (((Save1 *)func_00232cc0(1))->fl[q] >> s) & 1;
    return 2;
}

s32 func_001eb318(s32 n) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    return (((Save1 *)func_00232cc0(1))->fl2[q] >> s) & 1;
}

s32 func_001eb380(VmRec *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    ((Save1 *)func_00232cc0(1))->fl2[q] |= 1 << s;
    vm->sp--;
    return 2;
}

void func_001eb418(s32 n, s32 on) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    Save1 *v = func_00232cc0(1);
    if (on) v->fl2[q] |= 1 << s;
    else v->fl2[q] &= ~(1 << s);
}

s32 func_001eb4b8(VmRec *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    vm->stk[vm->sp] = (((Save1 *)func_00232cc0(1))->fl2[q] >> s) & 1;
    return 2;
}

s32 func_001eb558(VmRec *vm) {
    Save1 *v = func_00232cc0(1);
    s32 i, c;
    for (i = 0, c = 0; i < 100; i++) {
        s32 q = i / 8;
        s32 s = 7 - (i % 8);
        c += (v->fl2[q] >> s) & 1;
    }
    vm->sp++;
    vm->stk[vm->sp] = c;
    return 2;
}

s32 func_001eb5f0(s32 a, s32 b) {
    return ((Save1 *)func_00232cc0(1))->tbl[a][b];
}

void func_001eb640(s32 a, s32 b, s32 x) {
    ((Save1 *)func_00232cc0(1))->tbl[a][b] = x;
}

s32 func_001eb698(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i = vm->sp;
    s32 a = s->stk[i - 2];
    s32 b = s->stk[i - 1];
    u32 c = s->stk[i];
    Save1T *r = func_00232cc0(1);
    Save1Tbl *q = &r->s;
    s32 j, k;
    for (j = 0; j < 5; j++) {
        if (q->tbl[a][j] == -1 || (b == 0 && q->tbl[a][j] < c) || (b == 1 && q->tbl[a][j] > c)) {
            for (k = 4; j < k; k--) q->tbl[a][k] = q->tbl[a][k - 1];
            q->tbl[a][j] = c;
            break;
        }
    }
    vm->sp -= 3;
    return 2;
}

/* func_001eb7b0 is in src/save/flags.fmam.c. */

s32 func_001eb910(VmRec *vm) {
    s32 a = vm->stk[vm->sp - 1];
    s32 b = vm->stk[vm->sp] - 1;
    Save1 *v = func_00232cc0(1);
    vm->sp--;
    vm->stk[vm->sp] = v->tbl[a][b];
    return 2;
}

s32 func_001eb9a8(s32 a, s32 b) {
    s32 s = 31 - b;
    return (((Save1 *)func_00232cc0(1))->w[a] >> s) & 1;
}

void func_001eb9f8(s32 a, s32 b, s32 on) {
    s32 s = 31 - b;
    Save1 *v = func_00232cc0(1);
    if (on) v->w[a] |= 1 << s;
    else v->w[a] &= ~(1 << s);
}

s32 func_001eba80(VmRec *vm) {
    s32 a = vm->stk[vm->sp - 1];
    s32 b = vm->stk[vm->sp];
    s32 s = 32 - b;
    ((Save1 *)func_00232cc0(1))->w[a] |= 1 << s;
    vm->sp -= 2;
    return 2;
}

s32 func_001ebb10(VmRec *vm) {
    s32 a = vm->stk[vm->sp - 1];
    s32 b = vm->stk[vm->sp];
    s32 s = 32 - b;
    ((Save1 *)func_00232cc0(1))->w[a] &= ~(1 << s);
    vm->sp -= 2;
    return 2;
}

s32 func_001ebba0(VmRec *vm) {
    s32 b = vm->stk[vm->sp];
    s32 a = vm->stk[vm->sp - 1];
    s32 s = 32 - b;
    Save1 *v = func_00232cc0(1);
    vm->sp--;
    vm->stk[vm->sp] = (v->w[a] >> s) & 1;
    return 2;
}

s32 func_001ebc38(s32 n) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    return (((Save1 *)func_00232cc0(1))->fl3[q] >> s) & 1;
}

void func_001ebca0(s32 n, s32 on) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    Save1 *v = func_00232cc0(1);
    if (on) v->fl3[q] |= 1 << s;
    else v->fl3[q] &= ~(1 << s);
}

s32 func_001ebd48(VmRec *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    ((Save1 *)func_00232cc0(1))->fl3[q] |= 1 << s;
    vm->sp--;
    return 2;
}

s32 func_001ebde0(VmRec *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    vm->stk[vm->sp] = (((Save1 *)func_00232cc0(1))->fl3[q] >> s) & 1;
    return 2;
}

s32 func_001ebe80(void) {
    return ((Save1 *)func_00232cc0(1))->x.f.dc4 & 1;
}

s32 func_001ebea8(void) {
    return (((Save1 *)func_00232cc0(1))->x.f.dc4 >> 2) & 1;
}

void func_001ebed0(s32 on) {
    Save1 *v = func_00232cc0(1);
    v->x.f.dc4 = (v->x.f.dc4 & ~4) | ((on & 1) * 4);
}

s32 func_001ebf18(void) {
    Save1 *v = func_00232cc0(1);
    v->x.f.dc4 |= 4;
    return 2;
}

s32 func_001ebf48(VmRec *vm) {
    Save1 *v = func_00232cc0(1);
    vm->sp++;
    vm->stk[vm->sp] = v->x.f.dc4 & 1;
    return 2;
}

s32 func_001ebf98(void) {
    Save1 *v = func_00232cc0(1);
    v->x.f.dc4 |= 1;
    return 2;
}

s32 func_001ebfc8(void) {
    return (((Save1 *)func_00232cc0(1))->x.f.dc4 >> 1) & 1;
}

s32 func_001ebff0(VmRec *vm) {
    Save1 *v = func_00232cc0(1);
    vm->sp++;
    vm->stk[vm->sp] = (v->x.f.dc4 >> 1) & 1;
    return 2;
}

s32 func_001ec040(VmRec *vm) {
    Save1 *v = func_00232cc0(1);
    if (vm->stk[vm->sp]) v->x.f.dc4 |= 2;
    else v->x.f.dc4 &= ~2;
    vm->sp--;
    return 2;
}

void func_001ec0b0(void) {
    Save1 *v = func_00232cc0(1);
    v->x.f.dc4 |= 2;
}

s32 func_001ec0d8(VmRec *vm) {
    Save1 *v = func_00232cc0(1);
    switch (vm->stk[vm->sp]) {
    case 0: v->ad0.open |= 1; break;
    case 1: v->ad0.open |= 2; break;
    case 2: v->ad0.open |= 4; break;
    case 3: v->ad0.open |= 8; break;
    }
    vm->sp--;
    return 2;
}

s32 func_001ec1a0(VmRec *vm) {
    Save1 *v = func_00232cc0(1);
    switch (vm->stk[vm->sp]) {
    case 0: vm->stk[vm->sp] = (u8)v->ad0.open & 1; break;
    case 1: vm->stk[vm->sp] = (v->ad0.open >> 1) & 1; break;
    case 2: vm->stk[vm->sp] = (v->ad0.open >> 2) & 1; break;
    case 3: vm->stk[vm->sp] = (v->ad0.open >> 3) & 1; break;
    }
    return 2;
}

s32 func_001ec258(s32 n) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    return (((Save1 *)func_00232cc0(1))->x.f.fl5[q] >> s) & 1;
}

void func_001ec2c0(s32 n, s32 on) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    Save1 *v = func_00232cc0(1);
    if (on) v->x.f.fl5[q] |= 1 << s;
    else v->x.f.fl5[q] &= ~(1 << s);
}

u8 func_001ec360(void) {
    return ((Save1 *)func_00232cc0(1))->x.i.dd0;
}

void func_001ec380(s32 x) {
    ((Save1 *)func_00232cc0(1))->x.i.dd0 = x;
}

s32 func_001ec3b0(VmRec *vm) {
    Save1 *v = func_00232cc0(1);
    vm->sp++;
    vm->stk[vm->sp] = v->x.i.dd0;
    return 2;
}

s32 func_001ec3f8(VmRec *vm) {
    Save1 *v = func_00232cc0(1);
    if (vm->stk[vm->sp]) v->x.f.dc4 |= 8;
    else v->x.f.dc4 &= ~8;
    vm->sp--;
    return 2;
}

s32 func_001ec468(VmRec *vm) {
    Save1 *v = func_00232cc0(1);
    vm->sp++;
    vm->stk[vm->sp] = (v->x.f.dc4 >> 3) & 1;
    return 2;
}

void func_001ec4b8(void) {
    Save1 *v = func_00232cc0(1);
    v->x.f.dc4 |= 8;
}

void func_001ec4e0(void) {
    Save1 *v = func_00232cc0(1);
    v->x.f.dc4 &= ~8;
}

s32 func_001ec510(void) {
    return (((Save1 *)func_00232cc0(1))->x.f.dc4 >> 3) & 1;
}

s32 func_001ec538(s32 n) {
    return (((Save1 *)func_00232cc0(1))->dd4 >> ~n) & 1;
}

void func_001ec570(s32 n, s32 on) {
    Save1 *v = func_00232cc0(1);
    if (on) v->dd4 |= 1 << (31 - n);
    else v->dd4 &= ~(1 << (31 - n));
}

s32 func_001ec5d8(s32 n) {
    return (((Save2 *)func_00232cc0(2))->f1b.s >> n) & 1;
}

void func_001ec610(s32 n, s32 on) {
    Save2 *v = (Save2 *)func_00232cc0(2);
    if (on) v->f1b.u |= 1 << n;
    else v->f1b.u &= ~(1 << n);
}

s32 func_001ec678(void) {
    S10 t = D_00490900;
    Save1 *v = func_00232cc0(1);
    u32 i;
    for (i = 0; i < 10; i++) {
        v->ad0.b.name[i] = t.c[i];
    }
    func_001ba2a8(0, (u8 *)v->ad0.b.name);
    return 2;
}

/* The records at 0x34c (b == 0) and 0x368 (four words each), by offset. */
s32 func_001ec6f8(s32 a, s32 b) {
    u8 *v = (u8 *)func_00232cc0(1);
    s32 off;
    if (b == 0) off = a * 4 + 0x34c;
    else off = (a * 4 + b) * 4 + 0x368;
    return *(s32 *)(v + off);
}

void func_001ec758(s32 a, s32 b, s32 x) {
    u8 *v = (u8 *)func_00232cc0(1);
    s32 off;
    if (b == 0) off = a * 4 + 0x34c;
    else off = (a * 4 + b) * 4 + 0x368;
    *(s32 *)(v + off) = x;
}
#include "data/pieces/D_004908E0.h"
#include "data/pieces/D_004908F0.h"
#include "data/pieces/D_00490900.h"
