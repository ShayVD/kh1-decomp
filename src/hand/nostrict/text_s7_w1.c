#include "common.h"

/* ---- func_00135bb0 ---- */
typedef union { u64 x; struct { u32 lo; u32 x32:13; u32 b45:1; u32 x46:3; u32 b49:1; u32 hi:14; } b; } F370e;
typedef struct { u8 p0[0x40]; f32 sx, sy, sz; u8 p4c[4]; f32 f50[4]; u8 p60[0xd0-0x60]; f32 fd0[4][4]; u8 p110[0x370-0x110]; F370e f370; } Ob9;
#include "data/pieces/D_002BBFA0.h"
extern void func_00135b88(Ob9 *, void *);
extern void sceVu0CopyMatrix(void *, void *);
extern void func_002675a8(f32 *, f32 *);
extern void sceVu0MulMatrix(void *, void *, void *);
extern s32 func_0012f040(Ob9 *, s32);
extern void func_0012ec88(Ob9 *, f32 *);
extern s32 func_0024edf0(f32 (*)[4], void *);
void func_00135a68(void *, f32, f32);
CONTEXT_ONLY void func_00135b88(Ob9 *o, void *b) { func_00135a68(b, *(f32 *)((u8 *)o + 0x410), *(f32 *)((u8 *)o + 0x414)); }
s32 func_00135bb0(Ob9 *o) {
    f32 m[4][4];
    f32 v[4];
    u8 buf[128];
    if (o->f370.b.b45 && o->sx * o->sy * o->sz == 0.0f) return 0;
    if (o->f370.b.b49) goto r1;
    func_00135b88(o, buf);
    sceVu0CopyMatrix(m, o->fd0);
    func_002675a8(m[3], o->f50);
    m[3][3] = 1.0f;
    sceVu0MulMatrix(m, D_002BBFA0, m);
    if (func_0012f040(o, -1)) {
        func_0012ec88(o, v);
        if (func_0024edf0(m, buf) == 0) goto r1;
        return 0;
    }
    if (func_0024edf0(m, buf) == 0) goto r1;
    return 0;
r1:
    return 1;
}

/* ---- func_0018d038 (pppKeBornRndFrame) ---- */
/* Hand-matched functions (worker b07). Built without strict aliasing. */
#include "ppp.h"

void sceVu0MulMatrix(void *, void *, void *);

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef f32 PppVec4[4] __attribute__((aligned(16)));
extern PppMtx D_00615FC0;

typedef struct {
    s32 init;
    f32 a, da, dda;  /* +0x4 */
    f32 b, db, ddb;  /* +0x10 */
} PppMdlLoop;

typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;

typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;

u8 *func_00182588(PppSystem *, PppSlot *);

/* Start an instance of program slot `id` owned by `o`. */

static inline u8 *inl_spawn(PppSystem *sys, s32 id, void *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(void **) (i + 4) = o;
    }
    return i;
}
void sceVu0CopyMatrix(void *, void *);
