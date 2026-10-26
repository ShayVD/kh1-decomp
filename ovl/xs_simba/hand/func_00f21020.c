/* xs_simba.x func_00f21020: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; s32 f4; } Sp;
typedef struct { u8 pad[0x10]; f32 pos[4]; } Obj;
void func_00f21898(Sp *, void *, s32, f32 *);
extern Obj *D_00F21C34;
extern Sp D_00FA6F38;
extern u8 D_00FA6F50[];

void func_00f21020(void) {
    f32 v[4];
    PlatVu0CopyVector(v, D_00F21C34->pos);
    func_00f21898(&D_00FA6F38, D_00FA6F50, 0x80, v);
    D_00FA6F38.f4 |= 1;
}
