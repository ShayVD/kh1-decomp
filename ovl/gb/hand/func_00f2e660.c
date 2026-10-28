/* gb.x func_00f2e660: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x2330]; u64 tex; } World;
typedef struct { u8 pad[0x2FC]; s32 u, v; } Tbl;
s32 func_00f26ba8(u64 *p, s32 x, s32 y, s32 z, s32 w, s32 h, s32 u, s32 v, s32 du, s32 dv, u64 a, u64 b);
u64 *func_00f26fb8(u64 *, s32, s32);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);
extern World *D_00F56DC0;
extern u8 D_00F61570[];
extern Tbl D_00F61880;

#define RGBAQ(r, g, b, a) ((u64)(r) | ((u64)(g) << 8) | ((u64)(b) << 16) | ((u64)(a) << 24) | ((u64)0x3F800000 << 32))

void func_00f2e660(u64 **pp, s32 idx, s32 x, s32 size, s32 c) {
    s32 off = D_00F61570[idx];
    s32 u;
    *pp = func_00f3f9d0(*pp);
    *pp = func_00f26fb8(*pp, 0, 0);
    u = D_00F61880.u + off * 32;
    *pp = (u64 *)func_00f26ba8(*pp, x - size / 2 + 0x2B0, 0x220 - size / 2, 0, size, size, u * 16, D_00F61880.v * 16, 0x200, 0x200, RGBAQ(c, c, c, 0x80), D_00F56DC0->tex);
    func_00f3fe80(0x2B71, func_00f3f9e8(*pp));
}
