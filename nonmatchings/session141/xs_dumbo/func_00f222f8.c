/* Round 31 (wgb): 346 -> 343 words with func_00249988 declared and called in the order (f32, f32 *, f32 *, f32 *): same EE EABI registers, but the target sets the arguments up in this order (cf. wm func_00f3a860). score 93 (1548 vs 1560). Round 29 wwm2, first draft: builds the 9 x 10 strip of triangle pairs from the D_00F2C410 grid (row pointers r0/r1/r2), alpha per row clamped by func_00249950, UV scroll + wrap (func_00f21ca8), the partial last row lerped by frac (func_00249988), then the top row's alpha cleared. Key: the row loop must not be a loop.c loop (127/0/128 are reloaded each row, nothing strength-reduced): a goto into a for(;;) (or a plain goto loop) with r2 += 10 at its top; a structured for/while hoists them (288-346). Left: the original's start label is 8-aligned (one nop), its r2 and gcse copies get later stack slots (r2 72, copies 76-96 in another order), and the end-of-row increments are scheduled differently. */
#include "ovl.h"
typedef struct { u8 h[0x10]; OvlVec pos[3]; OvlVec col[3]; OvlVec pad70; OvlVec uv[3]; } Tri;
extern OvlVec D_00F2C410[10][10];
void func_00249950(f32 *, f32, f32);
void func_00249988(f32, f32 *, f32 *, f32 *);
void func_00f21ca8(OvlVec *, s32);

void func_00f222f8(Tri *t, s32 rows, f32 du, f32 dv, f32 alpha, f32 frac) {
    f32 inv;
    f32 a0, a1;
    s32 j, i;
    OvlVec *r0, *r1, *r2;
    Tri *p;

    inv = 1.0f / rows;
    p = t;
    r0 = D_00F2C410[0];
    r1 = D_00F2C410[1];
    r2 = D_00F2C410[1];
    i = 0;
    goto start;
    for (;;) {
        r2 += 10;
start:
        a0 = (1.0f - inv * i) * 127.0f * alpha;
        a1 = (1.0f - inv * (i + 1)) * 127.0f * alpha;
        func_00249950(&a0, 0.0f, 127.0f);
        func_00249950(&a1, 0.0f, 127.0f);
        for (j = 0; j < 10; j++, p += 2) {
            if (j < 9) {
                sceVu0CopyVector(p[0].pos[0], r0[j]);
                sceVu0CopyVector(p[0].pos[1], r0[j + 1]);
                sceVu0CopyVector(p[0].pos[2], r1[j]);
                sceVu0CopyVector(p[1].pos[0], r1[j + 1]);
                sceVu0CopyVector(p[1].pos[1], r1[j]);
                sceVu0CopyVector(p[1].pos[2], r0[j + 1]);
            } else {
                sceVu0CopyVector(p[0].pos[0], r0[j]);
                sceVu0CopyVector(p[0].pos[1], r0[0]);
                sceVu0CopyVector(p[0].pos[2], r1[j]);
                sceVu0CopyVector(p[1].pos[0], r1[0]);
                sceVu0CopyVector(p[1].pos[1], r1[j]);
                sceVu0CopyVector(p[1].pos[2], r0[0]);
            }
            p[0].uv[0][0] += du;
            p[0].uv[1][0] += du;
            p[0].uv[2][0] += du;
            p[1].uv[0][0] += du;
            p[1].uv[1][0] += du;
            p[1].uv[2][0] += du;
            func_00f21ca8(p[0].uv, 3);
            func_00f21ca8(p[1].uv, 3);
            p[0].uv[0][1] += dv;
            p[0].uv[1][1] += dv;
            p[0].uv[2][1] += dv;
            p[1].uv[0][1] += dv;
            p[1].uv[1][1] += dv;
            p[1].uv[2][1] += dv;
            func_00f21ca8(p[0].uv, 3);
            func_00f21ca8(p[1].uv, 3);
            p[0].col[0][0] = 128.0f;
            p[0].col[0][1] = 128.0f;
            p[0].col[0][2] = 128.0f;
            p[0].col[0][3] = a0;
            p[0].col[1][0] = 128.0f;
            p[0].col[1][1] = 128.0f;
            p[0].col[1][2] = 128.0f;
            p[0].col[1][3] = a0;
            p[0].col[2][0] = 128.0f;
            p[0].col[2][1] = 128.0f;
            p[0].col[2][2] = 128.0f;
            p[0].col[2][3] = a1;
            p[1].col[0][0] = 128.0f;
            p[1].col[0][1] = 128.0f;
            p[1].col[0][2] = 128.0f;
            p[1].col[0][3] = a1;
            p[1].col[1][0] = 128.0f;
            p[1].col[1][1] = 128.0f;
            p[1].col[1][2] = 128.0f;
            p[1].col[1][3] = a1;
            p[1].col[2][0] = 128.0f;
            p[1].col[2][1] = 128.0f;
            p[1].col[2][2] = 128.0f;
            p[1].col[2][3] = a0;
            if (rows != 9 && i == rows - 1) {
                if (j < 9) {
                    OvlVec v;
                    sceVu0CopyVector(p[0].pos[0], r0[j]);
                    sceVu0CopyVector(p[0].pos[1], r0[j + 1]);
                    func_00249988(frac, v, r0[j], r1[j]);
                    sceVu0CopyVector(p[0].pos[2], v);
                    func_00249988(frac, v, r0[j + 1], r1[j + 1]);
                    sceVu0CopyVector(p[1].pos[0], v);
                    func_00249988(frac, v, r0[j], r1[j]);
                    sceVu0CopyVector(p[1].pos[1], v);
                    sceVu0CopyVector(p[1].pos[2], r0[j + 1]);
                } else {
                    OvlVec v;
                    sceVu0CopyVector(p[0].pos[0], r0[j]);
                    sceVu0CopyVector(p[0].pos[1], r0[0]);
                    func_00249988(frac, v, r0[j], r1[j]);
                    sceVu0CopyVector(p[0].pos[2], v);
                    func_00249988(frac, v, r0[0], r1[0]);
                    sceVu0CopyVector(p[1].pos[0], v);
                    func_00249988(frac, v, r0[j], r1[j]);
                    sceVu0CopyVector(p[1].pos[1], v);
                    sceVu0CopyVector(p[1].pos[2], r0[0]);
                }
            }
        }
        r0 = r2;
        r1 += 10;
        i++;
        if (i >= 9)
            break;
    }
    p = t;
    for (j = 0; j < 10; j++, p += 2) {
        p[0].col[0][0] = 128.0f;
        p[0].col[0][1] = 128.0f;
        p[0].col[0][2] = 128.0f;
        p[0].col[0][3] = 0.0f;
        p[0].col[1][0] = 128.0f;
        p[0].col[1][1] = 128.0f;
        p[0].col[1][2] = 128.0f;
        p[0].col[1][3] = 0.0f;
        p[1].col[2][0] = 128.0f;
        p[1].col[2][1] = 128.0f;
        p[1].col[2][2] = 128.0f;
        p[1].col[2][3] = 0.0f;
    }
}
