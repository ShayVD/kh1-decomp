/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0017dbb8();
extern s32 D_002E27A8;
extern s32 D_003623F0;
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
#include "data/pieces/D_00362430.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_00362438.h"
#include "data/pieces/D_0036243C.h"
extern s32 D_00362440;
extern s32 D_00362444;
extern s32 D_00362448;
extern void *D_00575894;
void func_0017e8a0(void);
void func_0017eaa0(void);

void func_0017e7d8(void) {
    if (D_00575894 != NULL) {
        M2C_FIELD(D_00575894, s32 *, 0) = (s32) (M2C_FIELD(D_00575894, s32 *, 0) | 1);
        M2C_FIELD(D_00575894, f32 *, 0x64) = 1.0f;
        func_0017dbb8();
    }
    D_00575894 = NULL;
    D_002E27A8 = 0;
    D_003623F0 = 1;
}

void func_0017eb20(void) {
    func_0017eaa0();
    (*(s32 *)&D_00362428) = 0;
    (*(s32 *)&D_0036242C) = 0;
    (*(s32 *)&D_00362430) = 0;
    D_00362434 = 0;
    D_00362438 = 0;
    D_0036243C = 0;
    D_00362440 = 0;
    D_00362444 = 0;
    D_00362448 = 0;
    func_0017e8a0();
}
#include "data/bss_0057_mixed.h"
#include "data/data_002E.h"
#include "data/data_0036.h"
