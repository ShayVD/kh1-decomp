/* wm.x func_00f22ac8: matched by hand. */
#include "ovl.h"

typedef struct { u64 *p; } C22ac8;
typedef struct { u8 pad[168]; u8 c[4]; } P22ac8;
extern s32 D_00FBAA90, D_00FBAA94, D_00FBB320, D_00FBAA7C, D_00FBAA78, D_00FBB324, D_00FBAA84, D_00FBB330, D_00FBAA80;
extern u64 *D_00FBB32C;
extern C22ac8 *D_00F85160;
extern P22ac8 D_00FB6498;
extern s32 D_00F87900[2];
extern f32 D_00F87910[4][4];
extern s32 D_00FBAA98[];
extern f32 D_00FBAB20[][4][4];
u64 *func_00f67278(s32, s32, u64 *);
void func_00f22358(s32, s32, s32, u32, f32 (*)[4], s32);
s32 func_00f68b40(s32);
s32 func_00f68b48(f32 (*)[4], f32 *, s32, s32);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
s32 func_00f68770(s32, s32, f32 (*)[4], f32 *, s32);
void func_00f68808(s32, s32);
void func_00f689f0(s32, f32 (*)[4]);

s32 func_00f22ac8(void) {
    f32 m[4][4];
    f32 v[4];
    u32 col;
    u8 cr;
    u8 cg;
    u8 cb;
    u8 ca;
    s32 n;
    s32 i;
    s32 r;

    if (D_00FBAA90 == 0) {
        goto end;
    }
    cr = D_00FB6498.c[0];
    cg = D_00FB6498.c[1];
    cb = D_00FB6498.c[2];
    ca = D_00FB6498.c[3];
    col = cr | (cg << 8) | (cb << 16) | (ca << 24);
    if (D_00FBAA94) {
        if (D_00FBB320) {
            D_00FBB32C = D_00F85160->p;
            D_00F85160->p = func_00f67278(13824, D_00FBAA7C, D_00FBB32C);
            func_00f22358(0xC351, D_00F87900[0], D_00F87900[1], col, D_00F87910, D_00FBAA78);
        } else {
            func_00f22358(0xC351, D_00F87900[0], D_00F87900[1], col, D_00F87910, 0);
        }
    }
    if (D_00FBB324 == 0) {
        goto end;
    }
    if (D_00FBAA98[0] < 0) {
        n = func_00f68b40(D_00FBAA84);
        for (i = 0; i < n; i++) {
            r = func_00f68b48(D_00FBAB20[i], v, i, D_00FBAA84);
            if (D_00FBB330 == 13 && r == 1) {
                D_00FBAA98[i] = -1;
                continue;
            }
            sceVu0MulMatrix(m, D_00F87910, D_00FBAB20[i]);
            r = func_00f68770(r, 0, m, v, D_00FBAA80);
            func_00f68808(r, i);
            D_00FBAA98[i] = r;
        }
    } else {
        n = func_00f68b40(D_00FBAA84);
        for (i = 0; i < n; i++) {
            if (D_00FBAA98[i] >= 0) {
                sceVu0MulMatrix(m, D_00F87910, D_00FBAB20[i]);
                func_00f689f0(D_00FBAA98[i], m);
            }
        }
    }
end:
    return 0;
}
