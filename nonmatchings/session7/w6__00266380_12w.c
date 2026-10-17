/* 00266380 sceGsExecStoreImage: mode sdk/gcc991111_as296 (2.96 gas fills the GsPutIMR jal slot with BUSDIR=0; 991111a reorg never puts volatile stores in delay slots), rodata RO=00492d70. 12w: only rest/buf s5<->s6 swapped (orig buf=s5 rest=s6; global-alloc priority). Keys: void scePrintf, block-local q per case, function-level x for the rest tails, else-branches 'goto norem' into case 20's shared else, reset code duplicated in timeout3/4. No single flag helps. */
#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct { u64 SBP:14, p0:2, SBW:6, p1:2, SPSM:6, p2:34; } TBitblt;
typedef struct { u64 RRW:12, p0:20, RRH:12, p1:20; } TTrxreg;
typedef struct {
    u32 vifcode[4];
    u64 giftag[2];
    TBitblt bitbltbuf; u64 bitbltbufaddr;
    u64 trxpos; u64 trxposaddr;
    TTrxreg trxreg; u64 trxregaddr;
    u64 finish; u64 finishaddr;
    u64 trxdir; u64 trxdiraddr;
} GsStoreImage;
u64 GsGetIMR(void);
u64 GsPutIMR(u64);
void scePrintf(const char *, ...);
extern char D_00492C90[], D_00492CC8[], D_00492CF8[], D_00492D38[];
extern u128 D_0046C530;
#define CHCR (*(volatile u32 *)0x10009000)
#define MADR (*(volatile u32 *)0x10009010)
#define QWC (*(volatile u32 *)0x10009020)
#define VSTAT (*(volatile u32 *)0x10003c00)
#define FIFO (*(volatile u128 *)0x10005000)
#define CSR (*(volatile u64 *)0x12001000)
#define BUSDIR (*(volatile u64 *)0x12001040)

s32 sceGsExecStoreImage(GsStoreImage *sp, u128 *buf) {
    u32 cnt = 0;
    s32 full = 0, part = 0, rem = 0, rest = 0;
    s32 w, h, hh, n, q, i, x;
    u64 imr, r;
    u8 tmp[16] __attribute__((aligned(16)));
    char *msg;
    r = *(u64 *)&sp->trxreg;
    w = r & 0xfff;
    h = (r >> 32) & 0xfff;
    hh = 0;
    switch (sp->bitbltbuf.SPSM) {
    case 0: case 48:
        n = w * h * 4;
        { s32 q = n >> 4; rem = n & 15; full = q & 0xfffffff8; part = q & 7; }
        if (rem) { hh = (h + 3) & ~3; x = w * hh >> 2; rest = x - full - part - 1; }
        else goto norem;
        break;
    case 1: case 49:
        n = w * h * 3;
        { s32 q = n >> 4; rem = n & 15; full = q & 0xfffffff8; part = q & 7; }
        if (rem) { hh = (h + 15) & ~15; x = w * hh * 3 >> 4; rest = x - full - part - 1; }
        else goto norem;
        break;
    case 2: case 10: case 50: case 58:
        n = w * h * 2;
        { s32 q = n >> 4; rem = n & 15; part = q & 7; full = q & 0xfffffff8; }
        if (rem) { hh = (h + 7) & 0xfffffff8; x = w * hh >> 3; rest = x - full - part - 1; }
        else goto norem;
        break;
    case 19: case 27:
        n = w * h;
        { s32 q = n >> 4; rem = n & 15; part = q & 7; full = q & 0xfffffff8; }
        if (rem) { hh = (h + 7) & 0xfffffff8; x = w * hh >> 4; rest = x - full - part - 1; }
        else goto norem;
        break;
    case 20: case 36: case 44:
        n = w * h / 2;
        { s32 q = n >> 4; rem = n & 15; part = q & 7; full = q & 0xfffffff8; }
        if (!rem) { norem: hh = h; rest = 0; }
        else { hh = (h + 7) & 0xfffffff8; x = w * hh >> 5; rest = x - full - part - 1; }
        break;
    }
    if (rem) {
        *(u64 *)((u32)&sp->trxreg | 0x20000000) = (s32)sp->trxreg.RRW | (u64)hh << 32;
    }
    while (CHCR & 0x100) {
        if (cnt++ > 0x1000000) goto timeout1;
    }
    imr = GsPutIMR(GsGetIMR() | 0x200);
    CSR = 2;
    QWC = 7;
    if (((u32)sp & 0x70000000) == 0x70000000) MADR = ((u32)sp & 0x0fffffff) | 0x80000000;
    else MADR = (u32)sp & 0x0fffffff;
    CHCR = 0x101;
    while (CHCR & 0x100) {
        if (cnt++ > 0x1000000) goto timeout1;
    }
    while (!(CSR & 2)) {
        if (cnt++ > 0x1000000) goto timeout2;
    }
    VSTAT = 0x800000;
    BUSDIR = 1;
    if (full) {
        QWC = full;
        if (((u32)buf & 0x70000000) == 0x70000000) MADR = ((u32)buf & 0x0fffffff) | 0x80000000;
        else {
            goto el;
timeout1:
    scePrintf(D_00492C90);
    return -1;
timeout2:
    scePrintf(D_00492CC8);
    FIFO = D_0046C530;
    return -1;
timeout3:
    scePrintf(D_00492CF8);
    CSR = 0x100;
    BUSDIR = 0;
    *(volatile u32 *)0x10003000 = 1;
    *(volatile u32 *)0x10003c10 = 1;
    return -1;
timeout4:
    scePrintf(D_00492D38);
    CSR = 0x100;
    BUSDIR = 0;
    *(volatile u32 *)0x10003000 = 1;
    *(volatile u32 *)0x10003c10 = 1;
    return -1;
el:
            MADR = (u32)buf & 0x0fffffff;
        }
        CHCR = 0x100;
        while (CHCR & 0x100) {
            if (cnt++ > 0x1000000) goto timeout3;
        }
    }
    for (i = 0; i < part; i++) {
        while (!(VSTAT & 0x1f000000)) {
            if (cnt++ > 0x1000000) goto timeout4;
        }
        buf[full + i] = FIFO;
    }
    if (rem) {
        while (!(VSTAT & 0x1f000000)) {
            if (cnt++ > 0x1000000) goto timeout4;
        }
        *(u128 *)tmp = FIFO;
        for (i = 0; i < rem; i++) ((u8 *)&buf[full + part])[i] = tmp[i];
        for (i = 0; i < rest; i++) {
            while (!(VSTAT & 0x1f000000)) {
                if (cnt++ > 0x1000000) goto timeout4;
            }
            *(u128 *)tmp = FIFO;
        }
    }
    VSTAT = 0;
    BUSDIR = 0;
    GsPutIMR(imr);
    {u128 t = D_0046C530;
    CSR = 2;
    FIFO = t;}
    return 0;
}
