/* wm.x func_00f676b8: matched by hand. */
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
    u8 *o;
    s32 i;
    V4 *dp;
    f32 *pu, *pv, *dd;

    tex = base;
    o = tex;
    tex += 208;
    d.col = (f32 *)tex;
    tex = base + 480;
    if (src != NULL) {
        d.uv = tex;
        tex = base + 752;
        pu = &src[1].u;
        pv = &src[1].v;
        dd = (f32 *)(base + 500);
        i = 0;
    loop:
        dd[-1] = *(f32 *)((u8 *)pu + (i << 3));
        dd[0] = *(f32 *)((u8 *)pv + (i << 3));
        i++;
        dd += 4;
        if (i < 4) goto loop;
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
    func_00f651d0(arg, o, tex, &d, a4, &m, a5);
}
