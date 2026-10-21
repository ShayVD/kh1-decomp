/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00175a98();
M2C_UNK func_00175d60(M2C_UNK *, s32);
M2C_UNK func_00175e80(M2C_UNK *);
M2C_UNK func_00176ea8();
M2C_UNK func_0017f178();
M2C_UNK func_0017fcd8();
M2C_UNK func_0017ff38();
M2C_UNK func_00180540();
M2C_UNK func_00182270();
M2C_UNK func_00183a48();
M2C_UNK func_001a9f88();
M2C_UNK func_001aa650();
M2C_UNK func_00250054(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_002675a8(M2C_UNK *, M2C_UNK *);
#include "data/pieces/D_0035E710.h"
extern M2C_UNK D_0035FB20;
extern M2C_UNK D_00360F30;
extern M2C_UNK D_00362400;
extern M2C_UNK D_00362410;
extern M2C_UNK D_00362660;
extern M2C_UNK D_00362670;
extern M2C_UNK D_00362690;
extern M2C_UNK D_003626C0;
#include "data/pieces/D_003626F0.h"
extern M2C_UNK D_005758F0;
extern M2C_UNK D_00575920; /* src/data/bss_0057.c: S920 D_00575920 */
extern M2C_UNK D_00575940;
extern M2C_UNK func_00176ee0;
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
extern s32 D_00362430;
#include "data/pieces/D_00362434.h"
extern s32 D_00362438;
#include "data/pieces/D_0036243C.h"
extern s32 D_00362440;
extern s32 D_00362448;
#include "data/pieces/D_00362710.h"
extern s32 D_00616228;
s32 D_00616238 ALIGNED(8);
extern void *D_00575894;
f32 func_001629e8();
s32 func_00219308();

f32 func_00171aa8(f32 fparg0, f32 fparg1) {
    return fparg0 + (func_001629e8() * (fparg1 - fparg0));
}

void func_00175980(void) {
    func_00176ea8();
    func_0011ef10(0x4E21, &func_00176ee0);
}

void func_001759a8(void) {
    func_00175a98();
}

void func_001759c0(void) {
    func_00250054(((M2C_UNK *)&D_0035E710), 0, 0x1410);
}

void func_001759e8(void) {
    func_00250054(&D_0035FB20, 0, 0x1410);
    func_00250054(&D_00360F30, 0, 0x1410);
}

void func_001760b0(s32 arg0) {
    func_00175d60(((M2C_UNK *)&D_0035E710), arg0);
}

void func_001760d0(s32 arg0) {
    func_00175d60(&D_0035FB20, arg0);
}

void func_001760f0(s32 arg0) {
    func_00175d60(&D_00360F30, arg0);
}

void func_001761d0(void) {
    func_00175e80(&D_0035FB20);
}

void func_00176340(void) {
    func_0017fcd8();
}

void func_00176388(void) {
    func_0017ff38();
}

void func_00176640(void) {
    func_00180540();
}

void func_00176838(void) {
    func_00182270();
}

void func_00176898(void) {

}

void func_001768a0(void) {

}

void func_001768a8(void) {

}

void func_001768b0(void) {

}

void func_001768b8(void) {

}

void func_001768c0(void) {

}

void func_001768c8(void **arg0) {
    void *temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != NULL) {
        *M2C_FIELD(temp_v0, s8 **, 0x10) = 1;
    }
    *arg0 = NULL;
}

s32 func_00177070(void) {
    s32 var_v0;

    var_v0 = 0;
    if (func_00219308() == 0) {
        var_v0 = M2C_FIELD(D_00575894, s32 *, 0x70) != 0x1B;
    }
    return var_v0;
}

void func_00177a98(void) {
    func_00250054(&D_005758F0, 0, 0x10);
}

void func_00179d08(void) {
    func_00250054(&D_00575920, 0, 0x20);
}

void func_0017b0e0(void) {
    func_00250054(&D_00575940, 0, 0x70);
    M2C_FIELD(&D_00575940, f32 *, 0x50) = 1.0f;
}

void func_0017b120(void) {
    func_00250054(&D_00362690, 0, 0x30);
}

void func_0017b148(void) {
    func_00250054(&D_003626C0, 0, 0x30);
}

void func_0017db68(void) {
    (*(s32 *)&D_00362424) = 0;
    (*(s32 *)&D_00362428) = 0;
    (*(s32 *)&D_0036242C) = 0;
    D_00362430 = 0;
    D_00362434 = 0;
    D_00362438 = 0;
    D_0036243C = 0;
    D_00362440 = 0;
    D_00362448 = 0;
}

void func_0017e8a0(void) {
    func_00250054(((M2C_UNK *)&D_003626F0), 0, 8);
}

void func_0017f150(void) {
    func_002675a8(&D_00362660, &D_00362410);
    func_0017f178();
}

void func_0017f1a0(void) {
    func_002675a8(&D_00362670, &D_00362400);
}

void func_0017f678(void) {
    D_00362710 = 0;
}

void func_0017f948(void) {
    D_00616238 = 0;
}

void func_0017f958(void) {
    func_00183a48();
}

void func_0017f970(void) {
    if (D_00616228 != 0) {
        func_001aa650();
        func_001a9f88();
    }
}
#include "data/bss_0057_mixed.h"
#include "data/data_0035.h"
#include "data/data_0036.h"
