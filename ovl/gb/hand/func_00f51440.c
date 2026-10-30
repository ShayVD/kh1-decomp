/* gb.x func_00f51440: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 x8; } GbPad;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u8 pad10[14]; u16 x1e; } GbWin;
s32 func_0011ef10(s32, void (*)());
void func_001bfac8(void);
s32 func_001f31a8(void *, s32);
void func_0011d768(s32);
void func_0020b968(void);
s32 func_001bc520(void);
void func_00f50dd8();
extern GbPad D_002C5AD0;
extern GbWin D_00F713E0;
extern u16 D_00F702F4;
extern u16 D_00F702F8;
extern s32 D_00F712E4;
extern s32 D_00F829C8;
extern s32 D_00F829E8;
extern s32 D_00F829EC;
extern s32 D_00F82A98;
extern s32 D_00F82D68;
extern s32 D_00F82D6C;
extern s32 D_00F82D70;

void func_00f51440(void) {
    func_0011d768(2);
    func_001bfac8();
    func_0020b968();
    D_00F82A98 = 1;
    D_00F829E8 = 0;
    D_00F82D68 = 0;
    D_00F829EC = 0;
    func_0011ef10(0x2BFE9, func_00f50dd8);
    D_00F712E4 = 1;
    D_00F82D70 = 0;
    D_00F82D6C = 1;
    D_00F713E0.x1e = func_001bc520();
    D_00F713E0.xc = D_00F702F4;
    D_00F713E0.xe = D_00F702F8;
    D_00F829C8 = 0;
    func_001f31a8(&D_00F713E0, 1);
    for (;;) {
        if (D_002C5AD0.x8 & 0x6000) {
            D_00F829EC = 1;
            break;
        }
        func_001bfac8();
    }
    func_0011d768(3);
    if (D_00F829EC != 2) {
        do {
            func_001bfac8();
        } while (D_00F829EC != 2);
    }
}
