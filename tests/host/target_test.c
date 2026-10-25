/* Render targets, the viewport and the scissor a port draws with (host/port/target.c, renderer-spec 4.13
 * "Session 123", vita-port-plan 5.1bk), tested on the game's FRAME / ZBUF / SCISSOR / XYOFFSET values (no
 * game data): tests/selftest.sh builds it with gcc -m32 when that works.
 *
 *   targets   the game's render-to-texture sends (the 3D pass, the frame copy into the display, the Z
 *             area as colour, the menu's and the depth blur's captures into the slot, the shadow windows,
 *             a CLUT pass, the movie frame) drawn into host/null/gsmem.c's model: every render target
 *             kh1_gsmem_targets lists is a port target (none OTHER) or one of the two depth buffers, each
 *             kept apart from the others, and each pass's target covers its SCISSOR.
 *   depth     the depth buffer each pass binds (the main one with the 3D target, the shadow's with the
 *             off-screen buffer) and the Z writes the port drops (the depth blur's capture).
 *   viewport  at the PS2's 4:3 every pass maps window pixels 1:1; under 960 x 544's wide view the 3D
 *             target's and display's left edge is the view's, a capture's half of it, at the canvas's
 *             scale; NDC corners at -1 / 1.
 *   scissor   the full canvas and its 32-pixel columns as the view's, any other rectangle moved by the
 *             margin, clipped to the target.
 *   alias     the PS2's shared blocks named both ways, the rest apart. */
#include "common.h"
#include "../../host/null/gsmem.h"
#include "platform/target.h"

int printf(const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("target_test: %s\n", name); fails++; } } while (0)

static int near(f32 a, f32 b) { return a - b < 0.01f && b - a < 0.01f; }
/* within a sixteenth's rounding (the margin is whole sixteenths, halved for a capture) */
static int near16(f32 a, f32 b) { return a - b < 0.07f && b - a < 0.07f; }
static u32 sc_lo(u32 x0, u32 x1) { return x0 | x1 << 16; }
static u32 sc_hi(u32 y0, u32 y1) { return y0 | y1 << 16; }

typedef struct {
    const char *name;
    u32 frame_lo, frame_hi, zbuf_lo, zbuf_hi, test_lo, slo, shi, ofx, ofy;
    u32 id, depth, zdrop;
} Send;

/* the game's values (renderer-spec 3.1 / 3.2 / 3.4, fscheck.py's sends) */
static const Send sends[] = {
    { "the 3D pass", 0x800D0, 0, 0x31000070, 0, 0x5000D, 511 << 16, 383 << 16, 0x7000, 0x7400,
      KH1_RT_MAIN, KH1_DS_MAIN, 0 },
    { "the frame copy into the display", 0x01080000, 0, 0x31000070, 1, 0x30000, 511 << 16, 447 << 16, 0x7000, 0x7400,
      KH1_RT_DISPLAY, KH1_DS_NONE, 0 },
    { "the Z area as colour (the sway's copy)", 0x01080070, 0, 0x31000000, 1, 0x30000, 511 << 16, 383 << 16, 0x7000,
      0x7400, KH1_RT_ZCOLOR, KH1_DS_NONE, 0 },
    { "the menu capture", 0x401B0, 0, 0x31000070, 1, 0x30000, 255 << 16, 191 << 16, 0x7000, 0x7400,
      KH1_RT_SLOT, KH1_DS_NONE, 0 },
    { "the depth blur's capture", 0x801B0, 0, 0x31000070, 0, 0x30000, 255 << 16, 191 << 16, 0x7000, 0x7400,
      KH1_RT_SLOT, KH1_DS_NONE, 1 },
    { "a shadow window", 0x401D0, 1, 0x3A0001C0, 0, 0x5000D, 30 | 225 << 16, 30 | 225 << 16, 0x7800, 0x7800,
      KH1_RT_OFFSCREEN, KH1_DS_SHADOW, 0 },
    { "a CLUT pass", 0x101F0, 0xFF000000u, 0x31000070, 1, 0x30000, 15 << 16, 15 << 16, 0x7000, 0x7400,
      KH1_RT_CLUT, KH1_DS_NONE, 0 },
    { "the movie frame", 0x010A008C, 0, 0x31000070, 1, 0x30000, 639 << 16, 447 << 16, 0x7000, 0x7400,
      KH1_RT_MOVIE, KH1_DS_NONE, 0 },
};
#define NSENDS (int)(sizeof sends / sizeof sends[0])

static void pass_of(const Send *s, const KH1Canvas *c, f32 scale, KH1RenderPass *p) {
    kh1_target_of(s->frame_lo, s->frame_hi, s->zbuf_lo, s->zbuf_hi, s->test_lo, s->slo, s->shi, s->ofx, s->ofy, c,
                  scale, p);
}

static void targets(void) {
    static KH1GsTarget t[32];
    KH1Canvas c;
    KH1RenderPass p;
    int i, j, n, ok = 1, cover = 1, apart = 1, ids = 1;
    u32 key[32];
    kh1_canvas_fit(&c, 512, 384);
    kh1_gsmem_reset();
    for (i = 0; i < NSENDS; i++)
        kh1_gsmem_draw(sends[i].frame_lo, sends[i].frame_hi, sends[i].zbuf_lo, sends[i].zbuf_hi, sends[i].slo,
                       sends[i].shi, sends[i].test_lo);
    n = kh1_gsmem_targets(t, 32);
    for (i = 0; i < n; i++) {
        if (t[i].psm >= 0x30) /* a depth buffer */
            key[i] = KH1_RT_COUNT + (t[i].bp == 0xE00 && t[i].psm == 0x31 ? KH1_DS_MAIN :
                                     t[i].bp == 0x3800 && t[i].psm == 0x3A ? KH1_DS_SHADOW : 9);
        else
            key[i] = kh1_target_id(t[i].bp / 32, t[i].bw, t[i].psm);
        if (key[i] == KH1_RT_OTHER || key[i] == KH1_RT_COUNT + 9) ok = 0;
    }
    /* two GS targets on one port texture only when they are the same buffer (the slot's FBW 4 / 8) */
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (key[i] == key[j] && !(key[i] == KH1_RT_SLOT && t[i].bp == t[j].bp)) apart = 0;
    for (i = 0; i < NSENDS; i++) {
        pass_of(&sends[i], &c, 1.0f, &p);
        if (p.id != sends[i].id) ids = 0;
        if (p.sx0 != (s32)(sends[i].slo & 0x7FF) || p.sx1 != (s32)(sends[i].slo >> 16 & 0x7FF) + 1 ||
            p.sy0 != (s32)(sends[i].shi & 0x7FF) || p.sy1 != (s32)(sends[i].shi >> 16 & 0x7FF) + 1 ||
            p.sx1 > (s32)p.w || p.sy1 > (s32)p.h)
            cover = 0;
    }
    CHECK("the model saw a target for every send (8 colour, 2 depth)", n == 10);
    CHECK("every GS render target is a port target or one of the two depth buffers", ok);
    CHECK("... each its own (the slot's two captures one buffer)", apart);
    CHECK("each send's port target", ids);
    CHECK("at 4:3 each pass's scissor is SCISSOR's and inside its target", cover);
}

static void depth(void) {
    KH1Canvas c;
    KH1RenderPass p;
    int i, ok = 1;
    kh1_canvas_fit(&c, 960, 544);
    for (i = 0; i < NSENDS; i++) {
        pass_of(&sends[i], &c, c.s, &p);
        if (p.depth != sends[i].depth || p.zdrop != sends[i].zdrop) ok = 0;
    }
    CHECK("the depth buffer each pass binds, the Z writes dropped (the depth blur's capture)", ok);
    /* the 3D target with ZTE 0 or ZTST ALWAYS and ZMSK 1: no depth buffer needed */
    kh1_target_of(0x800D0, 0, 0x31000070, 1, 0x30000, 511 << 16, 383 << 16, 0x7000, 0x7400, &c, 1.0f, &p);
    CHECK("the 3D target under ZTST ALWAYS with ZMSK 1 binds no depth", p.depth == KH1_DS_NONE && !p.zdrop);
    kh1_target_of(0x800D0, 0, 0x31000070, 0, 0x30000, 511 << 16, 383 << 16, 0x7000, 0x7400, &c, 1.0f, &p);
    CHECK("... ALWAYS with a write binds it", p.depth == KH1_DS_MAIN);
}

static void viewport(void) {
    KH1Canvas c;
    KH1RenderPass p;
    f32 x, y, nx, ny;
    int i, ok = 1;
    kh1_canvas_fit(&c, 512, 384);
    for (i = 0; i < NSENDS; i++) {
        pass_of(&sends[i], &c, 1.0f, &p);
        kh1_target_map(&p, sends[i].ofx + 16 * 37, sends[i].ofy + 16 * 11 + 8, &x, &y);
        if (!near(x, 37.0f) || !near(y, 11.5f)) ok = 0;
    }
    CHECK("at 4:3 every pass maps window pixels 1:1", ok);
    pass_of(&sends[0], &c, 1.0f, &p);
    CHECK("... the 3D target is 512 x 384", p.w == 512 && p.h == 384);
    kh1_canvas_fit(&c, 960, 544);
    pass_of(&sends[0], &c, c.s, &p);
    CHECK("960 x 544: the 3D target is the screen's size", p.w == 960 && p.h == 544);
    kh1_target_map(&p, 0x7000 + c.vx0, 0x7400, &x, &y);
    CHECK("... the view's left edge is pixel 0", near(x, 0.0f) && near(y, 0.0f));
    kh1_target_map(&p, 0x7000 + c.vx0 + c.vw, 0x7400 + 384 * 16, &x, &y);
    CHECK("... its right edge the target's (within a pixel's fraction)", x > 958.9f && x <= 960.0f && near(y, 544.0f));
    kh1_target_map(&p, 0x7000, 0x7400, &x, &y);
    CHECK("... canvas 0 at the pillarbox's edge", near16(x, c.ox));
    kh1_target_ndc(&p, 0x7000 + c.vx0, 0x7400, &nx, &ny);
    CHECK("... NDC -1 at the top left", near(nx, -1.0f) && near(ny, -1.0f));
    kh1_target_ndc(&p, 0x8000, 0x7400 + 384 * 16, &nx, &ny);
    CHECK("... the canvas's centre at NDC x 0, the bottom at 1", nx > -0.002f && nx < 0.002f && near(ny, 1.0f));
    pass_of(&sends[3], &c, 1.0f, &p);
    kh1_target_map(&p, 0x7000 + c.vx0 / 2, 0x7400, &x, &y);
    CHECK("a capture: half the view wide, its left edge at half the margin", near16(x, 0.0f) &&
          p.w == (u32)((c.vw / 32.0f) + 0.999f) && p.h == 192);
    pass_of(&sends[5], &c, 1.0f, &p);
    CHECK("the off-screen buffer keeps the PS2's 256 x 256", p.w == 256 && p.h == 256 && p.ox == 0.0f);
    pass_of(&sends[7], &c, 1.0f, &p);
    CHECK("the movie frame keeps 640 x 448", p.w == 640 && p.h == 448);
}

static void scissor(void) {
    KH1Canvas c;
    KH1RenderPass p;
    kh1_canvas_fit(&c, 960, 544);
    kh1_target_of(0x800D0, 0, 0x31000070, 0, 0x5000D, sc_lo(0, 511), sc_hi(0, 383), 0x7000, 0x7400, &c, 1.0f, &p);
    CHECK("the full canvas is the whole view", p.sx0 == 0 && p.sx1 == (s32)p.w && p.sy0 == 0 && p.sy1 == 384);
    kh1_target_of(0x800D0, 0, 0x31000070, 0, 0x5000D, sc_lo(0, 31), sc_hi(0, 383), 0x7000, 0x7400, &c, 1.0f, &p);
    CHECK("column 0 is the view's first sixteenth", p.sx0 == 0 && p.sx1 == (s32)(c.vw / 256.0f + 0.5f));
    kh1_target_of(0x800D0, 0, 0x31000070, 0, 0x5000D, sc_lo(480, 511), sc_hi(0, 383), 0x7000, 0x7400, &c, 1.0f, &p);
    CHECK("column 15 ends at the view's right edge", p.sx1 == (s32)p.w || p.sx1 == (s32)p.w - 1);
    kh1_target_of(0x800D0, 0, 0x31000070, 0, 0x5000D, sc_lo(100, 299), sc_hi(50, 149), 0x7000, 0x7400, &c, 1.0f, &p);
    CHECK("a window's scissor moves by the margin", p.sx0 == 100 + (s32)(p.ox + 0.5f) && p.sx1 == 300 + (s32)(p.ox + 0.5f) &&
          p.sy0 == 50 && p.sy1 == 150);
    kh1_target_of(0x800D0, 0, 0x31000070, 0, 0x5000D, sc_lo(0, 2047), sc_hi(0, 2047), 0x7000, 0x7400, &c, 1.0f, &p);
    CHECK("a scissor past the target is clipped to it", p.sx1 == (s32)p.w && p.sy1 == (s32)p.h);
    kh1_target_of(0x401B0, 0, 0x31000070, 1, 0x30000, sc_lo(0, 511), sc_hi(0, 383), 0x7000, 0x7400, &c, 1.0f, &p);
    CHECK("a capture's full scissor is half the view", p.sx0 == 0 && p.sx1 == (s32)p.w);
}

static void alias(void) {
    u32 a, b, n = 0, sym = 1;
    for (a = 0; a < KH1_RT_COUNT + 3; a++)
        for (b = 0; b < KH1_RT_COUNT + 3; b++) {
            if (kh1_target_alias(a, b) != kh1_target_alias(b, a)) sym = 0;
            if (a < b && kh1_target_alias(a, b)) n++;
        }
    CHECK("the PS2's shared blocks, named both ways: 6 pairs", sym && n == 6);
    CHECK("the Z area as colour shares the main depth's blocks, not the 3D target's",
          kh1_target_alias(KH1_RT_ZCOLOR, KH1_RT_COUNT + KH1_DS_MAIN) && !kh1_target_alias(KH1_RT_ZCOLOR, KH1_RT_MAIN));
}

int main(void) {
    targets();
    depth();
    viewport();
    scissor();
    alias();
    printf("target_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
