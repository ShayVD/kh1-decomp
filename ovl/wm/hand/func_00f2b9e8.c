/* wm.x func_00f2b9e8: matched by hand. */
#include "ovl.h"

typedef struct { u16 a; u16 b; u16 c; u16 d; } E;
typedef struct { u8 pad[8]; E e[8]; } A;
s32 func_001bb3f8(u16);
s32 func_00f2b9e8(A *arg0) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (arg0->e[i].a == 32 && func_001bb3f8(arg0->e[i].b) == 0) return 0;
    }
    return 1;
}
