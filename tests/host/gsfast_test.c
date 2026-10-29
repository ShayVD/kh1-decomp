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
void *memcpy(void *, const void *, __SIZE_TYPE__);
void *memset(void *, int, __SIZE_TYPE__);

static int fails;
#define CHECK(name, cond) do { if (!(cond)) { printf("gsfast_test: %s\n", name); fails++; } } while (0)

static u32 rs;
static u32 R(void) { rs = rs * 1103515245u + 12345u; return rs >> 8 ^ rs << 13; }

/* the present's caches as host/null/present.c keeps them: the texels as GS memory holds them at the
 * draw (the index for an indexed PSM), the palette as kh1_gsmem_clut gives it */
static u32 tex_buf[1024 * 1024], pal_buf[256];
/* session 147d: an answer kh1_gsmem_clut_id names is the same entries whenever that id comes back */
static struct { u32 id, n, e[256]; } ids[256];
static u32 id_seen, id_again, id_bad;
static void id_note(u32 n, const u32 *e) {
    u32 id = kh1_gsmem_clut_id(), k = id & 255;
    if (!id || !n) return;
    id_seen++;
    if (ids[k].id == id) {
        id_again++;
        if (ids[k].n != n || memcmp(ids[k].e, e, n * 4)) id_bad++;
        return;
    }
    ids[k].id = id;
    ids[k].n = n;
    memcpy(ids[k].e, e, n * 4);
}
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
    if (R() % 4 == 0) { /* session 135: a TRISTRIP rectangle's corner colours (gsregs.c's gs_quad) */
        s->quad = 1;
        for (i = 0; i < 4; i++) s->rgbav[i] = R() % 2 ? 0x00808080u | (R() & 0xFF) << 24 : R();
    }
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
    /* and over the texture's own blocks, so that its every byte matters (CT24's top one too) */
    for (i = 0; i < 8000; i++)
        kh1_gsmem_write_pixel(KH1_PSMCT32, s.tex0_lo & 0x3FFF, s.tex0_lo >> 14 & 63, R() % 128, R() % 128, R());
    if (R() % 3) kh1_gsmem_tex0(s.tex0_lo, s.tex0_hi | 2u << 29); /* a CLUT */
    r = flat ? kh1_gsmem_flat_sprite(&s) : kh1_gsmem_sprite(&s);
    /* the same sprite again: the memos (tex_scan, the tables) answer the second */
    r = r << 1 | (flat ? kh1_gsmem_flat_sprite(&s) : kh1_gsmem_sprite(&s));
    *hash = snap_hash();
    *st = *kh1_gsmem_stats();
    return r;
}

/* session 135: uploads (the kept addresses, trx_addrs; CT32's word a pixel): seed's memory, then the
 * same few rectangles uploaded twice in random pieces, then again with other bytes; the memory, the
 * stamps of textures over them and the counters must not depend on the fast paths */
static const u32 upsms[] = { KH1_PSMCT32, KH1_PSMCT24, KH1_PSMCT16, KH1_PSMCT16S, KH1_PSMT8, KH1_PSMT4,
                             KH1_PSMT8H, KH1_PSMT4HL, KH1_PSMT4HH, KH1_PSMZ32, KH1_PSMZ16 };
static u32 run_up(u32 seed, int fast, u32 *hash, KH1GsMemStats *st) {
    static u32 words[1 << 17];
    u32 i, j, r, stamps = 0, st0 = 0, st1;
    rs = seed;
    kh1_gsmem_reset();
    kh1_gsmem_fast(fast);
    for (i = 0; i < 5000; i++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0, 16, R() % 1024, R() % 1024, R());
    /* a draw's pages (a render target) under some of them */
    for (i = 0; i < 3; i++) kh1_gsmem_draw((R() % 512) | (1 + R() % 8) << 16, 0, 0, 0, (R() % 512) << 16, (R() % 512) << 16, 0);
    for (r = 0; r < 3; r++) {
        u32 psm = upsms[R() % 11], bp = R() % 0x4000, bw = 1 + R() % 8, x = R() % 64, y = R() % 64;
        u32 w = 1 + R() % 80, h = 1 + R() % 40, pass, data = R();
        if (r == 2 && seed % 3 == 0) { /* session 141: a large one, past the first blocks' row and column */
            x = R() % 1500; y = R() % 1500; w = 1 + R() % 540; h = 1 + R() % 200; bw = 1 + R() % 32;
        }
        u32 lo = bp | bw << 14 | psm << 20 | 7u << 26 | 7u << 30;
        for (pass = 0; pass < 3; pass++) {
            u32 left = (w * h * (psm == KH1_PSMT4 || psm == KH1_PSMT4HL || psm == KH1_PSMT4HH ? 4 : psm == KH1_PSMCT32 || psm == KH1_PSMZ32 ? 32 :
                        psm == KH1_PSMCT24 ? 24 : psm == KH1_PSMCT16 || psm == KH1_PSMCT16S || psm == KH1_PSMZ16 ? 16 : 8) + 31) / 32;
            u32 ds = pass == 2 ? data + 1 : data;
            kh1_gsmem_trxdir(0, 0, bp | bw << 16 | psm << 24, 0, x | y << 16, w, h);
            for (i = 0; i < left; i++) { ds = ds * 1103515245u + 12345u; words[i] = ds ^ ds >> 16; }
            for (i = 0; i < left; i += j) { /* pieces of 1 .. 64 words */
                j = 1 + R() % 64;
                if (j > left - i) j = left - i;
                kh1_gsmem_image(words + i, j);
            }
            /* the stamp's moves (its value counts every write since the start, not reset) */
            st1 = kh1_gsmem_tex_stamp(lo, 1);
            stamps = stamps * 3 + (pass ? (st1 != st0) + 1 : 0);
            stamps = stamps * 7 + kh1_gsmem_tex_target(lo, 1);
            st0 = st1;
        }
    }
    *hash = snap_hash();
    *st = *kh1_gsmem_stats();
    return stamps;
}

/* session 146: an upload as gsimage.c's load_image sends it, with kh1_gsmem_image_same (same 1) or always whole */
static int up(int same, u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 w, u32 h, const u8 *b, u32 bytes) {
    u32 done = 0, buf[64];
    kh1_gsmem_trxdir(0, 0, psm << 24 | bw << 16 | bp, 0, x | y << 16, w, h);
    if (same && kh1_gsmem_image_same(b, bytes)) return 1;
    while (done < bytes) {
        u32 k = bytes - done < sizeof buf ? bytes - done : sizeof buf, i;
        for (i = 0; i < (k + 3) / 4; i++) buf[i] = 0;
        memcpy(buf, b + done, k);
        kh1_gsmem_image(buf, (k + 3) / 4);
        done += k;
    }
    kh1_gsmem_image_kept(b, bytes);
    return 0;
}

/* the state a reader can see: every pixel's bits (CT32 view), each page's drawn bits for each PSM, a few
 * textures' targets and whether their stamps moved since the last call (stamps are seq values, which the
 * skip's own bookkeeping moves differently) */
static u32 stamp_was[64];
static u32 state_hash(void) {
    static const u32 ps[] = { KH1_PSMCT32, KH1_PSMCT24, KH1_PSMT8H, KH1_PSMT4HL, KH1_PSMT4HH, KH1_PSMT8 };
    static u32 all[1024 * 1024];
    u32 h = 2166136261u, p, i;
    kh1_gsmem_read_rect(KH1_PSMCT32, 0, 16, 0, 0, 1024, 1024, all, 1024);
    for (i = 0; i < 1024 * 1024; i++) h = (h ^ all[i]) * 16777619u;
    for (p = 0; p < 512; p++)
        for (i = 0; i < 6; i++)
            h = (h ^ (u32)kh1_gsmem_drawn(ps[i], p * 32, 1, 0, 0)) * 16777619u;
    for (i = 0; i < 64; i++) {
        u32 lo = (i * 256) | 4u << 14 | ps[i % 6] << 20 | 8u << 26 | 2u << 30, hi = 1;
        u32 st0 = kh1_gsmem_tex_stamp(lo, hi);
        h = (h ^ (st0 != stamp_was[i])) * 16777619u;
        stamp_was[i] = st0;
        h = (h ^ kh1_gsmem_tex_target(lo, hi)) * 16777619u;
    }
    return h;
}

int main(void) {
    u32 it, h0, h1, drawn = 0, x, y, hits = 0;
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
    for (it = 0; it < 150; it++) {
        u32 s0v = run_up(it * 104729u + 7, 0, &h0, &s0), s1v = run_up(it * 104729u + 7, 1, &h1, &s1);
        if (s0v != s1v || h0 != h1 || memcmp(&s0, &s1, sizeof s0)) {
            printf("gsfast_test: uploads %u: stamps %08x / %08x, memory %08x / %08x%s\n", it, s0v, s1v, h0, h1,
                   memcmp(&s0, &s1, sizeof s0) ? ", counters differ" : "");
            fails++;
        }
    }
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
    /* session 146: the frame copy's read_rect (the GPU thread's, its own fast paths) against the live one, and
     * its texture version: moved by a take that copied the texture's pages, not by a draw marking them */
    {
        u32 i, lo = 0x0E00 | 8 << 14 | (u32)KH1_PSMCT24 << 20 | 9u << 26, hi = 2, v0, v1, n = 0;
        static u32 live[256 * 256];
        CHECK("the copy is taken", kh1_gsmem_snap_take() >= 0);
        for (it = 0; it < 200; it++) {
            u32 psm = it < 22 ? tpsms[it % 11] : it % 3 ? fpsms[it % 6] : tpsms[R() % 11];
            u32 bp = it % 5 == 0 ? 0x3F00 + R() % 0x100 : R() % 0x4000, bw = 1 + R() % 16;
            u32 x0 = R() % 600, y0 = R() % 600, w = 1 + R() % 256, hh = 1 + R() % 256;
            CHECK("snap read_rect answers", kh1_gsmem_snap_read_rect(psm, bp, bw, x0, y0, w, hh, rect, 256) == 0);
            kh1_gsmem_read_rect(psm, bp, bw, x0, y0, w, hh, live, 256);
            for (y = 0; y < hh; y++)
                if (memcmp(rect + y * 256, live + y * 256, w * 4)) {
                    printf("gsfast_test: snap read_rect psm %02x bp %04x bw %u (%u, %u) %u x %u differs\n", psm, bp, bw, x0,
                           y0, w, hh);
                    fails++;
                    break;
                }
            n++;
        }
        kh1_gsmem_snap_take();
        v0 = kh1_gsmem_snap_tex_ver(lo, hi);
        v1 = kh1_gsmem_tex_stamp(lo, hi);
        CHECK("a version", v0 != 0);
        kh1_gsmem_draw(0x70 | 8 << 16 | 1u << 24, 0, 0x70 | 1u << 24, 0, 511u << 16, 255u << 16, 0x10000);
        CHECK("the draw moves the stamp", kh1_gsmem_tex_stamp(lo, hi) != v1);
        kh1_gsmem_snap_take();
        CHECK("a draw's mark keeps the version", kh1_gsmem_snap_tex_ver(lo, hi) == v0);
        for (i = 0; i < 4; i++) kh1_gsmem_write_pixel(KH1_PSMCT24, 0x0E00, 8, 100 + i, 50, R());
        CHECK("no take, the same version", kh1_gsmem_snap_tex_ver(lo, hi) == v0);
        kh1_gsmem_snap_take();
        v1 = kh1_gsmem_snap_tex_ver(lo, hi);
        CHECK("a write and a take move it", v1 != v0);
        kh1_gsmem_write_pixel(KH1_PSMCT32, 0x2000, 8, 0, 0, 1);
        kh1_gsmem_snap_take();
        CHECK("a write elsewhere keeps it", kh1_gsmem_snap_tex_ver(lo, hi) == v1);
        CHECK("200 copy rectangles", n == 200);
    }
    /* session 146: uploads of the bytes a rectangle already holds, over pages draws marked, skipped
     * (kh1_gsmem_image_same) or sent whole: the same pixels, marks, stamps and targets after every op */
    {
        static const u32 ups[] = { KH1_PSMCT24, KH1_PSMCT32, KH1_PSMT8, KH1_PSMT4, KH1_PSMT8H, KH1_PSMCT16 };
        static u8 bytes[6][128 * 64 * 4];
        u32 run, op, skips = 0, marked = 0;
        for (run = 0; run < 8; run++) {
            u32 ha[120], hb[120], k, rect[6][5];
            for (k = 0; k < 6; k++) {
                rect[k][0] = (R() % 0x3000) & ~31u; rect[k][1] = 2 + R() % 3;
                rect[k][2] = R() % 64; rect[k][3] = 1 + R() % 128; rect[k][4] = 1 + R() % 64;
            }
            for (k = 0; k < 2; k++) {
                u32 j, ss = run * 7919u + 1;
                rs = ss;
                kh1_gsmem_reset();
                kh1_gsmem_fast(1);
                memset(stamp_was, 0, sizeof stamp_was);
                state_hash();
                for (j = 0; j < 6; j++) {
                    u32 n;
                    for (n = 0; n < sizeof bytes[j]; n++) bytes[j][n] = (u8)R();
                }
                for (op = 0; op < 120; op++) {
                    u32 c = R() % 10, j = R() % 6, psm = ups[j], *q = rect[j];
                    u32 n = psm == KH1_PSMT4 ? (q[3] * q[4] + 1) / 2 : q[3] * q[4] * (psm == KH1_PSMCT32 ? 4 : psm == KH1_PSMCT24 ? 3 : psm == KH1_PSMCT16 ? 2 : 1);
                    if (c < 6) {
                        int was = kh1_gsmem_drawn(psm, q[0], q[1], q[2], 0);
                        if (up(k == 0, psm, q[0], q[1], q[2], 0, q[3], q[4], bytes[j], n)) {
                            skips++;
                            marked += was;
                        }
                    }
                    else if (c < 8) /* a draw (and its Z) over some pages */
                        kh1_gsmem_draw((q[0] >> 5) | q[1] << 16 | (R() % 2 ? 1u : 0) << 24, 0, (rect[R() % 6][0] >> 5) | 1u << 24, 0,
                                       (R() % 256) << 16, (R() % 128) << 16, R() % 2 ? 0x10000 : 0);
                    else if (c < 9) kh1_gsmem_write_pixel(psm, q[0], q[1], q[2] + R() % q[3], R() % q[4], R());
                    else bytes[j][R() % n] ^= 1 + R() % 255; /* new bytes for the next upload */
                    (k ? hb : ha)[op] = op % 8 == 7 || op == 119 ? state_hash() : 0; /* stamps compared hash to hash */
                }
            }
            for (op = 0; op < 120; op++)
                if (ha[op] != hb[op]) {
                    printf("gsfast_test: same-skip run %u differs after op %u\n", run, op);
                    fails++;
                    break;
                }
        }
        CHECK("uploads were skipped", skips > 100);
        CHECK("some of them over a draw's marks", marked > 20);
        printf("gsfast_test: %u uploads skipped, %u of them over a draw's marks\n", skips, marked);
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
    /* session 141: tex_scan by pages (a texture of whole pages) against its block scan, over pages that
     * uploads wrote and draws into a few targets marked, aligned bp or not, across the 0x4000 wrap */
    for (it = 0; it < 400; it++) {
        u32 i, psm = tpsms[it % 11], lo, hi, tw, th, s0v, s1v, t0v, t1v;
        rs = it * 15485863u + 3;
        kh1_gsmem_reset();
        kh1_gsmem_fast(1);
        for (i = 0; i < 1 + R() % 6; i++)
            kh1_gsmem_draw((R() % 512) | (1 + R() % 16) << 16 | (R() % 2 ? 0 : 2u) << 24, 0, (R() % 512) | 1u << 24, 0,
                           (R() % 1024) << 16, (R() % 1024) << 16, R() % 2 ? 0x10000 : 0);
        for (i = 0; i < R() % 300; i++) kh1_gsmem_write_pixel(tpsms[R() % 11], R() % 0x4000, 1 + R() % 16, R() % 512, R() % 512, R());
        tw = 5 + R() % 6;
        th = 5 + R() % 6;
        lo = (it % 4 == 0 ? 0x3F00 + R() % 0x100 : it % 2 ? (R() % 512) * 32 : R() % 0x4000) | (1 + R() % 16) << 14 |
             psm << 20 | tw << 26 | th << 30;
        hi = th >> 2;
        kh1_gsmem_fast(0);
        s0v = kh1_gsmem_tex_stamp(lo, hi);
        t0v = kh1_gsmem_tex_target(lo, hi);
        kh1_gsmem_fast(1);
        s1v = kh1_gsmem_tex_stamp(lo, hi);
        t1v = kh1_gsmem_tex_target(lo, hi);
        hits += t1v != 0;
        if (s0v != s1v || t0v != t1v) {
            printf("gsfast_test: tex_scan %u psm %02x tex0 %08x: stamp %u / %u, target %u / %u\n", it, psm, lo, s0v, s1v, t0v, t1v);
            fails++;
        }
    }
    CHECK("some textures read a target", hits > 40);
    /* session 147c: the CLUT loads' kept entries (gsmem.c clut_kept): a few CBPs loaded again and again, 8-bit and
     * 4-bit, CT32 / CT16 / CT16S, with pixel writes between that land in the CLUTs' blocks or beside them (often the
     * same value again), each load's palette against a load with the fast paths off */
    {
        static const u32 cps[] = { KH1_PSMCT32, KH1_PSMCT16, KH1_PSMCT16S };
        u32 cbps[4], pa[256], pb[256], pc[256], pd[256], na, nb, hitsame = 0, loads = 0;
        kh1_gsmem_reset();
        rs = 147;
        for (it = 0; it < 4; it++) cbps[it] = R() % 0x3FF0;
        for (it = 0; it < 6000; it++) {
            u32 cbp = cbps[R() % 4], cpsm = cps[R() % 3], b8 = R() & 1, csa = b8 ? 0 : R() % 16, lo, hi, k;
            lo = (b8 ? KH1_PSMT8 : KH1_PSMT4) << 20 | 1u << 14;
            hi = cpsm << 19 | cbp << 5 | csa << 24 | 1u << 29;
            for (k = 0; k < R() % 3; k++) { /* writes into a CLUT's area (its 16 x 16) or near it */
                u32 v = R() % 3 ? kh1_gsmem_read_pixel(cps[R() % 3], cbps[R() % 4], 1, R() % 16, R() % 16) : R();
                kh1_gsmem_write_pixel(cps[R() % 3], cbps[R() % 4] + (R() % 4 ? 0 : R() % 8), 1, R() % 16, R() % 24, v);
            }
            kh1_gsmem_fast(1);
            for (k = 0; k < R() % 3; k++) /* other loads first: another CBP, CPSM, size or CSA, or this one */
                kh1_gsmem_tex0((R() & 1 ? KH1_PSMT8 : KH1_PSMT4) << 20 | 1u << 14,
                               cps[R() % 3] << 19 | (R() % 2 ? cbp : cbps[R() % 4]) << 5 | (R() % 2 ? csa : R() % 16) << 24 | 1u << 29);
            kh1_gsmem_tex0(lo, hi);
            if (R() & 1) kh1_gsmem_tex0(lo, hi); /* again: the buffer holds it already */
            nb = (u32)kh1_gsmem_clut(lo, hi, 0x80, 0x80, pb);
            id_note(nb, pb);
            /* kh1_gsmem_clut's kept answer: the same question again, then another TEXA (CT16's alpha) */
            if (kh1_gsmem_clut(lo, hi, 0x80, 0x80, pc) != (int)nb || memcmp(pc, pb, nb * 4)) fails++;
            id_note(nb, pc);
            id_note((u32)kh1_gsmem_clut(lo, hi, 0x8040, 0x10, pc), pc);
            kh1_gsmem_fast(0);
            kh1_gsmem_tex0(lo, hi);
            kh1_gsmem_clut(lo, hi, 0x8040, 0x10, pd);
            if (memcmp(pc, pd, nb * 4)) fails++;
            na = (u32)kh1_gsmem_clut(lo, hi, 0x80, 0x80, pa);
            loads++;
            hitsame += na == nb && na && memcmp(pa, pb, na * 4) == 0;
            if (na != nb || memcmp(pa, pb, na * 4)) {
                if (fails < 20) printf("gsfast_test: CLUT load %u cpsm %u cbp %04x %s: the kept entries differ\n", it, cpsm, cbp, b8 ? "8-bit" : "4-bit");
                fails++;
            }
        }
        CHECK("the CLUT loads compared", hitsame == loads);
        CHECK("an id's entries are the same each time it comes back", id_bad == 0);
        CHECK("ids come back", id_seen > 3000 && id_again > 1000);
    }
    CHECK("read_rect refuses a PSM the model has not", kh1_gsmem_read_rect(0x3B, 0, 1, 0, 0, 4, 4, rect, 256) == -1);
    printf("gsfast_test: %s (600 sprites both ways, %u drawn; 150 upload runs; 200 rectangles, 200 from the copy; 400 texture scans, %u on a target)\n", fails ? "FAIL" : "PASS", drawn, hits);
    return fails != 0;
}
