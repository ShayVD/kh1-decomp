/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00120c18(M2C_UNK *);
M2C_UNK func_00175be0(M2C_UNK *, s32, s32, M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0017b250(M2C_UNK *, void *, f32);
M2C_UNK func_0017b308(void *, void *, s32, s32, s32);
M2C_UNK func_00267530(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_002675a8(s32, M2C_UNK *);
extern M2C_UNK D_002E2780;
extern M2C_UNK D_002E2790;
extern M2C_UNK D_0035FB20;
extern M2C_UNK D_00360F30;
extern M2C_UNK D_00575970;
extern s32 D_0035C6F8;
extern s32 D_0035C6FC;
extern void *D_00362438;
void func_001759c0(void);
void func_001759e8(void);
void func_00175a20(void);
void func_00182058(void);
void func_00182270(void);

void func_00175a48(void) {
    func_00182270();
    func_00182058();
    func_001759c0();
    func_001759e8();
    func_00175a20();
    D_0035C6F8 = 1;
    D_0035C6FC = 0;
}

void func_00175f98(s32 arg0, s32 arg1, s32 arg2) {
    func_00175be0(&D_0035FB20, arg0, arg1, -1, arg2, -1, 2);
}

void func_00175fd0(s32 arg0, s32 arg1, s32 arg2) {
    func_00175be0(&D_00360F30, arg0, arg1, -1, arg2, -1, 3);
}

void func_00176a60(s32 *arg0) {
    func_002675a8(*arg0, &D_002E2780);
}

void func_00176a80(s32 *arg0) {
    func_002675a8(*arg0, &D_002E2790);
}

void func_0017c110(s32 arg0, f32 fparg0) {
    s32 sp[20];
    func_0017b308(sp, D_00362438 + 0x20, M2C_FIELD(D_00362438, s32 *, 0), arg0, M2C_FIELD(D_00362438, s32 *, 0x18) & 1);
    func_0017b250(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, fparg0);
    func_00267530(&M2C_FIELD(sp, M2C_UNK *, 0x40), &D_00575970, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_00120c18(&M2C_FIELD(sp, M2C_UNK *, 0x40));
}
#include "data/data_0035.h"
#include "data/data_0036.h"
