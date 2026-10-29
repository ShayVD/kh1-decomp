/* gb.x func_00f2c300: matched by hand. */
#include "ovl.h"

typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
extern s32 D_00F61384;
s32 func_00f23078(void);
u64 *func_00f38158(OvlVec *, OvlVec *, u64, s32, u64 *);
u64 *func_00f38408(OvlVec *, OvlVec *, u64, s32, u64 *);
u64 *func_00f38848(OvlVec *, OvlVec *, u64, s32, s32, u64 *);
u64 *func_00f38bf8(OvlVec *, OvlVec *, u64, u64, s32, u64 *);

u64 *func_00f2c300(GbPos pos, GbPos size, s32 arg, u32 color, u64 *p, s32 type) {
    OvlVec v[3];
    u8 rgb[4];
    u64 c;
    s32 t, a;
    f32 f;
    v[0][0] = pos.x * 200.0f;
    v[0][1] = -(f32)pos.y * 200.0f;
    v[0][2] = pos.z * 200.0f;
    v[0][3] = 1.0f;
    v[1][0] = v[0][0] + size.x * 200.0f;
    v[1][1] = v[0][1] - size.y * 200.0f;
    v[1][2] = v[0][2] + size.z * 200.0f;
    v[1][3] = 1.0f;
    switch (type) {
    case 0:
    case 1:
    case 2:
        f = 10.0f;
        v[2][0] = f;
        v[2][1] = f;
        v[2][2] = f;
        break;
    case 3:
        f = size.x * -200.0f * 0.2f;
        v[2][0] = f;
        v[2][1] = f;
        v[2][2] = f;
        break;
    }
    v[0][0] -= v[2][0];
    v[0][1] += v[2][1];
    v[0][2] -= v[2][2];
    v[1][0] += v[2][0];
    v[1][1] -= v[2][1];
    v[1][2] += v[2][2];
    c = (u64)color | 0x3F80000000000000;
    t = func_00f23078() % 120;
    if (t < 60) {
        a = D_00F61384 * (t + 30) / 90;
    } else {
        t -= 60;
        a = D_00F61384 * (90 - t) / 90;
    }
    switch (type) {
    case 0:
        p = func_00f38158(&v[0], &v[1], c, arg, p);
        break;
    case 1:
        p = func_00f38408(&v[0], &v[1], c, arg, p);
        break;
    case 2:
        *(u32 *)rgb = color;
        rgb[0] >>= 1;
        rgb[1] >>= 1;
        rgb[2] >>= 1;
        p = func_00f38848(&v[0], &v[1], *(u32 *)rgb | 0x3F80000000000000, 15, arg, p);
        break;
    case 3:
        p = func_00f38bf8(&v[0], &v[1], (u64)color | 0x3F80000000000000, ((u64)a << 24) | 0x3F80000000003E7C, arg, p);
        break;
    }
    return p;
}
