/* wm.x func_00f78690: matched by hand. */
#include "ovl.h"

#include "platform/thread.h"

typedef struct { s32 x0; f32 x4; f32 x8; f32 xC; f32 x10; } Bob;
extern Bob D_00FB5ED8[];
extern char D_00FBA6F0[], D_00FBA6F8[], D_00FBA700[];
s32 func_0024ba28(s32 *p, char *name, s32 idx, void *out);

void func_00f78690(s32 *list) {
    s32 i;
    s32 n;
    f32 f;
    for (i = 0; i < 28; i++) {
        n = 0;
        if (func_0024ba28(list, D_00FBA6F0, i, &n) < 0) {
            PlatBreak();
        }
        D_00FB5ED8[i].x0 = n;
        if (func_0024ba28(list, D_00FBA6F8, i, &f) < 0) {
            PlatBreak();
        }
        D_00FB5ED8[i].xC = f;
        if (func_0024ba28(list, D_00FBA700, i, &f) < 0) {
            PlatBreak();
        }
        D_00FB5ED8[i].x10 = f;
    }
}
