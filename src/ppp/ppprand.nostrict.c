/* The ppp random-value classes, -fno-strict-aliasing (docs/modules.md
 * "Session 50"): pppRand*Frame (Float, Char, Short, Int and the FV / IV / CV
 * / HCV vectors, each plain, Up and Down) draw a random number with VU0's R
 * register on the first frame, store it in the work area, then add amp * r
 * - amp (ppprand.c) to a value in the object; the pppSRand classes do the
 * same with their own generators (func_001892a8 ... func_0018a258, one per
 * class, drawing once or twice).  The FV and CV ones are written with
 * macros (H39_SRAND_FV, PPP_SRAND_CV), as in their old files
 * (hand/nostrict/ppp_rand.c, text_00180000_h39.c / h62.c).  Read from the
 * code, not proved by a boot. */
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/types/nostrict_text_00180000_h39.h"
#include "data/pieces/D_00362730.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_00364130.h"

/* pppRandFloatFrame (from hand/nostrict/ppp_rand.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef struct {
    s32 frame; /* +0x0 */
    s32 dst;   /* +0x4 */
    f32 amp;   /* +0x8 */
    u8 twice;  /* +0xC */
} PppRandKey;
typedef struct {
    u8 pad[0xB0];
    u64 flags; /* +0xB0 */
} PppSystem;
extern s32 D_0061621C;
extern PppSystem *D_00615E60;
extern f32 D_00575A00;
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

/* pppRandUpFloatFrame (from hand/nostrict/ppp_rand.c). */
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

/* pppRandDownFloatFrame (from hand/nostrict/ppp_rand.c). */
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

/* pppRandCharFrame (from hand/nostrict/ppp_rand.c). */
typedef struct {
    s32 frame;
    s32 dst;
    u8 amp;   /* +0x8 */
    u8 twice; /* +0x9 */
} PppRandCharKey;
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

/* pppRandUpCharFrame (from hand/nostrict/ppp_rand.c). */
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

/* pppRandDownCharFrame (from hand/nostrict/ppp_rand.c). */
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

/* pppRandShortFrame (from hand/nostrict/ppp_rand.c). */
typedef struct {
    s32 frame;
    s32 dst;
    u16 amp;  /* +0x8 */
    u8 twice; /* +0xA */
} PppRandShortKey;
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

/* pppRandUpShortFrame (from hand/nostrict/ppp_rand.c). */
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

/* pppRandDownShortFrame (from hand/nostrict/ppp_rand.c). */
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

/* pppRandIntFrame (from hand/nostrict/ppp_rand.c). */
typedef struct {
    s32 frame;
    s32 dst;
    u32 amp;  /* +0x8 */
    u8 twice; /* +0xC */
} PppRandIntKey;
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

/* pppRandUpIntFrame (from hand/nostrict/ppp_rand.c). */
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

/* pppRandDownIntFrame (from hand/nostrict/ppp_rand.c). */
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

/* pppRandFVFrame (from hand/nostrict/text_00180000_h62.c). */
typedef struct {
    s32 frame;  /* +0x0 */
    s32 dst;    /* +0x4 */
    f32 amp[3]; /* +0x8 */
    u8 twice;   /* +0x14 */
} PppRandFVKey;
f32 func_00187df0(f32, f32);
void pppRandFVFrame(PppObject *obj, PppRandFVKey *key, PppEntry *e) {
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
    v[0] += func_00187df0(key->amp[0], *w);
    v[1] += func_00187df0(key->amp[1], *w);
    v[2] += func_00187df0(key->amp[2], *w);
}

/* pppRandUpFVFrame (from hand/nostrict/text_00180000_h62.c). */
f32 func_00187f98(f32, f32);
void pppRandUpFVFrame(PppObject *obj, PppRandFVKey *key, PppEntry *e) {
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
    v[0] += func_00187f98(key->amp[0], *w);
    v[1] += func_00187f98(key->amp[1], *w);
    v[2] += func_00187f98(key->amp[2], *w);
}

/* pppRandDownFVFrame (from hand/nostrict/text_00180000_h62.c). */
f32 func_00188148(f32, f32);
void pppRandDownFVFrame(PppObject *obj, PppRandFVKey *key, PppEntry *e) {
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
    v[0] += func_00188148(key->amp[0], *w);
    v[1] += func_00188148(key->amp[1], *w);
    v[2] += func_00188148(key->amp[2], *w);
}

/* pppRandIVFrame (from hand/nostrict/text_00180000_h62.c). */
typedef struct {
    s32 frame;
    s32 dst;
    s32 amp[3]; /* +0x8 */
    u8 twice;   /* +0x14 */
} PppRandIVKey;
s32 func_001882f8(s32, f32);
void pppRandIVFrame(PppObject *obj, PppRandIVKey *key, PppEntry *e) {
    f32 *w;
    s32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r += vu0Rand();
    else
        r += r;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (s32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (s32 *) &D_00575A00;
    v[0] += func_001882f8(key->amp[0], *w);
    v[1] += func_001882f8(key->amp[1], *w);
    v[2] += func_001882f8(key->amp[2], *w);
}

/* pppRandUpIVFrame (from hand/nostrict/text_00180000_h62.c). */
s32 func_00188498(s32, f32);
void pppRandUpIVFrame(PppObject *obj, PppRandIVKey *key, PppEntry *e) {
    f32 *w;
    s32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r = (r + vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (s32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (s32 *) &D_00575A00;
    v[0] += func_00188498(key->amp[0], *w);
    v[1] += func_00188498(key->amp[1], *w);
    v[2] += func_00188498(key->amp[2], *w);
}

/* pppRandDownIVFrame (from hand/nostrict/text_00180000_h62.c). */
s32 func_00188640(s32, f32);
void pppRandDownIVFrame(PppObject *obj, PppRandIVKey *key, PppEntry *e) {
    f32 *w;
    s32 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    r = -r;
    if (key->twice)
        r = (r - vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (s32 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (s32 *) &D_00575A00;
    v[0] += func_00188640(key->amp[0], *w);
    v[1] += func_00188640(key->amp[1], *w);
    v[2] += func_00188640(key->amp[2], *w);
}

/* pppRandCVFrame (from hand/nostrict/text_00180000_h62.c). */
typedef struct {
    s32 frame;
    s32 dst;
    s8 amp[4]; /* +0x8 */
    u8 twice;  /* +0xC */
} PppRandCVKey;
s8 func_001887e8(s8, f32);
void pppRandCVFrame(PppObject *obj, PppRandCVKey *key, PppEntry *e) {
    f32 *w;
    u8 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r += vu0Rand();
    else
        r += r;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u8 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u8 *) &D_00575A00;
    v[0] += func_001887e8(key->amp[0], *w);
    v[1] += func_001887e8(key->amp[1], *w);
    v[2] += func_001887e8(key->amp[2], *w);
    v[3] += func_001887e8(key->amp[3], *w);
}

/* pppRandUpCVFrame (from hand/nostrict/text_00180000_h62.c). */
s8 func_001889b0(s8, f32);
void pppRandUpCVFrame(PppObject *obj, PppRandCVKey *key, PppEntry *e) {
    f32 *w;
    u8 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r = (r + vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u8 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u8 *) &D_00575A00;
    v[0] += func_001889b0(key->amp[0], *w);
    v[1] += func_001889b0(key->amp[1], *w);
    v[2] += func_001889b0(key->amp[2], *w);
    v[3] += func_001889b0(key->amp[3], *w);
}

/* pppRandDownCVFrame (from hand/nostrict/text_00180000_h62.c). */
s8 func_00188b78(s8, f32);
void pppRandDownCVFrame(PppObject *obj, PppRandCVKey *key, PppEntry *e) {
    f32 *w;
    u8 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    r = -r;
    if (key->twice)
        r = (r - vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u8 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u8 *) &D_00575A00;
    v[0] += func_00188b78(key->amp[0], *w);
    v[1] += func_00188b78(key->amp[1], *w);
    v[2] += func_00188b78(key->amp[2], *w);
    v[3] += func_00188b78(key->amp[3], *w);
}

/* pppRandHCVFrame (from hand/nostrict/text_00180000_h62.c). */
typedef struct {
    s32 frame;
    s32 dst;
    s16 amp[4]; /* +0x8 */
    u8 twice;   /* +0x10 */
} PppRandHCVKey;
s16 func_00188d40(s16, f32);
void pppRandHCVFrame(PppObject *obj, PppRandHCVKey *key, PppEntry *e) {
    f32 *w;
    u16 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r += vu0Rand();
    else
        r += r;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u16 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u16 *) &D_00575A00;
    v[0] += func_00188d40(key->amp[0], *w);
    v[1] += func_00188d40(key->amp[1], *w);
    v[2] += func_00188d40(key->amp[2], *w);
    v[3] += func_00188d40(key->amp[3], *w);
}

/* pppRandUpHCVFrame (from hand/nostrict/text_00180000_h62.c). */
s16 func_00188f08(s16, f32);
void pppRandUpHCVFrame(PppObject *obj, PppRandHCVKey *key, PppEntry *e) {
    f32 *w;
    u16 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    if (key->twice)
        r = (r + vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u16 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u16 *) &D_00575A00;
    v[0] += func_00188f08(key->amp[0], *w);
    v[1] += func_00188f08(key->amp[1], *w);
    v[2] += func_00188f08(key->amp[2], *w);
    v[3] += func_00188f08(key->amp[3], *w);
}

/* pppRandDownHCVFrame (from hand/nostrict/text_00180000_h62.c). */
s16 func_001890d0(s16, f32);
void pppRandDownHCVFrame(PppObject *obj, PppRandHCVKey *key, PppEntry *e) {
    f32 *w;
    u16 *v;
    f32 r;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame != obj->frame)
        return;
    r = vu0Rand();
    r = -r;
    if (key->twice)
        r = (r - vu0Rand()) * 0.5f;
    w = PPP_WORK(f32, obj, e, 0);
    *w = r;
    if (key->dst != -1)
        v = (u16 *) ((u8 *) obj + key->dst + 0xA0);
    else
        v = (u16 *) &D_00575A00;
    v[0] += func_001890d0(key->amp[0], *w);
    v[1] += func_001890d0(key->amp[1], *w);
    v[2] += func_001890d0(key->amp[2], *w);
    v[3] += func_001890d0(key->amp[3], *w);
}

/* func_001892a8 (from hand/nostrict/ppp_rand.c). */
f32 func_001892a8(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r += vu0Rand();
    else
        r += r;
    return r;
}

/* pppSRandFVFrame (from hand/nostrict/text_00180000_h39.c). */
typedef struct {
    u8 pad00[0x20];
    s32 dataoff;  /* +0x20 */
    s16 prio;     /* +0x24 */
    s16 n;        /* +0x26 */
    PppEntry ent[1]; /* +0x28 */
} H39Prog;
typedef struct {
    H39Prog *prog;          /* +0x0 */
    struct H39Inst *last;   /* +0x4 */
    s32 time;               /* +0x8 */
    u16 count;              /* +0xC */
} H39Slot2;
typedef struct H39Inst {
    struct H39Inst *next;   /* +0x0 */
    s32 unk04;
    H39Slot2 *slot;         /* +0x8 */
    s32 frame;              /* +0xC */
    u8 pad10[0x80];
    s32 unk90, unk94;
    u8 pad98[4];
    u8 unk9C, unk9D, unk9E;
} H39Inst;
typedef struct {
    u8 pad00[0x30];
    f32 col[4];             /* +0x30: colour scale */
    u8 pad40[0x34];
    H39Inst *head;          /* +0x74 */
    u8 pad78[8];
    H39Slot2 *slots;        /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;              /* +0xB0 */
} H39PSys;
typedef struct {
    s32 frame;
    s32 dst;    /* +0x4: work offset of the value, -1: scratch */
    f32 amp[3]; /* +0x8 */
    u8 twice;   /* +0x14 */
} H39RandFVKey;
f32 func_00189298(f32, f32);
#define H39_SRAND_FV(name, rnd, add)                                       \
    void name(PppObject *obj, H39RandFVKey *key, PppEntry *e) {            \
        f32 *w;                                                            \
        f32 *v;                                                            \
                                                                           \
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))    \
            return;                                                        \
        if (obj->frame == 0) {                                             \
            w = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);               \
            w[0] = rnd(key->twice);                                        \
            w[1] = rnd(key->twice);                                        \
            w[2] = rnd(key->twice);                                        \
        } else {                                                           \
            if (key->frame != obj->frame)                                  \
                return;                                                    \
            w = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);               \
        }                                                                  \
        if (key->dst != -1)                                                \
            v = (f32 *) ((u8 *) obj + key->dst + 0xA0);                    \
        else                                                               \
            v = &D_00575A00;                                               \
        v[0] += add(key->amp[0], w[0]);                                    \
        v[1] += add(key->amp[1], w[1]);                                    \
        v[2] += add(key->amp[2], w[2]);                                    \
    }
#define D_00615E60 ((H39PSys *) D_00615E60)
H39_SRAND_FV(pppSRandFVFrame, func_001892a8, func_00189298)
#undef D_00615E60
#undef H39_SRAND_FV

/* func_00189470 (from hand/nostrict/ppp_rand.c). */
f32 func_00189470(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r = (r + vu0Rand()) * 0.5f;
    return r;
}

/* pppSRandUpFVFrame (from hand/nostrict/text_00180000_h39.c). */
f32 func_00189468(f32, f32);
#define H39_SRAND_FV(name, rnd, add)                                       \
    void name(PppObject *obj, H39RandFVKey *key, PppEntry *e) {            \
        f32 *w;                                                            \
        f32 *v;                                                            \
                                                                           \
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))    \
            return;                                                        \
        if (obj->frame == 0) {                                             \
            w = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);               \
            w[0] = rnd(key->twice);                                        \
            w[1] = rnd(key->twice);                                        \
            w[2] = rnd(key->twice);                                        \
        } else {                                                           \
            if (key->frame != obj->frame)                                  \
                return;                                                    \
            w = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);               \
        }                                                                  \
        if (key->dst != -1)                                                \
            v = (f32 *) ((u8 *) obj + key->dst + 0xA0);                    \
        else                                                               \
            v = &D_00575A00;                                               \
        v[0] += add(key->amp[0], w[0]);                                    \
        v[1] += add(key->amp[1], w[1]);                                    \
        v[2] += add(key->amp[2], w[2]);                                    \
    }
#define D_00615E60 ((H39PSys *) D_00615E60)
H39_SRAND_FV(pppSRandUpFVFrame, func_00189470, func_00189468)
#undef D_00615E60
#undef H39_SRAND_FV

/* func_00189648 (from hand/nostrict/ppp_rand.c). */
f32 func_00189648(u8 twice) {
    f32 r;

    r = vu0Rand();
    r = -r;
    if (twice)
        r = (r - vu0Rand()) * 0.5f;
    return r;
}

/* pppSRandDownFVFrame (from hand/nostrict/text_00180000_h39.c). */
f32 func_00189640(f32, f32);
#define H39_SRAND_FV(name, rnd, add)                                       \
    void name(PppObject *obj, H39RandFVKey *key, PppEntry *e) {            \
        f32 *w;                                                            \
        f32 *v;                                                            \
                                                                           \
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))    \
            return;                                                        \
        if (obj->frame == 0) {                                             \
            w = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);               \
            w[0] = rnd(key->twice);                                        \
            w[1] = rnd(key->twice);                                        \
            w[2] = rnd(key->twice);                                        \
        } else {                                                           \
            if (key->frame != obj->frame)                                  \
                return;                                                    \
            w = (f32 *) ((u8 *) obj + e->offsets[0] + 0xA0);               \
        }                                                                  \
        if (key->dst != -1)                                                \
            v = (f32 *) ((u8 *) obj + key->dst + 0xA0);                    \
        else                                                               \
            v = &D_00575A00;                                               \
        v[0] += add(key->amp[0], w[0]);                                    \
        v[1] += add(key->amp[1], w[1]);                                    \
        v[2] += add(key->amp[2], w[2]);                                    \
    }
#define D_00615E60 ((H39PSys *) D_00615E60)
H39_SRAND_FV(pppSRandDownFVFrame, func_00189648, func_00189640)
#undef D_00615E60
#undef H39_SRAND_FV

/* func_00189848 (from hand/nostrict/ppp_rand.c). */
f32 func_00189848(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r += vu0Rand();
    else
        r += r;
    return r;
}

/* pppSRandCVFrame (from hand/nostrict/ppp_rand.c). */
typedef struct {
    s32 frame;
    s32 dst;
    s8 amp[4];  /* +0x8 */
    u8 twice;   /* +0xC */
} PppSRandCVKey;
s8 func_00189818(s8, f32);
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
#undef PPP_SRAND_CV

/* func_00189a40 (from hand/nostrict/ppp_rand.c). */
f32 func_00189a40(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r = (r + vu0Rand()) * 0.5f;
    return r;
}

/* pppSRandUpCVFrame (from hand/nostrict/ppp_rand.c). */
s8 func_00189a18(s8, f32);
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
PPP_SRAND_CV(pppSRandUpCVFrame, PppSRandCVKey, u8, func_00189a40, func_00189a18)
#undef PPP_SRAND_CV

/* func_00189c48 (from hand/nostrict/ppp_rand.c). */
f32 func_00189c48(u8 twice) {
    f32 r;

    r = vu0Rand();
    r = -r;
    if (twice)
        r = (r - vu0Rand()) * 0.5f;
    return r;
}

/* pppSRandDownCVFrame (from hand/nostrict/ppp_rand.c). */
s8 func_00189c20(s8, f32);
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
PPP_SRAND_CV(pppSRandDownCVFrame, PppSRandCVKey, u8, func_00189c48, func_00189c20)
#undef PPP_SRAND_CV

/* func_00189e58 (from hand/nostrict/ppp_rand.c). */
f32 func_00189e58(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r += vu0Rand();
    else
        r += r;
    return r;
}

/* pppSRandHCVFrame (from hand/nostrict/ppp_rand.c). */
typedef struct {
    s32 frame;
    s32 dst;
    s16 amp[4]; /* +0x8 */
    u8 twice;   /* +0x10 */
} PppSRandHCVKey;
s8 func_00189e28(s16, f32);
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
PPP_SRAND_CV(pppSRandHCVFrame, PppSRandHCVKey, u16, func_00189e58, func_00189e28)
#undef PPP_SRAND_CV

/* func_0018a050 (from hand/nostrict/ppp_rand.c). */
f32 func_0018a050(u8 twice) {
    f32 r;

    r = vu0Rand();
    if (twice)
        r = (r + vu0Rand()) * 0.5f;
    return r;
}

/* pppSRandUpHCVFrame (from hand/nostrict/ppp_rand.c). */
s8 func_0018a028(s16, f32);
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
PPP_SRAND_CV(pppSRandUpHCVFrame, PppSRandHCVKey, u16, func_0018a050, func_0018a028)
#undef PPP_SRAND_CV

/* func_0018a258 (from hand/nostrict/ppp_rand.c). */
f32 func_0018a258(u8 twice) {
    f32 r;

    r = vu0Rand();
    r = -r;
    if (twice)
        r = (r - vu0Rand()) * 0.5f;
    return r;
}

/* pppSRandDownHCVFrame (from hand/nostrict/ppp_rand.c). */
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
PPP_SRAND_CV(pppSRandDownHCVFrame, PppSRandHCVKey, u16, func_0018a258, func_0018a230)
#undef PPP_SRAND_CV

