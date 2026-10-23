#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00304BE8_s.h"
extern s32 D_00642C88;

void func_00214f50(void) {
    s32 i;
    Save_304be8 *p = D_00304BE8;
    D_00642C88 = 0;
    i = 0;
    if (p->list599[i]) {
        D_00642C88 = 1;
        for (;;) {
            i++;
            if (i >= 48 || !D_00304BE8->list599[i]) return;
            D_00642C88++;
        }
    }
}
#include "data/data_003F.h"
