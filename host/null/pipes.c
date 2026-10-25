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
 * the draw calls a frame takes; session 125: with each primitive's vertex signature, so a column copy's repeats
 * merge (batch.h's column groups).  Session 126 (renderer-spec 4.13 "Session 126"): the batcher is a command
 * recorder's (include/platform/cmdbuf.h): each kick's GPU vertices (primasm.h, vertex.h) go into the per-frame
 * rings, and each frame's render passes get their load / store needs; the report adds `commands:` and `passes:`
 * lines and each distinct frame's pass list.  Not part of the PS2 build. */
#include "common.h"
#include "gsregs.h"
#include "gsmem.h"
#include "platform/drawstate.h"
#include "platform/target.h"
#include "platform/batch.h"
#include "platform/vertex.h"
#include "platform/canvas.h"
#include "platform/ring.h"
#include "platform/cmdbuf.h"
#include "platform/primasm.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

static KH1PipeSet set;
static u32 draws_seen;
static KH1CmdRec *rec;
#define batcher (rec->b)
void *malloc(__SIZE_TYPE__);

/* session 126: the recorder and its two rings, made at the first kick (only KH1_HOST_TRACE=5 runs use them) */
static KH1CmdRec *recorder(void) {
    if (!rec) {
        rec = (KH1CmdRec *)malloc(sizeof *rec);
        kh1_cmd_init(rec, malloc(KH1_RING_FRAMES * KH1_RING_VERTEX_BYTES), KH1_RING_VERTEX_BYTES,
                     malloc(KH1_RING_FRAMES * KH1_RING_UNIFORM_BYTES), KH1_RING_UNIFORM_BYTES);
    }
    return rec;
}

int memcmp(const void *, const void *, __SIZE_TYPE__);

const KH1Batcher *kh1_pipes_batcher(void) { return &recorder()->b; }
const KH1CmdRec *kh1_pipes_recorder(void) { return recorder(); }

/* the registers of the last kick's state, its draw state and pass (most kicks repeat the last one's) */
static KH1DrawRegs last_r;
static u32 last_scissor[2], last_xfer;
static int have_last;
static KH1DrawState last_d;
static KH1RenderPass last_p;

/* session 125: the primitive's vertex signature for batch.h's column groups (FNV-1a over the type and the
 * queued vertices; never 0) */
static u32 prim_sig(u32 prim, const KH1GsVert *v, u32 n) {
    const u8 *q = (const u8 *)v;
    u32 h = 2166136261u ^ (prim & 7), i;
    h *= 16777619u;
    for (i = 0; i < n * sizeof *v; i++) h = (h ^ q[i]) * 16777619u;
    return h | 1;
}

void kh1_pipes_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state) {
    static const KH1Canvas c43 = { 1.0f, 0.0f, 0.0f, 0, 8192 };
    const KH1GsState *gs = kh1_gs_state();
    const KH1GsContext *c = &gs->ctx[prim >> 9 & 1];
    const KH1GsMemStats *ms = kh1_gsmem_stats();
    u32 xfer = ms->uploads + ms->copies + ms->clut_loads;
    KH1DrawRegs r;
    KH1PrimAsm pa;
    KH1PaVert out[6];
    KH1GpuVert gv[6];
    KH1VertCtx vc;
    u32 i, nv = 0, t = prim & 7;
    (void)state;
    recorder();
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
    if (have_last && xfer != last_xfer) kh1_cmd_break(rec);
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
    /* session 126: the primitive's GPU vertices: a fresh list of its type (a strip's or fan's kick is one triangle
     * of the vertices the hook gives) through primasm.h and vertex.h */
    memset(&pa, 0, sizeof pa);
    kh1_pa_prim(&pa, (prim & ~7u) | (t == 2 ? 1 : t == 4 || t == 5 ? 3 : t));
    for (i = 0; i < n; i++) nv = kh1_pa_vertex(&pa, (const KH1PaVert *)&v[i], 1, out);
    kh1_vertex_ctx(&vc, &last_p, c->zbuf.lo, prim, c->tex0.lo, c->tex0.hi);
    kh1_vertex_of(&vc, out, nv, gv);
    kh1_cmd_prim(rec, &last_d, &last_p, gv, t == 6 ? 6 : n, prim_sig(prim, v, n));
}

/* session 126: called with the frame's commands before they are cleared (tests/host/cmdbuf_test.c) */
void (*kh1_pipes_frame_hook)(const KH1CmdRec *r);

/* session 126: each distinct pass list (by targets, loads and stores) printed once, up to 32 */
static u32 seq_sig[32], nseq, seq_frames[32];

void kh1_pipes_frame(void) {
    u32 i, h = 2166136261u;
    recorder();
    kh1_cmd_frame(rec);
    for (i = 0; i < rec->npass; i++) {
        const KH1CmdPass *p = &rec->pass[i];
        h = (h ^ (p->rt | p->fbp << 4 | p->depth << 14 | p->load << 16 | p->store << 17 | p->dload << 19 |
                  p->dstore << 20 | p->cleared << 22)) * 16777619u;
    }
    for (i = 0; i < nseq && seq_sig[i] != h; i++) ;
    if (i < nseq) {
        seq_frames[i]++;
    } else if (rec->npass && nseq < 32) {
        seq_sig[nseq] = h;
        seq_frames[nseq++] = 1;
        printf("kh1-host: frame %u: %u render passes, %u commands (pass list %u)\n", rec->b.frames, rec->npass,
               rec->ncmd, nseq);
        for (i = 0; i < rec->npass; i++)
            printf("kh1-host:   pass %u: %s\n", i + 1, kh1_cmd_pass_str(&rec->pass[i]));
    }
    if (kh1_pipes_frame_hook) kh1_pipes_frame_hook(rec);
    kh1_cmd_reset_frame(rec);
}

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

/* session 126: the recorder's totals (cmdbuf.h): commands, the passes' load / store needs */
static void report_cmds(void) {
    const KH1CmdCount *t = &rec->total;
    u32 i;
    kh1_cmd_finish(rec);
    printf("kh1-host: commands: %u frames, %u render passes, %u commands (a frame at most %u passes, %u commands; %u held "
           "by a column group at once), %u lost; %u passes joined the scene before them (only the depth binding "
           "differed)\n", t->frames, t->passes, t->cmds, t->max_passes, t->max_cmds, t->held_max, t->lost, t->depth_joins);
    printf("kh1-host:   passes: %u load, %u don't care (%u cleared by their leading sprites); %u store (%u sampled later, %u "
           "drawn again, %u read next frame, %u display), %u discard, %u open at the end; %u commands sample their own "
           "target\n", t->loads, t->dont_care, t->cleared, t->stores, t->why[0], t->why[1], t->why[2], t->why[3], t->discards,
           t->open, t->feedback);
    printf("kh1-host:   depth: %u passes with a depth buffer, %u load, %u store, %u discard, %u open at the end\n",
           t->dpasses, t->dloads, t->dstores, t->ddiscards, t->dopen);
    for (i = 0; i < nseq; i++) printf("kh1-host:   pass list %u: %u frames\n", i + 1, seq_frames[i]);
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
    printf("kh1-host:   column groups: %u columns merged, %u primitives absorbed (a frame at most %u)\n", t->columns,
           t->merged, m->merged);
    /* session 125: the most a frame wrote against include/platform/ring.h's per-frame sizes */
    printf("kh1-host:   ring: a frame at most %u of %u vertex bytes, %u of %u uniform bytes\n",
           kh1_ring_vertex_bytes(m->verts), KH1_RING_VERTEX_BYTES, kh1_ring_uniform_bytes(m->batches, m->passes),
           KH1_RING_UNIFORM_BYTES);
}

void kh1_pipes_report(void) {
    u32 i, vmask, nv;
    if (rec) {
        if (batcher.frame.prims) kh1_pipes_frame(); /* the last frame's primitives */
        report_batches();
        if (batcher.frames) report_cmds();
    }
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
