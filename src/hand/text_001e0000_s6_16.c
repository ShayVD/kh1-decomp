#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/vm_rec.h"
#include "vm/script_vm.h"

/* func_001ea128 is in src/vm/vm_util.c. */

/* func_001ea5f8, func_001ea658, func_001ea808, func_001ea888 are in src/vm/vm_ent.c. */




typedef W606Mem_304be8 C116;
typedef struct { u8 pad[0x48e]; u8 f48e[4]; } W17;

s32 func_001eeeb8(s32 id) {
    s32 n = 0, i;
    u8 c;
    C116 *e;
    for (i = 0; i < 4; i++) {
        c = D_00304BE8->x48e[i];
        if (c == 0xff) break;
        e = &D_00304BE8->m[c];
        if (e->sub.x32 == id) n++;
    }
    return n;
}

s32 func_001eef38(s32 id) {
    s32 n = 0, i, j;
    u8 c;
    C116 *e;
    for (i = 0; i < 4; i++) {
        c = D_00304BE8->x48e[i];
        if (c == 0xff) break;
        e = &D_00304BE8->m[c];
        for (j = 0; j < e->sub.x18; j++) {
            if (e->sub.x19[j] == id) n++;
        }
    }
    return n;
}

/* func_001e99e8 is in src/vm/vm_find.nofill.c. */
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
