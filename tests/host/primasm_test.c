/* The primitive assembly a port's GIF parser runs (host/port/primasm.c, renderer-spec 4.13 "Session 122",
 * vita-port-plan 5.1bj), tested against host/null/gsregs.c's vertex queue and gsmem.c's sprite fill with
 * made-up vertices (no game data): tests/selftest.sh builds it with gcc -m32 when that works.
 *
 *   fan      a TRIFAN of 7 vertices: triangles (v0, v(i-1), vi) from both (gsregs.c kept the fan's
 *            first vertex from session 122 on).
 *   bevel    the window bevel's strip (renderer-spec 4.9: TRISTRIP|ABE, flat, ALPHA_1 written between
 *            each pair of kicks): the port's batches split where the draw state changes, 4 batches of
 *            2 triangles, each batch's first triangle the last two vertices before the split and the
 *            new one; flat: every vertex the last one's colour.
 *   random   20000 GIF writes (PRIM of every type with IIP 0 / 1, XYZ2 / XYZF2 / XYZ3 / XYZF3, RGBAQ,
 *            UV, ST, FOG, ALPHA_1): every primitive the port emits is the one gsregs.c draws, the flat
 *            colour the last vertex's, a sprite's six corners from its two vertices.
 *   sprites  sprites at fractional 12.4 corners (both orders): the two triangles under a GPU's top-left
 *            rule, half a pixel on, cover the pixels gsmem.c's sprite fill covers. */
#include "common.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"
#include "platform/primasm.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);
int memcmp(const void *, const void *, __SIZE_TYPE__);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("primasm_test: %s\n", name); fails++; } } while (0)

/* what the hook saw at the last drawing kick */
static KH1GsVert hv[3];
static u32 hn, hprim, hstate, hcalls;
static void hook(u32 prim, const KH1GsVert *v, u32 n, u32 state) {
    u32 i;
    for (i = 0; i < n; i++) hv[i] = v[i];
    hn = n;
    hprim = prim;
    hstate = state;
    hcalls++;
}

/* the port's side: the assembler, fed the same writes */
static KH1PrimAsm pa;
static KH1PaVert out[6];
static u32 nout, rgbaq_lo, rgbaq_hi, uv, st_s, st_t, fog;

/* both sides back to the start: the register file and the shadow of what was written */
static void reset(void) {
    kh1_gs_reset();
    memset(&pa, 0, sizeof pa);
    rgbaq_lo = rgbaq_hi = uv = st_s = st_t = fog = 0;
}

static u32 x16(s32 px) { return (u32)(0x7000 + px) & 0xFFFF; }

static void w(u32 reg, u32 lo, u32 hi) {
    KH1PaVert v;
    hcalls = 0;
    nout = 0;
    kh1_gs_write(reg, lo, hi);
    switch (reg) {
    case 0x00: kh1_pa_prim(&pa, lo & 0x7FF); return;
    case 0x01: rgbaq_lo = lo; rgbaq_hi = hi; return;
    case 0x02: st_s = lo; st_t = hi; return;
    case 0x03: uv = lo; return;
    case 0x0A: fog = hi >> 24; return;
    case 0x04: case 0x05: case 0x0C: case 0x0D:
        v.xy = lo;
        v.z = reg == 0x04 || reg == 0x0C ? hi & 0xFFFFFF : hi;
        v.f = reg == 0x04 || reg == 0x0C ? hi >> 24 : fog;
        v.uv = uv;
        v.rgba = rgbaq_lo;
        v.q = rgbaq_hi;
        v.s = st_s;
        v.t = st_t;
        nout = kh1_pa_vertex(&pa, &v, reg < 0x0C, out);
        return;
    }
}

static int same(const KH1PaVert *a, const KH1GsVert *b) {
    return a->xy == b->xy && a->z == b->z && a->f == b->f && a->uv == b->uv && a->rgba == b->rgba && a->s == b->s &&
           a->t == b->t && a->q == b->q;
}

/* the port's primitive is the GS's: the same vertices in order (flat: the last one's RGBA), a sprite's
 * corners from its two */
static int agree(void) {
    u32 i, corners = 0;
    if (!hcalls) return nout == 0;
    if ((hprim & 7) == 6) {
        if (nout != 6) return 0;
        for (i = 0; i < 6; i++) {
            const KH1PaVert *o = &out[i];
            u32 x = o->xy & 0xFFFF, y = o->xy >> 16;
            if (o->rgba != hv[1].rgba || o->z != hv[1].z || o->f != hv[1].f || o->q != hv[1].q) return 0;
            /* X, U and S from one vertex, Y, V and T from one */
            if (!(x == (hv[0].xy & 0xFFFF) && (o->uv & 0xFFFF) == (hv[0].uv & 0xFFFF) && o->s == hv[0].s) &&
                !(x == (hv[1].xy & 0xFFFF) && (o->uv & 0xFFFF) == (hv[1].uv & 0xFFFF) && o->s == hv[1].s))
                return 0;
            if (!(y == hv[0].xy >> 16 && o->uv >> 16 == hv[0].uv >> 16 && o->t == hv[0].t) &&
                !(y == hv[1].xy >> 16 && o->uv >> 16 == hv[1].uv >> 16 && o->t == hv[1].t))
                return 0;
            corners |= 1 << ((x == (hv[1].xy & 0xFFFF)) + 2 * (y == hv[1].xy >> 16));
        }
        /* all four corners, unless the two vertices share an X or a Y */
        return corners == 15 || (hv[0].xy ^ hv[1].xy) < 0x10000 || !((hv[0].xy ^ hv[1].xy) & 0xFFFF);
    }
    if (nout != hn) return 0;
    for (i = 0; i < hn; i++) {
        KH1PaVert o = out[i];
        if (!(hprim >> 3 & 1)) {
            if (o.rgba != hv[hn - 1].rgba) return 0;
            o.rgba = hv[i].rgba;
        }
        if (!same(&o, &hv[i])) return 0;
    }
    return 1;
}

static void fan(void) {
    u32 i, ok = 1, tris = 0;
    reset();
    w(0x00, 5 | 1 << 3, 0); /* TRIFAN, IIP */
    for (i = 0; i < 7; i++) {
        w(0x01, 0x80000000u | i * 0x10101, 0);
        w(0x05, x16(i * 16 * 3) | x16(i * i * 16) << 16, 100 + i);
        if (!agree()) ok = 0;
        if (nout) {
            tris++;
            if ((out[0].z != 100 || out[1].z != 100 + i - 1 || out[2].z != 100 + i)) ok = 0;
        }
    }
    CHECK("a fan's triangles are (v0, v(i-1), vi), the port's and gsregs.c's", ok && tris == 5);
}

static void bevel(void) {
    static const u32 alpha[5] = { 0, 0x48, 0x42, 0x48, 0x42 };
    u32 g, k, ok = 1, batches = 0, tris = 0, state = ~0u, last[2] = { 0, 0 }, have = 0, first = 0;
    reset();
    w(0x00, 4 | 1 << 6, 0); /* TRISTRIP|ABE: flat */
    for (g = 0; g < 5; g++) {
        if (g == 0) w(0x01, 0x90202020u, 0);
        else w(0x42, alpha[g], 0); /* ALPHA_1 between the kicks */
        for (k = 0; k < 2; k++) {
            u32 n = g * 2 + k;
            w(0x01, 0x90000000u | n, 0); /* a colour per vertex: the flat rule picks the last */
            w(0x04, x16((n >> 1) * 32) | x16((n & 1) * 32) << 16, n);
            if (!agree()) ok = 0;
            if (!nout) continue;
            tris++;
            if (out[0].rgba != (0x90000000u | n) || out[1].rgba != out[0].rgba || out[2].rgba != out[0].rgba) ok = 0;
            if (hstate != state) { /* the port's batch ends where the draw state changes */
                batches++;
                state = hstate;
                first = 1;
            }
            /* the strip goes on across the split: the triangle is the two vertices before it and this one */
            if (have && (out[0].z != last[0] || out[1].z != last[1] || out[2].z != n)) ok = 0;
            if (first && g > 1 && out[0].z != n - 2) ok = 0;
            first = 0;
            last[0] = out[1].z;
            last[1] = out[2].z;
            have = 1;
        }
    }
    CHECK("the bevel: 8 triangles in 4 batches, the strip carried across each ALPHA_1 write", ok && tris == 8 && batches == 4);
}

static u32 rnd_s = 12345;
static u32 rnd(void) { rnd_s = rnd_s * 1103515245u + 12345u; return rnd_s >> 8; }

static void random_writes(void) {
    static const u32 xyz[4] = { 0x04, 0x05, 0x0C, 0x0D };
    u32 i, r, ok = 1, prims = 0, drawn[8] = { 0 };
    reset();
    for (i = 0; i < 20000; i++) {
        r = rnd() % 16;
        if (r == 0) w(0x00, (rnd() % 7) | (rnd() & 1) << 3 | (rnd() & 1) << 4 | (rnd() & 1) << 8, 0);
        else if (r == 1) w(0x01, rnd() * 2654435761u, rnd());
        else if (r == 2) w(0x03, rnd() & 0x3FFF3FFF, 0);
        else if (r == 3) w(0x02, rnd(), rnd());
        else if (r == 4) w(0x0A, 0, (rnd() & 0xFF) << 24);
        else if (r == 5) w(0x42, rnd() & 0xFF, 0);
        else {
            w(xyz[rnd() % 4 > 0 ? rnd() & 1 : 2 + (rnd() & 1)], x16(rnd() % 4096) | x16(rnd() % 4096) << 16, rnd() * 2654435761u);
            if (!agree()) {
                if (ok) printf("primasm_test: write %u, prim %03x: the port's primitive is not the GS's\n", i, hprim);
                ok = 0;
            }
            if (hcalls) { prims++; drawn[hprim & 7]++; }
        }
    }
    CHECK("20000 random writes: every primitive the GS's", ok);
    CHECK("random writes: every type drew", drawn[0] && drawn[1] && drawn[2] && drawn[3] && drawn[4] && drawn[5] && drawn[6]);
    printf("primasm_test: random: %u primitives\n", prims);
}

/* a GPU's top-left rule at pixel centres: the triangle's corners moved half a pixel on (the GS's 12.4
 * plus 8), the pixel (c, r) sampled at its centre (16 c + 8, 16 r + 8): the same as the GS's corners
 * sampled at (16 c, 16 r) */
static s32 edge(s32 ax, s32 ay, s32 bx, s32 by, s32 px, s32 py) { return (bx - ax) * (py - ay) - (by - ay) * (px - ax); }
static int covers(const s32 *x, const s32 *y, s32 px, s32 py) {
    s32 i, e, sgn = edge(x[0], y[0], x[1], y[1], x[2], y[2]) > 0 ? 1 : -1;
    if (!edge(x[0], y[0], x[1], y[1], x[2], y[2])) return 0;
    for (i = 0; i < 3; i++) {
        s32 ax = x[i], ay = y[i], bx = x[(i + 1) % 3], by = y[(i + 1) % 3], dx, dy;
        if (sgn < 0) { s32 t = ax; ax = bx; bx = t; t = ay; ay = by; by = t; }
        e = edge(ax, ay, bx, by, px, py);
        dx = bx - ax;
        dy = by - ay;
        if (e < 0 || (e == 0 && !(dy < 0 || (dy == 0 && dx > 0)))) return 0; /* top-left edges keep their pixels */
    }
    return 1;
}

#define FBP 0x50
static void sprites(void) {
    static const s32 rect[6][4] = { { 0, 0, 160, 160 }, { 7, 3, 165, 97 }, { 165, 97, 7, 3 },
                                    { 8, 8, 24, 24 }, { 15, 1, 17, 33 }, { 300, 40, 2, 250 } };
    u32 i, k, x, y, ok = 1, got, gpu, n;
    KH1GsSprite s;
    KH1PaVert v;
    s32 tx[3], ty[3];
    for (i = 0; i < 6; i++) {
        memset(&pa, 0, sizeof pa);
        memset(&s, 0, sizeof s);
        kh1_gsmem_reset();
        kh1_pa_prim(&pa, 6);
        memset(&v, 0, sizeof v);
        v.rgba = 0xFFFFFFFFu;
        v.xy = x16(rect[i][0]) | x16(rect[i][1]) << 16;
        kh1_pa_vertex(&pa, &v, 1, out);
        s.xy[0] = v.xy;
        v.xy = x16(rect[i][2]) | x16(rect[i][3]) << 16;
        n = kh1_pa_vertex(&pa, &v, 1, out);
        s.xy[1] = v.xy;
        s.prim = 6;
        s.frame_lo = FBP | 1 << 16 | KH1_PSMCT32 << 24;
        s.xyoffset_lo = 0x7000;
        s.xyoffset_hi = 0x7000;
        s.scissor_lo = 63u << 16;
        s.scissor_hi = 63u << 16;
        s.rgba = 0xFFFFFFFFu;
        kh1_gsmem_flat(1);
        kh1_gsmem_flat_sprite(&s);
        kh1_gsmem_flat(0);
        if (n != 6) { ok = 0; continue; }
        for (y = 0; y < 64; y++)
            for (x = 0; x < 64; x++) {
                got = kh1_gsmem_read_pixel(KH1_PSMCT32, FBP * 32, 1, x, y) != 0;
                gpu = 0;
                for (k = 0; k < 6; k += 3) {
                    u32 j, c = 0;
                    for (j = 0; j < 3; j++) {
                        tx[j] = (s32)(out[k + j].xy & 0xFFFF) - 0x7000 + 8;
                        ty[j] = (s32)(out[k + j].xy >> 16) - 0x7000 + 8;
                    }
                    c = covers(tx, ty, (s32)x * 16 + 8, (s32)y * 16 + 8);
                    if (c && gpu) ok = 0; /* the diagonal drawn twice */
                    gpu |= c;
                }
                if (got != gpu) {
                    if (ok) printf("primasm_test: sprite %u pixel (%u, %u): GS %u, GPU %u\n", i, x, y, got, gpu);
                    ok = 0;
                }
            }
    }
    CHECK("sprites: the two triangles half a pixel on cover the GS's pixels, the diagonal once", ok);
}

int main(void) {
    kh1_gs_prim_hook = hook;
    fan();
    bevel();
    random_writes();
    sprites();
    printf("primasm_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
