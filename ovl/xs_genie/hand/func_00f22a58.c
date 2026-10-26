/* xs_genie.x func_00f22a58: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; } P8;
typedef struct { s32 f0; s32 f4; s32 f8; P8 fc; } R;
R *func_00f22720(s32);
s32 func_00f22598(s32, P8 *);
extern s32 D_00FC2EE8;

void func_00f22a58(s32 a, P8 *b) {
    R *r = func_00f22720(a);
    r->f8 = a;
    r->fc = *b;
    r->f4 = func_00f22598(a, b);
    D_00FC2EE8 = r->f4;
}
