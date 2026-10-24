/* Projected shadows (docs/renderer-spec.md): the light-space matrix
 * (func_00127b98), the shadow models drawn into a texture (func_00127568,
 * func_00127960, func_00127c20; their records D_004F82C0), the GS packets
 * for the shadow texture (func_001284a0, func_00128738 on D_002E27E0) sent
 * through DMA (func_001274c8, func_00127500), func_00128218 an object's
 * shadow on the ground ray, func_00128b20 the reset. Flag mode: default (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C5C80.h"
#include "common.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"
#include "data/types/text_00120000_h5.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002E27A4.h"
#include "data/pieces/D_002C5C48.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/text_00120000_h31_p.h"
#include "data/pieces/D_002E26AC.h"
#include "data/pieces/D_00308CDC.h"
#include "data/types/text_00120000_h31.h"
#include "data/pieces/D_00351BC8.h"

/* func_001274c8 (from auto/text_00120000.c). */
M2C_UNK func_00266f38(s32, s32);
s32 func_00266c08(M2C_UNK);
s32 func_001274c8(void *arg0) {
    func_00266f38(func_00266c08(2), M2C_FIELD(arg0, s32 *, 0x10));
    return 2;
}

/* func_00127500 (from auto/text_00120000_16.c). */
void func_00121eb0(s32);
#define func_00266c08 ((s32 (*)(s32)) func_00266c08)
#define func_00266f38 ((void (*)(s32, s32)) func_00266f38)
s32 func_00127500(s32 arg0) {
  s32 *temp_v0;
  temp_v0 = func_00266c08(1);
  *temp_v0 = ((((*temp_v0) | 1) & (~0xC)) | 4) & (~0x30);
  *temp_v0 = (*temp_v0) & (~0x40);
  func_00266f38((s32) temp_v0, *((s32 *) (((s8 *) arg0) + 0x10)));
  func_00121eb0(*((s32 *) (((s8 *) arg0) + 0x10)));
  return 2;
}
#undef func_00266c08
#undef func_00266f38

/* func_00127b18 (from hand/text_00120000_h5.c). */
extern union { f32 f[4]; s32 i[4]; } D_002E27F0;
extern void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern void func_001149e8(f32 (*)[4], s32, s32, void *);
typedef struct SD0 { u8 pad[0xd0]; f32 m[4][4]; u8 pad110[0x44]; s32 f154; } SD0;
void func_00127b18(SD0 *a, f32 (*b)[4], s32 c) {
    f32 m[4][4] __attribute__((aligned(16)));
    sceVu0MulMatrix(m, b, a->m);
    D_002E27F0.f[3] = c;
    func_001149e8(m, a->f154, D_004F82C4 + D_004F82C0++, &D_002E27F0);
}

/* func_00127b98 (from auto/text_00120000_15.c). */
extern u8 D_004F82D0[];
void func_00127960(void *, void *, s32);
void func_00267328(void *, M2C_UNK *, s32);
#define D_004F82D0 (*(M2C_UNK (*)) &D_004F82D0)
#define func_00127b18 ((void (*)(void *, void *, s32)) func_00127b18)
void func_00127b98(void *arg0, s32 arg1, f32 fparg0) {
    s32 sp[16];
    func_00267328(sp, &D_004F82D0, arg1);
    if ((s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x27) & 1) {
        func_00127b18(arg0, sp, (s32) fparg0);
        return;
    }
    func_00127960(arg0, sp, (s32) fparg0);
}
#undef D_004F82D0
#undef func_00127b18

/* func_00128440 (from auto/text_00120000_8.c). */
extern D6 D_004F8270[];
void *func_0015ed80(M2C_UNK, M2C_UNK *);
#define D_004F8270 (*(M2C_UNK (*)) &D_004F8270)
s32 func_00128440(void) {
    D_004F82C0 = 0;
    M2C_FIELD(func_0015ed80(0xEC53, &func_001274c8), M2C_UNK **, 0x10) = &D_004F8270;
    M2C_FIELD(func_0015ed80(0xB1BB, &func_001274c8), M2C_UNK **, 0x10) = &D_004F8270;
    return 0;
}
#undef D_004F8270

/* func_001284a0 (from hand/text_00120000_b02.c). */
typedef union { struct { u64 a, b; } d; s32 w[4]; } QW;
extern s32 D_002E27E0[];
extern QW *func_0011fb38(s32, u64, QW *);
extern void func_0011fb48(QW *, s32, QW *);
extern void func_0011fb78(QW *, s32, QW *);
void func_001284a0(QW *buf, s32 idx) {
    QW *d;
    s32 w = D_002E27E0[idx];
    QW *t;
    s32 a, b, c;
    u64 r;
    d = buf;
    buf++;
    t = buf;
    buf++;
    buf = func_0011fb38(0x18, 0x0000780000007800ULL, buf);
    a = (256 - w) / 2;
    b = (256 + w) / 2;
    buf = func_0011fb38(0x40, (u64)a | (u64)(b - 1) << 16 | (u64)a << 32 | (u64)(b - 1) << 48, buf);
    buf = func_0011fb38(0x4c, 0x1000401d0ULL, buf);
    buf = func_0011fb38(0x4e, 0x3a0001c0, buf);
    buf = func_0011fb38(0x47, 0x30000, buf);
    buf = func_0011fb38(0x19, 0x0000780000007800ULL, buf);
    a += 2;
    b -= 3;
    r = (u64)a | (u64)b << 16 | (u64)a << 32 | (u64)b << 48;
    buf = func_0011fb38(0x41, r, buf);
    buf = func_0011fb38(0x4d, 0x1000401d0ULL, buf);
    buf = func_0011fb38(0x4f, 0x3a0001c0, buf);
    buf = func_0011fb38(0x16, 0x100000, buf);
    buf = func_0011fb38(0x3b, 0x80, buf);
    func_0011fb48(t, 0, buf);
    buf->d.a = 0x3003400000000001ULL;
    buf->d.b = 0x551;
    buf++;
    c = w / 2;
    buf->w[0] = 0;
    buf->w[3] = 0;
    buf->w[1] = 0;
    buf->w[2] = 0;
    buf++;
    buf->w[0] = (2048 - c) << 4;
    buf->w[1] = (2048 - c) << 4;
    buf->w[3] = 0x8000;
    buf->w[2] = 0;
    buf++;
    buf->w[0] = (2048 + c) << 4;
    buf->w[1] = (2048 + c) << 4;
    buf->w[2] = 0;
    buf->w[3] = 0;
    buf++;
    t = buf;
    buf = func_0011fb38(0x40, r, t + 1);
    buf = func_0011fb38(0x47, 0x5000d, buf);
    buf = func_0011fb38(0x48, 0x5000d, buf);
    func_0011fb48(t, 1, buf);
    func_0011fb78(d, 7, buf);
}

/* func_00128738 (from hand/text_00120000_b02.c). */
void func_00128738(QW *buf, s32 idx) {
    QW *d;
    s32 w = D_002E27E0[idx];
    QW *t;
    s32 a, b, c, m, n;
    d = buf;
    buf++;
    t = buf;
    buf++;
    buf = func_0011fb38(0x4c, 0x1000401b0ULL, buf);
    buf = func_0011fb38(0x18, 0x0000780000007800ULL, buf);
    m = 256 - w; n = 256 + w; b = n / 2; a = m / 2;
    buf = func_0011fb38(0x40, (u64)a | (u64)(b - 1) << 16 | (u64)a << 32 | (u64)(b - 1) << 48, buf);

    buf = func_0011fb38(6, 0x2000000620013a00ULL, buf);
    buf = func_0011fb38(0x14, 0x61, buf);
    buf = func_0011fb38(0x3f, 0, buf);
    buf = func_0011fb38(0x47, 0x30000, buf);
    buf = func_0011fb38(0x42, 0x8000000044ULL, buf);
    buf = func_0011fb38(0x3b, 0x8000000000ULL, buf);
    buf = func_0011fb38(0x4e, 0x100000000ULL, buf);
    func_0011fb48(t, 0, buf);
    buf->d.a = 0x508b400000000001ULL;
    buf->d.b = 0x53531;
    buf++;
    c = w / 2;
    buf->w[0] = 128;
    buf->w[1] = 128;
    buf->w[2] = 128;
    buf->w[3] = 128;
    buf++;
    buf->w[0] = m << 3;
    buf->w[1] = m << 3;
    buf++;
    buf->w[0] = (2048 - c) << 4;
    buf->w[1] = (2048 - c) << 4;
    buf->w[3] = 0x8000;
    buf->w[2] = 0;
    buf++;
    buf->w[0] = n << 3;
    buf->w[1] = n << 3;
    buf++;
    buf->w[0] = (2048 + c) << 4;
    buf->w[1] = (2048 + c) << 4;
    buf->w[2] = 0;
    buf->w[3] = 0;
    buf++;
    t = buf;
    buf++;
    buf = func_0011fb38(0x18, 0x0000740000007000ULL, buf);
    buf = func_0011fb38(0x40, 0x017F000001FF0000ULL, buf);
    buf = func_0011fb38(0x4c, 0x800d0, buf);
    buf = func_0011fb38(0x4e, 0x31000070, buf);
    buf = func_0011fb38(0x19, 0x0000740000007000ULL, buf);
    buf = func_0011fb38(0x41, 0x017F000001FF0000ULL, buf);
    buf = func_0011fb38(0x4d, 0x800d0, buf);
    buf = func_0011fb38(0x4f, 0x31000070, buf);
    func_0011fb48(t, 0, buf);
    t = buf;
    buf++;
    buf = func_0011fb38(0x48, 0x5000d, buf);
    buf = func_0011fb38(7, 0x2000000620013600ULL, buf);
    buf = func_0011fb38(0x15, 0x61, buf);
    buf = func_0011fb38(9, (u64)(a + 1) << 4 | (u64)(b - 1) << 14 | 10 | (u64)(a + 1) << 24 | (u64)(b - 1) << 34, buf);
    buf = func_0011fb38(0x3f, 0, buf);
    buf = func_0011fb38(0x43, 0x4000000044ULL, buf);
    func_0011fb48(t, 1, buf);
    func_0011fb78(d, 7, buf);
}

/* func_00128b20 (from hand/text_00120000_h31.c). */
extern void func_0011ef10(s32, void *);
extern A6 D_004F7820[3];
extern B6 D_004F7C10[3];
extern void func_00267b08(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
#define func_001284a0 ((void (*)(A6 *, s32)) func_001284a0)
#define func_00128738 ((void (*)(B6 *, s32)) func_00128738)
#define func_0011fb38 ((void *(*)(s32, s32, void *)) func_0011fb38)
#define func_0011fb48 ((void (*)(void *, s32, void *)) func_0011fb48)
#define func_0011fb78 ((void (*)(void *, s32, void *)) func_0011fb78)
void func_00128b20(void) {
    s32 i;
    u8 *q, *d, *b;
    for (i = 0; i < 3; i++) {
        func_001284a0(&D_004F7820[i], i);
        func_00128738(&D_004F7C10[i], i);
    }
    q = (u8 *)D_004F8270;
    d = q;
    q += 16;
    b = q;
    q = func_0011fb38(0x47, 0x50000, b + 16);
    q = func_0011fb38(0x48, 0x50000, q);
    q = func_0011fb38(0x14, 0x60, q);
    func_0011fb48(b, 1, q);
    func_0011fb78(d, 7, q);
    D_00351BC8(0);
    func_00267b08(D_004F82D0, 32768.0f, 1.0f, 1.0f, 2048.0f, 2048.0f, 1.0f, 65535.0f, 1.0f, 65535.0f);
    func_0011ef10(0x1fbcf, func_00128440);
}
#undef func_001284a0
#undef func_00128738
#undef func_0011fb38
#undef func_0011fb48
#undef func_0011fb78

