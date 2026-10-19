/* 00107548: LCS 17 (was 114), hand/nostrict, right size 1388, no context, FLAGGED dead FP test `if ((f32)i < 0.0f) b = 0;` after `*st = 2;` and an unnatural tail order. Everything but the tail is exact: zero stores 2F4, 2F8, 2FC, 300; tbl = (s32 *)(src->off + (s32)src). Left: tail sched/registers (lui of D_0047A1D0 and D_00494BE0 issue too early, t1 load late). */
/* func_00107548 114 LCS (hand/nostrict; was 118; 1428 vs 1388 bytes). NEW (from 00106ed0, same Pt address pattern): q8 = pt + 8; x as { s32 o0 = i * 32; *(f32 *)((s32)q8 + o0) } (base-first), y as ((Pt *)((s32)pt + o1))->y (base-first), z as { s32 o = i * 32 + 16; *(f32 *)(o + (s32)q8) } (combine splits it into index-first (i32 + q8) + 16 after cse): the three adds of the orig, no shared reg. Left: s3-s7 rotation, w->t0/t1 reloaded in the copies (a dst pointer temp gives the orig's single load and -24 bytes but LCS 195 from the regalloc shift), case 0 D_00494BA0 double lui. */
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
    s32 k;
    Work *w;
    f32 *z0, *z1;
    s32 *tbl;
    s32 last0, last1;
    s32 i, j, r, n;
    s32 *st, *b;

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
    D_0029B2F4 = 0;
    D_0029B2F8 = 0;
    D_0029B2FC = 0;
    D_0029B300 = 0;
    w->w = 1.0f;
    sceVu0MulMatrix(w->m, D_002BBFE0, mtx);
    tbl = (s32 *)(src->off + (s32)src);
    D_00494BA0 = 0;
    last0 = 0;
    D_00494BA4 = 0;
    last1 = 0;
        D_00494AA0[0] = 0;
    D_00494B20[0] = 0;
        for (i = 0; i < D_00494BB0; i = j) {
        j = i + 1;
        k = j * 4;
        if (func_00107520(i)) {
            r = func_00107ab8(w->m, src->e[i]);
            b = &D_00494BA8->state; st = b + i * 4;
            *st = 2;
            if ((f32)i < 0.0f) b = 0; /* dead FP test (flagged) */
            switch (r) {
            case 0:
                if (tbl[k] != 0) {
                    *st = 1;
                    { s32 n = D_0029B2FC * 4;
                    if (D_002BC0A8.b2) {
                        { Pt *pt = D_00494BAC; f32 *q8 = (f32 *)((s32)pt + 8);
                        { s32 o0 = i * 32; w->p[0] = *(f32 *)((s32)q8 + o0); }
                        { s32 o1 = i * 32; w->p[1] = ((Pt *)((s32)pt + o1))->y; }
                        { s32 o = i * 32 + 16; w->p[2] = *(f32 *)(o + (s32)q8); } }
                        func_002672f8(w->v, w->m, w->p);
                        z0[D_0029B2FC] = w->v[2] * 16.0f;
                        { s32 *kb = &D_00494BA8->key; s32 *key = kb + i * 4;
                        if (last0 != *key) {
                            D_00494AA0[++D_00494BA0] = 0;
                        }
                        D_00494AA0[D_00494BA0 - 1]++;
                        last0 = *key; }
                    }
                    { s32 *d = (s32 *)(n * 4 + (s32)w->t0); d[0] = tbl[k]; d[1] = tbl[k + 1]; }
                    D_0029B2FC++; }
                }
                break;
            case 1:
                if (tbl[k] != 0) {
                    *st = r;
                    { s32 n = D_0029B2F4 * 4;
                    if (D_002BC0A8.b2) {
                        { Pt *pt = D_00494BAC; f32 *q8 = (f32 *)((s32)pt + 8);
                        { s32 o0 = i * 32; w->p[0] = *(f32 *)((s32)q8 + o0); }
                        { s32 o1 = i * 32; w->p[1] = ((Pt *)((s32)pt + o1))->y; }
                        { s32 o = i * 32 + 16; w->p[2] = *(f32 *)(o + (s32)q8); } }
                        func_002672f8(w->v, w->m, w->p);
                        z1[D_0029B2F4] = w->v[2] * 16.0f;
                        { s32 *kb = &D_00494BA8->key; s32 *key = kb + i * 4;
                        if (last1 != *key) {
                            D_00494B20[++D_00494BA4] = 0;
                        }
                        D_00494B20[D_00494BA4 - 1]++;
                        last1 = *key; }
                    }
                    { s32 *d = (s32 *)(n * 4 + (s32)w->t1); d[0] = tbl[k]; d[1] = tbl[k + 1]; }
                    D_0029B2F4++; }
                }
                break;
            default:
                *st = 0;
                break;
            }
        } else {
            { s32 *sb = &D_00494BA8->state; sb[i * 4] = 0; }
        }
    }
    { s32 t = (s32)w->t1; s32 *d = (s32 *)(D_0029B2F4 * 16 + t); s32 *e; d[0] = D_00472150.a; D_00494BE0 = 0; t = (s32)w->t0; d[1] = D_00472150.b; e = (s32 *)(D_0029B2FC * 16 + t); e[0] = D_0047A1D0.a; e[1] = D_0047A1D0.b; }
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
