/* wm.x func_00f2b808: matched by hand. */
#include "ovl.h"

typedef struct { u16 id; u8 pad[0x46]; } E;
typedef struct { u16 n; u8 pad[6]; E e[1]; } T;
extern T *D_00FBB570;
s32 func_00f2b808(s32 arg0, s32 arg1) {
    s32 i;
    s32 c;
    if (arg0 == 0) return -1;
    c = 1;
    for (i = 0; i < D_00FBB570->n; i++) {
        if (D_00FBB570->e[i].id == arg0) {
            if (arg1 == c) return i;
            c++;
        }
    }
    return -1;
}
