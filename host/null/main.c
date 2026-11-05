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
 *   KH1_HOST_SND=iop    run the disc's own sound driver (LIBSSL.IRX) instead of the null server
 *                       (host/port/snd.c, docs/sound-spec.md 6); KH1_HOST_SND=wav:FILE also writes what
 *                       it plays, 48 kHz stereo; the summary prints its ticks, RPCs and IOP instructions
 *   KH1_HOST_PAD=FILE   a scripted controller, "FRAME BUTTONS [RX RY LX LY]" lines (host/null/pad.c,
 *                       session 87); without it one pad is connected with nothing pressed, and
 *                       KH1_HOST_PAD=none has no pad (the "no controller" band from frame 32)
 *   KH1_HOST_OVL=stub   a test switch: a call of the overlay entry D_00F20000 returns 0 instead
 *                       of faulting, so the run goes on past it (each call's two arguments are
 *                       printed).  No overlay code runs: what
 *                       the boot does next is the main ELF's own (docs/vita-port-plan.md 5.1h).
 *                       KH1_HOST_OVL=stub:N also asks for game state N at the title's entry call.
 *                       Not under valgrind, which runs the overlay's bytes instead of faulting.
 *                       Session 132: an overlay with native C (dktitle.x: ovl/dktitle/, host/port/ovl.c)
 *                       runs that C when the game calls the entry, with or without the switch; the
 *                       stub answers only the overlays that have none.
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
 *                       KH1_HOST_SHOT, which feed the GS memory model).  Session 118: and the
 *                       texture cache's stamp hits, hash hits, decodes, render targets and the
 *                       texels hashed / decoded a frame (host/port/texcache.c)
 *   KH1_HOST_QUIET=1    (session 135) the chain walk without its "dma ch" line per send, as the Vita
 *                       build runs it (host/null/dmawalk.h kh1_dma_quiet)
 *   KH1_HOST_FORK=N:PAD[,PAD...]  (session 145) at frame N the run forks one child per pad script, which
 *                       goes on with that script (its lines before N are ignored) and writes its output to
 *                       PAD.log and its shots (KH1_HOST_SHOT, if set) to PAD.d/; the children run one after
 *                       another (they share the disc image's file offset) and the parent ends when they have.  Tries inputs from a far frame (a menu after a save
 *                       load) without replaying the way there.  The null platform's state only: no threads
 *                       (KH1_HOST_GSQ, KH1_HOST_GPUQ, KH1_HOST_SND=iop are not forked).  2026-11-04:
 *                       KH1_HOST_FORK_NATGUMMI=A,B,... gives each child its natgummi (KH1_HOST_NATGUMMI), so
 *                       one run to the map serves both sides of a C0 / C1 A / B
 *   KH1_HOST_SHOT_FROM=N  (session 145) KH1_HOST_SHOT set up at frame N instead of the start: the chain walk
 *                       and the GS memory model (most of a shot run's time) stay off until then, so what
 *                       was uploaded before N (fonts, textures) is missing from the shots
 *   KH1_HOST_DUMP=F[,F...]:ADDR:LEN  (session 145) at each frame F, LEN bytes of the memory map from PS2 address
 *                       ADDR (the overlay area and up) into DUMP.F (DUMP = the KH1_HOST_FORK child's pad
 *                       file, or "dump"): diff two runs' dumps to find the variable an input changes
 *   KH1_HOST_MC=DIR     (session 140) a memory card in port 1 (the game's port 0): DIR holds the
 *                       save directories BISLPS-25198-NN/ (host/port/mc_dir.c; tools/host/ps2mc.py
 *                       copies them from an emulator's card).  The game reads and writes them, so
 *                       run on a copy.  Without it no card is in either slot, as before
 *   KH1_HOST_GSQ=1      (session 141) the GS side (the GIF decode, the register file, the GS memory
 *                       model, the recorder) on a worker thread fed by an ordered queue, as the Vita
 *                       runs it (host/null/gsqueue.h); the log is the same as without it.  A power of
 *                       two above 1 is the ring's size in bytes (4 MiB otherwise; small ones test the wrap)
 *   KH1_HOST_GPUQ=1     (session 142) the frame's GPU work (the recorder's hook: tools/vita/gxmcheck.sh's GXM
 *                       stand-in) on a thread of its own from a copy of the frame (host/null/pipes.c), as the
 *                       Vita's third core runs it; 2: the copy without the thread (the same reads, in order)
 *   KH1_HOST_GSQ_CHECK=N  (session 141) the Vita's frame order: the recorder takes each kick and a
 *                       frame's commands end at each vblank, and every N frames a "gsq digest" line
 *                       hashes the register file, all of GS memory and the frame's commands, to
 *                       compare a KH1_HOST_GSQ=1 run (the worker alongside the game) with one without
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
#include "platform/ovl.h"
#include "platform/vu1.h"
#include "platform/cmdbuf.h"
#include "platform/natdraw.h"
#include "platform/texcache.h"
const KH1TexCache *kh1_pipes_texcache_if(void);
#include <time.h>
extern u32 (*kh1_vu1_clock)(void);
extern volatile u32 kh1_pipes_frame_us[7];
static u32 host_us(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (u32)(t.tv_sec * 1000000u + t.tv_nsec / 1000);
}
static void host_clock_report(void) {
    printf("kh1-host: the frame op: %u ms the native flush, %u waiting for the recording, %u the passes, %u waiting "
           "for the GPU thread, %u the copies for it, %u the rest; %u the passes on the GPU thread\n",
           kh1_pipes_frame_us[0] / 1000, kh1_pipes_frame_us[1] / 1000, kh1_pipes_frame_us[2] / 1000,
           kh1_pipes_frame_us[3] / 1000, kh1_pipes_frame_us[4] / 1000, kh1_pipes_frame_us[5] / 1000,
           kh1_pipes_frame_us[6] / 1000);
    { /* 2026-10-31: each VU1 program's time (a native one's parse and hand-off), and the hand-offs' */
        extern int kh1_vu1_prog_stats(int i, int *num, u32 *us, u32 *runs, u32 *pairs);
        extern u32 kh1_vu1_nd_hand_us, kh1_vu1_nd13_hand_us;
        extern u32 kh1_vu1_nd13_fail, kh1_vu1_nd13_fail_us;
        int i, num;
        u32 us, runs, pairs;
        for (i = 0; kh1_vu1_prog_stats(i, &num, &us, &runs, &pairs); i++)
            if (runs) printf("kh1-host: P%d %u ms (%u runs)\n", num, us / 1000, runs);
        printf("kh1-host: native payloads handed to the GS worker: %u ms (P13's %u); %u P13 runs handed back (%u ms)\n",
               kh1_vu1_nd_hand_us / 1000, kh1_vu1_nd13_hand_us / 1000, kh1_vu1_nd13_fail, kh1_vu1_nd13_fail_us / 1000);
        printf("kh1-host: natchain=%d: %u runs read from the chain (%u K qwords never unpacked), %u unpacks written late, "
               "%u payloads differed\n", kh1_vu1_natchain, kh1_vu1_nc_runs, kh1_vu1_nc_qw / 1000, kh1_vu1_nc_flushed,
               kh1_vu1_nc_bad);
    }
    { /* 2026-11-02: natvb's cache (natdraw.h) */
        printf("kh1-host: natvb=%d: %u hits, %u misses, %u entries made, %u whose words changed, %u dropped for room, "
               "%u found no room, %u runs too big, %u hits differed from their parse\n", kh1_natvb, kh1_natvb_hits,
               kh1_natvb_miss, kh1_natvb_made, kh1_natvb_stale, kh1_natvb_evict, kh1_natvb_noroom, kh1_natvb_big,
               kh1_natvb_bad);
        printf("kh1-host: natvbjoin=%d natvbhome=%d: %u cached runs joined into the draw before; not joined: %u after "
               "another command, %u another state, %u a home before the draw's matrices' end, %u no room\n",
               kh1_cmd_natvbjoin, kh1_natvb_home, kh1_cmd_natvb_joins, kh1_cmd_natvb_nojoin[0], kh1_cmd_natvb_nojoin[1],
               kh1_cmd_natvb_nojoin[2], kh1_cmd_natvb_nojoin[3]);
    }
    { /* 2026-11-02: natdirect's payloads (dmawalk.c) */
        extern u32 kh1_dma_nat_direct_n, kh1_dma_nat_mixed_n, kh1_pipes_nat_dir_ends;
        if (kh1_dma_nat_direct_n || kh1_dma_nat_mixed_n)
            printf("kh1-host: natdirect: %u payloads straight to the GPU thread, %u read by the GS worker; %u ops ended by "
                   "the worker\n", kh1_dma_nat_direct_n, kh1_dma_nat_mixed_n, kh1_pipes_nat_dir_ends);
    }
    { /* 2026-11-02: repeated CLUT loads left out (pipes.c on_clut) */
        extern u32 kh1_pipes_clut_n, kh1_pipes_clut_skipped;
        extern int kh1_pipes_clutskip;
        if (kh1_pipes_clut_n)
            printf("kh1-host: clutskip=%d: %u CLUT loads, %u of them repeats left out\n", kh1_pipes_clutskip,
                   kh1_pipes_clut_n, kh1_pipes_clut_skipped);
    }
    { /* 2026-11-02: texture lookups that found the last one's texture (pipes.c tex_lookup, texskip) */
        extern u32 kh1_pipes_tex_n, kh1_pipes_tex_same, kh1_pipes_tex_dec;
        extern int kh1_pipes_texskip;
        if (kh1_pipes_tex_n)
            printf("kh1-host: texskip=%d: %u texture lookups, %u of them the last one's texture, %u decoded\n",
                   kh1_pipes_texskip, kh1_pipes_tex_n, kh1_pipes_tex_same, kh1_pipes_tex_dec);
    }
    { /* 2026-11-03: the recorder's texture cache by how each lookup hit (texcache.c, texver) */
        extern int kh1_pipes_texver;
        u32 kh1_gsmem_sig_lazy(void);
        const KH1TexCache *c = kh1_pipes_texcache_if();
        if (c && c->draws)
            printf("kh1-host: texver=%d: %u cache lookups, %u stamp hits, %u version hits, %u signature hits (%u checked "
                   "wrong), %u raw hits, %u hashed hits, %u decodes, %u targets; %u blocks hashed at a lookup\n",
                   kh1_pipes_texver, c->draws, c->stamp_hits, c->ver_hits, c->sig_hits, c->ver_bad, c->raw_hits,
                   c->hash_hits - c->ver_hits - c->sig_hits - c->raw_hits, c->decodes, c->targets, kh1_gsmem_sig_lazy());
    }
}
#include "gsregs.h"
#include "gsmem.h"
#include "gsqueue.h"
#include "dmawalk.h"
extern u32 kh1_vu1_snap_kicks;
extern unsigned long kh1_vu1_dump_frame;

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
void kh1_present_tex(int on); /* session 118: the texture cache's counts */
void kh1_present_tex_report(void);
extern unsigned char D_002A6890[]; /* brightfade.c's frame copy (renderer-spec 5.4 "Session 93") */

int kh1_host_stop_at_cdread = 1;
int kh1_host_trace;
extern const char *kh1_host_texdump; /* host/null/dmawalk.c */
extern int kh1_dma_quiet;                 /* host/null/dmawalk.c (session 135) */
extern int kh1_dma_vu1;                   /* host/null/dmawalk.c (session 137v): VIF1 / VU1 run */
extern int kh1_dma_native;                /* host/null/dmawalk.c: the native renderer */
extern unsigned kh1_pipes_nat_cull;       /* host/null/pipes.c */
unsigned int kh1_host_cd_reads, kh1_host_cd_sectors;
static unsigned long frames, max_frames = 600;
static int ovl_stub;
static int ovl_state = -1; /* KH1_HOST_OVL=stub:N (also read off x86, where the stub cannot work) */
static unsigned long ovl_calls;

unsigned long kh1_host_frame(void) { return frames; }
extern unsigned kh1_gs_list_nodes, kh1_gs_pending_sends, kh1_gs_list_waits; /* host/null/plat_null.c */
extern int kh1_host_dmac_defer;
extern unsigned kh1_snd_commands; /* host/null/sound.c */
extern unsigned kh1_snd_ticks, kh1_snd_rpcs, kh1_iop_insns; /* host/port/snd.c, iop.c */
void kh1_snd_host_end(void);
extern int kh1_counts_on; /* host/null/counts.c */
void kh1_counts_sample(void);
int kh1_counts_report(void);
/* session 123: the draw states' GPU pipelines (host/null/pipes.c, KH1_HOST_TRACE=5) */
void kh1_pipes_report(void);
extern void (*kh1_dma_draw_state)(); /* host/null/dmawalk.c (a const KH1GsDraw *) */
void kh1_pipes_draw();
/* session 124: the GPU batches a frame takes (host/null/pipes.c, KH1_HOST_TRACE=5) */
void kh1_pipes_prim();
void kh1_pipes_strip(u32 prim, const u32 *d, u32 n, u32 nq); /* session 151 */
void kh1_pipes_start(void);
void kh1_pipes_frame(void);
const KH1CmdRec *kh1_pipes_recorder(void);
static void summary(void) {
    kh1_gsq_sync(); /* session 141: the GS side's worker done */
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
    if (kh1_snd_ticks)
        fprintf(stderr, "kh1-host: sound driver: %u ticks, %u RPCs, %u IOP instructions\n", kh1_snd_ticks, kh1_snd_rpcs,
                kh1_iop_insns);
    kh1_snd_host_end();
    fflush(stderr);
    kh1_counts_report();
    kh1_present_pal_report();
    kh1_present_tex_report();
    kh1_pipes_report();
    fflush(stdout);
}

/* session 137v: KH1_HOST_VU1's counts of the last 300 frames (host/port/vu1.c) */
static void vu1_line(void) {
    KH1Vu1Stats v;
    u32 hi, lo, pc;
    kh1_vu1_stats(&v);
    kh1_vu1_first_unknown(&hi, &lo, &pc);
    printf("kh1-host: vu1 frame %lu: %u runs, %u pairs (%u cycles), %u kicks (%u qwords), %u unpacks (%u filled), "
           "%u programs loaded, %u runaway, %u unknown", frames, v.runs, v.insns, v.cycles, v.kicks, v.kick_qw,
           v.unpacks, v.fill, v.mpg, v.runaway, v.unknown);
    if (v.tr_runs || v.tr_checked) printf(", %u translated, %u checked (%u differ)", v.tr_runs, v.tr_checked, v.tr_differ);
    if (hi || lo) printf(" (first %08x %08x at %03x)", hi, lo, pc);
    printf("\n");
}

/* session 137v: KH1_HOST_PROF=F:N, under `valgrind --tool=callgrind --instr-atstart=no`, measures
 * frames F to F+N only (the Vita's speed work: where a 3D frame's CPU time goes) */
#if defined(__has_include)
#if __has_include(<valgrind/callgrind.h>)
#include <valgrind/callgrind.h>
#endif
#endif
static void prof_frame(void) {
#ifdef CALLGRIND_START_INSTRUMENTATION
    static long from = -2, n;
    if (from == -2) {
        const char *p = getenv("KH1_HOST_PROF");
        from = p ? atol(p) : -1;
        n = p && strchr(p, ':') ? atol(strchr(p, ':') + 1) : 60;
    }
    if (from < 0) return;
    if ((long)frames == from) CALLGRIND_START_INSTRUMENTATION;
    if ((long)frames == from + n) {
        CALLGRIND_STOP_INSTRUMENTATION;
        CALLGRIND_DUMP_STATS;
    }
#endif
}

/* session 141: KH1_HOST_GSQ_CHECK=N, the Vita's frame order (host/vita/main.c): the frame's commands end at
 * each vblank once the GS side's worker is done, and every N frames a digest of what the GS side holds */
static unsigned long gsq_check;
static int gs_strip = 1; /* session 151: KH1_HOST_GSSTRIP */
static u32 gsq_mem[1024 * 1024];
static u32 fnv(u32 h, const void *p, u32 n) {
    const u8 *b = (const u8 *)p;
    while (n--) h = (h ^ *b++) * 16777619u;
    return h;
}
static void gsq_frame(unsigned long frame) {
    const KH1CmdRec *r = kh1_pipes_recorder();
    u32 ncmd = r->ncmd, npass = r->npass, h;
    kh1_pipes_frame();
    if (frame % gsq_check) return;
    h = fnv(2166136261u, kh1_gs_state(), sizeof(KH1GsState));
    h = fnv(h, kh1_gsmem_stats(), sizeof(KH1GsMemStats));
    kh1_gsmem_read_rect(KH1_PSMCT32, 0, 16, 0, 0, 1024, 1024, gsq_mem, 1024); /* all 4 MB */
    printf("kh1-host: gsq digest frame %lu: state %08x, memory %08x, %u commands in %u passes\n", frame, h,
           fnv(2166136261u, gsq_mem, sizeof gsq_mem), ncmd, npass);
}
/* with the worker: the frame's op after its sends, the vblank waiting for the op before the last (host/vita/main.c's
 * order, session 145) */
static void w_gsq_frame(const u32 *a, const u32 *d, u32 n) { gsq_frame(a[0]); }
static u32 gsq_frame_end[2];

/* sceGsSyncVCallback's handler (host/port/sdk_host.c), an INTC handler: int (*)(int cause) */
extern void *kh1_vsync_cb;
void kh1_null_iop_frame(void);
void kh1_snd_frame(void); /* host/port/snd.c: the sound driver's four ticks a frame */
void kh1_snd_host_end(void);
int kh1_snd_host_init(void);
extern int kh1_snd_wanted;
/* 2026-11-02: KH1_HOST_SENDERS=FROM:TO prints the GS worker's blocks by sender over frames FROM to TO (dmawalk.h
 * kh1_dma_senders_take; KH1_HOST_CLOCK=1 for the times); addr2line -f -e the binary names each address */
static unsigned long snd_from, snd_to;
static int snd_cmp(const void *a, const void *b) {
    const KH1DmaSender *x = a, *y = b;
    return x->us != y->us ? (x->us < y->us ? 1 : -1) : x->qw < y->qw ? 1 : x->qw > y->qw ? -1 : 0;
}
static void snd_report(void) {
    KH1DmaSender t[KH1_DMA_SENDERS];
    int n, i;
    kh1_gsq_sync();
    n = kh1_dma_senders_take(t, KH1_DMA_SENDERS);
    if (frames == snd_from) return;
    qsort(t, n, sizeof t[0], snd_cmp);
    printf("kh1-host: gs senders, frames %lu-%lu: %d\n", snd_from, snd_to, n);
    for (i = 0; i < n; i++)
        printf("kh1-host: sender %08x: %u us, %u blocks, %u qwords: %u tags, %u packed, %u A+D, %u reglist, %u image\n",
               t[i].who, t[i].us, t[i].blocks, t[i].qw, t[i].tags, t[i].pk, t[i].ad, t[i].rl, t[i].img);
}
/* KH1_HOST_SHOT's set-up: at the start, or (KH1_HOST_SHOT_FROM=N, session 145) at frame N, with the chain
 * walk and the GS memory model off until then: much faster, but the model holds only what is sent from N
 * on (a texture uploaded before is missing from the shots) */
static int shot_setup(void) {
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
    return 0;
}
static unsigned long shot_from;
#include <sys/stat.h>
#include <sys/wait.h>
int kh1_null_pad_reload(const char *path);
void kh1_present_dir(const char *dir);
static unsigned long fork_frame;
static char *fork_pads;
static const char *dump_prefix = "dump";
/* KH1_HOST_DUMP=F[,F...]:ADDR:LEN */
extern unsigned char kh1_memmap[];
static void dump_frame(void) {
    static const char *spec;
    static int init;
    const char *s;
    unsigned long f, addr, len;
    char *e;
    if (!init) {
        init = 1;
        spec = getenv("KH1_HOST_DUMP");
    }
    if (!spec) return;
    for (s = spec;;) {
        f = strtoul(s, &e, 0);
        if (f == frames) break;
        if (*e != ',') return;
        s = e + 1;
    }
    s = strchr(spec, ':');
    if (!s) return;
    addr = strtoul(s + 1, &e, 0);
    len = *e == ':' ? strtoul(e + 1, 0, 0) : 0;
    if (addr < 0x6A0000u || addr + len > 0x2000000u) return; /* the memory map (KH1_MEM_BASE, KH1_MEM_END below) */
    {
        char path[512];
        FILE *o;
        snprintf(path, sizeof path, "%s.%lu", dump_prefix, frames);
        o = fopen(path, "wb");
        if (o) {
            fwrite(kh1_memmap + addr - 0x6A0000u, 1, len, o);
            fclose(o);
        }
    }
}
/* KH1_HOST_FORK: returns in each child; the parent waits for them and exits */
static void fork_runs(void) {
    static char dir[512], log[512];
    char *p = fork_pads, *e;
    const char *ng = getenv("KH1_HOST_FORK_NATGUMMI");
    int running = 0, st, idx = 0;
    fflush(stdout);
    fflush(stderr);
    for (; p && *p; p = e ? e + 1 : 0, idx++) {
        pid_t pid;
        e = strchr(p, ',');
        if (e) *e = 0;
        /* one at a time: the children share the disc image's open file and its offset */
        if (running == 1 && wait(&st) > 0) running--;
        pid = fork();
        if (pid == 0) {
            snprintf(log, sizeof log, "%s.log", p);
            snprintf(dir, sizeof dir, "%s.d", p);
            mkdir(dir, 0755);
            if (!freopen(log, "w", stdout) || !freopen(log, "a", stderr)) _exit(3);
            setvbuf(stdout, 0, _IOLBF, 0);
            setvbuf(stderr, 0, _IONBF, 0);
            kh1_present_dir(dir);
            if (getenv("KH1_HOST_GXM_PPM")) setenv("KH1_HOST_GXM_PPM", dir, 1); /* gxmcheck's pictures there too */
            dump_prefix = p;
            if (ng) { /* 2026-11-04: KH1_HOST_FORK_NATGUMMI=A,B,...: child i's natgummi (an A / B from one shared run) */
                const char *v = ng;
                int k;
                for (k = 0; k < idx && v; k++) v = strchr(v, ',') ? strchr(v, ',') + 1 : 0;
                if (v) kh1_vu1_draw_gum = atoi(v);
            }
            if (kh1_null_pad_reload(p) < 0) _exit(2);
            printf("kh1-host: KH1_HOST_FORK: frame %lu, pad %s, natgummi %d\n", frames, p, kh1_vu1_draw_gum);
            return;
        }
        if (pid > 0) running++;
        else perror("kh1-host: fork");
    }
    while (wait(&st) > 0) {}
    fprintf(stderr, "kh1-host: KH1_HOST_FORK: every run done\n");
    _exit(0);
}

void kh1_host_vblank(void) {
    static int in_vblank;
    if (in_vblank) return;
    in_vblank = 1;
    frames++;
    if (fork_frame && frames == fork_frame) fork_runs();
    if (shot_from && frames == shot_from && shot_setup()) exit(2);
    dump_frame();
    kh1_counts_sample();
    if (kh1_host_trace >= 5) printf("kh1-host: vblank %lu\n", frames); /* gsstate.py --nodes' frames */
    if (kh1_dma_vu1 && frames % 300 == 0) vu1_line();
    if (snd_to && (frames == snd_from || frames == snd_to)) snd_report();
    if (kh1_host_trace >= 5) {
        kh1_gsq_sync(); /* session 141: the GS side's worker done with the frame's sends (gsqueue.h) */
        kh1_pipes_frame(); /* session 124: the frame's batches */
    } else if (gsq_check && kh1_gsq_on) {
        u32 f = (u32)frames;
        kh1_gsq_wait(gsq_frame_end[1]);
        kh1_gsq_put(w_gsq_frame, &f, 1, 0, 0);
        gsq_frame_end[1] = gsq_frame_end[0];
        gsq_frame_end[0] = kh1_gsq_pos();
        kh1_gsq_flush();
    } else if (gsq_check)
        gsq_frame(frames);
    prof_frame();
    kh1_null_iop_frame();
    kh1_snd_frame();
    if (kh1_vsync_cb) ((int (*)(int))kh1_vsync_cb)(2);
    in_vblank = 0;
    if (frames >= max_frames) {
        kh1_gsq_sync();
        kh1_gpuq_wait(); /* session 142: the last frame's GPU work done */
        printf("kh1-host: %lu frames: stop\n", frames);
        summary();
        exit(0);
    }
}

/* host/port/memmap.c: the PS2's 0x6A0000 - 0x2000000 */
extern unsigned char kh1_memmap[];
#define KH1_MEM_BASE 0x6A0000u
#define KH1_MEM_END 0x2000000u
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
int func_00109558(int state);
static int ovl_entry(int cmd, int arg) {
    int ret;
    if (PlatOvlCall(cmd, arg, &ret)) /* a native overlay (host/port/ovl.c) */
        return ret;
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
    /* the faulting pc, not si_addr: under Rosetta (an x86 container on an Apple silicon Mac) a
     * jump into non-executable memory reports another si_addr, while the pc is the entry */
    unsigned long a = (unsigned long)r[REG_EIP] - (unsigned long)kh1_memmap + KH1_MEM_BASE;
    (void)si;
    if (!(ovl_stub || PlatOvlCurrent()) || a < KH1_OVL_BASE || a >= KH1_OVL_END)
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
#if defined(REG_EIP) && defined(REG_ESP)
    /* session 145: the faulting pc and stack, before the backtrace (which faults itself on a broken stack) */
    fprintf(stderr, "kh1-host: pc %p, sp %p, address %p\n", (void *)((ucontext_t *)uc)->uc_mcontext.gregs[REG_EIP],
            (void *)((ucontext_t *)uc)->uc_mcontext.gregs[REG_ESP], si->si_addr);
#endif
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
    if (getenv("KH1_HOST_SHOT_FROM")) shot_from = strtoul(getenv("KH1_HOST_SHOT_FROM"), 0, 0);
    if (getenv("KH1_HOST_FORK")) { /* N:PAD[,PAD...] */
        char *c;
        fork_frame = strtoul(getenv("KH1_HOST_FORK"), &c, 0);
        fork_pads = *c == ':' ? strdup(c + 1) : 0;
        if (!fork_pads) fork_frame = 0;
    }
    setvbuf(stdout, 0, _IONBF, 0);
    {
        static const int sigs[] = { SIGSEGV, SIGBUS, SIGFPE, SIGILL, SIGABRT };
        struct sigaction sa;
        unsigned i;
        static char alt[65536];
        stack_t ss;
        /* session 145: the handler on a stack of its own, so a stack overflow is reported too */
        ss.ss_sp = alt;
        ss.ss_size = sizeof alt;
        ss.ss_flags = 0;
        sigaltstack(&ss, 0);
        memset(&sa, 0, sizeof sa);
        sa.sa_sigaction = on_crash;
        sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
        for (i = 0; i < sizeof sigs / sizeof sigs[0]; i++)
            sigaction(sigs[i], &sa, 0);
    }
    if (cd && strcmp(cd, "go") == 0)
        kh1_host_stop_at_cdread = 0;
    kh1_snd_wanted = kh1_snd_host_init();
    if (nf)
        max_frames = strtoul(nf, 0, 0);
    {
        const char *tr = getenv("KH1_HOST_TRACE");
        kh1_host_trace = tr ? (atoi(tr) > 1 ? atoi(tr) : 1) : 0;
        kh1_host_texdump = getenv("KH1_HOST_TEXDUMP"); /* needs KH1_HOST_TRACE >= 2 (the chain walk) */
        kh1_dma_quiet = getenv("KH1_HOST_QUIET") != 0; /* session 135: no send lines, as on the Vita */
        if (getenv("KH1_HOST_T4BAND")) kh1_gsmem_t4band = atoi(getenv("KH1_HOST_T4BAND")); /* 2026-11-04: config t4band= */
        kh1_dma_vu1 = getenv("KH1_HOST_VU1") && atoi(getenv("KH1_HOST_VU1")); /* session 137v: the 3D */
        kh1_vu1_verbose = kh1_dma_vu1 ? atoi(getenv("KH1_HOST_VU1")) - 1 : 0;
        if (getenv("KH1_HOST_VU1TR")) kh1_vu1_tr = atoi(getenv("KH1_HOST_VU1TR")); /* 0 / 1 / 2: checked */
        if (getenv("KH1_HOST_VU1NAT")) kh1_vu1_native = atoi(getenv("KH1_HOST_VU1NAT")); /* session 150: vu1_nat.h */
        if (getenv("KH1_HOST_VU1DUMP")) { /* DIR:N, host/port/vu1.c's dump_run */
            static char dir[200];
            char *c;
            snprintf(dir, sizeof dir, "%s", getenv("KH1_HOST_VU1DUMP"));
            c = strrchr(dir, ':');
            kh1_vu1_dump_every = c ? strtoul(c + 1, 0, 0) : 1000;
            if (c) *c = 0;
            kh1_vu1_dump_dir = dir;
        }
        if (getenv("KH1_HOST_VU1_SNAP")) kh1_vu1_snap_run = strtoul(getenv("KH1_HOST_VU1_SNAP"), 0, 0);
        if (getenv("KH1_HOST_VU1_FRAME")) kh1_vu1_dump_frame = strtoul(getenv("KH1_HOST_VU1_FRAME"), 0, 0);
        if (getenv("KH1_HOST_VU1_SNAPK")) kh1_vu1_snap_kicks = strtoul(getenv("KH1_HOST_VU1_SNAPK"), 0, 0);
        if (kh1_host_trace >= 5) kh1_dma_draw_state = kh1_pipes_draw; /* session 123: the GPU pipelines */
        if (kh1_host_trace >= 5) kh1_gs_prim_hook = kh1_pipes_prim; /* session 124: the batches */
        /* session 151: the VU1 strips handed on whole (KH1_HOST_GSSTRIP=0: a triangle a call, as before) */
        if (getenv("KH1_HOST_GSSTRIP")) gs_strip = atoi(getenv("KH1_HOST_GSSTRIP"));
        if (kh1_host_trace >= 5 && gs_strip) kh1_gs_strip_hook = kh1_pipes_strip;
        if (kh1_host_trace >= 5) kh1_pipes_start(); /* session 127: the recorder sees the first transfers */
        /* the native renderer (docs/native-renderer.md): P18's runs drawn by the GPU's transform, not the VU1 program
         * (the recorder's, so trace 5; KH1_HOST_NATCULL=0 / 1 / 2 the cull mode: none, CCW, CW) */
        if (kh1_host_trace >= 5 && getenv("KH1_HOST_NATIVE")) kh1_dma_native = atoi(getenv("KH1_HOST_NATIVE"));
        if (getenv("KH1_HOST_NATCULL")) kh1_pipes_nat_cull = (u32)atoi(getenv("KH1_HOST_NATCULL"));
        if (getenv("KH1_HOST_NATCHECK")) kh1_vu1_natcheck = atoi(getenv("KH1_HOST_NATCHECK")); /* vu1_draw.h */
        if (getenv("KH1_HOST_NATP0")) kh1_vu1_draw_p0 = atoi(getenv("KH1_HOST_NATP0")); /* 2026-10-31: 0 P0 / P4 on the VU */
        if (getenv("KH1_HOST_NATGUMMI")) kh1_vu1_draw_gum = atoi(getenv("KH1_HOST_NATGUMMI")); /* 2026-11-04: 0 C0 / C1 on the VU */
        if (getenv("KH1_HOST_NATP11")) kh1_vu1_draw_p11 = atoi(getenv("KH1_HOST_NATP11")); /* 2026-10-31: 0 P11 on the VU */
        if (getenv("KH1_HOST_NATP13")) kh1_vu1_draw_p13 = atoi(getenv("KH1_HOST_NATP13")); /* 2026-10-31: 0 P13 on the VU */
        if (getenv("KH1_HOST_NATSKIN")) kh1_vu1_nat_skin = atoi(getenv("KH1_HOST_NATSKIN")); /* 2026-11-01: 0 the CPU's sums */
        if (getenv("KH1_HOST_NATCHAIN")) kh1_vu1_natchain = atoi(getenv("KH1_HOST_NATCHAIN")); /* 2026-11-01: 0 the old path */
        if (getenv("KH1_HOST_NATVB")) kh1_natvb = atoi(getenv("KH1_HOST_NATVB")); /* 2026-11-02: natdraw.h natvb */
        if (kh1_natvb && !kh1_natvb_mem) { /* the host's stand-in for GPU memory (gxm.c gives its own) */
            u32 mb = getenv("KH1_HOST_NATVBMB") ? (u32)atoi(getenv("KH1_HOST_NATVBMB")) : 16;
            kh1_natvb_bytes = mb << 20;
            kh1_natvb_mem = (u8 *)malloc(kh1_natvb_bytes);
            if (!kh1_natvb_mem) kh1_natvb = 0;
        }
        if (getenv("KH1_HOST_NATP10")) kh1_vu1_draw_p10 = atoi(getenv("KH1_HOST_NATP10")); /* 2026-10-31: 0 P10 on the VU */
        if (getenv("KH1_HOST_RECFRAME")) { /* 2026-10-31: pipes.c's frame op on the GPU thread (the Vita's recframe=) */
            extern int kh1_pipes_rq_frame;
            kh1_pipes_rq_frame = atoi(getenv("KH1_HOST_RECFRAME"));
        }
        if (getenv("KH1_HOST_NATSPAN")) { /* 2026-11-01: 0 each native record its own recording op (pipes.c) */
            extern int kh1_pipes_nat_span;
            kh1_pipes_nat_span = atoi(getenv("KH1_HOST_NATSPAN"));
        }
        if (getenv("KH1_HOST_NATINPLACE")) { /* 2026-11-04: 0 r_nat_dir copies the records into nat_op (pipes.c) */
            extern int kh1_pipes_nat_inplace;
            kh1_pipes_nat_inplace = atoi(getenv("KH1_HOST_NATINPLACE"));
        }
        if (getenv("KH1_HOST_NATPF")) kh1_nat_prefetch = atoi(getenv("KH1_HOST_NATPF")); /* 2026-11-04: natdraw.c */
        if (getenv("KH1_HOST_NATJOIN")) kh1_cmd_natjoin = atoi(getenv("KH1_HOST_NATJOIN")); /* 2026-11-01: cmdbuf.c nat_join */
        if (getenv("KH1_HOST_NATVBJOIN")) kh1_cmd_natvbjoin = atoi(getenv("KH1_HOST_NATVBJOIN")); /* 2026-11-02: vb_join */
        if (getenv("KH1_HOST_NATVBBULK")) kh1_cmd_natvbbulk = atoi(getenv("KH1_HOST_NATVBBULK")); /* 2026-11-03 */
        if (getenv("KH1_HOST_NATVBHOME")) kh1_natvb_home = atoi(getenv("KH1_HOST_NATVBHOME")); /* 2026-11-02: natdraw.c */
        if (getenv("KH1_HOST_HOIST")) kh1_cmd_hoist = atoi(getenv("KH1_HOST_HOIST")); /* 2026-10-31: cmdbuf.c hoist */
        if (getenv("KH1_HOST_RECFAST")) { /* 2026-11-01: 0 the GPU thread's recording as before (natdraw.c, cmdbuf.c) */
            extern int kh1_nat_once;
            kh1_cmd_fastrot = kh1_nat_once = atoi(getenv("KH1_HOST_RECFAST"));
        }
        if (getenv("KH1_HOST_SENDERS")) { /* 2026-11-02: FROM:TO, the GS worker's blocks by sender (snd_report) */
            char *e;
            snd_from = strtoul(getenv("KH1_HOST_SENDERS"), &e, 0);
            snd_to = *e == ':' ? strtoul(e + 1, 0, 0) : snd_from + 300;
        }
        if (getenv("KH1_HOST_CLOCK")) { /* 2026-10-31: kh1_vu1_clock on the host (the frame op's parts at the end) */
            kh1_vu1_clock = host_us;
            atexit(host_clock_report);
        }
        if (getenv("KH1_HOST_GSQ_CHECK") && kh1_host_trace >= 2 && kh1_host_trace < 5) {
            gsq_check = strtoul(getenv("KH1_HOST_GSQ_CHECK"), 0, 0);
            if (gsq_check) {
                kh1_gs_prim_hook = kh1_pipes_prim;
                if (gs_strip) kh1_gs_strip_hook = kh1_pipes_strip;
                kh1_pipes_start();
            }
        }
        if (getenv("KH1_HOST_GPUQ") && atoi(getenv("KH1_HOST_GPUQ"))) { /* session 142: the frame's copy, its thread */
            extern int kh1_pipes_snap;
            extern void (*kh1_pipes_gpu_wait)(void);
            extern void (*kh1_pipes_gpu_put)(KH1GsqFn fn, const u32 *args, u32 nargs);
            kh1_pipes_snap = 1;
            if (atoi(getenv("KH1_HOST_GPUQ")) == 1) {
                if (kh1_gpuq_start()) {
                    printf("kh1-host: KH1_HOST_GPUQ: no thread\n");
                } else {
                    kh1_pipes_gpu_wait = kh1_gpuq_wait;
                    kh1_pipes_gpu_put = kh1_gpuq_put;
                    /* session 146: KH1_HOST_RECQ=1, the recorder's work on that thread too (the Vita's recq=1) */
                    if (getenv("KH1_HOST_RECQ") && atoi(getenv("KH1_HOST_RECQ")) && kh1_recq_start(2u << 20))
                        printf("kh1-host: KH1_HOST_RECQ: no queue\n");
                }
            }
        }
        if (getenv("KH1_HOST_GSQ") && atoi(getenv("KH1_HOST_GSQ")) && /* a power of two > 1: the ring's bytes */
            kh1_gsq_start(atoi(getenv("KH1_HOST_GSQ")) > 1 ? (u32)atoi(getenv("KH1_HOST_GSQ")) : 4u << 20))
            printf("kh1-host: KH1_HOST_GSQ: no worker thread\n");
        else if (kh1_gsq_on) { /* 2026-11-01: KH1_HOST_NATREF=0 copies native payloads (the Vita's natref=) */
            extern int kh1_dma_natref;
            extern int kh1_dma_natbulk;
            if (getenv("KH1_HOST_NATREF")) kh1_dma_natref = atoi(getenv("KH1_HOST_NATREF"));
            if (getenv("KH1_HOST_NATBULK")) kh1_dma_natbulk = atoi(getenv("KH1_HOST_NATBULK"));
            { /* 2026-11-02: KH1_HOST_NATDIRECT=0 has the GS worker read every pooled payload (the Vita's natdirect=) */
                extern int kh1_dma_natdirect;
                if (getenv("KH1_HOST_NATDIRECT")) kh1_dma_natdirect = atoi(getenv("KH1_HOST_NATDIRECT"));
            }
            { /* 2026-11-02: KH1_HOST_CLUTSKIP=0 sends every CLUT load to the recorder (pipes.c on_clut; the Vita's clutskip=) */
                extern int kh1_pipes_clutskip;
                if (getenv("KH1_HOST_CLUTSKIP")) kh1_pipes_clutskip = atoi(getenv("KH1_HOST_CLUTSKIP"));
            }
            { /* 2026-11-03: KH1_HOST_TEXVER=0 checks a stamp miss's pages by their words (texcache.c; the Vita's texver=) */
                extern int kh1_pipes_texver;
                if (getenv("KH1_HOST_TEXVER")) kh1_pipes_texver = atoi(getenv("KH1_HOST_TEXVER"));
            }
            { /* 2026-11-02: KH1_HOST_TEXSKIP=0 looks every texture up again (pipes.c tex_lookup; the Vita's texskip=) */
                extern int kh1_pipes_texskip;
                if (getenv("KH1_HOST_TEXSKIP")) kh1_pipes_texskip = atoi(getenv("KH1_HOST_TEXSKIP"));
            }
            if (kh1_dma_natref && kh1_pool_start(getenv("KH1_HOST_NATPOOL") ? (u32)atoi(getenv("KH1_HOST_NATPOOL")) : 4u << 20))
                printf("kh1-host: KH1_HOST_NATREF: no pool\n");
        }
    }
    {
        const char *counts = getenv("KH1_HOST_COUNTS"); /* session 96: countcheck's DATA rows' marks */
        kh1_counts_on = counts && *counts && strcmp(counts, "0") != 0;
        if (kh1_counts_on) kh1_present_pal(1); /* session 117: fed by the chain walk (KH1_HOST_TRACE >= 2) */
        if (kh1_counts_on) kh1_present_tex(1); /* session 118: the texture cache likewise */
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
        if (!getenv("KH1_HOST_SHOT_FROM") && shot_setup()) return 2;
    }
    {
        const char *ovl = getenv("KH1_HOST_OVL");
        ovl_stub = ovl && strncmp(ovl, "stub", 4) == 0 && (ovl[4] == 0 || ovl[4] == ':');
        if (ovl_stub && ovl[4] == ':')
            ovl_state = strtol(ovl + 5, 0, 0);
    }
    {
        extern const char *kh1_mc_root[2]; /* host/port/mc_dir.c */
        const char *mc = getenv("KH1_HOST_MC");
        if (mc && *mc) {
            kh1_mc_root[0] = mc;
            printf("kh1-host: memory card 1 is %s\n", mc);
        }
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
