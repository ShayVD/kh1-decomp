/* Batches and draw calls (include/platform/batch.h, docs/renderer-spec.md 4.13 "Session 124"), checked by
 * tests/host/batch_test.c and counted over a host run (host/null/pipes.c, KH1_HOST_TRACE=5) and the ELF's
 * static packets (tools/host/drawpipes.py --batches).  Session 125: the column groups (batch.h).  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/batch.h"

void *memset(void *, int, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);

void kh1_batch_reset(KH1Batcher *b) { memset(b, 0, sizeof *b); }

/* session 126: an event for the recorder (batch.h KH1_BEV_*) */
static void ev(KH1Batcher *b, u32 what, const KH1BatchKey *k, u32 arg) {
    if (b->ev) b->ev(b->ev_ctx, what, k, arg);
}

void kh1_batch_key(const KH1DrawState *d, const KH1RenderPass *p, KH1BatchKey *out) {
    memset(out, 0, sizeof *out);
    out->n = d->n;
    out->setup = d->setup;
    out->pipe[0] = d->pipe[0];
    out->pipe[1] = d->pipe[1];
    out->setup_pipe = d->setup_pipe;
    out->u = d->u;
    out->sampler = d->sampler;
    out->tex0_lo = d->tex0_lo;
    out->tex0_hi = d->tex0_hi;
    out->rt = p->id;
    out->psm = p->psm;
    out->depth = p->depth;
    out->fbp = p->fbp;
    out->fbw = p->fbw;
    out->sx0 = p->sx0;
    out->sy0 = p->sy0;
    out->sx1 = p->sx1;
    out->sy1 = p->sy1;
}

/* a primitive with key k (src: KH1_BEV_NEW, or the group's primitive replayed): joins the open batch or opens one */
static int plain(KH1Batcher *b, const KH1BatchKey *kp, u32 nv, u32 src) {
    KH1BatchKey k = *kp;
    KH1BatchCount *f = &b->frame;
    int opened = 0;
    if (!b->open || b->broken || memcmp(&k, &b->cur, sizeof k)) {
        const KH1BatchKey *c = &b->cur;
        if (!b->open || k.rt != c->rt || k.psm != c->psm || k.depth != c->depth || k.fbp != c->fbp || k.fbw != c->fbw)
            f->passes++;
        if (b->open) {
            if (k.n != c->n || k.setup != c->setup || memcmp(k.pipe, c->pipe, sizeof k.pipe) ||
                memcmp(&k.setup_pipe, &c->setup_pipe, sizeof k.setup_pipe))
                f->pipes++;
            if (k.tex0_lo != c->tex0_lo || k.tex0_hi != c->tex0_hi || memcmp(&k.sampler, &c->sampler, sizeof k.sampler))
                f->textures++;
            if (memcmp(&k.u, &c->u, sizeof k.u)) f->uniforms++;
            if (k.sx0 != c->sx0 || k.sy0 != c->sy0 || k.sx1 != c->sx1 || k.sy1 != c->sy1) f->scissors++;
            if (b->broken) f->breaks++;
        }
        b->cur = k;
        b->open = 1;
        f->batches++;
        f->draws += k.n + k.setup;
        opened = 1;
        ev(b, KH1_BEV_OPEN, &k, 0);
    }
    b->broken = 0;
    f->prims++;
    f->verts += nv;
    ev(b, KH1_BEV_PRIM, &k, src);
    return opened;
}

/* the same key but the scissor */
static int same_but_scissor(const KH1BatchKey *a, const KH1BatchKey *g) {
    KH1BatchKey t = *a;
    t.sx0 = g->sx0;
    t.sx1 = g->sx1;
    return !memcmp(&t, g, sizeof t);
}

static int matches(const KH1BatchPrim *g, const KH1BatchKey *k, u32 nv, u32 sig) {
    return sig && g->sig == sig && g->nv == nv && same_but_scissor(k, &g->k);
}

/* a primitive that samples the target it draws into (or one sharing its blocks) */
static int feedback(const KH1DrawState *d, const KH1RenderPass *p) {
    u32 id;
    if (!d->pipe[0].shader.tex) return 0;
    id = kh1_target_id((d->tex0_lo & 0x3FFF) / 32, d->tex0_lo >> 14 & 63, d->tex0_lo >> 20 & 63);
    return id == p->id || kh1_target_alias(id, p->id);
}

/* a repeat that stopped part way: its primitives drawn under their own column after all */
static void replay(KH1Batcher *b) {
    u32 i, n = b->rep;
    for (i = 0; i < n; i++) {
        KH1BatchKey k = b->grp[i].k;
        k.sx0 = b->cx0;
        k.sx1 = b->cx1;
        b->frame.prims--;
        b->frame.verts -= b->grp[i].nv;
        b->frame.merged--;
        if (plain(b, &k, b->grp[i].nv, i) && !i) b->gfull = 0;
        else if (!i) b->gfull = 1;
        if (!i) ev(b, KH1_BEV_GROUP, &k, !b->gfull);
        b->grp[i].k = k;
    }
    /* they are a new group under that column */
    b->ngrp = n;
    b->ux0 = b->cx0;
    b->ux1 = b->cx1;
    b->gstate = n ? KH1_GRP_RECORD : KH1_GRP_NONE;
}

static void absorb(KH1Batcher *b, u32 nv) {
    b->frame.prims++;
    b->frame.verts += nv;
    b->frame.merged++;
    ev(b, KH1_BEV_ABSORB, 0, 0);
    if (++b->rep < b->ngrp) return;
    /* the column is complete: the group's batches now draw the union */
    if (b->open && b->cur.sx0 == b->ux0 && b->cur.sx1 == b->ux1) b->cur.sx1 = b->cx1;
    b->ux1 = b->cx1;
    b->frame.columns++;
    ev(b, KH1_BEV_WIDEN, 0, (u32)b->cx1);
    b->gstate = KH1_GRP_DONE;
}

int kh1_batch_prim_sig(KH1Batcher *b, const KH1DrawState *d, const KH1RenderPass *p, u32 nv, u32 sig) {
    KH1BatchKey k;
    int opened;
    if (!d->n) return 0;
    kh1_batch_key(d, p, &k);
    if (b->gstate == KH1_GRP_REPEAT) {
        if (k.sx0 == b->cx0 && k.sx1 == b->cx1 && matches(&b->grp[b->rep], &k, nv, sig)) {
            absorb(b, nv);
            return 0;
        }
        replay(b);
    }
    if ((b->gstate == KH1_GRP_DONE || b->gstate == KH1_GRP_RECORD) && !b->gfull && b->ngrp &&
        k.sx0 == b->ux1 && k.sx1 > k.sx0 && k.sy0 == b->grp[0].k.sy0 && k.sy1 == b->grp[0].k.sy1 &&
        matches(&b->grp[0], &k, nv, sig)) {
        b->gstate = KH1_GRP_REPEAT;
        b->rep = 0;
        b->cx0 = k.sx0;
        b->cx1 = k.sx1;
        absorb(b, nv);
        return 0;
    }
    opened = plain(b, &k, nv, KH1_BEV_NEW);
    if (b->gstate != KH1_GRP_RECORD || !b->ngrp || k.sx0 != b->ux0 || k.sx1 != b->ux1 || k.sy0 != b->grp[0].k.sy0 ||
        k.sy1 != b->grp[0].k.sy1) {
        b->gstate = KH1_GRP_RECORD;
        b->ngrp = 0;
        b->ux0 = k.sx0;
        b->ux1 = k.sx1;
        b->gfull = !opened; /* a group shares no batch with what came before it (its batches get widened) */
        ev(b, KH1_BEV_GROUP, &k, !b->gfull);
    }
    if (b->ngrp < KH1_BATCH_GROUP && !feedback(d, p)) {
        b->grp[b->ngrp].k = k;
        b->grp[b->ngrp].nv = nv;
        b->grp[b->ngrp].sig = sig;
        ev(b, KH1_BEV_REC, &k, b->ngrp);
        b->ngrp++;
    } else {
        if (!b->gfull) ev(b, KH1_BEV_END, 0, 0);
        b->gfull = 1;
    }
    return opened;
}

int kh1_batch_prim(KH1Batcher *b, const KH1DrawState *d, const KH1RenderPass *p, u32 nv) {
    return kh1_batch_prim_sig(b, d, p, nv, 0);
}

/* the column group ends (a transfer, the frame) */
static void group_end(KH1Batcher *b) {
    if (b->gstate == KH1_GRP_REPEAT) replay(b);
    if (b->gstate != KH1_GRP_NONE) ev(b, KH1_BEV_END, 0, 0);
    b->gstate = KH1_GRP_NONE;
    b->ngrp = 0;
    b->gfull = 0;
}

void kh1_batch_break(KH1Batcher *b) {
    group_end(b);
    if (b->open) b->broken = 1;
}

void kh1_batch_frame(KH1Batcher *b) {
    u32 *f = (u32 *)&b->frame, *t = (u32 *)&b->total, *m = (u32 *)&b->max, i;
    group_end(b);
    for (i = 0; i < sizeof b->frame / sizeof(u32); i++) {
        t[i] += f[i];
        if (f[i] > m[i]) m[i] = f[i];
    }
    memset(&b->frame, 0, sizeof b->frame);
    b->frames++;
    b->open = 0;
    b->broken = 0;
}
