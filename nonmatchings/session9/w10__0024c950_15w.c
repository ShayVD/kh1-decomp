/* 0024c950: LCS 15 (was 29; session-5 b17 draft), mode hand, 1164 vs 1172. Changes: abs()/N result in its own temp t (col = (t << 24) + K / t << 24), and the end-section k (0/1, 2nd arg of func_002077f0) is the SAME variable as col: its a1 copy preference puts col in a1 like the orig (was t1, 'global-alloc: col prefers t1'). Top k as a block-local kk computed before the D_00669A68/6C stores. Left: top local-alloc v0/a0 swap (orig: D_00669A5C load in v0, kk in a0); the orig's then-arm 'addu a1,a1,v0; b join; nop; nop' (unfilled delay slot plus an alignment nop before the else label .L0024CAD0, +8 bytes) is not reproduced: ours fills the slot with the addu. */
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
