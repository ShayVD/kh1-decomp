/* wm.x func_00f4e408: matched by hand. */
#include "ovl.h"

s32 func_00f4afb8(void);
s32 func_00f4cad0(void);
extern s32 D_00FA5AE8;

f32 func_00f4e408(void) {
    switch (D_00FA5AE8) {
    case 0:
        if (func_00f4afb8() > 0) {
            break;
        }
        return 0.5f;
    case 1:
        if (func_00f4cad0() == 0) {
            return 0.5f;
        }
        break;
    }
    return 1.0f;
}
