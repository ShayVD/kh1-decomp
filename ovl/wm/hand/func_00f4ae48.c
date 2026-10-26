/* wm.x func_00f4ae48: matched by hand. */
#include "ovl.h"

s32 func_001ba3f0(s32);
s32 func_001bb720(void);
s32 func_001bb730(void);

s32 func_00f4ae48(s32 cur) {
    s32 n = func_001bb720() + func_001bb730();
    s32 i;
    s32 id;

    if (cur >= 128) {
        cur = cur + func_001bb720() - 128;
    }
    for (i = 0; i < n; i++) {
        cur = (cur + n - 1) % n;
        id = cur;
        if (id >= func_001bb720()) {
            id = id - func_001bb720() + 128;
        }
        if (id != 49 && func_001ba3f0(id) > 0) {
            return id;
        }
    }
    return 0;
}
