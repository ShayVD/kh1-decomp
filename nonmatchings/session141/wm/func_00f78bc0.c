/* score 59 (50 words; 404 vs 400 bytes). Fade thread loop. The original's first fade-in loop is a crossjumped goto loop (`b` into a shared `jal`, address not hoisted, 128 kept in s4): f78bc0f.c-style `if ((D += 10) < 129) { loop: func(1); if (...) goto loop; }` gives that shape (score 69) but the outer-loop invariant set differs (sp+16 hoisted instead of 128). Tried do/while/for-comma/goto forms, inline helpers, array decl orders. */
#include "ovl.h"

typedef struct { u8 r, g, b, a; } Rgba;

extern s32 D_00FB5EC4;
extern u8 D_00FB5ECC;
extern s32 D_0108F910;
extern s32 D_0108F914;
void func_00f7a1a8(Rgba *rgba, s32 *x, s32 *y, u32 alpha);
void func_0024e468(s32);

void func_00f78bc0(void) {
    Rgba c[4];
    s32 x[4];
    s32 y[4];
    u8 a;

    while (1) {
        if (D_00FB5EC4 != 0) {
            a = D_00FB5ECC;
            c[0].r = 0;
            c[1].r = 0;
            c[2].r = 0;
            c[3].r = 0;
            c[0].g = 0;
            c[1].g = 0;
            c[2].g = 0;
            c[3].g = 0;
            c[0].b = 0;
            c[1].b = 0;
            c[2].b = 0;
            c[3].b = 0;
            c[0].a = a;
            c[1].a = a;
            c[2].a = a;
            c[3].a = a;
            x[0] = 0;
            y[0] = 42;
            x[1] = 512;
            y[1] = 42;
            x[2] = 0;
            y[2] = 344;
            x[3] = 512;
            y[3] = 344;
            func_00f7a1a8(c, x, y, 68);
        }
        if (D_0108F914 != 0) {
            func_0024e468(4);
            while ((D_0108F910 += 10) <= 128) {
                func_0024e468(1);
            }
            D_0108F910 = 128;
            while (D_0108F914 != 3) {
                func_0024e468(1);
            }
            while ((D_0108F910 -= 10) >= 0) {
                func_0024e468(1);
            }
            D_0108F910 = 0;
        }
        func_0024e468(1);
    }
}
