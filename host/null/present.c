/* KH1_HOST_SHOT (session 94, docs/vita-port-plan.md 5.1ah, renderer-spec 5.4 "Session 94"): a host
 * "present".  After each frame copy (brightfade.c's D_002A6890 send: the 3D target to the display) the
 * GS memory model's display buffer (the copy's FRAME), or with the target source the 3D target (the
 * copy's TEX0), is written as a W x H PAM through the canvas map (include/platform/canvas.h): the 4:3
 * canvas scaled to the screen's height and centred, point-sampled, black where the model has no pixel
 * (the pillarbox, and under KH1_HOST_WIDE the view's sides: the model's buffers are the PS2's 512
 * wide).  The display's 448 lines are the canvas's 384 (NTSC's taller pixels).  Session 97: under
 * KH1_HOST_WIDE (kh1_present_wide) the shot line says so; the display's copy is stretched (u from the
 * view's left edge, host/port/fullscreen.c), and since session 99 the model reads it back by the margin
 * (host/null/gsregs.c), so the display's pixel d holds canvas d as the target's does and both shots
 * are read as they are (renderer-spec 5.4 "Session 97" / "Session 99").
 *
 * The model holds what uploads, copies and the point-sampled sprites it can draw (host/null/gsmem.c)
 * wrote, and since session 95 the untextured sprites (the clears, the display clear, fade and
 * letterbox: kh1_gsmem_flat, turned on here, which leaves every trace counter as it was), and since
 * session 96 the textured sprites the exact model refuses, point-sampled (the frame copy itself: the
 * display shows what the 3D target holds), not the 3D, so on the fake disc a frame shows the clears' colours only; the
 * picture is for the real disc's run and for a renderer's bring-up to compare with.  Frames from the user's disc: never commit them.  Not part of the PS2 build. */
#include "common.h"
#include "gsregs.h"
#include "gsmem.h"
#include "dmawalk.h"
#include "platform/canvas.h"
#include "platform/palcache.h"
#include "platform/texcache.h"
#include "present.h"

void *fopen(const char *, const char *);
int fclose(void *);
int fprintf(void *, const char *, ...);
__SIZE_TYPE__ fwrite(const void *, __SIZE_TYPE__, __SIZE_TYPE__, void *);
int sprintf(char *, const char *, ...);
int printf(const char *, ...);
void *malloc(__SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);
unsigned long kh1_host_frame(void);

/* a buffer's pixel as RGB (R in bits 0-7): CT32 / CT24 as stored, CT16 / CT16S widened */
static u32 rgb_of(u32 psm, u32 v) {
    if (psm == KH1_PSMCT16 || psm == KH1_PSMCT16S)
        return (v & 0x1F) << 3 | (v >> 5 & 0x1F) << 11 | (v >> 10 & 0x1F) << 19;
    return v & 0xFFFFFF;
}

/* the buffer's pixel for canvas x is its column x (session 99: also under the wide view) */
static int present_rgb(u8 *rgb, s32 w, s32 h, u32 psm, u32 bp, u32 bw, u32 lines) {
    KH1Canvas c;
    s32 x, y;
    f32 cx, cy;
    if (psm != KH1_PSMCT32 && psm != KH1_PSMCT24 && psm != KH1_PSMCT16 && psm != KH1_PSMCT16S) return -1;
    if (!bw || !lines) return -1;
    kh1_canvas_fit(&c, (f32)w, (f32)h);
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) {
            u8 *o = rgb + (y * w + x) * 3;
            u32 v = 0;
            /* the pixel's centre, back to the canvas */
            kh1_canvas_unmap(&c, (f32)x + 0.5f, (f32)y + 0.5f, &cx, &cy);
            if (cx >= 0.0f && cx < 512.0f && cx < (f32)(bw * 64) && cy >= 0.0f && cy < 384.0f)
                v = rgb_of(psm, kh1_gsmem_read_pixel(psm, bp, bw, (u32)cx, (u32)(cy * (f32)lines / 384.0f)));
            o[0] = v;
            o[1] = v >> 8;
            o[2] = v >> 16;
        }
    return 0;
}

int kh1_present_rgb(u8 *rgb, s32 w, s32 h, u32 psm, u32 bp, u32 bw, u32 lines) {
    return present_rgb(rgb, w, h, psm, bp, bw, lines);
}

static s32 shot_w, shot_h, shot_target, shot_side16;
static const char *shot_dir;
static u32 shot_send, shot_n;
static u8 *shot_rgb;

static void present_after(u32 tadr) {
    const KH1GsState *s = kh1_gs_state();
    const KH1GsReg *r = shot_target ? &s->ctx[0].tex0 : &s->ctx[0].frame;
    u32 bp, bw, psm;
    char path[512], wide[160];
    void *f;
    if (tadr != shot_send) return;
    if (shot_target) { /* TEX0: TBP0, TBW, PSM */
        bp = r->lo & 0x3FFF;
        bw = r->lo >> 14 & 63;
        psm = r->lo >> 20 & 63;
    } else { /* FRAME: FBP (2048-word pages), FBW, PSM */
        bp = (r->lo & 0x1FF) * 32;
        bw = r->lo >> 16 & 63;
        psm = r->lo >> 24 & 63;
    }
    wide[0] = 0;
    /* session 99: the model reads its stretched copies back by the margin (host/null/gsregs.c), so the
     * display holds canvas 0 at pixel 0 like the target and both shots are read as they are */
    if (shot_side16)
        sprintf(wide, "; wide: the view's sides black, the model's buffers are the PS2's 512 (a renderer's come from the wide 3D)");
    if (present_rgb(shot_rgb, shot_w, shot_h, psm, bp, bw, shot_target ? 384 : 448)) {
        printf("kh1-host: shot frame %lu: psm %02x bw %u not presentable\n", kh1_host_frame(), psm, bw);
        return;
    }
    sprintf(path, "%.400s/shot_%05u.pam", shot_dir, shot_n++);
    f = fopen(path, "wb");
    if (!f) {
        printf("kh1-host: shot frame %lu: %s: cannot write\n", kh1_host_frame(), path);
        return;
    }
    fprintf(f, "P7\nWIDTH %d\nHEIGHT %d\nDEPTH 3\nMAXVAL 255\nTUPLTYPE RGB\nENDHDR\n", shot_w, shot_h);
    fwrite(shot_rgb, 3, (__SIZE_TYPE__)shot_w * shot_h, f);
    fclose(f);
    printf("kh1-host: shot frame %lu: %s (%s bp %04x bw %u psm %02x; %u flat, %u textured sprites so far%s)\n",
           kh1_host_frame(), path, shot_target ? "target" : "display", bp, bw, psm, kh1_gsmem_stats()->flat_sprites,
           kh1_gsmem_stats()->tex_sprites, wide);
}

void kh1_present_wide(s32 side16) { shot_side16 = side16; }

int kh1_present_init(s32 w, s32 h, int target, const char *dir, const void *send) {
    if (w <= 0 || h <= 0 || w > 4096 || h > 4096) return -1;
    shot_rgb = malloc((__SIZE_TYPE__)w * h * 3);
    if (!shot_rgb) return -1;
    shot_w = w;
    shot_h = h;
    shot_target = target;
    shot_dir = dir;
    shot_send = (u32)(unsigned long)send;
    kh1_dma_after_send = present_after;
    kh1_gsmem_flat(1); /* session 95: the clears, fades and letterbox filled into the model */
    kh1_present_pal(1); /* session 117: the indexed decodes through the port's palette cache */
    kh1_present_tex(1); /* session 118: the textured sprites' texels through the port's texture cache */
    return 0;
}

/* Session 117 (vita-port-plan 5.1be, renderer-spec 4.13 "Session 117"): the port's palette cache
 * (host/port/palcache.c) in the present.  At each CLUT load (kh1_gsmem_clut_loaded) the entries the
 * load's TEX0 reads (kh1_gsmem_clut, with TEXA as the register file holds it) are looked up and the
 * slot kept as the load's; the model's indexed decodes (kh1_gsmem_palette: the point-sampled sprites
 * and the present's textured sprites) read the texel's index in the slot's palette: the load's slot
 * when the draw's entries are the same (no second count), otherwise a lookup of its own (CLD 0 with
 * another CSA, a TEXA change for a CT16 CLUT).  A slot is a copy of kh1_gsmem_clut's words, so the
 * pixels are the same with the cache as without (tests/host/present_test.c).  Each frame
 * (kh1_host_frame) is the cache's frame; the counts are what a Vita renderer would upload: a fill is
 * one palette upload, a hit none, a full one drawn uncached.  KH1_HOST_SHOT turns it on, and
 * KH1_HOST_COUNTS=1 (host/null/main.c), whose report prints them at the end. */
static KH1PalCache pal_c;
static int pal_on, pal_cur = -1;
static u32 pal_buf[256], pal_loads, pal_draws, pal_frames, pal_fills_now, pal_fills_max;
static unsigned long pal_frame, pal_max_at;

/* the fills of the frame pal_frame into the high-water mark */
static void pal_mark(void) {
    if (pal_fills_now > pal_fills_max) { pal_fills_max = pal_fills_now; pal_max_at = pal_frame; }
}

/* a lookup in frame kh1_host_frame(): a new frame for the cache when it moved (pal_frames: frames
 * with a lookup) */
static void pal_tick(void) {
    unsigned long f = kh1_host_frame();
    if (pal_frames && f == pal_frame) return;
    if (pal_frames) {
        pal_mark();
        kh1_palcache_frame(&pal_c);
    }
    pal_fills_now = 0;
    pal_frame = f;
    pal_frames++;
}

static int pal_get(u32 n) {
    int fill, i = kh1_palcache_get(&pal_c, pal_buf, n, &fill);
    pal_fills_now += fill;
    return i;
}

static void pal_loaded(u32 lo, u32 hi) {
    const KH1GsState *s = kh1_gs_state();
    u32 n = (u32)kh1_gsmem_clut(lo, hi, s->texa.lo, s->texa.hi, pal_buf);
    pal_tick();
    pal_loads++;
    pal_cur = n ? pal_get(n) : -1;
}

static const u32 *pal_for(u32 lo, u32 hi, u32 texa_lo, u32 texa_hi) {
    u32 n = (u32)kh1_gsmem_clut(lo, hi, texa_lo, texa_hi, pal_buf);
    const KH1PalSlot *t;
    if (!n) return 0;
    pal_tick();
    t = pal_cur >= 0 ? &pal_c.slot[pal_cur] : 0;
    if (t && t->n == n && memcmp(t->col, pal_buf, n * 4) == 0) return t->col;
    pal_draws++;
    pal_cur = pal_get(n);
    return pal_cur >= 0 ? pal_c.slot[pal_cur].col : 0;
}

void kh1_present_pal(int on) {
    pal_on = on;
    kh1_gsmem_clut_loaded = on ? pal_loaded : 0;
    kh1_gsmem_palette = on ? pal_for : 0;
    if (!on) return;
    kh1_palcache_init(&pal_c);
    pal_cur = -1;
    pal_loads = pal_draws = pal_frames = pal_fills_now = pal_fills_max = 0;
    pal_frame = pal_max_at = 0;
}

const KH1PalCache *kh1_present_pal_cache(void) { return pal_on ? &pal_c : 0; }

void kh1_present_pal_report(void) {
    if (!pal_on) return;
    pal_mark(); /* the last frame's fills */
    printf("kh1-host: palette cache: %u CLUT loads and %u other draw lookups in %u frames with one: %u hits, %u fills, "
           "%u uncached (every slot in use); at most %u fills in a frame (frame %lu), %.2f a frame\n",
           pal_loads, pal_draws, pal_frames, pal_c.hits, pal_c.misses, pal_c.full, pal_fills_max, pal_max_at,
           pal_frames ? (double)pal_c.misses / pal_frames : 0.0);
}

/* Session 118 (vita-port-plan 5.1bf, renderer-spec 4.13 "Session 118"): the port's texture cache
 * (host/port/texcache.c) in the present.  Each textured sprite the model draws (kh1_gsmem_texels)
 * looks its TEX0 up with the page stamp (kh1_gsmem_tex_stamp) and the render target its pages hold
 * (kh1_gsmem_tex_target: the frame copy's 3D target, a pass at 0x3A00 read back after its draw), and
 * reads the stored texels the cache keeps; a target's texture is the GPU's own (0: the model reads
 * GS memory, as before).  The texels are GS memory's, so the pixels are the same with the cache as
 * without (tests/host/present_test.c).  The counts are what a Vita renderer would do: a stamp hit
 * reads nothing, a hash hit reads and hashes the texels, a decode is one GPU texture upload. */
static KH1TexCache tex_c;
static int tex_on;
static u32 tex_frames, tex_hashed_now, tex_decoded_now, tex_hashed_max, tex_decoded_max;
static unsigned long tex_frame, tex_hmax_at, tex_dmax_at;

static void tex_mark(void) {
    u32 h = tex_c.hashed - tex_hashed_now, d = tex_c.decoded - tex_decoded_now;
    if (h > tex_hashed_max) { tex_hashed_max = h; tex_hmax_at = tex_frame; }
    if (d > tex_decoded_max) { tex_decoded_max = d; tex_dmax_at = tex_frame; }
}

static void tex_tick(void) {
    unsigned long f = kh1_host_frame();
    if (tex_frames && f == tex_frame) return;
    if (tex_frames) {
        tex_mark();
        kh1_texcache_frame(&tex_c);
    }
    tex_hashed_now = tex_c.hashed; /* the counts at the frame's start */
    tex_decoded_now = tex_c.decoded;
    tex_frame = f;
    tex_frames++;
}

static void tex_read(u32 lo, u32 hi, u32 *out, void *ctx) {
    u32 w = 1u << (lo >> 26 & 15), h = 1u << ((lo >> 30 | hi << 2) & 15), x, y;
    (void)ctx;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) out[y * w + x] = kh1_gsmem_read_pixel(lo >> 20 & 63, lo & 0x3FFF, lo >> 14 & 63, x, y);
}

static const u32 *tex_for(u32 lo, u32 hi) {
    int decoded;
    tex_tick();
    return kh1_texcache_get(&tex_c, lo, hi, kh1_gsmem_tex_stamp(lo, hi), kh1_gsmem_tex_target(lo, hi), tex_read, 0,
                            &decoded);
}

void kh1_present_tex(int on) {
    tex_on = on && kh1_texcache_init(&tex_c) == 0;
    if (!on) kh1_texcache_free(&tex_c);
    kh1_gsmem_texels = tex_on ? tex_for : 0;
    tex_frames = tex_hashed_now = tex_decoded_now = tex_hashed_max = tex_decoded_max = 0;
    tex_frame = tex_hmax_at = tex_dmax_at = 0;
}

const KH1TexCache *kh1_present_tex_cache(void) { return tex_on ? &tex_c : 0; }

void kh1_present_tex_report(void) {
    if (!tex_on) return;
    if (tex_frames) tex_mark(); /* the last frame's */
    printf("kh1-host: texture cache: %u textured draws in %u frames with one: %u stamp hits, %u hash hits, "
           "%u decodes, %u render targets (not kept), %u not kept (full); texels hashed %u (at most %u in a frame, "
           "frame %lu), decoded %u (at most %u in a frame, frame %lu, %.0f a frame); %u texels held\n",
           tex_c.draws, tex_frames, tex_c.stamp_hits, tex_c.hash_hits, tex_c.decodes, tex_c.targets, tex_c.full,
           tex_c.hashed, tex_hashed_max, tex_hmax_at, tex_c.decoded, tex_decoded_max, tex_dmax_at,
           tex_frames ? (double)tex_c.decoded / tex_frames : 0.0, tex_c.texels);
}
