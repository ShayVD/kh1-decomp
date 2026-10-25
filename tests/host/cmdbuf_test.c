/* The command recorder (host/port/cmdbuf.c, renderer-spec 4.13 "Session 126", vita-port-plan 5.1bn), fed GS
 * writes through host/null/gsregs.c and host/null/pipes.c's kick hook the way a KH1_HOST_TRACE=5 run is, with
 * made-up packets and texels (no game data): tests/selftest.sh builds it with gcc -m32 when that works.  A
 * frame's commands are replayed through a GPU-style software rasteriser (pixel centres, the top-left rule,
 * the nearest texel, blend.h's GPU blend) and the pixels compared:
 *
 *   columns   8 columns of 16 pixels, each an opaque copy and an additive one (DECAL, texel alpha 0x40 ..
 *             0x80) of a 64 x 64 texture over the 128 x 32 corner of the 3D target: 2 commands with the
 *             union scissor and 12 vertices; the same RGB as host/null/gsmem.c's sprites under each
 *             column's SCISSOR.  While the group is open its commands are held (kh1_cmd_ready).
 *   partial   column 4's additive copy moved: the recorder appends the replayed column; still the same
 *             pixels as gsmem.c's.
 *   bevel     a flat TRISTRIP drawn twice over one band with ALPHA_1 written between pairs of kicks
 *             (additive / subtractive, As 0x90): 16 triangles in 6 commands; the commands replayed in order give the same RGB as
 *             each primitive drawn in the GS's order with the GS's blend (blend.h kh1_blend_gs).
 *   passes    a recorder fed directly over three frames: a 3D target cleared by an opaque full sprite
 *             (DONT_CARE, Z cleared), a slot capture sampling it (STORE: sampled), the display sampling the
 *             capture (STORE: display), the 3D target again (LOAD: the first pass STORE: redrawn; its Z
 *             tested: depth STORE).  Frame 2 clears the 3D target first: frame 1's last 3D pass DISCARD.
 *             Frame 3 samples the 3D target before drawing it: frame 2's last pass STORE (next frame).
 *             Frame 4: 16 full-screen sprites under 32-pixel column scissors clear the target (the game's
 *             strips; one command after the column group), 15 of them do not. */
#include "common.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"
#include "platform/cmdbuf.h"
#include "platform/canvas.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);

void kh1_pipes_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state);
void kh1_pipes_frame(void);
extern void (*kh1_pipes_frame_hook)(const KH1CmdRec *r);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("cmdbuf_test: %s\n", name); fails++; } } while (0)

static u32 x16(s32 px) { return (u32)(0x7000 + px * 16) & 0xFFFF; }
#define W kh1_gs_write
#define IW 128
#define IH 32
#define TBP 0x2000

/* ---- a GPU's rasteriser over a frame's commands ---- */
static u32 img[IH][IW]; /* RGBA8, alpha on the 0x80 scale (blend.h) */

static int edge_in(f32 ax, f32 ay, f32 bx, f32 by, f32 px, f32 py, int ccw, f32 *e) {
    f32 v;
    if (!ccw) { f32 t = ax; ax = bx; bx = t; t = ay; ay = by; by = t; }
    v = (bx - ax) * (py - ay) - (by - ay) * (px - ax);
    *e = ccw ? v : -v;
    if (v > 0) return 1;
    if (v < 0) return 0;
    return (by - ay) < 0 || ((by - ay) == 0 && (bx - ax) > 0); /* top-left edges keep their pixels */
}

static u32 texel(f32 s, f32 t) {
    s32 tx = (s32)(s * 64 + 0x10000) - 0x10000, ty = (s32)(t * 64 + 0x10000) - 0x10000;
    if (tx < 0) tx = 0;
    if (tx > 63) tx = 63;
    if (ty < 0) ty = 0;
    if (ty > 63) ty = 63;
    return kh1_gsmem_read_pixel(KH1_PSMCT32, TBP, 1, (u32)tx, (u32)ty);
}

/* one triangle into img under the scissor; blend: 0 the GPU's blend.h state st, 1 the GS's formula (alpha) */
static void tri(const KH1GpuVert *a, const KH1GpuVert *b, const KH1GpuVert *c, s32 sx0, s32 sy0, s32 sx1, s32 sy1,
                int tex, const KH1BlendState *st, int gs, u32 alpha_lo) {
    f32 area = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
    int ccw = area > 0;
    s32 x, y;
    if (area == 0) return;
    if (area < 0) area = -area;
    if (sx0 < 0) sx0 = 0;
    if (sy0 < 0) sy0 = 0;
    if (sx1 > IW) sx1 = IW;
    if (sy1 > IH) sy1 = IH;
    for (y = sy0; y < sy1; y++)
        for (x = sx0; x < sx1; x++) {
            f32 px = x + 0.5f, py = y + 0.5f, e0, e1, e2, l0, l1, l2;
            u32 cs, d = img[y][x];
            if (!edge_in(b->x, b->y, c->x, c->y, px, py, ccw, &e0) || !edge_in(c->x, c->y, a->x, a->y, px, py, ccw, &e1) ||
                !edge_in(a->x, a->y, b->x, b->y, px, py, ccw, &e2))
                continue;
            l0 = e0 / area;
            l1 = e1 / area;
            l2 = e2 / area;
            if (tex)
                cs = texel(l0 * a->s + l1 * b->s + l2 * c->s, l0 * a->t + l1 * b->t + l2 * c->t); /* DECAL, TCC */
            else
                cs = (u32)c->rgba[0] | (u32)c->rgba[1] << 8 | (u32)c->rgba[2] << 16 | (u32)c->rgba[3] << 24; /* flat */
            if (gs) {
                img[y][x] = kh1_blend_gs(alpha_lo, 0, cs, d & 0xFFFFFF, KH1_PSMCT32) & 0xFFFFFF;
            } else if (st->enable) {
                img[y][x] = kh1_blend_gpu(st, cs, d);
            } else {
                img[y][x] = (cs & 0xFFFFFF) | kh1_blend_store_alpha(cs >> 24) << 24;
            }
        }
}

static void replay(const KH1CmdRec *r) {
    u32 i, j;
    for (i = 0; i < r->ncmd; i++) {
        const KH1Cmd *c = &r->cmd[i];
        const KH1GpuVert *v = kh1_cmd_verts(r, c);
        for (j = 0; j + 2 < c->nv; j += 3)
            tri(&v[j], &v[j + 1], &v[j + 2], c->k.sx0, c->k.sy0, c->k.sx1, c->k.sy1, c->d.pipe[0].shader.tex != 0,
                &c->d.blend, 0, 0);
    }
}

/* ---- the frames ---- */
static KH1CmdRec snap_hdr;  /* the last frame's counts */
static u32 snap_ncmd, snap_nv, snap_sx0, snap_sx1;
static int do_replay;

static void hook(const KH1CmdRec *r) {
    u32 i;
    snap_ncmd = r->ncmd;
    snap_nv = 0;
    for (i = 0; i < r->ncmd; i++) snap_nv += r->cmd[i].nv;
    snap_sx0 = r->ncmd ? (u32)r->cmd[0].k.sx0 : 0;
    snap_sx1 = r->ncmd ? (u32)r->cmd[r->ncmd - 1].k.sx1 : 0;
    snap_hdr.frame = r->frame;
    if (do_replay) replay(r);
}

static void env(void) {
    W(0x4C, 0xD0 | 8 << 16, 0);           /* FRAME_1: 0x1A00 (the 3D target) */
    W(0x4E, 0x31000070, 1);               /* ZBUF_1 Z24, ZMSK */
    W(0x47, 0, 0);                        /* TEST_1: ZTE 0 */
    W(0x18, 0x7000, 0x7000);              /* XYOFFSET_1 */
    W(0x40, 511u << 16, 383u << 16);      /* SCISSOR_1 */
    W(0x06, TBP | 1 << 14 | 6 << 26 | 2u << 30, 1 | 1 << 2 | 1 << 3); /* TEX0_1: 64 x 64 CT32, TCC, DECAL */
    W(0x14, 0, 0);                        /* TEX1_1: point sampling */
    W(0x08, 5, 0);                        /* CLAMP_1 */
    W(0x42, 0x48, 0);                     /* ALPHA_1: Cs x As + Cd */
}

static void texels(void) {
    u32 x, y;
    for (y = 0; y < 64; y++)
        for (x = 0; x < 64; x++)
            kh1_gsmem_write_pixel(KH1_PSMCT32, TBP, 1, x, y, (0x40 + (x * 7 + y) % 0x41) << 24 | (y * 4) << 16 |
                                  (x * 3 + 17) << 8 | (x * 5 + y * 3) % 200);
}

/* the 128 x 32 copy, offset by d pixels: 64 texels stretched over 128, 32 rows 1:1 */
static void copy(s32 d) {
    W(0x03, 0, 0);
    W(0x05, x16(d) | x16(d) << 16, 0);
    W(0x03, 64 * 16 | (32u * 16) << 16, 0);
    W(0x05, x16(IW + d) | x16(IH + d) << 16, 0);
}

static void column(u32 k) { W(0x40, 16 * k | (16 * k + 15) << 16, (u32)(IH - 1) << 16); }

/* img against gsmem.c's 3D target, RGB */
static int same_as_gs(const char *what) {
    u32 x, y, bad = 0;
    for (y = 0; y < IH; y++)
        for (x = 0; x < IW; x++) {
            u32 g = kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1A00, 8, x, y) & 0xFFFFFF, c = img[y][x] & 0xFFFFFF;
            if (g != c) {
                if (!bad) printf("cmdbuf_test: %s: pixel (%u, %u) GS %06x, commands %06x\n", what, x, y, g, c);
                bad++;
            }
        }
    return !bad;
}

static void columns(int partial) {
    u32 k;
    kh1_gsmem_reset();
    texels();
    memset(img, 0, sizeof img);
    env();
    for (k = 0; k < 8; k++) {
        column(k);
        W(0x00, 0x116, 0); /* SPRITE | TME | FST, no blend */
        copy(0);
        W(0x00, 0x156, 0); /* + ABE */
        copy(partial && k == 4 ? -3 : -2);
    }
    do_replay = 1;
    kh1_pipes_frame();
    do_replay = 0;
    if (!partial) {
        CHECK("columns: 2 commands with the union scissor and 12 vertices", snap_ncmd == 2 && snap_nv == 12 &&
              snap_sx0 == 0 && snap_sx1 == IW);
        CHECK("columns: 7 columns merged", snap_hdr.frame.cmds == 2);
        CHECK("columns: the same pixels as gsmem.c's sprites", same_as_gs("columns"));
    } else {
        printf("cmdbuf_test: partial: %u commands, %u vertices\n", snap_ncmd, snap_nv);
        CHECK("partial: the replayed column is appended (more commands, every vertex kept)", snap_ncmd > 2 &&
              snap_nv > 12);
        CHECK("partial: the same pixels as gsmem.c's sprites", same_as_gs("partial"));
    }
}

/* held: the group's commands are not ready until it ends */
static void held(void) {
    static u8 vm[2][64 << 10] __attribute__((aligned(64))), um[2][16 << 10] __attribute__((aligned(64)));
    static KH1CmdRec r;
    KH1DrawRegs g;
    KH1DrawState d;
    KH1RenderPass p;
    static const KH1Canvas c43 = { 1.0f, 0.0f, 0.0f, 0, 8192 };
    KH1GpuVert v[6];
    u32 k, ok = 1;
    kh1_cmd_init(&r, vm, sizeof vm[0], um, sizeof um[0]);
    memset(&g, 0, sizeof g);
    memset(v, 0, sizeof v);
    g.prim = 0x116;
    g.frame_lo = 0xD0 | 8 << 16;
    g.zbuf_lo = 0x31000070;
    g.zbuf_hi = 1;
    g.tex0_lo = TBP | 1 << 14 | 6 << 26 | 2u << 30;
    g.tex0_hi = 1 | 1 << 2;
    g.clamp_lo = 5;
    kh1_drawstate_of(&g, &d);
    kh1_target_of(g.frame_lo, 0, g.zbuf_lo, g.zbuf_hi, 0, 0 | 31u << 16, 383u << 16, 0x7000, 0x7000, &c43, 1.0f, &p);
    kh1_cmd_prim(&r, &d, &p, v, 6, 0x111);
    CHECK("held: a group's first command is held", kh1_cmd_ready(&r) == 0 && r.held == 0);
    for (k = 1; k < 4; k++) {
        kh1_target_of(g.frame_lo, 0, g.zbuf_lo, g.zbuf_hi, 0, 32 * k | (32 * k + 31) << 16, 383u << 16, 0x7000, 0x7000,
                      &c43, 1.0f, &p);
        kh1_cmd_prim(&r, &d, &p, v, 6, 0x111);
        if (kh1_cmd_ready(&r) != 0 || r.ncmd != 1 || r.cmd[0].k.sx1 != 32 * (s32)(k + 1)) ok = 0;
    }
    CHECK("held: each column widens the held command", ok);
    kh1_cmd_break(&r);
    CHECK("held: a transfer ends the group (the open command alone is not ready)", r.held == -1 && kh1_cmd_ready(&r) == 0);
    kh1_cmd_prim(&r, &d, &p, v, 6, 0x222);
    CHECK("held: then the first command is ready", kh1_cmd_ready(&r) == 1 && r.ncmd == 2);
}

/* the bevel: a flat strip with ALPHA_1 changes, twice over one band, against the GS's order */
static struct { KH1GpuVert v[3]; u32 alpha; } ref[64];
static u32 nref;
static void cap(u32 prim, const KH1GsVert *v, u32 n, u32 state) {
    KH1PrimAsm pa;
    KH1PaVert out[6];
    KH1RenderPass p;
    KH1VertCtx c;
    u32 i, nv = 0;
    memset(&pa, 0, sizeof pa);
    memset(&p, 0, sizeof p);
    p.ofx = p.ofy = 0x7000;
    p.scale = 1.0f;
    kh1_pa_prim(&pa, (prim & ~7u) | 3);
    for (i = 0; i < n; i++) nv = kh1_pa_vertex(&pa, (const KH1PaVert *)&v[i], 1, out);
    kh1_vertex_ctx(&c, &p, 0, prim, 0, 0);
    if (nv == 3 && nref < 64) {
        kh1_vertex_of(&c, out, 3, ref[nref].v);
        ref[nref++].alpha = kh1_gs_state()->ctx[0].alpha.lo;
    }
    kh1_pipes_prim(prim, v, n, state);
}

static void bevel(void) {
    static const u32 alpha[5] = { 0x48, 0x42, 0x48, 0x42, 0x48 };
    static u32 start[IH][IW], gsimg[IH][IW];
    u32 x, y, g, k, n, pass, bad = 0;
    for (y = 0; y < IH; y++)
        for (x = 0; x < IW; x++) start[y][x] = 0x80000000u | (x * 3) << 16 | (y * 5 + 40) << 8 | 0x60;
    nref = 0;
    kh1_gs_prim_hook = cap;
    W(0x40, 511u << 16, 383u << 16);
    W(0x00, 4 | 1 << 6, 0); /* TRISTRIP | ABE, flat */
    for (pass = 0; pass < 2; pass++) {
        W(0x00, 4 | 1 << 6, 0);
        for (g = 0; g < 5; g++) {
            W(0x42, alpha[(g + pass) % 5], 0);
            for (k = 0; k < 2; k++) {
                n = g * 2 + k;
                W(0x01, 0x90000000u | (n * 37 + pass * 50) << 16 | (n * 11) << 8 | (0x30 + n * 9), 0);
                W(0x04, x16((s32)((n >> 1) * 24 + pass * 5)) | x16((s32)((n & 1) * 28 + 2)) << 16, 0);
            }
        }
    }
    kh1_gs_prim_hook = kh1_pipes_prim;
    /* the GS's order */
    memcpy(img, start, sizeof img);
    for (n = 0; n < nref; n++) tri(&ref[n].v[0], &ref[n].v[1], &ref[n].v[2], 0, 0, IW, IH, 0, 0, 1, ref[n].alpha);
    memcpy(gsimg, img, sizeof img);
    /* the commands */
    memcpy(img, start, sizeof img);
    for (y = 0; y < IH; y++)
        for (x = 0; x < IW; x++) img[y][x] = (img[y][x] & 0xFFFFFF) | 0xFFu << 24;
    do_replay = 1;
    kh1_pipes_frame();
    do_replay = 0;
    printf("cmdbuf_test: bevel: %u primitives, %u commands\n", nref, snap_ncmd);
    for (y = 0; y < IH; y++)
        for (x = 0; x < IW; x++)
            if ((img[y][x] & 0xFFFFFF) != (gsimg[y][x] & 0xFFFFFF)) {
                if (!bad) printf("cmdbuf_test: bevel pixel (%u, %u): GS order %06x, commands %06x\n", x, y,
                                 gsimg[y][x] & 0xFFFFFF, img[y][x] & 0xFFFFFF);
                bad++;
            }
    CHECK("bevel: 16 triangles in 6 commands (a command per ALPHA_1 run)", nref == 16 && snap_ncmd == 6);
    CHECK("bevel: the commands in order give the GS's pixels", !bad);
}

/* ---- the passes' load / store needs ---- */
static KH1CmdRec pr;
static u8 pvm[2][64 << 10] __attribute__((aligned(64))), pum[2][16 << 10] __attribute__((aligned(64)));

/* a sprite x0 .. x1, y0 .. y1 (window pixels) in a state, under the full scissor of the frame */
static void psprite(u32 frame_lo, u32 test_lo, u32 zmsk, u32 prim, u32 tex0_lo, u32 sc_lo, u32 sc_hi, s32 x0, s32 y0,
                    s32 x1, s32 y1) {
    static const KH1Canvas c43 = { 1.0f, 0.0f, 0.0f, 0, 8192 };
    KH1DrawRegs g;
    KH1DrawState d;
    KH1RenderPass p;
    KH1PrimAsm pa;
    KH1PaVert v, out[6];
    KH1VertCtx vc;
    KH1GpuVert gv[6];
    memset(&g, 0, sizeof g);
    g.prim = prim;
    g.frame_lo = frame_lo;
    g.zbuf_lo = 0x31000070;
    g.zbuf_hi = zmsk;
    g.test_lo = test_lo;
    g.alpha_lo = 0x44;
    g.tex0_lo = tex0_lo;
    g.tex0_hi = 1 << 2;
    g.clamp_lo = 5;
    kh1_drawstate_of(&g, &d);
    kh1_target_of(frame_lo, 0, g.zbuf_lo, g.zbuf_hi, test_lo, sc_lo, sc_hi, 0x7000, 0x7000, &c43, 1.0f, &p);
    memset(&pa, 0, sizeof pa);
    memset(&v, 0, sizeof v);
    kh1_pa_prim(&pa, prim);
    v.rgba = 0x80808080u;
    v.xy = x16(x0) | x16(y0) << 16;
    kh1_pa_vertex(&pa, &v, 1, out);
    v.xy = x16(x1) | x16(y1) << 16;
    v.uv = 64 * 16 | (64u * 16) << 16;
    kh1_pa_vertex(&pa, &v, 1, out);
    kh1_vertex_ctx(&vc, &p, g.zbuf_lo, prim, tex0_lo, g.tex0_hi);
    kh1_vertex_of(&vc, out, 6, gv);
    kh1_cmd_prim(&pr, &d, &p, gv, 6, ((u32)x0 * 31 + (u32)y0 * 977 + (u32)x1 * 7919 + (u32)y1 * 104729 + prim) | 1);
}

#define F_MAIN (0xD0 | 8 << 16)
#define F_SLOT (0x1B0 | 4 << 16)
#define F_DISP (0 | 8 << 16 | 1 << 24)
#define T_MAIN (0x1A00 | 8 << 14 | 9u << 26 | 1u << 30)  /* CT32 512 x 512 */
#define T_SLOT (0x3600 | 4 << 14 | 8u << 26 | 0u << 30)
#define S_MAIN 511u << 16, 383u << 16
#define S_SLOT 255u << 16, 191u << 16
#define S_DISP 511u << 16, 447u << 16
#define Z_ALWAYS_W (1 << 16 | 1 << 17)   /* TEST: ZTE, ZTST ALWAYS */
#define Z_GEQUAL (1 << 16 | 2 << 17)

static void passes(void) {
    const KH1CmdPass *a, *b, *c, *d;
    kh1_cmd_init(&pr, pvm, sizeof pvm[0], pum, sizeof pum[0]);
    /* frame 1 */
    psprite(F_MAIN, Z_ALWAYS_W, 0, 0x6, 0, S_MAIN, 0, 0, 512, 384);          /* the clear: opaque, Z written */
    psprite(F_MAIN, Z_GEQUAL, 0, 0x46, 0, S_MAIN, 10, 10, 100, 100);         /* a blended draw, Z tested */
    psprite(F_SLOT, 0, 1, 0x116, T_MAIN, S_SLOT, 0, 0, 256, 192);            /* the capture samples it */
    psprite(F_DISP, 0, 1, 0x156, T_SLOT, S_DISP, 0, 0, 100, 100);            /* the display samples the capture */
    psprite(F_MAIN, Z_GEQUAL, 0, 0x46, 0, S_MAIN, 20, 20, 60, 60);           /* the 3D target again */
    kh1_cmd_frame(&pr);
    CHECK("passes: frame 1 has 4 passes", pr.npass == 4);
    a = &pr.pass[0];
    b = &pr.pass[1];
    c = &pr.pass[2];
    d = &pr.pass[3];
    printf("cmdbuf_test: frame 1 pass 1: %s\n", kh1_cmd_pass_str(a));
    printf("cmdbuf_test: frame 1 pass 4: %s\n", kh1_cmd_pass_str(d));
    CHECK("passes: the cleared 3D target needs no load, its colour and depth are stored (sampled, redrawn, Z tested)",
          a->cleared && a->zcleared && a->load == KH1_LOAD_DONT_CARE && a->dload == KH1_LOAD_DONT_CARE &&
          a->store == KH1_STORE_STORE && a->why == (KH1_WHY_SAMPLED | KH1_WHY_REDRAWN) && a->dstore == KH1_STORE_STORE);
    CHECK("passes: the capture is stored for the display", b->rt == KH1_RT_SLOT && b->store == KH1_STORE_STORE &&
          b->why == KH1_WHY_SAMPLED && b->load == KH1_LOAD_DONT_CARE);
    CHECK("passes: the display is stored (scanned out)", c->rt == KH1_RT_DISPLAY && c->store == KH1_STORE_STORE &&
          c->why == KH1_WHY_DISPLAY);
    CHECK("passes: the 3D target drawn again loads colour and depth; its store waits for the next frame",
          d->load == KH1_LOAD_LOAD && d->dload == KH1_LOAD_LOAD && d->store == KH1_STORE_OPEN &&
          d->dstore == KH1_STORE_OPEN);
    kh1_cmd_reset_frame(&pr);
    /* frame 2: cleared first, so frame 1's last 3D pass is discarded */
    psprite(F_MAIN, Z_ALWAYS_W, 0, 0x6, 0, S_MAIN, 0, 0, 512, 384);
    psprite(F_MAIN, Z_GEQUAL, 0, 0x46, 0, S_MAIN, 10, 10, 100, 100);
    kh1_cmd_frame(&pr);
    CHECK("passes: frame 2's clear discards frame 1's last 3D pass (colour and depth)", pr.total.discards >= 1 &&
          pr.total.ddiscards >= 1 && pr.total.why[2] == 0 && pr.pass[0].load == KH1_LOAD_DONT_CARE);
    kh1_cmd_reset_frame(&pr);
    /* frame 3: the 3D target sampled before it is drawn: frame 2's last pass is stored */
    psprite(F_SLOT, 0, 1, 0x116, T_MAIN, S_SLOT, 0, 0, 256, 192);
    kh1_cmd_frame(&pr);
    CHECK("passes: frame 3 samples the 3D target first: frame 2's pass is stored for the next frame",
          pr.total.why[2] == 1);
    kh1_cmd_reset_frame(&pr);
    {
        /* frame 4: the 3D target cleared in 16 strips of 32 pixels, each a full-screen sprite under its column
         * SCISSOR (merged into one command), then the same with column 9 missing */
        u32 k, miss;
        for (miss = 0; miss < 2; miss++) {
            for (k = 0; k < 16; k++)
                if (!miss || k != 9) psprite(F_MAIN, 0, 1, 0x6, 0, 32 * k | (32 * k + 31) << 16, 383u << 16, 0, 0, 512, 384);
            psprite(F_MAIN, 0, 1, 0x46, 0, S_MAIN, 10, 10, 50, 50);
            kh1_cmd_frame(&pr);
            printf("cmdbuf_test: strips%s: %u passes %u commands, cmd 1 scissor %d..%d, %s\n", miss ? " (one missing)" : "",
                   pr.npass, pr.ncmd, pr.cmd[0].k.sx0, pr.cmd[0].k.sx1, kh1_cmd_pass_str(&pr.pass[0]));
            if (!miss)
                CHECK("passes: 16 strips under column scissors clear the 3D target (one command)", pr.npass == 1 &&
                      pr.ncmd == 2 && pr.pass[0].cleared && pr.pass[0].load == KH1_LOAD_DONT_CARE);
            else
                CHECK("passes: 15 strips do not", pr.npass == 1 && !pr.pass[0].cleared && pr.pass[0].load == KH1_LOAD_LOAD);
            kh1_cmd_reset_frame(&pr);
        }
    }
    kh1_cmd_finish(&pr);
    printf("cmdbuf_test: passes: %u passes, %u load, %u don't care, %u store, %u discard, %u open; depth %u load, %u "
           "store, %u discard\n", pr.total.passes, pr.total.loads, pr.total.dont_care, pr.total.stores,
           pr.total.discards, pr.total.open, pr.total.dloads, pr.total.dstores, pr.total.ddiscards);
    CHECK("passes: every pass counted once", pr.total.stores + pr.total.discards + pr.total.open == pr.total.passes);
}

int main(void) {
    kh1_gs_reset();
    kh1_gsmem_reset();
    kh1_gs_prim_hook = kh1_pipes_prim;
    kh1_pipes_frame_hook = hook;
    columns(0);
    columns(1);
    held();
    bevel();
    passes();
    printf("cmdbuf_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
