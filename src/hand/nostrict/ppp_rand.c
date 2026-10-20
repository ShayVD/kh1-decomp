/* ppp random-value classes (pppRand*Frame): on the first frame they draw
 * a random number with VU0's R register, store it in the work area, then
 * add amp * r - amp to a value in the object. */
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

/* The keys: the frame they apply at, the work offset of the value to change
 * (-1: a scratch float), the amplitude and whether to draw twice. */
typedef struct {
    s32 frame; /* +0x0 */
    s32 dst;   /* +0x4 */
    f32 amp;   /* +0x8 */
    u8 twice;  /* +0xC */
} PppRandKey;

typedef struct {
    s32 frame;
    s32 dst;
    u8 amp;   /* +0x8 */
    u8 twice; /* +0x9 */
} PppRandCharKey;

typedef struct {
    s32 frame;
    s32 dst;
    u16 amp;  /* +0x8 */
    u8 twice; /* +0xA */
} PppRandShortKey;

typedef struct {
    s32 frame;
    s32 dst;
    u32 amp;  /* +0x8 */
    u8 twice; /* +0xC */
} PppRandIntKey;

typedef struct {
    u8 pad[0xB0];
    u64 flags; /* +0xB0 */
} PppSystem;

extern s32 D_0061621C;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
extern f32 D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */

/* A float in [0, 1) from VU0's random register. */
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

void pppRandFloatFrame(PppObject *obj, PppRandKey *key, PppEntry *e) {
    f32 *w;
    f32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r += vu0Rand();
        else
            r += r;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (f32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (f32 *) &D_00575A00;
    *v += key->amp * *w - key->amp;
}

void pppRandUpFloatFrame(PppObject *obj, PppRandKey *key, PppEntry *e) {
    f32 *w;
    f32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r = (r + vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (f32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (f32 *) &D_00575A00;
    *v += key->amp * *w;
}

void pppRandDownFloatFrame(PppObject *obj, PppRandKey *key, PppEntry *e) {
    f32 *w;
    f32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        r = -r;
        if (key->twice)
            r = (r - vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (f32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (f32 *) &D_00575A00;
    *v += key->amp * *w;
}

void pppRandCharFrame(PppObject *obj, PppRandCharKey *key, PppEntry *e) {
    f32 *w;
    u8 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r += vu0Rand();
        else
            r += r;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (u8 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u8 *) &D_00575A00;
    *v += (s32) (key->amp * *w - key->amp);
}

void pppRandUpCharFrame(PppObject *obj, PppRandCharKey *key, PppEntry *e) {
    f32 *w;
    u8 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r = (r + vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (u8 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u8 *) &D_00575A00;
    *v += (s32) (key->amp * *w);
}

void pppRandDownCharFrame(PppObject *obj, PppRandCharKey *key, PppEntry *e) {
    f32 *w;
    u8 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        r = -r;
        if (key->twice)
            r = (r - vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (u8 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u8 *) &D_00575A00;
    *v += (s32) (key->amp * *w);
}

void pppRandShortFrame(PppObject *obj, PppRandShortKey *key, PppEntry *e) {
    f32 *w;
    u16 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r += vu0Rand();
        else
            r += r;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (u16 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u16 *) &D_00575A00;
    *v += (s32) (key->amp * *w - key->amp);
}

void pppRandUpShortFrame(PppObject *obj, PppRandShortKey *key, PppEntry *e) {
    f32 *w;
    u16 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r = (r + vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (u16 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u16 *) &D_00575A00;
    *v += (s32) (key->amp * *w);
}

void pppRandDownShortFrame(PppObject *obj, PppRandShortKey *key, PppEntry *e) {
    f32 *w;
    u16 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        r = -r;
        if (key->twice)
            r = (r - vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (u16 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u16 *) &D_00575A00;
    *v += (s32) (key->amp * *w);
}

void pppRandIntFrame(PppObject *obj, PppRandIntKey *key, PppEntry *e) {
    f32 *w;
    s32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r += vu0Rand();
        else
            r += r;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (s32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (s32 *) &D_00575A00;
    *v += (s32) (key->amp * *w - key->amp);
}

void pppRandUpIntFrame(PppObject *obj, PppRandIntKey *key, PppEntry *e) {
    f32 *w;
    s32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        if (key->twice)
            r = (r + vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (s32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (s32 *) &D_00575A00;
    *v += (s32) (key->amp * *w);
}

void pppRandDownIntFrame(PppObject *obj, PppRandIntKey *key, PppEntry *e) {
    f32 *w;
    s32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (obj->frame == 0) {
        r = vu0Rand();
        r = -r;
        if (key->twice)
            r = (r - vu0Rand()) * 0.5f;
        w = PPP_WORK(f32, obj, e, 0);
        *w = r;
    } else {
        if (key->frame != obj->frame)
            return;
        w = PPP_WORK(f32, obj, e, 0);
    }
    if (key->dst != -1)
        v = (s32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (s32 *) &D_00575A00;
    *v += (s32) (key->amp * *w);
}

/* The same three draws as functions (used by the vector classes). */

f32 func_001892a8(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r += vu0Rand();
    else
        r += r;
    return r;
}

f32 func_00189470(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r = (r + vu0Rand()) * 0.5f;
    return r;
}

f32 func_00189648(u8 twice) {
    f32 r;

    r = vu0Rand();
    r = -r;
    if (twice)
        r = (r - vu0Rand()) * 0.5f;
    return r;
}

f32 func_00189848(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r += vu0Rand();
    else
        r += r;
    return r;
}

f32 func_00189a40(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r = (r + vu0Rand()) * 0.5f;
    return r;
}

f32 func_00189c48(u8 twice) {
    f32 r;

    r = vu0Rand();
    r = -r;
    if (twice)
        r = (r - vu0Rand()) * 0.5f;
    return r;
}

f32 func_00189e58(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r += vu0Rand();
    else
        r += r;
    return r;
}

f32 func_0018a050(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r = (r + vu0Rand()) * 0.5f;
    return r;
}

f32 func_0018a258(u8 twice) {
    f32 r;

    r = vu0Rand();
    r = -r;
    if (twice)
        r = (r - vu0Rand()) * 0.5f;
    return r;
}

/* The vector classes with char / short components (pppSRand*CVFrame,
 * pppSRand*HCVFrame): on their keyframe they draw one random number per
 * component into the work area, then add the scaled amplitude to the four
 * values in the object. They follow the draw functions above (the callees
 * must be defined earlier for these to match). */

typedef struct {
    s32 frame;
    s32 dst;
    s8 amp[4];  /* +0x8 */
    u8 twice;   /* +0xC */
} PppSRandCVKey;

typedef struct {
    s32 frame;
    s32 dst;
    s16 amp[4]; /* +0x8 */
    u8 twice;   /* +0x10 */
} PppSRandHCVKey;

s8 func_00189818(s8, f32);
s8 func_00189a18(s8, f32);
s8 func_00189c20(s8, f32);
s8 func_00189e28(s16, f32);
s8 func_0018a028(s16, f32);
s8 func_0018a230(s16, f32);

#define PPP_SRAND_CV(name, keyT, valT, rnd, add)                           \
    void name(PppObject *obj, keyT *key, PppEntry *e) {                    \
        f32 *w;                                                            \
        valT *v;                                                           \
                                                                           \
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))      \
            return;                                                        \
        if (key->frame != obj->frame)                                      \
            return;                                                        \
        w = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);                   \
        w[0] = rnd(key->twice);                                            \
        w[1] = rnd(key->twice);                                            \
        w[2] = rnd(key->twice);                                            \
        w[3] = rnd(key->twice);                                            \
        v = (valT *) &D_00575A00;                                          \
        if (key->dst != -1)                                                \
            v = (valT *) ((u8 *) obj + key->dst + 0xA0);                   \
        v[0] += add(key->amp[0], w[0]);                                    \
        v[1] += add(key->amp[1], w[1]);                                    \
        v[2] += add(key->amp[2], w[2]);                                    \
        v[3] += add(key->amp[3], w[3]);                                    \
    }

PPP_SRAND_CV(pppSRandCVFrame, PppSRandCVKey, u8, func_00189848, func_00189818)
PPP_SRAND_CV(pppSRandUpCVFrame, PppSRandCVKey, u8, func_00189a40, func_00189a18)
PPP_SRAND_CV(pppSRandDownCVFrame, PppSRandCVKey, u8, func_00189c48, func_00189c20)
PPP_SRAND_CV(pppSRandHCVFrame, PppSRandHCVKey, u16, func_00189e58, func_00189e28)
PPP_SRAND_CV(pppSRandUpHCVFrame, PppSRandHCVKey, u16, func_0018a050, func_0018a028)
PPP_SRAND_CV(pppSRandDownHCVFrame, PppSRandHCVKey, u16, func_0018a258, func_0018a230)
