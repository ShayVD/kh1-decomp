/* score 26 (1368 bytes, same size). World-map cutscene: effect 21 at the player, fade out 20 frames, camera flight pos[2] += 200 for 60 frames under func_001c0310(func_00f421d8), then reset and effect 22 with fade in. Floats need 1.59999996f/0.59999997f/-0.54999997f (gcc 2.96 truncates shorter literals). Keys: an early b = (u8 *)D_00F86500 and off = k * 0x590 with e = off + 0x540 + b and b += 0x80 for the matrix (32); hill2 on the init stores took it to 26. Left: off/b get s1/s2 swapped and the 1.0/1.6 store schedule. Round 27 wwm2. */
typedef struct { s32 a; s32 b; s32 c; } Sub;
typedef struct { u8 pad[0x80]; OvlMtx m; u8 b[0x400]; u8 c[0x80]; Sub s; u8 pad2[0x590 - 0x54C]; } Ent;
extern Ent D_00F86500[];
extern Ent *D_00F864C0;
extern f32 D_00F850C8;
extern s32 D_00F850E0;
extern f32 D_00F85268;
extern s32 D_00F87048;
extern s32 D_00F9B1C4;
extern s32 D_00F9B1C8;
extern s32 D_00F9B1CC;
extern s32 D_010807E0;
extern s32 D_010807E4;
extern char D_00FB7260[];
extern char D_00FB7278[];
extern OvlMtx D_00F85200;
void sceVu0UnitMatrix(OvlMtx);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0RotMatrixY(OvlMtx, OvlMtx, f32);
void func_00106978(s32);
void func_00106a58(s32);
void func_0011d1e0(s32, s32, f32 *, s32);
void func_001bb7c8(char *, s32);
void func_001bf048(OvlMtx, OvlMtx);
void func_001bfac8(void);
s32 func_001bff70(s32);
s32 func_001c0310(s32, void (*)(void), ...);
void func_00f29810(s32, u8 *, u8 *);
void func_00f2c7e8(f32);
void func_00f309d0(s32);
void func_00f32318(f32 *, f32 *, f32);
void func_00f344e0(s32);
void func_00f3a4c8(void);
void func_00f3e3a0(void);
void func_00f404c8(s32, s32);
void func_00f40b38(f32);
void func_00f421a8(void);
void func_00f421d8(void);
void func_00f64b88(s32);
void func_00f65a68(s32);
s32 func_00f68508(s32, s32, f32 *, f32 *, f32 *, s32);
void func_00f68a40(s32);

void func_00f422c0(void)
{
    f32 pos[4];
    f32 v[4];
    f32 rot[4];
    f32 scl[4];
    OvlMtx m;
    Sub *e;
    u8 *b;
    s32 off;
    s32 k;
    s32 h;
    s32 t;
    s32 i;

    b = (u8 *)D_00F86500;
    pos[0] = 0;
    D_010807E4 = 0;
    pos[3] = 1.0f;
    rot[3] = 1.0f;
    scl[0] = 1.59999996f;
    pos[1] = 0;
    scl[1] = 1.59999996f;
    pos[2] = 0;
    rot[0] = 0;
    rot[1] = 0;
    rot[2] = 0;
    scl[3] = 1.0f;
    scl[2] = 1.59999996f;
    func_00f309d0(1);
    func_00f344e0(1);
    func_00f32318(pos, rot, 0.0f);
    func_00f40b38(D_00F850C8);
    func_00f404c8(D_00F850E0, 0);
    func_00f3e3a0();
    func_00f3a4c8();
    D_00F9B1C4 = 0;
    off = (D_00F850E0 ^ 1) * 0x590;
    D_00F9B1CC = 0;
    D_00F9B1C8 = 1;
    e = (Sub *)(off + 0x540 + b);
    func_001bb7c8(D_00FB7260, e->b);
    func_00f64b88(e->b);
    func_001bb7c8(D_00FB7278, e->c);
    func_00f65a68(e->c);
    b += 0x80;
    sceVu0UnitMatrix((void *)(off + b));
    v[0] = pos[0];
    v[1] = pos[1];
    v[3] = pos[3];
    v[2] = pos[2] - D_00F85268 * 0.59999997f;
    h = func_00f68508(21, 1, v, rot, scl, D_00F87048);
    for (i = 0; i < 25; i++) {
        func_001bfac8();
    }
    for (i = 0; i < 20; i++) {
        func_00f2c7e8(-(f32)i / 20.0f + 1.0f);
        func_001bfac8();
    }
    func_00106978(30);
    for (i = 0; i < 30; i++) {
        func_001bfac8();
    }
    func_00f68a40(h);
    func_00f2c7e8(1.0f);
    func_00f421a8();
    func_001bfac8();
    t = func_001c0310(-1, func_00f421d8, D_00F850E0 ^ 1);
    func_00f29810(D_00F864C0->s.b, D_00F864C0->b, D_00F864C0->c);
    func_00106a58(20);
    D_010807E4 = 1;
    pos[2] = -1000.0f;
    sceVu0UnitMatrix(m);
    sceVu0RotMatrixX(m, m, 0.32f);
    sceVu0RotMatrixY(m, m, -0.54999997f);
    m[3][2] = D_00F850C8;
    sceVu0CopyMatrix(D_00F85200, m);
    func_001bf048(m, m);
    sceVu0CopyMatrix(D_00F864C0->m, m);
    func_0011d1e0(0xE2CE, -1, pos, 0);
    for (i = 0; i < 40; i++) {
        pos[2] += 200.0f;
        func_00f32318(pos, rot, 0.0f);
        func_001bfac8();
    }
    func_00106978(20);
    for (i = 0; i < 20; i++) {
        pos[2] += 200.0f;
        func_00f32318(pos, rot, 0.0f);
        func_001bfac8();
    }
    D_010807E4 = 0;
    while (func_001bff70(t) != 0) {
        func_001bfac8();
    }
    func_00f421a8();
    func_00f2c7e8(0.0f);
    pos[2] = 0.0f;
    func_00f32318(pos, rot, 0.0f);
    func_00f40b38(D_00F850C8);
    func_00f404c8(D_00F850E0, 0);
    func_00f29810(D_00F864C0->s.b, D_00F864C0->b, D_00F864C0->c);
    D_00F9B1CC = 1;
    func_00106a58(30);
    for (i = 0; i < 15; i++) {
        func_001bfac8();
    }
    h = func_00f68508(22, 1, v, rot, scl, D_00F87048);
    for (i = 0; i < 20; i++) {
        func_001bfac8();
    }
    for (i = 0; i < 25; i++) {
        func_00f2c7e8((f32)i / 25.0f + 0.0f);
        func_001bfac8();
    }
    func_00f2c7e8(1.0f);
    for (i = 0; i < 15; i++) {
        func_001bfac8();
    }
    func_00f68a40(h);
    func_00f32318(pos, rot, 1.0f);
    func_00f344e0(0);
    D_010807E0 = 1;
}
