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

extern Obj D_0063F758[24];
extern s32 D_003F1A60;
extern s32 D_00640E00[];
extern s32 D_00640E20;
extern s32 D_00640E24;
extern s32 D_00640E28;

s32 func_001fb428(s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fbcd8(s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_001fc330(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_002014a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00201550(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00201600(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00206370(s32, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_001f4148(void) {
    s32 i, n = 0;
    Obj *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state == 0) n++;
    }
    return n;
}

s32 func_001f4180(void) {
    s32 i, n = 0;
    Obj *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state == 3) n++;
    }
    return n;
}

s32 func_001f41c0(void) {
    s32 i, n = 0;
    Obj *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        switch (p->state) {
        case 1:
        case 2:
            n++;
        }
    }
    return n;
}

s32 func_001f4208(void) {
    s32 i, n = 0;
    Obj *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state < 6) {
            if (p->state >= 4) n++;
        }
    }
    return n;
}

s32 func_001f4390(Obj *o) {
    s32 s = o->state;
    if (s < 4) {
        if (s > 0) return ((s32)o->hi & 1) ^ 1;
    }
    return 0;
}

s32 func_001f43c8(Obj *o) {
    s32 s = o->state;
    if (s < 4) {
        if (s > 0) return ((s32)o->hi & 1) ^ 1;
    }
    return 0;
}

s32 func_001f4400(Obj *o) {
    if (o->state == 3) return ((s32)o->hi & 1) ^ 1;
    return 0;
}

s32 func_001f44a0(s32 id) {
    s32 i;
    Obj *p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state != 0 && p->id == id) return 1;
    }
    return 0;
}

s32 func_001f44e8(Obj *o, s32 id) {
    if (o == NULL) return 0;
    while (o->child != NULL) o = o->child;
    do {
        if (o->state != 0 && o->id == id) return 1;
        o = o->next;
    } while (o != NULL);
    return 0;
}

s32 func_001fb3e0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h) {
    return func_001fb428(a, b, c, d, e, f, g, h, D_003F1A60);
}

s32 func_001fb408(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h) {
    return func_001fb428(a, b, c, d, e, f, g, 18, h);
}

s32 func_001fbcb0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h) {
    return func_001fbcd8(a, b, c, d, e, f, g, h, 0x80808080);
}

s32 func_001fc308(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i) {
    return func_001fc330(a, b, c, d, e, f, g, h, h, i, i);
}

void func_001fd070(s32 a, s32 b, s32 c) {
    func_001fc308(a, b, c, 0, 0, 57, 0, 0x64323296, 0x64323296);
    func_001fc308(a, b + 14, c + 6, 0, 0, 56, 0, 0x64ffffff, 0x64ffffff);
}

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
