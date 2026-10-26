/* xs_genie.x func_00f21680: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; s32 f4; s32 pad[4]; } Ent;
typedef struct { Ent e[10]; s32 fF0; s32 fF4; s32 num; s32 start; } Tbl;
extern Tbl D_00FC1CE0;
s32 func_00f21680(s32 *arg0) {
    s32 i;
    s32 n = 0;
    for (i = D_00FC1CE0.start; i < D_00FC1CE0.num; i++) {
        if (D_00FC1CE0.e[i].f4 == *arg0) {
            n++;
        }
    }
    return n;
}
