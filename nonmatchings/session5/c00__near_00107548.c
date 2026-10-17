#include "common.h"

typedef struct { s32 a, b; } P8;
typedef struct { P8 v; s32 c, d; } E16;
typedef struct { u8 pad[8]; s32 key; s32 state; } Ent;
typedef struct { u8 pad[8]; f32 x, y; u8 pad10[8]; f32 z; u8 pad1c[4]; } Pt;
typedef struct { f32 v[4]; f32 p[3]; f32 w; f32 m[4][4]; E16 *t0; E16 *t1; u8 pad68[8]; } Work;
typedef struct { u8 pad[4]; s32 off; u8 pad8[8]; u8 e[1][128]; } Src;
typedef struct { u32 b0:1; u32 b1:1; u32 b2:1; u32 rest:29; } Flags;

void *func_00122048(s32, s32);
void func_001220b8(void *);
s32 func_00107520(s32);
s32 func_00107ab8(f32 (*)[4], void *);
void func_002672f8(f32 *, f32 (*)[4], f32 *);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_001072c0(s32, f32 *);
void func_001073f0(s32, f32 *);

extern s32 D_00351BD0;
extern E16 D_0047A210[], D_00472190[], D_004761D0[], D_0046E150[];
extern P8 D_00472150, D_0047A1D0;
extern s32 D_0029B2F4, D_0029B2F8, D_0029B2FC, D_0029B300;
extern f32 D_002BBFE0[4][4];
extern Flags D_002BC0A8;
extern s32 D_00494AA0[32];
extern s32 D_00494B20[32];
extern s32 D_00494BA0, D_00494BA4;
extern Ent *D_00494BA8;
extern Pt *D_00494BAC;
extern s32 D_00494BB0;
extern s32 D_00494BE0;

void func_00107548(f32 (*mtx)[4], Src *src) {
    Work *w;
    f32 *z0, *z1;
    E16 *tbl;
    s32 last0, last1;
    s32 i, r, n;

    w = func_00122048(0x70, 0x10);
    z0 = func_00122048(0x1000, 4);
    z1 = func_00122048(0x1000, 4);
    if (D_00351BD0 != 0) {
        w->t0 = D_0047A210;
        w->t1 = D_00472190;
    } else {
        w->t0 = D_004761D0;
        w->t1 = D_0046E150;
    }
    D_0029B2F8 = 0;
    D_0029B300 = 0;
    D_0029B2F4 = 0;
    D_0029B2FC = 0;
    w->w = 1.0f;
    sceVu0MulMatrix(w->m, D_002BBFE0, mtx);
    tbl = (E16 *)((u8 *)src + src->off);
    D_00494BA0 = 0;
    last0 = 0;
    D_00494BA4 = 0;
    last1 = 0;
    D_00494AA0[0] = 0;
    D_00494B20[0] = 0;
    for (i = 0; i < D_00494BB0; i++) {
        if (func_00107520(i)) {
            r = func_00107ab8(w->m, src->e[i]);
            D_00494BA8[i].state = 2;
            if (r == 0) {
                if (tbl[i + 1].v.a != 0) {
                    D_00494BA8[i].state = 1;
                    n = D_0029B2FC;
                    if (D_002BC0A8.b2) {
                        w->p[0] = D_00494BAC[i].x;
                        w->p[1] = D_00494BAC[i].y;
                        w->p[2] = D_00494BAC[i].z;
                        func_002672f8(w->v, w->m, w->p);
                        z0[D_0029B2FC] = w->v[2] * 16.0f;
                        if (last0 != D_00494BA8[i].key) {
                            D_00494AA0[++D_00494BA0] = 0;
                        }
                        D_00494AA0[D_00494BA0 - 1]++;
                        last0 = D_00494BA8[i].key;
                    }
                    w->t0[n].v = tbl[i + 1].v;
                    D_0029B2FC++;
                }
            } else if (r == 1) {
                if (tbl[i + 1].v.a != 0) {
                    D_00494BA8[i].state = r;
                    n = D_0029B2F4;
                    if (D_002BC0A8.b2) {
                        w->p[0] = D_00494BAC[i].x;
                        w->p[1] = D_00494BAC[i].y;
                        w->p[2] = D_00494BAC[i].z;
                        func_002672f8(w->v, w->m, w->p);
                        z1[D_0029B2F4] = w->v[2] * 16.0f;
                        if (last1 != D_00494BA8[i].key) {
                            D_00494B20[++D_00494BA4] = 0;
                        }
                        D_00494B20[D_00494BA4 - 1]++;
                        last1 = D_00494BA8[i].key;
                    }
                    w->t1[n].v = tbl[i + 1].v;
                    D_0029B2F4++;
                }
            } else {
                D_00494BA8[i].state = 0;
            }
        } else {
            D_00494BA8[i].state = 0;
        }
    }
    w->t1[D_0029B2F4].v = D_00472150;
    D_00494BE0 = 0;
    w->t0[D_0029B2FC].v = D_0047A1D0;
    if (D_002BC0A8.b2) {
        if (D_0029B2FC != 0) {
            func_001072c0(D_0029B2FC, z0);
        }
        if (D_0029B2F4 != 0) {
            func_001073f0(D_0029B2F4, z1);
        }
    }
    func_001220b8(z1);
    func_001220b8(z0);
    func_001220b8(w);
}
