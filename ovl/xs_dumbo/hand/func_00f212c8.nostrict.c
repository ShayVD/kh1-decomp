/* xs_dumbo.x func_00f212c8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; f32 *fC; s8 *f10; } Obj;
void func_00249950(f32 *, f32, f32);
extern s32 D_00F3C9D8;
extern Obj *D_00F44AA0;
extern f32 D_00F44AA4;
s32 func_00f212c8(void) {
    if (D_00F3C9D8 != 101) {
        if (D_00F3C9D8 != 100) {
            goto other;
        }
        if (D_00F44AA0 != 0) {
            goto body;
        }
    }
    return 4;
other:
    if (D_00F44AA0 != 0) {
body:
    D_00F44AA4 -= 0.0999999977648f;
    func_00249950(&D_00F44AA4, 0.0f, 1.0f);
    D_00F44AA0->fC[0] = 1.0f;
    D_00F44AA0->fC[1] = 1.0f;
    D_00F44AA0->fC[2] = 1.0f;
    D_00F44AA0->fC[3] = D_00F44AA4;
    if (D_00F44AA4 == 0.0f) {
        *D_00F44AA0->f10 = 1;
        D_00F44AA0 = 0;
    }
    }
    return 0;
}
