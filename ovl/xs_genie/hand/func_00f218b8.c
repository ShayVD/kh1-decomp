/* xs_genie.x func_00f218b8: matched by hand. */
#include "ovl.h"

typedef struct { s32 x; s32 a; s32 b; s32 p[2]; s32 c; } G;
s32 func_0012f040(s32, s32);
void func_0023c5a8(s32);
s32 func_00f218b8(G *a) { if (func_0012f040(a->a, a->b) == 0) { func_0023c5a8(a->c); return 0; } return 1; }
