#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"
typedef struct Obj7 { u8 pad[0x10]; struct Obj7 *x10; u8 p14[0x10]; struct Obj7 *x24; s32 x28; u8 p2c[0xBA - 0x2C]; s16 xba; u8 pbc[0xCC - 0xBC]; s16 xcc; s16 xce; s16 xd0; s16 xd2; } Obj7;
#include "data/types/text_00210000_b14_p.h"
typedef Sub_304be8 Sub;
typedef W606Mem_304be8 Rec74;
#include "data/types/text_00210000_b14.h"
#include "data/pieces/D_003F34B8.h"
#include "data/pieces/D_003E3D68.h"
extern PN D_003F40F8[];
extern s32 D_003F4368[];
extern s32 D_003F4380[];
extern s32 *D_003F43C8[];
extern u8 D_003F4430[];
extern u8 D_003F4460[];
extern u8 D_003F44A0[];
extern s32 D_003F44C8[];
extern u8 D_003F44E0[];
extern s32 D_003F45A8[];
extern u8 D_003F45C0[];
extern u8 D_003F45F0[];
extern u8 D_003F4620[];
extern Sub *D_00642C30; /* src/data/bss_0064.c: s32 D_00642C30 */
s32 D_00642C34 ALIGNED(4);
s32 D_00642C38 ALIGNED(8);
extern s32 D_00642C3C;
s32 D_00642C40 ALIGNED(16);
s32 D_00642C4C ALIGNED(4);
s32 D_00642C50 ALIGNED(16);
extern s32 D_00642C6C;
extern s32 D_00642C94;
extern s32 D_00642C98;
extern s32 D_00642C9C;
extern s32 D_00642CA0;
extern u16 D_00642CC8; /* src/data/bss_0064.c: s32 D_00642CC8 */
extern s32 D_00642CCC;
extern u16 D_00642CD0; /* src/data/bss_0064.c: s32 D_00642CD0 */
extern u16 D_00642CD4; /* src/data/bss_0064.c: s32 D_00642CD4 */

s32 func_00132f88(s32);
s32 func_0013c288(s32);
s32 func_00170dd8(s32, s32);
s32 func_001ee5f0(s32);
s32 func_001efbb8(s32);
s32 func_001f42b8(void *);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
void *func_001f31a8(u8 *, s32);
void func_001f3dc0(void *);
void func_001f3e48(void *, void *);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_001ff488(void *, s32, s32, s32, s32, s32);
void func_00206690(void *, s32, s32, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_00207830(void *, s32, s32, s32, s32, s32, s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);

static inline s32 col(s32 x, s32 y) {
    if (x < y) return 0x80FC927A;
    if (x == y) return 0x80808080;
    return 0x806E6EFF;
}

#define D_00642C3C (*(u32 *)&D_00642C3C)
#define BYTE D_00642C30->name[D_00642C34]
#undef D_00642C3C
#undef BYTE

#define D_00642C6C (*(u16 *)&D_00642C6C)
#undef D_00642C6C

#define D_00642C6C (*(u16 *)&D_00642C6C)
#undef D_00642C6C

void func_00217490(void *a) {
    s32 i, y, t, k, n, id, c, r;
    s32 *p;
    if (D_00642CCC == 0) {
        y = 0;
        for (i = 0; i < 3; i++) {
            func_00207830(a, 2, 2, 0, y, 180, D_003F45A8[i]);
            func_001f9438(a, 0, 86, y + 5, 51, 15, 0x20E6E6E6);
            t = func_00132f88(func_0013c288(i));
            if (!t) t = func_001efbb8(212);
            func_001f94f0(a, 0, 96, y + 5, t, 15, 0x20E6E6E6);
            y += 28;
        }
    } else {
        k = D_00304BE8->x48e[D_00642CCC];
        n = D_003F40F8[k].n;
        p = D_003F40F8[k].p;
        func_00207830(a, 2, 2, 0, 0, 342, D_003F4368[D_003F34B8->a[k]]);
        func_001ff488(a, 0, 28, 342, n * 28 + 10, 0x40000000);
        y = 57;
        for (i = 0; i < n; i++) {
            id = p[i];
            if (k == 2 && id == 7) c = 255;
            else c = D_003F4380[id];
            func_002066b0(a, 12, y, 318, 0x20E6E6E6, 0x20E6E6E6);
            func_001f9438(a, 0, 12, y - 15, c, 15, 0x20E6E6E6);
            r = func_00170dd8(k, id);
            func_001f9438(a, 0, 191, y - 15, D_003F43C8[id][2 - r], 15, 0x20E6E6E6);
            y += 26;
        }
    }
}

void func_00217b38(void *a) {
    Obj7 *o[3];
    s32 *p;
    if (func_001f42b8(a)) {
        p = &D_00642C94;
        switch (*p) {
        case 0:
            if ((o[0] = func_001f31a8(D_003F4620, 6))) {
                u32 *n;
                func_001f3e48(o[0], a);
                n = &D_003E3D68;
                o[0]->xcc = o[0]->xce = *n;
                o[0]->xba = *n * 448 - 32;
                o[0]->xd2 = D_00642CCC << 4;
                if ((o[1] = func_001f31a8(D_003F45F0, 6))) {
                    func_001f3e48(o[1], o[0]);
                    if ((o[2] = func_001f31a8(D_003F45C0, 6))) {
                        func_001f3e48(o[2], o[1]);
                        func_001f3dc0(o[0]);
                    }
                }
            }
            break;
        case 1:
        case1:
            if ((o[0] = func_001f31a8(D_003F44E0, 6))) {
                func_001f3e48(o[0], a);
                o[0]->xd2 = D_00642CD0 << 4;
                if ((o[1] = func_001f31a8(D_003F44A0, 6))) {
                    func_001f3e48(o[1], o[0]);
                    func_001f3dc0(o[0]);
                }
            }
            break;
        case 2:
            if ((o[0] = func_001f31a8(D_003F4460, 6))) {
                func_001f3e48(o[0], a);
                o[0]->xcc = o[0]->xce = D_00642CC8;
                o[0]->xd2 = D_00642CD4 << 4;
                if ((o[1] = func_001f31a8(D_003F4430, 6))) {
                    func_001f3e48(o[1], o[0]);
                    func_001f3dc0(o[0]);
                }
            }
            break;
        case 3:
            if (D_00642CCC == 0) {
                *p = 1;
                goto case1;
            }
            break;
        }
    }
    switch (D_00642C94) {
    default:
    case 0:
        break;
    case 1:
        func_00206690(a, 0, 83, 11);
        func_00207870(a, 11, 0, 11, 71, 122, func_001ee5f0(D_00642C98));
        break;
    case 2:
        func_00206690(a, 0, 83, 11);
        func_00207870(a, 11, 0, 11, 71, 122, func_001ee5f0(D_00642C98));
        func_00206690(a, 133, 83, 26);
        func_00207830(a, 11, 2, 159, 71, 166, D_003F44C8[D_00642C9C]);
        break;
    case 3:
        func_00206690(a, 0, 83, 11);
        func_00207870(a, 11, 0, 11, 71, 122, func_001ee5f0(D_00642C98));
        func_00206690(a, 133, 83, 26);
        func_00207830(a, 11, 2, 159, 71, 166, D_003F44C8[D_00642C9C]);
        func_00206690(a, 325, 83, 26);
        func_00207870(a, 11, 2, 351, 71, 122, D_00642CA0);
        func_00206690(a, 473, 83, 39);
        break;
    }
}
#include "data/data_003F.h"
#include "data/pieces/D_003F40D0.h"
