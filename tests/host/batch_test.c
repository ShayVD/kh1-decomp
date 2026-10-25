/* Batches and draw calls (host/port/batch.c, renderer-spec 4.13 "Session 124", vita-port-plan 5.1bl), fed
 * GS writes through host/null/gsregs.c and host/null/pipes.c's kick hook the way a KH1_HOST_TRACE=5 run is,
 * with made-up packets (no game data): tests/selftest.sh builds it with gcc -m32 when that works.
 *
 *   glyphs    100 sprites in one state: one batch, one draw call, 600 vertices.
 *   bevel     the window bevel's strip with ALPHA_1 written between pairs of kicks (renderer-spec 4.9):
 *             8 triangles in 4 batches, each opened by a pipeline change.
 *   moved     XYOFFSET written between sprites: still one batch (the vertices are mapped on the CPU).
 *   breaks    a texture upload between two sprites in one state: two batches, one opened by the transfer;
 *             TEX0 / FOGCOL / SCISSOR / FRAME changes: a texture, a uniform, a scissor, a render pass.
 *   date      a DATE draw: each batch two draw calls (the set-up and the draw).
 *   frames    kh1_batch_frame: five frames, the totals and the largest frame. */
#include "common.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"
#include "platform/batch.h"

int printf(const char *, ...);

void kh1_pipes_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state);
void kh1_pipes_frame(void);
const KH1Batcher *kh1_pipes_batcher(void);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("batch_test: %s\n", name); fails++; } } while (0)

static u32 x16(s32 px) { return (u32)(0x7000 + px * 16) & 0xFFFF; }
#define W kh1_gs_write

/* the 3D target with ZTE 0, a 64 x 64 CT32 texture at 0x2000, SPRITE | TME | FST */
static void env(void) {
    W(0x4C, 0xD0 | 8 << 16, 0);           /* FRAME_1: 0x1A00 (the 3D target) */
    W(0x4E, 0x31000070, 1);               /* ZBUF_1 Z24, ZMSK */
    W(0x47, 0, 0);                        /* TEST_1: ZTE 0 */
    W(0x18, 0x7000, 0x7000);              /* XYOFFSET_1 */
    W(0x40, 511u << 16, 383u << 16);      /* SCISSOR_1 */
    W(0x06, 0x2000 | 1 << 14 | 6 << 26 | 2u << 30, 1 | 1 << 2); /* TEX0_1 */
    W(0x08, 5, 0);                        /* CLAMP_1 */
    W(0x00, 0x156, 0);                    /* SPRITE | TME | ABE | FST */
}

static void sprite(s32 x, s32 y) {
    W(0x03, 0, 0);
    W(0x05, x16(x) | x16(y) << 16, 0);
    W(0x03, 16 * 16 | (16u * 16) << 16, 0);
    W(0x05, x16(x + 16) | x16(y + 16) << 16, 0);
}

static void upload(void) {
    u32 q[4] = { 0, 0, 0, 0 };
    W(0x50, 0, 0x2000 | 1 << 16);         /* BITBLTBUF: DBP 0x2000, DBW 1, CT32 */
    W(0x51, 0, 0);
    W(0x52, 4, 1);
    W(0x53, 0, 0);                        /* TRXDIR 0 */
    kh1_gsmem_image(q, 4);
}

static KH1BatchCount frame(void) {
    KH1BatchCount c;
    kh1_pipes_frame();
    c = kh1_pipes_batcher()->max;
    return c;
}

int main(void) {
    KH1BatchCount c;
    u32 i, g, k, n;
    const KH1Batcher *b = kh1_pipes_batcher();
    kh1_gs_reset();
    kh1_gsmem_reset();
    kh1_gs_prim_hook = kh1_pipes_prim;

    env();
    for (i = 0; i < 100; i++) sprite((i % 20) * 16, (i / 20) * 16);
    c = b->frame;
    CHECK("glyphs: 100 sprites in one state are one batch, one draw call, 600 vertices",
          c.batches == 1 && c.draws == 1 && c.prims == 100 && c.verts == 600 && c.passes == 1);
    frame();

    {
        static const u32 alpha[5] = { 0, 0x48, 0x42, 0x48, 0x42 };
        W(0x00, 4 | 1 << 6, 0); /* TRISTRIP | ABE, flat */
        for (g = 0; g < 5; g++) {
            if (g) W(0x42, alpha[g], 0);
            for (k = 0; k < 2; k++) {
                n = g * 2 + k;
                W(0x01, 0x90000000u | n, 0);
                W(0x04, x16((n >> 1) * 2) | x16((n & 1) * 2) << 16, n);
            }
        }
        c = b->frame;
        CHECK("bevel: 8 triangles in 4 batches, opened by 3 pipeline changes", c.prims == 8 && c.batches == 4 &&
              c.pipes == 3 && c.verts == 24 && c.passes == 1);
        frame();
    }

    W(0x00, 0x156, 0);
    for (i = 0; i < 4; i++) {
        W(0x18, 0x7000 + i * 160, 0x7000); /* the window moved */
        sprite(0, 0);
    }
    c = b->frame;
    CHECK("moved: XYOFFSET between sprites keeps one batch", c.batches == 1 && c.prims == 4);
    frame();

    W(0x18, 0x7000, 0x7000);
    sprite(0, 0);
    upload();
    sprite(16, 0);
    c = b->frame;
    CHECK("breaks: an upload between two sprites opens a second batch", c.batches == 2 && c.breaks == 1 && !c.pipes &&
          !c.textures);
    W(0x06, 0x2400 | 1 << 14 | 6 << 26 | 2u << 30, 1 | 1 << 2); /* another texture */
    sprite(32, 0);
    W(0x00, 0x176, 0); /* + FGE */
    W(0x3D, 0x112233, 0); /* FOGCOL */
    sprite(48, 0);
    W(0x3D, 0x445566, 0);
    sprite(64, 0);
    W(0x40, 255u << 16, 383u << 16); /* half the scissor */
    sprite(80, 0);
    W(0x4C, 0x1D0 | 4 << 16, 0); /* FRAME_1 0x3A00: the off-screen buffer */
    sprite(96, 0);
    c = b->frame;
    CHECK("breaks: a texture, a pipeline (fog), a uniform, a scissor and a render pass", c.batches == 7 &&
          c.textures == 1 && c.pipes == 1 && c.uniforms >= 1 && c.scissors >= 1 && c.passes == 2);
    printf("batch_test: breaks: %u batches (%u passes, %u pipelines, %u textures, %u uniforms, %u scissors, %u transfers)\n",
           c.batches, c.passes, c.pipes, c.textures, c.uniforms, c.scissors, c.breaks);
    frame();

    W(0x4C, 0xD0 | 8 << 16, 0);
    W(0x40, 511u << 16, 383u << 16);
    W(0x47, 1 << 14, 0); /* TEST_1: DATE */
    W(0x00, 0x156, 0);
    sprite(0, 0);
    sprite(16, 0);
    c = b->frame;
    CHECK("date: one batch of two draw calls (the set-up and the draw)", c.batches == 1 && c.draws == 2 && c.prims == 2);
    c = frame();

    CHECK("frames: five frames, the largest the breaks' 7 batches and the glyphs' 100 primitives",
          b->frames == 5 && c.batches == 7 && c.prims == 100 && b->total.prims == 100 + 8 + 4 + 7 + 2);
    printf("batch_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
