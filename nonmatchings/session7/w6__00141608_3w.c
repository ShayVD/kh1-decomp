/* func_00141608: 3w off, hand/nostrict (hand strict also 3). From s6 49w: clamp written as if (v < 0) { if (s->x44 > 0) {...} else v = 0; } else if (v > max) v = max; the id tests read o->info->x4c directly (not a local) with t = (o->info->x4c == 0) so cse does not fold m[0]. Still off: the original indexes m[] with a copy of the first load (move a0,v1: gcse load CSE) where ours reloads lhu 76(a0) (cse sees HI-mode loads for the compares and a zero_extend load for the index, so nothing merges); the lui/lw pair order follows. */
#include "common.h"
typedef struct { u8 pad[0x70]; u8 bits; u8 r[3]; } W7Mem;
typedef struct { u8 pad[4]; W7Mem m[10]; } W7Save;
extern W7Save *D_00304BE8;
typedef struct { u8 pad[0x38]; s16 x38; } T16c8;
typedef struct { u8 pad[0x44]; s32 x44; s32 x48; u8 pad4c[0xbe - 0x4c]; u16 xbe; u8 padc0[8]; T16c8 *xc8; } T16s;
typedef struct { u8 pad[0x4c]; u16 x4c; } T16i;
typedef struct { u8 pad[0x6c]; T16s *x6c; u8 pad70[0x130 - 0x70]; T16i *info; } T16o;
extern T16s D_00304C70;
extern u32 D_002C5958;
s32 func_00141540(T16o *o, s32 a);
s32 func_00141608(T16o *o, s32 n) {
    T16s *s = o->x6c;
    u16 id;
    s32 v, max;
    s32 t;
    if (s == 0 || s == &D_00304C70) return 0;
    if ((D_002C5958 >> 11) & 1) return s->xbe;
    if (o->info->x4c >= 10) return s->xbe;
    t = (o->info->x4c == 0);
    if (t && D_00304BE8->m[o->info->x4c].bits == 0) return s->xbe;
    v = s->xbe + n;
    max = s->x48 * 30;
    if (v < 0) {
        if (s->x44 > 0) {
            v += s->x44 * 30;
            func_00141540(o, -1);
        } else {
            v = 0;
        }
    } else if (v > max) {
        v = max;
    }
    s->xbe = v;
    if (s->xc8) s->xc8->x38 = v;
    return v;
}
