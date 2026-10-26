/* dkmovie.x func_00f23598: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x3DD48]; s32 fd; u8 pad1[0x3DF51 - 0x3DD4C]; s8 flag; s8 flag2; } MovieWork;
void func_00f22290(s32, MovieWork *);
void func_00f27ee8(s32, MovieWork *);
void func_00f23598(s32 arg0, s32 arg1, MovieWork *arg2) {
    if (arg2->flag != 0) {
        func_00f22290(arg1, arg2);
        return;
    }
    func_00f27ee8(arg1, arg2);
}
