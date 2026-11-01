/* The GPU vertex and the vertex shader's variants (include/platform/vertex.h, docs/renderer-spec.md
 * 4.13 "Session 124"), checked by tests/host/vertex_test.c against host/null/gsmem.c's sprite.  Not part
 * of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/vertex.h"
#include "platform/depth.h"

void kh1_vertex_ctx(KH1VertCtx *c, const KH1RenderPass *pass, u32 zbuf_lo, u32 prim, u32 tex0_lo, u32 tex0_hi) {
    u32 tw = tex0_lo >> 26 & 15, th = (tex0_lo >> 30 | tex0_hi << 2) & 15;
    if (tw > 10) tw = 10;
    if (th > 10) th = 10;
    c->pass = pass;
    c->zpsm = 0x30 | (zbuf_lo >> 24 & 15);
    c->fst = prim >> 8 & 1;
    c->su = 1.0f / (f32)(16u << tw);
    c->sv = 1.0f / (f32)(16u << th);
}

static f32 bits_f32(u32 v) {
    union { u32 u; f32 f; } x;
    x.u = v;
    return x.f;
}

void kh1_vertex_of(const KH1VertCtx *c, const KH1PaVert *in, u32 n, KH1GpuVert *out) {
    const KH1RenderPass *p = c->pass;
    u32 i;
    for (i = 0; i < n; i++) {
        const KH1PaVert *v = &in[i];
        KH1GpuVert *o = &out[i];
        /* half a GS pixel on: the GS's corner sample at the GPU's pixel centre */
        o->x = (((s32)(v->xy & 0xFFFF) - p->ofx + 8) / 16.0f + p->ox) * p->scale;
        o->y = (((s32)(v->xy >> 16) - p->ofy + 8) / 16.0f + p->oy) * p->scale;
        o->z = kh1_depth_f32(v->z, c->zpsm);
        if (c->fst) {
            o->s = (f32)(v->uv & 0x3FFF) * c->su;
            o->t = (f32)(v->uv >> 16 & 0x3FFF) * c->sv;
            o->q = 1.0f;
        } else {
            o->s = bits_f32(v->s);
            o->t = bits_f32(v->t);
            o->q = bits_f32(v->q);
        }
        o->rgba[0] = (u8)v->rgba;
        o->rgba[1] = (u8)(v->rgba >> 8);
        o->rgba[2] = (u8)(v->rgba >> 16);
        o->rgba[3] = (u8)(v->rgba >> 24);
        o->f = (u8)v->f;
        o->pad[0] = o->pad[1] = o->pad[2] = 0;
    }
}

void kh1_vertkey_of(const KH1PipeKey *p, KH1VertKey *out) {
    out->setup = p->shader.setup;
    out->tex = p->shader.setup || !p->shader.tex ? KH1_VTX_NONE : p->shader.fst ? KH1_VTX_UV : KH1_VTX_STQ;
    out->fog = !p->shader.setup && p->shader.fog;
}

u32 kh1_vertkey_index(const KH1VertKey *k) { return k->setup ? 0 : 1 + k->tex * 2 + k->fog; }

const char *kh1_vertkey_str(u32 index) {
    static const char *names[] = { "pos", "pos col", "pos col fog", "pos col uv", "pos col uv fog", "pos col stq",
                                   "pos col stq fog", "native pos", "native pos col", "native pos col fog", "native pos col uv",
                                   "native pos col uv fog", "native pos col stq", "native pos col stq fog",
                                   "skin pos", "skin pos col", "skin pos col fog", "skin pos col uv", "skin pos col uv fog",
                                   "skin pos col stq", "skin pos col stq fog" };
    return index < KH1_VERT_VARIANTS ? names[index] : "?";
}

u32 kh1_vertex_variants(const KH1PipeSet *s, u32 *mask) {
    u32 i, m = 0, n = 0;
    KH1VertKey k;
    for (i = 0; i < s->npipe; i++) {
        kh1_vertkey_of(&s->pipe[i], &k);
        m |= 1u << kh1_vertkey_index(&k);
    }
    for (i = 0; i < 7; i++) n += m >> i & 1;
    if (mask) *mask = m;
    return n;
}

u32 kh1_vertex_attrs(u32 index, KH1VtxAttr out[KH1_VTX_ATTRS]) {
    u32 nat = index >= KH1_VERT_NAT, skin = index >= KH1_VERT_SKIN, tex, fog, n = 0;
    if (index >= KH1_VERT_VARIANTS) return 0;
    if (skin) index -= KH1_VERT_SKIN;
    else if (nat) index -= KH1_VERT_NAT;
    tex = index >= 5 ? KH1_VTX_STQ : index >= 3 ? KH1_VTX_UV : KH1_VTX_NONE;
    fog = index && !(index & 1);
    /* the order is shadergen.c's kh1_shader_vert_cg: pos, col, tc, fog (and a native variant's matrix index) */
    out[n].name = "pos", out[n].offset = 0, out[n].format = KH1_VFMT_F32, out[n++].count = 3;
    if (index) out[n].name = "col", out[n].offset = 24, out[n].format = KH1_VFMT_U8N, out[n++].count = 4;
    if (tex) out[n].name = "tc", out[n].offset = 12, out[n].format = KH1_VFMT_F32, out[n++].count = tex == KH1_VTX_STQ ? 3 : 2;
    if (fog) out[n].name = "fog", out[n].offset = 28, out[n].format = KH1_VFMT_U8N, out[n++].count = 1;
    if (skin) { /* 2026-11-01: KH1GpuVertSk's offsets */
        u32 i;
        out[0].count = 4;
        for (i = 1; i < n; i++) out[i].offset = out[i].name[0] == 'c' ? 28 : out[i].name[0] == 't' ? 16 : 32;
        out[n].name = "mi", out[n].offset = 33, out[n].format = KH1_VFMT_U8N, out[n++].count = 1;
        out[n].name = "mi2", out[n].offset = 34, out[n].format = KH1_VFMT_U8N, out[n++].count = 1;
        out[n].name = "pos2", out[n].offset = 36, out[n].format = KH1_VFMT_F32, out[n++].count = 4;
    } else if (nat)
        out[n].name = "mi", out[n].offset = 29, out[n].format = KH1_VFMT_U8N, out[n++].count = 1;
    return n;
}

const char *kh1_vfmt_str(u32 format) { return format == KH1_VFMT_F32 ? "F32" : format == KH1_VFMT_U8N ? "U8N" : "?"; }

u32 kh1_vertex_gxm_attrs(u32 index, KH1GxmRegOf reg_of, void *prog, KH1GxmVtxAttr out[KH1_VTX_ATTRS], KH1GxmVtxStream *stream) {
    KH1VtxAttr a[KH1_VTX_ATTRS];
    u32 i, n = kh1_vertex_attrs(index, a);
    for (i = 0; i < n; i++) {
        s32 reg = reg_of(prog, a[i].name);
        if (reg < 0) return 0;
        out[i].streamIndex = 0;
        out[i].offset = a[i].offset;
        out[i].format = a[i].format == KH1_VFMT_F32 ? KH1_GXM_ATTR_F32 : KH1_GXM_ATTR_U8N;
        out[i].componentCount = a[i].count;
        out[i].regIndex = (u16)reg;
    }
    stream->stride = index >= KH1_VERT_SKIN ? KH1_VTX_SKIN_STRIDE : KH1_VTX_STRIDE;
    stream->indexSource = KH1_GXM_INDEX_16BIT;
    return n;
}
