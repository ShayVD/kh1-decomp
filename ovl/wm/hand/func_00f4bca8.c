/* wm.x func_00f4bca8: matched by hand. */
#include "ovl.h"

typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 pad : 4; u8 rest[10]; } E4bc;
typedef struct { u8 pad[6]; u16 nx; u16 ny; u16 nz; } D4bc;
typedef struct { u8 pad[0xA0]; union { D4bc d; struct { u8 p[4]; u16 n; } c; } u; u8 pad3[0x110 - 0xAC]; E4bc e[1]; } W4bc;
typedef struct { u32 pad; u16 x0 : 4; u32 y0 : 4; u32 z0 : 4; u32 : 4; u32 x1 : 4; u32 y1 : 4; u32 z1 : 4; } B4bc;
extern W4bc *D_00F9B540;

s32 func_00f4bca8(s32 x, s32 y, s32 z, B4bc *b)
{
    D4bc *d = &D_00F9B540->u.d;
    s32 i;
    E4bc *e;

    if (x + b->x0 < 0) x = 0;
    if (y + b->y0 < 0) y = 0;
    if (z + b->z0 < 0) z = 0;
    if (x + b->x1 >= d->nx) x = 0;
    if (y + b->y1 >= d->ny) y = 0;
    if (z + b->z1 >= d->nz) z = 0;
    if (x != 0 || y != 0 || z != 0) {
        e = D_00F9B540->e;
        for (i = 0; i < D_00F9B540->u.c.n; i++, e++) {
            e->x += (u8)x;
            e->y += (u8)y;
            e->z += (u8)z;
        }
        return 1;
    }
    return 0;
}
