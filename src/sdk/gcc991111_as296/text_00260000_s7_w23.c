#include "common.h"
/* libcdvd (w23, session 7): func_002695f8, func_00269830, func_002698c8, sceCdRead
 * (0x26a7f0) and func_0026a9d0 match in sdk/gcc991111_as296 with no asm barrier.
 * The libcdvd state words D_0046C610-D_0046C658 are volatile in the original:
 * written as VS() accesses, 991111a's reorg keeps them out of delay slots and the
 * 2.96 assembler fills those slots itself (the session-7 w4 drafts needed an empty
 * __asm__ volatile("") to get the same effect). Context: the header of
 * nonmatchings/session6/w6_28__ctx.h, copied below. */
/* Leftover SCE SDK functions matched by hand (session s2), ee-gcc 2.9-991111. */
#include "common.h"

s32 iSignalSema(s32);

s32 func_0025fd10(s32);
s64 func_00272c38(const char *, char **, s32);
s32 func_00260a20(s32);
s32 sceMcOpen(s32 a, s32 b, const char *name, s32 d);
s32 func_00260458(s32, s32, s32, s32, s32, s32, s32);
char *strcpy(char *, const char *);
s32 GetMemorySize(void);
s32 func_00260b00(void);
s32 func_002585d0(void);
s32 sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
s32 sceDbcDeleteSocket(s32);
s32 sceDbcGetDepNumber(s32);
s32 func_00269fd0(s32);
s32 DIntr(void);
s32 EIntr(void);
void SyncDCache(void *, void *);
s32 WaitSema(s32);
s32 SignalSema(s32);
s32 PollSema(s32);
s32 CreateSema(void *);
s32 DeleteSema(s32);
s32 func_00257ee0(u16, void *, s32); /* syscall 0xFC: SetAlarm(time, handler, arg) */
s32 func_0025a750(void *);
s32 scePrintf(const char *, ...);
u32 sceDmaPause(volatile u32 *);
void func_00268a78(const char *, ...);
s32 func_00257e20(s32, void *);
void func_00260f40(void);
u32 strlen(const char *);
s32 func_00269dc8(s32);
s32 func_0025b588(const char *, s32);
s32 func_0025bbc8(s32, void *, s32);
s32 func_0025b810(s32);
void FlushCache(s32);
void func_00260738(void *, s32);
void func_00260928(s32, s32);
s32 func_00260918(s32);
void func_002608d0(u32, void *, s32);
s32 func_00269210(u8 *, void *);
void func_00271558(s32);
s32 GetThreadId(void);
s32 ReferThreadStatus(s32, void *);
s32 CreateThread(void *);
s32 StartThread(s32, void *);
s32 ChangeThreadPriority(s32, s32);
void func_002695f8(void);
void func_00266bd0(void *, s32);
/* libdma environment: stall/drain/MFIFO selectors, cycle count, PCR and SQWC
 * halves, ring buffer address and size. */
typedef struct { u8 sts, std, mfd, rcyc; u16 express, notify; u16 sqwc, tqwc; void *rbadr; u32 rbmsk; } DmaEnv;
s32 sceDmaPutEnv(DmaEnv *);
void sceVu0ScaleVector(f32 *, f32 *, f32);
void sceVu0Normalize(f32 *, f32 *);
void sceVu0TransposeMatrix(f32 *, f32 *);
void *sceGsGetGParam(void);
s32 func_0026a0e0(s32);
s32 func_002585f0(void);
s64 func_00258680(void);
/* libdbc command word, passed by value in one 64-bit register. */
typedef struct { u64 a:14; u64 b:2; u64 c:8; u64 d:8; } DbcCmd;
typedef union { DbcCmd f; u64 w; } DbcU;
s32 func_002690d0(s32);
typedef struct { s32 n0, n1; u8 d[40]; } VibBuf; /* libvib send buffer */
s32 sceDbcReceiveData(s32 sock, u32 cmd, s32 *len, u8 *data);
s32 sceDbcSendData2(s32 sock, u32 cmd, s32 *len, u8 *data);
/* libvib passes the command word as the 64-bit bitfield struct. */
#define DbcRecvC ((s32 (*)(s32, DbcCmd, s32 *, void *))sceDbcReceiveData)
#define DbcSend2C ((s32 (*)(s32, DbcCmd, s32 *, void *))sceDbcSendData2)
void *memcpy(void *, const void *, u32);

typedef struct { s32 a, b; } E8;
extern E8 *D_0066E6E4;
extern E8 *D_0066E6EC;
extern s32 D_0066E800[];
extern u32 D_0046C550[];
typedef struct { s32 w[5]; } S20;
extern S20 D_0066FAD8;
extern s32 D_0046E090;
extern void *D_00673344;
extern s32 D_00673348;
extern s32 D_0046C624;
extern char *D_0046C5E0[];
extern char D_004930D8[];
extern u8 D_0066FB08[];
extern s32 D_0066FB80[];
/* libpad2 socket table: 16 slots of 0x330 bytes. */
/* Two 128-byte DMA buffers per socket; the counter at +124 orders them. */
typedef struct { u8 b0, b1, b2, b3; s32 x4; u8 p8[20]; u8 m[32]; u8 p60[64]; s32 cnt; } PadBuf;
typedef struct { s32 valid, type, idx, shift; } BtnEnt; /* button table entry */
typedef struct { s32 x0, x4, x8; PadBuf *buf; BtnEnt btn[50]; } Pad2Slot;
extern Pad2Slot D_00670040[];
PadBuf *func_00269128(s32);
s32 func_00269190(s32);
extern s32 D_00673340;
extern s32 D_0046C5D8[2];
extern s32 D_0046C628, D_0046C62C;
extern s32 D_0046C654, D_0046C658, D_0046C630, D_0046C614, D_0046C620;
extern char D_00492920[]; /* "rom0:ROMVER" */
extern char D_004931B8[]; /* "N cmd wait\n" */
extern u8 D_0046D7D0[];
extern s32 D_0046C680[];
extern s32 D_0046D800[];
typedef struct { s16 h0, h2, h4, h6; s32 x8; } GsState;
typedef struct { u64 pmode, smode2, dispfb, display, bgcolor; } DispEnv;
typedef struct { s32 n0, n1; u8 *d0, *d1; u8 b0[64]; u8 b1[64]; } McXfer;
extern char D_00492F50[]; /* "sceDbcSetWorkAddr: rpc error\n" */
extern char D_004931C8[]; /* "S cmd wait\n" */
extern char D_00492E60[]; /* "libdma: sync timeout\n" */
extern char D_00492F90[]; /* "sceDbcDeleteSocket: rpc error\n" */
extern char D_00492FD0[]; /* "sceDbcInitSocket: rpc error\n" */
extern char D_00492FF0[]; /* "sceDbcResetSocket: rpc error\n" */
extern char D_00493010[]; /* "sceDbcGetDeviceStatus: rpc error\n" */
extern char D_00494008[]; /* "sceMcUdCheckNewCard RPC faild\n" */
extern char D_00493038[]; /* "sceDbcSRData: rpc error\n" */
extern char D_00493058[]; /* "sceDbcSendData: rpc error\n" */
extern char D_00493078[]; /* "sceDbcSendData2: rpc error\n" */
extern char D_00493098[]; /* "sceDbcReceiveData: rpc error\n" */
extern u8 D_0066FB30[];   /* libdbc no-wait RPC client */
extern s32 D_0046C63C;
extern s32 D_0046C1C8[];
extern char D_00673BC0[];
typedef struct { u8 pad[0x24]; void *server; } SifClient;
extern SifClient D_00673600;   /* libmc RPC client */
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; s32 x10; s32 x14; void *x18; void *x1c; u8 data[16]; } McArg;
/* libmc RPC send buffer for calls that carry a path name. */
typedef struct { s32 x0, x4, x8, xc; void *x10; char name[1024]; } McNameArg;
extern McNameArg D_006736B0;
extern u8 D_00673B00[];
extern u8 D_00673640[];
char *func_00265190(char *, const char *, u32);
void *memset(void *, s32, u32);
typedef struct { u8 n[16]; } Name16;
typedef struct { s32 w[5]; Name16 name; } DbcSockCfg;
s32 sceDbcCreateSocket(DbcSockCfg *cfg, void *a, void *b);
typedef struct { s32 x0, x4, x8, xc; Name16 name; } Pad2SockParam;
extern McArg D_00673680;       /* libmc RPC send buffer */
extern s32 D_0046E094;
extern s32 D_0046C208;
extern s32 D_00673350;
extern u8 D_00673358[];
typedef struct { s32 status; void *func; void *stack; s32 stack_size; void *gp_reg; s32 initial_priority; } ThreadParam;
extern ThreadParam D_00673388;
extern u8 D_00494050[];
extern s32 D_0046DC40;
extern u8 D_0046BE90[];
typedef struct { s32 a, b; } Pair;
extern Pair D_0046C210[];         /* libmc semaphore */
extern char D_004932B8[];      /* "status called\n" */
extern s32 D_00674BC0[];
extern s32 D_0046C610;
extern u8 D_0046E048[];
typedef struct { u32 chcr; u32 pad[3]; u32 madr; u32 pad2[3]; u32 qwc; } DmaCh;
typedef struct { u32 chcr; u32 p0[3]; u32 madr; u32 p1[3]; u32 qwc; u32 p2[3]; u32 tadr; u32 p3[3]; u32 asr0; u32 p4[3]; u32 asr1; u32 p5[11]; u32 sadr; } DmaChReg;
extern const s32 D_00492E78[]; /* libdma: which channels to reset */
typedef struct { u32 dir:1; u32 pad:1; u32 mod:2; u32 asp:2; u32 tte:1; u32 tie:1; u32 str:1; u32 pad2:7; u32 tag:16; } Chcr;
typedef struct { s32 count, max_count, init_count, wait_threads; u32 attr, option; } SemaParam;
extern s32 *D_00673628;
extern s32 *D_0067362C;
extern s32 *D_00673630;
extern char D_00492968[];

#define VS(x) (*(volatile s32 *)&(x))
#define UNCACHED(p) ((s32 *)((u32)(p) | 0x20000000))
#define IPU_CTRL (*(volatile s32 *)0x10002010)
#define D_CTRL (*(volatile u32 *)0x1000e000)
#define R(a) (*(volatile u32 *)(a))
#define DREG(a) (*(volatile u32 *)(a))

/* Session s2, second batch. */
typedef struct { u8 b[64]; } Blk64;
typedef struct { u64 tag[10]; u64 tag2; } GsLoadImage;
void exit(s32);
s32 sceSifInitRpc(s32);
s32 sceSifBindRpc(void *, u32, s32);
s32 sceMcSync(s32 mode, s32 *cmd, s32 *result);
s32 sceDbcSetWorkAddr(s32 addr);
s32 func_0026a070(s32);
void func_00269830(void);
extern s32 D_00670000[16];      /* libdbc device table */
extern u8 D_0066FF80[];         /* libdbc work area */
extern s32 D_0046C61C, D_0046C618, D_0046C638, D_0046C648;
extern u8 D_00492EA0[], D_00492EB0[], D_00492EC0[]; /* libdma selector tables */
extern char D_00492ED0[]; /* "libdbc: bind failed\n" */
extern char D_00492EE8[]; /* "libdbc: Module version mismatch " */
extern char D_00492F10[]; /* "[libdbc.a = %d.%d, dbcman.irx = %d.%d]\n" */
extern char D_00492F38[]; /* "SifDmaAddr %08x\n" */
extern char D_00492FB0[]; /* "sceDbcGetDepNumber: rpc error\n" */
extern char D_00493178[]; /* "Ncmd fail sema cur_cmd:%d keep_cmd:%d\n" */
extern char D_004931A0[]; /* "Libcdvd bind err N CMD\n" */
extern char D_004931D8[]; /* "Scmd fail sema cur_cmd:%d keep_cmd:%d\n" */
extern char D_00493200[]; /* "Libcdvd bind err S cmd\n" */
extern char D_00493FA0[]; /* "bind error libmc \n" */
extern char D_00493FB8[]; /* "libmc: too old release of mcserv.irx\n" */
extern char D_00493FE0[]; /* "libmc: too old release of mcman.irx\n" */
extern char D_00492C50[]; /* "sceGsExecLoadImage: DMA Ch.2 does not terminate\r\n" */

extern s32 D_0067334C;
extern char D_004930E0[];
void ExitDeleteThread(void);
extern s32 D_0046C640;
extern u8 D_00673540[];
extern s32 D_00673500[];
extern char D_00493108[], D_00493128[], D_00493140[], D_00493150[], D_00493160[];
typedef struct { u32 lsn; u32 size; char name[16]; u8 date[8]; u32 flag; } CdlFile;
typedef struct { CdlFile file; char name[256]; void *addr; s32 mode; } CdSearchArg;
extern CdSearchArg D_006733C0;
extern s32 D_0046C650, D_0046C64C, D_0046C644, D_0046C634;
extern u8 D_00673568[];
extern s32 D_006735C0;
extern char D_00493218[], D_00493238[];
#define UNC(x) (*(s32 *)((u32)&(x) | 0x20000000))
void func_002698c8(void);
s32 func_00269a18(void);
extern u8 D_00673590[];
extern s32 D_006735D0;
extern char D_00493248[], D_00493258[], D_00493278[];
#define PRINTF ((void (*)(const char *, ...))scePrintf)
#define SIFINIT ((void (*)(s32))sceSifInitRpc)
typedef struct { u8 trycount, spindlctrl, datapattern, pad; } CdRMode;
typedef struct { u32 lbn; u32 sectors; void *buf; CdRMode mode; void *x10; void *x14; } CdReadArg;
extern CdReadArg D_0046C700;
extern u8 D_0046D700[];
extern s32 D_0046D7C0[];
extern char D_00493290[], D_004932A8[];
s32 func_00269f38(void);
void func_00269790(u32);
void func_00269558(s32 *);
typedef unsigned int u128 __attribute__((mode(TI)));
extern u128 D_0046E0B0[];
extern u128 D_0046E100[];
void func_00272738(s32);
#define IPU_CMDR (*(volatile u32 *)0x10002000)
#define IPU_CTRLR (*(volatile s32 *)0x10002010)
#define IPU_FIFO (*(volatile u128 *)0x10007010)
extern u8 D_00491A19[];
typedef struct { s32 _errno; } Reent0;
extern const char D_00491A18[];

void func_002695f8(void) {
    while (1) {
        WaitSema(D_0046C620);
        if (D_0046C654 == -1) {
            VS(D_0046C630) = 0;
            D_0046C654 = 0;
            D_0046C614 = 0;
            D_0067334C = 0;
            ExitDeleteThread();
        }
        if (D_0046C610 > 0) scePrintf(D_004930E0, D_00673340, D_0046C658);
        if (D_00673340 != 0) {
            if (VS(D_0046C658) != 0) ((void (*)(s32))D_00673340)(VS(D_0046C658));
        }
        VS(D_0046C630) = 0;
    }
}

void func_00269830(void) {
    SemaParam p;
    if (VS(D_0046C628) == -1 || VS(D_0046C62C) == -1) {
        p.option = 0;
        p.init_count = 1;
        p.max_count = 1;
        VS(D_0046C628) = CreateSema(&p);
        VS(D_0046C62C) = CreateSema(&p);
        p.init_count = 0;
        VS(D_0046C620) = CreateSema(&p);
        VS(D_0046C630) = 0;
    }
}

void func_002698c8(void) {
    s32 e;
    if (D_0046C614) {
        VS(D_0046C654) = -1;
        SignalSema(VS(D_0046C620));
    }
    DeleteSema(D_0046C628);
    DeleteSema(D_0046C62C);
    DeleteSema(D_0046C620);
    e = DIntr();
    func_00260430(0x80000012);
    if (e) EIntr();
}

s32 sceCdRead(u32 lbn, u32 sectors, void *buf, CdRMode *mode) {
    CdReadArg *a = &D_0046C700;
    s32 size;
    if (!(D_0046C634 & 1)) {
        if (func_00269f38() == 6) return 0;
    }
    if (!func_00269dc8(4)) return 0;
    a->lbn = lbn;
    a->sectors = sectors;
    a->buf = buf;
    a->mode.trycount = mode->trycount;
    a->mode.spindlctrl = mode->spindlctrl;
    a->mode.datapattern = mode->datapattern;
    a->x10 = D_0046D700;
    a->x14 = D_0046D7C0;
    switch (mode->datapattern) {
    case 1:
        size = sectors * 2328;
        break;
    case 2:
        size = sectors * 2340;
        break;
    case 0:
    default:
        size = sectors << 11;
        break;
    }
    D_0046D7C0[0] = 0;
    if (!(VS(D_0046C634) & 2)) func_00260738(buf, size);
    func_00260738(D_0046D700, 144);
    func_00260738(a, 24);
    func_00260738(D_0046D7C0, 4);
    if (D_0046C610 > 0) PRINTF(D_00493290);
    VS(D_0046C654) = 1;
    VS(D_0046C630) = 1;
    if (sceSifCallRpc(D_0046D7D0, 1, 1, a, 24, 0, 0, func_00269790, D_0046D700) < 0) {
        VS(D_0046C654) = 0;
        VS(D_0046C630) = 0;
        SignalSema(VS(D_0046C628));
        return 0;
    }
    if (D_0046C610 > 0) PRINTF(D_004932A8);
    return 1;
}

s32 func_0026a9d0(s32 a) {
    CdReadArg *p = &D_0046C700;
    if (func_00269f38() == 6) return 0;
    if (!func_00269dc8(9)) return 0;
    p->lbn = a;
    func_00260738(p, 4);
    VS(D_0046C654) = 4;
    VS(D_0046C630) = 1;
    if (sceSifCallRpc(D_0046D7D0, 5, 1, p, 4, 0, 0, func_00269558, &D_0046C654) < 0) {
        VS(D_0046C654) = 0;
        VS(D_0046C630) = 0;
        SignalSema(VS(D_0046C628));
        return 0;
    }
    return 1;
}
