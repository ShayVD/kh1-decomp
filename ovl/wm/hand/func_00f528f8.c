/* wm.x func_00f528f8: matched by hand. */
#include "ovl.h"

typedef struct {
    s32 r, g, b, a;
} __attribute__((aligned(16))) Col;

typedef struct {
    u8 pad0[0x88];
    f32 x88;
    u8 pad8C[0x2328 - 0x8C];
    u64 tex;
} World;

typedef struct {
    u8 pad0[0x2E4];
    s16 idx;
    s16 pad2E6;
    s32 u;
    s32 v;
    s32 w;
    s32 h;
} Tbl;

typedef struct {
    s32 w;
    s32 h;
    s32 pad[2];
} TexSize;

extern World *D_00F9B540;
extern f32 D_00FA5AF8;
extern Col D_00FB7810;
extern Tbl D_00FA6000;
extern TexSize D_00FA6310[];
void func_00f5e710(s32, OvlVec *, OvlVec *, u64, Col *, s32);

void func_00f528f8(s32 arg0, s32 arg1) {
    OvlVec pos[4];
    OvlVec uv[4];
    Col col;
    f32 s;
    f32 u0, v0, u1, v1;
    f32 tw, th;
    s32 c;
    s32 i;

    s = D_00F9B540->x88 / -4624.0f * 200.0f * 0.5f;
    col = D_00FB7810;
    c = D_00FA5AF8 * 128.0f;
    col.a = 128;
    col.r = c;
    col.g = c;
    col.b = c;
    for (i = 0; i < 4; i++) {
        pos[i][1] = 0.0f;
        pos[i][3] = 1.0f;
    }
    tw = D_00FA6310[D_00FA6000.idx].w;
    th = D_00FA6310[D_00FA6000.idx].h;
    u0 = (f32)D_00FA6000.u / tw;
    v0 = (f32)D_00FA6000.v / th;
    u1 = (f32)D_00FA6000.w / tw + u0;
    v1 = (f32)D_00FA6000.h / th + v0;
    pos[0][0] = -s;
    pos[0][2] = s;
    pos[1][0] = s;
    pos[1][2] = s;
    pos[2][0] = -s;
    pos[2][2] = -s;
    pos[3][0] = s;
    pos[3][2] = -s;
    uv[0][0] = u0;
    uv[0][1] = v0;
    uv[1][0] = u1;
    uv[1][1] = v0;
    uv[2][0] = u0;
    uv[2][1] = v1;
    uv[3][0] = u1;
    uv[3][1] = v1;
    func_00f5e710(arg1, pos, uv, D_00F9B540->tex, &col, arg0);
}
