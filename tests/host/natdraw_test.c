/* The native renderer's CPU side (host/port/natdraw.c, include/platform/natdraw.h, docs/native-renderer.md), with
 * made-up matrices and strips (no game data): tests/selftest.sh builds it with gcc -m32 when that works.
 *
 *   fold      F = N x M (kh1_nat_fold) applied as the native vertex shader does (F's row dot (x, y, z, 1), the
 *             divide, the viewport) lands where the GS path puts P18's vertex: kh1_nat_ref_xyz's position to
 *             12.4 as P18's FTOI4, then vertex.h's kh1_vertex_of; within the 12.4 truncation in x / y and one
 *             Z step in z, at two scales, both Z buffer formats and an X shift.
 *   cull      a strip's triangles from kh1_nat_tris kept by the one winding rule (cross(p1 - p0, p2 - p0) >= 0
 *             in GS space, y down) are exactly those P18 does not mark ADC (its cross product of the last two
 *             screen edges, the operands swapped by the parity (h[3] + j) & 1, negative), at both parities.
 *   tris      the strips' triangle count, a vertex whose matrix index is past the run's dropped, the vertex's
 *             fields and pad[0] the index, and *lost when out is full. */
#include "common.h"
#include "platform/natdraw.h"
#include "platform/vertex.h"
#include "platform/depth.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("natdraw_test: %s\n", name); fails++; } } while (0)

static f32 f32_of(u32 v) { union { u32 u; f32 f; } x; x.u = v; return x.f; }
static u32 bits_of(f32 v) { union { u32 u; f32 f; } x; x.f = v; return x.u; }

static u32 seed = 12345;
static f32 rnd(f32 lo, f32 hi) { /* a uniform float in lo .. hi */
    seed = seed * 1103515245u + 12345u;
    return lo + (hi - lo) * (f32)(seed >> 8 & 0xFFFF) / 65535.0f;
}

/* a P18-like matrix in VU column order: x, y about the screen's centre in GS units, w the depth, z a Z24-ish
 * depth that falls with distance */
static void mat(u32 *m) {
    f32 c[16];
    u32 k;
    f32 sx = rnd(150.0f, 400.0f), sy = rnd(150.0f, 400.0f);
    c[0] = sx; c[1] = rnd(-30.0f, 30.0f); c[2] = rnd(-1000.0f, 1000.0f); c[3] = rnd(-0.05f, 0.05f);
    c[4] = rnd(-30.0f, 30.0f); c[5] = sy; c[6] = rnd(-1000.0f, 1000.0f); c[7] = rnd(-0.05f, 0.05f);
    c[8] = 2048.0f; c[9] = 2048.0f; c[10] = rnd(-20000.0f, 20000.0f); c[11] = 1.0f;
    c[12] = 2048.0f * 6.0f; c[13] = 2048.0f * 6.0f; c[14] = 6.0e6f; c[15] = 6.0f;
    for (k = 0; k < 16; k++) m[k] = bits_of(c[k]);
}

/* the native vertex shader on one vertex (shadergen.c's statements: r2 = u_m rows . (pos, 1), z clamped 0 .. w),
 * then the GPU's divide and viewport: window pixels and depth */
static void shade(const f32 *um, const KH1GpuVert *v, const KH1RenderPass *p, f32 out[3]) {
    const f32 *m = um + v->pad[0] * 16;
    f32 c[4];
    u32 k;
    for (k = 0; k < 4; k++) c[k] = m[k * 4] * v->x + m[k * 4 + 1] * v->y + m[k * 4 + 2] * v->z + m[k * 4 + 3];
    if (c[2] < 0.0f) c[2] = 0.0f;
    if (c[2] > c[3]) c[2] = c[3];
    out[0] = (c[0] / c[3] + 1.0f) * 0.5f * (f32)p->w;
    out[1] = (c[1] / c[3] + 1.0f) * 0.5f * (f32)p->h;
    out[2] = c[2] / c[3];
}

static void fold(void) {
    static const f32 scales[2] = {1.0f, 1.4166666f};
    static const u32 zbufs[2] = {0x01000000u, 0x02000000u}; /* PSM Z24, Z16 */
    static const s32 shifts[2] = {0, 8};
    KH1RenderPass p;
    u32 mats[16 * 4], i, k, t, bad = 0, zbad = 0;
    f32 um[16 * 4], worst = 0.0f;
    for (t = 0; t < 8; t++) {
        f32 sc = scales[t & 1];
        u32 zbuf = zbufs[t >> 1 & 1];
        s32 xs = shifts[t >> 2 & 1];
        KH1VertCtx ctx;
        memset(&p, 0, sizeof p);
        p.ofx = (2048 - 320) * 16;
        p.ofy = (2048 - 224) * 16;
        p.ox = 32.0f;
        p.oy = 16.0f;
        p.scale = sc;
        p.w = (u32)((640 + 64) * sc);
        p.h = (u32)((448 + 32) * sc);
        kh1_vertex_ctx(&ctx, &p, zbuf, 0x14, 0, 0); /* TRISTRIP, ST / Q */
        for (k = 0; k < 4; k++) mat(mats + k * 16);
        kh1_nat_fold(&p, zbuf, xs, mats, 4, um);
        for (i = 0; i < 200; i++) {
            f32 pos[3], ref[3], got[3], d;
            KH1PaVert pv;
            KH1GpuVert gs, nv;
            u32 mi = i & 3, zmax = (zbuf >> 24 & 15) == 2 ? 0xFFFF : 0xFFFFFF, z;
            s32 x16, y16;
            pos[0] = rnd(-1.0f, 1.0f);
            pos[1] = rnd(-1.0f, 1.0f);
            pos[2] = rnd(-3.0f, 6.0f);
            kh1_nat_ref_xyz(mats + mi * 16, pos, ref);
            /* P18's FTOI4 (truncation) and the GS's Z clamp (gsregs.c), then the GS path's vertex */
            x16 = (s32)(ref[0] * 16.0f) + xs;
            y16 = (s32)(ref[1] * 16.0f);
            z = ref[2] < 0.0f ? 0 : ref[2] >= (f32)zmax ? zmax : (u32)ref[2];
            memset(&pv, 0, sizeof pv);
            pv.xy = ((u32)x16 & 0xFFFF) | (u32)y16 << 16;
            pv.z = z;
            kh1_vertex_of(&ctx, &pv, 1, &gs);
            memset(&nv, 0, sizeof nv);
            nv.x = pos[0];
            nv.y = pos[1];
            nv.z = pos[2];
            nv.pad[0] = (u8)mi;
            shade(um, &nv, &p, got);
            /* x / y: the GS path truncated to sixteenths, so the native position is up to 1/16 GS pixel right of
             * or below it */
            d = got[0] - gs.x;
            if (d < -0.002f || d > sc / 16.0f + 0.002f) bad++;
            if (d > worst) worst = d;
            d = got[1] - gs.y;
            if (d < -0.002f || d > sc / 16.0f + 0.002f) bad++;
            /* z: within one Z step of the truncated Z (the scale is 2^-bits) */
            d = got[2] - gs.z;
            if (d < -1e-6f || d > kh1_depth_f32(1, 0x30 | (zbuf >> 24 & 15)) + 1e-6f) zbad++;
        }
    }
    printf("natdraw_test: fold: 1600 vertices, the native position at most %.4f px past the GS path's\n", (double)worst);
    CHECK("fold: x / y within the 12.4 truncation of the GS path's (two scales, an X shift)", !bad);
    CHECK("fold: z within one Z step of the GS path's (Z24, Z16)", !zbad);
}

/* P18's ADC for vertex j of a strip (j >= 2) from the screen positions s: the edges e = s[j] - s[j-1],
 * l = s[j-1] - s[j-2]; at odd (h3 + j) the cross z of (l, e), else of (e, l); negative is ADC */
static int p18_adc(const f32 (*s)[2], u32 j, u32 h3) {
    f32 ex = s[j][0] - s[j - 1][0], ey = s[j][1] - s[j - 1][1];
    f32 lx = s[j - 1][0] - s[j - 2][0], ly = s[j - 1][1] - s[j - 2][1];
    f32 c = (h3 + j) & 1 ? lx * ey - ex * ly : ex * ly - lx * ey;
    return c < 0.0f;
}

static u32 rec[4 + 12 * 8];
static void cull(void) {
    static const f32 ident[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    u32 mats[16], t, j, bad = 0, kept = 0, total = 0;
    KH1GpuVert out[64];
    for (j = 0; j < 16; j++) mats[j] = bits_of(ident[j]);
    for (t = 0; t < 400; t++) {
        f32 s[12][2];
        u32 nv = 3 + t % 9, h3 = t >> 1 & 1, n, lost, k;
        rec[0] = 0x8000;
        rec[1] = 0x412 << 15 >> 15;
        rec[2] = nv;
        rec[3] = h3;
        for (j = 0; j < nv; j++) {
            u32 *v = rec + 4 + j * 8;
            s[j][0] = rnd(1800.0f, 2300.0f);
            s[j][1] = rnd(1800.0f, 2300.0f);
            v[0] = bits_of(s[j][0]);
            v[1] = bits_of(s[j][1]);
            v[2] = bits_of(1.0f);
            v[3] = 0;
            v[4] = v[5] = v[6] = bits_of(0.5f);
            v[7] = 0;
        }
        n = kh1_nat_tris(rec, 1, 1, 0x80808080u, 0, out, 64, &lost);
        if (n != (nv - 2) * 3 || lost) { bad++; continue; }
        for (k = 0; k < n / 3; k++) {
            const KH1GpuVert *a = &out[k * 3], *b = &out[k * 3 + 1], *c = &out[k * 3 + 2];
            f32 area = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
            int keep = area >= 0.0f, adc = p18_adc((const f32 (*)[2])s, k + 2, h3);
            if (area > -1e-3f && area < 1e-3f) continue; /* degenerate: sign of a rounding */
            total++;
            kept += keep;
            if (keep == adc) bad++;
        }
    }
    (void)mats;
    printf("natdraw_test: cull: %u triangles, %u kept by the winding rule\n", total, kept);
    CHECK("cull: the winding rule keeps exactly the triangles P18 does not mark ADC (both parities)", !bad && kept && kept < total);
}

static void tris(void) {
    u32 r[2][4 + 4 * 8], i, n, lost;
    KH1GpuVert out[16];
    memset(r, 0, sizeof r);
    for (i = 0; i < 2; i++) {
        u32 j;
        r[i][2] = 4;
        r[i][3] = i;
        for (j = 0; j < 4; j++) {
            u32 *v = r[i] + 4 + j * 8;
            v[0] = bits_of((f32)j);
            v[1] = bits_of((f32)(j * 2));
            v[2] = bits_of(3.0f);
            v[3] = i == 1 && j == 3 ? 5 : i;
            v[4] = bits_of(0.25f);
            v[5] = bits_of(0.5f);
            v[6] = bits_of(2.0f);
        }
    }
    n = kh1_nat_tris(r[0], 2, 2, 0x11223344u, 0x55, out, 16, &lost);
    /* record 0: 2 triangles; record 1: its second triangle uses index 5 (past 2 matrices): 1 */
    CHECK("tris: two strips of 4, one vertex's matrix past the run's: 3 triangles", n == 9 && !lost);
    CHECK("tris: even parity's first two swapped (record 0, triangle 0: 1, 0, 2)",
          out[0].x == 1.0f && out[1].x == 0.0f && out[2].x == 2.0f);
    CHECK("tris: odd parity in order (record 0, triangle 1: 1, 2, 3)",
          out[3].x == 1.0f && out[4].x == 2.0f && out[5].x == 3.0f);
    CHECK("tris: a vertex's fields, rgba / f the run's, pad[0] the matrix",
          out[6].y == 0.0f && out[6].z == 3.0f && out[6].s == 0.25f && out[6].t == 0.5f && out[6].q == 2.0f &&
          out[6].rgba[0] == 0x44 && out[6].rgba[3] == 0x11 && out[6].f == 0x55 && out[6].pad[0] == 1);
    n = kh1_nat_tris(r[0], 2, 2, 0, 0, out, 5, &lost);
    CHECK("tris: out full: 1 triangle written, 2 lost", n == 3 && lost == 2);
}

int main(void) {
    fold();
    cull();
    tris();
    if (fails) { printf("natdraw_test: %d of %d checks failed\n", fails, checks); return 1; }
    printf("natdraw_test: PASS (%d checks)\n", checks);
    return 0;
}
