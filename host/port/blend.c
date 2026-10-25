/* The blend state a port's GPU runs for the GS's ALPHA / FBMSK / COLCLAMP (include/platform/blend.h,
 * docs/renderer-spec.md 4.13 "Session 121"), checked by tests/host/blend_test.c against host/null/
 * gsmem.c's sprite and kh1_blend_gs for every A / B / C / D.  Not part of the PS2 build (it lives
 * outside src/). */
#include "common.h"
#include "platform/blend.h"

enum { CT32 = 0x00, CT24 = 0x01, CT16 = 0x02, CT16S = 0x0A }; /* the frame PSMs (gsmem.h's KH1_PSM*) */

static s32 clamp255(s32 v) { return v < 0 ? 0 : v > 255 ? 255 : v; }
/* (x * c) >> 7 as the GS shifts it: floored, also when negative */
static s32 shr7(s32 m) { return m >= 0 ? m >> 7 : -((-m + 127) >> 7); }
static s32 sel(u32 f, s32 cs, s32 cd) { return f == 0 ? cs : f == 1 ? cd : 0; }

u32 kh1_blend_gs(u32 alpha_lo, u32 alpha_hi, u32 cs, u32 cd, u32 frame_psm) {
    u32 i, out = cs & 0xFF000000u, csel = alpha_lo >> 4 & 3;
    s32 as = cs >> 24, ad = frame_psm == CT24 ? 0x80 : (s32)(cd >> 24), c, s, d;
    c = csel == 0 ? as : csel == 1 ? ad : (s32)(alpha_hi & 0xFF);
    for (i = 0; i < 24; i += 8) {
        s = cs >> i & 0xFF;
        d = cd >> i & 0xFF;
        out |= (u32)clamp255(shr7((sel(alpha_lo & 3, s, d) - sel(alpha_lo >> 2 & 3, s, d)) * c) + sel(alpha_lo >> 6 & 3, s, d)) << i;
    }
    return out;
}

u32 kh1_blend_store_alpha(u32 a) { return a >= 0x80 ? 255 : (a * 255 + 64) / 128; }
u32 kh1_blend_load_alpha(u32 a8) { return (a8 * 128 + 127) / 255; }

/* the colour write mask from FBMSK: a channel whose bits are all masked is off, one with some masked
 * is not a GPU mask (-1) */
static int channel_mask(u32 fbmsk, u32 psm) {
    static const u32 ct32[4] = { 0xFF, 0xFF00, 0xFF0000, 0xFF000000u };
    static const u32 ct16[4] = { 0xF8, 0xF800, 0xF80000, 0x80000000u }; /* RGBA 5551's bits */
    const u32 *bits = psm == CT16 || psm == CT16S ? ct16 : ct32;
    int i, m = 0;
    for (i = 0; i < 4; i++) {
        u32 k = fbmsk & bits[i];
        if (i == 3 && psm == CT24) continue; /* no alpha stored */
        if (!k) m |= 1 << i;
        else if (k != bits[i]) return -1;
    }
    return m;
}

/* a coefficient k = a x c + d (a in -1 .. 1, d in 0 .. 1) on one side of the blend */
void kh1_blend_state(u32 alpha_lo, u32 alpha_hi, u32 abe, u32 frame_psm, u32 fbmsk, KH1BlendState *out) {
    u32 A = alpha_lo & 3, B = alpha_lo >> 2 & 3, C = alpha_lo >> 4 & 3, D = alpha_lo >> 6 & 3, fix = alpha_hi & 0xFF;
    s32 sa = (A == 0) - (B == 0), sd = D == 0, da = (A == 1) - (B == 1), dd = D == 1, n = -1, ks, kd, sgn_s, sgn_d;
    int m = channel_mask(fbmsk, frame_psm), cconst;
    out->enable = 0;
    out->eq = KH1_BEQ_ADD;
    out->fs = KH1_BF_ONE;
    out->fd = KH1_BF_ZERO;
    out->pre_a = 0;
    out->pre_d = 1;
    out->pre_floor = 0;
    out->csel = C > 2 ? 2 : C;
    out->fix = C > 2 ? 0 : fix; /* C 3 is reserved: taken as FIX 0, as the model's sel */
    out->abcd = alpha_lo & 0xFF;
    out->psm = frame_psm;
    out->kind = KH1_BLEND_EXACT;
    out->mask = m < 0 ? 0xF : m;
    if (m < 0) out->kind = KH1_BLEND_FETCH;
    if (!abe) return;
    /* C as a number where the frame or FIX fixes it: FIX 0 / 0x80, or Ad on a CT24 frame (0x80) */
    if (out->csel == 2 && (out->fix == 0 || out->fix == 0x80)) n = out->fix >> 7;
    if (out->csel == 1 && frame_psm == CT24) n = 1;
    cconst = n >= 0;
    if (cconst) { sd += sa * n; sa = 0; dd += da * n; da = 0; }
    out->enable = 1;
    if (!cconst && out->csel == 1 && sa) { out->kind = KH1_BLEND_FETCH; return; } /* Cs x Ad: the shader has no Ad */
    /* the signs with 0 < c <= 1 */
    ks = sa ? (sd ? 1 : sa) : sd;      /* 1 - c and 1 + c are positive, c and -c take sa's sign */
    kd = da ? (dd ? 1 : da) : dd;
    sgn_s = ks > 0 ? 1 : ks < 0 ? -1 : 0;
    sgn_d = kd > 0 ? 1 : kd < 0 ? -1 : 0;
    if (sgn_s <= 0 && sgn_d <= 0) { /* nothing above 0: the result is black */
        out->pre_a = 0;
        out->pre_d = 0;
        out->fd = KH1_BF_ZERO;
        return;
    }
    /* the destination's factor |kd| */
    if (!da) out->fd = dd == 0 ? KH1_BF_ZERO : dd == 1 || dd == -1 ? KH1_BF_ONE : 0xFF;
    else if (dd == 0) out->fd = out->csel == 0 ? KH1_BF_SRC_ALPHA : out->csel == 1 ? KH1_BF_DST_ALPHA : 0xFF;
    else if (da < 0) out->fd = out->csel == 0 ? KH1_BF_ONE_MINUS_SRC_ALPHA : out->csel == 1 ? KH1_BF_ONE_MINUS_DST_ALPHA : 0xFF;
    else out->fd = 0xFF; /* 1 + c */
    if (out->fd == 0xFF) { out->fd = KH1_BF_ZERO; out->kind = KH1_BLEND_FETCH; return; }
    /* the equation, and the source's coefficient with the sign it is applied with */
    if (sgn_s < 0) { out->eq = KH1_BEQ_REVERSE_SUBTRACT; out->pre_a = -sa; out->pre_d = -sd; }
    else { out->eq = sgn_d < 0 ? KH1_BEQ_SUBTRACT : KH1_BEQ_ADD; out->pre_a = sa; out->pre_d = sd; }
    /* exact when the destination's factor is 0 or 1: the shader then floors the product as the GS does
     * (a coefficient applied negated is a ceil) */
    if (!da) {
        out->pre_floor = !out->pre_a ? 0 : out->eq == KH1_BEQ_REVERSE_SUBTRACT ? 2 : 1;
        if (out->eq == KH1_BEQ_ADD && out->fd == KH1_BF_ZERO && !out->pre_a && out->pre_d == 1) out->enable = 0; /* Cs */
    } else
        out->kind = KH1_BLEND_LE80;
    /* a source above 0xFF clamps before a subtract: 2 x Cs - Cd, Cs + Cs x c - Cd x c */
    if (out->eq == KH1_BEQ_SUBTRACT && (out->pre_d > 1 || (out->pre_a > 0 && out->pre_d > 0))) out->kind = KH1_BLEND_FETCH;
    if (m < 0) out->kind = KH1_BLEND_FETCH;
}

static float factor(u32 f, u32 sa8, u32 da8) {
    switch (f) {
    case KH1_BF_ZERO: return 0.0f;
    case KH1_BF_ONE: return 1.0f;
    case KH1_BF_SRC_ALPHA: return sa8 / 255.0f;
    case KH1_BF_ONE_MINUS_SRC_ALPHA: return 1.0f - sa8 / 255.0f;
    case KH1_BF_DST_ALPHA: return da8 / 255.0f;
    }
    return 1.0f - da8 / 255.0f;
}

u32 kh1_blend_gpu(const KH1BlendState *st, u32 cs, u32 dst) {
    u32 i, out = 0, as = cs >> 24, sa8 = kh1_blend_store_alpha(as), da8 = dst >> 24, c, mask;
    s32 s, p;
    float r, f;
    if (st->kind == KH1_BLEND_FETCH && st->enable) { /* the shader reads the frame: the GS's formula on what it holds */
        u32 cd = (dst & 0xFFFFFF) | kh1_blend_load_alpha(da8) << 24;
        out = (kh1_blend_gs(st->abcd, st->fix, cs, cd, st->psm) & 0xFFFFFF) | sa8 << 24;
    } else {
        c = st->csel == 0 ? as : st->csel == 1 ? kh1_blend_load_alpha(da8) : st->fix;
        f = factor(st->fd, sa8, da8);
        for (i = 0; i < 24; i += 8) {
            s = cs >> i & 0xFF;
            if (!st->enable) { out |= (u32)s << i; continue; }
            /* the shader's source, written to 8 bits */
            p = st->pre_a * s * (s32)c;
            if (st->pre_floor == 1) s = clamp255(shr7(p) + st->pre_d * s);
            else if (st->pre_floor == 2) s = clamp255(-shr7(-p) + st->pre_d * s);
            else {
                r = p / 128.0f + st->pre_d * s;
                s = r <= 0.0f ? 0 : r >= 255.0f ? 255 : (s32)(r + 0.5f);
            }
            /* the fixed-function blend, rounded to 8 bits */
            r = (float)(dst >> i & 0xFF) * f;
            r = st->eq == KH1_BEQ_ADD ? s + r : st->eq == KH1_BEQ_SUBTRACT ? s - r : r - s;
            out |= (u32)(r <= 0.0f ? 0 : r >= 255.0f ? 255 : (s32)(r + 0.5f)) << i;
        }
        out |= sa8 << 24; /* the alpha the shader writes (ONE, ZERO) */
    }
    mask = 0;
    for (i = 0; i < 4; i++)
        if (st->mask >> i & 1) mask |= 0xFFu << i * 8;
    return (out & mask) | (dst & ~mask);
}
