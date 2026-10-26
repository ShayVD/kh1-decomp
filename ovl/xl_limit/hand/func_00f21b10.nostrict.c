/* xl_limit.x func_00f21b10: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; void *fC; } Res;
typedef struct { u8 pad[8]; s32 f8; } Gs;
typedef struct { u8 pad[0x2C]; Gs *f2c; } Mdl;
typedef struct { u8 pad[0x14C]; Mdl *f14c; } Obj;
typedef struct { s32 f0; s32 f4; } Tgt;
s32 func_00122ff8(s32);
void func_0012ec60(s32, s32, f32 *);
void func_00130340(Obj *, s32, f32);
Res *func_00130578(Obj *, s32, f32);
void func_0013dc10(Obj *, s32);
void func_0013ecf8(Obj *, Tgt *, f32 *);
void func_001487f8(s32, s32, Obj *, s32);
extern Tgt D_002E31B0;
extern s32 D_00F23208;
extern s32 D_00F23E14;
void func_00f21a98(void);
void func_00f21ad8(void);
void func_00f21af8(void);

void func_00f21b10(Obj *arg0) {
    f32 v[4];
    s32 snd = 0xE9;
    s32 k;

    func_0013ecf8(arg0, &D_002E31B0, v);
    func_0013dc10(arg0, D_00F23E14++ + 47);
    if (func_00122ff8(D_002E31B0.f0) != 0) {
        func_0012ec60(D_002E31B0.f0, D_002E31B0.f4, v);
        PlatVu0SubVector(v, v, (u8 *)arg0 + 16);
        if (v[1] < -200.0f) {
            snd = 0xEC;
            func_00130340(arg0, D_00F23E14 == 5 ? 0x010000EB : 0x010000EA, 0.0f);
        }
    }
    *(u64 *)arg0->f14c->f2c |= 0x800000;
    if (D_00F23E14 == 5) {
        arg0->f14c->f2c->f8 = D_00F23208;
        k = 6;
    } else {
        k = 1;
    }
    func_001487f8(D_00F23208, k | 0x800, arg0, 48);
    func_00130578(arg0, snd, 0.0f)->fC = func_00f21a98;
    func_00130578(arg0, 238, 0.0f)->fC = func_00f21ad8;
    func_00130578(arg0, 0x40100000, 0.0f)->fC = func_00f21af8;
}
