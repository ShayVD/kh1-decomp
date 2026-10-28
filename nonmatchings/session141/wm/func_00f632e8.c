/* func_00f632e8: score 35, 55 words differ. w*16 and h*32 adds placed differently; permuter gave nothing */
extern u64 **D_00FA66D8;
extern s32 D_00FA66DC;
void *func_00f632d0(void *);
s32 func_00f632a8(void *);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
u64 *func_001f0798(u64 *, s32, u32, s32, s32, void *, s32);
s32 func_00f66ae0(u64 *);
void func_00f66f78(s32, s32);

void func_00f632e8(s32 x, s32 y, void *str) {
    u64 *p = *D_00FA66D8;
    s32 w;
    s32 h;
    s32 x0;
    s32 y0;
    s32 tx;
    s32 ty;

    w = func_00f632a8(func_00f632d0(str)) + D_00FA66DC;
    h = D_00FA66DC;
    ty = y - (h * 2 - h) / 2;
    tx = x - (w - h) / 2;
    x = (x - w / 2 + 1792) << 4;
    y = (y - (h * 2 >> 1) + 1856) << 4;
    p = func_00f66b78(func_00f66ac8(p));
    p[0] = 0x0000740000007000;
    p[1] = 0x18;
    p += 2;
    p[0] = 0x30000;
    p[1] = 0x47;
    p += 2;
    p[0] = 0x46;
    p[1] = 0;
    p += 2;
    p[0] = 0x3F80000080202020;
    p[1] = 1;
    p += 2;
    p[0] = x | ((u64)y << 16) | 0x100000000;
    p[1] = 5;
    p += 2;
    p[0] = (x + w * 16) | ((u64)(y + h * 32) << 16) | 0x100000000;
    p[1] = 5;
    p += 2;
    func_00f66b90(p);
    p = func_001f0798(p, 1, 0x80808080, tx, ty, func_00f632d0(str), D_00FA66DC);
    func_00f66f78(40000, func_00f66ae0(p));
    *D_00FA66D8 = p;
}
