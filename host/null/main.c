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
 *   KH1_HOST_TRACE=2    also walk every DMA chain a send starts (host/null/plat_null.c):
 *                       one line per send, each tag when the chain leaves host memory;
 *                       3 prints every tag; 4 (not the tags) each GS state value a send
 *                       writes (tools/host/gsstate.py makes the state list of a run); 5 also
 *                       each draw state the send drew in, from the GS register file
 *                       (host/null/gsregs.c, kept across sends) with its kick count, and
 *                       each draw / immediate list node as it starts (plat_null.c, session 83)
 *   KH1_HOST_SND=trace  print each sound command and RPC (host/null/sound.c, session 86; also at
 *                       KH1_HOST_TRACE=6); tools/host/sndlog.py summarises them
 *   KH1_HOST_PAD=FILE   a scripted controller, "FRAME BUTTONS [RX RY LX LY]" lines (host/null/pad.c,
 *                       session 87); without it one pad is connected with nothing pressed, and
 *                       KH1_HOST_PAD=none has no pad (the "no controller" band from frame 32)
 *   KH1_HOST_OVL=stub   a test switch: a call of the overlay entry D_00F20000 returns 0 instead
 *                       of faulting, so the run goes on past it (each call's two arguments are
 *                       printed).  No overlay code runs: what
 *                       the boot does next is the main ELF's own (docs/vita-port-plan.md 5.1h).
 *                       KH1_HOST_OVL=stub:N also asks for game state N at the title's entry call.
 *                       Not under valgrind, which runs the overlay's bytes instead of faulting.
 *   KH1_HOST_WIDE=W:H   (session 91) a hor+ view for a W:H screen (KH1_HOST_WIDE=1: 960:544): the
 *                       culls' frustum and the markers' / objwin's bounds widen (host/port/view.c,
 *                       docs/renderer-spec.md 5.4); the null platform draws nothing, so a run shows
 *                       it only in what the culls let through.  Session 92: the HUD's anchored parts
 *                       (host/port/hudanchor.c) move by the margin in the GIF path, which the chain
 *                       walk's extents show (KH1_HOST_TRACE=5, gsstate.py --extents).  Session 93:
 *                       the static full-screen packets (host/port/fullscreen.c) stretch to the view
 *                       and a full 4:3 SCISSOR (or a 32-pixel column) reads as the view's (a draw
 *                       line's ", view scissor X0 X1", include/platform/canvas.h).
 *   KH1_HOST_SHOT=W:H[:target][:DIR]  (session 94) a "present": after each frame copy (D_002A6890)
 *                       the GS memory model's display (or with "target" the 3D target) as a W x H
 *                       PAM, DIR/shot_N.pam (default "."), through the canvas map, pillarboxed
 *                       (host/null/present.c).  Turns on the chain walk (KH1_HOST_TRACE=2), which
 *                       feeds the model; it holds only what the model can draw (the fake disc's
 *                       frames are black).  From the user's disc: never commit the frames.
 *                       Session 97: with KH1_HOST_WIDE the shot line says what the 512-wide model
 *                       cannot show (the view's sides) and the display shot is read back by the
 *                       stretched copy's margin (host/null/present.c, kh1_present_wide).
 *   KH1_HOST_COUNTS=1   (session 96) the high-water marks of countcheck.py's DATA rows (renderer
 *                       B's lists, the collision candidates, the message pointers, the grid cells,
 *                       the trigger boxes, the windows' message lists), sampled at each vblank, DMA
 *                       send and list end and printed at the end against each array's size
 *                       (host/null/counts.c).  Session 117: also the port's palette cache's hits,
 *                       fills and fills a frame (host/null/present.c; with KH1_HOST_TRACE >= 2 or
 *                       KH1_HOST_SHOT, which feed the GS memory model)
 *
 * A crash prints a backtrace and what the run had read; a fault inside the memory map (a jump
 * into loaded code: the overlay entry D_00F20000 until the overlays build natively) prints the
 * PS2 address and the caller.  Not part of the PS2 build. */
#define _GNU_SOURCE
#include <execinfo.h>
#include <signal.h>
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void func_00100558(int argc, char **argv);
int kh1_cd_image_open(const char *path);
void kh1_view_init(float aspect); /* host/port/view.c */
extern float kh1_view_wide;
extern int kh1_view_side16;
void kh1_null_hud_wide(int margin16); /* host/null/plat_null.c */
int kh1_present_init(int w, int h, int target, const char *dir, const void *send); /* host/null/present.c */
void kh1_present_wide(int side16);
void kh1_present_pal(int on); /* session 117: the palette cache's counts */
void kh1_present_pal_report(void);
extern unsigned char D_002A6890[]; /* brightfade.c's frame copy (renderer-spec 5.4 "Session 93") */

int kh1_host_stop_at_cdread = 1;
int kh1_host_trace;
extern const char *kh1_host_texdump; /* host/null/dmawalk.c */
unsigned int kh1_host_cd_reads, kh1_host_cd_sectors;
static unsigned long frames, max_frames = 600;
static int ovl_stub;
static unsigned long ovl_calls;

unsigned long kh1_host_frame(void) { return frames; }
extern unsigned kh1_gs_list_nodes, kh1_gs_pending_sends, kh1_gs_list_waits; /* host/null/plat_null.c */
extern int kh1_host_dmac_defer;
extern unsigned kh1_snd_commands; /* host/null/sound.c */
extern int kh1_counts_on; /* host/null/counts.c */
void kh1_counts_sample(void);
int kh1_counts_report(void);
static void summary(void) {
    fprintf(stderr, "kh1-host: %lu frames, %u disc reads (%u sectors)\n", frames, kh1_host_cd_reads,
            kh1_host_cd_sectors);
    if (kh1_host_trace >= 5 || kh1_gs_pending_sends || kh1_gs_list_waits)
        fprintf(stderr, "kh1-host: %u draw / immediate list nodes run, %u main-thread GS calls and %u frame-end waits "
                "found the draw list pending%s\n", kh1_gs_list_nodes, kh1_gs_pending_sends, kh1_gs_list_waits,
                kh1_host_dmac_defer ? " (KH1_HOST_DMAC=defer)" : "");
    if (ovl_stub)
        fprintf(stderr, "kh1-host: %lu overlay calls answered 0 (KH1_HOST_OVL=stub)\n", ovl_calls);
    if (kh1_snd_commands)
        fprintf(stderr, "kh1-host: %u sound commands queued (KH1_HOST_SND=trace prints them)\n", kh1_snd_commands);
    fflush(stderr);
    kh1_counts_report();
    kh1_present_pal_report();
    fflush(stdout);
}

/* sceGsSyncVCallback's handler (host/port/sdk_host.c), an INTC handler: int (*)(int cause) */
extern void *kh1_vsync_cb;
void kh1_null_iop_frame(void);
void kh1_host_vblank(void) {
    static int in_vblank;
    if (in_vblank) return;
    in_vblank = 1;
    frames++;
    kh1_counts_sample();
    if (kh1_host_trace >= 5) printf("kh1-host: vblank %lu\n", frames); /* gsstate.py --nodes' frames */
    kh1_null_iop_frame();
    if (kh1_vsync_cb) ((int (*)(int))kh1_vsync_cb)(2);
    in_vblank = 0;
    if (frames >= max_frames) {
        printf("kh1-host: %lu frames: stop\n", frames);
        summary();
        exit(0);
    }
}

/* host/port/memmap.c: the PS2's 0x6A0000 - 0x1FE0000 */
extern unsigned char kh1_memmap[];
#define KH1_MEM_BASE 0x6A0000u
#define KH1_MEM_END 0x1FE0000u
/* the overlay area (host/port/memmap.c's D_00F20000, up to the slots at D_00FE0000) */
#define KH1_OVL_BASE 0xF20000u
#define KH1_OVL_END 0xFE0000u

#if defined(REG_EIP) && defined(REG_ESP)
/* KH1_HOST_OVL=stub[:N]: the fault is the call's first instruction (EIP is the faulting address),
 * so the stack is the call's: the return address on top, the arguments above it.  EIP moves to
 * ovl_entry, a host function with the entry's convention (int (int cmd, int arg), cdecl), which
 * returns 0 to the caller.  With N, the first call of dktitle.x's entry (0xF20000 (0, 0), from
 * func_00109630) also asks for game state N with func_00109558, the request the main ELF's own
 * state changes use (roomload.c, gameover.c): a guess at the title's choice (2 would be a new
 * game: func_00109770's case 2 runs func_00109588 and func_001095b0). */
static int ovl_state = -1;
int func_00109558(int state);
static int ovl_entry(int cmd, int arg) {
    ovl_calls++;
    printf("kh1-host: frame %lu: overlay entry D_00F20000(%d, %d) answered 0\n", frames, cmd, arg);
    if (ovl_state >= 0 && cmd == 0) {
        printf("kh1-host: KH1_HOST_OVL: func_00109558(%d), the title's choice (a guess)\n", ovl_state);
        func_00109558(ovl_state);
        ovl_state = -1;
    }
    return 0;
}
static int ovl_return(siginfo_t *si, void *uc) {
    greg_t *r = ((ucontext_t *)uc)->uc_mcontext.gregs;
    unsigned long a = (unsigned long)si->si_addr - (unsigned long)kh1_memmap + KH1_MEM_BASE;
    if (!ovl_stub || (void *)r[REG_EIP] != si->si_addr || a < KH1_OVL_BASE || a >= KH1_OVL_END)
        return 0;
    /* every call in src/ is to the entry; a fault further in means the bytes ran (valgrind
     * does not keep data from running, so the stub cannot work under it) */
    if (a != KH1_OVL_BASE) {
        fprintf(stderr, "kh1-host: KH1_HOST_OVL=stub: fault at PS2 0x%08lx, past the overlay entry: its bytes ran "
                "(under valgrind?)\n", a);
        return 0;
    }
    r[REG_EIP] = (greg_t)ovl_entry;
    return 1;
}
#else
static int ovl_return(siginfo_t *si, void *uc) {
    (void)si;
    (void)uc;
    return 0;
}
#endif

static void on_crash(int sig, siginfo_t *si, void *uc) {
    void *bt[64];
    int n;
    unsigned long a = (unsigned long)si->si_addr - (unsigned long)kh1_memmap;
    if ((sig == SIGSEGV || sig == SIGILL) && ovl_return(si, uc))
        return;
    fprintf(stderr, "kh1-host: signal %d (%s)\n", sig, strsignal(sig));
    /* executing the memory map: a call into loaded code, an overlay entry such as D_00F20000
     * (docs/vita-port-plan.md 5.2: the overlays need a native build) */
    if ((sig == SIGSEGV || sig == SIGILL) && a < KH1_MEM_END - KH1_MEM_BASE) {
        fprintf(stderr, "kh1-host: fault at PS2 0x%08lx in the memory map (a jump into loaded code?)\n",
                a + KH1_MEM_BASE);
#ifdef REG_ESP
        /* a call's return address is on top of the stack: the caller */
        {
            void *ret = *(void **)((ucontext_t *)uc)->uc_mcontext.gregs[REG_ESP];
            fprintf(stderr, "kh1-host: called from\n");
            backtrace_symbols_fd(&ret, 1, 2);
        }
#endif
    }
    n = backtrace(bt, 64);
    summary();
    backtrace_symbols_fd(bt, n, 2);
    _exit(128 + sig);
}

int main(int argc, char **argv) {
    const char *cd = getenv("KH1_HOST_CD");
    const char *iso = getenv("KH1_HOST_ISO");
    const char *nf = getenv("KH1_HOST_FRAMES");
    setvbuf(stdout, 0, _IONBF, 0);
    {
        static const int sigs[] = { SIGSEGV, SIGBUS, SIGFPE, SIGILL, SIGABRT };
        struct sigaction sa;
        unsigned i;
        memset(&sa, 0, sizeof sa);
        sa.sa_sigaction = on_crash;
        sa.sa_flags = SA_SIGINFO;
        for (i = 0; i < sizeof sigs / sizeof sigs[0]; i++)
            sigaction(sigs[i], &sa, 0);
    }
    if (cd && strcmp(cd, "go") == 0)
        kh1_host_stop_at_cdread = 0;
    if (nf)
        max_frames = strtoul(nf, 0, 0);
    {
        const char *tr = getenv("KH1_HOST_TRACE");
        kh1_host_trace = tr ? (atoi(tr) > 1 ? atoi(tr) : 1) : 0;
        kh1_host_texdump = getenv("KH1_HOST_TEXDUMP"); /* needs KH1_HOST_TRACE >= 2 (the chain walk) */
    }
    {
        const char *counts = getenv("KH1_HOST_COUNTS"); /* session 96: countcheck's DATA rows' marks */
        kh1_counts_on = counts && *counts && strcmp(counts, "0") != 0;
        if (kh1_counts_on) kh1_present_pal(1); /* session 117: fed by the chain walk (KH1_HOST_TRACE >= 2) */
    }
    {
        const char *dmac = getenv("KH1_HOST_DMAC"); /* defer: plat_null.c's replay test (session 84) */
        kh1_host_dmac_defer = dmac && strcmp(dmac, "defer") == 0;
    }
    {
        /* KH1_HOST_WIDE (session 91, renderer-spec 5.4): a hor+ view, W:H (1 = the Vita's 960:544) */
        const char *wide = getenv("KH1_HOST_WIDE");
        if (wide && *wide) {
            const char *c = strchr(wide, ':');
            float aspect = c ? (float)atof(wide) / (float)atof(c + 1) : 960.0f / 544.0f;
            kh1_view_init(aspect);
            printf("kh1-host: wide view x %.4f (canvas x %.4f .. %.4f, margin %d sixteenths)\n", kh1_view_wide,
                   -kh1_view_side16 / 16.0, 512 + kh1_view_side16 / 16.0, kh1_view_side16);
            /* session 92: the HUD's anchored parts move to the wide edges (renderer-spec 5.3.1) */
            kh1_null_hud_wide(kh1_view_side16); /* session 95: the one rounded margin */
        }
    }
    {
        /* KH1_HOST_SHOT=W:H[:target][:DIR] (session 94): the present after each frame copy */
        const char *shot = getenv("KH1_HOST_SHOT");
        if (shot && *shot) {
            const char *c = strchr(shot, ':'), *dir = ".";
            int w = atoi(shot), h = c ? atoi(c + 1) : 0, target = 0;
            c = c ? strchr(c + 1, ':') : 0;
            if (c && strncmp(c + 1, "target", 6) == 0 && (c[7] == 0 || c[7] == ':')) {
                target = 1;
                c = c[7] ? c + 7 : 0;
            }
            if (c && c[1] == ':') c++; /* W:H::DIR, the source left out */
            if (c && c[1]) dir = c + 1;
            if (kh1_present_init(w, h, target, dir, D_002A6890)) {
                fprintf(stderr, "kh1-host: KH1_HOST_SHOT=%s: want W:H[:target][:DIR]\n", shot);
                return 2;
            }
            if (kh1_host_trace < 2) kh1_host_trace = 2;
            if (kh1_view_side16) kh1_present_wide(kh1_view_side16); /* session 97 */
            printf("kh1-host: shot %dx%d of the %s after each frame copy, to %s\n", w, h,
                   target ? "3D target" : "display", dir);
        }
    }
    {
        const char *ovl = getenv("KH1_HOST_OVL");
        ovl_stub = ovl && strncmp(ovl, "stub", 4) == 0 && (ovl[4] == 0 || ovl[4] == ':');
        if (ovl_stub && ovl[4] == ':')
            ovl_state = strtol(ovl + 5, 0, 0);
    }
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
