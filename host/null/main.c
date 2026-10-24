/* The host runner (docs/vita-port-plan.md sections 5.1b and 5.1c): main() calls the game's own
 * main, func_00100558 (crt0's call: func_00262c78 (__main), func_00109288, then func_00109770
 * for ever), on the null platform.
 *
 *   KH1_HOST_ISO=PATH   the user's own disc image (never in the repo): PlatCdSearchFile and
 *                       PlatCdRead answer from it (host/port/cd_image.c).  Without one the first
 *                       PlatCdRead ends the run (exit 0), since there is no disc to answer it;
 *                       KH1_HOST_CD=go lets it carry on (every read fails and the game retries).
 *   KH1_HOST_FRAMES=N   stop after N frames (default 600); a frame is one call of the game's
 *                       vblank handler, which PlatGsSyncV and PlatWaitSema run
 *   KH1_HOST_TRACE=1    print every search and read
 *
 * A crash prints a backtrace and what the run had read.  Not part of the PS2 build. */
#define _GNU_SOURCE
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void func_00100558(int argc, char **argv);
int kh1_cd_image_open(const char *path);

int kh1_host_stop_at_cdread = 1;
int kh1_host_trace;
unsigned int kh1_host_cd_reads, kh1_host_cd_sectors;
static unsigned long frames, max_frames = 600;

static void summary(void) {
    fprintf(stderr, "kh1-host: %lu frames, %u disc reads (%u sectors)\n", frames, kh1_host_cd_reads,
            kh1_host_cd_sectors);
}

/* sceGsSyncVCallback's handler (host/port/sdk_host.c), an INTC handler: int (*)(int cause) */
extern void *kh1_vsync_cb;
void kh1_host_vblank(void) {
    static int in_vblank;
    if (in_vblank) return;
    in_vblank = 1;
    frames++;
    if (kh1_vsync_cb) ((int (*)(int))kh1_vsync_cb)(2);
    in_vblank = 0;
    if (frames >= max_frames) {
        printf("kh1-host: %lu frames: stop\n", frames);
        summary();
        exit(0);
    }
}

static void on_crash(int sig) {
    void *bt[64];
    int n = backtrace(bt, 64);
    fprintf(stderr, "kh1-host: signal %d (%s)\n", sig, strsignal(sig));
    summary();
    backtrace_symbols_fd(bt, n, 2);
    _exit(128 + sig);
}

int main(int argc, char **argv) {
    const char *cd = getenv("KH1_HOST_CD");
    const char *iso = getenv("KH1_HOST_ISO");
    const char *nf = getenv("KH1_HOST_FRAMES");
    setvbuf(stdout, 0, _IONBF, 0);
    signal(SIGSEGV, on_crash);
    signal(SIGBUS, on_crash);
    signal(SIGFPE, on_crash);
    signal(SIGILL, on_crash);
    signal(SIGABRT, on_crash);
    if (cd && strcmp(cd, "go") == 0)
        kh1_host_stop_at_cdread = 0;
    if (nf)
        max_frames = strtoul(nf, 0, 0);
    kh1_host_trace = getenv("KH1_HOST_TRACE") != 0;
    if (iso) {
        if (!kh1_cd_image_open(iso)) {
            fprintf(stderr, "kh1-host: %s: not a disc image (no ISO9660 volume at sector 16)\n", iso);
            return 2;
        }
        printf("kh1-host: disc image %s\n", iso);
    }
    printf("kh1-host: func_00100558 (the game's main)\n");
    func_00100558(argc, argv);
    printf("kh1-host: func_00100558 returned\n");
    summary();
    return 1;
}
