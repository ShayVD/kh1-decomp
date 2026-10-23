#include "common.h"

#include "data/types/nofill_text_001e0000_h22.h"
#include "data/pieces/D_003E8E30.h"
typedef struct { u8 pad[0x68]; E8E30 *x68; } O68;

void func_001f4058(O68 *p, s32 i) {
    p->x68 = (i == -1) ? 0 : &D_003E8E30[i];
}
#include "data/data_003E.h"
