/* 3 words (696 bytes, size matches). Only the loop count register differs: the target puts n = o->f20 / D_002BBDEC in a0 (mfc1 a0, blez a0) and copies it to s3 in the delay slot of the last pre-loop test (move s3,a0); gcc here puts n straight into s3. Needed: v = -m[2] * sp (the row at 128 is m[2]), case 61 and case 62 as separate bodies (gives the ==62 / <63 / ==61 compare tree), kind left unset by default, and f0 = 0 before p = NULL. Tried: a copy variable for the bound or for the i == n test, s16/u32 n, while and break forms, a guarded do-while (worse, 110), and a 10 min -j1 permuter run (no improvement). */
typedef struct { u8 pad[4]; u8 b4; } P36bc0;
typedef struct { s32 f0; P36bc0 *p; s32 f8; s32 f12; s32 f16; s32 f20; u8 pad[72]; f32 m[4][4]; f32 m160[4][4]; } O36bc0;
extern s32 D_00F87048;
extern f32 D_002BBDEC;
O36bc0 *func_00f363c0(s32);
void func_00f363e0(f32 (*)[4], s32, P36bc0 *);
s32 func_00f68770(s32, s32, void *, s32, s32);
void func_00f36308(s32);
void sceVu0TransMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void func_00f689f0(s32, f32 (*)[4]);
void func_00f68ab0(s32);
void func_001bfac8(void);
s32 func_00f41448(void);
void func_00f68a40(s32);

void func_00f36bc0(s32 arg) {
    f32 v[4];
    O36bc0 *o;
    s32 h;
    s32 i;
    s32 n;
    s32 kind;
    f32 sp;

    o = func_00f363c0(arg);
    func_00f363e0(o->m, o->f0, o->p);
    h = func_00f68770(o->f8, 1000, o->m, 0, D_00F87048);
    if (h < 0) return;
    sp = 500.0f;
    if (o->f16 != 0) {
        sp = o->f16 * 100.0f;
    }
    sp *= D_002BBDEC;
    if (o->f20 == 0) {
        o->f20 = 80;
    }
    n = o->f20 / D_002BBDEC;
    for (i = 0; i < n && o->f0 != 0 && o->p != NULL && !(o->f12 & 1); i++) {
        func_00f36308(arg);
        v[0] = -o->m[2][0] * sp;
        v[1] = -o->m[2][1] * sp;
        v[2] = -o->m[2][2] * sp;
        v[3] = 1.0f;
        sceVu0TransMatrix(o->m, o->m, v);
        func_00f689f0(h, o->m);
        if (i == n) {
            func_00f68ab0(h);
        }
        func_001bfac8();
        if (func_00f41448()) {
            o->f0 = 0;
            o->p = NULL;
            func_00f68a40(h);
            return;
        }
    }
    if (o->p != NULL && o->f0 != 0 && (o->f12 & 1)) {
        switch (o->p->b4 - 1) {
        case 61:
            kind = 53;
            break;
        case 62:
            kind = 53;
            break;
        case 63:
            kind = 54;
            break;
        }
        func_00f68770(kind, 1, o->m160, 0, D_00F87048);
    }
    o->f0 = 0;
    o->p = NULL;
    func_00f68a40(h);
}
