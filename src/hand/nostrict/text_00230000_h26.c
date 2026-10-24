/* 0x00230000-0x0024FFFF game code by hand (batch 26), built without
 * strict aliasing. */
#include "common.h"

#include "data/types/nostrict_text_00230000_h26.h"

/* 0xC0-byte records found by index from a header offset. */
extern s32 D_00669A18[8];

void func_0024b1f0(void) {
    s32 i;
    for (i = 0; i < 8; i++) D_00669A18[i] = 0;
}
#include "data/bss_0066_mixed.h"
