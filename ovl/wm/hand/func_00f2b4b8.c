/* wm.x func_00f2b4b8: matched by hand. */
#include "ovl.h"

typedef struct { s8 a; s8 b; s8 c; } E2b4b8;
extern E2b4b8 D_00F8BBC8[];
void func_001c0da0(s32, s32, s8 *);
CONTEXT_ONLY s32 func_00f2ab98(s32 arg0) {
    s8 b[16];
    func_001c0da0(arg0 + 752, 1, b);
    return b[0];
}

static inline s32 big_2b4b8(void) {
    if ((func_00f2ab98(7) & 0xF) < 2) return 0;
    return 1;
}

s32 func_00f2b4b8(s32 arg0, s32 arg1) {
    s32 ok;
    E2b4b8 *p;
    s32 i;
    if (arg0 == 27) arg0 = 13;
    if (arg1 == 27) arg1 = 13;
    ok = big_2b4b8() && ((arg0 == 9 && arg1 == 10) || (arg0 == 10 && arg1 == 9));
    if (ok) {
        return 0;
    }
    for (i = 0; D_00F8BBC8[i].a >= 0; i++) {
        if (D_00F8BBC8[i].a == arg0 && D_00F8BBC8[i].b == arg1) {
            do { return 1; } while (0); /* permuter: changes register allocation */
        }
    }
    return 0;
}
