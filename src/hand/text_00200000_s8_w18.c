/* func_0020b6a8 (hand): one packet word written through a u64/s32[2] union (W64), which gives that sw a dependence on the later sd buf[0] in sched2; tail order found by hill_s8. */
#include "common.h"
extern volatile s32 D_002BBDF8;
extern u8 D_003F1E70[];
extern f32 D_00641210;
extern f32 D_00641214;
extern f32 D_00641218;
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
void *func_00122048(s32, s32);
void func_001220b8(void *);
s32 sceGsSyncPath(s32, s32);
f32 sinf(f32);

typedef union { u64 ul; s32 i[2]; } W64;
void func_0020b6a8(void) {
    u64 *buf;
    u64 *p;
    void *ua;
    f32 f;
    u32 a;
    s32 x, y, m;
    s32 k = 22;
    func_00266f38(func_00266c08(2), D_003F1E70);
    buf = func_00122048(0x400, 0x80);
    p = buf + 2;
    ua = (void *)(((u32)buf & 0x0FFFFFFF) | 0x80000000);
    m = D_002BBDF8;
    p[0] = 0x50AB400000000001;
    p[1] = 0xEEEEE;
    p[3] = 0x3F;
    p[4] = 0x7BF8621413D7C;
    p[5] = 6;
    p[6] = 0x4007BF8001300000;
    p[8] = 0x0407BF8001400000;
    p[10] = 0x48;
    p[11] = 0x42;
    p[12] = 0x5000000000008001;
    p[13] = 0x4343E;
    p[7] = k;
    p[9] = k;
    p[2] = 0;
    f = (sinf((f32)(m % 90) / 90.0f * 6.2831855f) * 32.0f + 96.0f) * D_00641218;
    a = f;
    x = (s32)D_00641210 * 16;
    y = (s32)D_00641214 * 16;

    ((s32 *)p)[38] = 0x100000;
    ((s32 *)p)[32] = 0xE18;
    p[14] = (u32)(((a >> 7) << 24) | 0x808080);
    ((s32 *)p)[33] = 0x158;
    ((s32 *)p)[36] = x + 0x6F10;
    ((s32 *)p)[39] = 0x8000;
    ((s32 *)p)[40] = 0xFE8;
    ((s32 *)p)[41] = 0x328;
    ((W64 *)p)[18].i[1] = y + 0x7310;
    ((s32 *)p)[44] = x + 0x70F0;
    p[15] = 1;
    ((s32 *)p)[47] = 0;
    ((s32 *)p)[45] = y + 0x74F0;
    ((s32 *)p)[46] = 0x100000;
    buf[0] = (((s32)((u8 *)p - (u8 *)buf + 0xC0) >> 4) - 1) | 0x70000000;

    func_00266f38(func_00266c08(2), ua);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}
#include "data/bss_0064_mixed.h"
