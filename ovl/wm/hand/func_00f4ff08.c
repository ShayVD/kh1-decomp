/* wm.x func_00f4ff08: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 id; u8 pad2[6]; } WmEnt12;
typedef struct { u8 pad[4]; u16 n; } WmCnt;
typedef struct { u8 pad[0xA0]; WmCnt c; u8 pad2[0x110 - 0xA6]; WmEnt12 e[1]; } WmTbl;
typedef struct { f32 v; s32 a; s32 b; } WmBD;
extern WmTbl *D_00F9B540;
extern WmBD D_0108BD00[];
u8 *func_001bb658(s32);
s32 func_00f4aa00(s32);
s32 func_00f65160(s32, s32);

void func_00f4ff08(s32 arg0, s32 arg1, f32 add) {
    WmTbl *t = D_00F9B540;
    WmCnt *c = &t->c;
    s32 i;

    for (i = 0; i < c->n; i++) {
        s32 id = t->e[i].id - 1;
        if (id == arg0) {
            u8 *q = func_001bb658(id);
            if (q[9] != 0xFF) {
                f32 *v = &D_0108BD00[i].v;
                *v += add;
                if (arg1 != 0) {
                    f32 m = func_00f65160(func_00f4aa00(q[9]), -1);
                    if (m < *v) {
                        *v -= m;
                    }
                }
            }
        }
    }
}
