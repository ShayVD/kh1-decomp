#ifndef PLATFORM_VIEW_H
#define PLATFORM_VIEW_H

/* The 3D view's visible x range in the 2D canvas's target pixels (docs/renderer-spec.md 5.4).
 * The PS2 shows 0..512 of the 512 x 384 target.  A port with a wider screen keeps the vertical
 * view (hor+) and widens the frustum by one constant (host/port/view.c, func_00110618), and the
 * code that hides 2D parts off the 4:3 screen reads these instead of 0 / 512 (objwin.nostrict.c
 * func_0010b390; hudmath.c's bounds are data, set by kh1_view_init). */
#ifdef KH1_PS2
#define PLAT_VIEW_X0 0
#define PLAT_VIEW_X1 512
#define PLAT_VIEW_SIDE16 0
#define PLAT_VIEW_SIDE 0.0f
#else
/* Session 95: one convention for the margin.  kh1_view_side16 is the view's margin past each 4:3
 * edge in sixteenths of a canvas pixel (the GS's 12.4 unit), rounded once by kh1_view_init: 1325
 * (82.8125 px) at 960 x 544, the same number the full-screen stretch, the HUD's anchors, the scissor
 * rule and the present use (host/port/canvas.c kh1_canvas_fit, host/null/plat_null.c).  Every
 * other form below is exact in it, so the C passes and the stretched static packets meet on the
 * same sixteenth at both edges. */
extern s32 kh1_view_side16;
#define PLAT_VIEW_SIDE16 kh1_view_side16
#define PLAT_VIEW_X0 (-kh1_view_side16 / 16.0f)
#define PLAT_VIEW_X1 (512.0f + kh1_view_side16 / 16.0f)
/* the view's margin in canvas pixels as a float (82.8125 at 960 x 544; 0.0f on the PS2).  The lens
 * grid (sceneeff.c func_00103c48) reads its copy of the target, which starts at the view's left
 * edge, at u 64 .. 448 of the 4:3 canvas: the margin moves its ST back onto the same pixels. */
#define PLAT_VIEW_SIDE (kh1_view_side16 / 16.0f)
/* the view's width over the PS2's 4:3 (1.0 there; KH1_HOST_WIDE sets it), and the start-up call
 * that applies it (host/port/view.c) */
extern f32 kh1_view_wide;
void kh1_view_init(f32 aspect);
#endif

/* Session 92: the full-screen passes built in C (renderer-spec 5.4 "Session 92"): the clear, fades,
 * flash, blurs, sway and spin cover the whole view, not the 4:3 canvas.  PLAT_VIEW_W16 is the view's
 * width in canvas sixteenths (8192 on the PS2); PLAT_VIEW_GX0 / GX1 its left / right edge in GS units
 * (12.4 with XYOFFSET's 0x7000 origin: 0x7000 / 0x9000 on the PS2, where every use folds to the
 * literal the original has).  A copy of the target is addressed in texels from the view's left
 * edge, so a texel range 0 .. 512 (sixteenths 0 .. 8192) becomes 0 .. PLAT_VIEW_W16. */
#define PLAT_VIEW_W16 (8192 + 2 * PLAT_VIEW_SIDE16)
#define PLAT_VIEW_GX0 (0x7000 - PLAT_VIEW_SIDE16)
#define PLAT_VIEW_GX1 (0x9000 + PLAT_VIEW_SIDE16)

#endif
