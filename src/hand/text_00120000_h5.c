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
typedef struct S4c { u8 pad[0x4c]; u16 f4c; } S4c;
typedef struct V8 { s32 a, b; } V8;

/* 0x730-byte list node (pool D_004F8310[64], chained through next). */
#include "data/types/text_00120000_h5.h"

#include "data/pieces/D_002E31B0.h"

/* ---- data ---- */
extern V8 *D_00525288;
extern s32 D_0052528C;
extern V8 D_00524F80[];

/* ---- functions ---- */
extern Ent *func_001230a0(Ent *);
extern void *func_00123488();
extern void func_00124920(void);
extern void func_001247e8(Ent *);

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

/* ---- script command handlers (Arg *p) ---- */

/* f370 bits 37-38 as a bitfield (store zero-extends the u32 arg: lwu). */

/* Radians -> 16-bit angle units, three components. */

/* ---- */

/* Allocate a node and append it to a's chain. */
#include "data/bss_004F_typed.h"
#include "data/data_002E.h"
