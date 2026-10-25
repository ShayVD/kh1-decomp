/* KH1_HOST_COUNTS=1 (session 96, docs/vita-port-plan.md 5.1aj): the high-water marks of the counts
 * tools/host/countcheck.py's DATA rows name, the lists bounded only by what the disc's files hold (on
 * the PS2 too), so the real-disc run needs no gdb watchpoints.  Each count is read at every sample
 * point (each vblank, each DMA send, each draw / immediate list's end: host/null/plat_null.c and
 * main.c call kh1_counts_sample) and its largest value kept, with the frame it was first seen in;
 * kh1_counts_report prints them at the run's end (main.c's summary), one line each against the
 * array's size, "OVER" when a mark passed it.
 *
 * A sample point sees a count between the game's own steps, not inside them: the collision
 * candidate count D_002C12C4 is reset per query (mapcoll.c), so its mark is the largest a query
 * had left when a sample came, a lower bound of the true one.  Renderer B's lists (D_0055C698,
 * mdldraw.nostrict.c's B4Gl) and renderer A's grid count are reset each frame, after the draw list
 * that reads them was built, so the list-end sample sees them full.  Reads only: the game's memory
 * is not touched.  Not part of the PS2 build. */
#include "common.h"
#include "vm/vm_mgr.h"

int printf(const char *, ...);
unsigned long kh1_host_frame(void);

/* renderer B's per-frame block (mdldraw.nostrict.c B4Gl): its first five words */
typedef struct { s32 x0, x4, x8, xc, x10; } KH1B4Counts;
extern KH1B4Counts D_0055C698;
extern s32 D_002C12C4; /* the collision candidate count (D_002BD250[2048]) */
extern s32 D_00389C80; /* the message pointer count (D_00388480[273]) */
extern s32 D_0029B2FC; /* renderer A's grid list count (about 1020 entries, renderer-spec 4.14) */
extern VmMgr D_00389C90; /* the script manager: the windows' message lists and the trigger boxes */

typedef struct {
    const char *name, *what;
    s32 size;
    const s32 *p;
    s32 max;
    unsigned long frame;
} KH1Count;

static KH1Count counts[] = {
    {"D_0055C698.x4", "renderer B's objects obj[2][78]", 78, &D_0055C698.x4},
    {"D_0055C698.x8", "renderer B's part draws dsl[2][480]", 480, &D_0055C698.x8},
    {"D_0055C698.xc", "renderer B's models pr[2][72]", 72, &D_0055C698.xc},
    {"D_002C12C4", "collision candidates D_002BD250[2048] (per query: a lower bound)", 2048, &D_002C12C4},
    {"D_00389C80", "message pointers D_00388480[273]", 273, &D_00389C80},
    {"D_0029B2FC", "renderer A's grid cells (about 1020)", 1020, &D_0029B2FC},
    {"D_00389C90.nbox", "script trigger boxes box[10]", 10, &D_00389C90.nbox},
    {"D_00389C90.cnt[0]", "window template 0's messages tbl[0][256]", 256, &D_00389C90.cnt[0]},
    {"D_00389C90.cnt[1]", "window template 1's messages tbl[1][256]", 256, &D_00389C90.cnt[1]},
    {"D_00389C90.cnt[2]", "window template 2's messages tbl[2][256]", 256, &D_00389C90.cnt[2]},
    {"D_00389C90.cnt[3]", "window template 3's messages tbl[3][256]", 256, &D_00389C90.cnt[3]},
    {"D_00389C90.cnt[4]", "window template 4's messages tbl[4][256]", 256, &D_00389C90.cnt[4]},
    {"D_00389C90.cnt[5]", "window template 5's messages tbl[5][256]", 256, &D_00389C90.cnt[5]},
    {"D_00389C90.cnt[6]", "window template 6's messages tbl[6][256]", 256, &D_00389C90.cnt[6]},
    {"D_00389C90.cnt[7]", "window template 7's messages tbl[7][256]", 256, &D_00389C90.cnt[7]},
};
#define NCOUNTS (s32)(sizeof counts / sizeof counts[0])

int kh1_counts_on;
static unsigned long samples;

void kh1_counts_sample(void) {
    s32 i, v;
    if (!kh1_counts_on) return;
    samples++;
    for (i = 0; i < NCOUNTS; i++) {
        v = *counts[i].p;
        if (v > counts[i].max) {
            counts[i].max = v;
            counts[i].frame = kh1_host_frame();
        }
    }
}

/* 1 when a mark passed its array's size */
int kh1_counts_report(void) {
    s32 i, over = 0;
    if (!kh1_counts_on) return 0;
    printf("kh1-host: counts: high-water marks over %lu samples (KH1_HOST_COUNTS, countcheck.py's DATA rows)\n",
           samples);
    for (i = 0; i < NCOUNTS; i++) {
        printf("kh1-host: count %-18s %6d / %-5d frame %-6lu %s%s\n", counts[i].name, counts[i].max, counts[i].size,
               counts[i].frame, counts[i].what, counts[i].max > counts[i].size ? "  OVER" : "");
        over |= counts[i].max > counts[i].size;
    }
    return over;
}
