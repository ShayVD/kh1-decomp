/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_00425C48.h"
#include "data/pieces/D_00425C68.h"
#include "data/pieces/D_00425C88.h"
extern s8 D_00648050; /* src/data/bss_0064.c: f32 D_00648050[5] */

void func_00233f68(s32 arg0, s32 arg1) {
    *(M2C_UNK *)((s8 *)&D_00425C48 + (((arg0 * 4) + arg1) * 4)) = 0;
}

void func_00233fb0(s32 arg0, s32 arg1) {
    *(M2C_UNK *)((s8 *)&D_00425C68 + (((arg0 * 4) + arg1) * 4)) = 0;
}

void func_00233ff8(s32 arg0, s32 arg1) {
    *(M2C_UNK *)((s8 *)&D_00425C88 + (((arg0 * 4) + arg1) * 4)) = 0;
}

void func_00236928(s32 arg0) {
    f32 *temp_a0;

    temp_a0 = &D_00648050 + (arg0 * 4);
    *temp_a0 = ((*temp_a0 * 69069.0f) + 1.0f) * 2.32830644e-10f;
}
