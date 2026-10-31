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
 *             strips; one command after the column group), 15 of them do not.
 *   gxm       (session 128) columns, partial and transfers again, each frame walked by host/port/gxmrec.c into
 *             GXM calls and only the calls replayed (programs from the frame's pipeline table, uniforms read
 *             from the ring at SET_UNIFORMS, textures and palettes by slot, target uploads and the CLUT
 *             read-back): the same pixels; a DONT_CARE scene that is cleared starts from garbage, a DISCARD
 *             scene ends in garbage, and that still gives the same pixels.
 *   date      (session 129) DATE (DATM 1, brightfade's form) on two overlapping flat sprites over a target whose
 *             alpha bit 7 is striped: the first writes alpha 0, so the second must skip the overlap's marked
 *             pixels.  Replayed from the GXM calls with a stencil buffer that starts as garbage (all 1): each
 *             sprite a command of its own, its clear and set-up over its own vertices, then the draw; the same
 *             RGB and alpha bit 7 as the GS's DATE (gsmem.c's copy, then the rule applied sprite by sprite in the
 *             GS's order).  Without the clear the replay differs (the check sees it). */
#include "common.h"
#include "../../host/null/gsregs.h"
#include "../../host/null/gsmem.h"
#include "platform/cmdbuf.h"
#include "platform/canvas.h"
#include "platform/palcache.h"
#include "platform/texcache.h"
#include "platform/gxmrec.h"

int printf(const char *, ...);
void *memset(void *, int, __SIZE_TYPE__);
void *memcpy(void *, const void *, __SIZE_TYPE__);

void kh1_pipes_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state);
void kh1_pipes_frame(void);
extern void (*kh1_pipes_frame_hook)(const KH1CmdRec *r);
const KH1CmdRec *kh1_pipes_recorder(void);
const KH1PalCache *kh1_pipes_palcache(void);
const KH1TexCache *kh1_pipes_texcache(void);

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

/* session 127: the image a replayed draw writes and its texture fetch (by default img and texel) */
static u32 *rt_img = &img[0][0];
static s32 rt_w = IW, rt_h = IH;
static u32 texel(f32 s, f32 t);
static u32 (*fetch)(f32 s, f32 t) = texel;
#define PX(x, y) rt_img[(y) * rt_w + (x)]

static u32 texel(f32 s, f32 t) {
    s32 tx = (s32)(s * 64 + 0x10000) - 0x10000, ty = (s32)(t * 64 + 0x10000) - 0x10000;
    if (tx < 0) tx = 0;
    if (tx > 63) tx = 63;
    if (ty < 0) ty = 0;
    if (ty > 63) ty = 63;
    return kh1_gsmem_read_pixel(KH1_PSMCT32, TBP, 1, (u32)tx, (u32)ty);
}

/* session 129: the stencil a replayed GXM draw tests or writes (img only): tri_stencil 0 none, 1 draw where it is 1,
 * 2 the DATE set-up (1 where the target's alpha is DATM: tri_datm), 3 the clear (0) */
static u8 stn[IH][IW];
static int tri_stencil, tri_datm;

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
    if (sx1 > rt_w) sx1 = rt_w;
    if (sy1 > rt_h) sy1 = rt_h;
    for (y = sy0; y < sy1; y++)
        for (x = sx0; x < sx1; x++) {
            f32 px = x + 0.5f, py = y + 0.5f, e0, e1, e2, l0, l1, l2;
            u32 cs, d = PX(x, y);
            if (!edge_in(b->x, b->y, c->x, c->y, px, py, ccw, &e0) || !edge_in(c->x, c->y, a->x, a->y, px, py, ccw, &e1) ||
                !edge_in(a->x, a->y, b->x, b->y, px, py, ccw, &e2))
                continue;
            if (tri_stencil == 3) { stn[y][x] = 0; continue; }
            if (tri_stencil == 2) {
                KH1AtestState as;
                memset(&as, 0, sizeof as);
                as.date = 1;
                as.datm = (u8)tri_datm;
                if (kh1_atest_date_mark(&as, d >> 24)) stn[y][x] = 1;
                continue;
            }
            if (tri_stencil == 1 && stn[y][x] != 1) continue;
            l0 = e0 / area;
            l1 = e1 / area;
            l2 = e2 / area;
            if (tex)
                cs = fetch(l0 * a->s + l1 * b->s + l2 * c->s, l0 * a->t + l1 * b->t + l2 * c->t); /* DECAL, TCC */
            else
                cs = (u32)c->rgba[0] | (u32)c->rgba[1] << 8 | (u32)c->rgba[2] << 16 | (u32)c->rgba[3] << 24; /* flat */
            if (gs) {
                PX(x, y) = kh1_blend_gs(alpha_lo, 0, cs, d & 0xFFFFFF, KH1_PSMCT32) & 0xFFFFFF;
            } else if (st->enable) {
                PX(x, y) = kh1_blend_gpu(st, cs, d);
            } else {
                PX(x, y) = (cs & 0xFFFFFF) | kh1_blend_store_alpha(cs >> 24) << 24;
            }
        }
}

static void replay_x(const KH1CmdRec *r);
static void replay_gxm(const KH1CmdRec *r);
static int do_replay;       /* 1 the frame's draws replayed into img; 2 session 127's transfer frame (replay_x) */
static int use_gxm;         /* session 128: replay the frame's GXM calls instead (replay_gxm) */
static void replay(const KH1CmdRec *r) {
    u32 i, j;
    if (use_gxm) { replay_gxm(r); return; }
    if (do_replay == 2) { replay_x(r); return; }
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

static void hook(const KH1CmdRec *r) {
    u32 i;
    s32 first = -1, last = -1;
    snap_ncmd = snap_nv = 0;
    for (i = 0; i < r->ncmd; i++) /* the draw commands (session 127: the texture decodes are commands too) */
        if (r->cmd[i].kind == KH1_CMD_DRAW) {
            snap_ncmd++;
            snap_nv += r->cmd[i].nv;
            if (first < 0) first = (s32)i;
            last = (s32)i;
        }
    snap_sx0 = first >= 0 ? (u32)r->cmd[first].k.sx0 : 0;
    snap_sx1 = last >= 0 ? (u32)r->cmd[last].k.sx1 : 0;
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
        CHECK("columns: 7 columns merged", snap_hdr.frame.cmds == 2 + snap_hdr.frame.textures);
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

static KH1GxmRec gxp; /* session 128: frame 1's GXM calls */

/* the scenes of a frame's GXM calls against its passes: one BEGIN / END pair a pass, in order, each with its loads
 * and stores */
static int gxm_scenes_match(const KH1CmdRec *r, const KH1GxmRec *g) {
    u32 i, n = 0, open = 0;
    for (i = 0; i < g->n; i++) {
        const KH1GxmCall *c = &g->call[i];
        const KH1CmdPass *p = &r->pass[n < r->npass ? n : 0];
        if (c->op == KH1_GXM_BEGIN_SCENE) {
            if (open || n >= r->npass || c->rt != p->rt || c->load != p->load || (p->depth && c->dload != p->dload)) return 0;
            open = 1;
        } else if (c->op == KH1_GXM_END_SCENE) {
            if (!open || c->store != p->store || (p->depth && p->zwrite && c->dstore != p->dstore)) return 0;
            open = 0;
            n++;
        } else if (c->op == KH1_GXM_DRAW && !open) {
            return 0;
        }
    }
    return !open && n == r->npass;
}

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
    kh1_gxm_clear(&gxp);
    kh1_gxm_frame(&gxp, &pr);
    CHECK("passes: frame 1's GXM calls: a scene a pass with its loads and stores, 5 draws",
          gxm_scenes_match(&pr, &gxp) && gxp.frame.scenes == 4 && gxp.frame.draws == 5 &&
          gxp.call[0].op == KH1_GXM_BEGIN_SCENE && gxp.call[0].cleared && gxp.call[0].load == KH1_LOAD_DONT_CARE &&
          gxp.call[0].dload == KH1_LOAD_DONT_CARE);
    kh1_cmd_reset_frame(&pr);
    /* frame 2: cleared first, so frame 1's last 3D pass is discarded */
    psprite(F_MAIN, Z_ALWAYS_W, 0, 0x6, 0, S_MAIN, 0, 0, 512, 384);
    psprite(F_MAIN, Z_GEQUAL, 0, 0x46, 0, S_MAIN, 10, 10, 100, 100);
    kh1_cmd_frame(&pr);
    CHECK("passes: frame 2's clear discards frame 1's last 3D pass (colour and depth)", pr.total.discards >= 1 &&
          pr.total.ddiscards >= 1 && pr.total.why[2] == 0 && pr.pass[0].load == KH1_LOAD_DONT_CARE);
    kh1_gxm_frame(&gxp, &pr);
    CHECK("passes: frame 2's GXM calls match its passes", gxm_scenes_match(&pr, &gxp) && gxp.total.frames == 2);
    kh1_cmd_reset_frame(&pr);
    /* frame 3: the 3D target sampled before it is drawn: frame 2's last pass is stored */
    psprite(F_SLOT, 0, 1, 0x116, T_MAIN, S_SLOT, 0, 0, 256, 192);
    kh1_cmd_frame(&pr);
    CHECK("passes: frame 3 samples the 3D target first: frame 2's pass is stored for the next frame",
          pr.total.why[2] == 1);
    kh1_cmd_reset_frame(&pr);
    {
        /* frame 4: the 3D target cleared in 16 strips of 32 pixels, each a full-screen sprite under its column
         * SCISSOR (merged into one command), then the same with column 9 missing; then 12 strips of 42 or 43
         * pixels, off the 8-pixel cells (2026-10-31: the wide view's strips) */
        u32 k, miss;
        for (miss = 0; miss < 3; miss++) {
            for (k = 0; k < 16; k++)
                if (miss == 2) {
                    if (k < 12) psprite(F_MAIN, 0, 1, 0x6, 0, 512 * k / 12 | (512 * (k + 1) / 12 - 1) << 16, 383u << 16, 0, 0, 512, 384);
                } else if (!miss || k != 9) psprite(F_MAIN, 0, 1, 0x6, 0, 32 * k | (32 * k + 31) << 16, 383u << 16, 0, 0, 512, 384);
            psprite(F_MAIN, 0, 1, 0x46, 0, S_MAIN, 10, 10, 50, 50);
            kh1_cmd_frame(&pr);
            printf("cmdbuf_test: strips%s: %u passes %u commands, cmd 1 scissor %d..%d, %s\n",
                   miss == 2 ? " (off the cells)" : miss ? " (one missing)" : "",
                   pr.npass, pr.ncmd, pr.cmd[0].k.sx0, pr.cmd[0].k.sx1, kh1_cmd_pass_str(&pr.pass[0]));
            if (!miss)
                CHECK("passes: 16 strips under column scissors clear the 3D target (one command)", pr.npass == 1 &&
                      pr.ncmd == 2 && pr.pass[0].cleared && pr.pass[0].load == KH1_LOAD_DONT_CARE);
            else if (miss == 2)
                CHECK("passes: 12 strips off the 8-pixel cells clear it too", pr.npass == 1 && pr.ncmd == 2 &&
                      pr.pass[0].cleared && pr.pass[0].load == KH1_LOAD_DONT_CARE);
            else
                CHECK("passes: 15 strips do not", pr.npass == 1 && !pr.pass[0].cleared && pr.pass[0].load == KH1_LOAD_LOAD);
            kh1_cmd_reset_frame(&pr);
        }
    }
    {
        /* frame 5 (2026-10-31, the hoist): the 3D target, then a small target drawn without reading the 3D one,
         * then the 3D target again, sampling the small one: the small pass is drawn first and the 3D target is one
         * pass, never stored and reloaded in between; with kh1_cmd_hoist off it stays 3 passes */
        int on;
        for (on = 1; on >= 0; on--) {
            kh1_cmd_hoist = on;
            psprite(F_MAIN, Z_ALWAYS_W, 0, 0x6, 0, S_MAIN, 0, 0, 512, 384);
            psprite(F_MAIN, Z_GEQUAL, 0, 0x46, 0, S_MAIN, 10, 10, 100, 100);
            psprite(F_SLOT, 0, 1, 0x6, 0, S_SLOT, 0, 0, 64, 64);
            psprite(F_MAIN, Z_GEQUAL, 0, 0x156, T_SLOT, S_MAIN, 20, 20, 60, 60);
            kh1_cmd_frame(&pr);
            printf("cmdbuf_test: hoist %d: %u passes, %u hoisted; pass 1 %s\n", on, pr.npass, pr.frame.hoists,
                   kh1_cmd_pass_str(&pr.pass[0]));
            if (on)
                CHECK("passes: a small pass between two 3D passes is drawn first, the 3D target one cleared pass",
                      pr.npass == 2 && pr.frame.hoists == 1 && pr.pass[0].rt == KH1_RT_SLOT &&
                      pr.pass[0].ncmd == 1 && pr.pass[1].ncmd == 3 && pr.pass[1].cleared &&
                      pr.pass[1].load == KH1_LOAD_DONT_CARE && pr.cmd[0].pass == 0 && pr.cmd[1].pass == 1 &&
                      pr.cmd[3].pass == 1);
            else
                CHECK("passes: with the hoist off it is 3 passes, the 3D target reloaded",
                      pr.npass == 3 && pr.frame.hoists == 0 && pr.pass[2].load == KH1_LOAD_LOAD);
            kh1_gxm_frame(&gxp, &pr);
            CHECK("passes: and its GXM calls match its passes", gxm_scenes_match(&pr, &gxp));
            kh1_cmd_reset_frame(&pr);
        }
        kh1_cmd_hoist = 1;
        /* frame 6: the small pass samples the 3D target: not moved */
        psprite(F_MAIN, Z_ALWAYS_W, 0, 0x6, 0, S_MAIN, 0, 0, 512, 384);
        psprite(F_SLOT, 0, 1, 0x116, T_MAIN, S_SLOT, 0, 0, 64, 64);
        psprite(F_MAIN, Z_GEQUAL, 0, 0x46, 0, S_MAIN, 20, 20, 60, 60);
        kh1_cmd_frame(&pr);
        CHECK("passes: a small pass that samples the 3D target is not moved", pr.npass == 3 && pr.frame.hoists == 0);
        kh1_cmd_reset_frame(&pr);
    }
    kh1_cmd_finish(&pr);
    printf("cmdbuf_test: passes: %u passes, %u load, %u don't care, %u store, %u discard, %u open; depth %u load, %u "
           "store, %u discard\n", pr.total.passes, pr.total.loads, pr.total.dont_care, pr.total.stores,
           pr.total.discards, pr.total.open, pr.total.dloads, pr.total.dstores, pr.total.ddiscards);
    CHECK("passes: every pass counted once", pr.total.stores + pr.total.discards + pr.total.open == pr.total.passes);
}

/* ---- session 127: the transfers as commands ----
 * One frame through gsregs.c and pipes.c with every kind of transfer between the draws, replayed the way a GPU
 * would run the list (replay_x): the textures from the recorder's texture cache entries the draws name, an
 * upload into a render target written into that target's image, the CLUT read back from the CLUT pass's
 * image, a target's texture from its image; the 3D target's pixels against gsmem.c's. */
#define XW 128
#define XH 16
static u32 offimg[64][64], clutimg[16][16];
static KH1Cmd xc[64];
static KH1CmdPass xp[16];
static u32 nxc, nxp, xpal[256], xpal_ok, xpal_bad;
static const u32 *x_tex, *x_pal;
static u32 x_tw, x_th, x_psm;
static u32 (*x_img)[64];

static u32 fetch_tex(f32 s, f32 t) {
    s32 tx = (s32)(s * x_tw + 0x10000) - 0x10000, ty = (s32)(t * x_th + 0x10000) - 0x10000;
    u32 v;
    if (tx < 0) tx = 0;
    if (ty < 0) ty = 0;
    if (tx >= (s32)x_tw) tx = (s32)x_tw - 1;
    if (ty >= (s32)x_th) ty = (s32)x_th - 1;
    if (x_img) { /* a render target's own texture: the stored alpha back on the GS's scale */
        v = x_img[ty][tx];
        return (v & 0xFFFFFF) | kh1_blend_load_alpha(v >> 24) << 24;
    }
    v = x_tex[ty * x_tw + (u32)tx];
    return x_psm == KH1_PSMT8 ? x_pal[v & 0xFF] : v;
}

static void replay_x(const KH1CmdRec *r) {
    const KH1TexCache *tc = kh1_pipes_texcache();
    const KH1PalCache *pc = kh1_pipes_palcache();
    u32 i, j, e;
    nxc = r->ncmd < 64 ? r->ncmd : 64;
    nxp = r->npass < 16 ? r->npass : 16;
    memcpy(xc, r->cmd, nxc * sizeof *xc);
    memcpy(xp, r->pass, nxp * sizeof *xp);
    x_pal = 0;
    for (i = 0; i < r->ncmd; i++) {
        const KH1Cmd *c = &r->cmd[i];
        const KH1GpuVert *v;
        if (c->kind == KH1_CMD_UPLOAD && c->x.dst) { /* into the off-screen buffer's image */
            for (j = 0; j < c->x.h; j++)
                for (e = 0; e < c->x.w; e++) {
                    u32 g = kh1_gsmem_read_pixel(KH1_PSMCT32, c->x.bb_hi & 0x3FFF, c->x.bb_hi >> 16 & 63, c->x.dx + e, c->x.dy + j);
                    offimg[c->x.dy + j][c->x.dx + e] = (g & 0xFFFFFF) | kh1_blend_store_alpha(g >> 24) << 24;
                }
            continue;
        }
        if (c->kind == KH1_CMD_CLUT) {
            if (c->x.src) { /* read back from the CLUT pass's image: entries 8-15 / 16-23 of each 32 swapped */
                for (e = 0; e < 256; e++) {
                    u32 p = (e & 0xE7) | (e & 8) << 1 | (e & 0x10) >> 1, g = clutimg[p >> 4][p & 15];
                    xpal[e] = (g & 0xFFFFFF) | kh1_blend_load_alpha(g >> 24) << 24;
                }
                x_pal = xpal;
                xpal_ok = c->x.slot >= 0;
                xpal_bad = 0;
                for (e = 0; xpal_ok && e < 256; e++)
                    if (xpal[e] != pc->slot[c->x.slot].col[e]) xpal_bad++;
            } else if (c->x.slot >= 0) {
                x_pal = pc->slot[c->x.slot].col;
            }
            continue;
        }
        if (c->kind != KH1_CMD_DRAW) continue;
        /* the target's image */
        if (c->k.rt == KH1_RT_OFFSCREEN) { rt_img = &offimg[0][0]; rt_w = rt_h = 64; }
        else if (c->k.rt == KH1_RT_CLUT) { rt_img = &clutimg[0][0]; rt_w = rt_h = 16; }
        else { rt_img = &img[0][0]; rt_w = IW; rt_h = IH; }
        x_tw = 1u << (c->d.tex0_lo >> 26 & 15);
        x_th = 1u << ((c->d.tex0_lo >> 30 | c->d.tex0_hi << 2) & 15);
        x_psm = c->d.tex0_lo >> 20 & 63;
        x_img = c->samples ? offimg : 0;
        x_tex = !c->samples && c->tslot >= 0 ? tc->slot[c->tslot].tex : 0;
        if (!x_img && !x_tex) continue;
        fetch = fetch_tex;
        v = kh1_cmd_verts(r, c);
        for (j = 0; j + 2 < c->nv; j += 3)
            tri(&v[j], &v[j + 1], &v[j + 2], c->k.sx0, c->k.sy0, c->k.sx1, c->k.sy1, 1, &c->d.blend, 0, 0);
    }
    fetch = texel;
    rt_img = &img[0][0];
    rt_w = IW;
    rt_h = IH;
}

/* ---- session 128: the frame's GXM calls replayed (host/port/gxmrec.c) ---- */
static KH1GxmRec gx;
static u32 gx_scrambled, gx_draws;
static int gx_no_clear;     /* session 129's deliberate break: DATE's stencil clears skipped */
static u32 gx_clears, gx_setups;

static void scramble(u32 *p, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) p[i] = 0xA5A5A5A5u ^ i * 0x9E3779B1u;
    gx_scrambled++;
}

static void target_image(u32 rt, u32 **pix, s32 *w, s32 *h) {
    if (rt == KH1_RT_OFFSCREEN) { *pix = &offimg[0][0]; *w = *h = 64; }
    else if (rt == KH1_RT_CLUT) { *pix = &clutimg[0][0]; *w = *h = 16; }
    else { *pix = &img[0][0]; *w = IW; *h = IH; }
}

static void replay_gxm(const KH1CmdRec *r) {
    const KH1TexCache *tc = kh1_pipes_texcache();
    const KH1PalCache *pc = kh1_pipes_palcache();
    const KH1GpuVert *vb = (const KH1GpuVert *)(r->vring.base + r->vring.cur * r->vring.slot);
    const u8 *ub = r->uring.base + r->uring.cur * r->uring.slot;
    const KH1PipeKey *pk = 0;
    const f32 *u = 0;
    u8 tgt_rt[KH1_CMD_TARGETS];
    s32 readback = -1, sx0 = 0, sy0 = 0, sx1 = 0, sy1 = 0, w, h;
    u32 i, j, e, *pix;
    if (do_replay == 2) { /* the transfer frame's checks read the commands */
        nxc = r->ncmd < 64 ? r->ncmd : 64;
        nxp = r->npass < 16 ? r->npass : 16;
        memcpy(xc, r->cmd, nxc * sizeof *xc);
        memcpy(xp, r->pass, nxp * sizeof *xp);
    }
    memset(tgt_rt, KH1_RT_OTHER, sizeof tgt_rt);
    kh1_gxm_frame(&gx, r);
    x_tex = x_pal = 0;
    x_img = 0;
    for (i = 0; i < gx.n; i++) {
        const KH1GxmCall *c = &gx.call[i];
        switch (c->op) {
        case KH1_GXM_BEGIN_SCENE:
            if (c->tgt < KH1_CMD_TARGETS) tgt_rt[c->tgt] = c->rt;
            target_image(c->rt, &rt_img, &rt_w, &rt_h);
            if (c->load == KH1_LOAD_DONT_CARE && c->cleared) scramble(rt_img, (u32)(rt_w * rt_h));
            if (rt_img == &img[0][0]) memset(stn, 1, sizeof stn); /* the depth-stencil's garbage: every pixel marked */
            pk = 0;
            break;
        case KH1_GXM_END_SCENE:
            if (c->store == KH1_STORE_DISCARD) { target_image(c->rt, &pix, &w, &h); scramble(pix, (u32)(w * h)); }
            break;
        case KH1_GXM_TARGET_UPLOAD: { /* the CPU's texels (GS memory at the upload's BITBLTBUF) */
            const KH1CmdXfer *x = &r->cmd[c->cmd].x;
            if (!c->tgt || c->tgt > KH1_CMD_TARGETS) break;
            target_image(tgt_rt[c->tgt - 1], &pix, &w, &h);
            for (j = 0; j < c->h; j++)
                for (e = 0; e < c->w; e++) {
                    u32 g = kh1_gsmem_read_pixel(KH1_PSMCT32, x->bb_hi & 0x3FFF, x->bb_hi >> 16 & 63, c->dx + e, c->dy + j);
                    if ((s32)(c->dx + e) < w && (s32)(c->dy + j) < h)
                        pix[(c->dy + j) * w + c->dx + e] = (g & 0xFFFFFF) | kh1_blend_store_alpha(g >> 24) << 24;
                }
            break;
        }
        case KH1_GXM_PAL_READBACK: /* the CLUT pass's pixels as a palette: entries 8-15 / 16-23 of each 32 swapped */
            for (e = 0; e < 256; e++) {
                u32 p = (e & 0xE7) | (e & 8) << 1 | (e & 0x10) >> 1, g = clutimg[p >> 4][p & 15];
                xpal[e] = (g & 0xFFFFFF) | kh1_blend_load_alpha(g >> 24) << 24;
            }
            readback = c->slot;
            break;
        case KH1_GXM_SET_PROGRAMS:
            pk = c->pipe < gx.npipe ? &gx.pipe[c->pipe] : 0;
            break;
        case KH1_GXM_SET_TEXTURE:
            x_tw = 1u << (c->tex0_lo >> 26 & 15);
            x_th = 1u << ((c->tex0_lo >> 30 | c->tex0_hi << 2) & 15);
            x_psm = c->tex0_lo >> 20 & 63;
            x_img = c->src ? offimg : 0;
            x_tex = !c->src && c->slot >= 0 ? tc->slot[c->slot].tex : 0;
            x_pal = c->pslot < 0 ? 0 : c->pslot == readback ? xpal : pc->slot[c->pslot].col;
            break;
        case KH1_GXM_SET_REGION:
            sx0 = c->sx0; sy0 = c->sy0; sx1 = c->sx1; sy1 = c->sy1;
            break;
        case KH1_GXM_SET_UNIFORMS:
            u = (const f32 *)(ub + c->uoff);
            break;
        case KH1_GXM_DRAW: { /* the pipeline's blend and the shader's pre-scale, FIX from the uniforms */
            KH1BlendState st;
            const KH1GpuVert *v = vb + c->v0;
            if (!pk || !u || c->cls != KH1_PA_TRIANGLES) break;
            if (c->stencil == 3) gx_clears++;
            if (c->stencil == 2) gx_setups++;
            if (c->stencil == 3 && gx_no_clear) break;
            if (pk->shader.tex && !x_img && !x_tex) break;
            memset(&st, 0, sizeof st);
            st.enable = pk->blend;
            st.eq = pk->eq;
            st.fs = pk->fs;
            st.fd = pk->fd;
            st.pre_a = (s8)(pk->shader.pre_a - 2);
            st.pre_d = (s8)(pk->shader.pre_d - 2);
            st.pre_floor = pk->shader.pre_floor;
            st.csel = pk->shader.csel;
            st.fix = (u8)u[1];
            st.mask = pk->mask;
            st.kind = KH1_BLEND_EXACT;
            fetch = pk->shader.tex ? fetch_tex : texel;
            tri_stencil = rt_img == &img[0][0] ? c->stencil : 0;
            tri_datm = pk->shader.datm;
            for (j = 0; j + 2 < c->nv; j += 3) tri(&v[j], &v[j + 1], &v[j + 2], sx0, sy0, sx1, sy1, pk->shader.tex != 0, &st, 0, 0);
            tri_stencil = 0;
            gx_draws++;
            break;
        }
        }
    }
    fetch = texel;
    rt_img = &img[0][0];
    rt_w = IW;
    rt_h = IH;
}

static void columns(int partial);
static void transfers(void);
static void gxm(void) {
    u32 i;
    gx_scrambled = gx_draws = 0;
    kh1_gxm_clear(&gx);
    use_gxm = 1;
    columns(0);
    columns(1);
    transfers();
    use_gxm = 0;
    for (i = 0; i < gx.n; i++) printf("cmdbuf_test: gxm: %2u %s\n", i + 1, kh1_gxm_call_str(&gx.call[i]));
    printf("cmdbuf_test: gxm: %u frames, %u calls, %u scenes, %u draws, %u program sets, %u scenes scrambled\n",
           gx.total.frames, gx.total.calls, gx.total.scenes, gx.total.draws, gx.total.programs, gx_scrambled);
    CHECK("gxm: columns, partial and transfers replayed from the GXM calls alone (same checks, same pixels)",
          gx.total.frames >= 3 && gx_draws && !gx.total.lost);
    CHECK("gxm: the transfer frame's calls: a target upload and a palette read-back, each after its scene ended",
          gx.frame.target_uploads == 1 && gx.frame.pal_readbacks == 1);
}

/* ---- session 129: DATE's set-up from the GXM calls ---- */
static void flat_sprite(u32 rgba, s32 x0, s32 y0, s32 x1, s32 y1) {
    W(0x00, 0x6, 0);                 /* SPRITE, flat, no blend */
    W(0x01, rgba, 0x3F800000);       /* RGBAQ */
    W(0x05, x16(x0) | x16(y0) << 16, 0);
    W(0x05, x16(x1) | x16(y1) << 16, 0);
}

/* the GS's DATE in its order: the copy's pixels (gsmem.c's sprite), then each flat sprite writes where Ad's bit 7
 * is DATM (1) at the moment it draws (gsmem.c's model draws no flat sprite, so the test applies the rule) */
static const struct { u32 rgba; s32 x0, y0, x1, y1; } date_spr[2] = {
    { 0x00309020, 10, 4, 70, 20 },   /* alpha 0: the second sprite fails where this one drew */
    { 0x807010C0, 40, 10, 110, 30 }, /* alpha 0x80, overlapping it */
};
static u32 gs_date[IH][IW];

/* img against the GS's pixels: RGB, and alpha bit 7 (what DATE reads) against "stored 1.0" */
static u32 date_diff(void) {
    u32 x, y, bad = 0, i;
    for (y = 0; y < IH; y++)
        for (x = 0; x < IW; x++) gs_date[y][x] = kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1A00, 8, x, y);
    for (i = 0; i < 2; i++)
        for (y = (u32)date_spr[i].y0; y < (u32)date_spr[i].y1 && y < IH; y++)
            for (x = (u32)date_spr[i].x0; x < (u32)date_spr[i].x1 && x < IW; x++)
                if (gs_date[y][x] >> 31 == 1) gs_date[y][x] = date_spr[i].rgba;
    for (y = 0; y < IH; y++)
        for (x = 0; x < IW; x++) {
            u32 g = gs_date[y][x], c = img[y][x];
            if ((g & 0xFFFFFF) != (c & 0xFFFFFF) || (g >> 31) != ((c >> 24) == 255)) {
                if (bad < 6 && !gx_no_clear) printf("cmdbuf_test: date: pixel (%u, %u) GS %08x, GXM %08x\n", x, y, g, c);
                bad++;
            }
        }
    return bad;
}

static u32 date_frame(int no_clear) {
    u32 x, y;
    kh1_gsmem_reset();
    for (y = 0; y < 64; y++) /* the stripes: alpha 0x80 (bit 7) or 0x30 */
        for (x = 0; x < 64; x++)
            kh1_gsmem_write_pixel(KH1_PSMCT32, TBP, 1, x, y, ((x / 3 + y / 2) & 1 ? 0x80u : 0x30u) << 24 | (x * 4) << 8 | y * 8);
    /* (the GS's flat sprites are applied by date_diff: gsmem.c draws the copy only) */
    memset(img, 0, sizeof img);
    env();
    W(0x00, 0x116, 0); /* the striped copy over the whole target */
    copy(0);
    W(0x47, 1 << 14 | 1 << 15, 0); /* TEST_1: DATE, DATM 1 */
    for (x = 0; x < 2; x++) flat_sprite(date_spr[x].rgba, date_spr[x].x0, date_spr[x].y0, date_spr[x].x1, date_spr[x].y1);
    W(0x47, 0, 0);
    gx_no_clear = no_clear;
    use_gxm = do_replay = 1;
    kh1_pipes_frame();
    use_gxm = do_replay = 0;
    x = date_diff();
    gx_no_clear = 0;
    return x;
}

static void date(void) {
    u32 bad, broken, s0, ncmd;
    gx_clears = gx_setups = 0;
    bad = date_frame(0);
    ncmd = snap_ncmd;
    s0 = gx_clears;
    printf("cmdbuf_test: date: %u commands, %u stencil clears, %u set-ups, %u pixels differ\n", ncmd, gx_clears,
           gx_setups, bad);
    CHECK("date: each DATE sprite a command of its own, its clear and set-up before its draw", ncmd == 3 &&
          gx_clears == 2 && gx_setups == 2);
    CHECK("date: the GXM calls with the stencil give gsmem.c's DATE pixels (RGB and alpha bit 7)", bad == 0);
    broken = date_frame(1);
    CHECK("date: without the clear the replay differs (the stencil's garbage and the first sprite's marks)",
          broken != 0 && gx_clears == s0 + 2);
}

/* an upload of w x h pixels in psm at block bp, width bw, to (x, y): n words of IMAGE data */
static void xupload(u32 bp, u32 bw, u32 psm, u32 x, u32 y, u32 w, u32 h, const u32 *data, u32 n) {
    W(0x50, 0, bp | bw << 16 | psm << 24);
    W(0x51, 0, x | y << 16);
    W(0x52, w, h);
    W(0x53, 0, 0);
    kh1_gsmem_image(data, n);
}

static void xsprite(s32 x0, s32 x1) {
    W(0x00, 0x116, 0); /* SPRITE | TME | FST */
    W(0x03, 0, 0);
    W(0x05, x16(x0) | x16(0) << 16, 0);
    W(0x03, 16 * 16 | (16u * 16) << 16, 0);
    W(0x05, x16(x1) | x16(16) << 16, 0);
}

#define TEX16(bp, bw, psm) ((bp) | (bw) << 14 | (psm) << 20 | 4u << 26 | 0u << 30)
#define TEX16_HI (1 | 1 << 2 | 1 << 3) /* TH 4, TCC, DECAL */

static void transfers(void) {
    static u32 a[256], b[256], cc[64], pal_t[256], idx[64];
    u32 i, x, y, bad = 0, ntex = 0, ndraw = 0, ups = 0;
    s32 d1 = -1, d2 = -1, d8 = -1, clut = -1, off_pass = -1, clut_pass = -1;
    u32 salt = use_gxm ? 0x030201 : 0; /* the gxm run's texels differ: the caches decode and fill again */
    for (i = 0; i < 256; i++) {
        a[i] = ((0x20 + i % 0x61) << 24 | (i * 3) << 16 | (255 - i) << 8 | (i * 7 & 0xFF)) ^ salt;
        b[i] = ((0x80 - i % 0x50) << 24 | (i * 5 & 0xFF) << 16 | (i * 11 & 0xFF) << 8 | (200 - i % 200)) ^ salt;
        pal_t[i] = ((i % 0x81) << 24 | (i * 13 & 0xFF) << 16 | (i ^ 0x5A) << 8 | (i * 29 & 0xFF)) ^ salt;
    }
    for (i = 0; i < 64; i++) cc[i] = (0x7F000000u | (i * 4) << 16 | 0x40 << 8 | (i * 3)) ^ salt;
    for (i = 0; i < 64; i++) /* 256 indices, bytes */
        idx[i] = ((i * 4 + 0) * 37 & 0xFF) | ((i * 4 + 1) * 37 & 0xFF) << 8 | ((i * 4 + 2) * 37 & 0xFF) << 16 |
                 (u32)((i * 4 + 3) * 37 & 0xFF) << 24;
    kh1_gsmem_reset();
    memset(img, 0, sizeof img);
    memset(offimg, 0, sizeof offimg);
    memset(clutimg, 0, sizeof clutimg);
    env();
    W(0x08, 5, 0); /* CLAMP_1: CLAMP */
    xupload(0x2800, 1, KH1_PSMCT32, 0, 0, 16, 16, a, 256);       /* texture A */
    W(0x06, TEX16(0x2800, 1, KH1_PSMCT32), TEX16_HI);
    xsprite(0, 16);                                                /* the 3D target from A */
    xupload(0x2800, 1, KH1_PSMCT32, 0, 0, 16, 16, b, 256);       /* the same place: B */
    xsprite(16, 32);                                               /* from B */
    W(0x4C, 0x1D0 | 4 << 16, 0);                                   /* the off-screen buffer 0x3A00 */
    W(0x40, 255u << 16, 255u << 16);
    xsprite(0, 16);                                                /* B into it */
    W(0x4C, 0xD0 | 8 << 16, 0);
    W(0x40, 511u << 16, 383u << 16);
    W(0x06, TEX16(0x3A00, 4, KH1_PSMCT32), TEX16_HI);
    xsprite(32, 48);                                               /* the 3D target samples it */
    xupload(0x3A00, 4, KH1_PSMCT32, 4, 4, 8, 8, cc, 64);         /* an upload into the off-screen buffer */
    xsprite(48, 64);                                               /* sampled again */
    xupload(0x2900, 1, KH1_PSMCT32, 0, 0, 16, 16, pal_t, 256);   /* the CLUT pass's source */
    W(0x4C, 0x1F0 | 1 << 16, 0);                                   /* the CLUT pass 0x3E00 */
    W(0x40, 15u << 16, 15u << 16);
    W(0x06, TEX16(0x2900, 1, KH1_PSMCT32), TEX16_HI);
    xsprite(0, 16);
    xupload(0x2A00, 2, KH1_PSMT8, 0, 0, 16, 16, idx, 64);        /* an 8-bit texture */
    W(0x4C, 0xD0 | 8 << 16, 0);
    W(0x40, 511u << 16, 383u << 16);
    W(0x06, TEX16(0x2A00, 2, KH1_PSMT8), TEX16_HI | 0x3E00u << 5 | 1u << 29); /* CBP 0x3E00, CT32, CLD 1: a load */
    xsprite(64, 80);
    do_replay = 2;
    kh1_pipes_frame();
    do_replay = 0;
    for (i = 0; i < nxc; i++) {
        const KH1Cmd *c = &xc[i];
        printf("cmdbuf_test: transfers: %2u %s\n", i + 1, kh1_cmd_str(kh1_pipes_recorder(), c));
        if (c->kind == KH1_CMD_TEXTURE) ntex++;
        if (c->kind == KH1_CMD_UPLOAD) ups++;
        if (c->kind == KH1_CMD_CLUT) clut = (s32)i;
        if (c->kind != KH1_CMD_DRAW) continue;
        ndraw++;
        if (c->k.rt == KH1_RT_MAIN && d1 < 0) d1 = (s32)i;
        else if (c->k.rt == KH1_RT_MAIN && d2 < 0) d2 = (s32)i;
        if (c->k.rt == KH1_RT_MAIN) d8 = (s32)i;
        if (c->k.rt == KH1_RT_OFFSCREEN) off_pass = (s32)c->pass;
        if (c->k.rt == KH1_RT_CLUT) clut_pass = (s32)c->pass;
    }
    for (i = 0; i < nxp; i++) printf("cmdbuf_test: transfers: pass %u: %s\n", i + 1, kh1_cmd_pass_str(&xp[i]));
    CHECK("transfers: 7 draws, 5 uploads, one CLUT load", ndraw == 7 && ups == 5 && clut >= 0);
    CHECK("transfers: A and B are two texture entries, each decoded by a TEXTURE command before its draw",
          d1 >= 1 && d2 > d1 && xc[d1].tslot >= 0 && xc[d2].tslot >= 0 && xc[d1].tslot != xc[d2].tslot &&
          xc[d1 - 1].kind == KH1_CMD_TEXTURE && xc[d1 - 1].x.slot == xc[d1].tslot && xc[d2 - 1].kind == KH1_CMD_TEXTURE &&
          xc[d2 - 1].x.slot == xc[d2].tslot);
    CHECK("transfers: the off-screen buffer is stored (sampled, then written by an upload)", off_pass >= 0 &&
          xp[off_pass].store == KH1_STORE_STORE && xp[off_pass].why == (KH1_WHY_SAMPLED | KH1_WHY_REDRAWN));
    CHECK("transfers: the CLUT load reads the CLUT pass back (stored for it), filling a palette slot",
          clut >= 0 && xc[clut].x.src && xc[clut].x.fill && xc[clut].x.slot >= 0 && clut_pass >= 0 &&
          xp[clut_pass].store == KH1_STORE_STORE && xp[clut_pass].why == KH1_WHY_SAMPLED);
    CHECK("transfers: the indexed draw binds the loaded palette", d8 > clut && xc[d8].pslot == xc[clut].x.slot);
    CHECK("transfers: the palette read back from the CLUT pass is the palette cache's (gsmem.c's CLUT)", xpal_ok &&
          !xpal_bad);
    /* 2026-10-31: the upload into the off-screen buffer no longer splits the 3D target's scene (upload_join) */
    CHECK("transfers: counted (5 uploads, 1 CLUT load and fill, 1 target read, 1 target write, inside the scene)",
          snap_hdr.frame.uploads == 5 && snap_hdr.frame.cluts == 1 && snap_hdr.frame.pal_fills == 1 &&
          snap_hdr.frame.tgt_reads == 1 && snap_hdr.frame.tgt_writes == 1 && snap_hdr.frame.splits == 0 &&
          snap_hdr.frame.xfer_joins == 1 &&
          snap_hdr.frame.textures == ntex);
    for (y = 0; y < XH; y++)
        for (x = 0; x < 80; x++) {
            u32 g = kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1A00, 8, x, y), c = img[y][x];
            g = (g & 0xFFFFFF) | kh1_blend_store_alpha(g >> 24) << 24;
            if (g != c) {
                if (!bad) printf("cmdbuf_test: transfers: pixel (%u, %u) GS %08x, commands %08x\n", x, y, g, c);
                bad++;
            }
        }
    CHECK("transfers: the list replayed gives gsmem.c's pixels (A, B, the target before and after the upload, the "
          "CLUT pass's palette)", !bad);
}

/* 2026-10-31 (cmdbuf.h): an upload into another target between draws on the 3D target leaves one pass (the Dive's
 * particle textures in the slot capture's pages); a draw that then samples that target reads GS memory's texels
 * (the upload marked its pages the CPU's, cpu_pages), so it stays in the pass too */
static void upload_join(void) {
    static u32 a[256], cc[64];
    u32 i, x, y, bad = 0, main_passes = 0, ndraw = 0;
    for (i = 0; i < 256; i++) a[i] = 0x80000000u | (i * 3) << 16 | (255 - i) << 8 | (i * 7 & 0xFF);
    for (i = 0; i < 64; i++) cc[i] = 0x7F000000u | (i * 4) << 16 | 0x40 << 8 | (i * 3);
    kh1_gsmem_reset();
    memset(img, 0, sizeof img);
    memset(offimg, 0, sizeof offimg);
    env();
    W(0x08, 5, 0);
    xupload(0x2800, 1, KH1_PSMCT32, 0, 0, 16, 16, a, 256);       /* texture A */
    W(0x06, TEX16(0x2800, 1, KH1_PSMCT32), TEX16_HI);
    W(0x4C, 0x1D0 | 4 << 16, 0);                                   /* the off-screen buffer: a target this frame */
    W(0x40, 255u << 16, 255u << 16);
    xsprite(0, 16);
    W(0x4C, 0xD0 | 8 << 16, 0);                                    /* the 3D target */
    W(0x40, 511u << 16, 383u << 16);
    xsprite(0, 16);
    xupload(0x3A00, 4, KH1_PSMCT32, 4, 4, 8, 8, cc, 64);         /* into the off-screen buffer */
    xsprite(16, 32);                                               /* the same scene */
    xupload(0x3A00, 4, KH1_PSMCT32, 0, 0, 8, 8, cc, 64);
    W(0x06, TEX16(0x3A00, 4, KH1_PSMCT32), TEX16_HI);
    xsprite(32, 48);                                               /* samples what the upload wrote (GS memory's) */
    do_replay = 2;
    kh1_pipes_frame();
    do_replay = 0;
    for (i = 0; i < nxp; i++) {
        printf("cmdbuf_test: upload join: pass %u: %s\n", i + 1, kh1_cmd_pass_str(&xp[i]));
        if (xp[i].rt == KH1_RT_MAIN) main_passes++;
    }
    for (i = 0; i < nxc; i++)
        if (xc[i].kind == KH1_CMD_DRAW && xc[i].k.rt == KH1_RT_MAIN) ndraw++;
    CHECK("upload join: 3 draws on the 3D target in one pass, the last reading the uploaded texels from GS memory",
          ndraw == 3 && main_passes == 1 && nxp == 2 && xp[1].ndraw == 3 && !xc[nxc - 1].samples);
    CHECK("upload join: counted (two uploads inside the scene, no split)", snap_hdr.frame.xfer_joins == 2 &&
          snap_hdr.frame.splits == 0);
    for (y = 0; y < XH; y++)
        for (x = 0; x < 48; x++) {
            u32 g = kh1_gsmem_read_pixel(KH1_PSMCT32, 0x1A00, 8, x, y), c = img[y][x];
            g = (g & 0xFFFFFF) | kh1_blend_store_alpha(g >> 24) << 24;
            if (g != c) {
                if (!bad) printf("cmdbuf_test: upload join: pixel (%u, %u) GS %08x, commands %08x\n", x, y, g, c);
                bad++;
            }
        }
    CHECK("upload join: the list replayed gives gsmem.c's pixels", !bad);
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
    transfers();
    upload_join();
    gxm();
    date();
    printf("cmdbuf_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
