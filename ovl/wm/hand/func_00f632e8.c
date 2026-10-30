/* wm.x func_00f632e8: matched by hand. Port of gb func_00f3c1f0 (wgb round 48). */
#include "ovl.h"

extern u64 **D_00FA66D8;
extern s32 D_00FA66DC;
void *func_00f632d0(void *);
s32 func_00f632a8(void *);
u64 *func_001f0798(u64 *, s32, u32, s32, s32, void *, s32);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66ae0(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void func_00f66f78(s32, u64 *);

void func_00f632e8(s32 x, s32 y, void *str) {
    u64 *q;
    s32 w, h;
    s32 bw, bh, tx, ty;
    s32 x1, y1;
    q = *D_00FA66D8;
    w = func_00f632a8(func_00f632d0(str));
    h = D_00FA66DC;
    bw = w + h;
    bh = h * 2;
    tx = x - (bw - h) / 2;
    ty = y - (bh - h) / 2;
    x = (x - bw / 2 + 0x700) << 4;
    y = (y - bh / 2 + 0x740) << 4;
    x1 = x + (bw << 4);
    y1 = y + (bh << 4);
    q = func_00f66b78(func_00f66ac8(q));
    q[0] = 0x740000007000;
    q[1] = 0x18;
    q += 2;
    q[0] = 0x30000;
    q[1] = 0x47;
    q += 2;
    q[0] = 0x46;
    q[1] = 0;
    q += 2;
    q[0] = 0x3F80000080202020;
    q[1] = 1;
    q += 2;
    q[0] = x | ((u64)y << 16) | 0x100000000;
    q[1] = 5;
    q += 2;
    q[0] = ((u64)y1 << 16) | x1 | 0x100000000;
    q[1] = 5;
    q += 2;
    func_00f66b90(q);
    q = func_001f0798(q, 1, 0x80808080, tx, ty, func_00f632d0(str), D_00FA66DC);
    func_00f66f78(0x9C40, func_00f66ae0(q));
    *D_00FA66D8 = q;
}
