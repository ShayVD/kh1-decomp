/* wm.x func_00f37170: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[4]; u8 kind; u8 pad5[27]; u16 id; } A37170;
typedef struct { u8 pad[0x540]; s32 x540; } G37170;
typedef struct { u16 h0; u16 h2; } R37170;
extern G37170 *D_00F864C0;
R37170 *func_00f62c78(s32, s32);

s32 func_00f37170(A37170 *arg0) {
    if (arg0->id == 0xFFFF) {
        return 0;
    }
    switch (arg0->kind) {
    case 2:
    case 3:
        if (func_00f62c78(arg0->id, D_00F864C0->x540)->h2 == 0) {
            return 1;
        }
        break;
    }
    return 0;
}
