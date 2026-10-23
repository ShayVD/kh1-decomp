/* The item shop's menu, part 4 (docs/modules.md "Session 43"), 0x002316f8-0x00231908:
 * the opener and its wrappers.  func_00231740(mode, list, on_cursor, on_choice) opens one
 * list by itself (D_003F7A64 = 1, the task func_002316f8; D_003F7A68 = 1
 * lets the list take input): mode 0 buys the goods list (D_00646A08 the
 * count, D_00646A0C the items after it) in D_003F78B0 (shopbuy.c), 1 sells
 * (D_003F79E0, shopsell.c), 2 and 3 buy and sell the second kind of goods
 * (D_003F7A10 / D_003F7A40, shopgummi.c, D_00647640 = func_001eeb20()).
 * D_00646A00 / D_00646A04 take the two hooks; most likely the shop's VM
 * (src/shop/shop.c) calls it.  func_00231908 / func_00231930 open the buy
 * and sell lists with no hooks, func_00231958 closes the list (D_00646A10),
 * func_002319b0 / func_002319c0 clear D_003F7A64.  Not proved by a boot. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_003F7A68.h"

extern s32 D_003F7A64;
extern s32 D_00646A00, D_00646A04;
extern s32 *D_00646A08; /* src/data/bss_0064.c: u16 *D_00646A08 */
extern void *D_00646A10;
extern s32 D_00646A28;
extern s32 D_00647640, D_00647644;
extern u8 D_003F78B0[], D_003F79E0[], D_003F7A10[], D_003F7A40[];

void func_0011d768(s32);
s16 *func_0011ef10(s32, void *);
s32 func_001eeb20(void);
void func_001ef830(void);
void func_001f3110(void);
void func_001f3840(void *);
void *func_001f31a8(void *, s32);
s32 func_001f40c8(void);
void func_001f82b0(void);
void func_0020b998(void);
void func_0020bb90(s32, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0022eee0(s32);
void func_0022fc88(s32);
void func_00231740(s32, s32 *, s32, s32);

s32 func_002316f8(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    D_003F7A64 = 0;
    return 4;
}

void func_00231740(s32 mode, s32 *p, s32 a2, s32 a3) {
    if (D_003F7A64 != 0) return;
    func_001f3110();
    D_003F7A64 = 1;
    D_003F7A68 = 1;
    func_001ef830();
    func_0022eee0(-1);
    func_0022fc88(-1);
    D_00646A00 = a2;
    D_00646A04 = a3;
    D_00646A28 = 1;
    D_00647644 = 0;
    func_0011d768(16);
    func_0020bb90(544, -32);
    func_0020bda8(16);
    switch (mode) {
    case 0:
        D_00646A08 = p;
        D_00646A0C = p + 1;
        D_00646A10 = func_001f31a8(D_003F78B0, 6);
        break;
    case 1:
        D_00646A10 = func_001f31a8(D_003F79E0, 6);
        break;
    case 2:
        D_00646A08 = p;
        D_00646A0C = p + 1;
        D_00647640 = func_001eeb20();
        D_00646A10 = func_001f31a8(D_003F7A10, 6);
        break;
    case 3:
        D_00647640 = func_001eeb20();
        D_00646A10 = func_001f31a8(D_003F7A40, 6);
        break;
    }
    func_0011ef10(0x2BF84, func_002316f8);
}

void func_00231908(s32 *arg0) {
    func_00231740(0, arg0, 0, 0);
}

void func_00231930(s32 *arg0) {
    func_00231740(1, arg0, 0, 0);
}

void func_00231958(void) {
    func_001f3840(D_00646A10);
    func_0020be10(0x10);
}

void func_00231980(void) {
    func_00231958();
}

void func_00231998(void) {
    func_00231958();
}

void func_002319b0(void) {
    D_003F7A64 = 0;
}

void func_002319c0(void) {
    D_003F7A64 = 0;
}
