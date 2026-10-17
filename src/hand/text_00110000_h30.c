#include "common.h"
typedef struct { s32 id, x4, x8, handle, x10; u8 active, x15, kind, x17; } SndSlot;
typedef struct { s32 x0, x4, x8; } Slot12;
typedef struct { s32 a, b; } Pair;
extern s32 D_004E344C;
extern SndSlot *D_004E3450;
extern Slot12 *D_004E3454;
extern SndSlot D_004E3458[];
extern Slot12 D_004E3818[];
extern Pair D_004E39F8[];
void *func_001559f0(s32, s32);

void func_0011c898(s32 a0) {
    s32 i;
    SndSlot *e;
    Slot12 *p;
    if (a0 == 0) {
        D_004E3450 = D_004E3458;
        D_004E3454 = D_004E3818;
        D_004E344C = 40;
    } else {
        D_004E3450 = func_001559f0(16, 1);
        D_004E3454 = func_001559f0(17, 1);
        D_004E344C = 128;
    }
    e = D_004E3450;
    p = D_004E3454;
    for (i = 0; i < D_004E344C; i++, e++, p++) {
        e->active = 0;
        p->x0 = 0;
        p->x4 = 0;
        p->x8 = 0;
    }
    for (i = 0; i < 4; i++) {
        D_004E39F8[i].a = 0;
        D_004E39F8[i].b = 0;
    }
}

typedef struct { s32 off, size; } Chunk;
typedef struct { u8 pad[16]; Chunk c[2]; } SndHdr;
extern s32 D_002C1368[];
extern void (*D_004E3430)(void);
void func_001ed128(s32, s32);
void func_001ed460(s32, void *, s32);
void func_001ed658(s32, void *, s32);
void func_0011ef10(s32, s32 (*)(void));
s32 func_0011cba0(void);

void func_0011cbe0(s32 a0, SndHdr *a1, s32 a2, void (*a3)(void)) {
    Chunk *c = &a1->c[0];
    s32 off0 = c->off, sz0 = c->size;
    s32 off1, sz1;
    u8 *p0, *p1;
    c = &a1->c[1];
    off1 = c->off; sz1 = c->size;
    D_004E3430 = a3;
    p0 = (u8 *)a1 + off0;
    if (((s32 *)(p1 = (u8 *)a1 + off1))[1] > 0x7547f) {
        func_001ed128(0, 0);
        func_001ed128(1, 0);
        func_001ed128(0, 1);
        func_001ed128(1, 1);
        D_002C1368[1] = D_002C1368[0] = -2;
        if (a0 == 1) {
            a0 = 0;
            goto skip;
        }
    }
    D_002C1368[a0] = a2;
    func_001ed128(0, a0);
    func_001ed128(1, a0);
skip:
    func_001ed460(a0, p0, sz0);
    func_001ed658(a0, p1, sz1);
    func_0011ef10(10000, func_0011cba0);
}
