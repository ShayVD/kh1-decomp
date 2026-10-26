/* xs_dumbo.x func_00f21ae8: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0, f4, f8, fC; OvlMtx m[10]; f32 ang[10]; s32 f2B8; } Wk;
extern Wk D_00F2BB10;
f32 cosf(f32);
f32 sinf(f32);
extern f32 D_00F2BAD0;
extern f32 D_00F2BAD4;
extern f32 D_00F2BAD8;
extern f32 D_00F2BB08;
void func_00f21ae8(void) {
    s32 i;
    f32 c, s;
    f32 one = 1.0f;
    for (i = 0; i < 10; i++) {
        c = cosf(i * D_00F2BAD0 * 3.14159257412f / 180.0f + D_00F2BAD4 * D_00F2BB10.f2B8 * 3.14159257412f / 180.0f);
        s = one + (D_00F2BAD8 - one) * sinf(i * 10.0f * 3.14159257412f / 180.0f);
        D_00F2BB10.ang[i] = s * c * D_00F2BB08 + s * (1.0f - D_00F2BB08);
    }
}
