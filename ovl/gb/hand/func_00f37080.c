/* gb.x func_00f37080: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; u8 b8; } I355a8;
typedef struct { s32 r; u8 pad[36]; } E355a8;
I355a8 *func_001bb658(s32);
s32 func_00f23860(s32);
s32 func_00f3dff0(s32);
void func_001be820(void *, s32);
extern E355a8 *D_00F813D0[192];
extern E355a8 D_00F809D0[];

void func_00f37080(void) {
    s32 i;
    I355a8 *info;
    s32 r;
    s32 n;

    for (i = 191; i >= 0; i--) {
        D_00F813D0[i] = 0;
    }
    n = 0;
    for (i = 128; i < 160; i++) {
        info = func_001bb658(i);
        if (info != NULL && info->b8 != 255) {
            r = func_00f3dff0(func_00f23860(info->b8));
            if (r != 0) {
                func_001be820(&D_00F809D0[n], 40);
                D_00F809D0[n].r = r;
                D_00F813D0[info->b8] = &D_00F809D0[n];
                n++;
            }
        }
    }
}
