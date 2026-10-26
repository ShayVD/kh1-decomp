/* gb.x func_00f22f28: matched by hand. */
#include "ovl.h"

extern s32 D_003773EC, D_00F56D98, D_00F56D8C, D_00F56D90, D_00F56D94, D_00F60BF8, D_00F56EC4, D_00F56EC0, D_00F56D88, D_00F61834;
extern s32 D_00F56DA0, D_00F56DA4, D_00F56D80;
extern u8 D_00F56E80[], D_00F56E00[], D_00F56F80[], D_00F56F00[];
void func_00112e98(void);
void func_001bade8(void);
void func_00f3cff0(void);
void func_00f272f0(s32);
void func_00f20208(void);
void func_00f22d00(void);
void func_001bb858(void *, void *);
void func_001bb438(void);
s32 func_001bfec8(void);
s32 func_001bb500(s32, s32);
void func_001bfe50(s32);
void func_001bfc90(s32);
void func_00f20518(void);
void func_00f41078(void);
void func_00f3fda0(void);
s32 func_00f22bf8(void);
void func_00f20330(void);
void func_0011ef10(s32, s32 (*)(void));
s32 func_001c00e8(s32, void (*)(void), kh1_u128);
void func_00f22f28(void) {
    if (D_003773EC) func_00112e98();
    D_003773EC = 0;
    func_001bade8();
    func_00f3cff0();
    func_00f272f0(0);
    func_00f20208();
    D_00F60BF8 = 0;
    D_00F56EC4 = 0;
    D_00F56EC0 = 0;
    D_00F56D88 = 0;
    D_00F61834 = 0;
    D_00F56D98 = 0;
    D_00F56D8C = 1;
    D_00F56D90 = 0;
    D_00F56D94 = 0;
    func_00f22d00();
    D_00F56DA0 = 0;
    D_00F56DA4 = 0;
    D_00F56D80 = 1;
    func_001bb858(D_00F56E80, D_00F56E00);
    func_001bb858(D_00F56F80, D_00F56F00);
    func_001bb438();
    func_001bfe50(func_001bb500(func_001bfec8(), 16));
    func_001bfc90(1);
    func_00f20518();
    func_00f41078();
    func_00f3fda0();
    func_0011ef10(0x1D4C1, func_00f22bf8);
    func_001c00e8(1, func_00f20330, KH1_Q(0));
}
