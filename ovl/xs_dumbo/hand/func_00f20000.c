/* xs_dumbo.x func_00f20000: matched by hand. */
#include "ovl.h"

void func_00130340(s32, s32, f32);
void func_00131500(s32);
void func_0014f658(s32, s32);
void func_00f20150(s32);
void func_00f20790(void);
extern s32 D_00F23200;
extern s32 D_00F23208;
extern s32 D_00F3CA80;
s32 func_00f20000(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
        D_00F23208 = arg1;
        func_00f20790();
        return 0;
    case 1:
        return D_00F3CA80;
    case 2:
        func_0014f658(D_00F23200, 0);
        func_00131500(D_00F23200);
        func_00130340(D_00F23200, 0, 0.0f);
        func_00f20150(101);
        return 0;
    }
    return 0;
}
