#include "common.h"
typedef int u128 __attribute__((mode(TI)));
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
typedef struct { s32 off, size; } Chunk;
typedef struct { u8 pad[16]; Chunk c[2]; } SndHdr;
extern s32 D_002C1368[];
extern void (*D_004E3430)(void);
s32 func_001ed128(s32, s32);
void func_001ed460(s32, void *, s32);
void func_001ed658(s32, void *, s32);
void *func_0011ef10(s32, void *);
s32 func_0011cba0(void);
typedef f32 V4[4] __attribute__((aligned(16)));
extern V4 D_004E3A20;
extern V4 D_004E3A30;
typedef struct { u32 b0 : 1; u32 rest : 31; } Bits5958;
extern Bits5958 D_002C5958;
extern s32 D_004E3438, D_004E343C, D_004E3440;
extern s32 D_002C1378[];
extern s32 D_004E3448;
void func_0011c7c0(s32, s32, s32);
void func_0011c7a8(s32, s32, s32, s32, s32, s32);
int sprintf(char *, const char *, ...);
char *strcat(char *, const char *);
typedef struct TNode { u16 flags; u16 mask; s32 key; struct TNode *next; s32 (*fn)(struct TNode *); } TNode;
typedef struct { u16 size; u16 count; u8 *base; TNode *head; TNode *cur; } TPool;
TNode *func_0011f058(TPool *, TNode *);
typedef struct {
    u16 active;
    u8 x2;
    u8 x3;
    u32 cur;
    u32 press;
    u32 release;
    u32 rep;
    u32 rep2;
    s32 x18;
    s32 t1;
    s32 t2;
    u8 pad24[12];
    V4 a[2];
    V4 b[2];
} PadState;
extern s32 D_002C5C24, D_002C5C28;
typedef struct { u32 b0 : 1; u32 b1 : 1; u32 r : 30; } Flags5968;
extern volatile Flags5968 D_002C5968;
extern u8 D_002C5C38[];
s32 sceCdDiskReady(s32);
s32 sceCdRead(u32, u32, void *, void *);
s32 func_00269fd0(s32);
s32 func_0026aaa0(void);
typedef struct {
    u32 b0 : 1;
    u32 comp : 1;
    u32 r : 30;
    u8 pad4[32];
    u32 lsn;
    u32 size;
    u8 *buf;
    u32 result;
} CdReq;
void FlushCache(s32);
typedef struct {
    u8 pad0[16];
    char name[40];
    u8 *buf;
    void (*cb)(u32, s32, u8 *);
    s32 wait;
    s32 user;
    CdReq *req;
} LoadTask;
s32 func_00120678(LoadTask *);
void func_002672f8(f32 *, V4 *, f32 *);
extern f32 D_002BBDFC;
void func_002675a8(f32 *, f32 *);
extern s32 D_002C5910[4][4];
typedef struct { u8 pad0[12]; s32 xC; u8 pad10[60]; u16 x4C; u8 pad4e[6]; s8 kind; u8 pad55[4]; u8 x59; } Info123;
typedef union {
    u64 v;
    struct { u32 lo0; u32 x0 : 1; u32 b33 : 1; u32 x2 : 14; u32 b48 : 1; u32 x17 : 5; u32 b54 : 1; u32 x23 : 9; } b;
    struct { u64 lo : 33; u64 b33 : 1; u64 m : 14; u64 b48 : 1; u64 m2 : 5; u64 b54 : 1; u64 hi : 9; } c;
} ObjFlags;
typedef struct {
    u32 x0;
    u8 pad4[300];
    Info123 *info;
    u8 pad134[4];
    s32 x138;
    u8 pad13c[8];
    s32 x144;
    u8 pad148[552];
    ObjFlags fl;
    u8 pad378[40];
    s32 x3a0;
} Obj123;
extern Obj123 *D_002E26A0[];


void func_0011f548(PadState *p, u32 b) {
    u32 old = p->cur;
    u32 x, pr;
    p->rep2 = 0;
    p->rep = 0;
    p->release = 0;
    p->press = 0;
    p->cur = b;
    if (p->active == 0) return;
    pr = (old ^ b) & b;
    p->release = (old ^ b) & ~b;
    p->press = pr;
    if (pr) {
        s32 t = D_002C5C24;
        p->t2 = t;
        p->t1 = t;
        p->rep2 = pr;
        p->rep = pr;
        return;
    }
    if (b == 0) return;
    p->t1 = p->t1 - D_002BBDFC;
    p->t2 = p->t2 - D_002BBDFC;
    if (p->t1 <= 0.0f) {
        s32 t = D_002C5C28;
        p->rep = b;
        p->t1 = t;
    }
    if (p->t2 <= 0.0f) {
        p->rep2 = b;
        p->t2 = 0;
    }
}

void func_00170400(Obj123 *);
s32 func_00132008(Obj123 *);
s32 func_0012b888(s32);
void func_0012ba30(s32, Obj123 **, s32);

void func_00123f28(Obj123 *o) {
    Info123 *info = o->info;
    s8 k = info->kind;
    if (k >= 0) {
        switch (k) {
        case 1:
            func_00170400(o);
            break;
        case 6:
            o->x3a0 = func_00132008(o);
            break;
        case 2:
        case 5:
            o->fl.c.b48 = 1;
            break;
        }
    } else {
        o->x138 = info->xC;
        o->fl.c.b48 = 1;
    }
    if (o->fl.b.b48) {
        if (o->x138 == 0) {
            o->fl.c.b48 = 0;
            return;
        }
        o->x144 = func_0012b888(o->x138);
        func_0012ba30(o->x144, &o, 4);
    }
}

typedef struct { u8 pad0[8]; u32 lo : 16; u32 b16 : 1; u32 hi : 15; u8 padc[104]; } Ent116;
typedef struct { u8 pad0[48]; Ent116 e[10]; } Tbl4BE8;
extern Tbl4BE8 *D_00304BE8;

void func_00124920(void) {
    s32 i;
    Obj123 *o;
    for (i = 0; i < 10; i++) D_00304BE8->e[i].b16 = 0;
    for (i = 0; i < 3; i++) {
        o = D_002E26A0[i];
        if (o && (o->x0 & 0x4000)) D_00304BE8->e[o->info->x4C].b16 = 1;
    }
}
