/* Object class 0x00, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_0015a418 registers in the class table D_00350D88
 * (func_0014f830(0x00, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class00.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "platform/math.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"

/* func_0015a258 (from hand/nostrict/text_00150000_h36.c). */
extern u32 D_002C5958;
s32 func_0013f510(void *, s32);
s32 func_001401d8(void *, s32);
s32 func_001404d8(void *, s32);
s32 func_00144410(void *, s32);
void func_0014f658(void *, s32);
void func_00159f78(void *, s32, s32);
s32 func_0015d770(void *, s32);
s32 func_0015dd50(void *, f32 *);
void func_0015a258(void *a, s32 b) {
    if (func_001404d8(a, b)) return;
    if (func_001401d8(a, b)) return;
    if (func_0013f510(a, b)) return;
    if (func_0015d770(a, b)) return;
    if (func_00144410(a, b)) return;
    if (func_0015dd50(a, (f32 *)b)) return;
    if ((D_002C5958 >> 17) & 1) {
        func_0014f658(a, 30);
        return;
    }
    func_00159f78(a, b, 0);
}

