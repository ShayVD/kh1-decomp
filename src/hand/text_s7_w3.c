#include "common.h"


typedef struct {
    u8 pad0[0x14];
    f32 x14;
    u8 pad18[0x3b0 - 0x18];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
    f32 v3c0[4];
} Pc;
f32 sinf(f32);
void func_0014cd38(Pc *);
extern f32 D_002BBDFC;

static inline f32 mn(f32 x, f32 l) { return x < l ? x : l; }
void func_0014cdc8(Pc *o, f32 *v) {
    f32 a;
    f32 b;
    f32 y;

    a = o->x3b0;
    b = o->x3b8;
    if (a < b) {
        a = sinf(a / b * 3.1415928f * 0.5f);
        a = sinf(a * 3.1415928f * 0.5f);
        y = o->x3b4 + a * o->x3bc; v[1] = y - o->x14;
        func_0014cd38(o);
    } else {
        a -= b;
        y = o->x3b4 + o->x3bc + 0.4846938625f * a * a * 0.5f;
        v[1] = mn(y - o->x14, D_002BBDFC * 20.0f);
    }
    o->v3c0[1] = v[1];
}

/* func_001cb738 is in src/msgwin/msgwin.c, func_001d0380 in src/vm/vm_lib.c. */
#include "data/data_002B.h"
#include "data/data_003C.h"
#include "data/pieces/D_002BBDFC.h"
