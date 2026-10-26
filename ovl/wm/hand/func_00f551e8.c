/* wm.x func_00f551e8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x40]; u8 c0[4]; u8 c1[4]; u8 pad2[0x7E - 0x48]; s16 area; } WmObjC;
extern u8 D_00379F28[][4];
extern u8 D_0037A028[][4];
extern WmObjC *D_00F9B540;

void func_00f551e8(void) {
    D_00F9B540->c0[0] = D_00379F28[D_00F9B540->area][0];
    D_00F9B540->c0[1] = D_00379F28[D_00F9B540->area][1];
    D_00F9B540->c0[2] = D_00379F28[D_00F9B540->area][2];
    D_00F9B540->c1[0] = D_0037A028[D_00F9B540->area][0];
    D_00F9B540->c1[1] = D_0037A028[D_00F9B540->area][1];
    D_00F9B540->c1[2] = D_0037A028[D_00F9B540->area][2];
}
