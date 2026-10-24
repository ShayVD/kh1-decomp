#include "common.h"

typedef struct { s32 x0; u8 pad[28]; } E63;
typedef struct { u8 pad[0xc]; s32 n; E63 e[1]; } H63;
void func_00176640(s32);

/* h is reassigned from base after p is set, so cse keeps base as the canonical register
   for the copied entry test (lw 12(s2)) while the loop test still reads h (a0). */
void func_001763f0(H63 *h) {
    s32 base = (s32)h;
    s32 *p = (s32 *)base;
    s32 i = 0;
    h = (H63 *)base;
    p += 4;
    for (; i < h->n; i++) {
        if (*p) *p += base;
        p += 8;
    }
    {
        s32 k = *p++;
        if (k > 0) {
            i = k;
            do {
                func_00176640(*p++ + base);
            } while (--i);
        }
    }
}

/* func_001cb3c0 is in src/msgwin/msgwin.c. */

#include "data/data_003C.h"
