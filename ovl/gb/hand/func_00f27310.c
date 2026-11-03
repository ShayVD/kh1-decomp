/* gb.x func_00f27310: matched by hand. */
#include "ovl.h"

s32 func_00f23ec0(s32);
s32 func_00f259d8(s32);
extern s32 D_00F61368;

f32 func_00f27310(s32 id) {
    switch (D_00F61368) {
    case 0:
        if (func_00f23ec0(id) > 0) {
            break;
        }
        return 0.5f;
    case 1:
        if (func_00f259d8(id) == 0) {
            return 0.5f;
        }
        break;
    }
    return 1.0f;
}
