/* The GS register file the port keeps (docs/renderer-spec.md 5.1), the second step of the Vita's
 * GIF parser after host/null/dmawalk.c's packet reader: every A+D, PACKED and REGLIST write and
 * each GIF tag's PRE update the registers 5.1 keeps (per context where the GS has two), and each
 * vertex kick is counted against the draw state in force (the PRIM attributes, the context PRIM's
 * CTXT bit chooses, FOGCOL and TEXA).  The state lives across sends, as on the GS: the text windows
 * send a header and then their sprites, opdma's set-up packet heads the frame's lists.
 *
 * Only the GIF channel's packets and VIF1 DIRECT (PATH2) reach it: VU1's XGKICK output (renderer
 * A / B meshes, PATH1) is not modelled, nor the order the GIF arbitrates its three paths in, so on
 * the host a send's state is what the sends before it left, in send order.  Fed only while
 * KH1_HOST_TRACE >= 2 walks the chains; KH1_HOST_TRACE=5 prints each send's draws. */
#include "common.h"
#include "gsregs.h"

void *memset(void *, int, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);

#define DRAWS 256

static KH1GsState gs = { { 0, 0 }, { 1, 0 } };
static u32 gs_q = 0x3F800000; /* the PACKED Q (ST's third word), 1.0 at each GIF tag */
static KH1GsDraw draws[DRAWS];
static u32 ndraws, cur = ~0u; /* cur: the draw state of the last kick, ~0 once the state changes */

/* the state before any write: 0, except PRMODECONT 1 (PRIM's attributes rule), what every
 * environment the game sends writes (renderer-spec 5.1) */
void kh1_gs_reset(void) {
    memset(&gs, 0, sizeof gs);
    gs.prmodecont.lo = 1;
    gs_q = 0x3F800000;
    kh1_gs_clear_draws();
}

void kh1_gs_clear_draws(void) {
    ndraws = 0;
    cur = ~0u;
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

static void gs_kick(int draw) {
    u32 p = gs_prim(), need = kh1_gs_prim_verts(p), i;
    KH1GsDraw d, *k;
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
        for (i = 0; i < ndraws; i++)
            if (!memcmp(&draws[i], &d, (char *)&d.kicks - (char *)&d)) break;
        if (i == ndraws && ndraws < DRAWS) draws[ndraws++] = d;
        cur = i < ndraws ? i : DRAWS;
    }
    k = cur < DRAWS ? &draws[cur] : 0;
    if (k) k->kicks++;
    else gs.lost++;
    if (!need) return;
    if (gs.nvert < need) gs.nvert++;
    if (gs.nvert < need) return;
    /* a full queue: XYZ2 / XYZF2 draw; the lists (POINT, LINE, TRIANGLE, SPRITE) start again,
     * the strips and the fan keep their last vertices */
    if (draw && k) k->draws++;
    i = p & 7;
    if (i == 0 || i == 1 || i == 3 || i == 6) gs.nvert = 0;
}

static void set(KH1GsReg *r, u32 lo, u32 hi) {
    r->lo = lo;
    r->hi = hi;
    cur = ~0u;
}

void kh1_gs_write(u32 reg, u32 lo, u32 hi) {
    KH1GsContext *c = &gs.ctx[reg & 1];
    switch (reg) {
    case 0x00: set(&gs.prim, lo & 0x7FF, 0); gs.nvert = 0; return;
    case 0x01: gs.rgbaq.lo = lo; gs.rgbaq.hi = hi; return;
    case 0x02: gs.st.lo = lo; gs.st.hi = hi; return;
    case 0x03: gs.uv.lo = lo; gs.uv.hi = hi; return;
    case 0x0A: gs.fog.lo = lo; gs.fog.hi = hi; return;
    case 0x04: case 0x05: gs_kick(1); return;  /* XYZF2 / XYZ2 */
    case 0x0C: case 0x0D: gs_kick(0); return;  /* XYZF3 / XYZ3: a vertex, no drawing */
    case 0x06: case 0x07: set(&gs.ctx[reg - 6].tex0, lo, hi); return;
    case 0x08: case 0x09: set(&gs.ctx[reg - 8].clamp, lo, hi); return;
    case 0x14: case 0x15: set(&c->tex1, lo, hi); return;
    case 0x16: case 0x17: /* TEX2: PSM and the CLUT fields (CBP, CPSM, CSM, CSA, CLD) of TEX0 */
        c = &gs.ctx[reg - 0x16];
        set(&c->tex0, (c->tex0.lo & ~0x03F00000u) | (lo & 0x03F00000u),
            (c->tex0.hi & 0x1Fu) | (hi & ~0x1Fu));
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
    case 0x53: gs.trxdir.lo = lo; gs.trxdir.hi = hi; return;
    /* dropped (5.1): TEXCLUT, SCANMSK, MIPTBP1/2, TEXFLUSH, DIMX, DTHE, COLCLAMP, PABE, FBA,
     * HWREG, SIGNAL, FINISH, LABEL */
    case 0x1C: case 0x22: case 0x34: case 0x35: case 0x36: case 0x37: case 0x3F: case 0x44:
    case 0x45: case 0x46: case 0x49: case 0x4A: case 0x4B: case 0x54: case 0x60: case 0x61: case 0x62:
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

void kh1_gs_giftag(int pre, u32 prim) {
    gs_q = 0x3F800000;
    if (pre) kh1_gs_write(0x00, prim, 0);
}
