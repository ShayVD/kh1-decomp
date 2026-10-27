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
 *       trace=N               the host's KH1_HOST_TRACE levels into the log (default 1: disc reads;
 *                             2 adds the chain walk's line per DMA send, which costs speed)
 *       frames=N              exit after N frames (default 0: never)
 *       gpu=N                 session 136: 1 (the default) draws with the GPU (host/vita/gxm.c) when its
 *                             shaders can be had (ur0:data/libshacccg.suprx, or the cache in
 *                             ux0:data/kh1/shaders/); 0 keeps the GS model's software picture
 *       pad=PATH              session 137v: a host pad script (tests/host/pads/, host/null/pad.c) played instead of
 *                             the Vita's controls, e.g. ux0:data/kh1/dive.txt
 *       vu1=N                 1 (the default) runs VIF1 and the VU1 microprograms (host/port/vu1.c), so the 3D
 *                             (maps, characters) reaches the GS; 0 skips them as before (the 3D stays black)
 *       vu1tr=N               1 (the default) runs the programs out/gen/vu1_tr.c translated as their C; 0 the
 *                             interpreter only; 2 both, compared (slow; differences go to the log)
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
#include "gsregs.h"
#include "vita.h"
#include "dmawalk.h"
#include "platform/cmdbuf.h"
#include "platform/vu1.h"

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
static volatile u32 kh1_vita_us_wait; /* session 135: microseconds in the vblank wait (the watchdog's) */
extern volatile u32 kh1_vita_us_present; /* display.c */
static int title_state = 2;
extern const char *kh1_vita_pad_script; /* host/null/pad.c */
static int use_gpu = 1; /* session 136: config.txt's gpu= */
static int gpu_on;      /* the GPU renderer runs (gxm.c) */
/* session 136: where a GPU frame's CPU time goes (the watchdog's): recording the kicks, the frame's
 * commands (gxm.c's submit included), the present, and the slowest frame (vblank to vblank, its wait left
 * out) of each 2 s */
static volatile u32 us_record, us_frame, us_draw, us_worst;
static SceUID log_fd = -1;

/* the log goes straight to sceIoWrite (a FILE from funopen, unbuffered): newlib's own fopen'd log
 * stayed empty in Vita3K through two runs */
static int log_write(void *cookie, const char *buf, int n) {
    (void)cookie;
    if (log_fd >= 0) sceIoWrite(log_fd, buf, n);
    return n;
}

/* this file's own lines go straight to the log too, whatever stdio does */
#define vlog kh1_vita_log
void kh1_vita_log(const char *fmt, ...) {
    char buf[4608]; /* session 136: room for a shader's text (gxm.c) */
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    if (n > (int)sizeof buf - 1) n = sizeof buf - 1;
    if (log_fd >= 0 && n > 0) sceIoWrite(log_fd, buf, n);
}

unsigned long kh1_host_frame(void) { return frames; }
static u32 vita_us(void) { return (u32)sceKernelGetProcessTimeWide(); }

extern int kh1_counts_on; /* host/null/counts.c */
void kh1_counts_sample(void);
void kh1_null_iop_frame(void);
/* host/null/pipes.c: the command recorder (session 136: the GPU renderer's input) */
void kh1_pipes_start(void);
void kh1_pipes_frame(void);
void kh1_pipes_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state);
static void timed_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state) {
    SceUInt64 t0 = sceKernelGetProcessTimeWide();
    kh1_pipes_prim(prim, v, n, state);
    us_record += (u32)(sceKernelGetProcessTimeWide() - t0);
}
extern void (*kh1_pipes_frame_hook)(const KH1CmdRec *r);
void kh1_vita_gxm_frame(const KH1CmdRec *r);
extern void *kh1_vsync_cb; /* sceGsSyncVCallback's handler (host/port/sdk_host.c) */

/* one frame: the game's vblank handler, paced by the Vita's own vblank */
void kh1_host_vblank(void) {
    static int in_vblank;
    static SceUInt64 woke; /* the end of the last vblank wait */
    if (in_vblank) return;
    in_vblank = 1;
    frames++;
    if (frames % 60 == 0) vlog("kh1-vita: frame %lu, %u disc reads\n", frames, kh1_host_cd_reads);
    kh1_counts_sample();
    kh1_null_iop_frame();
    if (kh1_vsync_cb) ((int (*)(int))kh1_vsync_cb)(2);
    if (gpu_on) { /* session 136: the frame's GS draws on the GPU (gxm.c through the recorder's hook), shown */
        SceUInt64 t0 = sceKernelGetProcessTimeWide(), t1;
        kh1_pipes_frame();
        /* only a whole picture is shown: the display target as the frame copy left it (the software
         * present's rule); between copies the game may be part-way through the next one */
        if (kh1_vita_frame_copied()) kh1_vita_gxm_latch();
        t1 = sceKernelGetProcessTimeWide();
        kh1_vita_draw();
        us_frame += (u32)(t1 - t0);
        us_draw += (u32)(sceKernelGetProcessTimeWide() - t1);
    }
    kh1_vita_status(frames, kh1_host_cd_reads);
    {
        SceUInt64 t0 = sceKernelGetProcessTimeWide();
        if (woke && (u32)(t0 - woke) > us_worst) us_worst = (u32)(t0 - woke);
        sceDisplayWaitVblankStart();
        woke = sceKernelGetProcessTimeWide();
        kh1_vita_us_wait += (u32)(woke - t0);
    }
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
extern volatile u32 kh1_vita_us_gpu;
static int watchdog(SceSize args, void *argp) {
    unsigned long last = (unsigned long)-1;
    u32 wait0 = 0, present0 = 0, gpu0 = 0, rec0 = 0, frame0 = 0, draw0 = 0, vu0 = 0, kick0 = 0;
    (void)args;
    (void)argp;
    for (;;) {
        sceKernelDelayThread(2000000);
        /* session 135: of the 2 s, the ms spent waiting for the Vita's vblank and in the present; the
         * rest is the game and the chain walk (the GS model's drawing) */
        vlog("kh1-vita: watchdog %llu ms: frame %lu, %u disc reads, %u sends (last 0x%08x), %u shown; "
             "%u ms vblank wait, %u ms present%s\n",
             (unsigned long long)(sceKernelGetProcessTimeWide() / 1000), frames, kh1_host_cd_reads,
             kh1_vita_sends, kh1_vita_last_send, kh1_vita_shown, (kh1_vita_us_wait - wait0) / 1000,
             (kh1_vita_us_present - present0) / 1000, frames == last ? " (no vblank since the last)" : "");
        if (gpu_on) { /* session 136: the GPU frame's CPU time (its waits for the GPU included), its counts */
            u32 f, d, sk, sc;
            kh1_vita_gxm_stats(&f, &d, &sk, &sc);
            vlog("kh1-vita: gpu: %u ms submitting; %u frames, %u scenes, %u draws, %u skipped\n",
                 (kh1_vita_us_gpu - gpu0) / 1000, f, sc, d, sk);
            /* the rest of the 2 s (less the vblank wait) is the game and the GS model's chain walk */
            vlog("kh1-vita: cpu: %u ms recording, %u ms the frame's commands (the submit in it), %u ms present; "
                 "slowest frame %u.%u ms\n", (us_record - rec0) / 1000, (us_frame - frame0) / 1000,
                 (us_draw - draw0) / 1000, us_worst / 1000, us_worst / 100 % 10);
            us_worst = 0;
            /* session 137v: of the rest, the VU1 programs (the kicks they hand on included, then alone) */
            vlog("kh1-vita: vu1: %u ms in programs, %u ms of it passing their kicks on\n", (kh1_vu1_us - vu0) / 1000,
                 (kh1_vu1_kick_us - kick0) / 1000);
        }
        vu0 = kh1_vu1_us;
        kick0 = kh1_vu1_kick_us;
        rec0 = us_record;
        frame0 = us_frame;
        draw0 = us_draw;
        gpu0 = kh1_vita_us_gpu;
        wait0 = kh1_vita_us_wait;
        present0 = kh1_vita_us_present;
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
        else if (strcmp(line, "gpu") == 0) use_gpu = atoi(v);
        else if (strcmp(line, "vu1") == 0) kh1_dma_vu1 = atoi(v);
        else if (strcmp(line, "vu1tr") == 0) kh1_vu1_tr = atoi(v);
        else if (strcmp(line, "pad") == 0) { /* session 137v: a host pad script (host/null/pad.c) */
            static char pad[160];
            snprintf(pad, sizeof pad, "%s", v);
            kh1_vita_pad_script = pad;
        }
        else if (strcmp(line, "shacc_ext") == 0) kh1_vita_shacc_ext = atoi(v);
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
    sceIoRemove(log); /* session 136: Vita3K's open kept the last run's tail past this run's lines (no truncate) */
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
    kh1_dma_vu1 = 1; /* the 3D (config.txt's vu1=) */
    kh1_vu1_clock = vita_us;
    config(iso, sizeof iso);
    if (!kh1_cd_image_open(iso)) {
        snprintf(iso, sizeof iso, "%s/kh1.bin", kh1_vita_dir);
        if (!kh1_cd_image_open(iso)) no_disc(iso);
    }
    vlog("kh1-vita: disc image %s\n", iso);
    vlog("kh1-vita: vu1=%d (the 3D), vu1tr=%d (its programs as C), pad %s\n", kh1_dma_vu1, kh1_vu1_tr, kh1_vita_pad_script ? kh1_vita_pad_script : "the Vita's controls");
    /* the chain walk feeds the GS memory model (KH1_HOST_TRACE >= 2 on the host); session 135: without
     * its line per send (~7 a frame through the unbuffered log) unless config.txt asks for trace=2 */
    if (kh1_host_trace < 2) {
        kh1_host_trace = 2;
        kh1_dma_quiet = 1;
    }
    /* session 136: the GPU renderer when its shaders can be had: the recorder (host/null/pipes.c) takes each
     * kick and transfer, gxm.c draws each frame's commands, and the model keeps GS memory but draws no
     * pixels for the picture (no flat sprites); else the software picture as before */
    gpu_on = use_gpu && kh1_vita_gxm_init() == 0;
    vlog("kh1-vita: picture: %s\n", gpu_on ? "the GPU (gxm.c)" : "the GS model's, by the CPU");
    if (gpu_on) {
        kh1_pipes_start();
        kh1_gs_prim_hook = timed_prim;
        kh1_pipes_frame_hook = kh1_vita_gxm_frame;
        kh1_vita_present_gpu();
    } else {
        kh1_gsmem_flat(1);  /* the clears, fades and letterbox filled into the model */
        kh1_present_pal(1); /* the indexed decodes through the port's palette cache */
        kh1_present_tex(1); /* the textured sprites through the port's texture cache */
        kh1_vita_present_on();
    }
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
