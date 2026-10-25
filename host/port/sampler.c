/* The sampler state a port draws a texture with: CLAMP's wrap modes and TEX1's filter as a GPU sampler
 * plus the shader's steps (include/platform/sampler.h, docs/renderer-spec.md 4.13 "Session 120"),
 * checked by tests/host/sampler_test.c against the GS's rule and host/null/gsmem.c's sprite.  Not part
 * of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/sampler.h"

static void axis(KH1SamplerAxis *a, u32 wm, u32 lo, u32 hi, u32 n) {
    a->wm = wm;
    a->n = n;
    a->lo = lo;
    a->hi = hi;
    a->past = 0;
    a->shader = KH1_SHADER_NONE;
    switch (wm) {
    case KH1_WM_REPEAT: a->addr = KH1_ADDR_REPEAT; break;
    case KH1_WM_CLAMP: a->addr = KH1_ADDR_CLAMP; break;
    case KH1_WM_REGION_CLAMP:
        a->addr = KH1_ADDR_CLAMP;
        if (hi > n - 1) { a->hi = hi = n - 1; a->past = 1; }
        if (lo > hi) a->lo = lo = hi;
        if (lo || hi < n - 1) a->shader = KH1_SHADER_CLAMP;
        break;
    default: /* REGION_REPEAT: a mask that keeps every bit of n - 1 and no fix is a repeat */
        a->addr = KH1_ADDR_REPEAT;
        if ((lo & (n - 1)) != n - 1 || hi & (n - 1)) a->shader = KH1_SHADER_TAPS;
        break;
    }
}

void kh1_sampler_of(u32 clamp_lo, u32 clamp_hi, u32 tex1_lo, u32 tex1_hi, u32 tw, u32 th, KH1Sampler *s) {
    u32 mmag = tex1_lo >> 5 & 1, mmin = tex1_lo >> 6 & 7;
    s32 k = (s32)(tex1_hi << 20) >> 20; /* K, 12 bits signed */
    axis(&s->u, clamp_lo & 3, clamp_lo >> 4 & 0x3FF, clamp_lo >> 14 & 0x3FF, 1u << tw);
    axis(&s->v, clamp_lo >> 2 & 3, (clamp_lo >> 24 | clamp_hi << 8) & 0x3FF, clamp_hi >> 2 & 0x3FF, 1u << th);
    mmin = mmin >= 4 ? 1 : mmin >= 2 ? 0 : mmin; /* one level: a mipmap form is its base filter */
    if (tex1_lo & 1) s->linear = k <= 0 ? mmag : mmin; /* LCM 1: the LOD is K */
    else s->linear = mmag;
    s->split = !(tex1_lo & 1) && mmag != mmin;
    s->mips = (tex1_lo >> 2 & 7) != 0;
}

/* the GS's rule for one tap's texel */
static u32 gs_texel(const KH1SamplerAxis *a, s32 c) {
    switch (a->wm) {
    case KH1_WM_REPEAT: return (u32)c & (a->n - 1);
    case KH1_WM_CLAMP: return c < 0 ? 0 : c > a->n - 1 ? a->n - 1 : (u32)c;
    case KH1_WM_REGION_CLAMP: return c < (s32)a->lo ? a->lo : c > (s32)a->hi ? a->hi : (u32)c;
    }
    return ((u32)c & a->lo) | a->hi;
}

/* the GPU's address mode on one tap's texel, or the shader's own tap */
static u32 port_texel(const KH1SamplerAxis *a, s32 c) {
    if (a->shader == KH1_SHADER_TAPS) return (((u32)c & a->lo) | a->hi) & (a->n - 1);
    if (a->addr == KH1_ADDR_REPEAT) return (u32)c & (a->n - 1);
    return c < 0 ? 0 : c > a->n - 1 ? a->n - 1 : (u32)c;
}

/* the shader's coordinate clamp (1/16 texels): MIN + 0.5 .. MAX + 0.5 */
static s32 port_coord(const KH1SamplerAxis *a, s32 c) {
    if (a->shader != KH1_SHADER_CLAMP) return c;
    if (c < a->lo * 16 + 8) return a->lo * 16 + 8;
    if (c > a->hi * 16 + 8) return a->hi * 16 + 8;
    return c;
}

static u32 blend(const u32 t[4], u32 fu, u32 fv) {
    u32 i, out = 0, w[4];
    w[0] = (16 - fu) * (16 - fv);
    w[1] = fu * (16 - fv);
    w[2] = (16 - fu) * fv;
    w[3] = fu * fv;
    for (i = 0; i < 32; i += 8)
        out |= ((t[0] >> i & 0xFF) * w[0] + (t[1] >> i & 0xFF) * w[1] + (t[2] >> i & 0xFF) * w[2] +
                (t[3] >> i & 0xFF) * w[3] + 128) >> 8 << i;
    return out;
}

static u32 sample(const KH1Sampler *s, KH1SamplerFetch f, void *ctx, s32 u, s32 v, int port) {
    u32 (*tx)(const KH1SamplerAxis *, s32) = port ? port_texel : gs_texel;
    u32 t[4];
    s32 u0, v0;
    if (port) {
        u = port_coord(&s->u, u);
        v = port_coord(&s->v, v);
    }
    if (!s->linear) return f(tx(&s->u, u >> 4), tx(&s->v, v >> 4), ctx);
    u0 = (u - 8) >> 4;
    v0 = (v - 8) >> 4;
    t[0] = f(tx(&s->u, u0), tx(&s->v, v0), ctx);
    t[1] = f(tx(&s->u, u0 + 1), tx(&s->v, v0), ctx);
    t[2] = f(tx(&s->u, u0), tx(&s->v, v0 + 1), ctx);
    t[3] = f(tx(&s->u, u0 + 1), tx(&s->v, v0 + 1), ctx);
    return blend(t, (u32)(u - 8) & 15, (u32)(v - 8) & 15);
}

u32 kh1_sampler_gs(const KH1Sampler *s, KH1SamplerFetch f, void *ctx, s32 u, s32 v) { return sample(s, f, ctx, u, v, 0); }
u32 kh1_sampler_port(const KH1Sampler *s, KH1SamplerFetch f, void *ctx, s32 u, s32 v) { return sample(s, f, ctx, u, v, 1); }
