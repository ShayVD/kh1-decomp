/* xs_tink.x func_00f20958: matched by hand (session 131b). */
#include "ovl.h"

typedef struct {
    f32 t;
    f32 vy;
    f32 g;
    f32 **obj;
    OvlVec dir;
} TinkHop;
extern TinkHop D_00F20ED0;
extern u8 *D_00F20D84;
extern OvlVec D_00F20EA0;
extern f32 D_00F20EC0, D_00F20EC4, D_00F20EC8;
extern f32 D_00F20EF0[3];
extern s32 D_00F20ECC;
extern void *D_00F20E90;
void func_0011ef10(s32, void *);
s32 func_00f20818(void);
void func_00f20958(void) {
    s32 i;

    PlatVu0CopyVector(D_00F20EA0, D_00F20D84 + 0x10);
    D_00F20EA0[1] -= 300.0f;
    D_00F20EC0 = 0.0f;
    D_00F20EC4 = 0.0f;
    D_00F20EC8 = 0.0f;
    D_00F20ED0.g = 0.1f;
    D_00F20ED0.t = 0.0f;
    D_00F20ED0.vy = 0.0f;
    D_00F20ED0.obj = NULL;
    for (i = 0; i < 3; i++) {
        D_00F20EF0[i] = (f32)(i + 1) * 100.0f;
    }
    D_00F20E90 = NULL;
    D_00F20ECC = 4;
    func_0011ef10(0x21728, func_00f20818);
}
