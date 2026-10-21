#include "common.h"
#include "data/bss_0049.h"

extern s32 D_002A3F38;
extern s32 D_002BC128;
extern s32 D_002BC12C;
extern s32 D_002BC138;
extern s32 D_002BC13C;
extern char D_002BCCE0[];
extern s32 D_002BCDB4;
extern s32 D_002BCDB8;
extern s32 D_002BCDD8;
extern char D_0048CC38[];
void func_00112400(s32);
void func_0011d4e0(s32);
void func_00101728(s32);
void func_0011c898(s32);
void func_001015a8(void);
void func_0011ef10(s32, void *);
void func_00113768(void);
void func_001012e0(void);
s32 func_001137c8(s32, s32);
void func_00120748(char *, s32, void *, s32);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);

s32 func_001017e8(void) {
    char tmp[16];
    char buf[64];

    func_00112400(D_002BC12C);
    if (D_002BCDB4 == 1 && D_002BC13C == D_002BC12C) {
        D_002BCDB8 = D_002BCDB4;
    }
    func_0011d4e0(480);
    func_00101728(960);
    if (D_002BC128 == 8 && D_002BC12C == D_002BC128) {
        func_0011c898(1);
    }
    if (D_002BC138 == 8 && D_002BC13C == D_002BC138) {
        func_0011c898(0);
    }
    D_002BC138 = D_002BC128;
    if (D_002BCDB8 == 1) {
        if (D_002BCDD8 != 0) {
            func_001015a8();
        } else {
            func_0011ef10(50000, func_00113768);
        }
    } else {
        strcpy(buf, D_002BCCE0);
        strcat(buf, D_0048CC38);
        D_002A3F38 = func_001137c8(D_002A3F38, 128);
        func_00120748(buf, D_002A3F38, func_001012e0, 0);
    }
    D_002BC13C = D_002BC12C;
    return 4;
}

extern s32 D_002BC740;
extern f32 D_00494A88;
extern f32 D_00494A8C;
extern s32 D_00494A84;
extern s32 D_00494A80;
extern s32 D_00494A7C;
extern u64 D_002A6AB0[];
extern u64 D_002A6A40[];
extern u64 D_002A6B70[];
extern u64 D_002A6AA0[];
extern u8 D_002C13A0[];
void func_00106b18(void *);
void func_00106438(void *);

#define XYZ(x, y, z) ((u64)(x) | ((u64)(y) << 16) | ((u64)(z) << 32))

s32 func_00106460(void) {
    s32 n;

    if (D_002BC740 == 1) {
        D_00494A88 = 0.0f;
        return 4;
    }
    if (D_00494A88 == 0.0f) return 4;
    func_00106b18(D_002A6A40);
    D_00494A8C += D_00494A88;
    n = 800.0f / D_00494A8C;
    if (n <= D_00494A84) n = D_00494A84;
    if (D_00494A8C < 0.0f) n = 800;
    func_00106438(D_002C13A0);
    D_002A6AB0[21] = XYZ(D_00494A7C - n * 16, D_00494A80 - n * 28, 0xfffffffe);
    D_002A6AB0[23] = XYZ(D_00494A7C + n * 16, D_00494A80 + n * 28, 0xfffffffe);
    func_00106b18(D_002A6B70);
    func_00106b18(D_002A6AA0);
    return 0;
}

typedef struct { f32 x, y, z, w; } V4b;
typedef struct {
    u8 pad0[4]; s32 x4; s16 x8; s16 xA; s16 xC; s16 xE; u8 x10; u8 pad11; u8 x12; u8 x13;
    f32 x14; u8 pad18[8]; s32 x20; struct Obj_s *x24; s32 x28;
} Spr;
typedef struct Obj_s {
    u8 pad0[4]; u16 type; u8 pad6[4]; u16 xA; u16 xC; u16 xE; u16 x10; u16 x12; s32 x14; s32 x18;
    u8 pad1c[4]; f32 x20; u8 pad24[12]; V4b pos; V4b sc; u8 pad50[0x20]; V4b v70; Spr spr;
} Obj;
typedef struct { u8 pad[0x1c]; void *obj; void *spr; } Task;
#define SPR(t) ((Spr *)(t)->spr)
extern s32 D_00495254;
extern u8 D_002B7590[];
extern u16 D_002B67C0[];
extern u16 D_002B67C8[];
extern f32 D_002B6798[];
extern u16 D_002B6780[];
void func_0010ba98();
Task *func_0011f090(void *, s32, void *);
void func_002675a8(V4b *, V4b *);
void func_0010bdd0(Obj *o, s32 arg) {
    Task *t;
    u16 type;
    Spr *sp;
    t = func_0011f090(D_002B7590, D_00495254++, func_0010ba98);
    if (t == 0) return;
    t->spr = &o->spr;
    t->obj = o;
    func_002675a8(&o->v70, &o->pos);
    o->x18 = 0;
    o->x14 = arg;
    sp = SPR(t);
    sp->x8 = (u32)(o->pos.x + 254.0f - o->sc.x * 12.0f);
    sp->xA = (u32)(o->pos.y + 180.0f - o->sc.y * 12.0f);
    sp->xC = o->pos.x + 256.0f;
    o->spr.x4 = 0;
    sp->x12 = 0;
    sp->x24 = o;
    SPR(t)->x20 = 0;
    SPR(t)->xE = 0;
    SPR(t)->x13 = 0;
    SPR(t)->x13 &= ~1;
    o->x10 = D_002B67C0[o->xC];
    SPR(t)->x14 = 0.5f;
    o->x12 = D_002B67C8[o->xE];
    type = o->type;
    o->x20 = D_002B6798[type];
    SPR(t)->x28 = 0;
    o->xA = D_002B6780[type];
    switch (type) {
    case 0:
        SPR(t)->x10 = 0;
        SPR(t)->x13 &= ~2;
        break;
    case 1:
        SPR(t)->x10 = 0;
        SPR(t)->x13 |= 2;
        break;
    default:
        SPR(t)->x10 = 1;
        SPR(t)->x13 |= 2;
        break;
    }
}

typedef struct { u8 pad[0x30]; f32 x; f32 y; u8 pad38[0x38]; f32 ox; f32 oy; } Obj70;
extern f32 D_002BBDFC;
extern f32 D_004D5AFC;
extern u64 D_002BBAF0[];
extern u64 D_002BBB90[];
f32 cosf(f32);
void func_0010f0d0(s32 px, s32 py, Obj70 *o) {
    s32 c, x2;
    D_004D5AFC += D_002BBDFC * 0.2f;
    if (D_004D5AFC > 3.14159275f) D_004D5AFC -= 6.2831854820251465f;
    if (D_004D5AFC < -3.14159275f) D_004D5AFC += 6.2831854820251465f;
    c = cosf(D_004D5AFC) * 64.0f + 64.0f;
    px = px + (o->x - o->ox);
    py = py + (o->y - o->oy);
    {
    u64 a, b, d, e;
/*P*/
    x2 = px + 40;
    a = (u64)(px * 16 - c + 0x7000);
    b = (u64)(x2 * 16 - c + 0x7000);
    { s32 y2 = py + 24; d = (u64)(py * 16 + 0x7400) << 16; e = (u64)(y2 * 16 + 0x7400) << 16; }
/*Q*/
    D_002BBAF0[17] = a | d | (u64)1 << 32;
    D_002BBAF0[19] = b | e | (u64)1 << 32;
    }
    func_00106b18(D_002BBB90);
}

/* needs make: uses rodata */
typedef struct {
    u32 p0:3; u32 b3:1; u32 p4:4; u32 b8:1; u32 b9:1; u32 b10:1; u32 p11:4;
    u32 b15:1; u32 b16:1; u32 b17:1; u32 p18:4; u32 b22:1; u32 b23:1; u32 b24:1;
    u32 b25:1; u32 b26:1; u32 b27:1; u32 b28:1; u32 p29:3;
} TriFlags;
typedef struct { s16 v[4]; u8 pad8[3]; u8 group; u8 pad12[4]; TriFlags f; } Tri20;
extern Tri20 *D_002A6238;
extern s32 D_002A6258;

void func_001054d0(s32 group, s32 which, s32 on) {
    s32 i;
    for (i = 0; i < D_002A6258; i++) {
        Tri20 *t = &D_002A6238[i];
        if (t->group != group) continue;
        switch (which) {
        case 0: t->f.b3 = on; break;
        case 1: t->f.b8 = on; break;
        case 2: t->f.b9 = on; break;
        case 3: t->f.b10 = on; break;
        case 4: t->f.b15 = on; break;
        case 5: t->f.b16 = on; break;
        case 6: t->f.b17 = on; break;
        case 7: t->f.b22 = on; break;
        case 8: t->f.b23 = on; break;
        case 9: t->f.b24 = on; break;
        case 10: t->f.b25 = on; break;
        case 11: t->f.b26 = on; break;
        case 12: t->f.b27 = on; break;
        case 13: t->f.b28 = on; break;
        }
    }
}

void func_0010c5c8(u64 *p, s32 mode, s32 psm) {
    s32 tbp;
    switch (psm) {
    case 0x11: tbp = 0x3FEC; break;
    case 0x12: tbp = 0x3FEE; break;
    case 0x13: tbp = 0x3FF0; break;
    case 0x14: tbp = 0x3FF2; break;
    default: tbp = 0x3FDC; break;
    case 0x22: tbp = 0x3FDE; break;
    case 0x23: tbp = 0x3FE0; break;
    case 0x24: tbp = 0x3FE2; break;
    case 0x31: tbp = 0x3FE4; break;
    case 0x32: tbp = 0x3FE6; break;
    case 0x33: tbp = 0x3FE8; break;
    case 0x34: tbp = 0x3FEA; break;
    }
    switch (mode) {
    case 0: *p = (u64)tbp << 37 | 0x2000000665423600; break;
    case 1: *p = (u64)(tbp + 1) << 37 | 0x2000000665423600; break;
    case 2: *p = (u64)tbp << 37 | 0x2000000665423800; break;
    case 3: *p = (u64)(tbp + 1) << 37 | 0x2000000665423800; break;
    }
}
#include "data/bss_0049_mixed.h"
#include "data/bss_004D_mixed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_0048.h"
#include "data/data_002C.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BC128.h"
