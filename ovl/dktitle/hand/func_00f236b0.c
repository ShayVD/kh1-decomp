/* dktitle.x func_00f236b0: matched by hand. */
#include "ovl.h"

void func_00109278(void);
s32 func_0011ef10(s32, void *);
void func_00f228c8(void);
extern s32 D_002B6478;
extern s32 D_002BC73C;
extern s32 (*D_0046A6A4)(void);
extern s32 D_00F2C700;
extern s32 D_00F2C704;
extern s32 D_00F2C708;

void func_00f236b0(void) {
    func_00109278();
    D_00F2C700 = 0;
    func_0011ef10(0x2BF20, func_00f228c8);
    D_00F2C708 = 0;
    if (D_002BC73C != 0) {
        D_00F2C708 = 0x17;
    }
    D_002B6478 = D_0046A6A4();
    if (D_002B6478 == 0) {
        D_00F2C704 = 2;
    } else {
        D_00F2C704 = 3;
    }
}
