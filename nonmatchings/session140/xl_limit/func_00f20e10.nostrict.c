/* 2 words: mtc1 zero,$f21 / li s3,10 swapped in the >= 60 default block (EE8/EEC); needs the KH1_REG pin on mot (else s0/s4 swap, 15 words). nostrict mode. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; void *fC; } Res;
typedef struct { u8 pad[8]; f32 *scale; } Fx;
typedef struct {
    s32 flags;
    u8 pad4[0x2C];
    OvlVec v30;
    u8 pad40[0x380];
    OvlVec v3c0;
} LimObj;
f32 func_00f209e0(LimObj *, f32);
void func_00130340(LimObj *, s32, f32);
Res *func_00130578(LimObj *, s32, f32);
void func_001315c0(LimObj *, s32, f32 *, f32);
Fx *func_00147ed8(s32, s32, s32, f32 *);
void func_00147d50(Fx *, f32 *);
void func_00147790(s32);
void func_00f20940();
void func_00f20ac8();
void func_00f206e8(LimObj *, void *, s32);
extern LimObj *D_002E26A0;
extern u8 D_002E31B0[];
extern s32 D_00F23208;
extern f32 D_00F23484;

void func_00f20e10(void) {
    LimObj *o;
    OvlVec v;
    Fx *fx;
    s32 kind;
    s32 n;
    register s32 mot KH1_REG("s4");
    f32 h;
    f32 s;
    f32 *sc;

    mot = 0xF7;
    if (D_00F23484 < 40.0f) {

        kind = 5;
        h = 10.0f;
        s = 0.0f;
        n = 10;

    } else if (D_00F23484 < 50.0f) {
        kind = 5;
        h = 20.0f;
        s = -4.0f;
        n = 17;
        func_00147790(3);
    } else {
        kind = 5;
        if (D_00F23484 < 60.0f) {
            kind = 6;
            n = 25;
            h = 30.0f;
            s = -8.0f;
            mot = 0xF8;
            func_00147790(4);
        } else {
            h = 10.0f;
            s = 0.0f;
            n = 10;
        }
    }
    o = D_002E26A0;
    func_00f209e0(o, h);
    sceVu0ScaleVector(o->v3c0, o->v30, s);
    func_00130340(o, mot | 0x01000000, 0.0f);
    func_00130578(o, 0x40000006, 8.0f)->fC = func_00f20ac8;
    func_001315c0(o, 48, v, 1.0f);
    fx = func_00147ed8(D_00F23208, kind, 20000, v);
    func_00147d50(fx, o->v30);
    sc = fx->scale;
    sc[2] = 1.5f;
    sc[1] = 1.5f;
    sc[0] = 1.5f;
    func_00f20940((s64)0xFFC0 << 46);
    func_00f206e8(o, D_002E31B0, n);
}
