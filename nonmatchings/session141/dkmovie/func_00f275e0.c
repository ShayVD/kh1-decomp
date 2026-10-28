/* dkmovie.x func_00f275e0: near miss (session 141), score 20: a goto loop gives the original's unrotated shape; the original loads D_00F28460 into v0 and copies it to a1 in the b delay slot (ours loads it straight into a1). */
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
    Strm *s = D_00F28460;
    s32 total = 0;
    s32 sz;
    s->start[n] = s->idx;
    goto check;
loop:
    total += sz;
    s->idx++;
check:
    sz = s->size[s->idx];
    if (sz == 0) return total;
    if (total + sz < s->limit) goto loop;
    return total;
}
