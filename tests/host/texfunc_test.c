/* The texture function a port's shader runs (host/port/texfunc.c, renderer-spec 4.13 "Session 120",
 * vita-port-plan 5.1bh), tested on host/null/gsmem.c's model with made-up texels (no game data):
 * tests/selftest.sh builds it with gcc -m32 when that works.
 *
 *   formulas  the GS manual's four TFX forms with TCC 0 / 1 on known values (the 0x80 scale, the clamps);
 *             the shader's exact form (the 8-bit values taken back) equal to them for every pair of
 *             8-bit channel values, the plain float form at most 1 apart.
 *   sprites   MODULATE and DECAL with TCC 0 / 1 and four vertex colours, drawn by the model's sprite
 *             (kh1_gsmem_sprite) from a CT32, a CT16 and a T8 texture: every pixel is kh1_texfunc of
 *             the shader's texel (texfmt's upload and sample) and the vertex colour. */
#include "common.h"
#include "../../host/null/gsmem.h"
#include "platform/texfmt.h"
#include "platform/texfunc.h"

int printf(const char *, ...);
int sprintf(char *, const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("texfunc_test: %s\n", name); fails++; } } while (0)

static u32 rgba(u32 r, u32 g, u32 b, u32 a) { return r | g << 8 | b << 16 | a << 24; }

static void formulas(void) {
    static const char *name[4] = { "MODULATE", "DECAL", "HIGHLIGHT", "HIGHLIGHT2" };
    u32 tfx, tcc, t, c, exact, near, d, i, a, b, maxd;
    char msg[96];
    /* 0x80 is 1.0 on both sides */
    CHECK("MODULATE: 0x80 x 0x80 is 0x80", kh1_texfunc(0, 1, 0x80808080, 0x80808080) == 0x80808080);
    CHECK("MODULATE: 0xFF x 0xFF clamps to 0xFF", kh1_texfunc(0, 1, 0xFFFFFFFF, 0xFFFFFFFF) == 0xFFFFFFFF);
    CHECK("MODULATE: Ct x Cv >> 7 truncates", kh1_texfunc(0, 1, rgba(3, 100, 200, 0x40), rgba(0x41, 0x80, 0x20, 0x81)) ==
          rgba(1, 100, 50, 0x40));
    CHECK("MODULATE TCC 0: the vertex alpha", kh1_texfunc(0, 0, rgba(0x80, 0, 0, 0x10), rgba(0x80, 0, 0, 0x55)) >> 24 == 0x55);
    CHECK("DECAL: the texel (TCC 1)", kh1_texfunc(1, 1, 0x12345678, 0x9ABCDEF0) == 0x12345678);
    CHECK("DECAL TCC 0: the texel's colour, the vertex alpha", kh1_texfunc(1, 0, 0x12345678, 0x9ABCDEF0) == 0x9A345678);
    CHECK("HIGHLIGHT: + Av, A At + Av", kh1_texfunc(2, 1, rgba(0x80, 0x40, 0xF0, 0x30), rgba(0x80, 0x80, 0x80, 0x20)) ==
          rgba(0xA0, 0x60, 0xFF, 0x50));
    CHECK("HIGHLIGHT: A clamps", kh1_texfunc(2, 1, 0xC0000000, 0x60000000) >> 24 == 0xFF);
    CHECK("HIGHLIGHT2: + Av, A At", kh1_texfunc(3, 1, rgba(0x80, 0x40, 0xF0, 0x30), rgba(0x80, 0x80, 0x80, 0x20)) ==
          rgba(0xA0, 0x60, 0xFF, 0x30));
    CHECK("HIGHLIGHT TCC 0: A Av", kh1_texfunc(2, 0, 0x30000000, 0x20000000) >> 24 == 0x20);
    CHECK("from TEX0's high word (TCC 1 DECAL)", kh1_texfunc_tex0(1 << 2 | 1 << 3, 0x12345678, 0) == 0x12345678);
    /* every pair of 8-bit values in one channel and in A, the other channels made up */
    for (tfx = 0; tfx < 4; tfx++)
        for (tcc = 0; tcc < 2; tcc++) {
            exact = 1;
            maxd = 0;
            for (t = 0; t < 256; t++)
                for (c = 0; c < 256; c++) {
                    u32 ct = rgba(t, 255 - t, t ^ 0x5A, t), cv = rgba(c, (c * 7) & 0xFF, 255 - c, (c + t) & 0xFF);
                    u32 ref = kh1_texfunc(tfx, tcc, ct, cv);
                    if (kh1_texfunc_shader(tfx, tcc, ct, cv, 1) != ref) exact = 0;
                    near = kh1_texfunc_shader(tfx, tcc, ct, cv, 0);
                    for (i = 0; i < 32; i += 8) {
                        a = ref >> i & 0xFF;
                        b = near >> i & 0xFF;
                        d = a > b ? a - b : b - a;
                        if (d > maxd) maxd = d;
                    }
                }
            sprintf(msg, "%s TCC %u: the exact shader is the GS", name[tfx], tcc);
            CHECK(msg, exact);
            sprintf(msg, "%s TCC %u: the float shader within 1 (%u)", name[tfx], tcc, maxd);
            CHECK(msg, maxd <= 1);
        }
}

/* sprites: a 16 x 16 texture at tbp drawn at frame (0, 0) 16 x 16, point-sampled, no blending */
#define FBP 0x50
#define CBP 0x3000
static u32 stored[256], pal[256];
static u8 up[16 * 16 * 4];

static u32 made_up(u32 psm, u32 x, u32 y) {
    u32 v = (x * 0x2F1B3 + y * 0x91D7 + 0x3C) * 2654435761u;
    if (psm == KH1_PSMCT16) return v >> 8 & 0xFFFF;
    if (psm == KH1_PSMT8) return (x * 37 + y * 11) & 0xFF;
    return v;
}

static void sprite_case(const char *name, u32 psm, u32 tbp) {
    static const u32 cv[4] = { 0x80808080u, 0x40C08060u, 0xFF102030u, 0x00FFFF01u };
    u32 lo = tbp | 1u << 14 | psm << 20 | 4u << 26, hi = 1, x, y, i, tfx, tcc, ok = 1, drawn = 1, cl;
    KH1GsSprite s = { 0 };
    char msg[96];
    if (psm == KH1_PSMT8) { /* a CT32 16 x 16 CLUT at CBP, loaded by TEX0 CLD 1 */
        for (y = 0; y < 16; y++)
            for (x = 0; x < 16; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, CBP, 1, x, y, (x * 0x01020304u + y * 0x10203040u) ^ 0x80000000u);
        cl = CBP << 5 | 1u << 29;
        kh1_gsmem_tex0(lo, hi | cl);
        hi |= CBP << 5;
        kh1_gsmem_clut(lo, hi, 0x80, 0x80, pal);
    }
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) {
            kh1_gsmem_write_pixel(psm, tbp, 1, x, y, made_up(psm, x, y));
            stored[y * 16 + x] = kh1_gsmem_read_pixel(psm, tbp, 1, x, y);
        }
    kh1_texfmt_convert(psm, stored, 16, 16, up);
    s.prim = 6 | 1 << 4 | 1 << 8; /* SPRITE, TME, FST */
    s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
    s.tex0_lo = lo;
    s.scissor_lo = 63u << 16;
    s.scissor_hi = 63u << 16;
    s.texa_lo = 0x80;
    s.texa_hi = 0x80;
    s.xy[1] = 16 << 4 | (16 << 4) << 16;
    s.uv[1] = 16 << 4 | (16 << 4) << 16;
    for (tfx = 0; tfx < 2; tfx++)
        for (tcc = 0; tcc < 2; tcc++)
            for (i = 0; i < 4; i++) {
                s.tex0_hi = hi | tcc << 2 | tfx << 3;
                s.rgba = cv[i];
                if (!kh1_gsmem_sprite(&s)) { drawn = 0; continue; }
                for (y = 0; y < 16; y++)
                    for (x = 0; x < 16; x++) {
                        u32 t = kh1_texfmt_sample(psm, up, 16, x, y, pal, 0x80, 0x80);
                        u32 want = kh1_texfunc(tfx, tcc, t, cv[i]), got = kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y);
                        if (got != want) {
                            if (ok) printf("texfunc_test: %s TFX %u TCC %u colour %08x (%u, %u): %08x, want %08x\n", name, tfx, tcc,
                                           cv[i], x, y, got, want);
                            ok = 0;
                        }
                    }
            }
    sprintf(msg, "%s: the model drew each sprite", name);
    CHECK(msg, drawn);
    sprintf(msg, "%s: MODULATE / DECAL with TCC 0 / 1 are kh1_texfunc of the shader's texel", name);
    CHECK(msg, ok);
}

int main(void) {
    formulas();
    kh1_gsmem_reset();
    sprite_case("CT32", KH1_PSMCT32, 0x1000);
    sprite_case("CT16", KH1_PSMCT16, 0x1100);
    sprite_case("T8", KH1_PSMT8, 0x1200);
    printf("texfunc_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
