#include "common.h"

typedef struct W {
    s32 x0, x4, x8, xc, x10;
    struct W *x14;
    struct W *x18;
    s32 x1c, x20, x24, x28, x2c, x30, x34, x38, x3c;
    union {
        struct { u64 lo:32; u64 hi:32; } a;
        struct { u64 :32; u64 b0:1; u64 :31; } b;
    } u40;
    u64 c0:1;
    u64 crest:63;
    u64 x50;
    s32 x58, x5c;
    s32 id;
    void *x64;
    s32 x68;
    s32 x6c;
    s32 x70;
    f32 x74;
    f32 x78;
    s32 x7c, x80, x84, x88;
    s32 state;
    s32 x90, x94, x98, x9c, xa0, xa4, xa8, xac;
    s32 xb0, xb4;
    s16 xb8, xba, xbc, xbe, xc0, xc2, xc4, xc6, xc8, xca, xcc, xce;
    s16 xd0, xd2, xd4, xd6, xd8, xda;
    u8 xdc[16];
    u8 padec[4];
} W;

typedef struct {
    s32 x0, x4, x8;
    s16 xc, xe;
    u16 x10, x12, x14, x16, x18, x1a, x1c, x1e, x20;
} WA;

extern W D_0063F758[24]; /* src/data/bss_0063.c: Obj D_0063F758[24] */
extern W *D_00640DD8; /* src/data/bss_0064.c: s32 D_00640DD8 */
extern u8 D_00490AE0[];
s32 func_002366d8(s32, s32);
void func_001f3dc0(W *);

/* rodata */ /* jtbl at 0x490af0. Init-block store order read off the original; xdc filled by a count-up loop (loop.c reverses it: li 64 before li 15). */
W *func_001f31a8(WA *a, s32 b) {
    s32 i;
    W *p;
    s32 v;
    s32 j;

    if (a->x8 & 0xc) {
        p = D_0063F758;
        for (i = 0; i < 24; i++, p++) {
            switch (p->state) {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
                if (p->id == (s32)a) {
                    if (a->x8 & 8) return 0;
                    if (!((s32)p->u40.a.hi & 1)) return 0;
                }
                break;
            case 4:
            case 5:
                if (p->id == (s32)a) {
                    if (a->x8 & 8) return 0;
                }
                break;
            }
        }
    }
    p = D_0063F758;
    for (i = 0; i < 24; i++, p++) {
        if (p->state != 0) continue;

        p->x4 = a->x0;
        p->x8 = a->x4;
        p->u40.a.lo = 0;
        p->u40.b.b0 = 0;
        p->c0 = 0;
        p->x0 = 0;
        p->xc = 0;
        p->x64 = D_00490AE0;
        p->x10 = 0;
        p->x6c = 0x60000000;
        p->x1c = 0;
        p->x20 = 0;
        p->x24 = 0;
        p->x28 = 0;
        p->x2c = 0;
        p->x30 = 0;
        p->x34 = 0;
        p->x38 = 0;
        p->x3c = 0;
        p->x50 = 0;
        p->id = (s32)a;
        p->x68 = 0;
        p->x70 = 1;
        p->x74 = 1.0f;
        p->x78 = 1.0f;
        p->x7c = 0;
        if (b == -1) v = func_002366d8(4, 54) + 1; else v = b;
        p->x80 = v;
        p->x84 = v;
        p->x88 = a->x8;
        p->x90 = 128;
        p->state = 1;
        p->x94 = 0;
        p->xb0 = a->xc * 16 + 0x7000;
        p->xb4 = a->xe * 16 + 0x7400;
        p->x98 = 0;
        p->xb8 = a->x10 << 4;
        p->xba = a->x12 << 4;
        p->xbc = 0;
        p->x9c = 0;
        p->xbe = a->x14 << 4;
        p->xc0 = a->x16 << 4;
        p->xa0 = 0;
        p->xa4 = 0;
        p->xc2 = a->x18 << 4;
        p->xa8 = 0;
        p->xc4 = a->x1a << 4;
        p->xc6 = 0;
        p->xac = 0;
        p->xc8 = a->x1c << 4;
        p->xca = a->x1e;
        p->xcc = a->x1e;
        p->xce = a->x20;
        p->xd8 = 1;
        p->xd0 = 0;
        p->xd2 = 0;
        p->xd4 = 0;
        p->xd6 = 0;
        p->xda = 0;

        for (j = 0; j < 16; j++) p->xdc[j] = 64;
        if (D_00640DD8) {
            D_00640DD8->x14 = p;
            p->x18 = D_00640DD8;
        } else {
            p->x18 = 0;
        }
        p->x14 = 0;
        D_00640DD8 = p;
        func_001f3dc0(p);
        return p;
    }
    return 0;
}
