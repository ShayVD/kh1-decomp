/* func_00241260 ~104w/size -8 (nostrict): orig reloads D_00651D60 after the 'lo' store of the tex packet (D60->hi via reloaded ptr, then D60++ reloaded); ours folds D60 = D_00351E10+0x20. Rest matches in shape. Header = first 53 lines of src/hand/nostrict/text_00240000_h75.c + func_0023fd58 proto. */
#include "common.h"
typedef struct { u64 lo, hi; } QW;
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
void func_0023d528(Obj *, s32 *, s32 *);
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
QW *func_00240ae0(void *, s32, s32, QW *, f32);
QW *func_00237008(s32, u64, QW *);
void func_00236fd8(QW *, QW *);
void func_00237018(void *, s32, s32);

QW *func_0023fd58(Obj *, QW *);

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
    p[1].lo = 0x1000000000008001;
    p[1].hi = 14;
    p += 2;
    D_00651D60 = p;
    D_00651D60->lo = o->unk70->unk18;
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
        D_00651D60 = func_00240ae0(o->unk520, b[0], b[1], D_00651D60, o->unkA1C);
        q = func_00240ae0(o->unk780, b[0], b[1], D_00651D60, o->unkA1C);
        D_00651D60 = q + 1;
        D_00651D60 = func_00237008(0x42, 0x8000000044, q + 1);
        func_00236fd8(q, D_00651D60);
    }
    func_00237018(D_00651D64, D_00651D60 - D_00651D64, 1);
}
