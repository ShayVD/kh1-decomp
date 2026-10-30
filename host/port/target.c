/* Render targets, the viewport and the scissor a port's GPU draws with (include/platform/target.h,
 * docs/renderer-spec.md 4.13 "Session 123"), checked by tests/host/target_test.c against host/null/
 * gsmem.c's target list.  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/target.h"

u32 kh1_target_id(u32 fbp, u32 fbw, u32 psm) {
    switch (fbp) {
    case 0x00: return fbw == 8 && psm == 0x01 ? KH1_RT_DISPLAY : KH1_RT_OTHER;
    case 0x70: return KH1_RT_ZCOLOR;
    case 0x8C: return KH1_RT_MOVIE;
    case 0xD0: return KH1_RT_MAIN;
    case 0x1B0: return fbw == 4 || fbw == 8 ? KH1_RT_SLOT : KH1_RT_OTHER;
    case 0x1D0: return KH1_RT_OFFSCREEN;
    case 0x1F0: return KH1_RT_CLUT;
    }
    return KH1_RT_OTHER;
}

static s32 iround(f32 v) { return v >= 0.0f ? (s32)(v + 0.5f) : -(s32)(-v + 0.5f); }
static u32 iceil(f32 v) { u32 n = (u32)v; return (f32)n < v ? n + 1 : n; }

void kh1_target_of(u32 frame_lo, u32 frame_hi, u32 zbuf_lo, u32 zbuf_hi, u32 test_lo, u32 scissor_lo,
                   u32 scissor_hi, u32 xyoffset_lo, u32 xyoffset_hi, const KH1Canvas *c, f32 scale,
                   KH1RenderPass *out) {
    u32 fbp = frame_lo & 0x1FF, fbw = frame_lo >> 16 & 63, psm = frame_lo >> 24 & 63, id = kh1_target_id(fbp, fbw, psm);
    u32 zte = test_lo >> 16 & 1, ztst = test_lo >> 17 & 3, zwrite = zte && ztst && !(zbuf_hi & 1);
    u32 zbp = zbuf_lo & 0x1FF, zpsm = 0x30 | (zbuf_lo >> 24 & 15), ds = KH1_DS_NONE, rows, gw;
    s32 vx0 = c->vx0, vw = c->vw, sx0, sx1, sy0, sy1;
    f32 w;
    (void)frame_hi;
    out->id = (u8)id;
    out->psm = (u8)psm;
    out->fbp = (u16)fbp;
    out->fbw = (u16)fbw;
    out->scale = scale;
    out->ofx = (s32)(xyoffset_lo & 0xFFFF);
    out->ofy = (s32)(xyoffset_hi & 0xFFFF);
    out->oy = 0.0f;
    out->wide = 0;
    gw = fbw * 64;
    rows = (scissor_hi >> 16 & 0x7FF) + 1;
    switch (id) {
    case KH1_RT_DISPLAY: out->wide = 1; rows = 448; break;
    case KH1_RT_ZCOLOR: out->wide = 1; rows = 384; break;
    case KH1_RT_MOVIE: gw = 640; rows = 448; break;
    case KH1_RT_MAIN: out->wide = 1; rows = 384; break;
    case KH1_RT_SLOT: out->wide = 2; rows = 192; break;
    case KH1_RT_OFFSCREEN: gw = 256; rows = 256; break;
    }
    /* a slot draw away from the canvas's origin (the shadow's window copy, XYOFFSET 0x7800) is a buffer of its own,
     * not a capture of the view: no margin */
    if (out->wide == 2 && out->ofx != 0x7000) { vx0 = 0; vw = 8192; }
    if (out->wide == 1) { out->ox = -vx0 / 16.0f; w = vw / 16.0f; }
    else if (out->wide == 2) { out->ox = -vx0 / 32.0f; w = vw / 32.0f; }
    else { out->ox = 0.0f; w = (f32)gw; }
    out->w = iceil(w * scale);
    out->h = iceil((f32)rows * scale);
    /* the depth buffer: the main one with the 3D target, the shadow's with the off-screen buffer */
    if (zte && ztst && (ztst != 1 || zwrite)) {
        if (id == KH1_RT_MAIN && zbp == 0x70 && zpsm == 0x31) ds = KH1_DS_MAIN;
        else if (id == KH1_RT_OFFSCREEN && zbp == 0x1C0 && zpsm == 0x3A) ds = KH1_DS_SHADOW;
    }
    out->depth = (u8)ds;
    out->zdrop = zwrite && ds == KH1_DS_NONE;
    /* the scissor: canvas.h's rule under a wide view, the margin, whole pixels, clipped */
    if (out->wide && kh1_canvas_scissor(scissor_lo, scissor_hi, vx0, vw, &sx0, &sx1)) {
        if (out->wide == 2) { sx0 /= 2; sx1 /= 2; }
    } else {
        sx0 = (s32)(scissor_lo & 0x7FF) * 16;
        sx1 = ((s32)(scissor_lo >> 16 & 0x7FF) + 1) * 16;
    }
    sy0 = (s32)(scissor_hi & 0x7FF) * 16;
    sy1 = ((s32)(scissor_hi >> 16 & 0x7FF) + 1) * 16;
    out->sx0 = iround((sx0 / 16.0f + out->ox) * scale);
    out->sx1 = iround((sx1 / 16.0f + out->ox) * scale);
    out->sy0 = iround(sy0 / 16.0f * scale);
    out->sy1 = iround(sy1 / 16.0f * scale);
    if (out->sx0 < 0) out->sx0 = 0;
    if (out->sy0 < 0) out->sy0 = 0;
    if (out->sx1 > (s32)out->w) out->sx1 = (s32)out->w;
    if (out->sy1 > (s32)out->h) out->sy1 = (s32)out->h;
}

void kh1_target_map(const KH1RenderPass *p, s32 gx, s32 gy, f32 *px, f32 *py) {
    *px = ((gx - p->ofx) / 16.0f + p->ox) * p->scale;
    *py = ((gy - p->ofy) / 16.0f + p->oy) * p->scale;
}

void kh1_target_ndc(const KH1RenderPass *p, s32 gx, s32 gy, f32 *nx, f32 *ny) {
    f32 x, y;
    kh1_target_map(p, gx, gy, &x, &y);
    *nx = x / (f32)p->w * 2.0f - 1.0f;
    *ny = y / (f32)p->h * 2.0f - 1.0f;
}

int kh1_target_alias(u32 a, u32 b) {
    enum { ZMAIN = KH1_RT_COUNT + KH1_DS_MAIN, ZSHADOW = KH1_RT_COUNT + KH1_DS_SHADOW };
    static const u8 pairs[][2] = {
        { KH1_RT_ZCOLOR, ZMAIN },          /* the Z area drawn as colour */
        { KH1_RT_MOVIE, ZMAIN },           /* 640 x 448 CT24 from 0x1180 runs through the Z area */
        { KH1_RT_MOVIE, KH1_RT_ZCOLOR },
        { KH1_RT_MOVIE, KH1_RT_MAIN },     /* ... into the 3D target's first blocks */
        { KH1_RT_SLOT, KH1_RT_OFFSCREEN }, /* the depth blur's 512 x 192 capture */
        { KH1_RT_SLOT, ZSHADOW },          /* Z16S at 0x3800, the slot's upper half */
    };
    u32 i;
    for (i = 0; i < sizeof pairs / sizeof pairs[0]; i++)
        if ((pairs[i][0] == a && pairs[i][1] == b) || (pairs[i][0] == b && pairs[i][1] == a)) return 1;
    return 0;
}
