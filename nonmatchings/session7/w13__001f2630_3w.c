/* func_001f2630: 3w off, hand/nofill (w4 draft 4w). Annealed (multi-move, ~90k orders) store block; only the g->x2c (li a1,0x8000) sw is still scheduled right after the d[1] sd (orig: after the x14 store). */
#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 a, b; } Q;
typedef struct {
    u64 d[2];
    s32 x10, x14, x18, x1c;
    s32 x20, x24, x28, x2c;
    s32 x30, x34, x38, x3c;
    s32 x40, x44, x48, x4c;
} Pg;
extern Glyph *D_003E8E28;
extern s32 D_003E8D00[];
extern s32 D_0063F740;
extern s32 D_0063F74C;
extern s32 D_0063F750;

#define SETX() \
    switch (mode) { \
    case 0: \
    default: \
        cx = x * 16 + 0x7000; \
        break; \
    case 1: \
        cx = (x - func_001f0340(str, sc)) * 16 + 0x7000; \
        break; \
    case 2: \
        cx = (x - func_001f0340(str, sc) / 2) * 16 + 0x7000; \
        break; \
    }

extern s32 D_003E8E00;
extern s32 D_003E8E04;
extern s32 D_003E8E2C;
CONTEXT_ONLY void func_001efb78(s32 arg0) { D_003E8E00 = arg0; }
CONTEXT_ONLY s32 func_001efb88(void) { return D_003E8E00; }
CONTEXT_ONLY void func_001efb98(s32 arg0) { D_003E8E04 = arg0; }
CONTEXT_ONLY s32 func_001efba8(void) { return D_003E8E04; }
CONTEXT_ONLY s32 func_001eff50(s32 a) {
    s32 i;
    Glyph *e = D_003E8E28;
    for (i = 0; i < D_003E8E2C; i++, e++) {
        if (e->code == a) return i;
    }
    return 0;
}
CONTEXT_ONLY s32 func_001f0340(u8 *p, s32 scale) {
    s32 d = 18;
    s32 x = 0;
    for (;;) {
        s32 c = *p;
        s32 k;
        if (c == 0 || c == 10) return x >> 4;
        k = c | (p[1] << 8);
        p += 2;
        if (k == 0x4081) {
            x += (scale << 8) / d;
        } else {
            Glyph *g = &D_003E8E28[func_001eff50(k)];
            x += ((g->w << 4) + func_001efb88()) * scale / d;
        }
    }
}

s32 func_00266c08(s32);
void func_00266f38(s32, void *);
Q *func_00122048(s32, s32);
s32 sceGsSyncPath(s32, u16);
void func_001220b8(void *);
extern u8 D_003F2270[];

void func_001f2630(s32 mode, u32 a1, s32 x, s32 y, u8 *str, s32 sc) {
    u64 *d;
    Q *buf;
    void *dma;
    Pg *g;
    Glyph *gl;
    s32 cx, cy, c, w, s, h;
    u8 f7;
    s32 f2, f4, t, a;

    func_001efb78(0);
    func_001efb98(0);
    h = sc * 16;
    func_00266f38(func_00266c08(2), D_003F2270);
    buf = func_00122048(1024, 128);
    dma = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    g = (Pg *)(buf + 1);
    d = (u64 *)g;
    d[0] = 0x4000000000000001;
    d[1] = 0xeeee;
    d[2] = 0;
    d[3] = 0x3f;
    d[4] = 0x4007ff8001300000;
    d[5] = 22;
    d[6] = 68;
    d[7] = 66;
    d[8] = a1;
    d[9] = 1;
    d[10] = 0x50ab400000008001;
    d[11] = 0x4343e;
    *(u64 *)buf = 0x7000000b;
    g = (Pg *)(buf + 7);
    cy = y * 16 + 0x7400;
    SETX();
    for (;;) {
        c = *str;
        if (c == 0) goto done;
        if (c == '\n') {
            str++;
            cy += D_0063F740;
            SETX();
            continue;
        }
        c |= str[1] << 8;
        str += 2;
        if (c == 0x4081) {
            cx += (sc << 8) / 18;
            continue;
        }
        gl = &D_003E8E28[func_001eff50(c)];
        w = gl->w << 4;
        s = w * sc / 18;
        a = (w + func_001efb88()) * sc / 18;
/*P*/
        f7 = gl->f7;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        f4 = gl->f4;
        g->x24 = cy;
        g->d[1] = 22;
        g->x28 = 0x100000;
        g->x2c = 0x8000;
        f2 = gl->f2;
        g->x44 = cy + h;
        g->x34 = f4 + 288;
        g->x20 = cx;
        g->x30 = f2 + w;
        g->x40 = cx + s;
        g->x48 = 0x100000;
        g->x4c = 0;
        g->x14 = f4;
        g->x10 = f2;
/*Q*/
        t = func_00266c08(2);
        cx += a;
        func_00266f38(t, dma);
        sceGsSyncPath(0, 0);
    }
done:
    func_001220b8(buf);
    D_0063F74C = (cx - 0x7000) >> 4;
    D_0063F750 = (cy - 0x7400) >> 4;
}
