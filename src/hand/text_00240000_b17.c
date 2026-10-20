#include "common.h"
#include "data/bss_0066.h"

/* UI quad packet builder (ttlib/ui.c). Ui is the 0xC0-byte element read by
 * func_0024ac68: rect at +0x0, uv rect at +0x10, 4x4 colours at +0x20,
 * flags at +0x60. Both setxy expansions are cross-jumped into one tail. */
typedef union {
    struct { u8 pad[0x60]; u64 flags; } h;
    struct { s32 r[4]; s32 t[4]; s32 m[4][4]; } s;
} Ui;
typedef struct {
    u64 unk0, unk8, unk10, unk18;
    s32 uv[4][4];
    s32 m[4][4];
    s32 xy[4][4];
} Pk;
void func_0024a0e0(Ui *, s32 *);
void func_0024a300(Ui *, s32 (*)[4]);
void func_0024a588(Ui *, s32 *);

static inline void inl_0024a6b8_setxy(Pk *p, s32 rx, s32 ry, s32 rw, s32 rh) {
    s32 x0, y0, x1, y1;
    y1 = ((ry + rh) << 4) + 0x7400;
    x0 = (rx << 4) + 0x7000;
    y0 = (ry << 4) + 0x7400;
    x1 = ((rx + rw) << 4) + 0x7000;
    p->xy[0][0] = x0; p->xy[0][1] = y0; p->xy[0][2] = -256; p->xy[0][3] = 0;
    p->xy[1][0] = x0; p->xy[1][1] = y1; p->xy[1][2] = -256; p->xy[1][3] = 0;
    p->xy[2][0] = x1; p->xy[2][1] = y0; p->xy[2][2] = -256; p->xy[2][3] = 0;
    p->xy[3][0] = x1; p->xy[3][1] = y1; p->xy[3][2] = -256; p->xy[3][3] = 0;
}

void func_0024a6b8(Pk *p, Ui *u, u64 x) {
    s32 t[4];
    s32 r[4];
    s32 t2[4][4];
    s32 i, j;
    p->unk0 = x;
    p->unk8 = 6;
    p->unk10 = x;
    p->unk18 = 6;
    if ((u->h.flags & 10) == 10) {
        func_0024a0e0(u, t);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                p->m[i][j] = t[j];
    } else if ((u->h.flags & 0xC0) == 0xC0) {
        func_0024a300(u, t2);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                p->m[i][j] = t2[i][j];
    } else if (*(u32 *)&u->h.flags & 0x20) {
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                p->m[i][j] = u->s.m[i][j];
    } else {
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                p->m[i][j] = u->s.m[0][j];
    }
    if ((u->h.flags & 20) == 20) {
        func_0024a588(u, r);
        inl_0024a6b8_setxy(p, r[0], r[1], r[2], r[3]);
    } else {
        inl_0024a6b8_setxy(p, u->s.r[0], u->s.r[1], u->s.r[2], u->s.r[3]);
    }
    if (u->s.t[0] < u->s.t[2]) {
        p->uv[0][0] = u->s.t[0] * 16 + 8;
        p->uv[1][0] = u->s.t[0] * 16 + 8;
        p->uv[2][0] = u->s.t[2] * 16 + 24;
        p->uv[3][0] = u->s.t[2] * 16 + 24;
    } else {
        p->uv[0][0] = u->s.t[0] * 16 + 8;
        p->uv[1][0] = u->s.t[0] * 16 + 8;
        p->uv[2][0] = u->s.t[2] * 16 - 8;
        p->uv[3][0] = u->s.t[2] * 16 - 8;
    }
    if (u->s.t[1] < u->s.t[3]) {
        p->uv[0][1] = u->s.t[1] * 16 + 8;
        p->uv[1][1] = u->s.t[3] * 16 + 24;
        p->uv[2][1] = u->s.t[1] * 16 + 8;
        p->uv[3][1] = u->s.t[3] * 16 + 24;
    } else {
        p->uv[0][1] = u->s.t[1] * 16 + 8;
        p->uv[1][1] = u->s.t[3] * 16 - 8;
        p->uv[2][1] = u->s.t[1] * 16 + 8;
        p->uv[3][1] = u->s.t[3] * 16 - 8;
    }
}

/* needs make: uses rodata (local initialisers from D_00491908/D_00491910) */
extern s32 D_00669A70;
extern s32 D_00669A78;
extern s32 D_00669A5C;
extern s32 D_0046A540;
extern s16 D_0046A580[], D_0046A588[], D_0046A590[], D_0046A598[], D_0046A5A0[];
extern s16 D_0046A5A8[];
extern u8 D_0046A080[];
extern u8 D_0046A0C0[];
void func_00206130(void *, s32, s32, s32, s32, s32);
void func_0024c8b8(void *, s16 *, s32, s32, s32, s32);
void func_001efb18(void *, void *);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_002014a0(void *, s32, s32, s32, s32, s32, s32, void *, s32, s32);

void func_0024c460(void *a) {
    s32 c[2];
    s32 w[2] = { 17, 15 };
    s32 col[5] = { 0x0CFB8D2A, 0x0CF29829, 0x0CDFB128, 0x0CCBCB27, 0x0CC2D726 };
    s32 x, i, k;
    x = 156 - w[0];
    func_00206130(a, 0, x + D_00669A70, 512, 173, 0x59191202);
    if (D_00669A5C)
        func_00206130(a, 0, x + 173, 512, 211 - x, 0x59191202);
    c[0] = 0x4C00509A;
    c[1] = 0x4C2998FF;
    func_00206130(a, 187, D_00669A78 + 325, 47, 17, c[D_0046A540 == 0]);
    func_00206130(a, 239, D_00669A78 + 325, 47, 17, c[D_0046A540 == 1]);
    func_00206130(a, 291, D_00669A78 + 325, 47, 17, c[D_0046A540 == 2]);
    func_00206130(a, 343, D_00669A78 + 325, 47, 17, c[D_0046A540 == 3]);
    func_00206130(a, 395, D_00669A78 + 325, 47, 17, c[D_0046A540 == 4]);
    func_0024c8b8(a, D_0046A580, 189, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A588, 241, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A590, 293, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A598, 345, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A5A0, 397, D_00669A78 + 326, 14, 0x4F000000);
    func_001efb18(D_0046A080, D_0046A0C0);
    func_001f9438(a, 0, 147, D_00669A78 + 352, 2, 14, 0x4CFFFFFF);
    for (i = 0; i < 11; i++) {
        if (i & 1)
            func_00206130(a, 0, x + D_00669A70, 512, w[i & 1], col[i / 2]);
        x += w[i & 1];
    }
    func_00206130(a, 0, D_00669A70 - w[0] + 156, 512, 2, 0x80784040);
    func_001efb18(D_0046A080, D_0046A0C0);
    k = D_00669A5C ? 3 : 1;
    func_002014a0(a, 2, 2, 12, D_00669A70 + 127, 120, 70, D_0046A5A8, k, 16);
    func_00206130(a, 0, D_00669A70 - w[0] + 329, 512, 2, 0x80784040);
}
#include "data/data_0046.h"
