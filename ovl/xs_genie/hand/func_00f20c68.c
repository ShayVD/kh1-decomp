/* xs_genie.x func_00f20c68: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; } P8;
void func_00f216e0(void);
extern s32 D_00FC1A48;
extern P8 D_00FC1748[];

void func_00f20c68(P8 *p) {
    D_00FC1748[D_00FC1A48++] = *p;
    func_00f216e0();
}
