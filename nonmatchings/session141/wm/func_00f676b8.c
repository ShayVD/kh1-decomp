/* score 60 (90 words; 368 vs 392 bytes). Same code as func_00f67530 (only the callee and t1/t2 order differ), so one match gives both. Rest is close; the uv copy loop is the problem: the original keeps i (slti 4), reduces only the dst giv (base+500, -4/0) and computes src+8/src+12 + (i<<3) each pass; every spelling here (struct/array/byte-offset/inline helper, u32/s16/s64 i, do-while) gets reversed and fully reduced. All modes tried. */
#include "ovl.h"

typedef struct {
    f32 *col;
    s32 zero;
    u8 *uv;
} Desc;

typedef struct {
    f32 u, v;
} UV;

typedef struct {
    f32 x, y, z, w;
} V4;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Mode;

extern u8 D_00379F28[];
extern u8 D_0037A028[];
void func_00f651d0(s32, u8 *, u8 *, Desc *, s32, Mode *, s32);


void func_00f676b8(s32 flag, s32 arg, u8 *base, s32 idx, s32 a4, s32 a5, UV *src) {
    Mode m;
    Desc d;
    u8 *tex;
    s32 i;

    d.col = (f32 *)(base + 208);
    tex = base + 480;
    if (src != NULL) {
        d.uv = tex;
        tex = base + 752;
        for (i = 0; i < 4; i++) {
            ((V4 *)(base + 496))[i].x = src[i + 1].u;
            ((V4 *)(base + 496))[i].y = src[i + 1].v;
        }
        d.zero = 0;
    } else {
        d.zero = 0;
        d.uv = NULL;
    }
    d.col[4] = D_00379F28[idx * 4 + 0];
    d.col[5] = D_00379F28[idx * 4 + 1];
    d.col[6] = D_00379F28[idx * 4 + 2];
    d.col[7] = 128.0f;
    d.col[8] = D_0037A028[idx * 4 + 0];
    d.col[9] = D_0037A028[idx * 4 + 1];
    d.col[10] = D_0037A028[idx * 4 + 2];
    d.col[11] = 128.0f;
    if (flag != 0) {
        m.a = 4;
        m.b = 0;
        m.c = 0;
    } else {
        m.a = 5;
        m.b = 1;
        m.c = 1;
    }
    func_00f651d0(arg, base, tex, &d, a4, &m, a5);
}
