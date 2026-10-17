/* Hand-matched functions from 0x001bfed8-0x001cc208 (worker 14); these need -fno-strict-aliasing. */
#include "common.h"

/* ---- types ---- */
/* 48-byte slots of the table D_0037A16C points to. */
typedef struct { u16 used; u16 h2; u16 h4; u8 pad6[26]; void (*fn)(void); u8 pad36[12]; } Slot;
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
typedef struct { u64 a, b, c, d; } Msg;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { u8 pad[176]; } Ent176;

/* ---- data ---- */
extern Slot *D_0037A16C;
extern s32 D_0037A168;
extern Big D_00389C90;
extern s32 D_003F34A4;
extern Tween D_003C5510;
extern f32 D_002BBDFC;
extern f32 D_003C55E0, D_003C55E4, D_003C55E8, D_003C55F4, D_003C55F8, D_003C5630, D_003C5634;
extern V4 D_003C55F0[];
extern u64 D_0038CD00;
extern s32 D_0038CD04;
extern f32 D_0036266C;
extern s32 D_006277E0, D_006277E4, D_006297F0, D_006297F4;
extern Msg D_006257E0[256], D_006277F0[256];
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

s32 func_001c1980(VM *v, s32 a, s32 b) {
    if (a < v->depth) {
        v->w756 = 0;
        v->ret[v->depth] = v->pc;
        v->depth = a;
        v->pc = b;
        v->flags &= ~4;
    } else if (a == v->depth) {
        v->pc = b;
        v->w756 = 0;
        v->flags &= ~4;
    }
    v->ret[a] = b;
    return 1;
}

s32 func_001c8c90(VM *v) {
    Tween *p;
    s32 sp;
    f32 a, b;
    func_001c6890(v);
    p = &D_003C5510;
    p->flags |= 4;
    p->start[0] = p->cur[0];
    sp = v->sp;
    p->t[0] = 0.0f;
    a = v->stack[sp - 1];
    b = v->stack[sp];
    v->sp = sp - 2;
    p->end[0] = b;
    p->dur[0] = a * 2.0f;
    return 2;
}

s32 func_001c8d98(VM *v) {
    Tween *p;
    s32 sp;
    f32 a, b;
    func_001c6890(v);
    p = &D_003C5510;
    p->flags |= 8;
    p->start[1] = p->cur[1];
    sp = v->sp;
    p->t[1] = 0.0f;
    a = v->stack[sp - 1];
    b = v->stack[sp];
    v->sp = sp - 2;
    p->end[1] = b;
    p->dur[1] = a * 2.0f;
    return 2;
}

s32 func_001c9ca8(VM *v) {
    Tween *p;
    s32 sp, m;
    f32 d, e;
    func_001c6890(v);
    p = &D_003C5510;
    p->flags |= 64;
    p->start[0] = p->cur[0];
    sp = v->sp;
    p->t[0] = 0.0f;
    m = v->stack[sp - 1];
    d = (f32)v->stack[sp - 2] * 2.0f;
    p->m[0] = m;
    e = v->stack[v->sp];
    v->sp -= 3;
    p->dur[0] = d;
    p->end[0] = e;
    return 2;
}

s32 func_001ca060(VM *v) {
    Tween *p;
    s32 sp, m;
    f32 d, e;
    func_001c6890(v);
    p = &D_003C5510;
    p->flags |= 128;
    p->start[1] = p->cur[1];
    sp = v->sp;
    m = v->stack[sp - 1];
    d = (f32)v->stack[sp - 2] * 2.0f;
    p->m[1] = m;
    e = v->stack[v->sp];
    v->sp -= 3;
    p->dur[1] = d;
    p->end[1] = e;
    return 2;
}
