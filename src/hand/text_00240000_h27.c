#include "common.h"
#include "data/bss_0066.h"

#define BREAK() __asm__ volatile("break")

typedef struct { void *dst; s32 id; } Req;

extern s32 D_0046A540;
#include "data/pieces/D_0046A568.h"
extern s32 D_00669A60;
extern s16 D_00669A40[];

typedef struct { s32 a; s8 s[92]; } Slot;
typedef struct { u8 pad[0x60]; Slot slot[1]; } SaveHdr;

SaveHdr *func_001bc4e0(void);
void func_0011ef10(s32, void *);
void func_0024d138(void);
u8 *func_001eafd8(void);
void func_0024d1c8(s16 *buf, s32 a1, s32 a2, s32 a3);
s32 func_0025dd48(s32 a0, s32 a1, s32 a2, s32 a3, void *a4, s32 a5);

extern s32 D_0046A618;
extern s32 D_0046A614;

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

void func_0024ce80(u8 *d, s16 *s) {
    s32 i, n = 0;
    s32 c;
    for (i = 0; i < 8 && (c = *s) >= 0; i++) {
        if (c == 0) c = 1;
        else { c += 32; if (c >= 256) { c += 0x1800; d[n++] = c >> 8; } }
        s++;
        d[n++] = c;
    }
    d[n] = 0;
}

void func_0024cf00(void) {
    Slot *p = &func_001bc4e0()->slot[D_00669A60];
    s32 i;
    for (i = 0; p->s[i + 48] != 0; i++) p->s[i + 48] = 0;
    func_0024ce80((u8 *)p + 52, D_00669A40);
}

void func_0024d418(void) {
    s16 buf[16];
    s32 i;
    func_0011ef10(0x2BFE8, func_0024d138);
    for (i = 0; i < 9; i++) buf[i] = -1;
    func_0024cde8(buf, func_001eafd8());
    func_0024d1c8(buf, -1, 0, 1);
}

void func_0024d5d0(s32 n) {
    s32 i;
    for (i = 0; i < n; i++) {
        s32 *p = &D_0046A618;
        (*p)++;
    }
}

s32 func_0024dad0(s32 a0, s32 n) {
    u32 v;
    func_0025dd48(a0, 0x4802, 0, 0, 0, 0);
    D_0046A614 = 60;
    v = 0;
    if (func_0025dd48(a0, 0x480A, 0, 0, &v, 4) != 0) return 0;
    D_0046A614 = 70;
    if ((s32)(v >> 18) < n) return 0;
    return 1;
}
#include "data/bss_0066_mixed.h"
#include "data/data_0046.h"
