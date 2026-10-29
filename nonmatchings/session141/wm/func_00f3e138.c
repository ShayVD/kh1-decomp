/* 113 words, score 119 (was 114/125). Round 32 wwm2: hill2 moved the d[1] line after d[2]; ctx2 gives nothing. Earlier header: 114 words (612 vs 616). Homing loop: ApplyMatrix pos, then step toward func_00f2c818 m[3] with speed 100 (+10, cap 400) until within 100 or speed; PlatSqrtf (include platform/math.h) gives the bare sqrt.s. Left: the target hoists &D[i] to a stack slot (sp+84) for the x0 fail path and keeps i/i*2 in s7/sp+80; tried do/while vs while, an e pointer for cond/fail/h in several mixes. */
#include "platform/math.h"
typedef struct { s32 x0; s32 h; u8 pad8[8]; f32 pos[4]; s32 flag; u8 pad24[12]; } E3e138;
extern E3e138 D_00F9A5C0[64];
extern f32 (*D_00F864C0)[4];
extern s32 D_00F850F4;
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);
void sceVu0Normalize(f32 *, f32 *);
void func_00f2c818(f32 (*)[4]);
void func_00f30ae0(s32);
void func_00f688c8(s32, f32 *, s32);
void func_001bfac8(void);
void func_00f68a40(s32);

void func_00f3e138(s32 i) {
    f32 m[4][4];
    f32 d[4];
    f32 len;
    f32 speed;

    D_00F9A5C0[i].flag |= 4;
    sceVu0ApplyMatrix(D_00F9A5C0[i].pos, D_00F864C0, D_00F9A5C0[i].pos);
    speed = 100.0f;
    while (D_00F850F4 != 0 && D_00F9A5C0[i].x0 >= 0) {
            func_00f2c818(m);
            d[0] = m[3][0] - D_00F9A5C0[i].pos[0];
            d[2] = m[3][2] - D_00F9A5C0[i].pos[2];
            d[3] = 1.0f;
            d[1] = m[3][1] - D_00F9A5C0[i].pos[1];
            len = PlatSqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
            if (len < 100.0f || len < speed) {
                func_00f30ae0(D_00F9A5C0[i].x0);
                D_00F9A5C0[i].x0 = -1;
                break;
            }
            sceVu0Normalize(d, d);
            speed += 10.0f;
            if (400.0f < speed) {
                speed = 400.0f;
            }
            D_00F9A5C0[i].pos[0] += d[0] * speed;
            D_00F9A5C0[i].pos[1] += d[1] * speed;
            D_00F9A5C0[i].pos[2] += d[2] * speed;
            func_00f688c8(D_00F9A5C0[i].h, D_00F9A5C0[i].pos, 0);
            func_001bfac8();
    }
    func_00f68a40(D_00F9A5C0[i].h);
    D_00F9A5C0[i].h = -1;
    D_00F9A5C0[i].flag = 0;
}
