/* gb.x func_00f27310: matched by hand. */
#include "ovl.h"

s32 func_00f23ec0(void);
s32 func_00f259d8(void);
extern s32 D_00F61368;

f32 func_00f27310(void) {
    switch (D_00F61368) {
    case 0:
        if (func_00f23ec0() > 0) {
            break;
        }
        return 0.5f;
    case 1:
        if (func_00f259d8() == 0) {
            return 0.5f;
        }
        break;
    }
    return 1.0f;
}
