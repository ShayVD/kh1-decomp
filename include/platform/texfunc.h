#ifndef PLATFORM_TEXFUNC_H
#define PLATFORM_TEXFUNC_H

/* The texture function a port's fragment shader runs (docs/renderer-spec.md 4.13 "Session 120",
 * vita-port-plan 5.1bh): port code, not game code.  After the texel is sampled (include/platform/
 * texfmt.h: RGBA8 on the GS's scale, A 0x80 = 1.0), TEX0's TFX and TCC combine it with the vertex
 * colour (RGBAQ, also 0x80 = 1.0), as the GS manual gives it, each result clamped to 0xFF:
 *
 *   TFX              RGB                      A with TCC 1         A with TCC 0
 *   0 MODULATE       Ct x Cv >> 7             At x Av >> 7         Av
 *   1 DECAL          Ct                       At                   Av
 *   2 HIGHLIGHT      (Ct x Cv >> 7) + Av      At + Av              Av
 *   3 HIGHLIGHT2     (Ct x Cv >> 7) + Av      At                   Av
 *
 * What the game uses (session 120's survey, 4.13 "Session 120"): MODULATE in every static packet but
 * one and in every TEX0 the C builds, DECAL in texspot's sprite (D_0035C550); no HIGHLIGHT or
 * HIGHLIGHT2 in the main ELF.  TCC 0 only on CT24 copies.  The meshes' TEX0_2 come with the disc's
 * model data: check them on the real-disc run.  All four forms are here, so a model or an overlay
 * that uses one is drawn right.
 *
 * The shader gets the texel and the vertex colour as UNORM8 values (x / 255).  Multiplied in floats
 * and written back to an 8-bit target the result rounds where the GS truncates (at most 1 apart);
 * kh1_texfunc_shader models a shader that takes the 8-bit values back (floor(x x 255 + 0.5)) and
 * does the GS's integer steps, which is exact.  Not part of the PS2 build. */
#ifndef KH1_PS2
enum { KH1_TFX_MODULATE, KH1_TFX_DECAL, KH1_TFX_HIGHLIGHT, KH1_TFX_HIGHLIGHT2 };

/* the GS's colour for texel ct and vertex colour cv (RGBA8, R in bits 0-7) under TFX tfx and TCC tcc */
u32 kh1_texfunc(u32 tfx, u32 tcc, u32 ct, u32 cv);
/* the same from TEX0's high word (TCC bit 2, TFX bits 3-4) */
u32 kh1_texfunc_tex0(u32 tex0_hi, u32 ct, u32 cv);
/* a model of the fragment shader on UNORM inputs: exact (the 8-bit values taken back) when exact is
 * nonzero, else the plain float form (t x c x 255 / 128 ...) rounded to 8 bits */
u32 kh1_texfunc_shader(u32 tfx, u32 tcc, u32 ct, u32 cv, int exact);
#endif

#endif
