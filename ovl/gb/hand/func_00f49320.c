/* gb.x func_00f49320: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[176]; s32 x; s32 y; u8 pad2[6]; s16 hbe; s16 pad3; s16 hc2; } Obj;
typedef struct { s32 x0, x4; u32 x8; } Pad;
typedef struct { s32 v[2]; } T2;
extern Pad D_002C5AD0;
extern T2 D_00F74070;
extern u16 D_00F711E8[];
extern u16 D_00F82B08[];
extern u16 D_00F82B28[];
extern s32 D_00F829C8;
extern s32 D_00F705E0;
extern s32 D_00F705E4;
extern s32 D_00F829D4, D_00F829D8, D_00F82AF8, D_00F82AFC, D_00F82B00;
s32 func_001ba3f0(s32);
void func_001bc4d0(void);
s32 func_001f42b8(Obj *);
void func_001fd858(Obj *);
void func_001bb558(void);
void func_00202fc0(Obj *);
void func_001f8ee0(Obj *);
s32 func_001fd618(Obj *);
s32 func_001fd638(Obj *);
s32 func_001fd590(Obj *);
s32 func_001fd548(Obj *);
s32 func_00f39330(void);
s32 func_00f39340(void);
void func_001efb18(s32, s32);
void func_002078f0(Obj *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001f8f30(void);
s32 func_001f4390(Obj *);
void func_001f3840(Obj *);
void func_0011d768(s32);

void func_00f49320(Obj *o)
{
    T2 t = D_00F74070;
    s32 n = 7;
    s32 k;
    s32 i, y, sel;

    if (func_001ba3f0(64) <= 0 && func_001ba3f0(65) <= 0) n = 6;
    D_00F82B08[0] = D_00F711E8[0];
    D_00F82B08[1] = D_00F711E8[1];
    D_00F82B28[1] = 1;
    D_00F82B08[2] = D_00F711E8[2];
    D_00F82B28[2] = 2;
    D_00F82B08[3] = D_00F711E8[3];
    D_00F82B28[3] = 3;
    D_00F82B08[4] = D_00F711E8[4];
    D_00F82B28[4] = 4;
    D_00F82B28[0] = 0;
    k = 5;
    if (func_001ba3f0(64) > 0 || func_001ba3f0(65) > 0) {
        D_00F82B28[5] = 5;
        k = 6;
        D_00F82B08[5] = D_00F711E8[5];
    }
    D_00F82B08[k] = D_00F711E8[6];
    D_00F82B28[k] = 6;
    func_001bc4d0();
    if (func_001f42b8(o) && D_00F829C8 == 0) func_001fd858(o);
    func_001bb558();
    func_00202fc0(o);
    func_001f8ee0(o);
    i = func_001fd618(o);
    y = func_001fd590(o);
    sel = func_001fd548(o);
    o->hbe = 0;
    o->hc2 = *(u16 *)&D_00F705E0 << 4;
    func_001efb18(func_00f39330(), func_00f39340());
    for (k = 9; k >= 0; k--) {
        if (i < n) {
            func_002078f0(o, t.v[sel == i], 2, 0, 0, y, D_00F705E0, D_00F705E4, (s16)D_00F82B08[i]);
            if (sel == i && func_001f4390(o)) {
                D_00F829D4 = (o->x >> 4) + D_00F705E0 - 1792;
                D_00F829D8 = (o->y >> 4) + y - 1856;
            }
            y += 28;
        }
        i++;
    }
    func_001f8f30();
    if (func_001f4390(o)) {
        if (D_002C5AD0.x8 & 0x6000) {
            D_00F82AFC = func_001fd618(o) << 4;
            D_00F82B00 = func_001fd638(o) << 4;
            if (D_002C5AD0.x8 & 0x2000) {
                D_00F82AF8 = sel;
                func_0011d768(2);
            } else {
                D_00F82AF8 = -1;
                func_0011d768(3);
            }
            func_001f3840(o);
            D_00F829C8 = 1;
        }
    }
}
