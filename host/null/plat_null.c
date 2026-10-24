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

/* platform/dma.h */
PlatDmaChan * PlatDmaGetChan(int id) { return (PlatDmaChan *)&null_chan[id & 15]; }
void PlatDmaSend(PlatDmaChan *ch, void *tag) {}
void PlatDmaPutStat(u32 v) {}
void PlatDmaPutVif1Chcr(u32 v) {}
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
int PlatSifCallRpc(void *client, unsigned int num, unsigned int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *param) { return 0; }
/* iop.h: the reboot and the module loads succeed (module id 1), PlatSifSyncIop 1 */
int PlatSifLoadModule(const char *name, int arglen, const char *args) { return 1; }
int PlatSifLoadStartModule(const char *name, int arglen, const char *args, int *result) { return 1; }
int PlatSifSearchModuleByName(const char *name) { return -1; /* no IOP module is loaded */ }
int PlatSifRebootIop(const char *image) { return 1; }
int PlatSifSyncIop(void) { return 1; }

/* platform/mc.h */
int PlatMcInit(void) { return 0; }
int PlatMcGetSlotMax(int port) { return 0; }
int PlatMcGetInfo(int port, int slot, int *type, int *free, int *format) { return 0; }
int PlatMcOpen(int port, int slot, const char *name, int mode) { return 0; }
int PlatMcClose(int fd) { return 0; }
int PlatMcRead(int fd, void *buf, int size) { return 0; }
int PlatMcWrite(int fd, const void *buf, int size) { return 0; }
int PlatMcMkdir(int port, int slot, const char *name) { return 0; }
int PlatMcChdir(int port, int slot, const char *name, char *cur) { return 0; }
int PlatMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, void *table) { return 0; }
int PlatMcDelete(int port, int slot, const char *name) { return 0; }
int PlatMcFormat(int port, int slot) { return 0; }
int PlatMcUnformat(int port, int slot) { return 0; }
int PlatMcRename(int port, int slot, const char *name, const char *newname) { return 0; }
int PlatMcSync(int mode, int *cmd, int *result) { return 0; }

/* platform/pad.h */
int PlatDbcInit(void) { return 0; }
int PlatPadInit(int mode) { return 0; }
int PlatPadCreateSocket(void *param, void *addr) { return 0; }
int PlatPadGetState(int socket) { return 0; }
int PlatPadGetButtonProfile(int socket, void *profile) { return 0; }
int PlatPadRead(int socket, u8 *data) { return 0; }
int PlatVibSetActParam(int socket, int psize, u8 *profile, int dsize, void *data) { return 0; }

/* platform/thread.h */
void PlatFlushCache(int op) {}
void PlatIFlushCache(int op) {}
int PlatCreateThread(void *param) { return 0; }
int PlatStartThread(int id, void *arg) { return 0; }
int PlatChangeThreadPriority(int id, int prio) { return 0; }
int PlatGetThreadId(void) { return 0; }
int PlatCreateSema(void *param) { return 0; }
/* There is no other thread: a wait that would block on the EE lets a frame pass instead (the
 * main loop's frame wait, src/util/thread.c func_0010c348, is a semaphore the vblank handler
 * signals), then returns. */
int PlatWaitSema(int id) {
    kh1_host_vblank();
    return 0;
}
int PlatSignalSema(int id) { return 0; }
int PlatISignalSema(int id) { return 0; }
int PlatIReferSemaStatus(int id, void *param) { return 0; }
int PlatAddDmacHandler(int ch, int (*handler)(int), int next) { return 0; }
int PlatRemoveDmacHandler(int ch, int id) { return 0; }
int PlatEnableDmac(int ch) { return 0; }
int PlatDisableDmac(int ch) { return 0; }
int PlatPcStart(int control, int c0, int c1) { return 0; }
void PlatPcStop(void) {}

/* platform/vu.h (off-EE helpers) */
u32 PlatVu0GetVpuStat(void) { return 0; /* VU1 idle */ }
