/* wm.x func_00f78538: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 x8; } GbPad;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u8 pad10[14]; u16 x1e; } GbWin;
s32 func_0011ef10(s32, void (*)());
void func_001bfac8(void);
s32 func_001f31a8(void *, s32);
void func_0011d768(s32);
void func_0020b968(void);
s32 func_001bc520(void);
void func_00f77ed0();
extern GbPad D_002C5AD0;
extern GbWin D_00FB5B60;
extern u16 D_00FB4A74;
extern u16 D_00FB4A78;
extern s32 D_00FB5A64;
extern s32 D_0108F188;
extern s32 D_0108F1A8;
extern s32 D_0108F1AC;
extern s32 D_0108F258;
extern s32 D_0108F528;
extern s32 D_0108F52C;
extern s32 D_0108F530;

void func_00f78538(void) {
    func_0011d768(2);
    func_001bfac8();
    func_0020b968();
    D_0108F258 = 1;
    D_0108F1A8 = 0;
    D_0108F528 = 0;
    D_0108F1AC = 0;
    func_0011ef10(0x2BFE9, func_00f77ed0);
    D_00FB5A64 = 1;
    D_0108F530 = 0;
    D_0108F52C = 1;
    D_00FB5B60.x1e = func_001bc520();
    D_00FB5B60.xc = D_00FB4A74;
    D_00FB5B60.xe = D_00FB4A78;
    D_0108F188 = 0;
    func_001f31a8(&D_00FB5B60, 1);
    for (;;) {
        if (D_002C5AD0.x8 & 0x6000) {
            D_0108F1AC = 1;
            break;
        }
        func_001bfac8();
    }
    func_0011d768(3);
    if (D_0108F1AC != 2) {
        do {
            func_001bfac8();
        } while (D_0108F1AC != 2);
    }
}
