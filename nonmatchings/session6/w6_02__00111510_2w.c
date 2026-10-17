/* 2w off (hand, strict): bnel a3,v0 + i++ at latch vs orig plain bne with i++ in slot. Context stubs of 00111480/00111380/001113f8 do not change it. */
#include "common.h"
typedef struct { s8 a, b, c, d; } E4;
extern E4 D_002BCB80[];
extern s32 D_002BC128;
extern volatile s32 D_002BC130;
void func_00111480(void);
void func_00111380(void);
void func_001113f8(s32);

void func_00111510(void) {
    s32 i;
    E4 *e;
    func_00111480();
    for (i = 0; i < 39; i++) {
        e = &D_002BCB80[i];
        if (D_002BC128 == e->a && D_002BC130 == e->b) {
            func_001113f8(e->c);
            return;
        }
    }
    func_00111380();
}
