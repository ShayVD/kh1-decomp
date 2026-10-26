/* wm.x func_00f2cba8: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 f0;
    u8 pad[143];
} E;
typedef struct {
    s32 a;
    s32 b;
    s32 c;
} T;
extern E D_00FBEBC0[];
extern T D_00FBB808;
extern T D_00FBB818;
extern s32 D_00FBB820;
extern s32 D_00FBB824;
extern s32 D_00FBB828;

void func_00f2cba8(void) {
    s32 i;
    for (i = 383; i >= 0; i--) {
        D_00FBEBC0[i].f0 = 0;
    }
    D_00FBB808.a = 0;
    D_00FBB808.b = 0;
    D_00FBB808.c = 0;
    D_00FBB818.a = 0;
    D_00FBB818.b = 0;
    D_00FBB818.c = 0;
    D_00FBB820 = 0;
    D_00FBB824 = 0;
    D_00FBB828 = 0;
}
