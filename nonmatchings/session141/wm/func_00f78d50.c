/* func_00f78d50: score 71, 126 words differ. original leaves soft-double libcall delay slots empty; global stores scheduled differently; all flag modes tried */
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
} Hdr;

typedef struct {
    void (*f0)(void);
    void (*f4)(void);
    void (*f8)(void *, s32, s32);
} Mode;

extern s32 D_00FB5BB0;
extern s32 D_00FB5EC4;
extern s32 D_0108F914;
extern s32 D_00FB6164;
extern s32 D_0108FA80;
extern s32 D_0108FA84;
extern s32 D_00FB5EC8;
extern s32 D_0108F910;
extern s32 D_00FB610C;
extern s32 D_0108F730[2];
extern s32 D_00FB5EC0;
extern Hdr D_0108F6B8;
extern f32 D_0108F7C0[27];
extern f32 D_0108F830[27];
extern f32 D_0108F8A0[27];
extern f32 D_00FB5BBC;
extern f32 D_00FB5BC0;
extern f32 D_00FB5BC4;
extern f32 D_0108F918[6][4];
extern s32 D_00FB5EAC;
extern Mode *D_00FB5EA8;
extern s32 D_0108F6B4;
void func_001fd720(void);
void func_00f206d8(s32, s32, s32);
s32 func_0024b778(s32);
Mode *func_0024b7a0(s32, s32, s32);
void func_00f7da90(void);
void func_00f78bc0(void);

void func_00f78d50(s32 arg) {
    s32 i;
    s32 j;
    s32 k;
    double a;
    f32 *p;
    f32 v;

    D_00FB5BB0 = 1;
    D_00FB5EC4 = 0;
    D_0108F914 = 0;
    D_00FB6164 = 0;
    D_0108FA80 = 0;
    D_0108FA84 = 0;
    D_00FB5EC8 = 0;
    D_0108F910 = 0;
    func_001fd720();
    func_00f206d8(0, 0, 0);
    D_00FB610C = -1;
    D_0108F730[1] = 1;
    D_00FB5EC0 = 0;
    D_0108F6B8.x8 = 0;
    D_0108F6B8.x0 = 0;
    D_0108F6B8.x4 = 0;
    D_0108F730[0] = 1;
    for (i = 0; i < 27; i++) {
        D_0108F7C0[i] = D_00FB5BBC;
        D_0108F830[i] = D_00FB5BC0;
        D_0108F8A0[i] = D_00FB5BC4;
    }
    for (i = 0; i < 6; i++) {
        a = i * 2.0f * 3.14159 / 6.0;
        p = D_0108F918[i];
        for (j = 0; j < 4; j++, p++) {
            v = j * 2.0f * 3.141592f / 6.0f + a;
            *p = v;
            if (v > 6.283184f) {
                *p = v - 6.283184f;
            }
        }
    }
    D_00FB5EAC = 0;
    k = func_0024b778(3);
    D_00FB5EA8 = func_0024b7a0(3, arg, 0);
    D_00FB5EA8->f8(func_00f7da90, 1, 1);
    D_00FB5EA8->f8(func_00f78bc0, 1, 2);
    D_0108F6B4 = arg + k;
}
