/* A four-entry cache keyed by the world / room / area numbers D_002BC128,
 * D_002BC130, D_002BC134 (D_0052CB20 entries of 256 slots, the current one
 * D_0052EB40, ages from D_0052EB44); a guess at its use: what each room
 * remembers. Flag mode: default (the other modes are in the sibling files).
 * Read from the code, not proved by a boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00304D64.h"
#include "common.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/text_00130000_h7.h"

/* func_00142030 (from auto/text_00140000_10.c). */
M2C_UNK func_001418b8(M2C_UNK *);
extern s32 D_0052CB18;
void func_00142030(void) {
    D_0052CB18 = 0;
    func_001418b8(((M2C_UNK *)&D_00304C70));
}

/* func_001421d0 (from hand/text_00130000_h7.c). */
typedef struct {
    s32 key;
    s32 val;
} W7Kv;
typedef struct {
    s32 x0;
    s32 x4;
    W7Kv e[256];
} W7Tbl;
extern W7Tbl *D_0052EB40;
void func_001421d0(s32 k, s32 v) {
    s32 i;
    for (i = 0; i < 256; i++) {
        W7Kv *e = D_0052EB40->e;
        s32 *p = &e[i].key;
        if (*p == k) {
            D_0052EB40->e[i].val = v;
            return;
        }
        if (*p == -1) {
            *p = k;
            D_0052EB40->e[i].val = v;
            return;
        }
    }
}

/* func_00142240 (from hand/text_00130000_h7.c). */
s32 func_00142240(s32 k) {
    s32 i;
    for (i = 0; i < 256; i++) {
        W7Kv *e = D_0052EB40->e;
        s32 *p = &e[i].key;
        if (*p == k) {
            return D_0052EB40->e[i].val;
        }
        if (*p == -1) {
            *p = k;
            D_0052EB40->e[i].val = 0;
            return 0;
        }
    }
    return 0;
}

/* func_001422b0 (from hand/text_00130000_h7.c). */
extern W7Tbl D_0052CB20[4];
void func_001422b0(s32 n) {
    s32 i, j;
    for (i = 0; i < 4; i++) {
        if (D_0052CB20[i].x0 >= 0 && D_0052CB20[i].x4 >= D_0052EB44 - n - 1) {
            for (j = 0; j < 256; j++) {
                D_0052CB20[i].e[j].key = -1;
            }
        }
    }
}

/* func_00142340 (from hand/text_00130000_h7.c). */
void func_00142340(void) {
    s32 i;
    D_0052EB44 = 0;
    for (i = 0; i < 4; i++) {
        D_0052CB20[i].x0 = -1;
    }
}

