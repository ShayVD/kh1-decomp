/* The HUD's drawing helpers (docs/modules.md "Session 46"), 0x00239558-0x00239e30
 * (nostrict_nofill part).  func_00239558 draws a glyph (text.c's func_001f0638) in
 * grey level c at (x, y) with the HUD's alpha D_00650DD0.  func_00239630 /
 * func_00239860 / func_00239b90 fill the sprite packet D_00648900 from a sprite
 * (func_0024aa48), move it by (dx, dy), scale its colours by s (and its alpha by
 * D_00650DD4) and send it with func_002388b8 (src/gfx/prim.nostrict_nofill.c)
 * into the buffer D_006488F0; func_00239860 / func_00239b90 first take the
 * colours from one or four caller colours. */
#include "common.h"
#include "data/bss_0064_mixed.h"
#include "data/bss_0065.h"

typedef struct { u8 r, g, b, a; } Rgba;
typedef struct { u8 pad[4]; u16 x4; } Res;
typedef struct { s32 x, y, z, w; } I4b;
/* The textured quad func_0024aa48 writes and func_002388b8 sends. */
typedef struct { u8 pad[0x60]; s32 c[4][4]; I4b p[4]; } Spr6;

extern Spr6 D_00648900;
extern f32 D_00650DD0;
extern f32 D_00650DD4;
extern s32 D_006488F0;
Res *func_001478c8(s32);
s32 func_00147808(s32);
s32 func_001f0638(s32, s32, s32, s32, s32, s32);
void func_0024aa48(void *, Spr6 *, void *);
s32 func_002388b8(Spr6 *, s32, s32);

void func_00239558(s32 id, s32 x, s32 y, s32 c) {
    Rgba col;
    u8 v = c;
    col.r = v;
    col.g = v;
    col.b = v;
    col.a = D_00650DD0 * 128.0f;
    D_006488F0 = func_001f0638(D_006488F0, 1, *(s32 *)&col, ((x * 16 + 0x7100) >> 4) - 0x700,
                               ((y * 16 + 0x7420) >> 4) - 0x740, func_00147808(func_001478c8(id)->x4));
}

void func_00239630(void *a0, void *a1, s32 dx, s32 dy, f32 s) {
    s32 i, j;
    s32 *q;
    func_0024aa48(a0, &D_00648900, a1);
    for (i = 0; i < 4; i++) {
        q = &D_00648900.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_00648900.c[i][j] = D_00648900.c[i][j] * s;
        }
    }
    for (i = 0; i < 4; i++) {
        D_00648900.c[i][3] = D_00648900.c[i][3] * D_00650DD4;
    }
    D_006488F0 = func_002388b8(&D_00648900, 1, D_006488F0);
}

void func_00239860(void *a0, void *a1, s32 dx, s32 dy, f32 s, s32 scale, s32 *src, s32 all) {
    s32 i, j;
    s32 *q;
    func_0024aa48(a0, &D_00648900, a1);
    for (i = 0; i < 4; i++) {
        q = &D_00648900.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (all || j != 3) D_00648900.c[i][j] = src[j];
            if (scale) D_00648900.c[i][j] = D_00648900.c[i][j] * s;
        }
    }
    for (i = 0; i < 4; i++) {
        D_00648900.c[i][3] = D_00648900.c[i][3] * D_00650DD4;
    }
    D_006488F0 = func_002388b8(&D_00648900, 1, D_006488F0);
}

void func_00239b90(void *a0, void *a1, s32 dx, s32 dy, f32 s, s32 scale, s32 (*src)[4], s32 all) {
    s32 i, j;
    s32 *q;
    func_0024aa48(a0, &D_00648900, a1);
    for (i = 0; i < 4; i++) {
        q = &D_00648900.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (all || j != 3) D_00648900.c[i][j] = src[i][j];
            if (scale) D_00648900.c[i][j] = D_00648900.c[i][j] * s;
        }
    }
    for (i = 0; i < 4; i++) {
        D_00648900.c[i][3] = D_00648900.c[i][3] * D_00650DD4;
    }
    D_006488F0 = func_002388b8(&D_00648900, 1, D_006488F0);
}

