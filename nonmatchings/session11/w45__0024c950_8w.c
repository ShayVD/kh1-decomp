/* 0024c950: 8w LCS (11 pos, right size 1172), hand/nofill, no context. s11w45: s10 r2_2 9w draft + FLAGGED dead FP test `if ((f32)D_00669A5C < (f32)(D_00669A5C + 1)) t = 0; else n = 0;` right after `D_00669A6C = x;` (the then-arm jump over the else keeps it to both allocators; flow2 deletes it, sched2 re-merges the blocks). The cvt and the +1 give the D_00669A5C load 4 refs, so local-alloc gives it v0 and kk a0 (the s10 swap is fixed). Left: the test splits `p = D_00669A40` and the loop preheader (lui 0x47/s3) into another block, and L now lives to the block end: A68 pair a1 (orig v1), A6C hi v1 (orig v0), A40 pair v0 (orig a1), 0x47 hi v1 (orig v0). Test placed after p= or inside the kk block, or p= moved before the stores: 9w or worse. */
#include "common.h"
extern s32 D_00669A70;
extern s32 D_00669A74;
extern s32 D_00669A78;
extern s32 D_00669A5C;
extern s32 D_00669A58;
extern s32 D_00669A68;
extern s32 D_00669A6C;
extern s16 D_00669A40[8];
extern s32 D_0046A5BC;
extern s32 D_0046A558;
extern s32 D_0046A560;
extern s16 D_0046A5C0[], D_0046A5D0[];
void func_00206130(void *, s32, s32, s32, s32, s32);
void func_0024c8b8(void *, s16 *, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_002077f0(void *, s32, s32, s32, s32, s32);
void func_001fade0(void *, s32, s32, s32, s32, s32);
s32 func_001fc308(void *, s32, s32, s32, s32, s32, s32, s32, s32);

void func_0024c950(void *a) {
    s32 x, y, yy;
    s32 i, n, c, col, k, col2, h;
    s16 *p;
    s32 cc;
    s32 t;
    if (D_00669A5C == 0) {
        func_002078f0(a, 19, 2, 0, 188, D_00669A78 + D_00669A74 + 94, 200, 512, 1);
        x = 220;
        y = D_00669A78 + D_00669A74 + 89;
    } else {
        x = 190;
        y = 80;
    }
    { s32 kk = 11; if (D_00669A5C) kk = 0; yy = y + kk; }
    D_00669A68 = x;
    D_00669A6C = x;
    if ((f32)D_00669A5C < (f32)(D_00669A5C + 1)) t = 0; else n = 0;
    p = D_00669A40;
    for (i = 0; i < 8; i++) {
        n = *p;
        D_0046A5BC++;
        if (D_00669A5C == 0) {
            if (D_0046A5BC > 600) D_0046A5BC = 40;
            t = abs(D_0046A5BC * 102 - 30600) / 300;
            if (D_00669A58 == i) col = (t << 24) + 0x00E6E664;
            else col = 0x28E6E664;
        } else {
            if (D_0046A5BC > 300) D_0046A5BC = 20;
            col = abs(D_0046A5BC * 102 - 15300) / 150;
            col = (D_00669A58 == i) ? col << 24 : 0x28000000;
        }
        if (n < 0 || (D_00669A58 == 7 && i == D_00669A58))
            func_00206130(a, x, yy + 1, 15, 15, col);
        if (n > 0) {
            if (D_00669A5C == 0) {
                func_001fade0(a, x, y + 11, n, 15, 0x6635B300);
                x += 16;
            } else {
                func_001fade0(a, x, y, n, 15, 0x6635B300);
                x += 16;
            }
        } else
            x += 16;
        if (D_00669A58 >= i) {
            D_00669A6C = D_00669A68;
            D_00669A68 = x;
        }
        p++;
    }
    if (D_00669A5C == 0) {
        if (D_0046A558 == 0) { col = 0; col2 = 0x80808080; }
        else { col = 1; col2 = 0x80F0F0F0; }
        func_002077f0(a, col, 2, 12, D_00669A70 + 245, 120);
        func_0024c8b8(a, D_0046A5C0, 33, D_00669A70 + 250, 15, col2);
    }
    if (D_0046A560 == 0) { col = 0; col2 = 0x80808080; }
    else { col = 1; col2 = 0x80F0F0F0; }
    func_002077f0(a, col, 2, 12, D_00669A70 + 277, 120);
    func_0024c8b8(a, D_0046A5D0, 57, D_00669A70 + 282, 15, col2);
    cc = 0x4CE6E6E6;
    func_001fc308(a, 138, D_00669A78 + 323, 0, 0, 8, 0, cc, cc);
    func_001fc308(a, 171, D_00669A78 + 328, 0, 0, 17, 0, cc, cc);
    func_001fc308(a, 452, D_00669A78 + 328, 0, 0, 18, 0, cc, cc);
    func_001fc308(a, 464, D_00669A78 + 323, 0, 0, 9, 0, cc, cc);
}
