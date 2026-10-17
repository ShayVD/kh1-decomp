#include "common.h"
typedef struct { u8 pad[0xcc]; s32 active; } E3530;
typedef struct { E3530 e[3]; u8 pad[0x33c - 0x270]; s32 x33c; } S3530;
extern S3530 D_003F3530;
extern s32 D_003F3870;
s32 func_001ef8f8(s32);
void func_00122f20(s32, void *);
void func_0020a248(s32);

void func_00209d48(void) {
    s32 i;
    s32 p;
    D_003F3870 = 0;
    for (i = 0; i < 3; i++) {
        p = func_001ef8f8(i);
        if (p == 0) {
            D_003F3530.e[i].active = 0;
        } else {
            D_003F3530.e[i].active = 1;
            func_00122f20(p, &D_003F3530.e[i]);
            func_0020a248(i);
            D_003F3870++;
        }
    }
    D_003F3530.x33c = 0;
}

extern s32 D_006411E0;
extern f32 D_006411E4;
extern s32 D_006411E8;
extern f32 D_006411EC;
extern f32 D_006411F0;
extern f32 D_006411F4;
extern f32 D_006411F8;
extern f32 D_00641210;
extern f32 D_00641214;

void func_0020bc48(s32 a0, s32 a1, s32 a2) {
    if ((a1 - (s32)D_00641210 + 1) >> 1 == 0 && (a2 - (s32)D_00641214 + 1) >> 1 == 0) {
        D_00641210 = a1;
        D_00641214 = a2;
        D_006411E0 = 0;
        return;
    }
    D_006411E0 = 1;
    D_006411E4 = a0;
    D_006411E8 = 0;
    D_006411EC = D_00641210;
    D_006411F0 = D_00641214;
    D_006411F4 = a1;
    D_006411F8 = a2;
}

extern s32 D_003F3448[];
extern s32 D_003F3488[];
s32 func_001f31a8(s32, s32);
void func_001f3d58(s32, s32);
void func_001f3e20(s32, s32);
void func_001f3e90(s32, s32);

s32 func_0020d1d8(s32 a0) {
    s32 buf[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        buf[i] = func_001f31a8(D_003F3448[i], 1);
        if (buf[i] != 0) {
            func_001f3e90(a0, buf[i]);
            func_001f3e20(buf[i], a0);
            func_001f3d58(buf[i], D_003F3488[i]);
            a0 = buf[i];
        }
    }
    return a0;
}

typedef struct { u8 pad[0x24]; s32 x24; s32 x28; } Obj7d8;
typedef struct { u8 pad[8]; s32 flags; } G5bc8;
extern G5bc8 *D_00425BC8;
void func_0011d768(s32);
void func_001f3708(Obj7d8 *, s32);
s32 func_001f42b8(void);
void func_001f9438(Obj7d8 *, s32, s32, s32, s32, s32, s32);
s32 func_001fe570(Obj7d8 *);
void func_002079c8(Obj7d8 *);
void func_0020bd18(Obj7d8 *, s32);
void func_0020c100(Obj7d8 *, s32);

void func_0020d7d8(Obj7d8 *a0) {
    if (func_001f42b8() != 0) {
        if (D_00425BC8->flags & 0x4000) {
            func_001f3708(a0, 6);
            func_0011d768(3);
        } else {
            func_0020bd18(a0, 8);
            if (func_001fe570(a0) != 0) {
                func_001f3708(a0, 6);
            }
        }
    }
    func_0020c100(a0, a0->x28);
    func_001f9438(a0, 0, 0x80, 0xE, a0->x24, 0xF, 0x801EC8C8);
    func_002079c8(a0);
}

typedef struct { u8 pad[0x25]; u8 n; u8 v[0x4e]; } E4BE8;
extern u32 D_003E3D68;
extern u8 *D_00304BE8;
extern s32 D_00641378[];
extern s32 D_00641278[][16];

void func_0020eb98(void) {
    u32 i;
    s32 j;
    for (i = 0; i < D_003E3D68; i++) {
        E4BE8 *e = (E4BE8 *)(D_00304BE8 + D_00304BE8[0x48e + i] * 0x74);
        D_00641378[i] = e->n;
        for (j = 0; j < D_00641378[i]; j++) {
            D_00641278[i][j] = e->v[j];
        }
    }
}

u32 func_0020f260(s32);

void func_0020f290(s32 *a, s32 l, s32 r) {
    s32 i, j, t;
    u32 p;
    p = func_0020f260(a[(l + r) / 2]);
    i = l;
    j = r;
    for (;;) {
        while (func_0020f260(a[i]) < p) i++;
        while (p < func_0020f260(a[j])) j--;
        if (i >= j) break;
        t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
    if (l < i - 1) func_0020f290(a, l, i - 1);
    if (j + 1 < r) func_0020f290(a, j + 1, r);
}
