#ifndef PLATFORM_BLEND_H
#define PLATFORM_BLEND_H

/* The blend state a port's GPU runs for the GS's ALPHA, FBMSK and COLCLAMP (docs/renderer-spec.md 4.13
 * "Session 121", vita-port-plan 5.1bi): port code, not game code.  The GS blends the colour as
 *
 *   Cv = ((A - B) x C >> 7) + D, clamped to 0 .. 0xFF (COLCLAMP 1)     A, B, D: Cs, Cd or 0; C: As, Ad or FIX
 *
 * with the product floored (an arithmetic shift), and writes the source's alpha As unblended.  C is on
 * the 0x80 scale, so As above 0x80 is a factor above 1.0.  A GPU blends src x Fs (+ / -) dst x Fd with
 * factors in 0 .. 1 and one source alpha that is both the factor and the value written, so the port:
 *
 *   - keeps its render targets' alpha on the GS's 0x80 scale: the alpha a draw writes is
 *     min(As, 0x80) / 0x80 (kh1_blend_store_alpha), read back exactly as min(As, 0x80)
 *     (kh1_blend_load_alpha).  The shader's output alpha is then the factor C / 0x80 when C is As,
 *     DST_ALPHA is Ad / 0x80, and DATE's bit 7 is "the stored alpha is 1.0" (include/platform/atest.h).
 *     A target sampled as a texture gives At = A x 0x80, not A x 0xFF (renderer-spec 4.13).  Lost: an
 *     As above 0x80 read back from a target (it reads 0x80).
 *   - pre-scales Cs in the shader: it writes pre_a x (Cs x C / 0x80) + pre_d x Cs, clamped to 0 .. 0xFF,
 *     and the blend takes it with Fs ONE (added, or subtracted under REVERSE_SUBTRACT), so the GPU's
 *     factors only carry the destination's.  When the destination factor is
 *     ZERO or ONE the shader floors the product (ceils it when negative, the GS's arithmetic shift) and
 *     the result is exact for every As; otherwise it is within 1 while C <= 0x80.
 *
 * What the game sets (4.13 "Session 121"): (Cs - Cd) x As + Cd (the normal blend, 20 static senders,
 * renderer B), (Cs - 0) x As + Cd (additive: func_00106000, the bevel, the HUD's numbers with FIX 0x80),
 * (Cd - Cs) x As + 0 (func_00106000's darken), (0 - Cs) x As + Cd (the bevel, As 0x90) and
 * (0 - 0) x FIX + Cs (renderer B's default, no blending).  The bevel's As 0x90 is in a one-term form,
 * exact; whether a normal blend's As goes past 0x80 comes with the disc's data (the real-disc run).
 * Forms with no fixed-function equivalent are KH1_BLEND_FETCH (the shader reads the frame): Cs x Ad, a
 * destination term 1 + C, a destination term x FIX other than 0 / 0x80 (no constant blend factor is
 * assumed), a source that can pass 0xFF before a subtract, a per-bit FBMSK.  30 of the 135 forms
 * (tests/host/blend_test.c); none is used by the main ELF.
 * Not part of the PS2 build. */
#ifndef KH1_PS2
enum { KH1_BF_ZERO, KH1_BF_ONE, KH1_BF_SRC_ALPHA, KH1_BF_ONE_MINUS_SRC_ALPHA, KH1_BF_DST_ALPHA, KH1_BF_ONE_MINUS_DST_ALPHA };
enum { KH1_BEQ_ADD, KH1_BEQ_SUBTRACT /* src - dst */, KH1_BEQ_REVERSE_SUBTRACT /* dst - src */ };
enum {
    KH1_BLEND_EXACT,  /* equal to the GS for every As (a one-term form, or blending off) */
    KH1_BLEND_LE80,   /* within 1 of the GS while C <= 0x80; above it the factor clamps to 1.0 */
    KH1_BLEND_FETCH   /* no fixed-function form: the shader reads the frame and runs kh1_blend_gs */
};

typedef struct {
    u8 enable;      /* 0: the shader's colour is written (ABE 0, or a form that is Cs) */
    u8 eq, fs, fd;  /* the colour channels' equation and factors (KH1_BEQ_*, KH1_BF_*) */
    s8 pre_a;       /* the shader's source: pre_a x (Cs x C / 0x80) + pre_d x Cs, clamped to 0 .. 0xFF */
    s8 pre_d;
    u8 pre_floor;   /* 1: the shader floors pre_a x Cs x C / 0x80 to an integer, 2: ceils it (the GS's
                     * floored product applied negated), 0: a float (with a destination factor) */
    u8 csel;        /* C: 0 As, 1 Ad, 2 FIX */
    u8 fix;         /* FIX, the shader's uniform when csel is 2 */
    u8 mask;        /* the colour write mask: bit 0 R, 1 G, 2 B, 3 A (from FBMSK and the frame's PSM) */
    u8 kind;        /* KH1_BLEND_EXACT / LE80 / FETCH */
    u8 abcd, psm;   /* ALPHA's low byte and the frame's PSM (a FETCH form's shader runs the GS's formula) */
} KH1BlendState;

/* the state for ALPHA (alpha_lo: A bits 0-1, B 2-3, C 4-5, D 6-7; alpha_hi: FIX), PRIM's ABE, FRAME's
 * PSM and FBMSK */
void kh1_blend_state(u32 alpha_lo, u32 alpha_hi, u32 abe, u32 frame_psm, u32 fbmsk, KH1BlendState *out);

/* the GS's blended colour for source cs (RGBA8, A = As) over destination cd (A = Ad; a CT24 frame's is
 * 0x80): RGB blended, A the source's */
u32 kh1_blend_gs(u32 alpha_lo, u32 alpha_hi, u32 cs, u32 cd, u32 frame_psm);

/* the 0x80-scale alpha a port's target stores for a GS alpha, and the GS alpha it reads back */
u32 kh1_blend_store_alpha(u32 a);
u32 kh1_blend_load_alpha(u32 a8);

/* a model of the GPU: the shader's 8-bit output for st, then the fixed-function blend over the
 * target's stored pixel dst (8-bit, its alpha on the 0x80 scale), rounded to 8 bits, the write mask
 * applied.  Returns the target's new pixel (alpha on the 0x80 scale). */
u32 kh1_blend_gpu(const KH1BlendState *st, u32 cs, u32 dst);
#endif

#endif
