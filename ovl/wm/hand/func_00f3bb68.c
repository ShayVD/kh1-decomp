/* wm.x func_00f3bb68: matched by hand. */
#include "ovl.h"

typedef struct { s32 *p; u8 pad[188]; } E3bb68;
extern E3bb68 D_0106808C[];
void func_001c0310(s32, void (*)(s32), ...);
void func_00f3ba08(s32);

s32 func_00f3bb68(s32 arg0) {
    if (*D_0106808C[arg0].p == 1) {
        return 0;
    }
    func_001c0310(-1, func_00f3ba08, arg0);
    return 1;
}
