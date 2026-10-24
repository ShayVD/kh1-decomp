#include "common.h"

/* ---- func_00135bb0 ---- */
typedef union { u64 x; struct { u32 lo; u32 x32:13; u32 b45:1; u32 x46:3; u32 b49:1; u32 hi:14; } b; } F370e;
typedef struct { u8 p0[0x40]; f32 sx, sy, sz; u8 p4c[4]; f32 f50[4]; u8 p60[0xd0-0x60]; f32 fd0[4][4]; u8 p110[0x370-0x110]; F370e f370; } Ob9;
extern void func_00135b88(Ob9 *, void *);
extern void sceVu0CopyMatrix(void *, void *);
extern void sceVu0MulMatrix(void *, void *, void *);
void func_00135a68(void *, f32, f32);
CONTEXT_ONLY void func_00135b88(Ob9 *o, void *b) { func_00135a68(b, *(f32 *)((u8 *)o + 0x410), *(f32 *)((u8 *)o + 0x414)); }

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
