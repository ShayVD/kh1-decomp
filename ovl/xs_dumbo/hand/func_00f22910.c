/* xs_dumbo.x func_00f22910: matched by hand. */
#include "ovl.h"

typedef struct { OvlMtx m[10]; f32 ang[10]; s32 pad[2]; OvlVec in[100]; OvlVec out[100]; } Wk;
extern Wk D_00F2BB20;
void func_00249518(OvlMtx, f32);
void func_00f22910(void) {
    OvlMtx m;
    s32 i, j;
    OvlVec *in = D_00F2BB20.in;
    OvlVec *out = D_00F2BB20.out;
    for (i = 0; i < 10; i++) {
        func_00249518(m, D_00F2BB20.ang[i]);
        PlatVu0MulMatrix(m, D_00F2BB20.m[i], m);
        for (j = 0; j < 10; j++) {
            PlatVu0ApplyMatrix(*out, m, *in);
            out++;
            in++;
        }
    }
}
