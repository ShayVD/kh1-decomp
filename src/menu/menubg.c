/* The backgrounds of the menus (docs/modules.md "Session 39"),
 * 0x0020a8f0-0x0020b6a8: func_0020a8f0 reads two pixels of the frame buffer
 * back (sceGsExecStoreImage at (4, 16) and (443, 16)) into D_003F34B0, the
 * top and bottom colours; func_0020a9b0 / func_0020ab88 / func_0020ae98 draw
 * a full-screen gradient with them (plain, through the textures of D_003F1A70
 * / D_003F1E70, or into a packet), func_0020b120 one with four colours,
 * func_0020b338 loads the two images of D_00641080 / D_00641130 and
 * func_0020b3d8 draws them as a sprite at a window's text origin. */
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "text/textwin.h"

typedef struct { u8 si[2][0x70]; u32 px[2][0x40]; } StoreBuf;

extern s32 D_002BCC94;
extern s32 D_003F31F0[];
extern u8 D_00641080[];
extern u8 D_00641130[];

s32 func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, s32, void *);   /* s32: as void, func_0020b338 swaps v0 / v1 */
u64 *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(u32, s32);
u32 func_001edf40(u32, u32);
s32 func_001f4570(TextWin *);
s32 func_001f45e0(TextWin *);

#include "data/pieces/D_003F34B0.h"
#include "data/pieces/D_003F1A70.h"
#include "data/pieces/D_003F1E70.h"

void func_0020a8f0(void) {
    StoreBuf b;
    PlatGsSetDefStoreImage(b.si[0], 0, 8, 0, 0x100, 4, 0x10, 1);
    PlatGsSetDefStoreImage(b.si[1], 0, 8, 0, 0x100, 0x1BB, 0x10, 1);
    PlatFlushCache(0);
    PlatGsExecStoreImage(b.si[0], b.px[0]);
    PlatGsExecStoreImage(b.si[1], b.px[1]);
    PlatGsSyncPath(0, 0);
    D_003F34B0[0] = b.px[0][0] & 0xFFFFFF;
    D_003F34B0[1] = b.px[1][0] & 0xFFFFFF;
}

void func_0020b338(void) {
    func_0011fbb0(0x3600, 2, 0x13, 0, 0, 0x68, 0x38, 0x16C, D_002BCC94 + 0x40, D_00641080);
    func_0011fbb0(0x3640, 1, 0, 0, 0, 0x10, 0x10, 0x40, D_002BCC94 + 0x1700, D_00641130);
}
