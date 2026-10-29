/* Round 42 wwm2: score 99 -> 74, port.py of the wm twin func_00f584d0 draft. Earlier header below. */
/* Round 41 wwm2: score 145 -> 99, port.py of the wm twin func_00f584d0 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
typedef struct { s32 a; s32 u; s32 v; s32 w; s32 h; } T584d0;
typedef struct { u8 pad[0x2200]; u64 tex[1]; } W584d0;
extern T584d0 D_00F61880[];
extern W584d0 *D_00F56DC0;
extern u64 *D_00F56DC8;
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);

#define RGBAQ(r, g, b, a) ((u64)(r) | ((u64)(g) << 8) | ((u64)(b) << 16) | ((u64)(a) << 24) | ((u64)0x3F800000 << 32))

void func_00f313d8(s32 n, s32 r, s32 g, s32 b) {
    s32 x0, y0, x1, y1, u0, v0, u1, v1;
    s32 idx = n + 22;
    u64 *p;

    x0 = 0;
    y0 = 142;
    x1 = x0 + D_00F61880[idx].w;
    v0 = D_00F61880[idx].v;
    y1 = D_00F61880[idx].h;
    u0 = D_00F61880[idx].u;
    v1 = v0 + D_00F61880[idx].h + 1;
    u1 = u0 + D_00F61880[idx].w + 1;
    p = func_00f3fa80(func_00f3f9d0(D_00F56DC8));
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
    p[0] = D_00F56DC0->tex[idx];
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
    func_00f3fa98(p);
    func_00f3fe80(12160, func_00f3f9e8(p));
    D_00F56DC8 = p;
}
