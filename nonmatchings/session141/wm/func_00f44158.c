/* 9 words left, score 16 (was 27/40). Round 30 (wgb): the v[] setup plus sceVu0UnitMatrix(m) as a static inline helper (27 -> 13 words), and an empty do { } while (0) before the switch (permuter find; it fixes the case-1 100.0f scheduling, 13 -> 9). Left: arg0 and arg4 swap s0/s1 (the target keeps arg4 in s1). Tried a local copy of arg4, (u32)/u32 arg4, arg0 == arg4 in case 1, default/case 0 order, case 1 first, if/else form, per-case inline helpers (worse), the barrier at every other line, CONTEXT_ONLY callees (ctx2), a 10-minute -j1 permuter run. Older notes: variants a-i. */
extern s32 D_00F85098;
extern f32 D_00F8509C;
extern f32 D_00F86480[4][4];
extern f32 D_00F9A540[4][4];
void func_00f3b360(void);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);

static inline void setv_44158(f32 *v, s32 x, s32 y, s32 z, f32 (*m)[4]) {
    v[0] = x * 100.0f;
    v[1] = y * 100.0f;
    v[2] = z * 100.0f;
    v[3] = 1.0f;
    sceVu0UnitMatrix(m);
}

void func_00f44158(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    f32 v[4];
    do {
    } while (0);
    switch (arg4) {
    case 0:
    default:
        D_00F85098 = arg0;
        if (arg0 == 1) {
            setv_44158(v, arg1, arg2, arg3, D_00F86480);
            D_00F86480[0][0] = -1.0f;
            D_00F86480[2][2] = -1.0f;
            sceVu0TransMatrix(D_00F86480, D_00F86480, v);
            D_00F8509C = 1.0f;
        }
        break;
    case 1:
        func_00f3b360();
        if (arg0 == 1) {
            setv_44158(v, arg1, arg2, arg3, D_00F9A540);
            D_00F9A540[1][1] = -1.0f;
            D_00F9A540[2][2] = -1.0f;
            sceVu0TransMatrix(D_00F9A540, D_00F9A540, v);
        }
        break;
    }
}
