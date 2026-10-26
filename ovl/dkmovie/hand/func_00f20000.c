/* dkmovie.x func_00f20000: matched by hand. */
#include "ovl.h"

void func_00f20258(s32);
void func_00f20320(void);
s32 func_00f20230(void);
extern s32 (*D_00F28480)(void);
extern s32 (*D_00F28488)(void);
extern s32 D_00F2848C;
extern s16 D_00F28490;
extern void (*D_00F28498)(s32);
extern s32 (*D_00F2849C)(void);
extern s32 D_00F284A0;

s32 func_00f20000(u32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
        func_00f20258(arg1);
        break;
    case 1:
        func_00f20320();
        break;
    case 2:
        return func_00f20230();
    case 3:
        return D_00F28490;
    case 4:
        D_00F28480();
        break;
    case 5:
        return D_00F2849C();
    case 6:
        D_00F28498(arg1);
        break;
    case 7:
        D_00F28488();
        break;
    case 8:
        return D_00F284A0;
    case 9:
        return D_00F2848C;
    }
    return 0;
}
