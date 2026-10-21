#include "common.h"

typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; s32 x10; } G958;
extern G958 D_0054F958;
#include "data/types/nostrict_text_00150000_s8_w16.h"
#include "data/pieces/D_00351530.h"
typedef struct { u8 pad[0x48]; s16 x48; } C130f;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x130 - 8]; C130f *x130; } Bf;
typedef struct { u8 pad[0x440]; u64 x440; } Af;
typedef union { u16 h; struct { u8 b0; u8 b1; } b; } Pf;
u8 func_0013c9e0(s32, s32);
s32 func_001ba2f8(s32);
void func_001ef7b0(s32);
Pf *func_00147778(s32);
void func_0013c638(s32, s32);
void func_001586a8(s32);
void func_00130340(Af *, s32, f32);
void func_001373f8(Af *, f32);
s32 func_001337e0(s32, Bf *, G958 *);

/* rodata: jtbl 0x48e4c0 (wqb03_rr.py 0048e4c0 MATCH). One s32 e reused (table entry, then D.xc before func_00147778) so combine cannot drop the per-case andi. */
s32 func_001519c0(Af *a, Bf *b) {
    s32 k;
    s32 e;
    Pf *p;

    k = b->x130->x48;
    D_0054F958.x0 = b->x4;
    D_0054F958.x10 = 0;
    e = D_00351530[k].h;
    D_0054F958.x4 = k;
    D_0054F958.xc = (u16)e >> 4;
    D_0054F958.x8 = ((u16)e >> 1) & 7;
    switch (D_0054F958.x8) {
    case 0:
        D_0054F958.x10 = func_0013c9e0((e & 0xffff) >> 4, 12) == 0xff;
        break;
    case 1:
        D_0054F958.x10 = func_001ba2f8((e & 0xffff) >> 4) == 0;
        break;
    case 3:
        D_0054F958.xc *= 10;
        func_001ef7b0(D_0054F958.xc);
        break;
    case 7:
        e = D_0054F958.xc;
        p = func_00147778(e);
        if (!(p->h & 0xf)) {
            D_0054F958.x8 = 0;
            D_0054F958.xc = p->b.b1;
            D_0054F958.x10 = func_0013c9e0(p->b.b1, 12) == 0xff;
        }
        break;
    case 2: case 4: case 5: case 6:
        break;
    }
    if (!D_0054F958.x10) {
        func_0013c638(k, 1);
        func_001586a8(16);
    }
    a->x440 |= 0x200000000ULL;
    func_00130340(a, 0x900a6, 0.0f);
    func_001373f8(a, 0.0f);
    return func_001337e0(5, b, &D_0054F958);
}
