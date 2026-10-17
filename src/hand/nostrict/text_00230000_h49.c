/* 0x00230000-0x0024FFFF game code by hand (batch 49), built without strict aliasing. */
#include "common.h"
typedef struct { s32 r, g, b, a; } __attribute__((aligned(16))) Col;
extern Col D_004915F0;
typedef struct {
    u8 pad0[0x80];
    u8 unk80[0x10];
    u8 *unk90;
    u8 pad94[0x9E4 - 0x94];
    f32 unk9E4;
    f32 unk9E8;
    f32 unk9EC;
    f32 unk9F0;
    u8 pad9F4[0xA1C - 0x9F4];
    f32 unkA1C;
} Obj;
s32 func_0023e160(void *, void *, Col *, s32, f32, f32, f32);

s32 func_0023f700(Obj *o, s32 a1) {
    Col c = D_004915F0;
    s32 v;
    a1 = func_0023e160(o->unk80, o->unk90 + 0x30, &c, a1, 0.0f, o->unk9E4, o->unkA1C);
    if (o->unk9F0 != 0.0f) {
        v = o->unk9EC;
        c.a = 128;
        c.b = v;
        c.g = v;
        c.r = v;
        a1 = func_0023e160(o->unk80, o->unk90 + 0x30, &c, a1, o->unk9E4, o->unk9E8, o->unkA1C);
    }
    return a1;
}
void func_00237018(void *, s32, s32);
typedef struct { u64 lo, hi; } QW;
extern u8 D_00351E10[];
extern QW *D_00651D60;
extern QW *D_00651D64;
typedef struct { u8 pad[0x18]; u64 unk18; } Tex;
typedef struct { u8 pad[0x70]; Tex *unk70; } Obj4;
void func_00240b68(Obj4 *);
QW *func_0023ee80(Obj4 *, QW *);
QW *func_0023dfc0(Obj4 *, QW *);
QW *func_0023f920(Obj4 *, QW *);
QW *func_0023f688(Obj4 *, QW *);
QW *func_0023dfd8(Obj4 *, QW *);
QW *func_00240400(Obj4 *, QW *);

void func_00240fa0(Obj4 *o) {
    D_00651D64 = (QW *)D_00351E10;
    D_00651D60 = (QW *)(D_00351E10 + 0x10);
    func_00240b68(o);
    D_00651D60 = func_0023ee80(o, D_00651D60);
    D_00651D60 = func_0023dfc0(o, D_00651D60);
    D_00651D60->lo = 0x1000000000008001;
    D_00651D60->hi = 14;
    D_00651D60++;
    D_00651D60->lo = o->unk70->unk18;
    D_00651D60->hi = 6;
    D_00651D60++;
    D_00651D60 = func_0023f920(o, D_00651D60);
    D_00651D60 = func_0023f688(o, D_00651D60);
    D_00651D60 = func_0023dfd8(o, D_00651D60);
    D_00651D60 = func_00240400(o, D_00651D60);
    func_00237018(D_00651D64, D_00651D60 - D_00651D64, 1);
}
typedef struct { u8 pad[0xA1C]; f32 unkA1C; f32 unkA20; u8 padA24[0xD00 - 0xA24]; } Slot1C;
extern Slot1C D_00651E70[];

void func_002414a8(s32 i, s32 a) {
    Slot1C *e = &D_00651E70[i];
    switch (a) {
    case 0:
        e->unkA1C = 1.0f;
        e->unkA20 = -0.0999999940395355224609375f;
        break;
    case 1:
        e->unkA20 = 0.0999999940395355224609375f;
        e->unkA1C = 0.0f;
        break;
    case 2:
        e->unkA1C = 1.0f;
        e->unkA20 = 0.0f;
        break;
    case 3:
        e->unkA20 = 0.0f;
        e->unkA1C = 0.0f;
        break;
    }
}
extern u8 D_00426940[];
typedef struct { u8 pad[0xA1C]; f32 unkA1C; u8 padA20[0xA84 - 0xA20]; s32 unkA84; } Obj5;
void func_0023d528(Obj5 *, s32 *, s32 *);
void func_0023d698(s32);
QW *func_0023d700(s32, void *, s32, s32, QW *, f32);

void func_002415f0(Obj5 *o) {
    s32 a[4];
    s32 b[2];
    s32 x, y;
    D_00651D64 = (QW *)D_00351E10;
    D_00651D60 = (QW *)(D_00351E10 + 0x10);
    func_0023d528(o, a, b);
    x = b[0];
    y = b[1];
    func_0023d698(2);
    D_00651D60 = func_0023d700(o->unkA84, D_00426940, x, y, D_00651D60, o->unkA1C);
    func_00237018(D_00651D64, D_00651D60 - D_00651D64, 1);
}
typedef struct { u8 pad[0x44]; s32 unk44; u8 pad48[0xBE - 0x48]; u16 unkBE; } Prof;
typedef struct { u8 pad[0x6C]; Prof *unk6C; } Ch3;
typedef struct {
    s32 unk0;
    Ch3 *unk4;
    u8 pad8[0x9E0 - 8];
    s32 unk9E0;
    f32 unk9E4;
    u8 pad9E8[4];
    u8 unk9EC[0x10];
    s32 unk9FC;
    f32 unkA00;
    u8 padA04[4];
    u8 unkA08[0x10];
    u8 padA18[0xD00 - 0xA18];
} Slot3;
typedef struct { s32 on[8]; Slot3 e[5]; } SlotTbl3;
extern SlotTbl3 D_00651E50;
void func_002492d0(void *, f32, f32, f32, f32);

void func_00241a38(s32 i) {
    Slot3 *e;
    Prof *p;
    s32 a;
    u16 b;
    if (D_00651E50.on[i] == 0) return;
    e = &D_00651E50.e[i];
    if (e->unk0 == 4) return;
    if (e->unk0 == 3) return;
    p = e->unk4->unk6C;
    a = p->unk44;
    b = p->unkBE;
    e->unk9E0 = a;
    e->unk9E4 = a * 0.5235987f;
    func_002492d0(e->unk9EC, 0.0f, 0.0f, 0.0f, 128.0f);
    e->unk9FC = b;
    e->unkA00 = b * 0.017453289f;
    func_002492d0(e->unkA08, 0.0f, 0.0f, 0.0f, 128.0f);
}
typedef struct { s32 x, y, z, w; } I4;
typedef struct { u8 pad[0x60]; I4 c[4]; I4 p[4]; } Pkt;
extern Pkt D_006560F0;
extern s32 D_006560E0;
void func_0024aa48(s32, Pkt *, s32);
s32 func_002388b8(Pkt *, s32, s32);

void func_002432d8(s32 a0, s32 a1, s32 x, s32 y) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_006560F0, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_006560F0.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    D_006560E0 = func_002388b8(&D_006560F0, 1, D_006560E0);
}
