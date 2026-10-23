/* The settings block's accessors (docs/modules.md "Session 41"),
 * 0x00219128-0x00219440: D_003F34B8 (S34B8_3f34b8, D_003F34B8.h) holds
 * seven settings, f0 f4 f8 f10 f14 f18 and f2c, numbered 0-6 by
 * func_00219158 (get) and func_002191f0 (set); func_00219f98, the next
 * page's input handler, steps them by that number between 0 and
 * D_003F4C18[n], so most likely the config page's options (not proved by a
 * boot).  func_00219128 resets them (gamedata.c's new game), and each has a
 * get, a wrapper and a set below.  fc has no accessor (func_00219330 /
 * func_00219338 / func_00219340 stand in its place).  func_00219428 tests
 * D_002B6478 (2). */
#include "common.h"
#include "menu/settings.h"
#include "data/data_002B.h"
#include "data/pieces/D_003F34B8.h"

void func_00219128(void) {
    S34B8_3f34b8 *p = D_003F34B8;
    p->f2c = 1;
    p->f8 = 0;
    p->f4 = 0;
    p->fc = 0;
    p->f10 = 0;
    p->f14 = 0;
    p->f18 = 0;
    p->f0 = 0;
}

s32 func_00219158(s32 a0) {
    switch (a0) {
    case 0: return D_003F34B8->f0;
    case 1: return D_003F34B8->f4;
    case 2: return D_003F34B8->f8;
    case 3: return D_003F34B8->f10;
    case 4: return D_003F34B8->f14;
    case 5: return D_003F34B8->f18;
    case 6:
    default: return D_003F34B8->f2c;
    }
}

void func_002191f0(s32 a0, s32 a1) {
    switch (a0) {
    case 0: D_003F34B8->f0 = a1; break;
    case 1: D_003F34B8->f4 = a1; break;
    case 2: D_003F34B8->f8 = a1; break;
    case 3: D_003F34B8->f10 = a1; break;
    case 4: D_003F34B8->f14 = a1; break;
    case 5: D_003F34B8->f18 = a1; break;
    case 6:
    default: D_003F34B8->f2c = a1; break;
    }
}

s32 func_00219288(void) {
    return D_003F34B8->f0;
}

void func_00219298(void) {
    func_00219288();
}

void func_002192b0(s32 arg0) {
    D_003F34B8->f0 = arg0;
}

s32 func_002192c0(void) {
    return D_003F34B8->f4;
}

void func_002192d0(void) {
    func_002192c0();
}

void func_002192e8(s32 arg0) {
    D_003F34B8->f4 = arg0;
}

s32 func_002192f8(void) {
    return D_003F34B8->f8;
}

void func_00219308(void) {
    func_002192f8();
}

void func_00219320(s32 arg0) {
    D_003F34B8->f8 = arg0;
}

s32 func_00219330(void) {
    return 0;
}

s32 func_00219338(void) {
    return 0;
}

void func_00219340(void) {
}

s32 func_00219348(void) {
    return D_003F34B8->f10;
}

void func_00219358(void) {
    func_00219348();
}

void func_00219370(s32 arg0) {
    D_003F34B8->f10 = arg0;
}

s32 func_00219380(void) {
    return D_003F34B8->f14;
}

void func_00219390(void) {
    func_00219380();
}

void func_002193a8(s32 arg0) {
    D_003F34B8->f14 = arg0;
}

s32 func_002193b8(void) {
    return D_003F34B8->f18;
}

void func_002193c8(void) {
    func_002193b8();
}

void func_002193e0(s32 arg0) {
    D_003F34B8->f18 = arg0;
}

s32 func_002193f0(void) {
    return D_003F34B8->f2c;
}

void func_00219400(void) {
    func_002193f0();
}

void func_00219418(s32 arg0) {
    D_003F34B8->f2c = arg0;
}

s32 func_00219428(void) {
    return D_002B6478 == 2;
}
