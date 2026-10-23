#include "common.h"
#include "data/bss_0064.h"

#include "data/types/text_001f0000_h23.h"
extern s32 D_00640E00[];
extern s32 D_00640E20;
extern s32 D_00640E24;
extern s32 D_00640E28;

void func_00207598(void) {
    s32 i;
    D_00640E24 = 0;
    for (i = 0; i < D_00640E20; i++) {
        if (D_00640E28 == D_00640E00[i]) D_00640E24 = i;
    }
}

#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
