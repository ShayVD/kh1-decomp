/* wm.x func_00f3a5a0: matched by hand. */
#include "ovl.h"

typedef struct { s32 type; s32 pad[3]; s32 k; s32 pad2[7]; } Ent;
typedef struct { u8 pad[0x10C]; Ent *e; } A;
s32 func_00f39968(s32, A *, Ent *);

s32 func_00f3a5a0(A *a) {
    s32 i;
    Ent *p;
    Ent *q;
    q = a->e;
    if (q->type != 1) {
        p = q;
        i = 0;
        do {
            if (p->k == 5 && func_00f39968(-1, a, &a->e[i]) != 0) return 1;
            p++;
            i++;
        } while (p->type != 1);
    }
    return 0;
}
