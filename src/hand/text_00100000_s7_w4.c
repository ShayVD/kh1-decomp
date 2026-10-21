#include "common.h"

typedef struct { u64 x[20]; } Blk160;
typedef struct { s32 m[32][16]; s32 v[4]; } Blk810;
typedef struct { u8 kind[16]; u8 pad10[4]; u16 n0; u16 n1; } Setup;
typedef struct { s32 o0; u32 sz4; s32 o8; s32 pc; s32 o10; s32 p14; s32 o18; s32 p1c; s32 o20; u32 sz24; } Hdr;
#include "data/pieces/D_002A3F3C.h"
extern s32 D_002A3F20;
extern s32 D_002A3F24;
#include "data/pieces/D_0029B420.h"
s32 func_00108618(void);
void func_00100b18(Setup *);
void func_00100d18(void *, s32);
void func_00100d90(void *, s32);
void func_00100e08(void *, s32);
void func_00100e80(void *, s32);
void func_00100ef8(void *, s32);
void func_00100f70(Blk810 *);
void func_00101e70(void);
void func_00102978(void);
void func_0011ef10(s32, void (*)(void));
void func_00113768(void);
s32 func_00101048(void) {
    s32 i;
    Hdr *h;
    Blk160 *src;
    Blk810 *mt;
    Setup *s;
    u8 *tex;
    u8 *big;
    i = 0;
    func_00108618();
    h = ((Hdr *)D_002A3F3C);
    src = (Blk160 *)((u8 *)h + h->o0);
    D_002A3F20 = h->sz4 / sizeof(Blk160);
    for (; i < D_002A3F20; i++) {
        ((Blk160 *)&D_0029B420)[i] = src[i];
    }
    s = (Setup *)((u8 *)h + h->o8);
    tex = (u8 *)h + h->o10;
    big = (u8 *)h + h->o18;
    func_00100b18(s);
    for (i = 0; i < s->n0; i++) {
        func_00100d18(tex + i * 256, i + 0x3e00);
    }
    for (i = s->n0; i < s->n1; i += 4) {
        func_00100d90(tex + i * 256, i + 0x3e00);
    }
    for (i = 0; i < 16; i++) {
        if (s->kind[i] != 19) {
            if (s->kind[i] == 20) {
                func_00100e08(big + i * 0x10000, i * 256 + 0x2600);
            }
        } else {
            func_00100e80(big + i * 0x10000, i * 256 + 0x2600);
        }
    }
    func_00100ef8(big + 0x100000, 0);
    mt = (Blk810 *)((u8 *)h + h->o20);
    D_002A3F24 = h->sz24 / sizeof(Blk810);
    func_00100f70(mt);
    func_00101e70();
    func_00102978();
    func_0011ef10(0xc350, func_00113768);
    return 4;
}


typedef struct { u8 pad[0x29]; u8 x29; } S14c;
typedef struct { u8 pad[0xd0]; u8 xd0; } S6c;
typedef struct { u8 pad[0x6c]; S6c *x6c; u8 pad70[0xdc]; S14c *x14c; u8 pad150[0x14]; s32 x164; } Obj164;
typedef struct { s16 x0; u8 pad[18]; } E20;
#include "data/types/text_00100000_s7_w4.h"
extern E20 *D_004F7810; /* src/data/bss_004F.c: E7810 *D_004F7810 */
extern Pair8 D_002E27C0[4];
extern f32 D_002E27CC, D_002E27D0;
void func_00126238(Obj164 *, s32, s32 *);
f32 func_0012ed88(Obj164 *, s32 *, f32 *, s32);
u8 func_001269d8(Obj164 *o, s32 *a1, s32 a2) {
    s32 buf[66];
    f32 tmp[4];
    s32 i;
    u32 j;
    f32 d;
    for (i = 65; i >= 0; i--) buf[i] = 0;
    if (o->x14c->x29 >= o->x6c->xd0) buf[8] = 1;
    if (*a1 == 0) {
        func_00126238(o, a2, buf);
    } else {
        d = func_0012ed88(o, a1, tmp, a2);
        if (d < D_002E27D0 && D_002E27CC < d) buf[14] = 1;
        else func_00126238(o, a2, buf);
    }
    for (i = 0; i < 66; i++) {
        for (j = 0; j < 4; j++) {
            if (buf[D_002E27C0[j].a] > 0 && D_004F7810[D_002E27C0[j].b].x0 != o->x164) return D_002E27C0[j].b;
        }
    }
    if (o->x14c->x29 < 2) goto r25;
    if (o->x164 == D_004F7810[26].x0) {
        if (buf[14] > 0) return 25;
    }
    if (o->x164 != D_004F7810[24].x0) return 24;
r25:
    return 25;
}


typedef struct { u8 pad[0x4c]; u16 f4c; } Info;
typedef struct { u8 pad[0x130]; Info *f130; } Ent;
typedef struct { u8 pad[0x30]; s32 f30; } Q30;
typedef struct { s32 f0; u8 pad[8]; Q30 *fc; u8 pad10[0xc]; } T28;
typedef struct { u8 b74; u8 pad[0x73]; } E74;
typedef struct { E74 e[1]; } Sv;
#include "data/pieces/D_002E31A8.h"
extern Sv *D_00304BE8;
extern T28 D_00525368[]; /* src/data/bss_0052.c: M2C_UNK D_00525368 */
extern s32 func_00141288(Ent *, s32, s32);

s32 func_00133000(Ent *o, s32 i) {
    T28 *t = &D_00525368[i];
    Q30 *q;
    if ((D_002E31A8 >> 2) & 1) return 0;
    if (t->f0 == 0) goto r0;
    if (!(q = t->fc)) return 0;
    if (*(s32 *)((u8 *)D_00304BE8 + 0x874) & 1) goto r0;
    if ((D_00304BE8->e[o->f130->f4c + 1].b74 >> i) & 1) goto call;
r0:
    return 0;
call:
    return func_00141288(o, q->f30, i);
}


typedef struct {
    u8 pad0[0x180];
    s32 sp;
    s32 stk[105];
    s64 f328;
} VM2;
s32 func_0011e368(s32, s32);

s32 func_001e8da0(VM2 *vm) { s32 r = func_0011e368(vm->stk[vm->sp - 1], vm->stk[vm->sp]); if (r != 0) return r = 4; return 2; }
#include "data/data_002A.h"
#include "data/pieces/D_002E27CC.h"
#include "data/pieces/D_002E27D0.h"
#include "data/pieces/D_002E27C0.h"
