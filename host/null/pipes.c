/* KH1_HOST_TRACE=5 (session 123, docs/renderer-spec.md 4.13 "Session 123"): every draw state a send drew
 * in (host/null/gsregs.c's KH1GsDraw, as the trace's draw lines give them) turned into the port's whole
 * draw state (include/platform/drawstate.h) and counted: how many GPU pipelines, fragment shaders and
 * sampler objects the run needed.  kh1_pipes_report prints the totals and one line per pipeline at the
 * run's end (main.c's summary), then each render target host/null/gsmem.c saw with the port target it is
 * (include/platform/target.h: KH1_RT_*, or a depth buffer).  Reads the register file only.
 *
 * Session 124 (renderer-spec 4.13 "Session 124"): kh1_pipes_prim, at each drawing kick (gsregs.c's
 * kh1_gs_prim_hook), cuts the run's primitives into GPU batches (include/platform/batch.h) with the
 * registers in force, and kh1_pipes_frame ends a frame (main.c's vblank): the report's `batches:` lines give
 * the draw calls a frame takes.  Not part of the PS2 build. */
#include "common.h"
#include "gsregs.h"
#include "gsmem.h"
#include "platform/drawstate.h"
#include "platform/target.h"
#include "platform/batch.h"
#include "platform/vertex.h"
#include "platform/canvas.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

static KH1PipeSet set;
static u32 draws_seen;
static KH1Batcher batcher;

int memcmp(const void *, const void *, __SIZE_TYPE__);

const KH1Batcher *kh1_pipes_batcher(void) { return &batcher; }

/* the registers of the last kick's state, its draw state and pass (most kicks repeat the last one's) */
static KH1DrawRegs last_r;
static u32 last_scissor[2], last_xfer;
static int have_last;
static KH1DrawState last_d;
static KH1RenderPass last_p;

void kh1_pipes_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state) {
    static const KH1Canvas c43 = { 1.0f, 0.0f, 0.0f, 0, 8192 };
    const KH1GsState *gs = kh1_gs_state();
    const KH1GsContext *c = &gs->ctx[prim >> 9 & 1];
    const KH1GsMemStats *ms = kh1_gsmem_stats();
    u32 xfer = ms->uploads + ms->copies + ms->clut_loads;
    KH1DrawRegs r;
    (void)v;
    (void)state;
    memset(&r, 0, sizeof r);
    r.prim = prim;
    r.frame_lo = c->frame.lo;
    r.frame_hi = c->frame.hi;
    r.zbuf_lo = c->zbuf.lo;
    r.zbuf_hi = c->zbuf.hi;
    r.test_lo = c->test.lo;
    r.alpha_lo = c->alpha.lo;
    r.alpha_hi = c->alpha.hi;
    r.tex0_lo = c->tex0.lo;
    r.tex0_hi = c->tex0.hi;
    r.tex1_lo = c->tex1.lo;
    r.tex1_hi = c->tex1.hi;
    r.clamp_lo = c->clamp.lo;
    r.clamp_hi = c->clamp.hi;
    r.fogcol = gs->fogcol.lo;
    r.texa_lo = gs->texa.lo;
    r.texa_hi = gs->texa.hi;
    if (have_last && xfer != last_xfer) kh1_batch_break(&batcher);
    last_xfer = xfer;
    if (!have_last || memcmp(&r, &last_r, sizeof r) || c->scissor.lo != last_scissor[0] ||
        c->scissor.hi != last_scissor[1]) {
        kh1_drawstate_of(&r, &last_d);
        kh1_target_of(c->frame.lo, c->frame.hi, c->zbuf.lo, c->zbuf.hi, c->test.lo, c->scissor.lo, c->scissor.hi,
                      c->xyoffset.lo, c->xyoffset.hi, &c43, 1.0f, &last_p);
        last_r = r;
        last_scissor[0] = c->scissor.lo;
        last_scissor[1] = c->scissor.hi;
        have_last = 1;
    }
    kh1_batch_prim(&batcher, &last_d, &last_p, (prim & 7) == 6 ? 6 : n);
}

void kh1_pipes_frame(void) { kh1_batch_frame(&batcher); }

void kh1_pipes_draw(const KH1GsDraw *g) {
    KH1DrawRegs r;
    KH1DrawState d;
    r.prim = g->prim;
    r.frame_lo = g->ctx.frame.lo;
    r.frame_hi = g->ctx.frame.hi;
    r.zbuf_lo = g->ctx.zbuf.lo;
    r.zbuf_hi = g->ctx.zbuf.hi;
    r.test_lo = g->ctx.test.lo;
    r.alpha_lo = g->ctx.alpha.lo;
    r.alpha_hi = g->ctx.alpha.hi;
    r.tex0_lo = g->ctx.tex0.lo;
    r.tex0_hi = g->ctx.tex0.hi;
    r.tex1_lo = g->ctx.tex1.lo;
    r.tex1_hi = g->ctx.tex1.hi;
    r.clamp_lo = g->ctx.clamp.lo;
    r.clamp_hi = g->ctx.clamp.hi;
    r.fogcol = g->fogcol.lo;
    r.texa_lo = g->texa.lo;
    r.texa_hi = g->texa.hi;
    kh1_drawstate_of(&r, &d);
    kh1_pipeset_add(&set, &d);
    draws_seen += g->draws;
}

/* gsmem.c's render targets as port targets (an "OTHER" or an unknown depth buffer is a new kind) */
static void report_targets(void) {
    static const char *names[] = { "display", "Z area as colour", "movie frame", "3D target", "slot capture",
                                   "off-screen buffer", "CLUT pass", "OTHER" };
    static KH1GsTarget t[32];
    int n = kh1_gsmem_targets(t, 32), i;
    for (i = 0; i < n && i < 32; i++) {
        const char *what;
        if (t[i].psm >= 0x30)
            what = t[i].bp == 0xE00 && t[i].psm == 0x31 ? "the main depth" : t[i].bp == 0x3800 && t[i].psm == 0x3A
                   ? "the shadow depth" : "an UNKNOWN depth buffer";
        else
            what = names[kh1_target_id(t[i].bp / 32, t[i].bw, t[i].psm)];
        printf("kh1-host:   port target %d bp %04x bw %u psm %02x: %s\n", i + 1, t[i].bp, t[i].bw, t[i].psm, what);
    }
}

static void report_batches(void) {
    const KH1BatchCount *t = &batcher.total, *m = &batcher.max;
    u32 f = batcher.frames ? batcher.frames : 1;
    if (!batcher.frames) return;
    printf("kh1-host: batches: %u frames, %u batches, %u draw calls, %u primitives, %u GPU vertices (%u KB); a frame "
           "%.1f / %.1f draw calls / %.1f primitives on average, at most %u batches / %u draw calls / %u primitives / %u "
           "vertices\n", batcher.frames, t->batches, t->draws, t->prims, t->verts, (u32)((t->verts * 32ull + 1023) / 1024),
           (double)t->batches / f, (double)t->draws / f, (double)t->prims / f, m->batches, m->draws, m->prims, m->verts);
    printf("kh1-host:   batches opened by: %u render passes, %u pipelines, %u textures, %u uniforms, %u scissors, %u "
           "transfers (a frame at most %u passes, %u pipelines, %u textures)\n", t->passes, t->pipes, t->textures,
           t->uniforms, t->scissors, t->breaks, m->passes, m->pipes, m->textures);
}

void kh1_pipes_report(void) {
    u32 i, vmask, nv;
    if (batcher.frame.prims) kh1_batch_frame(&batcher); /* the last frame's primitives */
    report_batches();
    if (!set.states) return;
    printf("kh1-host: pipelines: %u draw states over the sends (%u primitives, %u draw nothing), %u GPU pipelines, %u fragment "
           "shaders, %u samplers%s\n", set.states, draws_seen, set.empty, set.npipe, set.nshader, set.nsampler,
           set.lost ? " (some past the table)" : "");
    for (i = 0; i < set.npipe; i++)
        printf("kh1-host:   pipe %u: %s (%u states)\n", i + 1, kh1_pipekey_str(&set.pipe[i]), set.pipe_uses[i]);
    /* session 124: the vertex shaders those pipelines use (include/platform/vertex.h) */
    nv = kh1_vertex_variants(&set, &vmask);
    printf("kh1-host:   %u vertex shaders:", nv);
    for (i = 0; i < 7; i++)
        if (vmask >> i & 1) printf(" [%s]", kh1_vertkey_str(i));
    printf("\n");
    report_targets();
}
