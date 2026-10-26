/* xs_mushu.x func_00f20250: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x160]; s64 f160; } Pl;
s32 func_0013aa60(void);
s32 func_00147be0(s32);
s32 func_00157560(s32);
void func_00f20098(s32);
s32 func_00f20a98(void);
extern f32 D_002BBDFC;
extern u8 *D_00304B70;
extern f32 D_00304B7C;
extern s32 D_00F21380;
extern Pl *D_00F21384;
extern s32 D_00F21388;
extern s32 D_00F2138C;
extern s32 D_00F21398;
s32 func_00f20250(void) {
    D_00304B7C -= D_00304B70[1] * D_002BBDFC;
    switch (D_00F21398) {
    case 1:
        break;
    case 0:
        if (func_0013aa60()) {
            func_00f20098(100);
        }
        break;
    case 100:
        if (func_00f20a98() == 0 && func_00147be0(D_00F21380) == 0 && !((s32)(D_00F21384->f160 >> 5) & 1)
            && func_00157560(D_00F21388) != 2) {
            func_00f20098(101);
        }
        break;
    case 101:
        D_00F2138C = 0;
        return 4;
    }
    return 0;
}
