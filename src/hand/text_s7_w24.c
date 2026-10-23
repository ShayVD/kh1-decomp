#include "common.h"

#include "data/pieces/D_00364130.h"
typedef E0C0_364130_3 E0C0;
void func_00181f50(E0C0 *);

void func_00181fe0(E0C0 **out) {
    s32 i;
    E0C0 *e;
    for (i = 0; i < 256; i++) {
        e = &D_00364130.e0C0_3[i];
        if (!(e->x80 & 0x3000000000000)) {
            func_00181f50(e);
            *out = e;
            break;
        }
    }
}

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

typedef struct { u8 pad[0xD00]; } EntA;
typedef struct { s32 used[8]; EntA ent[5]; s32 unk4120; s32 unk4124; } G51E50;
extern G51E50 D_00651E50;
typedef struct { u8 pad[0x4C]; u16 x4c; } O130;
typedef struct { u8 pad[0x130]; O130 *x130; } Obj910;
s32 func_0013c318(u16);

EntA *func_00240910(Obj910 *o) {
    EntA *p;
    EntA *r;
    s32 k = func_0013c318(o->x130->x4c);
    r = 0;
    if (k == 1 || k == 2) {
        if (k == 1) {
            if (D_00651E50.used[1]) { p = &D_00651E50.ent[1]; goto set; }
        } else {
            if (D_00651E50.used[2]) { p = &D_00651E50.ent[2]; goto set; }
        }
    }
    return r;
set:
    r = p;
    return r;
}

#include "data/data_003C.h"
