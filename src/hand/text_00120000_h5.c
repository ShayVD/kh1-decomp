#include "common.h"
#include "data/bss_004F.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"

/* Hand-matched functions, 0x00123298-0x0012fb18 (worker 5). */

/* ---- shared types ---- */

/* Entity walked by func_001230a0 (iterator: NULL starts, NULL ends). */
typedef struct Ent {
    union {
        u64 flags; /* 0x000 */
        u8 b[8];
    };
    u8 pad008[0x134 - 8];
    u8 *info; /* 0x134 */
    u8 pad138[0x370 - 0x138];
    u64 f370; /* bits 37-38: 2-bit state */
    u8 pad378[0x3a0 - 0x378];
    s32 f3a0;
    u8 pad3a4[4];
    s32 f3a8;
} Ent;

/* Script-command argument slot: the handlers take an Arg array and write
 * their result back into slot 0. */
typedef union Arg {
    s32 i;
    u32 u;
    f32 f;
    void *p;
} Arg;

typedef struct FV { f32 f0, f4, f8, f0c; } FV;
typedef struct S4c { u8 pad[0x4c]; u16 f4c; } S4c;
typedef struct S3c0 { u8 pad[0x3c0]; u8 f3c0[16]; } S3c0;
typedef struct V8 { s32 a, b; } V8;

/* 0x730-byte list node (pool D_004F8310[64], chained through next). */
#include "data/types/text_00120000_h5.h"

#include "data/pieces/D_002E31B0.h"

/* ---- data ---- */
#include "data/pieces/D_002E26A0.h"
extern u32 D_002E3190;
extern union { f32 f[4]; s32 i[4]; } D_002E27F0;
extern s32 D_004F82C0;
extern s32 D_004F82C4;
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31A8.h"
extern V8 *D_00525288;
extern s32 D_0052528C;
extern V8 D_00524F80[];

/* ---- functions ---- */
extern Ent *func_001230a0(Ent *);
extern void *func_00123488();
extern void func_00124920(void);
extern void func_001247e8(Ent *);
extern s32 func_00130030(void *);
extern void func_002675a8(void *, void *);
extern void func_002672f8(void *, void *, void *);
extern void func_00267e90(void *, void *, f32);
extern void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern void func_001149e8(f32 (*)[4], s32, s32, void *);
extern f32 func_00120bf8(s32);
extern f32 func_00121748(s32, s32);
extern void func_0014e668(s32, s32, f32, f32, s32);
extern void func_001315c0(void *, s32, f32, void *);
extern f32 func_00142cf0(s32, s32, f32, f32);
extern f32 func_00142e30(s32, s32, s32);
extern f32 func_00131a68(s32, s32);
extern void func_00138a20(s32, f32, s32);
extern void func_0014f658(void *, s32);
extern s32 func_0012f1d0(void *, s32);
extern f32 func_00132f00(s32);
extern void func_001358b8(void *, s32);
extern s32 func_0013c318(s32);
extern void func_002414a8(s32, s32);
extern void func_00153d88(void *);
extern s32 func_0013a440(s32, s32, f32, s32);
extern void func_00176c60(s32);

/* Count entities whose 2-bit state (f370 bits 37-38) is 2. */
s32 func_00123298(void) {
    Ent *p = 0;
    s32 n = 0;
    while ((p = func_001230a0(p)) != 0) {
        if (((p->f370 >> 37) & 3) == 2) n++;
    }
    return n;
}

s32 func_001232f0(Ent *e) {
    s32 r = 0;
    if (e->info && e->info[4] && e->f3a0 == 0) {
        r = 1;
        if ((e->flags & 0x8010) != 0x8000) r = 0;
    }
    return r;
}

s32 func_00123330(Ent *e) {
    s32 r = 0;
    if (e->info && e->info[5]) {
        r = 1;
        if ((e->flags & 0x8020) != 0x8000) r = 0;
    }
    return r;
}

/* Push cur onto a small stack (count at +0x388) and set cur = v. */
typedef struct Stk {
    s32 cur;
    u8 pad004[0x37c - 4];
    s32 stack[3];
    s32 n;
} Stk;
void func_00123438(Stk *s, s32 v) {
    s32 *n = &s->n;
    s32 c = s->cur;
    s32 i = *n;
    s->stack[i] = c;
    *n = i + 1;
    s->cur = v;
}

typedef struct S130 { u8 pad[0x130]; S4c *p; } S130;
s32 func_00123618(void) {
    S130 *p = func_00123488();
    if (p) return p->p->f4c;
    return 255;
}

void func_001249d8(void) {
    Ent *p = 0;
    func_00124920();
    while ((p = func_001230a0(p)) != 0) func_001247e8(p);
}

typedef struct Actor { u8 pad[0x70]; s32 f70; } S70;
s32 func_00125a00(s32 a) {
    S70 *p = D_002E26A0[0];
    if ((a & 1) && p->f70) return 0;
    return 1;
}

typedef struct S164 { u8 pad[0x164]; s32 f164; } S164;
s32 func_00125b68(S164 *e) {
    if ((D_002E3190 >> 8) & 0xffff) goto no;
    switch (e->f164) {
    case 138:
    case 61:
        return 1;
    case 200:
    case 202:
        if (func_00130030(e)) return 1;
        goto no;
    default:
        return 0;
    }
no:
    return 0;
}

typedef struct FTbl { f32 f0, f4, f8; } FTbl;
typedef struct S6c { u8 pad[0x20]; u8 f20[0x4c]; FTbl *tbl; } S6c;
void func_00126e80(S6c *a, s32 b, FV *p) {
    if (0.0f < p->f0c) {
        if (p->f0c > 0.7999999523162842f) p->f0c = a->tbl->f8;
        else p->f0c = a->tbl->f4;
        return;
    }
    if (p->f0 == 0.0f && p->f8 == 0.0f) func_002675a8(p, a->f20);
    p->f4 = 0;
    p->f0c = 0;
}

typedef struct SD0 { u8 pad[0xd0]; f32 m[4][4]; u8 pad110[0x44]; s32 f154; } SD0;
void func_00127b18(SD0 *a, f32 (*b)[4], s32 c) {
    f32 m[4][4] __attribute__((aligned(16)));
    sceVu0MulMatrix(m, b, a->m);
    D_002E27F0.f[3] = c;
    func_001149e8(m, a->f154, D_004F82C4 + D_004F82C0++, &D_002E27F0);
}

/* ---- script command handlers (Arg *p) ---- */

void func_00128fc8(Arg *p) {
    p->f = func_00120bf8(p->i);
}

void func_00129210(Arg *p) {
    p[0].f = func_00121748(p[0].i, p[1].i);
}

void func_00129240(Arg *p) {
    func_0014e668(p[0].i, 0, p[1].f, p[2].f, p[3].i);
}

void func_00129460(Arg *p) {
    func_001315c0(p[0].p, p[1].i, p[2].f, p[3].p);
}

void func_00129488(Arg *p) {
    p[0].f = func_00142cf0(p[0].i, p[1].i, p[2].f, p[3].f);
}

typedef struct S178 { u8 pad[0x178]; s32 f178; } S178;
void func_00129510(Arg *p) {
    if (((S178 *)p[0].p)->f178 == 0) p[0].i = 0;
    else p[0].i = 1;
}

void func_001295a0(Arg *p) {
    p[0].f = func_00142e30(p[0].i, p[1].i, p[2].i);
}

void func_001295d8(Arg *p) {
    p[0].f = func_00131a68(p[0].i, p[1].i);
}

void func_00129668(Arg *p) {
    func_00138a20(p[0].i, p[1].f, p[2].i);
}

typedef struct S24 { u8 pad[0x24]; f32 f24; } S24;
typedef struct S18 { u8 pad[0x18]; S24 *f18; } S18;
typedef struct S14cA { u8 pad[0x14c]; S18 *f14c; } S14cA;
void func_00129730(Arg *p) {
    p[0].f = ((S14cA *)p[0].p)->f14c->f18->f24;
}

typedef struct S3d4 { u8 pad[0x3d4]; f32 f3d4; } S3d4;
void func_00129898(Arg *p) {
    p[0].f = ((S3d4 *)p[0].p)->f3d4;
}

/* f370 bits 37-38 as a bitfield (store zero-extends the u32 arg: lwu). */
typedef struct B370 { u8 pad[0x370]; u64 lo:37; u64 b37:2; u64 hi:25; } B370;
void func_00129908(Arg *p) {
    B370 *e = p[0].p;
    e->b37 = p[1].u;
}

void func_00129dc8(Arg *p) {
    func_0014f658(p[0].p, 4);
    func_00267e90(((S3c0 *)p[0].p)->f3c0, p[1].p, ((FV *)p[1].p)->f0c);
}

void func_00129e48(Arg *p) {
    u8 buf[16];
    if (D_002E26A0[0] == 0) {
        p[0].i = 1;
        return;
    }
    func_001315c0(D_002E26A0[0], 0, 1.0f, buf);
    p[0].i = func_0012f1d0(buf, p[0].i) == 0;
}

typedef struct E1 {
    u8 pad0[0x30];
    FV f30;
    u8 pad40[0xd0 - 0x40];
    f32 fd0[4][4];
    u8 pad110[0x1cc - 0x110];
    s32 f1cc;
    u8 pad1d0[0x450 - 0x1d0];
    FV f450;
} E1;
void func_00129ed8(Arg *p) {
    E1 *e = p[0].p;
    if (e->f1cc & 8) {
        func_002675a8(p[1].p, &e->f450);
        ((FV *)p[1].p)->f0c = 0;
        func_002672f8(p[1].p, e->fd0, p[1].p);
        return;
    }
    func_002675a8(p[1].p, &e->f30);
}

void func_0012a068(Arg *p) {
    func_0014f658(p[0].p, 7);
    func_00267e90(((S3c0 *)p[0].p)->f3c0, p[1].p, ((FV *)p[1].p)->f0c);
}

void func_0012a0a8(Arg *p) {
    Ent *e = p[0].p;
    p[0].i = e ? (s32)(e->f370 >> 37) & 3 : 0;
}

void func_0012a1f8(Arg *p) {
    p[0].f = func_00132f00(p[0].i);
}

typedef struct S284 { u8 pad[0x284]; f32 f284; } S284;
void func_0012a2a0(Arg *p) {
    p[0].f = ((S284 *)p[0].p)->f284;
}

typedef struct E2 {
    s32 w0;
    u8 pad004[0x130 - 4];
    S4c *f130;
    u8 pad134[0x370 - 0x134];
    union { u64 v; u8 b[8]; } f370;
    u8 pad378[0x3b0 - 0x378];
    s32 f3b0;
    u8 pad3b4[0x3c0 - 0x3b4];
    u8 f3c0[16];
} E2;
void func_0012a2b0(Arg *p) {
    E2 *e = p[0].p;
    e->w0 |= 0x240;
    func_001358b8(e, 10);
    func_0014f658(e, 8);
    func_002675a8(e->f3c0, &D_002C58B0);
    e->f3b0 = 0;
    e->f370.v |= 1ULL << 60;
    func_002414a8(func_0013c318(e->f130->f4c), 3);
    func_00153d88(e);
}

/* Radians -> 16-bit angle units, three components. */
typedef struct S4p { u8 pad[4]; Arg *f4; } S4p;
void func_0012a628(Arg *p) {
    f32 *v = p[1].p;
    S4p *o = p[0].p;
    o->f4[0].i = (s32)(v[0] / 6.2831855f * 65536.0f) & 0xffff;
    o->f4[1].i = (s32)(v[1] / 6.2831855f * 65536.0f) & 0xffff;
    o->f4[2].i = (s32)(v[2] / 6.2831855f * 65536.0f) & 0xffff;
}

typedef struct B0 {
    union {
        u64 v;
        struct { u64 lo:2; u64 b2:2; u64 hi:60; } bf;
    };
} B0;
void func_0012a970(Arg *p) {
    B0 *e = p[0].p;
    if (e && ((s32)(e->v >> 11) & 1)) e->bf.b2 = p[1].u;
}

void func_0012aaf8(Arg *p) {
    p[0].i = func_0013a440(p[0].i, p[1].i, p[2].f, p[3].i);
}

/* ---- */

void func_0012b2c0(void) {
    s32 i;
    D_002E31A8 |= 2;
    for (i = 0; i < 3; i++) {
        if (D_002E26A0[i]) *(s32 *)D_002E26A0[i] |= 0x1000080;
    }
    func_00176c60(0);
}

typedef struct S54 { u8 pad[0x54]; s8 f54; } S54;
typedef struct E3 { u8 pad[0x130]; S54 *f130; } E3;
void func_0012b690(s32 *out) {
    Ent *p = 0;
    s32 n = 0;
    while ((p = func_001230a0(p)) != 0) {
        if (((E3 *)p)->f130->f54 == 10) n++;
    }
    *out = n;
}

/* Allocate a node and append it to a's chain. */
#include "data/bss_004F_typed.h"
#include "data/data_002E.h"
