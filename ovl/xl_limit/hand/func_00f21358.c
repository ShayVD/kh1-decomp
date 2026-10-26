/* xl_limit.x func_00f21358: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x70]; s32 x70; u8 pad74[0xF0]; s32 x164; s32 pad168; f32 f16c; } LimO;
void func_00131500(LimO *);
s32 func_00130340(LimO *, s32, f32);
extern s32 D_00F23E04;
s32 func_00f21358(LimO *arg0, s32 arg1) {
    if ((D_00F23E04 >= 8 || (arg0->x164 == 217 && arg0->f16c >= 20.0f)) && arg1 != 0) {
        func_00131500(arg0);
        func_00130340(arg0, 6, 8.0f);
        return 2;
    }
    return arg0->x70;
}
