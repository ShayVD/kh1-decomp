/* xl_limit.x func_00f21938: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x28]; s32 f28; } Sub14C;
typedef struct { u8 pad[0x14C]; Sub14C *f14C; } Actor;
void func_0012cc38(s32, s32);
void func_0012ccb0(s32);
s32 func_00130030(Actor *);
extern Actor *D_002E26A0;
extern s32 D_00F23E14;
void func_00f21938(void) {
    Actor *a;
    if (D_00F23E14 < 4) {
        func_0012cc38(0, 0x5F);
    } else {
        func_0012cc38(0, 0x60);
    }
    a = D_002E26A0;
    if (D_00F23E14 < 5 && func_00130030(a) != 0 && (a->f14C->f28 & 0x10000)) {
        return;
    }
    func_0012ccb0(0);
}
