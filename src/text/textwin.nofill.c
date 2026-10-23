/* The function of src/text/textwin.c that needs nofill: set a window's
 * +0x68 to entry i of D_003E8E30 (-1: none). */
#include "common.h"
#include "text/textwin.h"
#include "data/pieces/D_003E8E30.h"

void func_001f4058(TextWin *p, s32 i) {
    p->x68 = (i == -1) ? 0 : &D_003E8E30[i];
}
