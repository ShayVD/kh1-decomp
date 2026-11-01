/* The GS register file the port keeps (docs/renderer-spec.md 5.1), the second step of the Vita's
 * GIF parser after host/null/dmawalk.c's packet reader: every A+D, PACKED and REGLIST write and
 * each GIF tag's PRE update the registers 5.1 keeps (per context where the GS has two), and each
 * vertex kick is counted against the draw state in force (the PRIM attributes, the context PRIM's
 * CTXT bit chooses, FOGCOL and TEXA).  The state lives across sends, as on the GS: the text windows
 * send a header and then their sprites, opdma's set-up packet heads the frame's lists.
 *
 * Only the GIF channel's packets and VIF1 DIRECT (PATH2) reach it: VU1's XGKICK output (renderer
 * A / B meshes, PATH1) is not modelled (a VU1 program start only marks context 2's FRAME / ZBUF as
 * drawn, kh1_gs_path1), nor the order the GIF arbitrates its three paths in, so on
 * the host a send's state is what the sends before it left, in send order.  Fed only while
 * KH1_HOST_TRACE >= 2 walks the chains; KH1_HOST_TRACE=5 prints each send's draws.
 * Session 83: a point-sampled textured SPRITE gsmem.c can draw (kh1_gsmem_sprite: the texture
 * animations' CLUT passes, renderer-spec 4.13) is drawn into the model's pixels instead of only
 * marking its FRAME as a render target. */
#include "common.h"
#include "gsregs.h"
#include "gsmem.h"
#include "platform/canvas.h"
#include "platform/fullscreen.h"
#include "platform/natdraw.h"

void *memset(void *, int, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);

#define DRAWS 256

static KH1GsState gs = { { 0, 0 }, { 1, 0 } };
static u32 gs_q = 0x3F800000; /* the PACKED Q (ST's third word), 1.0 at each GIF tag */
static KH1GsDraw draws[DRAWS];
static u32 ndraws, cur = ~0u; /* cur: the draw state of the last kick, ~0 once the state changes */
/* session 147: a state register written with the value it held (the Dive's VU1 kicks: a GIF tag's PRE PRIM per
 * strip of ~4 vertices) keeps cur; the next kick only redoes what the lookup did beyond the key, the render
 * target check (relook).  A view change since cur was found (view_moved) still makes it look again, as any write
 * did before */
static int relook, view_moved;
/* session 141 (the Vita's speed): the draw states by a hash of their key (the fields before kicks), where
 * every kick after a state write searched the list with memcmp; open addressing, index + 1 (0 empty) */
#define DRAW_SLOTS 512
#define DRAW_KEY ((unsigned long)&((KH1GsDraw *)0)->kicks) /* prim, ctx, fogcol, texa */
static u32 draw_hash[DRAWS];
static u16 draw_slot[DRAW_SLOTS];
static KH1GsVert vq[3]; /* the queued vertices (session 83: sprites; session 122: every field, the hook) */
/* session 135: a strip's first four vertices since its PRIM, for the present's quads (gs_quad) */
static KH1GsVert sv[4];
static u32 nsv;
void (*kh1_gs_prim_hook)(u32 prim, const KH1GsVert *v, u32 n, u32 state);
static s32 gs_xshift; /* added to each XYZ's X (session 92: the HUD's anchors, kh1_gs_xshift) */
static s32 gs_sx0, gs_sw; /* session 93: a full-screen packet's stretch (kh1_gs_xstretch), gs_sw 0 = none */
static u32 gs_swhat;
static s32 gs_vx0, gs_vw = 8192; /* session 93: the view the scissor rule reads (kh1_gs_view) */

/* the state before any write: 0, except PRMODECONT 1 (PRIM's attributes rule), what every
 * environment the game sends writes (renderer-spec 5.1) */
void kh1_gs_reset(void) {
    memset(&gs, 0, sizeof gs);
    kh1_gs_gen++;
    gs.prmodecont.lo = 1;
    gs_q = 0x3F800000;
    gs_xshift = 0;
    gs_sw = 0;
    gs_vx0 = 0;
    gs_vw = 8192;
    kh1_gs_clear_draws();
    kh1_gsmem_reset();
}

void kh1_gs_xshift(s32 sixteenths) { gs_xshift = sixteenths; }

void kh1_gs_xstretch(s32 x0, s32 w, u32 what) {
    gs_sx0 = x0;
    gs_sw = what ? w : 0;
    gs_swhat = what;
}

void kh1_gs_view(s32 x0, s32 w) {
    if (x0 != gs_vx0 || w != gs_vw) view_moved = 1;
    gs_vx0 = x0;
    gs_vw = w;
}

/* XYZ's X (bits 0-15, 12.4) stretched by a full-screen packet's stretch (session 93) and moved by the
 * shift in force, Y left */
static u32 gs_xs(u32 xy) {
    u32 x = xy;
    if (gs_sw && gs_swhat & (KH1_FS_X | KH1_FS_XS))
        x = (u32)kh1_canvas_stretch_x((s32)(xy & 0xFFFF), gs_swhat & KH1_FS_X ? gs_sx0 : 0, gs_sw);
    return (xy & 0xFFFF0000u) | ((x + (u32)gs_xshift) & 0xFFFF);
}

void kh1_gs_clear_draws(void) {
    ndraws = 0;
    cur = ~0u;
    memset(draw_slot, 0, sizeof draw_slot);
}

static u32 draw_key_hash(const KH1GsDraw *d) {
    const u32 *w = (const u32 *)d;
    u32 h = 2166136261u, i;
    for (i = 0; i < DRAW_KEY / 4; i++) h = (h ^ w[i]) * 16777619u;
    return h;
}

const KH1GsState *kh1_gs_state(void) { return &gs; }

int kh1_gs_draws(KH1GsDraw *out, int max) {
    int i;
    for (i = 0; i < (int)ndraws && i < max; i++) out[i] = draws[i];
    return ndraws;
}

/* POINT 1, LINE / LINESTRIP 2, TRIANGLE / TRISTRIP / TRIFAN 3, SPRITE 2, 7 reserved */
u32 kh1_gs_prim_verts(u32 type) {
    static const u8 n[8] = { 1, 2, 2, 3, 3, 3, 2, 0 };
    return n[type & 7];
}

/* the attributes in force: PRIM's, or PRMODE's when PRMODECONT is 0 (never seen, 5.1) */
static u32 gs_prim(void) {
    u32 p = gs.prim.lo & 0x7FF;
    if (!(gs.prmodecont.lo & 1)) p = (p & 7) | (gs.prmode.lo & 0x7F8);
    return p;
}

/* a SPRITE drawn into the model's pixels when gsmem.c can (kh1_gsmem_sprite), else 0; flat: session
 * 95's fill of an untextured one for the present instead (kh1_gsmem_flat_sprite, after the draw is marked) */
static int gs_sprite(u32 p, const KH1GsContext *c, int flat) {
    KH1GsSprite s;
    s.prim = p;
    s.frame_lo = c->frame.lo; s.frame_hi = c->frame.hi; s.zbuf_hi = c->zbuf.hi; s.test_lo = c->test.lo;
    s.alpha_lo = c->alpha.lo; s.alpha_hi = c->alpha.hi; s.tex0_lo = c->tex0.lo; s.tex0_hi = c->tex0.hi;
    s.tex1_lo = c->tex1.lo; s.clamp_lo = c->clamp.lo;
    s.xyoffset_lo = c->xyoffset.lo; s.xyoffset_hi = c->xyoffset.hi;
    s.scissor_lo = c->scissor.lo; s.scissor_hi = c->scissor.hi;
    s.texa_lo = gs.texa.lo; s.texa_hi = gs.texa.hi;
    s.xy[0] = vq[0].xy; s.xy[1] = vq[1].xy;
    s.uv[0] = vq[0].uv; s.uv[1] = vq[1].uv;
    s.rgba = vq[1].rgba;
    s.tests = 0;
    s.zbuf_lo = c->zbuf.lo; s.z = vq[1].z; s.f = vq[1].f; s.fogcol = gs.fogcol.lo;
    /* session 99: the model's buffers are the PS2's 512 wide with canvas 0 at pixel 0, so a stretched
     * copy of a buffer laid out like the target (u from the view's left edge, the renderer's) is read
     * back by the margin here, and every copy in the model reads the same canvas (renderer-spec 5.4
     * "Session 99"); a capture of its own (KH1_FS_UOWN) starts at its texel 0; the registers and the
     * trace keep the renderer's u */
    s.uorg = gs_sw && (gs_swhat & (KH1_FS_U | KH1_FS_UOWN)) == KH1_FS_U ? gs_sx0 : 0;
    s.quad = 0;
    return flat ? kh1_gsmem_flat_sprite(&s) : kh1_gsmem_sprite(&s);
}

/* Session 135: a TRISTRIP of four vertices that is an axis-aligned rectangle (v0 top left, v1 top right,
 * v2 bottom left, v3 bottom right, UV), as dktitle.x's menu text draws its lines (func_00f201c8: an
 * alpha fading to the right), filled for the present like a sprite with each pixel's colour
 * interpolated from the four (kh1_gsmem_flat_sprite's quad).  The GS's two Gouraud triangles give the
 * same colours for a gradient along one axis, the only kind the title draws.  0 when the strip is not
 * that shape. */
static int gs_quad(u32 p, const KH1GsContext *c) {
    KH1GsSprite t;
    u32 i;
    if ((sv[0].xy >> 16) != (sv[1].xy >> 16) || (sv[2].xy >> 16) != (sv[3].xy >> 16) ||
        (sv[0].xy & 0xFFFF) != (sv[2].xy & 0xFFFF) || (sv[1].xy & 0xFFFF) != (sv[3].xy & 0xFFFF) ||
        (sv[0].uv >> 16) != (sv[1].uv >> 16) || (sv[2].uv >> 16) != (sv[3].uv >> 16) ||
        (sv[0].uv & 0x3FFF) != (sv[2].uv & 0x3FFF) || (sv[1].uv & 0x3FFF) != (sv[3].uv & 0x3FFF))
        return 0;
    t.prim = (p & ~7u) | 6;
    t.frame_lo = c->frame.lo; t.frame_hi = c->frame.hi; t.zbuf_hi = c->zbuf.hi; t.test_lo = c->test.lo;
    t.alpha_lo = c->alpha.lo; t.alpha_hi = c->alpha.hi; t.tex0_lo = c->tex0.lo; t.tex0_hi = c->tex0.hi;
    t.tex1_lo = c->tex1.lo; t.clamp_lo = c->clamp.lo;
    t.xyoffset_lo = c->xyoffset.lo; t.xyoffset_hi = c->xyoffset.hi;
    t.scissor_lo = c->scissor.lo; t.scissor_hi = c->scissor.hi;
    t.texa_lo = gs.texa.lo; t.texa_hi = gs.texa.hi;
    t.xy[0] = sv[0].xy; t.xy[1] = sv[3].xy;
    t.uv[0] = sv[0].uv; t.uv[1] = sv[3].uv;
    t.rgba = sv[3].rgba;
    t.tests = 0;
    t.zbuf_lo = c->zbuf.lo; t.z = sv[3].z; t.f = sv[3].f; t.fogcol = gs.fogcol.lo;
    t.uorg = gs_sw && (gs_swhat & (KH1_FS_U | KH1_FS_UOWN)) == KH1_FS_U ? gs_sx0 : 0;
    t.quad = 1;
    for (i = 0; i < 4; i++) t.rgbav[i] = sv[i].rgba;
    return kh1_gsmem_flat_sprite(&t);
}

/* the draw record for the state in force (cur), found or made when a state write moved it */
static void gs_find(u32 p) {
    u32 i;
    KH1GsDraw d;
    if (cur == ~0u) {
        memset(&d, 0, sizeof d);
        d.prim = p;
        d.ctx = gs.ctx[p >> 9 & 1];
        /* only what the draw reads: the texture registers with TME, ALPHA with ABE, FOGCOL with
         * FGE (a renderer's pipeline key) */
        if (p >> 4 & 1) {
            d.texa = gs.texa;
        } else {
            memset(&d.ctx.tex0, 0, sizeof d.ctx.tex0);
            memset(&d.ctx.tex1, 0, sizeof d.ctx.tex1);
            memset(&d.ctx.clamp, 0, sizeof d.ctx.clamp);
        }
        if (!(p >> 6 & 1)) memset(&d.ctx.alpha, 0, sizeof d.ctx.alpha);
        if (p >> 5 & 1) d.fogcol = gs.fogcol;
        {
            u32 h = draw_key_hash(&d), sl = h & (DRAW_SLOTS - 1);
            for (i = ndraws; draw_slot[sl]; sl = (sl + 1) & (DRAW_SLOTS - 1)) {
                u32 j = draw_slot[sl] - 1u;
                if (draw_hash[j] == h && !memcmp(&draws[j], &d, DRAW_KEY)) { i = j; break; }
            }
            if (i == ndraws && ndraws < DRAWS) {
                draw_hash[ndraws] = h;
                draw_slot[sl] = (u16)(ndraws + 1);
            }
        }
        /* session 93: the scissor rule (a full 4:3 SCISSOR or one of the 16 columns is the view's) */
        if (!kh1_canvas_scissor(d.ctx.scissor.lo, d.ctx.scissor.hi, gs_vx0, gs_vw, &d.vx0, &d.vx1) ||
            (gs_vx0 == 0 && gs_vw == 8192))
            d.vx0 = d.vx1 = 0;
        d.x0 = d.y0 = 0x7FFFFFFF;
        d.x1 = d.y1 = -0x7FFFFFFF;
        if (i == ndraws && ndraws < DRAWS) draws[ndraws++] = d;
        cur = i < ndraws ? i : DRAWS;
        view_moved = 0;
        relook = 1;
    }
    if (relook) {
        relook = 0;
        /* a texture in drawn pages (a render target) is not the uploads' (host/null/gsmem.c) */
        if (cur < DRAWS && p >> 4 & 1 && !draws[cur].target)
            draws[cur].target = kh1_gsmem_tex_target(draws[cur].ctx.tex0.lo, draws[cur].ctx.tex0.hi);
    }
}

static void gs_kick(int draw, u32 xy, u32 z, u32 f) {
    u32 p = gs_prim(), need = kh1_gs_prim_verts(p), i;
    int fourth = 0;
    KH1GsDraw *k;
    gs_find(p);
    k = cur < DRAWS ? &draws[cur] : 0;
    if (k) k->kicks++;
    else gs.lost++;
    if (!need) return;
    if (k) { /* the extent (session 91, gsstate.py --extents): XYZ's 12.4 X / Y less XYOFFSET's */
        const KH1GsContext *c = &gs.ctx[p >> 9 & 1];
        s32 x = (s32)(xy & 0xFFFF) - (s32)(c->xyoffset.lo & 0xFFFF);
        s32 y = (s32)(xy >> 16) - (s32)(c->xyoffset.hi & 0xFFFF);
        if (x < k->x0) k->x0 = x;
        if (x > k->x1) k->x1 = x;
        if (y < k->y0) k->y0 = y;
        if (y > k->y1) k->y1 = y;
    }
    if (gs.nvert < need) {
        i = gs.nvert++;
    } else { /* a strip's next vertex: the queue moves up; session 122: a fan keeps its first vertex */
        for (i = (p & 7) == 5 ? 2 : 1; i < need; i++) vq[i - 1] = vq[i];
        i = need - 1;
    }
    vq[i].xy = xy;
    vq[i].z = z;
    vq[i].f = f;
    vq[i].uv = gs.uv.lo;
    vq[i].rgba = gs.rgbaq.lo;
    vq[i].q = gs.rgbaq.hi;
    vq[i].s = gs.st.lo;
    vq[i].t = gs.st.hi;
    if ((p & 7) == 4 && nsv < 4) { /* session 135: a strip's first four (gs_quad) */
        sv[nsv++] = vq[i];
        fourth = nsv == 4;
    }
    if (gs.nvert < need) return;
    if (draw && kh1_gs_prim_hook) kh1_gs_prim_hook(p, vq, need, cur);
    /* a full queue: XYZ2 / XYZF2 draw; the lists (POINT, LINE, TRIANGLE, SPRITE) start again,
     * the strips and the fan keep their last vertices */
    if (draw) {
        KH1GsContext *c = &gs.ctx[p >> 9 & 1];
        if (k) k->draws++;
        if ((p & 7) != 6 || !gs_sprite(p, c, 0)) {
            kh1_gsmem_draw(c->frame.lo, c->frame.hi, c->zbuf.lo, c->zbuf.hi, c->scissor.lo, c->scissor.hi, c->test.lo);
            if ((p & 7) == 6) gs_sprite(p, c, 1);
            /* session 135: the strip's second triangle completes a rectangle (the title's text) */
            if (fourth) gs_quad(p, c);
        }
    }
    i = p & 7;
    if (i == 0 || i == 1 || i == 3 || i == 6) gs.nvert = 0;
}

u32 kh1_gs_gen;

static void set(KH1GsReg *r, u32 lo, u32 hi) {
    if (r->lo == lo && r->hi == hi && cur != ~0u && !view_moved) {
        relook = 1;
        return;
    }
    if (r->lo != lo || r->hi != hi) kh1_gs_gen++;
    r->lo = lo;
    r->hi = hi;
    cur = ~0u;
}

void kh1_gs_write(u32 reg, u32 lo, u32 hi) {
    KH1GsContext *c = &gs.ctx[reg & 1];
    switch (reg) {
    case 0x00: set(&gs.prim, lo & 0x7FF, 0); gs.nvert = 0; nsv = 0; return;
    case 0x01: gs.rgbaq.lo = lo; gs.rgbaq.hi = hi; return;
    case 0x02: gs.st.lo = lo; gs.st.hi = hi; return;
    case 0x03: /* UV: a full-screen copy's u stretched with its X (session 93) */
        if (gs_sw && gs_swhat & KH1_FS_U) lo = (lo & ~0x3FFFu) | ((u32)kh1_canvas_stretch_u(lo & 0x3FFF, gs_sw) & 0x3FFF);
        gs.uv.lo = lo; gs.uv.hi = hi; return;
    case 0x0A: gs.fog.lo = lo; gs.fog.hi = hi; return;
    /* XYZF2 / XYZ2, XYZF3 / XYZ3 (a vertex, no drawing): XYZF's Z is 24 bits and its F the top byte,
     * XYZ's Z 32 bits with the FOG register's F */
    case 0x04: gs_kick(1, gs_xs(lo), hi & 0xFFFFFF, hi >> 24); return;
    case 0x05: gs_kick(1, gs_xs(lo), hi, gs.fog.hi >> 24); return;
    case 0x0C: gs_kick(0, gs_xs(lo), hi & 0xFFFFFF, hi >> 24); return;
    case 0x0D: gs_kick(0, gs_xs(lo), hi, gs.fog.hi >> 24); return;
    case 0x06: case 0x07: set(&gs.ctx[reg - 6].tex0, lo, hi); kh1_gsmem_tex0(lo, hi); return;
    case 0x08: case 0x09: /* session 94: the lens grid's REGION over a copy of the view's width */
        if (gs_sw && gs_swhat & KH1_FS_CLAMP) lo = kh1_canvas_stretch_clamp(lo, gs_sw);
        set(&gs.ctx[reg - 8].clamp, lo, hi);
        return;
    case 0x14: case 0x15: set(&c->tex1, lo, hi); return;
    case 0x16: case 0x17: /* TEX2: PSM and the CLUT fields (CBP, CPSM, CSM, CSA, CLD) of TEX0 */
        c = &gs.ctx[reg - 0x16];
        set(&c->tex0, (c->tex0.lo & ~0x03F00000u) | (lo & 0x03F00000u),
            (c->tex0.hi & 0x1Fu) | (hi & ~0x1Fu));
        kh1_gsmem_tex0(c->tex0.lo, c->tex0.hi);
        return;
    case 0x18: case 0x19: set(&gs.ctx[reg - 0x18].xyoffset, lo, hi); return;
    case 0x1A: set(&gs.prmodecont, lo, hi); return;
    case 0x1B: set(&gs.prmode, lo, hi); return;
    case 0x3B: set(&gs.texa, lo, hi); return;
    case 0x3D: set(&gs.fogcol, lo, hi); return;
    case 0x40: case 0x41: set(&gs.ctx[reg - 0x40].scissor, lo, hi); return;
    case 0x42: case 0x43: set(&gs.ctx[reg - 0x42].alpha, lo, hi); return;
    case 0x47: case 0x48: set(&gs.ctx[reg - 0x47].test, lo, hi); return;
    case 0x4C: case 0x4D: set(&gs.ctx[reg - 0x4C].frame, lo, hi); return;
    case 0x4E: case 0x4F: set(&gs.ctx[reg - 0x4E].zbuf, lo, hi); return;
    case 0x50: gs.bitbltbuf.lo = lo; gs.bitbltbuf.hi = hi; return;
    case 0x51: gs.trxpos.lo = lo; gs.trxpos.hi = hi; return;
    case 0x52: gs.trxreg.lo = lo; gs.trxreg.hi = hi; return;
    case 0x53: /* starts the transfer (host/null/gsmem.c, session 80) */
        gs.trxdir.lo = lo;
        gs.trxdir.hi = hi;
        kh1_gsmem_trxdir(lo & 3, gs.bitbltbuf.lo, gs.bitbltbuf.hi, gs.trxpos.lo, gs.trxpos.hi, gs.trxreg.lo,
                         gs.trxreg.hi);
        return;
    case 0x54: { /* HWREG: 64 bits of the upload's data (never seen) */
        u32 w[2];
        w[0] = lo;
        w[1] = hi;
        kh1_gsmem_image(w, 2);
        gs.dropped++;
        return;
    }
    /* dropped (5.1): TEXCLUT, SCANMSK, MIPTBP1/2, TEXFLUSH, DIMX, DTHE, COLCLAMP, PABE, FBA,
     * SIGNAL, FINISH, LABEL */
    case 0x1C: case 0x22: case 0x34: case 0x35: case 0x36: case 0x37: case 0x3F: case 0x44:
    case 0x45: case 0x46: case 0x49: case 0x4A: case 0x4B: case 0x60: case 0x61: case 0x62:
        gs.dropped++;
        return;
    }
    gs.unknown++;
}

void kh1_gs_packed(u32 desc, const u32 *q) {
    switch (desc & 15) {
    case 0x0: kh1_gs_write(0x00, q[0] & 0x7FF, 0); return;
    case 0x1: /* RGBA in four words' low bytes, the Q the last ST left */
        kh1_gs_write(0x01, (q[0] & 0xFF) | (q[1] & 0xFF) << 8 | (q[2] & 0xFF) << 16 | (q[3] & 0xFF) << 24, gs_q);
        return;
    case 0x2: gs_q = q[2]; kh1_gs_write(0x02, q[0], q[1]); return;
    case 0x3: kh1_gs_write(0x03, (q[0] & 0x3FFF) | (q[1] & 0x3FFF) << 16, 0); return;
    case 0x4: case 0xC: /* XYZF: Z 24 bits and F 8 bits from bits 4 up; ADC (bit 111) = XYZF3 */
        kh1_gs_write(desc == 0xC || q[3] >> 15 & 1 ? 0x0C : 0x04, (q[0] & 0xFFFF) | (q[1] & 0xFFFF) << 16,
                     (q[2] >> 4 & 0xFFFFFF) | (q[3] >> 4 & 0xFF) << 24);
        return;
    case 0x5: case 0xD: /* XYZ: Z 32 bits; ADC = XYZ3 */
        kh1_gs_write(desc == 0xD || q[3] >> 15 & 1 ? 0x0D : 0x05, (q[0] & 0xFFFF) | (q[1] & 0xFFFF) << 16, q[2]);
        return;
    case 0x6: case 0x7: case 0x8: case 0x9: kh1_gs_write(desc, q[0], q[1]); return;
    case 0xA: kh1_gs_write(0x0A, 0, (q[3] >> 4 & 0xFF) << 24); return;
    case 0xE: kh1_gs_write(q[2] & 0xFF, q[0], q[1]); return;
    case 0xF: return;
    }
    gs.unknown++; /* 0xB: reserved */
}

/* session 151: a TRISTRIP's vertices with the draw state found (each packet's first too) as one strip (kh1_gs_strip_hook): the same register
 * file, queue, extent, counts and GS memory marks as gs_kick a vertex, and the strip's triangles handed on at once.
 * Takes up to n vertices, returns how many */
void (*kh1_gs_strip_hook)(u32 prim, const u32 *d, u32 n, u32 nq);
static u32 strip_buf[KH1_GS_STRIP_MASK + KH1_GS_STRIP_MAX * 8];

static u32 gs_strip(const u32 *q, u32 n, u32 p) {
    KH1GsDraw *k = &draws[cur];
    KH1GsContext *c = &gs.ctx[p >> 9 & 1];
    KH1GsVert *v = (KH1GsVert *)(strip_buf + KH1_GS_STRIP_MASK);
    u32 *mask = strip_buf, nq = gs.nvert, nv = gs.nvert, m, i, t, nd = 0, quad = 0, rgba = 0;
    s32 ox = (s32)(c->xyoffset.lo & 0xFFFF), oy = (s32)(c->xyoffset.hi & 0xFFFF), x, y;
    s32 x0 = k->x0, x1 = k->x1, y0 = k->y0, y1 = k->y1;
    int stretch = gs_sw && gs_swhat & (KH1_FS_X | KH1_FS_XS); /* gs_xs's test, once */
    if (n > KH1_GS_STRIP_MAX - nq) n = KH1_GS_STRIP_MAX - nq;
    if (relook) { /* gs_kick's: a state write of the value it held (each packet's PRE PRIM) */
        relook = 0;
        if (p >> 4 & 1 && !k->target) k->target = kh1_gsmem_tex_target(k->ctx.tex0.lo, k->ctx.tex0.hi);
    }
    for (i = 0; i < KH1_GS_STRIP_MASK; i++) mask[i] = 0;
    for (i = 0; i < nq; i++) v[i] = vq[i];
    for (m = 0; m < n; m++, q += 12) {
        KH1GsVert *o = &v[t = nq + m];
        u32 xy = (q[8] & 0xFFFF) | (q[9] & 0xFFFF) << 16;
        xy = stretch ? gs_xs(xy) : (xy & 0xFFFF0000u) | ((xy + (u32)gs_xshift) & 0xFFFF);
        x = (s32)(xy & 0xFFFF) - ox;
        y = (s32)(xy >> 16) - oy;
        if (x < x0) x0 = x;
        if (x > x1) x1 = x;
        if (y < y0) y0 = y;
        if (y > y1) y1 = y;
        rgba = (q[4] & 0xFF) | (q[5] & 0xFF) << 8 | (q[6] & 0xFF) << 16 | (q[7] & 0xFF) << 24;
        o->xy = xy;
        o->z = q[10] >> 4 & 0xFFFFFF;
        o->f = q[11] >> 4 & 0xFF;
        o->uv = gs.uv.lo;
        o->rgba = rgba;
        o->s = q[0];
        o->t = q[1];
        o->q = q[2];
        if (nv < 3) nv++;
        if (nsv < 4) {
            sv[nsv++] = *o;
            if (nsv == 4 && nv == 3 && !(q[11] >> 15 & 1)) quad = t;
        }
        if (nv == 3 && !(q[11] >> 15 & 1)) { /* XYZF2 with a full queue draws; XYZF3 (ADC) only queues */
            mask[t >> 5] |= 1u << (t & 31);
            nd++;
        }
    }
    q -= 12;
    k->x0 = x0, k->x1 = x1, k->y0 = y0, k->y1 = y1;
    k->kicks += n;
    gs_q = q[2];
    gs.st.lo = q[0];
    gs.st.hi = q[1];
    gs.rgbaq.lo = rgba;
    gs.rgbaq.hi = q[2];
    for (i = 0; i < nv; i++) vq[i] = v[nq + n - nv + i];
    gs.nvert = nv;
    if (nd) {
        kh1_gs_strip_hook(p, strip_buf, nq + n, nq);
        k->draws += nd;
        if (quad) { /* the strip's fourth vertex drew: gs_kick's gs_quad after that draw */
            for (i = t = 0; i <= quad; i++) t += mask[i >> 5] >> (i & 31) & 1;
            kh1_gsmem_draw_n(c->frame.lo, c->frame.hi, c->zbuf.lo, c->zbuf.hi, c->scissor.lo, c->scissor.hi, c->test.lo, t);
            gs_quad(p, c);
            nd -= t;
        }
        kh1_gsmem_draw_n(c->frame.lo, c->frame.hi, c->zbuf.lo, c->zbuf.hi, c->scissor.lo, c->scissor.hi, c->test.lo, nd);
    }
    return n;
}

/* the native renderer (include/platform/natdraw.h): a strip of nv vertices the GPU transforms, so the model sees no
 * vertex.  The draw record is found as gs_kick finds it, counted, and given the scissor as its extent; GS memory marks
 * the target's (and Z's) pages drawn (kh1_gsmem_draw_n, as gs_strip does for its triangles); the vertex queue is left
 * empty (the next packet's PRE PRIM starts a new strip).  The PRIM in force, for the recorder */
u32 kh1_gs_native(u32 nv) {
    u32 p = gs_prim(), nd = nv > 2 ? nv - 2 : 0;
    KH1GsContext *c = &gs.ctx[p >> 9 & 1];
    KH1GsDraw *k;
    gs_find(p);
    k = cur < DRAWS ? &draws[cur] : 0;
    if (k) {
        s32 x0 = (s32)(c->scissor.lo & 0x7FF) * 16, x1 = (s32)(c->scissor.lo >> 16 & 0x7FF) * 16 + 15;
        s32 y0 = (s32)(c->scissor.hi & 0x7FF) * 16, y1 = (s32)(c->scissor.hi >> 16 & 0x7FF) * 16 + 15;
        k->kicks += nv;
        k->draws += nd;
        if (x0 < k->x0) k->x0 = x0;
        if (x1 > k->x1) k->x1 = x1;
        if (y0 < k->y0) k->y0 = y0;
        if (y1 > k->y1) k->y1 = y1;
    } else {
        gs.lost++;
    }
    gs.nvert = 0;
    nsv = 0;
    if (nd) kh1_gsmem_draw_n(c->frame.lo, c->frame.hi, c->zbuf.lo, c->zbuf.hi, c->scissor.lo, c->scissor.hi, c->test.lo, nd);
    return p;
}

s32 kh1_gs_xshift_of(void) { return gs_xshift; }

void (*kh1_gs_native_hook)(u32 what, u32 prim, const u32 *a, const u32 *b);

u32 kh1_gs_native_run(const u32 *d) {
    u32 nrec = d[1], r;
    const u32 *rec = d + 8;
    if (kh1_gs_native_hook) kh1_gs_native_hook(0, 0, d, d + (2 + d[3]) * 4);
    for (r = 0; r < nrec; r++) {
        u32 p;
        if (rec[1] >> 14 & 1) kh1_gs_write(0x00, rec[1] >> 15 & 0x7FF, 0); /* the GIF tag's PRE */
        p = kh1_gs_native(rec[2]);
        if (kh1_gs_native_hook) kh1_gs_native_hook(1, p, rec, 0);
        rec += KH1_NAT_REC_QW(rec) * 4;
    }
    if (kh1_gs_native_hook) kh1_gs_native_hook(2, 0, 0, 0);
    return nrec;
}

void kh1_gs_packed_stq_xyzf(const u32 *q, u32 n) {
    u32 xy, p;
    int draw;
    while (n) {
        p = gs_prim();
        if (kh1_gs_strip_hook && cur < DRAWS && (p & 7) == 4) {
            u32 m = gs_strip(q, n, p);
            n -= m;
            q += m * 12;
            continue;
        }
        n--;
        gs_q = q[2];
        gs.st.lo = q[0];
        gs.st.hi = q[1];
        gs.rgbaq.lo = (q[4] & 0xFF) | (q[5] & 0xFF) << 8 | (q[6] & 0xFF) << 16 | (q[7] & 0xFF) << 24;
        gs.rgbaq.hi = gs_q;
        /* XYZF2, or XYZF3 with ADC (no drawing): kh1_gs_write's 0x04 / 0x0C */
        draw = !(q[11] >> 15 & 1);
        xy = gs_xs((q[8] & 0xFFFF) | (q[9] & 0xFFFF) << 16);
        if (cur < DRAWS && !relook && gs.nvert == 3 && (p & 7) == 4 && nsv == 4) {
            /* session 150: a TRISTRIP's vertex past its first four with the state found (most of the VU1 kicks):
             * gs_kick's steps for that case only */
            KH1GsDraw *k = &draws[cur];
            KH1GsContext *c = &gs.ctx[p >> 9 & 1];
            s32 x = (s32)(xy & 0xFFFF) - (s32)(c->xyoffset.lo & 0xFFFF);
            s32 y = (s32)(xy >> 16) - (s32)(c->xyoffset.hi & 0xFFFF);
            k->kicks++;
            if (x < k->x0) k->x0 = x;
            if (x > k->x1) k->x1 = x;
            if (y < k->y0) k->y0 = y;
            if (y > k->y1) k->y1 = y;
            vq[0] = vq[1];
            vq[1] = vq[2];
            vq[2].xy = xy;
            vq[2].z = q[10] >> 4 & 0xFFFFFF;
            vq[2].f = q[11] >> 4 & 0xFF;
            vq[2].uv = gs.uv.lo;
            vq[2].rgba = gs.rgbaq.lo;
            vq[2].q = gs.rgbaq.hi;
            vq[2].s = gs.st.lo;
            vq[2].t = gs.st.hi;
            if (draw) {
                if (kh1_gs_prim_hook) kh1_gs_prim_hook(p, vq, 3, cur);
                k->draws++;
                kh1_gsmem_draw(c->frame.lo, c->frame.hi, c->zbuf.lo, c->zbuf.hi, c->scissor.lo, c->scissor.hi, c->test.lo);
            }
            q += 12;
            continue;
        }
        gs_kick(draw, xy, q[10] >> 4 & 0xFFFFFF, q[11] >> 4 & 0xFF);
        q += 12;
    }
}

void kh1_gs_path1(void) {
    KH1GsContext *c = &gs.ctx[1];
    gs.path1++;
    kh1_gsmem_draw(c->frame.lo, c->frame.hi, c->zbuf.lo, c->zbuf.hi, c->scissor.lo, c->scissor.hi, c->test.lo);
}

void kh1_gs_giftag(int pre, u32 prim) {
    gs_q = 0x3F800000;
    if (pre) kh1_gs_write(0x00, prim, 0);
}
