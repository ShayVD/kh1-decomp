/* wm.x func_00f3f7c8: matched by hand. */
#include "ovl.h"

typedef struct { s32 a[3]; } V3f7c8;
extern V3f7c8 D_00FB7218;
extern s32 D_00F9B1E4;
extern s32 D_00F87068;
void func_001ed560(s32, s32, s32);
s32 func_00f218d8(void);
void func_00f67fd0(s32, s32);
void func_00f68008(s32, s32);
void func_00f68070(void);
void func_001bfac8(void);

void func_00f3f7c8(s32 arg0) {
    V3f7c8 t = D_00FB7218;
    s32 start;
    s32 *cur = &D_00F9B1E4;
    if (*cur == arg0) {
        return;
    }
    if (*cur != 0) {
        func_001ed560(0, 0, 480);
    }
    if (arg0 != 0) {
        start = func_00f218d8();
        func_00f67fd0(t.a[arg0 - 1], D_00F87068);
        if (*cur != 0) {
            while (func_00f218d8() - start < 60) {
                func_001bfac8();
            }
        }
        func_00f68008(t.a[arg0 - 1], D_00F87068);
        func_00f68070();
    }
    D_00F9B1E4 = arg0;
}
