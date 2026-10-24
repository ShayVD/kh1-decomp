/* Hand-matched functions (worker b03). */
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"

extern f32 D_002BBDFC;
extern u32 D_002C5958;

extern f32 D_002BBDFC;
extern u32 D_002C5958;
f32 D_0052AD04 ALIGNED(4);
f32 D_0052AD08 ALIGNED(8);
f32 D_0052AD0C ALIGNED(4);
f32 D_0052AD10[4] ALIGNED(16);
f32 D_0052AD20[4] ALIGNED(16);
f32 D_0052AD30[4] ALIGNED(16);
f32 D_0052AD40[4] ALIGNED(16);
f32 D_0052AD50 ALIGNED(16);

typedef W606Mem_304be8 B3SvEnt;
typedef Save_304be8 B3Sv;
typedef struct {
    u8 x0, x1, x2, x3, x4;
    u8 x5[16];
    u8 x15, x16;
} B3SvSrc;
#include "data/pieces/D_00304BE8.h"
extern s32 D_00304BC0[10];
#include "data/pieces/D_00351530.h"
B3Sv *func_00232cc0(s32);
B3SvSrc *func_001477c8(s32);
void func_0013c9e0(s32, s32);
void func_0013c638(s32, s32);

void func_0013cb98(void) {
    B3Sv *s;
    B3SvSrc *d;
    B3SvEnt *e;
    s32 i, j;

    B3Sv **pp = &D_00304BE8;
    s = func_00232cc0(0);
    *pp = s;
    s->x0 = 5;
    for (i = 0; i < 256; i++) s->items[i] = 0;
    for (i = 0; i < 10; i++) {
        s->m[i].sub.x32 = D_00304BC0[i];
        func_0013c9e0(D_00304BC0[i], 12);
    }
    s->x48e[0] = 0;
    for (i = 1; i < 4; i++) s->x48e[i] = -1;
    for (i = 0; i < 48; i++) s->list599[i] = 0;
    e = s->m;
    d = func_001477c8(14808);
    for (i = 0; i < 10; i++) {
        e->sub.w34.h.x34 = 1;
        e->sub.lv = 1;
        e->sub.x1 = e->sub.hpmax = d->x0;
        e->sub.x3 = e->sub.mpmax = d->x1;
        e->sub.x38 = 0;
        e->sub.x5 = d->x2;
        e->sub.x6 = d->x3;
        e->sub.x7 = d->x4;
        e->sub.x18 = d->x15;
        e->sub.x21 = d->x16;
        e->sub.exp = 0;
        for (j = 0; j < 16; j++) e->sub.x8[j] = d->x5[j];
        for (j = 0; j < 8; j++) e->sub.x19[j] = 0;
        for (j = 0; j < 16; j++) e->sub.x22[j] = 0;
        for (j = 0; j < 48; j++) e->sub.name[j] = 0;
        e++;
        d++;
    }
    for (i = 0; i < 512; i++) func_0013c638(i, (*(u16 (*)[512])&D_00351530)[i] & 1);
    for (i = 0; i < 7; i++) s->x7d0[i] = -1;
    for (i = 0; i < 7; i++) D_00304BE8->b492[i] = 1;
    for (i = 0; i < 3; i++) s->x844[i] = -1;
}
#include "data/data_0030.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
