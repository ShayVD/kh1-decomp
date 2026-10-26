/* wm.x func_00f780a8: matched by hand. */
#include "ovl.h"

void func_0011d768(s32);
void func_001bfac8(void);
void func_00f6ad98(void);
s32 func_001be278(void);
void func_00f6b7c8(void);
extern s32 D_00FB4A58;
extern s32 D_00FB4A5C;
extern s8 D_00FB4EB9;
extern s8 D_00FB4EBA;
extern s32 D_0108F184;
extern s32 D_0108F254;
extern s32 D_0108F258;
extern s32 D_0108F27C;
extern s32 D_0108F280;
extern s32 D_0108F284;

void func_00f780a8(void) {
    s32 b = D_00FB4A5C;
    s32 a = D_00FB4A58;
    s32 v;

    func_0011d768(2);
    func_001bfac8();
    D_0108F254 = 0;
    D_0108F258 = 1;
    D_00FB4EB9 = 0;
    D_00FB4EBA = 0;
    func_00f6ad98();
    v = func_001be278() + 1;
    D_00FB4A5C = v;
    D_00FB4A58 = v;
    D_0108F27C = 1;
    D_0108F284 = 1;
    D_0108F280 = 0;
    func_00f6b7c8();
    D_00FB4EBA = 1;
    D_0108F184 = 0;
    while (D_00FB4EB9 == 0) {
        func_001bfac8();
    }
    D_00FB4A5C = b;
    D_00FB4A58 = a;
}
