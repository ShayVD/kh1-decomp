/* The captured frame (docs/modules.md "Session 34"), 0x001e05a8-0x001e0ab0:
 * send a packet list to path 2, load the 512x384 frame D_00F20000 (or the
 * image D_003DABD0[1]) into VRAM, and the two per-frame tasks that draw it
 * (started by src/screen/screen.c's func_001e25e8 / func_001e2628).
 *
 * A file of its own: the cross-fades after it (screen.c) match only when
 * func_001e0608 and func_001e07a8 are not defined above them (a definition
 * above moves a store into a branch delay slot), and screen.c has its own
 * copy of func_001e0608 (func_001e14e0). */
#include "common.h"
#include "platform/dma.h"
#include "data/data_003D.h"
#include "data/pieces/D_003DABD0.h"
#include "data/pieces/D_003DAD3C.h"

extern s32 D_0062F670;      /* the image transfer record */
extern u8 D_00F20000[];     /* the 512x384 RGB frame */

s32 FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
s32 sceGsExecLoadImage(void *, void *);
s32 func_002583e0(s32);
s32 func_00265bc0(s32, s32);

/* Send the packet list to path 2. */
void func_001e05a8(void *arg0) {
    s32 temp_s0;

    temp_s0 = PlatDmaGetChan(2);
    func_002583e0(0);
    func_00265bc0(0, 0);
    PlatDmaSend(temp_s0, (s32)arg0);
    func_00265bc0(0, 0);
}

/* Load the frame into VRAM (two halves at 0xe00 / 0x1400). */
void func_001e0608(void) {
    sceGsSetDefLoadImage(&D_0062F670, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, &D_00F20000);
    sceGsSetDefLoadImage(&D_0062F670, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, (s8 *)&D_00F20000 + 0x48000);
}

/* The same from line arg0 of the frame. */
void func_001e06c8(s32 arg0) {
    void *temp_s1;

    sceGsSetDefLoadImage(&D_0062F670, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    temp_s1 = (s8 *)&D_00F20000 + (arg0 * 0x600);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, temp_s1);
    sceGsSetDefLoadImage(&D_0062F670, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, (s8 *)temp_s1 + 0x48000);
}

/* The same from the image D_003DABD0[1]. */
void func_001e07a8(s32 arg0) {
    s32 temp_s0;

    sceGsSetDefLoadImage(&D_0062F670, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    temp_s0 = arg0 * 0x600;
    sceGsExecLoadImage(&D_0062F670, (void *)((s32)D_003DABD0[1] + temp_s0));
    sceGsSetDefLoadImage(&D_0062F670, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, (void *)((s32)D_003DABD0[1] + temp_s0 + 0x48000));
}

/* Every frame while D_003DAD38: draw the frame. */
s32 func_001e0898(void) {
    s32 var_v0;

    var_v0 = 4;
    if (D_003DAD38 == 0) {
        return var_v0;
    }
    func_001e0608();
    func_001e05a8(&D_003DAE30);
    var_v0 = 0;
    return var_v0;
}

/* Every frame while D_003DAD38: draw the frame from line D_003DAD3C,
 * scaled by D_003DACB0 / B4 and moved by D_003DACB8 / BC. */
s32 func_001e08d8(void) {
    f32 sx, sy;
    s32 ox, oy;
    u64 v, w;
    if (!D_003DAD38) return 4;
    func_001e06c8(D_003DAD3C);
    D_003DAE40[26] = 0x8080;
    sx = D_003DACB0;
    ox = D_003DACB8;
    D_003DAE40[15] = 0x180808080ULL;
    v = (f32)(ox + 0x7000) + (4096.0f - sx * 4096.0f);
    oy = D_003DACBC;
    sy = D_003DACB4;
    w = (f32)(oy + 0x73f8) + (3072.0f - sy * 3072.0f);
    D_003DAE40[31] = 0x180808080ULL;
    D_003DAE40[33] = v | (w << 16) | 0xFFFFFFFE00000000ULL;
    v = (sx * 8192.0f * 0.5f - 4096.0f + 36864.0f) + (f32)ox;
    w = (sy * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f) + (f32)oy;
    D_003DAE40[35] = v | (w << 16) | 0xFFFFFFFE00000000ULL;
    func_001e05a8(D_003DAF60);
    return 0;
}
