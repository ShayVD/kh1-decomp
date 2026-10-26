/* The Vita runner (docs/vita-build.md): main() calls the game's own main, func_00100558, on the
 * null platform's GS model and DMA walk (host/null/) with the Vita's own screen, controls and
 * threads (host/vita/).  It reads the user's own disc image from ux0:data/kh1/ (never shipped in the
 * VPK) and writes a log there.
 *
 *   ux0:data/kh1/kh1.iso      the user's disc image (2048-byte .iso, or a raw .bin as kh1.bin)
 *   ux0:data/kh1/config.txt   optional "key=value" lines:
 *       iso=PATH              another image path
 *       title=N               at the title overlay's entry call ask for game state N (2: a new
 *                             game, Dive to the Heart; -1: stay at the title).  Default 2.  The
 *                             title screen itself is dktitle.x: once its C is complete
 *                             (session 132, host/port/ovl.c) the title runs and this is unused;
 *                             until then nothing draws it: see kh1_ovl_entry.
 *       trace=N               the host's KH1_HOST_TRACE levels into the log (default 1: disc reads)
 *       frames=N              exit after N frames (default 0: never)
 *   ux0:data/kh1/kh1.log      stdout and stderr
 *
 * Not part of the PS2 build. */
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "platform/ovl.h"
#include "present.h"
#include "gsmem.h"
#include "vita.h"

/* newlib's heap and the main thread's stack: the game's coroutine stacks (0x40000 each, host/null
 * threads.c, host/port/tasks.c) and the model's buffers come from the heap; the 25 MiB memory map
 * (host/port/memmap.c) is .bss */
int _newlib_heap_size_user = 160 * 1024 * 1024;
unsigned int sceUserMainThreadStackSize = 4 * 1024 * 1024;

const char kh1_vita_dir[] = "ux0:data/kh1";

void func_00100558(int argc, char **argv);
int func_00109558(int state);
int kh1_cd_image_open(const char *path);
extern unsigned char D_002A6890[]; /* brightfade.c's frame copy (renderer-spec 5.4 "Session 93") */

/* what host/null/ and host/port/ expect from the runner (host/null/main.c on the host) */
int kh1_host_stop_at_cdread = 0;
int kh1_host_trace = 1;
unsigned int kh1_host_cd_reads, kh1_host_cd_sectors;
static unsigned long frames, max_frames;
static int title_state = 2;
static SceUID log_fd = -1;

/* the log goes straight to sceIoWrite (a FILE from funopen, unbuffered): newlib's own fopen'd log
 * stayed empty in Vita3K through two runs */
static int log_write(void *cookie, const char *buf, int n) {
    (void)cookie;
    if (log_fd >= 0) sceIoWrite(log_fd, buf, n);
    return n;
}

/* this file's own lines go straight to the log too, whatever stdio does */
static void vlog(const char *fmt, ...) {
    char buf[256];
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    if (n > (int)sizeof buf - 1) n = sizeof buf - 1;
    if (log_fd >= 0 && n > 0) sceIoWrite(log_fd, buf, n);
}

unsigned long kh1_host_frame(void) { return frames; }

extern int kh1_counts_on; /* host/null/counts.c */
void kh1_counts_sample(void);
void kh1_null_iop_frame(void);
extern void *kh1_vsync_cb; /* sceGsSyncVCallback's handler (host/port/sdk_host.c) */

/* one frame: the game's vblank handler, paced by the Vita's own vblank */
void kh1_host_vblank(void) {
    static int in_vblank;
    if (in_vblank) return;
    in_vblank = 1;
    frames++;
    if (frames % 60 == 0) vlog("kh1-vita: frame %lu, %u disc reads\n", frames, kh1_host_cd_reads);
    kh1_counts_sample();
    kh1_null_iop_frame();
    if (kh1_vsync_cb) ((int (*)(int))kh1_vsync_cb)(2);
    kh1_vita_status(frames, kh1_host_cd_reads);
    sceDisplayWaitVblankStart();
    in_vblank = 0;
    if (max_frames && frames >= max_frames) {
        vlog("kh1-vita: %lu frames: stop\n", frames);
        fflush(stdout);
        sceKernelExitProcess(0);
    }
}

/* The overlay entry D_00F20000: the game loads an overlay's MIPS code into the overlay area and
 * calls its first byte.  No overlay is decompiled yet (vita-port-plan 5.2), so tools/vita/build.py
 * compiles the files that call it with -DD_00F20000=kh1_ovl_entry and this answers 0, as the host's
 * KH1_HOST_OVL=stub does.  At the title's first call (0, 0) it asks for config.txt's game state
 * (func_00109558, the request roomload.c and gameover.c make): 2 starts a new game. */
static unsigned long ovl_calls;
int kh1_ovl_entry(int cmd, int arg) {
    int ret;
    if (PlatOvlCall(cmd, arg, &ret)) /* session 132: a native overlay (dktitle.x, host/port/ovl.c) */
        return ret;
    ovl_calls++;
    vlog("kh1-vita: frame %lu: overlay entry D_00F20000(%d, %d) answered 0 (no overlay is decompiled)\n", frames,
           cmd, arg);
    if (title_state >= 0 && cmd == 0) {
        vlog("kh1-vita: title: func_00109558(%d)\n", title_state);
        func_00109558(title_state);
        title_state = -1;
    }
    return 0;
}

/* a second thread: every 2 s of wall time, where the game is (a black screen with no status strip
 * means no vblank: this says whether DMA sends still move) */
extern volatile u32 kh1_vita_sends, kh1_vita_last_send, kh1_vita_shown;
static int watchdog(SceSize args, void *argp) {
    unsigned long last = (unsigned long)-1;
    (void)args;
    (void)argp;
    for (;;) {
        sceKernelDelayThread(2000000);
        vlog("kh1-vita: watchdog %llu ms: frame %lu, %u disc reads, %u sends (last 0x%08x), %u shown%s\n",
             (unsigned long long)(sceKernelGetProcessTimeWide() / 1000), frames, kh1_host_cd_reads,
             kh1_vita_sends, kh1_vita_last_send, kh1_vita_shown, frames == last ? " (no vblank since the last)" : "");
        last = frames;
    }
    return 0;
}

static void config(char *iso, int n) {
    char path[128], line[256];
    FILE *f;
    snprintf(path, sizeof path, "%s/config.txt", kh1_vita_dir);
    f = fopen(path, "r");
    if (!f) return;
    while (fgets(line, sizeof line, f)) {
        char *v = strchr(line, '='), *e;
        if (line[0] == '#' || !v) continue;
        *v++ = 0;
        for (e = v + strlen(v); e > v && (e[-1] == '\n' || e[-1] == '\r' || e[-1] == ' '); e--) e[-1] = 0;
        if (strcmp(line, "iso") == 0) snprintf(iso, n, "%s", v);
        else if (strcmp(line, "title") == 0) title_state = atoi(v);
        else if (strcmp(line, "trace") == 0) kh1_host_trace = atoi(v);
        else if (strcmp(line, "frames") == 0) max_frames = strtoul(v, 0, 0);
    }
    fclose(f);
}

/* no disc image: a red screen until START, then exit */
static void no_disc(const char *iso) {
    vlog("kh1-vita: %s: no disc image (put your own dump at %s/kh1.iso, see docs/vita-build.md)\n", iso,
           kh1_vita_dir);
    fflush(stdout);
    kh1_vita_fill(0xFF0000A0u);
    while (!(kh1_vita_buttons() & 0x0008)) sceDisplayWaitVblankStart();
    sceKernelExitProcess(0);
}

int main(int argc, char **argv) {
    char iso[256], log[128];
    /* the EE's FPU flushes denormals to zero (portability rule 7): the VFP's FZ bit (FPSCR bit 24);
     * the game's coroutines take it with the rest of FPSCR (host/vita/context.S) */
    {
        unsigned int fpscr;
        __asm__ volatile("vmrs %0, fpscr" : "=r"(fpscr));
        __asm__ volatile("vmsr fpscr, %0" : : "r"(fpscr | (1u << 24)));
    }
    sceIoMkdir(kh1_vita_dir, 0777);
    snprintf(log, sizeof log, "%s/kh1.log", kh1_vita_dir);
    log_fd = sceIoOpen(log, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
    if (log_fd >= 0) {
        FILE *f;
        /* newlib sets the standard streams up at its first stdio call on them (__sinit), which
         * would put the console's back over ours: make that happen first */
        fflush(stdout);
        fflush(stderr);
        f = funopen(0, 0, log_write, 0, 0);
        if (f) {
            setvbuf(f, 0, _IONBF, 0);
            stdout = f;
            stderr = f;
            _GLOBAL_REENT->_stdout = f;
            _GLOBAL_REENT->_stderr = f;
        }
        sceIoWrite(log_fd, "kh1-vita: log open\n", 19);
    }
    vlog("kh1-vita: kh1-decomp's first Vita build (docs/vita-build.md)\n");
    if (kh1_vita_display_init(D_002A6890)) {
        vlog("kh1-vita: no framebuffer\n");
        sceKernelExitProcess(1);
    }
    snprintf(iso, sizeof iso, "%s/kh1.iso", kh1_vita_dir);
    config(iso, sizeof iso);
    if (!kh1_cd_image_open(iso)) {
        snprintf(iso, sizeof iso, "%s/kh1.bin", kh1_vita_dir);
        if (!kh1_cd_image_open(iso)) no_disc(iso);
    }
    vlog("kh1-vita: disc image %s\n", iso);
    /* the chain walk feeds the GS memory model (KH1_HOST_TRACE >= 2 on the host) */
    if (kh1_host_trace < 2) kh1_host_trace = 2;
    kh1_gsmem_flat(1);  /* the clears, fades and letterbox filled into the model */
    kh1_present_pal(1); /* the indexed decodes through the port's palette cache */
    kh1_present_tex(1); /* the textured sprites through the port's texture cache */
    kh1_vita_present_on();
    {
        SceUID t = sceKernelCreateThread("kh1_watchdog", watchdog, 0x10000100, 0x4000, 0, 0, 0);
        if (t >= 0) sceKernelStartThread(t, 0, 0);
    }
    vlog("kh1-vita: func_00100558 (the game's main)\n");
    func_00100558(argc, argv);
    vlog("kh1-vita: func_00100558 returned after %lu frames, %u disc reads, %lu overlay calls\n", frames,
           kh1_host_cd_reads, ovl_calls);
    fflush(stdout);
    sceKernelExitProcess(0);
    return 0;
}
