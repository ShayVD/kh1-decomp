/* The party members' records in the save data D_00304BE8: abilities, items
 * and equipment by member (func_0013c968 asks whether a member has ability
 * c, func_0013c318, func_0013c598 ...), member stats, and func_0013cb98
 * builds the records from the new-game data D_00351530. Flag mode: nostrict
 * (the other modes are in the sibling files). Read from the code, not proved
 * by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00308CDC.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002E27C8.h"

/* func_0013c458 (from hand/nostrict/text_00130000_s6_06.c). */
typedef W606Mem_304be8 W606Mem;
u16 *func_0013c3f8(s32 i);
void func_0015b268(s32 i);
void func_0015b438(s32 i);
s32 func_0013c458(s32 i, s32 n) {
    W606Mem *m = &D_00304BE8->m[i];
    u16 *p = func_0013c3f8(i);
    s32 lv = 1;
    s32 first = 1;
    s32 e = n + m->sub.exp;
    if (e > 999999) e = 999999;
    m->sub.exp = e;
    while (lv < 100) {
        e -= *p++;
        if (e < 0) break;
        lv++;
        if (m->sub.lv < lv) {
            func_0015b268(i);
            if (first) {
                first = 0;
                func_0015b438(i);
            }
        }
    }
    return m->sub.exp;
}

/* func_0013c9e0 (from hand/nostrict/text_00140000_h33.c). */
typedef W606Mem_304be8 W7Member;
typedef struct { u8 x0, x1, x2; } Item;
Item *func_00147840(s32);
s32 func_0013c9e0(s32 item, u32 who) {
    if (item & 0x400) return 255;
    if (who < 10) {
        W7Member *m = &D_00304BE8->m[who];
        if (func_00147840(item)->x2 == 0) {
            s32 k;
            for (k = 0; k < m->sub.x21; k++) {
                if (m->sub.x22[k] == 0) {
                    m->sub.x22[k] = item;
                    return who;
                }
            }
        }
    }
    if (D_00304BE8->items[item] < 99) {
        D_00304BE8->items[item]++;
        return 12;
    }
    return 255;
}

/* func_0013cae8 (from hand/nostrict/text_00140000_h33.c). */
s32 func_0013cae8(u32 who, s32 item) {
    if (who < 10) {
        W7Member *m = &D_00304BE8->m[who];
        s32 k;
        for (k = 0; k < m->sub.x21; k++) {
            if (m->sub.x22[k] == item) {
                m->sub.x22[k] = 0;
                return who;
            }
        }
    }
    if (D_00304BE8->items[item] != 0) {
        D_00304BE8->items[item]--;
        return 12;
    }
    return 255;
}

