/* 14 words left: s5/s6 swap of idx and v0; sprite family, tried fam.py orders and a 10-min permuter */
typedef struct { s16 a; s16 b; s32 u; s32 v; s32 w; s32 h; } T_00f23df0;
extern T_00f23df0 *D_00FBAA60;
extern u64 *D_00FBAA64;
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);

u64 *func_00f23df0(s32 x, s32 y, s32 w, s32 h, s32 idx, s32 alpha, s32 pk) {
    s32 x0, y0, x1, y1, u0, v0, u1, v1;
    u64 *p;
    x0 = (x += 1792) - w / 2;
    y0 = (y += 1856) - h / 2;
    u0 = D_00FBAA60[idx].u;
    v0 = D_00FBAA60[idx].v;
    v1 = D_00FBAA60[idx].v + D_00FBAA60[idx].h + 1;
    u1 = D_00FBAA60[idx].u + D_00FBAA60[idx].w + 1;
    y1 = y0 + h;
    x1 = x0 + w;
    p = func_00f66b78(pk);
    p[0] = 0;
    p[1] = 20;
    p += 2;
    p[0] = D_00FBAA64[idx];
    p[1] = 6;
    p += 2;
    p[0] = 342;
    p[1] = 0;
    p += 2;
    p[0] = ((s64)alpha << 24) | 0x3F80000000808080LL;
    p[1] = 1;
    p += 2;
    p[0] = (s64)(u0 << 4) | ((s64)(v0 << 4) << 16);
    p[1] = 3;
    p += 2;
    p[0] = (s64)(x0 << 4) | ((s64)(y0 << 4) << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    p[0] = (s64)(u1 << 4) | ((s64)(v1 << 4) << 16);
    p[1] = 3;
    p += 2;
    p[0] = (s64)(x1 << 4) | ((s64)(y1 << 4) << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    func_00f66b90(p);
    return p;
}
