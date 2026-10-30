/* wm.x func_00f355a8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; u8 b8; } I355a8;
typedef struct { s32 r; u8 pad[36]; } E355a8;
I355a8 *func_001bb658(s32);
s32 func_00f200a8(s32);
s32 func_00f650e8(s32);
void func_001be820(void *, s32);
extern E355a8 *D_00FCE040[192];
extern E355a8 D_00FCD640[];

void func_00f355a8(void) {
    s32 i;
    I355a8 *info;
    s32 r;
    s32 n;

    for (i = 191; i >= 0; i--) {
        D_00FCE040[i] = 0;
    }
    n = 0;
    for (i = 128; i < 160; i++) {
        info = func_001bb658(i);
        if (info != NULL && info->b8 != 255) {
            r = func_00f650e8(func_00f200a8(info->b8));
            if (r != 0) {
                func_001be820(&D_00FCD640[n], 40);
                D_00FCD640[n].r = r;
                D_00FCE040[info->b8] = &D_00FCD640[n];
                n++;
            }
        }
    }
}
