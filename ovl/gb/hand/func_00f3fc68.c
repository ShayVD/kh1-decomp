/* gb.x func_00f3fc68: matched by hand. */
#include "ovl.h"

typedef struct { void (*fn)(s32); s32 arg; u16 next; } Ev;
extern s32 D_00F82884, D_00F82880;
extern u16 D_00F6CA68[];
extern Ev D_00F6D268[];
s32 sceGsSyncPath(s32, s32);
s32 sceDmaGetChan(s32);
s32 sceDmaSync(s32, s32, s32);
void func_001be820(void *, s32);
s32 func_00f3fc68(void) {
    s32 i;
    u16 n;
    if (D_00F82884 == 0) return 4;
    for (i = 0; i < 1024; i++) {
        if (D_00F6CA68[i]) {
            sceGsSyncPath(0, 0);
            sceDmaSync(sceDmaGetChan(1), 0, 0);
            sceDmaSync(sceDmaGetChan(2), 0, 0);
            for (n = D_00F6CA68[i]; n; n = D_00F6D268[n - 1].next)
                D_00F6D268[n - 1].fn(D_00F6D268[n - 1].arg);
        }
    }
    func_001be820(D_00F6CA68, 2048);
    func_001be820(D_00F6D268, 12288);
    D_00F82880 = 0;
    return 0;
}
