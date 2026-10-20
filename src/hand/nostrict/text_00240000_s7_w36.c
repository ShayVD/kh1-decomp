/* func_00241260 (hand/nostrict, session 7 w36): MATCH. Needs CONTEXT_ONLY copies of func_0023fd58 and func_0023d528 (the latter fixes beqzl -> beqz after func_0023dfd8), and func_00240ae0 declared as (void *, s32, s32, f32, QW *): with the QW * last, the a3 load is emitted after the $f12 load and lands in the jal slot. */
#include "common.h"
#include "data/types/nostrict_text_00240000_s7_w36.h"
typedef struct { u8 pad[0x44]; s32 unk44; u8 pad48[0xBE - 0x48]; u16 unkBE; } Prof;
typedef struct { u8 pad[0x4C]; u16 unk4C; } C130;
typedef struct { u8 pad[0x6C]; Prof *unk6C; u8 pad70[0x130 - 0x70]; C130 *unk130; } Chr;
typedef struct { s32 v[48]; } __attribute__((aligned(8))) Spr;
typedef struct { u8 pad[0x18]; u64 unk18; } Tex;
typedef struct {
    s32 unk0;
    Chr *unk4;
    u8 pad8[0x48 - 8];
    Spr *unk48;
    Spr *unk4C;
    Spr *unk50;
    u8 pad54[0x70 - 0x54];
    Tex *unk70;
    u8 pad74[0x520 - 0x74];
    u8 unk520[0x780 - 0x520];
    u8 unk780[0x9FC - 0x780];
    s32 unk9FC;
    f32 unkA00;
    f32 unkA04;
    u8 unkA08[0x10];
    s32 unkA18;
    f32 unkA1C;
    u8 padA20[0xA88 - 0xA20];
    f32 *unkA88;
    f32 *unkA8C;
    u8 padA90[0xAA0 - 0xA90];
    u8 unkAA0[0x10];
} Obj;
extern u8 D_00351E10[];
extern QW *D_00651D60;
extern QW *D_00651D64;
extern f32 D_002BBDFC;
QW *func_0023d700(Spr *, Tex *, s32, s32, QW *, f32);
void func_002492d0(void *, f32, f32, f32, f32);
s32 func_002492e8(void *, s32);
QW *func_0023fad0(Obj *, QW *);
void func_00240b68(Obj *);
QW *func_0023ee80(Obj *, QW *);
QW *func_0023dfc0(Obj *, QW *);
QW *func_00240118(Obj *, QW *);
QW *func_002403d0(Obj *, QW *);
QW *func_0023f920(Obj *, QW *);
QW *func_0023f688(Obj *, QW *);
QW *func_0023dfd8(Obj *, QW *);
QW *func_00240ae0(void *, s32, s32, f32, QW *);
QW *func_00237008(s32, u64, QW *);
void func_00236fd8(QW *, QW *);
void func_00237018(void *, s32, s32);

typedef struct { s32 x, y, z, w; } T16;
typedef struct { s32 unk0; u8 pad4[0x90]; s32 unk94; u8 pad98[4]; void *unk9C; } Ob9C;
extern T16 D_00454600[];
extern T16 D_00454650[];
extern T16 D_00454680[];
extern T16 D_004546C0[];
extern T16 D_00454700[];
void func_0024ac08(void *, s32 *);
CONTEXT_ONLY void func_0023d528(Obj *ov, s32 *p1, s32 *p2) {
    Ob9C *o = (Ob9C *)ov;
    s32 r[2];
    register T16 *t asm("$5");
    switch (o->unk0) {
    case 0:
        t = D_00454650;
        p1[0] = D_00454600[0].x;
        p1[1] = D_00454600[0].y;
        goto idx;
    case 1:
        p1[0] = D_00454600[1].x;
        p1[1] = D_00454600[1].y;
        p2[0] = D_00454680[0].x;
        p2[1] = D_00454680[0].y;
        break;
    case 2:
        p1[0] = D_00454600[2].x;
        p1[1] = D_00454600[2].y;
        p2[0] = D_004546C0[0].x;
        p2[1] = D_004546C0[0].y;
        break;
    case 3:
        t = D_00454700;
        p1[0] = D_00454600[3].x;
        p1[1] = D_00454600[3].y;
        goto idx;
    case 4:
        t = D_00454650;
        p1[0] = D_00454600[4].x;
        p1[1] = D_00454600[4].y;
    idx:
        p2[0] = t[o->unk94].x;
        p2[1] = t[o->unk94].y;
        break;
    }
    if (o->unk9C != 0) {
        func_0024ac08(o->unk9C, r);
        p2[0] += r[0];
        p2[1] += r[1];
    }
}
QW *func_0023fb90(Obj *, QW *);
CONTEXT_ONLY QW *func_0023fd58(Obj *o, QW *r) {
    s32 n = o->unk4->unk6C->unkBE;
    f32 a, b;
    s32 p;
    a = n * 0.017453289f;
    if (a > 4.71238803863525390625f) a = 4.71238803863525390625f;
    p = o->unk9FC;
    b = p * 0.017453289f;
    if (b > 4.71238803863525390625f) b = 4.71238803863525390625f;
    if (n < p) {
        o->unkA00 = a;
        o->unkA04 = b;
        func_002492d0(o->unkA08, 128.0f, -12.799999237060546875f, 0.0f, 128.0f);
    } else if (p < n) {
        o->unkA00 = b;
        o->unkA04 = a;
        func_002492d0(o->unkA08, 0.0f, 12.799999237060546875f, 0.0f, 128.0f);
    }
    if (func_002492e8(o->unkA08, D_002BBDFC) == 1) {
        o->unkA00 = o->unkA04;
    }
    r = func_0023fb90(o, func_0023fad0(o, r));
    o->unk9FC = n;
    return r;
}

static inline void qset(QW *q, u64 lo, u64 hi) {
    q->lo = lo;
    q->hi = hi;
}
void func_00241260(Obj *o) {
    s32 a[4];
    s32 b[2];
    QW *q;
    QW *p = (QW *)D_00351E10;
    D_00651D64 = p;
    D_00651D60 = p + 1;
    func_00240b68(o);
    D_00651D60 = func_0023ee80(o, D_00651D60);
    D_00651D60 = func_0023dfc0(o, D_00651D60);
    func_00237018(D_00651D64, D_00651D60 - D_00651D64, 1);
    D_00651D64 = p;
    { QW *t = p + 1; u64 lo = 0x1000000000008001; t->hi = 14; t->lo = lo; }
    p += 2;
    D_00651D60 = p;
    q = D_00651D60;
    q->lo = o->unk70->unk18;
    D_00651D60->hi = 6;
    D_00651D60++;
    if (o->unkA18) D_00651D60 = func_0023f920(o, D_00651D60);
    D_00651D60 = func_0023f688(o, D_00651D60);
    if (o->unk0 == 0 && o->unk4->unk130->unk4C == 0 && o->unkA18) D_00651D60 = func_0023fd58(o, D_00651D60);
    D_00651D60 = func_0023dfd8(o, D_00651D60);
    if (o->unk0 == 1 || o->unk0 == 2) {
        func_0023d528(o, a, b);
        q = D_00651D60;
        D_00651D60 = q + 1;
        D_00651D60 = func_00237008(0x42, 0x8000000048, q + 1);
        func_00236fd8(q, D_00651D60);
        D_00651D60 = func_00240ae0(o->unk520, b[0], b[1], o->unkA1C, D_00651D60);
        q = func_00240ae0(o->unk780, b[0], b[1], o->unkA1C, D_00651D60);
        D_00651D60 = q + 1;
        D_00651D60 = func_00237008(0x42, 0x8000000044, q + 1);
        func_00236fd8(q, D_00651D60);
    }
    func_00237018(D_00651D64, D_00651D60 - D_00651D64, 1);
}
