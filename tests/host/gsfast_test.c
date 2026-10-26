/* Session 135: the GS memory model's fast paths (host/null/gsmem.c: the address tables, the clear,
 * copy and cached-art loops, tex_scan's memo, kh1_gsmem_read_rect) against the model with them off
 * (kh1_gsmem_fast(0): every pixel's address computed, every pixel through the general loop), on
 * made-up pixels (no game data): random sprites of the shapes the title draws (its clears, the frame
 * copy's 16 strips, blended art from the texture and palette caches) and of every other shape, each
 * from the same starting memory both ways; the whole 4 MB must come out the same, and the sprite's
 * answer and the counters with it.  tests/selftest.sh builds it with gcc -m32 when that works. */
#include "common.h"
#include "../../host/null/gsmem.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);

static int fails;
#define CHECK(name, cond) do { if (!(cond)) { printf("gsfast_test: %s\n", name); fails++; } } while (0)

static u32 rs;
static u32 R(void) { rs = rs * 1103515245u + 12345u; return rs >> 8 ^ rs << 13; }

/* the present's caches as host/null/present.c keeps them: the texels as GS memory holds them at the
 * draw (the index for an indexed PSM), the palette as kh1_gsmem_clut gives it */
static u32 tex_buf[1024 * 1024], pal_buf[256];
static const u32 *texels(u32 lo, u32 hi) {
    u32 w = 1u << (lo >> 26 & 15), h = 1u << ((lo >> 30 | hi << 2) & 15), x, y;
    (void)hi;
    if (kh1_gsmem_tex_target(lo, hi)) return 0;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) tex_buf[y * w + x] = kh1_gsmem_read_pixel(lo >> 20 & 63, lo & 0x3FFF, lo >> 14 & 63, x, y);
    return tex_buf;
}
static const u32 *palette(u32 lo, u32 hi, u32 texa_lo, u32 texa_hi) {
    return kh1_gsmem_clut(lo, hi, texa_lo, texa_hi, pal_buf) ? pal_buf : 0;
}

static const u32 fpsms[] = { KH1_PSMCT32, KH1_PSMCT24, KH1_PSMCT16, KH1_PSMCT16S, KH1_PSMCT32, KH1_PSMCT24 };
static const u32 tpsms[] = { KH1_PSMCT32, KH1_PSMCT24, KH1_PSMCT16, KH1_PSMCT16S, KH1_PSMT8, KH1_PSMT4,
                             KH1_PSMT8H, KH1_PSMT4HL, KH1_PSMT4HH, KH1_PSMZ32, KH1_PSMZ24 };

/* a sprite; shape 0 any, 1 the clear / copy / art shapes */
static void make(KH1GsSprite *s, int shape) {
    u32 tw, th, i, fbw;
    memset(s, 0, sizeof *s);
    s->prim = 6 | (R() & 1) << 4 | 0x100 | (R() & 1) << 6 | (R() % 8 == 0) << 5;
    fbw = R() % 8 ? 1 + R() % 16 : 0;
    s->frame_lo = (R() % 512) | fbw << 16 | fpsms[R() % 6] << 24;
    s->frame_hi = R() % 4 ? 0 : R() & 1 ? 0xFF000000u : R();
    tw = R() % 11;
    th = R() % 11;
    if (R() & 1) { tw = R() % 7; th = R() % 7; }
    s->tex0_lo = (R() & 0x3FFF) | (1 + R() % 16) << 14 | tpsms[R() % 11] << 20 | tw << 26 | th << 30;
    s->tex0_hi = th >> 2 | (R() & 1) << 2 | (R() % 6 ? R() % 2 : 2) << 3 | (R() % 0x4000) << 5 |
                 (R() % 3 == 0 ? 0 : R() % 2 ? 2 : 10) << 19 | (R() % 2 ? 0 : R() % 32) << 24 | (R() % 4 == 0) << 29;
    s->tex1_lo = R() % 8 ? 0 : 0x60;
    s->clamp_lo = R() % 8 ? (R() % 2) | (R() % 2) << 2 : R() % 16;
    s->test_lo = R() % 2 ? 0x30000 : R() % 2 ? (R() & 0xFFF) | 0x30000 : R() & 0xFFFFF;
    s->tests = R() % 8;
    s->alpha_lo = R() % 2 ? 0x44 : R() & 0xFF;
    s->alpha_hi = R() & 0xFF;
    s->xyoffset_lo = s->xyoffset_hi = R() % 2 ? 0x7000 : 0;
    s->scissor_lo = (R() % 64) | (R() % 1100) << 16;
    s->scissor_hi = (R() % 64) | (R() % 1100) << 16;
    if (R() % 2) { s->scissor_lo = 0x01FF0000; s->scissor_hi = 0x01BF0000; }
    s->texa_lo = R() & 0x80FF;
    s->texa_hi = R() & 0xFF;
    for (i = 0; i < 2; i++) {
        u32 big = R() % 2;
        s->xy[i] = (s->xyoffset_lo + R() % (big ? 600 * 16 : 80 * 16)) | (s->xyoffset_hi + R() % (big ? 500 * 16 : 80 * 16)) << 16;
        s->uv[i] = (R() % 0x4000) | (R() % 0x4000) << 16;
    }
    if (R() % 3 == 0) { /* texel for pixel, as the frame copy */
        s->uv[0] = 8 | 8 << 16;
        s->uv[1] = ((s->xy[1] & 0xFFFF) - (s->xy[0] & 0xFFFF) + 8) | 0x1808u << 16;
    }
    s->rgba = R() % 2 ? 0x80808080u : R();
    s->uorg = R() % 4 ? 0 : (s32)(R() % 64) - 16;
    s->zbuf_lo = (R() % 512) | (R() % 16) << 24;
    s->zbuf_hi = R() & 1;
    s->z = R();
    s->f = R();
    s->fogcol = R();
    if (shape) {
        s->prim = 0x106 | (R() % 4 ? 0x10 : 0) | (R() % 2 ? 0x40 : 0);
        s->frame_lo = (s->frame_lo & 0xFFFFFF) | (R() % 2) << 24;
        s->frame_hi = 0;
        if (R() % 2) s->tex0_lo = (s->tex0_lo & ~(63u << 20)) | (R() % 2) << 20;
        s->tex0_hi = (s->tex0_hi & ~(3u << 3)) | (R() % 2) << 3;
        if (R() % 2) s->rgba = 0x80808080u;
        else if (R() % 2) s->rgba = 0x00808080u | R() << 24;
        if (R() % 4) s->test_lo = 0x30000;
        s->clamp_lo &= 5;
    }
}

static u32 snap_hash(void) {
    u32 h = 2166136261u, x, y;
    for (y = 0; y < 1024; y++)
        for (x = 0; x < 1024; x++) h = (h ^ kh1_gsmem_read_pixel(KH1_PSMCT32, 0, 16, x, y)) * 16777619u;
    return h;
}

/* one sprite from seed's memory, with the fast paths on or off: its answer, counters and memory */
static int run(u32 seed, int fast, int cached, int flat, u32 *hash, KH1GsMemStats *st, int shape) {
    KH1GsSprite s;
    int i, r;
    rs = seed;
    kh1_gsmem_reset();
    kh1_gsmem_fast(fast);
    kh1_gsmem_flat(1);
    kh1_gsmem_texels = cached ? texels : 0;
    kh1_gsmem_palette = cached ? palette : 0;
    for (i = 0; i < 20000; i++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0, 16, R() % 1024, R() % 1024, R());
    make(&s, shape);
    if (R() % 3) kh1_gsmem_tex0(s.tex0_lo, s.tex0_hi | 2u << 29); /* a CLUT */
    r = flat ? kh1_gsmem_flat_sprite(&s) : kh1_gsmem_sprite(&s);
    /* the same sprite again: the memos (tex_scan, the tables) answer the second */
    r = r << 1 | (flat ? kh1_gsmem_flat_sprite(&s) : kh1_gsmem_sprite(&s));
    *hash = snap_hash();
    *st = *kh1_gsmem_stats();
    return r;
}

int main(void) {
    u32 it, h0, h1, drawn = 0, x, y;
    KH1GsMemStats s0, s1;
    static u32 rect[256 * 256];
    for (it = 0; it < 600; it++) {
        int flat = it % 4 != 3, cached = it % 3 != 0, shape = it % 2, r0, r1;
        r0 = run(it * 7919u + 1, 0, cached, flat, &h0, &s0, shape);
        r1 = run(it * 7919u + 1, 1, cached, flat, &h1, &s1, shape);
        if (r0 != r1 || h0 != h1 || memcmp(&s0, &s1, sizeof s0)) {
            printf("gsfast_test: sprite %u (flat %d, cached %d, shape %d): answer %d / %d, memory %08x / %08x%s\n", it, flat,
                   cached, shape, r0, r1, h0, h1, memcmp(&s0, &s1, sizeof s0) ? ", counters differ" : "");
            fails++;
        }
        drawn += (r1 & 1) != 0;
    }
    CHECK("most sprites draw", drawn > 200);
    kh1_gsmem_texels = 0;
    kh1_gsmem_palette = 0;
    /* kh1_gsmem_read_rect against kh1_gsmem_read_pixel, every PSM, inside and across the 0x4000 wrap */
    rs = 99;
    kh1_gsmem_reset();
    kh1_gsmem_fast(1);
    for (it = 0; it < 30000; it++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0, 16, R() % 1024, R() % 1024, R());
    for (it = 0; it < 200; it++) {
        u32 psm = it < 22 ? tpsms[it % 11] : it % 3 ? fpsms[it % 6] : tpsms[R() % 11];
        u32 bp = it % 5 == 0 ? 0x3F00 + R() % 0x100 : R() % 0x4000, bw = 1 + R() % 16;
        u32 x0 = R() % 600, y0 = R() % 600, w = 1 + R() % 256, hh = 1 + R() % 256, bad = 0;
        CHECK("read_rect answers", kh1_gsmem_read_rect(psm, bp, bw, x0, y0, w, hh, rect, 256) == 0);
        for (y = 0; y < hh && !bad; y++)
            for (x = 0; x < w; x++)
                if (rect[y * 256 + x] != kh1_gsmem_read_pixel(psm, bp, bw, x0 + x, y0 + y)) { bad = 1; break; }
        if (bad) printf("gsfast_test: read_rect psm %02x bp %04x bw %u (%u, %u) %u x %u differs\n", psm, bp, bw, x0, y0, w, hh);
        fails += bad;
    }
    /* tex_scan's memo: a write into the texture's pages, or a draw into them, is seen at once */
    kh1_gsmem_reset();
    {
        u32 lo = 0x1000 | 1 << 14 | 6u << 26 | 6u << 30, st0, st1;
        st0 = kh1_gsmem_tex_stamp(lo, 1);
        CHECK("no target yet", kh1_gsmem_tex_target(lo, 1) == 0);
        kh1_gsmem_write_pixel(KH1_PSMCT32, 0x1000, 1, 5, 5, 1);
        st1 = kh1_gsmem_tex_stamp(lo, 1);
        CHECK("a write moves the stamp", st1 != st0);
        kh1_gsmem_draw(0x80 | 1 << 16, 0, 0, 0, 63u << 16, 63u << 16, 0);
        CHECK("a draw makes it a target", kh1_gsmem_tex_target(lo, 1) != 0);
        CHECK("and moves the stamp", kh1_gsmem_tex_stamp(lo, 1) != st1);
    }
    CHECK("read_rect refuses a PSM the model has not", kh1_gsmem_read_rect(0x3B, 0, 1, 0, 0, 4, 4, rect, 256) == -1);
    printf("gsfast_test: %s (600 sprites both ways, %u drawn; 200 rectangles)\n", fails ? "FAIL" : "PASS", drawn);
    return fails != 0;
}
