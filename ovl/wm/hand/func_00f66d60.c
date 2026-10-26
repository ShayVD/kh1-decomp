/* wm.x func_00f66d60: matched by hand. */
#include "ovl.h"

typedef struct { void (*fn)(s32); s32 arg; u16 next; } WmDrawNode;
void func_001be820(void *, s32);
s32 sceDmaGetChan(s32);
s32 sceDmaSync(s32, s32, s32);
s32 sceGsSyncPath(s32, s32);
extern u16 D_00FB11E8[1024];
extern WmDrawNode D_00FB19E8[];
extern s32 D_0108F040;
extern s32 D_0108F044;

s32 func_00f66d60(void) {
    s32 i;
    u16 n;

    if (D_0108F044 == 0) {
        return 4;
    }
    for (i = 0; i < 1024; i++) {
        if (D_00FB11E8[i] != 0) {
            sceGsSyncPath(0, 0);
            sceDmaSync(sceDmaGetChan(1), 0, 0);
            sceDmaSync(sceDmaGetChan(2), 0, 0);
            for (n = D_00FB11E8[i]; n != 0; n = D_00FB19E8[n - 1].next) {
                D_00FB19E8[n - 1].fn(D_00FB19E8[n - 1].arg);
            }
        }
    }
    func_001be820(D_00FB11E8, 0x800);
    func_001be820(D_00FB19E8, 0x3000);
    D_0108F040 = 0;
    return 0;
}
