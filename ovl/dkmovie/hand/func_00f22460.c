/* dkmovie.x func_00f22460: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x3DD48]; s32 fd; u8 pad1[0x3DF51 - 0x3DD4C]; s8 flag; s8 flag2; } MovieWork;
s8 func_00f220d0(void);
extern s8 D_00F28680;
s8 func_00f22460(MovieWork *arg0) {
    if (arg0->flag2 != 0) {
        return D_00F28680;
    }
    if (func_00f220d0() == 0) {
        D_00F28680 = 0;
        return 0;
    }
    return 1;
}
