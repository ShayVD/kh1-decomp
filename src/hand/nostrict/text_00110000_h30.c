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
#include "data/pieces/D_002C5968.h"
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
#include "data/pieces/D_002C5910.h"

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
#include "data/data_002C.h"
#include "data/data_0035.h"
#include "data/pieces/D_002C1378.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002C1368.h"
