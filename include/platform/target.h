#ifndef PLATFORM_TARGET_H
#define PLATFORM_TARGET_H

#include "platform/canvas.h"

/* Render targets, the viewport and the scissor a port's GPU draws with for the GS's FRAME, ZBUF,
 * XYOFFSET and SCISSOR (docs/renderer-spec.md 4.13 "Session 123", vita-port-plan 5.1bk): port code,
 * not game code.  The GS draws into whatever blocks FRAME / ZBUF name, so buffers overlap there; a
 * port keeps one GPU texture per buffer the game uses, picked by FRAME's FBP, FBW and PSM
 * (renderer-spec 3.1 / 3.2 and fscheck.py's REGIONS):
 *
 *   KH1_RT_DISPLAY    FBP 0x00 (block 0), FBW 8, CT24: the display, 448 rows (the frame copy's target)
 *   KH1_RT_ZCOLOR     FBP 0x70 (block 0x0E00): the Z area drawn as colour (the sway / lens grid's copy of
 *                     the 3D target, sceneeff func_00103c48 D_002A5FD0), a texture of its own: the depth
 *                     buffer at the same blocks is kept
 *   KH1_RT_MOVIE      FBP 0x8C (block 0x1180), FBW 10: the 640-wide movie / still frame, 448 rows
 *   KH1_RT_MAIN       FBP 0xD0 (block 0x1A00): the 3D target, CT32 512 x 384
 *   KH1_RT_SLOT       FBP 0x1B0 (block 0x3600): the texture slot as a capture: the menu's half-size copy
 *                     (FBW 4, capture.c) and the depth blur's (FBW 8, sceneeff.c), 192 rows
 *   KH1_RT_OFFSCREEN  FBP 0x1D0 (block 0x3A00): the 256 x 256 off-screen buffer (shadow windows, the eye
 *                     overlay, the crossfade)
 *   KH1_RT_CLUT       FBP 0x1F0 (block 0x3E00): the texture animations' CLUT passes (FBW 1)
 *   KH1_RT_OTHER      anything else: FBW x 64 by SCISSOR's rows, as the GS would
 *
 * The 3D target, the display, the Z area as colour and the slot's captures cover the wide view
 * (include/platform/canvas.h, KH1_HOST_WIDE): their left edge is the view's (vx0 sixteenths left of
 * canvas 0; a capture's at half that), so a port pixel is the GS's window pixel ((X - OFX) / 16) plus
 * the margin.  The others are the PS2's size.  Every size is in GS pixels times `scale` (1 draws at
 * the PS2's resolution; a texture sampled from a target is addressed by its GS size, so UVs stay
 * normalised the same).
 *
 * The depth buffer bound with a target: the main Z24 one (ZBP 0x70, sized like the 3D target) with the
 * 3D target, the shadow's Z16S (ZBP 0x1C0, 256 x 256) with the off-screen buffer, when the draw tests
 * or writes Z (ZTE 1, and a ZTST other than ALWAYS or a write).  A ZBUF any other target names is
 * dropped (`zdrop`): the depth blur's capture writes Z over the Z area on the PS2 (fscheck's
 * ZBLOCK_EXPECTED); a port's capture writes no depth (5.1ax).
 *
 * The viewport maps GS primitive coordinates (12.4) to target pixels: x = ((X - OFX) / 16 + ox) x scale,
 * y = ((Y - OFY) / 16 + oy) x scale; XYOFFSET's centring (OFX 1792, OFY 1856 for the 3D target: the
 * 512 x 384 window at 2048 - 256 / 2048 - 192) is in OFX / OFY.  The scissor is SCISSOR's rectangle
 * in window pixels, with canvas.h's rule under a wide view (the full canvas or a 32-pixel column of it
 * is the view's), plus the margin, half-open, rounded to whole pixels and clipped to the target.
 *
 * On the PS2 these share blocks (4.13 "Session 116", fscheck's BLOCK_EXPECTED): the Z area as colour
 * and the Z buffer (all of it); the movie frame and the Z area / the 3D target's first blocks; the
 * slot's FBW 8 capture and the off-screen buffer (0x3A00 .. 0x3BFF); the shadow's Z16S and the slot's
 * upper half (0x3800 .. 0x39FF); the off-screen buffer and the window font (0x3D7C .. 0x3DFF, a
 * texture re-sent before the windows draw); the message font and the Z buffer's top byte.  The port
 * keeps every one apart (kh1_target_alias names the pairs), so nothing it draws lands in another's
 * pixels; what the PS2 read through an overlap (the Z test against the copied colour bytes after the
 * sway) is the one difference a boot may show.  Not part of the PS2 build. */
#ifndef KH1_PS2
enum { KH1_RT_DISPLAY, KH1_RT_ZCOLOR, KH1_RT_MOVIE, KH1_RT_MAIN, KH1_RT_SLOT, KH1_RT_OFFSCREEN, KH1_RT_CLUT,
       KH1_RT_OTHER, KH1_RT_COUNT };
enum { KH1_DS_NONE, KH1_DS_MAIN, KH1_DS_SHADOW };

typedef struct {
    u8 id;        /* KH1_RT_* */
    u8 psm;       /* FRAME's PSM (the port's colour texture is RGBA8 for CT32 / CT24) */
    u8 wide;      /* 0 the PS2's width, 1 the view, 2 half the view (a capture) */
    u8 depth;     /* KH1_DS_*: the depth buffer bound */
    u8 zdrop;     /* the draw writes Z through a ZBUF the port does not bind */
    u16 fbp, fbw; /* FRAME's FBP and FBW (64-pixel units) */
    u32 w, h;     /* the GPU texture's size in pixels (scaled) */
    f32 ox, oy;   /* the margin: window pixel 0 is target pixel ox (unscaled) */
    f32 scale;
    s32 sx0, sy0, sx1, sy1; /* the scissor in target pixels, half-open */
    s32 ofx, ofy;           /* XYOFFSET (12.4) */
} KH1RenderPass;

/* the port target for FRAME's FBP, FBW and PSM (KH1_RT_*) */
u32 kh1_target_id(u32 fbp, u32 fbw, u32 psm);
/* the pass a draw renders in: FRAME, ZBUF, TEST, SCISSOR and XYOFFSET (lo / hi words), the canvas's view
 * (vx0, vw: kh1_canvas_fit's; 0 / 8192 for the PS2's 4:3) and the resolution scale */
void kh1_target_of(u32 frame_lo, u32 frame_hi, u32 zbuf_lo, u32 zbuf_hi, u32 test_lo, u32 scissor_lo,
                   u32 scissor_hi, u32 xyoffset_lo, u32 xyoffset_hi, const KH1Canvas *c, f32 scale,
                   KH1RenderPass *out);
/* GS primitive coordinates (12.4) to the target's pixels */
void kh1_target_map(const KH1RenderPass *p, s32 gx, s32 gy, f32 *px, f32 *py);
/* ... and to normalised device coordinates, -1 .. 1 across the target (y down, as the GS's) */
void kh1_target_ndc(const KH1RenderPass *p, s32 gx, s32 gy, f32 *nx, f32 *ny);
/* nonzero when two port targets (KH1_RT_*, or KH1_RT_COUNT + KH1_DS_* for a depth buffer) share GS
 * blocks on the PS2 */
int kh1_target_alias(u32 a, u32 b);
#endif

#endif
