/* xs_genie.x func_00f215f8: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; s32 e; s32 f; } P24;
typedef struct { s32 max; P24 *buf; s32 n; s32 rd; } Q;

s32 func_00f215f8(Q *q, P24 *p) {
    if (q->n == q->rd) {
        return 0;
    }
    *p = q->buf[q->rd];
    q->rd++;
    if (q->n == q->rd) {
        q->rd = 0;
        q->n = 0;
    }
    return 1;
}
