/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK func_00f22b48;
extern M2C_UNK func_00f25cb0;
extern s32 D_00F56D90;
extern s32 D_00F56EC0;
extern s32 D_00F74490;
extern s32 D_00F7F4E0;
s32 func_001c01b0(s32, s32, ...);
void func_001b9bb0(s32, s32);
void func_001b9ec0(void);
void func_001ba708(s32);
void func_001ba768(s32);
void func_001ba778(s32, s32, s32);
void func_001bfac8(void);
void func_00f25bc8(void);
void func_00f25e48(void);

void func_00f25f78(s32 arg0) {
    func_001ba768(arg0);
    func_001bfac8();
    func_001ba768(0);
    func_001bfac8();
}

void func_00f25fa8(s32 arg0, s32 arg1, s32 arg2) {
    func_001ba778(arg0, arg1, arg2);
    func_001bfac8();
    func_001ba778(arg0, 0, 0);
    func_001bfac8();
}

void func_00f26040(s32 arg0, s32 arg1) {
    switch (arg0) {                                 /* irregular */
    case 0:
        func_00f25bc8();
        func_001b9ec0();
        D_00F56EC0 = 1;
        if (arg1 == 2) {
            func_00f25e48();
            return;
        }
        return;
    case 1:
        D_00F56EC0 = 0;
        func_001b9bb0(0, 1);
        func_001ba708(0);
        func_001c01b0(-1, &func_00f22b48, 0, &func_00f25cb0);
        return;
    case 2:
        D_00F56D90 = arg1;
        break;
    }
}

s32 func_00f26120(s32 arg0) {
    s32 var_v0;

    var_v0 = 1;
    if (arg0 == 0) {
        return var_v0;
    }
    if (D_00F7F4E0 != 0) {
        if (D_00F7F4E0 == D_00F74490) {
            D_00F7F4E0 = 0;
            return 1;
        }
        return 0;
    }
    var_v0 = 0;
    D_00F7F4E0 = D_00F74490 + (arg0 * 2);
    /* Duplicate return node #6. Try simplifying control flow for better match */
    return var_v0;
    return var_v0;
}
