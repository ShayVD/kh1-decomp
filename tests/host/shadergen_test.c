/* The shaders as Cg source (host/port/shadergen.c, renderer-spec 4.13 "Session 127", vita-port-plan 5.1bo):
 * every generated shader read back by the CPU interpreter (kh1_shader_run, the same table of statement forms)
 * and run against the models it was written from, with made-up values (no game data): tests/selftest.sh
 * builds it with gcc -m32 when that works.
 *
 *   parse     every fragment variant of a sweep over KH1ShaderKey and the 7 vertex variants: each body line
 *             one of the forms, every form used
 *   texfunc   TFX 0-3 x TCC over a grid of texel and vertex colours: the shader's colour before the blend is
 *             kh1_texfunc's (texfunc.h: the GS's integer steps, so kh1_texfunc_shader's exact form)
 *   fog       C, F and FOGCOL grids: kh1_fog_gs
 *   blend     every ALPHA form blend.h does not FETCH, FIX 0x80 / 0x40, As up to 0xFF: the shader's 8-bit output
 *             through the fixed-function blend is kh1_blend_gpu's pixel
 *   atest     ATST x AFAIL x AREF, every alpha: each draw's discard is kh1_atest's compare (atest.h); DATE's
 *             set-up discards where kh1_atest_date_mark is 0
 *   texfmt    CT32, CT24, CT16, CT16S, T8, T4 under three TEXA values: the texel after the format's steps is
 *             kh1_texfmt_sample's, from the GPU's sample of kh1_texfmt_convert's upload
 *   sampler   REGION_CLAMP on U and V, point and bilinear: the shader's clamp, then the GPU's addressing and
 *             filter, is kh1_sampler_port's sample; ST / Q divided
 *   vertex    the 7 vertex shaders map a vertex.h vertex to clip space and pass its attributes on */
#include "common.h"
#include "platform/shadergen.h"
#include "platform/texfunc.h"
#include "platform/fog.h"
#include "platform/blend.h"
#include "platform/atest.h"
#include "platform/texfmt.h"
#include "platform/sampler.h"
#include "platform/vertex.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("shadergen_test: %s\n", name); fails++; } } while (0)

static char text[KH1_SHADER_TEXT];
static KH1ShaderRun run;
static u32 nfrag, nnot, maxlen, bad_texts;

static void set4(f32 *v, f32 a, f32 b, f32 c, f32 d) { v[0] = a; v[1] = b; v[2] = c; v[3] = d; }
static void unorm4(f32 *v, u32 c) { set4(v, (c & 0xFF) / 255.0f, (c >> 8 & 0xFF) / 255.0f, (c >> 16 & 0xFF) / 255.0f, (c >> 24) / 255.0f); }
static u32 reg8(const f32 *v) { /* a register in the GS's units as RGBA8 */
    u32 i, o = 0;
    for (i = 0; i < 4; i++) o |= (u32)(v[i] < 0 ? 0 : v[i] > 255 ? 255 : (s32)v[i]) << i * 8;
    return o;
}
static u32 out8(const f32 *v) { /* the colour output as the target's UNORM8 write rounds it */
    u32 i, o = 0;
    for (i = 0; i < 4; i++) o |= (u32)(v[i] <= 0 ? 0 : v[i] >= 1 ? 255 : (s32)(v[i] * 255.0f + 0.5f)) << i * 8;
    return o;
}
static void uniforms(const KH1DrawState *d) {
    f32 u[16];
    kh1_shader_uniforms(d, u);
    memcpy(run.v[KH1_SV_UA], u, sizeof u);
}

/* the shader for a key, generated and counted; 0 when not generated */
static const char *frag(const KH1ShaderKey *k) {
    u32 n = kh1_shader_frag_cg(k, text, sizeof text);
    if (!n) return 0;
    if (n > maxlen) maxlen = n;
    return text;
}

static void exec(const char *t) {
    kh1_shader_run(t, &run);
    if (run.bad && !bad_texts++) printf("shadergen_test: line %u not read back:\n%s", run.bad_line, t);
}

/* ---- the texture the GPU samples (tex2D's callback) ---- */
static u32 cur_texel; /* a 1 x 1 texture's texel (texfunc, blend) */
static void tex_one(void *ctx, f32 s, f32 t, f32 out[4]) { (void)ctx; (void)s; (void)t; unorm4(out, cur_texel); }

static KH1ShaderKey key0(void) {
    KH1ShaderKey k;
    memset(&k, 0, sizeof k);
    k.pre_a = 2; /* no pre-scale: Cs */
    k.pre_d = 3;
    return k;
}

/* ---- parse: a sweep of keys ---- */
static void parse(void) {
    static const u8 fmts[] = { KH1_TEXFMT_RGBA8, KH1_TEXFMT_A1B5G5R5, KH1_TEXFMT_P8, KH1_TEXFMT_P4 };
    KH1ShaderKey k;
    u32 i, n = 0, ok = 1, f, nf;
    const char **forms;
    const u32 *uses;
    for (i = 0; i < 4096; i++) {
        k = key0();
        k.tex = i & 1 ? fmts[i >> 1 & 3] : 0;
        k.texa = k.tex == KH1_TEXFMT_RGBA8 || k.tex == KH1_TEXFMT_A1B5G5R5 ? i >> 3 & 1 : 0;
        k.tfx = i >> 4 & 3;
        k.tcc = i >> 6 & 1;
        k.fst = i >> 7 & 1;
        k.fog = i >> 8 & 1;
        k.discard = (u8)(i >> 9 & 3) % 3;
        k.atst = (u8)((i * 7) & 7);
        if (i >> 11 & 1) { k.pre_a = (u8)(1 + (i >> 1) % 3); k.pre_d = (u8)(1 + (i >> 4) % 4); k.pre_floor = (u8)(i % 3); k.csel = (i >> 5 & 1) ? 2 : 0; }
        k.su = (i >> 2 & 1) ? KH1_SHADER_CLAMP : 0;
        k.sv = (i >> 10 & 1) ? KH1_SHADER_CLAMP : 0;
        if (!frag(&k)) { nnot++; continue; }
        nfrag++;
        memset(&run, 0, sizeof run);
        run.tex = tex_one;
        exec(text);
        if (run.bad) ok = 0;
        n++;
    }
    for (i = 0; i < 2; i++) {
        k = key0();
        k.setup = 1;
        k.datm = (u8)i;
        k.discard = KH1_DISCARD_FAIL;
        if (frag(&k)) { memset(&run, 0, sizeof run); run.tex = tex_one; exec(text); if (run.bad) ok = 0; }
    }
    k = key0();
    k.fetch = 1;
    CHECK("parse: a FETCH key is not generated", !frag(&k));
    k = key0();
    k.tex = KH1_TEXFMT_RGBA8;
    k.su = KH1_SHADER_TAPS;
    CHECK("parse: a TAPS key is not generated", !frag(&k));
    for (i = 0; i < 7; i++) {
        u32 len = kh1_shader_vert_cg(i, text, sizeof text);
        memset(&run, 0, sizeof run);
        exec(text);
        if (!len || run.bad) ok = 0;
    }
    printf("shadergen_test: parse: %u fragment variants generated (%u not), at most %u bytes; 7 vertex variants\n", n, nnot,
           maxlen);
    CHECK("parse: every generated line is one of the forms", ok && !bad_texts);
    nf = kh1_shader_forms(&forms, &uses);
    for (f = 0; f < nf; f++)
        if (!uses[f]) { printf("shadergen_test: form \"%s\" unused\n", forms[f]); ok = 0; }
    CHECK("parse: every form is used", ok);
    /* one of each, for the record */
    k = key0();
    k.tex = KH1_TEXFMT_A1B5G5R5;
    k.texa = 1;
    k.fst = 1;
    k.tcc = 1;
    k.fog = 1;
    k.discard = KH1_DISCARD_FAIL;
    k.atst = KH1_ATST_GREATER;
    k.pre_a = 1;
    k.pre_d = 3;
    k.pre_floor = 1;
    printf("%s", frag(&k) ? text : "?\n");
}

/* ---- texfunc ---- */
static const u32 vals[] = { 0x00, 0x01, 0x02, 0x3F, 0x40, 0x7F, 0x80, 0x81, 0xC0, 0xFE, 0xFF };
#define NV (sizeof vals / sizeof vals[0])

static void texfunc(void) {
    KH1ShaderKey k;
    u32 tfx, tcc, i, j, bad = 0, n = 0;
    for (tfx = 0; tfx < 4; tfx++)
        for (tcc = 0; tcc < 2; tcc++) {
            k = key0();
            k.tex = KH1_TEXFMT_RGBA8;
            k.fst = 1;
            k.tfx = (u8)tfx;
            k.tcc = (u8)tcc;
            frag(&k);
            for (i = 0; i < NV * NV; i++)
                for (j = 0; j < NV; j++) {
                    u32 ct = vals[i % NV] | vals[i / NV] << 8 | vals[j] << 16 | vals[(i + j) % NV] << 24;
                    u32 cv = vals[j] | vals[i % NV] << 8 | vals[(i * 3 + j) % NV] << 16 | vals[i / NV] << 24, want, got;
                    memset(&run, 0, sizeof run);
                    run.tex = tex_one;
                    cur_texel = ct;
                    unorm4(run.v[KH1_SV_COL], cv);
                    set4(run.v[KH1_SV_TC], 0.5f, 0.5f, 1.0f, 1.0f);
                    exec(text);
                    want = kh1_texfunc(tfx, tcc, ct, cv);
                    got = reg8(run.v[KH1_SV_R4]);
                    n++;
                    if (got != want || kh1_texfunc_shader(tfx, tcc, ct, cv, 1) != want) {
                        if (!bad++) printf("shadergen_test: texfunc %u/%u ct %08x cv %08x: model %08x, shader %08x\n", tfx, tcc,
                                           ct, cv, want, got);
                    }
                }
        }
    printf("shadergen_test: texfunc: %u cases\n", n);
    CHECK("texfunc: the generated shader is kh1_texfunc's for TFX 0-3 x TCC", !bad);
}

/* ---- fog ---- */
static void fog(void) {
    KH1ShaderKey k = key0();
    u32 c, f, fc, bad = 0, n = 0;
    k.fog = 1;
    frag(&k);
    for (c = 0; c < NV * NV; c++)
        for (f = 0; f < 256; f += 3)
            for (fc = 0; fc < NV; fc += 2) {
                u32 col = vals[c % NV] | vals[c / NV] << 8 | vals[(c + 3) % NV] << 16 | 0x80u << 24;
                u32 fogcol = vals[fc] | vals[(fc + 5) % NV] << 8 | vals[NV - 1 - fc] << 16, want, got;
                memset(&run, 0, sizeof run);
                unorm4(run.v[KH1_SV_COL], col);
                run.v[KH1_SV_FOG][0] = f / 255.0f;
                set4(run.v[KH1_SV_UB], 0.0f, (f32)(fogcol & 0xFF), (f32)(fogcol >> 8 & 0xFF), (f32)(fogcol >> 16));
                exec(text);
                want = kh1_fog_gs(col, f, fogcol);
                got = reg8(run.v[KH1_SV_R4]);
                n++;
                if (got != want && !bad++)
                    printf("shadergen_test: fog c %08x f %02x fogcol %06x: model %08x, shader %08x\n", col, f, fogcol, want, got);
            }
    printf("shadergen_test: fog: %u cases\n", n);
    CHECK("fog: the generated shader is kh1_fog_gs's", !bad);
}

/* ---- blend: the shader's output through the GPU's fixed-function blend ---- */
static f32 factor(u32 f, u32 sa8, u32 da8) {
    switch (f) {
    case KH1_BF_ZERO: return 0.0f;
    case KH1_BF_ONE: return 1.0f;
    case KH1_BF_SRC_ALPHA: return sa8 / 255.0f;
    case KH1_BF_ONE_MINUS_SRC_ALPHA: return 1.0f - sa8 / 255.0f;
    case KH1_BF_DST_ALPHA: return da8 / 255.0f;
    }
    return 1.0f - da8 / 255.0f;
}

static u32 fixed_function(const KH1BlendState *st, u32 src, u32 dst) {
    u32 i, out = 0, mask = 0;
    f32 f = factor(st->fd, src >> 24, dst >> 24), r;
    for (i = 0; i < 24; i += 8) {
        s32 s = (s32)(src >> i & 0xFF);
        if (!st->enable) { out |= (u32)s << i; continue; }
        r = (f32)(dst >> i & 0xFF) * f;
        r = st->eq == KH1_BEQ_ADD ? s + r : st->eq == KH1_BEQ_SUBTRACT ? s - r : r - s;
        out |= (u32)(r <= 0.0f ? 0 : r >= 255.0f ? 255 : (s32)(r + 0.5f)) << i;
    }
    out |= src & 0xFF000000u;
    for (i = 0; i < 4; i++)
        if (st->mask >> i & 1) mask |= 0xFFu << i * 8;
    return (out & mask) | (dst & ~mask);
}

static void blend(void) {
    static const u32 as[] = { 0x00, 0x01, 0x40, 0x7F, 0x80, 0x81, 0x90, 0xFF };
    static const u32 fix[] = { 0x80, 0x40, 0x00 };
    u32 a, b, c, d, fi, i, j, forms = 0, fetch = 0, bad = 0, n = 0;
    for (a = 0; a < 3; a++)
        for (b = 0; b < 3; b++)
            for (c = 0; c < 3; c++)
                for (d = 0; d < 3; d++)
                    for (fi = 0; fi < 3; fi++) {
                        KH1DrawRegs r;
                        KH1DrawState ds;
                        memset(&r, 0, sizeof r);
                        r.prim = 0x46; /* SPRITE | ABE, flat */
                        r.alpha_lo = a | b << 2 | c << 4 | d << 6;
                        r.alpha_hi = fix[fi];
                        r.zbuf_hi = 1;
                        kh1_drawstate_of(&r, &ds);
                        if (!ds.n) continue;
                        if (!frag(&ds.pipe[0].shader)) { fetch++; continue; }
                        forms++;
                        uniforms(&ds);
                        for (i = 0; i < NV * 8; i++)
                            for (j = 0; j < NV; j++) {
                                u32 cs = vals[i % NV] | vals[j] << 8 | vals[(i / NV + j) % NV] << 16 | as[i / NV] << 24;
                                u32 dst = vals[j] | vals[(i + 2) % NV] << 8 | vals[i % NV] << 16 | kh1_blend_store_alpha(as[(i + j) % 8]) << 24;
                                u32 want = kh1_blend_gpu(&ds.blend, cs, dst), got;
                                memset(run.v[KH1_SV_COL], 0, sizeof run.v[0]);
                                unorm4(run.v[KH1_SV_COL], cs);
                                exec(text);
                                got = fixed_function(&ds.blend, out8(run.v[KH1_SV_OCOLOR]), dst);
                                n++;
                                if (got != want && !bad++)
                                    printf("shadergen_test: blend %u%u%u%u fix %02x cs %08x dst %08x: model %08x, shader %08x\n", a,
                                           b, c, d, fix[fi], cs, dst, want, got);
                            }
                    }
    printf("shadergen_test: blend: %u forms generated, %u FETCH (not generated), %u cases\n", forms, fetch, n);
    CHECK("blend: the shader's output through the GPU's blend is kh1_blend_gpu's, every form not FETCH", !bad && forms);
}

/* ---- atest ---- */
static void atest(void) {
    static const u32 arefs[] = { 0x00, 0x10, 0x40, 0x7F, 0x80, 0xFF };
    u32 atst, afail, ri, i, a, draws = 0, bad = 0, n = 0;
    for (atst = 0; atst < 8; atst++)
        for (afail = 0; afail < 4; afail++)
            for (ri = 0; ri < 6; ri++) {
                KH1DrawRegs r;
                KH1DrawState ds;
                memset(&r, 0, sizeof r);
                r.prim = 0x06;
                r.test_lo = 1 | atst << 1 | arefs[ri] << 4 | afail << 12;
                kh1_drawstate_of(&r, &ds);
                for (i = 0; i < ds.n; i++) {
                    const KH1ShaderKey *k = &ds.pipe[i].shader;
                    if (!frag(k)) continue;
                    draws++;
                    memset(&run, 0, sizeof run);
                    uniforms(&ds);
                    for (a = 0; a < 256; a++) {
                        int pass = kh1_atest(atst, a, arefs[ri]), want;
                        want = k->discard == KH1_DISCARD_FAIL ? !pass : k->discard == KH1_DISCARD_PASS ? pass : 0;
                        unorm4(run.v[KH1_SV_COL], 0x00404040u | a << 24);
                        exec(text);
                        n++;
                        if (run.discarded != want && !bad++)
                            printf("shadergen_test: atest %u afail %u aref %02x draw %u a %02x: discarded %d, want %d\n", atst,
                                   afail, arefs[ri], i, a, run.discarded, want);
                    }
                }
            }
    printf("shadergen_test: atest: %u draws, %u cases\n", draws, n);
    CHECK("atest: each draw discards where kh1_atest says (its discard mode)", !bad && draws);
    /* DATE's set-up */
    bad = 0;
    for (i = 0; i < 2; i++) {
        KH1AtestState st;
        KH1ShaderKey k = key0();
        kh1_atest_state(1 << 14 | i << 15, 0xF, 1, &st);
        k.setup = 1;
        k.datm = st.datm;
        frag(&k);
        for (a = 0; a < 256; a++) {
            memset(&run, 0, sizeof run);
            run.tex = tex_one;
            cur_texel = 0x123456 | a << 24;
            set4(run.v[KH1_SV_POS], 100.5f, 20.5f, 0.0f, 1.0f);
            set4(run.v[KH1_SV_UXF], 2.0f / 512, 2.0f / 384, -1.0f, -1.0f);
            exec(text);
            if (run.discarded != !kh1_atest_date_mark(&st, a) && !bad++)
                printf("shadergen_test: DATE set-up DATM %u a8 %02x: discarded %d\n", i, a, run.discarded);
            if (run.v[KH1_SV_R1][0] != 100.5f / 512 || run.v[KH1_SV_R1][1] != 20.5f / 384) bad++;
        }
    }
    CHECK("atest: DATE's set-up discards where kh1_atest_date_mark is 0, at the pixel's texel", !bad);
}

/* ---- texfmt: the texel after the format's steps ---- */
static u8 upbuf[16 * 16 * 4];
static u32 pal[256], tf_psm, tf_w;
static u32 widen5(u32 c) { return c << 3 | c >> 2; }

/* the GPU's sample of the upload: RGBA8 / 255, A1B5G5R5 widened (5 bits to 8), the palette's word */
static void tex_up(void *ctx, f32 s, f32 t, f32 out[4]) {
    u32 x = (u32)(s * tf_w), y = (u32)(t * 16), fmt = kh1_texfmt_of(tf_psm);
    const u8 *p = upbuf + y * kh1_texfmt_stride(tf_psm, tf_w);
    (void)ctx;
    if (fmt == KH1_TEXFMT_RGBA8) unorm4(out, p[x * 4] | p[x * 4 + 1] << 8 | p[x * 4 + 2] << 16 | (u32)p[x * 4 + 3] << 24);
    else if (fmt == KH1_TEXFMT_A1B5G5R5) {
        u32 v = p[x * 2] | p[x * 2 + 1] << 8;
        set4(out, widen5(v & 31) / 255.0f, widen5(v >> 5 & 31) / 255.0f, widen5(v >> 10 & 31) / 255.0f, v >> 15 ? 1.0f : 0.0f);
    } else if (fmt == KH1_TEXFMT_P8) unorm4(out, pal[p[x]]);
    else unorm4(out, pal[p[x / 2] >> (x & 1) * 4 & 15]);
}

static void texfmt(void) {
    static const u32 psms[] = { 0x00, 0x01, 0x02, 0x0A, 0x13, 0x14 };
    static const u32 texa[3][2] = { { 0x80, 0x40 }, { 0x20 | 1 << 15, 0xFF }, { 0x00 | 1 << 15, 0x7F } };
    static u32 texels[256];
    u32 pi, ti, x, y, bad = 0, n = 0;
    for (x = 0; x < 256; x++) pal[x] = (x * 0x01030507u) ^ 0x5A000000u;
    for (pi = 0; pi < 6; pi++)
        for (ti = 0; ti < 3; ti++) {
            u32 psm = psms[pi];
            KH1DrawRegs r;
            KH1DrawState ds;
            tf_psm = psm;
            tf_w = 16;
            for (y = 0; y < 16; y++)
                for (x = 0; x < 16; x++) {
                    u32 v = (x * 0x2F1B3 + y * 0x91D7 + 0x3C) * 2654435761u;
                    if ((x + y * 3) % 5 == 0) v &= 0xFF000000u;
                    if (psm == 0x01) v &= 0xFFFFFF;
                    if (psm == 0x02 || psm == 0x0A) v = ((x + y * 3) % 5 == 0 ? 0 : v >> 8 & 0x7FFF) | ((x + y) % 3 == 0) << 15;
                    if (psm == 0x13) v = (x * 37 + y * 11) & 0xFF;
                    if (psm == 0x14) v = (x * 5 + y * 3) & 15;
                    texels[y * 16 + x] = v;
                }
            kh1_texfmt_convert(psm, texels, 16, 16, upbuf);
            memset(&r, 0, sizeof r);
            r.prim = 0x116; /* SPRITE | TME | FST */
            r.tex0_lo = psm << 20 | 1 << 14 | 4u << 26;
            r.tex0_hi = 1 | 1 << 2 | 1 << 3; /* TH 4, TCC, DECAL */
            r.clamp_lo = 5;
            r.texa_lo = texa[ti][0];
            r.texa_hi = texa[ti][1];
            r.zbuf_hi = 1;
            kh1_drawstate_of(&r, &ds);
            if (!frag(&ds.pipe[0].shader)) { bad++; continue; }
            memset(&run, 0, sizeof run);
            uniforms(&ds);
            run.tex = tex_up;
            for (y = 0; y < 16; y++)
                for (x = 0; x < 16; x++) {
                    u32 want = kh1_texfmt_sample(psm, upbuf, 16, x, y, pal, texa[ti][0], texa[ti][1]), got;
                    unorm4(run.v[KH1_SV_COL], 0x80808080u);
                    set4(run.v[KH1_SV_TC], (x + 0.5f) / 16, (y + 0.5f) / 16, 1.0f, 1.0f);
                    exec(text);
                    got = reg8(run.v[KH1_SV_R2]);
                    n++;
                    if (got != want && !bad++)
                        printf("shadergen_test: texfmt psm %02x texa %u (%u, %u): model %08x, shader %08x\n", psm, ti, x, y, want,
                               got);
                }
        }
    printf("shadergen_test: texfmt: %u texels\n", n);
    CHECK("texfmt: the shader's texel after the format's steps is kh1_texfmt_sample's", !bad);
}

/* ---- sampler: the shader's clamp, then the GPU's addressing and filter ---- */
static KH1Sampler gpu_s; /* the sampler without the shader's steps */
static u32 sm_n;
static u32 grid(u32 x, u32 y, void *ctx) {
    (void)ctx;
    return ((x * 29 + y * 7) & 0xFF) | ((x * 3 + y * 41) & 0xFF) << 8 | ((x ^ y) * 13 & 0xFF) << 16 | (0x40 + (x + y) % 0x41) << 24;
}
static void tex_gpu(void *ctx, f32 s, f32 t, f32 out[4]) {
    s32 u = (s32)(s * sm_n * 16 + (s < 0 ? -0.5f : 0.5f)), v = (s32)(t * sm_n * 16 + (t < 0 ? -0.5f : 0.5f));
    (void)ctx;
    unorm4(out, kh1_sampler_port(&gpu_s, grid, 0, u, v));
}

static void sampler(void) {
    static const u32 rc[][2] = { { 1, 14 }, { 0, 9 }, { 3, 3 }, { 5, 15 } };
    u32 ci, lin, bad = 0, n = 0;
    s32 u, v;
    sm_n = 16;
    for (ci = 0; ci < 4; ci++)
        for (lin = 0; lin < 2; lin++) {
            KH1DrawRegs r;
            KH1DrawState ds;
            memset(&r, 0, sizeof r);
            r.prim = 0x116;
            r.tex0_lo = 1 << 14 | 4u << 26;
            r.tex0_hi = 1 | 1 << 2 | 1 << 3;
            /* WMS / WMT REGION_CLAMP, MINU / MAXU, MINV / MAXV */
            r.clamp_lo = 2 | 2 << 2 | rc[ci][0] << 4 | rc[ci][1] << 14 | rc[3 - ci][0] << 24;
            r.clamp_hi = rc[3 - ci][0] >> 8 | rc[3 - ci][1] << 2;
            r.tex1_lo = lin ? 0x60 : 0; /* MMAG, MMIN linear */
            r.zbuf_hi = 1;
            kh1_drawstate_of(&r, &ds);
            gpu_s = ds.sampler;
            gpu_s.u.shader = gpu_s.v.shader = KH1_SHADER_NONE;
            if (!frag(&ds.pipe[0].shader)) { bad++; continue; }
            memset(&run, 0, sizeof run);
            uniforms(&ds);
            run.tex = tex_gpu;
            for (u = -40; u < 16 * 16 + 40; u += 3)
                for (v = -24; v < 16 * 16 + 24; v += 37) {
                    u32 want = kh1_sampler_port(&ds.sampler, grid, 0, u, v), got;
                    unorm4(run.v[KH1_SV_COL], 0x80808080u);
                    set4(run.v[KH1_SV_TC], u / 256.0f, v / 256.0f, 1.0f, 1.0f);
                    exec(text);
                    got = reg8(run.v[KH1_SV_R2]);
                    n++;
                    if (got != want && !bad++)
                        printf("shadergen_test: sampler case %u linear %u (%d, %d)/16: model %08x, shader %08x\n", ci, lin, u, v,
                               want, got);
                }
        }
    printf("shadergen_test: sampler: %u samples\n", n);
    CHECK("sampler: the shader's REGION_CLAMP clamp and the GPU's sample are kh1_sampler_port's", !bad);
    { /* ST / Q: the shader divides */
        KH1ShaderKey k = key0();
        k.tex = KH1_TEXFMT_RGBA8;
        k.tfx = KH1_TFX_DECAL;
        k.tcc = 1;
        frag(&k);
        memset(&run, 0, sizeof run);
        run.tex = tex_one;
        set4(run.v[KH1_SV_TC], 0.75f * 4.0f, 0.25f * 4.0f, 4.0f, 1.0f);
        exec(text);
        CHECK("sampler: ST / Q divided per pixel", run.v[KH1_SV_R1][0] == 0.75f && run.v[KH1_SV_R1][1] == 0.25f);
    }
}

/* ---- vertex shaders ---- */
static void vertex(void) {
    u32 i, bad = 0;
    for (i = 0; i < 7; i++) {
        KH1GpuVert g;
        f32 w = 512.0f, h = 384.0f;
        u32 tex = i >= 5 ? 2 : i >= 3 ? 1 : 0, fog = i && !(i & 1);
        memset(&g, 0, sizeof g);
        g.x = 100.5f;
        g.y = 300.25f;
        g.z = 0.375f;
        g.s = 0.125f;
        g.t = 0.625f;
        g.q = 2.0f;
        g.rgba[0] = 0x80;
        g.rgba[1] = 0x10;
        g.rgba[2] = 0xFF;
        g.rgba[3] = 0x40;
        g.f = 0x77;
        kh1_shader_vert_cg(i, text, sizeof text);
        memset(&run, 0, sizeof run);
        set4(run.v[KH1_SV_POS], g.x, g.y, g.z, 0.0f);
        set4(run.v[KH1_SV_COL], g.rgba[0] / 255.0f, g.rgba[1] / 255.0f, g.rgba[2] / 255.0f, g.rgba[3] / 255.0f);
        set4(run.v[KH1_SV_TC], g.s, g.t, g.q, 0.0f);
        run.v[KH1_SV_FOG][0] = g.f / 255.0f;
        set4(run.v[KH1_SV_UXF], 2.0f / w, 2.0f / h, -1.0f, -1.0f); /* cmdbuf.c's per-pass slot */
        exec(text);
        {
            const f32 *o = run.v[KH1_SV_OPOS];
            f32 px = (o[0] + 1.0f) * 0.5f * w, py = (o[1] + 1.0f) * 0.5f * h, dx = px - g.x, dy = py - g.y;
            if (dx < -1e-3f || dx > 1e-3f || dy < -1e-3f || dy > 1e-3f || o[2] != g.z || o[3] != 1.0f) bad++;
            if (i && run.v[KH1_SV_OCOL][3] != g.rgba[3] / 255.0f) bad++;
            if (tex && (run.v[KH1_SV_OTC][0] != g.s || run.v[KH1_SV_OTC][1] != g.t ||
                        run.v[KH1_SV_OTC][2] != (tex == 2 ? g.q : 1.0f)))
                bad++;
            if (fog && run.v[KH1_SV_OFOG][0] != g.f / 255.0f) bad++;
            if (run.bad) bad++;
        }
    }
    CHECK("vertex: the 7 vertex shaders map target pixels to clip space and pass the attributes on", !bad);
}

int main(void) {
    parse();
    texfunc();
    fog();
    blend();
    atest();
    texfmt();
    sampler();
    vertex();
    printf("shadergen_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
