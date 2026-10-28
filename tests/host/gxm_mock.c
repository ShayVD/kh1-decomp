/* A software stand-in for the Vita's sceGxm, vitaShaRK and the bits of vita2d host/vita/gxm.c calls, so the Vita's GPU
 * renderer runs inside the host runner (out/host/kh1-host) and its picture can be compared with the GS model's
 * (tools/vita/gxmcheck.sh, docs/vita-build.md "GPU").  Compiled for the host (-m32) against vitasdk's own headers,
 * so gxm.c's calls are checked against the real prototypes and struct layouts.
 *
 *   - a "compiled program" is the Cg text itself (shark_compile_shader_extended copies it): parameters are read
 *     from main()'s list, and a draw runs the vertex and fragment text through shadergen.c's interpreter
 *     (kh1_shader_run), so the shaders gxm.c binds are the ones that run;
 *   - the rasteriser: GXM's viewport, pixel centres, a top-left rule, attributes interpolated linearly (w is 1),
 *     the region clip (per pixel), depth (24 bits) and stencil in the depth-stencil memory, the fragment
 *     program's blend and write mask, UCHAR4 output; textures RGBA8 / U1U5U5U5 / P8 / P4, point or bilinear,
 *     repeat or clamp, from the SceGxmTexture words this file packs;
 *   - a depth-stencil surface without force-load starts each scene at depth 1.0 and stencil 0, and without
 *     force-store is scrambled at the scene's end (what a tiled GPU leaves); colour is loaded and stored.
 *
 * KH1_HOST_GXM=N turns it on: gxm.c takes every frame's commands (uploads always), the rasteriser draws the two
 * frames before each Nth and the display target is compared with the GS model's display buffer (RGB) at each
 * Nth; KH1_HOST_GXM_POINT=1 samples point (the model's sprites are point-sampled), KH1_HOST_GXM_PPM=DIR writes
 * both pictures, KH1_HOST_GXM_FROM=F checks every frame from F.  Run with KH1_HOST_SHOT so the model draws its pixels.  Not part of the PS2 build. */
#include <psp2/gxm.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vita2d.h>
#include <vitashark.h>
#include "common.h"
#include "gsmem.h"
#include "platform/cmdbuf.h"
#include "platform/gxmrec.h"
#include "platform/shadergen.h"
#include "platform/target.h"

int kh1_vita_gxm_init(void);
void kh1_vita_gxm_frame(const KH1CmdRec *r);
const void *kh1_vita_gxm_target(u32 rt, u32 *w, u32 *h, u32 *stride);
extern void (*kh1_pipes_frame_hook)(const KH1CmdRec *r);

void kh1_vita_log(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}

/* ---- the system ---- */
static void *blocks[64];
static int nblocks;
SceUID sceKernelAllocMemBlock(const char *name, SceKernelMemBlockType type, SceSize size, SceKernelAllocMemBlockOpt *opt) {
    (void)name; (void)type; (void)opt;
    if (nblocks == 64 || !(blocks[nblocks] = aligned_alloc(4096, (size + 4095) & ~4095u))) return -1;
    memset(blocks[nblocks], 0, size);
    return 0x100 + nblocks++;
}
int sceKernelGetMemBlockBase(SceUID uid, void **base) {
    *base = uid >= 0x100 && uid < 0x100 + nblocks ? blocks[uid - 0x100] : 0;
    return *base ? 0 : -1;
}
int sceKernelFreeMemBlock(SceUID uid) { (void)uid; return 0; }
SceUInt64 sceKernelGetProcessTimeWide(void) { return 0; }
SceUID sceIoOpen(const char *f, int fl, SceMode m) { (void)f; (void)fl; (void)m; return -1; } /* no shader cache */
int sceIoClose(SceUID fd) { (void)fd; return 0; }
int sceIoRead(SceUID fd, void *d, SceSize n) { (void)fd; (void)d; (void)n; return -1; }
int sceIoWrite(SceUID fd, const void *d, SceSize n) { (void)fd; (void)d; return (int)n; }
SceOff sceIoLseek(SceUID fd, SceOff o, int w) { (void)fd; (void)o; (void)w; return -1; }
int sceIoMkdir(const char *d, SceMode m) { (void)d; (void)m; return 0; }

/* ---- programs: the Cg text and its parameters ---- */
enum { P_IN, P_UNIFORM, P_SAMPLER, P_OUT };
struct SceGxmProgramParameter { char name[16]; int kind, index; };
typedef struct {
    char magic[4];
    int frag, kh1;            /* kh1: shadergen's text (the interpreter runs it) */
    int nparam;
    struct SceGxmProgramParameter param[16];
    char text[];
} MockProg;

static void parse_params(MockProg *p) {
    const char *s = strstr(p->text, "main("), *e;
    int nin = 0, nu = 0, ns = 0, no = 0;
    if (!s) return;
    s += 5;
    e = strchr(s, ')');
    while (s && s < e && p->nparam < 16) {
        const char *c = memchr(s, ',', (size_t)(e - s)), *end = c ? c : e, *colon, *q;
        char buf[128];
        struct SceGxmProgramParameter *pp = &p->param[p->nparam];
        size_t n = (size_t)(end - s) < sizeof buf - 1 ? (size_t)(end - s) : sizeof buf - 1;
        memcpy(buf, s, n);
        buf[n] = 0;
        colon = strchr(buf, ':');
        if (colon) buf[colon - buf] = 0;
        for (n = strlen(buf); n && (buf[n - 1] == ' ' || buf[n - 1] == '\n'); n--) buf[n - 1] = 0;
        q = strrchr(buf, ' ');
        snprintf(pp->name, sizeof pp->name, "%s", q ? q + 1 : buf);
        if (strstr(buf, "sampler2D")) pp->kind = P_SAMPLER, pp->index = ns++;
        else if (strstr(buf, "uniform")) pp->kind = P_UNIFORM, pp->index = nu++;
        else if (!strncmp(buf + strspn(buf, " \n"), "out ", 4)) pp->kind = P_OUT, pp->index = no++;
        else pp->kind = P_IN, pp->index = nin++;
        p->nparam++;
        s = c ? c + 1 : 0;
    }
}

static SceShaccCgCompileOutput no_output;
int shark_init_simple(const char *path) { (void)path; return 0; }
int shark_init(const char *path) { (void)path; return 0; }
void shark_clear_output(void) {}
void shark_end(void) {}
const SceShaccCgCompileOutput *shark_get_internal_compile_output(void) { return &no_output; }
SceGxmProgram *shark_compile_shader_extended(const char *src, uint32_t *size, shark_type type, shark_opt opt,
                                             int32_t fm, int32_t fp, int32_t fi) {
    u32 n = *size + 1; /* vitaShaRK takes *size as the source's length */
    MockProg *p;
    (void)opt; (void)fm; (void)fp; (void)fi;
    if (!*size || *size != strlen(src)) { printf("kh1-gxm-mock: a compile with size %u for %u bytes of source\n", *size, (u32)strlen(src)); return 0; }
    p = (MockProg *)calloc(1, sizeof *p + n);
    memcpy(p->magic, "KHMP", 4);
    p->frag = type == SHARK_FRAGMENT_SHADER;
    p->kh1 = strstr(src, "// kh1-decomp") == src;
    memcpy(p->text, src, n - 1);
    parse_params(p);
    *size = (uint32_t)(sizeof *p + n);
    return (SceGxmProgram *)p;
}
int sceGxmProgramCheck(const SceGxmProgram *p) { return memcmp(p, "KHMP", 4) ? -1 : 0; }
const SceGxmProgramParameter *sceGxmProgramFindParameterByName(const SceGxmProgram *prog, const char *name) {
    MockProg *p = (MockProg *)prog;
    int i;
    for (i = 0; i < p->nparam; i++)
        if (!strcmp(p->param[i].name, name)) {
            /* a uniform the code never reads is dropped by a compiler: so here too */
            if (p->param[i].kind == P_UNIFORM) {
                const char *b = strchr(p->text, '{');
                if (!b || !strstr(b, name)) return 0;
            }
            return &p->param[i];
        }
    return 0;
}
unsigned int sceGxmProgramParameterGetResourceIndex(const SceGxmProgramParameter *p) { return (unsigned)p->index; }

typedef struct { MockProg *p; int nattr; SceGxmVertexAttribute a[8]; u32 stride; } MockVP;
typedef struct { MockProg *p; int blend; SceGxmBlendInfo bi; } MockFP;

int sceGxmShaderPatcherRegisterProgram(SceGxmShaderPatcher *sp, const SceGxmProgram *h, SceGxmShaderPatcherId *id) {
    (void)sp;
    *id = (SceGxmShaderPatcherId)h;
    return 0;
}
int sceGxmShaderPatcherCreateVertexProgram(SceGxmShaderPatcher *sp, SceGxmShaderPatcherId id, const SceGxmVertexAttribute *a,
                                           unsigned int n, const SceGxmVertexStream *s, unsigned int ns, SceGxmVertexProgram **out) {
    MockVP *v = (MockVP *)calloc(1, sizeof *v);
    (void)sp; (void)ns;
    v->p = (MockProg *)id;
    v->nattr = (int)n;
    memcpy(v->a, a, n * sizeof *a);
    v->stride = s->stride;
    *out = (SceGxmVertexProgram *)v;
    return 0;
}
int sceGxmShaderPatcherCreateFragmentProgram(SceGxmShaderPatcher *sp, SceGxmShaderPatcherId id, SceGxmOutputRegisterFormat f,
                                             SceGxmMultisampleMode m, const SceGxmBlendInfo *bi, const SceGxmProgram *vp,
                                             SceGxmFragmentProgram **out) {
    MockFP *p = (MockFP *)calloc(1, sizeof *p);
    (void)sp; (void)f; (void)m; (void)vp;
    p->p = (MockProg *)id;
    if (bi) { p->blend = 1; p->bi = *bi; }
    *out = (SceGxmFragmentProgram *)p;
    return 0;
}

/* ---- surfaces, textures ---- */
int sceGxmMapMemory(void *b, SceSize s, SceGxmMemoryAttribFlags a) { (void)b; (void)s; (void)a; return 0; }
int sceGxmCreateRenderTarget(const SceGxmRenderTargetParams *p, SceGxmRenderTarget **rt) {
    (void)p;
    *rt = (SceGxmRenderTarget *)malloc(4);
    return 0;
}
int sceGxmDestroyRenderTarget(SceGxmRenderTarget *rt) {
    free(rt);
    return 0;
}
int sceGxmColorSurfaceInit(SceGxmColorSurface *s, SceGxmColorFormat f, SceGxmColorSurfaceType t, SceGxmColorSurfaceScaleMode sm,
                           SceGxmOutputRegisterSize o, unsigned int w, unsigned int h, unsigned int stride, void *data) {
    (void)f; (void)t; (void)sm; (void)o;
    memset(s, 0, sizeof *s);
    s->pbeEmitWords[0] = (unsigned)(uintptr_t)data;
    s->pbeEmitWords[1] = stride;
    s->pbeEmitWords[2] = w;
    s->pbeEmitWords[3] = h;
    return 0;
}
int sceGxmDepthStencilSurfaceInit(SceGxmDepthStencilSurface *s, SceGxmDepthStencilFormat f, SceGxmDepthStencilSurfaceType t,
                                  unsigned int stride, void *d, void *st) {
    (void)f; (void)t; (void)st;
    memset(s, 0, sizeof *s);
    s->depthData = d;
    s->backgroundControl = stride; /* the mock's: samples a row (its memory is linear here) */
    s->backgroundDepth = 1.0f;
    return 0;
}
void sceGxmDepthStencilSurfaceSetForceLoadMode(SceGxmDepthStencilSurface *s, SceGxmDepthStencilForceLoadMode m) {
    s->zlsControl = (s->zlsControl & ~2u) | (m ? 2u : 0);
}
void sceGxmDepthStencilSurfaceSetForceStoreMode(SceGxmDepthStencilSurface *s, SceGxmDepthStencilForceStoreMode m) {
    s->zlsControl = (s->zlsControl & ~4u) | (m ? 4u : 0);
}

/* SceGxmTexture as the mock packs it: word 0 the data, 1 the format code | byte stride << 4, 2 (w - 1) | (h - 1) << 12 |
 * min << 24 | mag << 25 | u addr << 26 | v addr << 28, 3 the palette */
enum { TF_RGBA8, TF_5551, TF_P8, TF_P4, TF_BAD };
static u32 tf_code(SceGxmTextureFormat f) {
    return f == SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ABGR ? TF_RGBA8 : f == SCE_GXM_TEXTURE_FORMAT_U1U5U5U5_ABGR ? TF_5551
           : f == SCE_GXM_TEXTURE_FORMAT_P8_ABGR ? TF_P8 : f == SCE_GXM_TEXTURE_FORMAT_P4_ABGR ? TF_P4 : TF_BAD;
}
static u32 *tw(SceGxmTexture *t) { return (u32 *)t; }
static int tex_init(SceGxmTexture *t, const void *d, SceGxmTextureFormat f, unsigned w, unsigned h, unsigned stride) {
    u32 c = tf_code(f);
    if (c == TF_BAD || !w || !h || w > 4096 || h > 4096) return -1;
    if (!stride) {
        u32 a = (w + 7) & ~7u;
        stride = c == TF_RGBA8 ? a * 4 : c == TF_5551 ? a * 2 : c == TF_P8 ? a : a / 2;
    }
    tw(t)[0] = (u32)(uintptr_t)d;
    tw(t)[1] = c | stride << 4;
    tw(t)[2] = (w - 1) | (h - 1) << 12;
    tw(t)[3] = 0;
    return 0;
}
int sceGxmTextureInitLinear(SceGxmTexture *t, const void *d, SceGxmTextureFormat f, unsigned w, unsigned h, unsigned mips) {
    (void)mips;
    return tex_init(t, d, f, w, h, 0);
}
int sceGxmTextureInitLinearStrided(SceGxmTexture *t, const void *d, SceGxmTextureFormat f, unsigned w, unsigned h, unsigned bs) {
    return tex_init(t, d, f, w, h, bs);
}
int sceGxmTextureSetMinFilter(SceGxmTexture *t, SceGxmTextureFilter f) { tw(t)[2] = (tw(t)[2] & ~(1u << 24)) | (f == SCE_GXM_TEXTURE_FILTER_LINEAR) << 24; return 0; }
int sceGxmTextureSetMagFilter(SceGxmTexture *t, SceGxmTextureFilter f) { tw(t)[2] = (tw(t)[2] & ~(1u << 25)) | (f == SCE_GXM_TEXTURE_FILTER_LINEAR) << 25; return 0; }
int sceGxmTextureSetUAddrMode(SceGxmTexture *t, SceGxmTextureAddrMode m) { tw(t)[2] = (tw(t)[2] & ~(3u << 26)) | (m == SCE_GXM_TEXTURE_ADDR_CLAMP) << 26; return 0; }
int sceGxmTextureSetVAddrMode(SceGxmTexture *t, SceGxmTextureAddrMode m) { tw(t)[2] = (tw(t)[2] & ~(3u << 28)) | (m == SCE_GXM_TEXTURE_ADDR_CLAMP) << 28; return 0; }
int sceGxmTextureSetPalette(SceGxmTexture *t, const void *p) {
    if ((uintptr_t)p & 63) { printf("kh1-gxm-mock: a palette not 64-byte aligned\n"); return -1; }
    tw(t)[3] = (u32)(uintptr_t)p;
    return 0;
}

/* ---- the context ---- */
static struct {
    int raster;               /* draws are rasterised (else only counted) */
    int point;                /* KH1_HOST_GXM_POINT */
    u32 *col, cstride, cw, ch; /* the scene's colour surface */
    SceGxmDepthStencilSurface *ds;
    u32 *z, zstride;          /* depth (24 bits) | stencil << 24, linear */
    u32 *zsave;               /* a scene's depth memory when it is not stored */
    MockVP *vp;
    MockFP *fp;
    SceGxmTexture tex[4];
    const u8 *stream;
    f32 vx[2], vy[2], vz[2];  /* viewport: offset, scale */
    u32 clip_mode, cx0, cy0, cx1, cy1;
    SceGxmDepthFunc zfunc;
    int zwrite;
    SceGxmStencilFunc sfunc;
    SceGxmStencilOp sfail, zfail, zpass;
    u32 smask, swmask, sref;
    f32 vub[64], fub[64];
    u32 draws, tris, pixels, lost;
    u32 n_in, n_disc, n_zfail; /* KH1_HOST_GXM_CALLS: a draw's covered, discarded and depth-failed pixels */
} g;

SceGxmContext *vita2d_get_context(void) { static int c; return (SceGxmContext *)&c; }
SceGxmShaderPatcher *vita2d_get_shader_patcher(void) { static int p; return (SceGxmShaderPatcher *)&p; }
void *vita2d_pool_memalign(unsigned int size, unsigned int align) { static u8 pool[4096] __attribute__((aligned(64))); (void)align; return size <= sizeof pool ? pool : 0; }
/* session 137v: the GPU runs a scene after its end, as late as sceGxmFinish, on the memory as it is then (a
 * texture, palette or vertex the CPU rewrote after the draw was issued is what the GPU reads): the scenes and
 * their draws are queued, each draw with the context's state at its call, and run at sceGxmFinish (and after
 * each frame, where gxm.c's next frame starts with one) */
typedef struct {
    int op;                                /* 0 begin, 1 draw, 2 end */
    SceGxmColorSurface cs;                 /* begin */
    SceGxmDepthStencilSurface ds;          /* as it is at the begin (its load / store modes) */
    SceGxmPrimitiveType t;                 /* draw */
    const void *ix;
    unsigned n;
    u8 st[sizeof g];                       /* the context at the draw */
} Queued;
static Queued *queue;
static u32 nqueue, capqueue;
static Queued *enqueue(int op) {
    if (nqueue == capqueue) {
        capqueue = capqueue ? capqueue * 2 : 256;
        queue = realloc(queue, capqueue * sizeof *queue);
    }
    queue[nqueue].op = op;
    return &queue[nqueue++];
}
static void do_begin(const SceGxmColorSurface *cs, const SceGxmDepthStencilSurface *ds);
static void do_end(void);
static void do_draw(SceGxmPrimitiveType t, const void *ix, unsigned int n);
static void flush(void) {
    u32 i;
    for (i = 0; i < nqueue; i++) {
        Queued *q = &queue[i];
        if (q->op == 0) do_begin(&q->cs, &q->ds);
        else if (q->op == 2) do_end();
        else {
            /* the draw's state, keeping the scene's surfaces and the counters */
            u32 *col = g.col, cs = g.cstride, cw = g.cw, ch = g.ch, *z = g.z, zs = g.zstride, *zsave = g.zsave;
            SceGxmDepthStencilSurface *dsf = g.ds;
            u32 draws = g.draws, tris = g.tris, pixels = g.pixels, lost = g.lost, a = g.n_in, b = g.n_disc, c = g.n_zfail;
            int raster = g.raster;
            memcpy(&g, q->st, sizeof g);
            g.col = col; g.cstride = cs; g.cw = cw; g.ch = ch; g.z = z; g.zstride = zs; g.zsave = zsave; g.ds = dsf;
            g.draws = draws; g.tris = tris; g.pixels = pixels; g.lost = lost; g.n_in = a; g.n_disc = b; g.n_zfail = c;
            g.raster = raster;
            do_draw(q->t, q->ix, q->n);
        }
    }
    nqueue = 0;
}
void sceGxmFinish(SceGxmContext *c) { (void)c; flush(); }

int sceGxmBeginScene(SceGxmContext *c, unsigned int flags, const SceGxmRenderTarget *rt, const SceGxmValidRegion *vr,
                     SceGxmSyncObject *vs, SceGxmSyncObject *fs, const SceGxmColorSurface *cs, const SceGxmDepthStencilSurface *ds) {
    Queued *q = enqueue(0);
    (void)c; (void)flags; (void)rt; (void)vr; (void)vs; (void)fs;
    q->cs = *cs;
    q->ds = *ds;
    g.clip_mode = SCE_GXM_REGION_CLIP_NONE;
    return 0;
}
static void do_begin(const SceGxmColorSurface *cs, const SceGxmDepthStencilSurface *ds) {
    g.col = (u32 *)(uintptr_t)cs->pbeEmitWords[0];
    g.cstride = cs->pbeEmitWords[1];
    g.cw = cs->pbeEmitWords[2];
    g.ch = cs->pbeEmitWords[3];
    g.ds = (SceGxmDepthStencilSurface *)ds;
    g.z = (u32 *)ds->depthData;
    g.zstride = ds->backgroundControl;
    if (!(ds->zlsControl & 4)) { /* not to be stored: the memory as it is, put back at the end */
        g.zsave = realloc(g.zsave, (size_t)g.ch * g.zstride * 4);
        memcpy(g.zsave, g.z, (size_t)g.ch * g.zstride * 4);
    }
    if (!(ds->zlsControl & 2)) { /* not loaded: the background depth 1.0, stencil 0 */
        u32 y, x;
        for (y = 0; y < g.ch; y++)
            for (x = 0; x < g.cw; x++) g.z[y * g.zstride + x] = 0xFFFFFF;
    }
}
int sceGxmEndScene(SceGxmContext *c, const SceGxmNotification *vn, const SceGxmNotification *fn) {
    (void)c; (void)vn; (void)fn;
    enqueue(2);
    return 0;
}
static void do_end(void) {
    /* not stored: the scene's depth stays on chip and the surface's memory keeps what an earlier scene stored
     * (session 137v: the mock used to scribble it, which a later scene's load of that earlier store, past a scene
     * that only tests depth, does not see on the GPU) */
    if (g.ds && !(g.ds->zlsControl & 4)) memcpy(g.z, g.zsave, (size_t)g.ch * g.zstride * 4);
    g.col = 0;
}
void sceGxmSetViewport(SceGxmContext *c, float xo, float xs, float yo, float ys, float zo, float zs) {
    (void)c;
    g.vx[0] = xo; g.vx[1] = xs; g.vy[0] = yo; g.vy[1] = ys; g.vz[0] = zo; g.vz[1] = zs;
}
void sceGxmSetCullMode(SceGxmContext *c, SceGxmCullMode m) { (void)c; if (m != SCE_GXM_CULL_NONE) g.lost++; }
void sceGxmSetTwoSidedEnable(SceGxmContext *c, SceGxmTwoSidedMode m) { (void)c; (void)m; }
void sceGxmSetFrontPointLineWidth(SceGxmContext *c, unsigned int w) { (void)c; (void)w; }
void sceGxmSetRegionClip(SceGxmContext *c, SceGxmRegionClipMode m, unsigned x0, unsigned y0, unsigned x1, unsigned y1) {
    (void)c;
    g.clip_mode = m; g.cx0 = x0; g.cy0 = y0; g.cx1 = x1; g.cy1 = y1;
}
void sceGxmSetVertexProgram(SceGxmContext *c, const SceGxmVertexProgram *p) { (void)c; g.vp = (MockVP *)p; }
void sceGxmSetFragmentProgram(SceGxmContext *c, const SceGxmFragmentProgram *p) { (void)c; g.fp = (MockFP *)p; }
void sceGxmSetFrontDepthFunc(SceGxmContext *c, SceGxmDepthFunc f) { (void)c; g.zfunc = f; }
void sceGxmSetFrontDepthWriteEnable(SceGxmContext *c, SceGxmDepthWriteMode m) { (void)c; g.zwrite = m == SCE_GXM_DEPTH_WRITE_ENABLED; }
void sceGxmSetFrontStencilFunc(SceGxmContext *c, SceGxmStencilFunc f, SceGxmStencilOp sf, SceGxmStencilOp zf, SceGxmStencilOp zp,
                               unsigned char cm, unsigned char wm) {
    (void)c;
    g.sfunc = f; g.sfail = sf; g.zfail = zf; g.zpass = zp; g.smask = cm; g.swmask = wm;
}
void sceGxmSetFrontStencilRef(SceGxmContext *c, unsigned int r) { (void)c; g.sref = r; }
int sceGxmReserveVertexDefaultUniformBuffer(SceGxmContext *c, void **b) { (void)c; memset(g.vub, 0, sizeof g.vub); *b = g.vub; return 0; }
int sceGxmReserveFragmentDefaultUniformBuffer(SceGxmContext *c, void **b) { (void)c; memset(g.fub, 0, sizeof g.fub); *b = g.fub; return 0; }
int sceGxmSetUniformDataF(void *b, const SceGxmProgramParameter *p, unsigned int off, unsigned int n, const float *d) {
    if (p->kind != P_UNIFORM || p->index * 4 + off + n > 64) return -1;
    memcpy((f32 *)b + p->index * 4 + off, d, n * sizeof *d);
    return 0;
}
int sceGxmSetVertexStream(SceGxmContext *c, unsigned int i, const void *d) { (void)c; if (!i) g.stream = (const u8 *)d; return 0; }
int sceGxmSetFragmentTexture(SceGxmContext *c, unsigned int i, const SceGxmTexture *t) { (void)c; if (i < 4) g.tex[i] = *t; return 0; }

/* ---- sampling ---- */
static u32 texel(const SceGxmTexture *t, s32 x, s32 y) {
    const u32 *w = (const u32 *)t;
    s32 tw_ = (s32)(w[2] & 0xFFF) + 1, th = (s32)(w[2] >> 12 & 0xFFF) + 1;
    u32 code = w[1] & 15, stride = w[1] >> 4;
    const u8 *row;
    if (w[2] >> 26 & 3) x = x < 0 ? 0 : x >= tw_ ? tw_ - 1 : x;
    else x = ((x % tw_) + tw_) % tw_;
    if (w[2] >> 28 & 3) y = y < 0 ? 0 : y >= th ? th - 1 : y;
    else y = ((y % th) + th) % th;
    row = (const u8 *)(uintptr_t)w[0] + (u32)y * stride;
    switch (code) {
    case TF_RGBA8: { u32 v; memcpy(&v, row + x * 4, 4); return v; }
    case TF_5551: {
        u32 h = row[x * 2] | row[x * 2 + 1] << 8, r = h & 31, gg = h >> 5 & 31, b = h >> 10 & 31;
        /* the GPU widens 5 bits by repeating the top ones (31 is 0xFF) */
        return (r << 3 | r >> 2) | (gg << 3 | gg >> 2) << 8 | (b << 3 | b >> 2) << 16 | (h >> 15 ? 0xFFu : 0) << 24;
    }
    case TF_P8: return ((const u32 *)(uintptr_t)w[3])[row[x]];
    case TF_P4: return ((const u32 *)(uintptr_t)w[3])[row[x >> 1] >> (x & 1) * 4 & 15];
    }
    return 0;
}

static void sample(void *ctx, f32 s, f32 t, f32 out[4]) {
    const SceGxmTexture *tx = (const SceGxmTexture *)ctx;
    const u32 *w = (const u32 *)tx;
    f32 tw_ = (f32)((w[2] & 0xFFF) + 1), th = (f32)((w[2] >> 12 & 0xFFF) + 1), u = s * tw_ - 0.5f, v = t * th - 0.5f;
    u32 i;
    if (!w[0]) { memset(out, 0, 16); return; }
    if (g.point || !(w[2] >> 24 & 1)) {
        u32 c = texel(tx, (s32)(s * tw_ + 4096.0f) - 4096, (s32)(t * th + 4096.0f) - 4096);
        for (i = 0; i < 4; i++) out[i] = (f32)(c >> i * 8 & 0xFF) / 255.0f;
    } else {
        s32 x0 = (s32)(u + 4096.0f) - 4096, y0 = (s32)(v + 4096.0f) - 4096;
        f32 fx = u - (f32)x0, fy = v - (f32)y0;
        u32 a = texel(tx, x0, y0), b = texel(tx, x0 + 1, y0), c = texel(tx, x0, y0 + 1), d = texel(tx, x0 + 1, y0 + 1);
        for (i = 0; i < 4; i++) {
            f32 top = (f32)(a >> i * 8 & 0xFF) * (1 - fx) + (f32)(b >> i * 8 & 0xFF) * fx;
            f32 bot = (f32)(c >> i * 8 & 0xFF) * (1 - fx) + (f32)(d >> i * 8 & 0xFF) * fx;
            out[i] = (top * (1 - fy) + bot * fy) / 255.0f;
        }
    }
}

/* ---- the rasteriser ---- */
typedef struct { f32 x, y, z; f32 col[4], tc[4], fog; } Vary;

static int sv_of(const char *name) {
    return !strcmp(name, "pos") ? KH1_SV_POS : !strcmp(name, "col") ? KH1_SV_COL : !strcmp(name, "tc") ? KH1_SV_TC
           : !strcmp(name, "fog") ? KH1_SV_FOG : -1;
}

static const struct SceGxmProgramParameter *param(const MockProg *p, int kind, int index) {
    int i;
    for (i = 0; i < p->nparam; i++)
        if (p->param[i].kind == kind && p->param[i].index == index) return &p->param[i];
    return 0;
}

static void uniforms(const MockProg *p, const f32 *buf, KH1ShaderRun *r) {
    static const char *names[] = { "u_a", "u_b", "u_r", "u_c", "u_xf" };
    static const int sv[] = { KH1_SV_UA, KH1_SV_UB, KH1_SV_UR, KH1_SV_UC, KH1_SV_UXF };
    int i, j;
    for (i = 0; i < 5; i++)
        for (j = 0; j < p->nparam; j++)
            if (p->param[j].kind == P_UNIFORM && !strcmp(p->param[j].name, names[i])) memcpy(r->v[sv[i]], buf + p->param[j].index * 4, 16);
}

static void vertex(u32 idx, Vary *o) {
    KH1ShaderRun r;
    int i;
    memset(&r, 0, sizeof r);
    for (i = 0; i < g.vp->nattr; i++) {
        const SceGxmVertexAttribute *a = &g.vp->a[i];
        const struct SceGxmProgramParameter *p = param(g.vp->p, P_IN, a->regIndex);
        const u8 *src = g.stream + idx * g.vp->stride + a->offset;
        int sv = p ? sv_of(p->name) : -1, c;
        if (sv < 0) { g.lost++; continue; }
        r.v[sv][3] = 1.0f;
        for (c = 0; c < a->componentCount && c < 4; c++) {
            if (a->format == SCE_GXM_ATTRIBUTE_FORMAT_F32) memcpy(&r.v[sv][c], src + c * 4, 4);
            else r.v[sv][c] = (f32)src[c] / 255.0f;
        }
    }
    uniforms(g.vp->p, g.vub, &r);
    kh1_shader_run(g.vp->p->text, &r);
    if (r.bad) g.lost++;
    /* window coordinates snapped to a sub-pixel grid (1/256 here), as a rasteriser's fixed point does */
    o->x = (f32)(s32)((r.v[KH1_SV_OPOS][0] * g.vx[1] + g.vx[0]) * 256.0f + 0.5f + 65536.0f * 256.0f) / 256.0f - 65536.0f;
    o->y = (f32)(s32)((r.v[KH1_SV_OPOS][1] * g.vy[1] + g.vy[0]) * 256.0f + 0.5f + 65536.0f * 256.0f) / 256.0f - 65536.0f;
    o->z = r.v[KH1_SV_OPOS][2] * g.vz[1] + g.vz[0];
    memcpy(o->col, r.v[KH1_SV_OCOL], 16);
    memcpy(o->tc, r.v[KH1_SV_OTC], 16);
    o->fog = r.v[KH1_SV_OFOG][0];
}

static int stest(u32 f, u32 ref, u32 v) {
    switch (f) {
    case SCE_GXM_STENCIL_FUNC_NEVER: return 0;
    case SCE_GXM_STENCIL_FUNC_EQUAL: return ref == v;
    case SCE_GXM_STENCIL_FUNC_NOT_EQUAL: return ref != v;
    case SCE_GXM_STENCIL_FUNC_ALWAYS: return 1;
    }
    g.lost++;
    return 1;
}
static u32 sop(u32 op, u32 v) { return op == SCE_GXM_STENCIL_OP_REPLACE ? g.sref : op == SCE_GXM_STENCIL_OP_KEEP ? v : (g.lost++, v); }
static int ztest(u32 f, u32 z, u32 d) {
    switch (f) {
    case SCE_GXM_DEPTH_FUNC_NEVER: return 0;
    case SCE_GXM_DEPTH_FUNC_ALWAYS: return 1;
    case SCE_GXM_DEPTH_FUNC_GREATER: return z > d;
    case SCE_GXM_DEPTH_FUNC_GREATER_EQUAL: return z >= d;
    case SCE_GXM_DEPTH_FUNC_LESS: return z < d;
    case SCE_GXM_DEPTH_FUNC_LESS_EQUAL: return z <= d;
    case SCE_GXM_DEPTH_FUNC_EQUAL: return z == d;
    }
    return 1;
}
static f32 factor(u32 f, f32 sa, f32 da) {
    switch (f) {
    case SCE_GXM_BLEND_FACTOR_ZERO: return 0;
    case SCE_GXM_BLEND_FACTOR_ONE: return 1;
    case SCE_GXM_BLEND_FACTOR_SRC_ALPHA: return sa;
    case SCE_GXM_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA: return 1 - sa;
    case SCE_GXM_BLEND_FACTOR_DST_ALPHA: return da;
    case SCE_GXM_BLEND_FACTOR_ONE_MINUS_DST_ALPHA: return 1 - da;
    }
    g.lost++;
    return 1;
}

static void pixel(s32 x, s32 y, const Vary *v) {
    KH1ShaderRun r;
    const MockProg *fp = g.fp->p;
    const struct SceGxmProgramParameter *sp = param(fp, P_SAMPLER, 0);
    u32 *z = &g.z[y * g.zstride + x], *c = &g.col[y * g.cstride + x], st = *z >> 24, zv, out = 0, i;
    f32 o[4];
    memset(&r, 0, sizeof r);
    memcpy(r.v[KH1_SV_COL], v->col, 16);
    memcpy(r.v[KH1_SV_TC], v->tc, 16);
    r.v[KH1_SV_FOG][0] = v->fog;
    r.v[KH1_SV_POS][0] = (f32)x + 0.5f;
    r.v[KH1_SV_POS][1] = (f32)y + 0.5f;
    r.v[KH1_SV_POS][3] = 1.0f;
    for (i = 0; i < 4; i++) r.v[KH1_SV_DST][i] = (f32)(*c >> i * 8 & 0xFF);
    uniforms(fp, g.fub, &r);
    r.tex = sample;
    r.ctx = sp ? &g.tex[sp->index] : 0;
    kh1_shader_run(fp->text, &r);
    if (r.bad) g.lost++;
    g.n_in++;
    if (r.discarded) { g.n_disc++; return; }
    if (!stest(g.sfunc, g.sref & g.smask, st & g.smask)) {
        *z = (*z & 0xFFFFFF) | (((st & ~g.swmask) | (sop(g.sfail, st) & g.swmask)) & 0xFF) << 24;
        return;
    }
    {
        f32 zf = v->z < 0 ? 0 : v->z > 1 ? 1 : v->z;
        zv = (u32)(zf * 16777215.0f + 0.5f);
    }
    if (!ztest(g.zfunc, zv, *z & 0xFFFFFF)) {
        g.n_zfail++;
        *z = (*z & 0xFFFFFF) | (((st & ~g.swmask) | (sop(g.zfail, st) & g.swmask)) & 0xFF) << 24;
        return;
    }
    *z = (g.zwrite ? zv : *z & 0xFFFFFF) | (((st & ~g.swmask) | (sop(g.zpass, st) & g.swmask)) & 0xFF) << 24;
    for (i = 0; i < 4; i++) {
        f32 q = r.v[KH1_SV_OCOLOR][i];
        o[i] = (f32)(u32)((q < 0 ? 0 : q > 1 ? 1 : q) * 255.0f + 0.5f); /* UCHAR4 */
    }
    if (g.fp->blend && g.fp->bi.colorFunc != SCE_GXM_BLEND_FUNC_NONE) {
        f32 sa = o[3] / 255.0f, da = (f32)(*c >> 24) / 255.0f;
        for (i = 0; i < 3; i++) {
            f32 s = o[i] * factor(g.fp->bi.colorSrc, sa, da), d = (f32)(*c >> i * 8 & 0xFF) * factor(g.fp->bi.colorDst, sa, da), b;
            b = g.fp->bi.colorFunc == SCE_GXM_BLEND_FUNC_ADD ? s + d : g.fp->bi.colorFunc == SCE_GXM_BLEND_FUNC_SUBTRACT ? s - d : d - s;
            o[i] = (f32)(u32)((b < 0 ? 0 : b > 255 ? 255 : b) + 0.5f);
        }
        if (g.fp->bi.alphaFunc != SCE_GXM_BLEND_FUNC_ADD || g.fp->bi.alphaSrc != SCE_GXM_BLEND_FACTOR_ONE ||
            g.fp->bi.alphaDst != SCE_GXM_BLEND_FACTOR_ZERO)
            g.lost++;
    }
    {
        u32 mask = g.fp->blend ? g.fp->bi.colorMask : SCE_GXM_COLOR_MASK_ALL;
        static const u32 bit[4] = { SCE_GXM_COLOR_MASK_R, SCE_GXM_COLOR_MASK_G, SCE_GXM_COLOR_MASK_B, SCE_GXM_COLOR_MASK_A };
        for (i = 0; i < 4; i++) out |= (mask & bit[i] ? (u32)o[i] : *c >> i * 8 & 0xFF) << i * 8;
    }
    if (getenv("KH1_HOST_GXM_VERTS") && x == 5 && y == 0) printf("kh1-gxm-mock:   pixel (5, 0) = %08x\n", out);
    *c = out;
    g.pixels++;
}

static f32 edge(const Vary *a, const Vary *b, f32 x, f32 y) { return (b->x - a->x) * (y - a->y) - (b->y - a->y) * (x - a->x); }

static void triangle(const Vary *a, const Vary *b, const Vary *c) {
    f32 area = edge(a, b, c->x, c->y);
    s32 x0, y0, x1, y1, x, y;
    const Vary *p[3] = { a, b, c };
    if (area == 0) return;
    if (area < 0) { p[1] = c; p[2] = b; area = -area; }
    x0 = (s32)(a->x < b->x ? (a->x < c->x ? a->x : c->x) : (b->x < c->x ? b->x : c->x)) - 1;
    x1 = (s32)(a->x > b->x ? (a->x > c->x ? a->x : c->x) : (b->x > c->x ? b->x : c->x)) + 1;
    y0 = (s32)(a->y < b->y ? (a->y < c->y ? a->y : c->y) : (b->y < c->y ? b->y : c->y)) - 1;
    y1 = (s32)(a->y > b->y ? (a->y > c->y ? a->y : c->y) : (b->y > c->y ? b->y : c->y)) + 1;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > (s32)g.cw - 1) x1 = (s32)g.cw - 1;
    if (y1 > (s32)g.ch - 1) y1 = (s32)g.ch - 1;
    if (g.clip_mode == SCE_GXM_REGION_CLIP_OUTSIDE) {
        if (x0 < (s32)g.cx0) x0 = (s32)g.cx0;
        if (y0 < (s32)g.cy0) y0 = (s32)g.cy0;
        if (x1 > (s32)g.cx1) x1 = (s32)g.cx1;
        if (y1 > (s32)g.cy1) y1 = (s32)g.cy1;
    }
    g.tris++;
    for (y = y0; y <= y1; y++)
        for (x = x0; x <= x1; x++) {
            f32 px = (f32)x + 0.5f, py = (f32)y + 0.5f, w[3];
            Vary v;
            int i, k, in = 1;
            for (i = 0; i < 3; i++) {
                const Vary *e0 = p[(i + 1) % 3], *e1 = p[(i + 2) % 3], *o = p[i];
                f32 e = edge(e0, e1, px, py);
                /* top-left: an edge exactly through the centre counts when it is a top edge (the triangle below it,
                 * y down) or a left edge (the triangle to its right) */
                if (e == 0) {
                    int top = e0->y == e1->y && o->y > e0->y;
                    int left = e0->y != e1->y && o->x > e0->x + (o->y - e0->y) * (e1->x - e0->x) / (e1->y - e0->y);
                    if (!top && !left) { in = 0; break; }
                } else if (e < 0) { in = 0; break; }
                w[i] = e / area;
            }
            if (getenv("KH1_HOST_GXM_VERTS") && g.raster && x == 5 && y == 0) printf("kh1-gxm-mock:   pixel (5, 0) in %d\n", in);
            if (!in) continue;
            v.x = px; v.y = py;
            v.z = w[0] * p[0]->z + w[1] * p[1]->z + w[2] * p[2]->z;
            for (k = 0; k < 4; k++) {
                v.col[k] = w[0] * p[0]->col[k] + w[1] * p[1]->col[k] + w[2] * p[2]->col[k];
                v.tc[k] = w[0] * p[0]->tc[k] + w[1] * p[1]->tc[k] + w[2] * p[2]->tc[k];
            }
            v.fog = w[0] * p[0]->fog + w[1] * p[1]->fog + w[2] * p[2]->fog;
            pixel(x, y, &v);
        }
}

int sceGxmDraw(SceGxmContext *c, SceGxmPrimitiveType t, SceGxmIndexFormat f, const void *ix, unsigned int n) {
    Queued *q = enqueue(1);
    (void)c; (void)f;
    q->t = t;
    q->ix = ix;
    q->n = n;
    memcpy(q->st, &g, sizeof g);
    return 0;
}
static void do_draw(SceGxmPrimitiveType t, const void *ix, unsigned int n) {
    const u16 *idx = (const u16 *)ix;
    unsigned i;
    g.draws++;
    if (!g.raster || !g.col || !g.vp || !g.fp) return;
    if (!g.vp->p->kh1 || !g.fp->p->kh1) return; /* the present's own pair: not interpreted */
    if (t != SCE_GXM_PRIMITIVE_TRIANGLES) { g.lost++; return; }
    for (i = 0; i + 2 < n; i += 3) {
        Vary v[3];
        vertex(idx[i], &v[0]);
        vertex(idx[i + 1], &v[1]);
        vertex(idx[i + 2], &v[2]);
        if (getenv("KH1_HOST_GXM_VERTS") && g.raster && i < 6)
            printf("kh1-gxm-mock:   tri (%.2f, %.2f, %.4f) (%.2f, %.2f) (%.2f, %.2f) col %.3f %.3f %.3f %.3f clip %u %u..%u %u\n", v[0].x, v[0].y,
                   v[0].z, v[1].x, v[1].y, v[2].x, v[2].y, v[0].col[0], v[0].col[1], v[0].col[2], v[0].col[3], g.cx0, g.cy0, g.cx1, g.cy1);
        triangle(&v[0], &v[1], &v[2]);
    }
    if (g.raster && getenv("KH1_HOST_GXM_CALLS")) {
        printf("kh1-gxm-mock:     %u pixels covered, %u discarded, %u failed depth\n", g.n_in, g.n_disc, g.n_zfail);
        g.n_in = g.n_disc = g.n_zfail = 0;
    }
}

/* ---- the check ---- */
static int every;
static const char *ppm;
static u32 frame, checks, bad_frames;

static void write_ppm(const char *name, const u32 *pix, u32 w, u32 h, u32 stride) {
    char path[512];
    FILE *f;
    u32 x, y;
    snprintf(path, sizeof path, "%s/%s_%05u.ppm", ppm, name, frame);
    f = fopen(path, "wb");
    if (!f) return;
    fprintf(f, "P6\n%u %u\n255\n", w, h);
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) {
            u32 v = pix[y * stride + x];
            fputc(v & 0xFF, f); fputc(v >> 8 & 0xFF, f); fputc(v >> 16 & 0xFF, f);
        }
    fclose(f);
}

/* the GPU's target of kind rt against the GS model's buffer at bp (FBW 8, RGB): nonzero when they differ */
static int compare(const char *what, u32 rt, u32 bp, u32 rows) {
    static u32 gs[512 * 512];
    u32 w, h, stride, x, y, diff = 0, most = 0, i, x0 = 512, y0 = 512, x1 = 0, y1 = 0;
    const u32 *gpu = (const u32 *)kh1_vita_gxm_target(rt, &w, &h, &stride);
    if (!gpu) {
        printf("kh1-gxm-mock: frame %u: no %s target drawn (%u draws)\n", frame, what, g.draws);
        return 1;
    }
    if (w > 512) w = 512;
    if (h > rows) h = rows;
    kh1_gsmem_read_rect(KH1_PSMCT32, bp, 8, 0, 0, w, h, gs, w);
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) {
            u32 a = gpu[y * stride + x], b = gs[y * w + x], d = 0;
            for (i = 0; i < 3; i++) {
                s32 e = (s32)(a >> i * 8 & 0xFF) - (s32)(b >> i * 8 & 0xFF);
                if (e < 0) e = -e;
                if ((u32)e > d) d = (u32)e;
            }
            if (d > most) most = d;
            if (d > 2) {
                diff++;
                if (x < x0) x0 = x;
                if (y < y0) y0 = y;
                if (x > x1) x1 = x;
                if (y > y1) y1 = y;
            }
        }
    printf("kh1-gxm-mock: frame %u: %s %u x %u, %u draws, %u triangles, %u pixels drawn; %u pixels differ from the GS model by "
           "more than 2 (at most %u", frame, what, w, h, g.draws, g.tris, g.pixels, diff, most);
    if (diff) printf(", in (%u, %u) .. (%u, %u)", x0, y0, x1, y1);
    printf("); %u lost\n", g.lost);
    if (ppm) {
        char name[32];
        snprintf(name, sizeof name, "gpu_%s", what);
        write_ppm(name, gpu, w, h, stride);
        snprintf(name, sizeof name, "gs_%s", what);
        write_ppm(name, gs, w, h, w);
    }
    return diff != 0;
}

static u32 from; /* KH1_HOST_GXM_FROM=F: rasterise and compare every frame from F */
/* session 142: KH1_HOST_GXM_HASH=1, a hash of the GPU's display and 3D targets at each Nth frame in place of the
 * comparison (which reads the GS model: with the frame on its own thread the model is a frame ahead) */
static int hash_only;
static void hook(const KH1CmdRec *r) {
    u32 n = frame % (u32)every;
    if (from && frame >= from) n = (u32)every - 1; /* KH1_HOST_GXM_FROM: every frame from there */
    g.raster = n >= (u32)every - 2;
    g.draws = g.tris = g.pixels = 0;
    kh1_vita_gxm_frame(r);
    flush(); /* the GPU done (gxm.c's next frame waits for it) */
    if (n == (u32)every - 1 && getenv("KH1_HOST_GXM_CALLS")) { /* the frame's calls and pipelines */
        static KH1GxmRec gr;
        u32 i;
        kh1_gxm_frame(&gr, r);
        for (i = 0; i < gr.n; i++) printf("kh1-gxm-mock:   %s\n", kh1_gxm_call_str(&gr.call[i]));
        for (i = 0; i < gr.npipe; i++) printf("kh1-gxm-mock:   pipe %u: %s\n", i, kh1_pipekey_str(&gr.pipe[i]));
        for (i = 0; i < r->ntgt; i++)
            printf("kh1-gxm-mock:   target %u: rt %u bp %04x bw %u\n", i, r->tgt[i] & 0xFF, (r->tgt[i] >> 8 & 0xFFF) * 32, r->tgt[i] >> 20);
    }
    if (n == (u32)every - 1 && hash_only) { /* session 142: the GPU's pictures alone (the model may run ahead) */
        static const u32 rts[2] = { KH1_RT_DISPLAY, KH1_RT_MAIN };
        u32 k, w, h, stride, y, x, hh;
        for (k = 0; k < 2; k++) {
            const u32 *gpu = (const u32 *)kh1_vita_gxm_target(rts[k], &w, &h, &stride);
            hh = 2166136261u;
            for (y = 0; gpu && y < h; y++)
                for (x = 0; x < w; x++) hh = (hh ^ gpu[y * stride + x]) * 16777619u;
            printf("kh1-gxm-mock: frame %u: %s target %08x (%u x %u), %u draws, %u triangles, %u pixels drawn\n", frame,
                   k ? "3d" : "display", gpu ? hh : 0, gpu ? w : 0, gpu ? h : 0, g.draws, g.tris, g.pixels);
        }
    } else if (n == (u32)every - 1) {
        checks++;
        if (compare("display", KH1_RT_DISPLAY, 0, 448) + compare("3d", KH1_RT_MAIN, 0x1A00, 384)) bad_frames++;
    }
    frame++;
}

static void report(void) { printf("kh1-gxm-mock: %u checks, %u with differences\n", checks, bad_frames); }

__attribute__((constructor)) static void start(void) {
    const char *e = getenv("KH1_HOST_GXM");
    if (!e || (every = atoi(e)) < 2) return;
    g.point = getenv("KH1_HOST_GXM_POINT") != 0;
    hash_only = getenv("KH1_HOST_GXM_HASH") != 0;
    from = getenv("KH1_HOST_GXM_FROM") ? (u32)atoi(getenv("KH1_HOST_GXM_FROM")) : 0;
    ppm = getenv("KH1_HOST_GXM_PPM");
    if (kh1_vita_gxm_init()) {
        printf("kh1-gxm-mock: gxm.c did not start\n");
        exit(1);
    }
    kh1_pipes_frame_hook = hook;
    atexit(report);
}
