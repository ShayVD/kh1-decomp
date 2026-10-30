/* gb.x func_00f3f2b0: matched by hand. */
#include "ovl.h"

/* gb.x func_00f3f2b0 (wgb round 44). v is set twice: first for the 12-word header at 0x1100FFA0, then as the base for the three M64 copies to 0x1100C000. With two sets, alias analysis no longer knows v as a constant, so the f32/s32 stores through v may alias D_00F82700..0C, and those are reloaded as in the target. With v set once, gcc keeps the loaded values in registers. */
typedef struct { f32 m[16]; } M64;
extern s32 D_00F82700;
extern s32 D_00F82704;
extern f32 D_00F82708;
extern f32 D_00F8270C;
extern f32 D_00F82710;
extern f32 D_00F82714;
void func_00f3f2b0(M64 *a, M64 *b, M64 *c, kh1_u128 *src, s32 n) {
    s32 i;
    f32 *v = (f32 *)0x1100FFA0;
    kh1_u128 *d;
    d = (kh1_u128 *)0x1100C0C0;
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
    v = (f32 *)0x1100C000;
    ((M64 *)v)[0] = *a;
    ((M64 *)v)[1] = *b;
    ((M64 *)v)[2] = *c;
    for (i = 0; i < n; i++) {
        *d++ = *src++;
    }
}
