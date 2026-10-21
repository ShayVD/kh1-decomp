/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_002A6210.h"
#include "data/pieces/D_002A6220.h"
#include "data/pieces/D_002A6234.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A623C.h"
extern s32 D_002A6240;
#include "data/pieces/D_002A6244.h"
extern s32 D_002A6248;
#include "data/pieces/D_002A624C.h"
#include "data/pieces/D_002A6250.h"
extern s32 D_002A6254;
extern s32 D_002A6258;
extern s32 D_002A625C;
extern s32 D_002A6260;
extern s32 D_002A6264;
extern s32 D_002A6268;
extern s32 D_002A626C;
#include "data/pieces/D_002A62AC.h"
#include "data/pieces/D_002A62B0.h"
extern s32 D_002A62B4;
extern s32 D_002A62B8;
extern s32 D_002A62BC;
#include "data/pieces/D_002A62C0.h"
#include "data/pieces/D_002A62C4.h"
#include "data/pieces/D_002A62C8.h"
#include "data/pieces/D_002A62CC.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002A62D4.h"
#include "data/pieces/D_002A62D8.h"
#include "data/pieces/D_002A62DC.h"
#include "data/pieces/D_002A62E0.h"
#include "data/pieces/D_002A62E4.h"
extern s32 D_002A62EC;

void func_00103280(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    M2C_FIELD((M2C_UNK *)&D_002A6210, f32 *, 0) = fparg0;
    M2C_FIELD((M2C_UNK *)&D_002A6210, f32 *, 4) = fparg1;
    M2C_FIELD((M2C_UNK *)&D_002A6210, f32 *, 8) = fparg2;
    M2C_FIELD((M2C_UNK *)&D_002A6210, f32 *, 0xC) = fparg3;
    M2C_FIELD((M2C_UNK *)&D_002A6220, s32 *, 0) = 0;
    M2C_FIELD((M2C_UNK *)&D_002A6220, s32 *, 4) = 0;
    M2C_FIELD((M2C_UNK *)&D_002A6220, s32 *, 8) = 0;
}

void func_00104678(void) {
    D_002A6234 = (*(s32 *)&D_002A62AC);
    D_002A6238 = ((s32)D_002A62B0);
    (*(s32 *)&D_002A623C) = D_002A62B4;
    D_002A6240 = D_002A62B8;
    (*(s32 *)&D_002A6244) = D_002A62BC;
    D_002A6248 = (*(s32 *)&D_002A62C0);
    (*(s32 *)&D_002A624C) = (*(s32 *)&D_002A62C4);
    (*(s32 *)&D_002A6250) = (*(s32 *)&D_002A62C8);
    D_002A6254 = (*(s32 *)&D_002A62CC);
    D_002A6258 = D_002A62D0;
    D_002A625C = D_002A62D4;
    D_002A6260 = D_002A62D8;
    D_002A6264 = D_002A62DC;
    D_002A6268 = D_002A62E0;
    D_002A626C = D_002A62E4;
    D_002A62EC = 1;
}
#include "data/data_002A.h"
