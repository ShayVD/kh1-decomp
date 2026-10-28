/* 2 words left: prologue order sll s2 vs sd ra; tried 6 variants (a-f) */
typedef struct { s32 a; u16 h; u16 pad; s32 c; } N2c910;
typedef struct { u8 pad[16]; f32 v10[4]; u8 pad20[12]; f32 f2c; u8 pad30[4]; N2c910 ent[1]; } D2c910;
extern D2c910 D_00F85240;
extern f32 D_00F8C240[4][4];
extern s32 D_00FBDA70;
void func_001bb658(s32);
void func_001bbf38(f32 (*)[4], N2c910 *);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0CopyVector(f32 *, f32 *);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void sceVu0RotMatrixY(f32 (*)[4], f32 (*)[4], f32);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

void func_00f2c910(f32 (*m)[4], s32 idx) {
    f32 t[4][4];
    func_001bb658(D_00F85240.ent[idx].h - 1);
    if (idx == -1) {
        sceVu0UnitMatrix(m);
        sceVu0CopyMatrix(m, D_00F8C240);
        return;
    }
    if (idx == -2) {
        sceVu0UnitMatrix(m);
        sceVu0CopyMatrix(m, D_00F8C240);
        m[3][0] = D_00F8C240[3][0];
        m[3][1] = D_00F8C240[3][1];
        m[3][2] = D_00F8C240[3][2] - D_00F85240.f2c;
        return;
    }
    if (idx == -3) {
        func_001bbf38(t, &D_00F85240.ent[D_00FBDA70]);
        sceVu0UnitMatrix(m);
        sceVu0CopyVector(m[3], t[3]);
        sceVu0TransMatrix(m, m, D_00F85240.v10);
        sceVu0UnitMatrix(t);
        sceVu0RotMatrixY(t, t, 3.1415927f);
        sceVu0MulMatrix(m, t, m);
        sceVu0MulMatrix(m, D_00F8C240, m);
        return;
    }
    sceVu0UnitMatrix(t);
    sceVu0RotMatrixY(t, t, 3.1415927f);
    func_001bbf38(m, &D_00F85240.ent[idx]);
    sceVu0TransMatrix(m, m, D_00F85240.v10);
    sceVu0MulMatrix(m, t, m);
    sceVu0MulMatrix(m, D_00F8C240, m);
}
