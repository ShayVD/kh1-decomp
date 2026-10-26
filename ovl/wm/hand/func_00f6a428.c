/* wm.x func_00f6a428: the twin of gb.x func_00f43330 (tools/ovl/twins.py). */
/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00FB4F78;
extern s32 D_00F70268;
void func_0024bc08(s32, s32);

void func_00f6a428(s32 arg0) {
    func_0024bc08(arg0, (s32) &D_00FB4F78);
}
