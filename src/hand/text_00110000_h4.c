#include "common.h"
#include "platform/math.h"

#include "data/pieces/D_002BBDE0.h"
extern s32 D_002C1310[];

void func_0011dc28(s32 *a, s32 *b, s32 *c) {
    s32 i = 3;
    s32 *p;
    if (D_002BBDE0 == i) return;
    p = D_002C1310;
    for (; i >= 0; i--) {
        if (*a == *p++) {
            if (*b < 9216 && *c < 9216) { *b = 9216; *c = 9216; }
        }
    }
}

typedef struct { s32 id; u8 pad[16]; u8 f14; } S0011dc98;

void func_0011dc98(S0011dc98 *a) {
    s32 i;
    s32 *p;
    if (D_002BBDE0 == 3) return;
    p = D_002C1310;
    for (i = 3; i >= 0; i--) {
        if (a->id == *p++) {
            a->f14 = 0;
        }
    }
}

typedef struct Node { u16 type; u16 f2; s32 key; struct Node *next; s32 data; } Node;
typedef struct { u16 size; u16 count; u8 *base; Node *head; u8 *cur; } Pool;

u8 *func_0011efe8(Pool *p) {
    u8 *cur = p->cur;
    u8 *base;
    u8 *end;
    s32 i;
    if (cur == 0) cur = p->base;
    base = p->base;
    end = base + p->size * p->count;
    for (i = 0; i < p->count; i++) {
        cur += p->size;
        if (cur >= end) cur = base;
        if (*(u16 *)cur == 0) return cur;
    }
    return 0;
}

Node *func_0011f2e0(Pool *p, s32 data) {
    Node *it;
    for (it = p->head; it; it = it->next) {
        if (it->data == data) return it;
    }
    return 0;
}

s32 func_0011f320(Pool *p, Node *n) {
    Node *it, *prev = 0;
    for (it = p->head; it; it = it->next) {
        if (it == n) {
            if (prev) prev->next = it->next; else p->head = it->next;
            it->next = 0;
            return 1;
        }
        prev = it;
    }
    return 0;
}

#include "data/types/text_00110000_h4_p.h"
extern MaskEnt D_002C5990[];

u32 func_0011f628(u32 m) {
    u32 r = 0;
    u32 i;
    for (i = 0; i < 30; i++) {
        if ((m & D_002C5990[i].mask) == D_002C5990[i].mask) r |= D_002C5990[i].val;
    }
    return r;
}

typedef struct { u64 a, b; } Q128;

void func_0011fb78(Q128 *p, u64 a1, Q128 *end) {
    u64 v = (end - p - 1) | (a1 << 28);
    if ((u32)end > 0x6fffffff) v |= 0x8000000000000000;
    *(u64 *)p = v;
}

typedef struct { u32 flags; u8 pad[44]; s32 x30; s32 x34; } Slot;
Slot D_004F3230[0x10] ALIGNED(16);
extern s32 D_002C5C44;
Slot *func_0011ffd0(void) {
    s32 i;
    Slot *s = D_004F3230;
    for (i = 0; i < 16; i++, s++) {
        if (!(s->flags & 1)) {
            s->flags |= 1;
            s->x34 = D_002C5C44++;
            s->x30 = -1;
            return s;
        }
    }
    return 0;
}

s32 func_00120170(u32 a, u32 *b) {
    if (a < *b) return -1;
    return *b < a;
}

s32 sceCdDiskReady(s32);
s32 func_00269da8(s32, s32);
void func_0011fd40(void);
void func_00120438(s32 a, s32 b) {
    while (sceCdDiskReady(1) != 2 || func_00269da8(a, b) == 0) func_0011fd40();
}


typedef struct { u8 pad[68]; s32 x44; s32 x48; } Ent4C;
Ent4C D_004E4528[0x10] ALIGNED(8);
s32 func_0011f2d0(Ent4C *);

s32 func_001207f8(s32 id) {
    s32 i;
    Ent4C *e = D_004E4528;
    for (i = 0; i < 16; i++, e++) {
        if (func_0011f2d0(e) && (id == -1 || id == e->x44)) return 1;
    }
    return 0;
}

extern Pool D_004E49E8; /* src/data/bss_004E.c: u8 D_004E49E8[0x18] */
extern s32 D_004E4520;
void func_0011efa8(Pool *, void *, s32, s32);
void func_00120038(Slot *);

void func_00120aa0(void) {
    s32 i;
    Slot *s;
    func_0011efa8(&D_004E49E8, D_004E4528, 76, 16);
    D_004E4520 = 0;
    s = D_004F3230;
    for (i = 15; i >= 0; i--) func_00120038(s++);
}

extern char D_0048D288[];
u8 D_004F35B0[0x1000] ALIGNED(16);
void sceSifInitRpc(s32);
void func_0025b550(void);
s32 sceCdInit(s32);
void func_0026a728(s32);
s32 func_0025f228(char *);
s32 func_0025f1f0(void);
void func_001101e8(void);
void func_002696b8(s32, void *, s32);
void func_00120b10(void) {
    sceSifInitRpc(0);
    func_0025b550();
    sceCdInit(0);
    func_0026a728(2);
    while (!func_0025f228(D_0048D288));
    while (!func_0025f1f0());
    func_001101e8();
    sceSifInitRpc(0);
    sceCdInit(0);
    func_0026a728(2);
    func_002696b8(0, D_004F35B0, 4096);
}

f32 func_00267390(void *, void *);
f32 func_00120bf8(void *a) {
    return PlatSqrtf(func_00267390(a, a));
}

f32 func_00120c88(f32 a) {
    s32 i;
    for (i = 0; i < 1024; i++) {
        if (a > 3.1415928f) a -= 6.2831856f;
        else if (a < -3.1415928f) a += 6.2831856f;
        else break;
    }
    return a;
}

#include "data/pieces/D_002C5C80.h"
typedef Vec4_2c5c80 Vec4;
void func_00267530(Vec4 *, Vec4 *, Vec4 *);
void func_00267370(Vec4 *, Vec4 *, Vec4 *);
void func_00121fc4(Vec4 *, Vec4 *);
void func_00120f70(Vec4 *pts, Vec4 *out) {
    Vec4 d[2];
    s32 i;
    for (i = 0; i < 2; i++) func_00267530(&d[i], &pts[i + 1], &pts[i]);
    d[1].v[3] = d[0].v[3] = 1.0f;
    func_00267370(out, &d[0], &d[1]);
    func_00121fc4(out, out);
}

s32 func_00267ea8(Vec4 *);
s32 func_00121120(Vec4 *v) {
    s32 r = 0;
    if (v->v[2] < 0.0f || func_00267ea8(v)) r = 1;
    return r;
}

f32 func_001214e0(f32 *a, f32 *b, f32 t) {
    s32 i = (s32)t;
    f32 f = t - (f32)i;
    return ((((b[i + 1] - b[i]) * f + b[i] * 3.0f) * f + ((a[i + 1] - a[i]) - (b[i] * 2.0f + b[i + 1]))) * f) + a[i];
}

void func_00267c10(Vec4 *, void *, s32, f32, f32, f32);
void func_00267e90(Vec4 *, Vec4 *, f32);

void func_00121620(Vec4 *m, void *a1, f32 x, f32 y, f32 z, f32 w) {
    func_00267c10(m, a1, 0, x, y, z);
    func_00267e90(&m[3], &m[3], w);
}

void func_00121668(f32 d[4][4], f32 s[4][4]) {
    d[0][0] = s[0][0]; d[0][1] = s[1][0]; d[0][2] = s[2][0]; d[0][3] = 0.0f;
    d[1][0] = s[0][1]; d[1][1] = s[1][1]; d[1][2] = s[2][1]; d[1][3] = 0.0f;
    d[2][0] = s[0][2]; d[2][1] = s[1][2]; d[2][2] = s[2][2]; d[2][3] = 0.0f;
    d[3][0] = 0.0f; d[3][1] = 0.0f; d[3][2] = 0.0f; d[3][3] = 1.0f;
}

extern f32 D_002BBDFC;

f32 func_001216d8(f32 a, f32 b, f32 c) {
    f32 d = func_00120c88(b - a);
    c *= D_002BBDFC;
    if (d > c) d = c;
    else if (d < -c) d = -c;
    return func_00120c88(a + d);
}

void func_00121958(Vec4 *d, Vec4 *s, f32 *k) {
    s32 i;
    for (i = 0; i < 3; i++) func_00267e90(&d[i], &s[i], *k++);
}

/* Heap block table: 512 entries, D_004F6DB0 (the rover) sits right after it. */
#include "data/types/text_00110000_h4.h"
extern Block D_004F45B0[];
extern Block *D_004F6DB0;
extern u8 D_009A0000[];

Block *func_00121d00(void) {
    Block *p = D_004F6DB0;
    s32 i;
    for (i = 1; i < 512; i++) {
        p++;
        if (p >= &D_004F45B0[512]) p = &D_004F45B0[1];
        if (p->addr == 0) { D_004F6DB0 = p; return p; }
    }
    return 0;
}

Block *func_00121d60(u32 size) {
    Block *p = D_004F45B0;
    Block *n;
    while ((n = (Block *)p->next) != 0) {
        if (n->addr - (p->addr + p->size) >= size) return p;
        p = n;
    }
    if ((u32)D_009A0000 - (p->addr + p->size) >= size) return p;
    return 0;
}

Block *func_00121de0(u32 addr) {
    Block *p;
    for (p = (Block *)D_004F45B0[0].next; p; p = (Block *)p->next) {
        if (p->addr == addr) return p;
    }
    return 0;
}

u32 func_00121e28(u32 size, u32 *out) {
    Block *b, *p;
    size = (size + 127) & ~127;
    b = func_00121d00();
    p = func_00121d60(size);
    b->addr = p->addr + p->size;
    if (out) *out = b->addr;
    b->size = size;
    b->owner = (u32)out;
    b->f0 = 0;
    b->next = p->next;
    p->next = (u32)b;
    return b->addr;
}

void func_00121ee0(u32 addr) {
    Block *prev = D_004F45B0;
    Block *p;
    while ((p = (Block *)prev->next) != 0 && p->addr != addr) prev = p;
    if (p->owner) *(u32 *)p->owner = 0;
    p->owner = 0;
    p->addr = 0;
    prev->next = p->next;
}

extern u32 *D_004F6EB8;

u32 func_00122048(u32 size, u32 align) {
    u32 *p = D_004F6EB8;
    u32 *old = p;
    u32 v;
    p += 2;
    D_004F6EB8 = p;
    v = (old[1] + align - 1) / align * align;
    p[0] = v;
    if (size) D_004F6EB8[1] = v + size;
    else D_004F6EB8[1] = 0x70004000;
    return v;
}

typedef Lt64_2c5c80 Ent40;
#include "data/pieces/D_002C5C60.h"
void func_002675a8(Vec4 *, Vec4 *);

Ent40 *func_001226f0(s32 a, s32 b, s32 c) {
    s32 i;
    Ent40 *e = &D_002C5C80;
    for (i = 0; i < 31; i++, e++) {
        if (e->kind == 0) {
            e->kind = a; e->b = b; e->c = c;
            func_002675a8(&e->v, ((Vec4 *)&D_002C5C60));
            return e;
        }
    }
    return 0;
}

typedef struct { u8 pad[0x44]; f32 f44; u8 pad2[0x16]; u8 b5e; u8 b5f; } Sub130;
typedef struct {
    u32 flags; u8 pad[0x12c]; Sub130 *p130; u8 pad2[0x18]; s32 x14c; s32 pad3; s32 x154;
    u8 pad4[0x78]; s32 x1d0; u8 pad5[0x19c]; u64 x370;
} Obj;

void func_00122f20(Obj *o, s32 *out) {
    out[0] = o->x154;
    if (o->x14c) out[1] = *(s32 *)o->x14c; else out[1] = 0;
    out[2] = o->x1d0;
}

s32 func_00122fd0(Obj *o) {
    s32 r = 0;
    if (o->p130->b5f) {
        if (!(o->flags & 0x2000000)) r = 1;
    }
    return r;
}

s32 func_00122ff8(Obj *o) {
    s32 r = 0;
    if (o) {
        if ((o->x370 & 0x300000000) == 0x100000000) r = 1;
    }
    return r;
}

/* Actor table: 1200-byte entries from D_002C64A0 up to D_002E26A0. */
typedef struct Act {
    u8 pad0[6]; u8 b6; u8 pad7[0x6d]; struct Act *x74; s32 x78; s32 pad7c; s32 x80;
    u8 pad84[0x2ec];
    union { u64 x370; struct { u32 lo0; u32 lo : 5; u32 kind : 2; u32 hi : 25; } b370; } u370;
    u8 pad378[0x138];
} Act;
extern Act D_002C64A0[];
#include "data/pieces/D_002E26A0.h"
Act *func_001230a0(Act *a);
s32 func_00123118(s32, Act *);

void func_00123030(Act *x, Act *a1, s32 a2) {
    Act *a;
    x->x74 = a1;
    x->x78 = a2;
    a = 0;
    while ((a = func_001230a0(a)) != 0) a->x80 = 0;
    while ((a = func_001230a0(a)) != 0) {
        if (a->x74) a->x74->x80++;
    }
}

Act *func_001230a0(Act *a) {
    if (a == 0) a = D_002C64A0; else a++;
    for (; a < ((Act *)&D_002E26A0); a++) {
        if ((a->u370.x370 & 0x300000000) == 0x100000000) return a;
    }
    return 0;
}

Act *func_00123158(s32 k, Act *a) {
    while ((a = func_001230a0(a)) != 0) {
        if (func_00123118(k, a)) return a;
    }
    return 0;
}

Act *func_001231b8(Act *x, Act *a) {
    while ((a = func_001230a0(a)) != 0) {
        if (x != a && x->u370.b370.kind == a->u370.b370.kind) return a;
    }
    return 0;
}

Act *func_00123220(Act *a) {
    while ((a = func_001230a0(a)) != 0) {
        if (a->b6 == 2 || a->b6 == 9 || a->b6 == 10 || a->u370.b370.kind == 2) return a;
    }
    return 0;
}

/* needs make: uses rodata */
/* "%3d" at D_0048D110, "amusic/music" at D_0048D118 (inlined strcpy). */
int sprintf(char *, const char *, ...);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
extern char D_0048D198[]; /* ".bgm", shared with a later function */

void func_0011ea40(s32 n, char *out) {
    char buf[80];
    sprintf(buf, "%3d", n);
    if (buf[0] == ' ') {
        buf[0] = '0';
        if (buf[1] == ' ') buf[1] = '0';
    }
    strcpy(out, "amusic/music");
    strcat(out, buf);
    strcat(out, D_0048D198);
}
#include "data/bss_004F_mixed.h"
#include "data/data_002C.h"
#include "data/data_0048.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002C5990.h"
