/* wm.x func_00f4aa20: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 x; } R4a;
R4a *func_001bb658(s32);
s32 func_001bb720(void);
s32 func_001bb730(void);
s32 func_00f4ad68(s32);

s32 func_00f4aa20(s32 cur) {
    s32 best = 10;
    s32 n = func_001bb720() + func_001bb730();
    s32 i;
    s32 id = 0;
    s32 x;
    s32 d;

    for (i = 0; i < n; i++) {
        x = func_001bb658(id)->x;
        d = (x - cur + 10) % 10;
        if (cur != x && x != 0) {
            if (d < best) {
                best = d;
            }
        }
        id = func_00f4ad68(id);
        if (id == 0) {
            break;
        }
    }
    return (best + cur) % 10;
}
