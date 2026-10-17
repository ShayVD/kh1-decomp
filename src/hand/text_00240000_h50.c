#include "common.h"

/* 16-byte list entries; the D_00667F50/D_00667F54-style globals are
 * [end, begin) pointers into such lists. */
typedef struct { s32 a, b, c, d; } Q4;

/* Panel state blocks (D_00667F60, D_00668290, D_00668F90, D_006691E0). */
typedef struct { u8 pad[0x60]; Q4 q[4]; Q4 r[4]; } Panel;

typedef struct { u8 pad[0x60]; u64 x60; u8 pad2[0x78]; u64 xe0; } S7df0;
typedef struct { u8 pad[0x4c]; u16 id; } S130;
typedef struct { u8 pad[0x130]; S130 *p; } SC;
typedef struct { u8 pad[0xc]; SC *c; } SArg;

typedef struct { u32 state; s32 cnt; u8 pad[0x18]; u8 sub[1]; } S5cd0;
typedef struct { s32 state; s32 cnt; u8 pad[0x28]; u8 sub[1]; } S70d0;
typedef struct { u8 pad0[0x20]; u8 a[0xc0]; u8 b[0x780]; } E860;
typedef struct { u8 pad0[0x30]; u8 a[0xc0]; u8 b[0xc0]; u8 c[0x780]; } E930;
typedef struct { u64 x[24]; } B192;
typedef struct { u8 pad[0x180]; B192 b; } L240;
typedef struct { u32 state; s32 cnt; u8 pad[0x18]; u8 sub[1]; } S5cd0b;
typedef struct { u32 state; f32 t; s32 x8; s32 xc; s32 x10; u8 pad[0xa8c]; s32 xaa0; } S8370;
typedef struct { u8 r, g, b, a; } RGBA;
typedef struct {
    s32 x0; s32 x4; u8 pad8[0x10]; s32 x18; s32 x1c; s32 x20;
    u8 pad24[8]; s32 x2c; s32 x30;
} Ctx;
typedef struct { s32 x0; Ctx *c; } S8140;

extern u8 D_0045BC10[];
extern E860 D_00662A30[10];
extern u8 D_0045D240[];
extern u8 D_0045D248[];
extern Panel D_00667F60;
extern Q4 *D_00667F50;
extern Q4 *D_00667F54;
extern S7df0 D_00667DF0;
extern Q4 D_00351E10[];
extern u8 D_00668040[];
extern u8 D_0045D280[];
extern u8 D_0045D6D0[];
extern B192 D_00668060;
extern Panel D_00668290;
extern Q4 *D_00668280;
extern S8370 D_00668370;
extern f32 D_002BBDFC;
extern Panel D_00668F90;
extern Q4 *D_00668F80;
extern u8 D_0045E1F0[];
extern E930 D_0045FAC0[10];
extern u8 D_0045FA80[];
extern u8 D_0045FA88[];
extern u8 D_0045FA90[];
extern Panel D_006691E0;
extern Q4 *D_006691D0;
extern Q4 *D_006691D4;
extern s32 D_00467408;
extern s32 D_0046740C;

void *memset(void *, s32, u32);
s32 sprintf(char *, const char *, ...);
u32 strlen(const char *);
void func_0011ef10(s32, void *);
s32 func_0011ef38(void *);
s32 func_0013c318(u16);
Q4 *func_001f12c0(Q4 *, s32, s32, s32, s32, s32, s32);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
Q4 *func_002388b8(void *, s32, Q4 *);
void func_002393d8(void);
s32 func_00242bf0(s32);
void func_00245b08(s32, S5cd0 *);
void func_00245da0(void);
void func_00246120(SArg *, s32, f32);
s32 func_00246320(void);
void func_00246750(s32, s32, s32, f32);
void func_00246ed8(s32, S70d0 *);
void func_00247190(void);
void func_00247b50(Ctx *);
void func_00247bd0(Ctx *);
void func_00247c50(Ctx *);
void func_00247cf8(Ctx *);
void func_002480d8(Ctx *);
s32 func_0024a1c0(void *);
void func_0024aa48(s32, void *, s32);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);

void func_00245e40(void) {
    s32 i;
    E860 *p;
    func_0024aac8(D_0045BC10);
    p = D_00662A30;
    for (i = 0; i < 10; i++) {
        func_0024af40(D_0045D240, p->a, D_0045BC10);
        func_0024af40(D_0045D248, p->b, D_0045BC10);
        p++;
    }
    if (func_0011ef38(func_00245da0) == 0)
        func_0011ef10(0x28489, func_00245da0);
}

void func_00246038(s32 a0, s32 a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_00667F60;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_00667F60.q[i].d = D_00667F60.q[i].d * s;
    }
    D_00667F50 = func_002388b8(&D_00667F60, 1, D_00667F50);
}

void func_002461f8(SArg *a0, s32 a1, f32 f) {
    s32 t, k;
    func_002370c8(&D_00667DF0);
    D_00667DF0.xe0 = 5;
    D_00667DF0.x60 = 0x30003;
    func_00237018(&D_00667DF0, 22, 1);
    D_00667F54 = D_00351E10;
    D_00667F50 = D_00351E10 + 1;
    func_00246120(a0, a1, f);
    t = func_0013c318(a0->c->p->id);
    if (t == 1) k = 1;
    else if (t == 2) k = 2;
    if (func_00242bf0(k)) {
        func_00237018(D_00667F54, D_00667F50 - D_00667F54, 1);
    }
}

void func_00246438(void) {
    L240 l;
    memset(D_00668040, 0, 32);
    func_0024aac8(D_0045D280);
    func_0024af40(D_0045D6D0, &l, D_0045D280);
    D_00668060 = l.b;
    if (func_0011ef38(func_00246320) == 0)
        func_0011ef10(0x28489, func_00246320);
}

void func_00246570(s32 a0, s32 a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_00668290;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_00668290.q[i].d = D_00668290.q[i].d * s;
    }
    D_00668280 = func_002388b8(&D_00668290, 1, D_00668280);
}

void func_00246dc0(s32 a0, s32 a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_00668F90;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_00668F90.q[i].d = D_00668F90.q[i].d * s;
    }
    D_00668F80 = func_002388b8(&D_00668F90, 1, D_00668F80);
}

void func_002470d0(S70d0 *p) {
    s32 r = 0;
    switch (p->state) {
    case 0:
        return;
    case 1:
        p->state = 2;
        r = 1;
        break;
    case 2:
        if (func_0024a1c0(p->sub) & 4) p->state++;
        break;
    case 3:
        p->state = 0;
        break;
    }
    p->cnt++;
    func_00246ed8(r, p);
}

void func_00247258(void) {
    s32 i;
    E930 *p;
    func_0024aac8(D_0045E1F0);
    p = D_0045FAC0;
    for (i = 0; i < 10; i++) {
        func_0024af40(D_0045FA80, p->a, D_0045E1F0);
        func_0024af40(D_0045FA88, p->b, D_0045E1F0);
        func_0024af40(D_0045FA90, p->c, D_0045E1F0);
        p++;
    }
    if (func_0011ef38(func_00247190) == 0)
        func_0011ef10(0x28489, func_00247190);
}

void func_002474e8(s32 a0, s32 a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_006691E0;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_006691E0.q[i].d = D_006691E0.q[i].d * s;
    }
    D_006691D0 = func_002388b8(&D_006691E0, 1, D_006691D0);
}

void func_002475d0(s32 a0, s32 a1, u8 *c, char *a3, s32 a4, f32 f) {
    RGBA col;
    col.r = *c++;
    col.g = *c++;
    col.b = *c++;
    col.a = (u32)(f * 128.0f);
    D_006691D0 = func_001f12c0(D_006691D0, 1, *(s32 *)&col, a0, a1, (s32)a3, a4);
}

/* ---- the functions below need make: they use rodata (jump tables,
 * string literals) ---- */

void func_00245cd0(S5cd0 *p) {
    s32 r = 0;
    switch (p->state) {
    case 0:
        return;
    case 1:
        r = 1;
        p->state++;
        break;
    case 2: case 3: case 4:
        p->state++;
        break;
    case 5:
        if (func_0024a1c0(p->sub) & 4) p->state++;
        break;
    case 6:
        p->state = 0;
        return;
    }
    p->cnt++;
    func_00245b08(r, p);
}

s32 func_00246aa8(void) {
    S8370 *p = &D_00668370;
    s32 f = p->xaa0;
    p->xaa0 = 0;
    switch (p->state) {
    case 0:
        return 0;
    case 1:
        p->t = 0.0f;
        p->state++;
        break;
    case 2:
        p->t += D_002BBDFC * 0.199999988079071044921875f;
        if (p->t >= 1.0f) {
            p->t = 1.0f;
            p->state++;
        }
        break;
    case 3:
        if (f == 0) p->state++;
        break;
    case 4:
        p->state++;
        p->t = 1.0f;
        break;
    case 5:
        p->t -= D_002BBDFC * 0.199999988079071044921875f;
        if (p->t <= 0.0f) {
            p->t = 0.0f;
            p->state = 0;
        }
        break;
    }
    func_00246750(p->xc, p->x10, f, p->t);
    return 0;
}

void func_00248010(Ctx *p) {
    char buf[16];
    u8 col[3];
    s32 x;
    col[0] = 0xff;
    col[1] = 0xff;
    col[2] = 0xff;
    sprintf(buf, "%d", p->x1c);
    x = 69;
    func_002475d0(x, 22, col, buf, D_00467408, 1.0f);
    x += strlen(buf) * 13;
    sprintf(buf, "m");
    func_002475d0(x + 2, 24, col, buf, D_0046740C, 1.0f);
}

/* func_00248010 must stay above this one (beqz vs beqzl). */
void func_00248140(S8140 *a) {
    Ctx *c;
    D_006691D4 = D_00351E10;
    D_006691D0 = D_00351E10 + 1;
    c = a->c;
    func_002393d8();
    if (c->x20) {
        if (c->x30 == 0) func_00247c50(c);
        else if (c->x2c == 0) func_00247bd0(c);
        else func_00247b50(c);
    }
    if (c->x4 || c->x18) func_002480d8(c);
    if (c->x4) func_00247cf8(c);
    if (c->x18) func_00248010(c);
    func_00237018(D_006691D4, D_006691D0 - D_006691D4, 1);
}
