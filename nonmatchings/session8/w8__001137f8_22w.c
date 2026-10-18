/* 001137f8 hand, 22w (session-6 draft 27w), same size. col built in three statements 'col = D_004D934C; col |= D_004D9358 << 24; ...; col |= (D_004D9354 << 16) | (D_004D9350 << 8);' fixes the or tree and colour registers (one expression is always reassociated by combine to (934C|9354<<16)|(9358<<24|9350<<8)); b between the col statements (hill-climbed). Left: prologue load order (orig loads 9354, 935C first and materialises 1<<32 early in a2) and the 1<<32 register. GS-macro forms of a/b: no change. */
#include "common.h"
extern s32 D_004D934C, D_004D9350, D_004D9354, D_004D9358, D_004D935C, D_004D9360;
extern u64 D_002BCE00[];
extern u8 D_002BD100[];
void func_001104e0(void);
void func_0010f580(void);
void func_0010f5d0(void);
s32 func_00106b18(void *);
u8 *func_001efc10(s32);
void func_001f1ed8(s32, s32, s32, u8 *, s32);
s32 sceGsSyncPath(s32, s32);

void func_001137f8(void) {
    s32 col;
    u64 a, b;
    col = D_004D934C;
    col |= D_004D9358 << 24;
    b = ((s64)D_004D935C << 24) | 0x100000000;
    col |= (D_004D9354 << 16) | (D_004D9350 << 8);
    a = ((s64)D_004D9360 << 24) | 0x100D17A88;
    D_002BCE00[0x140/8] = a;
    D_002BCE00[0x160/8] = a;
    D_002BCE00[0x180/8] = a;
    D_002BCE00[0x190/8] = a;
    D_002BCE00[0x1A0/8] = a;
    D_002BCE00[0x1B0/8] = a;
    D_002BCE00[0x1D0/8] = a;
    D_002BCE00[0x1F0/8] = a;
    D_002BCE00[0x230/8] = a;
    D_002BCE00[0x250/8] = a;
    D_002BCE00[0x270/8] = a;
    D_002BCE00[0x280/8] = a;
    D_002BCE00[0x290/8] = a;
    D_002BCE00[0x2A0/8] = a;
    D_002BCE00[0x2C0/8] = a;
    D_002BCE00[0x2E0/8] = a;
    D_002BCE00[0x50/8] = b;
    D_002BCE00[0x70/8] = b;
    D_002BCE00[0x90/8] = b;
    D_002BCE00[0xA0/8] = b;
    D_002BCE00[0xB0/8] = b;
    D_002BCE00[0xC0/8] = b;
    D_002BCE00[0xE0/8] = b;
    D_002BCE00[0x100/8] = b;
    func_001104e0();
    func_0010f580();
    func_00106b18(D_002BD100);
    func_001f1ed8(col, 182, 54, func_001efc10(5), 18);
    func_001f1ed8(col, 214, 54, func_001efc10(6), 18);
    func_001f1ed8(col, 246, 54, func_001efc10(7), 18);
    func_001f1ed8(col, 278, 54, func_001efc10(8), 18);
    func_001f1ed8(col, 310, 54, func_001efc10(9), 18);
    func_0010f5d0();
    sceGsSyncPath(0, 0);
    *(volatile u64 *)0x12000000 = 0xff03;
    *(volatile u64 *)0x12000070 = 0x11b0;
    *(volatile u64 *)0x12000080 = 0x0007f9ff020d227cUL;
}
