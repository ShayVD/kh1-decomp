/* The KeTh helpers (docs/modules.md "Session 49"), with keth.nostrict.c and
 * kethdraw.nostrict.c: the pppKeTh* classes keep chains of nodes, each a
 * header and a strip of 48-byte entries, taken from fixed-size pools.
 * func_001a8920 builds a pool (the pppKeThRes*Con classes: n blocks of
 * (sz - 1) * 48 + 128 bytes) and func_001a8900 takes a block from its free
 * list; func_001a89f0 starts a node at the head of a group (pppKeThFrame);
 * func_001a8828 unlinks one after marking its entries' children
 * (func_001a67b8), func_001a8988 frees a whole list.  "Th" is the classes'
 * own abbreviation; a thread / trail reading is a guess.
 * Read from the code, not proved by a boot. */
#include "m2c.h"

void func_001a67b8(void *arg0, s32 arg1) {
  void *var_v1;
  int new_var;
  new_var = arg1 | 8;
  var_v1 = *((void **) (((s8 *) arg0) + 0x18));
  if (var_v1 != 0)
  {
    do
    {
      *((s32 *) (((s8 *) var_v1) + 0xC)) = 0;
      *((u16 *) (((s8 *) var_v1) + 0x3E)) = (u16) ((*((u16 *) (((s8 *) var_v1) + 0x3E))) | new_var);
      var_v1 = *((void **) (((s8 *) var_v1) + 8));
    }
    while (var_v1 != 0);
  }
}

typedef struct Lnk { u8 p0[8]; struct Lnk *next; struct Lnk *pprev; } Lnk;
typedef struct { u8 p[48]; } Ent48;
typedef struct {
    u8 p0[8]; Lnk *next; Lnk *pprev; u8 p10[36];
    u16 h34; u8 p36[2]; u16 h38; u8 p3a[2]; u16 h3c; u16 h3e;
    Ent48 e[1];
} Hdr9;

void func_001a8828(Hdr9 *h) {
    Ent48 *e = h->e;
    s32 n = h->h3c;
    s32 f = h->h3e & 0x20;
    for (; n > 0; n--) func_001a67b8((void *)e++, f);
    e = &h->e[h->h34];
    for (n = h->h38; n > 0; n--) func_001a67b8((void *)e++, f);
    if (h->pprev) {
        if (h->next) h->next->pprev = h->pprev;
        *(Lnk **)h->pprev = h->next;
    }
}

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

void func_001a8988(M2C_UNK **arg0, void *arg1) {
  M2C_UNK *new_var;
  M2C_UNK *temp_s0;
  M2C_UNK *var_s1;
  var_s1 = *arg0;
  if (var_s1 != 0)
  {
    do
    {
      temp_s0 = var_s1;
      var_s1 = (M2C_UNK *)*var_s1;
      new_var = temp_s0;
      func_001a8828((Hdr9 *)new_var);
 do { *new_var = (M2C_UNK)*((M2C_UNK **) (((s8 *) arg1) + 4)); } while (0);
      *((M2C_UNK **) (((s8 *) arg1) + 4)) = new_var;
    }
    while (var_s1 != 0);
  }
  *arg0 = 0;
}

typedef struct DL { struct DL *next; struct DL *prev; } DL;
typedef struct { DL l; u8 p8[40]; s32 w30; u8 p34[10]; u16 h3e; u8 e40[28]; s32 w5c; u8 e60[32]; } Hdr10;
typedef struct { DL *next; u8 f; } Grp10;
typedef struct { u8 p0; u8 n; } Pool10;
typedef struct { Hdr10 *h; u8 n; } Bld10;
void func_001a8780(Bld10 *);
void func_001a9098(void *, s32);

void func_001a89f0(Grp10 *g, Pool10 *pl, s32 a, s32 b) {
    Hdr10 *h = (Hdr10 *)func_001a8900((Pool *)pl);
    Bld10 bl;
    s32 fl;
    if (h == NULL) return;
    bl.h = h;
    bl.n = pl->n;
    fl = 0x100;
    func_001a8780(&bl);
    h->w5c = 0;
    h->w30 = 0;
    if (g->f & 4) fl = 0x180;
    if (g->f & 0x10) fl |= 0x200;
    if (g->f & 8) fl |= 0x400;
    if (g->f & 0x20) fl |= 0x1000;
    h->h3e |= fl;
    func_001a9098(h->e40, a);
    func_001a9098(h->e60, b);
    if (g->next) g->next->prev = &h->l;
    h->l.next = g->next;
    h->l.prev = (DL *)g;
    g->next = &h->l;
}

void func_001a8d78(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 4) = 0;
}
