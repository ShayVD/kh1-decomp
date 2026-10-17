/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void pppVertexApAtCon(s32 arg0, void *arg1) {
  void *new_var;
  void *temp_a0;
  temp_a0 = arg0 + (*(*((s32 **) (((s8 *) arg1) + 0xC))));
 do { *((s16 *) (((s8 *) (new_var = temp_a0 + 0xA0)) + 2)) = 0; } while (0);
  *((s16 *) (((s8 *) temp_a0) + 0xA0)) = 0;
}
