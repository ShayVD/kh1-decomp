/* gb.x func_00f510c8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[176]; s32 x; s32 y; } Obj;
typedef struct { s32 x0, x4; u32 x8; } Pad;
extern Pad D_002C5AD0;
extern s32 D_00F82DAC, D_00F829EC, D_00F82DA8, D_00F829F0, D_00F82DB4, D_00F82DB0, D_00F82DB8, D_00F829D4, D_00F829D8;
void func_001f8f30(Obj *);
s32 func_001f4390(Obj *);
void func_001f3840(Obj *);
void func_0011d768(s32);
void func_00f43350(void);
void func_00f41c98(Obj *, s32, s32, s32, s32);
void func_00f41ac8(Obj *, s32, s32, s32, s32);
void func_00f510c8(Obj *o) {
    func_001f8f30(o);
    if (func_001f4390(o)) {
        u32 b = D_002C5AD0.x8;
        if (b & 0x6000) {
            if (b & 0x4000) D_00F82DAC = 1;
            D_00F829EC = 1;
            func_001f3840(o);
            b = D_002C5AD0.x8;
            b &= 0x2000;
            if (b) func_0011d768(2);
            else func_0011d768(3);
        } else if ((b | (b >> 24)) & 0xA0) {
            s32 v = (D_00F82DA8 + 1) & 1;
            D_00F82DA8 = v;
            D_00F82DAC = v;
            func_0011d768(1);
        }
    }
    func_00f43350();
    func_00f41c98(o, D_00F829F0, 3, D_00F82DB4, D_00F82DB0);
    func_00f41ac8(o, D_00F82DA8, 160, D_00F82DB8 + 216, 110);
    if (D_00F829EC == 0) {
        if (D_00F82DA8) D_00F829D4 = (o->x >> 4) - 1424;
        else D_00F829D4 = (o->x >> 4) - 1534;
        D_00F829D8 = (o->y >> 4) - 1648;
    }
}
