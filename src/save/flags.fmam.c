/* The save-data command of src/save/flags.c that needs fmam
 * (-fmove-all-movables; without it 2 words differ, the giv-init copy
 * order).  The source keeps `c < r->s.tbl[a + 1][j]` read through r, not q. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/vm_sub.h"

/* h45's view of save block 1's score tables from +4 (src/save/flags.c). */
typedef struct { u8 pad[0xb10]; u32 tbl[4][5]; } Save1Tbl;
typedef struct { s32 x0; Save1Tbl s; } Save1T;

void *func_00232cc0(s32);

s32 func_001eb7b0(VmRec *vm) {
    VmSub *s = (VmSub *)&vm->obj;
    s32 i = vm->sp;
    s32 a = s->stk[i - 2];
    u32 b = s->stk[i - 1];
    u32 c = s->stk[i];
    Save1T *r = func_00232cc0(1);
    Save1Tbl *q = &r->s;
    s32 j, k;
    for (j = 0; j < 5; j++) {
        if (q->tbl[a][j] < b) {
            for (k = j; k < 4; k++) {
                q->tbl[a][k + 1] = q->tbl[a][k];
                q->tbl[a + 1][k + 1] = q->tbl[a + 1][k];
            }
            q->tbl[a][j] = b;
            q->tbl[a + 1][j] = c;
            break;
        }
        if (q->tbl[a][j] == b && c < r->s.tbl[a + 1][j]) {
            for (k = j; k < 4; k++) {
                q->tbl[a][k + 1] = q->tbl[a][k];
                q->tbl[a + 1][k + 1] = q->tbl[a + 1][k];
            }
            q->tbl[a][j] = b;
            q->tbl[a + 1][j] = c;
            break;
        }
    }
    vm->sp -= 3;
    return 2;
}
