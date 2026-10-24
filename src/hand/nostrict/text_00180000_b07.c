/* Hand-matched functions (worker b07). Built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

void sceVu0MulMatrix(void *, void *, void *);

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef f32 PppVec4[4] __attribute__((aligned(16)));

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

/* --- func_00182870: build the object matrix D_00615E70 --- */

typedef struct {
    f32 x, y, z, w;
} V4F __attribute__((aligned(16)));

typedef struct {
    u8 pad0[0x80];
    f32 x80, x84, x88;
    u8 pad8c[4];
    u8 x90[0x10];
    f32 xa0, xa4, xa8;
    u8 padac[0xf9 - 0xac];
    u8 xf9;
    u8 xfa;
    u8 padfb[0x104 - 0xfb];
    s32 x104;
} MOwner;

typedef struct {
    f32 x0, x4, x8;
    u8 padc[4];
    u8 x10[0x10];
    f32 x20, x24, x28;
    u8 pad2c[0x14];
    f32 x40, x44, x48;
    u8 pad4c[0x8c - 0x4c];
    MOwner *own;
    u8 pad90[0xb2 - 0x90];
    u8 xb2;
} MObj;

extern V4F D_00615E70;
V4F D_00615E80 ALIGNED(16);
V4F D_00615E90 ALIGNED(16);
V4F D_00615EA0 ALIGNED(16);
extern V4F D_00615F70; /* src/data/bss_0061.c: f32 D_00615F70[4] */
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"

void func_00183be0(void *, void *);
void func_002675a8(void *, void *);
void func_00121fc4(void *, void *);
f32 atan2f(f32, f32);
f32 asinf(f32);

static inline void vu0ScaleRow2(f32 s, void *row) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}

static inline void setTrans(V4F *m, MObj *o) {
    m[3].x = o->x0;
    m[3].y = o->x4;
    m[3].z = o->x8;
}

static inline void addTrans(V4F *m, V4F *d) {
    m[3].x += d->x;
    m[3].z += d->z;
}

void func_00182870(MObj *o) {
    V4F m[4];
    f32 ang[3];
    s32 i;

    func_00183be0(&D_00615E70, o->x10);
    vu0ScaleRow2(o->x20, &D_00615E70);
    vu0ScaleRow2(o->x24, &D_00615E80);
    vu0ScaleRow2(o->x28, &D_00615E90);
    if (o->own->xf9) {
        vu0ScaleRow2(o->x40, &D_00615E70);
        vu0ScaleRow2(o->x44, &D_00615E80);
        vu0ScaleRow2(o->x48, &D_00615E90);
    }
    setTrans(&D_00615E70, o);
    func_00183be0(m, o->own->x90);
    vu0ScaleRow2(o->own->xa0, &m[0]);
    vu0ScaleRow2(o->own->xa4, &m[1]);
    vu0ScaleRow2(o->own->xa8, &m[2]);
    m[3].x = o->own->x80;
    m[3].y = o->own->x84;
    m[3].z = o->own->x88;
    sceVu0MulMatrix(&D_00615E70, &D_00615E70, m);
    if (o->own->xfa && o->own->x104 >= 0) {
        func_00183be0(m, o->own->x90);
        vu0ScaleRow2(o->own->xa0 * o->x20, &m[0]);
        vu0ScaleRow2(o->own->xa4 * o->x24, &m[1]);
        vu0ScaleRow2(o->own->xa8 * o->x28, &m[2]);
        func_002675a8(&D_00615E70, &m[0]);
        func_002675a8(&(&D_00615E70)[1], &m[1]);
        func_002675a8(&(&D_00615E70)[2], &m[2]);
    }
    if (o->xb2) {
        addTrans(&D_00615E70, &D_00615F70);
    }
    {
        f32 *w;
        i = 0;
        w = &m[0].w;
        for (; i < 3; i++) {
            func_00121fc4(&m[i], &(&D_00615E70)[i]);
            D_003701F0[i] = *w;
            *w = 0.0f;
            w += 4;
        }
    }
    ang[0] = atan2f(-m[1].z, m[0].z);
    ang[1] = asinf(-m[2].z);
    ang[2] = atan2f(m[2].y, m[2].x);
    for (i = 0; i < 3; i++) D_003701E0[i] = ang[i] * 32768.0f / 3.1415926f;
    func_002675a8(&D_003701D0, &D_00615EA0);
}

/* --- pppDrawMdl* draw callbacks: fill a PppMdlDraw for func_001aaf88 --- */

/* --- pppKeThSft: per-frame shift of a key work area --- */

/* --- pppKeBornRnd: spawn instances at vertices of a vertex map --- */
typedef struct {
    s32 frame;
    s16 map0;     /* +0x4 */
    s16 map1;     /* +0x6 */
    u8 count;     /* +0x8 */
    u8 mask;      /* +0x9 */
    u8 rnd;       /* +0xA */
    u8 padB;
    s32 slot;     /* +0xC */
    s32 off0;     /* +0x10 */
    s32 off1;     /* +0x14 */
    s32 off2;     /* +0x18 */
} PppBornRndKey;
void sceVu0CopyMatrix(void *, void *);
void func_001a90f8(void *, void *, void *);

/* --- pppKeBornRnd4: born-at-random plus spawn at vertices --- */

/* --- pppKeMdlTfdUv / Uv2: scrolled texture page upload, then draw --- */

/* --- pppKeShpTail3Frame --- */

/* --- pppKeShpDttDraw --- */

typedef unsigned int u128 __attribute__((mode(TI)));

static inline void dttSet(f32 *v, f32 x, f32 y, f32 z, f32 w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

/* --- pppKeTkFadeDraw: build a faded 256-entry CLUT and upload it --- */

/* --- pppDrawMdlTs3Draw --- */
#include "data/data_0037.h"
