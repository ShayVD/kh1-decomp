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


typedef struct {
    u8 pad0[4];
    u32 x4;
    s32 x8;
    u8 pad0c[4];
    f32 x10;
    f32 x14;
    u8 pad18[0x4c - 0x18];
    u16 x4c;
    u8 pad4e[0x54 - 0x4e];
    s8 x54;
    s8 x55;
    s8 x56;
    s8 x57;
    u8 x58;
    u8 x59;
} C01Def;
typedef struct { u8 pad[8]; f32 x8; f32 xc; } C01Pt;
typedef struct { u8 pad[4]; u8 x4; u8 pad5; u8 x6; u8 pad7[5]; f32 xc; C01Pt *x10; } C01Ent4;
typedef struct { u8 pad[0xe0]; s32 xe0; } C01S148;
typedef struct { u8 pad[0xf]; s8 xf; u8 pad10[0xc]; s32 x1c; u8 pad20[4]; s32 x24; } C01S14c;
typedef struct { u8 pad[0x3a]; u16 x3a; u8 pad3c[0x74 - 0x3c]; } C01Tbl74;
typedef struct { u8 pad[0xbd]; u8 xbd; } C01Fx;
typedef struct {
    u32 x0;
    union { s32 id; struct { u16 lo; u8 b6; u8 b7; } s; } u4;
    s32 x8;
    s32 xc;
    u8 pad010[0x40 - 0x10];
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4c;
    u8 pad050[0x60 - 0x50];
    f32 x60;
    s32 x64;
    u8 pad068[0x6c - 0x68];
    void *x6c;
    s32 x70;
    u8 pad074[0x7c - 0x74];
    s32 x7c;
    s32 x80;
    u8 pad084[0x8c - 0x84];
    s32 x8c;
    u8 pad090[0x98 - 0x90];
    s32 x98;
    s32 x9c;
    f32 xa0;
    f32 xa4;
    f32 xa8;
    f32 xac;
    s32 xb0;
    u8 pad0b4[0x130 - 0xb4];
    C01Def *x130;
    C01Ent4 *x134;
    u8 pad138[0x13c - 0x138];
    s32 x13c;
    s32 x140;
    s32 x144;
    C01S148 *x148;
    C01S14c *x14c;
    u8 pad150[0x160 - 0x150];
    s32 x160;
    s32 x164;
    u8 pad168[0x1cc - 0x168];
    s32 x1cc;
    s32 x1d0;
    u8 pad1d4[0x1d8 - 0x1d4];
    s32 x1d8;
    u8 pad1dc[0x2c0 - 0x1dc];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x350 - 0x2c8];
    s32 x350;
    s32 x354;
    s32 x358;
    s32 x35c;
    u8 pad360[0x370 - 0x360];
    union { u64 x; u8 c[8]; u16 h[4]; struct { u64 lo : 40; u64 f40 : 2; u64 m42 : 7; u64 b49 : 1; u64 hi : 14; } b; } u370;
    s32 x378;
    u8 pad37c[0x38c - 0x37c];
    s32 x38c;
    s32 x390;
    u8 pad394[0x398 - 0x394];
    s32 x398;
    u8 x39c;
    u8 x39d;
    u8 x39e;
    u8 pad39f[0x3a0 - 0x39f];
    s32 x3a0;
    s32 x3a4;
    s32 x3a8;
    s32 x3ac;
    u8 pad3b0[0x3e0 - 0x3b0];
    s32 x3e0;
    s32 x3e4;
    s16 x3e8;
    s16 x3ea;
    s32 x3ec;
    u8 pad3f0[0x400 - 0x3f0];
    s32 x400;
    s32 x404;
    s32 x408;
    u8 pad40c[0x410 - 0x40c];
    f32 x410;
    f32 x414;
    u8 pad418[0x440 - 0x418];
    s32 x440;
    u8 pad444[0x448 - 0x444];
    s32 x448;
    u8 pad44c[0x488 - 0x44c];
    s32 x488;
    u8 pad48c[0x4a0 - 0x48c];
    s32 x4a0;
    s32 x4a4;
    s32 x4a8;
    u8 pad4ac[0x4b0 - 0x4ac];
} C01Act;

extern s32 D_00350D7C;
extern s32 D_00350D80;
#define D_00304BE8 (*(C01Tbl74 * *)&D_00304BE8)
extern u8 D_00304C70[];
extern u8 D_00FE0000[];

s32 func_00131f78(s32);
C01Def *func_001320a8(s32);
s32 func_0015aac0(C01Def *);
C01Act *func_00123810(void);
void func_00123030(C01Act *, s32, s32);
C01Fx *func_00141a40(void);
void func_001323a0(C01Act *, s32);
void func_00123d48(C01Act *);
void func_001358b8(C01Act *, s32);
void func_001238c0(C01Act *, f32, f32);
void func_00123b40(C01Act *, void *);
void func_00124060(C01Act *, void *);
void func_00131438(C01Act *);
void func_00130340(C01Act *, s32, f32);
void func_001371f0(C01Act *);
void func_00138400(C01Act *);
void func_0012ba98(s32);

C01Act *func_00124218(u32 id) {
    u8 buf[16];
    C01Def *d;
    C01Act *a;
    C01Ent4 *e;
    u32 f;

    if ((id >> 16 & 0xff) == 11) {
        id = func_00131f78(id & 0xffff);
        if (id == -1) return 0;
    }
    d = func_001320a8(id);
    if (D_00350D7C > 0 && D_00350D7C < D_00350D80 + d->x59) return 0;
    if (d->x54 == 16 && func_0015aac0(d)) return 0;
    D_00350D80 += d->x59;
    a = func_00123810();
    f = a->x0;
    a->u4.id = id;
    a->x130 = d;
    a->x0 = f | 0x8000;
    if (!(d->x4 & 0x100)) a->x0 = f | 0x8003;
    if (d->x4c < 10 && (D_00304BE8[d->x4c].x3a & 1)) a->x0 |= 0x4000;
    a->u370.x = (a->u370.x & ~(3ULL << 40)) | ((u64)(d->x4 >> 3 & 3) << 40);
    if (a->x130->x4 & 0x80) a->u370.x |= 1ULL << 47;
    a->x144 = 0;
    a->x140 = 0;
    a->x6c = D_00304C70;
    a->x13c = 0;
    a->x4a8 = 0;
    a->x488 = 0;
    a->xb0 = 0;
    a->x440 = 0;
    a->x448 = 0;
    a->x148 = 0;
    a->x14c = 0;
    a->x398 = 0;
    a->x8c = 0;
    a->x98 = 0;
    a->x4a0 = 0;
    a->x378 = 0;
    a->x70 = 0;
    a->x160 = 0;
    a->x1d8 = 0;
    a->x1cc = 0;
    func_00123030(a, 0, 0);
    a->x7c = 0;
/*P*/
    a->u370.c[3] = 0x80;
    a->u370.c[2] = 0x80;
    a->u370.c[1] = 0x80;
    a->u370.c[0] = 0x80;
    a->x3ea = 82;
    a->x80 = 0;
    a->x8 = 0;
    a->xc = 0;
    a->x3ec = 0;
    a->x3e0 = 0;
    a->x3e8 = 0;
    a->x400 = 0;
    a->x408 = 0;
    a->x3e4 = 0;
    a->x404 = 0;
    a->x134 = 0;
    a->x60 = 1.0f;
    a->x64 = 0;
    a->xac = 1.0f;
    a->xa8 = 1.0f;
    a->xa4 = 1.0f;
    a->xa0 = 1.0f;
    a->x4a4 = 0;
    a->x38c = 0;
    a->x390 = 0;
    a->x39c = 0;
    a->x39d = 0;
    a->x39e = 0;
    a->x3a0 = 0;
    a->u370.x &= ~(3ULL << 37);
/*Q*/
    switch (a->u4.s.b6) {
    case 3:
        a->u370.x |= 1ULL << 42;
        a->u370.x = (a->u370.x & ~(3ULL << 37)) | (2ULL << 37);
        a->x6c = func_00141a40();
        break;
    case 5:
    case 10:
        if (a->x130->x4 & 0x400) a->x39d |= 1;
        if (a->x130->x4 & 0x800) a->x39d |= 2;
        break;
    case 7: {
        C01Fx *fx = func_00141a40();
        a->x6c = fx;
        fx->xbd = 2;
        break;
    }
    }
    if (!d->x8) d->x8 = (s32)D_00FE0000 + (d->x55 << 18);
    func_001323a0(a, d->x8);
    func_00123d48(a);
    if (a->u4.s.b6 == 2) func_001358b8(a, 12);
    func_00123f28((Obj123 *)a);
    if (a->x14c) {
        a->x14c->xf = -1;
        a->x14c->x1c = 0;
        a->x14c->x24 = -1;
    }
    if (a->x148) a->x148->xe0 = 0;
    e = a->x134;
    if (!e || e->xc == 0.0f) {
        func_001238c0(a, d->x14, d->x10);
        e = a->x134;
        if (d->x4 & 0x20) { a->u370.x |= 1ULL << 49; a->u370.x |= 3ULL << 40; }
    }
    a->x3a4 = 0;
    a->x3a8 = 0;
    a->x3ac = 0;
    if (e && e->x6) {
        a->u370.x &= ~(1ULL << 47);
        if (!((s32)(a->u370.x >> 37) & 3)) a->u370.x |= 3ULL << 37;
    }
    if (e && e->x4) {
        a->x2c4 = e->x10->x8;
        a->x2c0 = e->x10->xc;
    } else {
        a->x2c0 = a->x410;
        a->x2c4 = a->x414 * 0.5f;
    }
    a->x9c = 0;
    a->x4c = 1.0f;
    a->x48 = 1.0f;
    a->x44 = 1.0f;
    a->x40 = 1.0f;
    func_00123b40(a, buf);
    a->x350 = 128;
    a->x354 = 128;
    a->x358 = 128;
    a->x35c = 128;
    func_00124060(a, buf);
    if (a->x1d0) {
        func_00131438(a);
        a->x164 = d->x57;
        func_00130340(a, d->x57, 0.0f);
    }
    func_001371f0(a);
    func_00138400(a);
    if ((s32)(a->u370.x >> 48) & 1) func_0012ba98(a->x144);
    a->x0 &= ~0x400;
    return a;
}
#undef D_00304BE8
#include "data/data_002C.h"
#include "data/data_0035.h"
#include "data/pieces/D_002C1378.h"
