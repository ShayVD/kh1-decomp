/* Round 41 wwm2: score 188 -> 162. The second UV word is written with its v (<< 16) half first. Found by r41/orsweep.py, which tries every order of the | terms in each packed GS word line; no other single line helps. */
/* Round 36 (wwm2): wm.x func_00f5f940 near miss: score 205 -> 188 (214 -> 217 words, 928 vs 944); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, 120 s, seed 363). Earlier header below. */
/* 214 words (round 13): 8 RotTransPers corners plus a sprite packet per corner, same family as func_00f53758. Helps: r = out set before the calls (loop pointer s6 = sp16), *q++ for the call outputs, D_00FA6000 as a 20-byte struct array (gives the four separate field pointers). Left: the target hoists the 0x100000000 constant into s7 at entry and the 5 constant after the calls; we do the opposite. A u64 z local for the constant made it worse (221). The frame is 256 vs 240. */
typedef struct { u8 pad[8704]; u64 tex[1]; } G5f940;
extern G5f940 *D_00F9B540;
typedef struct { s32 w0; s32 w1; s32 w2; s32 w3; s32 w4; } E5f940;
extern E5f940 D_00FA6000[];
void sceVu0RotTransPers(s32 *, f32 (*)[4], f32 *, s32);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);

u64 *func_00f5f940(f32 *a, f32 *b, u64 c, s32 idx, f32 (*mat)[4], u64 *p) {
    f32 v[4];
    s32 out[8][4];
    s32 (*q)[4];
    s32 (*r)[4];
    s32 i;
    s32 x;
    s32 y;

    v[3] = 1.0f;
    r = out;
    q = out;
    v[0] = a[0];
    v[1] = a[1];
    v[2] = a[2];
    sceVu0RotTransPers(*q++, mat, v, 0);
    v[2] = a[2];
    v[0] = b[0];
    sceVu0RotTransPers(*q++, mat, v, 0);
    v[0] = a[0];
    v[2] = b[2];
    sceVu0RotTransPers(*q++, mat, v, 0);
    v[0] = b[0];
    v[2] = b[2];
    sceVu0RotTransPers(*q++, mat, v, 0);
    v[0] = a[0];
    v[1] = b[1];
    v[2] = a[2];
    sceVu0RotTransPers(*q++, mat, v, 0);
    v[0] = b[0];
    v[2] = a[2];
    sceVu0RotTransPers(*q++, mat, v, 0);
    v[0] = a[0];
    v[2] = b[2];
    sceVu0RotTransPers(*q++, mat, v, 0);
    v[0] = b[0];
    v[2] = b[2];
    sceVu0RotTransPers(*q++, mat, v, 0);
    p = func_00f66b78(p);
    p[0] = 0;
    p[1] = 20;
    p += 2;
    func_00f66b90(p);
    for (i = 0; i < 8; i++, r++) {
        x = ((*r)[0] + 8) & ~15;
        y = ((*r)[1] + 8) & ~15;
        p = func_00f66b78(p);
        p[0] = D_00F9B540->tex[idx];
        p[1] = 6;
        p += 2;
        p[1] = 0;
        p[0] = 342;
        p += 2;
        y -= 48;
        p[1] = 1;
        p[0] = c;
        x -= 48;
        p += 2;
        p[0] = (u64)(D_00FA6000[idx].w1 << 4) | ((u64)(D_00FA6000[idx].w2 << 4) << 16);
        p[1] = 3;
        p += 2;
        p[1] = 5;
        p[0] = (u64)x | ((u64)y << 16) | 0x100000000LL;
        p += 2;
        p[0] = ((u64)(((D_00FA6000[idx].w2 + D_00FA6000[idx].w4) << 4) + 16) << 16) | (u64)(((D_00FA6000[idx].w1 + D_00FA6000[idx].w3) << 4) + 16);
        p[1] = 3;
        p += 2;
        p[1] = 5;
        p[0] = (u64)(x + 96) | ((u64)(y + 96) << 16) | 0x100000000LL;
        p += 2;
        func_00f66b90(p);
    }
    p = func_00f66b78(p);
    p[0] = 96;
    p[1] = 20;
    p += 2;
    func_00f66b90(p);
    return p;
}
