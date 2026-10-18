/* func_001eb7b0: 2 words off (was 20), mode hand. Fix: read the equality-case compare through r (c < r->s.tbl[a + 1][j]) instead of q, which gives the 4th loop giv. Left: the order of the two giv-init copies before the loop (ours move t1,t0; move a1,a3, orig the reverse; created by the second loop.c pass). Statement/loop-form/compare/store-order variants all stay at 2. */
/* 20w (all modes): orig has 4 loop givs (separate row-base copies t0/t1 for the two shift loops, separate a1 for the c<tbl[a+1][j] compare); ours shares them, 4 bytes shorter. strict hand */
#include "common.h"

/* Script VM handlers: obj at +4, top index at +0x180, value stack at +0x184.
 * The stack is indexed off &vm->u.s (vm+4) with a local copy of sp. */
typedef struct {
    void *obj;
    u8 pad4[0x17c];
    s32 stk[105];
} Sub;
typedef struct {
    s32 x0;
    union {
        Sub s;
        struct { void *obj; u8 pad[0x178]; s32 sp; } h;
    } u;
} VM;
typedef struct { u8 pad[0xb10]; u32 tbl[4][5]; } Rec98s;
typedef struct { s32 x0; Rec98s s; } Rec98;
Rec98 *func_00232cc0(s32);

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
    vm->u.h.sp -= 3;
    return 2;
}
