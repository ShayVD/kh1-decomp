/* The GPU vertex a port draws with (host/port/vertex.c, renderer-spec 4.13 "Session 124", vita-port-plan
 * 5.1bl), tested against host/null/gsmem.c's textured sprite with made-up texels (no game data):
 * tests/selftest.sh builds it with gcc -m32 when that works.
 *
 *   layout    the vertex is 32 bytes; Z through depth.h, ST / Q passed, RGBA and F as bytes, UV divided by
 *             the texture's size.
 *   sprites   textured FST sprites (DECAL, point sampling, CLAMP) at fractional 12.4 corners, both vertex
 *             orders, 1:1, stretched, shrunk and offset UVs: primasm.h's two triangles through
 *             kh1_vertex_of, rasterised as a GPU does (pixel centres, the top-left rule, the attributes
 *             interpolated in f32 barycentrics, nearest texel floor(s x 2^TW)), cover the pixels
 *             gsmem.c's sprite writes and sample the texel it wrote there (scale 1, 4:3).
 *   scaled    the same sprites at a scale of 1.4167 (960 x 544 from 512 x 384): each target pixel's
 *             centre is GS position ((j + 0.5) / s - 0.5) x 16 in sixteenths; the GPU covers it where the
 *             GS's rule would (x0 <= P < x1) and samples the texel the GS's u would give there.
 *   variants  the vertex shaders of a few pipelines: the set-up's position only, UV or ST / Q, fog. */
#include "common.h"
#include "../../host/null/gsmem.h"
#include "platform/vertex.h"
#include "platform/depth.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("vertex_test: %s\n", name); fails++; } } while (0)

static u32 x16(s32 v) { return (u32)(0x7000 + v) & 0xFFFF; }
static f32 f32_of(u32 v) { union { u32 u; f32 f; } x; x.u = v; return x.f; }
static u32 bits_of(f32 v) { union { u32 u; f32 f; } x; x.f = v; return x.u; }

static void layout(void) {
    KH1RenderPass p;
    KH1VertCtx c;
    KH1PaVert v;
    KH1GpuVert o;
    memset(&p, 0, sizeof p);
    p.ofx = 0x7000;
    p.ofy = 0x7400;
    p.ox = 82.8f;
    p.scale = 1.0f;
    memset(&v, 0, sizeof v);
    v.xy = 0x7010 | 0x7420u << 16; /* window pixel (1, 2) */
    v.z = 0x123456;
    v.f = 0x7F;
    v.rgba = 0x80402010u;
    v.s = bits_of(0.25f);
    v.t = bits_of(0.75f);
    v.q = bits_of(2.0f);
    v.uv = 32 * 16 | (16u * 16) << 16;
    CHECK("the vertex is 32 bytes", sizeof(KH1GpuVert) == 32);
    kh1_vertex_ctx(&c, &p, 0x31000070, 0x5C, 6u << 26 | 2u << 30, 1); /* FST 0, TW 6, TH 6 */
    kh1_vertex_of(&c, &v, 1, &o);
    CHECK("position: the viewport plus half a pixel", o.x == 1.5f + 82.8f && o.y == 2.5f);
    CHECK("Z through depth.h", o.z == kh1_depth_f32(0x123456, KH1_PSMZ24));
    CHECK("ST / Q passed as sent", o.s == 0.25f && o.t == 0.75f && o.q == 2.0f);
    CHECK("RGBA and F as bytes", o.rgba[0] == 0x10 && o.rgba[1] == 0x20 && o.rgba[2] == 0x40 && o.rgba[3] == 0x80 && o.f == 0x7F);
    kh1_vertex_ctx(&c, &p, 0x3A000070, 0x15C | 0x100, 6u << 26 | 2u << 30, 1); /* FST 1, Z16S */
    v.z = 0xFFFFFFFEu;
    kh1_vertex_of(&c, &v, 1, &o);
    CHECK("UV divided by the texture's size", o.s == 0.5f && o.t == 0.25f && o.q == 1.0f);
    CHECK("Z clamped to the buffer's format", o.z == kh1_depth_f32(0xFFFF, KH1_PSMZ16S));
}

/* a GPU's rasteriser over two triangles: coverage at pixel centres with the top-left rule, s / t
 * interpolated in f32 barycentrics, the nearest texel of a 64 x 64 CLAMP texture */
#define TW 6
static int edge_in(f32 ax, f32 ay, f32 bx, f32 by, f32 px, f32 py, int ccw, f32 *e) {
    f32 v;
    if (!ccw) { f32 t = ax; ax = bx; bx = t; t = ay; ay = by; by = t; }
    v = (bx - ax) * (py - ay) - (by - ay) * (px - ax);
    *e = ccw ? v : -v;
    if (v > 0) return 1;
    if (v < 0) return 0;
    return (by - ay) < 0 || ((by - ay) == 0 && (bx - ax) > 0); /* top-left edges keep their pixels */
}
static int gpu_pixel(const KH1GpuVert *o, u32 j, u32 k, s32 *tx, s32 *ty) {
    u32 t, hit = 0;
    f32 px = (f32)j + 0.5f, py = (f32)k + 0.5f;
    for (t = 0; t < 6; t += 3) {
        const KH1GpuVert *a = &o[t], *b = &o[t + 1], *c = &o[t + 2];
        f32 area = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x), e0, e1, e2, l0, l1, l2, s, tt;
        int ccw = area > 0;
        if (area == 0) continue;
        if (!edge_in(b->x, b->y, c->x, c->y, px, py, ccw, &e0) || !edge_in(c->x, c->y, a->x, a->y, px, py, ccw, &e1) ||
            !edge_in(a->x, a->y, b->x, b->y, px, py, ccw, &e2))
            continue;
        if (area < 0) area = -area;
        l0 = e0 / area;
        l1 = e1 / area;
        l2 = e2 / area;
        s = l0 * a->s + l1 * b->s + l2 * c->s;
        tt = l0 * a->t + l1 * b->t + l2 * c->t;
        *tx = (s32)(s * (1 << TW) + 0x10000) - 0x10000; /* floor */
        *ty = (s32)(tt * (1 << TW) + 0x10000) - 0x10000;
        if (*tx < 0) *tx = 0;
        if (*tx > 63) *tx = 63;
        if (*ty < 0) *ty = 0;
        if (*ty > 63) *ty = 63;
        hit++;
    }
    return hit; /* 2: the diagonal drawn twice */
}

/* x0 y0 x1 y1 (sixteenths of the window) u0 v0 u1 v1 (10.4) */
static const s32 rect[][8] = {
    { 0, 0, 512, 512, 0, 0, 512, 512 },          /* 1:1 at whole pixels */
    { 7, 3, 517, 509, 0, 0, 510, 506 },          /* fractional corners, 1:1 */
    { 517, 509, 7, 3, 510, 506, 0, 0 },          /* the other order */
    { 16, 16, 1008, 1008, 0, 0, 512, 512 },      /* stretched 2x (62 pixels from 32 texels) */
    { 0, 0, 480, 400, 8, 24, 968, 824 },         /* shrunk, half-texel offset UVs */
    { 40, 8, 1000, 1000, 1000, 0, 0, 1000 },     /* u reversed */
    { 3, 5, 931, 101, 17, 33, 900, 101 },        /* odd fractions both ways */
    { 160, 160, 176, 1000, 0, 0, 1000, 1000 },   /* one pixel wide */
};
#define NRECT (sizeof rect / sizeof rect[0])
#define FBP 0x50
#define TBP 0x2000

static void sprite_verts(u32 i, const KH1RenderPass *p, KH1GpuVert *o) {
    KH1PrimAsm pa;
    KH1PaVert v, out[6];
    KH1VertCtx c;
    memset(&pa, 0, sizeof pa);
    memset(&v, 0, sizeof v);
    kh1_pa_prim(&pa, 0x116);
    v.rgba = 0x80808080u;
    v.xy = x16(rect[i][0]) | x16(rect[i][1]) << 16;
    v.uv = (u32)rect[i][4] | (u32)rect[i][5] << 16;
    kh1_pa_vertex(&pa, &v, 1, out);
    v.xy = x16(rect[i][2]) | x16(rect[i][3]) << 16;
    v.uv = (u32)rect[i][6] | (u32)rect[i][7] << 16;
    kh1_pa_vertex(&pa, &v, 1, out);
    kh1_vertex_ctx(&c, p, 0, 0x116, (u32)TW << 26 | (u32)(TW & 3) << 30, TW >> 2);
    kh1_vertex_of(&c, out, 6, o);
}

static void sprites(void) {
    u32 i, x, y, ok = 1, twice = 0, pixels = 0;
    KH1RenderPass p;
    KH1GsSprite s;
    KH1GpuVert o[6];
    memset(&p, 0, sizeof p);
    p.ofx = p.ofy = 0x7000;
    p.scale = 1.0f;
    p.w = p.h = 64;
    for (i = 0; i < NRECT; i++) {
        kh1_gsmem_reset();
        for (y = 0; y < 64; y++)
            for (x = 0; x < 64; x++) kh1_gsmem_write_pixel(KH1_PSMCT32, TBP, 1, x, y, 0x80000000u | (y + 1) << 8 | (x + 1));
        memset(&s, 0, sizeof s);
        s.prim = 0x116; /* SPRITE | TME | FST */
        s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
        s.tex0_lo = TBP | 1 << 14 | (u32)TW << 26 | (u32)(TW & 3) << 30;
        s.tex0_hi = TW >> 2 | 1 << 2 | 1 << 3; /* TCC, DECAL */
        s.clamp_lo = 5;
        s.xyoffset_lo = s.xyoffset_hi = 0x7000;
        s.scissor_lo = 63u << 16;
        s.scissor_hi = 63u << 16;
        s.xy[0] = x16(rect[i][0]) | x16(rect[i][1]) << 16;
        s.xy[1] = x16(rect[i][2]) | x16(rect[i][3]) << 16;
        s.uv[0] = (u32)rect[i][4] | (u32)rect[i][5] << 16;
        s.uv[1] = (u32)rect[i][6] | (u32)rect[i][7] << 16;
        s.rgba = 0x80808080u;
        if (!kh1_gsmem_sprite(&s)) { printf("vertex_test: gsmem.c refused sprite %u\n", i); ok = 0; continue; }
        sprite_verts(i, &p, o);
        for (y = 0; y < 64; y++)
            for (x = 0; x < 64; x++) {
                u32 g = kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y);
                s32 tx = -1, ty = -1;
                int hit = gpu_pixel(o, x, y, &tx, &ty);
                if (hit > 1) twice++;
                if (g) pixels++;
                if ((g != 0) != (hit != 0) || (g && ((s32)(g & 0xFF) - 1 != tx || (s32)(g >> 8 & 0xFF) - 1 != ty))) {
                    if (ok) printf("vertex_test: sprite %u pixel (%u, %u): GS %s texel (%d, %d), GPU %s (%d, %d)\n", i, x, y,
                                   g ? "covered" : "empty", (int)(g & 0xFF) - 1, (int)(g >> 8 & 0xFF) - 1,
                                   hit ? "covered" : "empty", tx, ty);
                    ok = 0;
                }
            }
    }
    CHECK("sprites at 4:3: the GPU covers gsmem.c's pixels and samples its texels", ok);
    CHECK("sprites: the diagonal drawn once", !twice);
    printf("vertex_test: %u sprites, %u pixels compared with gsmem.c\n", (unsigned)NRECT, pixels);
}

/* the GS's rule at a continuous sample position (sixteenths of the window) */
static int gs_at(u32 i, double px, double py, s32 *tx, s32 *ty) {
    double x0 = rect[i][0], y0 = rect[i][1], x1 = rect[i][2], y1 = rect[i][3];
    double u0 = rect[i][4], v0 = rect[i][5], u1 = rect[i][6], v1 = rect[i][7], t, u, v;
    if (x1 < x0) { t = x0; x0 = x1; x1 = t; t = u0; u0 = u1; u1 = t; }
    if (y1 < y0) { t = y0; y0 = y1; y1 = t; t = v0; v0 = v1; v1 = t; }
    if (!(px >= x0 && px < x1 && py >= y0 && py < y1)) return 0;
    u = u0 + (px - x0) * (u1 - u0) / (x1 - x0);
    v = v0 + (py - y0) * (v1 - v0) / (y1 - y0);
    *tx = (s32)(u / 16.0 + 4096.0) - 4096;
    *ty = (s32)(v / 16.0 + 4096.0) - 4096;
    if (*tx > 63) *tx = 63;
    if (*ty > 63) *ty = 63;
    if (*tx < 0) *tx = 0;
    if (*ty < 0) *ty = 0;
    return 1;
}

static void scaled(void) {
    const f32 sc = 544.0f / 384.0f;
    u32 i, x, y, ok = 1, n = 0, pixels = 0, near_edge = 0;
    KH1RenderPass p;
    KH1GpuVert o[6];
    memset(&p, 0, sizeof p);
    p.ofx = p.ofy = 0x7000;
    p.scale = sc;
    p.w = p.h = 91;
    for (i = 0; i < NRECT; i++) {
        sprite_verts(i, &p, o);
        for (y = 0; y < p.h; y++)
            for (x = 0; x < p.w; x++) {
                double gx = ((x + 0.5) / sc - 0.5) * 16.0, gy = ((y + 0.5) / sc - 0.5) * 16.0;
                s32 tx = -1, ty = -1, ux = -1, uy = -1;
                int hit = gpu_pixel(o, x, y, &tx, &ty) != 0, g = gs_at(i, gx, gy, &ux, &uy);
                n++;
                if (g) pixels++;
                if (hit != g || (g && (tx != ux || ty != uy))) {
                    /* a sample within f32's rounding of an edge or a texel boundary is a tie a GPU may break
                     * either way: counted, not failed (the GS's 12.4 grid never lands there at scale 1) */
                    s32 a, b;
                    double e = 1e-3 * 16.0;
                    int tie = gs_at(i, gx + e, gy + e, &a, &b) != gs_at(i, gx - e, gy - e, &a, &b) ||
                              (gs_at(i, gx + e, gy + e, &a, &b) && (gs_at(i, gx - e, gy - e, &ux, &uy), a != ux || b != uy));
                    if (tie) { near_edge++; continue; }
                    if (ok) printf("vertex_test: scaled sprite %u pixel (%u, %u): GS %d (%d, %d), GPU %d (%d, %d)\n", i, x, y,
                                   g, ux, uy, hit, tx, ty);
                    ok = 0;
                }
            }
    }
    CHECK("sprites at a scale of 1.4167: the GS's coverage and texels at each pixel centre", ok);
    printf("vertex_test: scaled: %u pixels (%u covered), %u ties within f32 rounding\n", n, pixels, near_edge);
}

static void variants(void) {
    KH1PipeSet *set;
    static KH1PipeSet s;
    KH1PipeKey k;
    KH1VertKey vk;
    u32 mask;
    set = &s;
    kh1_pipeset_clear(set);
    memset(&k, 0, sizeof k);
    k.cls = KH1_PA_TRIANGLES;
    set->pipe[set->npipe++] = k;                   /* untextured */
    k.shader.tex = 1; k.shader.fst = 1;
    set->pipe[set->npipe++] = k;                   /* UV */
    k.shader.fog = 1; k.shader.fst = 0;
    set->pipe[set->npipe++] = k;                   /* ST / Q + fog */
    k.shader.discard = 1;
    set->pipe[set->npipe++] = k;                   /* the same vertex shader */
    memset(&k, 0, sizeof k);
    k.shader.setup = 1; k.shader.tex = 1; k.shader.fog = 1;
    set->pipe[set->npipe++] = k;                   /* DATE's set-up: position only */
    kh1_vertkey_of(&set->pipe[4], &vk);
    CHECK("the set-up's vertex shader reads the position only", kh1_vertkey_index(&vk) == 0 && !vk.tex && !vk.fog);
    CHECK("five pipelines, four vertex shaders", kh1_vertex_variants(set, &mask) == 4 && mask == (1 | 2 | 8 | 64));
    CHECK("the names", kh1_vertkey_str(6)[0] == 'p' && kh1_vertkey_str(4)[11] == 'f');
}

int main(void) {
    (void)f32_of;
    layout();
    sprites();
    scaled();
    variants();
    printf("vertex_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
