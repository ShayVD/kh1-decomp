#include "common.h"
#include "data/bss_0064.h"

typedef struct { u64 a; s32 unk8; u8 pad[0xC0 - 12]; } Blk;
typedef struct {
    u32 state;
    f32 t;
    s32 x8;
    s32 xc;
    s32 x10;
    u8 pad14[0x20 - 0x14];
    Blk b20;
    Blk bE0;
    Blk b1A0;
    Blk b260[3];
    Blk b4A0;
    Blk b560;
    Blk b620[5];
    Blk b9E0;
} S8370;
typedef struct { s32 a, b, c, d; } Q4;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
extern S8370 D_00668370;
Q D_00668120 ALIGNED(32);
Q4 *D_00668284 ALIGNED(4);
extern Q4 *D_00668280;
extern Q4 D_00351E10[];
extern u8 D_004268B0[], D_004267F0[];
void func_002370c8(Q *);
void func_00237018(void *, s32, s32);
s32 func_002485f0(void);
s32 func_0023cfc8(void);
void func_00246570(Blk *, void *, s32, s32, f32);
s32 func_002466e8(s32);
void func_00246708(Blk *, Blk *, s32);
void func_00246658(s32, s32 *);

void func_00246750(s32 a0) {
    s32 t[5];
    Blk blk;
    S8370 *p;
    s32 y = 24;
    s32 i, n, c;
    Blk *q;
    Blk *bp;
    func_002370c8(&D_00668120);
    D_00668120.unkE0 = 5;
    D_00668120.unk60 = 0x30003;
    func_00237018(&D_00668120, 22, 1);
    D_00668284 = D_00351E10;
    D_00668280 = D_00351E10 + 1;
    p = &D_00668370;
    if (func_002485f0() & 2) y = 80;
    else if (func_002485f0() & 1) y = 65;
    if (func_0023cfc8()) y += 28;
    func_00246570(&p->b20, D_004268B0, 16, y, p->t);
    for (i = 0; i < 3; i++) func_00246570(&p->b260[i], D_004267F0, 16, y, p->t);
    n = func_002466e8(p->x10);
    c = n < 150;
    bp = &blk;
    q = &p->bE0;
    if (c) {
        func_00246708(bp, q, n);
        func_00246570(bp, D_004268B0, 16, y, p->t);
    } else func_00246570(q, D_004268B0, 16, y, p->t);
    q = &p->b4A0;
    if (c) {
        func_00246708(bp, q, n);
        func_00246570(bp, D_004267F0, 16, y, p->t);
    } else func_00246570(q, D_004267F0, 16, y, p->t);
    func_00246658(a0, t);
    for (i = 0; i < 5; i++) {
        func_00246708(&blk, &p->b620[i], t[i]);
        func_00246570(&blk, D_004267F0, 16, y, p->t);
    }
    func_00246570(&p->b1A0, D_004268B0, n + 44, y, p->t);
    func_00246570(&p->b560, D_004267F0, n + 44, y, p->t);
    for (i = 4; i >= 0; i--) if (t[i] > 0) break;
    if (i > 0) func_00246570(&p->b9E0, D_004267F0, t[i] + 44, y, p->t);
    func_00237018(D_00668284, D_00668280 - D_00668284, 1);
}

typedef struct { u8 pad[0x24]; s32 x; s32 y; s32 on; u8 pad30[4]; s32 v34; s32 v38; s32 v3C; s32 v40; } Clk;
extern void *D_00669358[];
u8 D_006692F0[0x18] ALIGNED(16);
void func_00247678(s32, s32 *, s32 *);
void func_002474e8(void *, void *, s32, s32, f32);

void func_002476a0(Clk *o) {
    s32 a, b;
    s32 x, y;
    x = o->x; x += 73; y = o->y;
    if (o->on) {
        func_00247678(o->v40, &a, &b);
        func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
        x += 15;
        func_002474e8(D_00669358[b], D_006692F0, x, y, 1.0f);
        x += 16;
        func_002474e8(D_00669358[10], D_006692F0, x, y, 1.0f);
        x += 13;
    }
    func_00247678(o->v3C, &a, &b);
    func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
    x += 15;
    func_002474e8(D_00669358[b], D_006692F0, x, y, 1.0f);
    x += 17;
    func_002474e8(D_00669358[11], D_006692F0, x, y, 1.0f);
    x += 9;
    func_00247678(o->v38, &a, &b);
    func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
    x += 15;
    func_002474e8(D_00669358[b], D_006692F0, x, y, 1.0f);
    x += 17;
    func_002474e8(D_00669358[11], D_006692F0, x, y, 1.0f);
    x += 5;
    func_002474e8(D_00669358[11], D_006692F0, x, y, 1.0f);
    x += 4;
    func_00247678(o->v34, &a, &b);
    func_002474e8(D_00669358[a], D_006692F0, x, y, 1.0f);
    func_002474e8(D_00669358[b], D_006692F0, x + 15, y, 1.0f);
}

/* needs make: uses rodata */

s32 func_00270f00(s32, s32, s32, s32);
void func_00271070(s32);
s32 func_002713b0(s32, s32, s32);
s32 func_002715a0(s32, s32, s32 *);
extern s32 D_00425C10;
extern s32 D_00425C14;
extern s32 D_00647FB0;
extern s32 D_00647FB4;
extern s32 D_00647FC4;
extern s32 D_00647FC8;
extern s32 D_00647FD4;
extern s32 D_00647FD8;
extern s32 D_00648014;
extern s32 D_00648020;
extern s32 D_00648028;
extern s32 D_0064802C;
extern s32 D_00648030;
extern void (*D_00648034)(s32);

void func_00236190(void) {

    switch (D_00647FB4) {
    case 0:
        func_00270f00(D_00425C10, D_00425C14, D_00648020, 2);
        D_00647FB4++;
        break;
    case 1:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 2: {
        s32 v = D_00647FC8;
        if (v >= 0) {
            D_00648030 = v;
            D_00647FB4++;
            break;
        }
        if (v == -2) D_00648014 = 1;
        else if (v == -3) D_00648014 = 2;
        else if (v == -4) D_00648014 = 3;
        else if (v == -5) D_00648014 = 4;
        else if (v == -7) D_00648014 = 5;
        else D_00648014 = 7;
        goto common; }
    case 3:
        func_002713b0(D_00648030, D_00648028, D_0064802C);
        D_00647FB4++;
        break;
    case 4:
        if (func_002715a0(1, 0, &D_00647FC8)) D_00647FB4++;
        break;
    case 5: {
        s32 v = D_00647FC8;
        if (v >= 0) {
            if (v == D_0064802C) D_00648014 = 0;
            else D_00648014 = 6;
        } else {
            if (v == -2) D_00648014 = 1;
            else if (v == -3) D_00648014 = 2;
            else if (v == -4) D_00648014 = 5;
            else if (v == -5) D_00648014 = 4;
            else if (v == -8) D_00648014 = 6;
            else D_00648014 = 7;
        }
        D_00647FB4++;
        break; }
    case 6:
        func_00271070(D_00648030);
        D_00647FB4++;
        break;
    case 7:
        if (func_002715a0(1, 0, &D_00647FC8)) {
        common:
            D_00647FB0 = 0;
            D_00647FD8 = D_00647FD4;
            if (D_00648034) D_00648034(D_00647FC4);
        }
        break;
    }
}

typedef struct { u8 pad[8]; s32 on; s32 mode; s32 a; s32 b; } Sc;
extern s32 D_00467408;
int sprintf(char *, const char *, ...);
void func_002475d0(s32, s32, u8 *, f32, char *, s32);
extern char D_004917D8[];

void func_00247cf8(Sc *p) {
    char buf[16];
    u8 col[3];
    col[0] = 0xff;
    col[1] = 0xff;
    col[2] = 0xff;
    switch (p->mode) {
    case 1:
        sprintf(buf, "%01d", p->a);
        func_002475d0(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            func_002475d0(84, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, "%01d", p->b);
            func_002475d0(97, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    case 2:
        sprintf(buf, D_004917D8, p->a);
        func_002475d0(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            func_002475d0(97, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, D_004917D8, p->b);
            func_002475d0(110, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    case 3:
        sprintf(buf, "%03d", p->a);
        func_002475d0(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            func_002475d0(110, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, "%03d", p->b);
            func_002475d0(123, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    case 4:
        sprintf(buf, "%04d", p->a);
        func_002475d0(69, 22, col, 1.0f, buf, D_00467408);
        if (p->on) {
            sprintf(buf, "/");
            func_002475d0(123, 22, col, 1.0f, buf, D_00467408);
            sprintf(buf, "%04d", p->b);
            func_002475d0(136, 22, col, 1.0f, buf, D_00467408);
        }
        break;
    }
}
