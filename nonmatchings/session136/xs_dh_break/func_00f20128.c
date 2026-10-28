/* xs_dh_break.x func_00f20128: draft (session 136), not byte-identical; the port runs it
 * (ovl/xs_dh_break/drafts.tsv). Sends D_00FA2000's chain (func_00f20080's) and a full-screen
 * textured sprite. No caller in the file (nothing jumps to it or stores its address). */
#include "ovl.h"
#include "platform/dma.h"
#include "platform/gs.h"

void *func_0011fb38(s32, u64, void *);
void *func_00122048(u32, u32);
void func_001220b8(void *);
extern u64 D_00FA2000[];

void func_00f20128(void) {
    u64 *p, *q;
    u32 *w;
    u32 spr;
    PlatDmaSend(PlatDmaGetChan(2), D_00FA2000);
    p = func_00122048(0x400, 0x80);
    q = p;
    p += 2;
    spr = PLAT_DMA_SPR_ADDR(q);
    p[0] = 0x20AB400000008001ULL;
    p[1] = 0x1E;
    p = func_0011fb38(0x42, 0x44, p + 2);
    w = (u32 *)p;
    w[0] = 0x80; w[1] = 0x80; w[2] = 0x80; w[3] = 0x70;
    p += 2;
    p[0] = 0x2000000000008002ULL;
    p[1] = 0x43;
    p += 2;
    w = (u32 *)p;
    w[0] = 0; w[1] = 0;
    w[4] = 0x7000; w[5] = 0x7400; w[6] = 0x100100; w[7] = 0;
    w[8] = 0x2000; w[9] = 0x1C00;
    w[12] = 0x9000; w[13] = 0x8C00; w[14] = 0x100100; w[15] = 0;
    p += 8;
    q[0] = ((((u8 *)p - (u8 *)q) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)spr);
    PlatGsSyncPath(0, 0);
    func_001220b8(q);
}
