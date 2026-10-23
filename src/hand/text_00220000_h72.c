#include "common.h"
#include "data/bss_0064.h"

typedef struct O98 {
    u8 pad[0xc];
    struct O98 *xc;
    s32 x10;
    u8 pad14[0x24 - 0x14];
    union { s32 i; u16 h; } x24;
    u8 p0[0x90 - 0x28];
    s32 x90;
    u8 p1[0xa0 - 0x94];
    f32 xa0;
    u8 p2[0xb0 - 0xa4];
    s32 xb0;
    s32 xb4;
    u8 p3[0xba - 0xb8];
    s16 xba;
    s16 xbc;
    s16 xbe;
    s16 xc0;
    s16 xc2;
    s16 xc4;
    s16 xc6;
    s16 xc8;
    s16 xca;
    s16 xcc;
    s16 xce;
    u8 p5[0xd2 - 0xd0];
    s16 xd2;
    u8 p6[0xd8 - 0xd4];
    s16 xd8;
    s16 xda;
} O98;
void func_0011d768(s32);
#include "data/pieces/D_00425BC8.h"
extern s32 D_003F6568[];
s32 func_001f42b8(void);
void func_001fd858(void *);
s32 func_001fd518(void *);
s32 func_001fe570(void *);
#include "vm/script_vm.h"
void func_001fdfd0(void *);
s32 func_001fd538(void *);
#include "data/types/text_00220000_h72.h"
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
extern s32 D_006469B0;
extern s32 D_006469B4;
extern u8 D_003F7210[];
void func_001f3708(void *, s32);
void func_0020bc48(s32, s32, s32);
void func_002193a8(s32);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
s32 func_001fa808(void *, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00219370(s32);
extern s32 D_003F7240[];
#include "data/pieces/D_003F7238.h"
void func_00219320(s32);
void func_00209820(void *, s32, s32, s32, void *);

void func_0022c2a0(O98 *a0) {
    s32 s, x, y;
    if (func_001f42b8()) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0 = D_006469B0 - 1;
        } else {
            func_001fdfd0(a0);
            x = a0->xb0 + a0->xda * 96 + (u32)(a0->xbe - 0x7000);
            y = a0->xb4 + a0->xc4 * a0->xd2 / 16;
            func_0020bc48(8, (s32)(x + a0->xc2 - a0->xc6) >> 4, (y + a0->xc0 - 0x7400) >> 4);
            if (func_001fe570(a0)) {
                func_001f3708(a0, 11);
                func_002193a8(func_001fd538(a0));
                D_006469B4 = D_006469B0;
                D_006469B0 = D_006469B0 + 1;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80c2726e, 0x80c2726e);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80c2726e, 0x80c2726e);
    func_001fa808(a0, 161, 475, 15, 0x80e6e6e6);
    s = func_001fd538(a0);
    func_002078f0(a0, s == 0, 2, 2, 163, 174, 90, 208, 477);
    func_002078f0(a0, s == 1, 2, 2, 259, 174, 90, 304, 478);
}

void func_0022c4e8(O98 *a0) {
    s32 s, x, y;
    if (func_001f42b8()) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0 = D_006469B0 - 1;
        } else {
            func_001fdfd0(a0);
            x = a0->xb0 + a0->xda * 96 + (u32)(a0->xbe - 0x7000);
            y = a0->xb4 + a0->xc4 * a0->xd2 / 16;
            func_0020bc48(8, (s32)(x + a0->xc2 - a0->xc6) >> 4, (y + a0->xc0 - 0x7400) >> 4);
            if (func_001fe570(a0)) {
                func_001f3708(a0, 11);
                func_00219370(func_001fd538(a0));
                D_006469B4 = D_006469B0;
                D_006469B0 = D_006469B0 + 1;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80c2726e, 0x80c2726e);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80c2726e, 0x80c2726e);
    func_001fa808(a0, 161, 89, 15, 0x80e6e6e6);
    s = func_001fd538(a0);
    func_002078f0(a0, s == 0, 2, 2, 163, 174, 90, 208, 46);
    func_002078f0(a0, s == 1, 2, 2, 259, 174, 90, 304, 47);
}

void func_0022c730(O98 *a0) {
    s32 i, y;
    if (func_001f42b8()) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0 = D_006469B0 - 1;
        } else {
            func_0020bc48(8, (a0->xb0 + a0->xc2 + a0->xbe - 0x7000) >> 4,
                          (a0->xb4 + a0->xc4 * a0->xd2 / 16 + a0->xc0 - 0x7400) >> 4);
            func_001fd858(a0);
            if (func_001fe570(a0)) {
                func_001f3708(a0, 11);
                func_00219320(func_001fd518(a0));
                D_006469B4 = D_006469B0;
                D_006469B0 = D_006469B0 + 1;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80c2726e, 0x80c2726e);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80c2726e, 0x80c2726e);
    func_001fa808(a0, 161, 466, 15, 0x80e6e6e6);
    y = 166;
    for (i = 0; i < 2; i++) {
        func_001f9438(a0, 0, 131, y, D_003F7240[i], 15, 0x80e6e6e6);
        y += 28;
    }
    func_00209820(a0, 2, 2, 71, D_003F7238);
}

/* needs make: uses rodata */
#include "menu/partymdl.h"

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_003F63C0[];
extern u8 D_003F63F0[];
extern u8 D_003F6420[];
extern u8 D_003F6450[];
extern u8 D_003F6480[];
extern u8 D_003F64B0[];
extern u8 D_003F64E0[];
extern u8 D_003F6510[];
extern u8 D_003F6540[];
s32 D_003F6568[0xa] ALIGNED(8) = {
    (s32)D_003F63C0, (s32)D_003F63F0, (s32)D_003F6420, (s32)D_003F6450,
    (s32)D_003F6480, (s32)D_003F64B0, (s32)D_003F64E0, (s32)D_003F6510,
    (s32)D_003F6540, 0,
};
#include "data/data_003F.h"
#include "data/data_003E.h"
#include "data/pieces/D_003F6DF0.h"
