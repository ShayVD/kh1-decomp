/* The bit sets of the block D_003F34B8 (docs/modules.md "Session 38"),
 * 0x00206e28-0x00207428: for each set a clear-all, then clear / set / test
 * bit n (word n / 32, bit n % 32): b48 (64 bits), b56, b60 (32 each), b64
 * (320), b104, b108 and b112 (only its first word is cleared, but the bit
 * functions reach all four).  The block also holds the munny (x1c,
 * src/game/gamedata.c). */
#include "common.h"
#include "data/pieces/D_003F34B8.h"

void func_00206e28(void) {
    s32 i;
    for (i = 0; i < 2; i++) D_003F34B8->b48[i] = 0;
}

void func_00206e60(s32 n) {
    D_003F34B8->b48[n / 32] &= ~(1 << n);
}

void func_00206ea8(s32 n) {
    D_003F34B8->b48[n / 32] |= 1 << n;
}

u32 func_00206ee8(s32 n) {
    return D_003F34B8->b48[n / 32] & (1 << n);
}

void func_00206f20(void) {
    D_003F34B8->b56[0] = 0;
}

void func_00206f30(s32 n) {
    D_003F34B8->b56[n / 32] &= ~(1 << n);
}

void func_00206f78(s32 n) {
    D_003F34B8->b56[n / 32] |= 1 << n;
}

u32 func_00206fb8(s32 n) {
    return D_003F34B8->b56[n / 32] & (1 << n);
}

void func_00206ff0(void) {
    D_003F34B8->b60[0] = 0;
}

void func_00207000(s32 n) {
    D_003F34B8->b60[n / 32] &= ~(1 << n);
}

void func_00207048(s32 n) {
    D_003F34B8->b60[n / 32] |= 1 << n;
}

u32 func_00207088(s32 n) {
    return D_003F34B8->b60[n / 32] & (1 << n);
}

void func_002070c0(void) {
    u32 *p;
    s32 n;

    n = 9;
    p = D_003F34B8->b64;
    do {
        n -= 1;
        *p = 0;
        p += 1;
    } while (n >= 0);
}

void func_002070f8(s32 n) {
    D_003F34B8->b64[n / 32] &= ~(1 << n);
}

void func_00207140(s32 n) {
    D_003F34B8->b64[n / 32] |= 1 << n;
}

u32 func_00207180(s32 n) {
    return D_003F34B8->b64[n / 32] & (1 << n);
}

void func_002071b8(void) {
    D_003F34B8->b104[0] = 0;
}

void func_002071c8(s32 n) {
    D_003F34B8->b104[n / 32] &= ~(1 << n);
}

void func_00207210(s32 n) {
    D_003F34B8->b104[n / 32] |= 1 << n;
}

u32 func_00207250(s32 n) {
    return D_003F34B8->b104[n / 32] & (1 << n);
}

void func_00207288(void) {
    D_003F34B8->b108[0] = 0;
}

void func_00207298(s32 n) {
    D_003F34B8->b108[n / 32] &= ~(1 << n);
}

void func_002072e0(s32 n) {
    D_003F34B8->b108[n / 32] |= 1 << n;
}

u32 func_00207320(s32 n) {
    return D_003F34B8->b108[n / 32] & (1 << n);
}

void func_00207358(void) {
    D_003F34B8->b112[0] = 0;
}

void func_00207368(s32 n) {
    D_003F34B8->b112[n / 32] &= ~(1 << n);
}

void func_002073b0(s32 n) {
    D_003F34B8->b112[n / 32] |= 1 << n;
}

u32 func_002073f0(s32 n) {
    return D_003F34B8->b112[n / 32] & (1 << n);
}
