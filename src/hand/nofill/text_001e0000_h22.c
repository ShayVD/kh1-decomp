#include "common.h"

u32 func_001ee118(void);

u32 func_001ee388(void) {
    return (u32)((f32)(func_001ee118() % 60U) * 1.6666667f);
}

extern u16 D_003E890E[];
extern u8 D_003E5ED8[];

u8 *func_001efc10(s32 a) {
    return &D_003E5ED8[D_003E890E[a]];
}

#include "data/types/nofill_text_001e0000_h22.h"
#include "data/pieces/D_003E8E30.h"
typedef struct { u8 pad[0x68]; E8E30 *x68; } O68;

void func_001f4058(O68 *p, s32 i) {
    p->x68 = (i == -1) ? 0 : &D_003E8E30[i];
}
#include "data/data_003E.h"
