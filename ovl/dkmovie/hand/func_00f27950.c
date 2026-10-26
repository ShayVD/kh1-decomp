/* dkmovie.x func_00f27950: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x14]; s32 f14; u8 pad2[4]; s32 f1c; } St;
s32 func_00122048(s32, s32);
void func_001220b8(s32, s32);
void func_00f23188(s32);
extern s32 D_0003DD2C;
extern s32 D_0003DEF0;
extern void (**D_00F28468)(void);
extern s32 D_00F28470;
extern s32 D_00F28474;
extern St D_00F28478;

s32 func_00f27950(void) {
    s32 p;
    if (D_00F28474 != 0) {
        p = func_00122048(0x20F0, 0x10);
        func_00f23188(p);
        *(s32 *)(D_00F28470 + 0x3DEF0) = D_00F28478.f1c;
        (*D_00F28468)();
        D_00F28478.f14 = *(s32 *)(D_00F28470 + 0x3DD2C);
        func_001220b8(p, D_00F28470);
    }
    return 0;
}
