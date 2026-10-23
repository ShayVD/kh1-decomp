#include "common.h"
#include "data/types/vm_rec.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"

/* The save block at D_00304BE8. */
typedef Save_304be8 SaveM;

/* Text layout: control codes < 0x15 index a length table, 0x15-0x1f are
 * two-byte codes, >= 0x20 one byte. */

/* Pad state: x8 = trigger, x10 = repeat. */

typedef struct { u8 pad0[0xd8]; s16 d8; } Obj203;
typedef struct { u8 pad0[0x94]; f32 f94; } Obj207;
typedef struct { u8 pad0[0xbe]; s16 be; s16 c0; s16 c2; s16 c4; s16 c6; } Obj207a;
#include "data/pieces/D_003F2C40.h"
typedef E20_3F2C40_2 E20;
#include "data/pieces/D_003E3D70.h"
typedef E228_3E3D70 E228;
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

/* func_001ebca0, func_001ec0d8, func_001ec1a0 are in src/save/flags.c. */

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

#include "data/bss_0064_mixed.h"
#include "data/data_003E.h"
#include "data/data_003F.h"
#include "data/data_0049.h"
