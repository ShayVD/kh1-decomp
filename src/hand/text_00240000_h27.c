#include "common.h"

#define BREAK() __asm__ volatile("break")

typedef struct { void *dst; s32 id; } Req;

extern s32 D_0046A540;
extern u32 *D_0046A568[];

s32 func_0024ba28(s32 a0, s32 a1, s32 a2, void *a3);
s32 func_001fade0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_0024bb88(s32 a0, s32 a1, f32 *out) {
    f32 v;
    if (func_0024ba28(a0, a1, 0, &v) < 0) {
        BREAK();
    }
    *out = v;
}

void func_0024bbc8(s32 a0, s32 a1, s32 *out) {
    s32 v;
    if (func_0024ba28(a0, a1, 0, &v) < 0) {
        BREAK();
    }
    *out = v;
}

void func_0024bc08(s32 a0, Req *r) {
    while (r->dst != 0) {
        if (func_0024ba28(a0, r->id, 0, r->dst) < 0) {
            BREAK();
        }
        r++;
    }
}

s32 func_0024bc68(u32 a0, u32 a1) {
    u32 *p = D_0046A568[D_0046A540];
    while (((s16 *)p)[1] != -10) {
        if (((s16 *)p)[1] == -1 && a0 == ((*p >> 4) & 0xf) && a1 == ((*p >> 8) & 0xf)) return 1;
        p++;
    }
    return 0;
}

void func_0024c8b8(s32 a0, s16 *p, s32 x, s32 y, s32 dx, s32 a5) {
    s32 i;
    for (i = 0; p[i] >= 0; i++) {
        func_001fade0(a0, x, y, p[i], dx, a5);
        x += dx;
    }
}

void func_0024cde8(u16 *d, u8 *s) {
    s32 i = 0;
    while (s[i] != 0) {
        u32 c = s[i];
        if (c == 1) {
            c = 0;
        } else if (c - 32 < 224) {
            c = c - 32;
        } else {
            if (c == 24) { c = s[i + 1]; c -= 25; c <<= 8; }
            else { c -= 25; c <<= 8; c += s[i + 1]; }
            c += 224;
            i++;
        }
        *d++ = c;
        i++;
    }
}
