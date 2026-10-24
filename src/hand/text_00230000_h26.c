/* 0x00230000-0x0024FFFF game code by hand (batch 26). */
#include "common.h"

typedef struct { u8 pad[0xA24]; s32 unkA24; u8 padA28[8]; s32 unkA30; } Obj3;
extern f32 D_002BBDFC;

s32 func_00240b28(Obj3 *e) {
    s32 r;
    if (e->unkA30 > 0) {
        e->unkA30 = e->unkA30 - D_002BBDFC;
        r = 1;
    } else {
        r = 2;
        if (e->unkA24 == 0) r = 0;
    }
    return r;
}

/* Five 0xD00-byte slots, each with an in-use flag. */
typedef struct {
    u32 state;  /* +0x0 */
    s32 unk4;   /* +0x4 */
    u8 pad8[0x94 - 8];
    s32 unk94;
    s32 unk98;
    s32 unk9C;
    u8 padA0[0x770 - 0xA0];
    s32 unk770;
    u8 pad774[0x9D0 - 0x774];
    s32 unk9D0;
    u8 pad9D4[0xA18 - 0x9D4];
    s32 unkA18;
    f32 unkA1C;
    s32 unkA20;
    s32 unkA24;
    u8 padA28[0xD00 - 0xA28];
} Slot;
typedef struct {
    s32 on[8];  /* +0x0 */
    Slot e[5];  /* +0x20 */
} SlotTbl;
extern SlotTbl D_00651E50;
s32 func_00122ff8(s32);
s32 func_0023d490(Slot *);
void func_002414a8(s32, s32);
void func_0023d1a0(void);

void func_00241560(void) {
    s32 i;
    Slot *p = D_00651E50.e;
    for (i = 0; i < 5; i++, p++) {
        if (D_00651E50.on[i] && p->state < 3) {
            if (!func_00122ff8(p->unk4)) {
                D_00651E50.on[i] = 0;
                if (p->state == 0) func_0023d1a0();
            }
        }
    }
}

Slot *func_00241b60(s32 i, s32 b) {
    Slot *p;
    D_00651E50.on[i] = 1;
    D_00651E50.e[i].unk4 = b;
    p = &D_00651E50.e[i];
    p->unkA18 = 1;
    p->state = i;
    p->unk98 = p->unk94 = func_0023d490(p);
    p->unkA24 = 0;
    p->unk770 = 0;
    p->unk9D0 = 0;
    p->unk9C = 0;
    func_002414a8(i, 1);
    return p;
}

typedef struct { s32 a, b, c; } Vec12;
typedef struct { s32 cap; Vec12 *buf; s32 wr; s32 rd; } Vec12Queue;
/* The current record, then the queue of pending ones. */
typedef struct {
    s32 on;         /* +0x0 */
    Vec12 v;        /* +0x4 */
    s32 unk10;
    Vec12Queue q;   /* +0x14 */
} Vec12Mgr;

void func_0024ae00(void *);

/* Three rows of five 0xA00-byte cells, with a used count per row. */

/* Ten 0x860-byte channels: a free one, else the oldest. */
typedef struct { s32 a, b, c, d; } Q4;
extern Q4 D_00668040[2]; /* src/data/bss_0066.c: u8 D_00668040[0x20] */

void func_002464f8(s32 *out) {
    s32 i;
    for (i = 0; i < 2; i++) {
        switch (D_00668040[i].a) {
        case 0: out[i] = 0; break;
        case 4: out[i] = 0; break;
        case 5: out[i] = 0; break;
        case 6: out[i] = 0; break;
        default: out[i] = 1; break;
        }
    }
}

/* Splits x into five 300-wide steps, halved. */
void func_00246658(s32 x, s32 *out) {
    s32 t[5];
    s32 i;
    for (i = 0; i < 5; i++) out[i] = 0;
    for (i = 0; i < 5; i++) {
        if (x >= 0) {
            t[i] = x + 1;
            if (x + 1 > 300) t[i] = 300;
            x -= 300;
            out[i] = t[i] / 2;
        }
    }
}

typedef struct { u64 a; s32 unk8; u8 pad[0xC0 - 12]; } Blk;

void func_00246708(Blk *d, Blk *s, s32 v) {
    *d = *s;
    d->unk8 = v;
}

/* Ten 0x930-byte slots: a free one, else the oldest. */
#include "data/types/text_00230000_h26.h"
#include "data/pieces/D_0045FAC0.h"

void func_00247350(void) {
    s32 i;
    for (i = 0; i < 10; i++) D_0045FAC0[i].used = 0;
}

Fx *func_00247388(void) {
    s32 max = -1;
    Fx *best = 0;
    s32 i;
    Fx *p;
    for (i = 0; i < 10; i++) {
        p = &D_0045FAC0[i];
        if (p->used == 0) return p;
    }
    for (i = 0; i < 10; i++) {
        p = &D_0045FAC0[i];
        if (max < p->age) {
            max = p->age;
            best = p;
        }
    }
    return best;
}

s32 func_002474a8(void) {
    s32 i;
    for (i = 0; i < 10; i++)
        if (D_0045FAC0[i].used) return 1;
    return 0;
}

typedef struct { u8 pad[0x24]; s32 unk24; s32 unk28; } Mdl;
extern s32 D_006693B0[8];
extern s32 D_00669390[8];
extern s32 D_006693D0[7]; /* src/data/bss_0066.c: u8 D_006693D0[0x20] */
u8 D_006692C0[0x18] ALIGNED(16);
void func_002474e8(s32, void *, s32, s32, f32);
void func_002476a0(Mdl *);
void func_00247930(Mdl *);
void func_00247b50(Mdl *m) {
    s32 i;
    for (i = 0; i < 8; i++)
        func_002474e8(D_006693B0[i], D_006692C0, m->unk24, m->unk28, 1.0f);
    func_002476a0(m);
    func_00247930(m);
}
void func_00247bd0(Mdl *m) {
    s32 i;
    for (i = 0; i < 8; i++)
        func_002474e8(D_00669390[i], D_006692C0, m->unk24, m->unk28, 1.0f);
    func_002476a0(m);
    func_00247930(m);
}
void func_00247c50(Mdl *m) {
    s32 i;
    for (i = 0; i < 7; i++)
        func_002474e8(D_006693D0[i], D_006692C0, m->unk24, m->unk28, 1.0f);
    func_002476a0(m);
}

extern s32 D_00669388[2];
u8 D_00669320[0x18] ALIGNED(16);
void func_002474e8(s32, void *, s32, s32, f32);
void func_002480d8(void) {
    s32 i;
    for (i = 0; i < 2; i++)
        func_002474e8(D_00669388[i], D_00669320, 0, 0, 1.0f);
}
void func_00248678(Vec12Queue *q, Vec12 *v) {
    if (q->wr != q->cap) {
        q->buf[q->wr] = *v;
        q->wr++;
    }
}
s32 func_002486c8(Vec12Queue *q, Vec12 *v) {
    if (q->wr == q->rd)
        return 0;
    *v = q->buf[q->rd];
    q->rd++;
    if (q->wr == q->rd) {
        q->rd = 0;
        q->wr = 0;
    }
    return 1;
}
s32 func_00248738(Vec12Queue *q, Vec12 *v) {
    if (q->wr == q->rd)
        return 0;
    *v = q->buf[q->rd];
    return 1;
}

extern Vec12Mgr D_00669700;
void func_00248b58(s32);

void func_00248b28(Vec12 *v) {
    D_00669700.unk10 = 0;
    D_00669700.v = *v;
    D_00669700.on = 1;
}

/* Needs func_002486c8/func_00248738 defined above it. */
s32 func_00248e30(void) {
    Vec12 v;
    s32 r = 0;
    Vec12Mgr *s = &D_00669700;
    if (s->on == 0) {
        if (!func_002486c8(&s->q, &v)) return 0;
        func_00248b28(&v);
    } else {
        r = func_00248738(&s->q, &v) != 0;
    }
    func_00248b58(r);
    return 0;
}

typedef struct { f32 val; f32 speed; } Fade;
#include "data/pieces/D_002C5960.h"

/* Steps a fade by speed*dt (unless paused): 2 when it reaches 0, 1 when it
 * reaches 128. */
s32 func_002492e8(Fade *p, s32 dt) {
    if (p->speed != 0.0f) {
        if (!((*(u32 *)&D_002C5960) & 1)) p->val += p->speed * (f32)dt;
        if (p->val <= 0.0f) {
            p->val = 0.0f;
            p->speed = 0.0f;
            return 2;
        }
        if (p->val >= 128.0f) {
            p->val = 128.0f;
            p->speed = 0.0f;
            return 1;
        }
    }
    return 0;
}

typedef struct {
    u64 a : 14;
    u64 p0 : 23;
    u64 b : 14;
    u64 p1 : 13;
} Bits;
typedef struct {
    u8 pad[0x28];
    Bits bits;
} Obj5;

void func_00249d50(Obj5 *e, s32 a, s32 b) {
    Bits *p = &e->bits;
    p->a = a;
    p->b = b;
}

typedef struct {
    u64 lo : 20;
    u64 f20 : 6;
    u64 mid : 30;
    u64 f56 : 5;
    u64 f61 : 3;
} Tag;
typedef struct { u8 pad[0x18]; u64 unk18; } Src;
void func_0024a6b8(Tag *, void *, u64);
void func_0024aa48(void *a, Tag *t, Src *s) {
    func_0024a6b8(t, a, s->unk18);
    t->f56 = 0;
    t->f61 = 1;
    t->f20 = 0x13;
}

/* Runs func_0024e0f0 with the globals at 0x0046A03C..0x0046A048 loaded from a
 * parameter block; the ones at +0x40 and +0x48 are restored after. */
typedef struct { s32 unk0, unk4, unk8, unkC, unk10, unk14, unk18; } Prm;
extern Prm *D_00669A18[8]; /* src/data/bss_0066.c: s32 D_00669A18[8] */
#include "data/pieces/D_0046A040.h"
extern s32 D_0046A048;
#include "data/pieces/D_0046A044.h"
#include "data/pieces/D_0046A03C.h"
void func_0024e0f0(s32, s32, s32);
void func_0024b228(s32 i, s32 a, s32 b, s32 c) {
    Prm *p = D_00669A18[i];
    s32 o40, o48, t10, t18;
    D_0046A03C = p->unkC;
    o40 = D_0046A040;
    o48 = D_0046A048;
    t10 = p->unk10;
    (*(s32 *)&D_0046A044) = p->unk14;
    t18 = p->unk18;
    D_0046A040 = t10;
    D_0046A048 = t18;
    func_0024e0f0(a, b, c);
    D_0046A040 = o40;
    D_0046A048 = o48;
}
void func_0024b6d0(Prm *p, s32 a, s32 b, s32 c) {
    s32 o40, o48, t10, t18;
    D_0046A03C = p->unkC;
    o40 = D_0046A040;
    o48 = D_0046A048;
    t10 = p->unk10;
    (*(s32 *)&D_0046A044) = p->unk14;
    t18 = p->unk18;
    D_0046A040 = t10;
    D_0046A048 = t18;
    func_0024e0f0(a, b, c);
    D_0046A040 = o40;
    D_0046A048 = o48;
}

s32 func_0024b778(s32 n) {
    s32 a = n * 32;
    a += n * 0x10320;
    return (a + 1511) & ~63;
}

/* needs make: uses rodata */

void func_002407b0(u8 *e, s32 k) {
    switch (k) {
    case 0: *(void **)(e + 0x9C) = e + 0xA0; break;
    case 1: *(void **)(e + 0x9C) = e + 0x160; break;
    case 2: *(void **)(e + 0x9C) = e + 0x220; break;
    case 3: *(void **)(e + 0x9C) = e + 0x2E0; break;
    case 4: *(void **)(e + 0x9C) = e + 0x3A0; break;
    }
    func_0024ae00(*(void **)(e + 0x9C));
}
#include "data/data_0046.h"
#include "data/data_0045.h"
#include "data/pieces/D_002BBDFC.h"
