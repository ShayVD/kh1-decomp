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
#include "platform/natdraw.h"
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
char *getenv(const char *);
void free(void *);
void *memcpy(void *, const void *, __SIZE_TYPE__);
char *getenv(const char *);
unsigned long strtoul(const char *, char **, int);
char *strchr(const char *, int);

static void nat_flush(void); /* the native renderer's open op (below) */
/* 2026-10-31 (the frame op on the GPU thread, kh1_pipes_frame below): the texture cache entries this frame decoded
 * and the palette slots it filled, marked on the GS worker as it hands them to the recorder: the copies the frame's
 * GPU work reads (snap_frame's set, without reading the recorder's commands) */
static u8 fr_tex[KH1_TEXCACHE_SLOTS], fr_pal[KH1_PALCACHE_SLOTS];
static int fr_marks;
static void mark_tex(s32 slot) {
    if (slot >= 0 && slot < KH1_TEXCACHE_SLOTS) fr_tex[slot] = 1, fr_marks = 1;
}
static void mark_pal(s32 slot, int fill) {
    if (fill && slot >= 0 && slot < KH1_PALCACHE_SLOTS) fr_pal[slot] = 1, fr_marks = 1;
}

/* session 127: the recorder's caches (what a port's renderer would hold) */
static KH1PalCache *pal;
static KH1TexCache *tex;
static int tex_ok, tex_look = 1; /* tex_look: a transfer since the last lookup */
/* 2026-11-02 (docs/native-plan.md "Texture lookups by page lists"): the last lookup's TEX0, stamp and target and
 * its answer (lt_ok: one since the frame op), and pal_look: a CLUT load since the palette's last check */
static int lt_ok, pal_look = 1;
static u32 lt_lo, lt_hi, lt_stamp, lt_tgt;
int kh1_pipes_texskip = 1; /* config.txt texskip=, host KH1_HOST_TEXSKIP: 0 looks every time as before */
int kh1_pipes_texver = 1; /* 2026-11-03: config.txt texver=, host KH1_HOST_TEXVER: 0 checks a stamp miss's words as before */
u32 kh1_pipes_tex_same; /* the lookups that found the last one's texture (the watchdog's) */
static int oc_ok; /* the last clut op's TEX0, TEXA, id and slot (on_clut's oc_*) are what the recorder holds */
/* 2026-11-02: the GS worker's CLUT loads and texture lookups on kh1_vu1_clock (the Vita's watchdog prints them): calls,
 * microseconds, and the lookups that decoded the texture */
extern u32 (*kh1_vu1_clock)(void);
u32 kh1_pipes_clut_us, kh1_pipes_tex_n, kh1_pipes_tex_us, kh1_pipes_tex_dec;
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
    nat_flush(); /* a joined native op first (2026-10-31) */
    kh1_recq_put(r_upload, a, 7, 0, 0);
    tex_look = 1;
    oc_ok = 0;
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

/* 2026-11-02 (docs/native-plan.md "Repeated CLUT loads"; config.txt clutskip=, host KH1_HOST_CLUTSKIP): the fights'
 * HUD and effects load the same CLUT before each of their sprites (~half the loads repeat the one before).  A load
 * with the last load's TEX0 and TEXA whose entries are the same conversion (gsmem.c's id: the CLUT's words unchanged)
 * into the palette slot the recorder still has bound, its source not in pages a draw marked (the GPU's, which the
 * model does not hold), with no palette, upload or frame op since, binds nothing new: the clut op, the native op's
 * end before it and the texture lookup after it are left out.  0 sends every load as before */
int kh1_pipes_clutskip = 1;
u32 kh1_pipes_clut_n, kh1_pipes_clut_skipped; /* the loads, and those left out (the watchdog's) */
static u32 oc_lo, oc_hi, oc_ta, oc_tb, oc_id;
static void on_clut(u32 lo, u32 hi) {
    const KH1GsState *s = kh1_gs_state();
    u32 t0 = kh1_vu1_clock ? kh1_vu1_clock() : 0;
    u32 n = (u32)kh1_gsmem_clut(lo, hi, s->texa.lo, s->texa.hi, pal_buf), a[4], id = kh1_gsmem_clut_id();
    int fill = 0, slot = n ? pal_get(pal_buf, n, &fill) : -1;
    kh1_pipes_clut_n++;
    if (kh1_pipes_clutskip && oc_ok && id && id == oc_id && lo == oc_lo && hi == oc_hi && s->texa.lo == oc_ta &&
        s->texa.hi == oc_tb && slot >= 0 && slot == a_pslot && !fill) {
        u32 cpsm = hi >> 19 & 15, cbp = hi >> 5 & 0x3FFF, b8 = (lo >> 20 & 7) == 3; /* PSMT8 / T8H: 16 x 16, else 8 x 2 */
        if (cpsm == 1) cpsm = 0; /* CT24 read as CT32 (gsmem.c cpsm_of) */
        if (!kh1_gsmem_drawn(cpsm, cbp, 1, 0, 0) && !kh1_gsmem_drawn(cpsm, cbp, 1, b8 ? 15 : 7, b8 ? 15 : 1)) {
            kh1_pipes_clut_skipped++;
            if (kh1_vu1_clock) kh1_pipes_clut_us += kh1_vu1_clock() - t0;
            return;
        }
    }
    oc_ok = slot >= 0;
    oc_lo = lo;
    oc_hi = hi;
    oc_ta = s->texa.lo;
    oc_tb = s->texa.hi;
    oc_id = id;
    a[0] = lo;
    a[1] = hi;
    a[2] = (u32)slot;
    a[3] = (u32)fill;
    mark_pal(slot, fill);
    nat_flush(); /* a joined native op first (2026-10-31) */
    kh1_recq_put(r_clut, a, 4, 0, 0);
    a_pslot = (s16)slot;
    tex_look = pal_look = 1;
    if (kh1_vu1_clock) kh1_pipes_clut_us += kh1_vu1_clock() - t0;
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

/* the draw's texture: its entry in the recorder's texture cache (-1: a render target's, or not kept).
 * 2026-11-02 (docs/native-plan.md "Texture lookups by page lists"): with the TEX0, stamp and target of the last
 * lookup this frame, the cache would hit that entry again and the texture op would bind the slot the recorder has
 * (cmdbuf.c kh1_cmd_texture: no decode, no break): neither is done, nor the palette's check without a CLUT load or
 * a state change since (the CLUT buffer and the bound slot are as it left them) */
static void tex_lookup(u32 lo, u32 hi) {
    const u32 *t = 0;
    int decoded = 0;
    s32 slot = -1, i;
    u32 a[5], stamp, target;
    stamp = kh1_gsmem_tex_stamp(lo, hi);
    target = kh1_gsmem_tex_target(lo, hi);
    if (lt_ok && lo == lt_lo && hi == lt_hi && stamp == lt_stamp && target == lt_tgt) {
        kh1_pipes_tex_same++;
        if (!pal_look) return;
        a[0] = lo;
        a[1] = hi;
    } else {
        if (tex_ok) t = kh1_texcache_get(tex, lo, hi, stamp, target, tex_read, 0, &decoded);
        for (i = 0; t && i < KH1_TEXCACHE_SLOTS; i++)
            if (tex->slot[i].tex == t) {
                slot = i;
                break;
            }
        a[0] = lo;
        a[1] = hi;
        a[2] = (u32)slot;
        a[3] = (u32)decoded;
        a[4] = decoded && slot >= 0 ? tex->slot[slot].n : 0;
        if (decoded) mark_tex(slot), kh1_pipes_tex_dec++;
        nat_flush(); /* a joined native op first (2026-10-31) */
        kh1_recq_put(r_texture, a, 5, 0, 0);
        lt_ok = kh1_pipes_texskip;
        lt_lo = lo;
        lt_hi = hi;
        lt_stamp = stamp;
        lt_tgt = target;
    }
    pal_look = 0;
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
            mark_pal(slot, fill);
            nat_flush(); /* a joined native op first (2026-10-31) */
            kh1_recq_put(r_palette, a, 4, 0, 0);
            a_pslot = (s16)slot;
            oc_ok = 0;
        }
    }
}

/* session 126: the recorder and its two rings, made at the first use (only KH1_HOST_TRACE=5 runs use them);
 * session 127: with its caches, and gsmem.c's transfer hooks set */
static void nat_hook(u32 what, u32 prim, const u32 *a, const u32 *b);
static void nat_idle(void);
static void nat_done(u32 free);
static int nat_direct(u32 prim, u32 prog, const u32 *p, u32 nqw, u32 free);
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
        tex->ver = kh1_pipes_texver ? kh1_gsmem_tex_ver : 0; /* 2026-11-03: nor one on the same pages' version */
        tex->same = kh1_pipes_texver ? kh1_gsmem_tex_raw_same : 0; /* and the words compared where they lie */
        tex->ver_check = getenv("KH1_HOST_TEXVERCHECK") != 0; /* the host's check of each version hit */
        kh1_gsmem_xfer_hook = on_xfer;
        kh1_gsmem_clut_hook = on_clut;
        kh1_gs_native_hook = nat_hook;
        kh1_gsq_idle_hook = nat_idle;
        kh1_gs_nat_done = nat_done;
        kh1_gs_nat_direct = nat_direct;
    }
    return rec;
}

/* session 127: made before the run's first transfer (host/null/main.c) */
void kh1_pipes_start(void) { recorder(); }

const KH1PalCache *kh1_pipes_palcache(void) { recorder(); return pal; }
const KH1TexCache *kh1_pipes_texcache(void) { recorder(); return tex_ok ? tex : 0; }
/* 2026-11-03: the same, 0 when no recorder was made (the end-of-run counts) */
const KH1TexCache *kh1_pipes_texcache_if(void) { return rec && tex_ok ? tex : 0; }

int memcmp(const void *, const void *, __SIZE_TYPE__);

/* session 146: the recorder's own state is read once its queue is done */
const KH1Batcher *kh1_pipes_batcher(void) {
    nat_flush();
    kh1_recq_sync();
    return &recorder()->b;
}
const KH1CmdRec *kh1_pipes_recorder(void) {
    nat_flush();
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

/* wide screen: the view's margin in canvas sixteenths (kh1_view_side16), set with the HUD's anchors (plat_null.c
 * kh1_null_hud_wide); 0 keeps the PS2's 512-wide targets */
static s32 view_side16;
void kh1_pipes_view(s32 side16) { view_side16 = side16; }

/* session 146: the recorder's side of a kick.  The state op: data the draw's registers (KH1DrawRegs), then SCISSOR's
 * and XYOFFSET's lo / hi words (the pass reads them; as before, only a change of the registers or SCISSOR makes a
 * new state), 6 qwords an op (ops put one after another join, the last one then holds) */
#define STATE_QW 6
static void r_state(const u32 *a, const u32 *d, u32 nqw) {
    /* the targets at the PS2's scale; under a wide view (kh1_view_init: the Vita's wide=1, the host's KH1_HOST_WIDE)
     * the 3D, display and Z-colour targets take the view's width, canvas x -side .. 512 + side */
    KH1Canvas c43 = { 1.0f, 0.0f, 0.0f, 0, 8192 };
    const u32 *w;
    (void)a;
    if (nqw < STATE_QW) return;
    c43.vx0 = -view_side16;
    c43.vw = 8192 + 2 * view_side16;
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

/* session 151: a strip's op (kh1_gs_strip_hook): arguments PRIM, the vertex count n and the queued count nq, data the
 * draw bits and the n vertices.  Each vertex goes to the GPU's form once, and each triangle a bit names goes to the
 * recorder as r_prim gives it (the vertices in the GS's order, IIP 0's colour the last vertex's, the same signature);
 * the ops of the next strips with the same arguments join it */
static void r_strip(const u32 *a, const u32 *d, u32 nqw) {
    u32 prim = a[0], n = a[1], step = KH1_GS_STRIP_MASK / 4 + n * (u32)(sizeof(KH1GsVert) / 16), q = 0, j;
    KH1GpuVert gv[KH1_GS_STRIP_MAX], tri[3];
    KH1VertCtx vc;
    kh1_vertex_ctx(&vc, &last_p, rec_r.zbuf_lo, prim, rec_r.tex0_lo, rec_r.tex0_hi);
    do {
        const u32 *m = d + q * 4;
        const KH1GsVert *v = (const KH1GsVert *)(m + KH1_GS_STRIP_MASK);
        kh1_vertex_of(&vc, (const KH1PaVert *)v, n, gv);
        for (j = 2; j < n; j++) {
            if (!(m[j >> 5] >> (j & 31) & 1)) continue;
            tri[0] = gv[j - 2];
            tri[1] = gv[j - 1];
            tri[2] = gv[j];
            if (!(prim >> 3 & 1)) { /* IIP 0: the colour of the vertex that drew (primasm.c) */
                memcpy(tri[0].rgba, gv[j].rgba, sizeof tri[0].rgba);
                memcpy(tri[1].rgba, gv[j].rgba, sizeof tri[1].rgba);
            }
            kh1_cmd_prim(rec, &last_d, &last_p, tri, 3, prim_sig(prim, v + j - 2, 3));
        }
    } while ((q += step) < nqw);
}

/* the GS worker's side: the registers compared with the last kick's, a new state op when they moved; the texture
 * lookup (it reads GS memory) */
static void prim_state(u32 prim) {
    const KH1GsState *gs = kh1_gs_state();
    const KH1GsContext *c = &gs->ctx[prim >> 9 & 1];
    KH1DrawRegs r;
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
        nat_flush(); /* a joined native op first (2026-10-31) */
        kh1_recq_put(r_state, 0, 0, w, STATE_QW);
        last_r = r;
        last_scissor[0] = c->scissor.lo;
        last_scissor[1] = c->scissor.hi;
        have_last = 1;
        tex_look = pal_look = 1;
    }
same:
    if (tex_look && prim >> 4 & 1) { /* session 127: the binding may have moved: the texture cache's answer */
        u32 t0 = kh1_vu1_clock ? kh1_vu1_clock() : 0;
        tex_lookup(c->tex0.lo, c->tex0.hi);
        tex_look = 0;
        kh1_pipes_tex_n++;
        if (kh1_vu1_clock) kh1_pipes_tex_us += kh1_vu1_clock() - t0;
    }
}

/* then the primitive op */
void kh1_pipes_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state) {
    u32 a[2];
    (void)state;
    prim_state(prim);
    a[0] = prim;
    a[1] = n;
    nat_flush(); /* a joined native op first (2026-10-31) */
    kh1_recq_put(r_prim, a, 2, (const u32 *)v, n * (u32)(sizeof *v / 16));
}

/* session 151: or a strip's (gsregs.h's kh1_gs_strip_hook) */
void kh1_pipes_strip(u32 prim, const u32 *d, u32 n, u32 nq) {
    u32 a[2];
    (void)nq;
    prim_state(prim);
    a[0] = prim;
    a[1] = n;
    nat_flush(); /* a joined native op first (2026-10-31) */
    kh1_recq_put(r_strip, a, 2, d, KH1_GS_STRIP_MASK / 4 + n * (u32)(sizeof(KH1GsVert) / 16));
}

/* The native renderer (include/platform/natdraw.h, docs/native-renderer.md): a VU1 run's payload (host/port/vu1_draw.h)
 * reaches the GS worker in place of its kicks (host/null/dmawalk.c w_native).  For each record the worker applies the
 * GIF tag's PRE PRIM and counts the strip in the model (gsregs.c kh1_gs_native), then hands it here: the records of a
 * run drawn in one state go to the recorder as one op (the state op before it, as for a kick), whose side lists the
 * triangles, folds the matrices with the pass's mapping and records one draw command (cmdbuf.h kh1_cmd_native).
 * kh1_pipes_nat_cull is the cull mode a back-face-culled run gets (config.txt natcull= / KH1_HOST_NATCULL) */
u32 kh1_pipes_nat_cull = KH1_NAT_CULL_CCW;
u32 kh1_pipes_nat_draws, kh1_pipes_nat_tris; /* the recorder's native commands and triangles so far */
#define NAT_QW 4096
static u32 nat_op[NAT_QW][4];
static const u32 *nat_hdr, *nat_mats;
/* the open op's header (2 qwords) and matrices, kept: 2026-10-31, P0's runs with the same matrix and header join
 * one op (a map object's batches), so the op can stay open past its payload */
static u32 nat_hs[8], nat_ms[KH1_NAT_MATS * 16];
static u32 nat_rq, nat_nrec, nat_prim, nat_gen;
static u32 nat_moff; /* 2026-10-31: the open op's matrix index of the current run's first matrix (a joined P13 run's) */
static int nat_open;
static KH1GpuVert nat_v[KH1_NAT_VERTS];
static KH1GpuVertSk nat_vs[KH1_NAT_VERTS]; /* 2026-11-01: P13's skinned draws' (natdraw.h KH1_NAT_SKIN) */
static f32 nat_m[KH1_NAT_MATS * 16];

/* the recorder's side: argument the GS's X shift, data one or more payloads (ops put one after another join) */
static void r_native(const u32 *a, const u32 *d, u32 nqw) {
    while (nqw >= 2) {
        u32 nrec = d[1], nmat = d[2], rq = d[3], len = 2 + rq + nmat * 4, n, lost;
        if (len > nqw || nmat > KH1_NAT_MATS) break;
        if ((d[0] & 0xFF) == 0) { /* 2026-10-31: P0 (natdraw.h): the culled triangles, then the double-sided ones */
            u32 pass;
            kh1_nat_fold(&last_p, rec_r.zbuf_lo, (s32)a[0], d + (2 + rq) * 4, nmat, nat_m);
            for (pass = 0; pass < 2; pass++) {
                n = kh1_nat_tris0(d + 8, nrec, d[4], !pass, nat_v, KH1_NAT_VERTS, &lost);
                if (!n) continue;
                kh1_cmd_native(rec, &last_d, &last_p, nat_v, n, nat_m, nmat,
                               (!pass ? kh1_pipes_nat_cull : KH1_NAT_CULL_NONE) | KH1_NAT_LIN);
                kh1_pipes_nat_draws++;
                kh1_pipes_nat_tris += n / 3;
            }
        } else if (!d[6] && (d[0] & 0xFF) == 13 && nrec && d[8 + 3] & KH1_NAT_SKIN) {
            /* 2026-11-01: P13's skinned records (natdraw.h KH1_NAT_SKIN): the bigger vertex, its own shaders */
            n = kh1_nat_tris_skin(d + 8, nrec, nmat, d[4], d[5], KH1_NAT_LIN, nat_vs, KH1_NAT_VERTS, &lost);
            kh1_nat_fold(&last_p, rec_r.zbuf_lo, (s32)a[0], d + (2 + rq) * 4, nmat, nat_m);
            kh1_cmd_native_skin(rec, &last_d, &last_p, nat_vs, n, nat_m, nmat,
                                (d[7] ? kh1_pipes_nat_cull : KH1_NAT_CULL_NONE) | KH1_NAT_LIN);
            kh1_pipes_nat_draws++;
            kh1_pipes_nat_tris += n / 3;
        } else if (!d[6] && nrec && d[8 + 3] & KH1_NAT_VB) {
            /* 2026-11-02 (natdraw.h natvb): a cached run's stubs: each run of them in one entry with contiguous indices one
             * draw from natvb's GPU memory, in the records' order */
            const u32 *q = d + 8;
            u32 i, cull = d[7] ? kh1_pipes_nat_cull : KH1_NAT_CULL_NONE;
            const KH1GpuVert *xv = 0;
            const u16 *xi = 0;
            u32 ni = 0, seq = 0, home = 0;
            if ((d[0] & 0xFF) == 11) cull |= KH1_NAT_LIN;
            kh1_nat_fold(&last_p, rec_r.zbuf_lo, (s32)a[0], d + (2 + rq) * 4, nmat, nat_m);
            for (i = 0; i <= nrec; i++, q += 8) {
                const KH1GpuVert *v = i < nrec ? (const KH1GpuVert *)(unsigned long)q[4] : 0;
                const u16 *x = i < nrec ? (const u16 *)(unsigned long)q[5] : 0;
                if (i < nrec && !(q[3] & KH1_NAT_VB)) break; /* (an op is all stubs or none) */
                if (ni && (i == nrec || v != xv || x != xi + ni)) {
                    kh1_cmd_native_vb(rec, &last_d, &last_p, xv, xi, ni, nat_m, nmat, home, cull, seq);
                    kh1_pipes_nat_draws++;
                    kh1_pipes_nat_tris += ni / 3;
                    ni = 0;
                }
                if (i == nrec) break;
                if (!ni) {
                    xv = v;
                    xi = x;
                    home = KH1_NAT_VB_HOME(q[6]); /* (one entry's records share it) */
                }
                ni += KH1_NAT_VB_COUNT(q[6]);
                if ((s32)(q[7] - seq) > 0) seq = q[7];
            }
        } else if (!d[6]) { /* not every vertex ADC */
            u32 lin = (d[0] & 0xFF) == 11 || (d[0] & 0xFF) == 13 ? KH1_NAT_LIN : 0, i;
            n = kh1_nat_tris(d + 8, nrec, nmat, d[4], d[5], nat_v, KH1_NAT_VERTS, &lost);
            /* 2026-10-31: P11 (and P13) with z not clamped, so the GPU clips where P11 dropped what crossed its near plane
             * (P13: what left its guard band) */
            if (lin) for (i = 0; i < n; i++) nat_v[i].pad[0] |= (u8)KH1_NAT_LIN;
            kh1_nat_fold(&last_p, rec_r.zbuf_lo, (s32)a[0], d + (2 + rq) * 4, nmat, nat_m);
            kh1_cmd_native(rec, &last_d, &last_p, nat_v, n, nat_m, nmat, (d[7] ? kh1_pipes_nat_cull : KH1_NAT_CULL_NONE) | lin);
            kh1_pipes_nat_draws++;
            kh1_pipes_nat_tris += n / 3;
        }
        d += len * 4;
        nqw -= len;
    }
}

/* 2026-10-31 (the Vita's renderer=native log: w_native 160-520 ms per 2.4 s on the GS worker): the op is built on
 * the recorder's side.  The worker used to copy each record into nat_op and then nat_op into the queue, two passes
 * over every payload's bytes on a core whose time is the frame rate's limit; now it puts the op's start (header and
 * matrices), each record (joined into one queue op while unpublished) and its end, and the GPU thread assembles
 * nat_op as before, so r_native sees the same ops as before (the same draws).  nat_rq and nat_nrec still count on the
 * worker, so an op ends where it did */
static u32 nat_crq, nat_cnrec; /* the recorder's side: the op being assembled in nat_op, its matrices */
static u32 nat_cms[KH1_NAT_MATS * 16], nat_cmoff;
static void r_nat_open(const u32 *a, const u32 *d, u32 nqw) {
    (void)a;
    memcpy(nat_op[0], d, 32);
    memcpy(nat_cms, d + 8, d[2] * 64);
    nat_crq = 2;
    nat_cnrec = 0;
    nat_cmoff = 0;
    (void)nqw;
}
/* a joined P13 run's matrices (argument their first index in the op), after the op's earlier ones */
static void r_nat_mats(const u32 *a, const u32 *d, u32 nqw) {
    if (a[0] + nqw / 4 > KH1_NAT_MATS) return;
    memcpy(nat_cms + a[0] * 16, d, nqw * 16);
    nat_op[0][2] = a[0] + nqw / 4;
    nat_cmoff = a[0];
}
static void r_nat_rec(const u32 *a, const u32 *d, u32 nqw) {
    (void)a;
    while (nqw) {
        u32 nq = KH1_NAT_REC_QW(d);
        if (nq > nqw || nat_crq + nq > NAT_QW) break;
        memcpy(nat_op[nat_crq], d, nq * 16);
        if (nat_cmoff && !(d[3] & KH1_NAT_VB)) { /* a joined run's vertices: its matrices follow the op's earlier ones (nat_rec's rule); a
                          * skinned vertex's two indices (natdraw.h KH1_NAT_SKIN) both */
            u32 j, vq = d[3] & KH1_NAT_SKIN ? 3 : 2, add = vq == 3 ? nat_cmoff | nat_cmoff << 16 : nat_cmoff;
            for (j = 0; j < d[2]; j++) nat_op[nat_crq + 1 + j * vq][3] += add;
        }
        nat_crq += nq;
        nat_cnrec++;
        d += nq * 4;
        nqw -= nq;
    }
}
static void r_nat_end(const u32 *a, const u32 *d, u32 nqw) {
    u32 nmat = nat_op[0][2];
    (void)d;
    (void)nqw;
    if (!nat_cnrec || nat_crq + nmat * 4 > NAT_QW) return;
    nat_op[0][1] = nat_cnrec;
    nat_op[0][3] = nat_crq - 2;
    memcpy(nat_op[nat_crq], nat_cms, nmat * 64);
    r_native(a, nat_op[0], nat_crq + nmat * 4);
}

/* 2026-11-01 (native-plan.md stage 0: w_native 800 ms per 2.4 s on the Vita's GS worker, ~3x its instruction count's
 * share): a payload's records are contiguous, so the ones nat_rec takes are put to the recording queue as one op at
 * the payload's end (or before any other op of the native path), not one op each: one queue put (its atomic loads
 * and stores, barriers on ARM) a span instead of a record.  r_nat_rec takes any number of records already, so the
 * GPU thread's side is unchanged.  kh1_pipes_nat_span 0 (config.txt natspan=0) puts each record as before */
int kh1_pipes_nat_span = 1;
static const u32 *span_p;
static u32 span_nq;

/* 2026-11-01 (docs/native-plan.md "Native payloads by reference", dmawalk.c's natref): a payload in the pool
 * (gsqueue.h kh1_pool_*) stays where the game thread wrote it until the GPU thread frees it, so a span of its
 * records goes to the recording queue as a reference: a qword (the records' address, their qwords, a pool position to
 * free once they are read, 1 when there is one), which r_nat_ref reads in place.  The free rides on the payload's
 * last span (or, when it has none, the next span put; the worker's idle hook puts it on its own before the worker
 * sleeps, so a game thread waiting for room is never left waiting).  gsregs.h's kh1_gs_nat_pooled is set while a
 * pooled payload runs, kh1_gs_nat_free the position after it */
static int span_ref, nat_pend_on;
static u32 nat_pend;
static void r_nat_ref(const u32 *a, const u32 *d, u32 nqw) {
    for (; nqw; nqw--, d += 4) {
        if (d[1]) r_nat_rec(a, (const u32 *)(unsigned long)d[0], d[1]);
        if (d[3]) kh1_pool_free(d[2]);
    }
}
static void nat_ref_put(const u32 *p, u32 nq) {
    u32 r[4];
    r[0] = (u32)(unsigned long)p;
    r[1] = nq;
    r[2] = nat_pend;
    r[3] = (u32)nat_pend_on;
    nat_pend_on = 0;
    kh1_recq_put(r_nat_ref, 0, 0, r, 1);
}
/* the GS worker idle (gsqueue.c kh1_gsq_idle_hook): a free still held back goes on its own */
static void nat_idle(void) {
    if (nat_pend_on) nat_ref_put(0, 0);
}
/* dmawalk.c, after a pooled payload's run (gsregs.h kh1_gs_nat_done): the pool up to free may be freed after the
 * records put so far */
static void nat_done(u32 free) {
    nat_pend = free;
    nat_pend_on = 1;
}

static void span_flush(void) {
    if (!span_nq) return;
    if (span_ref) nat_ref_put(span_p, span_nq);
    else kh1_recq_put(r_nat_rec, 0, 0, span_p, span_nq);
    span_nq = 0;
}

/* 2026-11-02 (docs/native-plan.md "Native payloads straight to the GPU thread", dmawalk.c's natdirect): a payload drawn
 * in one PRIM goes to the GPU thread whole, as one reference op, and the GPU thread does what nat_hook and nat_rec do
 * here for it: the joins with the open op (P0's same header and matrix, P13's same header with its matrices added),
 * an op opened at the first record that fits, ended where one would not fit, and at the payload's end unless it is
 * P0's or P13's (they can stay open).  The worker keeps only what decides a join without the payload's bytes: the PRIM
 * and the GS state's generation the open op was drawn in (dir_prim, dir_gen); when either changed it ends the op
 * first, so the GPU thread joins only when nat_rec would have.  The state op before an open goes as before
 * (prim_state).  nat_flush ends an op the GPU thread may hold (r_nat_dend) before any other recording op, as it ends
 * the worker's own.  The GPU thread frees the pool up to the payload's end once it has read it */
static int dir_open, nat_copen;
static u32 dir_prim, dir_gen;
u32 kh1_pipes_nat_dir_ends; /* the GPU thread's ops ended by the worker (r_nat_dend), for the log */
static void r_nat_dend(const u32 *a, const u32 *d, u32 nqw) {
    if (!nat_copen) return;
    nat_copen = 0;
    r_nat_end(a, d, nqw);
}
static void r_nat_dir(const u32 *a, const u32 *d, u32 nqw) {
    for (; nqw; nqw--, d += 4) {
        const u32 *h = (const u32 *)(unsigned long)d[0], *rec = h + 8, *mats;
        u32 prog = h[0] & 0xFF, nrec = h[1], nmat = h[2], r;
        mats = h + (2 + h[3]) * 4;
        /* nat_hook's what 0: the joins */
        if (nat_copen && prog == 0 && (nat_op[0][0] & 0xFF) == 0 && nmat == nat_op[0][2] && !memcmp(h + 4, nat_op[0] + 4, 16) &&
            !memcmp(mats, nat_cms, nmat * 64)) {
        } else if (nat_copen && prog == 13 && h[0] == nat_op[0][0] && !memcmp(h + 4, nat_op[0] + 4, 16) &&
                   nat_op[0][2] + nmat <= KH1_NAT_MATS) {
            memcpy(nat_cms + nat_op[0][2] * 16, mats, nmat * 64);
            nat_cmoff = nat_op[0][2];
            nat_op[0][2] += nmat;
        } else if (nat_copen) {
            nat_copen = 0;
            r_nat_end(a, 0, 0);
        }
        /* nat_rec, a record at a time */
        for (r = 0; r < nrec; r++) {
            u32 nq = KH1_NAT_REC_QW(rec);
            if (nat_copen && nat_crq + nq + nat_op[0][2] * 4 > NAT_QW) {
                nat_copen = 0;
                r_nat_end(a, 0, 0);
            }
            if (!nat_copen) {
                if (2 + nq + nmat * 4 > NAT_QW || nmat > KH1_NAT_MATS) { /* cannot fit */
                    rec += nq * 4;
                    continue;
                }
                memcpy(nat_op[0], h, 32);
                memcpy(nat_cms, mats, nmat * 64);
                nat_crq = 2;
                nat_cnrec = 0;
                nat_cmoff = 0;
                nat_copen = 1;
            }
            r_nat_rec(a, rec, nq);
            rec += nq * 4;
        }
        /* nat_hook's what 2: only P0's and P13's ops stay open */
        if (nat_copen && prog != 0 && prog != 13) {
            nat_copen = 0;
            r_nat_end(a, 0, 0);
        }
        kh1_pool_free(d[2]);
    }
}
/* the worker's side (gsregs.h kh1_gs_nat_direct, dmawalk.c w_native_dir) */
static int nat_direct(u32 prim, u32 prog, const u32 *p, u32 nqw, u32 free) {
    u32 a, r[4];
    recorder();
    if (nat_open || !dir_open || prim != dir_prim || kh1_gs_gen != dir_gen) nat_flush();
    nat_pend_on = 0; /* a free held back is before this one, which the GPU thread does after it */
    /* 2026-11-02: prim_state only when it has something to do (its own first test, and a texture lookup pending): most
     * payloads come in the state of the one before */
    if (!have_last || kh1_gs_gen != last_gen || prim != last_prim || (tex_look && prim >> 4 & 1)) prim_state(prim);
    a = (u32)kh1_gs_xshift_of();
    r[0] = (u32)(unsigned long)p;
    r[1] = nqw;
    r[2] = free;
    r[3] = 0;
    kh1_recq_put(r_nat_dir, &a, 1, r, 1);
    dir_open = prog == 0 || prog == 13;
    dir_prim = prim;
    dir_gen = kh1_gs_gen;
    return 1;
}

static void nat_flush(void) {
    u32 a;
    span_flush();
    if (dir_open) {
        dir_open = 0;
        a = (u32)kh1_gs_xshift_of();
        kh1_recq_put(r_nat_dend, &a, 1, 0, 0);
        kh1_pipes_nat_dir_ends++;
    }
    if (!nat_open) return;
    nat_open = 0;
    if (!nat_nrec) return;
    a = (u32)kh1_gs_xshift_of();
    kh1_recq_put(r_nat_end, &a, 1, 0, 0);
}

/* the GS worker's side (gsregs.h's kh1_gs_native_hook): a payload starts (its header, its matrices), each record with
 * the PRIM in force, the end */
static void nat_rec(u32 prim, const u32 *r) {
    u32 nq = KH1_NAT_REC_QW(r);
    if (nat_open && (prim != nat_prim || kh1_gs_gen != nat_gen || nat_rq + nq + nat_hs[2] * 4 > NAT_QW)) nat_flush();
    if (!nat_open && 2 + nq + nat_hdr[2] * 4 > NAT_QW) return; /* cannot fit */
    if (!nat_open) {
        u32 w[2 * 4 + KH1_NAT_MATS * 16];
        memcpy(nat_hs, nat_hdr, 32);
        memcpy(nat_ms, nat_mats, nat_hdr[2] * 64);
        prim_state(prim);
        nat_open = 1;
        nat_prim = prim;
        nat_gen = kh1_gs_gen;
        nat_rq = 2;
        nat_nrec = 0;
        nat_moff = 0;
        memcpy(w, nat_hs, 32);
        memcpy(w + 8, nat_ms, nat_hs[2] * 64);
        kh1_recq_put(r_nat_open, 0, 0, w, 2 + nat_hs[2] * 4);
    }
    /* joins the records before it while the queue holds them unpublished; a joined P13 run's matrix indices are
     * moved on the recorder's side (r_nat_mats, r_nat_rec) */
    if (!kh1_pipes_nat_span && !kh1_gs_nat_pooled) kh1_recq_put(r_nat_rec, 0, 0, r, nq);
    else if (span_nq && span_p + span_nq * 4 == r) span_nq += nq;
    else {
        span_flush();
        span_p = r;
        span_nq = nq;
        span_ref = kh1_gs_nat_pooled;
    }
    nat_rq += nq;
    nat_nrec++;
}

static void nat_hook(u32 what, u32 prim, const u32 *a, const u32 *b) {
    if (what == 0) {
        /* 2026-10-31: a P0 run with the open op's header and matrix joins it (nat_rec still ends it at a new PRIM or
         * state); anything else ends it */
        if (nat_open && (a[0] & 0xFF) == 0 && (nat_hs[0] & 0xFF) == 0 && a[2] == nat_hs[2] &&
            !memcmp(a + 4, nat_hs + 4, 16) && !memcmp(b, nat_ms, a[2] * 64)) {
        } else if (nat_open && (a[0] & 0xFF) == 13 && a[0] == nat_hs[0] && !memcmp(a + 4, nat_hs + 4, 16) &&
                   nat_hs[2] + a[2] <= KH1_NAT_MATS) {
            /* 2026-10-31: a P13 run with the open P13 op's colour, F and cull joins it, its matrices after the op's
             * (its vertices' indices moved by nat_rec); a new PRIM, state or a full op still ends it (P13 is one
             * run a model part, ~200 a Dive picture) */
            memcpy(nat_ms + nat_hs[2] * 16, b, a[2] * 64);
            nat_moff = nat_hs[2];
            nat_hs[2] += a[2];
            span_flush(); /* the earlier runs' records before the matrices that follow them */
            kh1_recq_put(r_nat_mats, &nat_moff, 1, b, a[2] * 4); /* the recorder's side of the join */
        } else {
            nat_flush();
        }
        nat_hdr = a;
        nat_mats = b;
    } else if (what == 1) {
        nat_rec(prim, a);
    } else {
        /* the payload's records are only valid during the worker's op (a pooled one's until its free: put with its
         * last span) */
        if (kh1_gs_nat_pooled) nat_done(kh1_gs_nat_free);
        span_flush();
        if ((nat_hdr[0] & 0xFF) != 0 && (nat_hdr[0] & 0xFF) != 13) nat_flush();
    }
}

/* session 126: called with the frame's commands before they are cleared (tests/host/cmdbuf_test.c) */
void (*kh1_pipes_frame_hook)(const KH1CmdRec *r);

/* session 126: each distinct pass list (by targets, loads and stores) printed once, up to 32 */
static u32 seq_sig[32], nseq, seq_frames[32];

/* 2026-10-31: 1 (the default) also records the frame's GXM calls here for the run's report (gxmrec.h); the Vita sets
 * 0: its GPU work (gxm.c) records them again itself, so here they were only counted, not drawn */
int kh1_pipes_gxm_count = 1;

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
    { /* KH1_HOST_CMDDUMP=A[:B]: frames A .. B's commands and passes in full (the GPU cost study, vita-build.md) */
        static int dump_set;
        static u32 dump_a, dump_b;
        if (!dump_set) {
            const char *e = getenv("KH1_HOST_CMDDUMP");
            dump_set = 1;
            if (e) {
                dump_a = (u32)strtoul(e, 0, 0);
                dump_b = strchr(e, ':') ? (u32)strtoul(strchr(e, ':') + 1, 0, 0) : dump_a;
            } else {
                dump_a = 1;
            }
        }
        if (rec->b.frames >= dump_a && rec->b.frames <= dump_b) {
            u32 pi = ~0u;
            printf("kh1-host: frame %u's commands: %u passes, %u commands\n", rec->b.frames, rec->npass, rec->ncmd);
            for (i = 0; i < rec->ncmd; i++) {
                const KH1Cmd *c = &rec->cmd[i];
                if (c->kind == KH1_CMD_DRAW && c->pass != pi && c->pass < rec->npass) {
                    pi = c->pass;
                    printf("kh1-host:  pass %u: %s\n", pi + 1, kh1_cmd_pass_str(&rec->pass[pi]));
                }
                printf("kh1-host:   %u: %s", i, kh1_cmd_str(rec, c));
                if (c->kind == KH1_CMD_DRAW)
                    printf(" tex0 %08x | %s", c->d.tex0_lo, c->d.n ? kh1_pipekey_str(&c->d.pipe[0]) : "nothing");
                printf("\n");
            }
        }
    }
    if (kh1_pipes_gxm_count) {
        kh1_gxm_frame(gxm, rec);
        if (gxm->frame.calls > gxm_max_calls) gxm_max_calls = gxm->frame.calls;
        if (gxm->frame.scenes > gxm_max_scenes) gxm_max_scenes = gxm->frame.scenes;
    }
}

/* 2026-11-02 (natdraw.h natvb): with no GPU renderer of its own fencing them (kh1_natvb_fenced), the frame's commands
 * have been read once the frame ends: its cached runs' entries are free to go */
static void vb_frame_done(void) {
    if (!kh1_natvb_fenced && rec->xseq) kh1_natvb_publish(rec->xseq);
}

static void frame_end(void) {
    vb_frame_done();
    kh1_cmd_reset_frame(rec);
    kh1_palcache_frame(pal);
    if (tex_ok) kh1_texcache_frame(tex);
    tex_look = pal_look = 1;
    lt_ok = 0; /* the frame's first lookup marks its entry the frame's (kh1_texcache_get) */
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

/* 2026-10-31 (the native renderer's Vita run: the GS worker's frame op ~7 ms a frame, the game waiting ~0.7 s per
 * 2.4 s for the worker): the frame op's time by part, on kh1_vu1_clock (the Vita's watchdog prints them): 0 the
 * native op's flush, 1 the wait for the frame's recording, 2 the passes (frame_begin: kh1_cmd_frame and its log),
 * 3 the wait for the GPU thread's last frame, 4 the copies for the GPU thread (snap_frame), 5 the rest; 6 the passes
 * when the frame op runs on the GPU thread (r_frame: that thread's time, not the worker's) */
volatile u32 kh1_pipes_frame_us[7];
extern u32 (*kh1_vu1_clock)(void);
static u32 pf_t;
static void pf_mark(int part) {
    u32 t;
    if (!kh1_vu1_clock) return;
    t = kh1_vu1_clock();
    if (part >= 0) kh1_pipes_frame_us[part] += t - pf_t;
    pf_t = t;
}

/* 2026-10-31 (docs/vita-build.md "The frame op on the GPU thread"): with the recording on the GPU frame's thread
 * (kh1_recq), the frame op is one more recording op there: the passes (frame_begin), the frame's GPU work (the hook,
 * on the recorder itself: nothing else writes it until the op ends) and the recorder's reset.  The GS worker only
 * copies what the GPU work reads of its own state (GS memory, the texels and palettes the frame's commands name,
 * marked as it handed them on: fr_tex, fr_pal) and goes on; it no longer waits for the frame's recording.  It waits
 * for the last frame op only when it must change those copies.  kh1_pipes_rq_frame 0 (config.txt recframe=0,
 * KH1_HOST_RECFRAME=0) keeps the frame op on the worker */
int kh1_pipes_rq_frame = 1;
static u32 rq_pos;   /* the queue's position after the last frame op put */
static int rq_posted;

static void r_frame(const u32 *a, const u32 *d, u32 n) {
    u32 t0 = kh1_vu1_clock ? kh1_vu1_clock() : 0;
    (void)d;
    (void)n;
    frame_begin();
    if (kh1_vu1_clock) kh1_pipes_frame_us[6] += kh1_vu1_clock() - t0;
    kh1_pipes_job_arg = a[0];
    kh1_pipes_frame_hook(rec);
    vb_frame_done();
    kh1_cmd_reset_frame(rec);
}

/* the copies of the marked entries (snap_frame's, from the marks) */
static int snap_marked(void) {
    u32 i, need = 0;
    if (!snap_pal && !(snap_pal = (u32 (*)[256])malloc(KH1_PALCACHE_SLOTS * 1024))) return -1;
    if (kh1_gsmem_snap_take() < 0) return -1;
    memset(snap_hastex, 0, sizeof snap_hastex);
    memset(snap_haspal, 0, sizeof snap_haspal);
    for (i = 0; i < KH1_TEXCACHE_SLOTS; i++)
        if (fr_tex[i] && tex_ok && tex->slot[i].tex) {
            snap_texoff[i] = need;
            snap_hastex[i] = 1;
            need += tex->slot[i].n;
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
    for (i = 0; i < KH1_PALCACHE_SLOTS; i++)
        if (fr_pal[i]) {
            memcpy(snap_pal[i], pal->slot[i].col, 1024);
            snap_haspal[i] = 1;
        }
    return 0;
}

/* the frame op as a recording op; 0 when put, -1 when a copy failed (the frame op then stays on the worker) */
static int rq_frame(void) {
    u32 a = kh1_pipes_frame_arg;
    /* the copies change only when the frame wrote GS memory or decoded or filled an entry: else the op reads the
     * copies the last one does (the Dive's every other frame: nothing drawn) and nothing waits */
    if (fr_marks || !kh1_gsmem_snap_same()) {
        pf_mark(2);
        if (rq_posted) kh1_recq_wait(rq_pos); /* the last frame op is done with the copies */
        pf_mark(3);
        if (snap_marked()) {
            printf("kh1-host: pipes: the frame's copy failed (no memory): the GPU frame on the GS worker from now\n");
            kh1_pipes_snap = 0;
            return -1;
        }
        pf_mark(4);
    }
    memset(fr_tex, 0, sizeof fr_tex);
    memset(fr_pal, 0, sizeof fr_pal);
    fr_marks = 0;
    kh1_recq_put(r_frame, &a, 1, 0, 0);
    rq_pos = kh1_recq_pos();
    rq_posted = 1;
    kh1_recq_flush(); /* to the thread now (and the next frame op never joins this one) */
    /* frame_end's worker side: the caches are the worker's */
    kh1_palcache_frame(pal);
    if (tex_ok) kh1_texcache_frame(tex);
    tex_look = pal_look = 1;
    lt_ok = 0; /* the frame's first lookup marks its entry the frame's (kh1_texcache_get) */
    pf_mark(5);
    return 0;
}

void kh1_pipes_frame(void) {
    oc_ok = 0; /* the next frame's first CLUT load is sent (on_clut) */
    pf_mark(-1);
    nat_flush();
    pf_mark(0);
    if (kh1_pipes_rq_frame && kh1_pipes_snap && kh1_recq_on && kh1_pipes_frame_hook && rec && !rq_frame()) return;
    memset(fr_tex, 0, sizeof fr_tex);
    memset(fr_pal, 0, sizeof fr_pal);
    fr_marks = 0;
    kh1_recq_sync(); /* session 146: the frame's recording done */
    pf_mark(1);
    frame_begin();
    pf_mark(2);
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
        pf_mark(3);
        empty_posted = 0;
        if (snap_frame()) {
            printf("kh1-host: pipes: the frame's copy failed (no memory): the GPU frame on this thread from now\n");
            kh1_pipes_snap = 0;
            kh1_pipes_job_arg = a;
            kh1_pipes_frame_hook(rec);
        } else if (kh1_pipes_gpu_put) {
            pf_mark(4);
            kh1_pipes_gpu_put(w_hook, &a, 1);
        } else {
            pf_mark(4);
            w_hook(&a, 0, 0);
        }
    } else if (kh1_pipes_frame_hook) {
        kh1_pipes_job_arg = kh1_pipes_frame_arg;
        kh1_pipes_frame_hook(rec);
    }
    frame_end();
    pf_mark(5);
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
           "%u read a render target, %u write one; %u scenes split by a transfer on their own target, %u uploads into "
           "another target inside a scene; %u times passes drawn ahead of a scene they split\n", t->uploads, t->copies,
           t->cluts, t->pal_fills, t->textures, t->texels, t->tgt_reads, t->tgt_writes, t->splits, t->xfer_joins, t->hoists);
    {   /* session 128: the GXM calls (include/platform/gxmrec.h) */
        const KH1GxmCount *g = &gxm->total;
        printf("kh1-host:   gxm: %u frames, %u calls (a frame at most %u, %u scenes), %u scenes (%u load, %u store), %u draws, "
               "%u program sets, %u texture sets, %u region sets; %u texture uploads, %u palette fills, %u palette "
               "read-backs, %u target uploads, %u blits; %u lost\n", g->frames, g->calls, gxm_max_calls, gxm_max_scenes,
               g->scenes, g->loads, g->stores, g->draws, g->programs, g->textures, g->regions, g->tex_uploads, g->pal_fills,
               g->pal_readbacks, g->target_uploads, g->blits, g->lost);
    }
    if (kh1_pipes_nat_draws) /* 2026-11-01: the native runs, and those joined into the draw before them (cmdbuf.c nat_join) */
        printf("kh1-host:   native: %u runs drawn, %u triangles; natjoin=%d: %u runs joined into the draw before; not "
               "joined: %u after another command, %u another cull mode or vertex kind, %u another state or texture, %u no "
               "room\n", kh1_pipes_nat_draws, kh1_pipes_nat_tris, kh1_cmd_natjoin, kh1_cmd_nat_joins, kh1_cmd_nat_nojoin[0],
               kh1_cmd_nat_nojoin[1], kh1_cmd_nat_nojoin[2], kh1_cmd_nat_nojoin[3]);
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
    nat_flush();
    kh1_recq_sync();
    if (rec) {
        if (batcher.frame.prims) {
            kh1_pipes_frame(); /* the last frame's primitives */
            kh1_recq_sync();   /* on the GPU thread with kh1_pipes_rq_frame */
        }
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
