/* xs_tink.x func_00f20690: matched by hand (session 131b). */
#include "ovl.h"

typedef struct {
    f32 t;
    f32 vy;
    f32 g;
    f32 **obj;
    OvlVec dir;
} TinkHop;
extern TinkHop D_00F20ED0;
extern void *D_00F20D80;
extern u8 *D_00F20D84;
extern OvlVec D_00F20EA0;
extern f32 D_002BBDFC;
extern u8 *D_00F20E90;
f32 **func_00147c98(void *, s32, s32);
f32 sinf(f32);
void func_00f20690(void) {
    TinkHop *h = &D_00F20ED0;
    OvlVec v;

    if (h->t == 0.0f) {
        h->obj = func_00147c98(D_00F20D80, 5, 20000);
        h->vy = 0.0f;
        h->g = 0.1f;
        PlatVu0SubVector(h->dir, D_00F20EA0, D_00F20D84 + 0x10);
        h->dir[1] = 0.0f;
        PlatVu0Normalize(h->dir, h->dir);
    }
    h->t += D_002BBDFC;
    if (h->t < 56.0f) {
        PlatVu0ScaleVector(v, h->dir, sinf(h->t * 0.11219974f) * 1.5f);
        h->g += D_002BBDFC * -0.008f;
        h->vy += h->g * D_002BBDFC;
        v[1] = h->vy;
        PlatVu0ScaleVector(v, v, D_002BBDFC);
        PlatVu0AddVector(D_00F20EA0, D_00F20EA0, v);
        PlatVu0CopyVector(*h->obj, D_00F20EA0);
    } else if (D_00F20E90 != NULL) {
        **(u8 **)(D_00F20E90 + 0x10) = 1;
        D_00F20E90 = NULL;
    }
}
