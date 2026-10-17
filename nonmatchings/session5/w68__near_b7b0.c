#include "common.h"
#include "/tmp/claude-0/s/w68/hdr11.h"
s32 func_001eb7b0(VM *vm) {
    Sub *s = &vm->u.s;
    s32 i = vm->u.h.sp;
    s32 a = s->stk[i - 2];
    u32 b = s->stk[i - 1];
    u32 c = s->stk[i];
    Rec98 *r = func_00232cc0(1);
    Rec98s *q = &r->s;
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
        if (q->tbl[a][j] == b && c < q->tbl[a + 1][j]) {
            for (k = j; k < 4; k++) {
                q->tbl[a][k + 1] = q->tbl[a][k];
                q->tbl[a + 1][k + 1] = q->tbl[a + 1][k];
            }
            q->tbl[a][j] = b;
            q->tbl[a + 1][j] = c;
            break;
        }
    }
    vm->u.h.sp -= 3;
    return 2;
}
