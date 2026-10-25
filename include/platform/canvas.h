#ifndef PLATFORM_CANVAS_H
#define PLATFORM_CANVAS_H

/* The 2D canvas on a port's screen (docs/renderer-spec.md 5.3 step 1, 5.4 "Session 93"): port maths,
 * not game code.  Every GIF-path draw writes GS coordinates in 1/16 pixels of the 512 x 384 target
 * with its top left at (0x7000, 0x7400); a port draws them through one affine map, the canvas scaled
 * to the screen's height (its width when the screen is narrower than 4:3) and centred:
 *     screen x = (X / 16 - 1792) * s + ox,  screen y = (Y / 16 - 1856) * s + oy.
 * At 960 x 544: s = 1.4167, ox = 117.3 (the pillarbox), oy = 0.  The same map serves the wide view
 * (KH1_HOST_WIDE): what is drawn left of canvas 0 or right of 512 lands in the bars.  The view is the
 * whole screen in canvas units, x0 .. x0 + w (sixteenths: -1325 .. 9517 at 960 x 544), the margin
 * the HUD's anchors move by (include/platform/hudanchor.h).
 *
 * The full-screen rules (5.4 "Session 93"): a static full-screen packet's X from canvas 0 .. 512
 * stretched to the view (kh1_canvas_stretch_x), a texel u into a copy of the target or display
 * likewise (kh1_canvas_stretch_u: texels from the view's left edge), and a SCISSOR equal to the full
 * 4:3 canvas (or the display's 512 x 448), or one of the 16 32-pixel columns of the PS2's
 * texture-cache trick, read as the whole view or the view's column (kh1_canvas_scissor).  Not part
 * of the PS2 build. */
#ifndef KH1_PS2
typedef struct {
    f32 s;      /* screen pixels per canvas pixel */
    f32 ox, oy; /* the screen position of canvas (0, 0) */
    s32 vx0;    /* the view's left edge in canvas sixteenths (0 when the screen is 4:3 or narrower) */
    s32 vw;     /* the view's width in canvas sixteenths (8192 = 512 pixels at 4:3) */
} KH1Canvas;

/* the canvas centred on a screen_w x screen_h screen */
void kh1_canvas_fit(KH1Canvas *c, f32 screen_w, f32 screen_h);
/* GS X / Y (12.4, the target's origin at 0x7000 / 0x7400) to screen pixels */
void kh1_canvas_map(const KH1Canvas *c, s32 gx, s32 gy, f32 *sx, f32 *sy);
/* a full-screen packet's X (GS 12.4) from canvas 0 .. 512 to the view's x0 .. x0 + w (sixteenths) */
s32 kh1_canvas_stretch_x(s32 gx, s32 x0, s32 w);
/* a texel u (10.4) into a copy of the target: 0 .. 512 to 0 .. w / 16 */
s32 kh1_canvas_stretch_u(s32 u, s32 w);
/* SCISSOR's x range (SCAX0 / SCAX1 in its low word, SCAY0 / SCAY1 in its high one) in canvas
 * sixteenths, half-open [*x0, *x1): the full 4:3 canvas (0 .. 511 x 0 .. 383, or the display's
 * 0 .. 447) is the whole view, a column 32k .. 32k + 31 of the target's full height the view's column
 * k of 16; returns 1 then, else 0 with the register's own range */
int kh1_canvas_scissor(u32 lo, u32 hi, s32 x0, s32 w, s32 *sx0, s32 *sx1);
#endif

#endif
