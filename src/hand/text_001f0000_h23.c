#include "common.h"
#include "data/bss_0064.h"

#include "data/types/text_001f0000_h23.h"
#include "data/pieces/D_003F34B8.h"
extern s32 D_00640E00[];
extern s32 D_00640E20;
extern s32 D_00640E24;
extern s32 D_00640E28;

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

void func_00206f30(s32 n) {
    D_003F34B8->b56[n / 32] &= ~(1 << n);
}

void func_00206f78(s32 n) {
    D_003F34B8->b56[n / 32] |= 1 << n;
}

u32 func_00206fb8(s32 n) {
    return D_003F34B8->b56[n / 32] & (1 << n);
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

void func_002070f8(s32 n) {
    D_003F34B8->b64[n / 32] &= ~(1 << n);
}

void func_00207140(s32 n) {
    D_003F34B8->b64[n / 32] |= 1 << n;
}

u32 func_00207180(s32 n) {
    return D_003F34B8->b64[n / 32] & (1 << n);
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

void func_00207298(s32 n) {
    D_003F34B8->b108[n / 32] &= ~(1 << n);
}

void func_002072e0(s32 n) {
    D_003F34B8->b108[n / 32] |= 1 << n;
}

u32 func_00207320(s32 n) {
    return D_003F34B8->b108[n / 32] & (1 << n);
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

void func_00207598(void) {
    s32 i;
    D_00640E24 = 0;
    for (i = 0; i < D_00640E20; i++) {
        if (D_00640E28 == D_00640E00[i]) D_00640E24 = i;
    }
}

#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
