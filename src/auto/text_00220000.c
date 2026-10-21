/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_0021b800(s32);
M2C_UNK func_0021fbb8();
M2C_UNK func_00220338(s32);
M2C_UNK func_002205e0();
M2C_UNK func_00220fe8(s32);
M2C_UNK func_002210f8();
M2C_UNK func_002229a0(s32);
M2C_UNK func_00223260(s32);
M2C_UNK func_00223508();
M2C_UNK func_00223870(s32);
M2C_UNK func_0022f818();
extern s32 D_003F34C0;
#include "data/pieces/D_003F5C18.h"
extern s32 D_003F5C24;
extern s32 D_003F5C28;
extern s32 D_003F5C2C;
extern s32 D_003F6854;
extern s32 D_006433F0;
extern s32 D_00643418;
extern s32 D_0064341C;
extern s32 D_00643420;
extern s32 D_00643424;
extern s32 D_0064342C;
extern s32 D_00643660;
extern s32 D_00643674;
extern s32 D_00643690;
extern s32 D_00643694;
extern s32 D_00643698;
extern s32 D_0064369C;
extern s32 D_006436A0;
extern s32 D_00646A20; /* src/data/bss_0064.c: u32 D_00646A20 */
extern s32 D_00646A24; /* src/data/bss_0064.c: u32 D_00646A24 */
extern s32 D_00646A28;
extern s32 D_00647644;
s32 func_001f42b8();

void func_002204b0(s32 arg0) {
    if (func_001f42b8() != 0) {
        func_00220338(arg0);
    }
}

void func_00220580(s32 arg0) {
    D_006433F0 = arg0;
}

void func_00220590(void) {
    func_0021fbb8();
    (*(s32 *)&D_003F5C18) = D_00643418 != 0;
}

void func_002205c0(void) {
    D_0064341C = 0;
    D_00643420 = 0;
    D_00643424 = 0;
}

void func_00221058(s32 arg0) {
    if (func_001f42b8() != 0) {
        func_00220fe8(arg0);
    }
}

void func_002210c0(void) {
    func_002205e0();
    D_003F5C24 = D_0064342C != 0;
}

void func_002210f0(void) {

}

void func_00222a70(s32 arg0) {
    if (func_001f42b8() != 0) {
        func_002229a0(arg0);
    }
}

void func_00222b40(s32 arg0) {
    D_00643660 = arg0;
}

void func_00222b50(void) {
    func_002210f8();
    D_003F5C2C = D_00643674 != 0;
}

void func_00222b80(void) {
    D_00643690 = 0;
    D_00643694 = 0;
    D_00643698 = 0;
    D_0064369C = 0;
}

void func_00222c98(s32 arg0) {
    func_0021b800(arg0 + 0x13);
}

s32 func_00222cb0(s32 arg0) {
    return arg0;
}

void func_002233d8(s32 arg0) {
    if (func_001f42b8() != 0) {
        func_00223260(arg0);
    }
}

void func_002234a8(s32 arg0) {
    D_006436A0 = arg0;
}

void func_00223638(s32 arg0) {
    func_0021b800(arg0 + 0x2A);
}

void func_002238e0(s32 arg0) {
    if (func_001f42b8() != 0) {
        func_00223870(arg0);
    }
}

void func_00223948(void) {
    func_00223508();
    D_003F5C28 = D_003F6854 != 0;
}

void func_00223978(void) {

}

void func_002245a8(void) {
    D_003F34C0 &= ~2;
}

void func_0022d138(void) {

}

void func_0022d728(void) {

}

void func_0022db90(void) {

}

void func_0022dfd0(void) {

}

void func_0022e458(void) {

}

void func_0022ebe8(void) {

}

void func_0022ebf0(void) {

}

void func_0022eee0(s32 arg0) {
    D_00646A20 = arg0;
    D_00647644 = 0x1E;
}

void func_0022fc88(s32 arg0) {
    D_00646A24 = arg0;
    func_0022f818();
    D_00646A28 = 1;
}
#include "data/data_003F.h"
