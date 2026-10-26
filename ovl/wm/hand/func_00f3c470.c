/* wm.x func_00f3c470: matched by hand. */
#include "ovl.h"

u32 func_00f3f308(u16, s32);                        /* extern */

s32 func_00f3c470(void *arg0) {
    s32 temp_v1;
    s32 temp_a1;

    if (arg0 != NULL) {
        temp_v1 = M2C_FIELD(arg0, u16 *, 2);
        temp_a1 = (s32) temp_v1 < 2;
        if (temp_v1 != 2) {
            if ((temp_a1 == 0) && ((s32) temp_v1 < 7)) {
                if ((s32) temp_v1 >= 5) {
                    return 1;
                }
                goto block_8;
            }
            /* Duplicate return node #9. Try simplifying control flow for better match */
            return 0;
        }
        return func_00f3f308(M2C_FIELD(arg0, u16 *, 6), temp_a1) != 0;
    }
block_8:
    return 0;
}
