/* wm.x func_00f35a88: matched by hand. */
#include "ovl.h"

typedef struct { f32 x; u8 b4; u8 pad5[35]; f32 h; u8 pad2c[16]; f32 z; } O35a88;
typedef struct { s32 x0; s32 id; } L35a88;
typedef struct { u8 pad[0x540]; s32 x540; } G35a88;
extern G35a88 *D_00F864C0;
extern s32 D_00F8C2E0;
L35a88 *func_00f3b460(s32);
s32 func_00f3b480(void);
O35a88 *func_00f3f260(s32, s32);
f32 *func_00f2c848(void);
int abs(int);

O35a88 *func_00f35a88(O35a88 *arg0, s32 arg1) {
    s32 i;
    O35a88 *o;
    s32 dx, dz;
    f32 f;
    D_00F8C2E0 = 0;
    for (i = 0; i < func_00f3b480(); i++) {
        o = func_00f3f260(func_00f3b460(i)->id, D_00F864C0->x540);
        if (o->b4 != 1) continue;
        if (o == arg0) continue;
        dx = abs((s32)(o->x - arg0->x));
        dz = abs((s32)(o->z - arg0->z));
        if (dx < 5 && dz < 200) {
            f = *func_00f2c848();
            if (arg1) f = -f;
            if (f >= 0.0f) {
                D_00F8C2E0 = !arg1 ? 2 : 1;
                if (arg0->h > o->h) return arg0;
                return o;
            } else {
                D_00F8C2E0 = !arg1 ? 1 : 2;
                if (arg0->h < o->h) return arg0;
                return o;
            }
        }
    }
    return arg0;
}
