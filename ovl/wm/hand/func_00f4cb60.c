/* wm.x func_00f4cb60: the twin of gb.x func_00f25a68 (tools/ovl/twins.py). */
#include "ovl.h"

void func_00f5e270(void);
extern f32 D_01080B10[];

void func_00f4cb60(void) {
    f32 a;
    func_00f5e270();
    a = D_01080B10[0];
    a += 0.17453292f;
    if (a < -3.141592503f) a += 6.28318501f;
    if (a > 3.141592503f) a -= 6.28318501f;
    D_01080B10[0] = a;
    a = D_01080B10[6];
    a += -0.17453292f;
    if (a < -3.141592503f) a += 6.28318501f;
    if (a > 3.141592503f) a -= 6.28318501f;
    D_01080B10[6] = a;
}
