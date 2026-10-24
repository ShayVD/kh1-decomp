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

typedef struct FV { f32 f0, f4, f8, f0c; } FV;
typedef struct S4c { u8 pad[0x4c]; u16 f4c; } S4c;
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
extern void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern void func_001149e8(f32 (*)[4], s32, s32, void *);

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

/* f370 bits 37-38 as a bitfield (store zero-extends the u32 arg: lwu). */

/* Radians -> 16-bit angle units, three components. */

/* ---- */

/* Allocate a node and append it to a's chain. */
#include "data/bss_004F_typed.h"
#include "data/data_002E.h"
