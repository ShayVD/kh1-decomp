/* 27 words left: s0/s1 swap of arg0/arg4; tried variants a-i */
extern s32 D_00F85098;
extern f32 D_00F8509C;
extern f32 D_00F86480[4][4];
extern f32 D_00F9A540[4][4];
void func_00f3b360(void);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);

void func_00f44158(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    f32 v[4];
    switch (arg4) {
    case 0:
    default:
        D_00F85098 = arg0;
        if (arg0 == 1) {
            v[0] = arg1 * 100.0f;
            v[1] = arg2 * 100.0f;
            v[2] = arg3 * 100.0f;
            v[3] = 1.0f;
            sceVu0UnitMatrix(D_00F86480);
            D_00F86480[0][0] = -1.0f;
            D_00F86480[2][2] = -1.0f;
            sceVu0TransMatrix(D_00F86480, D_00F86480, v);
            D_00F8509C = 1.0f;
        }
        break;
    case 1:
        func_00f3b360();
        if (arg0 == 1) {
            v[0] = arg1 * 100.0f;
            v[1] = arg2 * 100.0f;
            v[2] = arg3 * 100.0f;
            v[3] = 1.0f;
            sceVu0UnitMatrix(D_00F9A540);
            D_00F9A540[1][1] = -1.0f;
            D_00F9A540[2][2] = -1.0f;
            sceVu0TransMatrix(D_00F9A540, D_00F9A540, v);
        }
        break;
    }
}
