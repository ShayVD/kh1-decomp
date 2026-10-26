/* wm.x func_00f31000: matched by hand. */
#include "ovl.h"

void func_00f344e0(s32);
void func_00106978(s32);
void func_001c0688(s32);
void func_00242b68(s32);
void func_00f3a4c8(void);
void func_001bfac8(void);
void func_00f3f358(void);
void func_00f33998(void);
void func_00f681b0(void);
void func_00f2c1b8(void);
s32 func_001bb848(void);
void func_00f201c0(void);
extern s32 D_002BBE04;
extern s32 D_002BC080[];
extern s32 D_002BC090, D_002BC094, D_002BC098, D_002BC09C, D_002BC0A0, D_002BC0A4;

void func_00f31000(void) {
    D_002BBE04 = 1;
    D_002BC080[0] = 0x80;
    D_002BC080[1] = 0x80;
    D_002BC080[2] = 0x80;
    D_002BC080[3] = 0x40;
    D_002BC090 = 0x100;
    D_002BC094 = 0xC0;
    D_002BC098 = 0;
    D_002BC09C = 1;
    D_002BC0A0 = 0;
    D_002BC0A4 = 0;
    func_00f344e0(1);
    func_00106978(0x37);
    func_001c0688(0x3C);
    func_00242b68(4);
    D_002BBE04 = 0;
    func_00f3a4c8();
    func_001bfac8();
    func_001bfac8();
    func_00f3f358();
    func_00f33998();
    func_00f681b0();
    func_00f2c1b8();
    while (func_001bb848() != 0) {
        while (func_001bb848() != 0) {
            func_001bfac8();
        }
        func_001bfac8();
    }
    func_00f201c0();
}
