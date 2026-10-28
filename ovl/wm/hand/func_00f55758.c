/* wm.x func_00f55758: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x2330]; u64 tex; } World;
typedef struct { u8 pad[0x2FC]; s32 u, v; } Tbl;
s32 func_00f4dca0(u64 *p, s32 x, s32 y, s32 z, s32 w, s32 h, s32 u, s32 v, s32 du, s32 dv, u64 a, u64 b);
u64 *func_00f4e0b0(u64 *, s32, s32);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66ae0(u64 *);
void func_00f66f78(s32, u64 *);
extern World *D_00F9B540;
extern u8 D_00FA5CF0[];
extern Tbl D_00FA6000;

#define RGBAQ(r, g, b, a) ((u64)(r) | ((u64)(g) << 8) | ((u64)(b) << 16) | ((u64)(a) << 24) | ((u64)0x3F800000 << 32))

void func_00f55758(u64 **pp, s32 idx, s32 x, s32 size, s32 c) {
    s32 off = D_00FA5CF0[idx];
    s32 u;
    *pp = func_00f66ac8(*pp);
    *pp = func_00f4e0b0(*pp, 0, 0);
    u = D_00FA6000.u + off * 32;
    *pp = (u64 *)func_00f4dca0(*pp, x - size / 2 + 0x2B0, 0x220 - size / 2, 0, size, size, u * 16, D_00FA6000.v * 16, 0x200, 0x200, RGBAQ(c, c, c, 0x80), D_00F9B540->tex);
    func_00f66f78(0x2B71, func_00f66ae0(*pp));
}
