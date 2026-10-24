/* A four-entry cache keyed by the world / room / area numbers D_002BC128,
 * D_002BC130, D_002BC134 (D_0052CB20 entries of 256 slots, the current one
 * D_0052EB40, ages from D_0052EB44); a guess at its use: what each room
 * remembers. Flag mode: nostrict (the other modes are in the sibling files).
 * Read from the code, not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/types/nostrict_text_00130000_h55.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0037A378.h"
#include "vm/script_vm.h"

/* func_00142058 (from hand/nostrict/text_00130000_h55.c). */
extern W55Cache D_0052CB20[4];
extern W55Cache *D_0052EB40;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
void func_00142058(s32 lim) {
    W55Cache *best = D_0052CB20;
    W55Cache *e;
    s32 key, i;
    D_0052EB40 = 0;
    key = (D_002BC128 << 16) | (D_002BC130 << 8) | D_002BC134;
    e = D_0052CB20;
    for (i = 0; i < 4; i++, e++) {
        if (e->key == key && e->age >= D_0052EB44 - lim) {
            if (!D_0052EB40 || D_0052EB40->age < e->age) D_0052EB40 = e;
        }
        if (e->key < 0 || (best->key >= 0 && e->age < best->age)) best = e;
    }
    if (!D_0052EB40) {
        D_0052EB40 = best;
        best->key = key;
        for (i = 0; i < 256; i++) D_0052EB40->e[i].a = -1;
    } else {
        for (i = 0; i < 4; i++) {
            if (D_0052CB20[i].age < D_0052EB40->age) D_0052CB20[i].age++;
        }
    }
    D_0052EB40->age = D_0052EB44++;
}

