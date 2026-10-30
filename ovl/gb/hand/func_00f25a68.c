/* gb.x func_00f25a68: matched by hand. */
#include "ovl.h"

void func_00f37178(void);
extern f32 D_00F74350[];

void func_00f25a68(void) {
    f32 a;
    func_00f37178();
    a = D_00F74350[0];
    a += 0.17453292f;
    if (a < -3.141592503f) a += 6.28318501f;
    if (a > 3.141592503f) a -= 6.28318501f;
    D_00F74350[0] = a;
    a = D_00F74350[6];
    a += -0.17453292f;
    if (a < -3.141592503f) a += 6.28318501f;
    if (a > 3.141592503f) a -= 6.28318501f;
    D_00F74350[6] = a;
}
