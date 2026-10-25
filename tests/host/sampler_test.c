/* The sampler state a port draws a texture with (host/port/sampler.c, renderer-spec 4.13 "Session
 * 120", vita-port-plan 5.1bh), tested with made-up texels (no game data): tests/selftest.sh builds it
 * with gcc -m32 when that works.
 *
 *   decode   CLAMP / TEX1 values the game writes (CLAMP_1 5, the REGION_CLAMP windows 1 .. 255 and
 *            0 .. 510, the dump's REGION_REPEAT mask 255, TEX1 0x60 / 0x61 / 0 / 0x21) and the edge
 *            cases (a region past the texture, a split filter, mipmaps) mapped to the GPU mode and the
 *            shader's step expected.
 *   sweep    every wrap mode on each axis (regions inside, at the edges and one past the texture),
 *            point and bilinear, at every 1/16 texel from 4 texels left of the texture to 4 past it:
 *            the port's sample (the shader's clamp or taps, the GPU's mode) is the GS's.
 *   sprites  point-sampled REPEAT / CLAMP against host/null/gsmem.c's sprite: a 16 x 16 CT32 texture
 *            drawn 48 x 48 with UV running to 48 texels, DECAL TCC 1, each pixel the port's sample. */
#include "common.h"
#include "../../host/null/gsmem.h"
#include "platform/sampler.h"

int printf(const char *, ...);
int sprintf(char *, const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("sampler_test: %s\n", name); fails++; } } while (0)

/* CLAMP's two words from WMS / WMT and the four region fields */
static void clamp_words(u32 wms, u32 wmt, u32 minu, u32 maxu, u32 minv, u32 maxv, u32 *lo, u32 *hi) {
    *lo = wms | wmt << 2 | minu << 4 | maxu << 14 | (minv & 0xFF) << 24;
    *hi = minv >> 8 | maxv << 2;
}

static void decode(void) {
    KH1Sampler s;
    u32 lo, hi;
    kh1_sampler_of(5, 0, 0x60, 0, 8, 8, &s);
    CHECK("CLAMP_1 5, TEX1 0x60: GPU clamp both axes, bilinear",
          s.u.addr == KH1_ADDR_CLAMP && s.v.addr == KH1_ADDR_CLAMP && !s.u.shader && !s.v.shader && s.linear && !s.split && !s.mips);
    kh1_sampler_of(0, 0, 0, 0, 4, 4, &s);
    CHECK("REPEAT, TEX1 0: GPU repeat, point", s.u.addr == KH1_ADDR_REPEAT && s.v.addr == KH1_ADDR_REPEAT && !s.u.shader && !s.linear);
    clamp_words(2, 2, 1, 255, 1, 255, &lo, &hi);
    kh1_sampler_of(lo, hi, 0x61, 0, 8, 8, &s);
    CHECK("texspot's REGION_CLAMP 1 .. 255 of 256, TEX1 0x61: the shader's clamp, bilinear",
          s.u.shader == KH1_SHADER_CLAMP && s.u.lo == 1 && s.u.hi == 255 && s.v.shader == KH1_SHADER_CLAMP && s.v.lo == 1 &&
          s.linear && !s.u.past);
    clamp_words(2, 2, 0, 510, 0, 510, &lo, &hi);
    kh1_sampler_of(lo, hi, 0x60, 0, 9, 9, &s);
    CHECK("the lens grid's REGION_CLAMP 0 .. 510 of 512: the shader's clamp", s.u.shader == KH1_SHADER_CLAMP && s.u.hi == 510 &&
          s.v.hi == 510);
    clamp_words(2, 2, 0, 255, 0, 127, &lo, &hi);
    kh1_sampler_of(lo, hi, 0x60, 0, 8, 7, &s);
    CHECK("REGION_CLAMP over the whole texture: a plain clamp", s.u.addr == KH1_ADDR_CLAMP && !s.u.shader && !s.v.shader);
    clamp_words(2, 1, 0, 676, 0, 0, &lo, &hi);
    kh1_sampler_of(lo, hi, 0x60, 0, 9, 9, &s);
    CHECK("REGION_CLAMP past the texture (the wide lens grid's 676 of 512): clamped to 511, counted",
          s.u.past && s.u.hi == 511 && !s.u.shader && s.v.addr == KH1_ADDR_CLAMP);
    clamp_words(3, 3, 255, 0, 255, 0, &lo, &hi);
    kh1_sampler_of(lo, hi, 0x60, 0, 8, 8, &s);
    CHECK("REGION_REPEAT mask 255 on 256: GPU repeat", s.u.addr == KH1_ADDR_REPEAT && !s.u.shader && !s.v.shader);
    kh1_sampler_of(lo, hi, 0x60, 0, 9, 8, &s);
    CHECK("REGION_REPEAT mask 255 on 512: the shader's taps", s.u.shader == KH1_SHADER_TAPS && !s.v.shader);
    clamp_words(3, 0, 63, 128, 0, 0, &lo, &hi);
    kh1_sampler_of(lo, hi, 0x60, 0, 8, 8, &s);
    CHECK("REGION_REPEAT mask 63 fix 128 (an atlas tile): the shader's taps", s.u.shader == KH1_SHADER_TAPS && s.u.lo == 63 &&
          s.u.hi == 128);
    kh1_sampler_of(5, 0, 0x21, 0, 8, 8, &s);
    CHECK("TEX1 0x21 (LCM 1, MMAG 1, MMIN 0, K 0): bilinear, not split", s.linear && !s.split);
    kh1_sampler_of(5, 0, 0x21, 0x10, 8, 8, &s);
    CHECK("TEX1 LCM 1 K 1.0: minified, MMIN's point", !s.linear);
    kh1_sampler_of(5, 0, 0x20, 0, 8, 8, &s);
    CHECK("TEX1 MMAG 1 MMIN 0, LCM 0: split", s.split && s.linear);
    kh1_sampler_of(5, 0, 0x60 | 1 << 2, 0, 8, 8, &s);
    CHECK("TEX1 MXL 1: mipmaps flagged", s.mips);
    kh1_sampler_of(5, 0, 0x20 | 5 << 6, 0, 8, 8, &s);
    CHECK("TEX1 MMIN LINEAR_MIPMAP_LINEAR with one level: bilinear, not split", s.linear && !s.split);
}

#define TW 16
#define TH 8
static u32 tex[TH][TW];
static u32 fetch(u32 x, u32 y, void *ctx) {
    (void)ctx;
    if (x >= TW || y >= TH) return 0xDEADBEEF; /* a tap outside the texture: never equal by chance */
    return tex[y][x];
}

static void sweep(void) {
    /* (wm, lo, hi) per axis; regions inside, at an edge, a tile */
    static const u32 modes[][3] = {
        { 0, 0, 0 }, { 1, 0, 0 }, { 2, 0, 15 }, { 2, 3, 9 }, { 2, 0, 4 }, { 2, 11, 15 }, { 2, 5, 5 }, { 2, 2, 40 },
        { 3, 15, 0 }, { 3, 7, 0 }, { 3, 7, 8 }, { 3, 3, 4 }, { 3, 1, 14 },
    };
    u32 n = sizeof modes / sizeof modes[0], i, j, f, x, y, lo, hi, ok, bad = 0, gs_out = 0;
    s32 u, v;
    KH1Sampler s;
    char msg[96];
    for (y = 0; y < TH; y++)
        for (x = 0; x < TW; x++) tex[y][x] = (x * 0x3B + y * 0x95) * 0x01010101u ^ (x << 24 | y << 3);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (f = 0; f < 2; f++) {
                u32 mv0 = modes[j][1] & (TH - 1), mv1 = modes[j][2];
                if (modes[j][0] == 2 && mv1 > 15) mv1 = 40;
                else if (modes[j][0] >= 2) mv1 &= TH - 1;
                if (modes[j][0] == 2 && mv0 > mv1) mv0 = mv1;
                clamp_words(modes[i][0], modes[j][0], modes[i][1], modes[i][2], mv0, mv1, &lo, &hi);
                kh1_sampler_of(lo, hi, f ? 0x60 : 0, 0, 4, 3, &s);
                ok = 1;
                for (v = -4 * 16; v < (TH + 4) * 16; v++)
                    for (u = -4 * 16; u < (TW + 4) * 16; u += 3) {
                        u32 g, p;
                        /* the GS reads past the texture only with REGION_CLAMP's MAX past it: skip those */
                        if ((s.u.past || s.v.past)) continue;
                        g = kh1_sampler_gs(&s, fetch, 0, u, v);
                        p = kh1_sampler_port(&s, fetch, 0, u, v);
                        if (g == 0xDEADBEEF) gs_out++;
                        if (g != p) {
                            if (ok) printf("sampler_test: modes %u / %u %s at (%d, %d)/16: port %08x, GS %08x\n", i, j,
                                           f ? "bilinear" : "point", u, v, p, g);
                            ok = 0;
                        }
                    }
                if (!ok) bad++;
            }
    sprintf(msg, "sweep: the port's sample is the GS's in every mode pair and filter (%u failed)", bad);
    CHECK(msg, bad == 0);
    CHECK("sweep: no GS tap outside the texture in the modes swept", gs_out == 0);
    /* the region past the texture: the port clamps it to n - 1, which is the GS's wherever the GS
     * stays in the texture */
    clamp_words(2, 1, 2, 40, 0, 0, &lo, &hi);
    kh1_sampler_of(lo, hi, 0x60, 0, 4, 3, &s);
    ok = 1;
    for (u = 2 * 16 + 8; u <= (TW - 1) * 16 + 8; u++)
        if (kh1_sampler_port(&s, fetch, 0, u, 40) != kh1_sampler_gs(&s, fetch, 0, u, 40)) ok = 0;
    CHECK("a region past the texture: the GS's inside it", ok && s.u.past);
}

/* point-sampled REPEAT / CLAMP against the model's sprite */
#define FBP 0x50
static u32 fetch_gs(u32 x, u32 y, void *ctx) { return kh1_gsmem_read_pixel(KH1_PSMCT32, *(u32 *)ctx, 1, x, y); }

static void sprites(void) {
    static const u32 cl[4][2] = { { 0, 0 }, { 1, 1 }, { 0, 1 }, { 1, 0 } };
    static const char *name[4] = { "REPEAT / REPEAT", "CLAMP / CLAMP", "REPEAT / CLAMP", "CLAMP / REPEAT" };
    u32 tbp = 0x1000, x, y, i, ok, lo, hi;
    KH1GsSprite s = { 0 };
    KH1Sampler sm;
    char msg[96];
    kh1_gsmem_reset();
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, tbp, 1, x, y, (x * 0x2F1B3 + y * 0x91D7 + 0x3C) * 2654435761u);
    s.prim = 6 | 1 << 4 | 1 << 8; /* SPRITE, TME, FST */
    s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
    s.tex0_lo = tbp | 1u << 14 | KH1_PSMCT32 << 20 | 4u << 26;
    s.tex0_hi = 1 | 1 << 2 | 1 << 3; /* TH 4, TCC, DECAL */
    s.scissor_lo = 63u << 16;
    s.scissor_hi = 63u << 16;
    s.xy[1] = 48 << 4 | (48 << 4) << 16;
    s.uv[1] = 48 << 4 | (48 << 4) << 16;
    s.rgba = 0x80808080u;
    for (i = 0; i < 4; i++) {
        clamp_words(cl[i][0], cl[i][1], 0, 0, 0, 0, &lo, &hi);
        s.clamp_lo = lo;
        kh1_sampler_of(lo, hi, 0, 0, 4, 4, &sm);
        ok = kh1_gsmem_sprite(&s);
        for (y = 0; ok && y < 48; y++)
            for (x = 0; x < 48; x++)
                if (kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y) != kh1_sampler_port(&sm, fetch_gs, &tbp, x * 16, y * 16)) {
                    printf("sampler_test: %s (%u, %u)\n", name[i], x, y);
                    ok = 0;
                    break;
                }
        sprintf(msg, "sprite %s: the model's pixels are the port's point samples", name[i]);
        CHECK(msg, ok);
    }
}

int main(void) {
    decode();
    sweep();
    sprites();
    printf("sampler_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
