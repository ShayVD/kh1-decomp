#include "common.h"
s32 func_00257e10(s32, void *);
void func_00260d00(void);
extern s32 D_0046C1C0;
s32 func_002607e8(s32 a) {
    D_0046C1C0 = a;
    func_00257e10(1, func_00260d00);
    func_00257e10(2, func_00260d00);
    func_00257e10(3, func_00260d00);
    return a;
}
