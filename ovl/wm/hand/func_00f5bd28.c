/* wm.x func_00f5bd28: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 id; u8 pad2[6]; } WmEnt12;
typedef struct { u8 pad[0xA4]; u16 n; u16 sx; u16 sy; u16 sz; u8 pad2[0x110 - 0xAC]; WmEnt12 e[1]; } WmTbl;
extern WmTbl *D_00F9B540;
extern s32 D_00F9B568;
void func_00f5ae98(s32, s32);
s32 func_00f68770(s32, s32, void *, s32, s32);

void func_00f5bd28(void) {
    f32 m[4][4];
    f32 t[4];
    s32 i;

    for (i = 0; i < D_00F9B540->n; i++) {
        switch (D_00F9B540->e[i].id - 1) {
        case 48:
            t[2] = D_00F9B540->sz * 0.5f * 200.0f;
            t[0] = D_00F9B540->sx * 0.5f * 200.0f;
            t[1] = -(D_00F9B540->sy * 0.5f) * 200.0f;
            t[3] = 1.0f;
            PlatVu0UnitMatrix(m);
            PlatVu0TransMatrix(m, m, t);
            func_00f5ae98(func_00f68770(55, 1, m, 0, D_00F9B568), 7);
            return;
        }
    }
}
