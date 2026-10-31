#ifndef PLATFORM_DRAWSTATE_H
#define PLATFORM_DRAWSTATE_H

#include "platform/atest.h"
#include "platform/blend.h"
#include "platform/depth.h"
#include "platform/sampler.h"

/* The whole draw state a port's GPU needs for one GS draw state (docs/renderer-spec.md 4.13
 * "Session 123", vita-port-plan 5.1bk): port code, not game code.  Sessions 119 to 122 turned each
 * GS register into its GPU piece (texfmt.h, texfunc.h, sampler.h, blend.h, atest.h, depth.h, fog.h,
 * primasm.h); this puts them together, from the registers a draw reads (host/null/gsregs.h's
 * KH1GsDraw: PRIM, the chosen context's FRAME / ZBUF / TEST / ALPHA / TEX0 / TEX1 / CLAMP, FOGCOL,
 * TEXA), as
 *
 *   - up to two GPU draws (atest.h: the pass draw and AFAIL's fail draw), each a pipeline: the
 *     fixed-function state (the primitive class, the blend's equation and factors, the colour write
 *     mask, the depth compare and write, the stencil test DATE needs) and the fragment shader;
 *   - DATE's stencil set-up draw, a pipeline of its own (the shader samples the target's alpha);
 *   - the fragment shader's variant (KH1ShaderKey): what the shader does, compiled once per value:
 *     the texture's upload format and TEXA, TFX / TCC, fog, the blend's pre-scale, the frame read
 *     a FETCH blend needs, the alpha test's discard and compare, the sampler's shader steps, ST / UV;
 *   - the per-draw uniforms (KH1DrawUniforms): AREF, FIX, FOGCOL, TEXA, the REGION_CLAMP /
 *     REGION_REPEAT bounds, and a FETCH blend's ALPHA (its shader runs the GS's formula);
 *   - the sampler object (sampler.h's address modes and filter) and the texture binding (TEX0's
 *     TBP0 / TBW / PSM / TW / TH, the texture cache's key; the CLUT is the palette cache's).
 *
 * A key holds only u8 fields, so two keys compare with memcmp (kh1_drawstate_of clears them first).
 * What is left out on purpose: IIP (primasm.h copies a flat colour into the vertices, so flat and
 * Gouraud draw with the same shader), AA1 (not modelled), the render target and the depth buffer's
 * format (the render pass's, include/platform/target.h) and the texture's address.  Not part of the
 * PS2 build. */
#ifndef KH1_PS2
/* the GS registers a draw reads (lo / hi words; FOGCOL's 24 bits in fogcol) */
typedef struct {
    u32 prim;
    u32 frame_lo, frame_hi, zbuf_lo, zbuf_hi, test_lo;
    u32 alpha_lo, alpha_hi, tex0_lo, tex0_hi, tex1_lo, tex1_hi, clamp_lo, clamp_hi;
    u32 fogcol, texa_lo, texa_hi;
} KH1DrawRegs;

/* the fragment shader's variant */
typedef struct {
    u8 tex;       /* 0: no texture (TME 0), else texfmt.h's KH1_TEXFMT_* the texture uploads as */
    u8 texa;      /* the shader takes A from TEXA (texfmt.h: CT24 / CT16 and their Z twins) */
    u8 tfx, tcc;  /* texfunc.h's TFX and TCC (with a texture) */
    u8 fst;       /* 1: UV (no divide), 0: ST / Q (the shader divides) */
    u8 fog;       /* FGE: fog.h's step */
    u8 pre_a, pre_d; /* blend.h's pre-scale, + 2 (so -1 .. 1 are 1 .. 3) */
    u8 pre_floor, csel; /* blend.h's */
    u8 fetch;     /* the shader reads the frame: 1 a KH1_BLEND_FETCH blend (it blends itself), 2 no blend but a
                   * per-bit FBMSK (it merges the bits) */
    u8 discard;   /* atest.h's KH1_DISCARD_* */
    u8 atst;      /* the compare when it discards (else 0) */
    u8 su, sv;    /* sampler.h's KH1_SHADER_* on each axis (with a texture) */
    u8 setup;     /* 1: DATE's set-up shader (samples the target's alpha, discards, no colour); 2: its clear
                   * (session 129: no sample, no discard, no colour) */
    u8 datm;      /* the set-up's DATM: it keeps the pixels whose stored alpha is 1.0 when 1, below it when 0 */
    /* a frame read's own (fetch 1 / 2, else 0; renderer-spec 4.13 "Session 128"): */
    u8 fabcd;     /* fetch 1: ALPHA's A / B / C / D byte (the shader runs the GS's formula with it) */
    u8 fpsm;      /* the frame: 0 CT32, 1 CT24 (Ad is 0x80, no alpha stored), 2 CT16 / CT16S */
    u8 fbm[4];    /* FBMSK's bytes R, G, B, A: the bits the shader keeps from the target */
    u8 lin;       /* 2026-10-31: a native draw with a texture (natdraw.h): the colour and fog arrive multiplied by the
                   * clip w and tc.w holds w, so the shader divides them back: interpolated straight across the
                   * screen as the GS does, not with the perspective the GPU gives every varying */
} KH1ShaderKey;

/* one GPU pipeline */
typedef struct {
    u8 cls;       /* primasm.h's KH1_PA_POINTS / LINES / TRIANGLES */
    u8 blend;     /* blending on */
    u8 eq, fs, fd; /* blend.h's equation and destination-side factors (with blend) */
    u8 mask;      /* the colour write mask: bit 0 R, 1 G, 2 B, 3 A */
    u8 ztest;     /* depth.h's KH1_ZTST_ALWAYS / GEQUAL / GREATER (ALWAYS: the test off) */
    u8 zwrite;    /* the depth write */
    u8 stencil;   /* 0 none, 1 the draw tests stencil == 1 (DATE), 2 the set-up writes stencil 1, 3 the set-up's
                   * clear writes stencil 0 (ALWAYS, REPLACE) */
    KH1ShaderKey shader;
} KH1PipeKey;

/* the per-draw uniforms */
typedef struct {
    u32 aref;     /* the alpha test's reference (when the shader discards) */
    u32 fix;      /* ALPHA's FIX (when the blend's C is FIX) */
    u32 fogcol;   /* RGB (with fog) */
    u32 ta0, aem, ta1; /* TEXA (when the shader takes A from it) */
    u32 u0, u1, v0, v1; /* REGION_CLAMP's MIN / MAX or REGION_REPEAT's mask / fix (sampler.h) */
    u32 abcd, psm; /* ALPHA's low byte and the frame's PSM (a FETCH blend's formula) */
    u32 fbmsk;    /* FBMSK when the shader merges a per-bit mask (fetch 2, or a FETCH blend's) */
} KH1DrawUniforms;

typedef struct {
    u8 n;                    /* GPU draws: 0 (nothing is written), 1 or 2 */
    KH1PipeKey pipe[2];
    u8 setup;                /* 1: DATE's set-up draws come first (its clear, then setup_pipe) */
    KH1PipeKey setup_pipe;   /* the set-up: the draw's own primitives (its class and vertices), stencil 1 where
                              * the target's alpha is DATM; session 129: kh1_date_clear_pipe's clear before it */
    KH1DrawUniforms u;
    KH1Sampler sampler;      /* with a texture */
    u32 tex0_lo, tex0_hi;    /* the texture binding: TEX0 with CLD and the CLUT fields cleared */
    /* the pieces, as sessions 120 to 122's calls give them */
    KH1BlendState blend;
    KH1AtestState atest;
    KH1DepthState depth;
} KH1DrawState;

/* the whole state for a draw's registers */
void kh1_drawstate_of(const KH1DrawRegs *r, KH1DrawState *out);
/* a key as text (for traces): "tri blend add/1/1-sa mask f z ge/w | tex p8 mod tcc ..." */
const char *kh1_pipekey_str(const KH1PipeKey *k);
/* DATE's clear before the set-up (session 129, renderer-spec 4.13 "Session 129"): stencil 0 over the same
 * primitives, so the set-up's discards leave 0, not what an earlier DATE command or the scene's load left */
void kh1_date_clear_pipe(const KH1PipeKey *setup, KH1PipeKey *out);

/* a set of distinct pipelines, fragment shaders and samplers, counted over draw states */
#define KH1_PIPESET_MAX 256
typedef struct {
    u32 states;              /* draw states added */
    u32 empty;               /* of them with no GPU draw (ZTST NEVER, nothing written) */
    u32 npipe, nshader, nsampler;
    KH1PipeKey pipe[KH1_PIPESET_MAX];
    u32 pipe_uses[KH1_PIPESET_MAX]; /* draw states using it */
    KH1ShaderKey shader[KH1_PIPESET_MAX];
    u8 sampler[KH1_PIPESET_MAX][4]; /* addr u, addr v, linear, 0 */
    u32 lost;                /* keys past KH1_PIPESET_MAX */
} KH1PipeSet;
void kh1_pipeset_clear(KH1PipeSet *s);
void kh1_pipeset_add(KH1PipeSet *s, const KH1DrawState *d);
#endif

#endif
