#ifndef PLATFORM_SHADERGEN_H
#define PLATFORM_SHADERGEN_H

#include "platform/drawstate.h"

/* The shaders as source (docs/renderer-spec.md 4.13 "Session 127", vita-port-plan 5.1bo): port code, not
 * game code.  Each fragment shader variant (drawstate.h's KH1ShaderKey) and each vertex shader variant
 * (vertex.h's KH1VertKey index, 0 .. 6) written as Cg, the Vita's shading language (compiled to .gxp
 * offline with psp2cgc, or at boot by the system's SceShaccCg as vitaShaRK does), from one table of
 * statement forms (shadergen.c's `forms`).  The same table reads the text back: kh1_shader_run is a CPU
 * interpreter of the generated statements (each line matched against the forms, then run in f32), so
 * tests/host/shadergen_test.c checks the text itself against the models it was written from (texfunc.c,
 * fog.c, blend.c's pre-scale, atest.c, texfmt.c's shader steps, sampler.c's coordinate clamp).
 *
 * The fragment shader works in the GS's integer units throughout (0x80 = 1.0 for colour and alpha): each
 * UNORM input is taken back to its 8-bit value (floor(x x 255 + 0.5)), then the GS's integer steps run in
 * floats, exact below 2^24 (texfunc.h's and fog.h's "exact" forms), in the GS's order:
 *
 *   the vertex colour Cv; the texture coordinate (UV, or ST / Q divided), the sampler's clamp (CLAMP
 *   axes); the texel (tex2D), its format's steps (A1B5G5R5's 5 bits shifted up 3, TEXA's alpha); the
 *   texture function (TFX / TCC); fog; the alpha test's discard; the blend's pre-scale (pre_a x
 *   floor-or-ceil(Cs x C / 0x80) + pre_d x Cs, clamped); the alpha written, min(As, 0x80) on the 0x80
 *   scale (blend.h kh1_blend_store_alpha); the colour out / 255.
 *
 * DATE's set-up shader samples the target's alpha and discards where (A == 1.0) != DATM.
 *
 * A frame read (session 128, 4.13 "Session 128"): fetch 1 (a FETCH blend) and fetch 2 (no blend, a per-bit
 * FBMSK) take the target's pixel as an input `dst` (the Vita's programmable blending: the colour surface's
 * value at the fragment, as its 8-bit unsigned bytes), and the pipeline blends nothing.  Fetch 1 runs the
 * GS's formula (kh1_blend_gs) on Cs and the target (Ad read back from the 0x80 scale, 0x80 on a CT24 frame)
 * with A / B / C / D from the key; then both merge FBMSK's bits: per colour byte, a mask of the low k bits
 * (kept from the target) or the high 8 - k bits, and an alpha byte 0 or 0xFF.  Not generated
 * (kh1_shader_frag_cg returns 0): another mask shape (no float form; integer ops would do it), a CT16 / CT16S
 * frame with a frame read (the 5551 target's bits) and the sampler's own taps (KH1_SHADER_TAPS,
 * REGION_REPEAT with a fix or a narrow mask).  Of the main ELF's 27 static fragment shaders (drawpipes.py)
 * one has a frame read: the shadow casters' FBMSK 0x00000001 (fetch 2, R's lowest bit kept: func_001284a0's
 * environment), now generated; no TAPS.  The frame read's declarations (session 136, from SceShaccCg's own
 * diagnostics): `__nativecolor void main(...)`, `__regformat unsigned char4 dst : FRAGCOLOR` and a
 * `__regformat unsigned char4` COLOR output written as bytes (kh1_shader_run scales it back to 0 .. 1).
 *
 * The uniforms the code reads are kh1_shader_uniforms' 16 floats (one 64-byte uniform slot, ring.h):
 *   u_a = (AREF, FIX, TA0, TA1)   u_b = (AEM, FOGCOL R, G, B)   u_r = REGION_CLAMP's texel-centre bounds
 *   (U MIN + 0.5, U MAX + 0.5, V ..., normalised)   u_c = (ALPHA's ABCD, the frame PSM, 0, 0)
 * and the vertex shader's u_xf (2 / w, 2 / h, -1, -1), cmdbuf.h's per-pass slot.  Not part of the PS2
 * build. */
#ifndef KH1_PS2
#define KH1_SHADER_TEXT 4096 /* room for the longest generated shader */

/* the fragment shader for a key into buf; its length, 0 when the key is not generated (or buf too small) */
u32 kh1_shader_frag_cg(const KH1ShaderKey *k, char *buf, u32 cap);
/* the vertex shader variant `index` (vertex.h kh1_vertkey_index) */
u32 kh1_shader_vert_cg(u32 index, char *buf, u32 cap);
/* the uniforms a draw's shader reads */
void kh1_shader_uniforms(const KH1DrawState *d, f32 out[16]);

/* the interpreter's variables: inputs, uniforms, registers, outputs */
enum {
    KH1_SV_COL, KH1_SV_TC, KH1_SV_FOG, KH1_SV_POS,       /* inputs (fragment: as interpolated; vertex: the attributes) */
    KH1_SV_DST,                                          /* a frame read's target pixel, 8-bit (0 .. 255) */
    KH1_SV_UA, KH1_SV_UB, KH1_SV_UR, KH1_SV_UC, KH1_SV_UXF, /* uniforms */
    KH1_SV_R0, KH1_SV_R1, KH1_SV_R2, KH1_SV_R3, KH1_SV_R4, KH1_SV_R5, KH1_SV_R6, KH1_SV_R7, /* registers */
    KH1_SV_OCOLOR, KH1_SV_OPOS, KH1_SV_OCOL, KH1_SV_OTC, KH1_SV_OFOG, /* outputs */
    KH1_SV_COUNT
};
typedef struct {
    f32 v[KH1_SV_COUNT][4];
    /* tex2D(tex, c): the GPU's filtered sample at the normalised coordinate, as UNORM floats */
    void (*tex)(void *ctx, f32 s, f32 t, f32 out[4]);
    void *ctx;
    int discarded;   /* a clip() fired */
    u32 lines;       /* statements run */
    u32 bad;         /* body lines no form matches (the first one's number in bad_line) */
    u32 bad_line;
} KH1ShaderRun;

/* runs the generated text's body (the statements between the braces) on run's variables */
void kh1_shader_run(const char *text, KH1ShaderRun *run);
/* the forms (for the tests: every form used) and how many lines each matched since the start */
u32 kh1_shader_forms(const char ***forms, const u32 **uses);
#endif

#endif
