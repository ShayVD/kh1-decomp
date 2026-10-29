/* wm.x func_00f371d8: matched by hand. */
#include "ovl.h"

typedef struct { f32 x; u8 pad[2]; u16 h6; u8 pad2[24]; u16 h32; } O371d8;
typedef struct { u8 pad[1344]; s32 f1344; } G371d8;
typedef struct { s32 f224; s32 f228; s32 pad3; s32 f236; u8 pad4[12]; s32 f252; } Q371d8;
typedef struct { f32 m[4][4]; u8 pad[0xE0 - 0x40]; Q371d8 s; u8 pad5[16]; } E371d8;
extern s32 D_00F850A0, D_00FCE384, D_00F8C23C, D_00F9B1C0, D_00F9B2EC, D_00F9B2D4, D_00F9B2D8, D_00F85098;
extern G371d8 *D_00F864C0;
extern E371d8 D_00FCE390[];
extern f32 D_00F86480[4][4];
s32 func_00f41448(void);
s32 func_00f40c98(void);
s32 func_00f43d88(s32);
O371d8 *func_00f3f260(s32, s32);
s32 func_00f37170(O371d8 *);
s32 func_00f36218(void);
s32 func_00f62c78(s32, s32);
s32 func_00f3a640(s32, O371d8 *, s32, s32);
void func_00f3b118(s32, s32, s32, s32, f32 (*)[4], s32);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0RotMatrixZ(f32 (*)[4], f32 (*)[4], f32);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

void func_00f371d8(void) {
    f32 m[4][4];
    f32 rot[4][4];
    O371d8 *o;
    E371d8 *e;
    s32 n;
    s32 i;
    s32 k;
    f32 z;
    Q371d8 *q;

    if (D_00F850A0 != 0) {
        D_00FCE384--;
    }
    if (func_00f41448() == 0 && D_00F8C23C == 0 && func_00f40c98() == 0 && D_00F9B1C0 >= 30 && D_00F9B2EC == 0) {
        n = func_00f43d88(D_00F864C0->f1344);
        for (i = 0; i < n; i++) {
            o = func_00f3f260(i, D_00F864C0->f1344);
            if (o->x < (f32)D_00F9B2D4) continue;
            if ((f32)D_00F9B2D8 < o->x) continue;
            if (o->h6 & 5) continue;
            if (func_00f37170(o) == 0) continue;
            k = func_00f36218();
            if (k < 0) break;
            if (func_00f3a640(k, o, func_00f62c78(o->h32, D_00F864C0->f1344), i)) {
                o->h6 |= 4;
            }
        }
    }
    for (i = 0; i < 256; i++) {
        z = D_00FCE390[i].m[3][2];
        q = &D_00FCE390[i].s;
        if (q->f252 != 0 && q->f224 != 0 && z < 36000.0f) {
            sceVu0UnitMatrix(rot);
            sceVu0RotMatrixZ(rot, rot, 3.141592503f);
            sceVu0MulMatrix(m, D_00FCE390[i].m, rot);
            func_00f3b118(0, 2, q->f228, q->f236, m, 0);
        }
    }
    if (D_00F85098 == 1 && D_00F850A0 == 0) {
        sceVu0UnitMatrix(rot);
        sceVu0RotMatrixZ(rot, rot, 3.141592503f);
        sceVu0MulMatrix(m, D_00F86480, rot);
        func_00f3b118(0, 0, 0x80000000, 0, m, 0);
    }
}
