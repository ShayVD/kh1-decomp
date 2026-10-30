/* 17 words / score 28 (472 = 472); was 83/86. Copy-family pattern from f40438: tex = base; o = tex; c = (f32 *)(o + 208); d.col = c; tex = o + 480; colours through c; Desc padded to 32 bytes (frame 112); the uv copy is a plain pointer loop (ps = src + 3; dd = o + 500; dd[-1] = ps[-1]; dd[0] = ps[0]) because the original strength-reduces it. Left: the original also copies c into tex (t2 = a0) before storing d.col and keeps o (t3) for the 752/500 offsets; every form that adds that copy (tex = (u8 *)c; d.col = (f32 *)tex) swaps s1/s2 and adds a second copy (score 86-90). Hill-climb of the head block: no gain. Round 15 (wwm1): func_00f3e388 returns MdlWork * (ovl/gb/hand/func_00f3e388.c); declaring it as returning a pointer takes this from 17 to 14 words. */
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
extern f32 *D_00F813CC[];
s32 func_00f23860(s32);
s32 func_00f23908(s32);
void *func_00f3e388(s32, u8 *, u8 *, Desc *, s32, s32, Mode *, f32);

void func_00f37270(s32 arg, u8 *base, s32 id, s32 id2, s32 idx, f32 f) {
    Mode m;
    Desc d;
    u8 *tex;
    u8 *o;
    s32 i;
    f32 *src;
    f32 *c;
    f32 *ps, *dd;
    s32 r = func_00f23860(id - 1);
    s32 r2;
    if (id2 > 0)
        r2 = func_00f23908(id2 - 1);
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
    src = D_00F813CC[id];
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
    func_00f3e388(arg, o, tex, &d, r, r2, &m, f);
}
