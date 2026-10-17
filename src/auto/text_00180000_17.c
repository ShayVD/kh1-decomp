/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void pppKeBornRnd6Con(s32 arg0, void *arg1) {
  void *temp_a0;
  void *new_var;
  temp_a0 = arg0 + (*(*((s32 **) (((s8 *) arg1) + 0xC))));
  new_var = temp_a0 + 0xA0;
  *((s16 *) (((s8 *) temp_a0) + 0xA0)) = 0;
  *((s8 *) (((s8 *) new_var) + 2)) = 0;
}
