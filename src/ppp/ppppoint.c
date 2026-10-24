/* The ppp point classes' default-flag functions (docs/modules.md "Session
 * 50"): pppPObjPoint (the position of another instance), the Cons of
 * pppPointAp and pppPointRAp, and pppPointRApFrame (starts an effect at the
 * owner's position every n frames).  pppPointApFrame is in
 * ppppoint.nostrict.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "ppp.h"
#include "data/pieces/D_00370130.h"
#include "common.h"
#ifndef KH1_PS2
#include "platform/vu.h"
#endif

/* pppPObjPointFrame (from auto/text_00180000_10.c). */
extern M2C_UNK D_00575A00;
extern s32 D_0061621C;
extern void *D_00615E60;
void pppPObjPointFrame(void *arg0, void *arg1, void *arg2) {
    M2C_UNK *temp_v0_3;
    M2C_UNK *var_v0;
    s32 temp_v0_2;
    void *temp_a2;
    void *temp_v0;

    if ((D_0061621C == 0) && !(M2C_FIELD(D_00615E60, s64 *, 0xB0) & (((s64) 0xFF << 0x20) | 0xFF00))) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_a2 = temp_v0 + 0xA0;
        if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
            temp_v0_2 = M2C_FIELD(arg1, s32 *, 4);
            if (temp_v0_2 != -1) {
                var_v0 = M2C_FIELD(((temp_v0_2 * 0x10) + M2C_FIELD(D_00615E60, s32 *, 0x80)), s32 *, 4) + M2C_FIELD(arg1, s32 *, 8) + 0xA0;
            } else {
                var_v0 = &D_00575A00;
            }
            M2C_FIELD(temp_a2, M2C_UNK **, 0xC) = var_v0;
        }
        temp_v0_3 = M2C_FIELD(temp_a2, M2C_UNK **, 0xC);
        M2C_FIELD(temp_a2, f32 *, 0x0) = (f32) M2C_FIELD(temp_v0_3, f32 *, 0);
        M2C_FIELD(temp_a2, f32 *, 4) = (f32) M2C_FIELD(temp_v0_3, f32 *, 4);
        M2C_FIELD(temp_a2, f32 *, 8) = (f32) M2C_FIELD(temp_v0_3, f32 *, 8);
    }
}

/* pppPointApCon (from auto/text_00180000.c). */
void pppPointApCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[1]), s8 *, 0xA1) = 0;
}

/* pppPointRApCon (from auto/text_00180000.c). */
void pppPointRApCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[1]), s8 *, 0xA1) = 0;
}

/* pppPointRApFrame (from hand/text_00180000_s7_w30.c). */
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
#ifdef KH1_PS2
#define VU0_RAND(r) __asm__ volatile( \
        "addi $8, $0, -1\n" \
        "qmtc2 $8, $vf2\n" \
        "vrxor R, $vf2x\n" \
        "vrnext.x $vf1x, R\n" \
        "vrxor R, $vf2x\n" \
        "vrnext.x $vf1x, R\n" \
        "vrxor R, $vf2x\n" \
        "vrnext.x $vf1x, R\n" \
        "vrxor R, $vf2x\n" \
        "vrnext.x $vf1x, R\n" \
        "vrxor R, $vf2x\n" \
        "vrnext.x $vf1x, R\n" \
        "vitof0.x $vf2x, $vf2x\n" \
        "vadd.x $vf1x, $vf1x, $vf2x\n" \
        "qmfc2 %0, $vf1\n" \
        : "=r"(r) : : "$8")
#else
#define VU0_RAND(r) ((r) = PlatVu0Rand())
#endif
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
#define D_00615E60 ((PppSystem *) D_00615E60)
/* pppPointRApFrame 0x186ab0: MATCH hand (and hand/nostrict). The VU0 random helper as a statement macro writing a local (not a static inline returning f32): the two 32768.0f constants then stay separate pseudos, and post-reload cse reuses f1. */
void pppPointRApFrame(void *obj, PtRApKey *key, PppEntry *e) {
    PtRApWork *c = PPP_WORK(PtRApWork, obj, e, 1);
    f32 *w;
    u8 *inst;
    f32 *d0, *d1;
    u32 a;
    f32 s, co, x, y, z, r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (c->cnt == 0) {
        w = PPP_WORK(f32, obj, e, 0);
        if (key->slot == -1)
            return;
        inst = inl_spawn(D_00615E60, key->slot, obj);
        VU0_RAND(r);
        a = (s32) (r * 32768.0f - 16384.0f);
        s = D_003732D0[(a >> 4) & 0xFFF];
        co = D_003732D0[((a + 0x4000) >> 4) & 0xFFF];
        y = s * key->r;
        co = co * key->r;
        VU0_RAND(r);
        a = (s32) (r * 32768.0f * 2.0f);
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
#undef D_00615E60
#undef PPP_WORK
#undef VU0_RAND

