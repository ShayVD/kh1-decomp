/* The pppKeShpDtt class's frame (empty) and Con, default flags
 * (docs/modules.md "Session 50"); its draw is in keshpdttdraw.nostrict.c,
 * the draw's helpers in keshpdtt.nostrict.c.  Read from the code, not proved
 * by a boot. */

/* pppKeShpDttFrame (from auto/text_00190000.c). */
#include "m2c.h"
#include "ppp.h"
void pppKeShpDttFrame(void) {

}

/* pppKeShpDttCon (from auto/text_00190000_12.c). */
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

