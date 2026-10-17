/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void pppKeShpDttCon(s32 arg0, void *arg1) {
  void *temp_a0;
  s8 *new_var;
  s8 *new_var2;
  temp_a0 = arg0 + (*(*((s32 **) (((s8 *) arg1) + 0xC))));
  new_var = ((s8 *) temp_a0) + 0xA0;
  *((s64 *) new_var) = 0;
  new_var2 = (s8 *) (temp_a0 + 0xA0);
  *((s32 *) (new_var2 + 8)) = 0;
}
