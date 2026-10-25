/* host/null/gsregs.c on made-up writes and chains (no game data): tests/selftest.sh builds it with
 * gcc -m32 when that works, with host/null/dmawalk.c feeding it the way the host run does. */
#include "common.h"
#include "../../host/null/dmawalk.h"
#include "../../host/null/gsregs.h"

int printf(const char *, ...);

int kh1_host_trace = 2;

static u32 mem[64][4] ALIGNED(16);

static const char *where(u32 a, u32 n) {
    return a >= (u32)(unsigned long)mem && a + n <= (u32)(unsigned long)mem + sizeof mem ? "mem" : 0;
}

#define A(i) ((u32)(unsigned long)mem[i])
static void q(int i, u32 a, u32 b, u32 c, u32 d) { mem[i][0] = a; mem[i][1] = b; mem[i][2] = c; mem[i][3] = d; }
static void clear(void) { int i; for (i = 0; i < 64; i++) q(i, 0, 0, 0, 0); }

static int fails;
#define CHECK(name, cond) do { if (!(cond)) { printf("gsregs_test: %s\n", name); fails++; } } while (0)

static KH1GsDraw d[8];

/* a vertex as A+D writes it: RGBAQ then XYZ2 */
static void vert(u32 x, u32 y) {
    kh1_gs_write(0x01, 0x80808080, 0x3F800000);
    kh1_gs_write(0x05, x | y << 16, 0);
}

int main(void) {
    const KH1GsState *s = kh1_gs_state();
    u32 v[4];
    int n;

    /* the HUD's environment in one send (A+D: FRAME_1, TEST_1 ignore Z, CLAMP_1 5, ALPHA_1), then
     * a SPRITE with TME and ABE (PRE) of 2 PACKED RGBAQ + XYZ2 in the next: the state stays across
     * sends */
    kh1_gs_reset();
    clear();
    q(0, 0x70000005, 0, 0, 0);
    q(1, 4 | 1 << 15, 1 << 28, 0xE, 0);
    q(2, 0x00080000, 0, 0x4C, 0);
    q(3, 0x00030003, 0, 0x47, 0);
    q(4, 5, 0, 0x08, 0);
    q(5, 0x44, 0x80, 0x42, 0);
    CHECK("environment walk", kh1_dma_walk(2, 0x104, A(0), where) == 0);
    CHECK("environment: no draw", kh1_gs_draws(d, 8) == 0);
    CHECK("environment: TEST_1", s->ctx[0].test.lo == 0x30003 && s->ctx[0].clamp.lo == 5);
    clear();
    q(10, 0x70000005, 0, 0, 0);
    q(11, 2 | 1 << 15, 1 << 14 | 0x56 << 15 | 2 << 28, 0x51, 0);
    q(12, 0x80, 0x40, 0x20, 0x80);
    q(13, 0x100, 0x200, 0x10, 0);
    q(14, 0x80, 0x40, 0x20, 0x80);
    q(15, 0x300, 0x400, 0x10, 0);
    CHECK("sprite walk", kh1_dma_walk(2, 0x104, A(10), where) == 0);
    n = kh1_gs_draws(d, 8);
    CHECK("sprite: one state, 2 kicks, 1 prim", n == 1 && d[0].kicks == 2 && d[0].draws == 1);
    CHECK("sprite: the HUD's state", d[0].prim == 0x56 && d[0].ctx.test.lo == 0x30003 && d[0].ctx.clamp.lo == 5 &&
          d[0].ctx.frame.lo == 0x00080000 && d[0].ctx.alpha.lo == 0x44 && d[0].ctx.alpha.hi == 0x80);
    CHECK("sprite: PACKED RGBAQ, Q 1.0 from the tag", s->rgbaq.lo == 0x80204080 && s->rgbaq.hi == 0x3F800000);

    /* without TME the texture registers are not part of the state */
    kh1_gs_clear_draws();
    kh1_gs_write(0x00, 6, 0);
    vert(0, 0); vert(16, 16);
    kh1_gs_write(0x06, 0x1234, 0);
    vert(0, 0); vert(16, 16);
    n = kh1_gs_draws(d, 8);
    CHECK("no TME: one state", n == 1 && d[0].draws == 2 && d[0].ctx.tex0.lo == 0 && d[0].ctx.alpha.lo == 0);
    /* PRMODECONT 0: the attributes come from PRMODE (ABE here), the type from PRIM */
    kh1_gs_clear_draws();
    kh1_gs_write(0x1B, 0x40, 0);
    kh1_gs_write(0x1A, 0, 0);
    vert(0, 0); vert(16, 16);
    kh1_gs_write(0x1A, 1, 0);
    n = kh1_gs_draws(d, 8);
    CHECK("PRMODE", n == 1 && d[0].prim == 0x46);

    /* ZTE 0 (the text headers' TEST_1): a state of its own, the same sprite otherwise */
    kh1_gs_clear_draws();
    kh1_gs_write(0x00, 6, 0);
    vert(0, 0); vert(16, 16);
    kh1_gs_write(0x47, 0x00030003 & ~0x10000u, 0);
    vert(0, 0); vert(16, 16);
    n = kh1_gs_draws(d, 8);
    CHECK("ZTE 0: two states", n == 2 && d[0].draws == 1 && d[1].draws == 1 && !(d[1].ctx.test.lo >> 16 & 1));

    /* opdma's PRIM 0 with no vertex: nothing drawn, the queue empty */
    kh1_gs_clear_draws();
    kh1_gs_write(0x00, 0, 0);
    CHECK("PRIM 0: no draw", kh1_gs_draws(d, 8) == 0 && s->nvert == 0 && s->prim.lo == 0);

    /* TEX2 changes PSM and the CLUT fields only: TBP0 / TBW / TW / TH / TCC / TFX stay */
    kh1_gs_write(0x06, 0x12345678 & ~0x03F00000u, 0x00000015);
    kh1_gs_write(0x16, 0x13 << 20 | 0x5678, 0xABCDE000 | 0x0A);
    CHECK("TEX2: PSM and CLUT", s->ctx[0].tex0.lo == ((0x12345678 & ~0x03F00000u) | 0x13 << 20) &&
          s->ctx[0].tex0.hi == (0xABCDE000 | 0x15));

    /* PRIM's CTXT bit chooses context 2; TRISTRIP of 5 vertices draws 3; XYZ3 kicks without drawing */
    kh1_gs_clear_draws();
    kh1_gs_write(0x48, 0x5000D, 0);
    kh1_gs_write(0x00, 4 | 1 << 9, 0);
    vert(0, 0); vert(1, 0); vert(0, 1); vert(1, 1); vert(2, 1);
    kh1_gs_write(0x0D, 0, 0);
    n = kh1_gs_draws(d, 8);
    CHECK("CTXT 2 strip", n == 1 && d[0].ctx.test.lo == 0x5000D && d[0].kicks == 6 && d[0].draws == 3);
    /* TRIANGLE: 7 vertices are 2 triangles and one queued */
    kh1_gs_clear_draws();
    kh1_gs_write(0x00, 3, 0);
    vert(0, 0); vert(1, 0); vert(0, 1); vert(1, 1); vert(2, 1); vert(2, 2); vert(3, 3);
    n = kh1_gs_draws(d, 8);
    CHECK("triangles", n == 1 && d[0].draws == 2 && s->nvert == 1);

    /* REGLIST (PRIM, XYZ2 x 2 for a LINE) and PACKED ST's Q reaching the next RGBAQ */
    kh1_gs_reset();
    clear();
    q(0, 0x70000003, 0, 0, 0);
    q(1, 1 | 1 << 15, 1 << 26 | 3 << 28, 0x550, 0);
    q(2, 1, 0, 0x00100010, 0);
    q(3, 0x00200020, 0, 0, 0);
    CHECK("reglist walk", kh1_dma_walk(2, 0x104, A(0), where) == 0);
    n = kh1_gs_draws(d, 8);
    CHECK("reglist line", n == 1 && d[0].prim == 1 && d[0].kicks == 2 && d[0].draws == 1);
    v[0] = 0x3F000000; v[1] = 0x3E800000; v[2] = 0x40000000; v[3] = 0;
    kh1_gs_packed(0x2, v);
    v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
    kh1_gs_packed(0x1, v);
    CHECK("ST then RGBAQ", s->st.lo == 0x3F000000 && s->rgbaq.lo == 0x04030201 && s->rgbaq.hi == 0x40000000);
    /* XYZF2 PACKED with ADC: XYZF3, no drawing (SPRITE needs 2: the second draws) */
    kh1_gs_write(0x00, 6, 0);
    v[0] = 0x10; v[1] = 0x20; v[2] = 0x123450; v[3] = 0x8070;
    kh1_gs_packed(0x4, v);
    v[3] = 0x70;
    kh1_gs_packed(0x4, v);
    n = kh1_gs_draws(d, 8);
    CHECK("ADC", n == 2 && d[1].kicks == 2 && d[1].draws == 1);
    /* the field text (renderer-spec 4.10, session 81): a REGLIST header writes PRIM
     * SPRITE|TME|ABE|FST as a register and RGBAQ; the glyph's REGLIST tag (NREG 6 TEX0_1, RGBAQ, UV,
     * XYZ2, UV, XYZ2, regs 0x535316) has no PRE and draws with that PRIM; a PRE bit and PRIM field
     * in a REGLIST tag are ignored (PRE is PACKED's only) */
    kh1_gs_reset();
    clear();
    q(0, 0x70000006, 0, 0, 0);
    q(1, 1 | 1 << 15, 1 << 26 | 2 << 28, 0x10, 0);
    q(2, 0x156, 0, 0x80808080, 0x3F800000);
    q(3, 1 | 1 << 15, 1 << 14 | 3 << 15 | 1 << 26 | 6u << 28, 0x535316, 0);
    q(4, 0x3600 | 8 << 14 | 0x14 << 20 | 9 << 26 | 1u << 30, 2 | 0x3FDC << 5 | 1 << 29, 0x80808080, 0x3F800000);
    q(5, 0x00100010, 0, 0x01000100, 0x00FFFFFE);
    q(6, 0x00200020, 0, 0x02000200, 0x00FFFFFE);
    CHECK("field text walk", kh1_dma_walk(2, 0x104, A(0), where) == 0);
    n = kh1_gs_draws(d, 8);
    CHECK("field text: REGLIST PRIM", n == 1 && d[0].prim == 0x156 && d[0].kicks == 2 && d[0].draws == 1 &&
          d[0].ctx.tex0.lo == (0x3600 | 8 << 14 | 0x14 << 20 | 9 << 26 | 1u << 30) && s->prim.lo == 0x156);
    /* the list frame (func_00208458): TRISTRIP|IIP|ABE NLOOP 18 of (A+D RGBAQ, XYZF2), ADC on v6 / v7
     * and v12 / v13: three 6-vertex strips in one tag, 4 triangles each, none across a restart */
    kh1_gs_reset();
    clear();
    q(0, 0x70000000 | 37, 0, 0, 0);
    q(1, 18 | 1 << 15, 1 << 14 | 0x4C << 15 | 2u << 28, 0x4E, 0);
    for (n = 0; n < 18; n++) {
        q(2 + 2 * n, 0x80808080, 0x3F800000, 0x01, 0);
        q(3 + 2 * n, n * 16, n & 1 ? 0x100 : 0, 0x1000000, n == 6 || n == 7 || n == 12 || n == 13 ? 0x8000 : 0);
    }
    CHECK("list frame walk", kh1_dma_walk(2, 0x104, A(0), where) == 0);
    n = kh1_gs_draws(d, 8);
    CHECK("list frame: ADC restarts", n == 1 && d[0].prim == 0x4C && d[0].kicks == 18 && d[0].draws == 12);
    /* a restart also holds in a TRIFAN (the HUD arcs' kind): ADC vertices draw nothing */
    kh1_gs_clear_draws();
    kh1_gs_write(0x00, 5, 0);
    vert(0, 0); vert(1, 0); vert(1, 1);
    kh1_gs_write(0x0D, 0, 0);
    vert(0, 1);
    n = kh1_gs_draws(d, 8);
    CHECK("fan: XYZ3 kept, no draw", n == 1 && d[0].kicks == 5 && d[0].draws == 2);

    /* session 91: the extent is in 1/16 pixels from the drawing context's XYOFFSET */
    kh1_gs_clear_draws();
    kh1_gs_write(0x18, 0x7000, 0x7400);
    kh1_gs_write(0x00, 6, 0);
    vert(0x7000 + (16 << 4), 0x7400 + (260 << 4));
    vert(0x7000 + (116 << 4), 0x7400 + (368 << 4));
    vert(0x7000 - 16, 0x7400 + 8);
    vert(0x7000, 0x7400);
    n = kh1_gs_draws(d, 8);
    CHECK("extent", n == 1 && d[0].draws == 2 && d[0].x0 == -16 && d[0].y0 == 0 && d[0].x1 == 116 << 4 &&
          d[0].y1 == 368 << 4);

    /* dropped registers are counted, not kept; a non-register is unknown */
    kh1_gs_write(0x45, 0, 0);
    kh1_gs_write(0x46, 1, 0);
    kh1_gs_write(0x7F, 0, 0);
    CHECK("dropped / unknown", s->dropped == 2 && s->unknown == 1);

    if (fails) { printf("gsregs_test: %d failed\n", fails); return 1; }
    printf("gsregs_test: PASS\n");
    return 0;
}
