/* wm.x func_00f5e178: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; u8 b8; } I5e178;
typedef struct { s32 r; u8 pad[36]; } E5e178;
I5e178 *func_001bb658(s32);
s32 func_00f4a958(s32);
s32 func_00f650e8(s32);
void func_001be820(void *, s32);
extern E5e178 *D_0108DB90[192];
extern E5e178 D_0108D190[];

void func_00f5e178(void) {
    s32 i;
    I5e178 *info;
    s32 r;
    s32 n;

    for (i = 191; i >= 0; i--) {
        D_0108DB90[i] = 0;
    }
    n = 0;
    for (i = 128; i < 160; i++) {
        info = func_001bb658(i);
        if (info != NULL && info->b8 != 255) {
            r = func_00f650e8(func_00f4a958(info->b8));
            if (r != 0) {
                func_001be820(&D_0108D190[n], 40);
                D_0108D190[n].r = r;
                D_0108DB90[info->b8] = &D_0108D190[n];
                n++;
            }
        }
    }
}
