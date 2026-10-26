/* wm.x func_00f4d0a0: the twin of gb.x func_00f25fa8 (tools/ovl/twins.py). */
/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK func_00f22b48;
extern M2C_UNK func_00f25cb0;
extern s32 D_00F56D90;
extern s32 D_00F56EC0;
extern s32 D_00F74490;
extern s32 D_00F7F4E0;
s32 func_001c01b0(s32, s32, ...);
void func_001b9bb0(s32, s32);
void func_001b9ec0(void);
void func_001ba708(s32);
void func_001ba768(s32);
void func_001ba778(s32, s32, s32);
void func_001bfac8(void);
void func_00f25bc8(void);
void func_00f25e48(void);

void func_00f4d0a0(s32 arg0, s32 arg1, s32 arg2) {
    func_001ba778(arg0, arg1, arg2);
    func_001bfac8();
    func_001ba778(arg0, 0, 0);
    func_001bfac8();
}

