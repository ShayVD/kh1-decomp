/* 71 words / score 91: logic right. The original keeps every memory access in source order (col copy, t[3]=1, header sds, and in the loop each ld/sd pair interleaved); this draft lets the scheduler hoist the header stores and group the loads. Tried nostrict, a struct copy of col, indexed and *p++ headers, u64 copies through a union. */
typedef union { s32 i[4]; f32 f[4]; u64 d[2]; } GbV;
typedef struct { f32 s, t, q; s32 pad; GbV rgba; GbV xyz; } GbStq;
void sceVu0ApplyMatrix(f32 *, OvlMtx, f32 *);
void sceVu0ScaleVectorXYZ(f32 *, f32 *, f32);
void sceVu0FTOI4Vector(s32 *, f32 *);

u64 *func_00f37618(u64 *p, f32 (*v)[4], f32 (*uv)[4], u64 prim, s32 *col, OvlMtx m) {
    GbV t;
    GbV c;
    GbStq *o;
    s32 i;
    f32 q;
    c.i[0] = col[0];
    c.i[1] = col[1];
    c.i[2] = col[2];
    c.i[3] = col[3];
    t.f[3] = 1.0f;
    p[0] = 0x1000000000008001ULL;
    p[1] = 14;
    p += 2;
    p[0] = prim;
    p[1] = 6;
    p += 2;
    p[0] = 0xC02A400000008001ULL;
    p[1] = 0xE412412412412ULL;
    p += 2;
    for (i = 0; i < 4; i++) {
        sceVu0ApplyMatrix(t.f, m, v[i]);
        q = 1.0f / t.f[3];
        sceVu0ScaleVectorXYZ(t.f, t.f, q);
        sceVu0FTOI4Vector(t.i, t.f);
        ((f32 *)p)[0] = uv[i][0] * q;
        ((f32 *)p)[2] = q;
        ((f32 *)p)[1] = uv[i][1] * q;
        p[2] = c.d[0];
        p[3] = c.d[1];
        p[4] = t.d[0];
        p[5] = t.d[1];
        ((s32 *)p)[11] = 16;
        p += 6;
    }
    return p;
}
