#include "common.h"
#include "data/bss_0064.h"

#include "data/types/text_001f0000_h23.h"

typedef struct Win {
    u8 pad0[192];
    u16 f192;
    u16 pad194;
    u16 f196;
    u8 pad198[204 - 198];
    s16 f204;
    s16 f206;
    s16 f208;
    s16 f210;
    s16 f212;
    s16 f214;
    u8 f216[4];
    u8 f220[64];
} Win;

#include "data/pieces/D_00425BC8.h"
typedef struct { u8 pad[36]; s32 v[1]; } Menu;
#include "data/pieces/D_003F34B8.h"
extern s32 D_00640E00[];
extern s32 D_00640E20;
extern s32 D_00640E24;
extern s32 D_00640E28;
s32 func_002014a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00201550(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00201600(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00206370(s32, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_001fd590(Win *w) {
    return ((s16)w->f192 >> 4) - ((s16)w->f196 >> 4) * (w->f208 & 0xf) / 16;
}

void func_001fd688(Win *w) {
    s32 a = w->f204;
    s32 d;
    if (a == 0) return;
    d = (a - w->f206) << 4;
    if (d <= 0) {
        a = (a - 1) << 4;
        w->f208 = 0;
        w->f214 = 0;
        if (a < w->f210) {
            w->f210 = a;
            w->f212 = 0;
        }
    } else if (d < w->f208) {
        w->f208 = d;
        w->f214 = 0;
    }
}

s32 func_001fd6f0(Win *w) {
    s32 a = w->f204;
    s32 b = w->f206;
    return a < b ? a : b;
}

s32 func_001fe718(Menu *m, s32 idx, s32 max) {
    s32 r = 0;
    u32 f = D_00425BC8->x10;
    if (f & 0x10000010) {
        if (m->v[idx] > 0) {
            m->v[idx]--;
            r = 1;
        }
    } else if (f & 0x40000040) {
        if (m->v[idx] < max - 1) {
            m->v[idx]++;
            r = 1;
        }
    }
    return r;
}

s32 func_001fe860(Menu *m, s32 idx, s32 max) {
    s32 r = 0;
    u32 f = D_00425BC8->x10;
    if (f & 0x80000080) {
        if (m->v[idx] > 0) {
            m->v[idx]--;
            r = 1;
        }
    } else if (f & 0x20000020) {
        if (m->v[idx] < max - 1) {
            m->v[idx]++;
            r = 1;
        }
    }
    return r;
}

s32 func_001fe9a8(Menu *m, s32 idx, s32 max) {
    s32 r = 0;
    u32 f = D_00425BC8->x10;
    if (f & 0x80000480) {
        if (m->v[idx] > 0) {
            m->v[idx]--;
            r = 1;
        }
    } else if (f & 0x20000820) {
        if (m->v[idx] < max - 1) {
            m->v[idx]++;
            r = 1;
        }
    }
    return r;
}

s32 func_00201440(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j) {
    return func_002014a0(a, b, c, d, e, f, g, h, i, 15);
}

s32 func_00201460(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j) {
    return func_00201550(a, b, c, d, e, f, g, h, i, 15);
}

s32 func_00201480(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j) {
    return func_00201600(a, b, c, d, e, f, g, h, i, 15);
}

s32 func_002066b0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    return func_00206370(a, b, c, d, 2, e, f, e, f);
}

s32 func_00206710(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    return func_00206370(a, b, c, 2, d, e, e, f, f);
}

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
