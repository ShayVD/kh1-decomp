/* Batches and draw calls (include/platform/batch.h, docs/renderer-spec.md 4.13 "Session 124"), checked by
 * tests/host/batch_test.c and counted over a host run (host/null/pipes.c, KH1_HOST_TRACE=5) and the ELF's
 * static packets (tools/host/drawpipes.py --batches).  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/batch.h"

void *memset(void *, int, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);

void kh1_batch_reset(KH1Batcher *b) { memset(b, 0, sizeof *b); }

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

int kh1_batch_prim(KH1Batcher *b, const KH1DrawState *d, const KH1RenderPass *p, u32 nv) {
    KH1BatchKey k;
    KH1BatchCount *f = &b->frame;
    int opened = 0;
    if (!d->n) return 0;
    kh1_batch_key(d, p, &k);
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
    }
    b->broken = 0;
    f->prims++;
    f->verts += nv;
    return opened;
}

void kh1_batch_break(KH1Batcher *b) {
    if (b->open) b->broken = 1;
}

void kh1_batch_frame(KH1Batcher *b) {
    u32 *f = (u32 *)&b->frame, *t = (u32 *)&b->total, *m = (u32 *)&b->max, i;
    for (i = 0; i < sizeof b->frame / sizeof(u32); i++) {
        t[i] += f[i];
        if (f[i] > m[i]) m[i] = f[i];
    }
    memset(&b->frame, 0, sizeof b->frame);
    b->frames++;
    b->open = 0;
    b->broken = 0;
}
