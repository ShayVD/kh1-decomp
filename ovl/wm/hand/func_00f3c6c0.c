/* wm.x func_00f3c6c0: matched by hand. */
#include "ovl.h"

typedef struct { f32 v[4]; } __attribute__((aligned(16))) V3c;
typedef union { struct { u32 type : 4; u32 id : 24; u32 rest : 4; } f; u32 w; } B3c;
typedef struct { u16 h0, h2, h4, h6; } D3c;
typedef struct {
    u8 pad0[4];
    s32 x4;
    u8 pad8[0x14];
    D3c *x1C;
    f32 m20[12];
    f32 v50[4];
} E3c;
extern V3c D_00FB7120;
extern s32 D_00F87040;
extern s32 D_00F8703C;
extern s32 D_00F87044;
extern f32 D_0107FFE0[][4][4];
void func_001be820(void *, s32);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0RotMatrixX(f32 (*)[4], f32 (*)[4], f32);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
s32 func_00f3b480(void);
E3c *func_00f3b460(s32);
s32 func_00f3c470(D3c *);
s32 func_00f3c4d8(f32 *);
f32 func_00f3f2e8(void);
f32 func_00f3b318(s32);
s32 func_00f3c550(s32, f32 (*)[4], u8 *, V3c *);
s32 func_00f68b40(s32);
s32 func_00f68b48(f32 (*)[4], f32 *, s32, s32);
s32 func_00f68770(s32, s32, f32 (*)[4], f32 *, s32);
void func_00f68980(s32, V3c *);
void func_00f687e8(s32, B3c);
void func_00f68808(s32, s32);
u32 func_00f68828(s32);
void func_00f68a40(s32);

void func_00f3c6c0(void) {
    u8 used[256];
    f32 m[4][4];
    f32 r[4][4];
    f32 m2[4][4];
    f32 v[4];
    V3c col = D_00FB7120;
    E3c *e;
    B3c b;
    s32 i, j, n, k, h, cnt;
    f32 (*p)[4];

    func_001be820(used, 256);
    sceVu0UnitMatrix(r);
    sceVu0RotMatrixX(r, r, 3.1415927f);
    for (i = 0; i < func_00f3b480(); i++) {
        e = func_00f3b460(i);
        if (!func_00f3c470(e->x1C)) continue;
        if (func_00f3c4d8(e->v50) < 0) continue;
        sceVu0MulMatrix(m, (void *)e->m20, r);
        col.v[3] = func_00f3f2e8() * func_00f3b318(i);
        n = func_00f3c550(e->x4, m, used, &col);
        if (n != 0) continue;
        switch (e->x1C->h2) {
        case 2:
            cnt = func_00f68b40(D_00F87040);

            for (j = 0; j < cnt; j++) {
                k = func_00f68b48(D_0107FFE0[j], v, j, D_00F87040);
                if (e->x1C->h6 == 13 && k == 1) continue;
                sceVu0MulMatrix(m2, m, D_0107FFE0[j]);
                h = func_00f68770(k, 10000, m2, v, D_00F8703C);
                b.f.type = 2;
                func_00f68980(h, &col);
                b.f.id = e->x4;
                func_00f687e8(h, b);
                func_00f68808(h, j);
                used[h] = 1;
            }
            break;
        case 5:
            b.f.type = 5;
            h = func_00f68770(e->x1C->h6, 10000, m, 0, D_00F87044);
            func_00f68980(h, &col);
            b.f.id = e->x4;
            func_00f687e8(h, b);
            used[h] = 1;
            break;
        case 6:
            b.f.type = 6;
            h = func_00f68770(e->x1C->h6 + 3, 10000, m, 0, D_00F87044);
            func_00f68980(h, &col);
            b.f.id = e->x4;
            func_00f687e8(h, b);
            used[h] = 1;
            break;
        }
    }
    for (i = 0; i < 256; i++) {
        b.w = func_00f68828(i);
        if (!used[i] && b.f.type) func_00f68a40(i);
    }
}
