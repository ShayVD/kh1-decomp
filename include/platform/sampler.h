#ifndef PLATFORM_SAMPLER_H
#define PLATFORM_SAMPLER_H

/* The sampler state a port draws a texture with (docs/renderer-spec.md 4.13 "Session 120",
 * vita-port-plan 5.1bh): port code, not game code.  CLAMP's WMS / WMT and TEX1's filter turned into a
 * GPU sampler plus what the shader does where the GPU has no mode:
 *
 *   WMS / WMT           the GS, on each tap's texel c (n texels)     the port
 *   0 REPEAT            c & (n - 1)                                  GPU repeat
 *   1 CLAMP             c clamped to 0 .. n - 1                      GPU clamp to edge
 *   2 REGION_CLAMP      c clamped to MIN .. MAX                      GPU clamp; the shader clamps the
 *                                                                    coordinate to MIN + 0.5 .. MAX + 0.5
 *                                                                    texels (each tap then lands inside,
 *                                                                    with the GS's weights); MIN 0 and
 *                                                                    MAX n - 1 or more: plain clamp
 *   3 REGION_REPEAT     (c & MIN) | MAX  (MIN the mask, MAX the fix) the shader computes the taps and
 *                                                                    reads them with texelFetch (one, or
 *                                                                    four and the bilinear weights); mask
 *                                                                    n - 1 or more with fix 0: GPU repeat
 *
 * A coordinate is wrapped after the half-texel step, per tap, as the GPU does too, so a GPU mode is the
 * GS's rule exactly; a region seam needs the per-tap form (a wrapped coordinate would blend across it).
 * REGION_CLAMP's MAX past the texture reads GS memory beyond it on the PS2: the port clamps to n - 1
 * (`past` counts it).
 *
 * TEX1: MMAG (bit 5) and MMIN (bits 6-8: 0 NEAREST, 1 LINEAR, 2 / 3 NEAREST_MIPMAP_*, 4 / 5
 * LINEAR_MIPMAP_*); with MXL 0 there is one level, so a mipmap form is its base filter.  LCM 1 fixes
 * the LOD at K (signed, 1/16): K 0 or less magnifies (MMAG), above it minifies (MMIN), so both GPU
 * filters take that one.  MXL above 0 (mipmaps, MIPTBP1 / 2) is not handled (`mips`).
 *
 * What the game sets (session 120's survey, 4.13 "Session 120"): CLAMP, REGION_CLAMP (1 .. 255,
 * 0 .. 510, the atlas windows of 3.3, keshpdtt's rectangle from data), REPEAT and one REGION_REPEAT
 * (mask 255) in the session 15 dump; TEX1 bilinear (LCM 0 or 1, K 0) or point, MMAG equal to MMIN
 * in every LCM 0 value (the HUD's 0x21 is LCM 1, K 0: MMAG's bilinear), MXL 0 everywhere.  Not part of the PS2 build. */
#ifndef KH1_PS2
enum { KH1_WM_REPEAT, KH1_WM_CLAMP, KH1_WM_REGION_CLAMP, KH1_WM_REGION_REPEAT };
enum { KH1_ADDR_REPEAT, KH1_ADDR_CLAMP };            /* the GPU sampler's address mode */
enum { KH1_SHADER_NONE, KH1_SHADER_CLAMP, KH1_SHADER_TAPS }; /* the shader's step on that axis */

typedef struct {
    u8 wm;     /* the GS's WMS / WMT */
    u8 addr;   /* KH1_ADDR_* */
    u8 shader; /* KH1_SHADER_* */
    u8 past;   /* REGION_CLAMP's MAX was past the texture (clamped to n - 1) */
    u16 lo, hi; /* REGION_CLAMP: MIN, MAX (MAX at most n - 1); REGION_REPEAT: mask, fix */
    u16 n;     /* texels on this axis (TW / TH) */
} KH1SamplerAxis;

typedef struct {
    KH1SamplerAxis u, v;
    u8 linear;  /* the one filter both GPU filters take: 1 bilinear, 0 point */
    u8 split;   /* MMAG and MMIN differ with LCM 0 (the GPU picks by its own LOD; not in the game) */
    u8 mips;    /* MXL above 0: not handled */
} KH1Sampler;

/* the sampler for a 1 << tw by 1 << th texture drawn with CLAMP (lo, hi words) and TEX1 (lo, hi) */
void kh1_sampler_of(u32 clamp_lo, u32 clamp_hi, u32 tex1_lo, u32 tex1_hi, u32 tw, u32 th, KH1Sampler *s);

/* a texel (x, y) of the texture, RGBA8 */
typedef u32 (*KH1SamplerFetch)(u32 x, u32 y, void *ctx);
/* the GS's sample at (u, v) in 1/16 texels: point, texel floor(u); bilinear, the taps at u - 0.5 and
 * the next, each wrapped by its axis's WMS / WMT, weighted in sixteenths */
u32 kh1_sampler_gs(const KH1Sampler *s, KH1SamplerFetch f, void *ctx, s32 u, s32 v);
/* the port's: the shader's coordinate clamp, then the GPU address mode on each tap, or the shader's
 * taps (REGION_REPEAT), the same weights.  A model of what the GPU and the shader do, for the tests */
u32 kh1_sampler_port(const KH1Sampler *s, KH1SamplerFetch f, void *ctx, s32 u, s32 v);
#endif

#endif
