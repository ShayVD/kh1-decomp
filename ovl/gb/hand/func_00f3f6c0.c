/* gb.x func_00f3f6c0: matched by hand. */
#include "ovl.h"

#include "ovl.h"

extern s32 D_00F82700;
extern s32 D_00F82704;
extern f32 D_00F82708;
extern f32 D_00F8270C;
extern f32 D_00F82710;
extern f32 D_00F82714;
extern u32 D_00F82830[];

u32 *func_00f3f6c0(u32 *p, u32 addr, u32 qwc) {
    f32 *v;
    u32 *q;
    f32 hw = D_00F82700 * 0.5f;
    f32 hh = D_00F82704 * 0.5f;
    D_00F82830[0] = 0x13000000;
    D_00F82830[1] = 0x01000404;
    D_00F82830[2] = 0x6C0303FA;
    D_00F82830[15] = 0;
    v = (f32 *)&D_00F82830[3];
    v[0] = 2048.0f - hw;
    v[1] = 2048.0f - hh;
    v[2] = 0.0f;
    v[3] = D_00F8270C;
    v[4] = 2048.0f + hw;
    v[5] = 2048.0f + hh;
    v[6] = 0.0f;
    v[7] = D_00F82708;
    v[8] = D_00F82708;
    v[9] = D_00F82710;
    v[10] = D_00F82714;
    v[11] = D_00F8270C;
    p[0] = 0x30000004;
    p[1] = (u32)D_00F82830;
    p[2] = 0;
    p[3] = 0;
    q = p + 4;
    q[0] = qwc | 0x30000000;
    q[1] = addr;
    q[2] = 0;
    q[3] = 0;
    q = p + 8;
    q[0] = 0x70000000;
    q[1] = 0;
    q[2] = 0;
    q[3] = 0;
    return q;
}
