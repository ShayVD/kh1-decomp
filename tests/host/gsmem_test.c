/* host/null/gsmem.c on made-up pixels (no game data): tests/selftest.sh builds it with gcc -m32 when
 * that works, fed through host/null/gsregs.c's registers and host/null/dmawalk.c's IMAGE reader the
 * way the host run feeds it.  The fixed addresses below were checked against PCSX2's swizzle tables
 * (session 80, outside the repo). */
#include "common.h"
#include "../../host/null/dmawalk.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"

int printf(const char *, ...);

int kh1_host_trace = 2;

static u32 mem[64][4] ALIGNED(16);

static const char *where(u32 a, u32 n) {
    return a >= (u32)(unsigned long)mem && a + n <= (u32)(unsigned long)mem + sizeof mem ? "mem" : 0;
}

#define A(i) ((u32)(unsigned long)mem[i])
static void q(int i, u32 a, u32 b, u32 c, u32 d) { mem[i][0] = a; mem[i][1] = b; mem[i][2] = c; mem[i][3] = d; }

static int fails;
#define CHECK(name, cond) do { if (!(cond)) { printf("gsmem_test: %s\n", name); fails++; } } while (0)

/* the four A+D writes that start an upload of w x h pixels at (x, y) of buffer bp / bw / psm */
static void upload(u32 bp, u32 bw, u32 psm, u32 x, u32 y, u32 w, u32 h) {
    kh1_gs_write(0x50, 0, bp | bw << 16 | psm << 24);
    kh1_gs_write(0x51, 0, x | y << 16);
    kh1_gs_write(0x52, w, h);
    kh1_gs_write(0x53, 0, 0);
}

static u32 words[1024];
static void image(u32 n) { u32 i; for (i = 0; i < n; i += 4) kh1_gsmem_image(words + i, 4); }

static u32 tex[64 * 64];

int main(void) {
    const KH1GsMemStats *st = kh1_gsmem_stats();
    u32 i, x, y, ok, s0;

    /* addresses: blocks inside a page, pixels inside a block, pages by BW */
    CHECK("CT32 (8,0)", kh1_gsmem_addr(KH1_PSMCT32, 0, 1, 8, 0) == 64);
    CHECK("CT32 (0,8)", kh1_gsmem_addr(KH1_PSMCT32, 0, 1, 0, 8) == 128);
    CHECK("CT32 (3,5)", kh1_gsmem_addr(KH1_PSMCT32, 0, 1, 3, 5) == 39);
    CHECK("CT32 page by BW", kh1_gsmem_addr(KH1_PSMCT32, 0, 2, 64, 0) == 2048 &&
                             kh1_gsmem_addr(KH1_PSMCT32, 0, 2, 0, 32) == 4096);
    CHECK("CT32 bp", kh1_gsmem_addr(KH1_PSMCT32, 5, 1, 0, 0) == 320);
    CHECK("CT16 (8,0) (16,0)", kh1_gsmem_addr(KH1_PSMCT16, 0, 1, 8, 0) == 1 &&
                               kh1_gsmem_addr(KH1_PSMCT16, 0, 1, 16, 0) == 256);
    CHECK("T8 (0,2) (16,0) (1,4)", kh1_gsmem_addr(KH1_PSMT8, 0, 2, 0, 2) == 33 &&
                                   kh1_gsmem_addr(KH1_PSMT8, 0, 2, 16, 0) == 256 &&
                                   kh1_gsmem_addr(KH1_PSMT8, 0, 2, 1, 4) == 100);
    CHECK("T8 page by BW", kh1_gsmem_addr(KH1_PSMT8, 0, 2, 0, 64) == 8192);
    CHECK("T4 (0,2) (32,0) (8,0)", kh1_gsmem_addr(KH1_PSMT4, 0, 2, 0, 2) == 65 &&
                                   kh1_gsmem_addr(KH1_PSMT4, 0, 2, 32, 0) == 1024 &&
                                   kh1_gsmem_addr(KH1_PSMT4, 0, 2, 8, 0) == 2);
    CHECK("T4HL shares CT32", kh1_gsmem_addr(KH1_PSMT4HL, 0, 1, 3, 5) == 39);
    CHECK("Z32 not modelled", kh1_gsmem_addr(0x30, 0, 1, 0, 0) == ~0u);

    /* an upload per PSM, read back pixel by pixel */
    kh1_gs_reset();
    for (i = 0; i < 1024; i++) words[i] = i * 0x01030507u + 0x11;
    upload(0x100, 1, KH1_PSMCT32, 3, 2, 16, 16);
    image(256);
    for (ok = 1, i = 0; i < 256; i++) ok &= kh1_gsmem_read_pixel(KH1_PSMCT32, 0x100, 1, 3 + i % 16, 2 + i / 16) == words[i];
    CHECK("CT32 upload", ok && st->uploads == 1 && st->pixels == 256 && st->extra == 0);
    kh1_gsmem_image(words, 4);
    CHECK("IMAGE past the end is extra", st->extra == 1);
    upload(0x200, 2, KH1_PSMT8, 0, 0, 32, 32);
    image(256);
    for (ok = 1, i = 0; i < 1024; i++)
        ok &= kh1_gsmem_read_pixel(KH1_PSMT8, 0x200, 2, i % 32, i / 32) == (words[i / 4] >> i % 4 * 8 & 0xFF);
    CHECK("T8 upload", ok);
    upload(0x400, 2, KH1_PSMT4, 0, 0, 64, 32);
    image(256);
    for (ok = 1, i = 0; i < 2048; i++)
        ok &= kh1_gsmem_read_pixel(KH1_PSMT4, 0x400, 2, i % 64, i / 64) == (words[i / 8] >> i % 8 * 4 & 15);
    CHECK("T4 upload (low nibble first)", ok);
    upload(0x600, 1, KH1_PSMCT16, 0, 0, 16, 16);
    image(128);
    for (ok = 1, i = 0; i < 256; i++)
        ok &= kh1_gsmem_read_pixel(KH1_PSMCT16, 0x600, 1, i % 16, i / 16) == (words[i / 2] >> i % 2 * 16 & 0xFFFF);
    CHECK("CT16 upload", ok);
    /* CT24: 3 bytes a pixel across the words, the top byte left alone */
    upload(0x100, 1, KH1_PSMCT24, 3, 2, 4, 1);
    words[0] = 0x44332211; words[1] = 0x88776655; words[2] = 0xCCBBAA99; words[3] = 0;
    image(4);
    CHECK("CT24 packing", kh1_gsmem_read_pixel(KH1_PSMCT32, 0x100, 1, 4, 2) >> 24 ==
                          (u32)((1 * 0x01030507u + 0x11) >> 24) &&
                          (kh1_gsmem_read_pixel(KH1_PSMCT32, 0x100, 1, 4, 2) & 0xFFFFFF) == 0x665544 &&
                          kh1_gsmem_read_pixel(KH1_PSMCT24, 0x100, 1, 6, 2) == 0xCCBBAA);

    /* the font in the Z buffer's top byte: T4HL then T4HH over a Z24 pattern keep the Z bits */
    for (y = 0; y < 8; y++)
        for (x = 0; x < 8; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x1000, 1, x, y, 0x00ABCDEF);
    upload(0x1000, 1, KH1_PSMT4HL, 0, 0, 8, 8);
    for (i = 0; i < 8; i++) words[i] = 0x76543210;
    image(8);
    upload(0x1000, 1, KH1_PSMT4HH, 0, 0, 8, 8);
    for (i = 0; i < 8; i++) words[i] = 0x89ABCDEF;
    image(8);
    for (ok = 1, i = 0; i < 64; i++) {
        u32 v = kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1000, 1, i % 8, i / 8);
        ok &= (v & 0xFFFFFF) == 0xABCDEF && (v >> 24 & 15) == i % 8 && v >> 28 == 15 - i % 8;
    }
    CHECK("T4HL / T4HH keep the Z bits", ok);

    /* a 4-bit CLUT: two CT32 8 x 2 CLUTs loaded at CSA 0 (TEX0, CLD 1) and CSA 1 (TEX2, CLD 1), then
     * a T4 texture read with each */
    upload(0x2000, 1, KH1_PSMCT32, 0, 0, 8, 2);
    for (i = 0; i < 16; i++) words[i] = 0x80000000u | i;
    image(16);
    upload(0x2004, 1, KH1_PSMCT32, 0, 0, 8, 2);
    for (i = 0; i < 16; i++) words[i] = 0x40000000u | i << 8;
    image(16);
    upload(0x2100, 2, KH1_PSMT4, 0, 0, 8, 8);
    for (i = 0; i < 8; i++) words[i] = 0xFEDCBA98u - i;
    image(8);
    s0 = kh1_gsmem_clut_stamp();
    /* TEX0_1: TBP0 0x2100 TBW 2 PSMT4 TW 3 TH 3, CBP 0x2000 CPSM CT32 CSA 0 CLD 1 */
    kh1_gs_write(0x06, 0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30, 0x2000 << 5 | 1u << 29);
    CHECK("TEX0 CLD 1 loads", kh1_gsmem_clut_stamp() == s0 + 1 && st->clut_loads == 1);
    kh1_gs_write(0x06, 0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30, 0x2000 << 5);
    CHECK("TEX0 CLD 0 does not", st->clut_loads == 1);
    /* TEX2_1: PSMT4, CBP 0x2004, CSA 1, CLD 1 */
    kh1_gs_write(0x16, KH1_PSMT4 << 20, 0x2004 << 5 | 1 << 24 | 1u << 29);
    CHECK("TEX2 CLD 1 loads", st->clut_loads == 2);
    CHECK("read CSA 0", kh1_gsmem_read_tex(0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30, 0x2000 << 5,
                                           0, 0, tex) == 0 && tex[0] == 0x80000008 && tex[1] == 0x80000009);
    CHECK("read CSA 1", kh1_gsmem_read_tex(0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30,
                                           0x2004 << 5 | 1 << 24, 0, 0, tex) == 0 &&
                        tex[0] == 0x40000800 && tex[15] == 0x40000F00);
    /* CLD 2 then 4: a load with CBP0 set, then CLD 4 with the same CBP does not load again */
    kh1_gs_write(0x06, 0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30, 0x2000 << 5 | 2u << 29);
    kh1_gs_write(0x06, 0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30, 0x2000 << 5 | 4u << 29);
    CHECK("CLD 2 then 4", st->clut_loads == 3);

    /* an 8-bit CLUT: the 16 x 16 stored entries 8-15 and 16-23 of each 32 swapped */
    upload(0x2200, 1, KH1_PSMCT32, 0, 0, 16, 16);
    for (i = 0; i < 256; i++) words[i] = i;
    image(256);
    upload(0x2300, 2, KH1_PSMT8, 0, 0, 16, 1);
    words[0] = 0x03020100; words[1] = 0x07060504; words[2] = 0x0B0A0908; words[3] = 0x13121110;
    image(4);
    kh1_gs_write(0x06, 0x2300 | 2 << 14 | KH1_PSMT8 << 20 | 4 << 26 | 0u << 30, 0x2200 << 5 | 1u << 29);
    CHECK("read T8", kh1_gsmem_read_tex(0x2300 | 2 << 14 | KH1_PSMT8 << 20 | 4 << 26, 0x2200 << 5, 0, 0, tex) == 0 &&
                     tex[0] == 0 && tex[7] == 7 && tex[8] == 16 && tex[11] == 19 && tex[12] == 8 && tex[15] == 11);
    /* the text windows' glyphs (renderer-spec 4.9): 4-bit reads at CSA 0 / 1 (CLD 0) of the 8-bit CLUT
     * the header loaded, so CSA 1's entries 16-23 are the stored row 0's x 8-15 */
    CHECK("T4 CSA 1 of an 8-bit CLUT", kh1_gsmem_read_tex(0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30,
                                                          0x2200 << 5 | 1 << 24, 0, 0, tex) == 0 &&
                                       tex[0] == 24 && tex[8] == 15);

    /* CT16 and CT24 alpha from TEXA (TA0 0x40, AEM 1, TA1 0x80) */
    upload(0x2400, 1, KH1_PSMCT16, 0, 0, 2, 1);
    words[0] = 0x801F0000 | 0x7C00;
    image(4);
    kh1_gsmem_read_tex(0x2400 | 1 << 14 | KH1_PSMCT16 << 20 | 1 << 26, 0, 0x40 | 1 << 15, 0x80, tex);
    CHECK("CT16 TEXA", tex[0] == 0x40F80000 && tex[1] == 0x800000F8);
    kh1_gsmem_write_pixel(KH1_PSMCT32, 0x2500, 1, 0, 0, 0x12000000);
    kh1_gsmem_write_pixel(KH1_PSMCT32, 0x2500, 1, 1, 0, 0x12000001);
    kh1_gsmem_read_tex(0x2500 | 1 << 14 | KH1_PSMCT24 << 20 | 1 << 26, 0, 0x40 | 1 << 15, 0x80, tex);
    CHECK("CT24 TEXA (AEM black)", tex[0] == 0 && tex[1] == 0x40000001);

    /* a local->local copy, and the cache stamp: moved by a write to the texture's page only */
    s0 = kh1_gsmem_tex_stamp(0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30, 0);
    kh1_gs_write(0x50, 0x100 | 1 << 16, 0x3000 | 1 << 16);
    kh1_gs_write(0x51, 3 | 2 << 16, 0);
    kh1_gs_write(0x52, 16, 16);
    kh1_gs_write(0x53, 2, 0);
    for (ok = 1, i = 0; i < 256; i++)
        ok &= kh1_gsmem_read_pixel(KH1_PSMCT32, 0x3000, 1, i % 16, i / 16) ==
              kh1_gsmem_read_pixel(KH1_PSMCT32, 0x100, 1, 3 + i % 16, 2 + i / 16);
    CHECK("local->local copy", ok && st->copies == 1);
    CHECK("stamp: other page", kh1_gsmem_tex_stamp(0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30, 0) == s0);
    kh1_gsmem_write_pixel(KH1_PSMT4, 0x2100, 2, 5, 5, 1);
    CHECK("stamp: same page", kh1_gsmem_tex_stamp(0x2100 | 2 << 14 | KH1_PSMT4 << 20 | 3 << 26 | 3u << 30, 0) > s0);

    /* through the GIF reader: an A+D packet then an IMAGE packet of 2 qwords (8 CT32 pixels) */
    kh1_gs_reset();
    q(0, 0x70000008, 0, 0, 0);
    q(1, 4 | 1 << 15, 1 << 28, 0xE, 0);
    q(2, 0, 0x3100 | 4 << 16, 0x50, 0);
    q(3, 0, 0, 0x51, 0);
    q(4, 4, 2, 0x52, 0);
    q(5, 0, 0, 0x53, 0);
    q(6, 2 | 1 << 15, 2u << 26, 0, 0);
    q(7, 1, 2, 3, 4);
    q(8, 5, 6, 7, 8);
    CHECK("image walk", kh1_dma_walk(2, 0x104, A(0), where) == 0);
    CHECK("image through the GIF", kh1_gsmem_read_pixel(KH1_PSMCT32, 0x3100, 4, 3, 0) == 4 &&
                                   kh1_gsmem_read_pixel(KH1_PSMCT32, 0x3100, 4, 0, 1) == 5 &&
                                   kh1_gsmem_read_pixel(KH1_PSMCT32, 0x3100, 4, 3, 1) == 8 && st->pixels == 8);
    {
        KH1GsUpload u[2];
        CHECK("upload log", kh1_gsmem_log(u, 2) == 1 && u[0].bp == 0x3100 && u[0].bw == 4 && u[0].w == 4 &&
                            u[0].h == 2 && u[0].pixels == 8 && u[0].dir == 0);
    }
    CHECK("unsupported", st->unsupported == 0);
    upload(0x3200, 1, 0x30, 0, 0, 4, 1);
    image(4);
    CHECK("Z32 upload counted, data taken", st->unsupported == 1 && st->pixels == 12 && st->extra == 0);

    if (fails) { printf("gsmem_test: %d failed\n", fails); return 1; }
    printf("gsmem_test: PASS\n");
    return 0;
}
