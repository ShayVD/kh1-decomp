/* The GPU pipelines a list of GS draw states needs (session 123, docs/renderer-spec.md 4.13 "Session 123"):
 * tools/host/drawpipes.py compiles this with host/port/drawstate.c and its pieces under gcc and feeds it
 * one draw state a line, 17 hex words in include/platform/drawstate.h's KH1DrawRegs order:
 *
 *   prim frame_lo frame_hi zbuf_lo zbuf_hi test_lo alpha_lo alpha_hi tex0_lo tex0_hi tex1_lo tex1_hi
 *   clamp_lo clamp_hi fogcol texa_lo texa_hi
 *
 * For each it prints `state N: P1 [P2] [setup P]` (the pipelines' numbers, 1 up, or `none`), then the
 * totals and `pipe N: KEY` per pipeline, and `shader N: KEY` per fragment shader.  Register values
 * only: nothing from the disc. */
#include "common.h"
#include "platform/drawstate.h"

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

int main(void) {
    u32 w[17], i, n = 0;
    KH1DrawRegs r;
    KH1DrawState d;
    KH1PipeKey shk;
    for (;;) {
        for (i = 0; i < 17; i++)
            if (scanf("%x", &w[i]) != 1) break;
        if (i < 17) break;
        r.prim = w[0]; r.frame_lo = w[1]; r.frame_hi = w[2]; r.zbuf_lo = w[3]; r.zbuf_hi = w[4];
        r.test_lo = w[5]; r.alpha_lo = w[6]; r.alpha_hi = w[7]; r.tex0_lo = w[8]; r.tex0_hi = w[9];
        r.tex1_lo = w[10]; r.tex1_hi = w[11]; r.clamp_lo = w[12]; r.clamp_hi = w[13]; r.fogcol = w[14];
        r.texa_lo = w[15]; r.texa_hi = w[16];
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
    return 0;
}
