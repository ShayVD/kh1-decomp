/* gb.x func_00f42928: matched by hand. */
#include "ovl.h"

void func_0010c170(void (*)(void), s32);
void func_001bfac8(void);
void func_00f42898(void);
extern s32 D_00F82AA0;
extern s32 D_00F82AA8;
extern s32 D_00F82AAC;
extern s32 D_00F82AB0;
extern s32 D_00F82AB4;
extern s32 D_00F82AB8;

void func_00f42928(void) {
    D_00F82AA0 = 0;
    func_0010c170(func_00f42898, 0);
    while (D_00F82AA0 == 0) {
        func_001bfac8();
    }
    D_00F82AAC = 2;
    D_00F82AB0 = D_00F82AA8;
    D_00F82AB4 = D_00F82AB8;
}
