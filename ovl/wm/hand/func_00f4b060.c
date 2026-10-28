/* wm.x func_00f4b060: matched by hand. */
#include "ovl.h"

typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 w : 4; } Cell;
s32 func_00f4b1e8(s32, s32, s32, s32);
s32 func_00f4b060(Cell pos, Cell size, s32 arg) {
    s32 x, y, z;
    for (y = pos.y; y < pos.y + size.y; y++) {
        for (z = pos.z; z < pos.z + size.z; z++) {
            for (x = pos.x; x < pos.x + size.x; x++) {
                if (func_00f4b1e8(x, y, z, arg)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
