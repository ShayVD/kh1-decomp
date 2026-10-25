/* The texture formats a port uploads (host/port/texfmt.c, renderer-spec 4.13 "Session 119",
 * vita-port-plan 5.1bg), tested on host/null/gsmem.c's model with made-up texels (no game data):
 * tests/selftest.sh builds it with gcc -m32 when that works.
 *
 *   formats  each PSM the texture cache keeps: the stored texels (kh1_gsmem_read_pixel's) converted to
 *            the GPU format and sampled the way the shader must (kh1_texfmt_sample) give
 *            kh1_gsmem_read_tex's RGBA8 for every texel, under three TEXA values (AEM off and on), the
 *            indexed ones through kh1_gsmem_clut's palette (the palette cache's words); rows padded.
 *   texa     (item 4c) a CT16 and a CT24 texture drawn by the model's sprite (kh1_gsmem_sprite) under
 *            two TEXA values each, once reading GS memory and once through the port's texture cache
 *            (kh1_gsmem_texels): the same pixels, the shader's sample's colour, and one entry a
 *            texture (TEXA is not in the key: the second TEXA is a stamp hit, no upload). */
#include "common.h"
#include "../../host/null/gsmem.h"
#include "platform/texcache.h"
#include "platform/texfmt.h"

int printf(const char *, ...);
int sprintf(char *, const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("texfmt_test: %s\n", name); fails++; } } while (0)

#define MAXW 16
#define MAXH 16
static u32 stored[MAXW * MAXH], ref[MAXW * MAXH], pal[256];
static u8 up[MAXH * MAXW * 4];

/* a made-up stored value for texel (x, y): every few a black one, CT16's STP bit on some */
static u32 made_up(u32 psm, u32 x, u32 y) {
    u32 v = (x * 0x2F1B3 + y * 0x91D7 + 0x3C) * 2654435761u;
    if ((x + y * 3) % 5 == 0) v &= 0xFF000000u; /* black (CT32 keeps an A) */
    switch (psm) {
    case KH1_PSMCT24: case KH1_PSMZ24: return v & 0xFFFFFF;
    case KH1_PSMCT16: case KH1_PSMCT16S: case KH1_PSMZ16: case KH1_PSMZ16S:
        return ((x + y * 3) % 5 == 0 ? 0 : v >> 8 & 0x7FFF) | ((x + y) % 3 == 0) << 15;
    case KH1_PSMT8: case KH1_PSMT8H: return (x * 37 + y * 11) & 0xFF;
    case KH1_PSMT4: case KH1_PSMT4HL: case KH1_PSMT4HH: return (x * 5 + y * 3) & 15;
    }
    return v;
}

static int indexed(u32 psm) {
    return psm == KH1_PSMT8 || psm == KH1_PSMT8H || psm == KH1_PSMT4 || psm == KH1_PSMT4HL || psm == KH1_PSMT4HH;
}

#define CBP 0x3000
/* a CLUT at CBP: CT32 16 x 16 for the 8-bit PSMs, CT16 8 x 2 at CSA 3 for the 4-bit ones (blacks and
 * STP bits among them, so TEXA reaches the palette), loaded by a TEX0 with CLD 1 */
static u32 clut_hi(u32 psm) {
    u32 x, y, c16 = !(psm == KH1_PSMT8 || psm == KH1_PSMT8H), cpsm = c16 ? KH1_PSMCT16 : KH1_PSMCT32;
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++)
            kh1_gsmem_write_pixel(cpsm, CBP, 1, x, y, c16 ? (x == 2 ? 0x8000 : x == 5 ? 0 : (x * 0x1357 + y * 0x2468) & 0xFFFF)
                                                          : (x * 0x01020304u + y * 0x10203040u) ^ 0x80000000u);
    return CBP << 5 | cpsm << 19 | (c16 ? 3u : 0u) << 24 | 1u << 29;
}

static const u32 texa[3][2] = { { 0x80, 0x40 }, { 0x20 | 1 << 15, 0xFF }, { 0x00 | 1 << 15, 0x7F } };

/* one PSM at tbp, 1 << tw by 1 << th */
static void format_case(const char *name, u32 psm, u32 tbp, u32 tw, u32 th) {
    u32 w = 1u << tw, h = 1u << th, x, y, i, n, lo, hi = 0, stride, used, ok = 1, pad = 1, np = 0;
    char msg[96];
    lo = tbp | 1u << 14 | psm << 20 | tw << 26 | (th & 3) << 30;
    hi = th >> 2;
    if (indexed(psm)) {
        hi |= clut_hi(psm);
        kh1_gsmem_tex0(lo, hi);
        hi &= ~(7u << 29);
    }
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) kh1_gsmem_write_pixel(psm, tbp, 1, x, y, made_up(psm, x, y));
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) stored[y * w + x] = kh1_gsmem_read_pixel(psm, tbp, 1, x, y);
    stride = kh1_texfmt_stride(psm, w);
    n = kh1_texfmt_convert(psm, stored, w, h, up);
    sprintf(msg, "%s: %u bytes in rows of %u", name, n, stride);
    CHECK(msg, n == stride * h);
    used = kh1_texfmt_of(psm) == KH1_TEXFMT_P4 ? (w + 1) / 2 : w * (stride / ((w + 7) & ~7u)); /* the texels' bytes */
    for (y = 0; y < h; y++) /* the padding is 0 */
        for (i = used; i < stride; i++)
            if (up[y * stride + i]) pad = 0;
    sprintf(msg, "%s: padding 0", name);
    CHECK(msg, pad);
    for (i = 0; i < 3; i++) {
        if (kh1_gsmem_read_tex(lo, hi, texa[i][0], texa[i][1], ref)) { ok = 0; break; }
        if (indexed(psm)) np = (u32)kh1_gsmem_clut(lo, hi, texa[i][0], texa[i][1], pal);
        for (y = 0; y < h; y++)
            for (x = 0; x < w; x++)
                if (kh1_texfmt_sample(psm, up, w, x, y, pal, texa[i][0], texa[i][1]) != ref[y * w + x]) {
                    if (ok) printf("texfmt_test: %s TEXA %u (%u, %u): %08x, the GS %08x\n", name, i, x, y,
                                   kh1_texfmt_sample(psm, up, w, x, y, pal, texa[i][0], texa[i][1]), ref[y * w + x]);
                    ok = 0;
                }
    }
    sprintf(msg, "%s: the shader's sample is the GS's texel under each TEXA", name);
    CHECK(msg, ok && (!indexed(psm) || np == (kh1_texfmt_of(psm) == KH1_TEXFMT_P8 ? 256u : 16u)));
}

/* item 4c: sprites through the texture cache */
static KH1TexCache cache;
static void read_stored(u32 lo, u32 hi, u32 *out, void *ctx) {
    u32 w = 1u << (lo >> 26 & 15), h = 1u << ((lo >> 30 | hi << 2) & 15), x, y;
    (void)ctx;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) out[y * w + x] = kh1_gsmem_read_pixel(lo >> 20 & 63, lo & 0x3FFF, lo >> 14 & 63, x, y);
}
static const u32 *texels(u32 lo, u32 hi) {
    int decoded;
    return kh1_texcache_get(&cache, lo, hi, kh1_gsmem_tex_stamp(lo, hi), kh1_gsmem_tex_target(lo, hi), read_stored, 0,
                            &decoded);
}

#define FBP 0x50 /* blocks 0xA00: a CT32 frame 64 wide */
static u32 frame[2][16 * 16];

/* the 16 x 16 texture tex0_lo (TH's low bits 0) drawn at frame (0, 0) DECAL with TCC 1 under TEXA t; the frame read back */
static int draw(u32 tex0_lo, const u32 *t, u32 *out) {
    KH1GsSprite s = { 0 };
    u32 x, y;
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, FBP * 32, 1, x, y, 0x5A5A5A5A);
    s.prim = 6 | 1 << 4 | 1 << 8; /* SPRITE, TME, FST */
    s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
    s.tex0_lo = tex0_lo;
    s.tex0_hi = 1 | 1 << 2 | 1 << 3; /* TH 4 (its high bits), TCC, DECAL */
    s.scissor_lo = 63u << 16;
    s.scissor_hi = 63u << 16;
    s.texa_lo = t[0];
    s.texa_hi = t[1];
    s.xy[1] = 16 << 4 | (16 << 4) << 16;
    s.uv[1] = 16 << 4 | (16 << 4) << 16;
    s.rgba = 0x80808080u;
    if (!kh1_gsmem_sprite(&s)) return 0;
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) out[y * 16 + x] = kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y);
    return 1;
}

static void texa_case(const char *name, u32 psm, u32 tbp) {
    u32 lo = tbp | 1u << 14 | psm << 20 | 4u << 26, x, y, i, same = 1, shader = 1, d0, sh0;
    char msg[96];
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) {
            kh1_gsmem_write_pixel(psm, tbp, 1, x, y, made_up(psm, x, y));
            stored[y * 16 + x] = kh1_gsmem_read_pixel(psm, tbp, 1, x, y);
        }
    kh1_texfmt_convert(psm, stored, 16, 16, up);
    d0 = cache.decodes;
    sh0 = cache.stamp_hits;
    for (i = 0; i < 2; i++) {
        kh1_gsmem_texels = 0;
        if (!draw(lo, texa[i], frame[0])) same = 0;
        kh1_gsmem_texels = texels;
        if (!draw(lo, texa[i], frame[1])) same = 0;
        kh1_gsmem_texels = 0;
        for (y = 0; y < 256; y++) {
            if (frame[0][y] != frame[1][y]) same = 0;
            if (frame[1][y] != kh1_texfmt_sample(psm, up, 16, y & 15, y >> 4, 0, texa[i][0], texa[i][1])) shader = 0;
        }
    }
    sprintf(msg, "%s: the same pixels through the texture cache under two TEXA", name);
    CHECK(msg, same);
    sprintf(msg, "%s: the pixels are the shader's sample", name);
    CHECK(msg, shader);
    sprintf(msg, "%s: one upload, the second TEXA a stamp hit", name);
    CHECK(msg, cache.decodes == d0 + 1 && cache.stamp_hits == sh0 + 1);
}

int main(void) {
    static const struct { const char *name; u32 psm, tw, th; } f[] = {
        { "CT32", KH1_PSMCT32, 4, 3 },   { "CT24", KH1_PSMCT24, 4, 4 },   { "CT16", KH1_PSMCT16, 4, 3 },
        { "CT16S", KH1_PSMCT16S, 2, 2 }, { "T8", KH1_PSMT8, 4, 4 },       { "T8H", KH1_PSMT8H, 3, 2 },
        { "T4", KH1_PSMT4, 4, 3 },       { "T4 4 wide", KH1_PSMT4, 2, 1 }, { "T4HL", KH1_PSMT4HL, 4, 2 },
        { "T4HH", KH1_PSMT4HH, 1, 0 },   { "Z32", KH1_PSMZ32, 3, 3 },     { "Z24", KH1_PSMZ24, 3, 3 },
        { "Z16", KH1_PSMZ16, 3, 3 },     { "Z16S", KH1_PSMZ16S, 2, 3 },
    };
    u32 i, slots = 0;
    kh1_gsmem_reset();
    CHECK("PSMT8 uploads as P8, CT16 as A1B5G5R5, CT24 takes TEXA, CT32 not",
          kh1_texfmt_of(KH1_PSMT8) == KH1_TEXFMT_P8 && kh1_texfmt_of(KH1_PSMCT16) == KH1_TEXFMT_A1B5G5R5 &&
          kh1_texfmt_texa(KH1_PSMCT24) && !kh1_texfmt_texa(KH1_PSMCT32) && !kh1_texfmt_texa(KH1_PSMT4));
    CHECK("an unknown PSM: none", kh1_texfmt_of(0x09) == KH1_TEXFMT_NONE && kh1_texfmt_stride(0x09, 16) == 0);
    CHECK("rows padded to 8 texels", kh1_texfmt_stride(KH1_PSMT4, 2) == 4 && kh1_texfmt_stride(KH1_PSMCT32, 4) == 32 &&
          kh1_texfmt_stride(KH1_PSMCT16, 16) == 32);
    for (i = 0; i < sizeof f / sizeof f[0]; i++) format_case(f[i].name, f[i].psm, 0x1000 + i * 0x100, f[i].tw, f[i].th);

    CHECK("texa: the cache", kh1_texcache_init(&cache) == 0);
    texa_case("texa CT16", KH1_PSMCT16, 0x2000);
    texa_case("texa CT24", KH1_PSMCT24, 0x2100);
    for (i = 0; i < KH1_TEXCACHE_SLOTS; i++) slots += cache.slot[i].n != 0;
    CHECK("texa: one entry a texture", slots == 2 && cache.decodes == 2 && cache.hash_hits == 0);
    kh1_texcache_free(&cache);

    printf("texfmt_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
