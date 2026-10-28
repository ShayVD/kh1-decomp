/* wm.x func_00f3e408: matched by hand. */
#include "ovl.h"

typedef struct { f32 v[4]; } __attribute__((aligned(16))) V3e408;
typedef struct { s32 x0; s32 h; u8 pad8[8]; f32 pos[4]; s32 flag; u8 pad24[12]; } E3e408;
extern E3e408 D_00F9A5C0[64];
extern f32 (*D_00F864C0)[4];
extern V3e408 D_00FB7130;
extern V3e408 D_00FB7140;
extern s32 D_00F850F4;
extern s32 D_00F87048;
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0CopyVector(f32 *, f32 *);
s32 func_00f3c4d8(f32 *);
void func_00f68a40(s32);
s32 func_00f3e0e0(s32);
s32 func_00f68770(s32, s32, f32 (*)[4], V3e408 *, s32);
f32 func_00f3f2e8(void);
void func_00f689f0(s32, f32 (*)[4]);
void func_00f68980(s32, V3e408 *);
void func_001c0310(s32, void (*)(s32), ...);
void func_00f3e138(s32);

void func_00f3e408(void) {
    s32 i;
    s32 r;
    f32 m[4][4];
    f32 t[4];
    V3e408 a = D_00FB7130;
    V3e408 b = D_00FB7140;
    if (D_00F850F4 == 0) {
        return;
    }
    for (i = 0; i < 64; i++) {
        E3e408 *e = &D_00F9A5C0[i];
        if (e->x0 < 0) continue;
        if (D_00F9A5C0[i].flag & 2) continue;
        sceVu0ApplyMatrix(t, D_00F864C0, D_00F9A5C0[i].pos);
        sceVu0UnitMatrix(m);
        sceVu0CopyVector(m[3], t);
        r = func_00f3c4d8(t);
        if (r < 0) {
            if (e->h >= 0) {
                func_00f68a40(e->h);
            }
            e->x0 = -1;
            e->h = -1;
        } else if (e->h < 0) {
            e->h = func_00f68770(func_00f3e0e0(e->x0), 10, m, &a, D_00F87048);
        } else {
            b.v[3] = func_00f3f2e8();
            func_00f689f0(e->h, m);
            func_00f68980(e->h, &b);
        }
        if (D_00F9A5C0[i].flag & 1) {
            D_00F9A5C0[i].flag = 2;
            func_001c0310(-1, func_00f3e138, i);
        }
    }
}
