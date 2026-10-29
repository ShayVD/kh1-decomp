/* 54 words (score 81, 404 vs 408). GS STQ/RGBAQ/XYZ2 strip; target copies color/xyz with in-order ld/sd (looks like movstr block move), mine get scheduled. Tried u64 copies, struct copies, nostrict. */
typedef struct { f32 c[4]; } __attribute__((aligned(8))) Col5e710;
typedef struct { f32 s, t, q, pad; Col5e710 rgba; Col5e710 xyz; } Ent5e710;
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);
void sceVu0ScaleVectorXYZ(f32 *, f32 *, f32);
void sceVu0FTOI4Vector(s32 *, f32 *);

u64 *func_00f5e710(u64 *p, f32 (*vtx)[4], f32 (*uv)[4], u64 tex0, s32 *col, f32 (*m)[4]) {
    f32 v[4] __attribute__((aligned(16)));
    Col5e710 c __attribute__((aligned(16)));
    Ent5e710 *e;
    f32 q;
    s32 i;

    ((s32 *)&c)[0] = col[0]; ((s32 *)&c)[1] = col[1]; ((s32 *)&c)[2] = col[2]; ((s32 *)&c)[3] = col[3];
    v[3] = 1.0f;
    p[0] = 0x1000000000008001;
    p[1] = 14;
    p += 2;
    p[0] = tex0;
    p[1] = 6;
    p += 2;
    p[0] = 0xC02A400000008001;
    p[1] = 0x000E412412412412;
    p += 2;
    for (i = 0; i < 4; i++) {
        sceVu0ApplyMatrix(v, m, vtx[i]);
        q = 1.0f / v[3];
        sceVu0ScaleVectorXYZ(v, v, q);
        sceVu0FTOI4Vector((s32 *)v, v);
        e = (Ent5e710 *)p;
        e->s = uv[i][0] * q;
        e->t = uv[i][1] * q;
        e->q = q;
        e->rgba = c;
        e->xyz = *(Col5e710 *)v;
        ((s32 *)&e->xyz)[3] = 16;
        p += 6;
    }
    return p;
}
