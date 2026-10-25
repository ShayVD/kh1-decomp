/* The depth state a port's GPU runs (host/port/depth.c, renderer-spec 4.13 "Session 122", vita-port-plan
 * 5.1bj), tested on host/null/gsmem.c's model with made-up Zs (no game data): tests/selftest.sh builds it
 * with gcc -m32 when that works.
 *
 *   states   ZBUF / TEST decoded: the game's values (renderer B's GEQUAL, opdma's GREATER, the HUD's
 *            ALWAYS, the text headers' ZTE 0), NEVER, ZMSK; the vertex Z clamped per format (the 2D
 *            packets' 0xFFFFFFFE and -256).
 *   values   every Z24 and Z16 value: the float depth exact (its bits back), strictly increasing; a D24
 *            unorm buffer's z / 0xFFFFFF stored back as z; the GPU's compare equal to the GS's for every
 *            ZTE / ZTST on equal, adjacent and far Zs.
 *   sprites  the model's sprite (kh1_gsmem_sprite with tests 2) over a Z24 and a Z16S buffer of made-up
 *            Zs, every ZTE / ZTST / ZMSK and a vertex Z clamped: each pixel's frame and Z are what the
 *            port's compare and write give; opdma's Z-only write (ATST NEVER, AFAIL ZB_ONLY, ZTST
 *            GREATER) through atest.h's draw. */
#include "common.h"
#include "../../host/null/gsmem.h"
#include "platform/atest.h"
#include "platform/depth.h"

int printf(const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("depth_test: %s\n", name); fails++; } } while (0)

static u32 test_word(u32 ate, u32 atst, u32 afail, u32 zte, u32 ztst) {
    return ate | atst << 1 | afail << 12 | zte << 16 | ztst << 17;
}

static void states(void) {
    KH1DepthState st;
    kh1_depth_state(0x70 | 1 << 24, 0, 0x5080B, &st); /* renderer B's default TEST, the 3D Z24 */
    CHECK("renderer B: GEQUAL, written, Z24", st.draw && st.func == KH1_ZTST_GEQUAL && st.write && st.bits == 24 &&
          st.psm == KH1_PSMZ24);
    kh1_depth_state(0x70 | 1 << 24, 1, 0x5080B, &st);
    CHECK("ZMSK 1: tested, not written", st.func == KH1_ZTST_GEQUAL && !st.write);
    kh1_depth_state(0x70 | 1 << 24, 0, test_word(1, 0, 2, 1, 3), &st);
    CHECK("opdma's Z-only write: GREATER", st.func == KH1_ZTST_GREATER && st.write);
    kh1_depth_state(0x70 | 1 << 24, 0, 0x30003, &st);
    CHECK("the HUD's 0x30003: ALWAYS", st.draw && st.func == KH1_ZTST_ALWAYS && st.write);
    kh1_depth_state(0x70 | 1 << 24, 0, 0x4000D, &st);
    CHECK("the text headers' ZTE 0: ALWAYS, nothing written", st.draw && st.func == KH1_ZTST_ALWAYS && !st.write);
    kh1_depth_state(0x70 | 1 << 24, 0, 1 << 16, &st);
    CHECK("ZTST NEVER: nothing drawn", !st.draw && !st.write);
    kh1_depth_state(0x1C0 | 0xA << 24, 0, 0x5080B, &st);
    CHECK("the shadow pass's Z16S: 16 bits", st.bits == 16 && st.psm == KH1_PSMZ16S);
    CHECK("Z24 clamps 0xFFFFFFFE", kh1_depth_clamp(0xFFFFFFFEu, KH1_PSMZ24) == 0xFFFFFF);
    CHECK("Z24 clamps -256", kh1_depth_clamp((u32)-256, KH1_PSMZ24) == 0xFFFFFF);
    CHECK("Z24 keeps zmax 16777000", kh1_depth_clamp(16777000, KH1_PSMZ24) == 16777000);
    CHECK("Z16S clamps 0x10000", kh1_depth_clamp(0x10000, KH1_PSMZ16S) == 0xFFFF);
    CHECK("Z32 keeps 0xFFFFFFFE", kh1_depth_clamp(0xFFFFFFFEu, KH1_PSMZ32) == 0xFFFFFFFEu);
}

static void values(void) {
    u32 z, ok = 1, inc = 1, d24 = 1, z16 = 1, bad24 = 0, zte, ztst, i, j, cmp = 1;
    float prev = -1.0f, d;
    static const u32 zs[10] = { 0, 1, 2, 0x10000, 40000, 40001, 0x7FFFFF, 0x800000, 16777000, 0xFFFFFF };
    KH1DepthState st;
    for (z = 0; z < 0x1000000; z++) {
        d = kh1_depth_f32(z, KH1_PSMZ24);
        if (kh1_depth_bits(d, KH1_PSMZ24) != z) ok = 0;
        if (!(d > prev)) inc = 0;
        prev = d;
        if (kh1_depth_d24_store(kh1_depth_d24(z)) != z) { d24 = 0; bad24++; }
    }
    for (z = 0; z < 0x10000; z++)
        if (kh1_depth_bits(kh1_depth_f32(z, KH1_PSMZ16), KH1_PSMZ16) != z ||
            kh1_depth_f32(z, KH1_PSMZ16S) != kh1_depth_f32(z, KH1_PSMZ16))
            z16 = 0;
    CHECK("every Z24 value: the float depth's bits are z", ok);
    CHECK("every Z24 value: the float depth increases strictly", inc);
    if (!d24) printf("depth_test: D24: %u of 2^24 values not stored back\n", bad24);
    CHECK("every Z24 value: a D24 buffer stores z / 0xFFFFFF back as z", d24);
    CHECK("every Z16 / Z16S value: the float depth's bits are z", z16);
    for (zte = 0; zte < 2; zte++)
        for (ztst = 0; ztst < 4; ztst++) {
            kh1_depth_state(0x70 | 1 << 24, 0, test_word(0, 0, 0, zte, ztst), &st);
            for (i = 0; i < 10; i++)
                for (j = 0; j < 10; j++)
                    if (kh1_depth_gpu(&st, kh1_depth_f32(zs[i], KH1_PSMZ24), kh1_depth_f32(zs[j], KH1_PSMZ24)) !=
                        kh1_depth_gs(zte, ztst, zs[i], zs[j]))
                        cmp = 0;
        }
    CHECK("the GPU's compare is the GS's for every ZTE / ZTST", cmp);
}

/* sprites: a 16 x 16 CT32 texture drawn DECAL TCC 1 at frame (0, 0) 16 x 16, no blend */
#define FBP 0x50
#define ZBP 0x70
static u32 tex[256], under[256];

static u32 zat(u32 x, u32 y, u32 zbase) { return zbase - 8 + (x * 7 + y * 3) % 17; } /* around the sprite's Z */

static int sweep(u32 zpsm, u32 zvert, u32 zbase) {
    u32 zte, ztst, zm, x, y, ok = 1, zmax = zpsm == KH1_PSMZ24 ? 0xFFFFFF : 0xFFFF;
    KH1GsSprite s = { 0 };
    KH1DepthState st;
    s.prim = 6 | 1 << 4 | 1 << 8; /* SPRITE, TME, FST */
    s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
    s.zbuf_lo = ZBP | (zpsm & 15) << 24;
    s.tex0_lo = 0x1000 | 1u << 14 | KH1_PSMCT32 << 20 | 4u << 26;
    s.tex0_hi = 1 | 1 << 2 | 1 << 3; /* TH 4, TCC, DECAL */
    s.scissor_lo = 63u << 16;
    s.scissor_hi = 63u << 16;
    s.xy[1] = 16 << 4 | (16 << 4) << 16;
    s.uv[1] = 16 << 4 | (16 << 4) << 16;
    s.rgba = 0x80808080u;
    s.tests = 2;
    s.z = zvert;
    for (zte = 0; zte < 2; zte++)
        for (ztst = 0; ztst < 4; ztst++)
            for (zm = 0; zm < 2; zm++) {
                s.test_lo = test_word(0, 0, 0, zte, ztst);
                s.zbuf_hi = zm;
                kh1_depth_state(s.zbuf_lo, s.zbuf_hi, s.test_lo, &st);
                for (y = 0; y < 16; y++)
                    for (x = 0; x < 16; x++) {
                        kh1_gsmem_write_pixel(KH1_PSMCT32, FBP * 32, 1, x, y, under[y * 16 + x]);
                        kh1_gsmem_write_pixel(zpsm, ZBP * 32, 1, x, y, zat(x, y, zbase) & zmax);
                    }
                if (!kh1_gsmem_sprite(&s)) return 0;
                for (y = 0; y < 16; y++)
                    for (x = 0; x < 16; x++) {
                        u32 zb = zat(x, y, zbase) & zmax, zv = kh1_depth_clamp(zvert, zpsm);
                        int pass = kh1_depth_gpu(&st, kh1_depth_f32(zvert, zpsm), kh1_depth_f32(zb, zpsm));
                        u32 fwant = pass ? tex[y * 16 + x] : under[y * 16 + x];
                        u32 zwant = pass && st.write ? kh1_depth_bits(kh1_depth_f32(zvert, zpsm), zpsm) : zb;
                        if (kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y) != fwant ||
                            kh1_gsmem_read_pixel(zpsm, ZBP * 32, 1, x, y) != zwant || (pass && st.write && zwant != zv)) {
                            if (ok) printf("depth_test: psm %02x zte %u ztst %u zmsk %u (%u, %u)\n", zpsm, zte, ztst, zm, x, y);
                            ok = 0;
                        }
                    }
            }
    return ok;
}

/* opdma func_001aaf00's Z-only writes: ATST NEVER, AFAIL ZB_ONLY, ZTST GREATER, through atest.h's draw */
static int zonly(void) {
    u32 x, y, ok = 1, zvert = 40000;
    KH1GsSprite s = { 0 };
    KH1DepthState st;
    KH1AtestState at;
    s.prim = 6 | 1 << 4 | 1 << 8;
    s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
    s.zbuf_lo = ZBP | 1 << 24;
    s.tex0_lo = 0x1000 | 1u << 14 | KH1_PSMCT32 << 20 | 4u << 26;
    s.tex0_hi = 1 | 1 << 2 | 1 << 3;
    s.scissor_lo = 63u << 16;
    s.scissor_hi = 63u << 16;
    s.xy[1] = 16 << 4 | (16 << 4) << 16;
    s.uv[1] = 16 << 4 | (16 << 4) << 16;
    s.rgba = 0x80808080u;
    s.tests = 3;
    s.z = zvert;
    s.test_lo = test_word(1, 0, 2, 1, 3);
    kh1_depth_state(s.zbuf_lo, 0, s.test_lo, &st);
    kh1_atest_state(s.test_lo, 0xF, 0, &at);
    if (at.n != 1 || at.draw[0].mask || !at.draw[0].zwrite) return 0;
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) {
            kh1_gsmem_write_pixel(KH1_PSMCT32, FBP * 32, 1, x, y, under[y * 16 + x]);
            kh1_gsmem_write_pixel(KH1_PSMZ24, ZBP * 32, 1, x, y, zat(x, y, zvert));
        }
    if (!kh1_gsmem_sprite(&s)) return 0;
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) {
            u32 zb = zat(x, y, zvert);
            int pass = kh1_depth_gpu(&st, kh1_depth_f32(zvert, KH1_PSMZ24), kh1_depth_f32(zb, KH1_PSMZ24));
            if (kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y) != under[y * 16 + x] ||
                kh1_gsmem_read_pixel(KH1_PSMZ24, ZBP * 32, 1, x, y) != (pass ? zvert : zb))
                ok = 0;
        }
    return ok;
}

static void sprites(void) {
    u32 x, y;
    kh1_gsmem_reset();
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) {
            kh1_gsmem_write_pixel(KH1_PSMCT32, 0x1000, 1, x, y, (x * 0x2F1B3 + y * 0x91D7 + 0x3C) * 2654435761u);
            tex[y * 16 + x] = kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1000, 1, x, y);
            under[y * 16 + x] = (x * 0x01234567u + y * 0x89ABCDEFu) ^ 0x5A5A5A5Au;
        }
    CHECK("Z24 sprites: every ZTE / ZTST / ZMSK as the port's compare and write", sweep(KH1_PSMZ24, 40000, 40000));
    CHECK("Z24 sprites near the top: z 0xFFFFF8", sweep(KH1_PSMZ24, 0xFFFFF8, 0xFFFFF0));
    CHECK("Z24 sprites: a vertex Z of 0xFFFFFFFE clamped", sweep(KH1_PSMZ24, 0xFFFFFFFEu, 0xFFFFF7));
    CHECK("Z16S sprites: every ZTE / ZTST / ZMSK", sweep(KH1_PSMZ16S, 0x8000, 0x8000));
    CHECK("Z16S sprites: a Z24-range vertex Z clamped to 0xFFFF", sweep(KH1_PSMZ16S, 16777000, 0xFFF7));
    CHECK("opdma's Z-only write: Z where GREATER, the frame kept", zonly());
}

int main(void) {
    states();
    values();
    sprites();
    printf("depth_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
