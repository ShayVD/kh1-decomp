/* score 49 (1324 vs 1328, the 4 is end padding). Box vs sphere test: 8 corners through func_00f3caf0, then point in box space via transposed matrix with m[3] cleared, four box tests (plain, x/y/z widened by r). Unused f32 u[4] gives the frame (122 -> 76); v[0],v[1],v[2],v[3] order. Left: corner checks 2-8 use bnezl where orig has bnez + li v0,1 in the delay slot, and arg setup order. Tried ret variable, inline helper. Round 26 wwm2. Round 17 (wwm1): a CONTEXT_ONLY func_00f3caf0 above it (s32 (f32 *, f32 *, f32, f32), as matched) fixes the bnezl / bnez + li v0,1 slots (24 -> 17). Left: in each corner call the target sets f12 = r before a1 = v. */
CONTEXT_ONLY s32 func_00f3caf0(f32 * a0, f32 * a1, f32 a2, f32 a3) { return 0; }
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0TransposeMatrix(f32 (*)[4], f32 (*)[4]);

s32 func_00f3cdd0(f32 *p, f32 *c, f32 *a, f32 *b, f32 (*mtx)[4], f32 r)
{
    f32 m[4][4];
    f32 v[4];
    f32 u[4];

    v[0] = c[0] + a[0];
    v[3] = 1.0f;
    v[1] = c[1] + a[1];
    v[2] = c[2] + a[2];
    if (func_00f3caf0(p, v, r, 0.0f)) return 1;
    v[0] = c[0] - b[0];
    v[1] = c[1] + a[1];
    v[2] = c[2] + a[2];
    if (func_00f3caf0(p, v, r, 0.0f)) return 1;
    v[0] = c[0] + a[0];
    v[1] = c[1] - b[1];
    v[2] = c[2] + a[2];
    if (func_00f3caf0(p, v, r, 0.0f)) return 1;
    v[0] = c[0] - b[0];
    v[1] = c[1] - b[1];
    v[2] = c[2] + a[2];
    if (func_00f3caf0(p, v, r, 0.0f)) return 1;
    v[0] = c[0] + a[0];
    v[1] = c[1] + a[1];
    v[2] = c[2] - b[2];
    if (func_00f3caf0(p, v, r, 0.0f)) return 1;
    v[0] = c[0] - b[0];
    v[1] = c[1] + a[1];
    v[2] = c[2] - b[2];
    if (func_00f3caf0(p, v, r, 0.0f)) return 1;
    v[0] = c[0] + a[0];
    v[1] = c[1] - b[1];
    v[2] = c[2] - b[2];
    if (func_00f3caf0(p, v, r, 0.0f)) return 1;
    v[0] = c[0] - b[0];
    v[1] = c[1] - b[1];
    v[2] = c[2] - b[2];
    if (func_00f3caf0(p, v, r, 0.0f)) return 1;
    sceVu0CopyMatrix(m, mtx);
    m[3][2] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    sceVu0TransposeMatrix(m, m);
    v[0] = p[0] - c[0];
    v[1] = p[1] - c[1];
    v[2] = p[2] - c[2];
    v[3] = 1.0f;
    sceVu0ApplyMatrix(v, m, v);
    if (-b[0] < v[0] && v[0] < a[0] && -b[1] < v[1] && v[1] < a[1] && -b[2] < v[2] && v[2] < a[2]) return 1;
    if (-(b[0] + r) < v[0] && v[0] < a[0] + r && -b[1] < v[1] && v[1] < a[1] && -b[2] < v[2] && v[2] < a[2]) return 1;
    if (-b[0] < v[0] && v[0] < a[0] && -(b[1] + r) < v[1] && v[1] < a[1] + r && -b[2] < v[2] && v[2] < a[2]) return 1;
    if (-b[0] < v[0] && v[0] < a[0] && -b[1] < v[1] && v[1] < a[1] && -(b[2] + r) < v[2] && v[2] < a[2] + r) return 1;
    return 0;
}
