/* gb.x func_00f32668: matched by hand. */
#include "ovl.h"

typedef struct { u64 tex; u16 u; u16 v; u16 w; u16 h; } Spr;
typedef struct { u8 pad[0x2FC]; u16 u; u8 pad2fe[2]; u16 v; } Tbl;
typedef struct { u8 pad[0x2330]; u64 tex; } World;
extern World *D_00F56DC0;
extern u8 D_00F61570[];
extern Tbl D_00F61880;

void func_00f32668(s32 i, Spr *s) {
    u64 tex; s32 u, v, k; k = D_00F61570[i]; tex = D_00F56DC0->tex; v = D_00F61880.v; u = D_00F61880.u; s->w = 32; s->tex = tex; s->u = u + k * 32; s->v = v; s->h = 32;
}
