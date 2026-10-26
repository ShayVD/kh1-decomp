/* wm.x func_00f3e910: matched by hand. */
#include "ovl.h"

typedef struct { u16 a; u16 b; } T;
typedef struct { s32 st; s32 v; u8 pad[0x14]; T *t; } A;
s32 func_00f3e910(A *arg0) {
    if (arg0->v < 0) return 1;
    switch (arg0->st) {
    case 2:
    case 3:
        if (arg0->t == 0) return 0;
        switch (arg0->t->b) {
        case 0: return 1;
        case 2: return 2;
        case 5: return 3;
        }
        break;
    case 0:
    case 1:
        return 0;
    }
    return 0;
}
