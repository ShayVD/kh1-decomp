#include "common.h"
extern u8 D_002A4ED0[], D_002A4FC0[];
extern s32 D_002BC09C;
extern f32 D_002BC098;
extern s32 D_002BC730;
extern s32 D_002BC080[4];
extern volatile u64 D_002A4F60[];
extern u8 D_002BCAF0[];
void func_00106b18(void *);
void func_00102cc8(s32 *, s32 *, s32 *, s32 *);
void func_002676c0(void *, void *, f32);
void func_00102d20(void *, f32 *, s32 *, s32 *);

void func_00102da8(s32 arg0) {
    f32 mat[16];
    f32 v[4];
    s32 sx[4];
    s32 sy[4];
    s32 x0, x1, y0, y1;
    f32 f;

    if (arg0 == 4) {
        func_00106b18(D_002A4ED0);
    }
    f = D_002BC730 * (D_002BC098 / D_002BC09C);
    if (D_002BC098 < f) {
        f = D_002BC098;
    } else {
        D_002BC730++;
    }
    D_002A4F60[3] = (u64)D_002BC080[0] | ((u64)D_002BC080[1] << 8) | ((u64)D_002BC080[2] << 16) | ((u64)D_002BC080[3] << 24) | ((u64)1 << 32);
    func_00102cc8(&x0, &x1, &y0, &y1);
    func_002676c0(mat, D_002BCAF0, f);
    v[0] = (x0 >> 4) - 256;
    v[1] = (y0 >> 4) - 192;
    func_00102d20(mat, v, &sx[0], &sy[0]);
    v[0] = (x1 >> 4) - 256;
    v[1] = (y0 >> 4) - 192;
    func_00102d20(mat, v, &sx[1], &sy[1]);
    v[0] = (x0 >> 4) - 256;
    v[1] = (y1 >> 4) - 192;
    func_00102d20(mat, v, &sx[2], &sy[2]);
    v[0] = (x1 >> 4) - 256;
    v[1] = (y1 >> 4) - 192;
    func_00102d20(mat, v, &sx[3], &sy[3]);
    D_002A4F60[5] = (u64)(sx[0] + 28664) | ((u64)(sy[0] + 29680) << 16) | ((u64)-2 << 32);
    D_002A4F60[7] = (u64)(sx[1] + 28664) | ((u64)(sy[1] + 29680) << 16) | ((u64)-2 << 32);
    D_002A4F60[9] = (u64)(sx[2] + 28664) | ((u64)(sy[2] + 29680) << 16) | ((u64)-2 << 32);
    D_002A4F60[11] = (u64)(sx[3] + 28664) | ((u64)(sy[3] + 29680) << 16) | ((u64)-2 << 32);
    func_00106b18(D_002A4FC0);
}

extern s32 D_00351BD0;
extern s32 D_0048C518[], D_0048C558[], D_0048C308[][16], D_0048C398[][16], D_0048C418[][16];
extern s32 D_0048C1E8[], D_0048C228[], D_0048BFD8[][16], D_0048C068[][16], D_0048C0E8[][16];
extern s32 D_00494BC0[4][4], D_002A6C10[4][4], D_002BC170[4][4], D_002BC020[4][4], D_002BBF60[4][4];
extern s32 D_002A3F60[4][4][4];
void func_00107e60(void);

void func_00107ec0(s32 (*m)[4]) {
    s32 i, j, k;

    func_00107e60();
    if (D_00351BD0) {
        k = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                s32 g0 = D_002A3F60[0][i][j];
                s32 a = m[i][j];
                s32 b = D_002BC170[i][j];
                s32 g1 = D_002A3F60[1][i][j];
                s32 c = D_002BC020[i][j];
                s32 g2 = D_002A3F60[2][i][j];
                s32 d = D_002BBF60[i][j];
                s32 g3 = D_002A3F60[3][i][j];
                D_0048C308[0][k] = a;
                D_0048C308[1][k] = b;
                D_0048C398[0][k] = c;
                D_0048C398[1][k] = d;
                D_0048C418[0][k] = g0;
                D_0048C518[k] = D_00494BC0[i][j];
                D_0048C558[k] = D_002A6C10[i][j];
                D_0048C418[1][k] = g1;
                D_0048C418[2][k] = g2;
                D_0048C418[3][k] = g3;
                k++;
            }
        }
    } else {
        k = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                s32 g0 = D_002A3F60[0][i][j];
                s32 a = m[0][i * 4 + j];
                s32 b = D_002BC170[i][j];
                s32 g1 = D_002A3F60[1][i][j];
                s32 c = D_002BC020[i][j];
                s32 g2 = D_002A3F60[2][i][j];
                s32 d = D_002BBF60[i][j];
                s32 g3 = D_002A3F60[3][i][j];
                D_0048BFD8[0][k] = a;
                D_0048BFD8[1][k] = b;
                D_0048C068[0][k] = c;
                D_0048C068[1][k] = d;
                D_0048C0E8[0][k] = g0;
                D_0048C1E8[k] = D_00494BC0[i][j];
                D_0048C228[k] = D_002A6C10[i][j];
                D_0048C0E8[1][k] = g1;
                D_0048C0E8[2][k] = g2;
                D_0048C0E8[3][k] = g3;
                k++;
            }
        }
    }
}
#include "data/data_002B.h"
#include "data/data_0035.h"
#include "data/data_002A.h"
#include "data/data_0048.h"
