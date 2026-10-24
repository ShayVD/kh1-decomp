/* DMA helpers and the packet buffers, 0x00106b18-0x00106e18:
 * func_00106b18 sends a chain on the channel D_002A6B84 (libdma), func_00106b98
 * / func_00106bd8 from interrupt handlers, func_00106c10 allocates the
 * packet buffers D_00494A90 (0x2000) and D_00494A94 (0x8000) and
 * func_00106ca8 / func_00106cd0 / func_00106d48 take space in them
 * (platform code: DMA). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6238.h"
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "data/pieces/D_002A624C.h"
#include "data/pieces/D_002A6274.h"
#include "data/types/text_00100000_h1.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C10.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0048CC30.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002C5968.h"

/* func_00106b18 (from auto/text_00100000.c). */
extern PlatDmaChan *D_002A6B84;
void func_00106b18(s32 arg0) {
    PlatFlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatDmaSend(D_002A6B84, arg0);
}

/* func_00106b58 (from hand/text_00100000_h1.c). */
void func_00106b58(u32 x) {
    u32 v = x | 0x80000000;
    PlatGsSyncPath(0, 0);
    PlatDmaSend(D_002A6B84, v);
}

/* func_00106b98 (from auto/text_00100000_9.c). */
s32 func_00106b98(void *arg0) {
    PlatIFlushCache(0);
    PlatDmaSend(D_002A6B84, M2C_FIELD(arg0, s32 *, 0x10));
    return 2;
}

/* func_00106bd8 (from auto/text_00100000_10.c). */
void *func_0015ed80(s32, M2C_UNK *);
void func_00106bd8(s32 arg0, s32 arg1) {
    M2C_FIELD(func_0015ed80(arg1, &func_00106b98), s32 *, 0x10) = arg0;
}

/* func_00106c10 (from auto/text_00100000_2.c). */
s32 func_00121e28(M2C_UNK, s32 *);
void func_00106c10(void) {
    D_00494A98 = 0;
    D_00494A9C = 0;
    D_00494A90 = func_00121e28(0x2000, &D_00494A90);
    D_00494A94 = func_00121e28(0x8000, &D_00494A94);
}

/* func_00106c78 (from auto/text_00100000_3.c). */
void func_00121ee0(s32);
void func_00106c78(void) {
    func_00121ee0(D_00494A94);
    func_00121ee0(D_00494A90);
}

/* func_00106ca8 (from auto/text_00100000.c). */
s32 func_00106ca8(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_00494A98 * 0x10;
    D_00494A98 += arg0;
    return D_00494A94 + temp_v0;
}

/* func_00106cd0 (from auto/text_00100000_13.c). */
s32 func_00106cd0(s32 arg0, s32 arg1) {
    s32 temp_a0;
    void *temp_v1;

    *(M2C_UNK *)((s32) ((D_00494A9C * 0x10)) + (s32) D_00494A90) = arg1 + 0x30000000;
    M2C_FIELD(((D_00494A9C * 0x10) + D_00494A90), s32 *, 4) = arg0;
    temp_v1 = (D_00494A9C * 0x10) + D_00494A90;
    M2C_FIELD(temp_v1, s32 *, 0xC) = 0;
    M2C_FIELD(temp_v1, s32 *, 8) = 0;
    temp_a0 = D_00494A9C + 1;
    D_00494A9C = temp_a0;
    return (D_00494A90 + (temp_a0 * 0x10)) - 0x10;
}

/* func_00106d48 (from auto/text_00100000_13.c). */
void func_00106d48(s32 arg0) {
    void *temp_v0;

    *(M2C_UNK *)((s32) ((D_00494A9C * 0x10)) + (s32) D_00494A90) = 0x70000000;
    temp_v0 = (D_00494A9C * 0x10) + D_00494A90;
    M2C_FIELD(temp_v0, s32 *, 0xC) = 0;
    M2C_FIELD(temp_v0, s32 *, 8) = 0;
    M2C_FIELD(temp_v0, s32 *, 4) = 0;
    D_00494A9C += 1;
    func_00106b18(arg0);
}

/* func_00106db0 (from hand/text_00100000_h1.c). */
typedef struct { u8 pad[16]; u32 w16; } DmaReq;
s32 func_00106db0(DmaReq *r) {
    PlatDmaPutVif1Qwc(0);
    PlatDmaPutVif1Tadr(r->w16 & 0x0fffffff);
    PlatDmaPutStat(2);
    PlatIFlushCache(0);
    PlatDmaPutVif1Chcr(0x105);
    return 2;
}

