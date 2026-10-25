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
static u8 rgb[960 * 544 * 3];

static const char *where(u32 a, u32 n) {
    if (a >= (u32)(unsigned long)pkt && a + n <= (u32)(unsigned long)pkt + sizeof pkt) return "pkt";
    return a >= (u32)(unsigned long)mem && a + n <= (u32)(unsigned long)mem + sizeof mem ? "mem" : 0;
}

static void q4(int i, u32 a, u32 b, u32 c, u32 d) { pkt[i][0] = a; pkt[i][1] = b; pkt[i][2] = c; pkt[i][3] = d; }

/* the frame copy's shape (renderer-spec 4.15 / 5.4 "Session 97", brightfade.c's D_002A6890: one REFE of
 * 0x2C qwords): 6 x A+D (FRAME_1 the display CT24 FBW 8, ZBUF_1 ZMSK, TEX0_1 the target 0x1A00 CT24 512 x
 * 512 TCC MODULATE, TEST_1 ZTST ALWAYS, TEX1_1 bilinear, ALPHA_1 (Cs - Cd) As + Cd), REGLIST PRIM
 * SPRITE|TME|ABE|FST and RGBAQ 0x80, REGLIST 16 x (UV XYZ2 UV XYZ2): strip k is x 32k .. 32k + 32 of
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
    q4(i++, 6 | 1 << 4 | 1 << 6 | 1 << 8, 0, 0x80808080, 0x3F800000);
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
             * left edge, so the model's 512-wide display holds canvas x + margin at its pixel x */
            kh1_dma_fullscreen(fs, 1, -1325, 8192 + 2 * 1325);
            kh1_gs_view(-1325, 8192 + 2 * 1325);
            kh1_present_wide(1325);
            copy_walk(argv[1], 2, &f);
            CHECK("wide: the display shifted by the margin", kh1_gsmem_read_pixel(KH1_PSMCT24, 0, 8, 100, 100) == tcol(183, 85) &&
                  kh1_gsmem_read_pixel(KH1_PSMCT24, 0, 8, 4, 4) == tcol(87, 3));
            /* the present reads it back by the margin: canvas 300 is the target's 300, canvas 0 .. 82.8
             * (no target pixel there in the model) and the view's sides black */
            if (f) {
                kh1_canvas_map(&c, 0x7000 + 300 * 16 + 8, 0x7400 + 100 * 16 + 8, &sx, &sy);
                CHECK("wide: the display shot lined up", pam_at(f, 960, 544, (s32)sx, (s32)sy) == tcol(300, 100));
                kh1_canvas_map(&c, 0x7000 + 476 * 16 + 8, 0x7400 + 300 * 16 + 8, &sx, &sy);
                CHECK("wide: its right", pam_at(f, 960, 544, (s32)sx, (s32)sy) == tcol(476, 300));
                kh1_canvas_map(&c, 0x7000 + 40 * 16 + 8, 0x7400 + 100 * 16 + 8, &sx, &sy);
                CHECK("wide: left of the margin black", pam_at(f, 960, 544, (s32)sx, (s32)sy) == 0 &&
                      pam_at(f, 960, 544, 10, 272) == 0);
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
    }

    if (fails) { printf("present_test: %d of %d failed\n", fails, checks); return 1; }
    printf("present_test: PASS (%d checks)\n", checks);
    return 0;
}
