#ifndef PLATFORM_DEPTH_H
#define PLATFORM_DEPTH_H

/* The depth state a port's GPU runs for the GS's ZBUF, TEST's ZTE / ZTST and the vertices' Z
 * (docs/renderer-spec.md 4.13 "Session 122", vita-port-plan 5.1bj): port code, not game code.
 *
 * The GS's Z is an unsigned integer that grows toward the viewer: ZTST GEQUAL passes where the
 * fragment's Z >= the stored one, GREATER where it is >, ALWAYS always, NEVER never; ZTE 0 is ALWAYS
 * (renderer-spec 3.2).  A vertex's Z is clamped to the Z buffer's largest value (0xFFFFFF for Z24,
 * 0xFFFF for Z16 / Z16S, as PCSX2 does), so the 2D packets' Z 0xFFFFFFFE and the needles' -256 are
 * 0xFFFFFF in Z24.  The written Z is the fragment's when the tests pass and ZMSK is 0.
 *
 * The port keeps the GS's numbers and compares: its depth is Z x 2^-bits (bits 24 for Z24, 16 for
 * Z16 / Z16S, 32 for Z32) in a float depth buffer (D32F), with the GPU's compare GEQUAL / GREATER and
 * no reversal: Z24 and Z16 are exact there (a 24-bit integer is a float), so equal Zs compare equal
 * and the order is the GS's.  Z32 is not (the low 8 bits round away; the game has none).  A D24 unorm
 * buffer also works for Z24 when the depth is Z / 0xFFFFFF (the GPU stores round(d x 0xFFFFFF): z
 * back for every 24-bit z, tests/host/depth_test.c; check the Vita's conversion on the device).
 *
 * A primitive's depth between its vertices is interpolated by the GPU, not the GS: equal at the
 * vertices, maybe one unit apart inside.  What the game relies on is that a second pass over the same
 * vertices finds the same Zs (renderer B's pass 2 with ZTST GEQUAL and ZMSK 1, the depth blur's
 * constant z): on a GPU the same vertex positions through the same vertex program give the same
 * depths (declare the position invariant), so GEQUAL passes there too.
 *
 * What the game sets (4.13 "Session 122"): Z24 at block 0xE00 (ZBP 0x70) for the 3D target with ZTST
 * GEQUAL (renderer B, renderer A, the windows with flag 0x10, the depth blur's composites), GREATER
 * (opdma's Z-only writes and set-up packets), ALWAYS (2D, copies, the HUD), ZTE 0 (the text headers);
 * Z16S at 0x3800 for the shadow pass (3.4); ZMSK 1 for translucent passes and 2D.  Renderers A / B's
 * projection sends zmin 1 .. zmax 16777000 (func_00110618, 5.4), inside Z24.  The Z buffer drawn as
 * colour (sceneeff func_00103c48 / the sway's D_002A5CE0: the 3D target copied as CT24 into block 0xE00,
 * then read as TEX0 TBP0 0xE00) is a separate colour texture on the port, its depth buffer kept
 * (renderer-spec 4.17); kh1_depth_bits gives the GS's bits for a depth buffer sampled as a texture,
 * which nothing in the main ELF is seen to do.  Not part of the PS2 build. */
#ifndef KH1_PS2
enum { KH1_ZTST_NEVER, KH1_ZTST_ALWAYS, KH1_ZTST_GEQUAL, KH1_ZTST_GREATER };

typedef struct {
    u8 draw;   /* 0: ZTST NEVER with ZTE 1, nothing is drawn */
    u8 func;   /* the GPU's compare on kh1_depth_f32's values: KH1_ZTST_ALWAYS (ZTE 0 too), GEQUAL, GREATER */
    u8 write;  /* the depth write: ZTE 1 and ZMSK 0 */
    u8 bits;   /* the Z buffer's: 32, 24 or 16 */
    u8 psm;    /* 0x30 | ZBUF's PSM (KH1_PSMZ32 / Z24 / Z16 / Z16S) */
} KH1DepthState;

/* the state for ZBUF (zbuf_lo: ZBP bits 0-8, PSM 24-27; zbuf_hi: ZMSK bit 0) and TEST (ZTE bit 16,
 * ZTST 17-18) */
void kh1_depth_state(u32 zbuf_lo, u32 zbuf_hi, u32 test_lo, KH1DepthState *out);
/* the GS's Z for a vertex Z under Z buffer psm (0x30 | ZBUF.PSM): clamped to the format's largest */
u32 kh1_depth_clamp(u32 z, u32 psm);
/* the port's float depth for a GS Z (clamped first): z x 2^-bits, exact for Z24 / Z16 / Z16S */
float kh1_depth_f32(u32 z, u32 psm);
/* back: the GS's Z bits for a float depth (a depth buffer sampled as a texture, kh1_depth_f32's inverse) */
u32 kh1_depth_bits(float d, u32 psm);
/* a D24 unorm buffer's depth for a Z24 z (z / 0xFFFFFF), and the GPU's store of it (round to nearest) */
float kh1_depth_d24(u32 z);
u32 kh1_depth_d24_store(float d);
/* the GS's test of fragment Z z against the stored zb (ZTE 0 passes) */
int kh1_depth_gs(u32 zte, u32 ztst, u32 z, u32 zb);
/* the GPU's test of a fragment's depth d against the stored depth db under the state */
int kh1_depth_gpu(const KH1DepthState *st, float d, float db);
#endif

#endif
