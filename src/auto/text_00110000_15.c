/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_0048CFF8;
extern volatile s32 D_002A3F50[];
void func_00101728(s32);
void func_00112270(s32, s32);
void func_0011c7c0(s32, s32, s32);
void func_0011d4e0(s32);
void func_00157668(void);
void sprintf(s32, s32, ...);
void strcat(s32, s32);
void strcpy(s32, s32);

void func_00112298(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[20];
    func_00112270(arg0, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x10));
    sprintf((s32) sp, (s32) &D_0048CFF8, arg1 + 1);
    if (M2C_FIELD(sp, s8 *, 0x0) == 0x20) {
        M2C_FIELD(sp, s8 *, 0x0) = 0x30;
    }
    strcpy(arg3, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat(arg3, (s32) sp);
}

void func_00112d28(void) {
    func_00157668();
    D_002A3F50[0] = 0;
    D_002A3F50[1] = 0;
    func_0011c7c0(0, 0, 0x168);
    func_0011c7c0(1, 0, 0x168);
    func_0011d4e0(0x168);
    func_00101728(0x168);
}
