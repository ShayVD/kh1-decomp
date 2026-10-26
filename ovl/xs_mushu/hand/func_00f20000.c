/* xs_mushu.x func_00f20000: matched by hand. */
#include "ovl.h"

extern void *D_00F21380;
extern s32 D_00F2138C;
void func_00f20098(s32);
void func_00f200e8(void);
void func_00f20430(void);
s32 func_00f20000(s32 arg0, void *arg1) {
    switch (arg0) {
    case 0:
        D_00F21380 = arg1;
        func_00f20430();
        return 0;
    case 1:
        return D_00F2138C;
    case 2:
        func_00f20098(101);
        return 0;
    case 3:
        func_00f200e8();
        return 0;
    }
    return 0;
}
