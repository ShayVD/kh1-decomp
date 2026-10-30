/* The Vita's GPU renderer (docs/vita-build.md "GPU"): each frame's GS draws, as the port's command recorder
 * gives them (include/platform/cmdbuf.h, fed by host/null/pipes.c from the GIF's kicks) and as
 * include/platform/gxmrec.h turns them into GXM calls, run on the SGX543 with sceGxm.  This replaces the
 * software GS model's pixels (host/null/gsmem.c's flat sprites, the present's read back) when it can start:
 *
 *   - the shaders are shadergen.h's Cg (vertex.h's 7 vertex variants, one fragment shader per KH1ShaderKey),
 *     compiled on the device by the system's SceShaccCg through vitaShaRK (ur0:data/libshacccg.suprx, which the
 *     user dumps from their own Vita; vitasdk has no offline compiler) and kept in ux0:data/kh1/shaders/
 *     (<FNV-1a 64 of the text>.gxp), so a later run, or a device without the module, reads them back.  When the
 *     vertex shaders and the present's pair cannot be had, kh1_vita_gxm_init fails and the software picture
 *     stays (host/vita/display.c);
 *   - each render target the recorder tracks (cmdbuf.h's tgt index) is an RGBA8 linear colour surface in CDRAM,
 *     its alpha on the GS's 0x80 scale (blend.h), sampled in place as a texture; the depth buffers (main,
 *     shadow, and one for passes with none, for DATE's stencil) are S8D24;
 *   - the texture cache's entries (texcache.h) are converted by texfmt.h into their own GPU textures, the
 *     palette cache's slots (palcache.h) into 256-entry palettes; the frame's vertex ring is copied into a
 *     GPU buffer and drawn with a static 0, 1, 2 ... index buffer (vertex.h);
 *   - transfers that touch a target (an upload into it, a copy, the CLUT pass's palette) wait for the GPU
 *     (sceGxmFinish) and use the CPU on the target's memory.  So does the start of each frame, before the
 *     rings and caches are written again: one frame in flight, simple before fast.
 *
 * The display target (KH1_RT_DISPLAY) is shown by display.c through kh1_vita_gxm_present: one opaque quad of
 * it, bilinear, inside vita2d's scene, so vita2d's status strip draws over it as before.
 *
 * Not checked on hardware when written (session 136): the colour surfaces' load (GXM is taken to load them, so
 * DONT_CARE passes cost a load), the region clip's granularity (the GS scissor), a target sampled as CT32
 * (its 0x80-scale alpha reads back doubled: the shader key has no "from a target" bit), fetch shaders
 * (`__nativecolor`), points.  Not part of the PS2 build. */
#include <psp2/gxm.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/kernel/processmgr.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vita2d.h>
#include <vitashark.h>
#include "common.h"
#include "gsmem.h"
#include "platform/blend.h"
#include "platform/cmdbuf.h"
#include "platform/depth.h"
#include "platform/gxmrec.h"
#include "platform/palcache.h"
#include "platform/primasm.h"
#include "platform/shadergen.h"
#include "platform/target.h"
#include "platform/texcache.h"
#include "platform/texfmt.h"
#include "platform/vertex.h"
#include "vita.h"

/* vertex.h's SDK values, recalled without the SDK (session 130): checked here against psp2/gxm.h */
_Static_assert(KH1_GXM_ATTR_U8N == SCE_GXM_ATTRIBUTE_FORMAT_U8N, "U8N");
_Static_assert(KH1_GXM_ATTR_F32 == SCE_GXM_ATTRIBUTE_FORMAT_F32, "F32");
_Static_assert(KH1_GXM_INDEX_16BIT == SCE_GXM_INDEX_SOURCE_INDEX_16BIT, "INDEX_16BIT");
_Static_assert(sizeof(KH1GxmVtxAttr) == sizeof(SceGxmVertexAttribute), "SceGxmVertexAttribute");
_Static_assert(sizeof(KH1GxmVtxStream) == sizeof(SceGxmVertexStream), "SceGxmVertexStream");

/* host/null/pipes.c: the texels / palette a frame's upload reads (session 142: from the frame's copy when the
 * frame runs on its own thread, kh1_pipes_snap) */
const u32 *kh1_pipes_frame_texels(s32 slot);
const u32 *kh1_pipes_frame_pal(s32 slot);
extern int kh1_pipes_snap;
/* session 142: GS memory as the frame left it: the live model's, or with kh1_pipes_snap its copy (gsmem.h) */
static void gs_read_block(u32 b, u32 *out) {
    if (kh1_pipes_snap) kh1_gsmem_snap_read_block(b, out);
    else kh1_gsmem_read_block(b, out);
}
static int gs_read_rect(u32 psm, u32 bp, u32 bw, u32 x0, u32 y0, u32 w, u32 h, u32 *out, u32 stride) {
    return kh1_pipes_snap ? kh1_gsmem_snap_read_rect(psm, bp, bw, x0, y0, w, h, out, stride)
                          : kh1_gsmem_read_rect(psm, bp, bw, x0, y0, w, h, out, stride);
}
/* a loose texture's key check.  Session 146: from the copy, the take that last changed its pages' bytes, not
 * their stamp: the title's full-screen CT24 layer lies in the depth buffer's pages, which the frame's Z target
 * marks drawn (a new stamp) every frame though the copy's bytes stay, so it was read back and converted each
 * frame (the Vita's GPU thread ~1.7 s of every 2 s in the draws, the title at ~13 fps) */
static u32 gs_tex_stamp(u32 lo, u32 hi) {
    return kh1_pipes_snap ? kh1_gsmem_snap_tex_ver(lo, hi) : kh1_gsmem_tex_stamp(lo, hi);
}
void kh1_vita_log(const char *fmt, ...);     /* main.c */

#define SHADER_DIR "ux0:data/kh1/shaders"
#define MAX_INDEX 63999u                     /* SCE_GXM_INDEX_SOURCE_INDEX_16BIT: below 64000 */

/* ---- GPU memory: blocks mapped for the GPU, and a first-fit heap over one of them ---- */
static void *gpu_block(SceKernelMemBlockType type, u32 size, u32 align) {
    SceUID uid;
    void *base = 0;
    size = (size + align - 1) & ~(align - 1);
    uid = sceKernelAllocMemBlock("kh1_gxm", type, size, 0);
    if (uid < 0) return 0;
    if (sceKernelGetMemBlockBase(uid, &base) < 0 || sceGxmMapMemory(base, size, SCE_GXM_MEMORY_ATTRIB_RW) < 0) {
        sceKernelFreeMemBlock(uid);
        return 0;
    }
    return base;
}

#define HEAP_SPANS 1024
typedef struct {
    u8 *base;
    u32 size;
    u32 nfree;
    struct { u32 off, len; } free[HEAP_SPANS]; /* sorted by offset, coalesced */
} Heap;

static int heap_init(Heap *h, SceKernelMemBlockType type, u32 size) {
    h->base = (u8 *)gpu_block(type, size, type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW ? 256 * 1024 : 4096);
    if (!h->base) return -1;
    h->size = size;
    h->nfree = 1;
    h->free[0].off = 0;
    h->free[0].len = size;
    return 0;
}

static void *heap_alloc(Heap *h, u32 len) {
    u32 i;
    len = (len + 255) & ~255u; /* textures, surfaces and palettes all take 256-byte alignment */
    for (i = 0; i < h->nfree; i++)
        if (h->free[i].len >= len) {
            u32 off = h->free[i].off;
            h->free[i].off += len;
            h->free[i].len -= len;
            if (!h->free[i].len) {
                memmove(&h->free[i], &h->free[i + 1], (h->nfree - i - 1) * sizeof h->free[0]);
                h->nfree--;
            }
            return h->base + off;
        }
    return 0;
}

static u32 heap_largest(const Heap *h) {
    u32 i, n = 0;
    for (i = 0; i < h->nfree; i++)
        if (h->free[i].len > n) n = h->free[i].len;
    return n;
}

static u32 heap_free_bytes(const Heap *h) {
    u32 i, n = 0;
    for (i = 0; i < h->nfree; i++) n += h->free[i].len;
    return n;
}

static void heap_free(Heap *h, void *p, u32 len) {
    u32 off, i;
    if (!p) return;
    len = (len + 255) & ~255u;
    off = (u32)((u8 *)p - h->base);
    for (i = 0; i < h->nfree && h->free[i].off < off; i++) ;
    if (i > 0 && h->free[i - 1].off + h->free[i - 1].len == off) { /* joins the span before */
        h->free[i - 1].len += len;
        if (i < h->nfree && off + len == h->free[i].off) {
            h->free[i - 1].len += h->free[i].len;
            memmove(&h->free[i], &h->free[i + 1], (h->nfree - i - 1) * sizeof h->free[0]);
            h->nfree--;
        }
        return;
    }
    if (i < h->nfree && off + len == h->free[i].off) { /* joins the span after */
        h->free[i].off = off;
        h->free[i].len += len;
        return;
    }
    if (h->nfree == HEAP_SPANS) return; /* lost: too fragmented to track */
    memmove(&h->free[i + 1], &h->free[i], (h->nfree - i) * sizeof h->free[0]);
    h->free[i].off = off;
    h->free[i].len = len;
    h->nfree++;
}

static Heap vram;  /* CDRAM: targets, depth buffers */
static Heap tram;  /* LPDDR uncached: textures, palettes, vertices, indices */

/* ---- shaders: shadergen's Cg, compiled by SceShaccCg or read back from the cache ---- */
static int shark_ok;
extern int kh1_vita_shacc_restart;
static char tex_why[160], pipe_why[200]; /* the last texture binding's / pipeline's failure (the skip log's) */
static u32 compiled, cached, failed; /* shaders compiled on the device, read from the cache, refused */

static u64 fnv64(const char *s, u32 n) {
    u64 h = 14695981039346656037ull;
    u32 i;
    for (i = 0; i < n; i++) h = (h ^ (u8)s[i]) * 1099511628211ull;
    return h;
}

/* the program for the text: from the cache, else compiled and kept there; malloc'd, 0 when neither */
static SceGxmProgram *program_of(const char *text, u32 len, int frag) {
    char path[96];
    SceUID fd;
    SceGxmProgram *p = 0;
    u32 size = 0;
    u64 h = fnv64(text, len) ^ (frag ? 0x9E3779B97F4A7C15ull : 0);
    snprintf(path, sizeof path, "%s/%08x%08x.gxp", SHADER_DIR, (u32)(h >> 32), (u32)h);
    fd = sceIoOpen(path, SCE_O_RDONLY, 0);
    if (fd >= 0) {
        SceOff n = sceIoLseek(fd, 0, SCE_SEEK_END);
        sceIoLseek(fd, 0, SCE_SEEK_SET);
        if (n > 0 && n < (1 << 20) && (p = (SceGxmProgram *)malloc((size_t)n)) != 0 &&
            (sceIoRead(fd, p, (SceSize)n) != n || sceGxmProgramCheck(p) < 0)) {
            free(p);
            p = 0;
        }
        sceIoClose(fd);
        if (p) { cached++; return p; }
    }
    if (!shark_ok) { failed++; return 0; }
    {
        SceGxmProgram *c;
        static const int opts[4] = { SHARK_OPT_DEFAULT, SHARK_OPT_DEFAULT, SHARK_OPT_SAFE, SHARK_OPT_SLOW };
        int o;
        /* session 137v: after some hundred compiles SceShaccCg answered shaders it compiles at start (shadertest=1)
         * with "fatal internal error" (a heap the English disc's stale frees had corrupted, PR #153, is the
         * suspect).  Lower optimisation levels are tried; config.txt's shacc_restart=1 first restarts the
         * compiler (in Vita3K the restarted module reads NULL and the game hangs) */
        for (o = 0, c = 0; o < 4 && !(c && size); o++) {
            if (o == 1 && !kh1_vita_shacc_restart) continue;
            if (o) {
                shark_clear_output();
                if (o == 1) {
                    kh1_vita_log("kh1-gxm: a %s shader failed: restarting the compiler\n", frag ? "fragment" : "vertex");
                    shark_end();
                    shark_ok = shark_ok == 2 ? (shark_init(0) >= 0 ? 2 : 0) : shark_init_simple(0) >= 0;
                    if (!shark_ok) break;
                } else {
                    kh1_vita_log("kh1-gxm: trying optimisation level %d\n", 3 - o);
                }
            }
            size = len; /* in: the source's length (vitaShaRK passes it on as the source's size); out: the program's */
            c = shark_compile_shader_extended(text, &size, frag ? SHARK_FRAGMENT_SHADER : SHARK_VERTEX_SHADER,
                                              opts[o], SHARK_DISABLE, SHARK_DISABLE, SHARK_DISABLE);
        }
        if (!c || !size) {
            const SceShaccCgCompileOutput *o = shark_ok ? shark_get_internal_compile_output() : 0;
            int i;
            kh1_vita_log("kh1-gxm: a %s shader did not compile:\n%s", frag ? "fragment" : "vertex", text);
            for (i = 0; o && i < o->diagnosticCount; i++)
                kh1_vita_log("kh1-gxm:   line %d: %s\n", o->diagnostics[i].location ? o->diagnostics[i].location->lineNumber : 0,
                             o->diagnostics[i].message);
            if (shark_ok) shark_clear_output();
            failed++;
            return 0;
        }
        p = (SceGxmProgram *)malloc(size);
        if (p) memcpy(p, c, size);
        shark_clear_output();
    }
    if (!p) return 0;
    compiled++;
    fd = sceIoOpen(path, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
    if (fd >= 0) {
        sceIoWrite(fd, p, size);
        sceIoClose(fd);
    }
    return p;
}

static SceGxmShaderPatcher *patcher;
static SceGxmContext *ctx;
static char text[KH1_SHADER_TEXT];

typedef struct {
    SceGxmProgram *prog;
    SceGxmShaderPatcherId id;
    SceGxmVertexProgram *vp;
    const SceGxmProgramParameter *u_xf;
} VertProg;
static VertProg vert[7];

static s32 reg_of(void *prog, const char *name) {
    const SceGxmProgramParameter *p = sceGxmProgramFindParameterByName((const SceGxmProgram *)prog, name);
    return p ? (s32)sceGxmProgramParameterGetResourceIndex(p) : -1;
}

static int vert_load(u32 i) {
    VertProg *v = &vert[i];
    KH1GxmVtxAttr a[4];
    KH1GxmVtxStream s;
    u32 n, len = kh1_shader_vert_cg(i, text, sizeof text);
    if (!len || !(v->prog = program_of(text, len, 0))) return -1;
    if (sceGxmShaderPatcherRegisterProgram(patcher, v->prog, &v->id) < 0) return -1;
    n = kh1_vertex_gxm_attrs(i, reg_of, v->prog, a, &s);
    if (!n || sceGxmShaderPatcherCreateVertexProgram(patcher, v->id, (const SceGxmVertexAttribute *)a, n,
                                                     (const SceGxmVertexStream *)&s, 1, &v->vp) < 0)
        return -1;
    v->u_xf = sceGxmProgramFindParameterByName(v->prog, "u_xf");
    return 0;
}

/* a fragment shader variant: compiled once per KH1ShaderKey */
#define FRAGS 256
typedef struct {
    KH1ShaderKey k;
    int state;    /* 0 not tried, 1 ready, -1 not generated or not compiled */
    SceGxmProgram *prog;
    SceGxmShaderPatcherId id;
    const SceGxmProgramParameter *u[5]; /* u_a, u_b, u_r, u_c, u_xf */
    s32 tex;      /* the sampler's texture unit, -1 none */
} FragShader;
static FragShader frag[FRAGS];
static u32 nfrag;

static FragShader *frag_of(const KH1ShaderKey *k) {
    static const char *names[5] = { "u_a", "u_b", "u_r", "u_c", "u_xf" };
    FragShader *f;
    u32 i, len;
    for (i = 0; i < nfrag; i++)
        if (!memcmp(&frag[i].k, k, sizeof *k)) return frag[i].state > 0 ? &frag[i] : 0;
    if (nfrag == FRAGS) return 0;
    f = &frag[nfrag++];
    memset(f, 0, sizeof *f);
    f->k = *k;
    f->state = -1;
    len = kh1_shader_frag_cg(k, text, sizeof text);
    if (len && !(f->prog = program_of(text, len, 1)) && (k->su == KH1_SHADER_TAPS || k->sv == KH1_SHADER_TAPS)) {
        /* session 137v: a REGION_REPEAT shader SceShaccCg refuses (shadertest=1) is drawn with the plain
         * wrap instead, the region's texels then read from the whole texture: close, against nothing */
        KH1ShaderKey w = *k;
        if (w.su == KH1_SHADER_TAPS) w.su = KH1_SHADER_NONE;
        if (w.sv == KH1_SHADER_TAPS) w.sv = KH1_SHADER_NONE;
        len = kh1_shader_frag_cg(&w, text, sizeof text);
        if (len) {
            kh1_vita_log("kh1-gxm: drawing that shader's draws without the region repeat\n");
            f->prog = program_of(text, len, 1);
        }
    }
    if (!len || !f->prog) return 0;
    if (sceGxmShaderPatcherRegisterProgram(patcher, f->prog, &f->id) < 0) return 0;
    for (i = 0; i < 5; i++) f->u[i] = sceGxmProgramFindParameterByName(f->prog, names[i]);
    f->tex = reg_of(f->prog, "tex");
    f->state = 1;
    return f;
}

/* a fragment program: the shader, the pipeline's blend and write mask (GXM bakes them in), the vertex program */
#define PROGS 512
typedef struct {
    KH1ShaderKey k;
    u8 blend, eq, fs, fd, mask, vert;
    SceGxmFragmentProgram *fp;
} FragProg;
static FragProg prog[PROGS];
static u32 nprog;

static u8 factor(u8 f) {
    static const u8 m[] = { SCE_GXM_BLEND_FACTOR_ZERO, SCE_GXM_BLEND_FACTOR_ONE, SCE_GXM_BLEND_FACTOR_SRC_ALPHA,
                            SCE_GXM_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA, SCE_GXM_BLEND_FACTOR_DST_ALPHA,
                            SCE_GXM_BLEND_FACTOR_ONE_MINUS_DST_ALPHA };
    return f < 6 ? m[f] : SCE_GXM_BLEND_FACTOR_ONE;
}

/* a frame read's stand-in when its shader cannot be had (session 136): Vita3K takes no __nativecolor (that
 * needs SceShaccCgExt's patches, shark_init).  FBMSK's bits are written whole and the blend is the fixed
 * function's when blend.h has one without the mask (FIX taken as 0x80); 0: none (the draw is skipped) */
static int unfetch(const KH1PipeKey *p, KH1PipeKey *o) {
    KH1BlendState b;
    *o = *p;
    o->shader.fetch = o->shader.fabcd = o->shader.fpsm = 0;
    memset(o->shader.fbm, 0, sizeof o->shader.fbm);
    if (p->shader.fetch == 2) return 1;
    kh1_blend_state(p->shader.fabcd, 0x80, 1, p->shader.fpsm == 1 ? 0x01 : 0x00, 0, &b);
    if (b.kind == KH1_BLEND_FETCH) return 0;
    o->shader.pre_a = (u8)(b.pre_a + 2);
    o->shader.pre_d = (u8)(b.pre_d + 2);
    o->shader.pre_floor = b.pre_floor;
    o->shader.csel = b.pre_a ? b.csel : 0;
    o->blend = b.enable;
    o->eq = b.eq;
    o->fs = b.fs;
    o->fd = b.fd;
    return 1;
}

static SceGxmFragmentProgram *prog_of(const KH1PipeKey *p, u32 vi, FragShader **fs) {
    FragProg *e;
    SceGxmBlendInfo bi;
    KH1PipeKey alt;
    u32 i;
    *fs = frag_of(&p->shader);
    if (!*fs && p->shader.fetch && unfetch(p, &alt)) {
        p = &alt;
        *fs = frag_of(&p->shader);
    }
    if (!*fs || !vert[vi].vp) {
        snprintf(pipe_why, sizeof pipe_why, "%s: %s", kh1_pipekey_str(p), !*fs ? "its fragment shader" : "its vertex variant");
        return 0;
    }
    for (i = 0; i < nprog; i++) {
        e = &prog[i];
        if (e->blend == p->blend && e->eq == p->eq && e->fs == p->fs && e->fd == p->fd && e->mask == p->mask &&
            e->vert == vi && !memcmp(&e->k, &p->shader, sizeof e->k))
            return e->fp;
    }
    if (nprog == PROGS) {
        snprintf(pipe_why, sizeof pipe_why, "%s: the program table is full", kh1_pipekey_str(p));
        return 0;
    }
    e = &prog[nprog];
    memset(e, 0, sizeof *e);
    e->k = p->shader;
    e->blend = p->blend; e->eq = p->eq; e->fs = p->fs; e->fd = p->fd; e->mask = p->mask; e->vert = (u8)vi;
    /* blend.h: the colour blends src x ONE (the shader pre-scaled it) against dst x Fd; alpha is the source's */
    memset(&bi, 0, sizeof bi);
    bi.colorMask = (p->mask & 1 ? SCE_GXM_COLOR_MASK_R : 0) | (p->mask & 2 ? SCE_GXM_COLOR_MASK_G : 0) |
                   (p->mask & 4 ? SCE_GXM_COLOR_MASK_B : 0) | (p->mask & 8 ? SCE_GXM_COLOR_MASK_A : 0);
    bi.colorFunc = p->blend ? (p->eq == KH1_BEQ_SUBTRACT ? SCE_GXM_BLEND_FUNC_SUBTRACT
                              : p->eq == KH1_BEQ_REVERSE_SUBTRACT ? SCE_GXM_BLEND_FUNC_REVERSE_SUBTRACT
                              : SCE_GXM_BLEND_FUNC_ADD) : SCE_GXM_BLEND_FUNC_NONE;
    bi.alphaFunc = p->blend ? SCE_GXM_BLEND_FUNC_ADD : SCE_GXM_BLEND_FUNC_NONE;
    bi.colorSrc = p->blend ? factor(p->fs) : SCE_GXM_BLEND_FACTOR_ONE;
    bi.colorDst = p->blend ? factor(p->fd) : SCE_GXM_BLEND_FACTOR_ZERO;
    bi.alphaSrc = SCE_GXM_BLEND_FACTOR_ONE;
    bi.alphaDst = SCE_GXM_BLEND_FACTOR_ZERO;
    {
        int err = sceGxmShaderPatcherCreateFragmentProgram(patcher, (*fs)->id, SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4,
                                                           SCE_GXM_MULTISAMPLE_NONE, p->blend || p->mask != 15 ? &bi : 0,
                                                           vert[vi].prog, &e->fp);
        if (err < 0) {
            snprintf(pipe_why, sizeof pipe_why, "%s: sceGxmShaderPatcherCreateFragmentProgram 0x%08x", kh1_pipekey_str(p),
                     (u32)err);
            return 0;
        }
    }
    nprog++;
    return e->fp;
}

/* ---- the present's own pair: the display target as an opaque bilinear quad ---- */
static const char present_v[] =
    "void main(float2 pos : POSITION, float2 tc : TEXCOORD0, out float4 opos : POSITION, out float2 otc : TEXCOORD0)\n"
    "{\n    opos = float4(pos, 0.5, 1.0);\n    otc = tc;\n}\n";
static const char present_f[] =
    "void main(float2 tc : TEXCOORD0, uniform sampler2D tex, out float4 ocolor : COLOR)\n"
    "{\n    ocolor = float4(tex2D(tex, tc).rgb, 1.0);\n}\n";
static SceGxmVertexProgram *pv;
static SceGxmFragmentProgram *pf;

static int present_load(void) {
    SceGxmProgram *v = program_of(present_v, sizeof present_v - 1, 0), *f = program_of(present_f, sizeof present_f - 1, 1);
    SceGxmShaderPatcherId vid, fid;
    SceGxmVertexAttribute a[2];
    SceGxmVertexStream s;
    if (!v || !f || reg_of(v, "pos") < 0 || reg_of(v, "tc") < 0) return -1;
    if (sceGxmShaderPatcherRegisterProgram(patcher, v, &vid) < 0 || sceGxmShaderPatcherRegisterProgram(patcher, f, &fid) < 0)
        return -1;
    a[0].streamIndex = 0; a[0].offset = 0; a[0].format = SCE_GXM_ATTRIBUTE_FORMAT_F32; a[0].componentCount = 2;
    a[0].regIndex = (u16)reg_of(v, "pos");
    a[1].streamIndex = 0; a[1].offset = 8; a[1].format = SCE_GXM_ATTRIBUTE_FORMAT_F32; a[1].componentCount = 2;
    a[1].regIndex = (u16)reg_of(v, "tc");
    s.stride = 16;
    s.indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;
    if (sceGxmShaderPatcherCreateVertexProgram(patcher, vid, a, 2, &s, 1, &pv) < 0) return -1;
    if (sceGxmShaderPatcherCreateFragmentProgram(patcher, fid, SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4, SCE_GXM_MULTISAMPLE_NONE,
                                                 0, v, &pf) < 0)
        return -1;
    return 0;
}

/* session 150 (the watchdog's): blocks of uploads into targets kept for a target's pixels, and left as outside them;
 * flushes of them that needed no wait for the GPU */
volatile u32 kh1_vita_pend_in, kh1_vita_pend_out, kh1_vita_pend_nowait;

/* ---- render targets and depth buffers ---- */
typedef struct {
    u32 w, h;      /* the pass's size */
    u32 stride;    /* pixels a row */
    u32 bytes;
    u8 *mem;
    u8 rt;         /* KH1_RT_* */
    u8 drawn;      /* a scene drew it (since the run started) */
    Heap *heap;    /* CDRAM, or LPDDR when CDRAM had no room (session 136) */
    SceGxmColorSurface surf;
    SceGxmRenderTarget *gxrt;
    /* session 137v: uploads into it not yet written: GS memory is read as the frame left it, so each upload of a
     * frame writes the same bytes, and they are written once, before the target's next use (pend_flush).
     * Session 141: kept as the GS words they wrote (pend_block), placed by the target's own FBP / FBW */
    u8 pend;
    u32 fbp, fbw;
    /* session 150: the last scene (scene_no) that drew it or sampled it; once finish_seen has passed it the GPU is
     * done with its pixels, and pend_flush writes them with no wait */
    u32 used;
} Target;
static Target tgt[KH1_CMD_TARGETS];
static u32 scene_no, finish_seen; /* scenes begun, and the count when sceGxmFinish last returned */

/* GXM's render target objects, one a size; when the table is full the one used longest ago (never one of
 * this frame: sceGxmFinish at the frame's start covers the older) is destroyed for the new size */
#define RTOBJS 32
typedef struct {
    u32 w, h, used; /* used: the frame it last began a scene */
    SceGxmRenderTarget *rt;
} RtObj;
static RtObj rtobj[RTOBJS];
static u32 nrtobj, gxm_frame_no;
static char rt_why[96]; /* the last failure (the skip log's) */

static SceGxmRenderTarget *rt_of(u32 w, u32 h) {
    SceGxmRenderTargetParams p;
    RtObj *e;
    u32 i;
    int err;
    for (i = 0; i < nrtobj; i++)
        if (rtobj[i].w == w && rtobj[i].h == h) {
            rtobj[i].used = gxm_frame_no;
            return rtobj[i].rt;
        }
    if (nrtobj < RTOBJS) e = &rtobj[nrtobj];
    else {
        e = 0;
        for (i = 0; i < RTOBJS; i++)
            if (rtobj[i].used != gxm_frame_no && (!e || rtobj[i].used < e->used)) e = &rtobj[i];
        if (!e) {
            snprintf(rt_why, sizeof rt_why, "%u render target sizes in one frame", RTOBJS);
            return 0;
        }
        sceGxmDestroyRenderTarget(e->rt);
        e->rt = 0;
        e->w = e->h = 0;
    }
    memset(&p, 0, sizeof p);
    p.width = (u16)w;
    p.height = (u16)h;
    p.scenesPerFrame = 8;
    p.multisampleMode = SCE_GXM_MULTISAMPLE_NONE;
    p.driverMemBlock = -1;
    err = sceGxmCreateRenderTarget(&p, &e->rt);
    if (err < 0) {
        snprintf(rt_why, sizeof rt_why, "sceGxmCreateRenderTarget %u x %u: 0x%08x", w, h, (u32)err);
        e->rt = 0;
        return 0;
    }
    e->w = w;
    e->h = h;
    e->used = gxm_frame_no;
    if (e == &rtobj[nrtobj]) nrtobj++;
    return e->rt;
}

/* a GPU surface: CDRAM first, LPDDR (uncached) when CDRAM has no span that large */
static void *surface_alloc(u32 len, Heap **from) {
    void *p = heap_alloc(&vram, len);
    *from = &vram;
    if (!p) {
        p = heap_alloc(&tram, len);
        *from = &tram;
    }
    return p;
}

static u32 pow2_up(u32 v) {
    u32 p = 1;
    while (p < v) p <<= 1;
    return p;
}

/* the target for the recorder's index, made (or grown) to w x h */
static Target *target(u32 i, u32 rt, u32 w, u32 h) {
    Target *t;
    if (i >= KH1_CMD_TARGETS || !w || !h) return 0;
    t = &tgt[i];
    if (t->mem && t->w == w && t->h == h) return (t->gxrt = rt_of(w, h)) ? t : 0;
    if (t->mem) heap_free(t->heap, t->mem, t->bytes);
    memset(t, 0, sizeof *t);
    t->used = scene_no; /* its memory may have been another's that a scene in flight uses */
    t->w = w;
    t->h = h;
    t->rt = (u8)rt;
    t->stride = (w + 31) & ~31u;
    /* room below for a texture of the pass's power-of-two height (TEX0's TH) read in place, and a row past it */
    t->bytes = t->stride * 4 * (pow2_up(h) + 1);
    t->mem = (u8 *)surface_alloc(t->bytes, &t->heap);
    if (!t->mem) {
        snprintf(rt_why, sizeof rt_why, "%u KiB for its pixels", t->bytes >> 10);
        return 0;
    }
    memset(t->mem, 0, t->bytes);
    if (sceGxmColorSurfaceInit(&t->surf, SCE_GXM_COLOR_FORMAT_A8B8G8R8, SCE_GXM_COLOR_SURFACE_LINEAR,
                               SCE_GXM_COLOR_SURFACE_SCALE_NONE, SCE_GXM_OUTPUT_REGISTER_SIZE_32BIT, w, h, t->stride,
                               t->mem) < 0 || !(t->gxrt = rt_of(w, h))) {
        heap_free(t->heap, t->mem, t->bytes);
        t->mem = 0;
        return 0;
    }
    return t;
}

typedef struct {
    u32 w, h, bytes;
    void *mem;
    SceGxmDepthStencilSurface surf;
    Heap *heap;
} Depth;
static Depth depth[3]; /* KH1_DS_NONE (DATE's stencil only), MAIN, SHADOW */

static Depth *depth_of(u32 d, u32 w, u32 h) {
    Depth *z = &depth[d < 3 ? d : 0];
    u32 sw, sh;
    if (z->mem && z->w >= w && z->h >= h) return z;
    if (z->mem) heap_free(z->heap, z->mem, z->bytes);
    z->w = w > z->w ? w : z->w;
    z->h = h > z->h ? h : z->h;
    sw = (z->w + 31) & ~31u;
    sh = (z->h + 31) & ~31u;
    z->bytes = sw * sh * 4;
    z->mem = surface_alloc(z->bytes, &z->heap);
    if (!z->mem) return 0;
    sceGxmDepthStencilSurfaceInit(&z->surf, SCE_GXM_DEPTH_STENCIL_FORMAT_S8D24, SCE_GXM_DEPTH_STENCIL_SURFACE_TILED, sw,
                                  z->mem, 0);
    return z;
}

/* ---- textures and palettes ---- */
typedef struct {
    u32 lo, hi;     /* the TEX0 uploaded (texcache.h's key) */
    u32 bytes;
    void *mem;
    u32 w, h, psm;
} TexMem;
static TexMem tex[KH1_TEXCACHE_SLOTS];
static void *pal[KH1_PALCACHE_SLOTS]; /* 256 ABGR words each */
static void *pal_rb;                   /* the CLUT pass's read-back palette (one a frame is the game's use) */

static void tex_upload(s32 slot, u32 lo, u32 hi) {
    TexMem *m;
    u32 w = 1u << (lo >> 26 & 15), h = 1u << ((lo >> 30 | hi << 2) & 15), psm = lo >> 20 & 63, n;
    const u32 *texels = kh1_pipes_frame_texels(slot);
    if (!texels) return;
    m = &tex[slot];
    n = kh1_texfmt_stride(psm, w) * h;
    if (!n) return;
    if (!m->mem || m->bytes < n) {
        heap_free(&tram, m->mem, m->bytes);
        m->mem = heap_alloc(&tram, n);
        m->bytes = m->mem ? n : 0;
        if (!m->mem) return;
    }
    kh1_texfmt_convert(psm, texels, w, h, m->mem);
    m->lo = lo;
    m->hi = hi;
    m->w = w;
    m->h = h;
    m->psm = psm;
}

/* A texture neither cache keeps nor the recorder maps to a colour target (on the title: a full-screen CT24 layer at
 * 0x0E00, in the depth buffer's pages, which the game uploads into each frame): read from GS memory as the frame
 * left it, kept while its page stamp holds, never refilled in a frame that drew it (the GPU reads it later) */
#define LOOSE 32 /* session 137v: 8 ran out in Dive to the Heart on the English disc */
typedef struct {
    u32 lo, hi, stamp, frame, bytes;
    void *mem;
} Loose;
static Loose loose[LOOSE];
static u32 loose_frame, loose_reads;
static const char *loose_why; /* why tex_loose gave none */

static const TexMem *tex_loose(u32 lo, u32 hi) {
    static TexMem m;
    static u32 buf[1024 * 1024];
    u32 w = 1u << (lo >> 26 & 15), h = 1u << ((lo >> 30 | hi << 2) & 15), psm = lo >> 20 & 63, stamp, i, n;
    Loose *e = 0;
    loose_why = "too big or no format";
    if (w > 1024 || h > 1024 || !(n = kh1_texfmt_stride(psm, w) * h)) return 0;
    stamp = gs_tex_stamp(lo, hi);
    for (i = 0; i < LOOSE; i++)
        if (loose[i].mem && loose[i].lo == lo && loose[i].hi == hi) { e = &loose[i]; break; }
    loose_why = "drawn this frame with other bytes";
    if (e && e->stamp != stamp && e->frame == loose_frame) return 0; /* drawn this frame with other bytes */
    if (!e)
        for (i = 0; i < LOOSE; i++)
            if (loose[i].frame != loose_frame && (!e || loose[i].frame < e->frame)) e = &loose[i];
    loose_why = "every loose entry drawn this frame";
    if (!e) return 0;
    if (!e->mem || e->lo != lo || e->hi != hi || e->stamp != stamp) {
        if (e->bytes < n) {
            heap_free(&tram, e->mem, e->bytes);
            e->mem = heap_alloc(&tram, n);
            e->bytes = e->mem ? n : 0;
            loose_why = "no texture memory";
            if (!e->mem) return 0;
        }
        loose_why = "GS memory read refused";
        if (gs_read_rect(psm, lo & 0x3FFF, lo >> 14 & 63, 0, 0, w, h, buf, w)) return 0;
        kh1_texfmt_convert(psm, buf, w, h, e->mem);
        e->lo = lo;
        e->hi = hi;
        e->stamp = stamp;
        loose_reads++;
    }
    e->frame = loose_frame;
    m.mem = e->mem;
    m.lo = lo;
    m.hi = hi;
    m.w = w;
    m.h = h;
    m.psm = psm;
    return &m;
}

static SceGxmTextureFormat tex_format(u32 fmt) {
    switch (fmt) {
    case KH1_TEXFMT_A1B5G5R5: return SCE_GXM_TEXTURE_FORMAT_U1U5U5U5_ABGR;
    case KH1_TEXFMT_P8: return SCE_GXM_TEXTURE_FORMAT_P8_ABGR;
    case KH1_TEXFMT_P4: return SCE_GXM_TEXTURE_FORMAT_P4_ABGR;
    }
    return SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ABGR;
}

/* ---- the frame ---- */
static KH1GxmRec rec;
static u16 *index_buf;
static u8 *vbuf;          /* the frame's vertices (a copy of the recorder's ring slot) */
static u32 vbuf_bytes;
static int ready;
static s32 display = -1;  /* the display target's index, once drawn */
static u32 frames, draws, skipped, scenes; /* the watchdog's */

/* session 136: why a draw (or a scene, or a frame) is skipped, each reason's first case logged with what was
 * asked, and the counts every 600 frames while they grow */
enum { W_RING, W_TARGET, W_DEPTH, W_SCENE, W_NOSCENE, W_PIPE, W_TEX, W_RANGE, W_STATE, W_N };
static const char *const why_s[W_N] = { "the frame's vertices overflow the ring", "no render target", "no depth buffer",
                                        "sceGxmBeginScene refused", "in a scene that did not begin",
                                        "no pipeline", "no texture", "vertices out of range",
                                        "no uniforms or primitive class" };
static u32 why[W_N];
/* the texture skips by their reason (tex_why's text after its last ": "), with the first one's whole text */
static struct { char r[48], ex[160]; u32 n; } texskip[8];
static void skip(u32 w, const char *detail) {
    skipped++;
    if (w == W_TEX && detail) {
        const char *r = detail, *p;
        u32 i;
        for (p = detail; (p = strstr(p, ": ")) != 0; p += 2) r = p + 2;
        for (i = 0; i < 8 && texskip[i].n && strncmp(texskip[i].r, r, sizeof texskip[i].r - 1); i++) {}
        if (i < 8) {
            if (!texskip[i].n++) {
                snprintf(texskip[i].r, sizeof texskip[i].r, "%s", r);
                snprintf(texskip[i].ex, sizeof texskip[i].ex, "%s", detail);
            }
        }
    }
    if (!why[w]++) kh1_vita_log("kh1-gxm: first skip, %s: %s\n", why_s[w], detail ? detail : "");
}

volatile u32 kh1_vita_us_gpu; /* microseconds in kh1_vita_gxm_frame (the watchdog's) */
/* session 137v: of it, by part: 0 turning the commands into calls (gxmrec), 1 the vertex copy, 2 the scenes'
 * begin / end, 3 the draws (programs, textures, sceGxmDraw), 4 the transfers (texture, palette, target uploads) */
volatile u32 kh1_vita_us_part[5];
volatile u32 kh1_vita_us_finish, kh1_vita_finishes; /* of it, waiting in sceGxmFinish, and how many */
/* session 147d: by where (the title's New Game pages wait ~1.3 s per 2 s in ~2 finishes a frame): 0 the frame's start,
 * 1 the uploads into targets, 2 a CLUT pass's readback, 3 a blit */
volatile u32 kh1_vita_us_finish_at[4], kh1_vita_finishes_at[4];
static void finish_at(int at) {
    SceUInt64 t0 = sceKernelGetProcessTimeWide();
    u32 us;
    sceGxmFinish(ctx);
    finish_seen = scene_no;
    us = (u32)(sceKernelGetProcessTimeWide() - t0);
    kh1_vita_us_finish += us;
    kh1_vita_finishes++;
    kh1_vita_us_finish_at[at] += us;
    kh1_vita_finishes_at[at]++;
}

static void stencil(u32 mode) {
    switch (mode) {
    case 1: sceGxmSetFrontStencilFunc(ctx, SCE_GXM_STENCIL_FUNC_EQUAL, SCE_GXM_STENCIL_OP_KEEP, SCE_GXM_STENCIL_OP_KEEP,
                                      SCE_GXM_STENCIL_OP_KEEP, 0xFF, 0); sceGxmSetFrontStencilRef(ctx, 1); break;
    case 2: case 3:
        sceGxmSetFrontStencilFunc(ctx, SCE_GXM_STENCIL_FUNC_ALWAYS, SCE_GXM_STENCIL_OP_KEEP, SCE_GXM_STENCIL_OP_REPLACE,
                                  SCE_GXM_STENCIL_OP_REPLACE, 0xFF, 0xFF);
        sceGxmSetFrontStencilRef(ctx, mode == 2 ? 1 : 0);
        break;
    default: sceGxmSetFrontStencilFunc(ctx, SCE_GXM_STENCIL_FUNC_ALWAYS, SCE_GXM_STENCIL_OP_KEEP, SCE_GXM_STENCIL_OP_KEEP,
                                       SCE_GXM_STENCIL_OP_KEEP, 0xFF, 0xFF); break;
    }
}

/* Session 141: the words of GS memory uploads (and copies from GS memory) wrote into a target's pages, not yet
 * in its pixels: a block (0-0x3FFF) each, its 64 words' mask, its target, and whether CT24 wrote it (the alpha
 * then 0x80).  Before, a pending upload was a rectangle at BITBLTBUF's (DSAX, DSAY) read from GS memory in the
 * upload's own layout and written at the same (x, y) of the target: right only for an upload at the target's
 * own FBP in CT32 / CT24.  Dive to the Heart streams T8 textures and CT32 CLUTs at 0x3700-0x3980 into the
 * pages of targets at lower FBPs, ~40 a frame, each one's rectangle then written at the target's top left
 * (and read as CT32 from the upload's bp).  Now each word the upload wrote goes to the target pixel that
 * holds it (the target's CT32 layout from FBP / FBW), and only those: whole blocks from a table, the
 * rectangle's edge blocks pixel by pixel.  GS memory is still read as the frame left it, when written. */
static u64 pend_mask[0x4000];
static u32 pend_own[0x4000];  /* the targets (bit i: tgt[i]) it is pending for */
static u8 pend_24[0x4000];    /* CT24 wrote it */
static u16 pend_list[0x4000];
static u32 pend_n;
static u8 inv_x[2048], inv_y[2048]; /* a CT32 page's word (kh1_gsmem_addr at bp 0) -> its pixel */

/* a block's words m written for target t (its index); a block two overlapping targets wait for is written to
 * both (the words lie in both one's pages) */
static void pend_block(u32 t, u32 b, u64 m, int ct24) {
    b &= 0x3FFF;
    if (!pend_own[b]) {
        pend_mask[b] = 0;
        pend_list[pend_n++] = (u16)b;
    }
    pend_own[b] |= 1u << t;
    pend_mask[b] |= m;
    pend_24[b] = (u8)ct24;
}

/* GS memory's words in the pending blocks into the targets' pixels, the alpha on the 0x80 scale */
static void pend_write(Target *t, u32 b, u64 m, int ct24) {
    static u8 a8[256];
    static int made;
    u32 words[64], rel, pg, x0, y0, c;
    if (!made) {
        u32 x, y;
        for (c = 0; c < 256; c++) a8[c] = (u8)kh1_blend_store_alpha(c);
        for (y = 0; y < 32; y++)
            for (x = 0; x < 64; x++) {
                u32 a = kh1_gsmem_addr(KH1_PSMCT32, 0, 1, x, y);
                inv_x[a] = (u8)x;
                inv_y[a] = (u8)y;
            }
        made = 1;
    }
    if (!t->mem || !t->fbw) return;
    rel = (b - t->fbp * 32) & 0x3FFF;
    pg = rel >> 5;
    x0 = pg % t->fbw * 64;
    y0 = pg / t->fbw * 32;
    if (x0 >= t->w || y0 >= t->h) return;
    gs_read_block(b, words);
    for (c = 0; c < 64; c++) {
        u32 a = (rel & 31) * 64 + c, x = x0 + inv_x[a], y = y0 + inv_y[a], v = words[c];
        if (!(m >> c & 1) || x >= t->w || y >= t->h) continue;
        ((u32 *)t->mem)[y * t->stride + x] = ct24 ? (v & 0xFFFFFF) | 0x80000000u : (v & 0xFFFFFF) | (u32)a8[v >> 24] << 24;
    }
}

/* the pending uploads written; `only` one target's, or all.  Session 150: a wait for the GPU (one for them all)
 * only when a scene not yet finished drew or sampled one of those targets (the Dive's mid-frame flush is for
 * two targets no scene of the frame had used yet, ~5 ms a frame of waiting) */
static void pend_flush(Target *only) {
    u32 i, k = 0, sel = only ? 1u << (u32)(only - tgt) : ~0u;
    int wait = 0, any = 0;
    for (i = 0; i < KH1_CMD_TARGETS; i++)
        if (sel >> i & 1 && tgt[i].pend && tgt[i].used > finish_seen) wait = 1;
    for (i = 0; i < pend_n; i++) {
        u32 b = pend_list[i], own = pend_own[b] & sel, j;
        if (own) {
            if (!any) {
                if (wait) finish_at(1);
                else kh1_vita_pend_nowait++;
            }
            any = 1;
            for (j = 0; j < KH1_CMD_TARGETS; j++)
                if (own >> j & 1) pend_write(&tgt[j], b, pend_mask[b], pend_24[b]);
            pend_own[b] &= ~own;
        }
        if (pend_own[b]) pend_list[k++] = (u16)b;
    }
    pend_n = k;
    for (i = 0; i < KH1_CMD_TARGETS; i++)
        if (sel >> i & 1) tgt[i].pend = 0;
}

/* session 150: a block whose page lies outside the target's pixels (pend_write would write none of it) */
static int pend_outside(const Target *t, u32 b) {
    u32 pg = ((b & 0x3FFF) - t->fbp * 32) >> 5 & 511;
    return !t->fbw || pg % t->fbw * 64 >= t->w || pg / t->fbw * 32 >= t->h;
}

/* an upload's (BITBLTBUF's destination) w x h at (dx, dy), or a copy's from GS memory: the words it wrote.
 * Session 150: only the blocks that land in the target's pixels, and the target pending only when one does:
 * a wait for the GPU for words pend_write would drop was the Dive's ~7 ms a frame there */
static void pend_add(Target *t, u32 key, const KH1CmdXfer *x, u32 dx, u32 dy, u32 w, u32 h) {
    u32 psm = x->bb_hi >> 24 & 63, bp = x->bb_hi & 0x3FFF, bw = x->bb_hi >> 16 & 63, ti = (u32)(t - tgt);
    u32 bwid, bhgt, sh, bx, by, xx, yy;
    int ct24 = psm == KH1_PSMCT24;
    if (kh1_gsmem_addr(psm, 0, 1, 0, 0) == ~0u || !w || !h) return;
    t->fbp = key >> 8 & 0xFFF;
    t->fbw = key >> 20 & 63;
    bwid = psm == KH1_PSMT4 ? 32 : psm == KH1_PSMT8 || (psm & 0xF) == 2 || (psm & 0xF) == 0xA ? 16 : 8;
    bhgt = psm == KH1_PSMT8 || psm == KH1_PSMT4 ? 16 : 8;
    sh = psm == KH1_PSMT4 ? 3 : psm == KH1_PSMT8 ? 2 : bwid == 16 ? 1 : 0; /* kh1_gsmem_addr's units to words */
    for (by = dy / bhgt; by <= (dy + h - 1) / bhgt; by++)
        for (bx = dx / bwid; bx <= (dx + w - 1) / bwid; bx++) {
            u32 x0 = bx * bwid, y0 = by * bhgt, b = kh1_gsmem_addr(psm, bp, bw, x0, y0) >> sh >> 6;
            u64 m = 0;
            if (pend_outside(t, b)) {
                kh1_vita_pend_out++;
                continue;
            }
            kh1_vita_pend_in++;
            t->pend = 1;
            if (x0 >= dx && y0 >= dy && x0 + bwid <= dx + w && y0 + bhgt <= dy + h) { /* a whole block */
                pend_block(ti, b, ~0ull, ct24);
                continue;
            }
            for (yy = y0 < dy ? dy : y0; yy < y0 + bhgt && yy < dy + h; yy++)
                for (xx = x0 < dx ? dx : x0; xx < x0 + bwid && xx < dx + w; xx++)
                    m |= 1ull << (kh1_gsmem_addr(psm, bp, bw, xx, yy) >> sh & 63);
            pend_block(ti, b, m, ct24);
        }
}

void kh1_vita_gxm_frame(const KH1CmdRec *r) {
    const u8 *ub = r->uring.base + r->uring.cur * r->uring.slot;
    const u8 *vsrc = r->vring.base + r->vring.cur * r->vring.slot;
    const f32 *u = 0, *xf = 0;
    const KH1PipeKey *pk = 0;
    SceGxmFragmentProgram *fp = 0;
    FragShader *fs = 0;
    Target *cur = 0;
    SceGxmTexture t;
    int have_tex = 0, open = 0, bad_pipe = 0, zbound = 0; /* zbound: the scene's depth buffer is a GS one */
    u32 i, vi = 0, pal_rb_slot = ~0u;
    SceUInt64 t0;
    if (!ready) return;
    t0 = sceKernelGetProcessTimeWide();
    kh1_gxm_frame(&rec, r);
    kh1_vita_us_part[0] += (u32)(sceKernelGetProcessTimeWide() - t0);
    finish_at(0); /* the last frame's scenes are done with the rings, the caches' GPU copies and the targets */
    pend_flush(0); /* the last frame's uploads its scenes did not need (GS memory as this frame left it) */
    if (r->vring.head > vbuf_bytes) {
        char d[64];
        snprintf(d, sizeof d, "%u bytes, room for %u", (u32)r->vring.head, (u32)vbuf_bytes);
        skip(W_RING, d);
        return;
    }
    loose_frame++;
    gxm_frame_no++;
    if (frames % 600 == 0 && skipped) {
        static u32 last;
        if (skipped != last) {
            u32 w;
            char b[512];
            u32 n = 0;
            for (w = 0; w < W_N; w++)
                if (why[w] && n < sizeof b - 64) n += (u32)snprintf(b + n, sizeof b - n, " %u %s;", why[w], why_s[w]);
            b[n] = 0;
            kh1_vita_log("kh1-gxm: skipped so far:%s\n", b);
            for (w = 0; w < 8 && texskip[w].n; w++)
                kh1_vita_log("kh1-gxm:   no texture, %u: %s\n", texskip[w].n, texskip[w].ex);
            last = skipped;
        }
    }
    {
        SceUInt64 t1 = sceKernelGetProcessTimeWide();
        memcpy(vbuf, vsrc, r->vring.head);
        kh1_vita_us_part[1] += (u32)(sceKernelGetProcessTimeWide() - t1);
    }
    memset(&t, 0, sizeof t);
    for (i = 0; i < rec.n; i++) {
        const KH1GxmCall *c = &rec.call[i];
        const KH1Cmd *k = c->cmd < r->ncmd ? &r->cmd[c->cmd] : 0;
        SceUInt64 t1 = sceKernelGetProcessTimeWide();
        u32 part = c->op == KH1_GXM_BEGIN_SCENE || c->op == KH1_GXM_END_SCENE ? 2
                   : c->op == KH1_GXM_DRAW || c->op == KH1_GXM_SET_PROGRAMS || c->op == KH1_GXM_SET_TEXTURE ? 3 : 4;
        switch (c->op) {
        case KH1_GXM_BEGIN_SCENE: {
            Depth *z;
            u32 j, dstore = 0;
            cur = c->tgt < KH1_CMD_TARGETS ? target(c->tgt, c->rt, c->w, c->h) : 0;
            if (!cur) {
                char d[256];
                snprintf(d, sizeof d, "target %u (rt %u) %u x %u: %s; %u KiB of CDRAM free (largest %u), %u of LPDDR",
                         c->tgt, c->rt, c->w, c->h, rt_why, heap_free_bytes(&vram) >> 10, heap_largest(&vram) >> 10,
                         heap_free_bytes(&tram) >> 10);
                skip(W_TARGET, d);
                break;
            }
            for (j = i + 1; j < rec.n && rec.call[j].op != KH1_GXM_END_SCENE; j++) ;
            if (j < rec.n) dstore = rec.call[j].dstore != KH1_STORE_DISCARD;
            /* session 137v: a scene that neither loads nor stores its depth (its draws do not test it, or only
             * against what they wrote) runs on the spare buffer, so the GS one's memory is not touched at all
             * (Dive's floor, drawn in the scene after one such, flickered in Vita3K) */
            z = depth_of(c->depth != KH1_DS_NONE && c->dload != KH1_LOAD_LOAD && !dstore ? KH1_DS_NONE : c->depth, c->w, c->h);
            if (!z) {
                char d[256];
                snprintf(d, sizeof d, "depth %u %u x %u; %u KiB of CDRAM free (largest %u), %u of LPDDR", c->depth, c->w,
                         c->h, heap_free_bytes(&vram) >> 10, heap_largest(&vram) >> 10, heap_free_bytes(&tram) >> 10);
                skip(W_DEPTH, d);
                cur = 0;
                break;
            }
            {   /* the pending uploads into this target, and into those its draws sample */
                int need = cur->pend;
                for (j = i + 1; j < rec.n && rec.call[j].op != KH1_GXM_END_SCENE; j++)
                    if (rec.call[j].op == KH1_GXM_SET_TEXTURE && rec.call[j].src && rec.call[j].src <= KH1_CMD_TARGETS &&
                        tgt[rec.call[j].src - 1].pend)
                        need = 1;
                if (need) pend_flush(0);
            }
            sceGxmDepthStencilSurfaceSetForceLoadMode(&z->surf, c->depth != KH1_DS_NONE && c->dload == KH1_LOAD_LOAD
                                                      ? SCE_GXM_DEPTH_STENCIL_FORCE_LOAD_ENABLED : SCE_GXM_DEPTH_STENCIL_FORCE_LOAD_DISABLED);
            sceGxmDepthStencilSurfaceSetForceStoreMode(&z->surf, c->depth != KH1_DS_NONE && dstore
                                                       ? SCE_GXM_DEPTH_STENCIL_FORCE_STORE_ENABLED : SCE_GXM_DEPTH_STENCIL_FORCE_STORE_DISABLED);
            {
                int err = sceGxmBeginScene(ctx, 0, cur->gxrt, 0, 0, 0, &cur->surf, &z->surf);
                if (err < 0) {
                    char d[64];
                    snprintf(d, sizeof d, "0x%08x, target %u %u x %u", (u32)err, c->tgt, c->w, c->h);
                    skip(W_SCENE, d);
                    cur = 0;
                    break;
                }
            }
            open = 1;
            zbound = c->depth != KH1_DS_NONE;
            scenes++;
            cur->drawn = 1;
            cur->used = ++scene_no;
            if (c->rt == KH1_RT_DISPLAY) display = c->tgt;
            /* target pixels to the window: the vertex shader's u_xf maps x to 2x / w - 1 (y down), z as is */
            sceGxmSetViewport(ctx, cur->w * 0.5f, cur->w * 0.5f, cur->h * 0.5f, cur->h * 0.5f, 0.0f, 1.0f);
            sceGxmSetCullMode(ctx, SCE_GXM_CULL_NONE);
            sceGxmSetTwoSidedEnable(ctx, SCE_GXM_TWO_SIDED_DISABLED);
            sceGxmSetFrontPointLineWidth(ctx, 1);
            sceGxmSetRegionClip(ctx, SCE_GXM_REGION_CLIP_OUTSIDE, 0, 0, cur->w - 1, cur->h - 1);
            xf = (const f32 *)(ub + c->uoff);
            pk = 0;
            fp = 0;
            have_tex = 0;
            break;
        }
        case KH1_GXM_END_SCENE:
            if (open) sceGxmEndScene(ctx, 0, 0);
            open = 0;
            cur = 0;
            break;
        case KH1_GXM_TEX_UPLOAD:
            tex_upload(c->slot, c->tex0_lo, c->tex0_hi);
            break;
        case KH1_GXM_PAL_FILL:
            if (c->slot >= 0 && c->slot < KH1_PALCACHE_SLOTS && kh1_pipes_frame_pal(c->slot))
                memcpy(pal[c->slot], kh1_pipes_frame_pal(c->slot), 1024);
            break;
        case KH1_GXM_PAL_READBACK: { /* the CLUT pass's 16 x 16 pixels as a palette: entries 8-15 / 16-23 of each 32 swapped */
            Target *s = c->src && c->src <= KH1_CMD_TARGETS ? &tgt[c->src - 1] : 0;
            u32 e, *o = (u32 *)pal_rb;
            if (!s || !s->mem) break;
            pend_flush(s);
            if (s->used > finish_seen) finish_at(2); /* session 150: not again for the next readback of the frame */
            for (e = 0; e < 256; e++) {
                u32 p = (e & 0xE7) | (e & 8) << 1 | (e & 0x10) >> 1, g;
                g = (p >> 4) < s->h && (p & 15) < s->w ? ((u32 *)s->mem)[(p >> 4) * s->stride + (p & 15)] : 0;
                o[e] = (g & 0xFFFFFF) | kh1_blend_load_alpha(g >> 24) << 24;
            }
            pal_rb_slot = (u32)c->slot;
            break;
        }
        case KH1_GXM_TARGET_UPLOAD: {
            Target *d = c->tgt && c->tgt <= KH1_CMD_TARGETS ? &tgt[c->tgt - 1] : 0;
            if (!d || !d->mem || !k) break;
            pend_add(d, r->tgt[c->tgt - 1], &k->x, c->dx, c->dy, c->w, c->h);
            break;
        }
        case KH1_GXM_BLIT: { /* target to target (GS memory on either side keeps the CPU model's bytes) */
            Target *s = c->src && c->src <= KH1_CMD_TARGETS ? &tgt[c->src - 1] : 0;
            Target *d = c->tgt && c->tgt <= KH1_CMD_TARGETS ? &tgt[c->tgt - 1] : 0;
            u32 y, w, sx, sy;
            if (!d || !d->mem || !k) break;
            if (!s || !s->mem) { pend_add(d, r->tgt[c->tgt - 1], &k->x, c->dx, c->dy, c->w, c->h); break; }
            pend_flush(0);
            finish_at(3);
            sx = k->x.sx;
            sy = k->x.sy;
            for (y = 0; y < c->h; y++) {
                if (sy + y >= s->h || c->dy + y >= d->h || sx >= s->w || c->dx >= d->w) continue;
                w = c->w;
                if (sx + w > s->w) w = s->w - sx;
                if (c->dx + w > d->w) w = d->w - c->dx;
                memmove((u32 *)d->mem + (c->dy + y) * d->stride + c->dx, (u32 *)s->mem + (sy + y) * s->stride + sx, w * 4);
            }
            break;
        }
        case KH1_GXM_SET_PROGRAMS:
            pk = c->pipe < rec.npipe ? &rec.pipe[c->pipe] : 0;
            vi = c->vert;
            fp = pk && vi < 7 ? prog_of(pk, vi, &fs) : 0;
            bad_pipe = !fp;
            if (fp) {
                sceGxmSetVertexProgram(ctx, vert[vi].vp);
                sceGxmSetFragmentProgram(ctx, fp);
                sceGxmSetFrontDepthFunc(ctx, !zbound || pk->ztest == KH1_ZTST_ALWAYS ? SCE_GXM_DEPTH_FUNC_ALWAYS
                                        : pk->ztest == KH1_ZTST_GEQUAL ? SCE_GXM_DEPTH_FUNC_GREATER_EQUAL
                                        : pk->ztest == KH1_ZTST_GREATER ? SCE_GXM_DEPTH_FUNC_GREATER : SCE_GXM_DEPTH_FUNC_NEVER);
                sceGxmSetFrontDepthWriteEnable(ctx, zbound && pk->zwrite ? SCE_GXM_DEPTH_WRITE_ENABLED : SCE_GXM_DEPTH_WRITE_DISABLED);
            }
            break;
        case KH1_GXM_SET_TEXTURE: {
            u32 w = 1u << (c->tex0_lo >> 26 & 15), h = 1u << ((c->tex0_lo >> 30 | c->tex0_hi << 2) & 15);
            const KH1Sampler *sm = k ? &k->d.sampler : 0;
            have_tex = 0;
            if (c->src) { /* a target's own pixels, read in place */
                Target *s = c->src <= KH1_CMD_TARGETS ? &tgt[c->src - 1] : 0;
                if (!s || !s->mem || s == cur) { /* feedback: the scene's own target (not sampled) */
                    snprintf(tex_why, sizeof tex_why, "target %u as a texture: %s", c->src,
                             !s || !s->mem ? "not made" : "the scene's own target");
                    break;
                }
                s->used = scene_no;
                if (c->wtex && s->w <= s->stride) w = s->w; /* wide screen: its whole width, as cmdbuf.c took its s */
                if (sceGxmTextureInitLinearStrided(&t, s->mem, SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ABGR, w, h, s->stride * 4) < 0) {
                    snprintf(tex_why, sizeof tex_why, "target %u as a %u x %u texture (stride %u): refused", c->src, w, h,
                             s->stride);
                    break;
                }
            } else {
                const TexMem *m = c->slot >= 0 && c->slot < KH1_TEXCACHE_SLOTS ? &tex[c->slot] : tex_loose(c->tex0_lo, c->tex0_hi);
                u32 fmt;
                if (!m || !m->mem || m->lo != c->tex0_lo || m->w != w || m->h != h) {
                    snprintf(tex_why, sizeof tex_why, "tex0 %08x%08x %u x %u (slot %d): %s", c->tex0_hi, c->tex0_lo, w, h,
                             c->slot, !m ? loose_why : !m->mem ? "not uploaded" : "the slot holds another");
                    break;
                }
                fmt = kh1_texfmt_of(m->psm);
                if (sceGxmTextureInitLinear(&t, m->mem, tex_format(fmt), w, h, 0) < 0) {
                    snprintf(tex_why, sizeof tex_why, "tex0 %08x%08x %u x %u psm %02x: sceGxmTextureInitLinear refused",
                             c->tex0_hi, c->tex0_lo, w, h, m->psm);
                    break;
                }
                if (fmt == KH1_TEXFMT_P8 || fmt == KH1_TEXFMT_P4) {
                    void *pp = c->pslot >= 0 && (u32)c->pslot == pal_rb_slot ? pal_rb
                               : c->pslot >= 0 && c->pslot < KH1_PALCACHE_SLOTS ? pal[c->pslot] : 0;
                    if (!pp) {
                        snprintf(tex_why, sizeof tex_why, "tex0 %08x%08x: no palette (slot %d)", c->tex0_hi, c->tex0_lo,
                                 c->pslot);
                        break;
                    }
                    sceGxmTextureSetPalette(&t, pp);
                }
            }
            if (sm) {
                SceGxmTextureFilter f = sm->linear ? SCE_GXM_TEXTURE_FILTER_LINEAR : SCE_GXM_TEXTURE_FILTER_POINT;
                sceGxmTextureSetMinFilter(&t, f);
                sceGxmTextureSetMagFilter(&t, f);
                sceGxmTextureSetUAddrMode(&t, sm->u.addr == KH1_ADDR_CLAMP ? SCE_GXM_TEXTURE_ADDR_CLAMP : SCE_GXM_TEXTURE_ADDR_REPEAT);
                sceGxmTextureSetVAddrMode(&t, sm->v.addr == KH1_ADDR_CLAMP ? SCE_GXM_TEXTURE_ADDR_CLAMP : SCE_GXM_TEXTURE_ADDR_REPEAT);
            }
            have_tex = 1;
            break;
        }
        case KH1_GXM_SET_REGION:
            if (cur && c->sx1 > c->sx0 && c->sy1 > c->sy0)
                sceGxmSetRegionClip(ctx, SCE_GXM_REGION_CLIP_OUTSIDE, (u32)c->sx0, (u32)c->sy0, (u32)c->sx1 - 1, (u32)c->sy1 - 1);
            break;
        case KH1_GXM_SET_UNIFORMS:
            u = (const f32 *)(ub + c->uoff);
            break;
        case KH1_GXM_DRAW: {
            static const SceGxmPrimitiveType prim[4] = { SCE_GXM_PRIMITIVE_TRIANGLES, SCE_GXM_PRIMITIVE_POINTS,
                                                         SCE_GXM_PRIMITIVE_LINES, SCE_GXM_PRIMITIVE_TRIANGLES };
            u32 per = c->cls == KH1_PA_TRIANGLES ? 3 : c->cls == KH1_PA_LINES ? 2 : 1, v0 = c->v0, left = c->nv;
            void *vb, *fb;
            if (!cur) { skip(W_NOSCENE, 0); break; }
            if (bad_pipe || !pk || !fp) { skip(W_PIPE, pk ? pipe_why : "no pipeline set"); break; }
            if (pk->shader.tex && pk->shader.setup != 2 && !have_tex) { skip(W_TEX, tex_why); break; }
            if ((u64)(v0 + left) * 32 > r->vring.head) { skip(W_RANGE, 0); break; }
            if (!u || !xf || c->cls == KH1_PA_NONE) { skip(W_STATE, 0); break; }
            if (pk->shader.tex && fs->tex >= 0) sceGxmSetFragmentTexture(ctx, (u32)fs->tex, &t);
            stencil(c->stencil);
            while (left) {
                u32 n = left > MAX_INDEX ? MAX_INDEX / per * per : left;
                sceGxmReserveVertexDefaultUniformBuffer(ctx, &vb);
                if (vert[vi].u_xf) sceGxmSetUniformDataF(vb, vert[vi].u_xf, 0, 4, xf);
                sceGxmReserveFragmentDefaultUniformBuffer(ctx, &fb);
                {
                    u32 q;
                    for (q = 0; q < 4; q++)
                        if (fs->u[q]) sceGxmSetUniformDataF(fb, fs->u[q], 0, 4, u + q * 4);
                    if (fs->u[4]) sceGxmSetUniformDataF(fb, fs->u[4], 0, 4, xf);
                }
                sceGxmSetVertexStream(ctx, 0, vbuf + v0 * 32);
                sceGxmDraw(ctx, prim[c->cls & 3], SCE_GXM_INDEX_FORMAT_U16, index_buf, n);
                v0 += n;
                left -= n;
            }
            draws++;
            break;
        }
        }
        kh1_vita_us_part[part] += (u32)(sceKernelGetProcessTimeWide() - t1);
    }
    if (open) sceGxmEndScene(ctx, 0, 0);
    if (display >= 0 && tgt[display].pend) pend_flush(&tgt[display]); /* the present reads it; the rest wait for
                                                                      * the next frame's start */
    frames++;
    kh1_vita_us_gpu += (u32)(sceKernelGetProcessTimeWide() - t0);
}

/* session 136: the display target copied (by the GPU, after the frame's scenes) into its own surface at a
 * frame copy, so the present shows a whole picture; until the first one the display target itself */
static Target shown_tgt;
static f32 *latch_v; /* the copy's quad (LPDDR) */
static int latched;
void kh1_vita_gxm_latch(void) {
    Target *d = display >= 0 ? &tgt[display] : 0, *s = &shown_tgt;
    SceGxmTexture t;
    if (!ready || !d || !d->mem || !latch_v) return;
    if (!s->mem || s->w != d->w || s->h != d->h) {
        if (s->mem) heap_free(s->heap, s->mem, s->bytes);
        memset(s, 0, sizeof *s);
        s->w = d->w;
        s->h = d->h;
        s->stride = d->stride;
        s->bytes = s->stride * 4 * s->h;
        s->mem = (u8 *)surface_alloc(s->bytes, &s->heap);
        if (!s->mem) return;
        if (sceGxmColorSurfaceInit(&s->surf, SCE_GXM_COLOR_FORMAT_A8B8G8R8, SCE_GXM_COLOR_SURFACE_LINEAR,
                                   SCE_GXM_COLOR_SURFACE_SCALE_NONE, SCE_GXM_OUTPUT_REGISTER_SIZE_32BIT, s->w, s->h,
                                   s->stride, s->mem) < 0) {
            heap_free(s->heap, s->mem, s->bytes);
            s->mem = 0;
            return;
        }
    }
    if (!(s->gxrt = rt_of(s->w, s->h))) return;
    {   /* clip y -1 is row 0 under the frame's viewport (y down); texel centres line up, point sampled */
        f32 u1 = (f32)d->w / (f32)d->stride;
        f32 q[16] = { -1, -1, 0, 0, 1, -1, u1, 0, -1, 1, 0, 1, 1, 1, u1, 1 };
        memcpy(latch_v, q, sizeof q);
    }
    if (sceGxmBeginScene(ctx, 0, s->gxrt, 0, 0, 0, &s->surf, 0) < 0) return;
    sceGxmTextureInitLinearStrided(&t, d->mem, SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ABGR, d->stride, d->h, d->stride * 4);
    sceGxmTextureSetMinFilter(&t, SCE_GXM_TEXTURE_FILTER_POINT);
    sceGxmTextureSetMagFilter(&t, SCE_GXM_TEXTURE_FILTER_POINT);
    sceGxmSetViewport(ctx, (f32)s->w * 0.5f, (f32)s->w * 0.5f, (f32)s->h * 0.5f, (f32)s->h * 0.5f, 0.0f, 1.0f);
    sceGxmSetRegionClip(ctx, SCE_GXM_REGION_CLIP_NONE, 0, 0, s->w - 1, s->h - 1);
    sceGxmSetFrontDepthFunc(ctx, SCE_GXM_DEPTH_FUNC_ALWAYS);
    sceGxmSetFrontDepthWriteEnable(ctx, SCE_GXM_DEPTH_WRITE_DISABLED);
    stencil(0);
    sceGxmSetVertexProgram(ctx, pv);
    sceGxmSetFragmentProgram(ctx, pf);
    sceGxmSetFragmentTexture(ctx, 0, &t);
    sceGxmSetVertexStream(ctx, 0, latch_v);
    sceGxmDraw(ctx, SCE_GXM_PRIMITIVE_TRIANGLE_STRIP, SCE_GXM_INDEX_FORMAT_U16, index_buf, 4);
    sceGxmEndScene(ctx, 0, 0);
    latched = 1;
}

/* the display target into vita2d's open scene: the 4:3 picture over the canvas's rectangle (screen pixels) */
int kh1_vita_gxm_present(f32 x, f32 y, f32 w, f32 h) {
    Target *d = latched ? &shown_tgt : display >= 0 ? &tgt[display] : 0;
    SceGxmTexture t;
    f32 *v;
    if (!ready || !d || !d->mem) return 0;
    v = (f32 *)vita2d_pool_memalign(4 * 16, 16);
    if (!v) return 0;
    {   /* screen pixels to clip space under GXM's default viewport (y up), the texture's rows 0 .. h */
        f32 x0 = x / 480.0f - 1.0f, x1 = (x + w) / 480.0f - 1.0f, y0 = 1.0f - y / 272.0f, y1 = 1.0f - (y + h) / 272.0f;
        f32 u1 = (f32)d->w / (f32)d->stride, v1 = 1.0f;
        f32 q[16] = { x0, y0, 0, 0, x1, y0, u1, 0, x0, y1, 0, v1, x1, y1, u1, v1 };
        memcpy(v, q, sizeof q);
    }
    sceGxmTextureInitLinearStrided(&t, d->mem, SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ABGR, d->stride, d->h, d->stride * 4);
    sceGxmTextureSetMinFilter(&t, SCE_GXM_TEXTURE_FILTER_LINEAR);
    sceGxmTextureSetMagFilter(&t, SCE_GXM_TEXTURE_FILTER_LINEAR);
    sceGxmTextureSetUAddrMode(&t, SCE_GXM_TEXTURE_ADDR_CLAMP);
    sceGxmTextureSetVAddrMode(&t, SCE_GXM_TEXTURE_ADDR_CLAMP);
    sceGxmSetViewport(ctx, 480.0f, 480.0f, 272.0f, -272.0f, 0.5f, 0.5f);
    sceGxmSetRegionClip(ctx, SCE_GXM_REGION_CLIP_NONE, 0, 0, 959, 543);
    sceGxmSetFrontDepthFunc(ctx, SCE_GXM_DEPTH_FUNC_ALWAYS);
    sceGxmSetFrontDepthWriteEnable(ctx, SCE_GXM_DEPTH_WRITE_DISABLED);
    stencil(0);
    sceGxmSetVertexProgram(ctx, pv);
    sceGxmSetFragmentProgram(ctx, pf);
    sceGxmSetFragmentTexture(ctx, 0, &t);
    sceGxmSetVertexStream(ctx, 0, v);
    sceGxmDraw(ctx, SCE_GXM_PRIMITIVE_TRIANGLE_STRIP, SCE_GXM_INDEX_FORMAT_U16, index_buf, 4);
    return 1;
}

int kh1_vita_gxm_ready(void) { return ready; }

/* a target's pixels for a check (tools/vita/gxmcheck.sh): the last one of port kind rt, its size and stride */
const void *kh1_vita_gxm_target(u32 rt, u32 *w, u32 *h, u32 *stride) {
    s32 i;
    for (i = KH1_CMD_TARGETS - 1; i >= 0; i--)
        if (tgt[i].mem && tgt[i].drawn && tgt[i].rt == rt) {
            *w = tgt[i].w;
            *h = tgt[i].h;
            *stride = tgt[i].stride;
            return tgt[i].mem;
        }
    return 0;
}

void kh1_vita_gxm_stats(u32 *f, u32 *d, u32 *s, u32 *sc) {
    *f = frames;
    *d = draws;
    *s = skipped;
    *sc = scenes;
}

/* config.txt's shadertest=1 (session 137v): which part of the REGION_REPEAT shader that stops SceShaccCg
 * ("fatal internal error") does it.  The failing key and its neighbours (each field put back one at a time),
 * then the failing text with each body line left out in turn: a line whose removal compiles is one the
 * failure needs.  Each result goes to the log as "kh1-gxm: shadertest ..." */
int kh1_vita_shadertest;
static int test_compile(const char *t, u32 len) {
    u32 size = len;
    SceGxmProgram *c = shark_compile_shader_extended(t, &size, SHARK_FRAGMENT_SHADER, SHARK_OPT_DEFAULT, SHARK_DISABLE,
                                                     SHARK_DISABLE, SHARK_DISABLE);
    int ok = c && size;
    shark_clear_output();
    return ok;
}
static void shadertest(void) {
    static char base[KH1_SHADER_TEXT], t[KH1_SHADER_TEXT];
    static const char *what[] = { "the failing key", "no fog", "no discard", "u plain", "v plain", "uv (no divide)",
                                  "rgba8", "no tcc", "discard gequal", "discard-pass", "u only (no fog)",
                                  "u only (no discard)", "no fog, no discard" };
    KH1ShaderKey k0, k;
    u32 i, len, n;
    memset(&k0, 0, sizeof k0);
    k0.tex = KH1_TEXFMT_P8;
    k0.tcc = 1;
    k0.fog = 1;
    k0.pre_a = 2;
    k0.pre_d = 3;
    k0.discard = KH1_DISCARD_FAIL;
    k0.atst = KH1_ATST_GREATER;
    k0.su = k0.sv = KH1_SHADER_TAPS;
    for (i = 0; i < sizeof what / sizeof *what; i++) {
        k = k0;
        switch (i) {
        case 1: k.fog = 0; break;
        case 2: k.discard = 0, k.atst = 0; break;
        case 3: k.su = KH1_SHADER_NONE; break;
        case 4: k.sv = KH1_SHADER_NONE; break;
        case 5: k.fst = 1; break;
        case 6: k.tex = KH1_TEXFMT_RGBA8; break;
        case 7: k.tcc = 0; break;
        case 8: k.atst = KH1_ATST_GEQUAL; break;
        case 9: k.discard = KH1_DISCARD_PASS; break;
        case 10: k.sv = KH1_SHADER_NONE, k.fog = 0; break;
        case 11: k.sv = KH1_SHADER_NONE, k.discard = 0, k.atst = 0; break;
        case 12: k.fog = 0, k.discard = 0, k.atst = 0; break;
        }
        len = kh1_shader_frag_cg(&k, t, sizeof t);
        kh1_vita_log("kh1-gxm: shadertest key %u (%s): %s\n", i, what[i], !len ? "not generated" : test_compile(t, len) ? "ok" : "FAIL");
    }
    len = kh1_shader_frag_cg(&k0, base, sizeof base);
    if (!len) return;
    { /* rewrites of the failing text: the region's wrap by frac, the fog and the region apart in registers */
        static const char *rw[][2][3] = {
            { { "    r5.x = floor(r1.x * u_r.x);\n    r1.x = r5.x * u_r.y + r1.x;\n",
                "    r5.y = floor(r1.y * u_r.z);\n    r1.y = r5.y * u_r.w + r1.y;\n", 0 },
              { "    r1.x = frac(r1.x * u_r.x) * -u_r.y;\n", "    r1.y = frac(r1.y * u_r.z) * -u_r.w;\n", 0 } },
            { { "    r5.x = floor(r1.x * u_r.x);\n    r1.x = r5.x * u_r.y + r1.x;\n",
                "    r5.y = floor(r1.y * u_r.z);\n    r1.y = r5.y * u_r.w + r1.y;\n", 0 },
              { "    r3.x = floor(r1.x * u_r.x);\n    r1.x = r3.x * u_r.y + r1.x;\n",
                "    r3.y = floor(r1.y * u_r.z);\n    r1.y = r3.y * u_r.w + r1.y;\n", 0 } },
            { { "    r1.x = r1.x + u_c.z;\n    r5.y", "    r1.y = r1.y + u_c.w;\n", 0 },
              { "    r5.y", "", 0 } },
            { { "    r2 = tex2D(tex, r1.xy);\n", 0, 0 }, { "    r2 = tex2D(tex, r1.xy + float2(0.0, 0.0));\n", 0, 0 } },
        };
        static const char *rwn[] = { "the wrap by frac", "the region in r3", "no FIX offsets", "tex2D on an expression" };
        for (i = 0; i < sizeof rw / sizeof *rw; i++) {
            u32 j, bad = 0;
            memcpy(t, base, len + 1);
            for (j = 0; j < 3 && rw[i][0][j]; j++) {
                char *a = strstr(t, rw[i][0][j]);
                u32 la = (u32)strlen(rw[i][0][j]), lb = (u32)strlen(rw[i][1][j]), lt = (u32)strlen(t);
                if (!a || lt - la + lb + 1 > sizeof t) { bad = 1; break; }
                memmove(a + lb, a + la, lt - (u32)(a - t) - la + 1);
                memcpy(a, rw[i][1][j], lb);
            }
            kh1_vita_log("kh1-gxm: shadertest rewrite %u (%s): %s\n", i, rwn[i], bad ? "did not apply"
                         : test_compile(t, (u32)strlen(t)) ? "ok" : "FAIL");
        }
    }
    {
        const char *body = strstr(base, "{\n"), *p;
        u32 lines = 0;
        if (!body) return;
        body += 2;
        for (p = body; *p; p++) lines += *p == '\n';
        for (n = 0; n + 2 < lines; n++) { /* each body line but the closing brace */
            const char *a = body, *b;
            u32 j, m;
            for (j = 0; j < n; j++) a = strchr(a, '\n') + 1;
            b = strchr(a, '\n') + 1;
            m = (u32)(a - base);
            memcpy(t, base, m);
            memcpy(t + m, b, len - (u32)(b - base) + 1);
            kh1_vita_log("kh1-gxm: shadertest without line %u (%.*s): %s\n", n, (int)(b - a - 1), a,
                         test_compile(t, (u32)strlen(t)) ? "ok" : "FAIL");
        }
    }
}

/* the compiler, the shaders the frame needs before any draw (the vertex variants, the present's pair), the
 * GPU memory.  0 when the GPU path can run */
int kh1_vita_shacc_ext = 1; /* config.txt's shacc_ext= (main.c) */
int kh1_vita_shacc_restart; /* config.txt's shacc_restart= (main.c) */
int kh1_vita_gxm_init(void) {
    u32 i;
    ctx = vita2d_get_context();
    patcher = vita2d_get_shader_patcher();
    if (!ctx || !patcher) return -1;
    sceIoMkdir(SHADER_DIR, 0777);
    /* session 136: SceShaccCgExt's extensions (the Vita's own Cg: __nativecolor, the frame reads) where they
     * load, else the plain compiler (Vita3K's; the frame reads get unfetch's stand-ins) */
    if (kh1_vita_shacc_ext && shark_init(0) >= 0) shark_ok = 2;
    else shark_ok = shark_init_simple(0) >= 0;
    kh1_vita_log("kh1-gxm: shader compiler %s\n", shark_ok == 2 ? "loaded with its extensions (ur0:data/libshacccg.suprx)"
                 : shark_ok ? "loaded without its extensions (ur0:data/libshacccg.suprx; no frame reads)"
                 : "not loaded: only shaders already in " SHADER_DIR " can be used");
    if (kh1_vita_shadertest && shark_ok) shadertest();
    for (i = 1; i < 7; i++)
        if (vert_load(i)) {
            kh1_vita_log("kh1-gxm: vertex shader %u (%s) unavailable: the software picture stays\n", i, kh1_vertkey_str(i));
            return -1;
        }
    vert_load(0); /* DATE's set-up variant: its draws are skipped without it */
    if (present_load()) {
        kh1_vita_log("kh1-gxm: the present's shaders unavailable: the software picture stays\n");
        return -1;
    }
    if (heap_init(&vram, SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW, 48u << 20) ||
        heap_init(&tram, SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE, 32u << 20)) {
        kh1_vita_log("kh1-gxm: no GPU memory: the software picture stays\n");
        return -1;
    }
    vbuf_bytes = KH1_RING_VERTEX_BYTES;
    vbuf = (u8 *)heap_alloc(&tram, vbuf_bytes);
    index_buf = (u16 *)heap_alloc(&tram, 64000 * 2);
    latch_v = (f32 *)heap_alloc(&tram, 16 * sizeof(f32));
    pal_rb = heap_alloc(&tram, 1024);
    for (i = 0; i < KH1_PALCACHE_SLOTS; i++) pal[i] = heap_alloc(&tram, 1024);
    if (!vbuf || !index_buf || !pal_rb || !pal[KH1_PALCACHE_SLOTS - 1]) return -1;
    for (i = 0; i < 64000; i++) index_buf[i] = (u16)i;
    kh1_gxm_clear(&rec);
    ready = 1;
    kh1_vita_log("kh1-gxm: ready: %u shaders compiled now, %u from the cache\n", compiled, cached);
    return 0;
}
