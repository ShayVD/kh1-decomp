/* wm.x func_00f3f320: matched by hand. */
#include "ovl.h"

typedef struct { s32 idx; u8 pad[0x54]; } W58;
CONTEXT_ONLY W58 D_00F87E98[1] = { { 0 } };
CONTEXT_ONLY s32 D_00F9B27C[1] = { 0 };
s32 func_00f3f320(s32 arg0) {
    return D_00F9B27C[D_00F87E98[arg0].idx];
}
