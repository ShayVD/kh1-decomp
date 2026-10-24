#include "common.h"

typedef struct { u8 pad[0x40]; s32 h; s32 pad44; s32 w; } Stat;
typedef struct { u8 pad[0x6C]; Stat *st; } Ent6C;
typedef struct { s32 type; Ent6C *e; } Obj4;
typedef struct { s32 pad[2]; s32 x; s32 y; } G4A20;
extern G4A20 D_00454A20;

s32 func_0023d490(Obj4 *a) {
    s32 r;
    if (a->type == 4) {
        s32 x = D_00454A20.x;
        s32 y = D_00454A20.y;
        r = 0;
        if (y >= 25) r = 1;
        if (x >= 4) r = 1;
        if (y >= 49) r = 2;
        if (x >= 7) r = 2;
        return r;
    }
    if (a->type == 3) return 2;
    {
        Stat *s = a->e->st;
        s32 h = s->h;
        s32 w;
        if (h >= 37) return 2;
        w = s->w;
        if (w >= 7) return 2;
        if (h >= 19) return 1;
        if (w >= 4) return 1;
        return 0;
    }
}

#include "data/data_0044.h"
