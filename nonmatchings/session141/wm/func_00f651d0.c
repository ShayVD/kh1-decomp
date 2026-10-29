/* score 155 (122 words; 668 vs 688 bytes). Skinned-bone matrix build: Euler rot + translation per bone, optional base multiply, func_001bf048 copy, then parent multiplies and per-mesh func_00f66640 calls gated by D_00FB1144 bits. An unused `f32 u[4][4]` gives most of the frame. Left: the original spills the bone pointer (sp+208) and keeps the mesh table in s6, and saves t2..t5 with sq/lq around func_00f66640 (caller-save, 16 more frame bytes). Its loop over bones also uses blez/b plus a bnezl rotation. Tried mesh/bone order. */
#include "ovl.h"

typedef struct {
    f32 rot[4];
    f32 pos[4];
    u8 pad32[16];
    s32 parent;
    u8 pad52[12];
} BoneSrc;

typedef struct {
    u8 pad0[16];
    f32 m1[4][4];
    f32 m2[4][4];
} Bone;

typedef struct {
    s32 off;
    s32 bone;
    u8 pad8[32];
} Sub;

typedef struct {
    s32 count;
    s32 off;
    u8 pad8[32];
} Mesh;

typedef struct {
    u8 pad0[144];
    s32 n;
    s32 boneOff;
    s32 nm;
    s32 meshOff;
} Hdr;

extern u32 D_00FB1144;
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0RotMatrixX(f32 (*)[4], f32 (*)[4], f32);
void sceVu0RotMatrixY(f32 (*)[4], f32 (*)[4], f32);
void sceVu0RotMatrixZ(f32 (*)[4], f32 (*)[4], f32);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_001bf048(f32 (*)[4], f32 (*)[4]);
s32 func_00f66640(s32, s32, Bone *, s32, void *, s32);

Bone *func_00f651d0(s32 *out, s32 a1, Bone *mats, s32 *opt, Hdr *h, s32 *arr, f32 (*base)[4]) {
    f32 r[4][4];
    f32 t[4][4];
    f32 u[4][4];
    s32 p;
    BoneSrc *b;
    Mesh *m;
    Sub *s;
    s32 i;
    s32 j;
    s32 v;

    b = (BoneSrc *)((u8 *)h + h->boneOff);
    m = (Mesh *)((u8 *)h + h->meshOff);
    sceVu0UnitMatrix(r);
    for (i = 0; i < h->n; i++) {
        sceVu0RotMatrixX(t, r, b[i].rot[0]);
        sceVu0RotMatrixY(t, t, b[i].rot[1]);
        sceVu0RotMatrixZ(mats[i].m1, t, b[i].rot[2]);
        mats[i].m1[3][0] = b[i].pos[0];
        mats[i].m1[3][1] = b[i].pos[1];
        mats[i].m1[3][2] = b[i].pos[2];
        if (base != NULL) {
            sceVu0MulMatrix(mats[i].m1, base, mats[i].m1);
        }
        func_001bf048(mats[i].m2, mats[i].m1);
    }
    for (i = 0; i < h->n; i++) {
        p = b[i].parent;
        if (p >= 0) {
            sceVu0MulMatrix(mats[i].m2, mats[p].m2, mats[i].m2);
            sceVu0MulMatrix(mats[i].m1, mats[p].m1, mats[i].m1);
        }
    }
    for (j = 0; j < h->nm; j++) {
        v = 0;
        if (opt != NULL) {
            v = opt[j];
        }
        s = (Sub *)((u8 *)h + m[j].off);
        for (i = 0; i < m[j].count; i++) {
            if (D_00FB1144 & (1 << i)) {
                out[j] = func_00f66640(out[j], a1, &mats[s[i].bone], v, (u8 *)h + s[i].off, arr[j]);
            }
        }
    }
    return &mats[h->n];
}
