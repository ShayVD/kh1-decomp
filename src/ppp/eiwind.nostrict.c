/* pppEiWfaccFrame, -fno-strict-aliasing (docs/modules.md "Session 50"): a
 * wind force on the owner: inside a source's range and cone (a pppEiWindFun
 * work area, or D_00575A00), it accelerates the owner's velocity by the
 * source's force, scaled by the angle and distance and divided by the key's
 * mass.  Read from the code, not proved by a boot. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

/* pppEiWfaccFrame (from hand/nostrict/text_00190000_h63.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
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
extern PppSystem *D_00615E60;
extern f32 D_00575A00;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct {
    s32 frame;
    s32 slot0, off0;
    s32 slot1, off1;
    f32 mass;  /* +0x14 */
} PppWfaccKey;
typedef struct {
    f32 x, y, z;
    f32 range;  /* +0xC */
    f32 unk10;
    f32 min;    /* +0x14 */
    f32 force;  /* +0x18 */
} PppWfacc;
f32 func_00267390(PppWfacc *, f32 *);
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
void pppEiWfaccFrame(PppObject *obj, PppWfaccKey *key, PppEntry *e) {
    PppVec4 v;
    f32 *p = PPP_WORK(f32, obj, e, 0);
    PppWfacc *a;
    f32 *b;
    f32 len, d, k;
    f32 *w;

    if (key->slot0 != -1)
        a = (PppWfacc *) (D_00615E60->slots[key->slot0].inst + key->off0 + 0xA0);
    else
        a = (PppWfacc *) &D_00575A00;
    if (key->slot1 != -1)
        b = (f32 *) (D_00615E60->slots[key->slot1].inst + key->off1 + 0xA0);
    else
        b = &D_00575A00;
    v[0] = p[0] - b[0];
    v[1] = p[1] - b[1];
    v[2] = p[2] - b[2];
    len = vu0Normalize(v);
    if (len < a->range) {
        d = func_00267390(a, v);
        if (a->min < d) {
            k = a->force * ((d - a->min) / (1.0f - a->min)) * ((a->range - len) / a->range) / key->mass;
            w = PPP_WORK(f32, obj, e, 1);
            w[0] += v[0] * k;
            w[1] += v[1] * k;
            w[2] += v[2] * k;
        }
    }
}
#undef PPP_WORK

