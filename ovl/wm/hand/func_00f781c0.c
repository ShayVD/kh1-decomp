/* wm.x func_00f781c0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[176]; s32 x; s32 y; } Obj;
typedef struct { s32 x0, x4; u32 x8; } Pad;
extern Pad D_002C5AD0;
extern s32 D_0108F56C, D_0108F1AC, D_0108F568, D_0108F1B0, D_0108F574, D_0108F570, D_0108F578, D_0108F194, D_0108F198;
void func_001f8f30(Obj *);
s32 func_001f4390(Obj *);
void func_001f3840(Obj *);
void func_0011d768(s32);
void func_00f6a448(void);
void func_00f68d90(Obj *, s32, s32, s32, s32);
void func_00f68bc0(Obj *, s32, s32, s32, s32);
void func_00f781c0(Obj *o) {
    func_001f8f30(o);
    if (func_001f4390(o)) {
        u32 b = D_002C5AD0.x8;
        if (b & 0x6000) {
            if (b & 0x4000) D_0108F56C = 1;
            D_0108F1AC = 1;
            func_001f3840(o);
            b = D_002C5AD0.x8;
            b &= 0x2000;
            if (b) func_0011d768(2);
            else func_0011d768(3);
        } else if ((b | (b >> 24)) & 0xA0) {
            s32 v = (D_0108F568 + 1) & 1;
            D_0108F568 = v;
            D_0108F56C = v;
            func_0011d768(1);
        }
    }
    func_00f6a448();
    func_00f68d90(o, D_0108F1B0, 3, D_0108F574, D_0108F570);
    func_00f68bc0(o, D_0108F568, 160, D_0108F578 + 216, 110);
    if (D_0108F1AC == 0) {
        if (D_0108F568) D_0108F194 = (o->x >> 4) - 1424;
        else D_0108F194 = (o->x >> 4) - 1534;
        D_0108F198 = (o->y >> 4) - 1648;
    }
}
