/* Hand-matched functions in 0x001a0000-0x001c0000 (worker 13). */
#include "common.h"

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

typedef unsigned int u128 __attribute__((mode(TI)));
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
typedef union GsTag {
    u128 q;
    struct { u32 w0; union GsTag *next; union GsTag *tail; u32 w3; } s;
} GsTag;
extern GsTag D_0061EEA0[];  /* 16 priority list heads (followed by the tag pool) */
extern GsTag D_0061EFA0[];  /* 256 priority list heads */
extern GsTag D_0061FFA0[];  /* 16 priority list heads */

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

extern f32 D_00372800[16];

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
extern s32 D_00372EA8[];
extern s8 D_00372F28;
extern s32 D_00372F30[];

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
