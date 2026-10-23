/* The function of src/text/text.c that needs nofill: system message id
 * (from 1) to its string. */
#include "common.h"

extern u8 D_003E5ED8[];
extern u16 D_003E890E[];

u8 *func_001efc10(s32 a) {
    return &D_003E5ED8[D_003E890E[a]];
}
