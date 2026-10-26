/* wm.x func_00f68e50: matched by hand. */
#include "ovl.h"

typedef struct { u8 a; u8 b; u8 c; u8 d; u8 pad[0x5C]; } E68e;
E68e *func_001bc4e0(void);
s32 func_001bc510(void);

s32 func_00f68e50(void) {
    s32 n = func_001bc510();
    E68e *e = func_001bc4e0() + 1;
    s32 i;
    s32 c = 0;

    for (i = 0; i < n - 1; i++) {
        if (e[i].a != 0 && e[i].d != 0) {
            c++;
        }
    }
    return c;
}
