/* The draw list as GPU commands (include/platform/cmdbuf.h, docs/renderer-spec.md 4.13 "Session 126"):
 * batch.h's batches recorded with their vertices and uniforms in ring.h's rings, column groups held
 * until they end, and each pass's load / store needs decided at the frame end.  Checked by
 * tests/host/cmdbuf_test.c and run over a host run (host/null/pipes.c, KH1_HOST_TRACE=5) and the ELF's
 * static packets (tools/host/drawpipes.py --passes).  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/cmdbuf.h"

void *memset(void *, int, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);
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
    return r->ntgt++;
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

static void new_cmd(KH1CmdRec *r, const KH1BatchKey *k, const KH1DrawState *d, const KH1RenderPass *rp) {
    KH1Cmd *c;
    u8 *u;
    if (!r->npass || !same_pass(&r->pass[r->npass - 1], k)) new_pass(r, k, rp);
    else if (r->pass[r->npass - 1].depth != k->depth && k->depth != KH1_DS_NONE) {
        r->pass[r->npass - 1].depth = k->depth; /* the scene binds the depth buffer from its start */
        r->frame.depth_joins++;
    } else if (r->pass[r->npass - 1].depth != k->depth) {
        r->frame.depth_joins++;
    }
    if (r->ncmd == KH1_CMD_MAX) { r->dropped++; return; }
    c = &r->cmd[r->ncmd++];
    memset(c, 0, sizeof *c);
    c->k = *k;
    c->d = *d;
    c->pass = r->npass - 1;
    r->pass[c->pass].ncmd++;
    u = (u8 *)kh1_ring_alloc(&r->uring, KH1_RING_UNIFORM_SLOT, KH1_RING_UNIFORM_SLOT);
    if (u) {
        memset(u, 0, KH1_RING_UNIFORM_SLOT);
        memcpy(u, &d->u, sizeof d->u);
        c->uoff = (u32)(u - (r->uring.base + r->uring.cur * r->uring.slot));
    } else {
        c->lost = 1;
    }
    if (d->pipe[0].shader.tex) {
        u32 tbp = d->tex0_lo & 0x3FFF, tbw = d->tex0_lo >> 14 & 63, psm = d->tex0_lo >> 20 & 63, t;
        if (!(tbp & 31)) {
            t = tgt_find(r, tgt_key(kh1_target_id(tbp / 32, tbw, psm), tbp / 32, tbw), 0);
            if (t != ~0u) c->samples = (u8)(t + 1);
        }
    }
}

/* Clears (the GS has none): the pass's leading draws that write every channel without reading the target
 * (no blend, no partial mask, no frame fetch, no DATE), as axis-aligned rectangles (sprites) clipped to their
 * command's final scissor (a column group's union), covering the target: the game clears in 32-pixel strips.
 * Coverage is kept on an 8 x 8 cell grid (a cell counts when every pixel of it inside the target is covered),
 * so a pass of strips counts as cleared.  For depth the same with the draws that write Z under ALWAYS,
 * before the first draw that tests Z. */
#define CELL 8
#define CELLS_W 128 /* targets up to 1024 x 1024 at the cell size */
static u8 cell[CELLS_W][CELLS_W];

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
        s32 px0, px1, py0, py1, cx, cy;
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
        for (cy = 0; cy * CELL < (s32)p->h && cy < CELLS_W; cy++)
            for (cx = 0; cx * CELL < (s32)p->w && cx < CELLS_W; cx++) {
                s32 ex = cx * CELL + CELL < (s32)p->w ? cx * CELL + CELL : (s32)p->w;
                s32 ey = cy * CELL + CELL < (s32)p->h ? cy * CELL + CELL : (s32)p->h;
                if (px0 <= cx * CELL && px1 >= ex && py0 <= cy * CELL && py1 >= ey) cell[cy][cx] = 1;
            }
    }
    return 1;
}

static int all_cells(const KH1CmdPass *p) {
    s32 cx, cy;
    if (!p->w || !p->h || p->w > CELL * CELLS_W || p->h > CELL * CELLS_W) return 0;
    for (cy = 0; cy * CELL < (s32)p->h; cy++)
        for (cx = 0; cx * CELL < (s32)p->w; cx++)
            if (!cell[cy][cx]) return 0;
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
        if (reads_dst(&c->d, p->psm) || (c->samples && c->samples - 1 == p->tgt)) break;
        if (c->d.n == 1 && !k->shader.discard && k->ztest == KH1_ZTST_ALWAYS && cover_cmd(r, p, c)) p->cleared = all_cells(p);
    }
    if (p->depth == KH1_DS_NONE) return;
    memset(cell, 0, sizeof cell);
    for (j = p->cmd0; j < end && !p->zcleared; j++) {
        const KH1Cmd *c = &r->cmd[j];
        const KH1PipeKey *k = &c->d.pipe[0];
        if (k->ztest != KH1_ZTST_ALWAYS) break;
        if (k->zwrite && c->d.n == 1 && !k->shader.discard && !c->d.setup && cover_cmd(r, p, c)) p->zcleared = all_cells(p);
    }
}

static void prim(KH1CmdRec *r, const KH1BatchKey *k, u32 src) {
    const KH1DrawState *d = r->in_d;
    const KH1RenderPass *rp = r->in_p;
    const KH1GpuVert *v = r->in_v;
    u32 n = r->in_n;
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
    if (!r->ncmd || r->dropped) return;
    c = &r->cmd[r->ncmd - 1];
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
    at = (u8 *)kh1_ring_alloc(&r->vring, n * (u32)sizeof(KH1GpuVert), (u32)sizeof(KH1GpuVert));
    if (!at) {
        c->lost = 1;
    } else {
        if (v) memcpy(at, v, n * sizeof *v);
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
        r->held = arg && r->ncmd ? (s32)r->ncmd - 1 : -1;
        break;
    case KH1_BEV_WIDEN:
        if (r->held >= 0)
            for (i = r->held; i < (s32)r->ncmd; i++) r->cmd[i].k.sx1 = (s32)arg;
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
}

void kh1_cmd_prim(KH1CmdRec *r, const KH1DrawState *d, const KH1RenderPass *p, const KH1GpuVert *v, u32 n, u32 sig) {
    r->in_d = d;
    r->in_p = p;
    r->in_v = v;
    r->in_n = n;
    kh1_batch_prim_sig(&r->b, d, p, n, sig);
}

void kh1_cmd_break(KH1CmdRec *r) { kh1_batch_break(&r->b); }

u32 kh1_cmd_ready(const KH1CmdRec *r) {
    if (r->held >= 0) return (u32)r->held;
    return r->ncmd ? r->ncmd - 1 : 0;
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

void kh1_cmd_frame(KH1CmdRec *r) {
    s32 w[KH1_CMD_TARGETS], dw[3];
    u32 i, j, *f, *t;
    KH1CmdCount *fc = &r->frame;
    kh1_batch_frame(&r->b); /* a repeat cut short is replayed first */
    r->held = -1;
    for (i = 0; i < KH1_CMD_TARGETS; i++) w[i] = -1;
    dw[0] = dw[1] = dw[2] = -1;
    for (i = 0; i < r->npass; i++) {
        KH1CmdPass *p = &r->pass[i];
        u32 tg = p->tgt;
        int earlier;
        clears(r, p);
        earlier = r->assume_drawn || (tg < KH1_CMD_TARGETS && (w[tg] >= 0 || r->tdrawn[tg]));
        p->load = earlier && !p->cleared ? KH1_LOAD_LOAD : KH1_LOAD_DONT_CARE;
        if (p->load == KH1_LOAD_LOAD) need(r, w, tg, KH1_WHY_REDRAWN);
        for (j = p->cmd0; j < p->cmd0 + p->ncmd && j < r->ncmd; j++) {
            u32 s = r->cmd[j].samples;
            if (!s) continue;
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
        if (tg < KH1_CMD_TARGETS) w[tg] = (s32)i;
        if (p->load == KH1_LOAD_LOAD) fc->loads++;
        else fc->dont_care++;
        if (p->cleared) fc->cleared++;
    }
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
            (u32)p->fbp * 32, p->depth < 3 ? ds[p->depth] : " depth ?", p->ncmd,
            p->load ? "LOAD" : "DONT_CARE", p->cleared ? " (cleared)" : "", st[p->store], why);
    if (p->depth != KH1_DS_NONE && p->depth < 3)
        sprintf(buf + strlen(buf), ", depth load %s store %s%s", p->dload ? "LOAD" : "DONT_CARE",
                p->zwrite ? st[p->dstore] : "none", p->zcleared ? " (cleared)" : "");
    if (p->feedback) sprintf(buf + strlen(buf), ", samples itself");
    return buf;
}
