/* The null platform (phase 5, docs/vita-port-plan.md section 5 step 1): every
 * include/platform/ function off the EE as a stub, for the -m32 host build
 * (tools/host/census.py). Nothing is read, drawn or played: the calls succeed
 * and answer "done" or "nothing there". Not part of the PS2 build (it lives
 * outside src/). The Vita build replaces it with src/vita/. */
#include "common.h"
#include "platform/cd.h"
#include "platform/dma.h"
#include "platform/file.h"
#include "platform/gs.h"
#include "platform/iop.h"
#include "platform/math.h"
#include "platform/mc.h"
#include "platform/pad.h"
#include "platform/thread.h"
#include "platform/vu.h"
#include "dmawalk.h"
#include "gsregs.h"

/* the 16 KiB scratchpad (dma.h: PLAT_SPR_BASE / PLAT_SPR_END) */
u8 PlatSpr[0x4000] ALIGNED(16);

/* PlatDmaGetChan's handles: only compared and passed back to PlatDmaSend */
struct PlatDmaChan { u32 words[64]; };
static struct PlatDmaChan null_chan[16];

/* platform/cd.h */
int PlatCdInit(int mode) { return 0; }
int PlatCdInitEeCB(int priority, void *stack, int stacksize) { return 0; }
void *PlatCdPOffCallback(void (*func)(void *), void *arg) { return 0; }
/* With a disc image (KH1_HOST_ISO, host/port/cd_image.c) a search and a read answer from it;
 * without one every search answers found, at sector 0 with size 0 (the game retries a search
 * that fails for ever) and the runner stops at the first read.  libcdvd's sceCdlFILE: lsn,
 * size, name[16], date[8]. */
int kh1_cd_image_is_open(void);
int kh1_cd_image_search(const char *name, u32 *lsn, u32 *size);
int kh1_cd_image_read(u32 lsn, u32 n, void *buf);
extern int kh1_host_trace;
extern u32 kh1_host_cd_reads, kh1_host_cd_sectors;
int printf(const char *, ...);
void exit(int);
int PlatCdSearchFile(void *fp, const char *name) {
    u32 *f = (u32 *)fp;
    int i;
    f[0] = 0;
    f[1] = 0;
    if (!kh1_cd_image_is_open()) return 1;
    for (i = 0; i < 16; i++) {
        ((char *)fp)[8 + i] = name[i];
        if (!name[i]) break;
    }
    if (!kh1_cd_image_search(name, &f[0], &f[1])) {
        printf("kh1-host: PlatCdSearchFile %s: not on the disc\n", name);
        return 0;
    }
    if (kh1_host_trace) printf("kh1-host: PlatCdSearchFile %s: lsn %u, %u bytes\n", name, f[0], f[1]);
    return 1;
}
int PlatCdSync(int mode) { return 0; }
int PlatCdDiskReady(int mode) { return 2; /* SCECdComplete: the disc is ready */ }
int PlatCdMmode(int media) { return 0; }
/* without a disc image the host runner stops at the first read (host/null/main.c); with one the
 * read is done before PlatCdRead returns, so PlatCdSync and PlatCdGetError answer 0 */
extern int kh1_host_stop_at_cdread;
unsigned long kh1_host_frame(void);
int PlatCdRead(unsigned int lsn, unsigned int sectors, void *buf, void *mode) {
    if (kh1_cd_image_is_open()) {
        if (kh1_host_trace) printf("kh1-host: PlatCdRead lsn %u, %u sectors, frame %lu\n", lsn, sectors, kh1_host_frame());
        kh1_host_cd_reads++;
        kh1_host_cd_sectors += sectors;
        if (!kh1_cd_image_read(lsn, sectors, buf)) {
            printf("kh1-host: PlatCdRead lsn %u, %u sectors: past the end of the image\n", lsn, sectors);
            return 0;
        }
        return 1;
    }
    if (kh1_host_stop_at_cdread) {
        printf("kh1-host: first PlatCdRead (lsn %u, %u sectors, buf %p): stop\n", lsn, sectors, buf);
        exit(0);
    }
    return 0;
}
int PlatCdSeek(unsigned int lsn) { return 0; }
int PlatCdGetError(void) { return 0; }
int PlatCdStatus(void) { return 0; }
int PlatCdBreak(void) { return 0; }
int PlatCdPowerOff(int *result) { return 1; }

/* platform/dma.h: a transfer is done as soon as it starts.  Its channel's interrupt status (the
 * D_STAT bit) is set then and cleared by a PlatDmaPutStat of that bit (write 1 to clear), and an
 * enabled channel with a handler (PlatAddDmacHandler) runs it (null_dmac_run below). */
static void null_dmac_done(int ch);
static void null_dma_walk(int ch, u32 chcr, u32 tadr);
static void null_gs_send(const char *what, int send);
PlatDmaChan * PlatDmaGetChan(int id) { return (PlatDmaChan *)&null_chan[id & 15]; }
void kh1_counts_sample(void); /* host/null/counts.c (KH1_HOST_COUNTS, session 96) */
void PlatDmaSend(PlatDmaChan *ch, void *tag) {
    int n = (struct PlatDmaChan *)ch - null_chan;
    kh1_counts_sample();
    null_gs_send(n == 1 ? "PlatDmaSend ch 1" : n == 2 ? "PlatDmaSend ch 2" : 0, 1);
    if (kh1_host_trace >= 2) null_dma_walk(n, ch->words[0], (u32)(unsigned long)tag);
    null_dmac_done(n);
}
void PlatDmaPutStat(u32 v);
/* CHCR's STR (0x100) starts channel 1 (VIF1); MOD 1 (bits 2-3) walks the chain at TADR */
static u32 null_vif1_tadr;
void PlatDmaPutVif1Chcr(u32 v) {
    if (!(v & 0x100)) return;
    null_gs_send("PlatDmaPutVif1Chcr", 1);
    if (kh1_host_trace >= 2 && (v >> 2 & 3) == 1) null_dma_walk(1, v, null_vif1_tadr);
    null_dmac_done(1);
}
void PlatDmaPutVif1Qwc(u32 v) {}
void PlatDmaPutVif1Tadr(u32 v) { null_vif1_tadr = v; }

/* KH1_HOST_TRACE=2: host/null/dmawalk.c walks each chain a send starts.  The host owns the
 * executable's data and bss, the scratchpad and the stack. */
extern char __executable_start[], end[];
static const char *null_dma_where(u32 a, u32 n) {
    char local;
    unsigned long p = a, e = (unsigned long)a + n;
    if (p >= (unsigned long)__executable_start && e <= (unsigned long)end) return "image";
    if (p >= (unsigned long)PlatSpr && e <= (unsigned long)PlatSpr + sizeof PlatSpr) return "spr";
    if (p - (unsigned long)&local < 0x1000000) return "stack";
    return 0;
}
static void null_dma_walk(int ch, u32 chcr, u32 tadr) { kh1_dma_walk(ch, chcr, tadr, null_dma_where); }
void PlatVifPutErr(int n, u32 v) {}
u32 PlatVif1GetStat(void) { return 0; }

/* platform/file.h */
int PlatFsReset(void) { return 0; }
int PlatFsOpen(const char *name, int flag) { return 0; }
int PlatFsClose(int fd) { return 0; }
int PlatFsRead(int fd, void *buf, int n) { return 0; }
int PlatFsWrite(int fd, const void *buf, int n) { return -1; } /* session 132: no HDD */
int PlatFsSync(const char *dev, int flag) { return -1; }
int PlatFsRemove(const char *name) { return -1; }
int PlatFsMkdir(const char *name, int mode) { return -1; }
int PlatFsFormat(const char *dev, const char *blockdev, void *arg, int arglen) { return -1; }
int PlatFsLseek(int fd, int offset, int whence) { return 0; }
s64 PlatFsLseek64(int fd, s64 offset, int whence) { return 0; }
int PlatFsIoctl2(int fd, int req, void *arg, unsigned int arglen, void *buf, unsigned int buflen) { return 0; }
int PlatFsDopen(const char *name) { return 0; }
int PlatFsDclose(int fd) { return 0; }
int PlatFsDread(int fd, void *ent) { return 0; }
int PlatFsMount(const char *fsdev, const char *blockdev, int flag, void *arg, int arglen) { return 0; }
int PlatFsUmount(const char *fsdev) { return 0; }
int PlatFsDevctl(const char *dev, int cmd, const void *arg, unsigned int arglen, void *buf, unsigned int buflen) { return -1; /* no HDD */ }

/* platform/gs.h */
void PlatGsResetGraph(short mode, short inter, short omode, short ffmd) {}
void PlatGsResetPath(void) {}
/* a frame: the vblank handler the game installed (sceGsSyncVCallback, host/port/sdk_host.c) runs
 * once (host/null/main.c kh1_host_vblank) */
void kh1_host_vblank(void);
int PlatGsSyncV(int mode) {
    kh1_host_vblank();
    return 0;
}
/* mode 1 is only the draw list's own wait (func_0015ea98, func_0015eb78), not a main-thread sync */
int PlatGsSyncPath(int mode, unsigned short timeout) {
    if (mode == 0) null_gs_send("PlatGsSyncPath(0)", 0);
    return 0;
}
/* the image loads and stores: host/null/gsimage.c (session 101) */
void PlatGsDefDispEnv(void *disp, short psm, short w, short h, short dx, short dy) {}
void PlatGsPutDispEnv(void *disp) {}
/* the draw environment's GIF packet (tag + NLOOP qwords), read like a chain's data under
 * KH1_HOST_TRACE >= 2 (session 80: the boot environment sets both contexts, renderer-spec 4.11) */
void PlatGsPutDrawEnv(void *giftag) {
    null_gs_send("PlatGsPutDrawEnv", 1);
    if (kh1_host_trace >= 2) kh1_dma_gif_direct((const u32 *)giftag, (((const u32 *)giftag)[0] & 0x7FFF) + 1);
}
void PlatGsPutPmode(u64 v) {}
void PlatGsPutDispfb1(u64 v) {}
void PlatGsPutDisplay1(u64 v) {}
void PlatGsPutExtwrite(u64 v) {}
u64 PlatGsGetCsr(void) { return 0; }

/* platform/iop.h */
void PlatSifInitRpc(unsigned int mode) {}
/* bound: sceSifClientData's server pointer (+0x24) non-zero, which the game polls for
 * (src/sound/snd_rpc.c func_001ec7d0); no IOP answers the calls */
static u32 null_server[16];
int PlatSifBindRpc(void *client, unsigned int num, unsigned int mode) {
    *(u32 **)((u8 *)client + 0x24) = null_server;
    return 0;
}
/* The sound server (17, src/sound/snd_rpc.c) is host/null/sound.c's null server: it keeps the
 * status block the game polls (the bank transfer count, the SE voices and streams) and, with
 * KH1_HOST_SND=trace, prints each command (docs/sound-spec.md). No other server is bound. */
void kh1_null_snd_rpc(unsigned num, void *send, int ssize, void *recv, int rsize);
int PlatSifCallRpc(void *client, unsigned int num, unsigned int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *param) {
    kh1_null_snd_rpc(num, send, ssize, recv, rsize);
    return 0;
}
/* iop.h: the reboot and the module loads succeed (module id 1), PlatSifSyncIop 1 */
int PlatSifLoadModule(const char *name, int arglen, const char *args) { return 1; }
int PlatSifLoadStartModule(const char *name, int arglen, const char *args, int *result) { return 1; }
int PlatSifSearchModuleByName(const char *name) { return -1; /* no IOP module is loaded */ }
int PlatSifRebootIop(const char *image) { return 1; }
int PlatSifSyncIop(void) { return 1; }

/* platform/mc.h: host/port/mc_dir.c (a card is a directory; none set, no card in either slot) */

/* platform/pad.h: host/null/pad.c (session 87) */

/* platform/thread.h */
void PlatFlushCache(int op) {}
void PlatIFlushCache(int op) {}
/* threads and semaphores: host/null/threads.c */
/* The DMAC interrupts.  The one user is src/model/mdlgs.c: func_0015eb78 starts the frame's GS
 * task list with channels 1 and 2 masked (PlatDisableDmac, PlatDmaPutStat(6)), runs it until a
 * task starts a transfer and asks to go on in the interrupt (bit 2 of its answer), then enables
 * both; the handler func_0015efc0 runs the rest of the list one transfer at a time and clears
 * D_00559DB4 at its end, which func_0015ef60 waits for.  Unanswered it waited for ever (session
 * 68, KH1_HOST_OVL=stub:2).  Here an enabled channel whose status is set runs its handler
 * (cause = the channel), after the call that set or enabled it and never inside a handler: a
 * transfer a handler starts runs the handler again once it returns, as the next interrupt. */
#define NULL_DMAC_HANDLERS 4
static int (*null_dmac_fn[16][NULL_DMAC_HANDLERS])(int);
static u32 null_dmac_stat, null_dmac_mask;
static int null_dmac_running;
/* KH1_HOST_DMAC=defer (session 84, vita-port-plan 5.1x; host/null/main.c): a transfer's end and
 * PlatEnableDmac only set the status / mask, no handler runs there, so the draw list stays pending
 * after func_0015eb78's hand-over and only kh1_gs_flush_pending replays it: the port's order. */
int kh1_host_dmac_defer;
static void null_dmac_run(void) {
    int ch, i;
    u32 due;
    if (null_dmac_running) return;
    null_dmac_running = 1;
    while ((due = null_dmac_stat & null_dmac_mask) != 0) {
        for (ch = 0; !(due & (1u << ch)); ch++)
            ;
        null_dmac_stat &= ~(1u << ch);
        for (i = 0; i < NULL_DMAC_HANDLERS; i++)
            if (null_dmac_fn[ch][i]) null_dmac_fn[ch][i](ch);
    }
    null_dmac_running = 0;
}
static void null_dmac_done(int ch) {
    null_dmac_stat |= 1u << (ch & 15);
    if (!kh1_host_dmac_defer) null_dmac_run();
}
void PlatDmaPutStat(u32 v) { null_dmac_stat &= ~(v & 0xFFFF); }
/* the id is the handler's slot + 1 (0 would read as "none" to a caller) */
int PlatAddDmacHandler(int ch, int (*handler)(int), int next) {
    int i;
    for (i = 0; i < NULL_DMAC_HANDLERS; i++)
        if (!null_dmac_fn[ch & 15][i]) {
            null_dmac_fn[ch & 15][i] = handler;
            return i + 1;
        }
    return -1;
}
int PlatRemoveDmacHandler(int ch, int id) {
    if (id >= 1 && id <= NULL_DMAC_HANDLERS) null_dmac_fn[ch & 15][id - 1] = 0;
    return 0;
}
int PlatEnableDmac(int ch) {
    null_dmac_mask |= 1u << (ch & 15);
    if (!kh1_host_dmac_defer) null_dmac_run();
    return 0;
}
int PlatDisableDmac(int ch) {
    null_dmac_mask &= ~(1u << (ch & 15));
    return 0;
}
int PlatPcStart(int control, int c0, int c1) { return 0; }
void PlatPcStop(void) {}

/* platform/vu.h (off-EE helpers) */
u32 PlatVu0GetVpuStat(void) { return 0; /* VU1 idle */ }

/* The draw / immediate lists' nodes (session 83, platform/gs.h PlatGsListNode; renderer-spec 4.12,
 * vita-port-plan 5.1w).  KH1_HOST_TRACE=5 prints each node as it starts, before its sends' lines:
 *   kh1-host: node draw|imm KEY cb CALLBACK arg PAYLOAD   (KEY decimal; host addresses)
 * "kh1-host: node main" before the first send made outside a node after one, and
 *   kh1-host: list draw|imm end: N nodes, frame F
 * when a list is done (tools/host/gsstate.py --nodes reads them). */
static int null_node_list = -1;     /* the list whose node's callback is running, -1 none */
static int null_node_after;         /* a node ran since the last send outside one */
static unsigned null_node_count[2];
unsigned kh1_gs_list_nodes, kh1_gs_pending_sends, kh1_gs_list_waits;
unsigned long kh1_host_frame(void);
void PlatGsListNode(int list, void *node) {
    const u32 *n = node;
    if (!n) {
        null_node_list = -1;
        return;
    }
    null_node_list = list & 1;
    null_node_after = 1;
    null_node_count[list & 1]++;
    kh1_gs_list_nodes++;
    if (kh1_host_trace >= 5)
        printf("kh1-host: node %s %d cb %08x arg %08x\n", list ? "imm" : "draw", (s32)n[1], n[3], n[4]);
}
void PlatGsListEnd(int list) {
    kh1_counts_sample(); /* the frame's lists are full here (host/null/counts.c) */
    if (kh1_host_trace >= 5 && null_node_count[list & 1])
        printf("kh1-host: list %s end: %u nodes, frame %lu\n", list ? "imm" : "draw", null_node_count[list & 1],
               kh1_host_frame());
    null_node_count[list & 1] = 0;
    null_node_list = -1;
}

/* vita-port-plan 5.1v's rule: a main-thread GS send (or sync) first replays any pending draw list.
 * The draw list is pending from func_0015eb78's hand-over (D_00559DB4 = 1) until func_0015ea98
 * reaches its end (D_00559DB4 = 0).  Here the list runs from the DMAC handlers as each transfer
 * ends (null_dmac_run), so a send outside a node and outside a handler should never find it
 * pending; one that does is counted (kh1_gs_pending_sends, printed at the run's end) and replays
 * what the DMAC owes (the due handlers) before it goes on: kh1_gs_flush_pending is the port's hook. */
extern volatile s32 D_00559DB4;
static void kh1_gs_flush_pending(const char *what) {
    if (!D_00559DB4) return;
    kh1_gs_pending_sends++;
    if (kh1_host_trace >= 5)
        printf("kh1-host: flush: %s found the draw list pending (frame %lu)\n", what, kh1_host_frame());
    null_dmac_run();
}
/* what: the GS send or sync (0 for a channel that is not the GS's: VIF0); send: a transfer, which
 * prints its own line (dmawalk.c), so the marker goes before it and after the replayed nodes */
static void null_gs_send(const char *what, int send) {
    if (null_node_list >= 0 || null_dmac_running) return; /* a node's own send, or a handler's */
    if (what) kh1_gs_flush_pending(what);
    if (send && null_node_after) {
        if (kh1_host_trace >= 5) printf("kh1-host: node main\n");
        null_node_after = 0;
    }
}
/* func_0015ef60's frame-end wait (session 84): the list still pending there (KH1_HOST_DMAC=defer:
 * nothing replayed it since the hand-over) is replayed now.  A list that stays pending with no
 * handler due would spin for ever: say so and stop. */
void PlatGsListWait(void) {
    if (!D_00559DB4) return;
    kh1_gs_list_waits++;
    if (kh1_host_trace >= 5) printf("kh1-host: flush: frame-end wait found the draw list pending (frame %lu)\n",
                                    kh1_host_frame());
    null_dmac_run();
    if (D_00559DB4 && !(null_dmac_stat & null_dmac_mask)) {
        printf("kh1-host: the draw list is still pending at the frame-end wait, no DMAC handler due\n");
        exit(3);
    }
}

/* KH1_HOST_WIDE (session 92, host/null/main.c): the HUD's anchored parts move by the view's margin
 * past each 4:3 edge in the GIF path (include/platform/hudanchor.h, host/null/dmawalk.c); session 93:
 * the static full-screen packets stretch to the view (include/platform/fullscreen.h) and the scissor
 * rule reads the view (host/null/gsregs.c, include/platform/canvas.h) */
void kh1_gsq_sync(void);
void kh1_null_hud_wide(s32 m) { /* the margin in canvas sixteenths, kh1_view_side16 (session 95) */
    kh1_gsq_sync(); /* session 141: kh1_gs_view writes the register file (host/null/gsqueue.h) */
    kh1_dma_hud_anchors(kh1_hud_anchors, kh1_hud_nanchors, (u32)(unsigned long)kh1_hud_staging,
                        kh1_hud_staging_size, m);
    kh1_dma_fullscreen(kh1_fullscreen, kh1_nfullscreen, -m, 8192 + 2 * m);
    kh1_gs_view(-m, 8192 + 2 * m);
}
