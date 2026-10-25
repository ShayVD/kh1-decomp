/* The GPU pipelines a list of GS draw states needs (session 123, docs/renderer-spec.md 4.13 "Session 123"):
 * tools/host/drawpipes.py compiles this with host/port/drawstate.c and its pieces under gcc and feeds it
 * one draw state a line, 17 hex words in include/platform/drawstate.h's KH1DrawRegs order:
 *
 *   prim frame_lo frame_hi zbuf_lo zbuf_hi test_lo alpha_lo alpha_hi tex0_lo tex0_hi tex1_lo tex1_hi
 *   clamp_lo clamp_hi fogcol texa_lo texa_hi
 *
 * For each it prints `state N: P1 [P2] [setup P]` (the pipelines' numbers, 1 up, or `none`), then the
 * totals and `pipe N: KEY` per pipeline, and `shader N: KEY` per fragment shader.  Register values
 * only: nothing from the disc.
 *
 * Session 124: then `vertex shaders: N` with their names (include/platform/vertex.h).  With --batches it
 * reads sends instead (drawpipes.py --batches): `S` starts one, `B <17 words> <scissor lo hi> <primitives>
 * <vertices> <signature>` is a run of kicks in one state with the same vertices (session 125: the signature
 * feeds batch.h's column groups), `X` a transfer or CLUT load, `E` ends it; for each send it
 * prints `send N: BATCHES DRAWS PRIMS VERTS` (include/platform/batch.h's cut, the 3D target's 4:3 canvas at
 * scale 1), then the totals and what opened the batches.
 *
 * Session 126 (renderer-spec 4.13 "Session 126"): --passes reads the same sends through
 * include/platform/cmdbuf.h's recorder, each send alone with every target taken as drawn before it (what the
 * frame drew earlier is unknown here, and the packets' vertices are not passed, so no pass counts as cleared):
 * `send N: P passes C commands` and a `pass` line each (target, depth, load / store: a STORE is a later pass
 * of the same send sampling or drawing on the target; OPEN is decided by what follows the send), then the
 * totals. */
#include "common.h"
#include "platform/drawstate.h"
#include "platform/batch.h"
#include "platform/vertex.h"
#include "platform/cmdbuf.h"

int printf(const char *, ...);
int scanf(const char *, ...);
int memcmp(const void *, const void *, __SIZE_TYPE__);
void *memset(void *, int, __SIZE_TYPE__);

static KH1PipeSet set;

static u32 find(const KH1PipeKey *k) {
    u32 i;
    for (i = 0; i < set.npipe; i++)
        if (!memcmp(&set.pipe[i], k, sizeof *k)) return i + 1;
    return 0;
}

int strcmp(const char *, const char *);

static void read_regs(const u32 *w, KH1DrawRegs *r) {
    r->prim = w[0]; r->frame_lo = w[1]; r->frame_hi = w[2]; r->zbuf_lo = w[3]; r->zbuf_hi = w[4];
    r->test_lo = w[5]; r->alpha_lo = w[6]; r->alpha_hi = w[7]; r->tex0_lo = w[8]; r->tex0_hi = w[9];
    r->tex1_lo = w[10]; r->tex1_hi = w[11]; r->clamp_lo = w[12]; r->clamp_hi = w[13]; r->fogcol = w[14];
    r->texa_lo = w[15]; r->texa_hi = w[16];
}

static int batches(void) {
    static const KH1Canvas c43 = { 1.0f, 0.0f, 0.0f, 0, 8192 };
    static KH1Batcher b;
    char t[4];
    u32 w[22], i, n = 0;
    KH1DrawRegs r;
    KH1DrawState d;
    KH1RenderPass p;
    kh1_batch_reset(&b);
    while (scanf("%3s", t) == 1) {
        if (t[0] == 'S') continue;
        if (t[0] == 'X') { kh1_batch_break(&b); continue; }
        if (t[0] == 'E') {
            const KH1BatchCount *f = &b.frame;
            printf("send %u: %u %u %u %u\n", ++n, f->batches, f->draws, f->prims, f->verts);
            kh1_batch_frame(&b);
            continue;
        }
        for (i = 0; i < 22; i++)
            if (scanf("%x", &w[i]) != 1) return 1;
        read_regs(w, &r);
        kh1_drawstate_of(&r, &d);
        kh1_target_of(r.frame_lo, r.frame_hi, r.zbuf_lo, r.zbuf_hi, r.test_lo, w[17], w[18], 0, 0, &c43, 1.0f, &p);
        for (i = 0; i < w[19]; i++) kh1_batch_prim_sig(&b, &d, &p, w[20] / w[19], w[21]);
    }
    printf("batches opened by: %u render passes, %u pipelines, %u textures, %u uniforms, %u scissors, %u transfers\n",
           b.total.passes, b.total.pipes, b.total.textures, b.total.uniforms, b.total.scissors, b.total.breaks);
    printf("column groups: %u columns merged, %u primitives absorbed\n", b.total.columns, b.total.merged);
    printf("a send at most %u batches, %u draw calls, %u primitives\n", b.max.batches, b.max.draws, b.max.prims);
    return 0;
}

void *malloc(__SIZE_TYPE__);

static int passes(void) {
    static const KH1Canvas c43 = { 1.0f, 0.0f, 0.0f, 0, 8192 };
    static KH1CmdRec r;
    void *vm = malloc(2u << 20), *um = malloc(2u << 18);
    char t[4];
    u32 w[22], i, n = 0, multi = 0, sampled = 0, opened = 0, joins = 0;
    KH1DrawRegs g;
    KH1DrawState d;
    KH1RenderPass p;
    kh1_cmd_init(&r, vm, 1u << 20, um, 1u << 18);
    while (scanf("%3s", t) == 1) {
        if (t[0] == 'S') {
            kh1_cmd_init(&r, vm, 1u << 20, um, 1u << 18);
            r.assume_drawn = 1;
            continue;
        }
        if (t[0] == 'X') { kh1_cmd_break(&r); continue; }
        if (t[0] == 'E') {
            kh1_cmd_frame(&r);
            joins += r.frame.depth_joins;
            n++;
            if (r.npass) {
                printf("send %u: %u passes %u commands\n", n, r.npass, r.ncmd);
                for (i = 0; i < r.npass; i++) {
                    printf("pass %u: %s\n", i + 1, kh1_cmd_pass_str(&r.pass[i]));
                    if (r.pass[i].why & KH1_WHY_SAMPLED) sampled++;
                }
                if (r.npass > 1) multi++;
                opened += r.npass;
            } else {
                printf("send %u: 0 passes 0 commands\n", n);
            }
            kh1_cmd_reset_frame(&r);
            continue;
        }
        for (i = 0; i < 22; i++)
            if (scanf("%x", &w[i]) != 1) return 1;
        read_regs(w, &g);
        kh1_drawstate_of(&g, &d);
        kh1_target_of(g.frame_lo, g.frame_hi, g.zbuf_lo, g.zbuf_hi, g.test_lo, w[17], w[18], 0, 0, &c43, 1.0f, &p);
        for (i = 0; i < w[19]; i++) kh1_cmd_prim(&r, &d, &p, 0, w[20] / w[19], w[21]);
    }
    printf("total: %u sends, %u passes, %u sends with more than one pass, %u passes sampled by a later pass of their send, "
           "%u depth-only pass changes joined\n", n, opened, multi, sampled, joins);
    return 0;
}

int main(int argc, char **argv) {
    u32 w[17], i, n = 0, vmask, nv;
    if (argc > 1 && !strcmp(argv[1], "--batches")) return batches();
    if (argc > 1 && !strcmp(argv[1], "--passes")) return passes();
    KH1DrawRegs r;
    KH1DrawState d;
    KH1PipeKey shk;
    for (;;) {
        for (i = 0; i < 17; i++)
            if (scanf("%x", &w[i]) != 1) break;
        if (i < 17) break;
        read_regs(w, &r);
        kh1_drawstate_of(&r, &d);
        kh1_pipeset_add(&set, &d);
        printf("state %u:", ++n);
        if (!d.n) printf(" none");
        for (i = 0; i < d.n; i++) printf(" %u", find(&d.pipe[i]));
        if (d.setup) printf(" setup %u", find(&d.setup_pipe));
        printf("\n");
    }
    printf("total: %u draw states (%u draw nothing), %u GPU pipelines, %u fragment shaders, %u samplers%s\n",
           set.states, set.empty, set.npipe, set.nshader, set.nsampler, set.lost ? " (some past the table)" : "");
    for (i = 0; i < set.npipe; i++) printf("pipe %u: %s\n", i + 1, kh1_pipekey_str(&set.pipe[i]));
    for (i = 0; i < set.nshader; i++) {
        const char *s;
        int k;
        memset(&shk, 0, sizeof shk);
        shk.shader = set.shader[i];
        s = kh1_pipekey_str(&shk);
        for (k = 0; s[k] && s[k] != '|'; k++) ;
        printf("shader %u:%s\n", i + 1, s[k] ? s + k + 1 : s);
    }
    nv = kh1_vertex_variants(&set, &vmask);
    printf("vertex shaders: %u", nv);
    for (i = 0; i < 7; i++)
        if (vmask >> i & 1) printf(" [%s]", kh1_vertkey_str(i));
    printf("\n");
    return 0;
}
