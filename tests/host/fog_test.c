/* The fog a port's shader runs (host/port/fog.c, renderer-spec 4.13 "Session 122", vita-port-plan 5.1bj),
 * tested on host/null/gsmem.c's model with made-up texels (no game data): tests/selftest.sh builds it with
 * gcc -m32 when that works.
 *
 *   formulas  the GS's (F x C + (0xFF - F) x FOGCOL) >> 8 on known values (F 0xFF, F 0, A kept); the
 *             shader's exact form equal to it for every C, F and FOGCOL channel value, the plain float
 *             mix at most 2 apart.
 *   sprites   the model's sprite (kh1_gsmem_sprite with tests 4, FGE) under four Fs and two FOGCOLs,
 *             DECAL / MODULATE: every pixel is kh1_fog_gs of kh1_texfunc's colour; with ABE (Cs - Cd)
 *             x As + Cd the blend of the fogged colour (fog before the blend), and with ATE GREATER the
 *             test on the unfogged alpha (fog leaves A). */
#include "common.h"
#include "../../host/null/gsmem.h"
#include "platform/blend.h"
#include "platform/texfunc.h"
#include "platform/fog.h"

int printf(const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("fog_test: %s\n", name); fails++; } } while (0)

static u32 rgba(u32 r, u32 g, u32 b, u32 a) { return r | g << 8 | b << 16 | a << 24; }

static void formulas(void) {
    u32 c, f, k, ok = 1, maxd = 0, d, a, b;
    CHECK("F 0xFF: C x 255 >> 8 (0xFF gives 0xFE)", kh1_fog_gs(rgba(0xFF, 0x80, 0, 0x33), 0xFF, rgba(0, 0, 0xFF, 0)) ==
          rgba(0xFE, 0x7F, 0, 0x33));
    CHECK("F 0: FOGCOL x 255 >> 8", kh1_fog_gs(rgba(0xFF, 0x80, 0, 0x33), 0, rgba(0x10, 0xFF, 0x80, 0x99)) ==
          rgba(0x0F, 0xFE, 0x7F, 0x33));
    CHECK("F 0x80: half way, truncated", kh1_fog_gs(rgba(0xFF, 0, 0x81, 0), 0x80, rgba(0, 0xFF, 0x80, 0)) ==
          rgba(0x7F, 0x7E, 0x80, 0));
    for (c = 0; c < 256; c++)
        for (f = 0; f < 256; f++)
            for (k = 0; k < 256; k++) {
                u32 gs = kh1_fog_gs(c, f, k);
                if (kh1_fog_shader(c, f, k, 1) != gs) ok = 0;
                a = kh1_fog_shader(c, f, k, 0) & 0xFF;
                b = gs & 0xFF;
                d = a > b ? a - b : b - a;
                if (d > maxd) maxd = d;
            }
    CHECK("the shader's exact form is the GS's for every C, F, FOGCOL", ok);
    printf("fog_test: the float mix is at most %u from the GS\n", maxd);
    CHECK("the float mix is at most 2 from the GS", maxd <= 2);
}

/* sprites: a 16 x 16 CT32 texture drawn at frame (0, 0) 16 x 16 */
#define FBP 0x50
static u32 tex[256], under[256];

static int sweep(u32 tfx, u32 abe, u32 ate) {
    static const u32 fs[4] = { 0, 0x40, 0xC0, 0xFF }, cols[2] = { 0x00C08040, 0x00FFFFFF };
    static const u32 cv[2] = { 0x80808080u, 0x40C0A060u };
    u32 fi, ci, vi, x, y, ok = 1;
    KH1GsSprite s = { 0 };
    s.prim = 6 | 1 << 4 | 1 << 5 | abe << 6 | 1 << 8; /* SPRITE, TME, FGE, FST */
    s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
    s.tex0_lo = 0x1000 | 1u << 14 | KH1_PSMCT32 << 20 | 4u << 26;
    s.tex0_hi = 1 | 1 << 2 | tfx << 3; /* TH 4, TCC */
    s.alpha_lo = 0x44;
    s.test_lo = ate ? 1 | 6 << 1 | 0x60 << 4 : 0; /* ATST GREATER AREF 0x60, AFAIL KEEP */
    s.scissor_lo = 63u << 16;
    s.scissor_hi = 63u << 16;
    s.xy[1] = 16 << 4 | (16 << 4) << 16;
    s.uv[1] = 16 << 4 | (16 << 4) << 16;
    s.tests = 4 | (ate ? 1 : 0);
    for (fi = 0; fi < 4; fi++)
        for (ci = 0; ci < 2; ci++)
            for (vi = 0; vi < 2; vi++) {
                s.f = fs[fi];
                s.fogcol = cols[ci];
                s.rgba = cv[vi];
                for (y = 0; y < 16; y++)
                    for (x = 0; x < 16; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, FBP * 32, 1, x, y, under[y * 16 + x]);
                if (!kh1_gsmem_sprite(&s)) return 0;
                for (y = 0; y < 16; y++)
                    for (x = 0; x < 16; x++) {
                        u32 c = kh1_fog_gs(kh1_texfunc(tfx, 1, tex[y * 16 + x], s.rgba), s.f, s.fogcol), want;
                        if (ate && !(c >> 24 > 0x60)) want = under[y * 16 + x];
                        else want = abe ? kh1_blend_gs(0x44, 0, c, under[y * 16 + x], KH1_PSMCT32) : c;
                        if (kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y) != want) {
                            if (ok) printf("fog_test: tfx %u abe %u ate %u f %02x (%u, %u)\n", tfx, abe, ate, s.f, x, y);
                            ok = 0;
                        }
                    }
            }
    return ok;
}

static void sprites(void) {
    u32 x, y;
    KH1GsSprite s = { 0 };
    kh1_gsmem_reset();
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) {
            kh1_gsmem_write_pixel(KH1_PSMCT32, 0x1000, 1, x, y, (x * 0x2F1B3 + y * 0x91D7 + 0x3C) * 2654435761u);
            tex[y * 16 + x] = kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1000, 1, x, y);
            under[y * 16 + x] = (x * 0x01234567u + y * 0x89ABCDEFu) ^ 0x5A5A5A5Au;
        }
    CHECK("DECAL sprites: the fogged texel", sweep(1, 0, 0));
    CHECK("MODULATE sprites: the fogged texture function", sweep(0, 0, 0));
    CHECK("MODULATE + ABE 0x44: the fogged colour blended", sweep(0, 1, 0));
    CHECK("MODULATE + ATST GREATER: fog leaves the tested alpha", sweep(0, 0, 1));
    s.prim = 6 | 1 << 4 | 1 << 5 | 1 << 8;
    s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
    s.tex0_lo = 0x1000 | 1u << 14 | KH1_PSMCT32 << 20 | 4u << 26;
    s.tex0_hi = 1 | 1 << 2 | 1 << 3;
    s.scissor_lo = 63u << 16;
    s.scissor_hi = 63u << 16;
    s.xy[1] = 16 << 4 | (16 << 4) << 16;
    s.uv[1] = 16 << 4 | (16 << 4) << 16;
    CHECK("without tests bit 4 the model leaves FGE alone (a run's traces as before)", !kh1_gsmem_sprite(&s));
}

int main(void) {
    formulas();
    sprites();
    printf("fog_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
