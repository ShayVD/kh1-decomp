#include "common.h"
#include "data/bss_0064.h"
typedef struct N { u8 pad[0x10]; struct N *x10; u8 pad14[0x14]; s32 x28; u8 pad2c[0xba - 0x2c]; s16 xba; u8 padbc[0x10]; s16 xcc; s16 xce; } N;
#include "data/pieces/D_00425BC8.h"
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
void func_001fd858(N *);
void func_0020bd18(N *, s32);
s32 func_001fd518(N *);
s32 func_001fe5a0(N *);
void func_00207870(N *, s32, s32, s32, s32, s32, s32);

extern s32 D_00642C24, D_00642C28, D_00642C48, D_00642C70;
void func_001f3d58(N *, s32);
void func_00213fb0(void);
void func_00207830(N *, s32, s32, s32, s32, s32, s32);
void func_002143e0(N *a0) {
    s32 sel;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a0);
            func_0011d768(3);
            D_00642C24 = 2;
        } else {
            func_001fd858(a0);
            func_0020bd18(a0, 8);
            D_00642C70 = func_001fd518(a0);
            if (func_001fe5a0(a0)) {
                if (D_00642C70 == 1 && D_00642C28 == -1) {
                    func_0011d768(4);
                } else {
                    func_0011d768(74);
                    func_001f3d58(a0, 5);
                    func_001f3758(a0);
                    D_00642C48 = D_00642C70;
                    D_00642C24 = 5;
                    func_00213fb0();
                }
            }
        }
    }
    sel = func_001fd518(a0);
    func_00207830(a0, sel == 0, 2, 0, 0, 122, 193);
    { s32 k; if (D_00642C28 != -1) k = sel == 1; else k = sel == 1 ? 3 : 2; func_00207830(a0, k, 2, 0, 28, 122, 194); }
    func_00207830(a0, sel == 2, 2, 0, 56, 122, 195);
}

extern s32 D_00642C94, D_00642CA0, D_00642CC8, D_00642CD0, D_00642CD4;
extern s32 D_00642CA8[];
s32 func_001fe570(N *);
s32 func_001efbb8(s32);
s32 func_00132f88(s32);
void func_0013c270(s32, s32);
void func_002163e0(N *a0) {
    s32 i, y, sel;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(a0);
            func_0011d768(3);
            D_00642C94 = 1;
        } else {
            func_001fd858(a0);
            func_0020bd18(a0, 8);
            D_00642CD4 = func_001fd518(a0);
            if (func_001fe570(a0)) {
                func_001f3d58(a0, 5);
                func_001f3758(a0);
                D_00642C94 = 3;
                if (D_00642CD4 == D_00642CC8 - 1) {
                    D_00642CA0 = func_001efbb8(212);
                    func_0013c270(D_00642CD0, -1);
                } else {
                    s32 *q = D_00642CA8;
                    s32 *p = &D_00642CA0;
                    s32 v = func_00132f88(q[D_00642CD4]);
                    *p = v;
                    func_0013c270(D_00642CD0, q[D_00642CD4]);
                }
            }
        }
    }
    sel = func_001fd518(a0);
    for (i = 0, y = 0; i < D_00642CC8; i++, y += 28) {
        s32 t;
        if (i == D_00642CC8 - 1) t = func_001efbb8(212);
        else t = func_00132f88(D_00642CA8[i]);
        func_00207870(a0, i == sel, 2, 0, y, 122, t);
    }
}
#include "data/data_003F.h"
