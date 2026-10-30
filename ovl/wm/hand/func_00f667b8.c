/* wm.x func_00f667b8: matched by hand. */
#include "ovl.h"

extern s32 D_0108EEC0;
extern s32 D_0108EEC4;
extern f32 D_0108EEC8;
extern f32 D_0108EECC;
extern f32 D_0108EED0;
extern f32 D_0108EED4;
extern u32 D_0108EFF0[];

u32 *func_00f667b8(u32 *p, u32 addr, u32 qwc) {
    f32 *v;
    u32 *q;
    f32 hw = D_0108EEC0 * 0.5f;
    f32 hh = D_0108EEC4 * 0.5f;
    D_0108EFF0[0] = 0x13000000;
    D_0108EFF0[1] = 0x01000404;
    D_0108EFF0[2] = 0x6C0303FA;
    D_0108EFF0[15] = 0;
    v = (f32 *)&D_0108EFF0[3];
    v[0] = 2048.0f - hw;
    v[1] = 2048.0f - hh;
    v[2] = 0.0f;
    v[3] = D_0108EECC;
    v[4] = 2048.0f + hw;
    v[5] = 2048.0f + hh;
    v[6] = 0.0f;
    v[7] = D_0108EEC8;
    v[8] = D_0108EEC8;
    v[9] = D_0108EED0;
    v[10] = D_0108EED4;
    v[11] = D_0108EECC;
    p[0] = 0x30000004;
    p[1] = (u32)D_0108EFF0;
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
