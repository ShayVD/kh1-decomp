/* score 73 in nostrict (151 words; 612 vs 664 bytes). Writes 12 floats to VU memory 0x1100FFA0, copies three 64-byte unaligned blocks (ldl/sdl) to 0x1100C000/40/80, then lq/sq copies n qwords to 0x1100C0C0. The original reloads every global (D_0108EEC0..EED4) after each VU store, and keeps their addresses in registers. Ours CSEs the loads because gcc can tell the constant VU address from the globals. Volatile f or volatile globals did not reproduce it. */
#include "ovl.h"

typedef struct {
    u8 b[64];
} Blk;

extern s32 D_0108EEC0;
extern s32 D_0108EEC4;
extern f32 D_0108EEC8;
extern f32 D_0108EECC;
extern f32 D_0108EED0;
extern f32 D_0108EED4;

void func_00f663a8(Blk *a, Blk *b, Blk *c, kh1_u128 *src, s32 n) {
    f32 *f = (f32 *)0x1100FFA0;
    kh1_u128 *dst;

    f[0] = 2048.0f - D_0108EEC0 * 0.5f;
    f[1] = 2048.0f - D_0108EEC4 * 0.5f;
    f[2] = 0.0f;
    f[3] = D_0108EECC;
    f[4] = D_0108EEC0 * 0.5f + 2048.0f;
    f[5] = D_0108EEC4 * 0.5f + 2048.0f;
    f[6] = 0.0f;
    f[7] = D_0108EEC8;
    f[8] = D_0108EEC8;
    f[9] = D_0108EED0;
    f[10] = D_0108EED4;
    f[11] = D_0108EECC;
    *(Blk *)0x1100C000 = *a;
    *(Blk *)0x1100C040 = *b;
    *(Blk *)0x1100C080 = *c;
    dst = (kh1_u128 *)0x1100C0C0;
    while (n > 0) {
        *dst++ = *src++;
        n--;
    }
}
