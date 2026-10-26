/* wm.x func_00f35800: matched by hand. */
#include "ovl.h"

void func_00f356a0(void);
extern f32 D_00FCE340[];

void func_00f35800(void) {
    f32 a;
    func_00f356a0();
    a = D_00FCE340[0];
    a += 0.34906584f;
    if (a < -3.141592503f) a += 6.28318501f;
    if (a > 3.141592503f) a -= 6.28318501f;
    D_00FCE340[0] = a;
    a = D_00FCE340[6];
    a += -0.34906584f;
    if (a < -3.141592503f) a += 6.28318501f;
    if (a > 3.141592503f) a -= 6.28318501f;
    D_00FCE340[6] = a;
}
