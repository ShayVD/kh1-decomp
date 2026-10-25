/* host/null/present.c, the host "present" (KH1_HOST_SHOT, session 94), on made-up pixels in the GS
 * memory model (no game data): tests/selftest.sh builds it with gcc -m32 when that works.  argv[1]:
 * a scratch directory for the one shot it writes. */
#include "common.h"
#include "../../host/null/dmawalk.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"
#include "../../host/null/present.h"
#include "platform/canvas.h"

int printf(const char *, ...);
void *fopen(const char *, const char *);
int fclose(void *);
int sprintf(char *, const char *, ...);
int fseek(void *, long, int);
__SIZE_TYPE__ fread(void *, __SIZE_TYPE__, __SIZE_TYPE__, void *);

int kh1_host_trace = 2;
unsigned long kh1_host_frame(void) { return 7; }

static u32 mem[8][4] ALIGNED(16);
static u32 pkt[48][4] ALIGNED(16); /* session 97: a frame copy's packet, sent by a REFE tag in mem */
static u32 pkt2[48][4] ALIGNED(16); /* session 98: the Z-area copy's or the spin copy's, a REFE tag at mem[2] */
static u8 rgb[960 * 544 * 3];

static const char *where(u32 a, u32 n) {
    if (a >= (u32)(unsigned long)pkt && a + n <= (u32)(unsigned long)pkt + sizeof pkt) return "pkt";
    if (a >= (u32)(unsigned long)pkt2 && a + n <= (u32)(unsigned long)pkt2 + sizeof pkt2) return "pkt2";
    return a >= (u32)(unsigned long)mem && a + n <= (u32)(unsigned long)mem + sizeof mem ? "mem" : 0;
}

static void q4(int i, u32 a, u32 b, u32 c, u32 d) { pkt[i][0] = a; pkt[i][1] = b; pkt[i][2] = c; pkt[i][3] = d; }
static void p4(int i, u32 a, u32 b, u32 c, u32 d) { pkt2[i][0] = a; pkt2[i][1] = b; pkt2[i][2] = c; pkt2[i][3] = d; }

/* the frame copy's shape (renderer-spec 4.15 / 5.4 "Session 97", brightfade.c's D_002A6890: one REFE of
 * 0x2C qwords): 6 x A+D (FRAME_1 the display CT24 FBW 8, ZBUF_1 ZMSK, TEX0_1 the target 0x1A00 CT24 512 x
 * 512 TCC MODULATE, TEST_1 ZTST ALWAYS, TEX1_1 bilinear, ALPHA_1 (Cs - Cd) As + Cd), REGLIST PRIM
 * 0x116 SPRITE|TME|FST (session 98: no ABE, so the ALPHA_1 is unused) and RGBAQ 0x80, REGLIST 16 x
 * (UV XYZ2 UV XYZ2): strip k is x 32k .. 32k + 32 of
 * the 448 display lines, u 32k + 0.5 .. 32k + 32.5 and v 0 .. 384 (the target's lines), then ZBUF_1
 * back with ZMSK 0.  Written as a REFE tag at mem[0] for the chain walk. */
static int copy_packet(void) {
    int i = 0, k;
    q4(i++, 1, 6u << 28, 0xEEEEEE, 0);
    q4(i++, 0 | 8 << 16 | KH1_PSMCT24 << 24, 0, 0x4C, 0);
    q4(i++, 0x70 | 0x31u << 24, 1, 0x4E, 0);
    q4(i++, 0x1A00 | 8 << 14 | KH1_PSMCT24 << 20 | 9u << 26 | 1u << 30, 2 | 1 << 2, 0x06, 0);
    q4(i++, 1 << 16 | 1 << 17, 0, 0x47, 0);
    q4(i++, 1 << 5 | 1 << 6, 0, 0x14, 0);
    q4(i++, 0x44, 0, 0x42, 0);
    q4(i++, 1, 1u << 26 | 2u << 28, 0x10, 0);
    q4(i++, 6 | 1 << 4 | 1 << 8, 0, 0x80808080, 0x3F800000);
    q4(i++, 16, 1u << 26 | 4u << 28, 0x5353, 0);
    for (k = 0; k < 16; k++) {
        q4(i++, (u32)(k * 512 + 8), 0, (u32)(0x7000 + k * 512) | 0x7400u << 16, 0xFFFFFFFE);
        q4(i++, (u32)(k * 512 + 512 + 8) | 0x1800u << 16, 0, (u32)(0x7000 + k * 512 + 512) | 0x9000u << 16, 0xFFFFFFFE);
    }
    q4(i++, 1 | 1 << 15, 1u << 28, 0xE, 0);
    q4(i++, 0x70 | 0x31u << 24, 0, 0x4E, 0);
    mem[0][0] = (u32)i; /* REFE, qwc */
    mem[0][1] = (u32)(unsigned long)pkt;
    mem[0][2] = mem[0][3] = 0;
    return i;
}

/* session 98: the Z-area copy's shape (sceneeff.c's D_002A5FD0: one REFE of 0x2F qwords at D_002A5CE0):
 * 6 x A+D (ZBUF_1 ZBP 0 ZMSK, FRAME_1 FBP 0x70 FBW 8 CT24: the Z buffer's memory as colour, TEX0_1 the
 * target 0x1A00 CT24 512 x 512 TCC MODULATE, TEST_1 ZTST ALWAYS, ALPHA_1, TEX1_1 bilinear), REGLIST PRIM
 * 0x116 and RGBAQ 0x80, REGLIST 16 x (UV XYZ2 UV XYZ2): strip k is x 32k - 1.5 .. 32k + 30.5 over y -1.5
 * .. 382.5, u 32k .. 32k + 32 and v 0 .. 384 (one texel a pixel, 1.5 texels up and left), then an EOP
 * ZBUF_1 back (0x70, ZMSK 0) and FRAME_1 the target.  Its tag at mem[2]. */
static void zcopy_packet(void) {
    int i = 0, k;
    p4(i++, 1, 6u << 28, 0xEEEEEE, 0);
    p4(i++, 0 | 0x31u << 24, 1, 0x4E, 0);
    p4(i++, 0x70 | 8 << 16 | KH1_PSMCT24 << 24, 0, 0x4C, 0);
    p4(i++, 0x1A00 | 8 << 14 | KH1_PSMCT24 << 20 | 9u << 26 | 1u << 30, 2 | 1 << 2, 0x06, 0);
    p4(i++, 1 << 16 | 1 << 17, 0, 0x47, 0);
    p4(i++, 0x44, 0, 0x42, 0);
    p4(i++, 1 << 5 | 1 << 6, 0, 0x14, 0);
    p4(i++, 1, 1u << 26 | 2u << 28, 0x10, 0);
    p4(i++, 6 | 1 << 4 | 1 << 8, 0, 0x80808080, 0x3F800000);
    p4(i++, 16, 1u << 26 | 4u << 28, 0x5353, 0);
    for (k = 0; k < 16; k++) {
        p4(i++, (u32)(k * 512), 0, (u32)(0x6FE8 + k * 512) | 0x73E8u << 16, 0xFFFFFFFE);
        p4(i++, (u32)(k * 512 + 512) | 0x1800u << 16, 0, (u32)(0x6FE8 + k * 512 + 512) | 0x8BE8u << 16, 0xFFFFFFFE);
    }
    p4(i++, 1 | 1 << 15, 2u << 28, 0xCE, 0);
    p4(i++, 0x70 | 0x31u << 24, 0, 0x4E, 0);
    p4(i++, 0xD0 | 8 << 16 | KH1_PSMCT32 << 24, 0, 0x4C, 0);
    mem[2][0] = (u32)i;
    mem[2][1] = (u32)(unsigned long)pkt2;
    mem[2][2] = mem[2][3] = 0;
}

/* session 98: the spin copy's shape (sceneeff.c func_00102da8's D_002A4ED0: one REFE of 12 qwords at
 * D_002A4E10): 7 x A+D (FRAME_1 the target 0xD0 CT32, TEX0_1 the display block 0 CT24 512 x 512 TCC 0,
 * TEST_1 ZTST ALWAYS, TEX1_1 bilinear, ALPHA_1, SCISSOR_1 0 .. 511 x 0 .. 383, CLAMP_1 CLAMP both ways),
 * then one REGLIST (EOP) PRIM 0x116, RGBAQ 0x80, UV (1, 0) XYZ2 (0, 0), UV (513, 448) XYZ2 (512, 384):
 * the display's 448 lines shrunk to the target's 384, one texel right.  Its tag at mem[2]. */
static void spin_packet(void) {
    int i = 0;
    p4(i++, 1, 7u << 28, 0xEEEEEEE, 0);
    p4(i++, 0xD0 | 8 << 16 | KH1_PSMCT32 << 24, 0, 0x4C, 0);
    p4(i++, 0 | 8 << 14 | KH1_PSMCT24 << 20 | 9u << 26 | 1u << 30, 2, 0x06, 0);
    p4(i++, 1 << 16 | 1 << 17, 0, 0x47, 0);
    p4(i++, 1 << 5 | 1 << 6, 0, 0x14, 0);
    p4(i++, 0x44, 0, 0x42, 0);
    p4(i++, 511u << 16, 383u << 16, 0x40, 0);
    p4(i++, 1 | 1 << 2, 0, 0x08, 0);
    p4(i++, 1 | 1 << 15, 1u << 26 | 6u << 28, 0x535310, 0);
    p4(i++, 6 | 1 << 4 | 1 << 8, 0, 0x80808080, 0x3F800000);
    p4(i++, 16, 0, 0x7000 | 0x7400u << 16, 0xFFFFFFFE);
    p4(i++, 513 * 16 | (448u * 16) << 16, 0, 0x9000 | 0x8C00u << 16, 0xFFFFFFFE);
    mem[2][0] = (u32)i;
    mem[2][1] = (u32)(unsigned long)pkt2;
    mem[2][2] = mem[2][3] = 0;
}

/* a made-up colour that names its pixel: x in bits 0-8, y in 9-17 (CT24 keeps them) */
static u32 ucol(s32 x, s32 y) { return (u32)x | (u32)y << 9 | 0x800000; }
static s32 ucol_x(u32 c) { return (s32)(c & 0x1FF); }
static s32 ucol_y(u32 c) { return (s32)(c >> 9 & 0x1FF); }

/* the Z-area copy walked: the target filled with ucol, the game's environment (XYOFFSET, SCISSOR the
 * target's 512 x 384, TEXA TA0 0x80) */
static int zcopy_walk(void) {
    s32 x, y;
    kh1_gs_reset();
    for (y = 0; y < 384; y++)
        for (x = 0; x < 512; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x1A00, 8, x, y, 0x80000000u | ucol(x, y));
    kh1_gs_write(0x18, 0x7000, 0x7400);
    kh1_gs_write(0x40, 511 << 16, 383 << 16);
    kh1_gs_write(0x3B, 0x80, 0x80);
    zcopy_packet();
    return kh1_dma_walk(2, 0x104, (u32)(unsigned long)mem[2], where);
}

/* the spin copy walked: the display (CT24, 448 lines) filled with ucol */
static int spin_walk(void) {
    s32 x, y;
    kh1_gs_reset();
    for (y = 0; y < 448; y++)
        for (x = 0; x < 512; x++) kh1_gsmem_write_pixel(KH1_PSMCT24, 0, 8, x, y, ucol(x, y));
    kh1_gs_write(0x18, 0x7000, 0x7400);
    kh1_gs_write(0x3B, 0x80, 0x80);
    spin_packet();
    return kh1_dma_walk(2, 0x104, (u32)(unsigned long)mem[2], where);
}

/* the source texel x (or y) that pixel (x, y) of a copy's buffer holds, less the pixel's own: the
 * copy's offset there */
static s32 dx_at(u32 psm, u32 bp, s32 x, s32 y) { return ucol_x(kh1_gsmem_read_pixel(psm, bp, 8, x, y)) - x; }
static s32 dy_at(u32 psm, u32 bp, s32 x, s32 y) { return ucol_y(kh1_gsmem_read_pixel(psm, bp, 8, x, y)) - y; }

/* the RGB of a PAM shot's pixel (x, y), w x h, after its header */
static u32 pam_at(void *f, s32 w, s32 h, s32 x, s32 y) {
    char hdr[128];
    u8 p[3] = { 0, 0, 0 };
    s32 n = sprintf(hdr, "P7\nWIDTH %d\nHEIGHT %d\nDEPTH 3\nMAXVAL 255\nTUPLTYPE RGB\nENDHDR\n", w, h);
    fseek(f, n + (y * w + x) * 3, 0);
    fread(p, 1, 3, f);
    return p[0] | p[1] << 8 | p[2] << 16;
}

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("present_test: %s\n", name); fails++; } } while (0)

/* the RGB at screen pixel (x, y) of a 960-wide shot */
static u32 at(s32 x, s32 y) { const u8 *p = rgb + (y * 960 + x) * 3; return p[0] | p[1] << 8 | p[2] << 16; }

/* the made-up target's colour at (x, y): constant over 8 x 8 blocks, so a texel's rounding either way
 * reads the same */
static u32 tcol(s32 x, s32 y) { return (u32)(x >> 3) * 4 | (u32)(y >> 3) * 5 << 8 | 0x30 << 16; }

/* the frame copy's walk under a fresh GS: the target filled with tcol, the game's 4:3 environment
 * (XYOFFSET, SCISSOR 512 x 448, TEXA TA0 0x80), the copy walked; its shot read back from DIR */
static void copy_walk(const char *dir, u32 n, void **f) {
    char path[512];
    s32 x, y;
    kh1_gs_reset();
    for (y = 0; y < 384; y++)
        for (x = 0; x < 512; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x1A00, 8, x, y, 0x80000000u | tcol(x, y));
    kh1_gs_write(0x18, 0x7000, 0x7400);
    kh1_gs_write(0x40, 511 << 16, 447 << 16);
    kh1_gs_write(0x3B, 0x80, 0x80);
    copy_packet();
    CHECK("copy: walk", kh1_dma_walk(2, 0x104, (u32)(unsigned long)mem[0], where) == 0);
    sprintf(path, "%.400s/shot_%05u.pam", dir, n);
    *f = fopen(path, "rb");
    CHECK("copy: the shot written", *f != 0);
}

/* session 117: an indexed scene drawn through the model with the port's palette cache on or off
 * (host/null/present.c, kh1_present_pal): a 16 x 16 PSMT4 texture at 0x2000 drawn 32 x 32 (the
 * model's exact sprite) with CSA 0 loaded, again with CSA 1 and CLD 0 (no load: a draw lookup), and a
 * 128 x 128 PSMT8 at 0x2400 drawn 128 x 128 (the present's textured sprite), both CLUTs CT32 (0x3700
 * and 0x3A00, made-up colours); the display's 512 x 448 pixels are kept in out.  Session 118: tex turns
 * the port's texture cache on (kh1_present_tex), and a 16 x 16 CT32 texture at 0x2800 is drawn last
 * (a direct PSM through the cache's stored values) */
static u32 scene_px[512 * 448];
static void scene_sprite(u32 tex0_lo, u32 tex0_hi, s32 x, s32 y, s32 w, s32 h, u32 tw) {
    kh1_gs_write(0x06, tex0_lo, tex0_hi);
    kh1_gs_write(0x00, 6 | 1 << 4 | 1 << 8, 0);
    kh1_gs_write(0x01, 0x80808080, 0x3F800000);
    kh1_gs_write(0x03, 0, 0);
    kh1_gs_write(0x05, (u32)(0x7000 + x * 16) | (u32)(0x7400 + y * 16) << 16, 0);
    kh1_gs_write(0x03, tw * 16 | tw * 16 << 16, 0);
    kh1_gs_write(0x05, (u32)(0x7000 + (x + w) * 16) | (u32)(0x7400 + (y + h) * 16) << 16, 0);
}
static void scene(int cache, int tex, u32 *out) {
    u32 x, y, i;
    kh1_gsmem_reset();
    kh1_gs_reset();
    kh1_present_pal(cache);
    kh1_present_tex(tex);
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x2800, 1, x, y, 0x80000000u | (x * 0x0F0503 + y * 0x01070B));
    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++) kh1_gsmem_write_pixel(KH1_PSMT4, 0x2000, 1, x, y, (x + y * 3) & 15);
    for (y = 0; y < 128; y++)
        for (x = 0; x < 128; x++) kh1_gsmem_write_pixel(KH1_PSMT8, 0x2400, 2, x, y, (x * 7 + y * 3) & 0xFF);
    for (i = 0; i < 32; i++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x3700, 1, i & 7, i >> 3, 0x80000000u | (i * 0x070B0D + 0x203040));
    for (i = 0; i < 256; i++) kh1_gsmem_write_pixel(KH1_PSMCT32, 0x3A00, 1, i & 15, i >> 4, 0x80000000u | (i * 0x030507 + 0x102030));
    kh1_gs_write(0x4C, 0 | 8 << 16 | KH1_PSMCT24 << 24, 0); /* FRAME_1: the display */
    kh1_gs_write(0x18, 0x7000, 0x7400);
    kh1_gs_write(0x40, 511 << 16, 447 << 16);
    /* TEX0: TBP0, TBW, PSM, TW / TH 4 (16) or 7 (128); hi: TCC, CBP, CPSM CT32, CSA, CLD */
    scene_sprite(0x2000 | 1 << 14 | (u32)KH1_PSMT4 << 20 | 4u << 26, 0 | 1 << 2 | 0x3700 << 5 | 1u << 29, 10, 20, 32, 32, 16);
    scene_sprite(0x2000 | 1 << 14 | (u32)KH1_PSMT4 << 20 | 4u << 26, 0 | 1 << 2 | 0x3700 << 5 | 1u << 24, 50, 20, 32, 32, 16);
    scene_sprite(0x2400 | 2 << 14 | (u32)KH1_PSMT8 << 20 | 7u << 26 | 3u << 30, 1 | 1 << 2 | 0x3A00 << 5 | 1u << 29, 100, 100, 128, 128, 128);
    scene_sprite(0x2800 | 1 << 14 | (u32)KH1_PSMCT32 << 20 | 4u << 26, 0 | 1 << 2, 300, 20, 32, 32, 16);
    for (y = 0; y < 448; y++)
        for (x = 0; x < 512; x++) out[y * 512 + x] = kh1_gsmem_read_pixel(KH1_PSMCT24, 0, 8, x, y);
}

int main(int argc, char **argv) {
    KH1Canvas c;
    f32 sx, sy;
    char path[512];
    void *f;

    kh1_gs_reset();
    /* the display: CT24 at block 0, 512 wide, 448 lines; canvas row 192 is its row 224 */
    kh1_gsmem_write_pixel(KH1_PSMCT24, 0, 8, 256, 224, 0x112233);
    kh1_gsmem_write_pixel(KH1_PSMCT24, 0, 8, 0, 224, 0x445566);
    kh1_gsmem_write_pixel(KH1_PSMCT24, 0, 8, 511, 447, 0x778899);
    CHECK("display: shown", kh1_present_rgb(rgb, 960, 544, KH1_PSMCT24, 0, 8, 448) == 0);
    CHECK("display: centre", at(480, 272) == 0x112233);
    CHECK("display: canvas x 0", at(118, 272) == 0x445566);
    CHECK("display: the bars black", at(116, 272) == 0 && at(10, 272) == 0 && at(950, 272) == 0);
    CHECK("display: bottom right", at(842, 543) == 0x778899);

    /* the 3D target: CT32 at 0x1A00, 384 lines, no row scale; the alpha byte dropped */
    kh1_gsmem_write_pixel(KH1_PSMCT32, 0x1A00, 8, 100, 50, 0x80AABBCC);
    CHECK("target: shown", kh1_present_rgb(rgb, 960, 544, KH1_PSMCT32, 0x1A00, 8, 384) == 0);
    kh1_canvas_fit(&c, 960.0f, 544.0f);
    kh1_canvas_map(&c, 0x7000 + 100 * 16 + 8, 0x7400 + 50 * 16 + 8, &sx, &sy);
    CHECK("target: its pixel", at((s32)sx, (s32)sy) == 0xAABBCC);
    CHECK("not a colour buffer", kh1_present_rgb(rgb, 960, 544, KH1_PSMT8, 0, 8, 384) == -1);

    /* the hook: a send of the frame copy (here a lone END tag) writes DIR/shot_00000.pam */
    if (argc > 1) {
        mem[0][0] = 0x70000000;
        kh1_gs_write(0x4C, 0 | 8 << 16 | KH1_PSMCT24 << 24, 0); /* FRAME_1: the display */
        CHECK("hook: init", kh1_present_init(64, 48, 0, argv[1], mem[0]) == 0);
        CHECK("hook: walk", kh1_dma_walk(2, 0x104, (u32)(unsigned long)mem[0], where) == 0);
        sprintf(path, "%.400s/shot_00000.pam", argv[1]);
        f = fopen(path, "rb");
        CHECK("hook: the shot written", f != 0);
        if (f) fclose(f);
        /* session 95: the present turns the flat sprites on: a clear of the display shows */
        kh1_gs_write(0x18, 0x7000, 0x7400);
        kh1_gs_write(0x40, 511 << 16, 447 << 16);
        kh1_gs_write(0x00, 6, 0);
        kh1_gs_write(0x01, 0x80405060, 0x3F800000);
        kh1_gs_write(0x05, 0x7000 | 0x7400 << 16, 0);
        kh1_gs_write(0x05, 0x9000 | 0x9000 << 16, 0);
        CHECK("hook: a flat clear filled", kh1_gsmem_stats()->flat_sprites == 1 &&
              kh1_present_rgb(rgb, 960, 544, KH1_PSMCT24, 0, 8, 448) == 0 && at(480, 272) == 0x405060 && at(10, 272) == 0);
        CHECK("hook: bad size", kh1_present_init(0, 48, 0, argv[1], mem[0]) == -1);

        /* session 97: the frame copy's packet walked, the display shot showing the target's colours at
         * the canvas map's pixels (the copy's 384 texel rows over the display's 448 lines, read back as
         * the canvas's 384) */
        {
            static const s32 pts[][2] = { { 4, 4 }, { 100, 52 }, { 36, 100 }, { 260, 196 }, { 476, 300 }, { 508, 380 } };
            static const KH1FullScreen fs[1] = { { mem[0], KH1_FS_X | KH1_FS_U, "frame copy" } };
            u32 ok;
            int i;
            CHECK("copy: init", kh1_present_init(960, 544, 0, argv[1], mem[0]) == 0);
            copy_walk(argv[1], 1, &f);
            CHECK("copy: 16 strips", kh1_gsmem_stats()->tex_sprites == 16 && kh1_gsmem_stats()->tex_pixels == 512 * 448);
            if (f) {
                for (ok = 1, i = 0; i < (int)(sizeof pts / sizeof pts[0]); i++) {
                    kh1_canvas_map(&c, 0x7000 + pts[i][0] * 16 + 8, 0x7400 + pts[i][1] * 16 + 8, &sx, &sy);
                    if (pam_at(f, 960, 544, (s32)sx, (s32)sy) != tcol(pts[i][0], pts[i][1])) {
                        printf("present_test: canvas (%d, %d): %06x, want %06x\n", pts[i][0], pts[i][1],
                               pam_at(f, 960, 544, (s32)sx, (s32)sy), tcol(pts[i][0], pts[i][1]));
                        ok = 0;
                    }
                }
                CHECK("copy: the target's colours at the canvas map's pixels", ok);
                CHECK("copy: the bars black", pam_at(f, 960, 544, 10, 272) == 0 && pam_at(f, 960, 544, 950, 272) == 0);
                fclose(f);
            }

            /* under KH1_HOST_WIDE the copy is stretched (fullscreen.c's row): X to the view, u from its
             * left edge; session 99: the model reads the stretched u back by the margin (gsregs.c), so its
             * 512-wide display holds canvas x at its pixel x, the target's 0.5 texel scaled by 1.32 */
            kh1_dma_fullscreen(fs, 1, -1325, 8192 + 2 * 1325);
            kh1_gs_view(-1325, 8192 + 2 * 1325);
            kh1_present_wide(1325);
            copy_walk(argv[1], 2, &f);
            CHECK("wide: the display holds the canvas", kh1_gsmem_read_pixel(KH1_PSMCT24, 0, 8, 100, 100) == tcol(100, 85) &&
                  kh1_gsmem_read_pixel(KH1_PSMCT24, 0, 8, 4, 4) == tcol(4, 3) &&
                  kh1_gsmem_read_pixel(KH1_PSMCT24, 0, 8, 500, 100) == tcol(500, 85));
            /* the present reads it as it is: canvas 300 is the target's 300, canvas 40 the target's 40
             * (session 97's shot left it black: the copy was shifted), the view's sides black */
            if (f) {
                kh1_canvas_map(&c, 0x7000 + 300 * 16 + 8, 0x7400 + 100 * 16 + 8, &sx, &sy);
                CHECK("wide: the display shot lined up", pam_at(f, 960, 544, (s32)sx, (s32)sy) == tcol(300, 100));
                kh1_canvas_map(&c, 0x7000 + 476 * 16 + 8, 0x7400 + 300 * 16 + 8, &sx, &sy);
                CHECK("wide: its right", pam_at(f, 960, 544, (s32)sx, (s32)sy) == tcol(476, 300));
                kh1_canvas_map(&c, 0x7000 + 40 * 16 + 8, 0x7400 + 100 * 16 + 8, &sx, &sy);
                CHECK("wide: left of the margin shown, the sides black", pam_at(f, 960, 544, (s32)sx, (s32)sy) == tcol(40, 100) &&
                      pam_at(f, 960, 544, 10, 272) == 0 && pam_at(f, 960, 544, 950, 272) == 0);
                fclose(f);
            }
            /* the target shot under the wide view: the target as it is, the sides black */
            CHECK("wide target: init", kh1_present_init(960, 544, 1, argv[1], mem[0]) == 0);
            kh1_present_wide(1325);
            copy_walk(argv[1], 3, &f);
            kh1_dma_fullscreen(0, 0, 0, 0);
            kh1_gs_view(0, 8192);
            kh1_present_wide(0);
            if (f) {
                kh1_canvas_map(&c, 0x7000 + 4 * 16 + 8, 0x7400 + 4 * 16 + 8, &sx, &sy);
                CHECK("wide target: canvas 0 is texel 0", pam_at(f, 960, 544, (s32)sx, (s32)sy) == tcol(4, 4));
                CHECK("wide target: the sides black", pam_at(f, 960, 544, 10, 272) == 0 && pam_at(f, 960, 544, 950, 272) == 0);
                fclose(f);
            }
        }

        /* session 98: the other two copies of the target / display (renderer-spec 5.4 "Session 98"),
         * walked at 4:3 and under the wide stretch; the model point-samples (the texel at the pixel's
         * left / top edge) where the GS filters bilinearly, so offsets are whole texels here */
        {
            static const KH1FullScreen zfs[1] = { { mem[2], KH1_FS_X | KH1_FS_U, "copy into the Z area" } };
            static const KH1FullScreen sfs[1] = { { mem[2], KH1_FS_X | KH1_FS_U, "spin copy" } };
            static const KH1FullScreen ofs[1] = { { mem[2], KH1_FS_X | KH1_FS_U | KH1_FS_UOWN, "a capture's copy" } };
            CHECK("zcopy: walk", zcopy_walk() == 0);
            /* the Z area's pixel p holds the target's p + 1.5 (point-sampled: p + 1), rows the same */
            /* x -1.5 .. 510.5 covers pixels 0 .. 510 (the GS's x0 <= x < x1), rows 0 .. 382: the Z area's
             * last column and row are not written (they keep the Z buffer's depth bits) */
            CHECK("zcopy: 16 strips, 511 x 383", kh1_gsmem_stats()->tex_sprites == 16 && kh1_gsmem_stats()->tex_pixels == 511 * 383);
            CHECK("zcopy: column 511 and row 383 not written", kh1_gsmem_read_pixel(KH1_PSMCT24, 0xE00, 8, 511, 100) == 0 &&
                  kh1_gsmem_read_pixel(KH1_PSMCT24, 0xE00, 8, 100, 383) == 0);
            CHECK("zcopy: one texel right and down", dx_at(KH1_PSMCT24, 0xE00, 0, 0) == 1 && dx_at(KH1_PSMCT24, 0xE00, 200, 100) == 1 &&
                  dy_at(KH1_PSMCT24, 0xE00, 200, 100) == 1 && dx_at(KH1_PSMCT24, 0xE00, 479, 300) == 1);
            /* its strips' edges (x 30 / 31, 31 / 32 of the Z area) one texel apart, no seam */
            CHECK("zcopy: the strip edges", dx_at(KH1_PSMCT24, 0xE00, 30, 7) == 1 && dx_at(KH1_PSMCT24, 0xE00, 31, 7) == 1 &&
                  dx_at(KH1_PSMCT24, 0xE00, 32, 7) == 1);
            CHECK("zcopy: the target untouched", kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1A00, 8, 5, 5) == (0x80000000u | ucol(5, 5)));
            /* under the wide stretch: X to -84.8 .. 592.8, u 0 .. 677.6 (the renderer's, from the view's
             * left edge); session 98's model held the target's p + 82.8 + 1.99 at pixel p, session 99's
             * reads u back by the margin, so pixel p holds the target's p + 1.99 (the 1.5 texels scaled
             * by 1.32), as a view-wide renderer's does */
            kh1_dma_fullscreen(zfs, 1, -1325, 8192 + 2 * 1325);
            CHECK("zcopy wide: walk", zcopy_walk() == 0);
            CHECK("zcopy wide: no margin shift", dx_at(KH1_PSMCT24, 0xE00, 0, 50) == 2 && dx_at(KH1_PSMCT24, 0xE00, 100, 50) == 2 &&
                  dx_at(KH1_PSMCT24, 0xE00, 400, 50) == 2 && dy_at(KH1_PSMCT24, 0xE00, 100, 50) == 1);

            /* the spin copy: target pixel (t, r) holds the display's (t + 1, r x 448 / 384) */
            kh1_dma_fullscreen(0, 0, 0, 0);
            CHECK("spin: walk", spin_walk() == 0);
            CHECK("spin: one sprite", kh1_gsmem_stats()->tex_sprites == 1 && kh1_gsmem_stats()->tex_pixels == 512 * 384);
            CHECK("spin: one texel right", dx_at(KH1_PSMCT32, 0x1A00, 0, 0) == 1 && dx_at(KH1_PSMCT32, 0x1A00, 300, 100) == 1);
            CHECK("spin: the last column clamped", dx_at(KH1_PSMCT32, 0x1A00, 511, 100) == 0);
            CHECK("spin: 448 lines to 384", ucol_y(kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1A00, 8, 300, 0)) == 0 &&
                  ucol_y(kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1A00, 8, 300, 192)) == 224 &&
                  ucol_y(kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1A00, 8, 300, 383)) == 446);
            /* under the wide stretch session 98's model read the display's t + 82.8 + 1.32 at target pixel
             * t, over a display already holding canvas d + 82.8: the margin twice.  Session 99: the
             * model's display holds canvas d and the copy's u is read back by the margin, so target pixel
             * t holds the display's t + 1.32, as a renderer's view-wide display gives */
            kh1_dma_fullscreen(sfs, 1, -1325, 8192 + 2 * 1325);
            CHECK("spin wide: walk", spin_walk() == 0);
            CHECK("spin wide: no margin shift", dx_at(KH1_PSMCT32, 0x1A00, 0, 100) == 1 && dx_at(KH1_PSMCT32, 0x1A00, 300, 100) == 1);
            CHECK("spin wide: past the display clamped", dx_at(KH1_PSMCT32, 0x1A00, 511, 100) == 0);
            /* the same copy flagged as reading a buffer of its own (KH1_FS_UOWN, the blurs' capture): its u
             * from the buffer's texel 0, not read back, so the model shows session 98's t + 84 */
            kh1_dma_fullscreen(ofs, 1, -1325, 8192 + 2 * 1325);
            CHECK("spin wide: a capture of its own not read back", spin_walk() == 0 && dx_at(KH1_PSMCT32, 0x1A00, 300, 100) == 84);
            kh1_dma_fullscreen(0, 0, 0, 0);
        }
    }

    if (argc > 1) {
        /* session 117: the same pixels with the palette cache as without, and its counts */
        static u32 with_px[512 * 448];
        const KH1PalCache *pc;
        u32 i, same = 1;
        scene(1, 0, with_px);
        pc = kh1_present_pal_cache();
        CHECK("palcache: drawn", kh1_gsmem_stats()->sprites == 3 && kh1_gsmem_stats()->tex_sprites == 1 &&
              with_px[30 * 512 + 15] != 0 && with_px[110 * 512 + 110] != 0);
        CHECK("palcache: two loads two fills, the CSA 1 draw its own", pc && pc->misses == 3 && pc->hits == 0 && pc->full == 0);
        CHECK("palcache: the T4's CSA 1 a palette of its own", with_px[30 * 512 + 15] != with_px[30 * 512 + 55]);
        scene(0, 0, scene_px);
        CHECK("palcache: off", kh1_present_pal_cache() == 0 && kh1_gsmem_stats()->sprites == 3);
        for (i = 0; i < 512 * 448; i++)
            if (with_px[i] != scene_px[i]) same = 0;
        CHECK("palcache: the shot's pixels the same", same);
        /* the same scene twice with the cache: the second frame's loads hit (one frame here) */
        scene(1, 0, with_px);
        kh1_gs_write(0x06, 0x2000 | 1 << 14 | (u32)KH1_PSMT4 << 20 | 4u << 26, 0 | 1 << 2 | 0x3700 << 5 | 1u << 29);
        pc = kh1_present_pal_cache();
        CHECK("palcache: a reload hits", pc && pc->hits == 1 && pc->misses == 3);
        kh1_present_pal(1);
        /* session 118: the same pixels with the texture cache (and the palette cache) as without: the
         * two T4 draws one texture (CSA is not in the key: a stamp hit), the T8 and the CT32 their own */
        {
            const KH1TexCache *tc;
            scene(1, 1, with_px);
            tc = kh1_present_tex_cache();
            same = 1;
            for (i = 0; i < 512 * 448; i++)
                if (with_px[i] != scene_px[i]) same = 0;
            CHECK("texcache: the shot's pixels the same", same && with_px[30 * 512 + 310] != 0);
            CHECK("texcache: three decodes, the CSA 1 draw a stamp hit", tc && tc->draws == 4 && tc->decodes == 3 &&
                  tc->stamp_hits == 1 && tc->hash_hits == 0 && tc->targets == 0 &&
                  tc->decoded == 16 + 128 * 128 + 16); /* the 16-wide ones TH 0: one row */
            scene(0, 1, with_px);
            same = 1;
            for (i = 0; i < 512 * 448; i++)
                if (with_px[i] != scene_px[i]) same = 0;
            CHECK("texcache: without the palette cache, the same", same);
            CHECK("texcache: off", (kh1_present_tex(0), kh1_present_tex_cache() == 0));
            kh1_present_tex(1);
        }
    }

    if (fails) { printf("present_test: %d of %d failed\n", fails, checks); return 1; }
    printf("present_test: PASS (%d checks)\n", checks);
    return 0;
}
