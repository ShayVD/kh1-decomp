/* dkmovie.x func_00f25658: near miss (session 141), 800 vs 800 bytes, 46 words differ, score 72 (m2c draft was 236). IPU decode task. Keys: off as n * 768 giv (n starts -1, n++ at loop top), k == 0 ? 0x2C000000 : 0x28000000 (gives bnezl), cont = !(CTRL>>14&1) && !(CTRL>>15&1). Left: the original has a dead reload lw a1,0(sp) of size after the first IPU wait loop (ours has no such insn, so a nop shifts), the 0x10002010 pointer is a1 (ours a2) and the header pointer a0 (ours a1), and the bF bit terms are computed andi-first. Tried: volatile size, base term orders, if/else for the CMD value. */
#include "ovl.h"
typedef struct { s32 f0; u8 pad4[5]; u8 b9; u8 padA[4]; u8 bE; u8 bF; } MvHdr;
typedef struct {
    u8 pad[0x3DD08];
    u8 *f3DD08;
    u8 pad3DD0C[0x84];
    MvHdr *f3DD90;
} MovieWork;
extern MovieWork *D_00F28460;
extern u8 *D_00F28464;
void func_00f269c0(void);
void func_00f26a20(u8 *, s32);
void func_00f26af0(u8 *, u8 *, s32);
void func_00f26848(s32, s32, s32, s32);

#define IPU_CMD (*(volatile s32 *)0x10002000)
#define IPU_CTRL (*(volatile s32 *)0x10002010)
#define D4_CHCR (*(volatile u32 *)0x1000B400)
#define D3_CHCR (*(volatile u32 *)0x1000B000)
#define D1_CHCR (*(volatile u32 *)0x1000D000)

s32 func_00f25658(void) {
    MvHdr *h;
    u8 f;
    s32 size;
    s32 base;
    u8 b9;
    s32 off, n, k, cont, m;

    h = D_00F28460->f3DD90;
    base = ((h->bF & 1) << 22) + ((h->bF >> 1) << 16);
    base = (h->bE << 20) + base;
    size = h->f0;
    b9 = h->b9;
    IPU_CTRL = base + 0x1200000;
    IPU_CTRL = (IPU_CTRL | 0x40000000) + base;
    while (IPU_CTRL < 0) {
    }
    n = -1;
    k = 0;
    D_00F28460->f3DD90 = (MvHdr *)((u8 *)D_00F28460->f3DD90 + 16);
    func_00f269c0();
    do {
        IPU_CMD = 0x30000000;
        n++;
        while (IPU_CTRL < 0) {
        }
        func_00f26a20(D_00F28464 + 112, 768);
        IPU_CTRL = base + 0x1200000;
        IPU_CMD = (b9 << 16) | (k == 0 ? 0x2C000000 : 0x28000000);
        k++;
        while (IPU_CTRL < 0) {
        }
        while ((D3_CHCR >> 8) & 1) {
        }
        func_00f26af0(D_00F28460->f3DD08 + n * 768, D_00F28464 + 112, 768);
        while ((D1_CHCR >> 8) & 1) {
        }
        func_00f26848(n, 0, 0, 2);
        while ((D1_CHCR >> 8) & 1) {
        }
        cont = !(((u32)IPU_CTRL >> 14) & 1) && !(((u32)IPU_CTRL >> 15) & 1);
    } while (cont);
    D4_CHCR = 0;
    IPU_CTRL = (IPU_CTRL | 0x40000000) + base;
    while (IPU_CTRL < 0) {
    }
    while ((D4_CHCR >> 8) & 1) {
    }
    D_00F28460->f3DD90 = (MvHdr *)((u8 *)D_00F28460->f3DD90 + size);
    return 0;
}
