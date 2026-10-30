/* 2 words left (was 16): func_001c0310 returns s32 (16 -> 12), then hill.py on the k-> store order (12 -> 2). Left: `sw s3,0(v0)` (k->x00 = arg0) is scheduled before the x40 swc1 in the target, after it here. Tried the exact target store order (16), two more hill seeds, 10 min permuter. */
typedef struct { u8 pad[0x1C]; s32 a; s32 b; s32 c; } S38630;
typedef struct {
    s32 x00; s32 x04; s32 x08; s32 x0c; s32 x10; s32 x14; s32 x18; s32 pad1c;
    s32 x20; s32 x24; s32 pad28[2]; f32 x30; s32 x34; s32 x38; f32 x3c;
    f32 x40; s32 x44; s32 x48; f32 x4c; f32 x50; s32 x54; s32 pad58[2];
    f32 m[4][4];
} K38630;
extern s32 D_00F87058;
void func_00f37ea0(s32, f32 (*)[4]);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0RotMatrixY(f32 (*)[4], f32 (*)[4], f32);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
s32 func_00f68770(s32, s32, f32 (*)[4], s32, s32);
s32 func_00f36380(void);
K38630 *func_00f363c0(s32);
s32 func_001c0310(s32, void (*)(s32), s32);
void func_00f380b0(s32);

void func_00f38630(s32 arg0, S38630 *arg1) {
    f32 m0[4][4];
    f32 m1[4][4];
    f32 m2[4][4];
    s32 h;
    K38630 *k;
    func_00f37ea0(0, m0);
    sceVu0UnitMatrix(m2);
    sceVu0RotMatrixY(m2, m2, 1.5707963f);
    sceVu0MulMatrix(m1, m0, m2);
    func_00f68770(15, 1, m1, 0, D_00F87058);
    sceVu0UnitMatrix(m1);
    sceVu0MulMatrix(m1, m0, m1);
    sceVu0MulMatrix(m1, m1, m2);
    h = func_00f36380();
    k = func_00f363c0(h);
    k->x14 = arg1->a;
    k->x50 = 200.0f;
    k->x10 = arg1->b;
    k->x18 = arg1->c;
    k->x08 = 4;
    k->x20 = 1;
    k->x04 = 0;
    k->x0c = 0;
    k->x3c = 1.0f;
    k->x24 = 2;
    k->x00 = arg0;
    k->x34 = 0;
    k->x40 = 200.0f;
    k->x38 = 0;
    k->x30 = -200.0f;
    k->x4c = 1.0f;
    k->x54 = 3;
    k->x44 = 0;
    k->x48 = 0;
    sceVu0CopyMatrix(k->m, m1);
    func_001c0310(11, func_00f380b0, h);
}
