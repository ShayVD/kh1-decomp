#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct {
    u64 d[18];
    s32 x90, x94, x98, x9c;
    s32 xa0, xa4, xa8, xac;
    s32 xb0, xb4, xb8, xbc;
    s32 xc0, xc4, xc8, xcc;
} Pk;
extern Glyph *D_003E8E28;
extern s32 D_003E8D00[];
extern s32 D_0063F74C;
extern s32 D_0063F750;
void func_001efb78(s32);
void func_001efb98(s32);
s32 func_001efb88(void);

Pk *func_001f15f0(Pk *p, s32 a1, u32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    Glyph *g;
    s32 w, x, y, z, s, t, h;
    s32 f2, f4;
    u8 f7;
    func_001efb78(0);
    func_001efb98(0);
    x = a4 * 16;
    p->d[0] = 0x6000000000000001;
    p->d[1] = 0xeeeeee;
    p->d[3] = 0x3f;
    p->d[9] = 22;
    p->d[4] = 0x2007ff8622411000;
    p->d[5] = 6;
    p->d[6] = 97;
    p->d[7] = 20;
    y = a3 * 16 + 0x7000;
    p->d[8] = 0x4007ff8001300000;
    h = a6 * 16;
    p->d[2] = 0;
    p->d[10] = 68;
    p->d[11] = 66;
    z = x + 0x7400;
    p->d[13] = 1;
    p->d[15] = 0x4343e;
    p->d[12] = a2;
    p->d[14] = ((u64)a1 << 15) | 0x50ab400000000001;
    g = &D_003E8E28[a5];
    w = g->w << 4;
    s = w * a6 / 18;
    t = (w + func_001efb88()) * a6 / 18;
    f2 = g->f2;
    f7 = g->f7;
    p->d[16] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
    p->xa0 = y;
    f4 = g->f4;
    p->x90 = f2;
    p->d[17] = 22;
    p->xac = 0x8000;
    p->xb0 = f2 + w;
    p->x94 = f4;
    p->xa4 = z;
    p->xa8 = 0x100000;
    p->xcc = 0;
    p->xb4 = f4 + 288;
    p->xc0 = y + s;
    p->xc8 = 0x100000;
    p->xc4 = z + h;
    D_0063F74C = (y + t - 0x7000) >> 4;
    D_0063F750 = x >> 4;
    return p + 1;
}

#include "data/types/nofill_text_001f0000_h69.h"
extern Q D_003F1A70[];
extern Q D_003F1E70[];
extern Q D_003F2270[];
extern Q D_003F27D0[];
#include "data/pieces/D_003E9660.h"
#include "data/pieces/D_003F2670.h"
#include "data/pieces/D_003F1660.h"
#include "data/pieces/D_003F2720.h"
extern s32 D_003F1A68;
void func_0011fb78(Q *, s32, Q *);
Q *func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, u32, Q *, Q *);
void func_001f3110(void);

void func_001f2eb8(void) {
    Q *p, *d;
    p = D_003F1A70;
    d = p;
    p++;
    p->a = 0x1000000000008001;
    p->b = 14;
    p++;
    p->b = 0x47;
    p->a = 0x4000d;
    p++;
    func_0011fb78(d, 7, p);
    func_0011fbb0(0x3d7c, 4, 20, 0, 0, 256, 256, 2048, D_003E9660, D_003F2670);
    func_0011fbb0(0x3dfc, 1, 0, 0, 0, 16, 16, 64, D_003F1660, D_003F2720);
    p = D_003F1E70;
    d = p;
    p++;
    p->a = 0x1000000000008004;
    p->b = 14;
    p++;
    p->a = 0x4000d;
    p->b = 0x47;
    p++;
    p->b = 0x3f;
    p->a = 0;
    p++;
    p->a = 0x2007bf8621413d7c;
    p->b = 6;
    p++;
    p->a = 0x61;
    p->b = 0x14;
    p++;
    func_0011fb78(d, 7, p);
    p = D_003F2270;
    d = p;
    p++;
    p->a = 0x1000000000008004;
    p->b = 14;
    p++;
    p->a = 0x4000d;
    p->b = 0x47;
    p++;
    p->b = 0x3f;
    p->a = 0;
    p++;
    p->a = 0x2007ff8622411000;
    p->b = 6;
    p++;
    p->a = 0x61;
    p->b = 0x14;
    p++;
    func_0011fb78(d, 7, p);
    p = D_003F27D0;
    d = p;
    p++;
    p->a = 0x1000000000008001;
    p->b = 14;
    p++;
    p->b = 0x47;
    p->a = 0x5000d;
    p++;
    func_0011fb78(d, 7, p);
    D_003F1A68 = 0;
    func_001f3110();
}
#include "data/data_003E.h"
#include "data/pieces/D_003F1A68.h"
