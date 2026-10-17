/* Game code from files built without gcc's delay-slot filling (their
 * `jr ra` slots stay nop; kh1.toml). */
#include "common.h"

extern u8 D_00533BA0[];

u8 *func_001477c8(s32 a) {
    return D_00533BA0 + a;
}
