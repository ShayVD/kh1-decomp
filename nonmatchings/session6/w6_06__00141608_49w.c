/* ~49w off (nostrict): gcc folds D->m[id] with id==0 known (original keeps move a0,v1 + full id*0x74 calc), plus return-0 block layout and clamp/blezl shape differ. Unfinished. */
#include "common.h"
#include "/tmp/claude-0/s/w6_06/w7.h"
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
    if (s == 0 || s == &D_00304C70) return 0;
    if ((D_002C5958 >> 11) & 1) return s->xbe;
    id = o->info->x4c;
    if (id >= 10) return s->xbe;
    if (id == 0 && D_00304BE8->m[id].bits == 0) return s->xbe;
    v = s->xbe + n;
    max = s->x48 * 30;
    if (v < 0) {
        if (s->x44 <= 0) {
            v = 0;
        } else {
            v += s->x44 * 30;
            func_00141540(o, -1);
        }
    } else if (v > max) {
        v = max;
    }
    s->xbe = v;
    if (s->xc8) s->xc8->x38 = v;
    return v;
}
