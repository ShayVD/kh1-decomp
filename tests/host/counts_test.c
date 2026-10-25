/* host/null/counts.c, KH1_HOST_COUNTS's high-water marks (session 96), on made-up counts (no game
 * data): tests/selftest.sh builds it with gcc -m32 when that works.  The game's globals are this
 * file's own here. */
#include "common.h"
#include "vm/vm_mgr.h"

int printf(const char *, ...);

typedef struct { s32 x0, x4, x8, xc, x10; } B4Counts;
B4Counts D_0055C698;
s32 D_002C12C4, D_00389C80, D_0029B2FC;
VmMgr D_00389C90;

extern int kh1_counts_on;
void kh1_counts_sample(void);
int kh1_counts_report(void);

static unsigned long frame;
unsigned long kh1_host_frame(void) { return frame; }

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("counts_test: %s\n", name); fails++; } } while (0)

int main(void) {
    /* off: nothing kept */
    D_0055C698.x8 = 500;
    kh1_counts_sample();
    CHECK("off: no report", kh1_counts_report() == 0);
    kh1_counts_on = 1;
    D_0055C698.x8 = 12;
    D_00389C80 = 40;
    frame = 3;
    kh1_counts_sample();
    CHECK("under every size", kh1_counts_report() == 0);
    /* a mark is kept after the count drops; one over its size is reported */
    D_0055C698.x8 = 0;
    D_00389C90.nbox = 11;
    D_00389C90.cnt[5] = 9;
    frame = 9;
    kh1_counts_sample();
    D_00389C90.nbox = 2;
    kh1_counts_sample();
    CHECK("a box over 10", kh1_counts_report() == 1);
    if (fails) { printf("counts_test: %d / %d failed\n", fails, checks); return 1; }
    printf("counts_test: %d / %d checks pass\n", checks, checks);
    return 0;
}
