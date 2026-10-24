#include "common.h"

#include "data/pieces/D_002A6308.h"
#include "data/pieces/D_002A6318.h"
#include "data/pieces/D_002A6324.h"
void func_00104908(void) {
    (*(s32 (*)[3])&D_002A6318)[0] = (*(s32 (*)[3])&D_002A6308)[0] = (*(s32 (*)[3])&D_002A6318)[1] = (*(s32 (*)[3])&D_002A6318)[2] = (*(s32 (*)[3])&D_002A6308)[1] = (*(s32 (*)[3])&D_002A6308)[2] = -1;
    D_002A6324 = 0;
}

#include "data/types/text_00100000_s6_na.h"

/* func_001cdc58 is in src/vm/vm_lib.c. */
#include "data/data_002B.h"
