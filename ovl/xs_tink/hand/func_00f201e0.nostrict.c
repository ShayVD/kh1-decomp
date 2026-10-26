/* xs_tink.x func_00f201e0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x48]; s32 f48; } Sub;
typedef struct { u8 pad[0x6C]; Sub *f6C; } Pl;
s32 func_00122ff8(Pl *);
void func_001315c0(Pl *, s32, f32 *, f32);
void func_00141468(Pl *, s32);
void func_00148768(s32, s32, Pl *, s32, f32);
extern f32 D_002BBDFC;
extern Pl *D_002E26A0[];
extern s32 D_00F20D80;
extern f32 D_00F20EA0[];
extern f32 D_00F20EF0[];
void func_00f201e0(void) {
    OvlVec v;
    s32 i;
    Pl *p;
    for (i = 0; i < 3; i++) {
        if (D_00F20EF0[i] > 0.0f) {
            D_00F20EF0[i] -= D_002BBDFC;
        } else {
            D_00F20EF0[i] = 300.0f;
            p = D_002E26A0[i];
            if (func_00122ff8(p)) {
                func_001315c0(p, 0x8004, v, 0.0f);
                PlatVu0SubVector(v, v, D_00F20EA0);
                if (PlatVu0InnerProduct(v, v) < 90000.0f) {
                    func_00148768(D_00F20D80, 3, p, 0x8003, 0.0f);
                    func_00141468(p, D_002E26A0[0]->f6C->f48);
                }
            }
        }
    }
}
