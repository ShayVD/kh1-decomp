/* wm.x func_00f25588: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f22ac8(void);
void func_00f22d70(void);
extern s32 D_00F878E0;
extern s32 D_00F878E8;
extern s32 D_00FBAA90;

void func_00f25588(void) {
    s32 i;
    while (D_00F878E8 == 0) {
        if (D_00FBAA90 == 3) func_00f22ac8();
        func_001bfac8();
    }
    for (i = 0; i < D_00F878E0; i++) {
        if (D_00FBAA90 == 3) func_00f22ac8();
        func_001bfac8();
    }
    func_00f22d70();
}
