/* 83 words / score 86 (456 vs 472 bytes). Same family and same blocker as f36ee0: the original copies w into t3 after the calls (move t3,s2), and col into t2, then reuses t2 for buf. Ours keeps w in s1 and swaps the s1/s2 roles of w and ci. Tried a local copy of w, an inline colour helper, and an inline draw helper that takes c0/c1/uv pointers (worse). */
#include "ovl.h"

typedef struct {
    u8 pad0[0x10];
    OvlVec c0;
    OvlVec c1;
} GbCol;
typedef struct {
    u8 pad0[0x1F0];
    OvlVec uv[4];
} GbWork;
typedef struct {
    s32 mode;
    s32 b;
    s32 c;
} GbMode;
typedef struct {
    GbCol *col;
    s32 x4;
    void *tex;
    s32 xc;
    OvlVec pad;
} GbArgs;
s32 func_00f23860(s32);
s32 func_00f23908(s32);
void func_00f3e388(s32, GbWork *, void *, GbArgs *, s32, s32, GbMode *, f32);
extern u8 D_00379F28[];
extern u8 D_0037A028[];
extern f32 *D_00F813CC[];

void func_00f37270(s32 x, GbWork *w, s32 id, s32 id2, s32 ci, f32 f) {
    GbMode m;
    GbArgs a;
    void *buf;
    f32 *uv;
    s32 i;
    s32 r = func_00f23860(id - 1);
    s32 r2;
    if (id2 > 0)
        r2 = func_00f23908(id2 - 1);
    else
        r2 = 0;
    a.col = (GbCol *)((u8 *)w + 0xD0);
    buf = (u8 *)w + 0x1E0;
    a.col->c0[0] = D_00379F28[ci * 4];
    a.col->c0[1] = D_00379F28[ci * 4 + 1];
    a.col->c0[2] = D_00379F28[ci * 4 + 2];
    a.col->c0[3] = 128.0f;
    a.col->c1[0] = D_0037A028[ci * 4];
    a.col->c1[1] = D_0037A028[ci * 4 + 1];
    a.col->c1[2] = D_0037A028[ci * 4 + 2];
    a.col->c1[3] = 128.0f;
    uv = D_00F813CC[id];
    if (uv != NULL) {
        a.tex = buf;
        buf = (u8 *)w + 0x2F0;
        for (i = 0; i < 4; i++) {
            w->uv[i][0] = uv[i * 2 + 2];
            w->uv[i][1] = uv[i * 2 + 3];
        }
        a.x4 = 0;
    } else {
        a.x4 = 0;
        a.tex = NULL;
    }
    m.mode = 5;
    m.b = 1;
    m.c = 1;
    func_00f3e388(x, w, buf, &a, r, r2, &m, f);
}
