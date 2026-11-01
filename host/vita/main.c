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
 *       vu1nat=N              session 150: 1 (the default) runs the programs written by hand as C
 *                             (host/port/vu1_nat.h: P0, P4, P10-P13, P18) in place of their translation; 0 the
 *                             translation; 2 runs both and compares them (kh1-vu1 lines, vu1 "checked" counts)
 *       shadertest=1          session 137v: at start, which part of the REGION_REPEAT shader SceShaccCg refuses
 *                             ("kh1-gxm: shadertest" lines; gxm.c)
 *       shacc_restart=1       session 137v: restart the shader compiler when a shader fails (off: hangs Vita3K)
 *       gsq=N                 session 141: 1 (the default) runs the GS side (the GIF decode, the GS model, the
 *                             command recorder) on a worker thread on the second core (host/null/gsqueue.h), with
 *                             the GPU renderer only; 0 keeps it on the game's thread
 *       gpuq=N                session 142: 1 (the default, with gsq=1) runs the frame's GPU work (gxm.c's commands,
 *                             the latch, the present) on a thread of its own on the third core, from a copy of the
 *                             frame (host/null/pipes.c), while the worker records the next; 0 keeps it on the worker
 *       latewait=N            session 145: 0 (the default) skips the vblank wait when a vblank has already begun
 *                             since the last one ended (the frame is late: waiting would only lose time; session
 *                             149: and the frames after it, until they have made up up to 4 lost vblanks); 1 always
 *                             waits for the next vblank, as before
 *       recq=N                session 146: 1 (the default, with gpuq=1) runs the command recorder's work (the draw
 *                             states, the primitives' GPU vertices, the batches and commands) on the GPU frame's
 *                             thread, between its frames, while the GS worker goes on (gsqueue.h's kh1_recq); 0
 *                             keeps it on the worker
 *       recframe=N            2026-10-31: 1 (the default, with recq=1) runs the frame op's passes and the frame's GPU
 *                             work as one more recording op on the GPU frame's thread; the GS worker only copies GS
 *                             memory and the frame's texels for it (host/null/pipes.c kh1_pipes_rq_frame); 0 keeps
 *                             the passes on the worker, as before
 *       gsstrip=N             session 151: 1 (the default, with recq=1) hands the VU1 programs' strips to the recorder
 *                             whole (host/null/gsregs.c's kh1_gs_strip_hook): one op a strip, each vertex turned
 *                             into the GPU's form once; 0 one op a triangle, as before
 *       renderer=native       the native renderer (docs/native-renderer.md): P18's runs (Sora) are not run on the CPU
 *                             but drawn by the GPU's vertex shader from the game's own matrices; anything else (the
 *                             default) keeps the GS path
 *       natcull=N             with renderer=native, the cull mode of P18's back-face-culled runs: 1 (the default)
 *                             CCW in the window, 2 CW, 0 none (if Sora shows his inside, try 2)
 *       natp0=0               with renderer=native, P0 and P4 (the map's strips) on the VU1 programs as before
 *                             (2026-10-31; 1, the default, draws them natively too)
 *       natp11=0              with renderer=native, P11 (renderer B's unlit models with a near-plane cull) on its VU1
 *                             program as before (2026-10-31; 1, the default, draws it natively, the GPU clipping it)
 *       natp10=0              with renderer=native, P10 (the shadow pass's untextured strips) on its VU1 program
 *                             (2026-10-31; 1, the default, draws it natively)
 *       natp13=0              with renderer=native, P13 (renderer B's skinned models) on its VU1 program (2026-10-31;
 *                             1, the default, draws it natively: one-bone vertices transformed by the GPU, the others
 *                             summed on the CPU)
 *       natspan=0             with renderer=native, the GS worker puts each native record to the recording queue as
 *                             its own op (as before 2026-11-01; 1, the default: a payload's records as one op)
 *       natref=0              with renderer=native, a native payload is copied into the GS worker's queue and its
 *                             records again into the recording queue (as before 2026-11-01); 1, the default: the
 *                             payload is written once into a 4 MiB pool and both queues carry only a reference to it
 *       natbulk=0             with natref=1, the GS worker counts each native record in the GS model on its own (1, the
 *                             default: the records between PRIM changes in one count); natref=0 is always per record
 *       hoist=0               keep the game's pass order (2026-10-31; 1, the default: passes that split a scene and
 *                             do not touch it, the Dive's shadow, are drawn ahead of it and its two parts joined)
 *       present=0             copy each picture into a surface of its own and present it every frame (as before
 *                             2026-10-31); 1, the default: each new picture presented once, from the display target
 *       gputime=1             log each 2 s how long the GPU spent on each kind of scene (gxm.c; a polling thread, so
 *                             the frame rate of such a run is a little lower: for the split, not the speed)
 *       rcam=N                1 (the default) a free camera on the right stick, left / right and up / down (host/vita/
 *                             pad.c, fieldcam.c; rcaminv=1 flips up / down); -1 the same with left / right the other
 *                             way; 2 the stick's x only, sent as R2 / L2 (the game's own turn); 0 sends the right
 *                             stick as it is (the PS2's: the command menu's cursor)
 *       snd=N                 1 (the default) plays the game's sound: the disc's own sound driver (LIBSSL.IRX) in
 *                             host/port/iop.c's IOP and spu2.c's SPU2, out through host/vita/audio.c; 0 keeps the
 *                             null server (silence)
 *       sndcore=N             pins the sound's tick thread and mixer to core N (0, 1 or 2); the default, -1, lets
 *                             them run on any core (at sndprio's priority)
 *       sndprio=N             the sound's tick thread and mixer's priority against the game's threads (2026-10-31):
 *                             -4, the default, above them; 16 below them, as before (the sound then breaks up
 *                             when the cores are busy)
 *       wide=N                how the picture fills the 960 x 544 screen (docs/vita-build.md "Wide screen"): 1 (the
 *                             default) a 16:9 view, hor+ (the 3D sees more at the sides, host/port/view.c), the HUD's
 *                             gauges and command menu at the screen's edges, menus and text in the centred 4:3
 *                             canvas; needs the GPU picture (else 2); 2 the 4:3 picture stretched to the whole
 *                             screen; 0 the 4:3 picture in black bars, as before (widescreen=N: the same)
 *       fps=1                 the mod menu's FPS counter (host/vita/menu.c), the pictures a second; 0 (the default)
 *                             off
 *       swapox=1              swaps circle and cross (cross confirms); reartouch=0 turns the rear pad's L2 / R2 /
 *                             L3 / R3 off; volume=N the sound's level, 0-100 (all three: the mod menu's, menu.c)
 *       strip=1               keeps the status strip (the alive square, the read / frame bars) over a full-screen
 *                             picture; by default it shows there only while no picture is
 *   ux0:data/kh1/kh1.log      stdout and stderr
 *
 * Not part of the PS2 build. */
#include <psp2/ctrl.h>
#include <psp2/kernel/cpu.h>
#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/power.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
/* host/vita/audio.c: the sound */
extern int kh1_vita_snd, kh1_vita_snd_core, kh1_vita_snd_prio;
extern u32 kh1_vita_snd_us, kh1_vita_snd_tick_us, kh1_vita_snd_bufs, kh1_vita_snd_under, kh1_vita_snd_queued;
void kh1_vita_audio_init(void);
int kh1_snd_active(void);
extern u32 kh1_snd_ticks, kh1_snd_rpcs, kh1_snd_fifo_full, kh1_iop_insns;
int kh1_spu2_voices_on(void);
#include "platform/ovl.h"
#include "present.h"
#include "gsmem.h"
#include "gsregs.h"
#include "gsqueue.h"
#include "vita.h"
#include "dmawalk.h"
#include "platform/cmdbuf.h"
#include "platform/vu1.h"
#include "platform/costack.h"
#include "platform/view.h"
void kh1_null_hud_wide(s32 margin16); /* host/null/plat_null.c: the HUD anchors, full-screen stretch, scissor rule */

/* newlib's heap and the main thread's stack: the game's coroutine stacks (0x40000 each, host/null
 * threads.c, host/port/tasks.c) and the model's buffers come from the heap; the 25 MiB memory map
 * (host/port/memmap.c) is .bss */
/* both are read by the SDK by name (vita-elf-create's process parameters, newlib's sbrk), never by our
 * code: `used` keeps LTO from dropping them (without it the main thread got the default 256 KiB stack
 * and the app stopped at launch, 2026-10-30) */
__attribute__((used)) int _newlib_heap_size_user = 160 * 1024 * 1024;
/* session 137v: 4 MiB for the main thread's own frames, the rest the coroutines' stacks (platform/costack.h:
 * the kernel refuses a system call made on a stack outside the thread's).  Dive to the Heart makes two
 * (0x40000 each); a 52 MiB stack stopped the app at its start on hardware (C1-2681-7, no log) */
#define MAIN_OWN (4 * 1024 * 1024)
__attribute__((used)) unsigned int sceUserMainThreadStackSize = 8 * 1024 * 1024;
static u32 costack_bytes;

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
static int use_gsq = 1; /* session 141: config.txt's gsq= */
static int use_gpuq = 1; /* session 142: config.txt's gpuq= */
static int late_wait;    /* session 145: config.txt's latewait= */
#define CATCH_UP 4 /* session 149: the vblanks late frames may still make up (kh1_host_vblank) */
static int use_recq = 1; /* session 146: config.txt's recq= */
extern int kh1_pipes_rq_frame, kh1_pipes_gxm_count; /* 2026-10-31: config.txt's recframe= (host/null/pipes.c) */
static int use_gsstrip = 1; /* session 151: config.txt's gsstrip= */
static int use_native;      /* config.txt's renderer=native (docs/native-renderer.md) */
extern int kh1_dma_native, kh1_vita_gxm_native_ok;
extern u32 kh1_pipes_nat_cull, kh1_pipes_nat_draws, kh1_pipes_nat_tris;
extern int kh1_pipes_nat_span; /* pipes.c: config.txt natspan= (2026-11-01) */
extern int kh1_dma_natref, kh1_dma_natbulk; /* dmawalk.c: config.txt natref=, natbulk= (2026-11-01) */
static int wide = 1;      /* config.txt's wide= (0 4:3 pillarboxed, 1 the 16:9 hor+ view, 2 4:3 stretched) */
static int strip_always;  /* config.txt's strip= */
/* session 136: where a GPU frame's CPU time goes (the watchdog's): recording the kicks, the frame's
 * commands (gxm.c's submit included), the present, and the slowest frame (vblank to vblank, its wait left
 * out) of each 2 s */
static volatile u32 us_record, us_frame, us_draw, us_worst;
static SceUID log_fd = -1;

/* the log goes straight to sceIoWrite (a FILE from funopen, unbuffered): newlib's own fopen'd log
 * stayed empty in Vita3K through two runs */
/* session 143: every write to the log is one sceIoWrite, timed (the watchdog's "log:" line) */
static volatile u32 us_log, log_writes;
static void log_out(const void *buf, int n) {
    u32 t0;
    if (log_fd < 0 || n <= 0) return;
    t0 = (u32)sceKernelGetProcessTimeWide();
    sceIoWrite(log_fd, buf, n);
    us_log += (u32)sceKernelGetProcessTimeWide() - t0;
    log_writes++;
}

static int log_write(void *cookie, const char *buf, int n) {
    (void)cookie;
    log_out(buf, n);
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
    log_out(buf, n);
}

/* session 137v: the game's and host/null's printf straight into the log. Pointing newlib's stdout at the
 * log reached neither its global nor its per-thread stream on the Vita (no "kh1-host:" line ever
 * showed), so these take the place of libc's own (gcc turns a bare printf("...\n") into puts) */
int vprintf(const char *fmt, va_list ap) {
    char buf[1024];
    int n = vsnprintf(buf, sizeof buf, fmt, ap);
    if (n > (int)sizeof buf - 1) n = sizeof buf - 1;
    log_out(buf, n);
    return n;
}

int printf(const char *fmt, ...) {
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vprintf(fmt, ap);
    va_end(ap);
    return n;
}

int puts(const char *s) {
    int n = (int)strlen(s);
    log_out(s, n);
    log_out("\n", 1);
    return n + 1;
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
void kh1_pipes_strip(u32 prim, const u32 *d, u32 n, u32 nq);
static void timed_prim(u32 prim, const KH1GsVert *v, u32 n, u32 state) {
    SceUInt64 t0 = sceKernelGetProcessTimeWide();
    kh1_pipes_prim(prim, v, n, state);
    us_record += (u32)(sceKernelGetProcessTimeWide() - t0);
}
extern void (*kh1_pipes_frame_hook)(const KH1CmdRec *r);
void kh1_vita_gxm_frame(const KH1CmdRec *r);
extern void *kh1_vsync_cb; /* sceGsSyncVCallback's handler (host/port/sdk_host.c) */

/* the recorder's hook: the frame's commands (gxm.c), the display target latched when the frame copy made it
 * whole, shown.  Session 142: with gpuq on, on the third core from the frame's copy (host/null/pipes.c), the
 * frame copy's flag passed along with it (kh1_pipes_job_arg) */
extern u32 kh1_pipes_frame_arg, kh1_pipes_job_arg;
extern int kh1_pipes_snap;
extern void (*kh1_pipes_gpu_wait)(void);
extern void (*kh1_pipes_gpu_put)(KH1GsqFn fn, const u32 *args, u32 nargs);
static void vita_frame(const KH1CmdRec *r) {
    SceUInt64 t0 = sceKernelGetProcessTimeWide(), t1;
    kh1_vita_gxm_frame(r);
    /* only a whole picture is shown: the display target as the frame copy left it (the software
     * present's rule); between copies the game may be part-way through the next one */
    if (kh1_pipes_job_arg) {
        kh1_vita_gxm_latch();
        kh1_vita_pictures++; /* the FPS counter's (menu.c) */
    }
    t1 = sceKernelGetProcessTimeWide();
    kh1_vita_draw();
    us_frame += (u32)(t1 - t0);
    us_draw += (u32)(sceKernelGetProcessTimeWide() - t1);
}

static void gpu_frame(int copied) {
    kh1_pipes_frame_arg = (u32)copied;
    kh1_pipes_frame();
}

/* session 141: with the GS side on its worker the frame's commands are its last op of the frame, so the game
 * goes on with the next frame while the worker builds, submits and shows this one.  Every GPU call is then the
 * worker's (gxm.c, vita2d).  Session 145: the vblank waits for the frame op before the last one, not the last:
 * the Dive draws every other frame, and waiting for the last op at the empty frame after a drawn one made the
 * game wait for the worker's whole frame, so the game's next frame and the worker never overlapped */
static void w_gpu_frame(const u32 *a, const u32 *d, u32 n) { gpu_frame((int)a[0]); }
static u32 frame_end[2]; /* the queue's position after the last frame's op [0] and the one before [1] */

/* the mod menu, the game paused: the GS worker, the recorder and the GPU frame's thread finish their queues
 * first, so the menu's options may change the GS side's parameters and the menu draws the last picture itself */
static void menu_pause(void) {
    if (gpu_on && kh1_gsq_on) kh1_gsq_sync();
    if (kh1_recq_on) kh1_recq_sync();
    if (kh1_gpuq_on) kh1_gpuq_wait();
    kh1_vita_menu_run(kh1_vita_draw);
}

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
    if (gpu_on && kh1_gsq_on) { /* session 141: on the worker after the frame's sends */
        u32 copied = (u32)kh1_vita_frame_copied();
        kh1_gsq_wait(frame_end[1]);
        kh1_gsq_put(w_gpu_frame, &copied, 1, 0, 0);
        frame_end[1] = frame_end[0];
        frame_end[0] = kh1_gsq_pos();
        kh1_gsq_flush();
    } else if (gpu_on) /* session 136: the frame's GS draws on the GPU */
        gpu_frame(kh1_vita_frame_copied());
    kh1_vita_status(frames, kh1_host_cd_reads);
    if (kh1_vita_menu_poll()) { /* the mod menu (menu.c): the game waits here until it is closed */
        menu_pause();
        woke = 0; /* the paused time is not made up */
    }
    {
        /* session 145: a frame that ends after the next vblank has begun goes on at once.  Session 149: and so do
         * the frames after it until they have caught up with the vblanks they fell behind (at most CATCH_UP of
         * them): the game's frame is one vblank of its time, so a frame that took four vblanks owes three.  Before,
         * one frame a vblank at most: in the Dive a drawn frame takes ~4 vblanks and the empty frame after it then
         * waited for the next one, ~330 ms per 2 s the game stood still (3d-zp's log) */
        static int vcount; /* the vblank the frames have used up to */
        SceUInt64 t0 = sceKernelGetProcessTimeWide();
        int vc = sceDisplayGetVcount();
        if (woke && (u32)(t0 - woke) > us_worst) us_worst = (u32)(t0 - woke);
        if (late_wait || !woke || vc - vcount <= 0) {
            sceDisplayWaitVblankStart();
            vcount = sceDisplayGetVcount();
        } else if (vc - ++vcount > CATCH_UP) /* the rest of a long stall (a load) is not made up */
            vcount = vc - CATCH_UP;
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
    if (PlatOvlCall(cmd, arg, &ret)) { /* session 132: a native overlay (dktitle.x, host/port/ovl.c) */
        static unsigned shown;
        if (shown++ < 16) /* session 137v: whether the title's entry runs on the Vita */
            vlog("kh1-vita: frame %lu: %s entry (%d, %d) returned %d\n", frames, PlatOvlCurrent(), cmd, arg, ret);
        return ret;
    }
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
int kh1_null_threads_state(char *buf, int n);
extern u32 kh1_dma_walk_us; /* host/null/dmawalk.c */
extern u32 kh1_gs_load_us, kh1_gs_loads, kh1_gs_loads_same, kh1_gs_load_bytes; /* host/null/gsimage.c */
extern u8 D_004E4528[], D_002B75A0[];
extern s32 D_00532B80, D_0063F540, D_004E4520;
extern volatile u32 kh1_vita_sends, kh1_vita_last_send, kh1_vita_shown;
extern volatile u32 kh1_vita_us_gpu, kh1_vita_us_finish, kh1_vita_finishes, kh1_vita_us_part[5];
extern volatile u32 kh1_vita_us_finish_at[4], kh1_vita_finishes_at[4]; /* host/vita/gxm.c, session 147d */
extern volatile u32 kh1_vita_pend_in, kh1_vita_pend_out, kh1_vita_pend_nowait; /* host/vita/gxm.c, session 150 */
extern volatile u32 kh1_vita_scene_waits; /* host/vita/gxm.c, session 151 */
/* native-plan.md stage 0: the port's threads, each one's CPU time per window (the kernel's run clock, so time
 * another thread took from it is not counted), the core it last ran on, and how often it was preempted */
#define KH1_THREADS_MAX 12
static struct { SceUID uid; const char *name; SceUInt64 run; u32 pre; } kh1_threads[KH1_THREADS_MAX];
static int kh1_nthreads;
void kh1_vita_thread_note(int uid, const char *name) {
    if (uid < 0 || kh1_nthreads >= KH1_THREADS_MAX) return;
    kh1_threads[kh1_nthreads].uid = uid;
    kh1_threads[kh1_nthreads++].name = name;
}
static void threads_line(void) {
    char line[640];
    int i, len = snprintf(line, sizeof line, "kh1-vita: threads:");
    for (i = 0; i < kh1_nthreads && len < (int)sizeof line - 80; i++) {
        SceKernelThreadInfo ti;
        SceUInt64 run;
        u32 pre;
        memset(&ti, 0, sizeof ti);
        ti.size = sizeof ti;
        if (sceKernelGetThreadInfo(kh1_threads[i].uid, &ti) < 0) continue;
        run = (SceUInt64)ti.runClocks;
        pre = ti.threadPreemptCount + ti.intrPreemptCount;
        len += snprintf(line + len, sizeof line - len, "%s %s %u ms (core %d, mask %x, prio %x, %u preempted)",
                        i ? "," : "", kh1_threads[i].name, (u32)((run - kh1_threads[i].run) / 1000),
                        (int)ti.lastExecutedCpuId, (u32)ti.currentCpuAffinityMask, (u32)ti.currentPriority,
                        pre - kh1_threads[i].pre);
        kh1_threads[i].run = run;
        kh1_threads[i].pre = pre;
    }
    vlog("%s\n", line);
}

static int watchdog(SceSize args, void *argp) {
    unsigned long last = (unsigned long)-1;
    u32 at0 = (u32)sceKernelGetProcessTimeWide(), walk0 = 0;
    u32 rbusy0 = 0, rwait0 = 0, rwaits0 = 0, ld0[4] = { 0 };
    u32 gbusy0 = 0, gwait0 = 0, gwaits0 = 0, qbusy0 = 0, qwait0 = 0, qwaits0 = 0, qpages0 = 0, log0 = 0, logn0 = 0, bad0 = 0;
    u32 fat0[4] = { 0 }, nfat0[4] = { 0 };
    u32 part0[5] = { 0 }, wait0 = 0, present0 = 0, gpu0 = 0, fin0 = 0, nfin0 = 0, rec0 = 0, frame0 = 0, draw0 = 0, vu0 = 0, kick0 = 0;
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
        if (kh1_snd_active()) { /* the sound threads (host/vita/audio.c): the mixer's share of the 2 s, the driver's work */
            static u32 snd_us0, snd_tick_us0, snd_bufs0, snd_under0, snd_ticks0, snd_insns0;
            vlog("kh1-vita: sound: %u ms ticking, %u ms mixing, %u buffers played (%u short), %u frames queued, %u ticks, "
                 "%u IOP instructions, %d voices on, %u RPCs (%u FIFO full)\n", (kh1_vita_snd_tick_us - snd_tick_us0) / 1000,
                 (kh1_vita_snd_us - snd_us0) / 1000, kh1_vita_snd_bufs - snd_bufs0, kh1_vita_snd_under - snd_under0,
                 kh1_vita_snd_queued,
                 kh1_snd_ticks - snd_ticks0, kh1_iop_insns - snd_insns0, kh1_spu2_voices_on(), kh1_snd_rpcs, kh1_snd_fifo_full);
            snd_us0 = kh1_vita_snd_us;
            snd_tick_us0 = kh1_vita_snd_tick_us;
            snd_bufs0 = kh1_vita_snd_bufs;
            snd_under0 = kh1_vita_snd_under;
            snd_ticks0 = kh1_snd_ticks;
            snd_insns0 = kh1_iop_insns;
        }
        if (frames == last && kh1_gsq_on) { /* session 149: no frame in the window: the queues' state */
            char qb[256];
            kh1_gsq_state(qb, sizeof qb);
            vlog("kh1-vita: stalled: %s\n", qb);
        }
        { /* session 137v: the game's threads (host/null/threads.c): which one a stalled load waits on */
            char tb[192];
            kh1_null_threads_state(tb, sizeof tb);
            vlog("kh1-vita: game threads: %s\n", tb[0] ? tb : "none made");
        }
        { /* session 137v: the disc loader's queue (src/io/discfile.c): each load task's file, its frames to wait
           * and its request's result (-1 until read), the worker's two callback slots, and the gate
           * func_00146878 holds the queue on (the object requests' busy flag, the sound bank transfers left) */
            char lb[512];
            int i, k = 0;
            for (i = 0; i < 16 && k < (int)sizeof lb - 80; i++) {
                const u8 *e = D_004E4528 + i * 0x4C;
                const u8 *r = *(u8 *const *)(e + 72);
                if (!(*(const u16 *)e & 1)) continue;
                k += snprintf(lb + k, sizeof lb - k, " %.24s (wait %d, result %d)", (const char *)e + 16,
                              *(const s32 *)(e + 64), r ? *(const s32 *)(r + 48) : -2);
            }
            vlog("kh1-vita: loads: %d queued so far, object requests busy %d, sound transfers left %d, "
                 "worker slots %s %s;%s\n", D_004E4520, D_00532B80, D_0063F540, *(const u32 *)D_002B75A0 ? "used" : "free",
                 *(const u32 *)(D_002B75A0 + 12) ? "used" : "free", k ? lb : " no load tasks");
        }
        if (gpu_on) { /* session 136: the GPU frame's CPU time (its waits for the GPU included), its counts */
            u32 f, d, sk, sc;
            kh1_vita_gxm_stats(&f, &d, &sk, &sc);
            vlog("kh1-vita: gpu: %u ms submitting (%u ms of it in %u waits for the GPU); %u frames, %u scenes, %u draws, "
                 "%u skipped\n", (kh1_vita_us_gpu - gpu0) / 1000, (kh1_vita_us_finish - fin0) / 1000,
                 kh1_vita_finishes - nfin0, f, sc, d, sk);
            vlog("kh1-vita: gpu parts: %u ms the calls from the commands, %u the vertex copy, %u scenes, %u draws, "
                 "%u transfers\n", (kh1_vita_us_part[0] - part0[0]) / 1000, (kh1_vita_us_part[1] - part0[1]) / 1000,
                 (kh1_vita_us_part[2] - part0[2]) / 1000, (kh1_vita_us_part[3] - part0[3]) / 1000,
                 (kh1_vita_us_part[4] - part0[4]) / 1000);
            vlog("kh1-vita: gpu waits: %u ms at the frame's start (%u), %u for uploads into targets (%u), %u for CLUT "
                 "readbacks (%u), %u for blits (%u)\n", (kh1_vita_us_finish_at[0] - fat0[0]) / 1000,
                 kh1_vita_finishes_at[0] - nfat0[0], (kh1_vita_us_finish_at[1] - fat0[1]) / 1000,
                 kh1_vita_finishes_at[1] - nfat0[1], (kh1_vita_us_finish_at[2] - fat0[2]) / 1000,
                 kh1_vita_finishes_at[2] - nfat0[2], (kh1_vita_us_finish_at[3] - fat0[3]) / 1000,
                 kh1_vita_finishes_at[3] - nfat0[3]);
            { /* session 150: the blocks of uploads into targets that land in a target's pixels, and those outside */
                u32 pin = kh1_vita_pend_in, pout = kh1_vita_pend_out, pnw = kh1_vita_pend_nowait, sw = kh1_vita_scene_waits;
                kh1_vita_pend_in -= pin;
                kh1_vita_pend_out -= pout;
                kh1_vita_pend_nowait -= pnw;
                kh1_vita_scene_waits -= sw;
                vlog("kh1-vita: uploads into targets: %u blocks in a target's pixels, %u outside; %u writes with no wait "
                     "for the GPU; %u waits for one scene (in the gpu waits above)\n", pin, pout, pnw, sw);
            }
            /* the rest of the 2 s (less the vblank wait) is the game and the GS model's chain walk */
            vlog("kh1-vita: cpu: %u ms recording, %u ms the frame's commands (the submit in it), %u ms present; "
                 "slowest frame %u.%u ms\n", (us_record - rec0) / 1000, (us_frame - frame0) / 1000,
                 (us_draw - draw0) / 1000, us_worst / 1000, us_worst / 100 % 10);
            us_worst = 0;
            /* session 137v: of the rest, the VU1 programs (the kicks they hand on included, then alone) */
            vlog("kh1-vita: vu1: %u ms in programs, %u ms of it passing their kicks on\n", (kh1_vu1_us - vu0) / 1000,
                 (kh1_vu1_kick_us - kick0) / 1000);
            { /* session 147: the programs that took the most of it, and their time per instruction pair */
                static u32 p_us[KH1_VU1_PROGS], p_runs[KH1_VU1_PROGS], p_pairs[KH1_VU1_PROGS];
                u32 d[KH1_VU1_PROGS], us, runs, pairs, k;
                int i, num, best;
                char line[512];
                int len = snprintf(line, sizeof line, "kh1-vita: vu1 programs:");
                for (i = 0; i < KH1_VU1_PROGS; i++) d[i] = kh1_vu1_prog_stats(i, &num, &us, &runs, &pairs) ? us - p_us[i] : 0;
                for (k = 0; k < KH1_VU1_PROGS; k++) { /* stage 0: every program over 1 ms */
                    best = -1;
                    for (i = 0; i < KH1_VU1_PROGS; i++)
                        if (d[i] && (best < 0 || d[i] > d[best])) best = i;
                    if (best < 0 || d[best] < 1000) break;
                    kh1_vu1_prog_stats(best, &num, &us, &runs, &pairs);
                    len += snprintf(line + len, sizeof line - len, "%s P%d %u ms (%u runs, %u K pairs, %u ns a pair)",
                                    k ? "," : "", num, d[best] / 1000, runs - p_runs[best], (pairs - p_pairs[best]) >> 10,
                                    pairs - p_pairs[best] ? (u32)((u64)d[best] * 1000 / (pairs - p_pairs[best])) : 0);
                    d[best] = 0;
                }
                vlog("%s\n", line);
                for (i = 0; i < KH1_VU1_PROGS; i++)
                    if (kh1_vu1_prog_stats(i, &num, &us, &runs, &pairs)) { p_us[i] = us; p_runs[i] = runs; p_pairs[i] = pairs; }
            }
            if (kh1_vita_gputime) { /* 2026-10-31: the scenes' GPU time (gxm.c), by target kind */
                static const char *const kn[KH1_GT_KINDS] = { "display", "Z as colour", "movie", "3D target", "slot capture",
                                                              "off-screen", "CLUT pass", "other", "?" };
                static u32 us0[KH1_GT_KINDS], n0[KH1_GT_KINDS], sus0, sn0, polls0;
                char line[512];
                u32 i, all = 0;
                int len;
                for (i = 0; i < KH1_GT_KINDS; i++) all += kh1_vita_gt_us[i] - us0[i];
                len = snprintf(line, sizeof line, "kh1-vita: gpu time: %u ms busy;", all / 1000);
                for (i = 0; i < KH1_GT_KINDS; i++) {
                    if (kh1_vita_gt_n[i] != n0[i])
                        len += snprintf(line + len, sizeof line - len, " %s %u ms (%u scenes),", kn[i],
                                        (kh1_vita_gt_us[i] - us0[i]) / 1000, kh1_vita_gt_n[i] - n0[i]);
                    us0[i] = kh1_vita_gt_us[i];
                    n0[i] = kh1_vita_gt_n[i];
                }
                vlog("%s of them %u ms in %u scenes of 1-2 draws; %u polls\n", line, (kh1_vita_gt_small_us - sus0) / 1000,
                     kh1_vita_gt_small_n - sn0, kh1_vita_gt_polls - polls0);
                sus0 = kh1_vita_gt_small_us;
                sn0 = kh1_vita_gt_small_n;
                polls0 = kh1_vita_gt_polls;
            }
            if (kh1_dma_native) { /* the native renderer (docs/native-renderer.md) */
                static u32 n0, d0, t0, v0, m0, h0, h13, f0, fu0;
                vlog("kh1-vita: native renderer: %u runs drawn by the GPU's transform, %u draws, %u triangles; P13 %u vertices "
                     "(%u summed on the CPU); handing them to the GS worker %u ms (P13's %u ms; the rest of each program's "
                     "time is its parse); %u P13 runs handed back to the program (%u ms)\n", kh1_vu1_drawn - n0, kh1_pipes_nat_draws - d0, kh1_pipes_nat_tris - t0,
                     kh1_vu1_nd13_verts - v0, kh1_vu1_nd13_multi - m0, (kh1_vu1_nd_hand_us - h0) / 1000,
                     (kh1_vu1_nd13_hand_us - h13) / 1000, kh1_vu1_nd13_fail - f0, (kh1_vu1_nd13_fail_us - fu0) / 1000);
                f0 = kh1_vu1_nd13_fail;
                fu0 = kh1_vu1_nd13_fail_us;
                h0 = kh1_vu1_nd_hand_us;
                h13 = kh1_vu1_nd13_hand_us;
                v0 = kh1_vu1_nd13_verts;
                m0 = kh1_vu1_nd13_multi;
                n0 = kh1_vu1_drawn;
                d0 = kh1_pipes_nat_draws;
                t0 = kh1_pipes_nat_tris;
            }
            if (kh1_gsq_on) { /* session 141: the GS side's worker (the recording above is its time now) */
                static u32 pw0, pn0; /* 2026-11-01: natref's pool, its room waited for */
                vlog("kh1-vita: gs worker: %u ms busy; the game waited %u ms for it (%u waits); native payloads %s, "
                     "%u ms waiting for pool room (%u waits)\n",
                     (kh1_gsq_us_busy - gbusy0) / 1000, (kh1_gsq_us_wait - gwait0) / 1000, kh1_gsq_waits - gwaits0,
                     kh1_pool_on && kh1_dma_natref ? kh1_dma_natbulk ? "by reference, counted in bulk (natref=1)"
                                                                     : "by reference (natref=1 natbulk=0)"
                                                   : "copied (natref=0)",
                     (kh1_pool_us_wait - pw0) / 1000, kh1_pool_waits - pn0);
                pw0 = kh1_pool_us_wait;
                pn0 = kh1_pool_waits;
            }
            if (kh1_gpuq_on) /* session 142: the frame's GPU work on the third core (the commands and present above) */
                vlog("kh1-vita: gpu thread: %u ms busy; the GS worker waited %u ms for it (%u waits); %u GS memory pages "
                     "copied\n", (kh1_gpuq_us_busy - qbusy0) / 1000, (kh1_gpuq_us_wait - qwait0) / 1000,
                     kh1_gpuq_waits - qwaits0, kh1_gsmem_snap_pages - qpages0);
            if (kh1_recq_on) /* session 146: the recording on the GPU frame's thread (the `cpu:` line's is then 0) */
                vlog("kh1-vita: recording: %u ms on the gpu thread; the GS worker waited %u ms for it (%u waits)\n",
                     (kh1_recq_us_busy - rbusy0) / 1000, (kh1_recq_us_wait - rwait0) / 1000, kh1_recq_waits - rwaits0);
            if (kh1_gsq_on) { /* session 147b: the worker's busy time by op function (addresses: out/vita/kh1.elf) */
                u32 fn[KH1_GSQ_OPS], us[KH1_GSQ_OPS], nn[KH1_GSQ_OPS];
                char ob[400];
                int i, k = kh1_gsq_ops_take(fn, us, nn), o = 0;
                for (i = 0; i < k && o < (int)sizeof ob - 40; i++)
                    if (us[i] >= 1000) o += snprintf(ob + o, sizeof ob - o, " %08x %u ms (%u),", fn[i], us[i] / 1000, nn[i]);
                vlog("kh1-vita: gs worker ops:%s\n", o ? ob : " none over 1 ms");
                { /* 2026-10-31: the frame op (w_gpu_frame) by part (pipes.c kh1_pipes_frame_us) */
                    extern volatile u32 kh1_pipes_frame_us[7];
                    static u32 pf0[7];
                    u32 d[7], j;
                    for (j = 0; j < 7; j++) {
                        d[j] = kh1_pipes_frame_us[j] - pf0[j];
                        pf0[j] += d[j];
                    }
                    vlog("kh1-vita: gs worker's frame op: %u ms the native flush, %u waiting for the recording, %u the "
                         "passes, %u waiting for the GPU thread, %u the copies for it, %u the rest; %u the passes on the "
                         "GPU thread\n", d[0] / 1000, d[1] / 1000, d[2] / 1000, d[3] / 1000, d[4] / 1000, d[5] / 1000,
                         d[6] / 1000);
                }
            }
            /* session 147: of the rest, the large LoadImages the game thread stores itself (gsimage.c LOAD_HERE) */
            vlog("kh1-vita: large uploads: %u ms on the game thread, %u of them (%u unchanged), %u KiB\n",
                 (kh1_gs_load_us - ld0[0]) / 1000, kh1_gs_loads - ld0[1], kh1_gs_loads_same - ld0[2],
                 (kh1_gs_load_bytes - ld0[3]) >> 10);
            ld0[0] = kh1_gs_load_us;
            ld0[1] = kh1_gs_loads;
            ld0[2] = kh1_gs_loads_same;
            ld0[3] = kh1_gs_load_bytes;
            { /* session 137v: the whole window split: the DMA walks (the VU1 programs and the recording in
               * them), the frame's commands and present, the vblank wait; the rest is the game's own code */
                u32 now = (u32)sceKernelGetProcessTimeWide(), all = now - at0, walk = kh1_dma_walk_us - walk0;
                /* session 141: and the waits for the GS side's worker (at the vblank, LoadImage / StoreImage) */
                u32 gw = kh1_gsq_us_wait - gwait0;
                /* stage 0: a put that waits for room in the ring waits inside a walk, counted in both: once here */
                extern u32 kh1_dma_walk_ring_us;
                static u32 ring0;
                u32 rw = kh1_dma_walk_ring_us - ring0;
                u32 known;
                ring0 = kh1_dma_walk_ring_us;
                if (rw > walk) rw = walk;
                walk -= rw;
                known = walk + (kh1_gsq_on ? 0 : (us_frame - frame0) + (us_draw - draw0)) + (kh1_vita_us_wait - wait0) + gw;
                vlog("kh1-vita: split: %u ms in all, %u in the DMA walks (VU1 and recording in them; not counting %u ms "
                     "waiting for room in the GS worker's ring, which is in the GS worker wait), %u the frame's commands, %u present (with the GS worker: the worker's), %u the vblank wait, %u waiting for the GS worker, %u the rest "
                     "(the game's code)\n", all / 1000, walk / 1000, rw / 1000, (us_frame - frame0) / 1000, (us_draw - draw0) / 1000,
                     (kh1_vita_us_wait - wait0) / 1000, gw / 1000, all > known ? (all - known) / 1000 : 0);
            }
            { /* native-plan.md stage 0: the walks by channel, VIF1's data into VU memory, the ring's copies */
                extern u32 kh1_dma_ch_us[3], kh1_dma_ch_sends[3], kh1_dma_feed_us, kh1_dma_feed_words, kh1_gsq_puts,
                    kh1_gsq_put_bytes_n;
                static u32 cu0[3], cs0[3], fu0, fw0, gp0, gb0;
                vlog("kh1-vita: walk split (ring waits included): VIF0 %u ms (%u sends), VIF1 %u ms (%u sends; VU1 programs and their hand-off "
                     "in the vu1 lines, %u ms feeding %u K words into VU memory), GIF %u ms (%u sends); %u ops, %u KiB "
                     "into the GS worker's ring\n", (kh1_dma_ch_us[0] - cu0[0]) / 1000, kh1_dma_ch_sends[0] - cs0[0],
                     (kh1_dma_ch_us[1] - cu0[1]) / 1000, kh1_dma_ch_sends[1] - cs0[1], (kh1_dma_feed_us - fu0) / 1000,
                     (kh1_dma_feed_words - fw0) >> 10, (kh1_dma_ch_us[2] - cu0[2]) / 1000, kh1_dma_ch_sends[2] - cs0[2],
                     kh1_gsq_puts - gp0, (kh1_gsq_put_bytes_n - gb0) >> 10);
                memcpy(cu0, kh1_dma_ch_us, sizeof cu0);
                memcpy(cs0, kh1_dma_ch_sends, sizeof cs0);
                fu0 = kh1_dma_feed_us;
                fw0 = kh1_dma_feed_words;
                gp0 = kh1_gsq_puts;
                gb0 = kh1_gsq_put_bytes_n;
            }
        }
        /* session 143: the log's own cost (each line an sceIoWrite on the thread that prints it) and the sends
         * with a problem, whose tag lists only the first few print (dmawalk.h) */
        threads_line();
        vlog("kh1-vita: log: %u writes, %u ms in them; %u bad DMA sends (%u so far, the first %d printed)\n",
             log_writes - logn0, (us_log - log0) / 1000, kh1_dma_bad_sends - bad0, kh1_dma_bad_sends, KH1_DMA_BAD_SHOWN);
        log0 = us_log;
        logn0 = log_writes;
        bad0 = kh1_dma_bad_sends;
        at0 = (u32)sceKernelGetProcessTimeWide();
        gbusy0 = kh1_gsq_us_busy;
        qbusy0 = kh1_gpuq_us_busy;
        qwait0 = kh1_gpuq_us_wait;
        qwaits0 = kh1_gpuq_waits;
        rbusy0 = kh1_recq_us_busy;
        rwait0 = kh1_recq_us_wait;
        rwaits0 = kh1_recq_waits;
        qpages0 = kh1_gsmem_snap_pages;
        gwait0 = kh1_gsq_us_wait;
        gwaits0 = kh1_gsq_waits;
        walk0 = kh1_dma_walk_us;
        vu0 = kh1_vu1_us;
        kick0 = kh1_vu1_kick_us;
        rec0 = us_record;
        frame0 = us_frame;
        draw0 = us_draw;
        gpu0 = kh1_vita_us_gpu;
        fin0 = kh1_vita_us_finish;
        memcpy(part0, (const u32 *)kh1_vita_us_part, sizeof part0);
        nfin0 = kh1_vita_finishes;
        memcpy(fat0, (const u32 *)kh1_vita_us_finish_at, sizeof fat0);
        memcpy(nfat0, (const u32 *)kh1_vita_finishes_at, sizeof nfat0);
        wait0 = kh1_vita_us_wait;
        present0 = kh1_vita_us_present;
        last = frames;
    }
    return 0;
}

/* session 140: memory card 1 (host/port/mc_dir.c), ux0:data/kh1/mc0 unless config.txt's mc= names
 * another directory; no card when it does not exist */
static char mc_dir[128];
extern const char *kh1_mc_root[2];

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
        else if (strcmp(line, "vu1nat") == 0) kh1_vu1_native = atoi(v);
        else if (strcmp(line, "gsstrip") == 0) use_gsstrip = atoi(v);
        else if (strcmp(line, "renderer") == 0) use_native = strcmp(v, "native") == 0;
        else if (strcmp(line, "natcull") == 0) kh1_pipes_nat_cull = (u32)atoi(v);
        else if (strcmp(line, "natp0") == 0) kh1_vu1_draw_p0 = atoi(v);
        else if (strcmp(line, "natp11") == 0) kh1_vu1_draw_p11 = atoi(v);
        else if (strcmp(line, "natp10") == 0) kh1_vu1_draw_p10 = atoi(v);
        else if (strcmp(line, "natp13") == 0) kh1_vu1_draw_p13 = atoi(v);
        else if (strcmp(line, "natspan") == 0) kh1_pipes_nat_span = atoi(v);
        else if (strcmp(line, "natref") == 0) kh1_dma_natref = atoi(v);
        else if (strcmp(line, "natbulk") == 0) kh1_dma_natbulk = atoi(v);
        else if (strcmp(line, "hoist") == 0) kh1_cmd_hoist = atoi(v);
        else if (strcmp(line, "gputime") == 0) kh1_vita_gputime = atoi(v);
        else if (strcmp(line, "present") == 0) kh1_vita_present_direct = atoi(v);
        else if (strcmp(line, "pad") == 0) { /* session 137v: a host pad script (host/null/pad.c) */
            static char pad[160];
            snprintf(pad, sizeof pad, "%s", v);
            kh1_vita_pad_script = pad;
        }
        else if (strcmp(line, "shacc_ext") == 0) kh1_vita_shacc_ext = atoi(v);
        else if (strcmp(line, "mc") == 0) snprintf(mc_dir, sizeof mc_dir, "%s", v);
        else if (strcmp(line, "shadertest") == 0) kh1_vita_shadertest = atoi(v);
        else if (strcmp(line, "shacc_restart") == 0) kh1_vita_shacc_restart = atoi(v);
        else if (strcmp(line, "gsq") == 0) use_gsq = atoi(v);
        else if (strcmp(line, "gpuq") == 0) use_gpuq = atoi(v);
        else if (strcmp(line, "latewait") == 0) late_wait = atoi(v);
        else if (strcmp(line, "recq") == 0) use_recq = atoi(v);
        else if (strcmp(line, "recframe") == 0) kh1_pipes_rq_frame = atoi(v);
        else if (strcmp(line, "rcam") == 0) kh1_vita_rcam = atoi(v);
        else if (strcmp(line, "snd") == 0) kh1_vita_snd = atoi(v);
        else if (strcmp(line, "sndcore") == 0) kh1_vita_snd_core = atoi(v);
        else if (strcmp(line, "sndprio") == 0) kh1_vita_snd_prio = atoi(v);
        else if (strcmp(line, "wide") == 0 || strcmp(line, "widescreen") == 0) wide = atoi(v);
        else if (strcmp(line, "strip") == 0) strip_always = atoi(v);
        else kh1_vita_menu_config(line, v); /* the mod menu's own keys (menu.c) */
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
    kh1_vita_thread_note(sceKernelGetThreadId(), "game"); /* native-plan.md stage 0: the `threads:` line */
    { /* the main thread's stack below its own MAIN_OWN: the coroutines' stacks */
        SceKernelThreadInfo ti;
        volatile u8 here;
        memset(&ti, 0, sizeof ti);
        ti.size = sizeof ti;
        if (sceKernelGetThreadInfo(sceKernelGetThreadId(), &ti) >= 0 && ti.stack &&
            (u8 *)&here - (u8 *)ti.stack > MAIN_OWN)
            kh1_costack_pool(ti.stack, costack_bytes = (u32)((u8 *)&here - (u8 *)ti.stack) - MAIN_OWN);
        /* session 147: the DMA walk owns all of it (3d-zk: a chain's data at 0x846a3c30, the main thread's own
         * part, refused) */
        if (ti.stack && ti.stackSize > 0) kh1_costack_stack(ti.stack, (u32)ti.stackSize);
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
    vlog("kh1-vita: %u KiB of the main thread's stack for the game's threads and tasks\n", costack_bytes >> 10);
    /* session 137v (the real Vita's speed): an application starts at 333 MHz; the A9s at 444, the bus and
     * the GPU at 222 as other ports set them (Vita3K takes the calls and runs as fast either way) */
    {
        int arm0 = scePowerGetArmClockFrequency();
        scePowerSetArmClockFrequency(444);
        scePowerSetBusClockFrequency(222);
        scePowerSetGpuClockFrequency(222);
        scePowerSetGpuXbarClockFrequency(166);
        vlog("kh1-vita: clocks: ARM %d MHz (was %d), bus %d, GPU %d, GPU crossbar %d\n", scePowerGetArmClockFrequency(), arm0,
             scePowerGetBusClockFrequency(), scePowerGetGpuClockFrequency(), scePowerGetGpuXbarClockFrequency());
    }
    if (kh1_vita_display_init(D_002A6890)) {
        vlog("kh1-vita: no framebuffer\n");
        sceKernelExitProcess(1);
    }
    snprintf(iso, sizeof iso, "%s/kh1.iso", kh1_vita_dir);
    snprintf(mc_dir, sizeof mc_dir, "%s/mc0", kh1_vita_dir);
    kh1_dma_vu1 = 1; /* the 3D (config.txt's vu1=) */
    kh1_vu1_clock = vita_us;
    config(iso, sizeof iso);
    kh1_mc_root[0] = mc_dir;
    {
        SceIoStat st;
        vlog("kh1-vita: memory card 1: %s (%s)\n", mc_dir, sceIoGetstat(mc_dir, &st) >= 0 ? "found" : "none");
    }
    if (!kh1_cd_image_open(iso)) {
        vlog("kh1-vita: %s: not found or not readable\n", iso);
        snprintf(iso, sizeof iso, "%s/kh1.bin", kh1_vita_dir);
        if (!kh1_cd_image_open(iso)) no_disc(iso);
    }
    { /* session 137v: its size, against the copy on the PC (a short copy stops the loads where it ends) */
        SceIoStat st;
        if (sceIoGetstat(iso, &st) >= 0)
            vlog("kh1-vita: disc image %s, %llu bytes\n", iso, (unsigned long long)st.st_size);
        else
            vlog("kh1-vita: disc image %s\n", iso);
    }
    { /* 2026-11-01: what one read of the clock costs (the VU1 runs, the GS worker's ops and the walks each read it) */
        u32 t0 = vita_us(), i, t1;
        for (i = 0; i < 1000; i++) (void)vita_us();
        t1 = vita_us();
        vlog("kh1-vita: clock: %u ns a read (sceKernelGetProcessTimeWide)\n", t1 - t0);
    }
    vlog("kh1-vita: vu1=%d (the 3D), vu1tr=%d (its programs as C), vu1nat=%d, pad %s\n", kh1_dma_vu1, kh1_vu1_tr, kh1_vu1_native, kh1_vita_pad_script ? kh1_vita_pad_script : "the Vita's controls");
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
    /* the wide screen: the 16:9 view needs the GPU's targets (the GS model's buffers stay the PS2's 512), so without
     * the GPU it falls back to the stretch; set before the game's first frame and the GS worker */
    if (wide == 1 && !gpu_on) wide = 2;
    if (wide == 1) {
        kh1_view_init(960.0f / 544.0f);
        kh1_null_hud_wide(kh1_view_side16);
    }
    kh1_vita_display_mode(wide == 1 || wide == 2 ? wide : 0, strip_always);
    kh1_vita_menu_init(&wide, &late_wait, &use_native, &strip_always, gpu_on);
    vlog("kh1-vita: screen: %s\n", wide == 1 ? "16:9, the wide view (wide=1)" : wide == 2 ? "4:3 stretched to 16:9 (wide=2)"
                                                                               : "4:3 in black bars (wide=0)");
    if (gpu_on) {
        kh1_pipes_start();
        kh1_gs_prim_hook = timed_prim;
        kh1_pipes_frame_hook = vita_frame;
        kh1_pipes_gxm_count = 0; /* gxm.c records the frame's GXM calls itself: no second count on the worker */
        kh1_vita_present_gpu();
        /* session 141: the GS side on the second core, the game (and the VIF1 / VU1 programs) on the first */
        if (use_gsq) {
            int r = kh1_gsq_start(8u << 20);
            if (r == 0) sceKernelChangeThreadCpuAffinityMask(sceKernelGetThreadId(), SCE_KERNEL_CPU_MASK_USER_0);
            /* 2026-11-01: the native payloads' pool (natref=1; dmawalk.c path1_draw), made even when renderer=native
             * is off, so the menu's switch finds it */
            if (r == 0 && kh1_dma_natref && kh1_pool_start(4u << 20)) vlog("kh1-vita: natref: no pool (payloads copied)\n");
            vlog("kh1-vita: GS side: %s\n", r == 0 ? "a worker thread on the second core" : "the game's thread (no worker)");
            /* session 142: the frame's GPU work on the third core, from a copy of the frame */
            if (r == 0 && use_gpuq) {
                kh1_pipes_snap = kh1_gpuq_start() == 0;
                if (kh1_pipes_snap) {
                    kh1_pipes_gpu_wait = kh1_gpuq_wait;
                    kh1_pipes_gpu_put = kh1_gpuq_put;
                }
                vlog("kh1-vita: the frame's GPU work: %s\n", kh1_pipes_snap ? "a thread on the third core" : "the GS worker (no thread)");
                /* session 146: the recording on that thread too (a kick's own time is then not timed: two clock
                 * reads a kick, ~3,000 kicks a drawn frame in the Dive, were a share of the worker's time) */
                if (kh1_pipes_snap && use_recq && kh1_recq_start(2u << 20) == 0) {
                    kh1_gs_prim_hook = kh1_pipes_prim;
                    if (use_gsstrip) kh1_gs_strip_hook = kh1_pipes_strip;
                }
                vlog("kh1-vita: the recording: %s%s%s\n", kh1_recq_on ? "on the GPU frame's thread" : "the GS worker's",
                     kh1_gs_strip_hook ? ", the VU1 strips whole" : "",
                     kh1_recq_on && kh1_pipes_rq_frame ? ", the frame op's passes there too (recframe=1)" : "");
            }
        }
        /* the native renderer: P18's runs transformed by the GPU (its vertex variants compiled in gxm.c) */
        kh1_dma_native = use_native && kh1_vita_gxm_native_ok;
        vlog("kh1-vita: renderer: %s\n", kh1_dma_native ? "native (P18 drawn by the GPU's transform)"
                                         : use_native ? "the GS path (renderer=native asked, its vertex shaders unavailable)"
                                         : "the GS path");
    } else {
        kh1_gsmem_flat(1);  /* the clears, fades and letterbox filled into the model */
        kh1_present_pal(1); /* the indexed decodes through the port's palette cache */
        kh1_present_tex(1); /* the textured sprites through the port's texture cache */
        kh1_vita_present_on();
    }
    {
        /* session 141: on the third core, out of the game's and the GS worker's way */
        SceUID t = sceKernelCreateThread("kh1_watchdog", watchdog, 0x10000100, 0x4000, 0, SCE_KERNEL_CPU_MASK_USER_2, 0);
        if (t >= 0) sceKernelStartThread(t, 0, 0);
        kh1_vita_thread_note(t, "watchdog");
    }
    if (gpu_on && kh1_vita_gputime) { /* 2026-10-31: the scenes' GPU time (gxm.c), a poll on any core above the game's */
        SceUID t = sceKernelCreateThread("kh1_gputime", kh1_vita_gputime_thread, 0x10000100 - 8, 0x2000, 0, 0, 0);
        if (t >= 0) sceKernelStartThread(t, 0, 0);
        vlog("kh1-vita: gputime=1: each scene's GPU time polled (the frame rate is lower for it)\n");
    }
    kh1_vita_audio_init();
    vlog("kh1-vita: func_00100558 (the game's main)\n");
    func_00100558(argc, argv);
    vlog("kh1-vita: func_00100558 returned after %lu frames, %u disc reads, %lu overlay calls\n", frames,
           kh1_host_cd_reads, ovl_calls);
    fflush(stdout);
    sceKernelExitProcess(0);
    return 0;
}
