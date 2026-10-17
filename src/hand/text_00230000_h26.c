/* 0x00230000-0x0024FFFF game code by hand (batch 26). */
#include "common.h"

extern u8 D_00426970[];
extern u8 D_0042B790[];
extern u8 D_004305B0[];
void func_00249a48(void *, s32);

void func_0023d698(s32 a) {
    if (a == 0) {
        func_00249a48(D_00426970, 1);
    } else if (a == 1) {
        func_00249a48(D_0042B790, 1);
    } else {
        func_00249a48(D_004305B0, 1);
    }
}

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
extern Vec12Mgr D_006561D0;
s32 func_00243208(Vec12Queue *, Vec12 *);
s32 func_00243278(Vec12Queue *, Vec12 *);
void func_00243690(Vec12 *);
void func_002436c0(s32);

s32 func_00243a20(void) {
    Vec12 v;
    s32 r = 0;
    Vec12Mgr *s = &D_006561D0;
    if (s->on == 0) {
        if (!func_00243208(&s->q, &v)) return 0;
        func_00243690(&v);
    } else {
        r = func_00243278(&s->q, &v) != 0;
    }
    func_002436c0(r);
    return 0;
}

void func_0024ae00(void *);
void func_0024af00(void *);
void func_00243c10(void *, s32, s32, s32, f32, s32);

void func_00243d18(s32 f, void *p, s32 a, s32 b, s32 c, f32 x, s32 d) {
    if (f) func_0024ae00(p);
    func_0024af00(p);
    func_00243c10(p, a, b, c, x, d);
}

/* Three rows of five 0xA00-byte cells, with a used count per row. */
typedef struct { s32 on; u8 pad4[0xA00 - 4]; } Cell;
typedef struct { Cell c[5]; } Row;
typedef struct {
    s32 n[4];   /* +0x0 */
    Row r[3];   /* +0x10 */
} Grid;
extern Grid D_00656510;

void func_002444a0(void) {
    s32 i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 5; j++)
            D_00656510.r[i].c[j].on = 0;
}

s32 func_002448d8(void) {
    s32 i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < D_00656510.n[i]; j++)
            if ((&D_00656510.r[0])[i].c[j].on) return 1;
    return 0;
}

typedef struct { s32 id; s32 arg; s32 on; f32 t; s32 unk10; s32 unk14; } Req;
extern Req D_006627B0;
void func_00245238(s32 id, s32 arg) {
    Req *r = &D_006627B0;
    r->unk10 = 1;
    if (r->on == 0 || r->id != id) {
        r->id = id;
        r->arg = arg;
        r->on = 1;
        r->t = 1.0f;
    }
}
void func_00245280(s32 id, s32 arg) {
    Req *r = &D_006627B0;
    r->unk10 = 1;
    r->unk14 = 1;
    if (r->on == 0 || r->id != id) {
        r->id = id;
        r->arg = arg;
        r->on = 1;
        r->t = 1.0f;
    }
}

/* Ten 0x860-byte channels: a free one, else the oldest. */
typedef struct { s32 used; s32 age; u8 pad8[0x860 - 8]; } Snd;
extern Snd D_00662A30[10];

Snd *func_002457c8(void) {
    Snd *best = 0;
    s32 max = -1;
    s32 i;
    Snd *p = D_00662A30;
    for (i = 0; i < 10; i++, p++)
        if (p->used == 0) return p;
    for (i = 0; i < 10; i++) {
        p = &D_00662A30[i];
        if (max < p->age) {
            max = p->age;
            best = p;
        }
    }
    return best;
}

void func_002458e0(void) {
    s32 i;
    for (i = 0; i < 10; i++) D_00662A30[i].used = 0;
}

typedef struct { u8 pad[0x4C]; u16 unk4C; } Info;
typedef struct { u8 pad[0x130]; Info *unk130; } Act;
typedef struct { s32 a, b, c, d; } Q4;
extern Q4 D_00668040[2];
s32 func_0013daa8(s32);

Q4 *func_00245f58(Act *a) {
    s32 i = func_0013daa8(a->unk130->unk4C) != 1;
    return &D_00668040[i];
}

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
