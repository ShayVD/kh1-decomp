/* func_00f74440: score 246, 249 words differ. structure right; original leaves delay slots of double libcalls (cmpdf2/subdf3/truncdfsf2) empty and has no f21/f22 spill; all flag modes tried (same issue as f78d50) */
typedef struct {
    u8 pad0[16];
    f32 min[4];
    f32 max[4];
    u8 pad30[48];
} Box;

extern s32 D_00FB4A58;
extern s32 D_00FB4A54;
extern s32 D_00FB4A70;
extern s32 D_0108F1BC;
extern s32 D_0108F1C0;
extern s32 D_0108F1C4;
extern s32 D_0108F1C8;
extern s32 D_0108F1D8;
extern s32 D_0108F1E0;
extern f32 D_0108F1E4;
extern f32 D_0108F1E8;
extern s32 D_0108F1F8;
extern s32 D_0108F1FC;
extern s32 D_0108F200;
Box *func_001bc4e0(void);
void func_00f60898(s32, s32, s32, s32, s32, void *, s32, f32);
void func_00f606a0(s32, s32, s32, s32, s32, void *, s32, f32);

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define DABS(x) ((x) < 0.0 ? 0.0 - (x) : (x))

void func_00f74440(void) {
    f32 m0[4][4] __attribute__((aligned(16)));
    f32 m1[4][4] __attribute__((aligned(16)));
    f32 rot[4] __attribute__((aligned(16)));
    f32 t[4] __attribute__((aligned(16)));
    s32 n;
    Box *b;
    f32 m;
    f32 s;
    double d;

    n = D_00FB4A58;
    rot[1] = 0.436332256f;
    rot[3] = 1.0f;
    rot[0] = 0.436332256f;
    rot[2] = 0.0f;
    PlatVu0UnitMatrix(m0);
    PlatVu0UnitMatrix(m1);
    if (D_00FB4A54) {
        n = 0;
    }
    b = func_001bc4e0() + n;
    if (D_0108F1BC == 4) {
        t[0] = 0.0f;
        t[1] = 0.0f;
        t[2] = 0.0f;
    } else {
        t[0] = -((b->max[0] - b->min[0]) * 0.5f + b->min[0]);
        t[1] = (b->max[1] - b->min[1]) * 0.5f + b->min[1];
        t[2] = -((b->max[2] - b->min[2]) * 0.5f + b->min[2]);
    }
    t[3] = 1.0f;
    PlatVu0TransMatrix(m1, m1, t);
    d = b->max[0] - b->min[0];
    m = DABS(d);
    d = b->max[1] - b->min[1];
    m = MAX(m, DABS(d));
    d = b->max[2] - b->min[2];
    m = MAX(m, DABS(d));
    if (m == 0.0f) {
        m = 1.0f;
    }
    s = (f32)D_0108F1D8 / m;
    if (D_0108F1BC == 4) {
        s = 0.46f;
    }
    m0[2][2] = s;
    m0[0][0] = s;
    m0[1][1] = s;
    PlatVu0MulMatrix(m0, m0, m1);
    PlatVu0RotMatrix(m0, m0, rot);
    if (D_0108F1E4 != D_0108F1E8) {
        if (D_0108F1E8 < D_0108F1E4) {
            D_0108F1E4 = D_0108F1E4 - 128.0f / (f32)D_00FB4A70;
            if (D_0108F1E4 < D_0108F1E8) {
                D_0108F1E4 = D_0108F1E8;
            }
        } else {
            D_0108F1E4 = D_0108F1E4 + 128.0f / (f32)D_00FB4A70;
            if (D_0108F1E8 < D_0108F1E4) {
                D_0108F1E4 = D_0108F1E8;
            }
        }
    }
    if (D_0108F1BC != 4) {
        func_00f60898(D_0108F1BC, D_0108F1C4, D_0108F1C8, n, 0, m0,
                      (f32)D_0108F1E0 * D_0108F1E4 * (1.0f / 128.0f), 0.5f);
    } else {
        func_00f606a0(4, D_0108F1FC, D_0108F200, D_0108F1F8, 0, m0,
                      (f32)D_0108F1E0 * D_0108F1E4 * (1.0f / 128.0f), 1.0f);
        D_0108F1C0 = 1;
    }
}
