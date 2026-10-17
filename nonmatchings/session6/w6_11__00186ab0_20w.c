/* pppPointRApFrame 00186ab0, nostrict: 20 words off, FP register allocation only (orig keeps 32768.0f in f1, ours f5; everything else shifted). Structure/int regs match. */
#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef struct {
    s32 unk0;
    u8 *inst;
    s32 time;
    s32 unkC;
} PppSlot;

typedef struct {
    u8 pad[0x80];
    PppSlot *slots;
    u8 pad84[0x2C];
    u64 flags;
} PppSystem;

extern s32 D_0061621C;
extern PppSystem *D_00615E60;
extern f32 D_003732D0[];

u8 *func_00182588(PppSystem *, PppSlot *);

static inline u8 *inl_spawn(PppSystem *sys, s32 id, void *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(void **) (i + 4) = o;
    }
    return i;
}

static inline f32 vu0Rand(void) {
    f32 r;

    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=r"(r)
        :
        : "$8");
    return r;
}

typedef struct {
    s32 frame;
    f32 r;      /* +0x04 */
    f32 sp;     /* +0x08 */
    s32 slot;   /* +0x0C */
    s32 off0;   /* +0x10 */
    s32 pad14;
    s32 off1;   /* +0x18 */
    u8 n;       /* +0x1C */
} PtRApKey;

typedef struct {
    u8 b0;
    u8 cnt;
} PtRApWork;

void pppPointRApFrame(void *obj, PtRApKey *key, PppEntry *e) {
    PtRApWork *c = PPP_WORK(PtRApWork, obj, e, 1);
    f32 *w;
    u8 *inst;
    f32 *d0, *d1;
    u32 a;
    f32 s, co, x, y, z;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (c->cnt == 0) {
        w = PPP_WORK(f32, obj, e, 0);
        if (key->slot == -1)
            return;
        inst = inl_spawn(D_00615E60, key->slot, obj);
        a = (s32) (vu0Rand() * 32768.0f - 16384.0f);
        s = D_003732D0[(a >> 4) & 0xFFF];
        co = D_003732D0[((a + 0x4000) >> 4) & 0xFFF];
        y = s * key->r;
        co = co * key->r;
        a = (s32) (vu0Rand() * 32768.0f * 2.0f);
        x = D_003732D0[(a >> 4) & 0xFFF] * co;
        z = co * D_003732D0[((a + 0x4000) >> 4) & 0xFFF];
        d0 = (f32 *) (inst + key->off0 + 0xA0);
        d1 = (f32 *) (inst + key->off1 + 0xA0);
        d0[0] = w[0] + x;
        d0[1] = w[1] + y;
        d0[2] = w[2] + z;
        d1[0] = x * key->sp;
        d1[1] = y * key->sp;
        d1[2] = z * key->sp;
        c->cnt = key->n;
    }
    c->cnt--;
}
