#include "common.h"
#include "data/bss_0062.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { s32 a, b, c, d; } Q4;
typedef union { u128 q; u32 w; } U128;
typedef struct { U128 dma; u64 gif[8]; Q4 v[400]; U128 end; } Pkt620;


#include "data/types/text_001e0000_h68.h"
typedef struct { s8 used; u8 pad1[3]; s32 x4; s32 x8; s32 xc; s32 x10; u8 pad[180 - 20]; } Ent180;
typedef struct { u8 b0; u8 b1; s8 x2; s8 x3; s8 used; u8 pad5[11]; s32 x10; u8 pad[72 - 20]; } Ent72;

#include "data/pieces/D_00304BE8_s.h"
extern s32 D_003F7A68;
#include "data/pieces/D_003DBA68.h"
#include "data/pieces/D_003DC2A8.h"
#include "data/pieces/D_003DC370.h"
#include "data/pieces/D_003DCB90.h"
#include "data/pieces/D_003DD230.h"
extern s32 D_003DD258;
extern s32 D_003DD28C;
extern s32 D_003DD308;
extern s32 D_003DD30C;
extern s32 D_003DD310;
extern s32 D_003DD314;
extern s32 D_003C21A0;
#include "data/pieces/D_003C3A70.h"
extern s32 D_003C54F0;
extern RpcCd D_003E3C88;
extern s32 D_003E3CB0;
extern u32 D_00633640[2048];
extern s32 D_00635640[1024][8];
extern Ent180 D_0063D640[];
extern Ent72 D_0063EE40[];
extern u8 D_0063F640[256];
extern char D_00490910[];
extern u8 D_00490940[];
extern Pkt620 D_00631620;

s32 func_0011ef10(s32, void (*)());
void func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, void *);
s32 func_001205f0(void *, void *);
void *func_001559f0(s32, s32);
s32 func_001e9418(void);
void func_001ec7c0(s32);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 sceGsSyncPath(s32, s32);
void FlushCache(s32);
int sceSifBindRpc(void *, u32, s32);
int sceSifCallRpc(void *, u32, u32, void *, s32, void *, s32, void *, void *);
int printf(const char *, ...);

/* func_001e2a88, func_001e2d08, func_001e2f98, func_001e4070, func_001e4318, func_001e4578 are in src/shop/shop.c. */






/* func_001e5d78, func_001e5ee0, func_001e61c0, func_001e72a0, func_001e7ba8 are in src/list/list.c. */





void func_001e9670(void) {
#define pk (&D_00631620)
    Q4 *p;
    s32 i;
    Pkt620 *q;
    U128 *e;
    pk->dma.q = 0;
    pk->dma.w = 0x10000194;
    pk->gif[0] = 0x1000000000000002ULL;
    pk->gif[1] = 14;
    pk->gif[2] = 0x4000d;
    pk->gif[3] = 71;
    pk->gif[4] = 68;
    pk->gif[5] = 66;
    pk->gif[6] = 0x2024c000000080c8ULL;
    pk->gif[7] = 65;
    p = pk->v;
    for (i = 0; i < 100; i++) {
        p->a = i + 32;
        p->b = i + 96;
        p->c = i + 16;
        p->d = 96;
        p++;
        p->a = 0x7880;
        p->b = (i + 2098) << 4;
        p->c = 0xFFFFFF;
        p->d = 0;
        p++;
        p->a = i + 32;
        p->b = i + 96;
        p->c = i + 16;
        p->d = 96;
        p++;
        p->a = 0x8780;
        p->b = (i + 2098) << 4;
        p->c = 0xFFFFFF;
        p->d = 0;
        p++;
    }
    q = &D_00631620;
    e = &q->end;
    e->q = 0;
    e->w = 0x70000000;
    D_003DD308 = 0;
    D_003DD30C = 0;
    D_003DD310 = 4;
    D_003DD314 = 2;
    func_0011ef10(0xC350, (void (*)())func_001e9418);
}

/* func_001e9b98 is in src/vm/vm_find.nofill.c. */

s32 func_001ec7d0(s32 arg) {
    u32 i, j;
    func_001ec7c0(0);
    for (i = 0; i < 2048; i++) D_00633640[i] = 0;
    { u8 *p = (u8 *)D_0063D640; for (i = 0; i < 8192; i++) p[i] = 0; }
    { u8 *p = D_0063F640; for (i = 0; i < 256; i++) p[i] = 0; }
    for (;;) {
        if (sceSifBindRpc(&D_003E3C88, 17, 0) < 0) {
            printf(D_00490910);
            return -1;
        }
        if (D_003E3C88.server != 0) break;
        i = 0x10000; while (i--) ;
    }
    D_003E3CB0 = 0;
    for (j = 0; j < 1024; j++) {
        for (i = 0; i < 8; i++) D_00635640[j][i] = -1;
    }
    D_00633640[0] = (u32)D_0063D640;
    D_00633640[1] = arg;
    D_00633640[2] = (u32)D_0063F640;
    sceSifCallRpc(&D_003E3C88, 0, 0, D_00633640, 0x2000, D_00633640, 0x2000, 0, 0);
    return 0;
}

s32 func_001ecb08(s32 a, s32 b, s32 c) {
    Ent180 *p;
    s32 i;
    FlushCache(0);
    p = D_0063D640;
    if (b < 0 && c < 0) {
        for (i = 0; i < 24; i++, p++) {
            if (p->used && p->xc == a) return 1;
        }
    } else if (b < 0) {
        for (i = 0; i < 24; i++, p++) {
            if (p->used && p->xc == a && p->x4 == c) return 1;
        }
    } else if (c < 0) {
        for (i = 0; i < 24; i++, p++) {
            if (p->used && p->xc == a && p->x10 == b) return 1;
        }
    }
    for (i = 0; i < 24; i++, p++) {
        if (p->used && p->xc == a && p->x10 == b && p->x4 == c) return 1;
    }
    return 0;
}

s32 func_001ecd08(s32 a, s32 b, s32 c) {
    Ent72 *p;
    s32 i, n;
    FlushCache(0);
    p = D_0063EE40;
    if (a < 0 && b < 0 && c == 0) {
        n = 0;
        for (i = 0; i < 4; i++, p++) {
            if (p->used) n++;
        }
        return n;
    } else if (a < 0) {
        if (c == 0) {
            n = 0;
            for (i = 0; i < 4; i++, p++) {
                if (p->used && (p->b0 & 0x7f) == 1) n++;
            }
            return n;
        }
        for (i = 0; i < 4; i++, p++) {
            if (p->used && (p->b0 & 0x7f) == 1 && p->x10 == c) return 1;
        }
        return 0;
    }
    for (i = 0; i < 4; i++, p++) {
        if (p->used && p->b0 == 0 && p->x2 == a && p->x3 == b) return 1;
    }
    return 0;
}

void func_001ef950(void)
{
    u128 b[11];
    u128 a[11];
    u8 *p;

    p = func_001559f0(52, 12);
    func_001205f0(D_00490940, p);
    func_0011fbb0(16380, 1, 0, 0, 0, 16, 16, 64, p + 0x10000, a);
    FlushCache(0);
    func_00266f38(func_00266c08(2), a);
    sceGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 36, 0, 0, 256, 256, 2048, p, b);
    FlushCache(0);
    func_00266f38(func_00266c08(2), b);
    sceGsSyncPath(0, 0);
    func_0011fbb0(4096, 4, 44, 0, 0, 256, 256, 2048, p + 0x8000, b);
    FlushCache(0);
    func_00266f38(func_00266c08(2), b);
    sceGsSyncPath(0, 0);
}

#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003D.h"
#include "data/data_003E.h"
#include "data/data_0049.h"
#include "data/pieces/D_003E3C88.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
#include "data/pieces/D_003F7A68.h"
