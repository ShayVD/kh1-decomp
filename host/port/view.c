/* The camera's six matrices, func_00110618 (display.c func_00110a48 calls it each frame), in C for
 * every port platform, and the wide view (docs/renderer-spec.md 5.4).  func_00110618 is still a
 * non-match; this is the maths of its near-miss draft (nonmatchings/session12/s12w6), in natural
 * order and checked against the original's code by tools/host/viewcheck.py (which runs the PS2
 * function's FPU code), so the host links it in place of the draft (tools/host/census.py
 * HOST_TWINS).  Not part of the PS2 build (it lives outside src/).
 *
 * The wide view: the x half-extent 320 (the 4:3 screen at scrz) becomes 320 * kh1_view_wide, so the
 * two frustums every CPU cull tests (D_002BBE60 / D_002BBEE0, as D_002BBFA0 / D_002BBFE0: the grid,
 * props, actors and bit 35, shadows, ppp effects, the party warp) widen together; the projection,
 * the y 229 and the guard box (2045 / 360.5) stay.  kh1_view_init also widens the markers' bounds
 * (hudmath.c's D_00469F90 / D_00469FA0) and objwin's (PLAT_VIEW_X0 / X1). */
#include "common.h"
#include "platform/view.h"

typedef f32 Mtx[4][4] __attribute__((aligned(16)));
void sceVu0UnitMatrix(Mtx);
void sceVu0MulMatrix(Mtx, Mtx, Mtx);

f32 kh1_view_wide = 1.0f;
s32 kh1_view_x0 = 0, kh1_view_x1 = 512;
extern f32 D_00469F90[4], D_00469FA0[4]; /* the markers' GS-pixel bounds: (1792, 1856, 0, 1), (2304, 2240, 0, 4e8) */

/* aspect: the screen's width over its height (960 / 544 on the Vita); 4 / 3 or less keeps the PS2's */
void kh1_view_init(f32 aspect) {
    f32 side;
    kh1_view_wide = aspect > 4.0f / 3.0f ? aspect * 3.0f / 4.0f : 1.0f;
    side = 256.0f * (kh1_view_wide - 1.0f); /* canvas pixels past each 4:3 edge: 82.8 at 960 x 544 */
    kh1_view_x0 = (s32)-side;
    kh1_view_x1 = 512 + (s32)side;
    D_00469F90[0] = 1792.0f - side;
    D_00469FA0[0] = 2304.0f + side;
}

/* the view -> clip matrix of a scrw x scrh screen at scrz, depth zmin .. zmax (sceVu0ViewClipMatrix's form) */
static void view_clip(Mtx m, f32 scrw, f32 scrh, f32 scrz, f32 zmin, f32 zmax) {
    sceVu0UnitMatrix(m);
    m[0][0] = 2.0f * scrz / scrw;
    m[1][1] = 2.0f * scrz / scrh;
    m[2][2] = (zmax + zmin) / (zmax - zmin);
    m[3][2] = zmax * zmin * -2.0f / (zmax - zmin);
    m[2][3] = 1.0f;
    m[3][3] = 0.0f;
}

/* the view -> screen matrix, depth near .. far to GS Z zmin .. zmax (sceVu0ViewScreenMatrix's form) */
static void view_screen(Mtx m, f32 scrz, f32 ax, f32 ay, f32 cx, f32 cy, f32 zmin, f32 zmax, f32 near, f32 far) {
    Mtx t;
    sceVu0UnitMatrix(m);
    m[0][0] = scrz;
    m[1][1] = scrz;
    m[2][2] = 0.0f;
    m[3][2] = 1.0f;
    m[2][3] = 1.0f;
    m[3][3] = 0.0f;
    sceVu0UnitMatrix(t);
    t[0][0] = ax;
    t[1][1] = ay;
    t[2][2] = far * near * (zmax - zmin) / (far - near);
    t[3][0] = cx;
    t[3][1] = cy;
    t[3][2] = (-zmax * near + zmin * far) / (far - near);
    sceVu0MulMatrix(m, t, m);
}

/* m0 / m2 view -> screen (far / fog far), m1 / m3 view -> clip of the screen (far / fog far), m4 the
 * guard box's view -> clip, m5 its clip -> screen (renderer-spec 5.4's table) */
void func_00110618(Mtx m0, Mtx m1, Mtx m2, Mtx m3, Mtx m4, Mtx m5, f32 scrz, f32 ax, f32 ay, f32 cx, f32 cy,
                   f32 zmin, f32 zmax, f32 near, f32 far, f32 fog) {
    f32 w = near * 320.0f * kh1_view_wide / scrz, h = near * 229.0f / scrz;
    f32 gw = near * 2045.0f / scrz, gh = near * 360.5f / scrz;
    view_screen(m2, scrz, ax, ay, cx, cy, zmin, zmax, near, fog);
    view_clip(m3, w * 2.0f, h * 2.0f, near, near, fog);
    view_screen(m0, scrz, ax, ay, cx, cy, zmin, zmax, near, far);
    view_clip(m1, w * 2.0f, h * 2.0f, near, near, far);
    view_clip(m4, gw * 2.0f, gh * 2.0f, near, near, far);
    sceVu0UnitMatrix(m5);
    m5[0][0] = scrz * ax * gw / near;
    m5[1][1] = scrz * ay * gh / near;
    m5[2][2] = (zmin - zmax) * 0.5f;
    m5[3][0] = cx;
    m5[3][1] = cy;
    m5[3][2] = (zmax + zmin) * 0.5f;
    m5[3][3] = 1.0f;
}
