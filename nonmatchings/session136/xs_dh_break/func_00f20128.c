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
    u64 *buf, *p;
    u32 *w;
    PlatDmaSend(PlatDmaGetChan(2), D_00FA2000);
    buf = func_00122048(0x400, 0x80);
    buf[2] = 0x20AB400000008001ULL;
    buf[3] = 0x1E;
    p = func_0011fb38(0x42, 0x44, buf + 4);
    w = (u32 *)p;
    w[0] = 0x80; w[1] = 0x80; w[2] = 0x80; w[3] = 0x70;
    p[2] = 0x2000000000008002ULL;
    p[3] = 0x43;
    w = (u32 *)(p + 4);
    w[0] = 0; w[1] = 0;
    w[4] = 0x7000; w[5] = 0x7400; w[6] = 0x100100; w[7] = 0;
    w[8] = 0x2000; w[9] = 0x1C00;
    w[12] = 0x9000; w[13] = 0x8C00; w[14] = 0x100100; w[15] = 0;
    p += 12;
    buf[0] = ((((u8 *)p - (u8 *)buf) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)PLAT_DMA_SPR_ADDR(buf));
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
}
