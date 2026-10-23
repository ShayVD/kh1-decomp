/* Hand-matched functions from 0x001bfed8-0x001cc208 (worker 14). */
#include "common.h"
#include "data/bss_0062.h"

/* ---- types ---- */
/* 48-byte slots of the table D_0037A16C points to. */
#include "data/types/text_001b0000_h14_p.h"
/* Script VM: pc at +380, stack (sp at +384) at +388, registers, variables. */
typedef struct {
    u8 pad[380]; s32 pc; s32 sp; s32 stack[33]; s32 regs[26]; s32 vars[32]; s32 vidx;
    s32 w756; s32 ret[8]; s32 depth; u8 pad796[12]; u64 flags;
} VM;
/* D_00389C90 */
typedef struct {
    u8 b[4]; u8 c[8];
    union { u8 d[8]; struct { u8 pad[4]; u16 tbl[8][256]; } t; } u;
    s32 w[4]; u8 pad4128[16]; s8 idx[4]; u8 pad4148[8192];
    s32 w12340; s32 w12344; u8 pad12348[52]; u64 d12400; u64 d12408;
    u8 pad12416[192]; s32 w12608; s32 *p12612;
} Big;
/* D_003C5510: three interpolation channels. */
typedef struct {
    u64 flags; u8 pad8[4]; f32 dur[3]; u8 pad24[8]; f32 t[3]; u8 pad44[8]; s32 m[3];
    u8 pad64[32]; f32 start[3]; u8 pad108[36]; f32 end[3]; u8 pad156[132]; f32 cur[3]; f32 save;
} Tween;
#include "data/types/text_001b0000_h14.h"
typedef struct { f32 x, y, z, w; } V4;

/* ---- data ---- */
extern Slot *D_0037A16C;
extern s32 D_0037A168;
extern Big D_00389C90;
extern Tween D_003C5510;
extern f32 D_002BBDFC;
extern f32 D_003C55E0, D_003C55E4, D_003C55E8, D_003C55F4, D_003C55F8, D_003C5630, D_003C5634;
extern V4 D_003C55F0[];
extern u64 D_0038CD00;
extern s32 D_0038CD04;
extern f32 D_0036266C;
extern u8 D_0062A130[];
extern Ent176 D_00629E70[4];
typedef struct { u16 h; u8 pad[174]; } E176;
extern E176 D_006298F6[], D_006298F8[];

/* ---- functions ---- */
void func_001bffa0(s32 i);
void func_001c07f0(void);
void func_001dd170(void);
void func_001c6890(VM *v);
void func_001c6a20(Tween *t);
void func_001e9fe8(V4 *dst, V4 *src);
void func_001e9f18(V4 *dst, V4 *a, V4 *b, f32 t);
void func_0010bdd0(void *a, void *fn);
void func_0010bd90(void *a, void *fn);
void func_001caa20(void);
void func_001cae20(void *a, Ent176 *e);

s32 func_001bfed8(s32 a0) {
    s32 i;
    if (a0 == 0) {
        for (i = 1; i < 16; i++) {
            if (D_0037A16C[i].used == 0) return i;
        }
        return -1;
    }
    for (i = 0; i < 384; i++) {
        if (D_0037A16C[i + 16].used == 0) return i + 16;
    }
    return -1;
}

void func_001bffa0(s32 i) {
    if (i >= 0) {
        if (D_0037A16C[i].fn) D_0037A16C[i].fn();
        D_0037A16C[i].used = 0;
        D_0037A16C[i].h2 = 0;
        D_0037A16C[i].h4 = 0;
    }
}

typedef struct { u16 h0, h2, h4, h6; u8 *ctx; u8 *stk; u8 pad16[16]; void (*fn)(void); u8 pad36[12]; } Task;
typedef struct { u8 *ctx; s32 arg; } RunQ;
#include "data/pieces/D_0037A170.h"
extern s32 D_0037A174;
#define D_0037A16C (*(Task **)&D_0037A16C)
void func_001c0460(void) {
    s16 order[1024];
    s32 i, j, k, n;
    Task *p;
    Task **pp;
    RunQ *q;
    n = 1;
    for (i = 1; i < 400; i++) {
        if (D_0037A16C[i].h0 != 0) {
            if (D_0037A16C[i].h4 & 1) func_001bffa0(i);
        }
        if (D_0037A16C[i].h0 != 0) n++;
    }
    D_0037A174 = n;
    ((RunQ *)D_0037A170)[0].arg = 0;
    ((RunQ *)D_0037A170)[0].ctx = D_0037A16C[0].ctx;
    if (n < 2) return;
    order[0] = -1;
    n = 0;
    p = &D_0037A16C[1];
    for (i = 1; i < 400; i++, p++) {
        if (p->h0 == 0) continue;
        for (j = 0; j < n; j++) {
            if (D_0037A16C[i].h2 < D_0037A16C[order[j]].h2) break;
        }
        for (k = n - 1; k >= j; k--) order[k + 1] = order[k];
        order[j] = i;
        n++;
    }
    for (i = 0; i < n; i++) {
        ((RunQ *)D_0037A170)[i + 1].arg = order[i];
        ((RunQ *)D_0037A170)[i + 1].ctx = D_0037A16C[order[i]].ctx;
    }
    ((RunQ *)D_0037A170)[i + 1].arg = -1;
    ((RunQ *)D_0037A170)[i + 1].ctx = 0;
}
#undef D_0037A16C

void func_001c06c0(s32 i, void (*fn)(void)) {
    if (i < 0) i = D_0037A168;
    D_0037A16C[i].fn = fn;
}

void func_001c06f8(void) {
    Big **pb;
    Big *b = &D_00389C90;
    pb = &b;
    (*pb)->w12340 = 0;
    b->w12344 = 0;
    b->d12400 &= ~(1ULL << 58);
    func_001c07f0();
    func_001dd170();
}

s32 func_001c8478(VM *v) {
    f32 f;
    func_001c6890(v);
    f = D_003C55E0;
    v->sp++;
    v->stack[v->sp] = f;
    return 2;
}

s32 func_001c84c8(VM *v) {
    f32 f;
    func_001c6890(v);
    f = D_003C55E4;
    v->sp++;
    v->stack[v->sp] = f;
    return 2;
}

s32 func_001c8518(VM *v) {
    f32 f;
    func_001c6890(v);
    f = D_003C55E8;
    v->sp++;
    v->stack[v->sp] = f;
    return 2;
}

s32 func_001c8568(VM *v) {
    f32 f;
    func_001c6890(v);
    f = D_003C55F0[0].x / 3.1415928f * 180.0f;
    v->sp++;
    v->stack[v->sp] = f;
    return 2;
}

s32 func_001c85d8(VM *v) {
    f32 f;
    func_001c6890(v);
    f = D_003C55F4 / 3.1415928f * 180.0f;
    v->sp++;
    v->stack[v->sp] = f;
    return 2;
}

s32 func_001c8648(VM *v) {
    f32 f;
    func_001c6890(v);
    f = D_003C55F8 / 3.1415928f * 180.0f;
    v->sp++;
    v->stack[v->sp] = f;
    return 2;
}

s32 func_001c86b8(VM *v) {
    f32 f;
    func_001c6890(v);
    f = D_003C5630;
    v->sp++;
    v->stack[v->sp] = f;
    return 2;
}

s32 func_001c8708(VM *v) {
    f32 f;
    func_001c6890(v);
    f = D_003C5634;
    v->sp++;
    v->stack[v->sp] = f;
    return 2;
}

void func_001c8c10(void) {
    Tween *p = &D_003C5510;
    p->t[0] += D_002BBDFC;
    if (p->dur[0] < p->t[0]) {
        p->t[0] = p->dur[0];
        p->flags &= ~4;
    }
    p->cur[0] = p->start[0] + (p->end[0] - p->start[0]) / p->dur[0] * p->t[0];
    do { func_001c6a20(p); break; } while (1);
}

void func_001c8d18(void) {
    Tween *p = &D_003C5510;
    p->t[1] += D_002BBDFC;
    if (p->dur[1] < p->t[1]) {
        p->t[1] = p->dur[1];
        p->flags &= ~8;
    }
    p->cur[1] = p->start[1] + (p->end[1] - p->start[1]) / p->dur[1] * p->t[1];
    do { func_001c6a20(p); break; } while (1);
}

s32 func_001c92e8(void) {
    return ((u32)(D_0038CD00 >> 37) & 1) ? 4 : 2;
}

void func_001c9d40(void) {
    Tween *p = &D_003C5510;
    p->t[2] += D_002BBDFC;
    if (p->dur[2] < p->t[2]) {
        p->flags &= ~0x200;
        D_0036266C = p->end[2];
        return;
    }
    D_0036266C = (p->end[2] - p->start[2]) * (p->t[2] / p->dur[2]);
}

s32 func_001ca5f8(VM *v) {
    V4 out, tmp;
    V4 *b = D_003C55F0;
    func_001c6890(v);
    func_001e9fe8(&tmp, b);
    func_001e9f18(&out, b - 1, &tmp, b[4].x);
    v->sp++;
    v->stack[v->sp] = out.x;
    return 2;
}

s32 func_001ca680(VM *v) {
    V4 out, tmp;
    V4 *b = D_003C55F0;
    func_001c6890(v);
    func_001e9fe8(&tmp, b);
    func_001e9f18(&out, b - 1, &tmp, b[4].x);
    v->sp++;
    v->stack[v->sp] = out.y;
    return 2;
}

s32 func_001ca708(VM *v) {
    V4 out, tmp;
    V4 *b = D_003C55F0;
    func_001c6890(v);
    func_001e9fe8(&tmp, b);
    func_001e9f18(&out, b - 1, &tmp, b[4].x);
    v->sp++;
    v->stack[v->sp] = out.z;
    return 2;
}

s32 func_001caa50(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00389C90.b[i] != 0) break;
    }
    if (i < 4) return 0;
    func_0010bdd0(D_0062A130, func_001caa20);
    D_00389C90.idx[0] = 0;
    D_00389C90.b[0] = 2;
    return 4;
}

void func_001caae0(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        D_00389C90.b[i] = 0;
        D_00389C90.w[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        D_00389C90.c[i] = 0;
        D_00389C90.u.d[i] = 0;
    }
}

void func_001cac60(s32 x) {
    D_00389C90.w12608 = x;
    D_00389C90.d12400 &= ~(1ULL << 32);
    *D_00389C90.p12612 = x;
}

s32 func_001cae00(void) {
    return (D_0038CD04 & 1) ? 4 : 2;
}

void func_001cae20(void *a, Ent176 *e) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (&D_00629E70[i] == e) {
            s32 k = D_00389C90.idx[i];
            D_00389C90.b[i] = 0;
            D_00389C90.c[k] = 0;
            D_00389C90.w[k] = 0;
        }
    }
}

void func_001caf58(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_00389C90.b[i]) {
            func_0010bd90(&D_00629E70[i], func_001cae20);
            D_00389C90.b[i] = 3;
        }
    }
}

s32 func_001cc170(VM *v) {
    s32 k = v->stack[v->sp - 1];
    u16 val = v->stack[v->sp];
    v->sp -= 2;
    D_006298F6[k].h = val;
    return 2;
}

s32 func_001cc1c0(VM *v) {
    s32 k = v->stack[v->sp - 1];
    u16 val = v->stack[v->sp];
    v->sp -= 2;
    D_006298F8[k].h = val;
    return 2;
}
#include "data/bss_0062_mixed.h"
#include "data/bss_0062_typed.h"
#include "data/data_0036.h"
#include "data/data_0037.h"
#include "data/data_003C.h"
#include "data/data_003F.h"
#include "data/pieces/D_0037A130.h"
#include "data/pieces/D_002BBDFC.h"
