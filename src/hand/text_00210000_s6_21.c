#include "common.h"
#include "data/bss_0064.h"
typedef struct Win {
    u8 pad0[0x24]; struct Win *x24; s32 x28; u8 pad2c[0xB4 - 0x2C]; s32 xB4; u16 pB8; s16 xBA;
    u8 padBC[0xCC - 0xBC]; s16 xCC; s16 xCE; s16 xD0; s16 xD2;
} Win;
typedef struct { u16 v; u16 pad; } H4;
extern u8 D_003F3E30[], D_003F3E60[], D_003F3E90[], D_003F3ED0[], D_003F3F00[];
extern u8 D_003F3F30[], D_003F3F60[], D_003F3F90[], D_003F3FC0[];
extern u32 D_003E3D68;
extern u32 D_00642C24; /* src/data/bss_0064.c: s32 D_00642C24 */
extern s32 D_00642C28, D_00642C2C, D_00642C3C, D_00642C44, D_00642C48, D_00642C54;
extern u32 D_00642C58;
extern u16 D_00642C5C, D_00642C60, D_00642C64, D_00642C68, D_00642C6C, D_00642C70;
s32 func_001f42b8(void);
Win *func_001f31a8(void *, s32);
void func_001f3e90(void *, void *);
void func_001f3e20(void *, void *);
void func_001f3dc0(void *);
void func_001ef830(void);
s32 func_001ee5f0(s32);
s32 func_001efbb8(s32);
void func_00206690(void *, s32, s32, s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_00214130(void *, s32, s32, s32, s32, s32);

/* rodata */
void func_00215838(void *a0) {
    Win *w[3];
    s32 t; s32 t2;
    u16 h;
    if (func_001f42b8()) {
        switch (D_00642C24) {
        case 0:
            if ((w[0] = func_001f31a8(D_003F3FC0, 6)) != 0) {
                func_001f3e90(a0, w[0]);
                func_001f3e20(w[0], a0);
                t2 = D_003E3D68 + 1;
                w[0]->xD2 = (u16)D_00642C58 * 16;
                w[0]->xCE = t2;
                w[0]->xCC = t2;
                w[0]->xBA = t2 * 448 - 32;
                if ((w[1] = func_001f31a8(D_003F3F90, 6)) != 0) {
                    func_001f3e90(w[0], w[1]);
                    func_001f3e20(w[1], w[0]);
                    if ((w[2] = func_001f31a8(D_003F3F60, 6)) != 0) {
                        func_001f3e90(w[1], w[2]);
                        func_001f3e20(w[2], w[1]);
                        if (D_00642C58 < D_003E3D68) {
                            w[2]->xD0 = D_00642C5C * 16;
                            w[2]->xD2 = D_00642C60 * 16;
                        } else {
                            w[2]->xD0 = D_00642C64 * 16;
                            w[2]->xD2 = D_00642C68 * 16;
                        }
                        w[2]->x24 = (void*)D_00642C58;
                        func_001f3dc0(w[0]);
                    }
                }
            }
            break;
        case 1:
        case 4:
        l1:
            if ((w[0] = func_001f31a8(D_003F3F60, 6)) != 0) {
                func_001f3e90(a0, w[0]);
                func_001f3e20(w[0], a0);
                if (D_00642C58 < D_003E3D68) {
                    w[0]->xD0 = D_00642C5C * 16;
                    w[0]->xD2 = D_00642C60 * 16;
                } else {
                    w[0]->xD0 = D_00642C64 * 16;
                    w[0]->xD2 = D_00642C68 * 16;
                }
                if (D_00642C24 == 4) {
                    w[0]->xB4 += 448;
                    w[0]->xBA -= 448;
                }
                w[0]->x24 = (void*)D_00642C58;
                w[0]->x28 = 1;
                if ((w[1] = func_001f31a8(D_003F3F30, 6)) != 0) {
                    func_001f3e90(w[0], w[1]);
                    func_001f3e20(w[1], w[0]);
                    if (D_00642C58 < D_003E3D68) {
                        if ((w[2] = func_001f31a8(D_003F3F00, 6)) != 0) {
                            func_001f3e90(w[1], w[2]);
                            func_001f3e20(w[2], w[1]);
                        }
                    }
                    func_001f3dc0(w[0]);
                }
            }
            break;
        case 2:
            if ((w[0] = func_001f31a8(D_003F3ED0, 6)) != 0) {
                func_001f3e90(a0, w[0]);
                func_001f3e20(w[0], a0);
                w[0]->xD2 = D_00642C6C * 16;
                if ((w[1] = func_001f31a8(D_003F3E90, 6)) != 0) {
                    func_001f3e90(w[0], w[1]);
                    func_001f3e20(w[1], w[0]);
                    func_001f3dc0(w[0]);
                }
            }
            break;
        case 3:
            if ((w[0] = func_001f31a8(D_003F3E60, 6)) != 0) {
                func_001f3e90(a0, w[0]);
                func_001f3e20(w[0], a0);
                w[0]->xD2 = D_00642C70 * 16;
                if ((w[1] = func_001f31a8(D_003F3E30, 6)) != 0) {
                    func_001f3e90(w[0], w[1]);
                    func_001f3e20(w[1], w[0]);
                    func_001f3dc0(w[0]);
                }
            }
            break;
        case 5:
            func_001ef830();
            D_00642C24 = 1;
            goto l1;
        }
    }
    switch (D_00642C24) {
    case 0:
        break;
    case 1:
        func_00206690(a0, 0, 83, 11);
        func_00207870(a0, 11, 0, 11, 71, 122, D_00642C28 >= 0 ? func_001ee5f0(D_00642C2C) : func_001efbb8(192));
        break;
    case 2:
        func_00206690(a0, 0, 83, 11);
        func_00207870(a0, 11, 0, 11, 71, 122, D_00642C28 >= 0 ? func_001ee5f0(D_00642C2C) : func_001efbb8(192));
        func_00206690(a0, 133, 83, 26);
        func_00214130(a0, 11, 159, 71, 166, D_00642C3C);
        break;
    case 3:
    case 4:
        func_00206690(a0, 0, 83, 11);
        func_00207870(a0, 11, 0, 11, 71, 122, D_00642C28 >= 0 ? func_001ee5f0(D_00642C2C) : func_001efbb8(192));
        func_00206690(a0, 133, 83, 26);
        func_00214130(a0, 11, 159, 71, 166, D_00642C3C);
        func_00206690(a0, 325, 83, 26);
        switch (D_00642C44) {
        case 1: t = 187; break;
        case 0: t = (D_00642C3C & 0x80) ? 185 : 186; break;
        case 2: default: t = 188; break;
        }
        func_00207830(a0, 11, 2, 351, 71, 122, t);
        func_00206690(a0, 473, 83, 39);
        break;
    case 5:
        func_00206690(a0, 0, 83, 11);
        func_00207870(a0, 11, 0, 11, 71, 122, D_00642C28 >= 0 ? func_001ee5f0(D_00642C2C) : func_001efbb8(192));
        func_00206690(a0, 133, 83, 26);
        func_00214130(a0, 11, 159, 71, 166, D_00642C3C);
        func_00206690(a0, 325, 83, 26);
        switch (D_00642C44) {
        case 1: t = 187; break;
        case 0: t = (D_00642C3C & 0x80) ? 185 : 186; break;
        case 2: default: t = 188; break;
        }
        func_00207830(a0, 11, 2, 351, 71, 122, t);
        func_00206690(a0, 473, 83, 39);
        switch (D_00642C44) {
        case 1:
            func_00206690(a0, 0, 111, 159);
            func_00214130(a0, 11, 159, 99, 166, D_00642C54);
            func_00206690(a0, 325, 111, 187);
            break;
        case 0:
            break;
        case 2:
        default:
            func_00206690(a0, 0, 111, 11);
            switch (D_00642C48) {
            case 1: t = 194; break;
            case 0: t = 193; break;
            case 2: default: t = 195; break;
            }
            func_00207830(a0, 11, 2, 11, 99, 122, t);
            func_00206690(a0, 133, 111, 379);
            break;
        }
        break;
    }
}
#include "data/data_003F.h"
