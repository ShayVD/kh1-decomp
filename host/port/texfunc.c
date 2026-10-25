/* The texture function a port's fragment shader runs: TEX0's TFX / TCC with the vertex colour on the
 * GS's 0x80 scale (include/platform/texfunc.h, docs/renderer-spec.md 4.13 "Session 120"), checked by
 * tests/host/texfunc_test.c against host/null/gsmem.c's sprite (MODULATE, DECAL) and the GS manual's
 * formulas (HIGHLIGHT, HIGHLIGHT2).  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/texfunc.h"

static u32 min255(u32 v) { return v > 255 ? 255 : v; }

u32 kh1_texfunc(u32 tfx, u32 tcc, u32 ct, u32 cv) {
    u32 i, c, t, out = 0, av = cv >> 24, at = ct >> 24, a;
    for (i = 0; i < 24; i += 8) {
        t = ct >> i & 0xFF;
        c = cv >> i & 0xFF;
        switch (tfx & 3) {
        case KH1_TFX_MODULATE: c = min255(t * c >> 7); break;
        case KH1_TFX_DECAL: c = t; break;
        default: c = min255((t * c >> 7) + av); break; /* HIGHLIGHT, HIGHLIGHT2 */
        }
        out |= c << i;
    }
    if (!tcc) a = av;
    else switch (tfx & 3) {
    case KH1_TFX_MODULATE: a = min255(at * av >> 7); break;
    case KH1_TFX_HIGHLIGHT: a = min255(at + av); break;
    default: a = at; break; /* DECAL, HIGHLIGHT2 */
    }
    return out | a << 24;
}

u32 kh1_texfunc_tex0(u32 tex0_hi, u32 ct, u32 cv) {
    return kh1_texfunc(tex0_hi >> 3 & 3, tex0_hi >> 2 & 1, ct, cv);
}

/* the shader's UNORM inputs and its 8-bit output */
static float unorm(u32 v) { return (float)v / 255.0f; }
static u32 back8(float f) { return f <= 0.0f ? 0 : f >= 1.0f ? 255 : (u32)(f * 255.0f + 0.5f); }
static float fmin1(float f) { return f > 1.0f ? 1.0f : f; }

u32 kh1_texfunc_shader(u32 tfx, u32 tcc, u32 ct, u32 cv, int exact) {
    float t[4], c[4], o[4];
    u32 i, out = 0;
    for (i = 0; i < 4; i++) {
        t[i] = unorm(ct >> i * 8 & 0xFF);
        c[i] = unorm(cv >> i * 8 & 0xFF);
    }
    if (exact) { /* the 8-bit values back, then the GS's integer steps */
        u32 ti = 0, ci = 0;
        for (i = 0; i < 4; i++) {
            ti |= back8(t[i]) << i * 8;
            ci |= back8(c[i]) << i * 8;
        }
        return kh1_texfunc(tfx, tcc, ti, ci);
    }
    /* the plain float form: 0x80 is 1.0, so a product of two scales by 255 / 128 */
    for (i = 0; i < 3; i++)
        o[i] = (tfx & 3) == KH1_TFX_DECAL ? t[i] : fmin1(t[i] * c[i] * (255.0f / 128.0f) + ((tfx & 3) >= KH1_TFX_HIGHLIGHT ? c[3] : 0.0f));
    o[3] = !tcc ? c[3] : (tfx & 3) == KH1_TFX_MODULATE ? fmin1(t[3] * c[3] * (255.0f / 128.0f))
                       : (tfx & 3) == KH1_TFX_HIGHLIGHT ? fmin1(t[3] + c[3]) : t[3];
    for (i = 0; i < 4; i++) out |= back8(o[i]) << i * 8;
    return out;
}
