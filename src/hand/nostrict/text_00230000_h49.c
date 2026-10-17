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
/* The 0xD00-byte slots of D_00651E50 (see text_00230000_h26.c). */
typedef struct {
    s32 unk0;
    Ch3 *unk4;
    u8 pad8[0x9C - 8];
    void *unk9C;
    u8 padA0[0x9E0 - 0xA0];
    s32 unk9E0;
    f32 unk9E4;
    u8 pad9E8[4];
    u8 unk9EC[0x10];
    s32 unk9FC;
    f32 unkA00;
    u8 padA04[4];
    u8 unkA08[0x10];
    u8 padA18[0xA2C - 0xA18];
    s32 unkA2C;
    s32 unkA30;
    u8 unkA34[0xD00 - 0xA34];
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
typedef struct { s32 unk0; s32 unk4; s32 unk8; s32 unkC; s32 unk10; } Hp2;
extern Hp2 D_00454A20;
extern u8 D_00451040[];
Slot3 *func_00241b60(s32, s32);
void func_0023d1a0(void);
void func_00242bd0(void);
void func_0023cfe8(void *, s32, void *);

void func_00241c60(s32 b, s32 i) {
    Slot3 *e;
    if (b == 0 && i != 4) {
        D_00651E50.on[i] = 0;
        return;
    }
    e = func_00241b60(i, b);
    if (i == 0) {
        func_0023d1a0();
        func_00242bd0();
    }
    if (i == 4) {
        e->unk9E0 = D_00454A20.unk0;
        e->unk9E4 = D_00454A20.unk0 * 0.5235987f;
        func_002492d0(e->unk9EC, 0.0f, 0.0f, 0.0f, 128.0f);
        func_0023cfe8(e->unkA34, D_00454A20.unk10, D_00451040);
    } else {
        func_00241a38(i);
        e->unkA2C = 0;
        e->unkA30 = 0;
    }
}
void func_00243380(s32, u8 *, s32, s32, s32);
u16 *func_00147840(s32);
s32 func_00147808(u16);
void func_0024ac08(u8 *, s32 *);
void func_002433e8(s32, s32, s32, s32, f32);

void func_00243508(s32 a0, u8 *p, s32 c0, s32 c1, s32 x, s32 y, s32 id, s32 k, f32 f) {
    s32 i;
    u8 *q = p;
    s32 v;
    s32 d[4];
    for (i = 0; i < 7; i++) {
        func_00243380(a0, p, c0, x, y);
        p += 0xC0;
    }
    for (i = 0; i < 2; i++) {
        func_00243380(a0, p, c1, x, y);
        p += 0xC0;
    }
    if (id != 0) {
        v = func_00147808(*func_00147840(id));
        func_0024ac08(q, d);
        func_002433e8(x + d[0], y + d[1], v, k, f);
    }
}
extern Pkt D_00656430;
extern s32 D_00656420;

void func_00243c10(s32 a0, s32 a1, s32 x, s32 y, s32 *v, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_00656430, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_00656430.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_00656430.c[i].x = v[0];
        D_00656430.c[i].y = v[1];
        D_00656430.c[i].z = v[2];
        D_00656430.c[i].w = D_00656430.c[i].w * s;
    }
    D_00656420 = func_002388b8(&D_00656430, 1, D_00656420);
}
extern Pkt D_0065FCA0;
extern QW *D_0065FC90;

void func_00244968(s32 a0, s32 a1, s32 x, s32 y) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_0065FCA0, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_0065FCA0.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    D_0065FC90 = (QW *)func_002388b8(&D_0065FCA0, 1, (s32)D_0065FC90);
}
typedef struct { u8 b[0xC0]; } Spr0C0;
typedef struct { s32 unk0; s32 unk4; s32 unk8; s32 unkC; s32 unk10; s32 unk14; } Hud;
extern Hud D_00662540;
extern Spr0C0 D_0065FD80[5][10];
extern Spr0C0 D_00662300[];
void func_0024ae90(Spr0C0 *);

void func_00244a10(s32 a0, s32 a1) {
    s32 i, j;
    Hud *h = &D_00662540;
    if (h->unk0 == 0) {
        h->unk4 = a1;
        h->unk0 = 1;
        h->unk14 = a0;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) func_0024ae90(&D_0065FD80[i][j]);
        }
        for (i = 0; i < 3; i++) func_0024ae90(&D_00662300[i]);
    } else {
        h->unk4 += a1;
    }
    h->unk8 = 0;
}
extern u8 D_004267F0[];
extern u8 D_00426820[];
s32 func_00244b10(s32, s32 *);
void func_00244be0(s32 a0, s32 y, s32 z) {
    s32 buf[5];
    s32 n, k, cy;
    n = func_00244b10(a0, buf);
    cy = y;
    for (k = 0; k < n; k++) {
        func_00244968((s32)&D_0065FD80[k][buf[5 - n + k]], (s32)D_00426820, cy, z);
        cy += 13;
    }
    cy += 2;
    func_00244968((s32)&D_00662300[0], (s32)D_004267F0, cy, z);
    func_00244968((s32)(a0 < 2 ? &D_00662300[1] : &D_00662300[2]), (s32)D_004267F0, cy, z);
}
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[8]; u64 unk70; u8 pad78[0xE0 - 0x78]; u64 unkE0; } Q70;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; } Q;
extern Q70 D_0065FB30;
extern QW *D_0065FC94;
void func_002370c8(void *);
void func_00244960(void);
void func_00244f28(void);

s32 func_00245090(void) {
    func_002370c8(&D_0065FB30);
    D_0065FB30.unkE0 = 5;
    D_0065FB30.unk60 = 0x30003;
    D_0065FB30.unk70 = 0x8000000048ULL;
    func_00237018(&D_0065FB30, 0x16, 1);
    func_00244960();
    D_0065FC94 = (QW *)D_00351E10;
    D_0065FC90 = (QW *)(D_00351E10 + 0x10);
    func_00244f28();
    func_00237018(D_0065FC94, D_0065FC90 - D_0065FC94, 1);
    return 0;
}
extern u8 D_00459D40[];
extern u8 D_0045B770[];
extern u8 D_0045B780[];
void *memset(void *, s32, u32);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);

void func_00245148(void) {
    s32 i;
    memset(&D_00662540, 0, 0x18);
    func_0024aac8(D_00459D40);
    func_0024af40(D_0045B770, D_00662300, D_00459D40);
    for (i = 0; i < 5; i++) func_0024af40(D_0045B780, D_0065FD80[i], D_00459D40);
    if (func_0011ef38(func_00245090) == 0) func_0011ef10(0x28489, func_00245090);
}
extern Pkt D_006626D0;
extern QW *D_006626C0;

void func_00245300(s32 a0, s32 a1, s32 x, s32 y, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_006626D0, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_006626D0.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_006626D0.c[i].w = D_006626D0.c[i].w * s;
    }
    D_006626C0 = (QW *)func_002388b8(&D_006626D0, 1, (s32)D_006626C0);
}
typedef struct { s32 unk0; s32 unk4; u32 unk8; f32 unkC; s32 unk10; s32 unk14; } Msg3;
extern s32 D_006627C8, D_006627D0, D_006627D8;
extern Msg3 D_006627B0;
extern u8 D_002E26C0[], D_00431D20[];
typedef struct { s32 x, y; } XY;
void func_0024ae00(void *);
void func_0024af00(void *);
void func_001315c0(s32, s32, void *, f32);
s32 func_00249580(void *);
void func_00237a48(XY *, void *, void *, s32);
void func_00249558(XY *, XY *);

void func_002453e8(s32 a0, f32 f) {
    Msg3 *m = &D_006627B0;
    s32 v = 0;
    u8 buf[16];
    XY r;
    switch (m->unk0) {
    case 0:
        v = D_006627C8;
        break;
    case 1:
        v = D_006627D0;
        break;
    case 2:
        v = D_006627D8;
        break;
    }
    if (a0 != 0) func_0024ae00((void *)v);
    func_0024af00((void *)v);
    func_001315c0(m->unk4, 0x8004, buf, 0.0f);
    if (func_00249580(buf) == 0) {
        func_00237a48(&r, D_002E26C0, buf, 1);
        func_00249558(&r, &r);
        r.y -= 54;
        func_00245300(v, (s32)D_00431D20, r.x, r.y, f);
    }
}

extern Q D_00662560;
extern QW *D_006626C4;

void func_00245508(s32 a0, f32 f) {
    func_002370c8(&D_00662560);
    D_00662560.unkE0 = 5;
    D_00662560.unk60 = 0x30003;
    func_00237018(&D_00662560, 0x16, 1);
    D_006626C4 = (QW *)D_00351E10;
    D_006626C0 = (QW *)(D_00351E10 + 0x10);
    func_002453e8(a0, f);
    func_00237018(D_006626C4, D_006626C0 - D_006626C4, 1);
}

extern u8 D_0045B7B0[], D_0045BC00[];
void func_0024afc0(void *, void *, void *);
s32 func_002455c0(void);

void func_002456e8(void) {
    s32 buf[4];
    memset(&D_006627B0, 0, 0x18);
    D_006627B0.unk8 = 0;
    func_0024aac8(D_0045B7B0);
    func_0024afc0(D_0045BC00, buf, D_0045B7B0);
    D_006627C8 = buf[2];
    D_006627D0 = buf[1];
    D_006627D8 = buf[0];
    if (func_0011ef38(func_002455c0) == 0) func_0011ef10(0x28489, func_002455c0);
}

extern Pkt D_00662950;
extern s32 D_00662940;

void func_00245920(s32 a0, s32 a1, s32 x, s32 y, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_00662950, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_00662950.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_00662950.c[i].w = D_00662950.c[i].w * s;
    }
    D_00662940 = func_002388b8(&D_00662950, 1, D_00662940);
}

/* needs make: uses rodata */

typedef struct {
    void *unk0;
    u8 pad4[0xC];
    u8 unk10[0xC0];
    u8 unkD0[0xC0];
    u8 unk190[0xC0];
    u32 unk250;
    s32 unk254;
} Fade;
void func_0024ae00(void *);
void func_0024af00(void *);
s32 func_0024a1c0(void *);

void func_002409e0(Fade *o) {
    switch (o->unk250) {
    case 0:
        break;
    case 1:
        o->unk254 = 0;
        o->unk0 = o->unk10;
        func_0024ae00(o->unk0);
        o->unk250++;
        break;
    case 2:
        func_0024af00(o->unk0);
        if (func_0024a1c0(o->unk0) & 4) o->unk250++;
        break;
    case 3:
        o->unk0 = o->unkD0;
        func_0024ae00(o->unk0);
        o->unk250++;
        break;
    case 4:
        func_0024af00(o->unk0);
        if (func_0024a1c0(o->unk0) & 4) {
            if (o->unk254 == 0) do { func_0024ae00(o->unk0); } while (0);
            else o->unk250++;
        }
        break;
    case 5:
        o->unk0 = o->unk190;
        func_0024ae00(o->unk0);
        o->unk250++;
        break;
    case 6:
        func_0024af00(o->unk0);
        if (func_0024a1c0(o->unk0) & 4) o->unk250 = 0;
        break;
    }
}

/* func_0023d148 and func_00240b68 sit below func_002409e0: func_00240b68 matches only with both callees defined above it. */
typedef struct { u8 pad[0x3C]; s32 unk3C; } St6C;
typedef struct { u8 pad[0x6C]; St6C *unk6C; } Ow;
typedef struct Gm Gm;
struct Gm {
    s32 unk0;
    Ow *unk4;
    u8 pad8[0x80 - 8];
    s32 unk80;
    s32 unk84;
    u8 pad88[0x94 - 0x88];
    s32 unk94;
    s32 unk98;
    Gm *unk9C;
    u8 padA0[0x460 - 0xA0];
    u8 unk460[0x520 - 0x460];
    u8 unk520[0x780 - 0x520];
    u8 unk780[0xA1C - 0x780];
    f32 unkA1C;
    f32 unkA20;
    s32 unkA24;
    s32 unkA28;
    s32 unkA2C;
    u8 padA30[0xAA0 - 0xA30];
    u8 unkAA0[0x10];
};
typedef struct { u8 pad[0x4120]; s32 unk4120; } G51E50;
#define D_00651E50 (*(G51E50 *)&D_00651E50)
extern u32 D_002C5960;
extern u32 D_002C5958;
extern f32 D_002BBDFC;
s32 func_0023d490(Gm *);
void func_002407b0(Gm *, s32);
void func_0024af00(void *);
s32 func_00240810(Gm *);
void func_0024ae00(void *);
s32 func_0024a1c0(void *);
s32 func_001375d8(s32);
void func_0023d128(s32);
void func_0023d1a0(void);
void func_00240978(Ow *);
void func_002409b0(Ow *);
s32 func_00240b28(Gm *);

s32 func_0011d768(s32);
f32 func_0011d790(s32, s32);
void func_0023d148(s32 arg0) {
    if (D_00651E50.unk4120 == 0) {
        func_0011d768(0x2D);
        func_0011d790(0x2D, arg0);
        D_00651E50.unk4120 = 1;
    }
}

void func_00240b68(Obj4 *o_) {
    Gm *e = (Gm *)o_;
    s32 p1[4];
    s32 p2[4];
    s32 n, r;
    if (e->unkA20 != 0.0f) {
        if (!(D_002C5960 & 1)) e->unkA1C += e->unkA20 * D_002BBDFC;
        if (e->unkA1C <= 0.0f) {
            e->unkA20 = e->unkA1C = 0.0f;
        } else if (1.0f <= e->unkA1C) {
            e->unkA1C = 1.0f;
            e->unkA20 = 0.0f;
        }
    }
    if (e->unk0 == 0) {
        n = func_0023d490(e);
        if (e->unk98 != n) {
            e->unk98 = n;
            if (n == 0) func_002407b0(e, 0);
            else if (n == 1) func_002407b0(e, 0);
            else if (n == 2) func_002407b0(e, 1);
        }
    }
    if (e->unk9C) {
        func_0024af00(e->unk9C);
        if ((s32)e->unk9C->unk9C & 4) {
            e->unk9C = 0;
            e->unk94 = e->unk98;
        }
    }
    func_0023d528((Obj5 *)e, p1, p2);
    e->unk80 = (p1[0] + p2[0]) * 16 + 0x7000;
    e->unk84 = (p1[1] + p2[1]) * 16 + 0x7400;
    r = func_00240810(e);
    switch (e->unkA24) {
    case 0:
        if (r) e->unkA24 = 1;
        break;
    case 1:
        func_0024ae00(e->unk460);
        e->unkA24++;
        break;
    case 2:
        func_0024af00(e->unk460);
        if (func_0024a1c0(e->unk460) & 4) func_0024ae00(e->unk460);
        if (!r) e->unkA24++;
        break;
    case 3:
        e->unkA24 = 0;
        break;
    }
    if (e->unk0 == 0) {
        if (e->unkA28 == 0) {
            if (r == 1 && e->unkA1C > 0.0f && !func_001375d8((s32)e->unk4)) {
                if ((D_002C5958 & 1) == r) {
                    if (D_00651E50.unk4120 == 0) func_0023d148(0);
                    else func_0023d128(0);
                } else {
                    if (D_00651E50.unk4120 == 0) func_0023d148(1);
                    else func_0023d128(1);
                }
            }
            if (D_00651E50.unk4120 != 0) {
                if (r == 0 || e->unkA1C == 0.0f || func_001375d8((s32)e->unk4) == 1) func_0023d1a0();
            }
        } else {
            if (D_00651E50.unk4120 != 0) func_0023d1a0();
        }
    }
    if (e->unk0 == 4) {
        if (D_00651E50.unk4120 == 0) {
            if (r == 1 && e->unkA1C > 0.0f) func_0023d148(0);
        } else {
            if (r == 0 || e->unkA1C == 0.0f) func_0023d1a0();
        }
    }
    if (e->unk0 == 1 || e->unk0 == 2) {
        func_002409e0((Fade *)e->unk520);
        if (e->unk4->unk6C->unk3C <= 0) func_00240978(e->unk4);
        if (e->unk4->unk6C->unk3C > 0) func_002409b0(e->unk4);
        func_002409e0((Fade *)e->unk780);
    }
    if (e->unk0 == 3) func_002409e0((Fade *)e->unkAA0);
    if (e->unk0 == 0) e->unkA2C = func_00240b28(e);
}
#undef D_00651E50
typedef struct {
    u32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10, unk14, unk18, unk1C, unk20, unk24;
    u8 pad28[8];
    u8 unk30[0x300];
    u8 unk330[0x180];
    u8 unk4B0[0x480];
    u8 unk930[0xC0];
    f32 unk9F0;
    s32 unk9F4;
    s32 unk9F8;
} Wipe;
extern u8 D_004267C0[], D_004267F0[];
void func_00243ef8(s32, void *, void *, void *, void *, void *, void *, s32, f32, s32, s32, s32, s32, s32, s32, s32);

void func_00244188(Wipe *o) {
    s32 f = 0;
    switch (o->unk0) {
    case 0:
        return;
    case 1:
        f = 1;
        o->unk0++;
        break;
    case 2:
    case 4:
        o->unk0++;
        break;
    case 3:
        if (++o->unkC >= 91) o->unk0++;
        break;
    case 5:
        o->unk9F0 -= 0.125f;
        if (o->unk9F0 < 0.0f) {
            o->unk9F0 = 0.0f;
            o->unk0++;
        }
        break;
    case 6:
        o->unk0 = 0;
        break;
    }
    func_00243ef8(f, o->unk30, o->unk330, o->unk4B0, o->unk930, D_004267C0, D_004267F0, o->unk10, o->unk9F0,
                  o->unk14, o->unk18, o->unk24, o->unk1C, o->unk20, o->unk9F4, o->unk9F8);
}
s32 func_00122ff8(s32);
s32 func_001375d8(s32);
void func_002452c8(void);
void func_002452f0(void);

s32 func_002455c0(void) {
    Msg3 *m = &D_006627B0;
    s32 f = 0;
    switch (m->unk8) {
    case 0:
        return 0;
    case 1:
        f = 1;
        m->unk8++;
        break;
    case 2:
    case 4:
        m->unk8++;
        break;
    case 3:
        break;
    case 5:
        m->unkC -= 0.2f;
        if (m->unkC < 0.0f) {
            m->unkC = 0.0f;
            m->unk8++;
        }
        break;
    case 6:
        m->unk8 = 0;
        return 0;
    }
    if (m->unk4 == 0) return 0;
    if (func_00122ff8(m->unk4) == 0) return 0;
    if (m->unk14 == 0 && func_001375d8(m->unk4) != 0) {
        func_002452f0();
        return 0;
    }
    m->unk14 = 0;
    func_00245508(f, m->unkC);
    if (m->unk10 == 0) func_002452c8();
    m->unk10 = 0;
    return 0;
}
