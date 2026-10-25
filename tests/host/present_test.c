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

int kh1_host_trace = 2;
unsigned long kh1_host_frame(void) { return 7; }

static u32 mem[8][4] ALIGNED(16);
static u8 rgb[960 * 544 * 3];

static const char *where(u32 a, u32 n) {
    return a >= (u32)(unsigned long)mem && a + n <= (u32)(unsigned long)mem + sizeof mem ? "mem" : 0;
}

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("present_test: %s\n", name); fails++; } } while (0)

/* the RGB at screen pixel (x, y) of a 960-wide shot */
static u32 at(s32 x, s32 y) { const u8 *p = rgb + (y * 960 + x) * 3; return p[0] | p[1] << 8 | p[2] << 16; }

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
        CHECK("hook: bad size", kh1_present_init(0, 48, 0, argv[1], mem[0]) == -1);
    }

    if (fails) { printf("present_test: %d of %d failed\n", fails, checks); return 1; }
    printf("present_test: PASS (%d checks)\n", checks);
    return 0;
}
