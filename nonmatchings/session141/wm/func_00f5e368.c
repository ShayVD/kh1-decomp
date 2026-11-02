/* Round 41 wwm2: score 40 -> 26 (472 = 472). port.py of the gb twin func_00f37270 draft, which uses the copy family (tex = base; o = tex; c = o + 208; tex = o + 480). See that file for what is left. The earlier wm header was: 65 words, target copies the obj pointer into t3; that copy is what the port reproduces. */
typedef struct {
    f32 *col;
    s32 zero;
    u8 *uv;
    s32 xc;
    OvlVec pad;
} Desc;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Mode;

extern u8 D_00379F28[];
extern u8 D_0037A028[];
extern f32 *D_0108DB8C[];
s32 func_00f4a958(s32);
s32 func_00f4aa00(s32);
void *func_00f65480(s32, u8 *, u8 *, Desc *, s32, s32, Mode *, f32);

void *func_00f5e368(s32 arg, u8 *base, s32 id, s32 id2, s32 idx, f32 f) {
    Mode m;
    Desc d;
    u8 *tex;
    u8 *o;
    s32 i;
    f32 *src;
    f32 *c;
    f32 *ps, *dd;
    s32 r = func_00f4a958(id - 1);
    s32 r2;
    if (id2 > 0)
        r2 = func_00f4aa00(id2 - 1);
    else
        r2 = 0;
    tex = base;
    o = tex;
    c = (f32 *)(o + 208);
    d.col = c;
    tex = o + 480;
    c[4] = D_00379F28[idx * 4 + 0];
    c[5] = D_00379F28[idx * 4 + 1];
    c[6] = D_00379F28[idx * 4 + 2];
    c[7] = 128.0f;
    c[8] = D_0037A028[idx * 4 + 0];
    c[9] = D_0037A028[idx * 4 + 1];
    c[10] = D_0037A028[idx * 4 + 2];
    c[11] = 128.0f;
    src = D_0108DB8C[id];
    if (src != NULL) {
        d.uv = tex;
        tex = o + 752;
        ps = src + 3;
        dd = (f32 *)(o + 500);
        for (i = 0; i < 4; i++) {
            dd[-1] = ps[-1];
            dd[0] = ps[0];
            ps += 2;
            dd += 4;
        }
        d.zero = 0;
    } else {
        d.zero = 0;
        d.uv = NULL;
    }
    m.a = 5;
    m.b = 1;
    m.c = 1;
    return func_00f65480(arg, o, tex, &d, r, r2, &m, f);
}
