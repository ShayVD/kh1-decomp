#include "common.h"
/* func_001bc530 (hand, strict): matched in s10 r2_8. Key: lo->x/y/z computed first and v[0..2] copied from them (v[k] = lo->x), then hi, sz, v[3..5]; natural min/max order. */
typedef struct { u16 pos; u16 rot; u16 id; u16 x6; u8 pad8[4]; } CdPiece;
typedef struct { s32 x0; u16 n; u16 x6; u16 x8; u16 x10; u8 c12; u8 pad13[0x70 - 13]; CdPiece p[(0xF70 - 0x70) / 12]; } CdEnt;
typedef struct { f32 x, y, z, w; } V4;
s32 func_001bbdf0(CdPiece *);
#include "platform/math.h"
#define DX ((u16)r & 0xf)
#define DY (((u16)r >> 4) & 0xf)
#define DZ (((u16)r >> 8) & 0xf)
void func_001bc530(V4 *lo, V4 *hi, V4 *sz, CdEnt *a) {
    f32 v[6];
    f32 h[3];
    s32 i, first;
    s32 x0, y0, z0, x1, y1, z1;
    s32 px, py, pz, dx, dy, dz;
    s32 r, pos;
    CdPiece *pc;
    if (a->n == 0) {
        sz->x = 200.0f;
        sz->y = 200.0f;
        sz->z = 200.0f;
        sz->w = 200.0f;
        return;
    }
    
    x0 = 0;
    y0 = 0;
    z0 = 0;
    x1 = 0;
    y1 = 0;
    z1 = 0;

    pc = a->p;
    first = 0;
    for (i = 0; i < a->n; i++, pc++) {
        r = func_001bbdf0(pc);
        pos = pc->pos;
        px = (u16)pos & 0xf;
        py = ((u16)pos >> 4) & 0xf;
        pz = ((u16)pos >> 8) & 0xf;
        if (first) {
            if (px < x0) x0 = px;
            if (py < y0) y0 = py;
            if (pz < z0) z0 = pz;
            if (x1 < px + DX - 1) x1 = px + DX - 1;
            if (y1 < py + DY - 1) y1 = py + DY - 1;
            if (z1 < pz + DZ - 1) z1 = pz + DZ - 1;
        } else {
            x0 = px;
            y0 = py;
            z0 = pz;
            x1 = x0 + DX - 1;
            y1 = y0 + DY - 1;
            z1 = z0 + DZ - 1;
        }
        first = 1;
    }
    h[0] = a->x6 * 200.0f * 0.5f;
    h[1] = a->x8 * 200.0f * 0.5f;
    h[2] = a->x10 * 200.0f * 0.5f;
    lo->x = x0 * 200.0f - h[0];
    lo->y = y0 * 200.0f - h[1];
    lo->z = z0 * 200.0f - h[2];
    v[0] = lo->x;
    v[1] = lo->y;
    v[2] = lo->z;
    hi->x = (x1 + 1) * 200.0f - h[0];
    hi->y = (y1 + 1) * 200.0f - h[1];
    hi->z = (z1 + 1) * 200.0f - h[2];
    sz->x = (x1 - x0 + 1) * 200.0f;
    sz->y = (y1 - y0 + 1) * 200.0f;
    sz->z = (z1 - z0 + 1) * 200.0f;
    v[3] = x1 * 200.0f - h[0];
    v[4] = y1 * 200.0f - h[1];
    v[5] = z1 * 200.0f - h[2];
    for (i = 0; i < 6; i++) {
        if (v[i] < 0.0f) v[i] = -v[i];
    }
    if (v[3] > v[0]) v[0] = v[3];
    if (v[4] > v[1]) v[1] = v[4];
    if (v[5] > v[2]) v[2] = v[5];
    sz->w = PlatSqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (sz->w <= 0.0f) sz->w = 200.0f;
}
