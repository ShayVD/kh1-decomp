/* Leftover SCE SDK functions matched by hand (session s2), ee-gcc 2.9-991111. */
#include "common.h"

s32 iSignalSema(s32);
s32 sceCdSearchFile(void *, const char *, s32);
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

s32 func_002600d0(s32 i) {
    return D_0066E800[i];
}

s32 func_002600e8(s32 i, s32 v) {
    D_0066E800[i] = v;
    return v;
}

void func_00260400(s32 i, s32 a, s32 b) {
    u32 off = i << 3;
    if (i < 0) i = (u32)D_0066E6E4; else i = (u32)D_0066E6EC;
    off += i;
    ((E8 *)off)->a = a;
    ((E8 *)off)->b = b;
}

void func_00260430(s32 i) {
    u32 off = i << 3;
    if (i < 0) i = (u32)D_0066E6E4; else i = (u32)D_0066E6EC;
    off += i;
    ((E8 *)off)->a = 0;
}

s32 func_00260590(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    return func_00260458(a, 0, b, c, d, e, f);
}

s32 func_002605d0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    return func_00260458(a, 1, b, c, d, e, f);
}

u32 func_00260848(s32 cause, s32 h) {
    s32 old;
    if ((u32)(cause - 1) >= 13) return 0xffffffff;
    old = D_0046C1C8[cause];
    D_0046C1C8[cause] = h;
    if ((u32)(cause - 1) < 3) func_00257e10(cause, func_00260f40);
    else func_00257e20(cause, func_00260f40);
    return old;
}

void func_00260938(void) {
    Pair *p = D_0046C210;
    Pair *q;
    u32 i;
    func_00260928(p[0].a, p[0].b);
    func_002608d0(0x80075000, D_0046BE90, 816);
    FlushCache(0);
    FlushCache(2);
    func_00260928(p[1].a, p[1].b);
    func_00260928(p[2].a, p[2].b);
    q = &p[3];
    for (i = 3; i < 8; i++) {
        func_00260928(q->a, func_00260918(q->a));
        q++;
    }
    D_0046C208 = func_00260918(3);
}

s32 func_00260a30(s32 c) {
    if ((u32)(c - 13) >= 35) return -1;
    return func_00260a20(c);
}

s32 func_00260ac0(void) {
    if (GetMemorySize() == 0x2000000) return func_00260b00();
    return func_002585d0();
}

s32 func_00265558(void) {
    char buf[256];
    s32 fd;
    u32 i;
    char *p;
    fd = func_0025b588(D_00492920, 1);
    if (fd < 0) return -1;
    i = 0;
    p = buf;
    for (; i < 256; i++) {
        func_0025bbc8(fd, p, 1);
        if (*p++ == 0) break;
    }
    func_0025b810(fd);
    return func_002729d8(&buf[i - 9]) > 0x1315670;
}

void sceGsPutDispEnv(DispEnv *d) {
    if (((GsState *)sceGsGetGParam())->h6 == 1) {
        *(volatile u64 *)0x12000000 = d->pmode;
        *(volatile u64 *)0x12000070 = d->dispfb;
        *(volatile u64 *)0x12000080 = d->display;
        *(volatile u64 *)0x120000c0 = d->bgcolor;
    } else {
        *(volatile u64 *)0x12000000 = d->pmode;
        *(volatile u64 *)0x12000020 = d->smode2;
        *(volatile u64 *)0x12000090 = d->dispfb;
        *(volatile u64 *)0x120000a0 = d->display;
        *(volatile u64 *)0x120000e0 = d->bgcolor;
    }
}

s32 sceGsPutDrawEnv(u64 *tag) {
    u32 i = 0;
    while (R(0x1000a000) & 0x100) {
        if (i++ > 0x1000000) {
            scePrintf(D_00492968);
            return -1;
        }
    }
    R(0x1000a020) = (s32)(*tag & 0x7fff) + 1;
    if (((u32)tag & 0x70000000) == 0x70000000) R(0x1000a010) = ((u32)tag & 0x0fffffff) | 0x80000000;
    else R(0x1000a010) = (u32)tag & 0x0fffffff;
    R(0x1000a000) = 0x101;
    return 0;
}

s32 sceGsSyncV(void) {
    GsState *g = sceGsGetGParam();
    s64 f;
    if (g->x8 == 0) {
        func_002585f0();
        if (g->h0 == 1) return (*(volatile u64 *)0x12001000 >> 13) & 1;
    } else {
        f = (func_00258680() >> 13) & 1;
        if (g->h0 == 1) return f;
    }
}

s32 sceGsExecLoadImage(GsLoadImage *lp, void *src) {
    u32 i = 0;
    while (R(0x1000a000) & 0x100) {
        if (i++ > 0x1000000) {
            scePrintf(D_00492C50);
            return -1;
        }
    }
    R(0x1000a020) = 6;
    if (((u32)lp & 0x70000000) == 0x70000000) R(0x1000a010) = ((u32)lp & 0x0fffffff) | 0x80000000;
    else R(0x1000a010) = (u32)lp & 0x0fffffff;
    R(0x1000a000) = 0x101;
    while (R(0x1000a000) & 0x100) {
        if (i++ > 0x1000000) {
            scePrintf(D_00492C50);
            return -1;
        }
    }
    R(0x1000a020) = lp->tag2 & 0x7fff;
    if (((u32)src & 0x70000000) == 0x70000000) R(0x1000a010) = ((u32)src & 0x0fffffff) | 0x80000000;
    else R(0x1000a010) = (u32)src & 0x0fffffff;
    R(0x1000a000) = 0x101;
    return 0;
}

/* libdma: wait for a channel's CHCR.STR to clear. */
void func_00266ab0(volatile u32 *chcr) {
    s32 n = 0x1000000;
    while (*chcr & 0x100) {
        if (--n < 0) {
            scePrintf(D_00492E60);
            sceDmaPause(chcr);
        }
    }
}

void func_00266b20(volatile DmaCh *d, u32 addr, s32 t) {
#if 3 == 1
    s32 n = t ? t : 0x1000000;
#elif 3 == 2
    s32 n; if (t == 0) n = 0x1000000; else n = t;
#elif 3 == 3
    s32 n = 0x1000000; if (t != 0) n = t;
#else
    s32 n; if (t) n = t; else n = 0x1000000;
#endif
    while (d->madr < addr) {
        if (--n < 0) {
            scePrintf(D_00492E60);
            sceDmaPause(&d->chcr);
        }
    }
}

u32 func_00266ba8(u32 a) {
    if ((a >> 28) == 7) {
        a &= 0x0fffffff;
        a |= 0x80000000;
    }
    return a;
}

u32 sceDmaGetChan(u32 i) {
    if (i < 10) return D_0046C550[i];
    return 0;
}

s32 sceDmaReset(s32 enable) {
    u32 env[8];
    s32 old;
    s32 i;
    old = D_CTRL & 1;
    for (i = 0; i < 10; i++) {
        if (D_00492E78[i]) {
            DmaChReg *c = (DmaChReg *)D_0046C550[i];
            c->chcr = 0;
            c->tadr = 0;
            c->madr = 0;
            c->asr1 = 0;
            c->asr0 = 0;
            c->sadr = 0;
        }
    }
    {
        *(volatile u32 *)0x1000e010 = 0xff1f;
        *(u32 *)0x1000e010 = *(volatile u32 *)0x1000e010 & 0xff1f0000;
    }
    func_00266bd0(env, 20);
    sceDmaPutEnv((DmaEnv *)env);
    if (enable == 1) D_CTRL |= 1;
    return old;
}

s32 sceDmaPutEnv(DmaEnv *env) {
    u32 ctrl, pcr, sqwc, rbor, rbsr;
    ctrl = DREG(0x1000e000);
    pcr = DREG(0x1000e020);
    sqwc = DREG(0x1000e030);
    rbor = DREG(0x1000e050);
    rbsr = DREG(0x1000e040);
    if (env->sts >= 10) return -1;
    if (env->std >= 10) return -2;
    if (env->mfd >= 10) return -3;
    if (env->rcyc >= 7) return -4;
    ctrl = (ctrl & ~0x30) | (D_00492EA0[env->sts] << 4);
    ctrl = (ctrl & ~0xc0) | (D_00492EB0[env->std] << 6);
    ctrl = (ctrl & ~0x0c) | (D_00492EC0[env->mfd] << 2);
    if (env->rcyc) {
        ctrl |= 2;
        ctrl = (ctrl & ~0x300) | ((env->rcyc - 1) << 8);
    } else {
        ctrl &= ~2;
    }
    pcr = (env->express << 16) | env->notify;
    sqwc = (env->tqwc << 16) | env->sqwc;
    rbor = (u32)env->rbadr;
    rbsr = env->rbmsk;
    DREG(0x1000e000) = ctrl;
    DREG(0x1000e020) = pcr;
    DREG(0x1000e030) = sqwc;
    DREG(0x1000e050) = rbor;
    DREG(0x1000e040) = rbsr;
    D_0066FAD8 = *(S20 *)env;
    return 0;
}

S20 *sceDmaGetEnv(S20 *d) {
    *d = D_0066FAD8;
    return d;
}

void sceDmaRecvN(DmaCh *d, u32 addr, u32 qwc) {
    u32 a = func_00266ba8(addr);
    func_00266ab0(&d->chcr);
    if (d->madr != 0xffffffff) d->madr = a;
    d->qwc = qwc;
    {
        Chcr c = *(Chcr *)&d->chcr;
        c.mod = 0;
        c.dir = 0;
        c.str = 1;
        *(Chcr *)&d->chcr = c;
    }
}

u32 sceDmaPause(volatile u32 *chcr) {
    s32 e;
    u32 en, old;
    e = DIntr();
    en = *(volatile u32 *)0x1000f520;
    if (!(en & 0x10000)) *(volatile u32 *)0x1000f590 = en | 0x10000;
    *(volatile u32 *)0x1000e000;
    old = *chcr;
    *chcr = old & ~0x100;
    *(volatile u32 *)0x1000f590 = en;
    if (e) EIntr();
    return old;
}

void sceVu0NormalLightMatrix(f32 *m, f32 *a, f32 *b, f32 *c) {
    f32 v[4];
    sceVu0ScaleVector(v, a, -1.0f);
    sceVu0Normalize(m, v);
    sceVu0ScaleVector(v, b, -1.0f);
    sceVu0Normalize(m + 4, v);
    sceVu0ScaleVector(v, c, -1.0f);
    sceVu0Normalize(m + 8, v);
    m[12] = m[13] = m[14] = 0.0f;
    m[15] = 1.0f;
    sceVu0TransposeMatrix(m, m);
}

/* RPC 0x80000963 into the 1 KB buffer D_0066FB80; returns its first word. */
s32 func_00268040(void) {
    sceSifCallRpc(D_0066FB08, 0x80000963, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0);
    return D_0066FB80[0];
}

s32 sceDbcInit(void) {
    s32 i, v, maj;
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(D_0066FB08, 0x80000900, 0) < 0) {
            func_00268a78(D_00492ED0);
            exit(-1);
        }
        if (((SifClient *)D_0066FB08)->server) break;
        i = 0x10000;
        while (--i != -1);
    }
    while (1) {
        if (sceSifBindRpc(D_0066FB30, 0x8000091b, 0) < 0) {
            func_00268a78(D_00492ED0);
            exit(-1);
        }
        if (((SifClient *)D_0066FB30)->server) break;
        i = 0x10000;
        while (--i != -1);
    }
    v = func_00268040();
    maj = v >> 8;
    if (maj != 2) {
        scePrintf(D_00492EE8);
        scePrintf(D_00492F10, 2, 0, maj, v & 0xff);
        return 0;
    }
    for (i = 15; i >= 0; i--) D_00670000[i] = 0;
    func_00268a78(D_00492F38, D_0066FF80);
    sceDbcSetWorkAddr((s32)D_0066FF80);
    return 1;
}

s32 sceDbcSetWorkAddr(s32 addr) {
    D_0066FB80[1] = addr;
    if (sceSifCallRpc(D_0066FB08, 0x80000904, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00492F50);
        return 0;
    }
    return D_0066FB80[0];
}

s32 sceDbcDeleteSocket(s32 s) {
    D_0066FB80[0] = s;
    if (sceSifCallRpc(D_0066FB08, 0x80000902, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00492F90);
        return 0;
    }
    return D_0066FB80[1];
}

s32 sceDbcGetDepNumber(s32 s) {
    SyncDCache(D_0066FF80, D_0066FF80 + 128);
    DIntr();
    *(Blk64 *)D_00670000 = *(Blk64 *)D_0066FF80;
    EIntr();
    if (D_00670000[s] != 1) return -12;
    D_0066FB80[0] = s;
    if (sceSifCallRpc(D_0066FB08, 0x80000903, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00492FB0);
        return 0;
    }
    return D_0066FB80[1];
}

s32 sceDbcInitSocket(s32 s) {
    D_0066FB80[0] = s;
    if (sceSifCallRpc(D_0066FB08, 0x80000915, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00492FD0);
        return 0;
    }
    return D_0066FB80[1];
}

s32 sceDbcResetSocket(s32 s) {
    D_0066FB80[0] = s;
    if (sceSifCallRpc(D_0066FB08, 0x80000916, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00492FF0);
        return 0;
    }
    return D_0066FB80[1];
}

s32 sceDbcGetDeviceStatus(s32 s) {
    D_0066FB80[0] = s;
    if (sceSifCallRpc(D_0066FB08, 0x80000917, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00493010);
        return 0;
    }
    return D_0066FB80[1];
}

s32 sceDbcSRData(s32 sock, u32 cmd, s32 *slen, u8 *sdata, s32 *rlen, u8 *rdata) {
    s32 *p = D_0066FB80;
    s32 i;
    D_0066FB80[0] = sock;
    p[1] = cmd;
    p[2] = *slen;
    p[3] = *rlen;
    for (i = 0; i < *slen; i++) { u8 *d = (u8 *)&p[4]; d[i] = sdata[i]; }
    if (sceSifCallRpc(D_0066FB08, 0x80000918, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00493038);
        return 0;
    }
    if (p[68] >= 0) {
        *slen = p[2];
        *rlen = p[3];
        for (i = 0; i < p[3]; i++) { u8 *d = (u8 *)&p[36]; rdata[i] = d[i]; }
    }
    return p[68];
}

s32 sceDbcSendData(s32 sock, u32 cmd, s32 *len, u8 *data) {
    s32 *p = D_0066FB80;
    s32 i;
    D_0066FB80[0] = sock;
    p[1] = cmd;
    p[2] = *len;
    for (i = 0; i < *len; i++) { u8 *d = (u8 *)&p[3]; d[i] = data[i]; }
    if (sceSifCallRpc(D_0066FB08, 0x80000919, 0, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00493058);
        return 0;
    }
    if (p[35] >= 0) *len = p[2];
    return p[35];
}

s32 sceDbcSendData2(s32 sock, u32 cmd, s32 *len, u8 *data) {
    s32 *p = D_0066FB80;
    s32 i;
    D_0066FB80[0] = sock;
    p[1] = cmd;
    p[2] = *len;
    for (i = 0; i < *len; i++) { u8 *d = (u8 *)&p[3]; d[i] = data[i]; }
    if (func_0025a750(D_0066FB30) == 1) return 0;
    if (sceSifCallRpc(D_0066FB30, 0x8000091b, 1, D_0066FB80, 1024, D_0066FB80, 1024, 0, 0) < 0) {
        func_00268a78(D_00493078);
        return 0;
    }
    return 1;
}

s32 sceDbcReceiveData(s32 sock, u32 cmd, s32 *len, u8 *data) {
    s32 *p = D_0066FB80;
    s32 i;
    D_0066FB80[0] = sock;
    p[1] = cmd;
    p[2] = *len;
    if (sceSifCallRpc(D_0066FB08, 0x8000091a, 0, p, 1024, p, 1024, 0, 0) < 0) {
        func_00268a78(D_00493098);
        return 0;
    }
    if (p[35] >= 0) {
        *len = p[2];
        for (i = 0; i < p[2]; i++) { u8 *d = (u8 *)&p[3]; data[i] = d[i]; }
    }
    return p[35];
}

/* Empty varargs function, called from libdbc's bind retry loop. */
void func_00268a78(const char *fmt, ...) {
}

s32 scePad2CreateSocket(Pad2SockParam *param, PadBuf *buf) {
    DbcSockCfg cfg;
    s32 s, i;
    PadBuf *b;
    if ((u32)buf & 0x3f) return -1;
    if (param) {
        cfg.w[0] = param->x0;
        cfg.w[2] = param->x4;
        cfg.w[3] = param->x8;
        cfg.w[4] = param->xc;
        cfg.name = param->name;
    } else {
        cfg.w[0] = 0;
        cfg.w[2] = 0;
        cfg.w[3] = 0;
        cfg.w[4] = 0;
        cfg.name.n[0] = 0;
    }
    cfg.w[1] = 1;
    cfg.w[0] |= 1;
    s = sceDbcCreateSocket(&cfg, buf, buf + 1);
    if (s < 0) return s;
    D_00670040[s].x0 = 1;
    D_00670040[s].buf = buf;
    b = buf;
    for (i = 0; i < 2; i++) {
        b->b0 = 0;
        b->cnt = 0;
        b->b1 = 0;
        b->b3 = 0;
        b->b2 = 0;
        b->x4 = 0;
        memset(b->m, 0xff, 32);
        b++;
    }
    return s;
}

s32 scePad2DeleteSocket(s32 s) {
    s32 r = sceDbcDeleteSocket(s);
    if (r < 0) return r;
    D_00670040[s].x0 = 0;
    D_00670040[s].x4 = 0;
    D_00670040[s].x8 = 0;
    return 1;
}

s32 scePad2Read(s32 s, u8 *buf) {
    u8 *b;
    if (D_00670040[s].x0 == 0) return -1;
    if (D_00670040[s].x4 == 0) {
        if (func_002690d0(s) < 0) return -1;
    }
    b = (u8 *)func_00269128(s);
    if (b[2]) {
        u8 *d = b + 28;
        if (d) {
            memcpy(buf, d, b[2]);
            func_00269210(b + (b[2] + 28), D_00670040[s].btn);
        }
    }
    if (((s32 *)b)[1] == 0) return -1;
    return b[2];
}

/* libpad2 passes the command word as an int (sign-extended), unlike libvib. */
s32 scePad2GetButtonProfile(s32 s, u8 *profile) {
    DbcU c;
    s32 n;
    s32 r;
    if (D_00670040[s].x4 == 0 && func_002690d0(s) < 0) return -1;
    c.f.a = 2;
    c.f.b = 3;
    c.f.c = 2;
    c.f.d = 1;
    r = sceDbcReceiveData(s, c.w, &n, profile);
    if (r < 0) return r;
    func_00269210(profile, D_00670040[s].btn);
    return n;
}

s32 scePad2GetState(s32 s) {
    DbcU c;
    u8 st;
    s32 n;
    PadBuf *b;
    if (D_00670040[s].x4 == 0 && func_002690d0(s) < 0) return 0;
    if (func_00269190(s)) {
        b = func_00269128(s);
        if (b->x4 == 0 && func_002690d0(s) < 0) {
            D_00670040[s].x4 = 0;
            return 0;
        }
        st = b->b0;
    } else {
        c.f.a = 12;
        c.f.b = 2;
        c.f.c = 1;
        c.f.d = 1;
        if (sceDbcReceiveData(s, c.w, &n, &st) < 0) return 0;
    }
    return st;
}

s32 func_00268ff0(s32 s, u8 *data, s32 btn) {
    BtnEnt e = D_00670040[s].btn[btn];
    u8 v;
    if (e.valid) {
        switch (e.type) {
        case 1:
            if ((data[e.idx] >> e.shift) & 1) return 0;
            return 1;
        case 8:
            v = data[e.idx] >> e.shift;
            if (e.shift) {
                e.idx++;
                v |= data[e.idx] << (e.type - e.shift);
            }
            return v;
        }
        return -1;
    }
    return -1;
}

/* Caches sceDbcGetDepNumber in the socket slot. */
s32 func_002690d0(s32 s) {
    s32 r = sceDbcGetDepNumber(s);
    if (r < 0) return r;
    D_00670040[s].x8 = r;
    D_00670040[s].x4 = 1;
    return r;
}

/* libpad2: the newer of the slot's two DMA buffers (counter at +124). */
PadBuf *func_00269128(s32 s) {
    PadBuf *p[2];
    PadBuf *b = D_00670040[s].buf;
    p[0] = b;
    p[1] = (PadBuf *)((u8 *)b + 128);
    SyncDCache(b, (u8 *)b + 256);
    return p[p[0]->cnt < p[1]->cnt];
}

/* libpad2: has either DMA buffer's counter changed since the last call? */
s32 func_00269190(s32 s) {
    PadBuf *p[2];
    PadBuf *b = D_00670040[s].buf;
    p[0] = b;
    p[1] = (PadBuf *)((u8 *)b + 128);
    if (p[0]->cnt == 0) return 0;
    if (D_0046C5D8[0] == p[0]->cnt && D_0046C5D8[1] == p[1]->cnt) return 0;
    D_0046C5D8[0] = p[0]->cnt;
    D_0046C5D8[1] = p[1]->cnt;
    return 1;
}

s32 func_00269210(u8 *bits, void *ep) {
    BtnEnt *e = ep;
    s32 bit = 0, idx = 0, i, shift = 0;
    for (i = 0; i < 40; i++, e++) {
        if ((*bits >> bit) & 1) {
            e->valid = 1;
            e->idx = idx;
            e->shift = shift;
            if ((i >= 16 && i < 32) || (i >= 35 && i < 39)) {
                e->type = 8;
                idx++;
            } else {
                shift++;
                e->type = 1;
                if ((shift & 7) == 0) {
                    idx++;
                    shift = 0;
                }
            }
        } else {
            e->valid = 0;
            e->idx = 0;
            e->shift = 0;
        }
        if ((++bit & 7) == 0) {
            bits++;
            bit = 0;
        }
    }
    return 1;
}

/* strcpy(buf, "") inlined: D_004930D8 is the "" after libpad2's state names. */
void scePad2StateIntToStr(u32 state, char *buf) {
    if (state < 4) strcpy(buf, D_0046C5E0[state]);
    else buf[0] = D_004930D8[0];
}

s32 sceVibGetProfile(s32 sock, u8 *profile) {
    DbcCmd c;
    s32 n;
    s32 r;
    c.a = 2;
    c.b = 2;
    c.c = 3;
    c.d = 1;
    r = DbcRecvC(sock, c, &n, profile);
    if (r < 0) return r;
    return n;
}

s32 sceVibSetActParam(s32 s, s32 n1, u8 *p1, s32 n2, u8 *p2) {
    DbcCmd c;
    VibBuf b;
    s32 len;
    c.a = 11;
    c.b = 1;
    c.c = 3;
    len = 40;
    c.d = 1;
    b.n1 = n2;
    memcpy(b.d, p2, n2);
    b.n0 = n1;
    memcpy(b.d + n2, p1, n1);
    return DbcSend2C(s, c, &len, &b);
}

/* Interrupt handler: signal the semaphore in the handler argument, then
 * ExitHandler (sync; ei). */
s32 func_00269468(s32 a, s32 b, s32 sema) {
    iSignalSema(sema);
    __asm__ volatile("sync.l; ei");
}

/* Sleep for n alarm ticks: alarm handler func_00269468 signals the sema. */
void func_00269490(u16 n) {
    SemaParam p;
    s32 s;
    p.max_count = 1;
    p.init_count = 0;
    p.option = 0;
    s = CreateSema(&p);
    func_00257ee0(n, func_00269468, s);
    WaitSema(s);
    DeleteSema(s);
}

s32 func_002694f8(s32 a) {
    s32 e, old;
    if (func_00269fd0(1)) return 0;
    e = DIntr();
    old = D_00673340;
    D_00673340 = a;
    if (e) EIntr();
    return old;
}

/* The cdvd state words are volatile here (and plain in the other functions). */
void func_00269558(s32 *p) {
    VS(D_0046C654) = *p;
    VS(D_0046C658) = VS(D_0046C654);
    if (VS(D_0046C654) == 11) {
        VS(D_0046C654) = 0;
        VS(D_0046C630) = 0;
        return;
    }
    iSignalSema(VS(D_0046C628));
    if (VS(D_0046C614) && VS(D_00673340)) iSignalSema(VS(D_0046C620));
    else VS(D_0046C630) = 0;
    VS(D_0046C654) = 0;
}

s32 func_002696b8(s32 prio, void *stack, s32 size) {
    s32 r = 1;
    if (D_0046C614 == 0) {
        s32 id = GetThreadId();
        D_00673350 = id;
        ReferThreadStatus(id, D_00673358);
        D_00673388.stack_size = size;
        D_00673388.gp_reg = D_00494050;
        D_00673388.func = func_002695f8;
        D_00673388.stack = stack;
        D_00673388.initial_priority = prio;
        D_0046C614 = CreateThread(&D_00673388);
        StartThread(D_0046C614, 0);
    } else {
        ChangeThreadPriority(D_0046C614, prio);
        r = 0;
    }
    return r;
}

void func_00269790(u32 a) {
    McXfer *x = (McXfer *)(a | 0x20000000);
    s32 i;
    if (x->n0 > 0) {
        u8 *d = x->d0;
        for (i = 0; i < x->n0; i++) d[i] = x->b0[i];
    }
    if (x->n1 > 0) {
        u8 *d = x->d1;
        for (i = 0; i < x->n1; i++) d[i] = x->b1[i];
    }
    func_00269558((s32 *)&D_0046C654);
}

void *func_00269960(void *cb, s32 arg) {
    s32 e;
    void *old;
    if (D_0046C63C < 0) func_00269a18();
    e = DIntr();
    old = D_00673344;
    D_00673348 = arg;
    D_00673344 = cb;
    if (e) EIntr();
    return old;
}

void func_002699d8(void) {
    if (D_00673344) {
        if (D_0046C624 == 0) ((void (*)(s32))D_00673344)(D_00673348);
    }
}

s32 func_00269a18(void) {
    s32 e;
    D_0046C624 = 1;
    e = DIntr();
    func_00260400(0x80000012, (s32)func_002699d8, 0);
    if (e) EIntr();
    D_0046C624 = 0;
    D_0046C63C = 1;
    return 1;
}

s32 func_00269da8(void *file, const char *name) {
    return sceCdSearchFile(file, name, 0);
}

s32 func_00269dc8(s32 cmd) {
    s32 i;
    func_00269830();
    if (VS(D_0046C628) != PollSema(VS(D_0046C628))) {
        if (D_0046C610 > 0) scePrintf(D_00493178, cmd, D_0046C61C);
        return 0;
    }
    D_0046C61C = cmd;
    ReferThreadStatus(D_00673350, D_00673358);
    if (func_00269fd0(1)) {
        SignalSema(VS(D_0046C628));
        return 0;
    }
    sceSifInitRpc(0);
    if ((i = VS(D_0046C638)) >= 0) return 1;
    while (1) {
        if (sceSifBindRpc(D_0046D7D0, 0x80000595, 0) < 0) {
            if (D_0046C610 > 0) scePrintf(D_004931A0);
            i = 0x100000;
            while (--i != -1);
            continue;
        }
        if (((SifClient *)D_0046D7D0)->server) break;
        i = 0x100000;
        while (--i != -1);
    }
    D_0046C638 = 0;
    return 1;
}

s32 func_00269f38(void) {
    s32 r;
    if (!func_00269dc8(2)) return 0;
    if (sceSifCallRpc(D_0046D7D0, 14, 0, 0, 0, D_0046C680, 4, 0, 0) < 0) {
        SignalSema(D_0046C628);
        return 0;
    }
    r = *(s32 *)((u32)D_0046C680 | 0x20000000);
    SignalSema(D_0046C628);
    return r;
}

s32 func_00269fd0(s32 mode) {
    if (mode == 0) {
        if (D_0046C610 > 0) scePrintf(D_004931B8);
        while (D_0046C630 || func_0025a750(D_0046D7D0)) func_00269490(60);
        return 0;
    }
    if (D_0046C630 || func_0025a750(D_0046D7D0)) return 1;
    return 0;
}

s32 func_0026a070(s32 mode) {
    if (mode == 0) {
        if (D_0046C610 > 0) scePrintf(D_004931C8);
        while (func_0025a750(D_0046E048)) func_00269490(60);
        return 0;
    }
    return func_0025a750(D_0046E048);
}

s32 func_0026a0e0(s32 cmd) {
    s32 i;
    func_00269830();
    if (VS(D_0046C62C) != PollSema(VS(D_0046C62C))) {
        if (D_0046C610 > 0) scePrintf(D_004931D8, cmd, D_0046C618);
        return 0;
    }
    D_0046C618 = cmd;
    ReferThreadStatus(D_00673350, D_00673358);
    if (func_0026a070(1)) {
        SignalSema(VS(D_0046C62C));
        return 0;
    }
    sceSifInitRpc(0);
    if ((i = VS(D_0046C648)) >= 0) return 1;
    while (1) {
        if (sceSifBindRpc(D_0046E048, 0x80000593, 0) < 0) {
            if (D_0046C610 > 0) scePrintf(D_00493200);
            i = 0x100000;
            while (--i != -1);
            continue;
        }
        if (((SifClient *)D_0046E048)->server) break;
        i = 0x100000;
        while (--i != -1);
    }
    D_0046C648 = 0;
    return 1;
}

s32 func_0026a728(s32 a) {
    s32 *p = &D_0046DC40;
    s32 r;
    if (!func_0026a0e0(34)) return 0;
    D_0046DC40 = a;
    func_00260738(p, 4);
    if (sceSifCallRpc(D_0046E048, 34, 0, p, 4, D_0046D800, 4, 0, 0) < 0) {
        SignalSema(D_0046C62C);
        return 0;
    }
    r = *UNCACHED(D_0046D800);
    SignalSema(D_0046C62C);
    return r;
}

s32 func_0026aaa0(void) {
    s32 r;
    if (!func_0026a0e0(3)) return -1;
    if (sceSifCallRpc(D_0046E048, 4, 0, 0, 0, D_0046D800, 4, 0, 0) < 0) {
        SignalSema(D_0046C62C);
        return -1;
    }
    r = *(s32 *)((u32)D_0046D800 | 0x20000000);
    SignalSema(D_0046C62C);
    return r;
}

s32 func_0026ab38(void) {
    s32 r;
    if (!func_0026a0e0(2)) return -1;
    if (sceSifCallRpc(D_0046E048, 12, 0, 0, 0, D_0046D800, 4, 0, 0) < 0) {
        SignalSema(D_0046C62C);
        return -1;
    }
    r = *UNCACHED(D_0046D800);
    SignalSema(D_0046C62C);
    if (D_0046C610 >= 2) scePrintf(D_004932B8);
    return r;
}

s32 func_0026abf0(void) {
    s32 r;
    if (!func_0026a0e0(30)) return 0;
    VS(D_0046C654) = 8;
    if (sceSifCallRpc(D_0046E048, 22, 0, 0, 0, D_0046D800, 4, 0, 0) < 0) {
        SignalSema(VS(D_0046C62C));
        VS(D_0046C654) = 0;
        return 0;
    }
    VS(D_0046C654) = 0;
    r = *UNCACHED(D_0046D800);
    SignalSema(VS(D_0046C62C));
    return r;
}

s32 func_0026aca8(s32 *out) {
    s32 r;
    if (!func_0026a0e0(33)) return 0;
    if (sceSifCallRpc(D_0046E048, 33, 0, 0, 0, D_0046D800, 8, 0, 0) < 0) {
        SignalSema(D_0046C62C);
        return 0;
    }
    *out = *UNCACHED(&D_0046D800[1]);
    r = *UNCACHED(D_0046D800);
    SignalSema(D_0046C62C);
    return r;
}

s32 sceMcInit(void) {
    SemaParam p;
    s32 i, r;
    if (D_0046E094 < 0) {
        p.init_count = 1;
        p.max_count = 1;
        p.option = 0;
        D_0046E094 = CreateSema(&p);
    }
    sceMcSync(0, 0, 0);
    WaitSema(D_0046E094);
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(&D_00673600, 0x80000400, 0) < 0) {
            scePrintf(D_00493FA0);
            while (1);
        }
        if (D_00673600.server) break;
        i = 0x100000;
        while (--i);
    }
    r = sceSifCallRpc(&D_00673600, 254, 0, &D_00673680, 48, D_00674BC0, 12, 0, 0);
    SignalSema(D_0046E094);
    if (r < 0) {
        D_00673600.server = 0;
        return r - 100;
    }
    if (D_00674BC0[1] < 522) {
        scePrintf(D_00493FB8);
        D_00673600.server = 0;
        return -120;
    }
    if (D_00674BC0[2] < 526) {
        scePrintf(D_00493FE0);
        D_00673600.server = 0;
        return -121;
    }
    return D_00674BC0[0];
}

s32 func_00270d88(s32 a) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x14 = a;
    r = sceSifCallRpc(&D_00673600, 20, 1, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 20;
    else SignalSema(D_0046E094);
    return r;
}

s32 sceMcGetSlotMax(s32 a) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x4 = a;
    r = sceSifCallRpc(&D_00673600, 21, 0, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r != 0) {
        SignalSema(D_0046E094);
        return r;
    }
    SignalSema(D_0046E094);
    return D_00674BC0[0];
}

s32 sceMcOpen(s32 a, s32 b, const char *name, s32 d) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    if (name == 0 || *name == 0) {
        SignalSema(D_0046E094);
        return -210;
    }
    func_00265190(D_006736B0.name, name, 1023);
    D_006736B0.x0 = a;
    D_006736B0.x8 = d;
    D_006736B0.x4 = b;
    D_006736B0.name[1023] = 0;
    r = sceSifCallRpc(&D_00673600, 2, 1, &D_006736B0, 1044, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 2;
    else SignalSema(D_0046E094);
    return r;
}

s32 sceMcMkdir(s32 a, s32 b, const char *c) {
    s32 r = sceMcOpen(a, b, c, 64);
    if (r == 0) D_0046E090 = 11;
    return r;
}

s32 sceMcClose(s32 a) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x0 = a;
    r = sceSifCallRpc(&D_00673600, 3, 1, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 3;
    else SignalSema(D_0046E094);
    return r;
}

s32 func_00271128(s32 a, s32 b, s32 c) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x0 = a;
    D_00673680.x10 = b;
    D_00673680.x14 = c;
    r = sceSifCallRpc(&D_00673600, 4, 1, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 4;
    else SignalSema(D_0046E094);
    return r;
}

void func_00271200(u32 a) {
    McXfer *x = (McXfer *)(a | 0x20000000);
    s32 i;
    u8 *d;
    if (x->n0) {
        d = x->d0;
        for (i = 0; i < x->n0; i++) *d++ = x->b0[i];
    }
    if (x->n1) {
        d = x->d1;
        for (i = 0; i < x->n1; i++) *d++ = x->b1[i];
    }
}

s32 sceMcRead(s32 a, void *buf, s32 size) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x0 = a;
    D_00673680.x18 = buf;
    D_00673680.xc = size;
    D_00673680.x1c = D_00673B00;
    func_00260738(buf, size);
    func_00260738(D_00673B00, 192);
    r = sceSifCallRpc(&D_00673600, 5, 1, &D_00673680, 48, D_00674BC0, 4, func_00271200, D_00673B00);
    if (r == 0) D_0046E090 = 5;
    else SignalSema(D_0046E094);
    return r;
}

s32 sceMcWrite(s32 a, u8 *buf, s32 size) {
    s32 r;
    u32 i;
    s32 n;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x0 = a;
    if (size < 17) {
        D_00673680.x14 = size;
        D_00673680.xc = 0;
        D_00673680.x18 = 0;
    } else {
        {
            u8 *top = (u8 *)(((u32)buf - 1) & ~0xf);
            u8 *bot = buf - 16;
            n = top - bot;
        }
        D_00673680.xc = size - n;
        D_00673680.x14 = n;
        D_00673680.x18 = buf + n;
    }
    for (i = 0; i < D_00673680.x14; i++) D_00673680.data[i] = buf[i];
    FlushCache(0);
    r = sceSifCallRpc(&D_00673600, 6, 1, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 6;
    else SignalSema(D_0046E094);
    return r;
}

s32 func_00271530(s32 a, s32 b, s32 sema) {
    func_0025fd10(sema);
    __asm__ volatile("sync.l; ei");
}

s32 sceMcSync(s32 mode, s32 *cmd, s32 *result) {
    s32 r;
    if (D_0046E090 == 0) return -1;
    r = func_0025a750(&D_00673600);
    if (mode == 0 && r) {
        while (func_0025a750(&D_00673600)) func_00271558(60);
        r = 0;
    }
    r = (r == 0);
    if (cmd) *cmd = D_0046E090;
    if (r) {
        D_0046E090 = 0;
        if (result) *result = D_00674BC0[0];
        SignalSema(D_0046E094);
    }
    return r;
}

void func_00271680(u32 a) {
    s32 *p = (s32 *)(a | 0x20000000);
    if (D_00673628) *D_00673628 = p[0];
    if (D_0067362C) *D_0067362C = p[1];
    if (D_00673630) *D_00673630 = p[36];
}

s32 sceMcGetInfo(s32 a, s32 b, s32 *c, s32 *d, s32 *e) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x4 = a;
    D_00673680.x8 = b;
    D_00673680.x1c = D_00673B00;
    if (c) D_00673680.x14 = 1;
    else D_00673680.x14 = 0;
    if (d) D_00673680.x10 = 1;
    else D_00673680.x10 = 0;
    if (e) D_00673680.xc = 1;
    else D_00673680.xc = 0;
    D_00673628 = c;
    D_0067362C = d;
    D_00673630 = e;
    func_00260738(D_00673B00, 192);
    r = sceSifCallRpc(&D_00673600, 1, 1, &D_00673680, 48, D_00674BC0, 4, func_00271680, D_00673B00);
    if (r == 0) D_0046E090 = 1;
    else SignalSema(D_0046E094);
    return r;
}

/* "sceMcUdCheckNewCard RPC faild" */
s32 func_00271860(void) {
    if (sceSifCallRpc(&D_00673600, 53, 0, &D_00673680, 48, D_00674BC0, 4, 0, 0) != 0) {
        scePrintf(D_00494008);
        return -1;
    }
    return D_00674BC0[0];
}

s32 sceMcGetDir(s32 a, s32 b, const char *name, s32 d, s32 n, void *buf) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    if (name == 0 || *name == 0) {
        SignalSema(D_0046E094);
        return -210;
    }
    D_006736B0.x0 = a;
    D_006736B0.x4 = b;
    D_006736B0.x8 = d;
    D_006736B0.xc = n;
    D_006736B0.x10 = buf;
    func_00265190(D_006736B0.name, name, 1023);
    D_006736B0.name[1023] = 0;
    if (n >= 0) func_00260738(buf, n << 6);
    r = sceSifCallRpc(&D_00673600, 13, 1, &D_006736B0, 1044, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 13;
    else SignalSema(D_0046E094);
    return r;
}

void func_00271a28(char *dst) {
    u32 n;
    if (dst == 0) return;
    if (strlen((char *)((u32)D_00673BC0 | 0x20000000)) < 1024)
        n = strlen((char *)((u32)D_00673BC0 | 0x20000000));
    else n = 1023;
    memcpy(dst, (char *)((u32)D_00673BC0 | 0x20000000), n);
    dst[n] = 0;
}

s32 sceMcChdir(s32 a, s32 b, const char *name, void *d) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    if (name == 0 || *name == 0) {
        SignalSema(D_0046E094);
        return -210;
    }
    D_006736B0.x0 = a;
    D_006736B0.x4 = b;
    D_006736B0.x10 = D_00673BC0;
    func_00265190(D_006736B0.name, name, 1023);
    D_006736B0.name[1023] = 0;
    func_00260738(D_00673BC0, 1024);
    r = sceSifCallRpc(&D_00673600, 12, 1, &D_006736B0, 1044, D_00674BC0, 4, func_00271a28, d);
    if (r == 0) D_0046E090 = 12;
    else SignalSema(D_0046E094);
    return r;
}

s32 sceMcFormat(s32 a, s32 b) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x8 = b;
    D_00673680.x4 = a;
    r = sceSifCallRpc(&D_00673600, 16, 1, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 16;
    else SignalSema(D_0046E094);
    return r;
}

s32 sceMcDelete(s32 a, s32 b, const char *name) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    if (name == 0 || *name == 0) {
        SignalSema(D_0046E094);
        return -210;
    }
    func_00265190(D_006736B0.name, name, 1023);
    D_006736B0.x0 = a;
    D_006736B0.x4 = b;
    D_006736B0.name[1023] = 0;
    D_006736B0.x8 = 0;
    r = sceSifCallRpc(&D_00673600, 15, 1, &D_006736B0, 1044, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 15;
    else SignalSema(D_0046E094);
    return r;
}

s32 func_00271df0(s32 a) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x0 = a;
    r = sceSifCallRpc(&D_00673600, 10, 1, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 10;
    else SignalSema(D_0046E094);
    return r;
}

s32 func_00271ea8(s32 a, s32 b, const char *name, Blk64 *d, s32 e) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    if (name == 0 || *name == 0) {
        SignalSema(D_0046E094);
        return -210;
    }
    e &= 7;
    D_006736B0.x0 = a;
    D_006736B0.x4 = b;
    D_006736B0.x8 = e;
    *(Blk64 *)D_00673640 = *d;
    D_006736B0.x10 = D_00673640;
    func_00265190(D_006736B0.name, name, 1023);
    D_006736B0.name[1023] = 0;
    FlushCache(0);
    r = sceSifCallRpc(&D_00673600, 14, 1, &D_006736B0, 1044, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 14;
    else SignalSema(D_0046E094);
    return r;
}

s32 sceMcRename(s32 a, s32 b, const char *name, const char *name2) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    if (name == 0 || *name == 0 || name2 == 0) {
        SignalSema(D_0046E094);
        return -210;
    }
    D_006736B0.x0 = a;
    D_006736B0.x4 = b;
    D_006736B0.x8 = 16;
    func_00265190(D_006736B0.name, name, 1023);
    D_006736B0.name[1023] = 0;
    func_00265190(D_00673640 + 32, name2, 32);
    D_00673640[63] = 0;
    D_006736B0.x10 = D_00673640;
    FlushCache(0);
    r = sceSifCallRpc(&D_00673600, 14, 1, &D_006736B0, 1044, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 19;
    else SignalSema(D_0046E094);
    return r;
}

s32 sceMcUnformat(s32 a, s32 b) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    D_00673680.x8 = b;
    D_00673680.x4 = a;
    r = sceSifCallRpc(&D_00673600, 17, 1, &D_00673680, 48, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 17;
    else SignalSema(D_0046E094);
    return r;
}

s32 func_002722b0(s32 a, s32 b, const char *name) {
    s32 r;
    if (PollSema(D_0046E094) < 0) return -200;
    if (D_00673600.server == 0) {
        SignalSema(D_0046E094);
        return -100;
    }
    if (name == 0 || *name == 0) {
        SignalSema(D_0046E094);
        return -210;
    }
    D_006736B0.x0 = a;
    D_006736B0.x4 = b;
    func_00265190(D_006736B0.name, name, 1023);
    D_006736B0.name[1023] = 0;
    r = sceSifCallRpc(&D_00673600, 18, 1, &D_006736B0, 1044, D_00674BC0, 4, 0, 0);
    if (r == 0) D_0046E090 = 18;
    else SignalSema(D_0046E094);
    return r;
}

/* libipu: write a DMA channel's CHCR (fromIPU 0x1000B000, toIPU 0x1000B400)
 * with the channel held in D_ENABLEW (0x1000F590). */
void func_002723c8(u32 v) {
    DIntr();
    *(volatile u32 *)0x1000f590 = *(volatile u32 *)0x1000f520 | 0x10000;
    *(volatile u32 *)0x1000b000 = v;
    *(volatile u32 *)0x1000f590 = *(volatile u32 *)0x1000f520 & ~0x10000;
    EIntr();
}

void func_00272430(u32 v) {
    DIntr();
    *(volatile u32 *)0x1000f590 = *(volatile u32 *)0x1000f520 | 0x10000;
    *(volatile u32 *)0x1000b400 = v;
    *(volatile u32 *)0x1000f590 = *(volatile u32 *)0x1000f520 & ~0x10000;
    EIntr();
}

void func_00272498(u32 *env) {
    func_00272430(1);
    env[0] = R(0x1000b410);
    env[1] = R(0x1000b430);
    env[2] = R(0x1000b420);
    env[3] = R(0x1000b400);
    while (R(0x10002010) & 0xf0);
    func_002723c8(0);
    env[4] = R(0x1000b010);
    env[5] = R(0x1000b020);
    env[6] = R(0x1000b000);
    env[7] = R(0x10002020);
    env[8] = R(0x10002010);
}

void func_00272580(u32 *env) {
    u32 cmd = env[7];
    u32 bp = cmd & 0x7f;
    u32 n = ((cmd >> 16) & 3) + ((cmd >> 8) & 0xf);
    u32 madr = env[0] - (n << 4);
    u32 qwc = env[2] + n;
    if (env[4] && env[5]) {
        R(0x1000b010) = env[4];
        R(0x1000b020) = env[5];
        func_002723c8(env[6] | 0x100);
    }
    while ((s32)R(0x10002010) < 0);
    R(0x10002000) = bp;
    while ((s32)R(0x10002010) < 0);
    if (madr && qwc) {
        R(0x1000b410) = madr;
        R(0x1000b430) = env[1];
        R(0x1000b420) = qwc;
        func_00272430(env[3] | 0x100);
    }
}

/* mode 0: wait while IPU_CTRL.BUSY; mode 1: return BUSY. */
s32 sceIpuSync(s32 mode) {
    s32 r = 0;
    switch (mode) {
    case 0:
        while (IPU_CTRL < 0);
        r = 0;
        break;
    case 1:
        r = (u32)IPU_CTRL >> 31;
        break;
    }
    return r;
}

void func_00272738(u32 v) {
    DIntr();
    *(volatile u32 *)0x1000f590 = *(volatile u32 *)0x1000f520 | 0x10000;
    *(volatile u32 *)0x1000b400 = v;
    *(volatile u32 *)0x1000f590 = *(volatile u32 *)0x1000f520 & ~0x10000;
    EIntr();
}

/* (s32)strtol(s, NULL, 10) */
s32 func_002729d8(const char *s) {
    return func_00272c38(s, 0, 10);
}
