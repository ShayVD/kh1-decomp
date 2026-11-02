/* wm.x func_00f33e48: first draft (session 142, for the native overlay), written from the asm.
 * Not a match: only checked by reading it against the asm.
 *
 * Loads Gummi ship `src` into the work copy D_00FCC680 (func_001bcd10, then func_00f2c518) and
 * fills the ship's view record D_00F85240: the grid's centre offset (-sx / 2, sy / 2, -sz / 2
 * blocks of 200), each piece copied (12 bytes from +0x34), the bounds of the pieces in blocks
 * (lo / hi, from each piece's position nibbles and its size, func_001bbdf0), their size and a
 * radius (the farthest corner from the centre on each axis). On the way: a 192-byte "id used"
 * table D_00FBDAF8, the index of the piece whose block type is 1 (D_00FBDA70), func_00f33aa0 /
 * func_00f33d30 for the block kinds that take one (type 1-5, 8, 9 except ids 0x84, 0x85 and
 * 0x8E; id 0x8E always), and two flag sets from ids 45-58, handed to func_00f2abe8(28 / 29)
 * when `flags` is set. */
#include "ovl.h"

typedef struct {
    u16 pos;  /* 0x0: x, y, z nibbles */
    u16 rot;  /* 0x2 */
    u16 id;   /* 0x4: block id + 1 */
    u16 x6;
    u8 pad8[4];
} Piece;

typedef struct {
    s32 x0;
    u16 n;  /* 0x04 */
    u16 sx; /* 0x06 */
    u16 sy; /* 0x08 */
    u16 sz; /* 0x0a */
    u8 pad0c[0x70 - 0x0c];
    Piece p[(0xF70 - 0x70) / 12]; /* 0x70 */
} Ship;

typedef struct {
    u8 pad0[4];
    u8 type; /* 0x04 */
} Block;

typedef struct {
    u8 b[12];
} Raw12;

typedef struct {
    s32 n;        /* 0x00 */
    u8 pad4[12];
    f32 org[4];   /* 0x10: the grid's centre offset; w = 1 */
    f32 ext[3];   /* 0x20: the bounds' size */
    f32 radius;   /* 0x2c */
    f32 zoff;     /* 0x30 */
    Raw12 p[1];   /* 0x34: the pieces */
} View;

extern Ship D_00FCC680;
extern View D_00F85240;
extern u8 D_00F85250[];
extern s32 D_00FBBA68;
extern s32 D_00FCC560;
extern s32 D_00FBDA70;
extern u8 D_00FBDAF8[192];

s32 func_001bcd10(Ship *, s32);
void func_00f2c518(Ship *);
u16 func_001bbdf0(Piece *);
Block *func_001bb658(s32);
void func_00f2abe8(s32, s8);
void func_00f33aa0(void *, s32, s32, s32, s32, s32, s32);
void func_00f33d30(void *, s32, s32, s32, s32, s32, s32, s32);

void func_00f33e48(s32 src, s32 flags) {
    f32 a[4], b[4];
    s32 x0, y0, z0, x1, y1, z1;
    s32 i, first, f1, f2;
    s32 px, py, pz, sx, sy, sz;
    u32 size, pos;
    f32 hx, hy, hz;
    Piece *rec;
    Raw12 *dst;
    Block *blk;
    u16 id;

    f2 = 0;
    f1 = 0;
    first = 0;
    func_001bcd10(&D_00FCC680, src);
    func_00f2c518(&D_00FCC680);
    D_00FBBA68 = 0;
    D_00F85240.org[3] = 1.0f;
    D_00FCC560 = 0;
    dst = D_00F85240.p;
    x0 = y0 = z0 = x1 = y1 = z1 = 0;
    D_00F85240.org[1] = D_00FCC680.sy * 0.5f * 200.0f;
    D_00F85240.org[0] = -(D_00FCC680.sx * 0.5f) * 200.0f;
    D_00F85240.org[2] = -(D_00FCC680.sz * 0.5f) * 200.0f;
    for (i = 191; i >= 0; i--) D_00FBDAF8[i] = 0;

    rec = D_00FCC680.p;
    for (i = 0; i < D_00FCC680.n; i++, rec++, dst++) {
        *dst = *(Raw12 *)rec;
        size = func_001bbdf0(rec);
        pos = rec->pos;
        px = pos & 15;
        py = (pos >> 4) & 15;
        pz = (pos >> 8) & 15;
        size &= 0xFFFF;
        sx = size & 15;
        sy = (size >> 4) & 15;
        sz = (size >> 8) & 15;
        if (first) {
            if (x1 < px + sx - 1) x1 = px + sx - 1;
            if (y1 < py + sy - 1) y1 = py + sy - 1;
            if (px < x0) x0 = px;
            if (py < y0) y0 = py;
            if (pz < z0) z0 = pz;
            if (z1 < pz + sz - 1) z1 = pz + sz - 1;
        } else {
            x0 = px;
            y0 = py;
            z0 = pz;
            x1 = px + sx - 1;
            y1 = py + sy - 1;
            z1 = pz + sz - 1;
        }
        blk = func_001bb658(rec->id - 1);
        if ((u8)(blk->type - 3) < 3 || blk->type == 1 || blk->type == 2 || blk->type == 8 || blk->type == 9) {
            id = rec->id;
            if ((u16)(id - 0x84) >= 2 && id != 0x8E)
                func_00f33aa0(D_00F85250, px, py, pz, sx, sy, sz);
        }
        if (rec->id == 0x8E)
            func_00f33d30(D_00F85250, px, py, pz, sx, sy, sz, (rec->rot >> 8) & 15);
        if (blk->type == 1) D_00FBDA70 = i;
        id = rec->id;
        D_00FBDAF8[id - 1] = 1;
        switch (id) {
        case 45: case 46: f2 |= 0x40; break;
        case 47: case 48: f2 |= -128; break;
        case 49: f1 |= 2; break;
        case 50: f1 |= 1; break;
        case 51: f2 |= 4; break;
        case 52: f2 |= 8; break;
        case 53: f2 |= 0x10; break;
        case 54: f2 |= 0x20; break;
        case 55: f2 |= 1; break;
        case 56: f2 |= 2; break;
        case 57: f1 |= 4; break;
        case 58: f1 |= 8; break;
        }
        first = 1;
    }
    if (flags) {
        func_00f2abe8(28, f1);
        func_00f2abe8(29, f2);
    }

    hx = D_00FCC680.sx * 0.5f;
    hz = D_00FCC680.sz * 0.5f;
    D_00F85240.n = D_00FCC680.n;
    hy = D_00FCC680.sy * 0.5f;
    a[0] = __builtin_fabsf(((f32)x0 - hx) * 200.0f);
    b[0] = __builtin_fabsf(((f32)x1 + 1.0f - hx) * 200.0f);
    a[1] = __builtin_fabsf(((f32)y0 - hy) * 200.0f);
    D_00F85240.ext[0] = (f32)(x1 - x0 + 1) * 200.0f;
    a[2] = __builtin_fabsf(((f32)z0 - hz) * 200.0f);
    D_00F85240.ext[1] = (f32)(y1 - y0 + 1) * 200.0f;
    b[1] = __builtin_fabsf(((f32)y1 + 1.0f - hy) * 200.0f);
    D_00F85240.ext[2] = (f32)(z1 - z0 + 1) * 200.0f;
    b[2] = __builtin_fabsf(((f32)z1 + 1.0f - hz) * 200.0f);
    D_00F85240.zoff = (hz - (f32)z0) * 200.0f;
    if (b[0] < a[0]) b[0] = a[0];
    if (b[1] < a[1]) b[1] = a[1];
    if (b[2] < a[2]) b[2] = a[2];
    D_00F85240.radius = __builtin_sqrtf(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);
}
