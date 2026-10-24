/* The EE side of the IOP sound driver (docs/modules.md "Session 36"),
 * 0x001ec7c0-0x001edc50.  Platform code: the Vita build replaces this file
 * (docs/portability.md, "sound").
 *
 * func_001ec7d0 binds SIF RPC server 17 (D_003E3C88), clears the shared
 * blocks and sends the IOP the addresses of its status block D_0063D640 and
 * message buffer D_0063F640 (RPC 0).  Every call goes through the 0x2000-byte
 * buffer D_00633640: word 0 in, word 0 back.  Most commands are not sent at
 * once: func_001ed000 queues an 8-word command in D_00635640 (1024 slots,
 * count D_003E3CB0) and func_001edba0 sends the whole queue (RPC 30).
 * D_003E3C80 (func_001ec7c0) masks command groups: bit 1 func_001ed4b8,
 * 2 func_001ed278, 4 func_001ecc68, 8 func_001ece70.  The IOP writes the
 * status block by DMA; the readers flush the cache first. */
#include "common.h"
#include "platform/iop.h"
#include "platform/thread.h"
#include "data/types/text_001e0000_h68.h"

/* The IOP's status block D_0063D640 (0x2000 bytes, src/data/data_0063.s):
 * 24 sound-effect slots, then 4 streams at +0x1800, words at +0x1c08 and
 * +0x1f00. */
typedef struct { s8 used; u8 pad1[3]; s32 x4; s32 x8; s32 xc; s32 x10; u8 pad[0xb4 - 0x14]; } SndSe;
typedef struct { u8 b0; u8 b1; s8 x2; s8 x3; s8 used; u8 pad5[11]; s32 x10; u8 pad14[4]; s32 x18; u8 pad1c[0x48 - 0x1c]; } SndStream;

extern s32 D_003E3C80;
extern u32 D_00633640[2048];
extern s32 D_00635640[1024][8];
extern RpcCd D_003E3C88;
extern s32 D_003E3CB0;
extern SndSe D_0063D640[];
extern SndStream D_0063EE40[4];
extern s32 D_0063F248;  /* src/data/data_0063.s: inside the IOP block D_0063D640 */
extern s32 D_0063F540;
/* The IOP's message buffer (src/data/bss_0063.c: u8 D_0063F640[256]); read signed. */
extern s8 D_0063F640[256];
extern char D_00490910[];
extern char D_00490928[];

int printf(const char *, ...);

void func_001ec7c0(s32);
void func_001ed000(s32, s32, s32, s32, s32, s32, s32, s32);

void func_001ec7c0(s32 arg0) {
    D_003E3C80 = arg0;
}

s32 func_001ec7d0(s32 arg) {
    u32 i, j;
    func_001ec7c0(0);
    for (i = 0; i < 2048; i++) D_00633640[i] = 0;
    { u8 *p = (u8 *)D_0063D640; for (i = 0; i < 8192; i++) p[i] = 0; }
    { u8 *p = (u8 *)D_0063F640; for (i = 0; i < 256; i++) p[i] = 0; }
    for (;;) {
        if (PlatSifBindRpc(&D_003E3C88, 17, 0) < 0) {
            printf(D_00490910);
            return -1;
        }
        if (D_003E3C88.server != 0) break;
        i = 0x10000; while (i--) ;
    }
    D_003E3CB0 = 0;
    for (j = 0; j < 1024; j++) {
        for (i = 0; i < 8; i++) D_00635640[j][i] = -1;
    }
    D_00633640[0] = (u32)D_0063D640;
    D_00633640[1] = arg;
    D_00633640[2] = (u32)D_0063F640;
    PlatSifCallRpc(&D_003E3C88, 0, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return 0;
}

s32 func_001ec9a8(void) {
    PlatSifCallRpc(&D_003E3C88, 0x1F, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001eca00(void) {
    PlatSifCallRpc(&D_003E3C88, 0x20, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001eca58(void) {
    PlatSifCallRpc(&D_003E3C88, 0x21, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ecab0(void) {
    PlatSifCallRpc(&D_003E3C88, 0x22, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ecb08(s32 a, s32 b, s32 c) {
    SndSe *p;
    s32 i;
    PlatFlushCache(0);
    p = D_0063D640;
    if (b < 0 && c < 0) {
        for (i = 0; i < 24; i++, p++) {
            if (p->used && p->xc == a) return 1;
        }
    } else if (b < 0) {
        for (i = 0; i < 24; i++, p++) {
            if (p->used && p->xc == a && p->x4 == c) return 1;
        }
    } else if (c < 0) {
        for (i = 0; i < 24; i++, p++) {
            if (p->used && p->xc == a && p->x10 == b) return 1;
        }
    }
    for (i = 0; i < 24; i++, p++) {
        if (p->used && p->xc == a && p->x10 == b && p->x4 == c) return 1;
    }
    return 0;
}

/* The early `return D_00633640[0];` is duplicated before the call (crossjump). */
s32 func_001ecc68(u8 *p, s32 a, s32 b, s32 c) {
    s32 v, x, y;
    v = p[16] << 24 | p[17] << 16;
    v |= p[18] << 8;
    v |= p[19];
    v = v * 4096 / 48000;
    x = p[30];
    y = p[31];
    if (D_003E3C80 & 4) return D_00633640[0];
    func_001ed000(18, (s32)p, a, b, c, v, x, y);
    return D_00633640[0];
}

s32 func_001ecd08(s32 a, s32 b, s32 c) {
    SndStream *p;
    s32 i, n;
    PlatFlushCache(0);
    p = D_0063EE40;
    if (a < 0 && b < 0 && c == 0) {
        n = 0;
        for (i = 0; i < 4; i++, p++) {
            if (p->used) n++;
        }
        return n;
    } else if (a < 0) {
        if (c == 0) {
            n = 0;
            for (i = 0; i < 4; i++, p++) {
                if (p->used && (p->b0 & 0x7f) == 1) n++;
            }
            return n;
        }
        for (i = 0; i < 4; i++, p++) {
            if (p->used && (p->b0 & 0x7f) == 1 && p->x10 == c) return 1;
        }
        return 0;
    }
    for (i = 0; i < 4; i++, p++) {
        if (p->used && p->b0 == 0 && p->x2 == a && p->x3 == b) return 1;
    }
    return 0;
}

s32 func_001ece70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_003E3C80 & 8) {
        return D_00633640[0];
    }
    func_001ed000(0x29, arg0, arg1, arg2, arg3, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001eced0(s32 id) {
    s32 i;
    SndStream *e;
    PlatFlushCache(0);
    for (e = D_0063EE40, i = 0; i < 4; i++, e++) {
        if (e->used != 0 && e->x10 == id) return e->x18;
    }
    return 0;
}

s32 func_001ecf40(s8 *dst) {
    s32 i;
    s8 *p;
    for (i = 0; i < 255; i++) *dst++ = D_0063F640[i];
    D_0063F640[255] = 0;
    if (D_0063F640[0] == 0) return 0;
    p = &D_0063F640[255];
    for (i = 255; i >= 0; i--) *p-- = 0;
    return 1;
}

s32 func_001ecfb0(void) {
    PlatFlushCache(0);
    return D_0063F248;
}

s32 func_001ecfd8(void) {
    PlatFlushCache(0);
    return D_0063F540;
}

void func_001ed000(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h) {
    s32 *pn = &D_003E3CB0;
    s32 n = *pn;
    D_00635640[n][0] = a;
    D_00635640[n][1] = b;
    D_00635640[n][2] = c;
    D_00635640[n][3] = d;
    D_00635640[n][4] = e;
    D_00635640[n][5] = f;
    D_00635640[n][6] = g;
    D_00635640[n][7] = h;
    *pn = n + 1;
    if (n + 1 >= 1024) {
        *pn = 0;
        printf(D_00490928);
    }
}

s32 func_001ed0d0(s32 arg0) {
    D_00633640[0] = arg0;
    PlatSifCallRpc(&D_003E3C88, 1, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ed128(s32 arg0, s32 arg1) {
    func_001ed000(0x26, arg0, arg1, 0, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed170(s32 arg0) {
    D_00633640[0] = arg0;
    PlatSifCallRpc(&D_003E3C88, 0x27, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ed1c8(s32 arg0) {
    D_00633640[0] = arg0;
    PlatSifCallRpc(&D_003E3C88, 0xF, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ed220(s32 arg0, s32 arg1, s32 arg2) {
    D_0063F540 += 1;
    func_001ed000(4, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed278(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (D_003E3C80 & 2) {
        return D_00633640[0];
    }
    func_001ed000(5, arg0, arg1, arg2, arg3, arg4, 0, 0);
    return D_00633640[0];
}

s32 func_001ed2d8(s32 arg0, s32 arg1, s32 arg2) {
    func_001ed000(6, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed320(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001ed000(2, arg0, arg1, arg2, arg3, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed370(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001ed000(7, arg0, arg1, arg2, arg3, arg4, 0, 0);
    return D_00633640[0];
}

s32 func_001ed3c0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_001ed000(8, arg0, arg1, arg2, arg3, arg4, 0, 0);
    return D_00633640[0];
}

s32 func_001ed410(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001ed000(9, arg0, arg1, arg2, arg3, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed460(s32 arg0, s32 arg1, s32 arg2) {
    D_0063F540 += 1;
    func_001ed000(0xB, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed4b8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (D_003E3C80 & 1) {
        return D_00633640[0];
    }
    func_001ed000(0xC, arg0, arg1, arg2, arg3, arg4, arg5, 0);
    return D_00633640[0];
}

s32 func_001ed520(s32 arg0) {
    func_001ed000(0xD, arg0, 0, 0, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed560(s32 arg0, s32 arg1, s32 arg2) {
    func_001ed000(0xE, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed5a8(s32 arg0) {
    D_00633640[0] = arg0;
    PlatSifCallRpc(&D_003E3C88, 0x2F, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ed600(s32 arg0) {
    D_00633640[0] = arg0;
    PlatSifCallRpc(&D_003E3C88, 0x30, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ed658(s32 arg0, s32 arg1, s32 arg2) {
    D_0063F540 += 1;
    func_001ed000(3, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed6b0(s32 arg0) {
    func_001ed000(0x13, arg0, 0, 0, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed6f0(s32 arg0, s32 arg1, s32 arg2) {
    func_001ed000(0x14, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed738(s32 arg0, s32 arg1, s32 arg2) {
    func_001ed000(0x15, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed780(s32 arg0, s32 arg1, s32 arg2) {
    D_0063F540 += 1;
    func_001ed000(0x28, arg0, arg1, arg2, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed7d8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001ed000(0x2A, arg0, arg1, arg2, arg3, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed828(s32 arg0, s32 arg1) {
    func_001ed000(0x2B, arg0, arg1, 0, 0, 0, 0, 0);
    return D_00633640[0];
}

s32 func_001ed870(void) {
    PlatSifCallRpc(&D_003E3C88, 0x16, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ed8c8(s32 arg0) {
    D_00633640[0] = arg0;
    PlatSifCallRpc(&D_003E3C88, 0x17, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ed920(void) {
    PlatSifCallRpc(&D_003E3C88, 0x18, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ed978(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00633640[0] = arg0;
    D_00633640[1] = arg1;
    D_00633640[2] = arg2;
    D_00633640[3] = arg3;
    PlatSifCallRpc(&D_003E3C88, 0x19, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001ed9e0(void) {
    PlatSifCallRpc(&D_003E3C88, 0x1B, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001eda38(s32 arg0) {
    D_00633640[0] = arg0;
    PlatSifCallRpc(&D_003E3C88, 0x1D, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001eda90(s32 arg0, s32 arg1) {
    D_00633640[0] = arg0;
    D_00633640[1] = arg1;
    PlatSifCallRpc(&D_003E3C88, 0x32, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001edaf0(s32 arg0) {
    D_00633640[0] = arg0;
    PlatSifCallRpc(&D_003E3C88, 0x23, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001edb48(s32 arg0) {
    D_00633640[0] = arg0;
    PlatSifCallRpc(&D_003E3C88, 0x24, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return D_00633640[0];
}

s32 func_001edba0(void) {
    s32 i, j;
    if (D_00635640[0][0] != -1) {
        PlatSifCallRpc(&D_003E3C88, 30, 0, D_00635640, 0x2000, D_00635640, 0x2000, 0, 0);
        D_003E3CB0 = 0;
        for (i = 0; i < 1024; i++) {
            for (j = 7; j >= 0; j--) D_00635640[i][j] = -1;
        }
    }
    return D_00633640[0];
}

#include "data/data_003E.h"
#include "data/data_0049.h"
#include "data/pieces/D_003E3C88.h"
