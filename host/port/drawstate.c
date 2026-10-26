/* The whole draw state a port's GPU needs for one GS draw state: pipelines, the fragment shader's
 * variant, the uniforms, the sampler and the texture binding (include/platform/drawstate.h,
 * docs/renderer-spec.md 4.13 "Session 123"), checked by tests/host/drawstate_test.c and counted over
 * a host run's draw states (host/null/pipes.c) and the ELF's static packets (tools/host/drawpipes.py).
 * Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/drawstate.h"
#include "platform/primasm.h"
#include "platform/texfmt.h"

int sprintf(char *, const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);

/* the shader's part every GPU draw of the state shares */
static void shader_of(const KH1DrawRegs *r, const KH1DrawState *d, KH1ShaderKey *k) {
    u32 psm = r->tex0_lo >> 20 & 63;
    if (r->prim >> 4 & 1) {
        k->tex = kh1_texfmt_of(psm);
        k->texa = kh1_texfmt_texa(psm) != 0;
        k->tfx = r->tex0_hi >> 3 & 3;
        k->tcc = r->tex0_hi >> 2 & 1;
        k->fst = r->prim >> 8 & 1;
        k->su = d->sampler.u.shader;
        k->sv = d->sampler.v.shader;
    }
    k->fog = r->prim >> 5 & 1;
    if (d->blend.kind == KH1_BLEND_FETCH) {
        u32 fpsm = r->frame_lo >> 24 & 63, i;
        k->fetch = d->blend.enable ? 1 : 2;
        k->fabcd = k->fetch == 1 ? d->blend.abcd : 0;
        k->fpsm = fpsm == 0x01 ? 1 : fpsm == 0x02 || fpsm == 0x0A ? 2 : 0;
        for (i = 0; i < 4; i++) k->fbm[i] = (u8)(r->frame_hi >> i * 8);
        if (k->fpsm == 1) k->fbm[3] = 0; /* no alpha stored */
    }
    if (k->fetch == 1) return;
    k->pre_a = (u8)(d->blend.pre_a + 2);
    k->pre_d = (u8)(d->blend.pre_d + 2);
    k->pre_floor = d->blend.pre_floor;
    k->csel = d->blend.pre_a ? d->blend.csel : 0; /* C only matters when the shader multiplies by it */
}

static void pipe_of(const KH1DrawState *d, const KH1ShaderKey *sk, u32 cls, const KH1AtestDraw *a, KH1PipeKey *p) {
    p->cls = (u8)cls;
    p->shader = *sk;
    if (d->blend.enable && sk->fetch != 1) {
        p->blend = 1;
        p->eq = d->blend.eq;
        p->fs = d->blend.fs;
        p->fd = d->blend.fd;
    }
    p->mask = a->mask;
    p->ztest = d->depth.func;
    p->zwrite = a->zwrite && d->depth.write;
    p->stencil = d->atest.date;
    p->shader.discard = a->discard;
    p->shader.atst = a->discard ? d->atest.atst : 0;
}

void kh1_drawstate_of(const KH1DrawRegs *r, KH1DrawState *out) {
    u32 tme = r->prim >> 4 & 1, abe = r->prim >> 6 & 1, frame_psm = r->frame_lo >> 24 & 63, i, cls;
    u32 tw = r->tex0_lo >> 26 & 15, th = (r->tex0_lo >> 30 | r->tex0_hi << 2) & 15;
    KH1ShaderKey sk;
    memset(out, 0, sizeof *out);
    memset(&sk, 0, sizeof sk);
    kh1_blend_state(r->alpha_lo, r->alpha_hi, abe, frame_psm, r->frame_hi, &out->blend);
    kh1_atest_state(r->test_lo, out->blend.mask, r->zbuf_hi & 1, &out->atest);
    kh1_depth_state(r->zbuf_lo, r->zbuf_hi, r->test_lo, &out->depth);
    if (tme) {
        kh1_sampler_of(r->clamp_lo, r->clamp_hi, r->tex1_lo, r->tex1_hi, tw > 10 ? 10 : tw, th > 10 ? 10 : th,
                       &out->sampler);
        out->tex0_lo = r->tex0_lo;
        out->tex0_hi = r->tex0_hi & 0x1F; /* TH's top bits, TCC, TFX: the CLUT is the palette cache's */
    }
    shader_of(r, out, &sk);
    cls = kh1_pa_class(r->prim);
    /* the uniforms, each only where the shader reads it */
    if (out->blend.enable && out->blend.csel == 2) out->u.fix = out->blend.fix;
    if (sk.fog) out->u.fogcol = r->fogcol & 0xFFFFFF;
    if (sk.texa) {
        out->u.ta0 = r->texa_lo & 0xFF;
        out->u.aem = r->texa_lo >> 15 & 1;
        out->u.ta1 = r->texa_hi & 0xFF;
    }
    if (sk.su) { out->u.u0 = out->sampler.u.lo; out->u.u1 = out->sampler.u.hi; }
    if (sk.sv) { out->u.v0 = out->sampler.v.lo; out->u.v1 = out->sampler.v.hi; }
    if (sk.fetch == 1) {
        out->u.abcd = out->blend.abcd;
        out->u.psm = frame_psm;
    }
    if (sk.fetch) out->u.fbmsk = r->frame_hi;
    if (!out->depth.draw || cls == KH1_PA_NONE) return; /* ZTST NEVER, PRIM 7: nothing drawn */
    out->n = out->atest.n;
    for (i = 0; i < out->n; i++) pipe_of(out, &sk, cls, &out->atest.draw[i], &out->pipe[i]);
    if (out->n && out->pipe[0].shader.discard) out->u.aref = out->atest.aref;
    if (out->n && out->atest.date) {
        /* the set-up: the draw's own primitives (session 129: its class, so a line or point draw marks its
         * own pixels), no colour, no depth, stencil written, its own shader */
        KH1PipeKey *p = &out->setup_pipe;
        out->setup = 1;
        p->cls = (u8)cls;
        p->ztest = KH1_ZTST_ALWAYS;
        p->stencil = 2;
        p->shader.setup = 1;
        p->shader.datm = out->atest.datm;
        p->shader.discard = KH1_DISCARD_FAIL;
    }
}

void kh1_date_clear_pipe(const KH1PipeKey *setup, KH1PipeKey *out) {
    *out = *setup;
    out->stencil = 3;
    out->shader.setup = 2;
    out->shader.datm = 0;
    out->shader.discard = KH1_DISCARD_NONE;
}

const char *kh1_pipekey_str(const KH1PipeKey *k) {
    static const char *cls[] = { "none", "point", "line", "tri" };
    static const char *eq[] = { "add", "sub", "rsub" };
    static const char *bf[] = { "0", "1", "sa", "1-sa", "da", "1-da" };
    static const char *zt[] = { "never", "always", "ge", "gt" };
    static const char *fmt[] = { "-", "rgba8", "5551", "p8", "p4" };
    static const char *tfx[] = { "mod", "decal", "hl", "hl2" };
    static const char *at[] = { "never", "always", "lt", "le", "eq", "ge", "gt", "ne" };
    static const char *ss[] = { "", "c", "t" };
    static char b[200];
    const KH1ShaderKey *s = &k->shader;
    char *p = b;
    p += sprintf(p, "%s", cls[k->cls & 3]);
    if (k->blend) p += sprintf(p, " %s/1/%s", eq[k->eq % 3], bf[k->fd % 6]);
    p += sprintf(p, " mask %x z %s%s", k->mask, zt[k->ztest & 3], k->zwrite ? "/w" : "");
    if (k->stencil) p += sprintf(p, " stencil %s", k->stencil == 1 ? "test" : k->stencil == 3 ? "clear" : "set");
    p += sprintf(p, " |");
    if (s->setup == 2) { sprintf(p, " date-clear"); return b; }
    if (s->setup) { sprintf(p, " date-setup datm %u", s->datm); return b; }
    if (s->tex)
        p += sprintf(p, " %s%s %s%s %s%s%s%s", fmt[s->tex % 5], s->texa ? "+texa" : "", tfx[s->tfx & 3],
                     s->tcc ? "" : " tcc0", s->fst ? "uv" : "stq", s->su || s->sv ? " region " : "",
                     ss[s->su % 3], ss[s->sv % 3]);
    else
        p += sprintf(p, " flat");
    if (s->fog) p += sprintf(p, " fog");
    if (s->fetch == 1) p += sprintf(p, " fetch %02x", s->fabcd);
    if (s->fetch == 2) p += sprintf(p, " fetch-mask");
    if (s->fetch && (s->fbm[0] | s->fbm[1] | s->fbm[2] | s->fbm[3]))
        p += sprintf(p, " fbmsk %02x%02x%02x%02x", s->fbm[3], s->fbm[2], s->fbm[1], s->fbm[0]);
    if (s->fetch != 1 && (s->pre_a != 2 || s->pre_d != 3))
        p += sprintf(p, " pre %d,%d%s%s", s->pre_a - 2, s->pre_d - 2, s->csel == 1 ? " ad" : s->csel == 2 ? " fix" : "",
                     s->pre_floor == 1 ? " floor" : s->pre_floor == 2 ? " ceil" : "");
    if (s->discard) sprintf(p, " discard %s %s", s->discard == KH1_DISCARD_FAIL ? "fail" : "pass", at[s->atst & 7]);
    return b;
}

void kh1_pipeset_clear(KH1PipeSet *s) { memset(s, 0, sizeof *s); }

static void add_shader(KH1PipeSet *s, const KH1ShaderKey *k) {
    u32 i;
    for (i = 0; i < s->nshader; i++)
        if (!memcmp(&s->shader[i], k, sizeof *k)) return;
    if (s->nshader == KH1_PIPESET_MAX) { s->lost++; return; }
    s->shader[s->nshader++] = *k;
}

static void add_pipe(KH1PipeSet *s, const KH1PipeKey *k) {
    u32 i;
    add_shader(s, &k->shader);
    for (i = 0; i < s->npipe; i++)
        if (!memcmp(&s->pipe[i], k, sizeof *k)) { s->pipe_uses[i]++; return; }
    if (s->npipe == KH1_PIPESET_MAX) { s->lost++; return; }
    s->pipe[s->npipe] = *k;
    s->pipe_uses[s->npipe++] = 1;
}

void kh1_pipeset_add(KH1PipeSet *s, const KH1DrawState *d) {
    u32 i;
    u8 smp[4];
    s->states++;
    if (!d->n) { s->empty++; return; }
    if (d->setup) {
        KH1PipeKey c;
        kh1_date_clear_pipe(&d->setup_pipe, &c);
        add_pipe(s, &c);
        add_pipe(s, &d->setup_pipe);
    }
    for (i = 0; i < d->n; i++) add_pipe(s, &d->pipe[i]);
    if (!d->pipe[0].shader.tex) return;
    smp[0] = d->sampler.u.addr;
    smp[1] = d->sampler.v.addr;
    smp[2] = d->sampler.linear;
    smp[3] = 0;
    for (i = 0; i < s->nsampler; i++)
        if (!memcmp(s->sampler[i], smp, 4)) return;
    if (s->nsampler < KH1_PIPESET_MAX) memcpy(s->sampler[s->nsampler++], smp, 4);
}
