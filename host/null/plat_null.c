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
int PlatCdRead(unsigned int lsn, unsigned int sectors, void *buf, void *mode) {
    if (kh1_cd_image_is_open()) {
        if (kh1_host_trace) printf("kh1-host: PlatCdRead lsn %u, %u sectors\n", lsn, sectors);
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
PlatDmaChan * PlatDmaGetChan(int id) { return (PlatDmaChan *)&null_chan[id & 15]; }
void PlatDmaSend(PlatDmaChan *ch, void *tag) { null_dmac_done((struct PlatDmaChan *)ch - null_chan); }
void PlatDmaPutStat(u32 v);
/* CHCR's STR (0x100) starts channel 1 (VIF1) */
void PlatDmaPutVif1Chcr(u32 v) {
    if (v & 0x100) null_dmac_done(1);
}
void PlatDmaPutVif1Qwc(u32 v) {}
void PlatDmaPutVif1Tadr(u32 v) {}
void PlatVifPutErr(int n, u32 v) {}
u32 PlatVif1GetStat(void) { return 0; }

/* platform/file.h */
int PlatFsReset(void) { return 0; }
int PlatFsOpen(const char *name, int flag) { return 0; }
int PlatFsClose(int fd) { return 0; }
int PlatFsRead(int fd, void *buf, int n) { return 0; }
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
int PlatGsSyncPath(int mode, unsigned short timeout) { return 0; }
int PlatGsSetDefLoadImage(void *lp, short dbp, short dbw, short psm, short x, short y, short w, short h) { return 0; }
int PlatGsSetDefStoreImage(void *sp, short sbp, short sbw, short psm, short x, short y, short w, short h) { return 0; }
int PlatGsExecLoadImage(void *lp, void *src) { return 0; }
int PlatGsExecStoreImage(void *sp, void *dst) { return 0; }
void PlatGsDefDispEnv(void *disp, short psm, short w, short h, short dx, short dy) {}
void PlatGsPutDispEnv(void *disp) {}
void PlatGsPutDrawEnv(void *giftag) {}
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
/* The sound server's answer is word 0 of recv (src/sound/snd_rpc.c), which the game shares
 * with send: unanswered, a call reads back its own request. The one answer the main ELF
 * waits on is RPC 0x30 (func_001ed600), the event command func_001e8b50 polling until what
 * RPC 0x2F (func_001ed5a8) started is ready: with no IOP it is ready at once (1). The other
 * answers (RPCs 1, 0xF, 0x1F-0x22, 0x27, 30 ...) are not read by any caller.
 *
 * The status block (RPC 0's word 0, D_0063D640) is the IOP's to write, and one word of it
 * the game waits on: +0x1F00 (D_0063F540, func_001ecfd8) counts the bank transfers not yet
 * done. The EE adds one for each transfer it queues (commands 3, 4 and 0xB: func_001ed658,
 * func_001ed220, func_001ed460) and the IOP's copy takes over once it has them. Boot
 * (func_0011cd20) waits for the count to be non-zero after sending the queue (RPC 30); the
 * sound objects (objse.c), the summons (summon.c), the bank task func_0011cba0 and the soft
 * reset (func_00109658) wait for it to be 0 again. Unanswered it stayed at 2 from boot on. With
 * no IOP, the transfers a sent queue holds are done at the next frame (null_iop_frame). */
#define NULL_SND_PENDING 0x1F00
static u8 *null_snd_status;
static s32 null_snd_landing;
int PlatSifCallRpc(void *client, unsigned int num, unsigned int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *param) {
    if (num == 0 && send != 0 && ssize >= 4) null_snd_status = (u8 *)(unsigned long)((u32 *)send)[0];
    if (num == 30 && send != 0) {
        /* the queue: 8-word commands, unused slots -1 (func_001ed000, func_001edba0) */
        s32 *q = send;
        s32 i;
        for (i = 0; i < ssize / 32 && q[i * 8] != -1; i++)
            if (q[i * 8] == 3 || q[i * 8] == 4 || q[i * 8] == 0xB) null_snd_landing++;
    }
    if (num == 0x30 && recv != 0 && rsize >= 4) *(u32 *)recv = 1;
    return 0;
}
/* a frame (kh1_host_vblank): the transfers sent before it are done */
void kh1_null_iop_frame(void) {
    s32 *pending;
    if (null_snd_status == 0 || null_snd_landing == 0) return;
    pending = (s32 *)(null_snd_status + NULL_SND_PENDING);
    *pending -= null_snd_landing;
    if (*pending < 0) *pending = 0;
    null_snd_landing = 0;
}
/* iop.h: the reboot and the module loads succeed (module id 1), PlatSifSyncIop 1 */
int PlatSifLoadModule(const char *name, int arglen, const char *args) { return 1; }
int PlatSifLoadStartModule(const char *name, int arglen, const char *args, int *result) { return 1; }
int PlatSifSearchModuleByName(const char *name) { return -1; /* no IOP module is loaded */ }
int PlatSifRebootIop(const char *image) { return 1; }
int PlatSifSyncIop(void) { return 1; }

/* platform/mc.h: no card in any slot. Every request is queued (0) and done at the next
 * PlatMcSync (1), whose result is libmc's "no card detected" (-10): src/memcard/mcstep.c's
 * steps poll sceMcSync until it answers, then read the result (and GetInfo's type) it wrote. */
#define NULL_MC_NO_CARD (-10)
int PlatMcInit(void) { return 0; }
int PlatMcGetSlotMax(int port) { return 0; }
int PlatMcGetInfo(int port, int slot, int *type, int *free, int *format) {
    if (type) *type = 0;  /* no card */
    if (free) *free = 0;
    if (format) *format = 0;
    return 0;
}
int PlatMcOpen(int port, int slot, const char *name, int mode) { return 0; }
int PlatMcClose(int fd) { return 0; }
int PlatMcRead(int fd, void *buf, int size) { return 0; }
int PlatMcWrite(int fd, const void *buf, int size) { return 0; }
int PlatMcMkdir(int port, int slot, const char *name) { return 0; }
int PlatMcChdir(int port, int slot, const char *name, char *cur) { return 0; }
/* the entry count is PlatMcSync's result: -10 here, so mcstep.c's func_00235228 stores
 * count -1 and error 3 and never reads the table (PlatMcRead's count the same way) */
int PlatMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, void *table) { return 0; }
int PlatMcDelete(int port, int slot, const char *name) { return 0; }
int PlatMcFormat(int port, int slot) { return 0; }
int PlatMcUnformat(int port, int slot) { return 0; }
int PlatMcRename(int port, int slot, const char *name, const char *newname) { return 0; }
int PlatMcSync(int mode, int *cmd, int *result) {
    if (cmd) *cmd = 0;
    if (result) *result = NULL_MC_NO_CARD;
    return 1;
}

/* platform/pad.h */
int PlatDbcInit(void) { return 0; }
int PlatPadInit(int mode) { return 0; }
int PlatPadCreateSocket(void *param, void *addr) { return 0; }
int PlatPadGetState(int socket) { return 0; }
/* no pad: no profile (src/pad/padread.nostrict.c skips the read on < 0; PlatPadGetState
 * never answers 1 anyway, so the profile, D_004E44C8, is not reached) */
int PlatPadGetButtonProfile(int socket, void *profile) { return -1; }
/* PlatPadGetState never answers 1 (stable), so src/pad/padread.nostrict.c does not read;
 * should it, the read fails and leaves no button pressed (the buttons are active low). */
int PlatPadRead(int socket, u8 *data) {
    data[0] = data[1] = 0xFF;
    return -1;
}
int PlatVibSetActParam(int socket, int psize, u8 *profile, int dsize, void *data) { return 0; }

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
static void null_dmac_run(void) {
    static int running;
    int ch, i;
    u32 due;
    if (running) return;
    running = 1;
    while ((due = null_dmac_stat & null_dmac_mask) != 0) {
        for (ch = 0; !(due & (1u << ch)); ch++)
            ;
        null_dmac_stat &= ~(1u << ch);
        for (i = 0; i < NULL_DMAC_HANDLERS; i++)
            if (null_dmac_fn[ch][i]) null_dmac_fn[ch][i](ch);
    }
    running = 0;
}
static void null_dmac_done(int ch) {
    null_dmac_stat |= 1u << (ch & 15);
    null_dmac_run();
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
    null_dmac_run();
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
