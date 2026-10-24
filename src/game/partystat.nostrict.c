/* The party members' stats: HP / MP changes clamped to the member's maximum
 * (func_00141468, func_00141540; the empty record D_00304C70), and a
 * member's stats rebuilt from the save data D_00304BE8 with its equipment
 * and abilities (func_00141b10). Flag mode: nostrict (the other modes are in
 * the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_003044E0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_00304C70.h"
#include "data/types/nostrict_text_00130000_h55.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_0037A378.h"
#include "vm/script_vm.h"
#include "data/pieces/D_0035C710.h"
#include "data/types/nostrict_text_00130000_b03_p3.h"
#include "data/pieces/D_00304BE8.h"

/* func_00141218 (from hand/nostrict/text_00130000_s6_06.c). */
typedef struct { u8 pad[0x38]; s16 x38; } W606T12c8;
typedef struct { u8 pad[0x40]; s32 x40; s32 x44; s32 x48; u8 pad4c[0xbe - 0x4c]; s16 xbe; u8 padc0[8]; W606T12c8 *xc8; } W606T12s;
typedef struct { u8 pad[0x6c]; W606T12s *x6c; } W606T12o;
s32 func_00141468();
s32 func_00141540();
#define func_00141468 ((void (*)(W606T12o *o, s32 a)) func_00141468)
#define func_00141540 ((s32 (*)(W606T12o *o, s32 a)) func_00141540)
void func_00141218(W606T12o *o) {
    s32 n;
    if (o == 0) return;
    func_00141468(o, o->x6c->x40);
    n = o->x6c->x48;
    if (o->x6c->x44 < n) {
        func_00141540(o, n);
        o->x6c->xbe = 0;
        if (o->x6c->xc8) o->x6c->xc8->x38 = 0;
    }
}
#undef func_00141468
#undef func_00141540

/* func_00141348 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { u8 pad[0x3C]; s32 w3c; s32 w40; } S6C;
typedef union {
    u64 x;
    struct { u64 lo:48; u64 b48:1; u64 hi:15; } d;
    struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b;
} B370;
typedef struct {
    u8 pad0[6];
    u8 b6;
    u8 pad7[0x6C - 7];
    S6C *p6c;
    u8 pad70[0x144 - 0x70];
    s32 w144;
    u8 pad148[0x370 - 0x148];
    B370 f370;
} P141;
typedef struct { P141 *p; s32 x4; } A141;
typedef struct { void *p; s32 n; } Pair;
typedef struct { s32 ok; s32 a; s32 b; } R141;
s32 func_0013c968(s32, s32);
void func_0012bce0(s32, s32, s32, Pair *, s32);
s32 func_00141348(A141 *a, R141 *r) {
    Pair pr[2];
    if (func_0013c968(10, 0) > 0 && a->p->b6 == 3 && a->p->f370.b.kind != 1) {
        r->ok = 1;
        r->a = a->p->p6c->w3c;
        r->b = a->p->p6c->w40;
        if ((s32)(a->p->f370.x >> 48) & 1) {
            if (a->p->w144) {
                pr[0].p = &a->x4;
                pr[0].n = 4;
                pr[1].p = &r;
                pr[1].n = 4;
                func_0012bce0(a->p->w144, 3, 2, pr, 0);
            }
        }
    } else {
        r->ok = 0;
    }
    return r->ok;
}

/* func_00141448 (from hand/nostrict/text_00140000_h33.c). */
/* func_00141468 and func_00141540 only match with func_00141448 defined
 * above them. */
s32 func_00141448(s32 a, s32 b, s32 max) {
    s32 v = a + b;
    if (max < v) {
        v = max;
    } else if (v < 0) {
        v = 0;
    }
    return v;
}

/* func_00141468 (from hand/nostrict/text_00140000_h33.c). */
typedef St6C_304c70 St6C;
typedef struct { u8 pad[0x4C]; u16 h4c; } S130b;
typedef struct { u8 pad[0x6C]; St6C *p6c; u8 pad70[0x18]; u32 w88; u8 pad8c[0x130 - 0x8C]; S130b *p130; } O1468;
/* func_00141468 and func_00141540 only match with func_00141448 defined
 * above them. */
s32 func_00141468(O1468 *o, s32 x) {
    St6C *s = o->p6c;
    s32 v;
    if (s == 0 || s == &D_00304C70) return 0;
    v = func_00141448(s->w3c, x, s->w40);
    if ((o->w88 & 0x20) && !func_0013c968(9, o->p130->h4c)) {
        v = s->w3c + (s32)((v - s->w3c) * (*(Cfg_308cdc **)&D_00308CDC)->f88);
    }
    s->w3c = v;
    s->flags &= ~4;
    if (s->pc8) s->pc8->b1 = v;
    return v;
}

/* func_00141540 (from hand/nostrict/text_00140000_h33.c). */
typedef St6C_304c70 St6Cb;
/* func_00141468 and func_00141540 only match with func_00141448 defined
 * above them. */
s32 func_00141540(O1468 *o, s32 x) {
    St6Cb *s = (St6Cb *)o->p6c;
    s32 v;
    if (s == 0 || s == &D_00304C70) return 0;
    v = func_00141448(s->x44, x, s->w48);
    if ((o->w88 & 0x20) && !func_0013c968(9, o->p130->h4c)) {
        v = s->x44 + (s32)((v - s->x44) * (*(Cfg_308cdc **)&D_00308CDC)->f88);
    }
    s->x44 = v;
    if (s->pc8) s->pc8->b3 = v;
    return v;
}

/* func_00141608 (from hand/nostrict/text_00140000_s7_w26.c). */
typedef St6C_304c70 T16s;
typedef struct { u8 pad[0x4c]; u16 x4c; } T16i;
typedef struct { u8 pad[0x6c]; T16s *x6c; u8 pad70[0x130 - 0x70]; T16i *info; } T16o;
extern u32 D_002C5958;
#define func_00141540 ((s32 (*)(T16o *o, s32 a)) func_00141540)
/* func_00141608: matches in hand/nostrict and hand. The three return-xbe tests as one || chain (one shared return label): cse then keeps the x4c reload for the index and gcse turns it into a copy of the first load (move a0,v1), with no folding of m[0]. */
s32 func_00141608(T16o *o, s32 n) {
    T16s *s = o->x6c;
    u16 id;
    s32 v, max;
    s32 t;
    if (s == 0 || s == &D_00304C70) return 0;
    if (((D_002C5958 >> 11) & 1) || o->info->x4c >= 10 || (o->info->x4c == 0 && D_00304BE8->m[o->info->x4c].bits == 0)) return s->xbe;
    v = s->xbe + n;
    max = s->w48 * 30;
    if (v < 0) {
        if (s->x44 > 0) {
            v += s->x44 * 30;
            func_00141540(o, -1);
        } else {
            v = 0;
        }
    } else if (v > max) {
        v = max;
    }
    s->xbe = v;
    if (s->pc8) s->pc8->x38 = v;
    return v;
}
#undef func_00141540

/* func_001417a0 (from hand/nostrict/text_00140000_h33.c). */
typedef FVec4 V4f;
extern f32 D_00304D54;
void func_002675a8(V4f *, V4f *);
void func_002458a0(V4f *, s32);
void func_0013c548(s32);
void D_00F20000(s32, s32);
typedef struct { u8 pad[0x6C]; St6C *p6c; } Act_417a0;
extern Act_417a0 *D_002E26A0_417a0[3] __asm__("D_002E26A0");
#define D_002E26A0 D_002E26A0_417a0
void func_001417a0(V4f *p, s32 n) {
    V4f t;
    if (D_002E26A0[0] == 0 || D_002E26A0[0]->p6c->w3c > 0) {
        func_002675a8(&t, p);
        t.w = 1.0f;
        n = n * D_00304D54 + 0.5f;
        func_002458a0(&t, n);
        func_0013c548(n);
        if (((*(u32 *)&D_00304B78) & 0xF) == 9) {
            D_00F20000(5, n);
        }
    }
}
#undef D_002E26A0

/* func_001418b8 (from hand/nostrict/text_00130000_h55.c). */
typedef struct {
    s32 x0;
    f32 x4, x8;
    u8 pad0c[4];
    f32 x10, x14, x18, x1c, x20, x24, x28, x2c, x30, x34, x38;
    s32 x3c, x40, x44, x48, x4c, x50, x54;
    f32 x58;
    s32 x5c;
    f32 x60, x64;
    s32 x68, x6c, x70, x74;
    f32 x78[16];
    s32 xb8;
    u8 xbc, xbd;
    s16 xbe, xc0, xc2;
    f32 xc4;
    s32 xc8;
    f32 xcc;
    u8 xd0, xd1;
    s16 xd2;
    f32 xd4;
    s32 xd8;
    f32 xdc;
    s32 xe0;
} W55Cam;
void func_001418b8(W55Cam *c) {
    s32 i;
    c->x4 = 2.0f;
    c->x0 = 0;
    c->x8 = 8.0f;
    c->x10 = 190.0f;
    c->x14 = 0.1f;
    c->x18 = 0.95f;
    c->x1c = 1.04719746112823486328125f;
    c->x20 = 1.22173035144805908203125f;
    c->x24 = 0.034906583f;
    c->x2c = 3.1415928f;
    c->x30 = 3.1415928f;
    c->x28 = 0.523598730564117431640625f;
    c->x34 = 3.1415928f;
    c->x38 = 3.1415928f;
    c->x40 = 18;
    c->x48 = 3;
    c->x4c = 0;
    c->x50 = 0;
    c->xe0 = 0;
    c->x54 = 0;
    c->x5c = 0;
    c->x3c = 18;
    c->x60 = 1.0f;
    c->x64 = 1.0f;
    c->x68 = 0;
    c->x44 = 3;
    c->x70 = 0;
    c->x58 = 0.5f;
    c->x74 = 0;
    c->x6c = 0x1000;
    for (i = 15; i >= 0; i--) c->x78[i] = 1.0f;
    c->xb8 = 0;
    c->xbc = 0;
    c->xbe = 0;
    c->xbd = 3;
    c->xc0 = 0;
    c->xc2 = 0;
    c->xc4 = 1.0f;
    c->xc8 = 0;
    c->xcc = 0.19634955f;
    c->xd1 = 3;
    c->xd0 = 3;
    c->xd2 = 0;
    c->xd4 = 1.0f;
    c->xd8 = 0;
    c->xdc = 1.0f;
}

/* func_00141b10 (from hand/nostrict/text_00130000_b03.c). */
typedef W606Mem_304be8 B3SvEnt;
typedef struct {
    u8 pad08[0x1c - 0x8];
    f32 x1c, x20, x24, x28, x2c, x30, x34, x38;
    s32 x3c, x40, x44, x48, x4c, x50;
    u8 pad54[0x5c - 0x54];
    f32 x5c;
    u8 pad60[0x68 - 0x60];
    s32 x68;
    u8 pad6c[0x78 - 0x6c];
    f32 x78[16];
    s32 xb8;
    u8 xbc;
    u8 xbd;
    u16 xbe, xc0, xc2;
    f32 xc4;
    B3SvEnt *xc8;
    u8 padcc[0xd0 - 0xcc];
    u8 xd0, xd1;
    u8 padd2[0xd4 - 0xd2];
    f32 xd4;
    u8 padd8[0xe0 - 0xd8];
    s32 xe0;
} B3StB;
typedef struct {
    s32 x0, x4;
    B3StB b;
} B3St;
typedef struct { u8 pad[0x30]; s8 x30; u8 pad31[7]; s8 x38; } B3Eq;
typedef struct { s8 x0, x1, x2, x3, x4, x5; s8 x6[16]; } B3It;
extern f32 D_00304C48[];
B3Eq *func_00149740(s32);
B3It *func_00147860(s32);
s32 func_0013c598(s32);
void func_00141b10(s32 n, B3St *p) {
    B3StB *b;
    B3SvEnt *e = &D_00304BE8->m[n];
    B3Eq *r;
    B3It *q;
    s32 i, j;

    p->b.x40 = e->sub.hpmax;
    p->b.x48 = e->sub.mpmax;
    p->b.xbe = e->sub.x38;
    p->b.x4c = e->sub.x6;
    p->b.x50 = e->sub.x7;
    p->b.xe0 = e->sub.x5;
    p->b.xc0 = 0;
    p->b.xc2 = 0;
    p->b.xc4 = 1.0f;
    p->b.xb8 = 0;
    p->b.xbc = 0;
    for (i = 0, b = &p->b; i < 16; i++) p->b.x78[i] = e->sub.x8[i] / 100.0f;
    r = func_00149740(n);
    if (r) {
        p->b.x4c += r->x30;
        p->b.x48 += r->x38;
    }
    for (i = 0; i < e->sub.x18; i++) {
        if (e->sub.x19[i]) {
            q = func_00147860(e->sub.x19[i]);
            p->b.x40 += q->x0;
            p->b.x48 += q->x1;
            p->b.x4c += q->x2;
            p->b.x50 += q->x3;
            p->b.xe0 += q->x4;
            for (j = 0; j < 16; j++) b->x78[j] *= q->x6[j] / 100.0f;
        }
    }
    p->b.x3c = (e->sub.x1 < p->b.x40) ? e->sub.x1 : p->b.x40;
    p->b.x44 = (e->sub.x3 < p->b.x48) ? e->sub.x3 : p->b.x48;
    p->b.xbe = (e->sub.x38 < p->b.x48 * 30) ? e->sub.x38 : p->b.x48 * 30;
    p->b.x4c = (p->b.x4c < 101) ? p->b.x4c : 100;
    p->b.x50 = (p->b.x50 < 101) ? p->b.x50 : 100;
    p->b.xe0 = (p->b.xe0 < 101) ? p->b.xe0 : 100;
    p->b.xc8 = e;
    p->b.xd0 = func_0013c968(6, n) + 3;
    p->b.xd1 = func_0013c968(7, n) + 3;
    p->b.xd4 = (f32)func_0013c968(8, n) + 1.0f;
    p->b.x5c = D_00304C48[n];
    p->b.x68 = func_0013c598(n);
    p->b.x1c = 1.0471974909305573f;
    p->b.x38 = 0.87266458570957184f;
    p->b.x2c = 0.34906581789255142f;
    p->b.x20 = 1.570796400308609f;
    p->b.x34 = 0.87266458570957184f;
    p->b.x30 = 0.34906581789255142f;
    p->b.x24 = 0.017453290987759829f;
}

/* func_00141f10 (from hand/nostrict/text_00140000_h33.c). */
typedef struct {
    u32 flags;
    u8 pad4[0x38];
    s32 w3c;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4c;
    s32 w50;
    u8 pad54[0x68 - 0x54];
    s32 w68;
    u8 pad6c[4];
    s32 w70;
    u8 pad74[4];
    f32 f78[16];
    s32 wb8;
    u8 bbc;
    u8 padbd;
    u16 hbe;
    u16 hc0;
    u16 hc2;
    f32 fc4;
    void *pc8;
    u8 padcc[6];
    u16 hd2;
    u8 padd4[4];
    s32 wd8;
    f32 fdc;
} Lv;
typedef struct Actor_41f10 { u8 pad[0x6C]; Lv *p6c; } Pl;
typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    u16 hc;
    u8 pade[2];
    u16 h10;
    u8 pad12[2];
    s32 w14;
    f32 f18;
    s32 w1c;
    u16 h20;
    u8 pad22[2];
    f32 f24;
    s32 a28[16];
    s32 w68;
} LvInit;
u8 *func_00147730(s32);
void func_00141f10(Pl *o, LvInit *in) {
    Lv *s = o->p6c;
    s32 i;
    s32 v = in->w0;
    s->w48 = 0;
    s->w40 = v;
    s->w3c = v;
    s->w44 = 0;
    s->hbe = 0;
    s->w4c = func_00147730(in->w4)[0];
    s->w50 = func_00147730(in->w8)[1];
    s->hc0 = in->hc;
    s->hc2 = in->h10;
    s->wb8 = 0;
    s->bbc = 0;
    s->fc4 = in->f18;
    s->w68 = in->w1c;
    s->hd2 = in->h20;
    s->wd8 = in->w14;
    s->fdc = in->f24;
    for (i = 0; i < 16; i++) {
        s->f78[i] = in->a28[i] / 100.0f;
    }
    s->w70 = in->w68;
}

