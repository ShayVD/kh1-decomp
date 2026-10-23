#include "common.h"
#include "data/types/vm_rec.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"

/* The save block at D_00304BE8. */
typedef Save_304be8 SaveM;

/* Text layout: control codes < 0x15 index a length table, 0x15-0x1f are
 * two-byte codes, >= 0x20 one byte. */

typedef struct {
    u8 pad0[0xce];
    s16 ce;
    s16 d0;
    s16 d2;
    u8 pad_d4[8];
    u8 dc[1];
} Fade;

/* Pad state: x8 = trigger, x10 = repeat. */
#include "data/pieces/D_00425BC8.h"
typedef struct { u8 pad0[0x24]; s32 cur[1]; } Menu24;

typedef struct { u8 pad0[0xd8]; s16 d8; } Obj203;
typedef struct { u8 pad0[0x94]; f32 f94; } Obj207;
typedef struct { u8 pad0[0xbe]; s16 be; s16 c0; s16 c2; s16 c4; s16 c6; } Obj207a;
#include "data/pieces/D_003F2C40.h"
typedef E20_3F2C40_2 E20;
#include "data/pieces/D_003E3D70.h"
typedef E228_3E3D70 E228;
extern s32 D_00640DE0;
extern s32 D_00640DE4;
extern s32 D_00640DE8;
extern s32 D_00640DEC;
extern s32 D_00640DF0;
extern s32 D_00640DF4;
extern s32 D_00640DF8;
extern f32 D_002BBDFC;
extern s32 D_003F2F10[];
f32 sinf(f32);
u8 *func_001efc10(s32);
s32 func_001f94f0(void *, s32, s32, s32, u8 *, s32, s32);
void func_001fb428(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fc308(Obj207 *, s32, s32, s32, s32, s32, s32, u32, u32);
s32 func_001fd538(void *);
s32 func_001fd658(void *);
void func_002016b0(void *, s32, s32, s32);
void func_00201988(void *, s32, s32, s32);
void func_00201c60(void *, s32, s32, s32);
void func_00203028(Obj203 *, s32, s32, s32, s32);
void func_002053e8(Obj207 *, s32, s32, s32, s32, u32);
void func_002078f0(Obj207a *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fd708(void);
void func_001fd720(s32 m);

/* func_001ebca0, func_001ec0d8, func_001ec1a0 are in src/save/flags.c. */

void func_001fd708(void) {
    func_001fd720(0);
}

void func_001fd720(s32 m) {
    switch (m) {
    case 0:
        D_00640DE0 = m;
        D_00640DE4 = 0x10000010;
        D_00640DE8 = 0x40000040;
        D_00640DEC = 0x50000050;
        D_00640DF0 = 0x80000080;
        D_00640DF4 = 0x20000020;
        D_00640DF8 = 0xA00000A0;
        break;
    case 1:
        D_00640DE0 = m;
        D_00640DE4 = 0x10;
        D_00640DE8 = 0x40;
        D_00640DEC = 0x50;
        D_00640DF0 = 0x80;
        D_00640DF4 = 0x20;
        D_00640DF8 = 0xA0;
        break;
    case 2:
        D_00640DE0 = m;
        D_00640DE4 = 0x10000000;
        D_00640DE8 = 0x40000000;
        D_00640DEC = 0x50000000;
        D_00640DF0 = 0x80000000;
        D_00640DF4 = 0x20000000;
        D_00640DF8 = 0xA0000000;
        break;
    }
}

void func_001fe408(Fade *o) {
    s32 i;
    s32 n1 = o->ce + 1;
    s32 cnt = (o->d0 & 0xf) ? n1 : o->ce;
    s32 k = (o->d0 >> 4) % n1;
    s32 sel = o->d2 >> 4;
    for (i = 0; i < cnt; i++) {
        u8 *p = &o->dc[k];
        if (i == sel) {
            *p = 0x80;
        } else {
            s32 d = D_002BBDFC * 4.0f;
            if (d + 64 >= *p) *p = 64;
            else *p -= d;
        }
        k = (k + 1) % n1;
    }
}

s32 func_001fe660(Menu24 *m, s32 i, s32 n) {
    s32 r = 0;
    if (D_00425BC8->x10 & 0x10000010) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        } else if (D_00425BC8->x8 & 0x10000010) {
            m->cur[i] = n - 1;
            r = 1;
        }
    } else if (D_00425BC8->x10 & 0x40000040) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        } else if (D_00425BC8->x8 & 0x40000040) {
            m->cur[i] = 0;
            r = 1;
        }
    }
    return r;
}

s32 func_001fe7a8(Menu24 *m, s32 i, s32 n) {
    s32 r = 0;
    if (D_00425BC8->x10 & 0x80000080) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        } else if (D_00425BC8->x8 & 0x80000080) {
            m->cur[i] = n - 1;
            r = 1;
        }
    } else if (D_00425BC8->x10 & 0x20000020) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        } else if (D_00425BC8->x8 & 0x20000020) {
            m->cur[i] = 0;
            r = 1;
        }
    }
    return r;
}

s32 func_001fe8f0(Menu24 *m, s32 i, s32 n) {
    s32 r = 0;
    if (D_00425BC8->x10 & 0x80000480) {
        if (m->cur[i] > 0) {
            m->cur[i]--;
            r = 1;
        } else if (D_00425BC8->x8 & 0x80000480) {
            m->cur[i] = n - 1;
            r = 1;
        }
    } else if (D_00425BC8->x10 & 0x20000820) {
        if (m->cur[i] < n - 1) {
            m->cur[i]++;
            r = 1;
        } else if (D_00425BC8->x8 & 0x20000820) {
            m->cur[i] = 0;
            r = 1;
        }
    }
    return r;
}

void func_00203788(Obj203 *o, s32 x0, s32 y, s32 x1, s32 c) {
    s32 mid;
    if (o->d8 < 2) return;
    func_00203028(o, x0, y, x1, c);
    y--;
    mid = x0 + (x1 - x0 + 9) / 2;
    func_001fb428(o, 1, 0, 0, mid - 7, y, func_001fd538(o) + 1, 15, c);
    func_001f94f0(o, 0, mid - 7, y, func_001efc10(84), 15, c);
    func_001fb428(o, 0, 0, 0, mid + 6, y, func_001fd658(o), 15, c);
}

void func_00207428(Obj207 *o, s32 x, s32 y) {
    s32 t = o->f94;
    u32 a = (u32)(sinf((f32)(t % 64) * 0.015625f * 3.1415928f) * 128.0f) << 24;
    u32 c1 = a | 0x1e9696;
    u32 c2 = a | 0xffffff;
    u32 c3 = a | 0x0a1e1e;
    func_002053e8(o, x + 2, y + 2, 26, 8, c2);
    func_001fc308(o, x, y, 0, 0, 62, 0, c1, c3);
}

void func_00207a38(Obj207a *o) {
    s32 i;
    s32 w = o->c2 >> 4;
    s32 h = w - (o->c6 >> 4);
    s32 x = o->be >> 4;
    s32 y = o->c0 >> 4;
    s32 half = h / 2;
    s32 sel = func_001fd538(o);
    for (i = 0; i < 2; i++) {
        func_002078f0(o, i == sel, 2, 2, x, y, h, x + half, D_003F2F10[i]);
        x += w;
    }
}

void func_00207d60(void *o, s32 i, s32 b, s32 y, s32 x, s32 p, s32 h) {
    E20 *e = &D_003F2C40.e20_2[i];
    func_002016b0(o, b, y + 2, e->a);
    func_001fb428(o, 1, 2, 0, x, y + (26 - h) / 2, p, h, e->x10);
}

void func_00207ec0(void *o, s32 i, s32 b, s32 y, s32 x, s32 p, s32 h) {
    E20 *e = &D_003F2C40.e20_2[i];
    func_00201988(o, b, y + 3, e->a);
    func_001fb428(o, 1, 4, 0, x, y + (26 - h) / 2, p, h, e->x10);
}

void func_00208020(void *o, s32 i, s32 b, s32 y, s32 x, s32 p, s32 h) {
    E20 *e = &D_003F2C40.e20_2[i];
    func_00201c60(o, b, y + 2, e->a);
    func_001fb428(o, 1, 2, 0, x, y + (26 - h) / 2, p, h, e->x10);
}

void func_002080e0(void *o, s32 i, s32 x, s32 y, s32 n) {
    E20 *e;
    if (n < 2) return;
    e = &D_003F2C40.e20_2[i];
    func_002016b0(o, x, y + 2, e->a);
    y += 7;
    func_001f9438(o, 0, x + 5, y, 85, 12, e->x10);
    func_001fb428(o, 1, 2, 0, x + 37, y, n, 12, e->x10);
}

void func_002081b0(void *o, s32 i, s32 x, s32 y, s32 n) {
    E20 *e;
    if (n < 2) return;
    e = &D_003F2C40.e20_2[i];
    func_00201988(o, x, y + 3, e->a);
    y += 7;
    func_001f9438(o, 0, x + 5, y, 85, 12, e->x10);
    func_001fb428(o, 1, 3, 0, x + 51, y, n, 12, e->x10);
}

/* needs make: uses rodata (switch jump tables) */

/* func_001fe5a0 only matches with func_001fe558 defined above it. */
typedef struct { u8 pad0[0xbc]; s16 bc; u8 padbe[0x12]; u64 d0; } Fade2;

s32 func_001fe558(Fade2 *o) {
    return (o->d0 & 0xffffffff00000000) != 0;
}

s32 func_001fe5a0(Fade2 *o) {
    switch (o->bc) {
    case 0:
        if (D_00425BC8->x8 & 0x2000) {
            if (func_001fe558(o)) o->bc++;
            else o->bc = 2;
        }
        break;
    case 1:
        if (!func_001fe558(o)) o->bc++;
        break;
    case 2:
        break;
    }
    if (o->bc == 2) { o->bc = 0; return 1; }
    return 0;
}
#include "data/bss_0064_mixed.h"
#include "data/data_003E.h"
#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_002BBDFC.h"
