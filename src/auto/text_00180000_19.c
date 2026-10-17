/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void pppKeMdlDttReset(s32 arg0, void *arg1) {
  s8 *new_var2;
  void *temp_a0;
  s32 **new_var;
  new_var = (s32 **) (((s8 *) arg1) + 0xC);
  temp_a0 = arg0 + (*(*new_var));
  *((s32 *) ((new_var2 = (s8 *) (temp_a0 + 0xA0)) + 8)) = (*((s64 *) (((s8 *) temp_a0) + 0xA0)) = 0);
}
