/* wm.x func_00f39b10: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xFC]; s32 fFC; } Obj39b10;
typedef struct { u8 pad[0x10]; s32 type; } Ev39b10;
void func_00f37770(s32, Obj39b10 *, Ev39b10 *, s32);
s32 func_00f37c08(Obj39b10 *, Ev39b10 *, s32);
s32 func_00f39220(Obj39b10 *, Ev39b10 *, s32);
s32 func_00f39910(Obj39b10 *, Ev39b10 *, s32);
s32 func_00f39920(Obj39b10 *, Ev39b10 *, s32);
s32 func_00f397f8(Obj39b10 *, Ev39b10 *, s32);
s32 func_00f39448(s32, Obj39b10 *, Ev39b10 *, s32);
s32 func_00f36e78(s32, Obj39b10 *, Ev39b10 *);
s32 func_00f37578(Obj39b10 *, Ev39b10 *);
s32 func_00f37648(Obj39b10 *, Ev39b10 *);
s32 func_00f37538(Obj39b10 *, Ev39b10 *);
s32 func_00f374b0(Obj39b10 *, Ev39b10 *);
s32 func_00f20020(void);
s32 func_00f38bf8(Obj39b10 *, Ev39b10 *);
s32 func_00f38b70(Obj39b10 *, Ev39b10 *);
s32 func_00f39708(Obj39b10 *, Ev39b10 *, s32);
extern s32 D_00F9B2EC;

void func_00f39b10(Obj39b10 *arg0, Ev39b10 *arg1, s32 arg2) {
    switch (arg1->type) {
    case 2:
        func_00f37770(0, arg0, arg1, arg2);
        return;
    case 7:
        func_00f37c08(arg0, arg1, arg2);
        return;
    case 10:
        func_00f37770(2, arg0, arg1, arg2);
        return;
    case 8:
        func_00f39220(arg0, arg1, arg2);
        return;
    case 9:
        func_00f39910(arg0, arg1, arg2);
        return;
    case 3:
        func_00f39920(arg0, arg1, arg2);
        return;
    case 4:
        func_00f397f8(arg0, arg1, arg2);
        return;
    case 6:
        if (arg0->fFC != 0) {
            arg0->fFC = 0;
            return;
        }
        return;
    case 11:
        func_00f39448(0, arg0, arg1, arg2);
        return;
    case 12:
        func_00f39448(1, arg0, arg1, arg2);
        return;
    case 14:
        if (D_00F9B2EC == 0) {
            func_00f36e78(0, arg0, arg1);
            return;
        }
    default:
        return;
    case 13:
        if (D_00F9B2EC == 0) {
            func_00f36e78(1, arg0, arg1);
            return;
        }
        break;
    case 16:
        func_00f37578(arg0, arg1);
        return;
    case 15:
        func_00f37648(arg0, arg1);
        return;
    case 17:
        func_00f37538(arg0, arg1);
        return;
    case 18:
        func_00f374b0(arg0, arg1);
        return;
    case 20:
        if (func_00f20020() == 0) {
            func_00f38bf8(arg0, arg1);
            return;
        }
        func_00f38b70(arg0, arg1);
        return;
    case 21:
        func_00f39708(arg0, arg1, arg2);
        return;
    }
}
