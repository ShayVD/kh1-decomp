/* The alpha test and destination alpha test a port's GPU runs (host/port/atest.c, renderer-spec 4.13
 * "Session 121", vita-port-plan 5.1bi), tested on host/null/gsmem.c's model with made-up colours (no game
 * data): tests/selftest.sh builds it with gcc -m32 when that works.
 *
 *   compare  the eight ATST methods for every alpha and AREF.
 *   states   every ATE / ATST / AFAIL / DATE / DATM / ZTE / ZTST with six AREFs, four write masks and
 *            ZMSK 0 / 1: the port's draws (discards, masks, the stencil set-up on blend.h's 0x80-scale
 *            stored alpha) write what the GS writes for every fragment alpha and four frame alphas, in
 *            at most two draws; the game's TEST values in one.
 *   sprites  the model's sprite (kh1_gsmem_sprite with tests 1, DECAL TCC 1, ABE (Cs - Cd) x As + Cd) under
 *            each ATST and AFAIL and DATE / DATM over a frame with made-up alphas: every pixel is the GS's
 *            blend where the port's draws write, the frame's bytes where they do not. */
#include "common.h"
#include "../../host/null/gsmem.h"
#include "platform/blend.h"
#include "platform/atest.h"

int printf(const char *, ...);
int sprintf(char *, const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("atest_test: %s\n", name); fails++; } } while (0)

static u32 test_word(u32 ate, u32 atst, u32 aref, u32 afail, u32 date, u32 datm, u32 zte, u32 ztst) {
    return ate | atst << 1 | aref << 4 | afail << 12 | date << 14 | datm << 15 | zte << 16 | ztst << 17;
}

static void compare(void) {
    u32 m, a, r, ok = 1, want;
    for (m = 0; m < 8; m++)
        for (a = 0; a < 256; a++)
            for (r = 0; r < 256; r++) {
                want = m == 0 ? 0 : m == 1 ? 1 : m == 2 ? a < r : m == 3 ? a <= r : m == 4 ? a == r : m == 5 ? a >= r : m == 6 ? a > r : a != r;
                if ((u32)kh1_atest(m, a, r) != want) ok = 0;
            }
    CHECK("the eight methods for every alpha and AREF", ok);
}

static void states(void) {
    static const u32 arefs[6] = { 0, 16, 120, 127, 128, 255 }, masks[4] = { 0xF, 0x8, 0x7, 0 }, ads[4] = { 0, 0x7F, 0x80, 0xFF };
    u32 ate, atst, afail, date, datm, zte, ztst, r, mk, zm, a, i, t, ok = 1, n2 = 0, many = 0;
    KH1AtestState st;
    char msg[96];
    for (ate = 0; ate < 2; ate++)
        for (atst = 0; atst < 8; atst++)
            for (afail = 0; afail < 4; afail++)
                for (date = 0; date < 2; date++)
                    for (datm = 0; datm < 2; datm++)
                        for (zte = 0; zte < 2; zte++)
                            for (ztst = 0; ztst < 4; ztst++)
                                for (r = 0; r < 6; r++)
                                    for (mk = 0; mk < 4; mk++)
                                        for (zm = 0; zm < 2; zm++) {
                                            t = test_word(ate, atst, arefs[r], afail, date, datm, zte, ztst);
                                            kh1_atest_state(t, masks[mk], zm, &st);
                                            if (st.n > 2) many++;
                                            if (st.n == 2) n2++;
                                            for (a = 0; a < 256; a++)
                                                for (i = 0; i < 4; i++)
                                                    if (kh1_atest_gpu(&st, a, kh1_atest_date_mark(&st, kh1_blend_store_alpha(ads[i]))) !=
                                                        kh1_atest_gs(t, masks[mk], zm, a, ads[i])) {
                                                        if (ok) printf("atest_test: TEST %05x mask %x ZMSK %u a %02x ad %02x\n", t, masks[mk], zm, a, ads[i]);
                                                        ok = 0;
                                                    }
                                        }
    CHECK("every TEST: the port's draws write what the GS writes", ok);
    sprintf(msg, "at most two draws (%u states take two)", n2);
    CHECK(msg, !many);
    printf("atest_test: %u of %u states take two draws\n", n2, 2u * 8 * 4 * 2 * 2 * 2 * 4 * 6 * 4 * 2);
    /* the game's (renderer-spec 3.2 TEST), each with ZMSK 0 and 1: one draw */
    {
        static const u32 game[] = {
            0x0001 | 6 << 1 | 1 << 16 | 2 << 17,   /* GREATER 0, GEQUAL */
            0x0001 | 6 << 1 | 1 << 16 | 1 << 17,   /* GREATER 0, ALWAYS */
            0x0001 | 6 << 1,                       /* GREATER 0, ZTE 0 */
            0x30003,                               /* the HUD: ALWAYS, ALWAYS */
            0x0001 | 7 << 1 | 1 << 16 | 1 << 17,   /* NOTEQUAL 0 */
            0x0001 | 5 << 1 | 120 << 4 | 1 << 16 | 1 << 17, /* GEQUAL 120 */
            0x0001 | 1 << 12 | 1 << 16 | 1 << 17,  /* NEVER FB_ONLY */
            0x0001 | 1 << 12 | 1 << 16 | 2 << 17,  /* NEVER FB_ONLY, GEQUAL */
            0x0001 | 2 << 12 | 1 << 16 | 3 << 17,  /* NEVER ZB_ONLY, GREATER (opdma) */
            1 << 14 | 1 << 15 | 1 << 16 | 1 << 17, /* DATE DATM 1 */
            0x5010D, 0x507FD, 0x5000D, 0x31001, 0x5080B, /* TEST_2 from the C, renderer B's default */
            0x0001 | 2 << 1 | 120 << 4 | 1 << 16 | 2 << 17, /* renderer B pass 2: LESS 120 */
        };
        u32 g, one = 1;
        for (g = 0; g < sizeof(game) / sizeof(game[0]); g++)
            for (zm = 0; zm < 2; zm++) {
                kh1_atest_state(game[g], 0xF, zm, &st);
                if (st.n > 1) { printf("atest_test: game TEST %05x ZMSK %u takes %u draws\n", game[g], zm, st.n); one = 0; }
            }
        CHECK("the game's TEST values: one draw each", one);
        kh1_atest_state(0x0001 | 2 << 12 | 1 << 16 | 3 << 17, 0xF, 0, &st);
        CHECK("NEVER ZB_ONLY: one draw, Z only, no discard", st.n == 1 && !st.draw[0].mask && st.draw[0].zwrite && !st.draw[0].discard);
        kh1_atest_state(0x0001 | 6 << 1 | 1 << 16 | 2 << 17, 0xF, 0, &st);
        CHECK("GREATER 0 KEEP: discard where it fails", st.n == 1 && st.draw[0].discard == KH1_DISCARD_FAIL && st.ztest == 1);
        kh1_atest_state(0x0001 | 6 << 1 | 1 << 12 | 1 << 16 | 2 << 17, 0xF, 0, &st);
        CHECK("GREATER 0 FB_ONLY with a Z write: two draws", st.n == 2 && st.draw[1].discard == KH1_DISCARD_PASS && !st.draw[1].zwrite);
        kh1_atest_state(0x0001 | 6 << 1 | 1 << 12 | 1 << 16 | 2 << 17, 0xF, 1, &st);
        CHECK("GREATER 0 FB_ONLY, ZMSK 1: one draw, no discard", st.n == 1 && !st.draw[0].discard);
        CHECK("DATE: 0x7F stores below 1.0, 0x80 at it", kh1_blend_store_alpha(0x7F) < 255 && kh1_blend_store_alpha(0x80) == 255);
    }
}

#define FBP 0x50
static u32 tex[256], under[256];

static void sprites(void) {
    static const u32 tests[] = { 0, 1 << 14, 1 << 14 | 1 << 15 };
    u32 atst, afail, dt, x, y, ok = 1, drawn = 1, tbp = 0x1000, t;
    KH1GsSprite s = { 0 };
    KH1AtestState st;
    kh1_gsmem_reset();
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) {
            kh1_gsmem_write_pixel(KH1_PSMCT32, tbp, 1, x, y, ((x * 0x2F1B3 + y * 0x91D7 + 0x3C) * 2654435761u & 0xFFFFFF) | (y * 16 + x) << 24);
            tex[y * 16 + x] = kh1_gsmem_read_pixel(KH1_PSMCT32, tbp, 1, x, y);
            under[y * 16 + x] = ((x * 0x01234567u + y * 0x89ABCDEFu) & 0xFFFFFF) | ((x * 37 + y * 101) & 0xFF) << 24;
        }
    s.prim = 6 | 1 << 4 | 1 << 6 | 1 << 8; /* SPRITE, TME, ABE, FST */
    s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
    s.tex0_lo = tbp | 1u << 14 | KH1_PSMCT32 << 20 | 4u << 26;
    s.tex0_hi = 1 | 1 << 2 | 1 << 3; /* TH 4, TCC, DECAL */
    s.alpha_lo = 0x44;
    s.scissor_lo = 63u << 16;
    s.scissor_hi = 63u << 16;
    s.xy[1] = 16 << 4 | (16 << 4) << 16;
    s.uv[1] = 16 << 4 | (16 << 4) << 16;
    s.rgba = 0x80808080u;
    s.tests = 1;
    for (atst = 0; atst < 8; atst++)
        for (afail = 0; afail < 4; afail++)
            for (dt = 0; dt < 3; dt++) {
                t = 1 | atst << 1 | 0x60 << 4 | afail << 12 | tests[dt]; /* ZTE 0 */
                s.test_lo = t;
                kh1_atest_state(t, 0xF, 1, &st);
                for (y = 0; y < 16; y++)
                    for (x = 0; x < 16; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, FBP * 32, 1, x, y, under[y * 16 + x]);
                if (!kh1_gsmem_sprite(&s)) { drawn = 0; continue; }
                for (y = 0; y < 16; y++)
                    for (x = 0; x < 16; x++) {
                        u32 i = y * 16 + x, w, m = 0, b, want, got;
                        w = kh1_atest_gpu(&st, tex[i] >> 24, kh1_atest_date_mark(&st, kh1_blend_store_alpha(under[i] >> 24)));
                        for (b = 0; b < 4; b++)
                            if (w >> b & 1) m |= 0xFFu << b * 8;
                        want = (kh1_blend_gs(0x44, 0, tex[i], under[i], KH1_PSMCT32) & m) | (under[i] & ~m);
                        got = kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y);
                        if (got != want) {
                            if (ok) printf("atest_test: TEST %05x (%u, %u): %08x, want %08x\n", t, x, y, got, want);
                            ok = 0;
                        }
                    }
            }
    CHECK("the model drew each sprite", drawn);
    CHECK("every ATST / AFAIL / DATE: the model's pixels are what the port's draws write", ok);
    /* tests 0 keeps the old refusal (gsregs.c's runs) */
    s.tests = 0;
    s.test_lo = 1 | 6 << 1;
    CHECK("tests 0: an alpha-tested sprite is still refused", !kh1_gsmem_sprite(&s));
}

int main(void) {
    compare();
    states();
    sprites();
    printf("atest_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
