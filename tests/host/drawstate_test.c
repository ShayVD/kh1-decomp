/* The whole draw state a port's GPU needs (host/port/drawstate.c, renderer-spec 4.13 "Session 123",
 * vita-port-plan 5.1bk), tested on made-up register values (no game data): tests/selftest.sh builds it
 * with gcc -m32 when that works.
 *
 *   blend     every ALPHA byte, four FIX values, ABE 0 / 1, CT32 / CT24 frames and four FBMSKs: the blend
 *             rebuilt from the pipeline key and the uniforms alone draws what blend.h's state draws
 *             (kh1_blend_gpu over a grid of colours and alphas), so the key drops nothing the blend reads.
 *   tests     every TEST (ATE, ATST, three AREFs, AFAIL, DATE, DATM, ZTE, ZTST) with ZMSK 0 / 1 and two
 *             write masks: the writes rebuilt from the pipelines (discard, mask, depth write, stencil,
 *             the set-up's DATM, the AREF uniform) are kh1_atest_gpu's for every alpha and stored alpha,
 *             and the depth compare is depth.h's.
 *   texture   every PSM, TFX and TCC: the key's format, TEXA flag and texture function are texfmt.h's /
 *             texfunc.h's.
 *   uniforms  states that differ only in AREF, FIX, FOGCOL, TEXA, the region bounds or the texture's
 *             address / CLUT share their pipelines; the uniforms are set only where the shader reads them.
 *   game      the game's forms as single pipelines (renderer B's two passes, the HUD's numbers, opdma's
 *             Z-only write, brightfade's DATE with its set-up), nothing drawn for ZTST NEVER and PRIM 7,
 *             and the pipeline set's counts. */
#include "common.h"
#include "platform/drawstate.h"
#include "platform/primasm.h"
#include "platform/texfmt.h"
#include "platform/texfunc.h"

int printf(const char *, ...);
int memcmp(const void *, const void *, __SIZE_TYPE__);
void *memset(void *, int, __SIZE_TYPE__);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("drawstate_test: %s\n", name); fails++; } } while (0)

static u32 test_word(u32 ate, u32 atst, u32 aref, u32 afail, u32 date, u32 datm, u32 zte, u32 ztst) {
    return ate | atst << 1 | aref << 4 | afail << 12 | date << 14 | datm << 15 | zte << 16 | ztst << 17;
}

/* the drawing environment's registers (renderer-spec 4.7): the 3D target, Z24, GREATER 0 / GEQUAL, 0x44 */
static void env(KH1DrawRegs *r, u32 prim) {
    memset(r, 0, sizeof *r);
    r->prim = prim;
    r->frame_lo = 0x800D0;
    r->zbuf_lo = 0x31000070;
    r->test_lo = 0x5000D;
    r->alpha_lo = 0x44;
    r->tex0_lo = 0xDD313600; /* renderer B's default: PSMT8 128 x 128 at 0x3600, CLUT 0x3700 */
    r->tex0_hi = 0x2006E005;
    r->tex1_lo = 0x60;
    r->clamp_lo = 5;
}

/* the blend a port runs, from the key and the uniforms alone */
static void blend_of_key(const KH1DrawState *d, KH1BlendState *b) {
    const KH1PipeKey *p = &d->pipe[0];
    const KH1ShaderKey *s = &p->shader;
    memset(b, 0, sizeof *b);
    b->enable = p->blend || s->fetch == 1;
    b->kind = s->fetch ? KH1_BLEND_FETCH : KH1_BLEND_EXACT;
    b->eq = p->blend ? p->eq : KH1_BEQ_ADD;
    b->fs = KH1_BF_ONE;
    b->fd = p->blend ? p->fd : KH1_BF_ZERO;
    b->pre_a = (s8)(s->pre_a - 2);
    b->pre_d = (s8)(s->pre_d - 2);
    b->pre_floor = s->pre_floor;
    b->csel = s->fetch == 1 ? (d->u.abcd >> 4 & 3) > 2 ? 2 : d->u.abcd >> 4 & 3 : s->csel;
    b->fix = d->u.fix;
    b->abcd = d->u.abcd;
    b->psm = d->u.psm;
    b->mask = 0xF;
}

static void blend(void) {
    static const u32 fixes[4] = { 0, 0x40, 0x80, 0x90 }, msks[4] = { 0, 0xFF000000u, 0xFFFFFF, 0x0F };
    static const u32 as[5] = { 0, 0x20, 0x7F, 0x80, 0xFF };
    u32 abe, ab, f, psm, m, i, j, k, ok = 1, n = 0, cs, cd;
    KH1DrawRegs r;
    KH1DrawState d;
    KH1BlendState b, piece;
    for (abe = 0; abe < 2; abe++)
        for (ab = 0; ab < 256; ab++)
            for (f = 0; f < 4; f++)
                for (psm = 0; psm < 2; psm++)
                    for (m = 0; m < 4; m++) {
                        env(&r, 6 | abe << 6);
                        r.test_lo = test_word(0, 0, 0, 0, 0, 0, 1, 1);
                        r.alpha_lo = ab;
                        r.alpha_hi = fixes[f];
                        r.frame_lo = 0x800D0 | psm << 24;
                        r.frame_hi = msks[m];
                        kh1_drawstate_of(&r, &d);
                        if (!d.n) continue; /* a mask that writes nothing */
                        blend_of_key(&d, &b);
                        piece = d.blend;
                        piece.mask = 0xF;
                        n++;
                        for (i = 0; i < 5; i++)
                            for (j = 0; j < 8; j++)
                                for (k = 0; k < 8; k++) {
                                    cs = as[i] << 24 | (j * 37) << 16 | (255 - j * 31) << 8 | j * 36;
                                    cd = ((k * 36 + 1) & 0xFF) << 24 | (k * 29) << 16 | (k * 33) << 8 | (255 - k * 35);
                                    if (kh1_blend_gpu(&b, cs, cd) != kh1_blend_gpu(&piece, cs, cd)) ok = 0;
                                }
                    }
    CHECK("the blend rebuilt from the key and uniforms is blend.h's for every ALPHA / FIX / ABE / PSM / FBMSK", ok && n > 8000);
}

static void tests(void) {
    static const u32 arefs[3] = { 0, 0x40, 0x80 }, a8s[4] = { 0, 128, 253, 255 };
    u32 ate, atst, ar, afail, date, datm, zte, ztst, zmsk, m, a, s, i, ok = 1, zok = 1, n = 0;
    KH1DrawRegs r;
    KH1DrawState d;
    for (ate = 0; ate < 2; ate++) for (atst = 0; atst < 8; atst++) for (ar = 0; ar < 3; ar++)
    for (afail = 0; afail < 4; afail++) for (date = 0; date < 2; date++) for (datm = 0; datm < 2; datm++)
    for (zte = 0; zte < 2; zte++) for (ztst = 0; ztst < 4; ztst++) for (zmsk = 0; zmsk < 2; zmsk++)
    for (m = 0; m < 2; m++) {
        env(&r, 3);
        r.test_lo = test_word(ate, atst, arefs[ar], afail, date, datm, zte, ztst);
        r.zbuf_hi = zmsk;
        r.frame_hi = m ? 0xFFFFFF : 0; /* RGBA, or A only */
        kh1_drawstate_of(&r, &d);
        n++;
        if (d.n && d.depth.func != d.pipe[0].ztest) zok = 0;
        for (a = 0; a < 256; a++)
            for (s = 0; s < 4; s++) {
                u32 want = kh1_atest_gpu(&d.atest, a, kh1_atest_date_mark(&d.atest, a8s[s])), got = 0, marked;
                if (!d.depth.draw) want = 0;
                if (!d.depth.write) want &= 0xF;
                marked = !d.setup || (a8s[s] == 255) == d.setup_pipe.shader.datm;
                for (i = 0; i < d.n; i++) {
                    const KH1PipeKey *p = &d.pipe[i];
                    int pass = kh1_atest(p->shader.atst, a, d.u.aref);
                    if (p->stencil && !marked) continue;
                    if (p->shader.discard == KH1_DISCARD_FAIL && !pass) continue;
                    if (p->shader.discard == KH1_DISCARD_PASS && pass) continue;
                    got |= p->mask | (u32)p->zwrite << 4;
                }
                if (got != want) ok = 0;
            }
    }
    CHECK("every TEST / ZMSK / mask: the pipelines' writes are atest.h's and depth.h's", ok && n == 2 * 8 * 3 * 4 * 2 * 2 * 2 * 4 * 2 * 2);
    CHECK("the depth compare is depth.h's", zok);
}

static void texture(void) {
    static const u32 psms[13] = { 0x00, 0x01, 0x02, 0x0A, 0x13, 0x14, 0x1B, 0x24, 0x2C, 0x30, 0x31, 0x32, 0x3A };
    u32 i, tfx, tcc, ok = 1, fok = 1, c;
    KH1DrawRegs r;
    KH1DrawState d;
    for (i = 0; i < 13; i++)
        for (tfx = 0; tfx < 4; tfx++)
            for (tcc = 0; tcc < 2; tcc++) {
                env(&r, 0x116); /* SPRITE | TME | FST */
                r.tex0_lo = (r.tex0_lo & ~(63u << 20)) | psms[i] << 20;
                r.tex0_hi = (r.tex0_hi & ~0x1Cu) | tcc << 2 | tfx << 3;
                kh1_drawstate_of(&r, &d);
                if (d.pipe[0].shader.tex != kh1_texfmt_of(psms[i]) ||
                    d.pipe[0].shader.texa != (kh1_texfmt_texa(psms[i]) != 0) || !d.pipe[0].shader.fst) ok = 0;
                for (c = 0; c < 64; c++) {
                    u32 ct = c * 0x0B0D0F11u, cv = c * 0x11131719u;
                    if (kh1_texfunc(d.pipe[0].shader.tfx, d.pipe[0].shader.tcc, ct, cv) != kh1_texfunc_tex0(r.tex0_hi, ct, cv))
                        fok = 0;
                }
            }
    CHECK("every PSM: the key's upload format and TEXA flag are texfmt.h's", ok);
    CHECK("every TFX / TCC: the key's texture function is TEX0's", fok);
}

static int same_pipes(const KH1DrawState *a, const KH1DrawState *b) {
    return a->n == b->n && !memcmp(a->pipe, b->pipe, sizeof a->pipe) && a->setup == b->setup &&
           !memcmp(&a->setup_pipe, &b->setup_pipe, sizeof a->setup_pipe);
}

static void uniforms(void) {
    KH1DrawRegs r, q;
    KH1DrawState a, b;
    /* a fogged, alpha-tested, FIX-blended CT24 texture with REGION_CLAMP */
    env(&r, 0x7D | 0x100);
    r.test_lo = test_word(1, 5, 0x40, 0, 0, 0, 1, 2);
    r.alpha_lo = 0x64; /* (Cs - Cd) x FIX + Cd */
    r.alpha_hi = 0x40;
    r.tex0_lo = (r.tex0_lo & ~(63u << 20)) | 0x01u << 20;
    r.clamp_lo = 2 | 2 << 2 | 3 << 4 | 100u << 14 | 5u << 24;
    r.clamp_hi = 120 << 2;
    r.fogcol = 0x102030;
    r.texa_lo = 0x80 | 1 << 15;
    r.texa_hi = 0x40;
    kh1_drawstate_of(&r, &a);
    CHECK("the made-up state draws once", a.n == 1);
    CHECK("its uniforms: AREF, FIX, FOGCOL, TEXA, the region",
          a.u.aref == 0x40 && a.u.fix == 0x40 && a.u.fogcol == 0x102030 && a.u.ta0 == 0x80 && a.u.aem == 1 &&
          a.u.ta1 == 0x40 && a.u.u0 == 3 && a.u.u1 == 100 && a.u.v0 == 5 && a.u.v1 == 120);
    q = r;
    q.test_lo = test_word(1, 5, 0x7F, 0, 0, 0, 1, 2);
    q.alpha_hi = 0x20;
    q.fogcol = 0x405060;
    q.texa_lo = 0x10;
    q.texa_hi = 0x80;
    q.clamp_lo = 2 | 2 << 2 | 1 << 4 | 50u << 14 | 7u << 24;
    q.clamp_hi = 99 << 2;
    q.tex0_lo = (q.tex0_lo & ~0x3FFFu) | 0x2600; /* another TBP0 */
    q.tex0_hi = q.tex0_hi + (1u << 5);           /* another CBP */
    kh1_drawstate_of(&q, &b);
    CHECK("another AREF / FIX / FOGCOL / TEXA / region / address: the same pipelines", same_pipes(&a, &b));
    CHECK("... and other uniforms", b.u.aref == 0x7F && b.u.fix == 0x20 && b.u.fogcol == 0x405060 && b.u.u1 == 50);
    CHECK("... and another texture binding, the CLUT left out", b.tex0_lo != a.tex0_lo && b.tex0_hi == a.tex0_hi);
    /* the uniforms the shader does not read are 0 */
    env(&r, 0x116);
    r.test_lo = test_word(0, 6, 0x55, 0, 0, 0, 1, 1); /* ATE 0: no discard */
    r.fogcol = 0x123456;                               /* FGE 0 */
    r.texa_lo = 0x80;                                  /* PSMT8: TEXA is in the palette */
    r.alpha_hi = 0x77;                                 /* ABE 0 */
    kh1_drawstate_of(&r, &a);
    CHECK("unread uniforms are 0 (AREF without a discard, FOGCOL without FGE, TEXA for P8, FIX without ABE)",
          a.u.aref == 0 && a.u.fogcol == 0 && a.u.ta0 == 0 && a.u.fix == 0 && a.u.u0 == 0 && a.u.u1 == 0);
    r.test_lo = test_word(0, 6, 0x11, 0, 0, 0, 1, 1);
    r.fogcol = 0;
    kh1_drawstate_of(&r, &b);
    CHECK("... so those states share their pipelines and uniforms", same_pipes(&a, &b) && !memcmp(&a.u, &b.u, sizeof a.u));
}

static void game(void) {
    KH1DrawRegs r;
    KH1DrawState d;
    KH1PipeSet *s;
    static KH1PipeSet set;
    const KH1PipeKey *p;
    /* renderer B pass 1: TRIFAN | IIP | TME | FGE | ABE, TEST 0x5080B, ALPHA 0x44 */
    env(&r, 0x7D);
    r.test_lo = 0x5080B;
    r.fogcol = 0x808080;
    kh1_drawstate_of(&r, &d);
    p = &d.pipe[0];
    CHECK("renderer B pass 1: one pipeline, triangles, ONE / ONE_MINUS_SRC_ALPHA, GEQUAL with a write",
          d.n == 1 && p->cls == KH1_PA_TRIANGLES && p->blend && p->eq == KH1_BEQ_ADD &&
          p->fd == KH1_BF_ONE_MINUS_SRC_ALPHA && p->mask == 0xF && p->ztest == KH1_ZTST_GEQUAL && p->zwrite);
    CHECK("... its shader: P8, MODULATE, ST / Q, fog, Cs x As pre-scaled, discard where GEQUAL fails",
          p->shader.tex == KH1_TEXFMT_P8 && p->shader.tfx == KH1_TFX_MODULATE && p->shader.tcc && !p->shader.fst &&
          p->shader.fog && p->shader.pre_a == 3 && p->shader.pre_d == 2 && p->shader.discard == KH1_DISCARD_FAIL &&
          p->shader.atst == KH1_ATST_GEQUAL && d.u.aref == 0x80 && d.u.fogcol == 0x808080);
    /* pass 2: ATST LESS, ZMSK 1 */
    r.test_lo = 0x50805;
    r.zbuf_hi = 1;
    kh1_drawstate_of(&r, &d);
    CHECK("renderer B pass 2: GEQUAL with no depth write, discard where LESS fails",
          d.n == 1 && d.pipe[0].ztest == KH1_ZTST_GEQUAL && !d.pipe[0].zwrite && d.pipe[0].shader.atst == KH1_ATST_LESS);
    /* the HUD's numbers: (Cs - 0) x As + Cd, FIX 0x80 unused, TEST 0x30003 */
    env(&r, 0x156);
    r.test_lo = 0x30003;
    r.alpha_lo = 0x48;
    r.alpha_hi = 0x80;
    r.tex0_lo = (r.tex0_lo & ~(63u << 20)) | 0x14u << 20;
    kh1_drawstate_of(&r, &d);
    p = &d.pipe[0];
    CHECK("the HUD's numbers: additive ONE / ONE with the product floored, no test, no discard",
          d.n == 1 && p->blend && p->fd == KH1_BF_ONE && p->shader.pre_floor == 1 && p->ztest == KH1_ZTST_ALWAYS &&
          p->zwrite && !p->shader.discard && p->shader.tex == KH1_TEXFMT_P4 && d.u.fix == 0);
    /* opdma's Z-only write: ATST NEVER, AFAIL ZB_ONLY, ZTST GREATER */
    env(&r, 6);
    r.test_lo = test_word(1, 0, 0, 2, 0, 0, 1, 3);
    kh1_drawstate_of(&r, &d);
    CHECK("opdma's Z-only write: no colour, GREATER with a write, no discard",
          d.n == 1 && d.pipe[0].mask == 0 && d.pipe[0].zwrite && d.pipe[0].ztest == KH1_ZTST_GREATER &&
          !d.pipe[0].shader.discard);
    /* brightfade's DATE draw: DATM 1, NOTEQUAL 0 */
    env(&r, 6);
    r.test_lo = test_word(1, 7, 0, 0, 1, 1, 1, 1);
    kh1_drawstate_of(&r, &d);
    CHECK("brightfade's DATE: a set-up pipeline (stencil set, DATM 1) and a draw that tests it",
          d.n == 1 && d.setup && d.setup_pipe.stencil == 2 && d.setup_pipe.shader.setup && d.setup_pipe.shader.datm == 1 &&
          d.setup_pipe.mask == 0 && !d.setup_pipe.zwrite && d.pipe[0].stencil == 1);
    /* nothing drawn */
    env(&r, 6);
    r.test_lo = test_word(0, 0, 0, 0, 0, 0, 1, 0);
    kh1_drawstate_of(&r, &d);
    CHECK("ZTST NEVER draws nothing", d.n == 0 && !d.setup);
    env(&r, 7);
    kh1_drawstate_of(&r, &d);
    CHECK("PRIM 7 draws nothing", d.n == 0);
    /* AFAIL FB_ONLY with a test that can pass and a Z write: two pipelines */
    env(&r, 3);
    r.test_lo = test_word(1, 6, 0, 1, 0, 0, 1, 2);
    kh1_drawstate_of(&r, &d);
    CHECK("GREATER with AFAIL FB_ONLY and a Z write: the pass draw and the fail draw",
          d.n == 2 && d.pipe[0].shader.discard == KH1_DISCARD_FAIL && d.pipe[0].zwrite &&
          d.pipe[1].shader.discard == KH1_DISCARD_PASS && !d.pipe[1].zwrite && d.pipe[1].mask == 0xF);
    /* the set */
    s = &set;
    kh1_pipeset_clear(s);
    kh1_pipeset_add(s, &d);
    kh1_pipeset_add(s, &d);
    env(&r, 6);
    r.test_lo = test_word(1, 7, 0, 0, 1, 1, 1, 1);
    kh1_drawstate_of(&r, &d);
    kh1_pipeset_add(s, &d);
    env(&r, 6);
    r.test_lo = test_word(0, 0, 0, 0, 0, 0, 1, 0);
    kh1_drawstate_of(&r, &d);
    kh1_pipeset_add(s, &d);
    CHECK("the set: 4 states (1 empty), 4 pipelines (the two-draw state twice, DATE's draw and set-up), 4 shaders",
          s->states == 4 && s->empty == 1 && s->npipe == 4 && s->pipe_uses[0] == 2 && s->pipe_uses[1] == 2 &&
          s->nshader == 4);
}

int main(void) {
    blend();
    tests();
    texture();
    uniforms();
    game();
    printf("drawstate_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
