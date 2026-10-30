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
 * lines and each distinct frame's pass list.  Session 127 (renderer-spec 4.13 "Session 127"): the transfers
 * are commands too: gsmem.c's hooks give each upload, copy and CLUT load (the CLUT through a palette cache of
 * the recorder's own, include/platform/palcache.h), and each textured kick whose binding may have moved looks
 * its TEX0 up in a texture cache of its own (include/platform/texcache.h): a decode is a TEXTURE command; the
 * report adds a `transfers:` line.  Not part of the PS2 build. */
#include "common.h"
#include "gsregs.h"
#include "gsmem.h"
#include "bytesame.h"
#include "platform/drawstate.h"
#include "platform/target.h"
#include "platform/batch.h"
#include "platform/vertex.h"
#include "platform/canvas.h"
#include "platform/ring.h"
#include "platform/cmdbuf.h"
#include "platform/gxmrec.h"
#include "platform/primasm.h"
#include "platform/palcache.h"
#include "platform/texcache.h"
#include "platform/shadergen.h"
#include "gsqueue.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

static KH1PipeSet set;
static u32 draws_seen;
static KH1CmdRec *rec;
static KH1GxmRec *gxm; /* session 128: each frame's commands as GXM calls (gxmrec.h) */
static u32 gxm_max_calls, gxm_max_scenes;
#define batcher (rec->b)
void *malloc(__SIZE_TYPE__);
void *calloc(__SIZE_TYPE__, __SIZE_TYPE__);
void free(void *);
void *memcpy(void *, const void *, __SIZE_TYPE__);

/* session 127: the recorder's caches (what a port's renderer would hold) */
static KH1PalCache *pal;
static KH1TexCache *tex;
static int tex_ok, tex_look = 1; /* tex_look: a transfer since the last lookup */
static u32 pal_buf[256];

/* Session 146 (docs/vita-build.md "The recording on the third core"): the recorder's own work (the draw state's
 * port form, the primitive's GPU vertices, the batches, commands and rings) is a queue's ops (gsqueue.h's
 * kh1_recq), run in order on the GPU frame's thread while the GS worker goes on with the GIF decode and GS memory;
 * off, each op runs at once here.  An op reads only its arguments and the recorder: what it needs of the register
 * file is copied into it, and what reads GS memory (the texture and palette caches' lookups) stays here and hands
 * the op its answer.  The recorder is the worker's again at the frame op, once the queue is done (kh1_recq_sync) */
static s16 a_pslot = -1; /* the recorder's bound palette slot (cmdbuf.c's clut_cmd sets rec->pslot), kept here */
static KH1DrawRegs rec_r; /* the registers of the last state op (the recorder's side) */
static KH1DrawState last_d;
static KH1RenderPass last_p;

static void r_upload(const u32 *a, const u32 *d, u32 n) {
    (void)d;
    (void)n;
    kh1_cmd_upload(rec, a[0], a[1], a[2], a[3], a[4], a[5], a[6]);
}

static void r_clut(const u32 *a, const u32 *d, u32 n) {
    (void)d;
    (void)n;
    kh1_cmd_clut(rec, a[0], a[1], (s32)a[2], (int)a[3]);
}

static void r_palette(const u32 *a, const u32 *d, u32 n) {
    (void)d;
    (void)n;
    kh1_cmd_palette(rec, a[0], a[1], (s32)a[2], (int)a[3]);
}

static void r_texture(const u32 *a, const u32 *d, u32 n) {
    (void)d;
    (void)n;
    kh1_cmd_texture(rec, a[0], a[1], (s32)a[2], (int)a[3], a[4]);
}

static void on_xfer(u32 dir, u32 bb_lo, u32 bb_hi, u32 pos_lo, u32 pos_hi, u32 reg_lo, u32 reg_hi) {
    u32 a[7];
    a[0] = dir;
    a[1] = bb_lo;
    a[2] = bb_hi;
    a[3] = pos_lo;
    a[4] = pos_hi;
    a[5] = reg_lo;
    a[6] = reg_hi;
    kh1_recq_put(r_upload, a, 7, 0, 0);
    tex_look = 1;
}

/* Session 147d (the title's New Game pages: ~200 glyph CLUT loads a frame over more palettes than the palette
 * cache's recent four): the palette slot each of kh1_gsmem_clut's kept answers (kh1_gsmem_clut_id) was got for,
 * with the slot's gen.  While the gen holds, the slot holds those entries, so the lookup is the hit
 * kh1_palcache_get would answer, without its hash and scan or a compare */
static struct { u32 id, gen; s16 slot; } pal_ids[64];
static int pal_known(u32 id, u32 n) {
    const KH1PalSlot *p;
    if (!id || pal_ids[id & 63].id != id) return -1;
    p = &pal->slot[pal_ids[id & 63].slot];
    return p->gen == pal_ids[id & 63].gen && p->n == n ? pal_ids[id & 63].slot : -1;
}
static int pal_get(const u32 *col, u32 n, int *fill) {
    u32 id = kh1_gsmem_clut_id();
    int slot = pal_known(id, n);
    *fill = 0;
    if (slot >= 0) {
        kh1_palcache_hit(pal, slot);
        return slot;
    }
    slot = kh1_palcache_get(pal, col, n, fill);
    if (id && slot >= 0) {
        pal_ids[id & 63].id = id;
        pal_ids[id & 63].gen = pal->slot[slot].gen;
        pal_ids[id & 63].slot = (s16)slot;
    }
    return slot;
}

static void on_clut(u32 lo, u32 hi) {
    const KH1GsState *s = kh1_gs_state();
    u32 n = (u32)kh1_gsmem_clut(lo, hi, s->texa.lo, s->texa.hi, pal_buf), a[4];
    int fill = 0, slot = n ? pal_get(pal_buf, n, &fill) : -1;
    a[0] = lo;
    a[1] = hi;
    a[2] = (u32)slot;
    a[3] = (u32)fill;
    kh1_recq_put(r_clut, a, 4, 0, 0);
    a_pslot = (s16)slot;
    tex_look = 1;
}

/* the CLUT buffer's entries a draw of TEX0 (lo, hi) reads: 0 for a texture that is not indexed */
static u32 pal_draw[256], pal_n;
static int pal_of(u32 lo, u32 hi) {
    const KH1GsState *s = kh1_gs_state();
    pal_n = (u32)kh1_gsmem_clut(lo, hi, s->texa.lo, s->texa.hi, pal_draw);
    return pal_n != 0;
}

static void tex_read(u32 lo, u32 hi, u32 *out, void *ctx) {
    u32 w = 1u << (lo >> 26 & 15), h = 1u << ((lo >> 30 | hi << 2) & 15), x, y;
    (void)ctx;
    /* session 136: the rectangle through gsmem.c's address tables (the Vita's GPU renderer decodes with this) */
    if (!kh1_gsmem_read_rect(lo >> 20 & 63, lo & 0x3FFF, lo >> 14 & 63, 0, 0, w, h, out, w)) return;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) out[y * w + x] = kh1_gsmem_read_pixel(lo >> 20 & 63, lo & 0x3FFF, lo >> 14 & 63, x, y);
}

/* the draw's texture: its entry in the recorder's texture cache (-1: a render target's, or not kept) */
static void tex_lookup(u32 lo, u32 hi) {
    const u32 *t = 0;
    int decoded = 0;
    s32 slot = -1, i;
    u32 a[5];
    if (tex_ok) t = kh1_texcache_get(tex, lo, hi, kh1_gsmem_tex_stamp(lo, hi), kh1_gsmem_tex_target(lo, hi), tex_read, 0,
                                     &decoded);
    for (i = 0; t && i < KH1_TEXCACHE_SLOTS; i++)
        if (tex->slot[i].tex == t) slot = i;
    a[0] = lo;
    a[1] = hi;
    a[2] = (u32)slot;
    a[3] = (u32)decoded;
    a[4] = decoded && slot >= 0 ? tex->slot[slot].n : 0;
    kh1_recq_put(r_texture, a, 5, 0, 0);
    /* session 136: an indexed draw reads the CLUT buffer at its own CSA, loaded or not (the GS's rule, and
     * present.c's pal_for): when its entries are not the bound slot's, bind theirs */
    if (pal_of(lo, hi)) {
        const KH1PalSlot *p = a_pslot >= 0 ? &pal->slot[a_pslot] : 0;
        if (p && p->n == pal_n &&
            (pal_known(kh1_gsmem_clut_id(), pal_n) == a_pslot || kh1_bytes_same(p->col, pal_draw, pal_n * 4))) {
            kh1_palcache_use(pal, a_pslot); /* session 141: bound from an earlier frame's load (CLD 0) */
        } else {
            int fill = 0;
            slot = pal_get(pal_draw, pal_n, &fill);
            a[2] = (u32)slot;
            a[3] = (u32)fill;
            kh1_recq_put(r_palette, a, 4, 0, 0);
            a_pslot = (s16)slot;
        }
    }
}

/* session 126: the recorder and its two rings, made at the first use (only KH1_HOST_TRACE=5 runs use them);
 * session 127: with its caches, and gsmem.c's transfer hooks set */
static KH1CmdRec *recorder(void) {
    if (!rec) {
        /* calloc: kh1_texcache_init frees what a used cache holds, so a block that is not zeroed
         * (the Vita's heap after lang.c freed the disc's ELF) had it free that memory's old words */
        rec = (KH1CmdRec *)calloc(1, sizeof *rec);
        kh1_cmd_init(rec, malloc(KH1_RING_FRAMES * KH1_RING_VERTEX_BYTES), KH1_RING_VERTEX_BYTES,
                     malloc(KH1_RING_FRAMES * KH1_RING_UNIFORM_BYTES), KH1_RING_UNIFORM_BYTES);
        pal = (KH1PalCache *)calloc(1, sizeof *pal);
        kh1_palcache_init(pal);
        gxm = (KH1GxmRec *)calloc(1, sizeof *gxm);
        kh1_gxm_clear(gxm);
        tex = (KH1TexCache *)calloc(1, sizeof *tex);
        tex_ok = kh1_texcache_init(tex) == 0;
        tex->raw = kh1_gsmem_tex_raw; /* session 142: a stamp miss on the same pages' words reads no texel */
        kh1_gsmem_xfer_hook = on_xfer;
        kh1_gsmem_clut_hook = on_clut;
    }
    return rec;
}

/* session 127: made before the run's first transfer (host/null/main.c) */
void kh1_pipes_start(void) { recorder(); }

const KH1PalCache *kh1_pipes_palcache(void) { recorder(); return pal; }
const KH1TexCache *kh1_pipes_texcache(void) { recorder(); return tex_ok ? tex : 0; }

int memcmp(const void *, const void *, __SIZE_TYPE__);

/* session 146: the recorder's own state is read once its queue is done */
const KH1Batcher *kh1_pipes_batcher(void) {
    kh1_recq_sync();
    return &recorder()->b;
}
const KH1CmdRec *kh1_pipes_recorder(void) {
    kh1_recq_sync();
    return recorder();
}

/* the registers of the last kick's state (most kicks repeat the last one's); the draw state and pass made from
 * them are the recorder's (last_d, last_p above) */
static KH1DrawRegs last_r;
static u32 last_scissor[2];
static int have_last;
/* session 150: kh1_gs_gen and PRIM at the last compare: unchanged, the registers are last_r's again (most kicks) */
static u32 last_gen, last_prim;

/* session 125: the primitive's vertex signature for batch.h's column groups (FNV-1a over the type and the
 * queued vertices; never 0).  Session 143: a word a step, not a byte (KH1GsVert is all u32; the A9 paid
 * a multiply a byte, ~7% of the GS worker); only equal signatures matter, so any good hash does */
static u32 prim_sig(u32 prim, const KH1GsVert *v, u32 n) {
    const u32 *q = (const u32 *)v;
    u32 h = 2166136261u ^ (prim & 7), i;
    h *= 16777619u;
    for (i = 0; i < n * (sizeof *v / 4); i++) {
        h = (h ^ q[i]) * 16777619u;
        h ^= h >> 15;
    }
    return h | 1;
}

/* session 146: the recorder's side of a kick.  The state op: data the draw's registers (KH1DrawRegs), then SCISSOR's
 * and XYOFFSET's lo / hi words (the pass reads them; as before, only a change of the registers or SCISSOR makes a
 * new state), 6 qwords an op (ops put one after another join, the last one then holds) */
#define STATE_QW 6
static void r_state(const u32 *a, const u32 *d, u32 nqw) {
    static const KH1Canvas c43 = { 1.0f, 0.0f, 0.0f, 0, 8192 };
    const u32 *w;
    (void)a;
    if (nqw < STATE_QW) return;
    d += (nqw - STATE_QW) * 4;
    w = d + sizeof rec_r / 4;
    memcpy(&rec_r, d, sizeof rec_r);
    kh1_drawstate_of(&rec_r, &last_d);
    kh1_target_of(rec_r.frame_lo, rec_r.frame_hi, rec_r.zbuf_lo, rec_r.zbuf_hi, rec_r.test_lo, w[0], w[1], w[2], w[3], &c43, 1.0f,
                  &last_p);
}

/* the primitive op: arguments PRIM and the vertex count n, data the n queued vertices (KH1GsVert, 2 qwords each);
 * the ops of the next primitives with the same PRIM and n join it */
static void r_prim(const u32 *a, const u32 *d, u32 nqw) {
    u32 prim = a[0], n = a[1], t = prim & 7, step = n * (u32)(sizeof(KH1GsVert) / 16), q = 0, i, nv;
    KH1PrimAsm pa;
    KH1PaVert out[6];
    KH1GpuVert gv[6];
    KH1VertCtx vc;
    do {
        const KH1GsVert *v = (const KH1GsVert *)(d + q * 4);
        /* session 126: the primitive's GPU vertices: a fresh list of its type (a strip's or fan's kick is one triangle
         * of the vertices the hook gives) through primasm.h and vertex.h */
        nv = 0;
        memset(&pa, 0, sizeof pa);
        kh1_pa_prim(&pa, (prim & ~7u) | (t == 2 ? 1 : t == 4 || t == 5 ? 3 : t));
        for (i = 0; i < n; i++) nv = kh1_pa_vertex(&pa, (const KH1PaVert *)&v[i], 1, out);
        kh1_vertex_ctx(&vc, &last_p, rec_r.zbuf_lo, prim, rec_r.tex0_lo, rec_r.tex0_hi);
        kh1_vertex_of(&vc, out, nv, gv);
        kh1_cmd_prim(rec, &last_d, &last_p, gv, t == 6 ? 6 : n, prim_sig(prim, v, n));
    } while (step && (q += step) < nqw);
}

/* the GS worker's side: the registers compared with the last kick's, a new state op when they moved; the texture
 * lookup (it reads GS memory); then the primitive op */
void kh1_pipes_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state) {
    const KH1GsState *gs = kh1_gs_state();
    const KH1GsContext *c = &gs->ctx[prim >> 9 & 1];
    KH1DrawRegs r;
    u32 a[2];
    (void)state;
    recorder();
    if (have_last && kh1_gs_gen == last_gen && prim == last_prim) goto same;
    last_gen = kh1_gs_gen;
    last_prim = prim;
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
    /* session 127: the transfers break the batch from gsmem.c's hooks (kh1_cmd_upload, kh1_cmd_clut) */
    if (!have_last || memcmp(&r, &last_r, sizeof r) || c->scissor.lo != last_scissor[0] ||
        c->scissor.hi != last_scissor[1]) {
        u32 w[STATE_QW * 4], k = sizeof r / 4;
        memcpy(w, &r, sizeof r);
        w[k] = c->scissor.lo;
        w[k + 1] = c->scissor.hi;
        w[k + 2] = c->xyoffset.lo;
        w[k + 3] = c->xyoffset.hi;
        for (k += 4; k < STATE_QW * 4; k++) w[k] = 0;
        kh1_recq_put(r_state, 0, 0, w, STATE_QW);
        last_r = r;
        last_scissor[0] = c->scissor.lo;
        last_scissor[1] = c->scissor.hi;
        have_last = 1;
        tex_look = 1;
    }
same:
    if (tex_look && prim >> 4 & 1) { /* session 127: the binding may have moved: the texture cache's answer */
        tex_lookup(c->tex0.lo, c->tex0.hi);
        tex_look = 0;
    }
    a[0] = prim;
    a[1] = n;
    kh1_recq_put(r_prim, a, 2, (const u32 *)v, n * (u32)(sizeof *v / 16));
}

/* session 126: called with the frame's commands before they are cleared (tests/host/cmdbuf_test.c) */
void (*kh1_pipes_frame_hook)(const KH1CmdRec *r);

/* session 126: each distinct pass list (by targets, loads and stores) printed once, up to 32 */
static u32 seq_sig[32], nseq, seq_frames[32];

/* the frame's commands ended (kh1_cmd_frame), its pass list logged and counted */
static void frame_begin(void) {
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
    kh1_gxm_frame(gxm, rec);
    if (gxm->frame.calls > gxm_max_calls) gxm_max_calls = gxm->frame.calls;
    if (gxm->frame.scenes > gxm_max_scenes) gxm_max_scenes = gxm->frame.scenes;
}

static void frame_end(void) {
    kh1_cmd_reset_frame(rec);
    kh1_palcache_frame(pal);
    if (tex_ok) kh1_texcache_frame(tex);
    tex_look = 1;
}

/* Session 142 (docs/vita-build.md "The GPU frame on the third core"): the frame handed to the hook on another
 * thread (gsqueue.h's kh1_gpuq) while this one records the next.  What the hook reads is copied as the frame
 * left it: the commands, passes and targets (the rings' slots stay: the next frame writes the other one, and
 * the one after waits for the hook), GS memory (gsmem.h's snapshot), and the texture and palette cache
 * entries the frame uploads (kh1_pipes_frame_texels / _pal) */
int kh1_pipes_snap;
u32 kh1_pipes_frame_arg, kh1_pipes_job_arg;
/* the thread's wait and put (gsqueue.h's kh1_gpuq_wait / _put, set with kh1_pipes_snap); 0: the hook runs here */
void (*kh1_pipes_gpu_wait)(void);
void (*kh1_pipes_gpu_put)(KH1GsqFn fn, const u32 *args, u32 nargs);
static KH1CmdRec *snap;
static u32 *snap_texbuf, snap_texcap;
static u32 snap_texoff[KH1_TEXCACHE_SLOTS];
static u8 snap_hastex[KH1_TEXCACHE_SLOTS], snap_haspal[KH1_PALCACHE_SLOTS];
static u32 (*snap_pal)[256];

static int snap_frame(void) {
    u32 i, need = 0;
    if (!snap && !(snap = (KH1CmdRec *)calloc(1, sizeof *snap))) return -1;
    if (!snap_pal && !(snap_pal = (u32 (*)[256])malloc(KH1_PALCACHE_SLOTS * 1024))) return -1;
    if (kh1_gsmem_snap_take() < 0) return -1;
    snap->vring = rec->vring;
    snap->uring = rec->uring;
    snap->ncmd = rec->ncmd;
    snap->npass = rec->npass;
    snap->ntgt = rec->ntgt;
    memcpy(snap->cmd, rec->cmd, rec->ncmd * sizeof rec->cmd[0]);
    memcpy(snap->pass, rec->pass, rec->npass * sizeof rec->pass[0]);
    memcpy(snap->tgt, rec->tgt, sizeof rec->tgt);
    memset(snap_hastex, 0, sizeof snap_hastex);
    memset(snap_haspal, 0, sizeof snap_haspal);
    for (i = 0; i < rec->ncmd; i++) { /* the texels the frame's texture uploads read */
        const KH1Cmd *c = &rec->cmd[i];
        s32 sl = c->x.slot;
        if (c->kind == KH1_CMD_TEXTURE && tex_ok && sl >= 0 && sl < KH1_TEXCACHE_SLOTS && tex->slot[sl].tex &&
            !snap_hastex[sl]) {
            snap_texoff[sl] = need;
            snap_hastex[sl] = 1;
            need += tex->slot[sl].n;
        }
    }
    if (need > snap_texcap) {
        free(snap_texbuf);
        snap_texcap = need + (need >> 1);
        if (!(snap_texbuf = (u32 *)malloc(snap_texcap * 4))) {
            snap_texcap = 0;
            return -1;
        }
    }
    for (i = 0; i < KH1_TEXCACHE_SLOTS; i++)
        if (snap_hastex[i]) memcpy(snap_texbuf + snap_texoff[i], tex->slot[i].tex, tex->slot[i].n * 4);
    for (i = 0; i < rec->ncmd; i++) { /* the palettes the frame's palette fills read */
        const KH1Cmd *c = &rec->cmd[i];
        s32 sl = c->x.slot;
        if (c->kind == KH1_CMD_CLUT && c->x.fill && sl >= 0 && sl < KH1_PALCACHE_SLOTS && !snap_haspal[sl]) {
            memcpy(snap_pal[sl], pal->slot[sl].col, 1024);
            snap_haspal[sl] = 1;
        }
    }
    return 0;
}

static void w_hook(const u32 *a, const u32 *d, u32 n) {
    (void)d;
    (void)n;
    kh1_pipes_job_arg = a[0];
    kh1_pipes_frame_hook(snap);
}

/* Session 145: the game draws every other frame in the Dive, so every other frame op finds nothing recorded,
 * nothing written to the rings and GS memory as the last copy has it.  Such a frame's job reads nothing the
 * worker changes (no commands, so no texels or palettes; the rings' slots it names hold nothing and are kept,
 * ring.c; GS memory is the copy the job before reads too), so it is posted behind that job without waiting for
 * it, from a copy of its own.  The next frame's op waits for both as before. */
static KH1CmdRec *snap_empty;
static int empty_posted; /* the last job posted is an empty frame's (snap_empty is its) */

static int empty_frame(void) {
    return !kh1_pipes_frame_arg && !rec->ncmd && !rec->npass && !rec->vring.head && !rec->uring.head &&
           kh1_gsmem_snap_same();
}

static void w_hook_empty(const u32 *a, const u32 *d, u32 n) {
    (void)d;
    (void)n;
    kh1_pipes_job_arg = a[0];
    kh1_pipes_frame_hook(snap_empty);
}

/* the texels of texture cache entry `slot` the frame's upload reads (the copy's when the frame was copied) */
const u32 *kh1_pipes_frame_texels(s32 slot) {
    if (slot < 0 || slot >= KH1_TEXCACHE_SLOTS) return 0;
    if (kh1_pipes_snap) return snap_hastex[slot] ? snap_texbuf + snap_texoff[slot] : 0;
    return tex_ok ? tex->slot[slot].tex : 0;
}

/* palette slot `slot`'s 256 words as the frame's palette fill reads them */
const u32 *kh1_pipes_frame_pal(s32 slot) {
    if (slot < 0 || slot >= KH1_PALCACHE_SLOTS) return 0;
    if (kh1_pipes_snap) return snap_haspal[slot] ? snap_pal[slot] : 0;
    return pal->slot[slot].col;
}

void kh1_pipes_frame(void) {
    kh1_recq_sync(); /* session 146: the frame's recording done */
    frame_begin();
    if (kh1_pipes_frame_hook && kh1_pipes_snap) {
        u32 a = kh1_pipes_frame_arg;
        if (kh1_pipes_gpu_put && empty_frame() && (snap_empty || (snap_empty = (KH1CmdRec *)calloc(1, sizeof *snap_empty)))) {
            if (empty_posted && kh1_pipes_gpu_wait) kh1_pipes_gpu_wait(); /* its copy is about to change */
            empty_posted = 1;
            snap_empty->vring = rec->vring;
            snap_empty->uring = rec->uring;
            snap_empty->ncmd = snap_empty->npass = 0;
            snap_empty->ntgt = rec->ntgt;
            memcpy(snap_empty->tgt, rec->tgt, sizeof rec->tgt);
            kh1_pipes_gpu_put(w_hook_empty, &a, 1);
            frame_end();
            return;
        }
        if (kh1_pipes_gpu_wait) kh1_pipes_gpu_wait(); /* the last frame's hook is done with the copies */
        empty_posted = 0;
        if (snap_frame()) {
            printf("kh1-host: pipes: the frame's copy failed (no memory): the GPU frame on this thread from now\n");
            kh1_pipes_snap = 0;
            kh1_pipes_job_arg = a;
            kh1_pipes_frame_hook(rec);
        } else if (kh1_pipes_gpu_put) {
            kh1_pipes_gpu_put(w_hook, &a, 1);
        } else {
            w_hook(&a, 0, 0);
        }
    } else if (kh1_pipes_frame_hook) {
        kh1_pipes_job_arg = kh1_pipes_frame_arg;
        kh1_pipes_frame_hook(rec);
    }
    frame_end();
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
    /* session 127: the transfers between the draws */
    printf("kh1-host:   transfers: %u uploads, %u copies, %u CLUT loads (%u palette fills), %u texture decodes (%u texels); "
           "%u read a render target, %u write one; %u scenes split by a transfer on their own target\n", t->uploads,
           t->copies, t->cluts, t->pal_fills, t->textures, t->texels, t->tgt_reads, t->tgt_writes, t->splits);
    {   /* session 128: the GXM calls (include/platform/gxmrec.h) */
        const KH1GxmCount *g = &gxm->total;
        printf("kh1-host:   gxm: %u frames, %u calls (a frame at most %u, %u scenes), %u scenes (%u load, %u store), %u draws, "
               "%u program sets, %u texture sets, %u region sets; %u texture uploads, %u palette fills, %u palette "
               "read-backs, %u target uploads, %u blits; %u lost\n", g->frames, g->calls, gxm_max_calls, gxm_max_scenes,
               g->scenes, g->loads, g->stores, g->draws, g->programs, g->textures, g->regions, g->tex_uploads, g->pal_fills,
               g->pal_readbacks, g->target_uploads, g->blits, g->lost);
    }
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

/* session 127: the run's shaders as Cg (shadergen.h): counted, and with KH1_HOST_SHADERS=DIR written there as
 * frag_N.cg (the pipe set's fragment shaders in order) and vert_N.cg (vertex.h's variant numbers) */
typedef struct _IO_FILE FILE;
FILE *fopen(const char *, const char *);
int fclose(FILE *);
__SIZE_TYPE__ fwrite(const void *, __SIZE_TYPE__, __SIZE_TYPE__, FILE *);
char *getenv(const char *);
int sprintf(char *, const char *, ...);

static void put_file(const char *dir, const char *name, u32 n, const char *text, u32 len) {
    char path[512];
    FILE *f;
    sprintf(path, "%.400s/%s_%u.cg", dir, name, n);
    f = fopen(path, "w");
    if (!f) return;
    fwrite(text, 1, len, f);
    fclose(f);
}

static void report_shaders(u32 vmask) {
    static char text[KH1_SHADER_TEXT];
    const char *dir = getenv("KH1_HOST_SHADERS");
    u32 i, gen = 0, not_gen = 0, len, most = 0;
    for (i = 0; i < set.nshader; i++) {
        len = kh1_shader_frag_cg(&set.shader[i], text, sizeof text);
        if (!len) { not_gen++; continue; }
        gen++;
        if (len > most) most = len;
        if (dir && *dir) put_file(dir, "frag", i + 1, text, len);
    }
    for (i = 0; i < 7; i++)
        if (vmask >> i & 1 && dir && *dir && (len = kh1_shader_vert_cg(i, text, sizeof text)) != 0) put_file(dir, "vert", i, text, len);
    printf("kh1-host:   Cg: %u fragment shaders generated (at most %u bytes), %u not (a frame read or the sampler's own "
           "taps)%s\n", gen, most, not_gen, dir && *dir ? ", written with the vertex shaders to KH1_HOST_SHADERS" : "");
}

void kh1_pipes_report(void) {
    u32 i, vmask, nv;
    kh1_recq_sync();
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
    report_shaders(vmask);
    report_targets();
}
