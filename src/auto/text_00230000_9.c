/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s8 D_003F8298[];
extern s8 D_003F82D0[];
extern s8 D_003F82F0[];
extern s8 D_003F8310[];
extern s8 D_003F8330[];
extern s8 D_003F8350[];

s8 *func_00232f88(u32 arg0) {
    D_003F8298[13] = (s8) ((arg0 / 10U) + 0x30);
    D_003F8298[14] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F8298;
}

s8 *func_00233018(u32 arg0) {
    D_003F82D0[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F82D0[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F82D0;
}

s8 *func_00233058(u32 arg0) {
    D_003F82F0[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F82F0[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F82F0;
}

s8 *func_00233098(u32 arg0) {
    D_003F8310[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F8310[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F8310;
}

s8 *func_002330d8(u32 arg0) {
    D_003F8330[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F8330[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F8330;
}

s8 *func_00233118(u32 arg0) {
    D_003F8350[14] = (s8) ((arg0 / 10U) + 0x30);
    D_003F8350[15] = (s8) ((arg0 % 10U) + 0x30);
    return D_003F8350;
}
