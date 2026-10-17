#include "common.h"
#include "platform/math.h"

extern volatile s32 D_002BBDE0;
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

typedef struct { u32 mask; u32 val; } MaskEnt;
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
extern Slot D_004F3230[];
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
extern Ent4C D_004E4528[];
s32 func_0011f2d0(Ent4C *);

s32 func_001207f8(s32 id) {
    s32 i;
    Ent4C *e = D_004E4528;
    for (i = 0; i < 16; i++, e++) {
        if (func_0011f2d0(e) && (id == -1 || id == e->x44)) return 1;
    }
    return 0;
}

extern Pool D_004E49E8;
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
extern u8 D_004F35B0[];
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
        if (a > ((f32)3.141592653589793)) a -= ((f32)6.283185307179586);
        else if (a < -((f32)3.141592653589793)) a += ((f32)6.283185307179586);
        else break;
    }
    return a;
}
