/* xs_dumbo.x func_00f22178: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[4]; s32 n; u8 pad8[0x38]; OvlVec col[3]; u64 tex; u64 prim; OvlVec uv[3]; } Tri;
typedef struct { u8 pad[0x18]; u64 tex; } Src;
void func_00f22178(Tri *t, Src *s, f32 a, f32 w, f32 h) {
    s32 i, j;
    f32 u0, u1, v0, v1;
    f32 dv = 1.0f / h;
    f32 al = a * 127.0f;

    u0 = 0.0f;
    v0 = dv;
    v1 = 0.0f;
    u1 = 1.0f / w;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 10; j++) {
            t[0].col[0][0] = 128.0f; t[0].col[0][1] = 128.0f; t[0].col[0][2] = 128.0f; t[0].col[0][3] = al;
            t[0].col[1][0] = 128.0f; t[0].col[1][1] = 128.0f; t[0].col[1][2] = 128.0f; t[0].col[1][3] = al;
            t[0].col[2][0] = 128.0f; t[0].col[2][1] = 128.0f; t[0].col[2][2] = 128.0f; t[0].col[2][3] = al;
            t[0].uv[0][0] = u0; t[0].uv[0][1] = v0; t[0].uv[0][2] = 1.0f; t[0].uv[0][3] = 0.0f;
            t[0].uv[1][0] = u1; t[0].uv[1][1] = v0; t[0].uv[1][2] = 1.0f; t[0].uv[1][3] = 0.0f;
            t[0].uv[2][0] = u0; t[0].uv[2][1] = v1; t[0].uv[2][2] = 1.0f; t[0].uv[2][3] = 0.0f;
            t[0].tex = s->tex;
            t[0].prim = 6;
            t[0].n = 3;
            t[1].col[0][0] = 128.0f; t[1].col[0][1] = 128.0f; t[1].col[0][2] = 128.0f; t[1].col[0][3] = al;
            t[1].col[1][0] = 128.0f; t[1].col[1][1] = 128.0f; t[1].col[1][2] = 128.0f; t[1].col[1][3] = al;
            t[1].col[2][0] = 128.0f; t[1].col[2][1] = 128.0f; t[1].col[2][2] = 128.0f; t[1].col[2][3] = al;
            t[1].uv[0][0] = u1; t[1].uv[0][1] = v1; t[1].uv[0][2] = 1.0f; t[1].uv[0][3] = 0.0f;
            t[1].uv[1][0] = u0; t[1].uv[1][1] = v1; t[1].uv[1][2] = 1.0f; t[1].uv[1][3] = 0.0f;
            t[1].uv[2][0] = u1; t[1].uv[2][1] = v0; t[1].uv[2][2] = 1.0f; t[1].uv[2][3] = 0.0f;
            t[1].tex = s->tex;
            t[1].prim = 6;
            t[1].n = 3;
            t += 2;
            u0 += 1.0f / w;
            u1 += 1.0f / w;
        }
        u0 = 0.0f;
        u1 = 1.0f / w;
        v1 -= dv;
        v0 -= dv;
    }
}
