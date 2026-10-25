/* The 2D canvas on a port's screen and the full-screen rules (include/platform/canvas.h,
 * docs/renderer-spec.md 5.3 step 1 and 5.4 "Session 93"): pure functions a renderer takes, checked by
 * tests/host/canvas_test.c.  The host's null GIF path uses the stretch and the scissor rule under
 * KH1_HOST_WIDE (host/null/gsregs.c).  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/canvas.h"

/* a * b / 8192 rounded half up, a floor division so a negative a (an X left of the canvas) rounds the
 * same way */
static s32 scale13(s32 a, s32 b) {
    s32 n = a * b + 4096;
    return n >= 0 ? n / 8192 : -((-n + 8191) / 8192);
}

void kh1_canvas_fit(KH1Canvas *c, f32 screen_w, f32 screen_h) {
    f32 sx = screen_w / 512.0f, sy = screen_h / 384.0f, side;
    c->s = sx < sy ? sx : sy;
    c->ox = (screen_w - 512.0f * c->s) * 0.5f;
    c->oy = (screen_h - 384.0f * c->s) * 0.5f;
    /* the bars in canvas pixels: 256 (k - 1) with k the screen's width over 4:3, as host/port/view.c's
     * kh1_view_init and the HUD's margin (82.8 = 1325 sixteenths at 960 x 544) */
    side = c->ox / c->s;
    c->vx0 = -(s32)(side * 16.0f + 0.5f);
    c->vw = 8192 - 2 * c->vx0;
}

void kh1_canvas_map(const KH1Canvas *c, s32 gx, s32 gy, f32 *sx, f32 *sy) {
    *sx = ((f32)gx / 16.0f - 1792.0f) * c->s + c->ox;
    *sy = ((f32)gy / 16.0f - 1856.0f) * c->s + c->oy;
}

s32 kh1_canvas_stretch_x(s32 gx, s32 x0, s32 w) { return 0x7000 + x0 + scale13(gx - 0x7000, w); }

s32 kh1_canvas_stretch_u(s32 u, s32 w) { return scale13(u, w); }

u32 kh1_canvas_stretch_clamp(u32 lo, s32 w) {
    s32 maxu = (s32)(lo >> 14 & 0x3FF), add = w - 8192;
    if ((lo & 3) != 2) return lo;
    maxu += add >= 0 ? (add + 8) / 16 : -((-add + 8) / 16);
    if (maxu > 1023) maxu = 1023;
    if (maxu < 0) maxu = 0;
    return (lo & ~(0x3FFu << 14)) | (u32)maxu << 14;
}

void kh1_canvas_unmap(const KH1Canvas *c, f32 sx, f32 sy, f32 *cx, f32 *cy) {
    *cx = (sx - c->ox) / c->s;
    *cy = (sy - c->oy) / c->s;
}

int kh1_canvas_scissor(u32 lo, u32 hi, s32 x0, s32 w, s32 *sx0, s32 *sx1) {
    u32 ax0 = lo & 0x7FF, ax1 = lo >> 16 & 0x7FF, ay0 = hi & 0x7FF, ay1 = hi >> 16 & 0x7FF, k;
    *sx0 = (s32)ax0 * 16;
    *sx1 = ((s32)ax1 + 1) * 16;
    if (ay0 != 0 || (ay1 != 383 && ay1 != 447)) return 0;
    if (ax0 == 0 && ax1 == 511) k = 16; /* the target's 384 lines or the display's 448 */
    else if (!(ax0 & 31) && ax1 == ax0 + 31 && ay1 == 383) k = ax0 >> 5;
    else return 0;
    if (k == 16) { /* the whole canvas: the whole view */
        *sx0 = x0;
        *sx1 = x0 + w;
    } else { /* column k: the view's column k, edges from the same map as the stretch */
        *sx0 = x0 + scale13((s32)k * 512, w);
        *sx1 = x0 + scale13((s32)(k + 1) * 512, w);
    }
    return 1;
}
