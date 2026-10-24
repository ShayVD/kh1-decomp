/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_0017f178();
M2C_UNK func_00250054(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_002675a8(M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_00362400;
extern M2C_UNK D_00362410;
extern M2C_UNK D_00362660;
extern M2C_UNK D_00362670;
extern M2C_UNK D_00362690;
#include "data/pieces/D_003626C0.h"
#include "data/pieces/D_003626F0.h"
extern M2C_UNK D_005758F0;
extern M2C_UNK D_00575920; /* src/data/bss_0057.c: S920 D_00575920 */
extern M2C_UNK D_00575940;
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
#include "data/pieces/D_00362430.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_0036243C.h"
extern s32 D_00362440;
extern s32 D_00362448;
#include "data/pieces/D_00362710.h"
extern void *D_00575894;
f32 func_001629e8();
s32 func_00219308();

f32 func_00171aa8(f32 fparg0, f32 fparg1) {
    return fparg0 + (func_001629e8() * (fparg1 - fparg0));
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
    func_00250054(((M2C_UNK *)&D_003626C0), 0, 0x30);
}

void func_0017db68(void) {
    D_00362424 = 0;
    D_00362428 = 0;
    D_0036242C = 0;
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
#include "data/bss_0057_mixed.h"
#include "data/data_0035.h"
#include "data/data_0036.h"
