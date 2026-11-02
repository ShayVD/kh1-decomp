/* wm.x func_00f5cb78: matched by hand (session 141, wwm1 round 17): a CONTEXT_ONLY func_00f5c8a8 and func_00f5c9b0 above it. A call to a function defined earlier in the file is nothrow, which changes reorg's branch-likely choice (docs/overlays.md, "Branch-likely vs plain branch"). */
#include "ovl.h"
typedef struct {
    u8 pad0[0xA0];
    u8 xA0[6];
    u16 hA6;
    u16 hA8;
    u16 hAA;
    u8 padAC[0x1010 - 0xAC];
    f32 m[4][4];
} W5c;
typedef struct {
    u8 pad0[10];
    u8 b10;
    u8 padB[5];
    f32 v10[4];
    f32 v20[4];
    u8 pad30[48];
} B5c;
typedef struct {
    f32 x0, x4, x8, xC;
    u8 pad10[0x30];
    f32 pos[4];
    f32 rot[4];
} C5c;
typedef struct { u8 pad[4]; s32 x4; s32 x8; } P5c;
extern W5c *D_00F9B540;
extern s32 D_00FA5E3C;
extern s32 D_00FA5E38;
extern f32 D_0108CFD0[4];
extern f32 D_0108CFE0[4];
extern f32 D_0108CFF0[4];
extern f32 D_0108D000[4];
extern f32 D_00FA5DB0[4];
extern C5c D_0108D120;
extern s32 D_0108D184;
extern s32 D_0108D188;
extern s32 D_0108D010;
extern f32 D_0108D020[4][4];
extern f32 D_00F9B580[4][4];
extern f32 D_00F9B600[4][4];
void func_001bc900(void *, B5c *);
void func_001bd9e8(void *);
void func_001bd470(void);
void sceVu0CopyVector(f32 *, f32 *);
void func_00f5c908(s32);
void sceVu0ViewScreenMatrix(f32 (*)[4], f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_001be9f0(f32 *);
void func_00f4fd68(void);
s32 func_001c0310(s32, void (*)(void), ...);
void func_00f5c4b0(void);
void func_00f5c4e0(void);
void func_00f5aa60(void);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void sceVu0RotMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void func_001bfac8(void);
P5c *func_001ba488(s32);
s32 func_00f4c510(P5c *);
CONTEXT_ONLY void func_00f5c8a8(void) {}
void func_00f4cb10(void);
void func_00f48aa8(s32);
s32 func_00f47158(void);
void func_00f47268(s32, s32);
CONTEXT_ONLY void func_00f5c9b0(s32 a0) {}
void func_001bebd0(f32 (*)[4], C5c *, f32 (*)[4]);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00f4ff08(s32, f32, s32);
#else
void func_00f4ff08(s32, s32, f32);
static __inline__ void ee_00f4ff08(s32 x0, f32 x1, s32 x2) { func_00f4ff08(x0, x2, x1); }
#undef func_00f4ff08
#define func_00f4ff08 ee_00f4ff08
#endif
void func_00f4cb60(void);

void func_00f5cb78(void) {
    f32 m[4][4];
    B5c buf;
    f32 x, y, z;
    f32 lo, hi, d;
    s32 i, n, k;
    P5c *p;
    u32 v;

    D_00FA5E3C = 0;
    func_001bc900(D_00F9B540->xA0, &buf);
    func_001bd9e8(D_00F9B540->xA0);
    func_001bd470();
    D_00FA5E38 = -1;
    x = -(D_00F9B540->hA6 * 0.5f) * 200.0f;
    y = D_00F9B540->hA8 * 0.5f * 200.0f;
    z = -(D_00F9B540->hAA * 0.5f) * 200.0f;
    D_0108D000[3] = 1.0f;
    D_00FA5DB0[3] = 1.0f;
    D_0108D000[1] = y;
    D_0108D000[2] = z;
    D_0108D000[0] = x;
    D_00FA5DB0[1] = -y;
    D_00FA5DB0[2] = -z;
    D_00FA5DB0[0] = -x;
    sceVu0CopyVector(D_0108CFD0, buf.v10);
    sceVu0CopyVector(D_0108CFE0, buf.v20);
    for (i = 0; i < 3; i++) {
        D_0108CFF0[i] = D_0108CFD0[i] + (D_0108CFE0[i] - D_0108CFD0[i]) * 0.5f;
    }
    D_0108CFF0[3] = 1.0f;
    func_00f5c908(buf.b10);
    sceVu0ViewScreenMatrix(m, 512.0f, 1.0f, 1.0f, 2064.0f, 2080.0f, 1.0f, 16777000.0f, 1.0f, 65536.0f);
    d = 0.0349065810442f;
    n = 0;
    hi = D_0108D120.x8 + (f32)(D_00F9B540->hA6 * 120);
    lo = D_0108D120.x8 - ((f32)(D_00F9B540->hA6 * 120) + (f32)(D_00F9B540->hA6 * 120));
    func_001be9f0(D_0108D120.rot);
    func_00f4fd68();
    func_001c0310(-1, func_00f5c4b0);
    D_0108D184 = 0;
    D_0108D010 = 1;
    for (;;) {
        sceVu0CopyMatrix(D_00F9B580, m);
        n++;
        sceVu0UnitMatrix(D_00F9B600);
        sceVu0TransMatrix(D_00F9B600, D_00F9B600, D_0108D120.pos);
        sceVu0RotMatrix(D_00F9B600, D_00F9B600, D_0108D120.rot);
        D_00F9B600[3][2] -= D_0108D120.x8;
        if (n < 5) {
            func_001bfac8();
            continue;
        }
        p = func_001ba488(0);
        k = func_00f4c510(p);
        v = p->x8;
        if (v & 0x4200) {
            D_0108D010 = 0;
            func_00f5c8a8();
            func_00f4cb10();
            func_00f48aa8(1);
            return;
        }
        if (v & 8) {
            if (!func_00f47158()) {
                D_0108D010 = 0;
                func_00f5c8a8();
                func_00f4cb10();
                func_001c0310(-1, func_00f5aa60);
                func_00f48aa8(3);
                return;
            }
            v = p->x8;
        }
        if (v & 1) {
            D_0108D010 = 0;
            n = 0;
            D_00FA5E3C = 1;
            func_00f5c8a8();
            func_00f47268(2, 0);
            func_001c0310(-1, func_00f5c4b0);
            D_00FA5E3C = 0;
            D_0108D010 = 1;
        } else if (v & 0x8000) {
            func_00f5c9b0(0);
        } else if (v & 0x1000) {
            func_00f5c9b0(1);
        } else if (D_0108D184 == 0 && (v & 0x2000)) {
            D_0108D188 = func_001c0310(-1, func_00f5c4e0);
        } else {
            if (k & 0x1000) D_0108D120.rot[0] -= d;
            if (k & 0x4000) D_0108D120.rot[0] += d;
            if (k & 0x8000) D_0108D120.rot[1] += d;
            if (k & 0x2000) D_0108D120.rot[1] -= d;
            if (p->x4 & 0x400) D_0108D120.x8 += 20.0f;
            if (p->x4 & 0x100) D_0108D120.x8 -= 20.0f;
            if (D_0108D120.x8 < lo) D_0108D120.x8 = lo;
            if (hi < D_0108D120.x8) D_0108D120.x8 = hi;
        }
        func_001be9f0(D_0108D120.rot);
        func_001bebd0(D_0108D020, &D_0108D120, D_00F9B540->m);
        func_00f4ff08(50, 0.5f, 1);
        func_00f4ff08(51, 0.5f, 1);
        func_00f4cb60();
        func_001bfac8();
    }
}
