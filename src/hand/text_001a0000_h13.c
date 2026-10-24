/* Hand-matched functions in 0x001a0000-0x001c0000 (worker 13). */
#include "common.h"
#include "data/bss_0062.h"

/* Singly linked free list: pool->free at +4. */
typedef struct Node { struct Node *next; } Node;
typedef struct { u8 pad[4]; Node *free; } Pool;

Node *func_001a8900(Pool *p) {
    Node *n = p->free;
    if (n == NULL) return NULL;
    p->free = n->next;
    return n;
}

/* Fixed-size block pool: n blocks of (sz-1)*48+128 bytes after a 16-byte header. */
typedef struct { u8 n; u8 sz; s16 stride; void *free; } Pool2;

void func_001a8920(Pool2 *p, u8 n, u8 sz) {
    u8 **q = (u8 **)((u8 *)p + 16);
    s32 i;
    s32 stride;
    p->free = q;
    p->n = n;
    p->sz = sz;
    stride = (u8)(sz - 1) * 48 + 128;
    p->stride = stride;
    for (i = n - 1; i > 0; i--) {
        u8 **c = q;
        q = (u8 **)((u8 *)q + stride);
        *c = (u8 *)q;
    }
    *q = NULL;
}

/* u16 free-list of ids: next[] table at +0, head id at +6 (0xffff = empty). */
typedef struct { u16 *next; u8 pad[2]; u16 cur; } IdList;

s32 func_001a93e0(IdList *l) {
    u16 c;
    if (l->cur == 0xffff) return 0xffff;
    c = l->cur;
    l->cur = l->next[l->cur];
    return c;
}

#include "data/types/shared.h"
extern u128 D_0061E8B0;
extern s32 D_00372908;
s32 sceGsSyncPath(s32, s32);
void FlushCache(s32);
void func_00266f38(s32, void *);

void func_001aa008(void) {
    u128 *p = &D_0061E8B0;
    u128 save = *p;
    *p = 0x70000006;
    sceGsSyncPath(0, 0);
    FlushCache(0);
    func_00266f38(D_00372908, p);
    sceGsSyncPath(0, 0);
    *p = save;
}

/* GS packet chain tags: 16-byte DMA tags; next at +4, list tail at +8. */
#include "data/types/text_001a0000_h13.h"
extern GsTag D_0061EEA0[];  /* 16 priority list heads (followed by the tag pool) */
extern GsTag D_0061EFA0[];  /* 256 priority list heads */
GsTag D_0061FFA0[0x30] ALIGNED(32);

void func_001aa650(void) {
    void *p = D_0061EEA0;
    sceGsSyncPath(0, 0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    func_00266f38(D_00372908, p);
    sceGsSyncPath(0, 0);
}

/* The original clears the tag with `sq $0`, which ee-gcc 2.96 cannot emit
 * from C (it loads a zero TImode register first); the empty asm keeps the
 * header store ahead of the clamp as in the original. */
void func_001aa6b0(GsTag *t, s32 qwc, s32 pri) {
    GsTag *tail, *n;
    __asm__ volatile("sq $0, 0(%0)" : : "r"(t) : "memory");
    t->s.w0 = (qwc - 1) | 0x20000000;
    __asm__ volatile("" : : : "memory");
    if (pri < 1) pri = 0;
    if (pri >= 16) pri = 15;
    tail = D_0061EEA0[pri].s.tail;
    n = tail->s.next;
    tail->s.next = t;
    t->s.next = n;
    D_0061EEA0[pri].s.tail = t;
}

void func_001aa700(GsTag *t, s32 qwc, s32 pri) {
    GsTag *tail, *n;
    __asm__ volatile("sq $0, 0(%0)" : : "r"(t) : "memory");
    t->s.w0 = (qwc - 1) | 0x20000000;
    __asm__ volatile("" : : : "memory");
    if (pri < 1) pri = 0;
    if (pri >= 16) pri = 15;
    tail = D_0061FFA0[pri].s.tail;
    n = tail->s.next;
    tail->s.next = t;
    t->s.next = n;
    D_0061FFA0[pri].s.tail = t;
}

void func_001aa750(GsTag *t, s32 qwc, s32 pri) {
    GsTag *tail, *n;
    __asm__ volatile("sq $0, 0(%0)" : : "r"(t) : "memory");
    t->s.w0 = (qwc - 1) | 0x20000000;
    __asm__ volatile("" : : : "memory");
    if (pri < 1) pri = 0;
    if (pri >= 256) pri = 255;
    tail = D_0061EFA0[pri].s.tail;
    n = tail->s.next;
    tail->s.next = t;
    t->s.next = n;
    D_0061EFA0[pri].s.tail = t;
}

#include "data/pieces/D_00372800.h"

void func_001aa858(void) {
    f32 *d = D_00372800;
    d[0] = d[1] = 0.0f;
    d[2] = 255.0f;
    d[3] = 0.0f;
    d[4] = d[5] = 0.0f;
    d[6] = 255.0f;
    d[7] = 255.0f;
    d[8] = 0.7999999523162842f;
    d[9] = -32.0f;
    d[10] = 128.0f;
    d[11] = 0.0f;
    d[12] = 0.0f;
    d[13] = 128.0f;
    d[14] = 128.0f;
    d[15] = 0.0f;
}

/* Two small s32 stacks with s8 stack pointers. */
extern s8 D_00372EA0;
#include "data/pieces/D_00372EA8.h"
extern s8 D_00372F28;
#include "data/pieces/D_00372F30.h"

s32 func_001aa950(s32 n) {
    s8 *sp = &D_00372EA0;
    s32 *st = D_00372EA8;
    s32 i = *sp;
    s32 v = st[i];
    i++;
    *sp = i;
    st[i] = v + n;
    return v;
}

s32 func_001aa990(s32 n) {
    s8 *sp = &D_00372F28;
    s32 *st = D_00372F30;
    s32 i = *sp;
    s32 v = st[i];
    i++;
    *sp = i;
    st[i] = v;
    return v - n;
}

s32 func_001aaa38(s32 n) {
    if ((s32)D_00372F30 - n < D_00372EA8[D_00372EA0 + 1]) return -1;
    return 0;
}

extern char D_0048FE18[];
s32 func_0025b588(char *, s32);
s32 func_0025b990(s32, s32, s32);
void func_0025b810(s32);
int printf(const char *, ...);
void exit(s32);

/* Returns a file's size (open, seek to end, close); exits if it is missing. */
s32 func_001aab20(char *name) {
    char buf[1024];
    s32 fd, size;
    fd = func_0025b588(name, 1);
    if (fd < 0) {
        printf(D_0048FE18, name);
        exit(1);
    }
    size = func_0025b990(fd, 0, 2);
    func_0025b810(fd);
    return size;
}

typedef struct { u8 pad[0x60]; u64 a; u64 b; } Gs800;
#include "data/types/text_001a0000_h13_p.h"
extern Gs800 D_0061E800;
extern Gs060 D_00373060;

void func_001aaf30(void) {
    Gs060 *d = &D_00373060;
    d->a = D_0061E800.a;
    d->b = D_0061E800.b;
    sceGsSyncPath(0, 0);
    func_00266f38(D_00372908, d);
}

extern u8 D_00F20000[];
extern s32 D_00621210;
s32 func_001205f0(char *, void *);

/* Loads a program to 0x00F20000 and runs it. */
void func_001b9c60(char *a) {
    void (*fn)(void) = (void (*)(void))D_00F20000;
    D_00621210 = func_001205f0(a, fn);
    FlushCache(0);
    FlushCache(2);
    fn();
}

s32 func_001ba9a8(s32);
s32 func_001ba458(s32);

s32 func_001ba2f8(s32 a) {
    u8 *p = (u8 *)(func_001ba9a8(a) + a);
    if (*p < func_001ba458(a)) {
        (*p)++;
        return 1;
    }
    return 0;
}

typedef struct { u8 pad[11]; u8 max; } ItemInfo;
ItemInfo *func_001bb658(s32);

s32 func_001ba458(s32 a) {
    if ((u32)(a - 71) < 48) return 1;
    return func_001bb658(a)->max;
}

typedef struct { u64 x[14]; } Blk112;
extern Blk112 D_00621220; /* src/data/bss_0062.c: Lt2 D_00621220 */
extern Blk112 D_002C5AD0;
void func_001ba520(void);

void func_001ba4a8(void) {
    func_001ba520();
    D_002C5AD0 = D_00621220;
}

/* Declared as a real 2-D array: a cast to s32 (*)[2] does not match. */
extern s32 D_00621308[][2]; /* src/data/bss_0062.c: s32 D_00621308[4] */

void func_001ba778(s32 i, s32 a, s32 b) {
    D_00621308[i][0] = a;
    D_00621308[i][1] = b;
}

extern void *D_003773DC;
extern void *D_003773E0;
extern void *D_003773E4;
extern s32 D_003773EC;
extern s32 D_003772DC;
extern s32 D_003772D8;
extern char D_00490008[];
extern char D_00490018[];
void func_001ba848(void);
void func_001ba850(void);
void func_001ba860(void);
void func_001c06f8(void);
void func_00236f18(void);
void func_001ba6f8(void);
int puts(const char *);

void func_001ba870(void) {
    s32 *cnt;
    D_003773EC = 1;
    D_003773DC = func_001ba848;
    D_003773E0 = func_001ba850;
    D_003773E4 = func_001ba860;
    D_003772DC = 2;
    func_001c06f8();
    func_00236f18();
    func_001ba6f8();
    puts(D_00490008);
    func_001b9c60(D_00490018);
    cnt = &D_003772D8;
    (*cnt)++;
}

typedef struct { u8 ord[8]; s32 n; } Ord8;

void func_001baa20(Ord8 *o) {
    s32 i;
    u8 *p;
    o->n = 0;
    p = &o->ord[7];
    for (i = 7; i >= 0; i--) *p-- = i;
}

typedef struct { u8 pad[0x9B40]; s32 v[10]; } BigAF0;

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

extern char D_00490020[];
void func_001be820(u8 *, u32);
void func_001bef98(char *, char *);

void func_001bab80(s32 n, u8 *p) {
    s32 i;
    for (i = 0; i < n; i++) {
        func_001be820(p, 3952);
        func_001bef98((char *)(p + 80), D_00490020);
        p += 3952;
    }
}

/* Save data block with per-item "seen" flags at +0xAC20. */
typedef struct { u8 pad[0xAC20]; u8 flags[1]; } SaveAC20;
void func_001b9b30(s32);
SaveAC20 *func_00232cc0(s32);
s32 func_001bb260(s32);
s32 func_001ba958(s32);

s32 func_001bb2e0(s32 a) {
    SaveAC20 *s;
    func_001b9b30(a);
    s = func_00232cc0(4);
    if (s->flags[a] == 0 && func_001ba958(func_001bb260(a)) >= 3) s->flags[a] = 1;
    return s->flags[a];
}

extern Str11 D_004900A8;

s32 func_001bb370(void) {
    Str11 ids = D_004900A8;
    u8 *p;
    for (p = ids.c; *p; p++) {
        if (func_001bb2e0(*p) < 4) return 0;
    }
    return 1;
}

extern s32 D_0037A148;
extern s32 D_0037A14C;
extern s32 D_0037A150;
extern s32 D_0037A154;
s32 func_00113008(void);

void func_001bb438(void) {
    s32 *p = &D_0037A14C;
    s32 v;
    D_0037A154 = 0;
    v = func_00113008();
    *p = v;
    D_0037A150 = v;
    D_0037A148 = v;
}

s32 func_001ba3f0(s32);

s32 func_001bb678(void) {
    s32 r = 6;
    if (func_001ba3f0(66) > 0) r = 8;
    if (func_001ba3f0(67) > 0) r = 10;
    return r;
}

u32 func_001bb750(u32 a, u32 b) {
    if (a % b) a += b - a % b;
    return a;
}

u32 func_001bb780(u32 a, u32 b) {
    if (a % b) a -= a % b;
    return a;
}

typedef struct { u8 id; u8 pad[3]; s32 n; } IdCnt;
extern s32 D_00625748;
extern IdCnt D_00625750[];
void func_001b9e40(s32, s32);

void func_001be470(void) {
    s32 i;
    for (i = 0; i < D_00625748; i++) func_001b9e40(D_00625750[i].id, D_00625750[i].n);
}

extern u8 *D_006257D0;
void func_001ba108(void *, s32);
s32 func_001ba9d8(s32);
void func_001bcd10(void *, s32);

void func_001be1e8(u8 *p, s32 k) {
    u8 **pp = &p; /* keeps the calls below from becoming tail calls */
    if (p == NULL) p = D_006257D0;
    func_001be820(p, 3952);
    if (!(k & 0x80)) {
        if (k < 10) func_001bcd10(D_006257D0, func_001ba9d8(k));
    } else {
        func_001ba108(p, k & 0x7f);
    }
}

s32 func_001be680(void) {
    if (func_001ba3f0(70)) return 200;
    return func_001ba3f0(69) ? 150 : 100;
}

s32 func_001be6c8(void) {
    if (func_001ba3f0(70)) return 6;
    return func_001ba3f0(69) ? 4 : 2;
}

s32 func_001be710(void) {
    if (func_001ba3f0(70)) return 10;
    return func_001ba3f0(69) ? 6 : 4;
}

/* Zero n bytes (the head loop clears p & 7 bytes, as in the original). */
void func_001be820(u8 *p, u32 n) {
    u32 i;
    for (i = (u32)p & 7; i != 0; i--) {
        *p++ = 0;
        n--;
    }
    while (n >= 8) {
        *(u64 *)p = 0;
        n -= 8;
        p += 8;
    }
    while (n != 0) {
        *p++ = 0;
        n--;
    }
}

/* Stack of 16 quadwords with a parallel s32 value per entry. The char member
 * makes the quadword stores alias n, as in the original (n is reloaded). */
typedef union { u128 q; u8 c[16]; } Q16;
typedef struct {
    Q16 q[16];      /* 0x000 */
    s32 val[16];    /* 0x100 */
    s32 cur;        /* 0x140 */
    Q16 *top;       /* 0x144 */
    s32 n;          /* 0x148 */
} QStack;

void func_001be758(QStack *s, s32 v, u128 q) {
    s32 i = s->n;
    s->val[i] = v;
    s->q[i].q = q;
    s->cur = v;
    s->top = &s->q[s->n];
    s->n++;
}

void func_001be798(QStack *s, u128 q) {
    s->n--;
    s->q[s->n - 1].q = q;
    s->top = &s->q[s->n - 1];
    s->cur = s->val[s->n - 1];
}

void func_001be988(f32 *out, f32 *a, f32 *b, s32 num, s32 den) {
    f32 t = (f32)num / (f32)den;
    s32 i;
    for (i = 0; i < 4; i++) out[i] = (b[i] - a[i]) * t + a[i];
}

float sqrtf(float);

f32 func_001bee80(f32 *a, f32 *b) {
    f32 d[3];
    d[0] = a[0] - b[0];
    d[1] = a[1] - b[1];
    d[2] = a[2] - b[2];
    return sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
}

void func_001bef40(char *d, char *s, char *t) {
    while (*s) *d++ = *s++;
    while (*t) *d++ = *t++;
    *d = 0;
}

void func_001bef98(char *d, char *s) {
    while (*s) *d++ = *s++;
    *d = 0;
}

/* Piecewise-linear lookup in {time, value} keys ending with a negative time. */
typedef struct { s32 t; f32 v; } Key;

f32 func_001befc8(s32 t, Key *k) {
    s32 pt = 0;
    f32 pv = 0.0f;
    for (; k->t >= 0; k++) {
        if (t == k->t) return k->v;
        if (t < k->t) return (k->v - pv) * ((f32)(t - pt) / (f32)(k->t - pt)) + pv;
        pv = k->v;
        pt = k->t;
    }
    return 0.0f;
}

/* needs make: uses rodata */

/* Jump table (jtbl_00490070); checked word-for-word except the table relocs. */
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
#include "data/bss_0061_typed.h"
#include "data/data_0037.h"
#include "data/data_0048.h"
#include "data/data_0049.h"
#include "data/pieces/D_00373060.h"
#include "data/pieces/D_004900A8.h"
