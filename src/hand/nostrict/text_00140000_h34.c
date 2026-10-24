#include "common.h"
void *func_0014a4a8();
typedef struct { u8 pad[0x20]; f32 x20; u8 pad24[8]; f32 x2c; u8 x30; u8 x31; s8 x32; u8 x33; } W34Prm;
typedef struct { u8 pad[0x14]; s32 x14; W34Prm *x18; u8 pad1c[0x14]; s32 x30; } W34Eff;
typedef struct { u8 pad[0x40]; f32 x40; u8 pad44[0x14c - 0x44]; W34Eff *x14c; } W34EObj;
typedef struct { u8 pad[8]; s32 x8; f32 xc; u8 pad10[0x10]; s32 x20; f32 x24; f32 x28; u8 pad2c[0x60 - 0x2c]; s32 *x60; s32 x64; u8 pad68[0x94 - 0x68]; f32 x94; s32 x98; } W34Prt;
W34Prt *func_0014a908(W34EObj *o) {
    W34Prt *r = func_0014a4a8(o);
    if (o->x14c) {
        if (r->x20 == 48) {
            W34Prm *p = o->x14c->x18;
            r->xc += p->x20 * o->x40;
            r->x24 *= p->x2c;
            r->x28 *= p->x2c;
            r->x64 += p->x33;
            if (r->x64 >= 100) r->x64 = 99;
            else if (r->x64 <= 0) r->x64 = 1;
            r->x94 *= p->x31 * 0.0499999970197677612304688f;
            r->x98 += p->x32;
        }
        r->x8 = o->x14c->x14;
        r->x60 = &o->x14c->x30;
        o->x14c->x30 = 0;
    }
    return r;
}
#include "data/types/nostrict_text_00140000_h34.h"
#include "data/data_0030.h"
