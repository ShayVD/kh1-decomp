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
#else
extern s32 kh1_view_x0, kh1_view_x1;
#define PLAT_VIEW_X0 kh1_view_x0
#define PLAT_VIEW_X1 kh1_view_x1
/* the view's width over the PS2's 4:3 (1.0 there; KH1_HOST_WIDE sets it), and the start-up call
 * that applies it (host/port/view.c) */
extern f32 kh1_view_wide;
void kh1_view_init(f32 aspect);
#endif

#endif
