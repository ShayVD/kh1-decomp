/* The start up and the frame loop: func_0011ecd8 the boot (the pads, the
 * disc, the scratchpad stack, the game phases), func_0011edc8 one frame (the
 * frame callbacks of src/util/proc.c, the object updates, the draw),
 * func_0011eeb0 the frame's end (1 / the frame time into D_002C5970,
 * func_0011f130 over the main list, the double buffer flip D_002C5950). Flag
 * mode: default (the other modes are in the sibling files). Read from the
 * code, not proved by a boot (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004F.h"
#include "data/types/text_00110000_h30.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC140.h"
#include "data/types/text_00110000_h30_p.h"
#include "data/pieces/D_002C58D0.h"

/* func_0011eda8 (from auto/text_00110000.c). */
M2C_UNK func_0015ef60();
s32 func_0011eda8(void) {
    func_0015ef60();
    return 0;
}

/* func_0011edc8 (from hand/text_00110000_h30.c). */
void *func_0011ef10(s32, void *);
typedef struct { u32 b0 : 1; u32 rest : 31; } Bits5958;
extern Bits5958 D_002C5958;
typedef struct { u16 type; s16 f2; } NodeHd;
extern s32 D_002C5950;
extern s32 D_002C596C;
extern u8 D_004E3A48[];
u8 D_004E3A58[0x828] ALIGNED(8);
void func_0011efa8(void *, void *, s32, s32);
void func_0015ec68(void);
void func_00121c78(void);
void func_00122028(void);
void func_00120a70(void);
void func_00147628(void);
void func_0011fb00(void);
void func_0012fc20(void);
void func_0011edc8(void) {
    s32 i, j;
    PlatVu0UnitMatrix(D_002C58D0);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) D_002C5910[i][j] = 0;
    }
    D_002C5950 = 0;
    *(s32 *)&D_002C5958 = 0;
    D_002C596C = 0;
    func_0011efa8(D_004E3A48, D_004E3A58, 16, 128);
    func_0015ec68();
    func_00121c78();
    func_00122028();
    func_00120a70();
    func_00147628();
    func_0011fb00();
    func_0012fc20();
    ((NodeHd *)func_0011ef10(150000, func_0011eda8))->f2 = -1;
}

/* func_0011eeb0 (from auto/text_00110000.c). */
M2C_UNK func_0011f130(M2C_UNK *, s32);
extern f32 D_002BBDFC;
extern f32 D_002C5970;
#define D_004E3A48 (*(M2C_UNK (*)) &D_004E3A48)
void func_0011eeb0(void) {
    D_002C5970 = 1.0f / D_002BBDFC;
    func_0011f130(&D_004E3A48, D_002C596C);
    D_002C5950 ^= 1;
}
#undef D_004E3A48

