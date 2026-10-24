/* The Gummi save block (docs/modules.md "Session 48"), 0x001b9b30-0x001bb438:
 * block 4 of the save image (func_00232cc0(4), 0xB040 bytes,
 * func_001ba1e0), signed "GUMI" version 0x101 and set up afresh by
 * func_001b9ec0 when the signature is missing (func_001b9b30, called by
 * every accessor).  Its layout as the accessors read it:
 *
 *   0x0008  the ship order (8 bytes) and 0x10 the current ship
 *           (func_001ba980, func_001baa20, func_001baaa8 / func_001baad0;
 *           bit 7 set: a preset ship, the low bits its number);
 *   0x0018  ten ships of 0xF70 bytes (GumiShip, func_001ba9d8; presets
 *           from D_00377648 / D_00377748, func_001b9f78 / func_001ba060 /
 *           func_001ba108, names func_001ba228);
 *   0x9A78  how many of each block are held (func_001ba9a8, func_001ba3f0,
 *           func_001ba2f8 / func_001ba358 add up to GumiBlock.max);
 *   0x9B38  two words (func_001bad78), 0x9B40 ten part values with their
 *           defaults (func_001b9cb0, func_001baaf0, func_001b9df0 /
 *           func_001b9e40), 0x9C00 bytes (func_001b9b78 / func_001b9bb0);
 *   0x9C20 / 0xA420  32 records of 64 bytes each, the second the best of the
 *           first (func_001bafb0 keeps the higher sum, func_001baf08:
 *           most likely the Gummi missions' records);
 *   0xAC20  one flag per world (func_001bb218, func_001bb2e0 sets it once
 *           the world's story byte func_001ba958 reaches 3; func_001bb370:
 *           all the worlds of D_004900A8).
 *
 * Between them: the Gummi Edit and World Map modes, two overlays run at
 * 0x00F20000 (func_001b9c60 loads and enters one, func_001b9c10 enters the
 * one loaded): func_001ba7e0 starts "gb.x" (Run Gumi Edit), func_001ba870
 * "wm.x" (Run WorldMap), func_001ba520 the pad block the overlay reads
 * (D_00621220: buttons, pressed / released edges and the two sticks from
 * D_00621308, func_001ba708 / func_001ba768 / func_001ba778).  func_001ba930
 * / func_001ba958 write and read a byte of the script variables
 * (src/vm/script_vm.c, offset 0x2f0 + i): func_001babe8 and func_001bade8
 * set them from the ship.
 *
 * Read from the code and the strings, not proved by a boot. */
#include "common.h"
#include "platform/thread.h"
#include "m2c.h"
#include "gummi/gummi.h"
#include "vm/script_vm.h"
#include "platform/math.h"
#include "data/types/text_001b0000_s12_s12w17.h"
#include "data/types/text_001a0000_h13_p.h"
#include "data/bss_0062.h"
#include "data/data_0037.h"
#include "data/data_0048.h"
#include "data/data_0049.h"
#include "data/pieces/D_004900A8.h"
#include "data/pieces/D_003773E0.h"

typedef struct { u8 sig[4]; s32 ver; } SaveHdr;
typedef struct { u8 p[68]; u8 b44; u8 p45[2]; u8 b47; } Rec9a8;
typedef struct { u8 ord[8]; s32 n; } Ord8;
typedef struct { u8 pad[0x9B40]; s32 v[10]; } BigAF0;
typedef struct { u8 pad[0xAC20]; u8 flags[1]; } SaveAC20;
typedef struct { u8 b[64]; } Blk64;
typedef struct { u8 pad[0x9c20]; Blk64 a; u8 pad2[0xa420 - 0x9c60]; Blk64 b; } SaveRow;

extern s32 D_00009B38;
extern s32 D_00009B3C;
extern s32 D_00009B40;
extern s32 D_00009B44;
extern s32 D_00009B48;
extern s32 D_00009B4C;
extern s32 D_00009B50;
extern s32 D_00009B54;
extern s32 D_00009B58;
extern s32 D_00009B5C;
extern s32 D_00009B60;
extern s32 D_00009C00;
extern s32 D_0000AC20;
extern u8 D_00F20000[];
extern s32 D_0037A128;
/* The two sticks' x and y (func_001ba778), read by func_001ba520. */
extern s32 D_00621308[][2];
#define D_00621308_S ((s32 *)D_00621308)
extern Lt2 D_00621220;
extern Lt2 D_002BCA00;
extern Lt D_002BCA70;
extern Lt D_002C5AD0;
extern GumiShip D_006202A0;

void *func_00232cc0(s32);
s32 func_001207f8(s32);
s32 func_001205f0(char *, void *);
double asin();
void func_0010fe80(void);
void func_0010fe90(void);
void func_00112fa0(void);
int puts(const char *);
void func_001c06f8(void);
void func_00236f18(void);
void func_001efaf0(void);
u8 *func_001efbb8(s32);
void func_001be670(s32);
void func_001be820(void *, u32);
void func_001bef98(char *, char *);
void func_001bb558(void);
void func_001bb580(void);
GumiBlock *func_001bb658(s32);
s32 func_001bb740(void);
s32 func_001be5c8(s32);
s32 func_001be5d0(s32);
s32 func_001bcd10(GumiShip *, GumiShip *);
void func_001b9b30(void);
void func_001b9c60(char *);
void func_001b9cb0(void);
void func_001b9ec0(void);
void func_001b9f78(s32);
void func_001ba108(GumiShip *, s32);
u8 *func_001ba228(s32);
s32 func_001ba458(s32);
void func_001ba520(void);
void func_001ba6f8(void);
void func_001ba7b8(void);
s32 func_001ba848(void);
f32 func_001ba850(void);
f32 func_001ba860(void);
void func_001ba910(s32);
void func_001ba930(s32, s8);
s8 func_001ba958(s32);
void *func_001ba980(void);
u8 *func_001ba9a8(void);
void func_001baa20(Ord8 *);
void func_001baaa8(s32);
s32 func_001baad0(void);
void func_001baaf0(BigAF0 *);
void func_001bab80(s32, u8 *);
s32 func_001baf08(s32 *);
s32 func_001baf70(s32, Blk64 *, Blk64 *);
s32 func_001bb260(s32);
s32 func_001bb2e0(s32);
u8 func_001ba3f0(s32);

void func_001b9b30(void) {
    void *temp_v0;

    temp_v0 = func_00232cc0(4);
    if ((M2C_FIELD(temp_v0, s32 *, 0) != 0x494D5547) || (M2C_FIELD(temp_v0, s32 *, 4) != 0x101)) {
        func_001b9ec0();
    }
}

u8 func_001b9b78(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_00009C00 + (arg0 + (s32)func_00232cc0(4)));
}

void func_001b9bb0(s32 arg0, s32 arg1) {
    *(s8 *)((s8 *)&D_00009C00 + (arg0 + (s32)func_00232cc0(4))) = arg1;
}

void func_001b9bf8(void) {
    asin();
}

s32 func_001b9c10(void) {
    if (func_001207f8(D_00621210) != 0) {
        return 0;
    }
    PlatFlushCache(0);
    PlatFlushCache(2);
    ((void (*)(void))D_00F20000)();
    return 4;
}

void func_001b9c60(char *a) {
    void (*fn)(void) = (void (*)(void))D_00F20000;
    D_00621210 = func_001205f0(a, fn);
    PlatFlushCache(0);
    PlatFlushCache(2);
    fn();
}

void func_001b9cb0(void) {
    s32 temp_v0;

    temp_v0 = (s32)func_00232cc0(4);
    if (*(M2C_UNK *)((s8 *)&D_00009B40 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B40 + temp_v0) = 0x4000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B44 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B44 + temp_v0) = 0x8000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B48 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B48 + temp_v0) = 0x400;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B4C + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B4C + temp_v0) = 0x2000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B50 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B50 + temp_v0) = 0x2000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B54 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B54 + temp_v0) = 0x2000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B58 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B58 + temp_v0) = 0x1000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B5C + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B5C + temp_v0) = 0x1000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B60 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B60 + temp_v0) = 0x1000;
    }
}

s32 func_001b9df0(s32 arg0) {
    s32 temp_s1;

    temp_s1 = (s32)func_00232cc0(4);
    func_001b9cb0();
    return *(M2C_UNK *)((s8 *)&D_00009B40 + ((arg0 * 4) + temp_s1));
}

void func_001b9e40(s32 arg0, s32 arg1) {
    *(M2C_UNK *)((s8 *)&D_00009B40 + ((arg0 * 4) + (s32)func_00232cc0(4))) = arg1;
}

s32 func_001b9e88(void) {
    s32 var_v0;

    var_v0 = 0;
    if (func_001baad0() & 0x80) {
        return var_v0;
    }
    var_v0 = ((s32 (*)(s32))func_001ba3f0)(0x31) > 0; /* read as s32 */
    return var_v0;
}

void func_001b9ec0(void) {
    SaveHdr *s;
    Rec9a8 *r;
    func_001bb580();
    s = func_00232cc0(4);
    func_001be820(s, 0xB040);
    s->ver = 257;
    s->sig[0] = 'G';
    s->sig[1] = 'U';
    s->sig[2] = 'M';
    s->sig[3] = 'I';
    func_001baaf0((BigAF0 *)s);
    func_001b9f78(0);
    r = (Rec9a8 *)func_001ba9a8();
    r->b44 = 1;
    r->b47 = 1;
    func_001baa20((Ord8 *)func_001ba980());
    func_001bab80(10, (u8 *)func_001ba9d8(0));
    func_001ba108(func_001ba9d8(0), 0);
}

/* func_001b9f78 (s11 w4): loop 2 reads the global struct directly (no p alias). */
void func_001b9f78(s32 k) {
    u8 *p;
    u8 *s;
    s32 i, n;
    u8 *c;
    func_001be820(&D_006202A0, 0xF70);
    p = (u8 *)&D_006202A0;
    n = D_00377648[k];
    s = D_00377748[k];
    for (i = 0; i < n; i++) *p++ = *s++;
    c = func_001ba9a8();
    for (i = 0; i < D_006202A0.n; i++) { if (D_006202A0.p[i].id) { s32 j = D_006202A0.p[i].id - 1; c[j]++; } }
}

void func_001ba060(GumiShip *ship, s32 k) {
    u8 *p = (u8 *)ship;
    u8 *d = p;
    u8 *s;
    u8 *t;
    s32 n, i;
    func_001be820(p, 3952);
    n = D_00377648[k];
    s = D_00377748[k];
    for (i = 0; i < n; i++) *d++ = *s++;
    t = func_001ba228(k + 71);
    for (i = 0; i < 32; i++) p[80 + i] = t[i];
}

void func_001ba108(GumiShip *ship, s32 k) {
    u8 *p = (u8 *)ship;
    u8 *d = (u8 *)&D_006202A0;
    u8 *s;
    u8 *t;
    s32 n, i;
    func_001be820(d, 3952);
    n = D_00377648[k];
    s = D_00377748[k];
    for (i = 0; i < n; i++) *d++ = *s++;
    func_001bcd10(ship, &D_006202A0);
    t = func_001ba228(k + 71);
    for (i = 0; i < 32; i++) p[80 + i] = t[i];
}

s32 func_001ba1e0(void) {
    return 0xB040;
}

u16 func_001ba1e8(s32 i) {
    return func_001bb658(i)->h14;
}

u16 func_001ba208(s32 i) {
    return func_001bb658(i)->h16;
}

u8 *func_001ba228(s32 i) {
    u8 *s;

    func_001bb558();
    s = func_001efbb8(func_001be5c8(i));
    func_001efaf0();
    return s;
}

u8 *func_001ba268(s32 i) {
    u8 *s;

    func_001bb558();
    s = func_001efbb8(func_001be5d0(i));
    func_001efaf0();
    return s;
}

void func_001ba2a8(s32 arg0, u8 *arg1) {
    s32 var_a1;
    u8 *temp_v0;
    u8 *var_a2;

    var_a2 = (u8 *)func_001ba9d8(arg0) + 0x50;
    var_a1 = 0;
    do {
        temp_v0 = arg1 + var_a1;
        var_a1 += 1;
        *var_a2 = *temp_v0;
        var_a2 += 1;
    } while (var_a1 < 0x20);
}

s32 func_001ba2f8(s32 a) {
    u8 *p = func_001ba9a8() + a;
    if (*p < func_001ba458(a)) {
        (*p)++;
        return 1;
    }
    return 0;
}

void func_001ba358(s32 arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_s2;
    u8 temp_s1;

    temp_s2 = func_001ba9a8() + arg0;
    temp_s1 = *temp_s2;
    if (func_001ba458(arg0) < (temp_s1 + arg1)) {
        var_v0 = func_001ba458(arg0);
    } else {
        var_v0 = *temp_s2 + arg1;
    }
    *temp_s2 = (u8) var_v0;
}

s32 func_001ba3d8(void) {
    return func_001bb740();
}

u8 func_001ba3f0(s32 i) {
    return func_001ba9a8()[i];
}

void func_001ba420(s32 i, s32 n) {
    func_001ba9a8()[i] = n;
}

s32 func_001ba458(s32 a) {
    if ((u32)(a - 71) < 48) return 1;
    return func_001bb658(a)->max;
}

Lt *func_001ba488(s32 i) {
    return (Lt *)((u8 *)&D_002C5AD0 + (i * 0x70));
}

void func_001ba4a8(void) {
    func_001ba520();
    D_002C5AD0 = D_00621220.l[0];
}

/* func_001ba520: one mask variable n for ~old then ~nw (set twice, so not
 * local-alloc'd: t = nw & n is not tied to it). */
void func_001ba520(void) {
    f32 v[4];
    Lt *l;
    s32 old, nw, t, n;
    if (D_003772D0 == 0) {
        D_00621220 = D_002BCA00;
        return;
    }
    (&D_00621220.l[0])[1] = D_002BCA70;
    l = &D_00621220.l[0];
    old = l->s.w4;
    nw = D_00621300;
    l->s.w4 = nw;
    n = ~old;
    t = nw & n;
    l->s.w8 = t;
    n = ~nw;
    l->s.w10 = t;
    l->s.wC = old & n;
    v[0] = (f32)D_00621308_S[0] * (1.0f / 256.0f);
    v[1] = (f32)D_00621308_S[1] * (1.0f / 256.0f);
    v[2] = 0.0f;
    v[3] = PlatSqrtf(v[0] * v[0] + v[1] * v[1]);
    l->s.a[0] = v[0];
    l->s.a[1] = v[1];
    l->s.a[2] = v[2];
    l->s.a[3] = v[3];
    l->s.an[0] = v[0] / v[3];
    l->s.an[1] = v[1] / v[3];
    v[0] = (f32)D_00621308_S[2] * (1.0f / 256.0f);
    v[1] = (f32)D_00621308_S[3] * (1.0f / 256.0f);
    v[2] = 0.0f;
    v[3] = PlatSqrtf(v[0] * v[0] + v[1] * v[1]);
    l->s.b[0] = v[0];
    l->s.b[1] = v[1];
    l->s.b[2] = v[2];
    l->s.b[3] = v[3];
    l->s.bn[0] = v[0] / v[3];
    l->s.bn[1] = v[1] / v[3];
}

void func_001ba6f8(void) {
    D_003772D0 = 0;
}

/* func_001ba708 stores the sticks through a volatile pointer (base plus
 * offsets, in this order); func_001ba778 and func_001ba520 use the plain
 * [][2] view. */
void func_001ba708(s32 arg0) {
    D_003772D0 = arg0;
    if (arg0 != 0) {
        volatile s32 *p;
        func_001be820(&D_00621220, 0x70);
        D_00621300 = 0;
        p = (volatile s32 *)D_00621308;
        p[3] = 0;
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        func_0010fe90();
        return;
    }
    func_0010fe80();
}

void func_001ba768(s32 arg0) {
    D_00621300 = arg0;
}

void func_001ba778(s32 i, s32 a, s32 b) {
    D_00621308[i][0] = a;
    D_00621308[i][1] = b;
}

void func_001ba798(void) {
    D_003772D0 = 0;
    func_001be670(0);
}

void func_001ba7b8(void) {
    func_00112fa0();
}

s32 func_001ba7d0(void) {
    return D_003772DC;
}

void func_001ba7e0(void) {
    D_003773EC = 1;
    D_003772DC = 1;
    func_001ba6f8();
    puts((char *)&D_0048FFF0);
    func_001b9c60((char *)&D_00490000);
    func_001ba910((s32)func_001ba7b8);
    D_003772D4 += 1;
}

s32 func_001ba848(void) {
    return 0;
}

f32 func_001ba850(void) {
    return 0.0f;
}

f32 func_001ba860(void) {
    return 0.0f;
}

void func_001ba870(void) {
    s32 *cnt;
    D_003773EC = 1;
    D_003773DC = (void *)func_001ba848;
    D_003773E0 = (void *)func_001ba850;
    D_003773E4 = (void *)func_001ba860;
    D_003772DC = 2;
    func_001c06f8();
    func_00236f18();
    func_001ba6f8();
    puts(D_00490008);
    func_001b9c60(D_00490018);
    cnt = &D_003772D8;
    (*cnt)++;
}

/* The function the World Map mode runs each frame (func_001ba7b8). */
s32 D_00621318 ALIGNED(8);

void func_001ba910(s32 arg0) {
    D_00621318 = arg0;
}

s32 func_001ba920(void) {
    return D_00621318;
}

void func_001ba930(s32 arg0, s8 arg1) {
    s32 sp[4];
    M2C_FIELD(sp, s8 *, 0x0) = arg1;
    func_001c0e80(arg0 + 0x2F0, 1, sp);
}

s8 func_001ba958(s32 arg0) {
    s32 sp[4];
    func_001c0da0(arg0 + 0x2F0, 1, sp);
    return M2C_FIELD(sp, M2C_UNK *, 0x0);
}

void *func_001ba980(void) {
    func_001b9b30();
    return (u8 *)func_00232cc0(4) + 8;
}

u8 *func_001ba9a8(void) {
    func_001b9b30();
    return (u8 *)func_00232cc0(4) + 0x9A78;
}

GumiShip *func_001ba9d8(s32 i) {
    func_001b9b30();
    return (GumiShip *)((u8 *)func_00232cc0(4) + (i * 0xF70) + 0x18);
}

void func_001baa20(Ord8 *o) {
    s32 i;
    u8 *p;
    o->n = 0;
    p = &o->ord[7];
    for (i = 7; i >= 0; i--) *p-- = i;
}

void func_001baa58(u8 *arg0) {
    u8 *temp_a2;
    s32 var_a1;
    u8 *temp_a0;
    u8 temp_v1;

    temp_a2 = func_001ba980();
    var_a1 = 0;
    do {
        temp_a0 = temp_a2 + var_a1;
        temp_v1 = arg0[var_a1];
        var_a1 += 1;
        *temp_a0 = temp_v1;
    } while (var_a1 < 8);
}

void func_001baaa8(s32 i) {
    ((Ord8 *)func_001ba980())->n = i;
}

s32 func_001baad0(void) {
    return ((Ord8 *)func_001ba980())->n;
}

void func_001baaf0(BigAF0 *b) {
    b->v[0] = 16384;
    b->v[1] = 0x8000;
    b->v[2] = 1024;
    b->v[3] = 8192;
    b->v[4] = 8192;
    b->v[5] = 8192;
    b->v[6] = 4096;
    b->v[7] = 4096;
    b->v[8] = 4096;
    b->v[9] = 0;
}

void func_001bab80(s32 n, u8 *p) {
    s32 i;
    for (i = 0; i < n; i++) {
        func_001be820(p, 3952);
        func_001bef98((char *)(p + 80), D_00490020);
        p += 3952;
    }
}

void func_001babe8(void) {
    u8 *h;

    h = func_001ba9a8();
    h[0x31] = h[0x31] + 1;
    func_001ba930(0, 4);
    func_001ba930(1, 4);
    func_001ba930(2, 4);
    func_001ba930(3, 4);
    func_001ba930(4, 4);
    func_001ba930(5, 4);
    func_001ba930(6, 4);
    func_001ba930(7, 4);
    func_001ba930(8, 4);
    func_001ba930(9, 4);
    func_001ba930(0xA, 3);
    func_001ba930(0xB, 2);
    func_001ba930(0xC, 4);
    func_001ba930(0xD, 4);
    func_001ba930(0xE, 4);
    func_001ba930(0xF, 0x1F);
    func_001ba930(0x10, 0x1F);
    func_001ba930(0x11, 0x1F);
    func_001ba930(0x12, 0x1F);
    func_001ba930(0x13, 0x1F);
    func_001ba930(0x14, 0x1F);
    func_001ba930(0x15, 0x1F);
    func_001ba930(0x16, 0x1F);
    func_001ba930(0x17, 0x1F);
    func_001ba930(0x18, 0x1F);
    func_001ba930(0x22, -1);
    func_001ba930(0x23, -1);
    func_001ba930(0x24, -1);
    func_001ba930(0x25, -1);
    func_001ba930(0x26, -1);
}

s32 func_001bad78(s32 arg0) {
    s32 temp_v0;

    temp_v0 = (s32)func_00232cc0(4);
    switch (arg0) {                                 /* irregular */
    case 0:
        return *(M2C_UNK *)((s8 *)&D_00009B38 + temp_v0);
    case 1:
        return *(M2C_UNK *)((s8 *)&D_00009B3C + temp_v0);
    default:
        return 0;
    }
}

void func_001bade8(void) {
    GumiShip *sv = func_001ba9d8(func_001baad0());
    s8 a, b;
    s32 i;
    for (i = 0; i < sv->n; i++) {
        switch (sv->p[i].id) {
        case 45: case 46: a |= 0x40; break;
        case 47: case 48: a |= 0x80; break;
        case 51: a |= 4; break;
        case 52: a |= 8; break;
        case 53: a |= 0x10; break;
        case 54: a |= 0x20; break;
        case 55: a |= 1; break;
        case 56: a |= 2; break;
        case 49: b |= 2; break;
        case 50: b |= 1; break;
        case 57: b |= 4; break;
        case 58: b |= 8; break;
        }
    }
    func_001ba930(28, b);
    func_001ba930(29, a);
}

s32 func_001baf08(s32 *arg0) {
    s32 *var_a0;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v1;

    var_a0 = arg0;
    var_a1 = 0;
    var_v1 = 7;
    do {
        temp_v0 = *var_a0;
        var_a0 += 1;
        var_v1 -= 1;
        var_a1 += temp_v0;
    } while (var_v1 >= 0);
    return var_a1;
}

s32 func_001baf38(s32 *arg0) {
    s32 *var_a0;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v1;

    var_a0 = arg0 + 2;
    var_a1 = 0;
    var_v1 = 5;
    do {
        temp_v0 = *var_a0;
        var_a0 += 1;
        var_v1 -= 1;
        var_a1 += temp_v0;
    } while (var_v1 >= 0);
    return var_a1;
}

s32 func_001baf70(s32 i, Blk64 *a, Blk64 *b) {
    s32 temp_s0;

    temp_s0 = func_001baf08((s32 *)a);
    return temp_s0 - func_001baf08((s32 *)b);
}

s32 func_001bafb0(s32 i, Blk64 *src) {
    SaveRow *r;
    func_001b9b30();
    r = (SaveRow *)(i * 64 + (u32)func_00232cc0(4));
    r->a = *src;
    if (func_001baf70(i, src, &r->b) > 0) {
        r->b = *src;
        return 1;
    }
    return 0;
}

Blk64 *func_001bb198(s32 i) {
    func_001b9b30();
    return (Blk64 *)((u8 *)func_00232cc0(4) + (i << 6) + 0x9C20);
}

Blk64 *func_001bb1d8(s32 i) {
    func_001b9b30();
    return (Blk64 *)((u8 *)func_00232cc0(4) + (i << 6) + 0xA420);
}

void func_001bb218(s32 arg0, s32 arg1) {
    func_001b9b30();
    *(s8 *)((s8 *)&D_0000AC20 + (arg0 + (s32)func_00232cc0(4))) = arg1;
}

s32 func_001bb260(s32 a) {
    switch (a) {
    case 3: return 0;
    case 4: return 1;
    case 11: return 2;
    case 5: return 3;
    case 8: return 4;
    case 9: return 6;
    case 10: return 5;
    case 13: return 7;
    case 15: return 8;
    case 16: return 9;
    }
    return 0;
}

s32 func_001bb2e0(s32 a) {
    SaveAC20 *s;
    func_001b9b30();
    s = func_00232cc0(4);
    if (s->flags[a] == 0 && func_001ba958(func_001bb260(a)) >= 3) s->flags[a] = 1;
    return s->flags[a];
}

s32 func_001bb370(void) {
    Str11 ids = D_004900A8;
    u8 *p;
    for (p = ids.c; *p; p++) {
        if (func_001bb2e0(*p) < 4) return 0;
    }
    return 1;
}

s32 func_001bb3f8(s32 w) {
    if ((func_001ba958(func_001bb260(w)) < 3) == 0) {
        return 1;
    }
    return 0;
}

void func_001bb428(s32 arg0) {
    D_0037A128 = arg0;
}

