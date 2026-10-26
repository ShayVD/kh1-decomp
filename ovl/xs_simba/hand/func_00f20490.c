/* xs_simba.x func_00f20490: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x70]; s32 f70; } Obj;
void func_0012cc38(s32, s32);
void func_0012ccb0(s32);
s32 func_0013aa60(void);
extern Obj *D_00F21C34;
extern Obj *D_00F21C38;
extern s32 D_00F21C40;
extern s32 D_00FA6A10;
void func_00f20490(void) {
    s32 v;
    if (D_00FA6A10 == 1 && D_00F21C40 != 0) {
        func_0012cc38(3, 0x5D);
    } else {
        func_0012cc38(3, 0x5C);
        if (func_0013aa60() != 0) {
            func_0012ccb0(3);
        }
    }
    v = D_00F21C34->f70;
    if ((v != 0 && v != 0x26) || D_00F21C38->f70 != 0) {
        func_0012ccb0(3);
    }
}
