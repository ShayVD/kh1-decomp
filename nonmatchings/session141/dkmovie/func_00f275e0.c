/* dkmovie.x func_00f275e0: near miss (session 141), 31 words, score 15 (was 20): goto loop using D_00F28460 directly everywhere. Left: the original loads D_00F28460 once into v0 and copies it to a1 in the b delay slot (the loop pointer is hoisted out of the loop); ours reloads it at the check label, so the 8-byte loop alignment nop is missing. Tried: local copy pointer before/after the start store, while/for forms (rotated loops, 164-172 bytes), all flag modes. */
#include "ovl.h"
typedef struct {
    u8 pad0[0x100];
    s32 size[(0x3DD4C - 0x100) / 4];
    s32 idx;
    s32 start[(0x3DF0C - 0x3DD50) / 4];
    s32 limit;
} Strm;
extern Strm *D_00F28460;
s32 func_00f275e0(s32 n) {
    s32 total = 0;
    s32 sz;
    D_00F28460->start[n] = D_00F28460->idx;
    goto check;
loop:
    total += sz;
    D_00F28460->idx++;
check:
    sz = D_00F28460->size[D_00F28460->idx];
    if (sz == 0) return total;
    if (total + sz < D_00F28460->limit) goto loop;
    return total;
}
