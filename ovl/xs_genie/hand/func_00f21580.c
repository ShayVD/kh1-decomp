/* xs_genie.x func_00f21580: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; s32 e; s32 f; } P24;
typedef struct { s32 max; P24 *buf; s32 n; } Q;

s32 func_00f21580(Q *q, P24 *p) {
    if (q->n == q->max) {
        return 0;
    }
    q->buf[q->n] = *p;
    q->n++;
    return 1;
}
