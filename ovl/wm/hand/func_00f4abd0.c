/* wm.x func_00f4abd0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 x; } R4a;
R4a *func_001bb658(s32);
s32 func_001ba3f0(s32);
s32 func_001bb720(void);
s32 func_001bb730(void);

s32 func_00f4abd0(s32 x) {
    s32 i;
    s32 id;
    if (x >= 9) {
        for (i = 0; i < func_001bb730(); i++) {
            id = i + 128;
            if (func_001ba3f0(id) > 0 && func_001bb658(id)->x == x) {
                return id;
            }
        }
    } else {
        for (i = 0; i < func_001bb720(); i++) {
            if (i != 49 && func_001ba3f0(i) > 0 && func_001bb658(i)->x == x) {
                return i;
            }
        }
    }
    return 0;
}
