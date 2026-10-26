/* The command list as GXM calls, a "null GXM" (include/platform/gxmrec.h, docs/renderer-spec.md 4.13
 * "Session 128"): one frame of cmdbuf.c's recorder walked into the calls a Vita renderer makes, checked by
 * tests/host/cmdbuf_test.c ("gxm": the calls replayed through its rasteriser give the commands' pixels).  Plain C
 * with no libc but memset / memcmp / sprintf / strlen (the Vita build compiles host/port/).  Not part of the PS2 build
 * (it lives outside src/). */
#include "common.h"
#include "platform/gxmrec.h"
#include "platform/primasm.h"
#include "platform/target.h"
#include "platform/texfmt.h"
#include "platform/vertex.h"

int sprintf(char *, const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);
__SIZE_TYPE__ strlen(const char *);

void kh1_gxm_clear(KH1GxmRec *g) { memset(g, 0, sizeof *g); }

static KH1GxmCall *emit(KH1GxmRec *g, u32 op, u32 cmd) {
    KH1GxmCall *c;
    if (g->n == KH1_GXM_CALLS) { g->frame.lost++; return 0; }
    c = &g->call[g->n++];
    memset(c, 0, sizeof *c);
    c->op = (u8)op;
    c->slot = c->pslot = -1;
    c->cmd = cmd;
    g->frame.calls++;
    return c;
}

static u32 pipe_index(KH1GxmRec *g, const KH1PipeKey *p) {
    u32 i;
    for (i = 0; i < g->npipe; i++)
        if (!memcmp(&g->pipe[i], p, sizeof *p)) return i;
    if (g->npipe == KH1_GXM_PIPES) { g->frame.lost++; return ~0u; }
    g->pipe[g->npipe] = *p;
    return g->npipe++;
}

static u32 frag_index(KH1GxmRec *g, const KH1ShaderKey *k) {
    u32 i;
    for (i = 0; i < g->nfrag; i++)
        if (!memcmp(&g->frag[i], k, sizeof *k)) return i;
    if (g->nfrag == KH1_GXM_FRAGS) { g->frame.lost++; return ~0u; }
    g->frag[g->nfrag] = *k;
    return g->nfrag++;
}

/* what is set in the open scene */
typedef struct {
    int open;            /* a scene is open: the pass index + 1 */
    u32 pipe;            /* ~0u: nothing set */
    int tex;             /* SET_TEXTURE given */
    s16 tslot, pslot;
    u8 src;
    u32 tex0_lo, tex0_hi;
    int region;
    s16 sx0, sy0, sx1, sy1;
} Bound;

static void end_scene(KH1GxmRec *g, const KH1CmdRec *r, Bound *b) {
    const KH1CmdPass *p;
    KH1GxmCall *c;
    if (!b->open) return;
    p = &r->pass[b->open - 1];
    c = emit(g, KH1_GXM_END_SCENE, p->cmd0 + p->ncmd);
    if (c) {
        c->tgt = p->tgt;
        c->rt = p->rt;
        c->depth = p->depth;
        c->store = p->store;
        c->dstore = p->depth != KH1_DS_NONE && p->zwrite ? p->dstore : KH1_STORE_DISCARD;
        if (p->store != KH1_STORE_DISCARD) g->frame.stores++;
    }
    b->open = 0;
}

static void begin_scene(KH1GxmRec *g, const KH1CmdRec *r, Bound *b, u32 pass) {
    const KH1CmdPass *p = &r->pass[pass];
    KH1GxmCall *c = emit(g, KH1_GXM_BEGIN_SCENE, p->cmd0);
    if (c) {
        c->tgt = p->tgt;
        c->rt = p->rt;
        c->psm = p->psm;
        c->depth = p->depth;
        c->fbp = p->fbp;
        c->fbw = p->fbw;
        c->w = (u16)p->w;
        c->h = (u16)p->h;
        c->load = p->load;
        c->dload = p->depth != KH1_DS_NONE ? p->dload : KH1_LOAD_DONT_CARE;
        c->cleared = p->cleared;
        c->uoff = p->uoff;
        if (p->load == KH1_LOAD_LOAD) g->frame.loads++;
    }
    g->frame.scenes++;
    memset(b, 0, sizeof *b);
    b->open = (int)pass + 1;
    b->pipe = ~0u;
}

static void draw(KH1GxmRec *g, const KH1CmdRec *r, Bound *b, u32 ci) {
    const KH1Cmd *k = &r->cmd[ci];
    const KH1DrawState *d = &k->d;
    const KH1PipeKey *ps[4];
    KH1PipeKey clear;
    KH1GxmCall *c;
    u32 n = 0, i;
    if (b->open != (int)k->pass + 1) {
        end_scene(g, r, b);
        begin_scene(g, r, b, k->pass);
    }
    if (d->setup) { /* the clear, then the set-up (drawstate.h kh1_date_clear_pipe) */
        kh1_date_clear_pipe(&d->setup_pipe, &clear);
        ps[n++] = &clear;
        ps[n++] = &d->setup_pipe;
    }
    for (i = 0; i < d->n; i++) ps[n++] = &d->pipe[i];
    if (!n || !k->nv) return;
    /* the texture: the cache's entry or a target's own (the same for every GPU draw of the command) */
    if (d->pipe[0].shader.tex &&
        (!b->tex || b->tslot != k->tslot || b->pslot != k->pslot || b->src != k->samples || b->tex0_lo != d->tex0_lo ||
         b->tex0_hi != d->tex0_hi)) {
        c = emit(g, KH1_GXM_SET_TEXTURE, ci);
        if (c) {
            c->slot = k->samples ? -1 : k->tslot;
            c->pslot = d->pipe[0].shader.tex >= KH1_TEXFMT_P8 ? k->pslot : -1; /* an indexed texture's palette */
            c->src = k->samples;
            c->tex0_lo = d->tex0_lo;
            c->tex0_hi = d->tex0_hi;
        }
        b->tex = 1;
        b->tslot = k->tslot;
        b->pslot = k->pslot;
        b->src = k->samples;
        b->tex0_lo = d->tex0_lo;
        b->tex0_hi = d->tex0_hi;
        g->frame.textures++;
    }
    if (!b->region || b->sx0 != k->k.sx0 || b->sy0 != k->k.sy0 || b->sx1 != k->k.sx1 || b->sy1 != k->k.sy1) {
        c = emit(g, KH1_GXM_SET_REGION, ci);
        if (c) {
            c->sx0 = (s16)k->k.sx0;
            c->sy0 = (s16)k->k.sy0;
            c->sx1 = (s16)k->k.sx1;
            c->sy1 = (s16)k->k.sy1;
        }
        b->region = 1;
        b->sx0 = (s16)k->k.sx0;
        b->sy0 = (s16)k->k.sy0;
        b->sx1 = (s16)k->k.sx1;
        b->sy1 = (s16)k->k.sy1;
        g->frame.regions++;
    }
    c = emit(g, KH1_GXM_SET_UNIFORMS, ci); /* every command has its own slot */
    if (c) c->uoff = k->uoff;
    g->frame.uniforms++;
    for (i = 0; i < n; i++) {
        u32 pi = pipe_index(g, ps[i]);
        if (pi != b->pipe) {
            KH1VertKey vk;
            c = emit(g, KH1_GXM_SET_PROGRAMS, ci);
            kh1_vertkey_of(ps[i], &vk);
            if (c) {
                c->pipe = pi;
                c->frag = frag_index(g, &ps[i]->shader);
                c->vert = kh1_vertkey_index(&vk);
            }
            b->pipe = pi;
            g->frame.programs++;
        }
        c = emit(g, KH1_GXM_DRAW, ci);
        if (c) {
            c->cls = ps[i]->cls;
            c->stencil = ps[i]->stencil;
            c->v0 = k->v0;
            c->nv = k->nv;
        }
        g->frame.draws++;
    }
}

void kh1_gxm_frame(KH1GxmRec *g, const KH1CmdRec *r) {
    Bound b;
    u32 i;
    KH1GxmCall *c;
    g->n = g->npipe = g->nfrag = 0;
    memset(&g->frame, 0, sizeof g->frame);
    memset(&b, 0, sizeof b);
    for (i = 0; i < r->ncmd; i++) {
        const KH1Cmd *k = &r->cmd[i];
        const KH1CmdXfer *x = &k->x;
        switch (k->kind) {
        case KH1_CMD_DRAW:
            draw(g, r, &b, i);
            break;
        case KH1_CMD_TEXTURE:
            if ((c = emit(g, KH1_GXM_TEX_UPLOAD, i)) != 0) {
                c->slot = x->slot;
                c->tex0_lo = x->tex0_lo;
                c->tex0_hi = x->tex0_hi;
            }
            g->frame.tex_uploads++;
            break;
        case KH1_CMD_CLUT:
            if (x->src) {
                end_scene(g, r, &b);
                if ((c = emit(g, KH1_GXM_PAL_READBACK, i)) != 0) {
                    c->src = x->src;
                    c->slot = x->slot;
                    c->tex0_lo = x->tex0_lo;
                    c->tex0_hi = x->tex0_hi;
                }
                g->frame.pal_readbacks++;
            } else if (x->fill) {
                if ((c = emit(g, KH1_GXM_PAL_FILL, i)) != 0) {
                    c->slot = x->slot;
                    c->tex0_lo = x->tex0_lo;
                    c->tex0_hi = x->tex0_hi;
                }
                g->frame.pal_fills++;
            }
            break;
        case KH1_CMD_UPLOAD:
        case KH1_CMD_COPY:
            if (!x->src && !x->dst) break; /* GS memory only: the CPU's */
            end_scene(g, r, &b);
            c = emit(g, k->kind == KH1_CMD_UPLOAD ? KH1_GXM_TARGET_UPLOAD : KH1_GXM_BLIT, i);
            if (c) {
                c->tgt = x->dst;
                c->src = k->kind == KH1_CMD_COPY ? x->src : 0;
                c->dx = x->dx;
                c->dy = x->dy;
                c->w = x->w;
                c->h = x->h;
            }
            if (k->kind == KH1_CMD_UPLOAD) g->frame.target_uploads++;
            else g->frame.blits++;
            break;
        }
    }
    end_scene(g, r, &b);
    g->frame.frames = 1;
    g->total.frames++;
    g->total.calls += g->frame.calls;
    g->total.scenes += g->frame.scenes;
    g->total.draws += g->frame.draws;
    g->total.programs += g->frame.programs;
    g->total.textures += g->frame.textures;
    g->total.regions += g->frame.regions;
    g->total.uniforms += g->frame.uniforms;
    g->total.tex_uploads += g->frame.tex_uploads;
    g->total.pal_fills += g->frame.pal_fills;
    g->total.pal_readbacks += g->frame.pal_readbacks;
    g->total.target_uploads += g->frame.target_uploads;
    g->total.blits += g->frame.blits;
    g->total.loads += g->frame.loads;
    g->total.stores += g->frame.stores;
    g->total.lost += g->frame.lost;
}

const char *kh1_gxm_call_str(const KH1GxmCall *c) {
    static const char *op[] = { "begin_scene", "end_scene", "tex_upload", "pal_fill", "pal_readback", "target_upload",
                                "blit", "set_programs", "set_texture", "set_region", "set_uniforms", "draw" };
    static const char *rt[] = { "display", "Z area as colour", "movie frame", "3D target", "slot capture",
                                "off-screen buffer", "CLUT pass", "other" };
    static const char *ds[] = { "", " depth main", " depth shadow" };
    static const char *st[] = { "DISCARD", "STORE", "OPEN" };
    static const char *cls[] = { "none", "points", "lines", "tri" };
    static char b[160];
    char *p = b;
    p += sprintf(p, "%s", c->op < KH1_GXM_OPS ? op[c->op] : "?");
    switch (c->op) {
    case KH1_GXM_BEGIN_SCENE:
        sprintf(p, " %s (%04x)%s %u x %u load %s%s", c->rt < KH1_RT_COUNT ? rt[c->rt] : "?", (u32)c->fbp * 32,
                c->depth < 3 ? ds[c->depth] : "", c->w, c->h, c->load ? "LOAD" : "DONT_CARE", c->cleared ? " (cleared)" : "");
        if (c->depth != KH1_DS_NONE) sprintf(b + strlen(b), " depth %s", c->dload ? "LOAD" : "DONT_CARE");
        break;
    case KH1_GXM_END_SCENE:
        sprintf(p, " %s store %s", c->rt < KH1_RT_COUNT ? rt[c->rt] : "?", c->store < 3 ? st[c->store] : "?");
        if (c->depth != KH1_DS_NONE) sprintf(b + strlen(b), " depth %s", c->dstore < 3 ? st[c->dstore] : "?");
        break;
    case KH1_GXM_TEX_UPLOAD: case KH1_GXM_PAL_FILL:
        sprintf(p, " slot %d (%04x)", c->slot, c->op == KH1_GXM_PAL_FILL ? c->tex0_hi >> 5 & 0x3FFF : c->tex0_lo & 0x3FFF);
        break;
    case KH1_GXM_PAL_READBACK:
        sprintf(p, " slot %d from target %u", c->slot, c->src - 1u);
        break;
    case KH1_GXM_TARGET_UPLOAD: case KH1_GXM_BLIT:
        sprintf(p, " %u x %u at (%u, %u) into %s%u", c->w, c->h, c->dx, c->dy, c->tgt ? "target " : "GS memory", c->tgt ? c->tgt - 1u : 0u);
        if (c->op == KH1_GXM_BLIT && c->src) sprintf(b + strlen(b), " from target %u", c->src - 1u);
        break;
    case KH1_GXM_SET_PROGRAMS:
        sprintf(p, " pipe %u frag %u vert %u", c->pipe, c->frag, c->vert);
        break;
    case KH1_GXM_SET_TEXTURE:
        if (c->src) sprintf(p, " target %u", c->src - 1u);
        else sprintf(p, " entry %d (%04x)", c->slot, c->tex0_lo & 0x3FFF);
        if (c->pslot >= 0) sprintf(b + strlen(b), " palette %d", c->pslot);
        break;
    case KH1_GXM_SET_REGION:
        sprintf(p, " (%d, %d) .. (%d, %d)", c->sx0, c->sy0, c->sx1, c->sy1);
        break;
    case KH1_GXM_SET_UNIFORMS:
        sprintf(p, " at %u", c->uoff);
        break;
    case KH1_GXM_DRAW:
        sprintf(p, " %s %u from %u%s", cls[c->cls & 3], c->nv, c->v0, c->stencil == 3 ? " (stencil clear)" : c->stencil == 2 ? " (stencil set-up)" :
                c->stencil ? " (stencil test)" : "");
        break;
    }
    return b;
}
