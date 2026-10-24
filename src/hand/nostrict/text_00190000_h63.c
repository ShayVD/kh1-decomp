/* ppp component callbacks around 0x18a000-0x194000, by hand (worker 63).
 * This region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;

typedef struct {
    u8 pad[0x30];
    f32 col[4];     /* +0x30 */
    u8 pad40[0x40];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

typedef f32 PppVec4[4] __attribute__((aligned(16)));

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

u8 *func_00182588(PppSystem *, PppSlot *);

/* Start an instance of program slot `id` owned by `o`. */
static inline u8 *inl_spawn(PppSystem *sys, s32 id, PppObject *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(PppObject **) (i + 4) = o;
    }
    return i;
}

typedef struct {
    s32 frame;
    s32 unk4;
    u8 col[4];     /* +0x8 */
    f32 f0C;       /* +0xC */
    u16 h10, h12;  /* +0x10 */
    u16 h14;       /* +0x14 */
} PppLnsClmKey;

static inline f32 vu0Normalize(f32 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vadd.xyz $vf8xyz, $vf0xyz, $vf10xyz\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vmove.xyz $vf9xyz, $vf10xyz\n"
        "vaddx.y $vf9y, $vf9y, $vf9x\n"
        "vaddy.z $vf9z, $vf9z, $vf9y\n"
        "vsqrt Q, $vf9z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 %0, $vf10\n"
        "vdiv Q, $vf0w, $vf10x\n"
        "vwaitq\n"
        "vmulq.xyz $vf9xyz, $vf8xyz, Q\n"
        "sqc2 $vf9, 0(%1)\n"
        : "=r"(r) : "r"(v) : "memory");
    return r;
}

void func_00192708(PppObject *, PppLnsClmKey *, PppEntry *);

void func_00192708(PppObject *, PppLnsClmKey *, PppEntry *);

/* needs make: uses rodata */
