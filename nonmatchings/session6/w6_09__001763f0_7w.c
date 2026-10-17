/* 7w off (nostrict/strict same): prologue copies: orig s2=a0 (base), s0=s2 (walker), entry test lw 12(s2); ours s0=a0, s2=s0, lw 12(a0) */
#include "common.h"
typedef struct { s32 x0; u8 pad[28]; } E63;
typedef struct { u8 pad[0xc]; s32 n; E63 e[1]; } H63;
void func_00176640(s32);

void func_001763f0(H63 *h) {
    s32 i = 0;
    s32 base = (s32)h;
    s32 *p = (s32 *)base;
    p += 4;
    for (; i < h->n; i++) {
        if (*p) *p += base;
        p += 8;
    }
    {s32 k = *p++;
    if (k > 0) {
        i = k;
        do {
            func_00176640(*p++ + base);
        } while (--i);
    }}
}
