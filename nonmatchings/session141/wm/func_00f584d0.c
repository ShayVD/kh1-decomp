/* Round 42 wwm2: score 99 -> 74. r42/msdscan.py (instruction multiset diff) showed addiu 2272 against our addiu 142: the original adds 142 << 4 after the shift, so y1 is D.h and the XY word uses (y1 << 4) + 2272. Then r42/hill3o.py reordered the setup lines (y0 = 142 last). Earlier header below. */
/* 67 words (628 vs 632). Sprite packet over D_00FA6000[n+22] (idx*20 table) with RGBAQ(r,g,b,0x80), 14 GIF entries; direct D[idx].field expressions already give the target element-address copies (t1/a0/v1/t0). Left: the target computes u+w, w<<4 and h<<4 before the calls but +1/<<4/+2272 and v+h after them; hill-climbed the 8 coordinate lines (105 -> 67); an explicit-locals variant scored worse. */
typedef struct { s32 a; s32 u; s32 v; s32 w; s32 h; } T584d0;
typedef struct { u8 pad[0x2200]; u64 tex[1]; } W584d0;
extern T584d0 D_00FA6000[];
extern W584d0 *D_00F9B540;
extern u64 *D_00F9B548;
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
u64 *func_00f66ae0(u64 *);
void func_00f66f78(s32, u64 *);

#define RGBAQ(r, g, b, a) ((u64)(r) | ((u64)(g) << 8) | ((u64)(b) << 16) | ((u64)(a) << 24) | ((u64)0x3F800000 << 32))

void func_00f584d0(s32 n, s32 r, s32 g, s32 b) {
    s32 x0, y0, x1, y1, u0, v0, u1, v1;
    s32 idx = n + 22;
    u64 *p;

    x0 = 0;
    y0 = 142;
    x1 = x0 + D_00FA6000[idx].w;
    v0 = D_00FA6000[idx].v;
    y1 = D_00FA6000[idx].h;
    u0 = D_00FA6000[idx].u;
    v1 = v0 + D_00FA6000[idx].h + 1;
    u1 = u0 + D_00FA6000[idx].w + 1;
    p = func_00f66b78(func_00f66ac8(D_00F9B548));
    p[0] = 0x30003;
    p[1] = 71;
    p += 2;
    p[0] = 0;
    p[1] = 24;
    p += 2;
    p[0] = 0;
    p[1] = 20;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    p[0] = D_00F9B540->tex[idx];
    p[1] = 6;
    p += 2;
    p[0] = 342;
    p[1] = 0;
    p += 2;
    p[0] = RGBAQ(r, g, b, 0x80);
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
    p[0] = (s64)(x1 << 4) | ((s64)((y1 << 4) + 2272) << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    p[0] = 96;
    p[1] = 20;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 0x5000D;
    p[1] = 71;
    p += 2;
    func_00f66b90(p);
    func_00f66f78(12160, func_00f66ae0(p));
    D_00F9B548 = p;
}
