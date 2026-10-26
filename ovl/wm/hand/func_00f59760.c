/* wm.x func_00f59760: the twin of gb.x func_00f32668 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u64 tex; u16 u; u16 v; u16 w; u16 h; } Spr;
typedef struct { u8 pad[0x2FC]; u16 u; u8 pad2fe[2]; u16 v; } Tbl;
typedef struct { u8 pad[0x2330]; u64 tex; } World;
extern World *D_00F9B540;
extern u8 D_00FA5CF0[];
extern Tbl D_00FA6000;

void func_00f59760(s32 i, Spr *s) {
    u64 tex; s32 u, v, k; k = D_00FA5CF0[i]; tex = D_00F9B540->tex; v = D_00FA6000.v; u = D_00FA6000.u; s->w = 32; s->tex = tex; s->u = u + k * 32; s->v = v; s->h = 32;
}
