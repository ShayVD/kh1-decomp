/* gb.x func_00f3f2b0: near miss (session 141), 151 words: VU1 data upload (12 floats at 0x1100FFA0, three 64-byte matrices, a quadword loop). The original reloads every global after each store (address kept in a register), ours keeps them; volatile globals reload but use lw + mtc1. */
#include "ovl.h"
typedef struct { f32 m[16]; } M64;
extern s32 D_00F82700;
extern s32 D_00F82704;
extern f32 D_00F82708;
extern f32 D_00F8270C;
extern f32 D_00F82710;
extern f32 D_00F82714;
void func_00f3f2b0(M64 *a, M64 *b, M64 *c, kh1_u128 *src, s32 n) {
    f32 *v = (f32 *)0x1100FFA0;
    kh1_u128 *d;
    s32 i;
    v[0] = 2048.0f - D_00F82700 * 0.5f;
    v[1] = 2048.0f - D_00F82704 * 0.5f;
    ((s32 *)v)[2] = 0;
    v[3] = D_00F8270C;
    v[4] = D_00F82700 * 0.5f + 2048.0f;
    v[5] = D_00F82704 * 0.5f + 2048.0f;
    ((s32 *)v)[6] = 0;
    v[7] = D_00F82708;
    v[8] = D_00F82708;
    v[9] = D_00F82710;
    v[10] = D_00F82714;
    v[11] = D_00F8270C;
    *(M64 *)0x1100C000 = *a;
    *(M64 *)0x1100C040 = *b;
    *(M64 *)0x1100C080 = *c;
    d = (kh1_u128 *)0x1100C0C0;
    for (i = 0; i < n; i++) {
        *d++ = *src++;
    }
}
