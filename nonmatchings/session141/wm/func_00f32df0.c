/* score 89 (1140 vs 1152). Marker effect sprites: 7 K6/K8 keyframe tables copied from rodata (lwl/ldl copies), func_001befc8 alpha curves, func_00f32b00 sprites for D_00F9B330[5]/[7]/[8]. Separate field pointers pu/pv/pw/ph (292 -> 121) and the copy order a,b,c,d,e (-> 91) helped; *pt for D_00F87070[5] -> 89. Left: original derives the field pointers from the D_00F9B330 base (ours from &[5].u), b/d copy scheduling, t4 vs a1 for the alpha int. Tried pointer-from-struct (worse), u32 alpha, inline helper. Round 26 wwm2. */
typedef struct { s32 x0; s32 u; s32 v; s32 w; s32 h; } Spr;
typedef struct { f32 v[6]; } K6;
typedef struct { f32 v[8]; } K8;
extern K6 D_00FB6EC8;
extern K6 D_00FB6EE0;
extern K6 D_00FB6EF8;
extern K6 D_00FB6F10;
extern K8 D_00FB6F28;
extern K6 D_00FB6F48;
extern K6 D_00FB6F60;
extern u64 D_00F87070[];
extern Spr D_00F9B330[];
f32 func_001befc8(s32, void *);
u64 *func_00f32b00(u64 *, s32, u64, s32, s32, s32, s32, s32, f32, f32, s32);

u64 *func_00f32df0(u64 *p, s32 x, s32 y, s32 k)
{
    K6 a;
    K6 b;
    K6 c;
    K6 d;
    K8 e;
    K6 f;
    K6 g;
    s32 col;
    f32 t;
    u64 *pt;
    s32 *pu, *pv, *pw, *ph;

    a = D_00FB6EC8;
    b = D_00FB6EE0;
    c = D_00FB6EF8;
    d = D_00FB6F10;
    e = D_00FB6F28;
    f = D_00FB6F48;
    g = D_00FB6F60;
    if (k >= 7) {
        pt = &D_00F87070[5];
        pu = &D_00F9B330[5].u;
        pv = &D_00F9B330[5].v;
        pw = &D_00F9B330[5].w;
        ph = &D_00F9B330[5].h;
        p = func_00f32b00(p, ((s32)(func_001befc8(k, &a) * 128.0f) << 24) | 0x808080, *pt, x, y,
                          *pw - 1, *ph - 1, *pu + 1, 0.0f, 1.0f, *pv + 1);
        p = func_00f32b00(p, ((s32)(func_001befc8(k, &b) * 128.0f) << 24) | 0x808080, *pt, x, y,
                          *pw - 1, *ph - 1, *pu + 1, 0.0f, 1.0f, *pv + 1);
    }
    if (k < 12) {
        col = ((s32)(func_001befc8(k, &e) * 128.0f) << 24) | 0x808080;
        t = func_001befc8(k, &c);
        p = func_00f32b00(p, col, D_00F87070[7], x, y, D_00F9B330[7].w, D_00F9B330[7].h, D_00F9B330[7].u,
                          func_001befc8(k, &d), t, D_00F9B330[7].v);
    }
    if ((u32)(k - 5) < 7) {
        col = ((s32)(func_001befc8(k, &g) * 128.0f) << 24) | 0x808080;
        p = func_00f32b00(p, col, D_00F87070[8], x, y, D_00F9B330[8].w, D_00F9B330[8].h, D_00F9B330[8].u,
                          0.0f, func_001befc8(k, &f), D_00F9B330[8].v);
    }
    return p;
}
