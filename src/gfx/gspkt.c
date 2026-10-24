/* GS packets (docs/modules.md "Session 45"), 0x00236fd8-0x00237548 (with
 * gspkt.nostrict_nofill.c's func_00237018).
 * func_00236fd8(tag, end) writes a GIFtag for the A+D qwords up to `end`
 * (NLOOP = qwords - 1, EOP, NREG 1, REGS 0xE) and func_00237008(reg, data,
 * p) one A+D qword, returning the next.  func_002370c8(p) fills p[2..43]
 * with the default drawing environment (two GIFtags: FRAME_1 512 wide,
 * ZBUF_1, XYOFFSET_1 (0x7000, 0x7400), SCISSOR_1 512x384, TEST_1, ALPHA_1,
 * FBA_1, TEX0/1/2_1, MIPTBP1/2_1, CLAMP_1, PRMODECONT, COLCLAMP, then DTHE,
 * DIMX, PABE, TEXA); func_002372e0 sends it from D_006480D0 and
 * func_00237318 sends a variant (TEST_1 0x5000D, ALPHA_1 0x44, CLAMP_1 5).
 * func_00237018 (gspkt.nostrict_nofill.c) sends a packet of n qwords over
 * the GIF DMA channel.  Callers outside: the HUD and the sprite code from
 * 0x00238000 on, the menus' backgrounds. */
#include "common.h"
#include "gfx/gspkt.h"

extern u64 D_006480D0[]; /* src/data/bss_0064.c: u64 D_006480D0[0x2c] */

void func_00236fd8(u64 *tag, u64 *end) {
    tag[1] = 0xE;
    tag[0] = (((s32)((u8 *)end - (u8 *)tag) >> 4) - 1) | 0x8000 | ((u64)0x8000 << 45);
}

u64 *func_00237008(u64 reg, u64 data, u64 *p) {
    p[0] = data;
    p[1] = reg;
    return p + 2;
}

void func_002370c8(u64 *p) {
    p[2] = 0xF000000000000001ULL;
    p[3] = 0xEEEEEEEEEEEEEEEEULL;
    p[4] = 0x800D0ULL;
    p[5] = 0x4CULL;
    p[6] = 0x31000070ULL;
    p[7] = 0x4EULL;
    p[8] = 0x740000007000ULL;
    p[9] = 0x18ULL;
    p[10] = 0x17F000001FF0000ULL;
    p[11] = 0x40ULL;
    p[12] = 0x50003ULL;
    p[13] = 0x47ULL;
    p[14] = 0x8000000044ULL;
    p[15] = 0x42ULL;
    p[16] = 0;
    p[17] = 0x4AULL;
    p[18] = 0x20000045DD308002ULL;
    p[19] = 6;
    p[20] = 0x60ULL;
    p[21] = 0x14ULL;
    p[22] = 0x2000000001300000ULL;
    p[23] = 0x16ULL;
    p[24] = 0;
    p[25] = 0x34ULL;
    p[26] = 0;
    p[27] = 0x36ULL;
    p[28] = 0;
    p[29] = 8;
    p[30] = 1;
    p[31] = 0x1AULL;
    p[32] = 1;
    p[33] = 0x46ULL;
    p[34] = 0x4000000000008001ULL;
    p[35] = 0xEEEEEEEEEEEEEEEEULL;
    p[36] = 0;
    p[37] = 0x45ULL;
    p[38] = -4;
    p[39] = 0x44ULL;
    p[40] = 0;
    p[41] = 0x49ULL;
    p[42] = 0x8000000080ULL;
    p[43] = 0x3BULL;
}

void func_002372e0(void) {
    func_002370c8(D_006480D0);
    func_00237018(D_006480D0, 22, 1);
}

void func_00237318(void) {
    D_006480D0[2] = 0xF000000000000001ULL;
    D_006480D0[3] = 0xEEEEEEEEEEEEEEEEULL;
    D_006480D0[4] = 0x800D0ULL;
    D_006480D0[5] = 0x4CULL;
    D_006480D0[6] = 0x31000070ULL;
    D_006480D0[7] = 0x4EULL;
    D_006480D0[8] = 0x740000007000ULL;
    D_006480D0[9] = 0x18ULL;
    D_006480D0[10] = 0x17F000001FF0000ULL;
    D_006480D0[11] = 0x40ULL;
    D_006480D0[12] = 0x5000DULL;
    D_006480D0[13] = 0x47ULL;
    D_006480D0[14] = 0x44ULL;
    D_006480D0[15] = 0x42ULL;
    D_006480D0[16] = 0;
    D_006480D0[17] = 0x4AULL;
    D_006480D0[18] = 0x20000045DD308002ULL;
    D_006480D0[19] = 6;
    D_006480D0[20] = 0x60ULL;
    D_006480D0[21] = 0x14ULL;
    D_006480D0[22] = 0x2000000001300000ULL;
    D_006480D0[23] = 0x16ULL;
    D_006480D0[24] = 0;
    D_006480D0[25] = 0x34ULL;
    D_006480D0[26] = 0;
    D_006480D0[27] = 0x36ULL;
    D_006480D0[28] = 5;
    D_006480D0[29] = 8;
    D_006480D0[30] = 1;
    D_006480D0[31] = 0x1AULL;
    D_006480D0[32] = 1;
    D_006480D0[33] = 0x46ULL;
    D_006480D0[34] = 0x4000000000008001ULL;
    D_006480D0[35] = 0xEEEEEEEEEEEEEEEEULL;
    D_006480D0[36] = 0;
    D_006480D0[37] = 0x45ULL;
    D_006480D0[38] = -4;
    D_006480D0[39] = 0x44ULL;
    D_006480D0[40] = 0;
    D_006480D0[41] = 0x49ULL;
    D_006480D0[42] = 0x8000000080ULL;
    D_006480D0[43] = 0x3BULL;
    func_00237018(D_006480D0, 22, 1);
}
