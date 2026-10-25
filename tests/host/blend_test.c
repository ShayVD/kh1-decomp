/* The blend state a port's GPU runs (host/port/blend.c, renderer-spec 4.13 "Session 121", vita-port-plan
 * 5.1bi), tested on host/null/gsmem.c's model with made-up colours (no game data): tests/selftest.sh
 * builds it with gcc -m32 when that works.
 *
 *   formulas  kh1_blend_gs on known values (the floored product, the clamps, FIX, a CT24 frame's Ad);
 *             the 0x80-scale stored alpha read back exactly up to 0x80.
 *   forms     every A / B / C / D (81; C = FIX with FIX 0 / 0x40 / 0x80: 135): the GPU model of kh1_blend_state equal
 *             to kh1_blend_gs for every As (EXACT), within 2 while C <= 0x80 (LE80), or through the
 *             shader's frame read (FETCH); the written alpha the source's on the 0x80 scale.  The
 *             game's five equations and the bevel's are not FETCH, and which kind each is.
 *   masks     FBMSK 0 / 0xFFFFFF / 0xFF000000 and a CT24 frame as channel masks, a per-bit one FETCH.
 *   sprites   all 81 forms drawn by the model's sprite (kh1_gsmem_sprite, ABE, DECAL TCC 1 from a CT32
 *             texture) over a made-up frame: every pixel is kh1_blend_gs of the texel and the frame. */
#include "common.h"
#include "../../host/null/gsmem.h"
#include "platform/texfmt.h"
#include "platform/blend.h"

int printf(const char *, ...);
int sprintf(char *, const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("blend_test: %s\n", name); fails++; } } while (0)

static u32 rgba(u32 r, u32 g, u32 b, u32 a) { return r | g << 8 | b << 16 | a << 24; }
static u32 abcd(u32 a, u32 b, u32 c, u32 d) { return a | b << 2 | c << 4 | d << 6; }

static u32 gs4(u32 lo, u32 hi, u32 cs, u32 cd) { return kh1_blend_gs(lo, hi, cs, cd, KH1_PSMCT32); }

static void formulas(void) {
    u32 a, ok = 1;
    /* (Cs - Cd) x As >> 7 + Cd: 0x80 is all of Cs, 0x40 half, the product floored also when negative */
    CHECK("normal: As 0x80 is Cs", gs4(0x44, 0, rgba(200, 10, 0, 0x80), rgba(50, 60, 70, 0)) == rgba(200, 10, 0, 0x80));
    CHECK("normal: As 0x40 is half way, floored", gs4(0x44, 0, rgba(200, 11, 0, 0x40), rgba(50, 60, 70, 0)) ==
          rgba(125, 35, 35, 0x40));
    CHECK("normal: As 0xFF extrapolates past Cs", gs4(0x44, 0, rgba(200, 100, 0, 0xFF), rgba(100, 200, 0, 0)) ==
          rgba(255, 0, 0, 0xFF));
    CHECK("additive (Cs - 0) x As + Cd", gs4(0x48, 0, rgba(0x20, 0x20, 0x20, 0x90), rgba(250, 10, 0, 0)) ==
          rgba(255, 46, 36, 0x90));
    CHECK("subtractive (0 - Cs) x As + Cd: the ceil", gs4(0x42, 0, rgba(0x20, 0x20, 0x21, 0x90), rgba(250, 10, 0x40, 0)) ==
          rgba(214, 0, 26, 0x90));
    CHECK("darken (Cd - Cs) x As + 0", gs4(0x81, 0, rgba(10, 100, 0, 0x40), rgba(30, 20, 9, 0)) == rgba(10, 0, 4, 0x40));
    CHECK("(0 - 0) x FIX + Cs is Cs", gs4(0x2A, 0x80, 0x12345678, 0x9ABCDEF0) == 0x12345678);
    CHECK("FIX as C", gs4(abcd(0, 2, 2, 1), 0x40, rgba(100, 0, 0, 0), rgba(10, 0, 0, 0)) == rgba(60, 0, 0, 0));
    CHECK("Ad on a CT24 frame is 0x80", kh1_blend_gs(abcd(0, 1, 1, 1), 0, rgba(100, 0, 0, 0), rgba(10, 0, 0, 0x10), KH1_PSMCT24) ==
          rgba(100, 0, 0, 0));
    for (a = 0; a <= 0x80; a++)
        if (kh1_blend_load_alpha(kh1_blend_store_alpha(a)) != a) ok = 0;
    CHECK("stored alpha 0 .. 0x80 reads back exactly", ok);
    CHECK("stored alpha 0x80 is 1.0", kh1_blend_store_alpha(0x80) == 255);
    CHECK("stored alpha above 0x80 clamps", kh1_blend_store_alpha(0xC0) == 255 && kh1_blend_load_alpha(255) == 0x80);
}

static u32 diff(u32 a, u32 b) {
    u32 i, d, m = 0;
    for (i = 0; i < 24; i += 8) {
        d = (a >> i & 0xFF) > (b >> i & 0xFF) ? (a >> i & 0xFF) - (b >> i & 0xFF) : (b >> i & 0xFF) - (a >> i & 0xFF);
        if (d > m) m = d;
    }
    return m;
}

static const u8 grid[] = { 0, 1, 2, 7, 31, 64, 100, 127, 128, 129, 170, 200, 254, 255 };
#define NG (sizeof(grid) / sizeof(grid[0]))

/* one form: the GPU model against the GS over the grid; returns the largest difference (0x100: the
 * written alpha wrong) */
static u32 form_case(u32 lo, u32 fix, u32 max_as, u32 *kind) {
    KH1BlendState st;
    u32 as, ad, i, j, k, cs, cd, dst, gs, gpu, m = 0, d;
    kh1_blend_state(lo, fix, 1, KH1_PSMCT32, 0, &st);
    *kind = st.kind;
    for (as = 0; as <= max_as; as++)
        for (ad = 0; ad <= 0x80; ad += 0x40)
            for (i = 0; i < NG; i++)
                for (j = 0; j < NG; j++)
                    for (k = 0; k < NG; k += 4) {
                        cs = rgba(grid[i], grid[j], grid[k], as);
                        cd = rgba(grid[j], grid[k], grid[i], ad);
                        dst = (cd & 0xFFFFFF) | kh1_blend_store_alpha(ad) << 24;
                        gs = kh1_blend_gs(lo, fix, cs, cd, KH1_PSMCT32);
                        gpu = kh1_blend_gpu(&st, cs, dst);
                        d = diff(gs, gpu);
                        if (kh1_blend_load_alpha(gpu >> 24) != (as > 0x80 ? 0x80 : as)) d = 0x100;
                        if (d > m) m = d;
                    }
    return m;
}

static void forms(void) {
    static const u32 fixes[3] = { 0, 0x40, 0x80 };
    u32 a, b, c, d, f, lo, kind, m, ok_exact = 1, ok_le80 = 1, ok_fetch = 1, n[3] = { 0, 0, 0 }, worst = 0;
    KH1BlendState st;
    char msg[128];
    for (a = 0; a < 3; a++)
        for (b = 0; b < 3; b++)
            for (c = 0; c < 3; c++)
                for (d = 0; d < 3; d++)
                    for (f = 0; f < (c == 2 ? 3u : 1u); f++) {
                        lo = abcd(a, b, c, d);
                        m = form_case(lo, fixes[f], 0xFF, &kind);
                        n[kind]++;
                        if (kind == KH1_BLEND_EXACT && m) {
                            if (ok_exact) printf("blend_test: form %02x FIX %02x EXACT is %u apart\n", lo, fixes[f], m);
                            ok_exact = 0;
                        }
                        if (kind == KH1_BLEND_FETCH && m) {
                            if (ok_fetch) printf("blend_test: form %02x FIX %02x FETCH is %u apart\n", lo, fixes[f], m);
                            ok_fetch = 0;
                        }
                        if (kind == KH1_BLEND_LE80) {
                            m = form_case(lo, fixes[f], 0x80, &kind);
                            if (m > worst) worst = m;
                            if (m > 2) {
                                if (ok_le80) printf("blend_test: form %02x FIX %02x LE80 is %u apart\n", lo, fixes[f], m);
                                ok_le80 = 0;
                            }
                        }
                    }
    CHECK("every EXACT form equals the GS for every As", ok_exact);
    sprintf(msg, "every LE80 form within 2 of the GS while C <= 0x80 (worst %u)", worst);
    CHECK(msg, ok_le80);
    CHECK("every FETCH form equals the GS on what the target holds", ok_fetch);
    sprintf(msg, "the 135 forms: %u exact, %u within 1-2, %u fetch", n[0], n[1], n[2]);
    CHECK(msg, n[0] + n[1] + n[2] == 135);
    printf("blend_test: %u exact, %u le80 (worst %u), %u fetch\n", n[0], n[1], worst, n[2]);
    /* the game's */
    kh1_blend_state(0x44, 0, 1, KH1_PSMCT32, 0, &st);
    CHECK("normal blend: ONE, ONE_MINUS_SRC_ALPHA on a pre-scaled Cs, LE80",
          st.enable && st.eq == KH1_BEQ_ADD && st.fd == KH1_BF_ONE_MINUS_SRC_ALPHA && st.pre_a == 1 && st.kind == KH1_BLEND_LE80);
    kh1_blend_state(0x48, 0x80, 1, KH1_PSMCT32, 0, &st);
    CHECK("additive: ADD ONE, ONE, the product floored, EXACT",
          st.eq == KH1_BEQ_ADD && st.fd == KH1_BF_ONE && st.pre_floor == 1 && st.pre_d == 0 && st.kind == KH1_BLEND_EXACT);
    kh1_blend_state(0x42, 0, 1, KH1_PSMCT32, 0, &st);
    CHECK("bevel subtractive: REVERSE_SUBTRACT ONE, ONE, the product ceiled, EXACT",
          st.eq == KH1_BEQ_REVERSE_SUBTRACT && st.fd == KH1_BF_ONE && st.pre_floor == 2 && st.pre_a == 1 && st.kind == KH1_BLEND_EXACT);
    kh1_blend_state(0x81, 0, 1, KH1_PSMCT32, 0, &st);
    CHECK("darken: REVERSE_SUBTRACT, Cd x SRC_ALPHA - Cs x As, LE80",
          st.eq == KH1_BEQ_REVERSE_SUBTRACT && st.fd == KH1_BF_SRC_ALPHA && st.pre_a == 1 && st.kind == KH1_BLEND_LE80);
    kh1_blend_state(0x2A, 0x80, 1, KH1_PSMCT32, 0, &st);
    CHECK("(0 - 0) x FIX + Cs: blending off", !st.enable && st.kind == KH1_BLEND_EXACT);
    kh1_blend_state(0x44, 0, 0, KH1_PSMCT32, 0, &st);
    CHECK("ABE 0: blending off", !st.enable && st.kind == KH1_BLEND_EXACT && st.mask == 0xF);
    /* the bevel's As 0x90 in its two forms, every Cs / Cd */
    {
        u32 s, t, ok = 1;
        KH1BlendState s48, s42;
        kh1_blend_state(0x48, 0, 1, KH1_PSMCT32, 0, &s48);
        kh1_blend_state(0x42, 0, 1, KH1_PSMCT32, 0, &s42);
        for (s = 0; s < 256; s++)
            for (t = 0; t < 256; t++) {
                u32 cs = rgba(s, 0x20, s, 0x90), cd = rgba(t, t, 0xFF - t, 0x80), dst = (cd & 0xFFFFFF) | 0xFF000000u;
                if ((kh1_blend_gpu(&s48, cs, dst) & 0xFFFFFF) != (kh1_blend_gs(0x48, 0, cs, cd, KH1_PSMCT32) & 0xFFFFFF)) ok = 0;
                if ((kh1_blend_gpu(&s42, cs, dst) & 0xFFFFFF) != (kh1_blend_gs(0x42, 0, cs, cd, KH1_PSMCT32) & 0xFFFFFF)) ok = 0;
            }
        CHECK("the bevel's As 0x90: both forms exact for every Cs / Cd", ok);
    }
}

static void masks(void) {
    KH1BlendState st;
    kh1_blend_state(0x44, 0, 1, KH1_PSMCT32, 0, &st);
    CHECK("FBMSK 0: RGBA written", st.mask == 0xF);
    kh1_blend_state(0x44, 0, 1, KH1_PSMCT32, 0xFFFFFF, &st);
    CHECK("FBMSK 0xFFFFFF: alpha only", st.mask == 0x8 && st.kind == KH1_BLEND_LE80);
    CHECK("FBMSK 0xFFFFFF: the colour kept", kh1_blend_gpu(&st, 0x40FFFFFF, 0x00123456) == (0x00123456 | kh1_blend_store_alpha(0x40) << 24));
    kh1_blend_state(0x44, 0, 1, KH1_PSMCT32, 0xFF000000u, &st);
    CHECK("FBMSK 0xFF000000: colour only", st.mask == 0x7);
    kh1_blend_state(0x44, 0, 1, KH1_PSMCT24, 0, &st);
    CHECK("CT24: no alpha written", st.mask == 0x7);
    kh1_blend_state(0x44, 0, 1, KH1_PSMCT16, 0x80F8F8F8u, &st);
    CHECK("CT16 FBMSK on 5551's bits: nothing written", st.mask == 0);
    kh1_blend_state(0x44, 0, 1, KH1_PSMCT32, 0x0F, &st);
    CHECK("a per-bit FBMSK: FETCH", st.kind == KH1_BLEND_FETCH);
}

/* sprites: a 16 x 16 CT32 texture drawn DECAL TCC 1 at frame (0, 0) 16 x 16 over a made-up frame */
#define FBP 0x50
static u32 tex[256], under[256];

static void sprites(void) {
    u32 a, b, c, d, x, y, lo, ok = 1, drawn = 1, tbp = 0x1000;
    KH1GsSprite s = { 0 };
    kh1_gsmem_reset();
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) {
            kh1_gsmem_write_pixel(KH1_PSMCT32, tbp, 1, x, y, (x * 0x2F1B3 + y * 0x91D7 + 0x3C) * 2654435761u);
            tex[y * 16 + x] = kh1_gsmem_read_pixel(KH1_PSMCT32, tbp, 1, x, y);
            under[y * 16 + x] = (x * 0x01234567u + y * 0x89ABCDEFu) ^ 0x5A5A5A5Au;
        }
    s.prim = 6 | 1 << 4 | 1 << 6 | 1 << 8; /* SPRITE, TME, ABE, FST */
    s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
    s.tex0_lo = tbp | 1u << 14 | KH1_PSMCT32 << 20 | 4u << 26;
    s.tex0_hi = 1 | 1 << 2 | 1 << 3; /* TH 4, TCC, DECAL */
    s.scissor_lo = 63u << 16;
    s.scissor_hi = 63u << 16;
    s.xy[1] = 16 << 4 | (16 << 4) << 16;
    s.uv[1] = 16 << 4 | (16 << 4) << 16;
    s.rgba = 0x80808080u;
    for (a = 0; a < 3; a++)
        for (b = 0; b < 3; b++)
            for (c = 0; c < 3; c++)
                for (d = 0; d < 3; d++) {
                    lo = abcd(a, b, c, d);
                    s.alpha_lo = lo;
                    s.alpha_hi = 0x50;
                    for (y = 0; y < 16; y++)
                        for (x = 0; x < 16; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, FBP * 32, 1, x, y, under[y * 16 + x]);
                    if (!kh1_gsmem_sprite(&s)) { drawn = 0; continue; }
                    for (y = 0; y < 16; y++)
                        for (x = 0; x < 16; x++) {
                            u32 got = kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y);
                            u32 want = kh1_blend_gs(lo, 0x50, tex[y * 16 + x], under[y * 16 + x], KH1_PSMCT32);
                            if (got != want) {
                                if (ok) printf("blend_test: form %02x (%u, %u): %08x, want %08x\n", lo, x, y, got, want);
                                ok = 0;
                            }
                        }
                }
    CHECK("the model drew each sprite", drawn);
    CHECK("the model's ABE is kh1_blend_gs for all 81 forms", ok);
}

int main(void) {
    formulas();
    forms();
    masks();
    sprites();
    printf("blend_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
