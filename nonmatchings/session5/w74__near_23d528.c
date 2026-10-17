#include "common.h"
typedef struct { s32 x, y, z, w; } T16;
typedef struct { s32 unk0; u8 pad4[0x90]; s32 unk94; u8 pad98[4]; void *unk9C; } Ob9C;
extern T16 D_00454600[];
extern T16 D_00454650[];
extern T16 D_00454680[];
extern T16 D_004546C0[];
extern T16 D_00454700[];
void func_0024ac08(void *, s32 *);

void func_0023d528(Ob9C *o, s32 *p1, s32 *p2) {
    s32 r[2];
    T16 *t;
    switch (o->unk0) {
    case 0:
        t = D_00454650;
        p1[0] = D_00454600[0].x;
        p1[1] = D_00454600[0].y;
        goto idx;
    case 1:
        p1[0] = D_00454600[1].x;
        p1[1] = D_00454600[1].y;
        p2[0] = D_00454680[0].x;
        p2[1] = D_00454680[0].y;
        break;
    case 2:
        p1[0] = D_00454600[2].x;
        p1[1] = D_00454600[2].y;
        p2[0] = D_004546C0[0].x;
        p2[1] = D_004546C0[0].y;
        break;
    case 3:
        t = D_00454700;
        p1[0] = D_00454600[3].x;
        p1[1] = D_00454600[3].y;
        goto idx;
    case 4:
        t = D_00454650;
        p1[0] = D_00454600[4].x;
        p1[1] = D_00454600[4].y;
    idx:
        p2[0] = t[o->unk94].x;
        p2[1] = t[o->unk94].y;
        break;
    }
    if (o->unk9C != 0) {
        func_0024ac08(o->unk9C, r);
        p2[0] += r[0];
        p2[1] += r[1];
    }
}
