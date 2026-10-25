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
 *   frames    kh1_batch_frame: five frames, the totals and the largest frame.
 * Session 125 (batch.h's column groups, renderer-spec 4.13 "Session 125"):
 *   columns   two full-screen sprites drawn under each of the 16 32-pixel column scissors (the PS2's
 *             texture-cache trick): one batch, 15 columns merged, 30 primitives absorbed; the full
 *             SCISSOR after them joins the same batch (the union is the whole canvas).
 *   partial   column 5's second sprite differs: columns 1-4 merge, column 5's first sprite is replayed
 *             under its own scissor and starts a new group, column 6 (back to the first pair) is replayed
 *             in turn, and columns 7-15 merge into it: 3 batches, 13 columns merged.
 *   feedback  the sprites sample the target they draw into: no column merges.
 *   transfer  an upload between two columns: no merge across it.
 *   wide      at 960 x 544 the view's 16 columns are adjacent and their union is the full scissor's
 *             (target.c's rounding), and a batcher fed them directly merges them into one batch. */
#include "common.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"
#include "platform/batch.h"
#include "platform/canvas.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

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

/* a full-screen sprite, offset by d pixels */
static void full(s32 d) {
    W(0x03, 0, 0);
    W(0x05, x16(d) | x16(d) << 16, 0);
    W(0x03, 256 * 16 | (192u * 16) << 16, 0);
    W(0x05, x16(512 + d) | x16(384 + d) << 16, 0);
}

static void column(u32 k) { W(0x40, 32 * k | (32 * k + 31) << 16, 383u << 16); }

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
    /* session 125: the column groups */
    W(0x47, 0, 0);
    W(0x00, 0x156, 0);
    for (k = 0; k < 16; k++) {
        column(k);
        full(0);
        full(-2);
    }
    c = b->frame;
    CHECK("columns: 16 columns of two full-screen sprites are one batch, 15 columns merged", c.batches == 1 &&
          c.prims == 32 && c.columns == 15 && c.merged == 30 && c.verts == 32 * 6);
    W(0x40, 511u << 16, 383u << 16);
    full(0);
    c = b->frame;
    CHECK("columns: the full scissor after them joins the batch (the union is the whole canvas)", c.batches == 1 &&
          c.prims == 33);
    frame();

    for (k = 0; k < 16; k++) {
        column(k);
        full(0);
        full(k == 5 ? -4 : -2);
    }
    c = b->frame;
    printf("batch_test: partial: %u batches, %u columns merged, %u absorbed, %u primitives\n", c.batches, c.columns,
           c.merged, c.prims);
    /* columns 0-4: one group, one batch; column 5's first sprite is replayed (a batch under its own scissor)
     * and its odd sprite joins it, the new group; column 6's second sprite differs from that group's, so column
     * 6 is replayed too (a third batch) and its pair the group columns 7-15 merge into: 4 + 9 columns */
    CHECK("partial: columns 1-4 merge, columns 5 and 6 are replayed, 7-15 merge, nothing is lost", c.columns == 13 &&
          c.merged == 26 && c.prims == 32 && c.batches == 3 && c.verts == 32 * 6);
    frame();

    W(0x06, 0x1A00 | 8 << 14 | 0 << 20 | 9 << 26 | 9u << 30, 1 << 2); /* TEX0_1: the 3D target itself */
    for (k = 0; k < 16; k++) {
        column(k);
        full(0);
    }
    c = b->frame;
    CHECK("feedback: sprites sampling their own target never merge", c.columns == 0 && c.batches == 16 && c.prims == 16);
    frame();

    W(0x06, 0x2000 | 1 << 14 | 6 << 26 | 2u << 30, 1 | 1 << 2);
    for (k = 0; k < 4; k++) {
        if (k == 2) upload();
        column(k);
        full(0);
    }
    c = b->frame;
    CHECK("transfer: an upload between columns 1 and 2 ends the group", c.columns == 2 && c.batches == 2 &&
          c.breaks == 1 && c.prims == 4);
    frame();

    {
        KH1Canvas cv;
        KH1RenderPass p, pf;
        KH1DrawRegs r;
        KH1DrawState d;
        static KH1Batcher wb;
        int adj = 1;
        kh1_canvas_fit(&cv, 960.0f, 544.0f);
        memset(&r, 0, sizeof r);
        r.prim = 0x156;
        r.frame_lo = 0xD0 | 8 << 16;
        r.zbuf_lo = 0x31000070;
        r.zbuf_hi = 1;
        r.alpha_lo = 0x44;
        r.tex0_lo = 0x2000 | 1 << 14 | 6 << 26 | 2u << 30;
        r.tex0_hi = 1 | 1 << 2;
        r.tex1_lo = 0x60;
        r.clamp_lo = 5;
        kh1_drawstate_of(&r, &d);
        kh1_batch_reset(&wb);
        kh1_target_of(r.frame_lo, 0, r.zbuf_lo, r.zbuf_hi, 0, 511u << 16, 383u << 16, 0x7000, 0x7400, &cv, 1.0f, &pf);
        for (k = 0; k < 16; k++) {
            s32 prev = p.sx1;
            kh1_target_of(r.frame_lo, 0, r.zbuf_lo, r.zbuf_hi, 0, 32 * k | (32 * k + 31) << 16, 383u << 16, 0x7000,
                          0x7400, &cv, 1.0f, &p);
            if (k ? p.sx0 != prev : p.sx0 != pf.sx0) adj = 0;
            kh1_batch_prim_sig(&wb, &d, &p, 6, 0x1234567);
        }
        CHECK("wide: the view's 16 columns are adjacent, their union the full scissor's", adj && p.sx1 == pf.sx1 &&
              pf.sx1 > 512);
        CHECK("wide: the 16 columns are one batch", wb.frame.batches == 1 && wb.frame.columns == 15 &&
              wb.cur.sx0 == pf.sx0 && wb.cur.sx1 == pf.sx1);
    }

    printf("batch_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
