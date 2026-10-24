/* libcdvd and libipu functions matched by hand (session 6, worker 28),
 * ee-gcc 2.9-991111. scePrintf and sceSifInitRpc return void here: with an
 * int return the caller's register choice differs. */
#include "common.h"

void scePrintf(const char *fmt, ...);
void sceSifInitRpc(s32 mode);
s32 sceSifBindRpc(void *client, u32 rpc, s32 mode);
s32 sceSifCallRpc(void *client, u32 fno, u32 mode, void *send, s32 ssize, void *recv, s32 rsize, void *end_func, void *end_para);
s32 SignalSema(s32 sema);
s32 PollSema(s32 sema);
s32 ReferThreadStatus(s32 id, void *status);
void func_00260738(void *addr, s32 size); /* cache writeback */
void func_00269830(void);
s32 sceCdSync(s32 mode);
s32 sceCdSyncS(s32 mode);
void func_00272738(s32 mode);
void *memcpy(void *, const void *, u32);

#define VS(x) (*(volatile s32 *)&(x))
#define UNC(x) (*(s32 *)((u32)&(x) | 0x20000000))

typedef struct { u8 pad[0x24]; void *server; } SifClient;

extern s32 D_0046C610;      /* debug print level */
extern s32 D_0046C61C;      /* current N command */
extern s32 D_0046C628;      /* N command semaphore */
extern s32 D_0046C62C;      /* S command semaphore */
extern s32 D_0046C640;      /* search-file bind state */
extern s32 D_0046C644;      /* disk-ready bind state */
extern s32 D_00673350;      /* caller thread id */
extern u8 D_00673358[];     /* thread status buffer */
extern s32 D_0046D800[];    /* RPC receive buffer */

/* sceCdLayerSearchFile's RPC block: the file record comes back in place. */
typedef struct { u32 lsn; u32 size; char name[16]; u8 date[8]; u32 flag; } CdlFile;
typedef struct { CdlFile file; char name[256]; void *addr; s32 mode; } CdSearchArg;
extern CdSearchArg D_006733C0;
extern u8 D_00673540[];     /* search-file RPC client */
extern s32 D_00673500[];    /* search-file RPC result */
extern char D_00493108[], D_00493128[], D_00493140[], D_00493150[], D_00493160[];

s32 sceCdLayerSearchFile(CdlFile *fp, const char *name, s32 mode) {
    s32 i;
    s32 r;
    s32 j;
    func_00269830();
    if (VS(D_0046C628) != PollSema(VS(D_0046C628))) return 0;
    D_0046C61C = 1;
    ReferThreadStatus(D_00673350, D_00673358);
    if (sceCdSync(1)) {
        SignalSema(VS(D_0046C628));
        return 0;
    }
    sceSifInitRpc(0);
    if (D_0046C640 < 0) {
        while (1) {
            if (sceSifBindRpc(D_00673540, 0x80000597, 0) < 0) {
                if (D_0046C610 > 0) scePrintf(D_00493108);
                j = 0x100000;
                while (--j != -1);
                continue;
            }
            if (((SifClient *)D_00673540)->server) { D_0046C640 = 0; break; }
            j = 0x100000;
            while (--j != -1);
        }
    }
    for (i = 0; i < 256; i++) {
        if ((D_006733C0.name[i] = name[i]) == 0) break;
    }
    if (i == 256) D_006733C0.name[255] = 0;
    if (D_0046C610 > 0) scePrintf(D_00493128, D_006733C0.name);
    D_006733C0.mode = mode;
    D_006733C0.addr = &D_006733C0;
    func_00260738(&D_006733C0, 300);
    if (sceSifCallRpc(D_00673540, 0, 0, &D_006733C0, 300, D_00673500, 4, 0, 0) < 0) {
        SignalSema(VS(D_0046C628));
        return 0;
    }
    memcpy(fp, (void *)((u32)&D_006733C0 | 0x20000000), 36);
    if (D_0046C610 > 0) {
        scePrintf(D_00493140, fp->name);
        if (D_0046C610 > 0) {
            scePrintf(D_00493150, fp->size);
            if (D_0046C610 > 0) scePrintf(D_00493160, fp->lsn);
        }
    }
    r = *(s32 *)((u32)D_00673500 | 0x20000000);
    SignalSema(VS(D_0046C628));
    return r;
}

extern u8 D_00673590[];     /* disk-ready RPC client */
extern s32 D_006735D0;      /* disk-ready send word */
extern char D_00493248[], D_00493258[], D_00493278[];

/* The two failure paths are written out twice: gcc merges them after
 * register allocation (cross-jumping), and the extra uses of mode and the
 * semaphore give the original register order. */
s32 sceCdDiskReady(s32 mode) {
    s32 j, r;
    if (D_0046C610 > 0) scePrintf(D_00493248);
    func_00269830();
    if (VS(D_0046C62C) != PollSema(VS(D_0046C62C))) return 6;
    if (sceCdSyncS(1)) {
        SignalSema(VS(D_0046C62C));
        return mode != 8 ? 6 : -1;
    }
    sceSifInitRpc(0);
    if (D_0046C644 < 0) {
        while (1) {
            if (sceSifBindRpc(D_00673590, 0x8000059a, 0) < 0) {
                if (D_0046C610 > 0) scePrintf(D_00493258);
                j = 0x100000;
                while (--j != -1);
                continue;
            }
            if (((SifClient *)D_00673590)->server) { D_0046C644 = 0; break; }
            j = 0x100000;
            while (--j != -1);
        }
    }
    D_006735D0 = mode;
    func_00260738(&D_006735D0, 4);
    if (sceSifCallRpc(D_00673590, 0, 0, &D_006735D0, 4, D_0046D800, 4, 0, 0) < 0) {
        SignalSema(VS(D_0046C62C));
        return mode != 8 ? 6 : -1;
    }
    if (D_0046C610 > 0) scePrintf(D_00493278);
    r = UNC(D_0046D800[0]);
    SignalSema(VS(D_0046C62C));
    return r;
}

/* libipu: IPU reset, BCLR, then SETIQ (intra, non-intra), SETVQ, SETTH. The
 * tables are read through volatile: the original reloads each quadword. */
typedef unsigned int u128 __attribute__((mode(TI)));
extern u128 D_0046E0B0[];   /* IQ tables */
extern u128 D_0046E100[];   /* VQ CLUT */
#define IPU_CMD (*(volatile u32 *)0x10002000)
#define IPU_CTRL (*(volatile s32 *)0x10002010)
#define IPU_IN_FIFO (*(volatile u128 *)0x10007010)

void sceIpuInit(void) {
    func_00272738(1);
    IPU_CTRL = 0x40000000;
    while (IPU_CTRL < 0);
    IPU_CMD = 0;
    while (IPU_CTRL < 0);
    IPU_IN_FIFO = ((volatile u128 *)D_0046E0B0)[0];
    IPU_IN_FIFO = ((volatile u128 *)D_0046E0B0)[1];
    IPU_IN_FIFO = ((volatile u128 *)D_0046E0B0)[2];
    IPU_IN_FIFO = ((volatile u128 *)D_0046E0B0)[3];
    IPU_IN_FIFO = ((volatile u128 *)D_0046E0B0)[4];
    IPU_IN_FIFO = ((volatile u128 *)D_0046E0B0)[4];
    IPU_IN_FIFO = ((volatile u128 *)D_0046E0B0)[4];
    IPU_IN_FIFO = ((volatile u128 *)D_0046E0B0)[4];
    IPU_CMD = 0x50000000;
    while (IPU_CTRL < 0);
    IPU_CMD = 0x58000000;
    while (IPU_CTRL < 0);
    IPU_IN_FIFO = ((volatile u128 *)D_0046E100)[0];
    IPU_IN_FIFO = ((volatile u128 *)D_0046E100)[1];
    IPU_CMD = 0x60000000;
    while (IPU_CTRL < 0);
    IPU_CMD = 0x90000000;
    while (IPU_CTRL < 0);
    IPU_CTRL = 0x40000000;
    while (IPU_CTRL < 0);
    IPU_CMD = 0;
    while (IPU_CTRL < 0);
}
