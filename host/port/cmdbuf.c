/* The draw list as GPU commands (include/platform/cmdbuf.h, docs/renderer-spec.md 4.13 "Session 126"):
 * batch.h's batches recorded with their vertices and uniforms in ring.h's rings, column groups held
 * until they end, and each pass's load / store needs decided at the frame end.  Session 127 (4.13
 * "Session 127"): the transfers, CLUT loads and texture decodes recorded between the draws.  Checked by
 * tests/host/cmdbuf_test.c and run over a host run (host/null/pipes.c, KH1_HOST_TRACE=5) and the ELF's
 * static packets (tools/host/drawpipes.py --passes).  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/cmdbuf.h"
#include "platform/natdraw.h"
#include "platform/shadergen.h"

void *memset(void *, int, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);
void *memmove(void *, const void *, __SIZE_TYPE__);
int sprintf(char *, const char *, ...);
__SIZE_TYPE__ strlen(const char *);

static u32 tgt_key(u32 rt, u32 fbp, u32 fbw) { return rt | fbp << 8 | fbw << 20; }

/* a colour target's index, added when add is set; ~0 when unknown */
static u32 tgt_find(KH1CmdRec *r, u32 key, int add) {
    u32 i;
    for (i = 0; i < r->ntgt; i++)
        if (r->tgt[i] == key) return i;
    if (!add || r->ntgt == KH1_CMD_TARGETS) return ~0u;
    r->tgt[r->ntgt] = key;
    r->tdrawn[r->ntgt] = 0;
    r->tpages[r->ntgt] = 0;
    return r->ntgt++;
}

/* session 127: 1 + the target whose pages the rectangle (x, y) w x h of a buffer at block bp, bw wide lies in
 * (page granularity, a CT32 page's 64 x 32 pixels, as host/null/gsmem.c marks them), 0 none */
static u8 tgt_at(const KH1CmdRec *r, u32 bp, u32 bw, u32 x, u32 y, u32 w, u32 h) {
    u32 p0, p1, i;
    if (!bw) bw = 1;
    if (!w) w = 1;
    if (!h) h = 1;
    p0 = bp / 32 + y / 32 * bw + x / 64;
    p1 = bp / 32 + (y + h - 1) / 32 * bw + (x + w - 1) / 64;
    for (i = 0; i < r->ntgt; i++) {
        u32 f = r->tgt[i] >> 8 & 0xFFF;
        if (p0 < f + r->tpages[i] && p1 >= f) return (u8)(i + 1);
    }
    return 0;
}

/* session 137v: the GS pages of a buffer rectangle marked (mode 1), cleared (0) or tested (2) as the CPU's latest
 * write: an upload into a target's pages after its draws (the characters' textures and CLUTs stream into the slot
 * capture's pages), which the texture and palette caches read from GS memory rather than from the target's pixels.
 * A page's pixels by the PSM's bits: 32 64 x 32, 16 64 x 64, 8 128 x 64, 4 128 x 128. */
static int cpu_pages(KH1CmdRec *r, u32 bp, u32 bw, u32 psm, u32 x, u32 y, u32 w, u32 h, int mode) {
    u32 bits = psm == 0x13 || psm == 0x1B ? 8 : psm == 0x14 || psm == 0x24 || psm == 0x2C ? 4 : psm == 2 || psm == 0xA ||
               psm == 0x32 || psm == 0x3A ? 16 : 32;
    u32 pw = bits <= 8 ? 128 : 64, ph = bits == 32 ? 32 : bits == 4 ? 128 : 64, row, p, yy;
    if (!bw) bw = 1;
    if (!w) w = 1;
    if (!h) h = 1;
    row = (bw * 64 + pw - 1) / pw;
    for (yy = y / ph; yy <= (y + h - 1) / ph; yy++)
        for (p = bp / 32 + yy * row + x / pw; p <= bp / 32 + yy * row + (x + w - 1) / pw && p < 512; p++) {
            if (mode == 2) { if (r->cpu_pages[p >> 5] >> (p & 31) & 1) return 1; }
            else if (mode) r->cpu_pages[p >> 5] |= 1u << (p & 31);
            else r->cpu_pages[p >> 5] &= ~(1u << (p & 31));
        }
    return 0;
}

/* the same scene: the same colour target, and the same depth buffer or none on one side (a draw that neither
 * tests nor writes Z draws the same with the pass's depth buffer bound, so the scene goes on; batch.c's pass
 * count still splits there) */
static int same_pass(const KH1CmdPass *p, const KH1BatchKey *k) {
    return p->rt == k->rt && p->psm == k->psm && p->fbp == k->fbp && p->fbw == k->fbw &&
           (p->depth == k->depth || p->depth == KH1_DS_NONE || k->depth == KH1_DS_NONE);
}

static void new_pass(KH1CmdRec *r, const KH1BatchKey *k, const KH1RenderPass *rp) {
    KH1CmdPass *p;
    f32 *u;
    u32 t;
    if (r->npass == KH1_CMD_PASSES) { r->dropped++; return; }
    p = &r->pass[r->npass++];
    memset(p, 0, sizeof *p);
    p->rt = k->rt;
    p->psm = k->psm;
    p->depth = k->depth;
    p->fbp = k->fbp;
    p->fbw = k->fbw;
    p->w = rp->w;
    p->h = rp->h;
    p->cmd0 = r->ncmd;
    t = tgt_find(r, tgt_key(k->rt, k->fbp, k->fbw), 1);
    p->tgt = t == ~0u ? 0xFF : (u8)t;
    if (t != ~0u) r->tsw[t] = rp->ox != 0.0f && rp->scale > 0.0f ? (f32)rp->w / rp->scale : 0.0f;
    if (t != ~0u) { /* the GS pages it spans: FBW by its rows (the pass's height unscaled) */
        u32 rows = (u32)(rp->scale > 0.0f ? rp->h / rp->scale + 0.5f : (f32)rp->h), n = (k->fbw ? k->fbw : 1) * ((rows + 31) / 32);
        if (n > r->tpages[t]) r->tpages[t] = n;
        { /* session 137v: the GPU writes these pages from here on */
            u32 q;
            for (q = k->fbp; q < k->fbp + n && q < 512; q++) r->cpu_pages[q >> 5] &= ~(1u << (q & 31));
        }
    }
    u = (f32 *)kh1_ring_alloc(&r->uring, KH1_RING_UNIFORM_SLOT, KH1_RING_UNIFORM_SLOT);
    if (u) {
        u[0] = rp->w ? 2.0f / rp->w : 0.0f;
        u[1] = rp->h ? 2.0f / rp->h : 0.0f;
        u[2] = u[3] = -1.0f;
        p->uoff = (u32)((u8 *)u - (r->uring.base + r->uring.cur * r->uring.slot));
    } else {
        r->frame.lost++;
    }
}

/* the target a draw samples (1 + its index; 0 none: no texture, or GS memory's texels through the texture cache) */
static u32 sampled(KH1CmdRec *r, const KH1DrawState *d, u8 *wtex) {
    *wtex = 0;
    if (d->pipe[0].shader.tex) {
        u32 tbp = d->tex0_lo & 0x3FFF, tbw = d->tex0_lo >> 14 & 63, psm = d->tex0_lo >> 20 & 63, t;
        /* session 137v: not when an upload wrote its pages since the target's last draw (cpu_pages) */
        if (!(tbp & 31)) {
            t = tgt_find(r, tgt_key(kh1_target_id(tbp / 32, tbw, psm), tbp / 32, tbw), 0);
            if (t != ~0u) { /* the texture's rows inside the target (a 512-row binding of a 384-row target) */
                u32 th = 1u << ((d->tex0_lo >> 30 | d->tex0_hi << 2) & 15), rows = r->tpages[t] / (tbw ? tbw : 1) * 32;
                if (!cpu_pages(r, tbp, tbw, psm, 0, 0, 1u << (d->tex0_lo >> 26 & 15), th < rows || !rows ? th : rows, 2)) {
                    *wtex = r->tsw[t] > 0.0f;
                    return t + 1;
                }
            }
        }
    }
    return 0;
}

static void new_cmd(KH1CmdRec *r, const KH1BatchKey *k, const KH1DrawState *d, const KH1RenderPass *rp) {
    KH1Cmd *c;
    u8 *u, wtex;
    u32 smp = sampled(r, d, &wtex);
    int same = r->npass && same_pass(&r->pass[r->npass - 1], k);
    if (same && !r->split && smp && (r->pwrote >> (smp - 1) & 1)) r->split = 1; /* a target written in this pass */
    if (same && r->split) r->frame.splits++;
    if (!same || r->split) {
        new_pass(r, k, rp);
        r->pwrote = 0;
        smp = sampled(r, d, &wtex); /* new_pass gave the target's pages back to the GPU (cpu_pages) */
    } else if (r->pass[r->npass - 1].depth != k->depth && k->depth != KH1_DS_NONE) {
        r->pass[r->npass - 1].depth = k->depth; /* the scene binds the depth buffer from its start */
        r->frame.depth_joins++;
    } else if (r->pass[r->npass - 1].depth != k->depth) {
        r->frame.depth_joins++;
    }
    r->split = 0;
    if (r->ncmd == KH1_CMD_MAX || !r->npass) { r->dropped++; r->cur = -1; return; }
    r->cur = (s32)r->ncmd;
    c = &r->cmd[r->ncmd++];
    memset(c, 0, sizeof *c);
    c->k = *k;
    c->d = *d;
    c->kind = KH1_CMD_DRAW;
    c->tslot = d->pipe[0].shader.tex ? r->tslot : -1;
    c->pslot = d->pipe[0].shader.tex ? r->pslot : -1;
    c->pass = r->npass - 1;
    r->pass[c->pass].ncmd = r->ncmd - r->pass[c->pass].cmd0;
    r->pass[c->pass].ndraw++;
    u = (u8 *)kh1_ring_alloc(&r->uring, KH1_RING_UNIFORM_SLOT, KH1_RING_UNIFORM_SLOT);
    if (u) { /* session 127: what the generated shaders read (shadergen.h: u_a, u_b, u_r, u_c) */
        f32 fu[16];
        memset(u, 0, KH1_RING_UNIFORM_SLOT);
        kh1_shader_uniforms(d, fu);
        memcpy(u, fu, sizeof fu < KH1_RING_UNIFORM_SLOT ? sizeof fu : KH1_RING_UNIFORM_SLOT);
        c->uoff = (u32)(u - (r->uring.base + r->uring.cur * r->uring.slot));
    } else {
        c->lost = 1;
    }
    if (smp) {
        c->samples = (u8)smp;
        c->wtex = wtex;
    }
}

/* Clears (the GS has none): the pass's leading draws that write every channel without reading the target
 * (no blend, no partial mask, no frame fetch, no DATE), as axis-aligned rectangles (sprites) clipped to their
 * command's final scissor (a column group's union), covering the target: the game clears in 32-pixel strips.
 * Coverage is kept on an 8 x 8 cell grid (a cell counts when every pixel of it inside the target is covered:
 * cell[] holds a bit per column),
 * so a pass of strips counts as cleared.  For depth the same with the draws that write Z under ALWAYS,
 * before the first draw that tests Z. */
#define CELL 8
#define CELLS_W 128 /* targets up to 1024 x 1024 at the cell size */
static u8 cell[CELLS_W][CELLS_W], cmask[CELLS_W];

static int reads_dst(const KH1DrawState *d, u32 psm) {
    const KH1PipeKey *k = &d->pipe[0];
    return d->setup || k->blend || (k->mask & 7) != 7 || (!(k->mask & 8) && psm != 1) || k->shader.fetch ||
           k->stencil;
}

/* marks the cells the command's rectangles cover; 0 when a primitive is not a rectangle */
static int cover_cmd(const KH1CmdRec *r, const KH1CmdPass *p, const KH1Cmd *c) {
    const KH1GpuVert *v = kh1_cmd_verts(r, c);
    u32 i, j;
    if (!c->hasv || c->lost || c->nv % 6) return 0;
    for (i = 0; i < c->nv; i += 6) {
        f32 x0 = v[i].x, x1 = v[i].x, y0 = v[i].y, y1 = v[i].y;
        s32 px0, px1, py0, py1, cx, cy, cx0;
        for (j = 1; j < 6; j++) {
            if (v[i + j].x < x0) x0 = v[i + j].x;
            if (v[i + j].x > x1) x1 = v[i + j].x;
            if (v[i + j].y < y0) y0 = v[i + j].y;
            if (v[i + j].y > y1) y1 = v[i + j].y;
        }
        for (j = 0; j < 6; j++)
            if ((v[i + j].x != x0 && v[i + j].x != x1) || (v[i + j].y != y0 && v[i + j].y != y1)) return 0;
        /* the pixels whose centres the rectangle covers, inside the scissor and the target */
        px0 = (s32)(x0 - 0.5f + 0.999f);
        py0 = (s32)(y0 - 0.5f + 0.999f);
        px1 = (s32)(x1 - 0.5f + 0.999f);
        py1 = (s32)(y1 - 0.5f + 0.999f);
        if (x0 < 0.5f) px0 = 0;
        if (y0 < 0.5f) py0 = 0;
        if (px0 < c->k.sx0) px0 = c->k.sx0;
        if (py0 < c->k.sy0) py0 = c->k.sy0;
        if (px1 > c->k.sx1) px1 = c->k.sx1;
        if (py1 > c->k.sy1) py1 = c->k.sy1;
        if (px1 > (s32)p->w) px1 = (s32)p->w;
        if (py1 > (s32)p->h) py1 = (s32)p->h;
        /* session 142: only the cells the rectangle can cover (a cell's start at or after px0 / py0, its end
         * rising with it), not the whole grid for every rectangle (Dive to the Heart: 133M of the GS worker's
         * 1,978M host instructions over 60 frames, now 6M) */
        /* session 147d: the columns once, the same for every row (a full-screen rectangle was ~60K instructions) */
        /* 2026-10-31: a cell keeps which of its 8 columns are covered (a bit each, the ones past the target's
         * edge set), so strips that do not meet on the cell grid still add up: the wide view scales the game's
         * 32-pixel strips to 42.3 target pixels (the Dive's depth clear, vita-build.md "The GPU's work in the
         * Dive").  Rows still count whole cells only. */
        if (px1 > CELLS_W * CELL) px1 = CELLS_W * CELL;
        if (px0 >= px1) continue;
        cx0 = px0 / CELL;
        for (cx = cx0; cx * CELL < px1; cx++) {
            s32 a = px0 > cx * CELL ? px0 - cx * CELL : 0, b = px1 < cx * CELL + CELL ? px1 - cx * CELL : CELL;
            u32 m = (0xFFu << a) & (0xFFu >> (CELL - b));
            if (cx * CELL + CELL > (s32)p->w) m |= 0xFFu << ((s32)p->w - cx * CELL);
            cmask[cx] = (u8)m;
        }
        for (cy = py0 > 0 ? (py0 + CELL - 1) / CELL : 0; cy * CELL < (s32)p->h && cy < CELLS_W; cy++) {
            s32 ey = cy * CELL + CELL < (s32)p->h ? cy * CELL + CELL : (s32)p->h, i2;
            if (py1 < ey) break;
            for (i2 = cx0; i2 < cx; i2++) cell[cy][i2] |= cmask[i2];
        }
    }
    return 1;
}

static int all_cells(const KH1CmdPass *p) {
    s32 cx, cy;
    if (!p->w || !p->h || p->w > CELL * CELLS_W || p->h > CELL * CELLS_W) return 0;
    for (cy = 0; cy * CELL < (s32)p->h; cy++)
        for (cx = 0; cx * CELL < (s32)p->w; cx++)
            if (cell[cy][cx] != 0xFF) return 0;
    return 1;
}

/* the pass's cleared / zcleared, from its commands as they end (widened scissors included) */
static void clears(const KH1CmdRec *r, KH1CmdPass *p) {
    u32 j, end = p->cmd0 + p->ncmd;
    if (end > r->ncmd) end = r->ncmd;
    memset(cell, 0, sizeof cell);
    for (j = p->cmd0; j < end && !p->cleared; j++) {
        const KH1Cmd *c = &r->cmd[j];
        const KH1PipeKey *k = &c->d.pipe[0];
        if (c->kind != KH1_CMD_DRAW) continue;
        if (reads_dst(&c->d, p->psm) || (c->samples && c->samples - 1 == p->tgt)) break;
        if (c->d.n == 1 && !k->shader.discard && k->ztest == KH1_ZTST_ALWAYS && !c->nmat && cover_cmd(r, p, c)) p->cleared = all_cells(p);
    }
    if (p->depth == KH1_DS_NONE) return;
    memset(cell, 0, sizeof cell);
    for (j = p->cmd0; j < end && !p->zcleared; j++) {
        const KH1Cmd *c = &r->cmd[j];
        const KH1PipeKey *k = &c->d.pipe[0];
        if (c->kind != KH1_CMD_DRAW) continue;
        if (k->ztest != KH1_ZTST_ALWAYS) break;
        if (k->zwrite && c->d.n == 1 && !k->shader.discard && !c->d.setup && !c->nmat && cover_cmd(r, p, c)) p->zcleared = all_cells(p);
    }
}

static void prim(KH1CmdRec *r, const KH1BatchKey *k, u32 src) {
    const KH1DrawState *d = r->in_d;
    const KH1RenderPass *rp = r->in_p;
    const KH1GpuVert *v = r->in_v;
    u32 n = r->in_n, stride;
    KH1Cmd *c;
    KH1CmdPass *p;
    u8 *at;
    if (src != KH1_BEV_NEW) {
        const KH1CmdGrpPrim *g = &r->grp[src];
        d = &g->d;
        rp = &g->p;
        v = v ? g->v : 0;
        n = g->n;
    }
    if (r->open_pending) {
        r->open_pending = 0;
        new_cmd(r, k, d, rp);
    }
    if (r->cur < 0 || r->dropped) return;
    c = &r->cmd[r->cur];
    p = &r->pass[c->pass];
    if (d->pipe[0].ztest != KH1_ZTST_ALWAYS) {
        p->ztest = 1;
        p->zseen = 1;
    }
    if (d->pipe[0].zwrite) {
        p->zwrite = 1;
        p->zseen = 1;
    }
    if (c->samples && c->samples - 1 == p->tgt) p->feedback = 1;
    /* 2026-11-01: a skinned native draw's vertices are bigger (KH1GpuVertSk), still from a 32-byte boundary */
    stride = src == KH1_BEV_NEW && r->in_skin ? (u32)sizeof(KH1GpuVertSk) : (u32)sizeof(KH1GpuVert);
    at = (u8 *)kh1_ring_alloc(&r->vring, n * stride, (u32)sizeof(KH1GpuVert));
    if (!at) {
        c->lost = 1;
    } else {
        if (v) memcpy(at, v, n * stride);
        if (v && c->wtex && stride == (u32)sizeof(KH1GpuVert)) { /* wide screen: s (over TW's 2^n texels) over the target's whole width, the same texels: a
                             * full-screen pass's u, stretched to the view, runs past 512 (the frame copy's 0 .. 678) */
            u32 lw = d->tex0_lo >> 26 & 15, i;
            f32 kk = (f32)(1u << (lw > 10 ? 10 : lw)) / r->tsw[c->samples - 1];
            for (i = 0; i < n; i++) ((KH1GpuVert *)at)[i].s *= kk;
        }
        if (!c->prims) c->hasv = v != 0;
        else if (!v) c->hasv = 0;
        if (!c->nv) c->v0 = (u32)(at - (r->vring.base + r->vring.cur * r->vring.slot)) / (u32)sizeof(KH1GpuVert);
    }
    c->nv += n;
    c->prims++;
}

static void on_event(void *ctx, u32 what, const KH1BatchKey *k, u32 arg) {
    KH1CmdRec *r = (KH1CmdRec *)ctx;
    s32 i;
    switch (what) {
    case KH1_BEV_OPEN:
        r->open_pending = 1;
        break;
    case KH1_BEV_PRIM:
        prim(r, k, arg);
        break;
    case KH1_BEV_REC:
        if (arg < KH1_BATCH_GROUP) {
            KH1CmdGrpPrim *g = &r->grp[arg];
            g->d = *r->in_d;
            g->p = *r->in_p;
            g->n = r->in_n > 6 ? 6 : r->in_n;
            if (r->in_v) memcpy(g->v, r->in_v, g->n * sizeof *g->v);
        }
        break;
    case KH1_BEV_GROUP:
        r->held = arg && r->cur >= 0 ? r->cur : -1;
        break;
    case KH1_BEV_WIDEN:
        if (r->held >= 0)
            for (i = r->held; i < (s32)r->ncmd; i++)
                if (r->cmd[i].kind == KH1_CMD_DRAW) r->cmd[i].k.sx1 = (s32)arg;
        break;
    case KH1_BEV_END:
        r->held = -1;
        break;
    }
    if (r->held >= 0 && r->ncmd - (u32)r->held > r->frame.held_max) r->frame.held_max = r->ncmd - (u32)r->held;
}

void kh1_cmd_init(KH1CmdRec *r, void *vmem, u32 vslot, void *umem, u32 uslot) {
    memset(r, 0, sizeof *r);
    kh1_batch_reset(&r->b);
    r->b.ev = on_event;
    r->b.ev_ctx = r;
    kh1_ring_init(&r->vring, vmem, vslot);
    kh1_ring_init(&r->uring, umem, uslot);
    r->held = -1;
    r->cur = -1;
    r->tslot = r->pslot = -1;
}

void kh1_cmd_prim(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVert *v, u32 n, u32 sig) {
    r->in_d = d;
    r->in_p = p;
    r->in_v = v;
    r->in_n = n;
    kh1_batch_prim_sig(&r->b, d, p, n, sig);
}

static void native(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVert *v, u32 n, const f32 *mats,
                   u32 nmat, u32 cull, u32 skin);

/* 2026-11-01 (docs/native-plan.md stage 1, "Batching"): a native run joins the draw command before it when that is the
 * last command of the list and a native draw with the same batch key (pipelines, uniforms, sampler, texture, target,
 * scissor), texture entry and palette slot, cull mode and vertex kind, with room for both runs' matrices in u_m
 * (KH1_NAT_MATS), and both rings' heads still right after its vertices and matrices.  Then the run's vertices and
 * matrices are appended to the command's, its vertices' matrix indices moved past the command's earlier matrices: the
 * same triangles in the same order, in one GPU draw instead of one a run.  Nothing else can have come between them (a
 * transfer, a CLUT load or a texture upload is a command of its own; a texture bind without one changes r->tslot).
 * kh1_cmd_natjoin 0 (config.txt natjoin=0, host KH1_HOST_NATJOIN=0) gives each run its own command as before */
int kh1_cmd_natjoin = 1;
u32 kh1_cmd_nat_joins; /* runs joined so far */
u32 kh1_cmd_nat_nojoin[4]; /* runs not joined: another command (or none) before; another cull mode or vertex kind; another
                            * state, texture or palette; no room (32 matrices, the rings) */
static int nat_join(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVert *v, u32 n, const f32 *mats,
                    u32 nmat, u32 cull, u32 skin) {
    KH1Cmd *c;
    KH1BatchKey k;
    u32 stride = skin ? (u32)sizeof(KH1GpuVertSk) : (u32)sizeof(KH1GpuVert), vend, mend, i, off;
    u8 *at, *u;
    if (r->cur < 0 || r->dropped || (u32)r->cur + 1 != r->ncmd || r->split || r->held >= 0) {
        kh1_cmd_nat_nojoin[0]++;
        return 0;
    }
    c = &r->cmd[r->cur];
    if (c->kind != KH1_CMD_DRAW || !c->nmat || c->lost || !c->hasv || c->pass + 1 != r->npass) {
        kh1_cmd_nat_nojoin[0]++;
        return 0;
    }
    if (c->skin != skin || c->cull != (cull & ~KH1_NAT_LIN)) {
        kh1_cmd_nat_nojoin[1]++;
        return 0;
    }
    if (c->nmat + nmat > KH1_NAT_MATS) {
        kh1_cmd_nat_nojoin[3]++;
        return 0;
    }
    if (d->pipe[0].shader.tex && (c->tslot != r->tslot || c->pslot != r->pslot)) {
        kh1_cmd_nat_nojoin[2]++;
        return 0;
    }
    vend = c->v0 * (u32)sizeof(KH1GpuVert) + c->nv * stride;
    mend = c->moff + c->nmat * 64u;
    if (r->vring.head != vend || r->uring.head != mend || n * stride > r->vring.slot - vend ||
        nmat * 64u > r->uring.slot - mend) {
        kh1_cmd_nat_nojoin[3]++;
        return 0;
    }
    kh1_batch_key(d, p, &k);
    if (memcmp(&k, &c->k, sizeof k)) {
        kh1_cmd_nat_nojoin[2]++;
        return 0;
    }
    at = (u8 *)kh1_ring_alloc(&r->vring, n * stride, 1);
    u = (u8 *)kh1_ring_alloc(&r->uring, nmat * 64u, 1);
    memcpy(at, v, n * stride);
    memcpy(u, mats, nmat * 64u);
    off = c->nmat;
    if (skin) {
        KH1GpuVertSk *o = (KH1GpuVertSk *)(void *)at;
        for (i = 0; i < n; i++) {
            o[i].mi = (u8)(o[i].mi + off);
            o[i].mi2 = (u8)(o[i].mi2 + off);
        }
    } else {
        KH1GpuVert *o = (KH1GpuVert *)(void *)at;
        for (i = 0; i < n; i++) o[i].pad[0] = (u8)(o[i].pad[0] + off);
        if (c->wtex) { /* prim()'s wide-screen s, as the command's first run had it */
            u32 lw = d->tex0_lo >> 26 & 15;
            f32 kk = (f32)(1u << (lw > 10 ? 10 : lw)) / r->tsw[c->samples - 1];
            for (i = 0; i < n; i++) o[i].s *= kk;
        }
    }
    c->nv += n;
    c->prims++;
    c->nmat = (u8)(c->nmat + nmat);
    kh1_cmd_nat_joins++;
    return 1;
}
void kh1_cmd_native(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVert *v, u32 n, const f32 *mats,
                    u32 nmat, u32 cull) {
    native(r, d, p, v, n, mats, nmat, cull, 0);
}
void kh1_cmd_native_skin(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVertSk *v, u32 n,
                         const f32 *mats, u32 nmat, u32 cull) {
    native(r, d, p, (const KH1GpuVert *)(const void *)v, n, mats, nmat, cull, 1);
}
static void native(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVert *v, u32 n, const f32 *mats,
                   u32 nmat, u32 cull, u32 skin) {
    KH1Cmd *c;
    u8 *u;
    u32 bytes = nmat * 64;
    static KH1DrawState nd; /* 2026-10-31: a texture, the shader's lin (drawstate.h): r->in_d here */
    u32 i;
    if (!n || !nmat || nmat > 255) return;
    /* 2026-10-31: every native textured draw is lin, not only KH1_NAT_LIN's: the native textured vertex shader hands
     * its colour over in a TEXCOORD (shadergen.c; a COLOR varying is clamped on the Vita), which only the lin
     * fragment shader reads.  Without mi's bit 7 its w is 1, so the divide changes nothing */
    if (d->pipe[0].shader.tex) {
        nd = *d;
        for (i = 0; i < 2; i++) nd.pipe[i].shader.lin = 1;
        d = &nd;
    }
    if (kh1_cmd_natjoin && nat_join(r, d, p, v, n, mats, nmat, cull, skin)) return;
    kh1_batch_break(&r->b); /* nothing before joins it */
    r->in_d = d;
    r->in_p = p;
    r->in_v = v;
    r->in_n = n;
    r->in_skin = skin;
    if (!kh1_batch_prim_sig(&r->b, d, p, n, 0) || r->cur < 0 || r->dropped) { /* a state that draws nothing, or no room */
        r->in_skin = 0;
        kh1_batch_break(&r->b);
        return;
    }
    r->in_skin = 0;
    c = &r->cmd[r->cur];
    c->nmat = (u8)nmat;
    c->skin = (u8)skin;
    c->cull = (u8)(cull & ~KH1_NAT_LIN);
    u = (u8 *)kh1_ring_alloc(&r->uring, bytes, KH1_RING_UNIFORM_SLOT);
    if (u) {
        memcpy(u, mats, bytes);
        c->moff = (u32)(u - (r->uring.base + r->uring.cur * r->uring.slot));
    } else {
        c->lost = 1;
    }
    kh1_batch_break(&r->b); /* nor anything after */
}

void kh1_cmd_break(KH1CmdRec *r) { kh1_batch_break(&r->b); }

/* session 127: a transfer command at the end of the list (0 when the table is full) */
static KH1Cmd *xfer_cmd(KH1CmdRec *r, u32 kind) {
    KH1Cmd *c;
    if (r->ncmd == KH1_CMD_MAX) { r->dropped++; return 0; }
    c = &r->cmd[r->ncmd++];
    memset(c, 0, sizeof *c);
    c->kind = (u8)kind;
    c->pass = r->npass ? r->npass - 1 : ~0u;
    c->tslot = c->pslot = -1;
    c->x.slot = -1;
    return c;
}

void kh1_cmd_upload(KH1CmdRec *r, u32 dir, u32 bb_lo, u32 bb_hi, u32 pos_lo, u32 pos_hi, u32 reg_lo, u32 reg_hi) {
    KH1Cmd *c;
    kh1_batch_break(&r->b);
    c = xfer_cmd(r, dir == 2 ? KH1_CMD_COPY : KH1_CMD_UPLOAD);
    if (!c) return;
    c->x.bb_lo = bb_lo;
    c->x.bb_hi = bb_hi;
    c->x.sx = (u16)(pos_lo & 2047);
    c->x.sy = (u16)(pos_lo >> 16 & 2047);
    c->x.dx = (u16)(pos_hi & 2047);
    c->x.dy = (u16)(pos_hi >> 16 & 2047);
    c->x.w = (u16)(reg_lo & 0xFFF);
    c->x.h = (u16)(reg_hi & 0xFFF);
    c->x.dst = tgt_at(r, bb_hi & 0x3FFF, bb_hi >> 16 & 63, c->x.dx, c->x.dy, c->x.w, c->x.h);
    if (dir == 2) c->x.src = tgt_at(r, bb_lo & 0x3FFF, bb_lo >> 16 & 63, c->x.sx, c->x.sy, c->x.w, c->x.h);
    if (c->x.src || dir == 2) {
        if (c->x.src || c->x.dst) r->split = 1;
    } else if (c->x.dst) { /* an upload: only into the open pass's own target (cmdbuf.h, 2026-10-31) */
        u32 t = c->x.dst - 1u;
        if (!r->npass || r->pass[r->npass - 1].tgt == t) {
            r->split = 1;
        } else {
            r->pwrote |= 1u << t;
            r->frame.xfer_joins++;
        }
    }
    if (dir == 0 || dir == 2) cpu_pages(r, bb_hi & 0x3FFF, bb_hi >> 16 & 63, bb_hi >> 24 & 63, c->x.dx, c->x.dy, c->x.w, c->x.h, !c->x.src);
}

static void clut_cmd(KH1CmdRec *r, u32 tex0_lo, u32 tex0_hi, s32 slot, int fill, int load) {
    KH1Cmd *c;
    u32 psm = tex0_lo >> 20 & 63, bits8 = psm == 0x13 || psm == 0x1B;
    kh1_batch_break(&r->b);
    r->pslot = (s16)slot;
    c = xfer_cmd(r, KH1_CMD_CLUT);
    if (!c) return;
    c->x.tex0_lo = tex0_lo;
    c->x.tex0_hi = tex0_hi;
    c->x.slot = (s16)slot;
    c->x.fill = fill != 0;
    /* the entries' rectangle at CBP: 16 x 16 for an 8-bit PSM, 8 x 2 for a 4-bit one (CSM 1) */
    if (!load) return;
    if (cpu_pages(r, tex0_hi >> 5 & 0x3FFF, 1, 0, 0, 0, bits8 ? 16 : 8, bits8 ? 16 : 2, 2)) return; /* session 137v: GS memory's */
    c->x.src = tgt_at(r, tex0_hi >> 5 & 0x3FFF, 1, 0, 0, bits8 ? 16 : 8, bits8 ? 16 : 2);
    if (c->x.src) r->split = 1;
}

void kh1_cmd_clut(KH1CmdRec *r, u32 tex0_lo, u32 tex0_hi, s32 slot, int fill) {
    clut_cmd(r, tex0_lo, tex0_hi, slot, fill, 1);
}

void kh1_cmd_palette(KH1CmdRec *r, u32 tex0_lo, u32 tex0_hi, s32 slot, int fill) {
    clut_cmd(r, tex0_lo, tex0_hi, slot, fill, 0);
}

void kh1_cmd_texture(KH1CmdRec *r, u32 tex0_lo, u32 tex0_hi, s32 slot, int decoded, u32 texels) {
    KH1Cmd *c;
    /* the open draw binds the same TEX0 to another entry: the next primitive must open a new command */
    if (r->cur >= 0) {
        const KH1Cmd *o = &r->cmd[r->cur];
        if (o->d.pipe[0].shader.tex && o->tslot != slot && o->d.tex0_lo == tex0_lo && !((o->d.tex0_hi ^ tex0_hi) & 3))
            kh1_batch_break(&r->b);
    }
    r->tslot = (s16)slot;
    if (!decoded) return;
    c = xfer_cmd(r, KH1_CMD_TEXTURE);
    if (!c) return;
    c->x.tex0_lo = tex0_lo;
    c->x.tex0_hi = tex0_hi;
    c->x.slot = (s16)slot;
    c->x.fill = 1;
    c->x.texels = texels;
}

u32 kh1_cmd_ready(const KH1CmdRec *r) {
    if (r->held >= 0) return (u32)r->held;
    return r->cur >= 0 ? (u32)r->cur : r->ncmd;
}

const KH1GpuVert *kh1_cmd_verts(const KH1CmdRec *r, const KH1Cmd *c) {
    return (const KH1GpuVert *)(r->vring.base + r->vring.cur * r->vring.slot) + c->v0;
}

/* the pass that last drew (colour) / wrote (depth) what pass `at` needs: this frame's (index in w), or the
 * previous frame's open one, gets the reason */
static void need(KH1CmdRec *r, const s32 *w, u32 t, u8 why) {
    u32 j;
    if (t >= KH1_CMD_TARGETS) return;
    if (w[t] >= 0) {
        r->pass[w[t]].why |= why;
        return;
    }
    for (j = 0; j < r->nprev; j++)
        if (r->prev[j].tgt == t && r->prev[j].store == KH1_STORE_OPEN) r->prev[j].why |= KH1_WHY_NEXT;
}

static void dneed(KH1CmdRec *r, const s32 *dw, u32 ds) {
    u32 j;
    if (dw[ds] >= 0) {
        r->pass[dw[ds]].dwhy = 1;
        return;
    }
    for (j = 0; j < r->nprev; j++)
        if (r->prev[j].depth == ds && r->prev[j].dstore == KH1_STORE_OPEN) r->prev[j].dwhy = 1;
}

static void count_store(KH1CmdCount *f, const KH1CmdPass *p) {
    u32 b;
    if (p->store == KH1_STORE_OPEN) { f->open++; return; }
    if (p->store == KH1_STORE_STORE) {
        f->stores++;
        for (b = 0; b < 4; b++)
            if (p->why >> b & 1) f->why[b]++;
    } else {
        f->discards++;
    }
}

static void count_dstore(KH1CmdCount *f, const KH1CmdPass *p) {
    if (p->depth == KH1_DS_NONE || !p->zwrite) return;
    if (p->dstore == KH1_STORE_OPEN) f->dopen++;
    else if (p->dstore == KH1_STORE_STORE) f->dstores++;
    else f->ddiscards++;
}

/* the previous frame's open stores, now that this frame has said what it needs */
static void settle_prev(KH1CmdRec *r) {
    u32 j;
    for (j = 0; j < r->nprev; j++) {
        KH1CmdPass *p = &r->prev[j];
        if (p->store == KH1_STORE_OPEN) {
            p->store = p->why ? KH1_STORE_STORE : KH1_STORE_DISCARD;
            count_store(&r->total, p);
        }
        if (p->dstore == KH1_STORE_OPEN && p->zwrite) {
            p->dstore = p->dwhy ? KH1_STORE_STORE : KH1_STORE_DISCARD;
            count_dstore(&r->total, p);
        }
    }
    r->nprev = 0;
}

/* session 127: a transfer command at its place in the frame: a target it reads is stored for it (sampled), one it
 * writes is stored first (redrawn) and counts as drawn for the next pass's load (xw) */
static void xfer_walk(KH1CmdRec *r, const KH1Cmd *c, const s32 *w, u8 *xw) {
    KH1CmdCount *fc = &r->frame;
    switch (c->kind) {
    case KH1_CMD_UPLOAD: fc->uploads++; break;
    case KH1_CMD_COPY: fc->copies++; break;
    case KH1_CMD_CLUT: fc->cluts++; fc->pal_fills += c->x.fill; break;
    case KH1_CMD_TEXTURE: fc->textures++; fc->texels += c->x.texels; break;
    default: return;
    }
    if (c->x.src) {
        need(r, w, c->x.src - 1u, KH1_WHY_SAMPLED);
        fc->tgt_reads++;
    }
    if (c->x.dst) {
        need(r, w, c->x.dst - 1u, KH1_WHY_REDRAWN);
        xw[c->x.dst - 1] = 1;
        fc->tgt_writes++;
    }
}

int kh1_cmd_hoist = 1;

/* 2026-10-31: kh1_cmd_hoist.  A pass on target T, then passes on other targets (the group G), then T again with the
 * same depth buffer: the GPU ends T's scene for G and loads T's colour and depth again after it (the Dive: the
 * shadow's two small passes between the 3D scene and its tail, ~2 MiB of tile loads and stores a picture).  When G
 * and T's first pass do not touch each other's work, G's commands (with the transfers just before them) go ahead of
 * T's first pass and the two T passes become one.  Not touching: G samples, reads or writes neither T nor T's depth
 * buffer; T's first pass samples no target G draws or samples and copies from none; neither side's texture or
 * palette uploads land in a slot the other side's draws use or uploads into (their order would change what a draw
 * sees).  An upload T's first pass made into a target G draws or samples (the Dive: the shadow buffer's base image,
 * sent during the 3D scene since it no longer ends it) is G's: it goes ahead with G, in its order */
static int g_upload(const KH1Cmd *c, u32 g, u8 T) {
    return (c->kind == KH1_CMD_UPLOAD || c->kind == KH1_CMD_COPY) && c->x.dst && c->x.dst - 1u != T &&
           (g >> (c->x.dst - 1u) & 1) && (!c->x.src || c->x.src - 1u != T);
}
static void cmd_swap(KH1Cmd *a, KH1Cmd *b) {
    KH1Cmd t = *a;
    *a = *b;
    *b = t;
}
static void cmd_rev(KH1CmdRec *r, u32 a, u32 b) { /* [a, b) reversed */
    while (a + 1 < b) cmd_swap(&r->cmd[a++], &r->cmd[--b]);
}
/* 2026-11-01 (native-plan.md stage 1: on the Vita the frame op's passes took ~0.55 s of the GPU thread's 2.8 s, and on
 * the host 75 % of their instructions were cmd_swap, hoist's three reversals of whole KH1Cmds): [s, mid) [mid, e) ->
 * [mid, e) [s, mid) through a scratch copy, each command moved once or twice where the reversals swapped it twice
 * (three copies a swap).  The same order of commands.  kh1_cmd_fastrot 0 (config.txt recfast=0) keeps the swaps */
int kh1_cmd_fastrot = 1;
static KH1Cmd rot_tmp[KH1_CMD_MAX];
static void cmd_rot(KH1CmdRec *r, u32 s, u32 mid, u32 e) {
    u32 a = mid - s, b = e - mid;
    if (!a || !b) return;
    if (a <= b) {
        memcpy(rot_tmp, &r->cmd[s], a * sizeof *rot_tmp);
        memmove(&r->cmd[s], &r->cmd[mid], b * sizeof *rot_tmp);
        memcpy(&r->cmd[s + b], rot_tmp, a * sizeof *rot_tmp);
    } else {
        memcpy(rot_tmp, &r->cmd[mid], b * sizeof *rot_tmp);
        memmove(&r->cmd[s + b], &r->cmd[s], a * sizeof *rot_tmp);
        memcpy(&r->cmd[s], rot_tmp, b * sizeof *rot_tmp);
    }
}
static int slot_clash(const KH1Cmd *x, const KH1Cmd *y) { /* x's upload against y's draw or upload */
    if (x->kind == KH1_CMD_TEXTURE && x->x.slot >= 0)
        return (y->kind == KH1_CMD_DRAW && y->tslot == x->x.slot) || (y->kind == KH1_CMD_TEXTURE && y->x.slot == x->x.slot);
    if (x->kind == KH1_CMD_CLUT && x->x.slot >= 0 && x->x.fill)
        return (y->kind == KH1_CMD_DRAW && y->pslot == x->x.slot) ||
               (y->kind == KH1_CMD_CLUT && y->x.fill && y->x.slot == x->x.slot);
    return 0;
}
static u32 hoist_g; /* hoist_ok's G targets (drawn, written or sampled) */
static int hoist_ok(const KH1CmdRec *r, u32 a, u32 b) {
    const KH1CmdPass *m = &r->pass[a], *t = &r->pass[b];
    u32 s = m->cmd0, mid = m->cmd0 + m->ncmd, e = r->pass[b - 1].cmd0 + r->pass[b - 1].ncmd, i, j, gt = 0, gs = 0;
    u8 T = m->tgt;
    if (T >= KH1_CMD_TARGETS || t->w != m->w || t->h != m->h) return 0;
    for (i = a + 1; i < b; i++) {
        const KH1CmdPass *g = &r->pass[i];
        if (g->tgt >= KH1_CMD_TARGETS || g->tgt == T) return 0;
        if (g->depth != KH1_DS_NONE && (g->depth == m->depth || g->depth == t->depth)) return 0;
        gt |= 1u << g->tgt;
    }
    for (i = mid; i < e; i++) { /* G (and the transfers before it) */
        const KH1Cmd *c = &r->cmd[i];
        if (c->kind == KH1_CMD_DRAW && c->samples) {
            if (c->samples - 1u == T) return 0;
            gs |= 1u << (c->samples - 1u);
        }
        if (c->kind != KH1_CMD_DRAW && ((c->x.src && c->x.src - 1u == T) || (c->x.dst && c->x.dst - 1u == T))) return 0;
        if (c->kind != KH1_CMD_DRAW && c->x.dst) gt |= 1u << (c->x.dst - 1u);
    }
    for (i = s; i < mid; i++) { /* T's first pass */
        const KH1Cmd *c = &r->cmd[i];
        if (c->kind == KH1_CMD_DRAW && c->samples && ((gt | gs) >> (c->samples - 1u) & 1)) return 0;
        if (c->kind != KH1_CMD_DRAW && c->x.src && ((gt | gs) >> (c->x.src - 1u) & 1)) return 0;
        if (c->kind != KH1_CMD_DRAW && c->x.dst && ((gt | gs) >> (c->x.dst - 1u) & 1) && !g_upload(c, gt | gs, T)) return 0;
        for (j = mid; j < e; j++)
            if (slot_clash(c, &r->cmd[j]) || slot_clash(&r->cmd[j], c)) return 0;
    }
    /* the T passes' join: the transfers between them leave T alone */
    for (i = e; i < t->cmd0; i++) {
        const KH1Cmd *c = &r->cmd[i];
        if (c->kind != KH1_CMD_DRAW && ((c->x.src && c->x.src - 1u == T) || (c->x.dst && c->x.dst - 1u == T))) return 0;
    }
    hoist_g = gt | gs;
    return 1;
}
static void hoist(KH1CmdRec *r) {
    u32 a, b, i, j, k;
    if (r->dropped) return;
    for (a = 0; a + 2 < r->npass; a++) {
        KH1CmdPass *m = &r->pass[a], keep;
        u32 s, mid, e, n;
        for (b = a + 1; b < r->npass && r->pass[b].tgt != m->tgt; b++) ;
        if (b == r->npass || b == a + 1) continue;
        if (r->pass[b].rt != m->rt || r->pass[b].psm != m->psm || r->pass[b].fbp != m->fbp || r->pass[b].fbw != m->fbw)
            continue;
        if (m->depth != KH1_DS_NONE && r->pass[b].depth != KH1_DS_NONE && m->depth != r->pass[b].depth) continue;
        if (m->cmd0 + m->ncmd > r->pass[a + 1].cmd0 || !hoist_ok(r, a, b)) continue;
        s = m->cmd0;
        mid = m->cmd0 + m->ncmd;
        e = r->pass[b - 1].cmd0 + r->pass[b - 1].ncmd;
        /* the commands: [s, mid) [mid, e) -> [mid, e) [s, mid) */
        n = e - mid;
        if (kh1_cmd_fastrot) {
            cmd_rot(r, s, mid, e);
            /* G's uploads from T's first pass ahead of G, in their order: [s, s + k), the others after them in
             * theirs (what the swaps below do), each command moved once */
            for (i = s + n, k = 0; i < e; i++)
                if (g_upload(&r->cmd[i], hoist_g, m->tgt)) k++;
            if (k) {
                u32 up = 0, rest = 0;
                for (i = s; i < e; i++) {
                    int g = i >= s + n && g_upload(&r->cmd[i], hoist_g, m->tgt);
                    if (g) rot_tmp[up++] = r->cmd[i];
                    else rot_tmp[k + rest++] = r->cmd[i];
                }
                memcpy(&r->cmd[s], rot_tmp, (e - s) * sizeof *rot_tmp);
            }
        } else {
            cmd_rev(r, s, mid);
            cmd_rev(r, mid, e);
            cmd_rev(r, s, e);
            /* G's uploads from T's first pass ahead of G, in their order: [s, s + k) */
            for (i = s + n, k = 0; i < e; i++)
                if (g_upload(&r->cmd[i], hoist_g, m->tgt)) {
                    for (j = i; j > s + k; j--) cmd_swap(&r->cmd[j], &r->cmd[j - 1]);
                    k++;
                }
        }
        keep = *m;
        for (i = a; i + 1 < b; i++) {
            r->pass[i] = r->pass[i + 1];
            r->pass[i].cmd0 -= mid - s;
            r->pass[i].cmd0 += k;
        }
        /* T's first pass now runs to its tail's end, the tail's draws and the transfers before it included */
        keep.cmd0 += n + k;
        keep.ncmd = r->pass[b].cmd0 + r->pass[b].ncmd - keep.cmd0;
        keep.ndraw += r->pass[b].ndraw;
        if (keep.depth == KH1_DS_NONE) keep.depth = r->pass[b].depth;
        keep.ztest |= r->pass[b].ztest;
        keep.zwrite |= r->pass[b].zwrite;
        keep.zseen |= r->pass[b].zseen;
        keep.feedback |= r->pass[b].feedback;
        r->pass[b - 1] = keep;
        for (i = b; i + 1 < r->npass; i++) r->pass[i] = r->pass[i + 1];
        r->npass--;
        for (i = 0; i < r->npass; i++)
            for (j = r->pass[i].cmd0; j < r->pass[i].cmd0 + r->pass[i].ncmd && j < r->ncmd; j++)
                if (r->cmd[j].kind == KH1_CMD_DRAW) r->cmd[j].pass = i;
        r->frame.hoists++;
        a = b - 2; /* the joined pass again (a++ next): its new tail may follow */
    }
}

void kh1_cmd_frame(KH1CmdRec *r) {
    s32 w[KH1_CMD_TARGETS], dw[3];
    u32 i, j, *f, *t, next = 0;
    u8 xw[KH1_CMD_TARGETS];
    KH1CmdCount *fc = &r->frame;
    kh1_batch_frame(&r->b); /* a repeat cut short is replayed first */
    r->held = -1;
    if (kh1_cmd_hoist) hoist(r);
    for (i = 0; i < KH1_CMD_TARGETS; i++) w[i] = -1;
    dw[0] = dw[1] = dw[2] = -1;
    memset(xw, 0, sizeof xw);
    for (i = 0; i < r->npass; i++) {
        KH1CmdPass *p = &r->pass[i];
        u32 tg = p->tgt;
        int earlier;
        /* the transfers before the pass, then those between its draws (none touches its target: that splits) */
        for (; next < p->cmd0 + p->ncmd && next < r->ncmd; next++) xfer_walk(r, &r->cmd[next], w, xw);
        clears(r, p);
        earlier = r->assume_drawn || (tg < KH1_CMD_TARGETS && (w[tg] >= 0 || r->tdrawn[tg] || xw[tg]));
        p->load = earlier && !p->cleared ? KH1_LOAD_LOAD : KH1_LOAD_DONT_CARE;
        if (p->load == KH1_LOAD_LOAD) need(r, w, tg, KH1_WHY_REDRAWN);
        for (j = p->cmd0; j < p->cmd0 + p->ncmd && j < r->ncmd; j++) {
            u32 s = r->cmd[j].samples;
            if (!s) continue;
            if (r->cmd[j].kind != KH1_CMD_DRAW) continue;
            if (s - 1 == tg) fc->feedback++;
            else need(r, w, s - 1, KH1_WHY_SAMPLED);
        }
        if (p->depth != KH1_DS_NONE && p->depth < 3) {
            int dearlier = r->assume_drawn || dw[p->depth] >= 0 || r->ddrawn[p->depth];
            p->dload = p->ztest && dearlier && !p->zcleared ? KH1_LOAD_LOAD : KH1_LOAD_DONT_CARE;
            if (p->dload == KH1_LOAD_LOAD) dneed(r, dw, p->depth);
            if (p->zwrite) dw[p->depth] = (s32)i;
            fc->dpasses++;
            if (p->dload == KH1_LOAD_LOAD) fc->dloads++;
        }
        if (tg < KH1_CMD_TARGETS) {
            w[tg] = (s32)i;
            xw[tg] = 0;
        }
        if (p->load == KH1_LOAD_LOAD) fc->loads++;
        else fc->dont_care++;
        if (p->cleared) fc->cleared++;
    }
    for (; next < r->ncmd; next++) xfer_walk(r, &r->cmd[next], w, xw); /* the frame's last transfers */
    settle_prev(r);
    for (i = 0; i < r->npass; i++) {
        KH1CmdPass *p = &r->pass[i];
        int last = p->tgt < KH1_CMD_TARGETS && w[p->tgt] == (s32)i;
        if (last && p->rt == KH1_RT_DISPLAY) p->why |= KH1_WHY_DISPLAY;
        p->store = p->why ? KH1_STORE_STORE : last ? KH1_STORE_OPEN : KH1_STORE_DISCARD;
        p->dstore = p->dwhy ? KH1_STORE_STORE : p->depth < 3 && p->zwrite && dw[p->depth] == (s32)i ? KH1_STORE_OPEN
                    : KH1_STORE_DISCARD;
        count_store(fc, p);
        count_dstore(fc, p);
        if ((p->store == KH1_STORE_OPEN || p->dstore == KH1_STORE_OPEN) && r->nprev < KH1_CMD_PASSES)
            r->prev[r->nprev++] = *p;
        if (p->tgt < KH1_CMD_TARGETS) r->tdrawn[p->tgt] = 1;
    }
    for (i = 0; i < 3; i++)
        if (dw[i] >= 0) r->ddrawn[i] = 1;
    fc->frames = 1;
    fc->passes = r->npass;
    fc->cmds = r->ncmd;
    fc->lost += r->dropped;
    for (i = 0; i < r->ncmd; i++) {
        fc->prims += r->cmd[i].prims;
        fc->verts += r->cmd[i].nv;
        if (r->cmd[i].lost) fc->lost++;
    }
    fc->max_passes = r->npass;
    fc->max_cmds = r->ncmd;
    f = (u32 *)fc;
    t = (u32 *)&r->total;
    for (i = 0; i < sizeof *fc / sizeof(u32); i++) {
        if (&f[i] == &fc->max_passes || &f[i] == &fc->max_cmds || &f[i] == &fc->held_max) {
            if (f[i] > t[i]) t[i] = f[i];
        } else {
            t[i] += f[i];
        }
    }
    /* open passes were counted as open this frame; the total counts them once settled */
    r->total.open -= fc->open;
    r->total.dopen -= fc->dopen;
}

void kh1_cmd_reset_frame(KH1CmdRec *r) {
    r->ncmd = 0;
    r->npass = 0;
    r->dropped = 0;
    r->held = -1;
    r->cur = -1;
    r->split = 0;
    r->pwrote = 0;
    r->open_pending = 0;
    memset(&r->frame, 0, sizeof r->frame);
    kh1_ring_frame(&r->vring);
    kh1_ring_frame(&r->uring);
}

void kh1_cmd_finish(KH1CmdRec *r) {
    u32 j;
    for (j = 0; j < r->nprev; j++) {
        if (r->prev[j].store == KH1_STORE_OPEN) r->total.open++;
        if (r->prev[j].dstore == KH1_STORE_OPEN && r->prev[j].zwrite) r->total.dopen++;
    }
    r->nprev = 0;
}

const char *kh1_cmd_str(const KH1CmdRec *r, const KH1Cmd *c) {
    static char buf[160];
    char tg[2][48];
    u32 i;
    for (i = 0; i < 2; i++) {
        u32 t = i ? c->x.dst : c->x.src;
        tg[i][0] = 0;
        if (t && t - 1 < r->ntgt) sprintf(tg[i], " (%s target %04x)", i ? "into" : "from", (r->tgt[t - 1] >> 8 & 0xFFF) * 32);
    }
    switch (c->kind) {
    case KH1_CMD_UPLOAD:
        sprintf(buf, "upload %04x bw %u psm %02x %u x %u at (%u, %u)%s", c->x.bb_hi & 0x3FFF, c->x.bb_hi >> 16 & 63,
                c->x.bb_hi >> 24 & 63, c->x.w, c->x.h, c->x.dx, c->x.dy, tg[1]);
        break;
    case KH1_CMD_COPY:
        sprintf(buf, "copy %04x (%u, %u) -> %04x (%u, %u) %u x %u%s%s", c->x.bb_lo & 0x3FFF, c->x.sx, c->x.sy,
                c->x.bb_hi & 0x3FFF, c->x.dx, c->x.dy, c->x.w, c->x.h, tg[0], tg[1]);
        break;
    case KH1_CMD_CLUT:
        sprintf(buf, "clut %04x csa %u slot %d%s%s", c->x.tex0_hi >> 5 & 0x3FFF, c->x.tex0_hi >> 24 & 31, c->x.slot,
                c->x.fill ? " fill" : "", tg[0]);
        break;
    case KH1_CMD_TEXTURE:
        sprintf(buf, "texture %04x psm %02x %u x %u into entry %d (%u texels)", c->x.tex0_lo & 0x3FFF,
                c->x.tex0_lo >> 20 & 63, 1u << (c->x.tex0_lo >> 26 & 15), 1u << ((c->x.tex0_lo >> 30 | c->x.tex0_hi << 2) & 15),
                c->x.slot, c->x.texels);
        break;
    default:
        sprintf(buf, "draw pass %u: %u prims, %u vertices, texture entry %d palette %d%s", c->pass + 1, c->prims, c->nv,
                c->tslot, c->pslot, c->samples ? " (samples a target)" : "");
        break;
    }
    return buf;
}

const char *kh1_cmd_pass_str(const KH1CmdPass *p) {
    static const char *rt[] = { "display", "Z area as colour", "movie frame", "3D target", "slot capture",
                                "off-screen buffer", "CLUT pass", "other" };
    static const char *ds[] = { "", " depth main", " depth shadow" };
    static const char *st[] = { "DISCARD", "STORE", "OPEN" };
    static char buf[200];
    char why[64];
    static const char *wn[] = { "sampled", "redrawn", "next frame", "display" };
    u32 b, n = 0;
    why[0] = 0;
    for (b = 0; b < 4; b++)
        if (p->why >> b & 1) n += sprintf(why + n, "%s%s", n ? ", " : " (", wn[b]);
    if (n) sprintf(why + n, ")");
    sprintf(buf, "%s (%04x)%s: %u cmds, load %s%s store %s%s", p->rt < KH1_RT_COUNT ? rt[p->rt] : "?",
            (u32)p->fbp * 32, p->depth < 3 ? ds[p->depth] : " depth ?", p->ndraw,
            p->load ? "LOAD" : "DONT_CARE", p->cleared ? " (cleared)" : "", st[p->store], why);
    if (p->depth != KH1_DS_NONE && p->depth < 3)
        sprintf(buf + strlen(buf), ", depth load %s store %s%s", p->dload ? "LOAD" : "DONT_CARE",
                p->zwrite ? st[p->dstore] : "none", p->zcleared ? " (cleared)" : "");
    if (p->feedback) sprintf(buf + strlen(buf), ", samples itself");
    return buf;
}
